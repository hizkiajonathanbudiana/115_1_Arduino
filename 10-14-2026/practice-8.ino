const int ldrPin = A0;
const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int mood = 10;
int lastButtonState = LOW;
int breathLevel = 0;
int breathStep = 3;

unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
unsigned long animTimer = 0;
unsigned long lastDebounceTime = 0;

const unsigned long debounceDelay = 40;
const unsigned long untouchedInterval = 5000;

void writeRGB(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);
}

void showMoodSpectrum(int currentMood) {
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

  writeRGB(redValue, greenValue, blueValue);
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  touchedTimer = millis();
  reducedTimer = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  int lightValue = analogRead(ldrPin);
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState && (currentMillis - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentMillis;

    if (reading == HIGH) {
      int boost = (lightValue < 300) ? 2 : 1;
      mood = mood + boost;
      if (mood > 20) {
        mood = 20;
      }
      touchedTimer = currentMillis;
      reducedTimer = currentMillis;
    }
  }
  lastButtonState = reading;

  if (lightValue > 700) {
    if (currentMillis - animTimer >= 30) {
      animTimer = currentMillis;
      breathLevel = breathLevel + breathStep;
      if (breathLevel <= 0 || breathLevel >= 90) {
        breathStep = -breathStep;
      }
      writeRGB(breathLevel, breathLevel / 3, breathLevel);
    }
  } else if (lightValue < 300) {
    if (currentMillis - animTimer >= 10) {
      animTimer = currentMillis;
      breathLevel = breathLevel + (breathStep * 2);

      if (breathLevel <= 0) {
        breathLevel = 0;
        breathStep = -breathStep;
      } else if (breathLevel >= 255) {
        breathLevel = 255;
        breathStep = -breathStep;
      }

      writeRGB(0, breathLevel / 2, breathLevel);
    }
  } else {
    if (currentMillis - touchedTimer > untouchedInterval && currentMillis - reducedTimer >= 1000) {
      reducedTimer = currentMillis;
      if (mood > 0) {
        mood = mood - 1;
      }
    }
    showMoodSpectrum(mood);
  }
}
