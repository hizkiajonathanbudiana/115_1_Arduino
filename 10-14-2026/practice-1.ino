const int photoresistorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(photoresistorPin);
  Serial.println(sensorValue);
  delay(10);
}
