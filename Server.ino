#include <WiFi.h>
#include <WiFiUdp.h>
#include <BluetoothSerial.h>

const char *ssid = "ser";
const char *password = "pass";
const unsigned int localPort = 8888; // local port to listen on
const char *host = "192.168.4.2"; // Client IP address

BluetoothSerial SerialBT;
WiFiUDP udp;

#define LED_PIN 2 // LED pin number

void setup() {
  Serial.begin(115200);

  if (!SerialBT.begin("ESP32_BT_Server")) {
    Serial.println("Bluetooth initialization failed");
  } else {
    Serial.println("Bluetooth initialized");
  }
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP started");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(IP);

  pinMode(LED_PIN, OUTPUT); // Set LED pin as output
  digitalWrite(LED_PIN, LOW); // Initially turn off the LED

  udp.begin(localPort);
}

void loop() {
  // Check for incoming Bluetooth data
  if (SerialBT.available()) {
    String receivedData = SerialBT.readString();
    Serial.print("Received via Bluetooth: ");
    Serial.println(receivedData);
    digitalWrite(LED_PIN, HIGH); // Turn LED on when data received

    // Send the received data over Wi-Fi to the client
    udp.beginPacket(host, localPort);
    udp.write((uint8_t *)receivedData.c_str(), receivedData.length());
    udp.endPacket();
    Serial.println("Data sent over Wi-Fi");
  }
  delay(10); // Delay a short while before continuing
  digitalWrite(LED_PIN, LOW); // Turn LED off after send

  // Check for incoming UDP packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char buffer[255];
    int length = udp.read(buffer, sizeof(buffer));
    buffer[length] = 0; // Null-terminate the received string
    Serial.print("Received via Wi-Fi: ");
    Serial.println(buffer);
  }
}