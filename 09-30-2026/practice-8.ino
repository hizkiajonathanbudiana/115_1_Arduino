const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;
int colorState = 1;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
      colorState++;
      if (colorState > 3) {
        colorState = 1;
      }
    } else {
      ledState = LOW;
    }

    if (ledState == LOW) {
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
    } else {
      if (colorState == 1) {
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, HIGH);
      } else if (colorState == 2) {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, HIGH);
      } else if (colorState == 3) {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);
      }
    }
  }
}