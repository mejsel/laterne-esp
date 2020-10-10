#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"
#include <FastLED.h>

DFRobotDFPlayerMini mp3player;

#define NUM_LEDS 2
#define DATA_PIN  17
CRGB leds[NUM_LEDS];

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 15, 13);

  Serial.println("laterne-esp serial output");
  //Serial1.println("serial1 output to dfplayer");

  delay(500);
  if (!mp3player.begin(Serial1)) {
    Serial.println("Fehler beim initialisieren von mp3player");
    //while(true);
  }


  delay(500);
  mp3player.volume(15);
  mp3player.enableLoopAll();
  //mp3player.play(1);

  Serial.println("mp3player initialisiert");

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical

}

void loop() {
  // put your main code here, to run repeatedly:
  leds[0] = CRGB::Blue;
  leds[1] = CRGB::Red;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Green;
  leds[1] = CRGB::Yellow;
  FastLED.show();
  delay(500);
  if (mp3player.available())
  {
    printDetail(mp3player.readType(), mp3player.read());
  }
}