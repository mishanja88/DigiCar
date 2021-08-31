#ifndef KEYES_H
#define KEYES_H

class Keyes
{
  public:
    explicit Keyes(int adcPin);

    char read();
    
  protected:
    int adcPin;
  
    int adc_count = 0;
    int adc_total_sum = 0;
    int adc_idx = 0;

    static const int ADC_VALUES_COUNT = 4;
    int adc_values[ ADC_VALUES_COUNT ] = { 0 };

    int adc_skip = ADC_VALUES_COUNT;
};

#endif // KEYES_H
