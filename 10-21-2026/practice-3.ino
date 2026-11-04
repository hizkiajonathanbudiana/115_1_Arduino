const int buttonPin = 2;

int lastButtonState = LOW;
bool isPressing = false;
bool longPressTriggered = false;

unsigned long pressStartTime = 0;
unsigned long lastDebounceTime = 0;

const unsigned long debounceDelay = 30;
const unsigned long longPressDuration = 800;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState && (currentMillis - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentMillis;

    if (reading == HIGH) {
      isPressing = true;
      longPressTriggered = false;
      pressStartTime = currentMillis;
    } else {
      if (isPressing && !longPressTriggered) {
        Serial.println("Short Click");
      }
      isPressing = false;
    }
  }
  lastButtonState = reading;

  if (isPressing && !longPressTriggered && (currentMillis - pressStartTime >= longPressDuration)) {
    longPressTriggered = true;
    Serial.println("Long Press");
  }
}