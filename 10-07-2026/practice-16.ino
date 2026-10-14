const int analogInPin = A0;
const int analogOutPin = 9;

int sensorValue = 0;
int outputValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(analogOutPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  long scaled = (long)sensorValue * (long)sensorValue * 255L / (1023L * 1023L);
  outputValue = (int)scaled;

  analogWrite(analogOutPin, outputValue);

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  delay(2);
}
