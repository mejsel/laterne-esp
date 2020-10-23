#ifndef MUSIK_H
#define MUSIK_H

class Musik
{
public:
  enum State
  {
    Idle
  };

private:
  enum State state_;

public:
  Musik();
  void begin();
  void update();

  enum State get_state() const { return state_; };
};

#endif
