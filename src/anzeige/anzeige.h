#ifndef ANZEIGE_H
#define ANZEIGE_H

#include <TFT_eSPI.h>
#include <SPI.h>
#include "app.h"
#include "licht/licht.h"
#include "musik/musik.h"
#include "batterie/batterie.h"

class Anzeige : public TFT_eSPI
{
public:
  enum State
  {
    Splash_Screen,
    Main_Screen
  };

private:
  enum State state_;
  uint32_t last_millis_;
  uint32_t frame_;
  uint32_t batterie_ticks_;
  char batterie_str_[10];

public:
  Anzeige();
  void begin();
  void update();
  enum State get_state() const { return state_; };

  void draw_splash_screen();
  void update_splash_screen();

  void draw_main_screen();
  void update_main_screen();


private:
  void draw_batterie();
};

#endif /* ANZEIGE_H */
