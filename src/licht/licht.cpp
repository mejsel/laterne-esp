#include "licht.h"

Licht::Licht()
  : state_(Aus)
  , last_millis_(0)
  , frame_(0)
{
}

void Licht::begin()
{
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds_, NUM_LEDS);
  FastLED.setBrightness(100);
  //state_ = Regenbogen_Rundlauf;
}

void Licht::update()
{
  switch (state_)
  {
    case Aus:
    {
      if (millis() > last_millis_ + 200)
      {
        FastLED.clear();
        FastLED.show();
        last_millis_ = millis();
      }
      break;
    }
    case Weiss:
    {
      if (millis() > last_millis_ + 20)
      {
        FastLED.showColor(CRGB::White);
        last_millis_ = millis();
      }
      break;
    }
    case Gruen:
    {
      if (millis() > last_millis_ + 20)
      {
        FastLED.showColor(CRGB::Green);
        last_millis_ = millis();
      }
      break;
    }
    case Blau:
    {
      if (millis() > last_millis_ + 20)
      {
        FastLED.showColor(CRGB::Blue);
        last_millis_ = millis();
      }
      break;
    }
    case Rot:
    {
      if (millis() > last_millis_ + 20)
      {
        FastLED.showColor(CRGB::Red);
        last_millis_ = millis();
      }
      break;
    }
    case Regenbogen:
    {
      if (millis() > last_millis_ + 20)
      {
        last_millis_ = millis();
        fill_rainbow(leds_, NUM_LEDS, frame_, 1);
        FastLED.show();
        frame_++;
        frame_ %= 255;
        // Serial.print("(licht) frame: ");
        // Serial.println(frame_);
      }
      break;
    }
    case Regenbogen_Rundlauf:
    {
      if (millis() > last_millis_ + 200)
      {
        last_millis_ = millis();
        fill_rainbow(leds_, NUM_LEDS, frame_, 20);
        FastLED.show();
        frame_++;
        frame_ %= 255;
        // Serial.print("(licht) frame: ");
        // Serial.println(frame_);
      }
      break;
    }
    case Kerze:
    {
      if (millis() > last_millis_ + 20)
      {
        last_millis_ = millis();
        FastLED.showColor(CRGB::OrangeRed);
        //FastLED.show();
        frame_++;
        frame_ %= 255;
      }
      break;
    }
  }
}

void Licht::set_state(enum State state)
{
  //last_millis_ = millis();
  last_millis_ = 0;
  frame_ = 0;
  state_ = state;
}

uint8_t Licht::next_effect()
{
  if (state_+1 == Ende)
    set_state((enum State) 0);
  else
    set_state((enum State) (state_+1));
  return (int8_t) get_state();
}

uint8_t Licht::previous_effect()
{
  if ((int32_t) state_ == 0)
    set_state((enum State)(Ende-1));
  else
    set_state((enum State) (state_-1));
  return (int8_t) get_state();
}