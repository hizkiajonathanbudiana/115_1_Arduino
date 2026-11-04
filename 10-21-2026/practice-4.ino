const int buttonPin = 2;

int lastButtonState = LOW;
bool isPressing = false;
bool longPressTriggered = false;

unsigned long pressStartTime = 0;
unsigned long lastDebounceTime = 0;

const unsigned long debounceDelay = 30;
const unsigned long longPressDuration = 800;

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

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonAction = checkButton();

  if (buttonAction == 1) {
    Serial.println("Short Click");
  } else if (buttonAction == 2) {
    Serial.println("Long Press");
  }
}