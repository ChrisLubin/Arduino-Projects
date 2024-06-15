const double DO_NOT_CHANGE_PID_VAL = 0.00;
enum PID_TUNINGS {
  P,
  I,
  D
};

void print(bool isLogging, String text) {
  if (!isLogging) {
    return;
  }

  Serial.print(text);
}

void print(bool isLogging, double text) {
  if (!isLogging) {
    return;
  }

  Serial.print(text);
}

void println(bool isLogging, String text) {
  if (!isLogging) {
    return;
  }

  Serial.println(text);
}

void println(bool isLogging, double text) {
  if (!isLogging) {
    return;
  }

  Serial.println(text);
}