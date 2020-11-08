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
  uint8_t volume_;

public:
  Musik();
  void begin();
  void update();

  enum State get_state() const { return state_; };

  void print_detail(uint8_t type, int value);

  void set_volume(uint8_t volume);
  uint8_t get_volume() const { return volume_; };
  void inc_volume();
  void dec_volume();
};

#endif
