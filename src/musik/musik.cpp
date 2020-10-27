#include "musik.h"

Musik::Musik()
  : state_(Aus)
  , last_millis_(0)
  , volume_(1)
{
}

void Musik::begin()
{
  Serial1.begin(9600, SERIAL_8N1, 13, 15);
  if (!dfplayer.begin(Serial1)) {
    Serial.println("(musik) Fehler beim Initialisieren von mp3player");
    last_millis_ = millis();
    //state_ = Fehler;
    //return;
  }
  Serial.println("mp3player initialisiert");
  //dfplayer.volume(volume_);
  //dfplayer.stop();
  //dfplayer.enableLoopAll();
  //mp3player.play(1);
  state_ = Bereit;
}

void Musik::update()
{
  switch (state_)
  {
    case Aus:
    {
      break;
    }
    case Fehler:
    {
      if (millis() > last_millis_ + 1000)
      {
        Serial1.println("(musik) serial1 output");
        last_millis_ = millis();
      }

        //begin();
      break;
    }
    case Bereit:
    {
      if (dfplayer.available())
        print_detail(dfplayer.readType(), dfplayer.read());
      break;
    }
  }
}

void Musik::print_detail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}