const int analogPin = A0;
const int digitalPin = 2;

void setup() {
  pinMode(digitalPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(analogPin);
  int digitalValue = digitalRead(digitalPin);

  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print("\t Digital: ");
  Serial.println(digitalValue);

  delay(50);
}
