// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
//#include <SPI.h>  /       // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

// Cog Reconvene LED Strip Lengths
int length0 = 58;
int length1 = 102;
int length2 = 88;
int length3 = 70;
int length4 = 59;
int length5 = 51;
int length6 = 46;
int lengths[] = {length0, length1, length2, length3, length4, length5, length6};

// Data and Clock Pins
int data0 = 2;
int data1 = 4;
int data2 = 6;
int data3 = 8;
int data4 = 10;
int data5 = 44;
int data6 = 12;

int clock0 = 3;
int clock1 = 5;
int clock2 = 7;
int clock3 = 9;
int clock4 = 11;
int clock5 = 45;
int clock6 = 13;

// DotStar Strp Definitions
Adafruit_DotStar strip0(length0, data0, clock0, DOTSTAR_BRG);
Adafruit_DotStar strip1(length1, data1, clock1, DOTSTAR_BRG);
Adafruit_DotStar strip2(length2, data2, clock2, DOTSTAR_BRG);
Adafruit_DotStar strip3(length3, data3, clock3, DOTSTAR_BRG);
Adafruit_DotStar strip4(length4, data4, clock4, DOTSTAR_BRG);
Adafruit_DotStar strip5(length5, data5, clock5, DOTSTAR_BRG);
Adafruit_DotStar strip6(length6, data6, clock6, DOTSTAR_BRG);
Adafruit_DotStar layers[] = {strip0, strip1, strip2, strip3, strip4, strip5, strip6};
int numLayers = sizeof(layers) / sizeof(Adafruit_DotStar);

// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BRG);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip0.begin(); // Initialize pins for output
  strip0.show();  // Turn all LEDs off ASAP
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();
  strip4.begin();
  strip4.show();
  strip5.begin();
  strip5.show();
  strip6.begin();
  strip6.show();
}

void loop() {
  rainbow();
}

void rainbow() {
  int spacing = 15;
  double scale = 0.4;
  for (int c = 0; c < 255; c++) {
    for (int layer = 0; layer < numLayers; layer++) {
      int add = spacing * layer;
      assignLayer(layer, scale * getRed(c + add), scale * getGreen(c + add), scale * getBlue(c + add));       
    }
    showAll();
  }
}

int getRed(int step) {
  return getColorStep(step + 85);
}

int getGreen(int step) {
  return getColorStep(step);
}

int getBlue(int step) {
  return getColorStep(step + 2 * 85);
}

int getColorStep(int step) {
  if (step < 85) {
    return 0;  
  } else if (step < 170) {
    return (step - 85) * 3;  
  } else if (step < 255) {
    return 255 - (step - 170) * 3;  
  } else {
    return getColorStep(step - 255);  
  }  
}

void assignLayer(int layer, int r, int g, int b) {
  uint32_t color = (uint32_t)(((long)g << 16) + ((long)r << 8) + (b));
  layers[layer].fill(color, 0, 0);
//  for (int led = 0; led < lengths[layer]; led++) {
//    layers[layer].setPixelColor(led, color);  
//  }
}

void showAll() {
  strip0.show();
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
}
