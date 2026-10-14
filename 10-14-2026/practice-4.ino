const int analogPin = A0;
const int digitalPin = 2;
const int ledPin = 9;

void setup() {
  pinMode(digitalPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  int outputValue = digitalRead(digitalPin);

  if (outputValue == 0) {
    analogWrite(ledPin, 255);
  } else {
    analogWrite(ledPin, 0);
  }

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  delay(10);
}
