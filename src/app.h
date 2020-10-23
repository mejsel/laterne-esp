#ifndef APP_H
#define APP_H

#include <Arduino.h>

class App
{
public:
  enum State
  {
    Idle
  };

private:
  enum State state_;

public:
  App();
  void begin();
  void update();

  enum State get_state() const { return state_; };
};

#endif /* APP_H */