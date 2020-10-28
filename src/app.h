#ifndef APP_H
#define APP_H

#include <Arduino.h>
#include "anzeige/anzeige.h"
#include "licht/licht.h"
#include "musik/musik.h"
#include <SimpleButton.h>

class App
{
public:
  enum State
  {
    Init,
    An,
    Lautstaerke_Plus,
    Lautstaerke_Minus,
  };

private:
  enum State state_;
  uint32_t last_millis_;
  uint8_t brightness_percent;
  bool increase_brightness;

public:
  App();
  void begin();
  void update();

  enum State get_state() const { return state_; };
};

#endif /* APP_H */