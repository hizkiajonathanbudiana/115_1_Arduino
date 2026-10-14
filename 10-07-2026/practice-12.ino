const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int wheelPosition = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int redValue = 0;
  int greenValue = 0;
  int blueValue = 0;

  if (wheelPosition < 256) {
    redValue = 255 - wheelPosition;
    greenValue = wheelPosition;
  } else if (wheelPosition < 512) {
    greenValue = 511 - wheelPosition;
    blueValue = wheelPosition - 256;
  } else {
    redValue = wheelPosition - 512;
    blueValue = 767 - wheelPosition;
  }

  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);

  wheelPosition = (wheelPosition + 1) % 768;
  delay(10);
}
