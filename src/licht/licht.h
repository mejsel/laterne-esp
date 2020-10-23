#ifndef LICHT_H
#define LICHT_H

class Licht
{
public:
  enum State
  {
    Idle
  };

private:
  enum State state_;

public:
  Licht();
  void begin();
  void update();

  enum State get_state() const { return state_; };
};

#endif /* LICHT_H */
