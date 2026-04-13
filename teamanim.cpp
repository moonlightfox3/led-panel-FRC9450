// Uses the FastLED Arduino library for interfacing with LEDs
#include <FastLED.h>

// Defined in fan_rgb_teamanim.ino
int NUM_LEDS;
extern CRGB leds[];

// Config - Options
const double FRAMERATE = 6.0;

// Config - Color data
const CRGB BLUE              = CRGB(  0,   5,  70);
const CRGB BLUE_GRADIENT     = CRGB(  0,  11, 135);
const CRGB BLUE_GRADIENT_2   = CRGB(  0,  15, 210);
const CRGB ORANGE            = CRGB(255,  17,   0);
const CRGB ORANGE_GRADIENT   = CRGB(220,  25,   0);
const CRGB ORANGE_GRADIENT_2 = CRGB(225,  35,   0);

// Config - Text data
const bool SHOW_TEXT = false;
const bool INVERT_TEXT = false;
const bool TEXT_DATA[48] = {
  1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1,
  0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1
};

// Color array
const int COLORS_SIZE = 10;
CRGB COLORS[COLORS_SIZE];

// Vars
int offset = 0;
int start;
int end;

void addReversedColors(int startIndex) { // a,b,c,d,e,f -> a,b,c,d,e,f,e,d,c,b
  for (int i = startIndex - 2; i >= 1; i--) {
    COLORS[startIndex] = COLORS[i];
    startIndex++;
  }
}
void reverseColors(int size) {
  for (int i = 0; i < size / 2; i++) {
    int endI = size - 1 - i;
    CRGB temp = COLORS[i];
    COLORS[i] = COLORS[endI];
    COLORS[endI] = temp;
  }
}

double teamanim_setup(int numLeds) {
  // Config - Color array data
  COLORS[0] = BLUE;
  COLORS[1] = BLUE_GRADIENT;
  COLORS[2] = BLUE_GRADIENT_2;
  COLORS[3] = ORANGE_GRADIENT_2;
  COLORS[4] = ORANGE_GRADIENT;
  COLORS[5] = ORANGE;
  
  // Color array final setup
  addReversedColors(6);
  reverseColors(COLORS_SIZE);

  // Vars
  NUM_LEDS = numLeds;
  start = 0;
  end = NUM_LEDS - 1;
  return FRAMERATE;
}
void teamanim() {
  int ledOffset = COLORS_SIZE - ((end + 1 - start) % COLORS_SIZE); // Used to start the animation at the correct place
  for (int led = end; led >= start; led--) {
    int colorIndex = (offset + ledOffset) % COLORS_SIZE;
    ledOffset++;
    
    if (SHOW_TEXT && INVERT_TEXT == TEXT_DATA[led]) leds[led] = CRGB::Black; // Show text
    else leds[led] = COLORS[colorIndex];
  }
  offset = (offset + 1) % COLORS_SIZE; // Update offset
}
