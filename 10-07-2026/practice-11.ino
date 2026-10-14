const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int brightness = 0;
int fadeAmount = 5;
int targetRed = 255;
int targetGreen = 0;
int targetBlue = 0;

void pickRandomColor() {
  targetRed = random(0, 256);
  targetGreen = random(0, 256);
  targetBlue = random(0, 256);

  if (targetRed < 30 && targetGreen < 30 && targetBlue < 30) {
    targetRed = 255;
  }
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  randomSeed(analogRead(A5));
  pickRandomColor();
}

void loop() {
  int currentRed = map(brightness, 0, 255, 0, targetRed);
  int currentGreen = map(brightness, 0, 255, 0, targetGreen);
  int currentBlue = map(brightness, 0, 255, 0, targetBlue);

  analogWrite(redPin, 255 - currentRed);
  analogWrite(greenPin, 255 - currentGreen);
  analogWrite(bluePin, 255 - currentBlue);

  brightness = brightness + fadeAmount;

  if (brightness >= 255) {
    brightness = 255;
    fadeAmount = -fadeAmount;
  } else if (brightness <= 0) {
    brightness = 0;
    fadeAmount = -fadeAmount;
    pickRandomColor();
  }

  delay(30);
}
