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

// Function declarations
void purpleIntro(Color spaceColor);
void blueDarkWhite();
void blueDarkWhite();
void blueDarkWhite();
void rainbow();
void yellowAndRed();
void blueAndFuchsia();
void cyanAndPink(Color spaceColor);
void newPattern();

Color spaceColors[2] = {black, white};
bool spaceColorSelector = false;

void setup() {
  int brightness = 80;
  initialize(brightness);
  setGamma(true);
//  Serial.begin(9600);
}

void loop() {
  bool shortLoop = false;
  if (shortLoop) {

  } else {
    Color spaceColor;
    if (!spaceColorSelector) {
      spaceColor = spaceColors[0];
    } else {
      spaceColor = spaceColors[1];
    }    
    purpleIntro(spaceColor);
    bluePurpleSlow();
    purpleIntro(spaceColor);
    
    delay(2000);
    fullTransition(white, 80);
    setDelay(3);
    blueDarkWhite();
    
    delay(500);
    fullTransition(yellow, 30);
    setDelay(2);
    yellowAndRed();

    delay(1500);
    setDelay(1);
    reverse();
    rainbow();
    fullTransition(fuchsia, 80);
    
    setSpacing(fuchsia, 20);
    reverse();
    setDelay(3);
//    blueAndFuchsia();

    setDelay(0);
//    blueGreen();
    
    reverse();
    setDelay(1);
    yellowPurpleTurquoise();

    displayWave(black, 120);
    displayWave(black, 120);
    displayWave(black, 120);
    triads();
  
    cyanAndPink(spaceColor);
    setSpacing(black, 12);
    setDelay(4);
    seaGreenAndOrange();

    setDelay(3);
    rainbow();
    spaceColorSelector = !spaceColorSelector;
    setDelay(4);
  }
}

void purpleIntro(Color spaceColor) {
  setDelay(10);
  for (int i = 0; i < 3; i++) {
    displayWave(purple, 100);
    setDelay(4);
    displayWave(spaceColor, 100);
    displayWave(spaceColor, 100);
    delay(3000);
  }
  for (int i = 0; i < 4; i++) {
    displayWave(purple, 40);
    displayWave(spaceColor, 40);
    displayWave(spaceColor, 100);
  }
  setSpacing(purple, 10);
}

void bluePurpleSlow() {
  for (int i = 0; i < 2; i++) {
    displayWave(purple, 120);
    displayWave(blue, 120);
    displayWave(black, 120);
    displayWave(black, 120);
    delay(1500);
  }

  for (int i = 0; i < 4; i++) {
    displayWave(purple, 120);
    displayWave(blue, 40);
    displayWave(black, 80);
    displayWave(blue, 120);
    displayWave(purple, 120);
    displayWave(black, 120);  
  }
}

void blueDarkWhite() {
  for (int i = 0; i < 8; i++) {
//  for (int i = 0; i < 1; i++) {
    displayWave(blue, 40);
    displayWave(red, 40);
    displayWave(darkWhite, 80);
    displayWave(blue, 100);
    displayWave(darkWhite, 20);  
    displayWave(blue, 100);
    displayWave(blue, 60);
    displayWave(blue, 30);
    displayWave(purple, 90);
    reverse();
  }  
}

void rainbow() {
  bool shouldReverse = false;
  for (int i = 0; i < 12; i++) {
//  for (int i = 0; i < 2; i++) {
    displayWave(green, 40);
    displayWave(red, 70);
    reverse();
    displayWave(blue, 20);
    displayWave(green, 50);
    displayWave(red, 40);
    displayWave(green, 10);
    displayWave(blue, 80);
    reverse();
    displayWave(red, 30);
    displayWave(blue, 90);
    displayWave(red, 90);
    displayWave(green, 90);
    displayWave(red, 60);
    if (shouldReverse) {
      reverse();
    }
    shouldReverse = !shouldReverse;
  }
  displayWave(red, 150);
}

void yellowAndRed() {
  for (int i = 0; i < 6; i++) {
    displayWave(yellow, 40);
    displayWave(black, 70);
    displayWave(yellow, 10);
    displayWave(yellow, 60);
    displayWave(red, 90);
    displayWave(yellow, 30);
    displayWave(yellow, 60);
    reverse();
    displayWave(black, 60);
    displayWave(black, 60);
    displayWave(black, 60);
    delay(200);
    displayWave(red, 10);
    displayWave(yellow, 60);
    reverse();
    displayWave(black, 30);
    displayWave(black, 50);
    reverse();
    displayWave(red, 10);
    displayWave(yellow, 40);
    displayWave(yellow, 60);
    reverse();
    displayWave(black, 30);
    displayWave(black, 50);
    reverse();    
    displayWave(yellow, 60);
  }
}

