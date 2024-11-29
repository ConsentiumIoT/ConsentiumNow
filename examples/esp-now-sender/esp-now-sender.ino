#include <esp_now.h>
#include <WiFi.h>

// Structure to hold the data to be sent
typedef struct {
  float data_0;
  float data_1;
} TransmitData;

TransmitData outgoingData; // Variable to store outgoing data

// MAC address of the receiver (replace with the actual MAC address of your receiver ESP32)
uint8_t receiverMac[] = {0x30, 0xC6, 0xF7, 0x14, 0xF7, 0xF0}; 

void setup() {
  Serial.begin(115200);

  // Initialize WiFi in STA mode for ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the receiver's MAC address
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
  outgoingData.data_0 = random(10, 20) + random(0, 100) / 100.0; // Random float for demo
  outgoingData.data_1 = random(30, 40) + random(0, 100) / 100.0; // Random float for demo

  // Send the data
  esp_err_t result = esp_now_send(receiverMac, (uint8_t *)&outgoingData, sizeof(outgoingData));

  // Check the result of the transmission
  if (result == ESP_OK) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.println("Error sending data");
  }

  // Wait before sending the next packet
  delay(2000);
}
