#include <QApplication>
#include <QPushButton>
#include <QDebug> // For printing to the console

int main(int argc, char *argv) {
    QApplication a(argc, argv); // Create the application object

    QPushButton *button = new QPushButton("Click Me!"); // Create a button

    // Connect the button's clicked signal to a lambda function
    QObject::connect(button, &QPushButton::clicked,() {
        qDebug() << "Button clicked!"; // Print to the console
        // You could put other actions here, like changing the text,
        // opening a new window, etc.
    });

    button->show(); // Make the button visible

    return a.exec(); // Start the event loop
}