void blueAndFuchsia() {
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 4; i++) {
//    for (int i = 0; i < 2; i++) {
      displayWave(blue, 80);
      displayWave(fuchsia, 80);
      displayWave(fuchsia, 60);
    }
    displayWave(blue, 80);
    displayWave(blue, 80);
    displayWave(blue, 80);
    for (int i = 0; i < 3; i++) {
      displayWave(royalBlue, 100);
      displayWave(purple, 30);
      displayWave(royalBlue, 100);
    }
    displayWave(darkGreen, 100);
    displayWave(blue, 100);
    reverse();
  }
}

void triads() {
  initialize(160);

  for (int j = 0; j < 2; j++) {
    setSpacing(black, 4);
    setDelay(4);
    for (int i = 0; i < 3; i++) {
      displayWave(triadSalmon, 20);
      displayWave(triadBlue, 20);
      displayWave(triadSalmon, 20);
      displayWave(triadBlue, 20);
      displayWave(triadSalmon, 20);
      displayWave(triadBlue, 20);
      displayWave(triadSalmon, 20);
      displayWave(triadBlue, 20);
      displayWave(triadSalmon, 20);
      displayWave(triadBlue, 20);
      reverse();
      displayWave(triadSalmon, 20);
      displayWave(triadBlue, 20);
      displayWave(triadSalmon, 20);
      displayWave(triadBlue, 20);
      reverse();
    }
    setSpacing(triadBlue, 7);
    setDelay(1);
    for (int i = 0; i < 3; i++) {
      displayWave(triadBlue, 120);
      displayWave(triadSalmon, 120);
      displayWave(triadGreen, 120);
      displayWave(black, 120);
      displayWave(triadGreen, 80);
      displayWave(triadSalmon, 20);
      displayWave(triadBlue, 120);
      displayWave(triadSalmon, 20);
      displayWave(triadGreen, 100);
      displayWave(black, 120);
      reverse();
    }
    displayWave(black, 120);
    displayWave(black, 120);
  }
  initialize(80);
}

void cyanAndPink(Color spaceColor) {
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
}

void seaGreenAndOrange() {
  for (int i = 0; i < 5; i++) {
    displayWave(seaGreen, 100);
    displayWave(black, 20);
    displayWave(orange, 30);
    displayWave(seaGreen, 30);
    displayWave(black, 20);
    displayWave(red, 50);
    displayWave(red, 30);
    reverse();
    displayWave(orange, 60);
    displayWave(white, 30);
    displayWave(orange, 60);
    displayWave(seaGreen, 40);
    displayWave(red, 60);
    displayWave(red, 60);
    reverse();
    displayWave(seaGreen, 80);
    displayWave(red, 10);
    displayWave(seaGreen, 80);
    displayWave(black, 40);
    displayWave(orange, 60);
  }
}

void blueGreen() {
  for (int j = 0; j < 3; j++) {
    displayWave(blue, 120);
    displayWave(green, 120);
    displayWave(blue, 120);
    displayWave(green, 120);
    displayWave(blue, 120);
    displayWave(green, 120);
    reverse();
    displayWave(blue, 120);
    displayWave(green, 120);
    displayWave(blue, 120);
    displayWave(green, 120);
    displayWave(blue, 120);
    displayWave(green, 120);
    displayWave(blue, 120);
    displayWave(green, 120);
    displayWave(black, 60);
    displayWave(green, 20);
    displayWave(blue, 120);
    displayWave(black, 120);
    displayWave(green, 120);
    displayWave(blue, 120);
    displayWave(black, 120);
    displayWave(green, 120);
    displayWave(blue, 120);
    displayWave(black, 120);
    displayWave(green, 120);
    displayWave(blue, 120);
    reverse();
  }
}

void yellowPurpleTurquoise() {
  for (int i = 0; i < 2; i++) {
    displayWave(yellow, 120);
    displayWave(purple, 30);
    displayWave(yellow, 120);
    displayWave(black, 30);
    displayWave(purple, 20);
    displayWave(turquoise, 120);
    displayWave(yellow, 120);
    displayWave(purple, 120);
    displayWave(black, 120);
    displayWave(black, 40);
    displayWave(turquoise, 20);
    displayWave(purple, 120);
    displayWave(white, 60);
    reverse();
    displayWave(purple, 120);
    displayWave(turquoise, 20);
    displayWave(black, 120);
    displayWave(white, 120);
    displayWave(purple, 120);
    displayWave(yellow, 120);
    displayWave(turquoise, 120);
    displayWave(black, 120);
    displayWave(white, 120);
    displayWave(purple, 120);
    displayWave(yellow, 120);
    displayWave(turquoise, 120);
    displayWave(black, 120);
    displayWave(white, 120);
    displayWave(purple, 120);
    displayWave(yellow, 120);
    displayWave(turquoise, 120);
}  
}
