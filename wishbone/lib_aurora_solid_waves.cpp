/* lib_aurora_solid_waves.c */
#include "lib_aurora_solid_waves.h"
#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <stdint.h>

const int animBufferSize = 256;
Color animBuffer[animBufferSize];
int animPos = 0;
int layerSpacing = 8;
bool splitMode = false;
bool animDirection = false;
bool gamma = false;

/* Forward declaration of internal library functions */
void displayWave(Wave wave);
void displaySolid(Wave wave);
void assignLayer(int layer, Color color);
void reverse();
int correctPosition(int position);
Color calcNextFadeColor(Fade fade, int waveStep);
Fade calcFade(Color prevColor, Color nextColor, int width);
Color gammaAdjust(Color inputColor);
extern const uint8_t gamma8[];

// Initialize the range, get the leds ready to display. Note that numLayers
// and layers[] are both external variables, they should be defined in your
// range's code.
void initialize(uint8_t brightness) {
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

void runAuroraRange(Wave * wavesPntr) {
  int numWaves = wavesPntr->numWaves;
  for (int waveCntr = 0; waveCntr < numWaves; waveCntr++) {
    displayWave(*wavesPntr);
    wavesPntr++;
  }
}

void displayWave(Wave wave) {
  if (wave.reverse) {
      reverse();
  }
  
  if (wave.spacing > 0 || wave.switchSplit) {
    displaySolid(wave);
    if (wave.spacing > 0) {
      layerSpacing = wave.spacing;
    }
    if (wave.switchSplit) {
      splitMode = !splitMode;
    }
    return;
  }

  if (wave.switchGamma) {
    gamma = !gamma;
  }

  Color prevColor = animBuffer[animPos];
  Color nextColor = gamma
                    ? gammaAdjust(wave.color)
                    : wave.color;
  Fade fade = calcFade(prevColor, nextColor, wave.width);
  int wavePos = animPos;

  // Calculate every color in the fade before displaying, results in smoother display
  // 1-indexed because otherwise the first step would be the same as prevColor.
  for (int waveStep = 1; waveStep <= wave.width; waveStep++) {
    wavePos = animDirection ? wavePos + 1 : wavePos - 1;
    wavePos = correctPosition(wavePos);
    animBuffer[wavePos] = calcNextFadeColor(fade, waveStep);
  }

  for (int waveStep = 1; waveStep <= wave.width; waveStep++) {
    animPos = animDirection ? animPos + 1 : animPos - 1;
    animPos = correctPosition(animPos);
    for (int layerCntr = 0; layerCntr < numLayers; layerCntr++) {
      int layerNum = splitMode
                     ? abs(numLayers / 2 - layerCntr)
                     : layerCntr;
      int thisLayerPos = animDirection
                         ? (animPos - (numLayers - layerNum - 1) * layerSpacing)
                         : (animPos + layerNum * layerSpacing);
      thisLayerPos = correctPosition(thisLayerPos);
      assignLayer(layerCntr, animBuffer[thisLayerPos]);
    }
  }
}

// Display two waves in order to get the whole range to one solid color.
void displaySolid (Wave wave) {
  Wave newSpacingWave = {.color = wave.color, .width = numLayers * layerSpacing};
  displayWave(newSpacingWave);
//  displayWave(newSpacingWave);
}

void assignLayer(int layer, Color color) {
  for (int pixel = 0; pixel < layers[layer].numPixels(); pixel++) {
    layers[layer].setPixelColor(pixel, color.r, color.g, color.b);
  }

  // Progressively showing each layer results in smoother transitions than
  // showing all layers at once.
  layers[layer].show();
}

// Recalculate animPos to be equal to the position of the layer currently
// at the back of the animation, and flip animDirection
void reverse() {
  animPos = animDirection
            ? animPos - (numLayers - 1) * layerSpacing
            : animPos + (numLayers - 1) * layerSpacing;
  animPos = correctPosition(animPos);
  animDirection = !animDirection;
}

// Ensure that a given position lies within [0, animBufferSize)
int correctPosition(int position) {
  if (position < 0) {
    position += animBufferSize;
  } else if (position >= animBufferSize) {
    position -= animBufferSize;
  }
  return position;
}

Color calcNextFadeColor(Fade fade, int waveStep) {
  Color nextColor = {
    fade.prevColor.r + waveStep * fade.rSlope,
    fade.prevColor.g + waveStep * fade.gSlope,
    fade.prevColor.b + waveStep * fade.bSlope
  };
  return nextColor;
}

Fade calcFade(Color prevColor, Color nextColor, int width) {
  float rSlope = (nextColor.r - prevColor.r) / (float) width;
  float gSlope = (nextColor.g - prevColor.g) / (float) width;
  float bSlope = (nextColor.b - prevColor.b) / (float) width;
  Fade fade = {prevColor, rSlope, gSlope, bSlope};
  return fade;
}

// Color definitions
Color black = {0, 0, 0};
Color red = {255, 0, 0};
Color green = {0, 255, 0};
Color blue = {0, 0, 255};
Color maroon = {128, 0, 0};
Color firebrick = {178, 34, 34};
Color orangeRed = {255, 69, 0};
Color gold = {255, 200, 0};
Color yellow = {255, 255, 0};
Color yellowGreen = {154, 205, 0};
Color darkGreen = {0, 100, 0};
Color cyan = {0, 255, 255};
Color turquoise = {64, 224, 208};
Color midnightBlue = {25, 25, 112};
Color royalBlue {65, 105, 225};
Color purple = {145, 0, 255};
Color fuchsia = {255, 0, 255};
Color pink = {255, 20, 147};


Color gammaAdjust(Color inputColor) {
  Color adjustedColor = {
    pgm_read_byte(&gamma8[inputColor.r]),
    pgm_read_byte(&gamma8[inputColor.g]),
    pgm_read_byte(&gamma8[inputColor.b])
  };
  return adjustedColor;
}

const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };
