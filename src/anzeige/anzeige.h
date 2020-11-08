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
  uint32_t batterie_wert_;
  uint32_t batterie_breite_;
  char batterie_str_[10];
  uint8_t helligkeit_;
  char lichteffekt_str_[30];
  char volume_str[10];
  uint8_t volume_;
  uint32_t volume_breite_;
  uint32_t delay_millis_;
  uint32_t app_state_nr_;
  uint32_t licht_state_nr_;
  uint32_t helligkeit_breite_;

public:
  Anzeige();
  void begin();
  void update();
  enum State get_state() const { return state_; };

  void draw_splash_screen();
  void update_splash_screen();

  void draw_main_screen();
  void update_main_screen();
};

#endif /* ANZEIGE_H */
