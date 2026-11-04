const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int colorIndex = 0;
int lastButtonState = LOW;
bool isPressing = false;
bool longPressTriggered = false;

unsigned long pressStartTime = 0;
unsigned long lastDebounceTime = 0;

const unsigned long debounceDelay = 30;
const unsigned long longPressDuration = 800;

const int colors[7][3] = {
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1},
  {1, 1, 0},
  {0, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
};

void showColor(int index) {
  digitalWrite(redPin, colors[index][0] ? LOW : HIGH);
  digitalWrite(greenPin, colors[index][1] ? LOW : HIGH);
  digitalWrite(bluePin, colors[index][2] ? LOW : HIGH);
}

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
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  showColor(colorIndex);
}

void loop() {
  int buttonAction = checkButton();

  if (buttonAction == 1) {
    colorIndex = (colorIndex + 1) % 7;
    showColor(colorIndex);
  }
}