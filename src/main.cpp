#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"
#include <FastLED.h>

DFRobotDFPlayerMini mp3player;

#define NUM_LEDS 2
#define DATA_PIN  17
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 13, 12);

  Serial.println("laterne-esp serial output");
  Serial1.println("serial1 output to dfplayer");

  if (!mp3player.begin(Serial1)) {
    Serial.println("Fehler beim initialisieren von mp3player");
    while(true);
  }

  Serial.println("mp3player initialisiert");

  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical

}

void loop() {
  // put your main code here, to run repeatedly:
  leds[0] = CRGB::Blue;
  leds[1] = CRGB::Red;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Green;
  leds[1] = CRGB::Yellow;
  FastLED.show();
  delay(1000);
}