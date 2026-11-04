const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int mode = 0;
int colorIndex = 0;
int blinkState = HIGH;
int brightness = 0;
int fadeAmount = 5;

int lastButtonState = LOW;
bool isPressing = false;
bool longPressTriggered = false;

unsigned long pressStartTime = 0;
unsigned long lastDebounceTime = 0;
unsigned long lastBlinkTime = 0;
unsigned long lastFadeTime = 0;

const unsigned long debounceDelay = 30;
const unsigned long longPressDuration = 800;
const unsigned long blinkInterval = 300;
const unsigned long fadeInterval = 20;

const int colors[7][3] = {
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1},
  {1, 1, 0},
  {0, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
};

void writeColorBrightness(int index, int level) {
  int redValue = colors[index][0] * level;
  int greenValue = colors[index][1] * level;
  int blueValue = colors[index][2] * level;

  analogWrite(redPin, 255 - redValue);
  analogWrite(greenPin, 255 - greenValue);
  analogWrite(bluePin, 255 - blueValue);
}

int checkButton() {
  unsigned long currentMillis = millis();
  int reading = digitalRead(buttonPin);
  int action = 0;

  if (reading != lastButtonState && (currentMillis - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentMillis;

    if (reading == HIGH) {
      isPressing = true;
      longPressTriggered = false;
      pressStartTime = currentMillis;
    } else {
      if (isPressing && !longPressTriggered) {
        action = 1;
      }
      isPressing = false;
    }
  }
  lastButtonState = reading;

  if (isPressing && !longPressTriggered && (currentMillis - pressStartTime >= longPressDuration)) {
    longPressTriggered = true;
    action = 2;
  }

  return action;
}

void updateLED() {
  unsigned long currentMillis = millis();

  if (mode == 0) {
    writeColorBrightness(colorIndex, 255);
  } else if (mode == 1) {
    if (currentMillis - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentMillis;
      blinkState = (blinkState == LOW) ? HIGH : LOW;
    }
    writeColorBrightness(colorIndex, (blinkState == HIGH) ? 255 : 0);
  } else if (mode == 2) {
    if (currentMillis - lastFadeTime >= fadeInterval) {
      lastFadeTime = currentMillis;
      brightness = brightness + fadeAmount;
      if (brightness <= 0) {
        brightness = 0;
        fadeAmount = -fadeAmount;
      } else if (brightness >= 255) {
        brightness = 255;
        fadeAmount = -fadeAmount;
      }
    }
    writeColorBrightness(colorIndex, brightness);
  }
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int buttonAction = checkButton();

  if (buttonAction == 1) {
    colorIndex = (colorIndex + 1) % 7;
  } else if (buttonAction == 2) {
    mode = (mode + 1) % 3;
    blinkState = HIGH;
    brightness = 0;
    fadeAmount = 5;
    lastBlinkTime = millis();
    lastFadeTime = millis();
  }

  updateLED();
}
