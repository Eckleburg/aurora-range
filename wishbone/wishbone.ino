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
  Color spaceColor = {255, 70, 0};
  
  reverse();
  for (int i = 0; i < 3; i++) {
    displayWave(red, 100);
    displayWave(spaceColor, 100);
    displayWave(spaceColor, 100);
    delay(3000);
  }
  for (int i = 0; i < 4; i++) {
    displayWave(red, 40);
    displayWave(spaceColor, 40);
    displayWave(spaceColor, 100);
  }
  setSpacing(red, 10);
  delay(700);
  
  setGamma(true);
  fullTransition(white, 80);
  setDelay(3);
//  for (int i = 0; i < 8; i++) {
  for (int i = 0; i < 2; i++) {
    displayWave(blue, 40);
    displayWave(red, 40);
    displayWave(darkWhite, 80);
    displayWave(blue, 100);
    displayWave(darkWhite, 20);  
    displayWave(blue, 100);
    displayWave(blue, 60);
  }
  
  setSpacing(black, 20);
  delay(1500);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      setDelay(1);
      displayWave(cyan, 80);
      displayWave(cyan, 80);
      displayWave(spaceColor, 40);
      displayWave(cyan, 40);
    }
    setDelay(0);
    displayWave(fuchsia, 140);
    displayWave(cyan, 80);
    reverse();
  }
  
  setDelay(1);
  reverse();
  bool shouldReverse = false;
  for (int i = 0; i < 8; i++) {
//  for (int i = 0; i < 2; i++) {
    displayWave(green, 40);
    displayWave(red, 70);
    displayWave(blue, 20);
    displayWave(green, 50);
    displayWave(red, 40);
    displayWave(green, 10);
    displayWave(blue, 80);
    displayWave(red, 30);
    if (shouldReverse) {
      reverse();
    }
    shouldReverse = !shouldReverse;
  }
  displayWave(red, 150);
  fullTransition(fuchsia, 80);
  
  setSpacing(fuchsia, 20);
  reverse();
  setDelay(3);
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 10; i++) {
//    for (int i = 0; i < 2; i++) {
      displayWave(blue, 80);
      displayWave(fuchsia, 80);
      displayWave(fuchsia, 60);
    }
    displayWave(blue, 80);
    displayWave(blue, 80);
    displayWave(blue, 80);
    for (int i = 0; i < 6; i++) {
      displayWave(royalBlue, 100);
      displayWave(purple, 30);
      displayWave(royalBlue, 100);
    }
    displayWave(darkGreen, 100);
    displayWave(blue, 100);
    reverse();
  }

  spaceColor = orange;
  setSpacing(black, 20);
  setDelay(4);
}
