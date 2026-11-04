const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int mode = 0;
int colorIndex = 0;
bool fastSpeed = false;

int blinkState = HIGH;
int brightness = 0;
int fadeAmount = 5;
int wheelPosition = 0;
int heartbeatStep = 0;

int lastButtonState = LOW;
bool isPressing = false;
bool longPressTriggered = false;
bool waitingSecondClick = false;

unsigned long pressStartTime = 0;
unsigned long lastDebounceTime = 0;
unsigned long firstClickTime = 0;
unsigned long lastEffectTime = 0;

const unsigned long debounceDelay = 30;
const unsigned long longPressDuration = 800;
const unsigned long doubleClickWindow = 280;

const int colors[7][3] = {
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1},
  {1, 1, 0},
  {0, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
};

const unsigned long heartbeatDurations[4] = {100, 120, 100, 600};
const int heartbeatLevels[4] = {255, 30, 255, 0};

void writeRGB(int r, int g, int b) {
  analogWrite(redPin, 255 - r);
  analogWrite(greenPin, 255 - g);
  analogWrite(bluePin, 255 - b);
}

void writeColorBrightness(int index, int level) {
  int r = colors[index][0] * level;
  int g = colors[index][1] * level;
  int b = colors[index][2] * level;
  writeRGB(r, g, b);
}

void showRainbowWheel(int pos) {
  int r = 0;
  int g = 0;
  int b = 0;

  if (pos < 256) {
    r = 255 - pos;
    g = pos;
  } else if (pos < 512) {
    g = 511 - pos;
    b = pos - 256;
  } else {
    r = pos - 512;
    b = 767 - pos;
  }
  writeRGB(r, g, b);
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
        if (waitingSecondClick && (currentMillis - firstClickTime <= doubleClickWindow)) {
          waitingSecondClick = false;
          action = 3;
        } else {
          waitingSecondClick = true;
          firstClickTime = currentMillis;
        }
      }
      isPressing = false;
    }
  }
  lastButtonState = reading;

  if (waitingSecondClick && (currentMillis - firstClickTime > doubleClickWindow)) {
    waitingSecondClick = false;
    action = 1;
  }

  if (isPressing && !longPressTriggered && (currentMillis - pressStartTime >= longPressDuration)) {
    longPressTriggered = true;
    waitingSecondClick = false;
    action = 2;
  }

  return action;
}

void updateLED() {
  unsigned long currentMillis = millis();
  unsigned long speedDivisor = fastSpeed ? 2 : 1;

  if (mode == 0) {
    writeColorBrightness(colorIndex, 255);
  } else if (mode == 1) {
    if (currentMillis - lastEffectTime >= (300 / speedDivisor)) {
      lastEffectTime = currentMillis;
      blinkState = (blinkState == LOW) ? HIGH : LOW;
    }
    writeColorBrightness(colorIndex, (blinkState == HIGH) ? 255 : 0);
  } else if (mode == 2) {
    if (currentMillis - lastEffectTime >= (20 / speedDivisor)) {
      lastEffectTime = currentMillis;
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
  } else if (mode == 3) {
    if (currentMillis - lastEffectTime >= (10 / speedDivisor)) {
      lastEffectTime = currentMillis;
      wheelPosition = (wheelPosition + 2) % 768;
    }
    showRainbowWheel(wheelPosition);
  } else if (mode == 4) {
    unsigned long stepTime = heartbeatDurations[heartbeatStep] / speedDivisor;
    if (currentMillis - lastEffectTime >= stepTime) {
      lastEffectTime = currentMillis;
      heartbeatStep = (heartbeatStep + 1) % 4;
    }
    writeColorBrightness(colorIndex, heartbeatLevels[heartbeatStep]);
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
    mode = (mode + 1) % 5;
    blinkState = HIGH;
    brightness = 0;
    fadeAmount = 5;
    heartbeatStep = 0;
    lastEffectTime = millis();
  } else if (buttonAction == 3) {
    fastSpeed = !fastSpeed;
  }

  updateLED();
}
