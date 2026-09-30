const int buttonPin = 2;
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;
int ledcolor = 0;
bool ButtonPressed = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH && !ButtonPressed) {
    ledcolor = ledcolor + 1;
    if (ledcolor > 3) {
      ledcolor = 0;
    }
    ButtonPressed = true;
    delay(50);
  }
  
  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
    delay(50);
  }
  
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