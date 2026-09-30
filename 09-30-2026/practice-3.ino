const int buttonPin = 2;
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;
int ledcolor = 0;
int lastButtonState = LOW;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH && lastButtonState == LOW) {
    ledcolor = ledcolor + 1;
    if (ledcolor > 3) {
      ledcolor = 0;
    }
    delay(100);
  }
  lastButtonState = buttonState;
  
  if (ledcolor == 0) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  } else if (ledcolor == 1) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  } else if (ledcolor == 2) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  } else if (ledcolor == 3) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }
}