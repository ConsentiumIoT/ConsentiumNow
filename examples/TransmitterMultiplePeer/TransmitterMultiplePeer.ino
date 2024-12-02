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

ConsentiumNow<SensorData> consentiumSender;

// Replace with the receiver's MAC address
uint8_t receiverMac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 

void setup() {
    Serial.begin(115200);

    // Initialize ESP-NOW for sending
    consentiumSender.sendBegin(receiverMac);

    Serial.println("Sender initialized.");
}

void loop() {
    // Prepare sensor data
    SensorData data;
    data.temperature = random(200, 300) / 10.0; // Simulated temperature (20.0 - 30.0)
    data.humidity = random(400, 600) / 10.0;    // Simulated humidity (40.0 - 60.0)

    // Send data
    consentiumSender.sendData(data);

    // Print sent data
    Serial.printf("Sent Data - Temperature: %.2f, Humidity: %.2f\n",
                  data.temperature, data.humidity);

    delay(2000); // Send data every 2 seconds
}
