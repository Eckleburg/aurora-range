/* lib_aurora_solid_waves.c */
#include "lib_aurora_solid_waves.h"
#include <stdint.h>
#include <Adafruit_NeoPixel.h>

const int animBufferSize = 61;
Color animBuffer[animBufferSize];
int animPos = 0;
int layerSpacing = 5;
int numLayers;

bool splitMode = false;
bool animDirection = false;

Color black = {0, 0, 0};
Color red = {255, 0, 0};
Color green = {0, 255, 0};
Color blue = {0, 0, 255};

/* Forward declaration of internal library functions */
Slopes calcSlopes(Color prevColor, Color nextColor, int width);
void displayWave(Wave wave);
void newSpeed(Wave wave);
void assignLayer(int layer, Color color);
void showAll();
Color calcNextFadeColor(Color prevColor, Slopes slopes, int waveStep);

void initialize(uint8_t brightness, int inputNumLayers) {
  numLayers = inputNumLayers;
  for (int l = 0; l < numLayers; l++) {
    layers[l].begin();
    layers[l].setBrightness(brightness);
    assignLayer(l, black);
    layers[l].show();
  }
  
  // Set animBuffer to all black
  for (int p = 0; p < animBufferSize; p++) {
    animBuffer[p] = black;
  }
}

//void test() {
//  for (int p = 0; p < 40; p++) {
//    layers[1].setPixelColor(p, layers[1].Color(255, 255, 255));
//  }
//  layers[1].show();
//  delay(2000);
//
//  for (int p = 0; p < 40; p++) {
//    layers[1].setPixelColor(p, 0);
//  }
//  layers[1].show();
//  delay(1000);
//}

void runAuroraRange(Wave * wavesPntr) {
  int numWaves = wavesPntr->numWaves;

  for(int waveCntr = 0; waveCntr < numWaves; waveCntr++) {
    displayWave(*wavesPntr);
    wavesPntr++;
  }
}

void displayWave(Wave wave) {
//  if (wave.reverse) {
//    animDirection = !animDirection;
//    // recalc position
//  }
//  if (wave.speed > 0) {
//    newSpeed(wave);
//  }

  Color prevColor = animBuffer[animPos];
  Slopes slopes = calcSlopes(prevColor, wave.color, wave.width);

  for (int waveStep = 0; waveStep < wave.width; waveStep++) {
    animPos = animDirection ? animPos + 1 : animPos - 1;
    if (animPos < 0) {
      animPos += 61;
    } else if (animPos > 60) {
      animPos -= 61;
    }

    animBuffer[animPos] = calcNextFadeColor(prevColor, slopes, waveStep);
    
    for (int layerCntr = 0; layerCntr < numLayers; layerCntr++) {
      int thisLayerPos = animDirection
          ? (animPos - layerCntr * layerSpacing)
          : (animPos + layerCntr * layerSpacing);
      if (thisLayerPos < 0) {
        thisLayerPos += 60;
      } else if (thisLayerPos > 60) {
        thisLayerPos -= 60;
      }

      assignLayer(layerCntr, animBuffer[thisLayerPos]);
    }

    showAll();
  }
}

void newSpeed (Wave wave) {
  Wave newSpeedWave = {.color = wave.color, .width = numLayers * layerSpacing};
  displayWave(newSpeedWave);
  displayWave(newSpeedWave);
  layerSpacing = 10 - wave.speed;
}

void assignLayer(int layer, Color color) {
  for (int pixel = 0; pixel < layers[layer].numPixels(); pixel++) {
    layers[layer].setPixelColor(pixel, color.r, color.g, color.b);
  }
}

void showAll() {
  for (int layer = 0; layer < numLayers; layer++) {
    layers[layer].show();
  }
}

Color calcNextFadeColor(Color prevColor, Slopes slopes, int waveStep) {
  Color nextColor = {
    prevColor.r + waveStep * slopes.rSlope,
    prevColor.g + waveStep * slopes.gSlope,
    prevColor.b + waveStep * slopes.bSlope
  };
  return nextColor;
}

Slopes calcSlopes(Color prevColor, Color nextColor, int width) {
  float rSlope = (nextColor.r - prevColor.r) / width;
  float gSlope = (nextColor.g - prevColor.g) / width;
  float bSlope = (nextColor.b - prevColor.b) / width;
  Slopes slopes = {rSlope, gSlope, bSlope};
  return slopes;
}
