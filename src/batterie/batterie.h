#ifndef BATTERIE_H
#define BATTERIE_H

#include <Arduino.h>

class Batterie
{
public:
  enum State
  {
    Inaktiv,
    Messung
  };

private:
  enum State state_;
  uint32_t last_millis_;
  int32_t bat_pin_;
  uint32_t update_period_;
  int32_t adc_;
  int32_t adc_filtered_;
  uint32_t ticks_;

public:
  Batterie();
  void begin(int32_t bat_pin = -1);
  void update();
  enum State get_state() const { return state_; };
  uint32_t get_ticks() const { return ticks_; };
  uint32_t get_adc() const { return adc_; };
  uint32_t get_adc_filtered() const { return adc_filtered_; };
  uint8_t get_prozent() { return adc_to_prozent(adc_filtered_); };

private:
  uint8_t adc_to_prozent(uint32_t adc);
  uint32_t lipo_table[12][3] {
    { 1975, 3483, 1 },
    { 2100, 3676, 5 },
    { 2160, 3777, 10 },
    { 2207, 3854, 20 },
    { 2237, 3902, 30 },
    { 2256, 3937, 40 },
    { 2295, 4001, 50 },
    { 2322, 4045, 60 },
    { 2336, 4067, 70 },
    { 2352, 4091, 80 },
    { 2380, 4137, 90 },
    { 2414, 4192, 100 } 
  };

};

#endif /* BATTERIE_H */
