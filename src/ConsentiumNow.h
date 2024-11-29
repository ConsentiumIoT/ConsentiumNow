#ifndef CONSENTIUM_NOW_H
#define CONSENTIUM_NOW_H

#include <esp_now.h>
#include <WiFi.h>

template <typename DataType>
class ConsentiumNow {
private:
    static DataType incomingData;     // Holds the received data
    static bool dataAvailable;        // Flag for new data availability
    static void onDataReceive(const esp_now_recv_info_t *info, const uint8_t *incoming, int len);

public:
    ConsentiumNow();                  // Constructor
    void receiveBegin();              // Initialize ESP-NOW for receiving
    void sendBegin(const uint8_t *peerMac); // Initialize ESP-NOW for sending

    static bool isDataAvailable();    // Check if new data is available
    static DataType getReceivedData();// Retrieve received data
    void sendData(const DataType &data); // Send data to a predefined peer

private:
    uint8_t peerMac[6];               // MAC address of the peer device
};

#include "ConsentiumNow.tpp"
#endif
