#include <SoftwareSerial.h>
#include <painlessMesh.h>
#include <TinyGPS++.h>

// Mesh network credentials
#define MESH_PREFIX "meshPrefix"
#define MESH_PASSWORD "password"
#define MESH_PORT 5555 // Mesh network port

// Define SoftwareSerial object for NEO-6M GPS module
SoftwareSerial gpsSerial(D2, D1); // RX, TX

// Create a painlessMesh object
painlessMesh mesh;

// Create a TinyGPS++ object
TinyGPSPlus gps;

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 5000; // Send data every 5 seconds

void receivedCallback(uint32_t from, String &msg) {
  // Do nothing for now
}

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  gpsSerial.begin(9600); // Initialize SoftwareSerial communication for GPS module

  // Initialize painlessMesh
  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.setRoot(true); // This node acts as the root node of the mesh network
}

void loop() {
  // Read characters from NEO-6M GPS module
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read()); // Feed characters to TinyGPS++ object
  }

    // If a complete GPS sentence is parsed and 5 seconds have elapsed, send data
    if (gps.location.isValid() && gps.time.isValid()) {
      // Construct the message string with latitude, longitude, and timestamp in URL query string format
      String message = "latitude=" + String(gps.location.lat(), 6) +
                      "&longitude=" + String(gps.location.lng(), 6) +
                      "&timestamp=" + formatTime(gps.time.hour()) + "%3A" +
                      formatTime(gps.time.minute()) + "%3A" +
                      formatTime(gps.time.second());

      // Send the message over the mesh network
      mesh.sendBroadcast(message);
      Serial.println("Sending:" + message);
    }

  // Update mesh network
  mesh.update();
}

// Function to format time value with leading zeros if needed
String formatTime(int timeValue) {
  if (timeValue < 10) {
    return "0" + String(timeValue);
  } else {
    return String(timeValue);
  }
}
