#include <WiFi.h>
#include <WiFiUdp.h>
#include <BluetoothSerial.h>

const unsigned int localPort = 8888; // Local port to listen on
const char *host = "192.168.4.1";  // Server IP address (replace with your server IP)

BluetoothSerial SerialBT;
WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  delay(1000); // Give some time for the Serial monitor to start

  // Initialize Bluetooth
  if (!SerialBT.begin("ESP32_Bluetooth_Client")) {
    Serial.println("Bluetooth initialization failed");
    while (1); // Halt further execution
  }
  Serial.println("Bluetooth Initialized");

  // Start Wi-Fi in Station mode (we will scan for networks first)
  WiFi.mode(WIFI_STA);
  delay(1000); // Wait for a second

  // Scan for available networks
  Serial.println("Scanning for available Wi-Fi networks...");
  int n = WiFi.scanNetworks();
  Serial.println("Scan complete.");
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.println("Available networks:");
    for (int i = 0; i < n; i++) {
      // Print SSID and signal strength for each network
      Serial.printf("%d: %s (%ddBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    }
  }

  // Connect to Wi-Fi after displaying available networks
  const char *ssid = "ser"; // Replace with selected network SSID
  const char *password = "pass"; // Replace with network password
  Serial.println("Connecting to Wi-Fi...");

  WiFi.begin(ssid, password);

  // Check for Wi-Fi connection
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) { // Limit attempts to prevent hanging
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to Wi-Fi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Start listening for UDP packets
    udp.begin(localPort);
    Serial.println("UDP listening on port " + String(localPort));
  } else {

    Serial.println("\nFailed to connect to Wi-Fi. Check SSID and Password.");
    while (1); // Halt further execution if not connected
  }
}

void loop() {
  // Check for incoming Bluetooth data
  if (SerialBT.available()) {
    String message = SerialBT.readString();
    Serial.printf("Sending via UDP: %s\n", message.c_str());

    // Send the received data over UDP
    udp.beginPacket(host, localPort);
    
    // Convert String to byte array and send
    udp.write((uint8_t *)message.c_str(), message.length());
    
    udp.endPacket();
    Serial.println("Data sent via UDP");
  }

  // Check for incoming UDP packets
  
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char buffer[255];
    int length = udp.read(buffer, sizeof(buffer));
    buffer[length]=0;
    Serial.printf("Received via UDP: %s\n", buffer);
    } 
  
  
}
