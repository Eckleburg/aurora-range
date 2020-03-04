#include <Adafruit_NeoPixel.h>

#include <Adafruit_NeoPixel.h>
#include "lib_aurora_solid_waves.h"

const int numLayers = 6;

Adafruit_NeoPixel layer5 = Adafruit_NeoPixel(24, 3);
Adafruit_NeoPixel layer4 = Adafruit_NeoPixel(25, 5);
Adafruit_NeoPixel layer3 = Adafruit_NeoPixel(27, 6);
Adafruit_NeoPixel layer2 = Adafruit_NeoPixel(30, 9);
Adafruit_NeoPixel layer1 = Adafruit_NeoPixel(37, 10);
Adafruit_NeoPixel layer0 = Adafruit_NeoPixel(48, 11);

Adafruit_NeoPixel layers[numLayers] =
  {layer0, layer1, layer2, layer3, layer4, layer5};

void setup() {
  int brightness = 80;
  initialize(brightness);
//  Serial.begin(9600);
}

void loop() {
  reverse();
  for (int i = 0; i < 5; i++) {
    displayWave(red, 100);
    displayWave(black, 100);
    displayWave(black, 100);
    delay(3000);
  }
  
  delay(100000);
}
