#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "your_SSID";         // Replace with your network SSID
const char* password = "your_PASSWORD"; // Replace with your network password

const char* serverUrl = "http://your_server_ip:3000/data"; // Replace with your Node.js server IP and port

WiFiClient client;  // Create a WiFiClient object

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(client, serverUrl); // Pass WiFiClient object and URL

    http.addHeader("Content-Type", "application/json");

    // Data to send (adjust the JSON structure to match your needs)
    String jsonData = "{\"value\":\"test_data\"}";

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Free resources

  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(60000); // Send data every minute (adjust as needed)
}
