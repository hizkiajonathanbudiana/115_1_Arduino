const int potPin = A0;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(potPin);
  int redValue = 0;
  int greenValue = 0;
  int blueValue = 0;

  if (sensorValue <= 511) {
    redValue = map(sensorValue, 0, 511, 255, 0);
    greenValue = map(sensorValue, 0, 511, 0, 255);
    blueValue = 0;
  } else {
    redValue = 0;
    greenValue = map(sensorValue, 512, 1023, 255, 0);
    blueValue = map(sensorValue, 512, 1023, 0, 255);
  }

  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);
}