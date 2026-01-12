#include "public.h"	

u8 F_ADC_Use;
													   
void  Adc_Init(void)
{
    ADC_InitType tempAdcConfig = {0};  //ADC工作模式结构体
    ADC_TrigSourceType tempAdcTrigSource = {0};       //ADC触发源（内部、外部）结构体 ，默认内部触发
    ADC_InitType* ADC_InitStructure;
    ADC_TrigSourceType* ADC_TrigSourceStructure;
    ADC_InitStructure = &tempAdcConfig;
    ADC_TrigSourceStructure = &tempAdcTrigSource;

    ADC_InitStructure->scanMode = 0;
    ADC_InitStructure->continousMode = 0;
    ADC_InitStructure->disContinousModeOnRegularGroup = 0;
    ADC_InitStructure->disContinousModeOnInjectGroup = 0;
    ADC_InitStructure->injectAutoMode = 0;

#if PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
	GPIO_SetFunc(GPIO_PA13, GPIOMUX_FUNC1);//AD_KEY2_ADC_IN6
	GPIO_SetFunc(GPIO_PA14, GPIOMUX_FUNC1);//POWER_H/L_DET_ADC_IN7
	GPIO_SetFunc(GPIO_PA7, GPIOMUX_FUNC1);//ADCH_FUEL_OIL_DET_ADC_IN0
	GPIO_SetFunc(GPIO_PA8, GPIOMUX_FUNC1);//ADCH_TEMPERATURE_DET_ADC_IN1
#else
    GPIO_SetFunc(GPIO_PA6, GPIOMUX_FUNC1);/// SWC-KEY1_ADC_IN10          //AD_KEY1_ADC_IN10
    GPIO_SetFunc(GPIO_PA7, GPIOMUX_FUNC1);//  SWC-KEY2_ADC_IN0              //AD_KEY2_ADC_IN0

#if MODEL==LINUX_Y038_55

#elif MODEL==LINUX_Q028_73M
	GPIO_SetFunc(GPIO_PA9, GPIOMUX_FUNC1);//AD_KEY1_ADC_IN1
	GPIO_SetFunc(GPIO_PA8, GPIOMUX_FUNC1);//POWER_KEY
#else
    GPIO_SetFunc(GPIO_PA8, GPIOMUX_FUNC1);//AD_KEY1_ADC_IN1
#endif
    GPIO_SetFunc(GPIO_PA13, GPIOMUX_FUNC1);//AD_KEY2_ADC_IN6
    GPIO_SetFunc(GPIO_PA14, GPIOMUX_FUNC1);//POWER_H/L_DET_ADC_IN7
    
#if TUNER_TYPE==MULTIPLE_TUNER
	GPIO_SetFunc(GPIO_PB0, GPIOMUX_FUNC1); // TUNER_TYPE_DET_AD ADC_IN9
#endif
#endif

    ADC_Init(ADC, ADC_InitStructure);

    //采样率计算公式：
    //ADC采样率 = ADC模块时钟频率 / 分频值 /（采样时钟数 + 转换时钟数）
    //ADC采样率 = 48M/(ADCx->CTRL2[PSC]+1)/(ADCx->SPTX + 12)    
    ADC_SetClockPrescaler(ADC, 4);                 ///<Set ADC Sample Rate 369K = 96M/2/(4+1)/(14+12)
    ADC_TrigSourceInit(ADC, ADC_TrigSourceStructure);
	ADC_SetRegularGroupLength(ADC, 0); 

    ADC_Cmd(ADC, ENABLE);

}		

//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 channel)   
{
    u32 result=0;
	u32 flag=1;
    F_ADC_Use=1;

    switch (channel)
	{
#if PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
		case ADCH_PANEL_KEY2:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD6);
			ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD6, ADC_SampleTime_14Cycle);
			break;
		case ADCH_BATTERY_VOLT_DET:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD7); 
			ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD7, ADC_SampleTime_14Cycle);
			break;
		case ADCH_FUEL_OIL_DET:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD0); 
			ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD0, ADC_SampleTime_14Cycle);
			break;
		case ADCH_TEMPERATURE_DET:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD1); 
			ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD1, ADC_SampleTime_14Cycle);
			break;
#else
		case ADCH_BATTERY_VOLT_DET:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD7); 
		    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD7, ADC_SampleTime_14Cycle);
			break;
		case ADCH_WHEEL_KEY1:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD10);
		    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD10, ADC_SampleTime_14Cycle);
		    break;
		case ADCH_WHEEL_KEY2:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD0);
		    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD0, ADC_SampleTime_14Cycle);
			break;
#if MODEL==LINUX_Q028_73M
		case ADCH_PANEL_KEY1:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD2);
		    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD2, ADC_SampleTime_14Cycle);
		    break;
		case ADCH_POWER_KEY:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD1);
		    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD1, ADC_SampleTime_14Cycle);
			break;
#else
		case ADCH_PANEL_KEY1:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD1);
		    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD1, ADC_SampleTime_14Cycle);
			break;	
#endif
		case ADCH_PANEL_KEY2:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD6);
		    ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD6, ADC_SampleTime_14Cycle);
			break;	
#if TUNER_TYPE==MULTIPLE_TUNER
		case ADCH_TUNER_TYPE_DET:
			ADC_SetRegularGroupSequence(ADC, 1, ADC_CHANNEL_AD9);
			ADC_ChannelSampleTimeSel(ADC, ADC_CHANNEL_AD9, ADC_SampleTime_14Cycle);
			break;
#endif
#endif
		default:
			flag=0;
			break;
	}
	if(flag)
	{
    ADC_SoftwareStartRegularConvCmd(ADC, ADC_ENABLE);
    while (!ADC_GetIntFlag(ADC, ADC_FLAG_EOC));
    result = ADC_GetRegularConversionValue(ADC);
	}
	F_ADC_Use=0;
	return result;		
}

