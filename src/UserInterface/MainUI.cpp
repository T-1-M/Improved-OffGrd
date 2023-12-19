#include <Arduino.h>
#include "Screen.h" // Meshtastic screen management
#include "InputBroker.h" // Input handling
#include "GPS.h" // GPS functionality
#include "MeshService.h" // Mesh networking
#include "Power.h" // Battery status
#include "Compass.h" // Compass functionality
#include "Channels.h" // Channel management

namespace graphics {
    class Screen; // Forward declaration from Meshtastic firmware
}

class MainScreen : public Observer<const InputEvent*> {
public:
    MainScreen();
    void display();
    void handleInput(const InputEvent& event);

private:
    graphics::Screen screen;
    void displayHeader();
    void displayMenu();
};

MainScreen::MainScreen() : screen(/* parameters for screen initialization */) {
    screen.setup();
    // Initialize and register with InputBroker
    inputBroker = new InputBroker();
    inputBroker->registerSource(this); // Register this class as an observer
}

void MainScreen::display() {
    displayHeader();
    displayMenu();
}

void MainScreen::displayHeader() {
    // Display GPS location
    GPSData gpsData = GPS::getCoordinates();
    screen.print("GPS: " + String(gpsData.latitude) + ", " + String(gpsData.longitude));

    // Display Current Time from GPS
    TimeData timeData = GPS::getCurrentTime();
    screen.print("Time: " + String(timeData.hour) + ":" + String(timeData.minute) + ":" + String(timeData.second));

    // Display Battery Status
    const meshtastic::PowerStatus* powerStatus = power->newStatus.getValue();
    int batteryPercent = powerStatus ? powerStatus->getBatteryChargePercent() : 0;
    screen.print("Battery: " + String(batteryPercent) + "%");

    // Display Current Channel Name
    const char* channelName = Channels::getName(Channels::getPrimaryIndex());
    screen.print("Channel: " + String(channelName));
}

void MainScreen::displayMenu() {
    screen.print("1. Info");
    screen.print("2. Messages");
    screen.print("3. GPS");
    screen.print("4. Settings");
    screen.print("5. Emergency Alert");
}

void MainScreen::handleInput(const InputEvent& event) {
    // Example implementation for handling input events
    switch(event.type) {
        case InputEvent::Type::ButtonPress:
            // Handle button press events
            // Example: if (event.key == '1') { /* Handle '1' key press */ }
            break;
        // Handle other types of input events
    }
}

void setup() {
    MainScreen mainScreen;
    mainScreen.display();
}

void loop() {
    InputEvent event = InputBroker::getInputEvent();
    mainScreen.handleInput(event);
    // Include other loop functionalities if necessary
}
