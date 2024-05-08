const int BUTTON_PIN = 4;
const int LIGHT_SENSOR_PIN = A0;
const int PIEZO_PIN = 8;
int lowLightVal = 1023;
int highLightVal = 0;
int lightVal = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(PIEZO_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  while(millis() < 5000) {
    lightVal = analogRead(LIGHT_SENSOR_PIN);
    Serial.print("Light Val - ");
    Serial.println(lightVal);
    if (lightVal < lowLightVal) {
      lowLightVal = lightVal;
    }
    if (lightVal > highLightVal) {
      highLightVal = lightVal;
    }
    delay(50);
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // Not part of the project, but added a button with a pull-down resistor because the sound is obnoxious
  if (digitalRead(BUTTON_PIN) == LOW) {
    return;
  }

  lightVal = analogRead(LIGHT_SENSOR_PIN);
  int pitch = map(lightVal, lowLightVal, highLightVal, 50, 4000);
  tone(PIEZO_PIN, pitch, 40);
  delay(10);

  Serial.print("Light Val - ");
  Serial.print(lightVal);
  Serial.print(" Pitch - ");
  Serial.println(pitch);
}
