#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel leds(4, RGB_PIN, NEO_GRB + NEO_KHZ800);

// 0 - 100
void setLedBrightness(int brightness) {
  leds.setBrightness(map(brightness, 0, 100, 0, 255));
}

void setUpLeds() {
  leds.begin();
  leds.clear();
  leds.show();
  setLedBrightness(7);
}

void ledsLoop(int r, int g, int b) {
  leds.setPixelColor(0, leds.Color(r, g, b));
  leds.setPixelColor(1, leds.Color(r, g, b));
  leds.setPixelColor(2, leds.Color(r, g, b));
  leds.setPixelColor(3, leds.Color(r, g, b));
  leds.show();
}
