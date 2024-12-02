#include "ConsentiumNow.h"

// Static member definitions
template <typename DataType>
DataType ConsentiumNow<DataType>::incomingData = {};

template <typename DataType>
bool ConsentiumNow<DataType>::dataAvailable = false;

// Constructor
template <typename DataType>
ConsentiumNow<DataType>::ConsentiumNow() {}

// Read and print the MAC address of the ESP32
template <typename DataType>
void ConsentiumNow<DataType>::readMacAddress() {
    WiFi.mode(WIFI_STA);
    WiFi.begin();
    uint8_t baseMac[6];
    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
    if (ret == ESP_OK) {
        Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
        Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                      baseMac[0], baseMac[1], baseMac[2],
                      baseMac[3], baseMac[4], baseMac[5]);
        Serial.println();
    } else {
        Serial.println("Failed to read MAC address");
    }
}

// Initialize ESP-NOW for receiving
template <typename DataType>
void ConsentiumNow<DataType>::receiveBegin() {
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the receive callback function
    esp_now_register_recv_cb(onDataReceive);

    Serial.println("ESP-NOW initialized for receiving.");
}

// Add a peer to the ESP-NOW network
template <typename DataType>
bool ConsentiumNow<DataType>::addPeer(const uint8_t *macAddress) {
    esp_now_peer_info_t peerInfo = {};
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, macAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return false;
    }

    // Add the sender's MAC address to the list
    senderMacs.push_back({macAddress[0], macAddress[1], macAddress[2],
                          macAddress[3], macAddress[4], macAddress[5]});
    Serial.println("Peer added successfully");
    return true;
}

// Initialize ESP-NOW for sending
template <typename DataType>
void ConsentiumNow<DataType>::sendBegin(const uint8_t *receiverMac) {
    memcpy(peerMac, receiverMac, 6);
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

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

// Send data to a predefined peer
template <typename DataType>
void ConsentiumNow<DataType>::sendData(const DataType &data) {
    esp_err_t result = esp_now_send(peerMac, reinterpret_cast<const uint8_t *>(&data), sizeof(data));
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

        Serial.printf("Data received from MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
                      info->src_addr[0], info->src_addr[1], info->src_addr[2],
                      info->src_addr[3], info->src_addr[4], info->src_addr[5]);
    } else {
        Serial.println("Received data size mismatch.");
    }
}
