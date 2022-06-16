#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "tangible-material-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "DbVKa4bsB9nty2B92hpvNhNlGW6pBedpYNYLBwcM"
#define WIFI_SSID "F6E4-HCH"
#define WIFI_PASSWORD "da749651henry"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Connected!");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String message = Serial.readString();
    Firebase.setString("message", message);
    if (Firebase.failed()) {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());  
        return;
    }
  }
}
