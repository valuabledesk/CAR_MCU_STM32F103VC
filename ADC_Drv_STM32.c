#include "public.h"	

u8 F_ADC_Use;
												   
void  Adc_Init(void)
{	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	u32 temp=0;

	//设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	//使能ADC1通道时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOA| RCC_APB2Periph_ADC1,ENABLE);   

#if MODEL==LINUX_Y038_55||MODEL==LINUX_Y039_55
    FormatMemery((u8 *)&GPIO_InitStructure,sizeof(GPIO_InitStructure));						   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOC, &GPIO_InitStructure);
#else
	FormatMemery((u8 *)&GPIO_InitStructure,sizeof(GPIO_InitStructure));						   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOC, &GPIO_InitStructure);

#endif

#if MODEL==LINUX_N039_DZ
	FormatMemery((u8 *)&GPIO_InitStructure,sizeof(GPIO_InitStructure));						   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

    ADC_DeInit(ADC1);  
    ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1; 
	ADC_Init(ADC1, &ADC_InitStructure); 

	ADC_Cmd(ADC1, ENABLE);	
	ADC_ResetCalibration(ADC1); 
	while(ADC_GetResetCalibrationStatus(ADC1)&&temp<0xFFFFFF)
	{
		temp++;
	}
	
	temp=0;
	ADC_StartCalibration(ADC1);  
	while(ADC_GetCalibrationStatus(ADC1)&&temp<0xFFFFFF)
	{
		temp++;
	}
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 	
}		


//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	u16 result=0;
	u32 timeout=0;

	F_ADC_Use=1;
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);		 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )&&(timeout<ADC_TIME_OUT))
	{
		timeout++;
	}
	result=ADC_GetConversionValue(ADC1);
	F_ADC_Use=0;
	return result;	
}

