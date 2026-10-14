const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int brightness = 0;
int fadeAmount = 5;
int colorIndex = 0;

const int colors[7][3] = {
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1},
  {1, 1, 0},
  {0, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
};

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int redValue = colors[colorIndex][0] * brightness;
  int greenValue = colors[colorIndex][1] * brightness;
  int blueValue = colors[colorIndex][2] * brightness;

  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);

  brightness = brightness + fadeAmount;

  if (brightness >= 255) {
    brightness = 255;
    fadeAmount = -fadeAmount;
  } else if (brightness <= 0) {
    brightness = 0;
    fadeAmount = -fadeAmount;
    colorIndex = (colorIndex + 1) % 7;
  }

  delay(30);
}
