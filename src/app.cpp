#include "app.h"

extern Anzeige anzeige;
extern Licht licht;
extern Musik musik;
extern simplebutton::ButtonPullup button_licht;
extern simplebutton::ButtonPullup button_links;
extern simplebutton::ButtonPullup button_rechts;

App::App()
  : state_(Init)
{
}

void App::begin()
{
  state_ = Init;
}

void App::update()
{
  switch (state_)
  {
    case Init:
    {
      state_ = An;
      break;
    }
    case An:
    {
      if (button_licht.clicked())
        Serial.println("(app) button_licht clicked");
      if (button_licht.released())
        Serial.println("(app) button_licht released");
      if (button_licht.doubleClicked())
        Serial.println("(app) button_licht doubleclicked");
      if (button_licht.holding())
        Serial.println("(app) button_licht holding");
      if (button_links.clicked())
        Serial.println("(app) button_links clicked");
      if (button_links.released())
        Serial.println("(app) button_links released");
      if (button_links.doubleClicked())
        Serial.println("(app) button_links doubleclicked");
      if (button_links.holding())
        Serial.println("(app) button_links holding");
      if (button_rechts.clicked())
        Serial.println("(app) button_rechts clicked");
      if (button_rechts.released())
        Serial.println("(app) button_rechts released");
      if (button_rechts.doubleClicked())
        Serial.println("(app) button_rechts doubleclicked");
      if (button_rechts.holding())
        Serial.println("(app) button_rechts holding");
      break;
    }
  }
}