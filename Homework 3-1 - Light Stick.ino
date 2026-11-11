
const byte BUTTON_PIN = 2;
const byte RED_PIN = 9;
const byte GREEN_PIN = 10;
const byte BLUE_PIN = 11;

const unsigned long DEBOUNCE_MS = 30;
const unsigned long HOLD_MS = 700;
const unsigned long BLINK_HALF_MS = 400;
const unsigned long BREATH_PERIOD_MS = 2200;

byte mode = 0;
byte colorIndex = 0;

const byte COLORS[6][3] = {
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {255, 255, 0},
  {0, 255, 255},
  {255, 255, 255}
};

bool lastRawPressed = false;
bool stablePressed = false;
bool holdHandled = false;

unsigned long lastRawChangeAt = 0;
unsigned long pressStartedAt = 0;
unsigned long effectStartedAt = 0;

void setRGB(byte r, byte g, byte b) {
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}

void shortClick(unsigned long now) {
  colorIndex = (colorIndex + 1) % 6;

  if (mode == 3) {
    mode = 0;
  }

  effectStartedAt = now;

  Serial.print("SHORT CLICK -> Color ");
  Serial.println(colorIndex);
}

void longPress(unsigned long now) {
  mode = (mode + 1) % 4;
  effectStartedAt = now;

  Serial.print("LONG PRESS -> ");

  if (mode == 0) {
    Serial.println("CONSTANT");
  } else if (mode == 1) {
    Serial.println("BLINK");
  } else if (mode == 2) {
    Serial.println("BREATHING");
  } else {
    Serial.println("RAINBOW BONUS");
  }
}

void checkButton(unsigned long now) {
  bool rawPressed = (digitalRead(BUTTON_PIN) == LOW);

  if (rawPressed != lastRawPressed) {
    lastRawPressed = rawPressed;
    lastRawChangeAt = now;
  }

  if (now - lastRawChangeAt >= DEBOUNCE_MS &&
      rawPressed != stablePressed) {

    stablePressed = rawPressed;

    if (stablePressed) {
      pressStartedAt = now;
      holdHandled = false;
    } else if (!holdHandled) {
      shortClick(now);
    }
  }

  if (stablePressed && !holdHandled &&
      now - pressStartedAt >= HOLD_MS) {

    holdHandled = true;
    longPress(now);
  }
}

void showRainbow(unsigned long now) {
  unsigned int p =
    ((now - effectStartedAt) / 6UL) % 768;

  if (p < 256) {
    setRGB(
      (byte)(255 - p),
      (byte)p,
      0
    );
  } else if (p < 512) {
    setRGB(
      0,
      (byte)(511 - p),
      (byte)(p - 256)
    );
  } else {
    setRGB(
      (byte)(p - 512),
      0,
      (byte)(767 - p)
    );
  }
}

void updateLED(unsigned long now) {
  if (mode == 3) {
    showRainbow(now);
    return;
  }

  byte r = COLORS[colorIndex][0];
  byte g = COLORS[colorIndex][1];
  byte b = COLORS[colorIndex][2];

  unsigned long elapsed = now - effectStartedAt;

  if (mode == 0) {
    setRGB(r, g, b);
  } else if (mode == 1) {
    bool on =
      ((elapsed / BLINK_HALF_MS) % 2) == 0;

    setRGB(
      on ? r : 0,
      on ? g : 0,
      on ? b : 0
    );
  } else {
    unsigned long phase =
      elapsed % BREATH_PERIOD_MS;

    unsigned long half =
      BREATH_PERIOD_MS / 2;

    byte brightness;

    if (phase <= half) {
      brightness =
        (byte)map(phase, 0, half, 0, 255);
    } else {
      brightness =
        (byte)map(
          phase,
          half,
          BREATH_PERIOD_MS,
          255,
          0
        );
    }

    setRGB(
      (byte)((unsigned int)r * brightness / 255),
      (byte)((unsigned int)g * brightness / 255),
      (byte)((unsigned int)b * brightness / 255)
    );
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  effectStartedAt = millis();
  setRGB(255, 0, 0);

  Serial.println("=== HW3-1 FOUR MODE LIGHT STICK ===");
  Serial.println("Short click = change color");
  Serial.println("Hold 0.7s = next mode");
  Serial.println(
    "Modes: Constant > Blink > Breathing > Rainbow > Constant"
  );
}

void loop() {
  unsigned long now = millis();

  checkButton(now);
  updateLED(now);
}
