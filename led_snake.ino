#include "FastLED.h"

#define NUM_LEDS 88
#define SWITCH_PIN 7
#define DATA_PIN 8

#define SNAKE_LENGTH 20
#define SNAKE_SPEED 50

CRGB leds[NUM_LEDS];
int red_color[3] = {255, 0, 0};
int blue_color[3] = {0, 0, 255};

void setup() {
  Serial.begin(9600);
  
  delay(1000);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  pinMode(SWITCH_PIN, INPUT);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

void loop() {
  bool switch_state = digitalRead(SWITCH_PIN) == true;

  for (int i = 0; i < NUM_LEDS - SNAKE_LENGTH + 1; i++) {
    for (int j = 0; j < SNAKE_LENGTH; j++) {
      leds[i + j].setRGB(switch_state ? red_color[0] : blue_color[0], switch_state ? red_color[1] : blue_color[1], switch_state ? red_color[2] : blue_color[2]);
    }

    FastLED.show();
    delay(1000 / SNAKE_SPEED);

    for (int j = 0; j < SNAKE_LENGTH; j++) {
      leds[i + j] = CRGB::Black;
    }
  }

  switch_state = digitalRead(SWITCH_PIN) == true;

  for (int i = NUM_LEDS - 1; i > SNAKE_LENGTH; i--) {
    for (int j = 0; j < SNAKE_LENGTH; j++) {
      leds[i - j].setRGB(switch_state ? red_color[0] : blue_color[0], switch_state ? red_color[1] : blue_color[1], switch_state ? red_color[2] : blue_color[2]);
    }

    FastLED.show();
    delay(1000 / SNAKE_SPEED);

    for (int j = 0; j < SNAKE_LENGTH; j++) {
      leds[i - j] = CRGB::Black;
    }
  }
}
