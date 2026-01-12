#ifndef _BEEP_PRO_H_
#define _BEEP_PRO_H_

#if MCU_NEED_BEEP_FUN==1
#define BEEP_ACK_TIME				T40MS_10
#define BEEP_WELCOME_TIME			T40MS_10
#define BEEP_FAIL_TIME				T40MS_10

#define BEEP_CYCLE_TIME				124


typedef enum
{
	BEEP_IDLE=0,
	BEEP_ACK_START,
	BEEP_ACK_WAIT,
	
	BEEP_WELCOME_START,//4
	BEEP_WELCOME_STEP1,
	BEEP_WELCOME_STEP2,
	BEEP_WELCOME_STEP3,
	
	BEEP_FAIL_START,//4
	BEEP_FAIL_STEP1,
	BEEP_FAIL_STEP2,
	BEEP_FAIL_STEP3,
	
	BEEP_STOP
}BEEP_STATE;

void Beep_Ack(void);
void Beep_Welcome(void);
void Beep_Fail(void);
void Beep_Pro(void);
u8 IsBeepIdle(void);

#endif

#endif



