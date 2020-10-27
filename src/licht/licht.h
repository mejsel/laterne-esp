#ifndef LICHT_H
#define LICHT_H

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS 7
#define DATA_PIN  17

class Licht
{
public:
  enum State
  {
    Weiss,
    Gruen,
    Blau,
    Rot,
    Regenbogen,
    Regenbogen_Rundlauf,
    Kerze,
    Aus,
  };

private:
  enum State state_;
  CRGB leds_[NUM_LEDS];
  uint32_t last_millis_;
  uint32_t frame_;

public:
  Licht();
  void begin();
  void update();

  enum State get_state() const { return state_; };
  void set_state(enum State state);

  uint8_t next_effect();
  uint8_t previous_effect();

  

};

#endif /* LICHT_H */
