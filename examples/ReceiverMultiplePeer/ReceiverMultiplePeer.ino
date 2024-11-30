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
    int sender_id; // ID of the sender device
};

// Create ConsentiumNow object with SensorData structure
ConsentiumNow<SensorData> consentiumNow;

// List of slave MAC addresses (replace with actual MAC addresses of your slave devices)
const uint8_t slaveAddresses[][6] = {
    {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC}, // MAC address of Slave 1
    {0x24, 0x6F, 0x28, 0xDD, 0xEE, 0xFF}  // MAC address of Slave 2
};

// Number of slaves
const size_t numSlaves = sizeof(slaveAddresses) / sizeof(slaveAddresses[0]);

void setup() {
    Serial.begin(115200); // Initialize serial communication for debugging
    Serial.println("Consentium IoT - ESP-NOW Master Receiver");
    Serial.println("----------------------------------------");

    // Initialize ESP-NOW communication
    if (!consentiumNow.begin()) {
        Serial.println("Failed to initialize ESP-NOW");
        return;
    }

    // Add all slave devices as peers
    for (size_t i = 0; i < numSlaves; i++) {
        if (!consentiumNow.addPeer(slaveAddresses[i])) {
            Serial.print("Failed to add peer: ");
            Serial.println(i);
        } else {
            Serial.print("Peer added: ");
            Serial.print(i);
            Serial.print(" - ");
            for (size_t j = 0; j < 6; j++) {
                Serial.print(slaveAddresses[i][j], HEX);
                if (j < 5) Serial.print(":");
            }
            Serial.println();
        }
    }

    consentiumNow.receiveBegin();
    Serial.println("Waiting for data...");
}

void loop() {
    // Check if new data is available
    if (consentiumNow.isDataAvailable()) {
        // Retrieve and process the received data
        SensorData data = consentiumNow.getReceivedData();

        // Display the received data
        Serial.println("\n--- New Data Received ---");
        Serial.print("Sender ID: ");
        Serial.println(data.sender_id);
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
