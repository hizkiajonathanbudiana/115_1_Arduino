const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int mood = 0;
int moodStep = 1;

void showLEDState(int currentMood) {
  int redValue = 0;
  int greenValue = 0;
  int blueValue = 0;

  if (currentMood >= 10) {
    greenValue = map(currentMood, 10, 20, 255, 0);
    blueValue = map(currentMood, 10, 20, 0, 255);
  } else {
    redValue = map(currentMood, 0, 10, 255, 0);
    greenValue = map(currentMood, 0, 10, 0, 255);
  }

  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  showLEDState(mood);
  mood = mood + moodStep;

  if (mood >= 20 || mood <= 0) {
    moodStep = -moodStep;
  }

  delay(200);
}
