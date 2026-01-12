#ifndef _CAN_LIB_H_
#define _CAN_LIB_H_

#if CAN_FUNCTION==1

typedef enum
{
	CAN_IDE_STD = 0,
	CAN_IDE_EXT
}CAN_IDE_TYPE_DEF;

typedef enum
{
	CAN_RTR_STD = 0,
	CAN_RTR_RMT
}CAN_RTR_TYPE_DEF;

typedef struct
{
	u32 ID;            ///< CAN identifier
	u8 RTR;            ///< Remote transmission request frame
	u8 IDE;            ///< Identifier Extension
	u8 DLC;            ///< Data length code
	u8 Data[8];           ///< Data
} CAN_MESSAGE_INFO;

extern u32 CanErrorTimer;

void CAN1_SetErrorTimer(void);
void CAN1_ClearErrorTimer(void);
void CAN1_TxFrame(u32 ID,u8 *array,u8 length);
void CAN2_TxFrame(u32 ID,u8 *array,u8 length);
void CAN1_Ext_TxFrame(u32 ID,u8 *array,u8 length);
void CAN1_RTR_TxFrame(u32 ID,u8 IDE,u8 RTR , u8 *array,u8 length);
void CAN1_ClearTxMessage(void);
void CAN2_ClearTxMessage(void);
void CAN1_Ext_ClearTxMessage(void);
void CAN1_Ext_ClearBufferTxMessage(void);
void CAN1_RTR_ClearTxMessage(u8 IDE,u8 RTR);
void CAN1_ClearRxMessage(void);
void CAN2_ClearRxMessage(void);
void CAN1_Ext_ClearRxMessage(void);
void CAN1_RTR_ClearRxMessage(u8 IDE,u8 RTR);
#endif
#endif
