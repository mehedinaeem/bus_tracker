# from django.http import JsonResponse
# from django.shortcuts import render
# from django.views.decorators.csrf import csrf_exempt
# import json
# from .models import GPSData



# # its for check server and module work...humidity
# latest_data = {"temperature": None, "humidity": None}  # Store latest values

# def weather_page(request):
#     return render(request, 'gsm/weather.html')

# @csrf_exempt
# def receive_data(request):
#     global latest_data
#     if request.method == "POST":
#         try:
#             data = json.loads(request.body.decode('utf-8'))
#             latest_data["temperature"] = data.get("temperature")
#             latest_data["humidity"] = data.get("humidity")

#             print(f"Received Data: Temperature={latest_data['temperature']}, Humidity={latest_data['humidity']}")
#             return JsonResponse({"status": "success", "data": latest_data})
#         except json.JSONDecodeError:
#             return JsonResponse({"status": "error", "message": "Invalid JSON"}, status=400)
#     else:
#         return JsonResponse({"status": "success", "data": latest_data})  # Returns latest data for frontend



# # check gps value...store in database
# # @csrf_exempt
# # def receive_data(request):
# #     if request.method == "POST":
# #         try:
# #             data = json.loads(request.body.decode('utf-8'))
# #             latitude = data.get("latitude")
# #             longitude = data.get("longitude")

# #             if latitude is None or longitude is None:
# #                 return JsonResponse({"status": "error", "message": "Missing latitude or longitude"}, status=400)

# #             gps_entry = GPSData(latitude=latitude, longitude=longitude)
# #             gps_entry.save()

# #             print(f"Received GPS Data: Latitude={latitude}, Longitude={longitude}")
# #             return JsonResponse({"status": "success", "data": {"latitude": latitude, "longitude": longitude}})
# #         except json.JSONDecodeError:
# #             return JsonResponse({"status": "error", "message": "Invalid JSON"}, status=400)
# #     else:
# #         return JsonResponse({"status": "failure", "message": "Use POST instead"}, status=405)
    
    
# # show data in frontend..map
# def get_gps_data(request):
#     gps_entries = GPSData.objects.order_by('-timestamp')[:10]  # Get last 10 entries
#     data = [{"latitude": entry.latitude, "longitude": entry.longitude} for entry in gps_entries]
#     return JsonResponse(data, safe=False)



# def map_view(request):
#     return render(request, 'gsm/map.html')

