// LEDs from old PC fans

// Uses the FastLED Arduino library for interfacing with LEDs
#include <FastLED.h>

// Defined in teamanim.cpp
double FRAMERATE;
extern double teamanim_setup(int numLeds);
extern void teamanim();

// FastLED stuff
FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

// FastLED setup
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

// LED data
const int DATA_PIN = 3;
const int NUM_LEDS_ONE = 16;
const int NUM_LEDS = 48;
const int NUM_STRIPS = 3;
const int LED_IDS[NUM_LEDS] = { // Maps array indexes to hardware LED indexes
  39, 38, 37, 36, 35, 34, 33, 32, 47, 46, 45, 44, 43, 42, 41, 40,
  23, 22, 21, 20, 19, 18, 17, 16, 31, 30, 29, 28, 27, 26, 25, 24,
   7,  6,  5,  4,  3,  2,  1,  0, 15, 14, 13, 12, 11, 10,  9,  8
};
CRGB leds[NUM_LEDS_ONE];
CRGB ledsDevice[NUM_LEDS];

// Config
const int BRIGHTNESS = 100;

void setup() {
  // Init LED array
  for (int i = 0; i < NUM_LEDS_ONE; i++) leds[i] = CRGB(0, 0, 0);

  // Init FastLED
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(ledsDevice, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // Init animation
  FRAMERATE = teamanim_setup(NUM_LEDS_ONE);
}
void loop() {
  // Run animation
  teamanim();
  
  // Reorder and display LEDs
  for (int i = 0; i < NUM_LEDS_ONE; i++) {
    for (int j = 0; j < NUM_STRIPS; j++) ledsDevice[LED_IDS[(NUM_LEDS_ONE * j) + i]] = leds[i];
  }
  FastLED.show();

  // Delay for correct framerate
  FastLED.delay(1000 / FRAMERATE);
}
