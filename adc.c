#include "sensors_header.h"
 unsigned int temp_read(unsigned int ch_num)
 {

     unsigned int adc_value=adc_read(ch_num);
     unsigned int voltage_mv = (adc_value * 3300.0) / 1023.0;
     unsigned int temp_c = (voltage_mv / 10.0);
     return temp_c;                                                
 } 
 unsigned int potentiometer_read(unsigned int CH_POT)
 {
     unsigned int adc_value;
         unsigned int Vout;
          adc_value=adc_read(CH_POT);
          Vout=(adc_value*3300)/1023; // volatge conversions from potentiometer value 
	 return Vout;
 
 }

  unsigned int ldr_read(unsigned int CH_LDR)
  {
      unsigned int adc_value;
          unsigned int Vout;
          adc_value=adc_read(CH_LDR);
          Vout=(adc_value*3300)/1023;
		return Vout;
         //int ch_ldr=CH_LDR;
     //return adc_read(ch_ldr);
  }
 
 #define DONE ((ADDR >> 31) & 1)
 void adc_init(void)
 {
     PINSEL1 = 0x15400000;
     ADCR   = 0x00200400;
  }
  unsigned int adc_read(unsigned int ch_num)
  {
     unsigned int result = 0;
     ADCR |= (1 << ch_num);
    ADCR |= (1 << 24);
    while (DONE == 0);
     ADCR ^= (1 << 24);
     ADCR ^= (1 << ch_num);
     result = (ADDR >> 6) & 0x3FF;
     return result;
 }
