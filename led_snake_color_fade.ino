#include "FastLED.h"

#define NUM_LEDS 88
#define DATA_PIN 8

// Length of snake
#define SNAKE_LENGTH 20
// LEDs per second
#define SNAKE_SPEED 50
// Resolution of color fade, usually a number around 50 is not discernable
#define RESOLUTION 200.

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

int init_color[] = {0, 0, 0}, current_color[] = {0, 0, 0}, target_color[3], loop_iter = 0;
double color_increment[3];
void update_color() {
  if (loop_iter <= 0 || loop_iter >= RESOLUTION) {
    init_color[0] = target_color[0];
    init_color[1] = target_color[1];
    init_color[2] = target_color[2];
    
    current_color[0] = init_color[0];
    current_color[1] = init_color[1];
    current_color[2] = init_color[2];
    
    target_color[0] = rand() % 255;
    target_color[1] = rand() % 255;
    target_color[2] = rand() % 255;
    
    int difference[] = {target_color[0] - init_color[0], target_color[1] - init_color[1], target_color[2] - init_color[2]};
    
    color_increment[0] = difference[0] / RESOLUTION;
    color_increment[1] = difference[1] / RESOLUTION;
    color_increment[2] = difference[2] / RESOLUTION;
    
    loop_iter = 0;
  }
  
  current_color[0] = init_color[0] + (int)(color_increment[0] * loop_iter);
  current_color[1] = init_color[1] + (int)(color_increment[1] * loop_iter);
  current_color[2] = init_color[2] + (int)(color_increment[2] * loop_iter);
  
  loop_iter++;
}

void loop() {
  for (int i = 0; i < NUM_LEDS - SNAKE_LENGTH + 1; i++) {
    for (int j = 0; j < SNAKE_LENGTH; j++) {
      leds[i + j].setRGB(current_color[0], current_color[1], current_color[2]);
    }

    FastLED.show();
    delay(1000 / SNAKE_SPEED);
    update_color();

    Serial.print("(");
    Serial.print(current_color[0]);
    Serial.print(", ");
    Serial.print(current_color[1]);
    Serial.print(", ");
    Serial.print(current_color[2]);
    Serial.print(")\n");

    for (int j = 0; j < SNAKE_LENGTH; j++) {
      leds[i + j] = CRGB::Black;
    }
  }


  for (int i = NUM_LEDS - 1; i > SNAKE_LENGTH; i--) {
    for (int j = 0; j < SNAKE_LENGTH; j++) {
      leds[i - j].setRGB(current_color[0], current_color[1], current_color[2]);
    }

    FastLED.show();
    delay(1000 / SNAKE_SPEED);
    update_color();

    Serial.print("(");
    Serial.print(current_color[0]);
    Serial.print(", ");
    Serial.print(current_color[1]);
    Serial.print(", ");
    Serial.print(current_color[2]);
    Serial.print(")\n");

    for (int j = 0; j < SNAKE_LENGTH; j++) {
      leds[i - j] = CRGB::Black;
    }
  }
}
