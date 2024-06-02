void waitUntil(bool (*funcToCheck)(), void (*loopFunc)()) {
  while(!(*funcToCheck)()) {
    (*loopFunc)();
  }
}