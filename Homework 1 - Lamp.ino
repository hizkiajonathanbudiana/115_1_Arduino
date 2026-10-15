const int buttonPin = 2;
const int RledPin = 3;
const int GledPin = 4;
const int BledPin = 5;

int buttonState = 0;
int lastButtonState = LOW;
int ledcolor = 0;

unsigned long lastClickTime = 0;

unsigned long previousMillis = 0;
int rainbowColor = 1;
bool isRainbowOn = true;

unsigned long breathMillis = 0;
int breathBrightness = 0;
int breathStep = 4; 
int breathColorIndex = 1; 

void setRGB(int r, int g, int b) {
  digitalWrite(RledPin, r);
  digitalWrite(GledPin, g);
  digitalWrite(BledPin, b);
}

void showColor(int colorIndex) {
  if (colorIndex == 0) {
    setRGB(HIGH, HIGH, HIGH);
    return;
  }
  switch (colorIndex) {
    case 1: setRGB(LOW, HIGH, HIGH); break;
    case 2: setRGB(HIGH, LOW, HIGH); break;
    case 3: setRGB(HIGH, HIGH, LOW); break;
    case 4: setRGB(LOW, LOW, HIGH); break;
    case 5: setRGB(LOW, HIGH, LOW); break;
    case 6: setRGB(HIGH, LOW, LOW); break;
    case 7: setRGB(LOW, LOW, LOW); break;
  }
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  
  setRGB(HIGH, HIGH, HIGH);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && lastButtonState == LOW && (currentMillis - lastClickTime > 50)) {
    lastClickTime = currentMillis;
    ledcolor++;
    if (ledcolor > 9) ledcolor = 0;

    Serial.print("Mode: ");
    Serial.println(ledcolor);
  }
  lastButtonState = buttonState;

  if (ledcolor >= 1 && ledcolor <= 7) {
    showColor(ledcolor);
  }
  else if (ledcolor == 8) {
    if (currentMillis - previousMillis >= 300) {
      previousMillis = currentMillis;
      isRainbowOn = !isRainbowOn; 
      if (isRainbowOn) {
        rainbowColor++;
        if (rainbowColor > 7) rainbowColor = 1;
      }
    }
    if (isRainbowOn) showColor(rainbowColor);
    else showColor(0);
  }
  else if (ledcolor == 9) {
    if (currentMillis - breathMillis >= 15) {
      breathMillis = currentMillis;
      breathBrightness += breathStep;
      
      if (breathBrightness <= 0) {
        breathBrightness = 0;
        breathStep = -breathStep; 
        breathColorIndex++;       
        if (breathColorIndex > 7) breathColorIndex = 1;
      } 
      else if (breathBrightness >= 255) {
        breathBrightness = 255;
        breathStep = -breathStep; 
      }
    }
    
    unsigned long pwmWindow = micros() % 2550;
    if (pwmWindow < (unsigned long)(breathBrightness * 10)) {
      showColor(breathColorIndex); 
    } else {
      showColor(0); 
    }
  }
  else {
    showColor(0);
  }
}
