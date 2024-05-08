#include <Servo.h>

Servo servo;
const int POT_PIN = A0;
int potVal;
int targetAngle;
int currentAngle;

void setup() {
  servo.attach(9);

  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(POT_PIN);
  targetAngle = map(potVal, 0, 1023, 0, 180);
  currentAngle = servo.read();

  Serial.print("Pot Val - ");
  Serial.print(potVal);
  Serial.print(" Target Angle - ");
  Serial.println(targetAngle);
  Serial.print(" Current Angle - ");
  Serial.println(currentAngle);

  servo.write(targetAngle);
  delay(5);
}
