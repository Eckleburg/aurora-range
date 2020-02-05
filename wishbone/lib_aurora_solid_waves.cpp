/* lib_aurora_solid_waves.c */
#include "lib_aurora_solid_waves.h"
#include <Adafruit_NeoPixel.h>

const int animBufferSize = 256;
Color animBuffer[animBufferSize];
int animPos = 0;
int layerSpacing = 8;
int numLayers;
bool splitMode = false;
bool animDirection = false;

/* Forward declaration of internal library functions */
void displayWave(Wave wave);
void newSpacing(Wave wave);
void assignLayer(int layer, Color color);
void reverse();
int correctPosition(int position);
Color calcNextFadeColor(Fade fade, int waveStep);
Fade calcFade(Color prevColor, Color nextColor, int width);

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
  if (wave.spacing > 0) {
    newSpacing(wave);
  }

  Color prevColor = animBuffer[animPos];
  Fade fade = calcFade(prevColor, wave.color, wave.width);
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
      int thisLayerPos = animDirection
                         ? (animPos - (numLayers - layerCntr - 1) * layerSpacing)
                         : (animPos + layerCntr * layerSpacing);
      thisLayerPos = correctPosition(thisLayerPos);
      assignLayer(layerCntr, animBuffer[thisLayerPos]);
    }
  }
}

// Display two waves in order to get the whole range to one solid color, then
// set the new spacing.
void newSpacing (Wave wave) {
  Wave newSpacingWave = {.color = wave.color, .width = numLayers * layerSpacing};
  displayWave(newSpacingWave);
  displayWave(newSpacingWave);
  layerSpacing = wave.spacing;
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
  } else if (position > animBufferSize - 1) {
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
