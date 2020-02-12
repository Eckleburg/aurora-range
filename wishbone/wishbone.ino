#include <Adafruit_NeoPixel.h>
#include "lib_aurora_solid_waves.h"

//const int numLayers = 6;
const int numLayers = 11;

Adafruit_NeoPixel layer10 = Adafruit_NeoPixel(36, 12);
Adafruit_NeoPixel layer9 = Adafruit_NeoPixel(41, 10);
Adafruit_NeoPixel layer8 = Adafruit_NeoPixel(47, 8);
Adafruit_NeoPixel layer7 = Adafruit_NeoPixel(54, 6);
Adafruit_NeoPixel layer6 = Adafruit_NeoPixel(110, 4);
Adafruit_NeoPixel layer5 = Adafruit_NeoPixel(40, 2);
Adafruit_NeoPixel layer4 = Adafruit_NeoPixel(83, 3);
Adafruit_NeoPixel layer3 = Adafruit_NeoPixel(39, 5);
Adafruit_NeoPixel layer2 = Adafruit_NeoPixel(33, 7);
Adafruit_NeoPixel layer1 = Adafruit_NeoPixel(31, 9);
Adafruit_NeoPixel layer0 = Adafruit_NeoPixel(27, 11);

//Adafruit_NeoPixel layers[numLayers] =
//  {layer0, layer1, layer2, layer3, layer4, layer5};
Adafruit_NeoPixel layers[numLayers] =
{layer0, layer1, layer2, layer3, layer4, layer5, layer6, layer7, layer8, layer9, layer10};

void setup() {
  int brightness = 30;
  initialize(brightness);
  runAuroraRange(getPattern2());
//  Serial.begin(9600);
}

void loop() {
    runAuroraRange(getPattern1());
}

Wave * getPattern1() {
  int width = 60;
  static Wave waves[] = {
    // Designated initializer only works if parameters are in correct order,
    // so it's necessary to explicitly initialize reverse when initializing
    // speed.
    {.color = green, .width = width},
    //    {.color = black, .width = 0},
    {.color = green, .width = 10},
    {.color = blue, .width = 10},
    {.color = red, .width = 10},
    {.color = blue, .width = 10},
    {.color = red, .width = 10},
    {.color =  blue, .width = width},
    {.color = red, .width = width, .reverse = true, .switchSplit = 1}
  };
  waves[0].numWaves = sizeof(waves) / sizeof(waves[0]);
  return waves;
}

Wave * getPattern2() {
  static Wave waves[] = {
    {.color = black, .width = 30, .reverse = 0, .switchSplit = 1},
  };
  waves[0].numWaves = sizeof(waves) / sizeof(waves[0]);
  return waves;
}

Wave * getPattern3() {
  static Wave waves[] = {
    {.color = blue, .width = 60},
    {.color = darkGreen, .width = 60},
    {.color = blue, .width = 60},
    {.color = yellowGreen, .width = 60},
  };
  waves[0].numWaves = sizeof(waves) / sizeof(waves[0]);
  return waves;
}
