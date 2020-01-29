#include <Adafruit_NeoPixel.h>
#include "lib_aurora_solid_waves.h"

const int numLayers = 6;
Adafruit_NeoPixel layers[numLayers];

void setup() {
  uint8_t  brightness = 20;
  
  layers[0] = Adafruit_NeoPixel(40, 2);  // Layer0
  layers[1] = Adafruit_NeoPixel(83, 3);  // Layer1
  layers[2] = Adafruit_NeoPixel(39, 5);  // Layer2
  layers[3] = Adafruit_NeoPixel(33, 7);  // Layer3
  layers[4] = Adafruit_NeoPixel(31, 9);  // Layer4
  layers[5] = Adafruit_NeoPixel(27, 11); // Layer5

  initialize(brightness, numLayers);
}

void loop() {
  runAuroraRange(getPattern1());
}

Wave * getPattern1() {
  static Wave waves[] = {
    // Designated initializer only works if parameters are in correct order,
    // so it's necessary to explicitly initialize reverse when initializing
    // speed.
    {.color = red, .width = 60},
    {.color = black, .width = 60},
    {.color = black, .width = 60},
    {.color = black, .width = 60},
//    {.color = green, .width = 50},
//    {.color =  blue, .width = 30},
  };
  waves[0].numWaves = sizeof(waves) / sizeof(waves[0]);
  return waves;
}
