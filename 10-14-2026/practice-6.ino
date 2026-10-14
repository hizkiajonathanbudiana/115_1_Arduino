const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int mood = 10;
int lastButtonState = LOW;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 40;
const unsigned long untouchedInterval = 5000;
const unsigned long reducedInterval = 1000;

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
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  showLEDState(mood);
  touchedTimer = millis();
  reducedTimer = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState && (currentMillis - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentMillis;

    if (reading == HIGH) {
      if (mood < 20) {
        mood = mood + 1;
      }
      touchedTimer = currentMillis;
      reducedTimer = currentMillis;
    }
  }
  lastButtonState = reading;

  if (currentMillis - touchedTimer > untouchedInterval && currentMillis - reducedTimer >= reducedInterval) {
    reducedTimer = currentMillis;
    if (mood > 0) {
      mood = mood - 1;
    }
  }

  showLEDState(mood);
}
