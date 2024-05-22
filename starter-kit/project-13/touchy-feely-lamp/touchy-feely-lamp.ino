#include <CapacitiveSensor.h>
CapacitiveSensor capacitiveSensor = CapacitiveSensor(4, 2);

#define ILLUMINATE_LED_THRESHOLD 1000
#define LED_PIN 12

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  long sensorVal = capacitiveSensor.capacitiveSensor(30);
  Serial.print("Sensor val - ");
  Serial.println(sensorVal);

  digitalWrite(LED_PIN, sensorVal > ILLUMINATE_LED_THRESHOLD ? HIGH : LOW);
  delay(10);
}
