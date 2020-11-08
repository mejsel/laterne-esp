#include "anzeige.h"

extern Anzeige anzeige;
extern Licht licht;
extern Musik musik;
extern Batterie batterie;
extern simplebutton::ButtonPullup button_licht;
extern simplebutton::ButtonPullup button_links;
extern simplebutton::ButtonPullup button_rechts;
extern App app;

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
  // if (app_state_nr_ != (uint32_t)app.get_state() )
  // {
  //   delay_millis_ = millis();
  //   app_state_nr_ = (uint32_t)app.get_state();
  // }
  // if ((app.get_state() == App::Lautstaerke_Minus || app.get_state() == App::Lautstaerke_Plus)
  //       && millis() > delay_millis_ + 1000)
  // {

  // }

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
}

void Anzeige::draw_main_screen()
{
  state_ = Main_Screen;
  Serial.println("(anzeige) draw main screen");
  fillScreen(TFT_BLACK);
  //draw_lautstaerke_balken(5);
  //draw_helligkeits_balken(100);
  setTextFont(4);
  setTextColor(TFT_ORANGE, TFT_BLACK);
  setTextDatum(TC_DATUM);
  drawString(F("Lichteffekt 3/7"), width()/2, 0);
  //fillRoundRect(width()/2-50, 0+27, 2*50, 10, 5, TFT_GREEN);
  // drawString(F("Lied 1/5 - spielt"), width()/2, 48);
  drawString(F("Lautstaerke"), width()/2, 48);
  //fillRoundRect(width()/2-30, 48+27, 2*30, 10, 5, TFT_RED);
  drawString(F("Batterie"), width()/2, 96);
  //fillRoundRect(width()/2-100, 96+27, 2*100, 10, 5, TFT_DARKGREY);
}

void Anzeige::update_main_screen()
{
  if (batterie.get_prozent()/10 != batterie_wert_)
  {
    fillRect(width()/2-(batterie_breite_/2), 96+27, batterie_breite_, 10, TFT_BLACK);
    batterie_wert_ = batterie.get_prozent()/10;
    batterie_breite_ = map(batterie_wert_, 0, 10, 0, width());
    fillRoundRect(width()/2-(batterie_breite_/2), 96+27, batterie_breite_, 10, 5, TFT_DARKGREY);
  }
  if (musik.get_volume() != volume_)
  {
    fillRect(width()/2-(volume_breite_/2), 48+27, volume_breite_, 10, TFT_BLACK);
    volume_ = musik.get_volume();
    volume_breite_ = map(volume_, 0, 30, 0, width());
    fillRoundRect(width()/2-(volume_breite_/2), 48+27, volume_breite_, 10, 5, TFT_RED);
  }
  if ((uint32_t)licht.get_state() != licht_state_nr_)
  {
    licht_state_nr_ = (uint32_t)licht.get_state();
    snprintf(lichteffekt_str_, 30, "   Lichteffekt %u/%u   ", licht_state_nr_, (uint32_t)Licht::Ende);
    drawString(lichteffekt_str_, width()/2, 0);
  }
  if (FastLED.getBrightness() != helligkeit_)
  {
    fillRect(width()/2-(helligkeit_breite_/2), 0+27, helligkeit_breite_, 10, TFT_BLACK);
    helligkeit_ = FastLED.getBrightness();
    helligkeit_breite_ = map(helligkeit_, 0, 255, 0, width());
    fillRoundRect(width()/2-(helligkeit_breite_/2), 0+27, helligkeit_breite_, 10, 5, TFT_DARKGREEN);
  }
}
