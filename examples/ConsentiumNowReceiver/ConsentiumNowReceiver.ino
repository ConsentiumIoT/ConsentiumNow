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

// Define a custom data structure for incoming data
struct SensorData {
    float data_0; // Placeholder for sensor reading 1
    float data_1; // Placeholder for sensor reading 2
};

// Create ConsentiumNow object with SensorData structure
ConsentiumNow<SensorData> consentiumNow;

void setup() {
    Serial.begin(115200); // Initialize serial communication for debugging
    Serial.println("Consentium IoT - ESP-NOW Receiver");
    Serial.println("----------------------------------");

    // Initialize ESP-NOW communication
    consentiumNow.receiveBegin();

    // Prints host MAC address
    consentiumNow.readMacAddress();

    Serial.println("Waiting for data...");
}

void loop() {
    // Check if new data is available
    if (consentiumNow.isDataAvailable()) {
        // Retrieve and process the received data
        SensorData data = consentiumNow.getReceivedData();

        // Display the received data
        Serial.println("\n--- New Data Received ---");
        Serial.print("Sensor Data 0: ");
        Serial.println(data.data_0);
        Serial.print("Sensor Data 1: ");
        Serial.println(data.data_1);
        Serial.println("--------------------------");
    } else {
        Serial.println("No new data received...");
    }

    delay(2000); // Wait for 2 seconds before checking again
}
