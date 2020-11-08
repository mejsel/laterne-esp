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
    Normalbetrieb,
    Lautstaerke_Plus,
    Lautstaerke_Minus,
    Helligkeit_Plus,
    Helligkeit_Minus
  };

private:
  enum State state_;
  uint32_t last_millis_;
  bool helligkeit_zuletzt_erhoeht;
  bool lautstaerke_zuletzt_erhoeht;
  bool gestartet;

public:
  App();
  void begin();
  void update();

  enum State get_state() const { return state_; };
};

#endif /* APP_H */