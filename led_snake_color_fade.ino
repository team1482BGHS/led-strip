#include "FastLED.h"

#define NUM_LEDS 88
#define DATA_PIN 8

// Resolution of color fade, usually a number around 50 is not discernable
#define RESOLUTION 255.
// Time, in seconds to fade to the next color
#define FADE_TIME 20.

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

int current[] = {0, 0, 0};

void loop() {
  int target[] = {rand() % 255, rand() % 255, rand() % 255};
  int difference[] = {target[0] - current[0], target[1] - current[1], target[2] - current[2]};
  double increment[] = {difference[0]/RESOLUTION, difference[1]/RESOLUTION, difference[2]/RESOLUTION};

  Serial.print(target[0]);
  Serial.print(",");
  Serial.print(target[1]);
  Serial.print(",");
  Serial.print(target[2]);
  Serial.print(" (");
  Serial.print(increment[0]);
  Serial.print(",");
  Serial.print(increment[1]);
  Serial.print(",");
  Serial.print(increment[2]);
  Serial.print(")\n");
  
  for (int i = 0; i < RESOLUTION; i++) {
    for (int led = 0; led < NUM_LEDS; led++) {
      leds[led].setRGB(current[0] + (increment[0] * i), current[1] + (increment[1] * i), current[2] + (increment[2] * i));
    }
    
    FastLED.show();
    delay(FADE_TIME * 1000 / RESOLUTION);
  }

  current[0] = target[0];
  current[1] = target[1];
  current[2] = target[2];
}
