#ifndef _AIM_915_916_PRO_H_
#define _AIM_915_916_PRO_H_

#if AIM_915_916_FUN==1

typedef enum
{
    AIM_INIT_IDLE,
    AIM_INIT_CONFIG,
    AIM_INIT_RESUME,
    AIM_INIT_FUNC,
    AIM_INIT_EXIT,
    AIM_INIT_NORMAL,
    AIM_INIT_POWER_ON,
    AIM_INIT_ERROR,
    AIM_INIT_SCREEN_ON,
    AIM_INIT_SCREEN_OFF,
    AIM_INIT_START
}AIM_INIT_STATUS;

extern AIM_INIT_STATUS Aim_Init_Status;


u8 AIM_915_ReadReg(u8 reg);
u8 AIM_916_ReadReg(u8 reg);



void AIM_915_916_Init(void);
void AIM_read_test(void);

void AIM_Init_StatusToConfig(u8 mode);
void AIM_Init_Step(void);


#endif
#endif
