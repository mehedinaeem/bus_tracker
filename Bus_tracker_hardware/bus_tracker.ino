#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>

// ============== CONFIGURATION ==============
// WiFi credentials
const char* ssid = "Connecting..._5G";
const char* password = "11223344";

// Server URL - Choose one:
// For LOCAL development:
// const char* serverUrl = "http://192.168.0.191:8000/tracker/api/location/";

// For PRODUCTION (Render) - Replace YOUR_APP_NAME with your actual Render app name:
const char* serverUrl = "https://YOUR_APP_NAME.onrender.com/tracker/api/location/";
// ============================================

// Set to true to test without GPS (sends test coordinates)
#define DEBUG_MODE true

#define RXPin 16  
#define TXPin 17  
HardwareSerial gpsSerial(1);  
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n=== ESP32 Bus Tracker Starting ===");
  
  gpsSerial.begin(9600, SERIAL_8N1, RXPin, TXPin);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  
  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < 30) {
    delay(1000);
    Serial.print(".");
    wifiAttempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Server URL: ");
    Serial.println(serverUrl);
  } else {
    Serial.println("\nFailed to connect to WiFi!");
  }
}

void loop() {
  float lat, lng;
  bool hasValidLocation = false;
  
  if (DEBUG_MODE) {
    // Test coordinates (Karachi) - for testing without GPS
    lat = 24.860966;
    lng = 67.001137;
    hasValidLocation = true;
    Serial.println("DEBUG MODE: Using test coordinates");
  } else {
    // Read GPS data
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }

    // Check if GPS location is valid
    if (gps.location.isValid()) {
      lat = gps.location.lat();
      lng = gps.location.lng();
      
      // Only valid if not zero
      if (lat != 0.0 && lng != 0.0) {
        hasValidLocation = true;
      }
    }
    
    if (!hasValidLocation) {
      Serial.println("GPS data not available yet. Waiting for valid data...");
      delay(5000);
      return;
    }
  }

  // If we have valid location data, send it
  if (hasValidLocation) {
    String jsonData = "{\"lat\": " + String(lat, 6) + ", \"lng\": " + String(lng, 6) + "}";
    Serial.println("Sending JSON: " + jsonData);

    // Check WiFi connection status before sending data
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected! Reconnecting...");
      WiFi.begin(ssid, password);
      int attempts = 0;
      while (WiFi.status() != WL_CONNECTED && attempts < 10) {
        delay(1000);
        Serial.print(".");
        attempts++;
      }
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nReconnected to WiFi!");
      } else {
        Serial.println("\nFailed to reconnect.");
        delay(5000);
        return; // Don't proceed if WiFi is still disconnected
      }
    }

    // Send POST request to server
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    Serial.println("Sending POST request...");
    int httpResponseCode = http.POST(jsonData);

    // Log the HTTP response code and server response
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server Response: " + response);
    } else {
      Serial.println("Error sending data!");
      Serial.print("HTTP Error code: ");
      Serial.println(httpResponseCode);
      // Common error codes:
      // -1 = Connection refused/failed
      // -2 = Send header failed
      // -3 = Send payload failed
      // -4 = Not connected
      // -5 = Connection lost
      // -11 = Read timeout
    }
    http.end();
  }

  delay(5000); // Delay before sending the next update
}
