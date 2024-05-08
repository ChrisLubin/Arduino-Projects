const int SENSOR_PIN = A0;
float BASELINE_TEMP;

void setup() {
  Serial.begin(9600);

  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }

  int sensorVal = analogRead(SENSOR_PIN);
  BASELINE_TEMP = getTemp(sensorVal);
}

void loop() {
  int sensorVal = analogRead(SENSOR_PIN);
  float temp = getTemp(sensorVal);

  Serial.println("BASELINE_TEMP");
  Serial.println(BASELINE_TEMP);
  Serial.println("Temp");
  Serial.println(temp);

  if (temp < BASELINE_TEMP + 0.5) {
    setLeds(LOW, LOW, LOW);
  } else if (temp >= BASELINE_TEMP + 0.5 && temp < BASELINE_TEMP + 1.5) {
    setLeds(HIGH, LOW, LOW);
  } else if (temp >= BASELINE_TEMP + 1.5 && temp < BASELINE_TEMP + 2.5) {
    setLeds(HIGH, HIGH, LOW);
  } else {
    setLeds(HIGH, HIGH, HIGH);
  }
  delay(100);
}

float getTemp(int sensorVal) {
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temp = (voltage - 0.5) * 100.0;
  return temp;
}

void setLeds(int firstLed, int secondLed, int thirdLed) {
  digitalWrite(2, firstLed);
  digitalWrite(3, secondLed);
  digitalWrite(4, thirdLed);
}