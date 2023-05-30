#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Myhotspot";
const char* password = "12345678";
const char* host = "localhost";
const int port = 3000;
const char* serverIP = "192.168.1.101";  // Replace with the IP address of your Python server
WiFiServer server(port);


void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Setup end");
  server.begin();
}

String listenComputer(String msg) {
  Serial.println("in listen computer");
  WiFiClient client;
  if (client.connect(serverIP, 3000)) {
    Serial.println("Connected to server");

    // Send data to the server
    if (msg != "") {
      client.println(msg);
    }
    
    // Receive and print the response from the server
    
      String response = client.readStringUntil('\r');
      Serial.println(response);
      return response;


  } else {
    Serial.println("Connection to server failed");
    return "";
  }
  client.stop();
  return "";
}

void loop() {
  // Your code here
  String str = listenComputer("");
  sendToArduino(str);
  listenArduino();
  delay(1000);
}

void sendToArduino(String str) {
  Serial.print(str);
}


void listenArduino() {
  if (Serial.available()) {
    String message = Serial.readStringUntil('@');
    listenComputer(message);
  }
}
