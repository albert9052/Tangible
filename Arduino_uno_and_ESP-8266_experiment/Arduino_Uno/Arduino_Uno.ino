#include <SoftwareSerial.h>

SoftwareSerial firebase(2, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  firebase.begin(115200);
}
String a = "a";
void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print(a);
//  firebase.print(a);
//  a = a + "b";
//  if (a == "abbbbbbbbbb") {
//    a = "a";
//  }
//  delay(2000);
  if (Serial.available() > 0) {
    byte b = Serial.read();
    //Serial.write(b);
    firebase.write(b);
  }
  if (firebase.available() > 0) {
    byte b = firebase.read();
    Serial.println("HI");
  }
}
