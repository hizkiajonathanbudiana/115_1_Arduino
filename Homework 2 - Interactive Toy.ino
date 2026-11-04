const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const bool BUTTON_ACTIVE_HIGH = false;
const bool RGB_COMMON_ANODE = true;

int mood = 10;

const int MIN_MOOD = 0;
const int NEUTRAL_MOOD = 10;
const int MAX_MOOD = 20;

const unsigned long DEBOUNCE_MS = 35;
const unsigned long UNTOUCHED_MS = 5000;
const unsigned long DECAY_MS = 1000;

unsigned long lastDebounceTime = 0;
unsigned long lastTouchTime = 0;
unsigned long lastDecayTime = 0;

bool lastRawPressed = false;
bool stablePressed = false;

void setRGB(int r, int g, int b) {
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);

  if (RGB_COMMON_ANODE) {
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
  }

  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void showMood(unsigned long now) {
  if (mood == MIN_MOOD) {
    bool blinkOn = (now / 200) % 2 == 0;

    if (blinkOn) {
      setRGB(255, 0, 0);
    } else {
      setRGB(0, 0, 0);
    }
  } else if (mood == MAX_MOOD) {
    unsigned long phase = now % 1800UL;
    int pulse;

    if (phase < 900) {
      pulse = phase;
    } else {
      pulse = 1800 - phase;
    }

    int red = map(pulse, 0, 900, 0, 100);
    int blue = map(pulse, 0, 900, 100, 255);

    setRGB(red, 0, blue);
  } else if (mood < NEUTRAL_MOOD) {
    int green = map(mood, 0, 10, 0, 255);
    int red = 255 - green;

    setRGB(red, green, 0);
  } else {
    int blue = map(mood, 10, 20, 0, 255);
    int green = 255 - blue;

    setRGB(0, green, blue);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  lastRawPressed =
      digitalRead(buttonPin) ==
      (BUTTON_ACTIVE_HIGH ? HIGH : LOW);

  stablePressed = lastRawPressed;

  lastTouchTime = millis();
  lastDecayTime = millis();

  setRGB(0, 255, 0);

  Serial.println("=== INTERACTIVE TOY ===");
  Serial.println("Initial Mood: 10");
  Serial.println("Status: NEUTRAL");
}

void loop() {
  unsigned long now = millis();

  bool rawPressed =
      digitalRead(buttonPin) ==
      (BUTTON_ACTIVE_HIGH ? HIGH : LOW);

  if (rawPressed != lastRawPressed) {
    lastDebounceTime = now;
  }

  if (now - lastDebounceTime >= DEBOUNCE_MS) {
    if (rawPressed != stablePressed) {
      stablePressed = rawPressed;

      if (stablePressed) {
        mood = min(mood + 1, MAX_MOOD);

        lastTouchTime = now;
        lastDecayTime = now;

        Serial.print("PET! Mood: ");
        Serial.println(mood);
      }
    }
  }

  lastRawPressed = rawPressed;

  if (stablePressed) {
    lastTouchTime = now;
    lastDecayTime = now;
  } else if (now - lastTouchTime >= UNTOUCHED_MS) {
    if (now - lastDecayTime >= DECAY_MS) {
      if (mood > MIN_MOOD) {
        mood--;

        Serial.print("LONELY! Mood: ");
        Serial.println(mood);
      }

      lastDecayTime = now;
    }
  }

  showMood(now);
}
