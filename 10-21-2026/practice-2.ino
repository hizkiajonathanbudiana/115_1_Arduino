const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

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
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    setRGB(LOW, LOW, LOW);
  } else {
    setRGB(HIGH, HIGH, HIGH);
  }
}