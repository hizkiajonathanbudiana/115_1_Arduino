const int buttonPin = 2;
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

int colorIndex = 0;
int direction = 1;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;

void showColor(int index) {
  if (index == 0) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  } else if (index == 1) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  } else if (index == 2) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  } else if (index == 3) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  showColor(colorIndex);
}

void loop() {
  unsigned long currentMillis = millis();
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState && (currentMillis - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentMillis;
    if (reading == HIGH) {
      direction = -direction;
    }
  }
  lastButtonState = reading;

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    colorIndex = (colorIndex + direction + 4) % 4;
    showColor(colorIndex);
  }
}