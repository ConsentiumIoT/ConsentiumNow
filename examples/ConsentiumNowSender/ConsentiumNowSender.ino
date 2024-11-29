#include <ConsentiumNow.h>

// Define the custom data structure
struct SensorData {
    float data_0;
    float data_1;
};

// Create ConsentiumNow object for sending
ConsentiumNow<SensorData> consentiumNow;

// MAC address of the receiver (replace with the actual MAC address)
uint8_t receiverMac[] = {0x7C, 0x9E, 0xBD, 0x66, 0x7A, 0x0C};

void setup() {
    Serial.begin(115200);

    // Initialize ConsentiumNow for sending
    consentiumNow.sendBegin(receiverMac);
}

void loop() {
    // Prepare data to send
    SensorData dataToSend;
    dataToSend.data_0 = random(10, 20) + random(0, 100) / 100.0; // Random float
    dataToSend.data_1 = random(30, 40) + random(0, 100) / 100.0; // Random float

    // Send the data
    consentiumNow.sendData(dataToSend);

    // Log sent data for reference
    Serial.print("Sent Data 0: ");
    Serial.println(dataToSend.data_0);
    Serial.print("Sent Data 1: ");
    Serial.println(dataToSend.data_1);

    // Wait before sending the next packet
    delay(2000);
}
