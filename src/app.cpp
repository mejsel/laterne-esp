#include "app.h"

//extern Anzeige anzeige;
extern Licht licht;
extern Musik musik;
extern simplebutton::ButtonPullup button_licht;
extern simplebutton::ButtonPullup button_links;
extern simplebutton::ButtonPullup button_rechts;
extern Anzeige anzeige;

App::App()
  : state_(Init)
  , last_millis_(0)
  , helligkeit_zuletzt_erhoeht(true)
{
}

void App::begin()
{
  last_millis_ = millis();
  state_ = Init;
}

void App::update()
{
  switch (state_)
  {
    case Init:
    {
      if (millis() > last_millis_ + 3000)
      {
        button_licht.reset();
        button_links.reset();
        button_rechts.reset();
        anzeige.draw_main_screen();
        state_ = Normalbetrieb;
      }
      break;
    }
    case Normalbetrieb:
    {
      // Lichtmodus //
      if (button_licht.clicked())
      {
        Serial.println("(app) button_licht clicked");
        licht.next_effect();
      }
      else if (button_licht.holding())
      {
        Serial.println("(app) button_licht holding");
        last_millis_ = millis();
        if (helligkeit_zuletzt_erhoeht)
          state_ = Helligkeit_Minus;
        else
          state_ = Helligkeit_Plus;
        //anzeige.draw_helligkeit_screen();
      }

      // zurück / leiser //
      if (button_links.holding())
      {
        Serial.println("(app) button_links holding");
        if (gestartet)
        {
          musik.dfplayer.pause();
          gestartet = false;
        }
        else
        {
          musik.dfplayer.start();
          gestartet = true;
        }
      }
      else if (button_links.clicked())
      {
        Serial.println("(app) button_links clicked");
        musik.dfplayer.previous();
      }

      // vor / lauter //
      if (button_rechts.holding())
      {
        Serial.println("(app) button_rechts holding");
        last_millis_ = millis();
        if (lautstaerke_zuletzt_erhoeht)
          state_ = Lautstaerke_Minus;
        else
          state_ = Lautstaerke_Plus;
        //anzeige.draw_lautstaerke_screen();
      }
      else if (button_rechts.clicked())
      {
        Serial.println("(app) button_rechts clicked");
        musik.dfplayer.next();
      }
      break;
    }
    case Lautstaerke_Plus:
    {
      if (button_rechts.released())
      {
        button_licht.reset();
        button_links.reset();
        button_rechts.reset();
        lautstaerke_zuletzt_erhoeht = true;
        //anzeige.draw_main_screen();
        state_ = Normalbetrieb;
      }
      else if (millis() > last_millis_ + 100)
      {
        last_millis_ = millis();
        musik.inc_volume();
        //musik.dfplayer.volumeUp();
        Serial.println("(app) volume up");
      }
      break;
    }
    case Lautstaerke_Minus:
    {
      if (button_rechts.released())
      {
        button_licht.reset();
        button_links.reset();
        button_rechts.reset();
        lautstaerke_zuletzt_erhoeht = false;
        //anzeige.draw_main_screen();
        state_ = Normalbetrieb;
      }
      else if (millis() > last_millis_ + 100)
      {
        last_millis_ = millis();
        musik.dec_volume();
        //musik.dfplayer.volumeDown();
        Serial.println("(app) volume down");
      }
      break;
    }
    case Helligkeit_Plus:
    {
      if (button_licht.released())
      {
        button_licht.reset();
        button_links.reset();
        button_rechts.reset();
        helligkeit_zuletzt_erhoeht = true;
        //anzeige.draw_main_screen();
        state_ = Normalbetrieb;
      }
      else if (millis() > last_millis_ + 20)
      {
        last_millis_ = millis();
        if (FastLED.getBrightness() < 255)
        {
          FastLED.setBrightness(FastLED.getBrightness()+1);
          FastLED.show();
        }
      }
      break;
    }
    case Helligkeit_Minus:
    {
      if (button_licht.released())
      {
        button_licht.reset();
        button_links.reset();
        button_rechts.reset();
        helligkeit_zuletzt_erhoeht = false;
        //anzeige.draw_main_screen();
        state_ = Normalbetrieb;
      }
      else if (millis() > last_millis_ + 20)
      {
        last_millis_ = millis();
        if (FastLED.getBrightness() != 0)
        {
          FastLED.setBrightness(FastLED.getBrightness()-1);
          FastLED.show();
        }
      }
      break;
    }
  }
}