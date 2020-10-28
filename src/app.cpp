#include "app.h"

//extern Anzeige anzeige;
extern Licht licht;
extern Musik musik;
extern simplebutton::ButtonPullup button_licht;
extern simplebutton::ButtonPullup button_links;
extern simplebutton::ButtonPullup button_rechts;

App::App()
  : state_(Init)
  , last_millis_(0)
  , brightness_percent(50)
  , increase_brightness(true)
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
      state_ = An;
      if (millis() > last_millis_ + 3000)
      {
        state_ = An;
      }
      break;
    }
    case An:
    {
      // Lichtmodus //
      if (button_licht.clicked())
      {
        Serial.println("(app) button_licht clicked");
        licht.next_effect();
      }
      if (button_licht.holding())
      {
        Serial.println("(app) button_licht holding");
        if (increase_brightness)
        {
          FastLED.setBrightness(FastLED.getBrightness()+25);
        }
        else
          FastLED.setBrightness(FastLED.getBrightness()-25);
      }

      // zurück / leiser //
      if (button_links.holding())
      {
        Serial.println("(app) button_links holding");
        musik.dfplayer.volumeDown();
        Serial.print("(app) volume: ");
        Serial.println(musik.dfplayer.readVolume());
      }
      if (button_links.clicked())
      {
        Serial.println("(app) button_links clicked");
        musik.dfplayer.play();
      }

      // vor / lauter //
      if (button_rechts.holding())
      {
        Serial.println("(app) button_rechts holding");
        musik.dfplayer.volumeUp();
        Serial.print("(app) volume: ");
        Serial.println(musik.dfplayer.readVolume());
      }
      if (button_rechts.clicked())
      {
        Serial.println("(app) button_rechts clicked");
        musik.dfplayer.next();
      }
      break;
    }
  }
}