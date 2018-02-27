#include "FastLED.h"

#define NUM_LEDS 115
#define DATA_PIN 8
#define BUTTON_PIN 2

#define SNAKE_LENGTH 5
#define SNAKE_SPEED 5

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  
  delay(1000);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  pinMode(BUTTON_PIN, INPUT);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

int teamColor = 0; // 0: red, 1: blue, 2: green
int index = 0;
bool reverse = false;
bool lastState = false;

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    bool quit = false;
    for (int i = 0; i < 100; i++) {
      if (digitalRead(BUTTON_PIN) == LOW) {
        quit = true;
      }
      if (!quit) {
      delay(10);
      }
    }

    if (!quit) {
      Serial.write("on\n");
      teamColor++;
      if (teamColor > 2) {
        teamColor = 0;
      }
    }
  }
  // Serial.write(buttonState ? "1\n" : "0\n");

  
  char number[2];
  itoa(index, number, 10);
  // Serial.write(number);
  // Serial.write("\n");
  
    
  for (int i = -1; i < SNAKE_LENGTH + 1; i++) {
    if (index + i < NUM_LEDS) {
      leds[index + i].setRGB(teamColor == 2 ? 255 : 0, teamColor == 0 ? 255 : 0, teamColor == 1 ? 255 : 0);
      if (i == -1 || i == SNAKE_LENGTH) {
        leds[index + i].setRGB(0, 0, 0);
      }
    }
    
  }

  FastLED.show();
  delay(SNAKE_SPEED);

  if (!reverse) {
    index++;
  } else {
    index--;
  }
  
  if (index >= NUM_LEDS) {
    reverse = true;
  } else if (index < 0) {
    reverse = false;
  }
}
