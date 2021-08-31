#include "keyes.h"
#include <Arduino.h>

Keyes::Keyes(int _adcPin)
  : adcPin(_adcPin)
{
  for(int i = 0; i < ADC_VALUES_COUNT; ++i)
    adc_values[ i ] = 0;
}

char Keyes::read()
{
    
  // read the input on analog pin 0:
  // int sensorValue = analogRead(0); // - reset :(
  int sensorValue = analogRead(adcPin);
  // print out the value you read:

  adc_total_sum -= adc_values[ adc_idx ];
  adc_total_sum += sensorValue;
  adc_values[ adc_idx ] = sensorValue;
  adc_idx = (adc_idx + 1) % ADC_VALUES_COUNT;

  char btn = '0';
  int adc_avg = adc_total_sum / ADC_VALUES_COUNT;

  if (adc_skip)
    adc_skip--;
  else
  {
    if (abs(adc_avg - sensorValue) > 50)
    {
      adc_skip = ADC_VALUES_COUNT;
    }
    else
    {

// 3V3 stabilizer
#define BTN_LEFT 0
#define BTN_UP 98
#define BTN_DOWN 226
#define BTN_RIGHT 347
#define BTN_START 512

#define BTN_NONE 712

      
      if (abs(adc_avg - BTN_START) < 80)
        btn = 'S';
      else
      {
        if (abs(adc_avg - BTN_RIGHT) < 50)
          btn = 'R';
        else
        {
          if (abs(adc_avg - BTN_LEFT) < 50)
            btn = 'L';
          else
          {
            if (abs(adc_avg - BTN_UP) < 50)
              btn = 'U';
            if (abs(adc_avg - BTN_DOWN) < 50)
              btn = 'D';
          }
        }
      }
    }
  }

 return btn;
}
