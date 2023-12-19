#include <Arduino.h>
#include "Screen.h"
#include "NodeDB.h" // For network status
#include "MeshTypes.h" // For node information types

class InfoScreen {
public:
    InfoScreen(graphics::Screen& screen);
    void display();

private:
    graphics::Screen& screen;
    void displayNetworkInfo();
    void displayDeviceInfo();
};

InfoScreen::InfoScreen(graphics::Screen& screen) : screen(screen) {
    // Initialization if needed
}

void InfoScreen::display() {
    displayNetworkInfo();
    displayDeviceInfo();
}

void InfoScreen::displayNetworkInfo() {
    // Example: Display information about each node in the network
    uint32_t readIndex = 0;
    const meshtastic_NodeInfoLite* nodeInfo;
    while ((nodeInfo = NodeDB::readNextMeshNode(readIndex)) != NULL) {
        screen.print("Node: " + String(nodeInfo->num));
        screen.print("Last Heard: " + String(nodeInfo->last_heard));
        screen.print("SNR: " + String(nodeInfo->snr));
        // Add more details as needed
    }
}

void InfoScreen::displayDeviceInfo() {
    // Display device-specific information
    // Example: Device ID, Firmware Version, etc.
    screen.print("Device ID: " + String(myNodeInfo.my_node_num));
    screen.print("Firmware: " + String(FIRMWARE_VERSION));
    // Add more device information as needed
}
