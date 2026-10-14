const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int gameState = 0;
int hits = 0;
int lastButtonState = LOW;
int blinkState = LOW;

unsigned long stateStartTime = 0;
unsigned long lastBlinkTime = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 30;
const unsigned long gameDuration = 5000;
const unsigned long calcDuration = 3000;
const unsigned long blinkInterval = 250;

void setRGB(int rState, int gState, int bState) {
  digitalWrite(redPin, rState);
  digitalWrite(greenPin, gState);
  digitalWrite(bluePin, bState);
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  setRGB(HIGH, HIGH, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();
  int reading = digitalRead(buttonPin);
  bool buttonClicked = false;

  if (reading != lastButtonState && (currentMillis - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentMillis;
    if (reading == HIGH) {
      buttonClicked = true;
    }
  }
  lastButtonState = reading;

  if (gameState == 0) {
    if (currentMillis - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentMillis;
      blinkState = (blinkState == LOW) ? HIGH : LOW;
      setRGB(blinkState, blinkState, blinkState);
    }
    if (buttonClicked) {
      hits = 0;
      gameState = 1;
      stateStartTime = currentMillis;
      setRGB(HIGH, HIGH, HIGH);
    }
  } else if (gameState == 1) {
    if (reading == HIGH) {
      setRGB(LOW, LOW, LOW);
    } else {
      setRGB(HIGH, HIGH, HIGH);
    }
    if (buttonClicked) {
      hits = hits + 1;
    }
    if (currentMillis - stateStartTime >= gameDuration) {
      gameState = 2;
      stateStartTime = currentMillis;
      setRGB(LOW, LOW, LOW);
    }
  } else if (gameState == 2) {
    setRGB(LOW, LOW, LOW);
    if (currentMillis - stateStartTime >= calcDuration) {
      gameState = 3;
      lastBlinkTime = currentMillis;
      blinkState = LOW;
    }
  } else if (gameState == 3) {
    if (currentMillis - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentMillis;
      blinkState = (blinkState == LOW) ? HIGH : LOW;
      if (hits <= 10) {
        setRGB(blinkState, HIGH, HIGH);
      } else if (hits <= 20) {
        setRGB(HIGH, HIGH, blinkState);
      } else {
        setRGB(HIGH, blinkState, HIGH);
      }
    }
    if (buttonClicked) {
      gameState = 0;
      lastBlinkTime = currentMillis;
    }
  }
}
