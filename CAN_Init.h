#ifndef _CAN_INIT_H_
#define _CAN_INIT_H_
#if CAN_FUNCTION==1



void CAN1_SetErrorFlag(void);
void CAN1_ClearErrorFlag(void);
u8 CAN1_GetErrorFlag(void);
void CAN1_Init(void);
u8 CAN1_Transmit(void);


void CAN1_TransBytefraem(u32 ID,u8 *data,u8 length);

#endif

#endif


