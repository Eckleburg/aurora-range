/* lib_aurora_solid_waves.h */
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include <stdbool.h>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct Wave {
  Color color;
  int width;
  bool reverse;
  int spacing;
  int numWaves;
};

struct Fade {
  Color prevColor;
  float rSlope;
  float gSlope;
  float bSlope;
};

void initialize(uint8_t brightness);
void runAuroraRange(Wave waves[]);

void test();

extern Adafruit_NeoPixel layers[];
extern const int numLayers;

extern Color red;
extern Color black;
extern Color green;
extern Color blue;
extern Color maroon;
extern Color firebrick;
extern Color orangeRed;
extern Color gold;
extern Color yellow;
extern Color yellowGreen;
extern Color darkGreen;
