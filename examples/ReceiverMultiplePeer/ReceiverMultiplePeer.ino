/***************************************************
  Consentium IoT - ConsentiumNow Library
  -------------------------------------------------
  This library enables seamless ESP-NOW communication 
  between ESP32-compatible devices. Designed for use 
  with Consentium IoT solutions, it supports custom 
  data structures and reliable data transfer.

  Features:
  - Lightweight and flexible ESP-NOW integration
  - Support for custom user-defined data structures
  - Efficient communication protocol for IoT applications

  Tutorials and Documentation:
  Visit us at: https://docs.consentiumiot.com

  For Support:
  Email: official@consentiumiot.com

  MIT license - Redistribution must include this header.
 ***************************************************/

#include <ConsentiumNow.h>

// Define the data structure to be exchanged
struct SensorData {
    float temperature;
    float humidity;
};

ConsentiumNow<SensorData> consentiumReceiver;

void setup() {
    Serial.begin(115200);

    // Initialize ESP-NOW for receiving
    consentiumReceiver.receiveBegin();

    // Add the MAC addresses of the expected sender boards
    uint8_t sender1Mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t sender2Mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    consentiumReceiver.addPeer(sender1Mac);
    consentiumReceiver.addPeer(sender2Mac);

    Serial.println("Receiver ready to receive data from multiple senders.");
}

void loop() {
    // Check if new data is available
    if (consentiumReceiver.isDataAvailable()) {
        // Retrieve the received data
        SensorData data = consentiumReceiver.getReceivedData();

        // Print the received data
        Serial.printf("Received Data - Temperature: %.2f, Humidity: %.2f\n",
                      data.temperature, data.humidity);
    }

    delay(500); // Add a short delay for stability
}
