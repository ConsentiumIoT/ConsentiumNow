#ifndef CONSENTIUM_NOW_H
#define CONSENTIUM_NOW_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <vector>

template <typename DataType>
class ConsentiumNow {
private:
    static DataType incomingData;        // Holds the received data
    static bool dataAvailable;           // Flag for new data availability
    static void onDataReceive(const esp_now_recv_info_t *info, const uint8_t *incoming, int len);

public:
    ConsentiumNow();                     // Constructor
    void receiveBegin();                 // Initialize ESP-NOW for receiving
    void sendBegin(const uint8_t *peerMac); // Initialize ESP-NOW for sending
    bool addPeer(const uint8_t *macAddress);
    void readMacAddress();
    static bool isDataAvailable();       // Check if new data is available
    static DataType getReceivedData();   // Retrieve received data
    void sendData(const DataType &data); // Send data to a predefined peer

private:
    uint8_t peerMac[6];                  // MAC address of a specific peer for sending
    std::vector<std::array<uint8_t, 6>> senderMacs; // List of MAC addresses for senders
};

#include "ConsentiumNow.tpp"
#endif
