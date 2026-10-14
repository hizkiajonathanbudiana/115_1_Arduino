const int analogInPin = A0;
const int analogOutPin = 9;

int sensorValue = 0;
int outputValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(analogOutPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(analogInPin);

  if (sensorValue <= 200) {
    outputValue = 0;
  } else if (sensorValue >= 800) {
    outputValue = 255;
  } else {
    outputValue = map(sensorValue, 200, 800, 0, 255);
  }

  analogWrite(analogOutPin, outputValue);

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  delay(2);
}
