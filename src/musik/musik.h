#ifndef MUSIK_H
#define MUSIK_H

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

class Musik
{
public:
  enum State
  {
    Aus,
    Fehler,
    Bereit
  };
  DFRobotDFPlayerMini dfplayer;

private:
  enum State state_;
  uint32_t last_millis_;

public:
  Musik();
  void begin();
  void update();

  enum State get_state() const { return state_; };

  void print_detail(uint8_t type, int value);
};

#endif
