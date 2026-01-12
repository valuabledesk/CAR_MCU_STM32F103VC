#ifndef _ADC_DRV_STM32_H_
#define _ADC_DRV_STM32_H_

#define ADC_TIME_OUT			0xFFFF

extern u8 F_ADC_Use;

void Adc_Init(void);
u16 Get_Adc(u8 ch);

#endif


