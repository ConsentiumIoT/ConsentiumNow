#include "ConsentiumNow.h"

// Static member definitions
template <typename DataType>
DataType ConsentiumNow<DataType>::incomingData = {};

template <typename DataType>
bool ConsentiumNow<DataType>::dataAvailable = false;

// Constructor
template <typename DataType>
ConsentiumNow<DataType>::ConsentiumNow() {}

// Initialize ESP-NOW for receiving
template <typename DataType>
void ConsentiumNow<DataType>::receiveBegin() {
    // Initialize WiFi in STA mode for ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the receive callback function
    esp_now_register_recv_cb(onDataReceive);

    Serial.println("ESP-NOW initialized for receiving.");
}

// Initialize ESP-NOW for sending
template <typename DataType>
void ConsentiumNow<DataType>::sendBegin(const uint8_t *receiverMac) {
    memcpy(peerMac, receiverMac, 6);
    // Initialize WiFi in STA mode
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the receiver's MAC address
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverMac, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    Serial.println("ESP-NOW initialized and peer registered successfully");
}


// Check if new data has been received
template <typename DataType>
bool ConsentiumNow<DataType>::isDataAvailable() {
    return dataAvailable;
}

// Retrieve the latest received data
template <typename DataType>
DataType ConsentiumNow<DataType>::getReceivedData() {
    dataAvailable = false; // Reset the flag
    return incomingData;
}

// Template member function for sending data
template <typename DataType>
void ConsentiumNow<DataType>::sendData(const DataType &data) {
    esp_err_t result = esp_now_send(peerMac, reinterpret_cast<const uint8_t*>(&data), sizeof(data));

    if (result == ESP_OK) {
        Serial.println("Data sent successfully!");
    } else {
        Serial.printf("Error sending data: %d\n", result);
    }
}


// Static callback function for receiving data
template <typename DataType>
void ConsentiumNow<DataType>::onDataReceive(const esp_now_recv_info_t *info, const uint8_t *incoming, int len) {
    if (len == sizeof(DataType)) {
        memcpy(&incomingData, incoming, sizeof(DataType));
        dataAvailable = true;
        Serial.println("Data received successfully.");
    } else {
        Serial.println("Received data size mismatch.");
    }
}