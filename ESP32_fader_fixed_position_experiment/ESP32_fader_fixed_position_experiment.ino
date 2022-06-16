// I used this library to control the motor
// https://github.com/vincasmiliunas/ESP32-Arduino-TB6612FNG

/* ------------------------------------------------------------ Motor Declaration ------------------------------------------------------------ */

#include <TB6612FNG.h>

int PWMA = 33;
int INA2 = 25;
int INA1 = 26;
int STBY = 27;
int INB1 = 14;
int INB2 = 12;
int PWMB = 13;

float target;
float average;
float threshold;
bool arrived;

Tb6612fng motor(STBY, INA1, INA2, PWMA);

/* ------------------------------------------------------------ /Motor Declaration/ ------------------------------------------------------------ */

/* ------------------------------------------------------------ Firebase Variables Declaration ------------------------------------------------------------ */

// Library: 
// https://github.com/mobizt/Firebase-ESP32

#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "FluffyPony"
#define WIFI_PASSWORD "fluffyfluffy"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyA6Ziuez3veAC8egz-fNHCMAI2JpbJ2lCQ"

/* 3. Define the RTDB URL */
#define DATABASE_URL "tangible-material-default-rtdb.asia-southeast1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "aabb9052@gmail.com"
#define USER_PASSWORD "fluffyfluffy"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

/* ------------------------------------------------------------ /Firebase Variables Declaration/ ------------------------------------------------------------ */

void setup() {
  pinMode(34, INPUT);
  average = analogRead(34);
  target = 2000;
  threshold = 50;
  arrived = false;

/* ------------------------------------------------------------ Motor Declaration ------------------------------------------------------------ */

  motor.begin();

/* ------------------------------------------------------------ /Motor Declaration/ ------------------------------------------------------------ */

/* ------------------------------------------------------------ Firebase Setup ------------------------------------------------------------ */

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  //////////////////////////////////////////////////////////////////////////////////////////////
  // Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
  // otherwise the SSL connection will fail.
  //////////////////////////////////////////////////////////////////////////////////////////////

  Firebase.begin(&config, &auth);

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

/* ------------------------------------------------------------ /Firebase Setup/ ------------------------------------------------------------ */
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    target = Serial.readString().toFloat();
    arrived = false;
  }

  // Firebase.ready() should be called repeatedly to handle authentication tasks.

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    if (Firebase.getFloat(fbdo, F("/test/float"))) {
      target = fbdo.to<float>();
      arrived = false;
    } else {
      Serial.printf("Error: %s\n", fbdo.errorReason().c_str());
    }

    //Serial.printf("Get float... %s\n", Firebase.getFloat(fbdo, F("/test/float")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
  }
  
  float sensorValue = analogRead(34);
  
  average = average * 0.99 + sensorValue * 0.01;

  if (arrived) {
    if (target - sensorValue > threshold * 1.5) {
       arrived = false;
    } else if (sensorValue - target > threshold * 1.5) {
       arrived = false;
    }
  } else {
    if (target - sensorValue > threshold) {
      motor.drive(0.55);
    } else if (sensorValue - target > threshold) {
      motor.drive(-0.55);
    } else {
      motor.brake();
      arrived = true;
    }
  }
}
