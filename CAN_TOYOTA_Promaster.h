#ifndef _CAN_TOYOTA_H_
#define _CAN_TOYOTA_H_
//#include "public.h"
#if CAN_FUN_TOYOTA_PROMASTER==1


#define CAN_RX_BUFFER_LENGTH 							400
#define CAN_TX_BUFFER_LENGTH 							100
/**********************MULTIMEDIA SYSTEM (MMS)***************************/
#define CAN_ID_RX1						0x0025



#define TOYOTA_HEAD_CODE						0x2E
#define CAN_STEER_ANNGLE						0x0A
typedef struct
{
  u8 turn;
	u8 steer_angle[2];
}TOYOTA_CAN_RX_INFO;



typedef struct
{
	u16 head;
	u16 tail;
	CAN_MESSAGE_INFO message[CAN_RX_BUFFER_LENGTH];
}CAN_RX_BUFFER;

typedef struct
{
	u8 head;
	u8 tail;
	u8 length;
	CAN_MESSAGE_INFO message[CAN_TX_BUFFER_LENGTH];
}CAN_TX_BUFFER;
typedef enum
{
	CAN_MAIN_IDLE=0,
	CAN_MAIN_CFG,
	CAN_MAIN_POWER_OFF,
	CAN_MAIN_POWER_ON,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
	CAN_MAIN_GO_TO_SLEEP,
	CAN_MAIN_SLEEP_CFG,
	CAN_MAIN_SLEEP
}CAN_MAIN_STATE;

typedef enum
{
	CAN_POST_MSG_NONE=0,
	CAN_POST_MSG_MAX_INDEX
}CAN_POST_MESSAGE_INDEX;

typedef struct
{
	unsigned f_can_sleep:1;
	unsigned f_can_interrupt:1;
	unsigned f_can_rx_data:1;
	unsigned f_can_init:1;
}_CAN_MAIN_FLAG;

typedef union
{
	_CAN_MAIN_FLAG field;
	u8 byte;
}CAN_MAIN_FLAG;


extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;

extern CAN_MAIN_FLAG     CanMainFlag;

extern TOYOTA_CAN_RX_INFO Toyota_Can_Rx_Info;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init
void CAN_TOYOTA_RxAppDataPro(u8 *buffer);
void CAN_TOYOTA_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);


void CAN_TOYOTA_PostMessage(CAN_POST_MESSAGE_INDEX index);
void CAN_TOYOTA_RxAppDataPro(u8 *buffer);
void CAN_TOYOTA_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
void CAN_TOYOTA_MainPro(void);//1ms ?~{!B~}??????

#endif
#endif



