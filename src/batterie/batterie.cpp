#include "batterie.h"

Batterie::Batterie()
  : state_(Inaktiv)
  , last_millis_(0)
  , bat_pin_(-1)
  , update_period_(100)
  , adc_(0)
  , adc_filtered_(0)
  , ticks_(0)
{
}

void Batterie::begin(int32_t bat_pin)
{
  if (bat_pin < 0)
  {
    state_ = Inaktiv;
    return;
  }
  bat_pin_ = bat_pin;
  pinMode(bat_pin_, INPUT);
  pinMode(14, OUTPUT);  // PWR_EN
  digitalWrite(14, HIGH);
  state_ = Messung;
}

void Batterie::update()
{
  switch (state_)
  {
    case Inaktiv:
    {
      break;
    }
    case Messung:
    {
      if (millis() >= last_millis_ + update_period_)
      {
        last_millis_ = millis();
        adc_ = analogRead(bat_pin_);
        if (ticks_ == 0)
          adc_filtered_ = adc_;
        else if (ticks_<20)
          adc_filtered_ = (adc_ + adc_filtered_*(ticks_-1))/ticks_;
        else
          adc_filtered_ = (adc_ + (adc_filtered_*19))/20;
        ticks_++;
      }
      break;
    }
  }
}

uint8_t Batterie::adc_to_prozent(uint32_t adc)
{
  if (adc <= lipo_table[0][0])
    return 0;
  uint8_t i;
  for (i=1; i<12; i++)
  {
    if (adc <= lipo_table[i][0])
      return map(adc, 
          lipo_table[i-1][0], lipo_table[i][0],
          lipo_table[i-1][2], lipo_table[i][2] );
  }
  return 100;
}