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
  bool switchSplit;
  bool switchGamma;
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
void displayWave(Color color, int width);
void fullTransition(Color color, int width);
void reverse();
void setGamma(boolean b);
void setSplit(Color color, boolean b);
void setSpacing(Color color, int spacing);
void setSplitAndSpacing(Color color, int spacing, boolean b);
void setDelay(int newDelay);

void test();

extern Adafruit_NeoPixel layers[];
extern const int numLayers;

extern Color red;
extern Color black;
extern Color green;
extern Color blue;
extern Color maroon;
extern Color firebrick;
extern Color orange;
extern Color gold;
extern Color yellow;
extern Color yellowGreen;
extern Color darkGreen;
extern Color cyan;
extern Color turquoise;
extern Color midnightBlue;
extern Color royalBlue;
extern Color purple;
extern Color fuchsia;
extern Color pink;
extern Color white;
extern Color darkWhite;
