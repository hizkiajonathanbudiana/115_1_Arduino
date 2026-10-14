const int potPin = A0;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int breathValue = 0;
int fadeAmount = 5;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  int maxBrightness = map(potValue, 0, 1023, 0, 255);
  int scaledBrightness = map(breathValue, 0, 255, 0, maxBrightness);
  int pwmOutput = 255 - scaledBrightness;

  analogWrite(redPin, pwmOutput);
  analogWrite(greenPin, pwmOutput);
  analogWrite(bluePin, pwmOutput);

  breathValue = breathValue + fadeAmount;
  if (breathValue <= 0 || breathValue >= 255) {
    fadeAmount = -fadeAmount;
  }

  delay(30);
}
