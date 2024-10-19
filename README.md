# ESP32WiFiBlueP2P
Simple P2P communication over WiFi  between two Android Phones paired with ESP32 Devices 

This project demonstrates a communication setup between two ESP32 devices using both Bluetooth and Wi-Fi. The server device creates a Wi-Fi access point (AP) and receives data from a client device via Bluetooth. The data is then sent over Wi-Fi using UDP. The client connects to the server's Wi-Fi network and sends data back to the server, creating a bidirectional communication channel.

## Hardware Requirements

- 2 x ESP32 development boards
- USB cables

## Features

- **Bluetooth**: The client sends data to the server via Bluetooth.
- **Wi-Fi**: The server and client communicate via UDP over Wi-Fi.
- **LED Indicator**: The server uses an LED to indicate when data is received over Bluetooth.
- **Wi-Fi AP and STA Modes**: The server operates in AP mode, while the client operates in STA mode.


- **Bluetooth**: The client sends data to the server via Bluetooth.
- **Wi-Fi**: The server and client communicate via UDP over Wi-Fi.
- **LED Indicator**: The server uses an LED to indicate when data is received over Bluetooth.
- **Wi-Fi AP and STA Modes**: The server operates in AP mode, while the client operates in STA mode.

## Setup

### Server ESP32

1. **Configure the Server**
   - The server creates a Wi-Fi access point with the specified SSID and password.
   - It listens for data over Bluetooth and sends the data over UDP to the client.
   - A LED on GPIO 2 will light up when Bluetooth data is received.
  
2. This code still need an app(from the Android side) to send and receive the data over bluetooth.
