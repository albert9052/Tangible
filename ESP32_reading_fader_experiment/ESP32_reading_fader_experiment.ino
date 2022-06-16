// This experiment is useless, because the way to measure the voltage is wrong.

float average;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  average = analogRead(34) - analogRead(35);
}

void loop() {
  // put your main code here, to run repeatedly:
  float sensorValue = analogRead(34) - analogRead(35);
  average = average * 0.99 + sensorValue * 0.01;
  Serial.println(average);
  delay(10);
}
