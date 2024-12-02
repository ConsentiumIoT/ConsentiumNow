# ConsentiumNow Library for ESP-NOW Communication

The **ConsentiumNow** library provides seamless and efficient ESP-NOW communication between ESP32-compatible devices. It is designed for Consentium IoT solutions, enabling reliable data exchange using custom data structures.

---

## Features

- Lightweight and flexible ESP-NOW integration.
- Support for user-defined custom data structures.
- Efficient communication for IoT applications.
- Easy-to-use API for both sending and receiving data.

---

## Getting Started

### Prerequisites

- ESP32-compatible board.
- Arduino IDE installed and configured for ESP32 development.
- Basic knowledge of ESP-NOW communication protocol.

---

### Installation

1. Clone or download this repository to your local machine.
2. Include the `ConsentiumNow` library in your Arduino IDE.
   - Go to **Sketch > Include Library > Add .ZIP Library**.
   - Select the downloaded `ConsentiumNow` library.

---

## Usage

### 1. Sender Example

```cpp
#include <ConsentiumNow.h>

// Define the data structure
struct SensorData {
    float temperature;
    float humidity;
};

// Create an instance of ConsentiumNow for the custom structure
ConsentiumNow<SensorData> consentiumSender;

// Replace with the receiver's MAC address
uint8_t receiverMac[] = {0x7C, 0x9E, 0xBD, 0x66, 0x7A, 0x0C}; 

void setup() {
    Serial.begin(115200);
    consentiumSender.sendBegin(receiverMac);
    Serial.println("Sender initialized.");
}

void loop() {
    SensorData data;
    data.temperature = random(200, 300) / 10.0; // Random temperature (20.0 - 30.0°C)
    data.humidity = random(400, 600) / 10.0;    // Random humidity (40.0 - 60.0%)

    consentiumSender.sendData(data);
    Serial.printf("Sent Data - Temperature: %.2f, Humidity: %.2f\n", 
                  data.temperature, data.humidity);
    delay(2000);
}
```

---

### 2. Receiver Example

```cpp
#include <ConsentiumNow.h>

// Define the data structure
struct SensorData {
    float temperature;
    float humidity;
};

// Create an instance of ConsentiumNow for receiving data
ConsentiumNow<SensorData> consentiumReceiver;

void setup() {
    Serial.begin(115200);
    consentiumReceiver.receiveBegin();
    Serial.println("Receiver initialized and ready.");
}

void loop() {
    if (consentiumReceiver.isDataAvailable()) {
        SensorData data = consentiumReceiver.getReceivedData();
        Serial.printf("Received Data - Temperature: %.2f, Humidity: %.2f\n", 
                      data.temperature, data.humidity);
    }
    delay(500);
}
```

---

## Advanced Examples

### Multi-Sender to One Receiver

- Configure multiple senders and their respective MAC addresses in the receiver.

### Custom Data Structures

- Modify the `struct` definitions to fit your application (e.g., adding new fields).

### Debugging

Use `Serial` outputs to monitor the transmission and reception status.

---

## Documentation and Support

- Tutorials and detailed documentation: [Consentium IoT Docs](https://docs.consentiumiot.com)
- For inquiries or support, email: [official@consentiumiot.com](mailto:official@consentiumiot.com)

---

## License

This project is licensed under the MIT License. Redistribution must include the license header. For details, refer to the `LICENSE` file.

---

## Acknowledgments

Thanks to the Consentium IoT community for their contributions and feedback.

Happy coding with ConsentiumNow! 🚀