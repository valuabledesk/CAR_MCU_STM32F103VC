#include "public.h"
#if MCU_NEED_BEEP_FUN==1

BEEP_STATE BeepState;
u8 BeepTimer;
void BeepStart(void)
{
#if defined(AUTOCHIPS_AC781X)
	PWM_SetChannelValue(PWM3, PWM_CHANNEL_CHANNEL0, 250);
#elif defined(HDSC_HC32F460)
	TIMERA_SetCompareValue(M4_TMRA2,TimeraCh6,((BEEP_PWM_CNT_FREQ/BEEP_PWM_FREQ)/2));
#elif defined(HDSC_HC32L072)
	Adt_SetCompareValue(M0P_ADTIM5,AdtCompareB,((BEEP_PWM_CNT_FREQ/BEEP_PWM_FREQ)/2));
#elif defined(STM32_F103VC)||defined(STM32F401xx)
    u16 temp;
    temp=TIM_GetCounter(TIM1);
    temp+=50;
    TIM_SetCompare2(TIM1,temp);
    TIM_ClearFlag(TIM1,TIM_FLAG_CC2);
    TIM_ITConfig(TIM1,TIM_IT_CC2,ENABLE);
#endif
#if BEEP_DEBUG_FUN==1
	printf("Beep Start\r\n");
#endif
}

void BeepStop(void)
{	
#if defined(AUTOCHIPS_AC781X)
    PWM_SetChannelValue(PWM3, PWM_CHANNEL_CHANNEL0, 0);
#elif defined(HDSC_HC32F460)
	TIMERA_SetCompareValue(M4_TMRA2,TimeraCh6,(BEEP_PWM_CNT_FREQ/BEEP_PWM_FREQ));
#elif defined(HDSC_HC32L072)
	Adt_SetCompareValue(M0P_ADTIM5,AdtCompareB,(BEEP_PWM_CNT_FREQ/BEEP_PWM_FREQ));
#elif defined(STM32_F103VC)||defined(STM32F401xx)
    TIM_ITConfig(TIM1,TIM_IT_CC2,DISABLE);
#endif
#if BEEP_DEBUG_FUN==1
	printf("Beep Stop\r\n");
#endif

}

void Beep_Ack(void)
{
	BeepState=BEEP_ACK_START;
#if BEEP_DEBUG_FUN==1
	printf("Beep Ack\r\n");
#endif
}

void Beep_Welcome(void)
{
	BeepState=BEEP_WELCOME_START;
#if BEEP_DEBUG_FUN==1
	printf("Beep Welcome\r\n");
#endif
}

void Beep_Fail(void)
{
	BeepState=BEEP_FAIL_START;
#if BEEP_DEBUG_FUN==1
	printf("Beep Fail\r\n");
#endif
}

u8 IsBeepIdle(void)
{
	u8 result=1;
	if(BeepState!=BEEP_IDLE)
	{
		result=0;
	}
	return result;
}
void Beep_Pro(void)
{
	if(Main_Power()==0||F_BEEP_Open==0)	
	{
		if(BeepState!=BEEP_IDLE)
		{
			BeepState=BEEP_IDLE;
			BeepStop();
		}
		return;
	}
	if(BeepTimer)
	{
		BeepTimer--;
	}
	switch(BeepState)
	{
		case BEEP_IDLE:
			break;
			
		case BEEP_ACK_START:
			BeepStart();
			BeepState=BEEP_ACK_WAIT;
			BeepTimer=BEEP_ACK_TIME;
#if BEEP_DEBUG_FUN==1
			printf("BEEP_ACK_START\r\n");
#endif
			break;
		case BEEP_ACK_WAIT:
			if(0==BeepTimer)
			{
				BeepState=BEEP_STOP;
#if BEEP_DEBUG_FUN==1
				printf("BEEP_ACK_WAIT\r\n");
#endif
			}
			break;
#if 0
		case BEEP_WELCOME_START:
			BeepStart();
			BeepState=BEEP_WELCOME_STEP1;
			BeepTimer=BEEP_WELCOME_TIME;			
#if BEEP_DEBUG_FUN==1
			printf("BEEP_WELCOME_START\r\n");
#endif
			break;
		case BEEP_WELCOME_STEP1:
			if(0==BeepTimer)
			{
				BeepStop();
				BeepState=BEEP_WELCOME_STEP2;
				BeepTimer=BEEP_WELCOME_TIME;
#if BEEP_DEBUG_FUN==1
				printf("BEEP_WELCOME_STEP1\r\n");
#endif
			}			
			break;
		case BEEP_WELCOME_STEP2:
			if(0==BeepTimer)
			{
				BeepStart();
				BeepState=BEEP_WELCOME_STEP3;
				BeepTimer=BEEP_WELCOME_TIME;
#if BEEP_DEBUG_FUN==1
				printf("BEEP_WELCOME_STEP2\r\n");
#endif
			}
			break;
		case BEEP_WELCOME_STEP3:
			if(0==BeepTimer)
			{
				BeepState=BEEP_STOP;
#if BEEP_DEBUG_FUN==1
				printf("BEEP_WELCOME_STEP3\r\n");
#endif
			}
			break;
#endif
		case BEEP_FAIL_START:
			BeepStart();
			BeepState=BEEP_FAIL_STEP1;
			BeepTimer=BEEP_FAIL_TIME;	
#if BEEP_DEBUG_FUN==1
			printf("BEEP_FAIL_START\r\n");
#endif
			break;
		case BEEP_FAIL_STEP1:
			if(0==BeepTimer)
			{
				BeepStop();
				BeepState=BEEP_FAIL_STEP2;
				BeepTimer=BEEP_FAIL_TIME;
#if BEEP_DEBUG_FUN==1
				printf("BEEP_FAIL_STEP1\r\n");
#endif
			}
			break;
		case BEEP_FAIL_STEP2:
			if(0==BeepTimer)
			{
				BeepStart();
				BeepState=BEEP_FAIL_STEP3;
				BeepTimer=BEEP_FAIL_TIME;
#if BEEP_DEBUG_FUN==1
				printf("BEEP_FAIL_STEP2\r\n");
#endif
			}			
			break;
		case BEEP_FAIL_STEP3:
			if(0==BeepTimer)
			{
				BeepState=BEEP_STOP;
#if BEEP_DEBUG_FUN==1
				printf("BEEP_FAIL_STEP3\r\n");
#endif
			}
			break;

		case BEEP_STOP:
			BeepStop();
			BeepState=BEEP_IDLE;
#if BEEP_DEBUG_FUN==1
			printf("BEEP_STOP\r\n");
#endif
			break;
		default:
			break;
	}
}
#endif






