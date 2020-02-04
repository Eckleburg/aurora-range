/* lib_aurora_solid_waves.c */
#include "lib_aurora_solid_waves.h"
#include <stdint.h>
#include <Adafruit_NeoPixel.h>

const int animBufferSize = 256;
Color animBuffer[animBufferSize];
int animPos = 0;
int layerSpacing = 8;
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

void test() {
  assignLayer(5, red);
  //  layers[5].setPixelColor(0, 255, 0, 0);
  //  layers[0].show();
  //  layers[5].show();
  showAll();
}

void runAuroraRange(Wave * wavesPntr) {
  int numWaves = wavesPntr->numWaves;

  for (int waveCntr = 0; waveCntr < numWaves; waveCntr++) {
    displayWave(*wavesPntr);
    wavesPntr++;
  }
}

void displayWave(Wave wave) {
    if (wave.reverse) {
      animPos = animDirection
                ? animPos - (numLayers - 1) * layerSpacing
                : animPos + (numLayers - 1) * layerSpacing;
      if (animPos < 0) {
        animPos += animBufferSize;
      } else if (animPos > animBufferSize - 1) {
        animPos -= animBufferSize;
      }
      animDirection = !animDirection;
//      Serial.println("reverse");
    }
  if (wave.speed > 0) {
    newSpeed(wave);
  }

  Color prevColor = animBuffer[animPos];
  Slopes slopes = calcSlopes(prevColor, wave.color, wave.width);

  int animStartPos = animPos;

  // 1-indexed because otherwise the first step would be the same as prevColor.
  for (int waveStep = 1; waveStep <= wave.width; waveStep++) {
    animPos = animDirection ? animPos + 1 : animPos - 1;
    if (animPos < 0) {
      animPos += animBufferSize;
    } else if (animPos > animBufferSize - 1) {
      animPos -= animBufferSize;
    }

    animBuffer[animPos] = calcNextFadeColor(prevColor, slopes, waveStep);
  }
  animPos = animStartPos;

  for (int waveStep = 1; waveStep <= wave.width; waveStep++) {
    animPos = animDirection ? animPos + 1 : animPos - 1;
    if (animPos < 0) {
      animPos += animBufferSize;
    } else if (animPos > animBufferSize - 1) {
      animPos -= animBufferSize;
    }
//    Serial.print("animPos: ");
//    Serial.println(animPos);
//    Serial.print("[");
    for (int layerCntr = 0; layerCntr < numLayers; layerCntr++) {
      int thisLayerPos = animDirection
                         ? (animPos - (numLayers - layerCntr - 1) * layerSpacing)
                         : (animPos + layerCntr * layerSpacing);
      if (thisLayerPos < 0) {
        thisLayerPos += animBufferSize;
      } else if (thisLayerPos > animBufferSize - 1) {
        thisLayerPos -= animBufferSize;
      }
//            Serial.print(thisLayerPos);
//            Serial.print(", ");

      assignLayer(layerCntr, animBuffer[thisLayerPos]);
    }
//        Serial.println("]");

    //    showAll();
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
  layers[layer].show();
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
  float rSlope = (nextColor.r - prevColor.r) / (float) width;
  float gSlope = (nextColor.g - prevColor.g) / (float) width;
  float bSlope = (nextColor.b - prevColor.b) / (float) width;
  Slopes slopes = {rSlope, gSlope, bSlope};
  return slopes;
}
