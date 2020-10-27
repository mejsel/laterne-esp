#include "anzeige.h"

extern Anzeige anzeige;
extern Licht licht;
extern Musik musik;
extern Batterie batterie;
extern simplebutton::ButtonPullup button_licht;
extern simplebutton::ButtonPullup button_links;
extern simplebutton::ButtonPullup button_rechts;

Anzeige::Anzeige()
  : state_(Splash_Screen)
  , last_millis_(0)
  , frame_(0)
  , batterie_ticks_(0)
{
}

void Anzeige::begin()
{
    TFT_eSPI::init();
    setRotation(3);
    if (TFT_BL > 0)
    {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
    }
    draw_splash_screen();
}

void Anzeige::update()
{
  switch (state_)
  {
    case Splash_Screen:
    {
      update_splash_screen();
      break;
    }
    case Main_Screen:
    {
      update_main_screen();
      break;
    }
  }
}

void Anzeige::draw_splash_screen()
{
  state_ = Splash_Screen;
  last_millis_ = millis();
  frame_ = 0;
  Serial.println("(anzeige) draw splash screen");
  fillScreen(TFT_BLACK);
  setTextFont(4);
  setTextColor(TFT_WHITE, TFT_BLACK);
  setTextDatum(MC_DATUM);
  drawString(F("LaterneLaterne"), width()/2, height()/2-20);
}

void Anzeige::update_splash_screen()
{
    if (millis() > last_millis_ + 1000 && frame_ == 0)
    {
      setTextFont(2);
      drawString(F("Software Version 1.0"), width()/2, height()/2+30);
      frame_ = 1;
    }
    if (millis() > last_millis_ + 2000 && frame_ == 1)
    {
      if (musik.get_state() == Musik::Fehler)
      {
        setTextColor(TFT_ORANGE, TFT_BLACK);
        drawString(F("MP3 Player: Fehler"), width()/2, height()/2+50);
      }
      else
      {
        drawString(F("MP3 Player: initialisiert"), width()/2, height()/2+50);
      }
      frame_ = 2;
    }
    else if (millis() > last_millis_ + 5000)
    {
      draw_main_screen();
      state_ = Main_Screen;
    }
}

void Anzeige::draw_main_screen()
{
  state_ = Main_Screen;
  Serial.println("(anzeige) draw main screen");
  fillScreen(TFT_BLACK);
  setTextFont(4);
  setTextColor(TFT_ORANGE, TFT_BLACK);
  setTextDatum(MR_DATUM);
  drawString(F("BAT_ADC: "), 150, 20);
  drawString(F("BAT_FILT: "), 150, 40);
  drawString(F("BAT_PROZ: "), 150, 60);
  setTextDatum(ML_DATUM);
}

void Anzeige::update_main_screen()
{
  if (batterie.get_ticks() != batterie_ticks_)
  {
    draw_batterie();
    batterie_ticks_ = batterie.get_ticks();
  }
}

void Anzeige::draw_batterie()
{
  sprintf(batterie_str_, "%i", batterie.get_adc());
  drawString(batterie_str_, 150, 20);
  sprintf(batterie_str_, "%i", batterie.get_adc_filtered());
  drawString(batterie_str_, 150, 40);
  sprintf(batterie_str_, "%i %%", batterie.get_prozent());
  drawString(batterie_str_, 150, 60);
}