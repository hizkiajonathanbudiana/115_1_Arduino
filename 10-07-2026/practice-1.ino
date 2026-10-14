const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

int ledState = HIGH;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == HIGH) {
      ledState = LOW;
    } else {
      ledState = HIGH;
    }
    digitalWrite(redPin, ledState);
    digitalWrite(greenPin, ledState);
    digitalWrite(bluePin, ledState);
  }
}