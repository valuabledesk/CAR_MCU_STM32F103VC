#ifndef _CANBOX_FIAT_SCUDO_Pro_H_
#define _CANBOX_FIAT_SCUDO_Pro_H_
#if CAN_ADAPTER==1
#if CANBOX_FIAT_SCUDO==1

#define FIAT_SCUDO_CAN_HEAD_CODE			0x2E

#define FIAT_SCUDO_MAX_CAN_RX_DATA_LENGTH					80	
#define FIAT_SCUDO_MIN_CAN_RX_DATA_LENGTH					5

#define FIAT_SCUDO_RX_SET_INFO         	0x97
#define FIAT_SCUDO_RX_TIME_INFO			0xC6

#define FIAT_SCUDO_CMD_APP_DATA                 0x01

typedef struct
{
  u8 security_cmd[2];
	u8 accompaniment_lighting[2];
	u8 reception_lighting[2];
	u8 language_cmd[2];
	u8 distance[2];
	u8 temperature[2];
	u8 time[7];
}FIAT_SCUDO_CAN_TX_INFO;

typedef enum
{
	FIAT_SCUDO_IDLE=0,
	FIAT_SCUDO_TX_START_COMMAND,
	FIAT_SCUDO_WORK_NORMAL,
	FIAT_SCUDO_TX_END_COMMAND,
	FIAT_SCUDO_POWER_OFF
}FIAT_SCUDO_WORK_STATE;

void FIAT_SCUDO_RxAppDataPro(u8 *buffer);
void FIAT_SCUDO_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
void CanBox_MainPro_FIAT_SCUDO(void);

#endif
#endif
#endif
