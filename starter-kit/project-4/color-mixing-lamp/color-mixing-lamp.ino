const int RED_LED_PIN = 10;
const int GREEN_LED_PIN = 9;
const int BLUE_LED_PIN = 11;

const int RED_SENSOR_PIN = A0;
const int GREEN_SENSOR_PIN = A1;
const int BLUE_SENSOR_PIN = A2;

int redLedVal = 0;
int greenLedVal = 0;
int blueLedVal = 0;

int redSensorVal = 0;
int greenSensorVal = 0;
int blueSensorVal = 0;

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
  delay(5);
  redSensorVal = analogRead(RED_SENSOR_PIN) / 4;
  delay(5);
  greenSensorVal = analogRead(GREEN_SENSOR_PIN) / 4;
  delay(5);
  blueSensorVal = analogRead(BLUE_SENSOR_PIN) / 4;

  analogWrite(RED_LED_PIN, redSensorVal);
  analogWrite(GREEN_LED_PIN, greenSensorVal);
  analogWrite(BLUE_LED_PIN, blueSensorVal);

  printValues();
}

void printValues() {
  Serial.print("SENSOR VALUES: Red - ");
  Serial.print(redSensorVal);
  Serial.print(" Green - ");
  Serial.print(greenSensorVal);
  Serial.print(" Blue - ");
  Serial.print(blueSensorVal);
  Serial.println("\n");
}
