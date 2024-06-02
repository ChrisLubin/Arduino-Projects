#define PROPER_DISTANCE_CHECK_COUNT 5 // How many valid distance checks do we need to update actualDistance
#define DISTANCE_DIFF_THRESHOLD 7 // The acceptable max difference between valid checks
#define AUTONOMOUS_MODE_TOO_CLOSE_DISTANCE 20

long actualDistance = 0;
long mostRecentDistances[PROPER_DISTANCE_CHECK_COUNT] = { -1, -1, -1, -1, -1 };
bool isTestingDistance = false; // Used to adjust too-close distance parameter

void setUpAutonomousMode() {
  pinMode(ULTRA_SONIC_ECHO_PIN, INPUT);
  pinMode(ULTRA_SONIC_TRIG_PIN, OUTPUT);
}

long getUltraSonicSensorDistance() {
  digitalWrite(ULTRA_SONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_SONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_SONIC_TRIG_PIN, LOW);

  long duration = pulseIn(ULTRA_SONIC_ECHO_PIN, HIGH);
  long centimeters = duration / 29 / 2;
  return centimeters;
}

void logDistances() {
  Serial.print("Actual - ");
  Serial.println(actualDistance);
  Serial.print("Recent Distances - ");

  for (int i = 0; i < PROPER_DISTANCE_CHECK_COUNT; i++) {
    Serial.print(mostRecentDistances[i]);
    Serial.print(", ");
  }

  Serial.println("");
}

void updateMostRecentDistances() {
  if (isTestingDistance) {
    logDistances();
  }

  long currentDistance = getUltraSonicSensorDistance();
  Serial.print("Calculated now - ");
  Serial.println(currentDistance);
  bool shouldResetArray = false;

  for (int i = 0; i < PROPER_DISTANCE_CHECK_COUNT; i++) {
    long distanceInArray = mostRecentDistances[i];

    if (i == PROPER_DISTANCE_CHECK_COUNT - 1 && distanceInArray != -1) {
      // Got all valid distances in a row
      actualDistance = currentDistance;
      shouldResetArray = true;
      break;
    }

    if (distanceInArray != -1 && abs(currentDistance - distanceInArray) <= DISTANCE_DIFF_THRESHOLD) {
      // Distance is valid
      continue;
    } else if (distanceInArray != -1 && abs(currentDistance - distanceInArray) > DISTANCE_DIFF_THRESHOLD) {
      // Distance is NOT valid
      shouldResetArray = true;
      break;
    } else if (distanceInArray == -1) {
      mostRecentDistances[i] = currentDistance;
      break;
    }
  }

  if (shouldResetArray) {
    for (int i = 0; i < PROPER_DISTANCE_CHECK_COUNT; i++) {
      mostRecentDistances[i] = -1;
    }
  }
}

void resetDistances() {
  actualDistance = 0;
  for (int i = 0; i < PROPER_DISTANCE_CHECK_COUNT; i++) {
    mostRecentDistances[i] = -1;
  }
}

void autonomousModeLoop(CONTROL_MODE controlMode) {
  if (controlMode != AUTONOMOUS) {
    resetDistances();
    return;
  }

  updateMostRecentDistances();
}

MOTOR_ACTIONS getMotorActionFromAutonomousMode() {
  if (isTestingDistance) {
    return NONE;
  }

  if (actualDistance == 0) {
    // Allow distance to be calculated before moving for the first time
    return NONE;
  } else if (actualDistance <= AUTONOMOUS_MODE_TOO_CLOSE_DISTANCE) {
    return ROTATE_RIGHT;
  } else {
    return GO_FORWARD;
  }
}
