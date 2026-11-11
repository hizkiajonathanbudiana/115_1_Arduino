const byte buttonPin = 2;
const byte ledPin = 3;

const unsigned long DEBOUNCE_MS = 30;

const unsigned long intervals[] = {
  0, 900, 350, 120
};

byte mode = 0;

bool lastRawPressed = false;
bool stablePressed = false;
bool ledState = true;

unsigned long debounceTime = 0;
unsigned long lastBlinkTime = 0;

void checkButton(unsigned long now) {
  bool rawPressed = digitalRead(buttonPin) == LOW;

  if (rawPressed != lastRawPressed) {
    lastRawPressed = rawPressed;
    debounceTime = now;
  }

  if (now - debounceTime >= DEBOUNCE_MS &&
      rawPressed != stablePressed) {

    stablePressed = rawPressed;

    if (stablePressed) {
      mode = (mode + 1) % 4;

      ledState = true;
      lastBlinkTime = now;

      Serial.print("Mode: ");
      Serial.println(mode);
    }
  }
}

void updateLED(unsigned long now) {
  if (mode == 0) {
    ledState = true;
  } else if (now - lastBlinkTime >= intervals[mode]) {
    ledState = !ledState;
    lastBlinkTime = now;
  }

  digitalWrite(ledPin, ledState ? HIGH : LOW);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  unsigned long now = millis();

  checkButton(now);
  updateLED(now);
}
