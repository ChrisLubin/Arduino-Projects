const int LED_PIN_1 = 10;
const int LED_PIN_2 = 11;
const int LED_PIN_3 = 12;
const int SOUND_SENSOR_PIN = 2;
int totalKnocks = 0;
int lastTimeDetectedKnock = 0;
int minTimeBetweenKnocks = 40;
bool isUnlocked = false;

int knockIntervals[] = {446, 456, 155, 161}; // Time between each knock to unlock
int knockErrorRange = 50;                    // Threshold range for knock intervals
int currentKnockInCode = 0;
int timingOfLastKnockDone = 0;

int isInTestMode = false; // Used to try out different knocks to get the timing for it

void setup()
{
  Serial.begin(9600);

  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
}

void loop()
{
  if (isInTestMode)
  {
    if (didKnock())
    {
      Serial.print("Time since last - ");
      Serial.println(timingOfLastKnockDone);
    }

    return;
  }

  if (isUnlocked)
  {
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, HIGH);
    return;
  }

  if (didKnock())
  {
    // Serial.println("Did knock!");
    totalKnocks++;

    if (didKnockWithCorrectTiming())
    {
      currentKnockInCode++;
      int knockIntervalsLength = sizeof(knockIntervals) / sizeof(knockIntervals[0]);

      if (currentKnockInCode == knockIntervalsLength + 1)
      {
        isUnlocked = true;
        return;
      }
    }
    else
    {
      currentKnockInCode = 0;
    }
  }

  digitalWrite(LED_PIN_1, totalKnocks % 3 == 0);
  digitalWrite(LED_PIN_2, totalKnocks % 3 == 1);
  digitalWrite(LED_PIN_3, totalKnocks % 3 == 2);
}

bool didKnock()
{
  int timeSinceStart = millis();

  if (timeSinceStart - lastTimeDetectedKnock < minTimeBetweenKnocks)
  {
    return false;
  }

  int didDetectKnock = digitalRead(SOUND_SENSOR_PIN);

  if (didDetectKnock)
  {
    timingOfLastKnockDone = timeSinceStart - lastTimeDetectedKnock;
    lastTimeDetectedKnock = timeSinceStart;
  }

  return didDetectKnock;
}

bool didKnockWithCorrectTiming()
{
  if (currentKnockInCode == 0)
  {
    return true;
  }

  int correctTimingOfKnock = knockIntervals[currentKnockInCode - 1];

  Serial.print("Time since last - ");
  Serial.println(timingOfLastKnockDone);

  if (timingOfLastKnockDone > correctTimingOfKnock - knockErrorRange && timingOfLastKnockDone < correctTimingOfKnock + knockErrorRange)
  {
    return true;
  }

  return false;
}