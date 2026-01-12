#ifndef _CAN_INIT_STM32_H_
#define _CAN_INIT_STM32_H_

#if CAN_FUNCTION==1

void CAN1_Init(void);
void CAN1_Transmit(void);
void CAN1_Ext_Transmit(void);
void CAN2_Transmit(void);
void CAN1_TransBytefraem(u32 ID,u8 *data,u8 length);
void CAN2_TransBytefraem(u32 ID,u8 *data,u8 length);
void CAN1_SetErrorFlag(void);
void CAN1_ClearErrorFlag(void);
u8 CAN1_GetErrorFlag(void);
void CAN_RxInterruptPro(void);
void CAN2_RxInterruptPro(void);
void BUS_OFF_Recovery_Main(void);
#endif
#endif
