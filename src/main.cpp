#include <Arduino.h>
#include "licht/licht.h"
#include "musik/musik.h"
#include "anzeige/anzeige.h"
#include "batterie/batterie.h"
#include "app.h"
#include "SimpleButton.h"

Licht licht;
Musik musik;
Batterie batterie;
Anzeige anzeige;
simplebutton::ButtonPullup button_licht;
simplebutton::ButtonPullup button_links;
simplebutton::ButtonPullup button_rechts;
App app;

void setup() {
  Serial.begin(115200);
  Serial.println("(main) laterne-esp startet");
  batterie.begin(34);
  licht.begin();
  musik.begin();
  anzeige.begin();
  button_licht = simplebutton::ButtonPullup(2);
  button_links = simplebutton::ButtonPullup(32);
  button_rechts = simplebutton::ButtonPullup(33);
  app.begin();
  Serial.println("(main) setup fertig");
}

void loop() {
  licht.update();
  musik.update();
  batterie.update();
  anzeige.update();
  button_licht.update();
  button_links.update();
  button_rechts.update();
  app.update();
}