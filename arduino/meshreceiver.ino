#include <ESP8266WiFi.h>


void setup() {
  Serial.begin(19200);     // Initialize serial for debugging
  Serial1.begin(19200, SERIAL_8N1, SERIAL_FULL, 1, 3);


  delay(1000);  // Allow time for the serial port to initialize
}

void loop() {
  // Send AT command to SIM900
  Serial1.println("AT");
  delay(1000);  // Wait for response
  printSerialData();  // Print serial data received from SIM900

  // Send AT+CSQ command to get signal strength
  Serial1.println("AT+CSQ");
  delay(1000);  // Wait for response
  printSerialData();  // Print serial data received from SIM900

  // Send AT+CREG? command to check network registration status
  Serial1.println("AT+CREG?");
  delay(1000);  // Wait for response
  printSerialData();  // Print serial data received from SIM900

  // Add more AT commands as needed
  // ...

  delay(5000);  // Wait 5 seconds before sending next set of AT commands
}

void printSerialData() {
  // Check if data is available from SIM900
  while (Serial1.available()) {
    char c = Serial1.read();
    Serial.write(c);  // Print received data for debugging
  }
}
