#ifndef _CANBOX_BNR_UPDATE_PRO_H_
#define _CANBOX_BNR_UPDATE_PRO_H_
#if CANBOX_BNR_UPDATE_FUN==1

#define CAN_BNR_UPDATE_START_ADDRESS		0x08002000

#define CAN_BNR_UPDATE_READ					0x11
#define CAN_BNR_UPDATE_RESET					0x21
#define CAN_BNR_UPDATE_WRITE					0x31
#define CAN_BNR_UPDATE_MODE					0xA3
#define CAN_BNR_UPDATE_SYNC					0x7F
#define CAN_BNR_UPDATE_ACK					0x79
#define CAN_BNR_UPDATE_NACK					0x1F

#define CAN_BNR_UPDATE_DATA_LENGTH			128

typedef enum
{
	CAN_UPD_IDLE=0,
	
	CAN_UPD_START,	
	
	CAN_UPD_TX_SYNC_SEQ,
	CAN_UPD_TX_SYNC,
	CAN_UPD_WAIT_SYNC,
	
	
	CAN_UPD_REQ_APP_DATA,
	CAN_UPD_WAIT_APP_DATA,
	
	CAN_UPD_TX_W_CMD,
	CAN_UPD_WAIT_W_CMD_ACK,
	CAN_UPD_TX_W_ADDR,
	CAN_UPD_WAIT_W_ADDR_ACK,
	CAN_UPD_TX_DATA,
	CAN_UPD_WAIT_DATA_ACK,

	CAN_UPD_TX_RESET_CMD,
	CAN_UPD_WAIT_RESTET_CMD_ACK,
	CAN_UPD_TX_RESET_ADDR,
	CAN_UPD_WAIT_RESET_ADDR_ACK,

	CAN_UPD_RESET_WAIT,
	CAN_UPD_RESTART
}CANBOX_UPDATE_STATE;

typedef enum
{
	APP_REQ_ENTER_CAN_UPDATE=1,
	APP_SEND_CAN_UPD_DATA,
	APP_SEND_CAN_UPD_END,
	APP_SEND_CAN_UPD_RESET
}CAN_UPDATE_APP_CMD_INDEX;
typedef struct
{
	unsigned F_req_can_update:1;
	unsigned F_can_update_result:1;
	unsigned F_can_update_reset:1;
}_CAN_UPDATE_FLAG;

typedef union
{
	_CAN_UPDATE_FLAG field;
	u8 byte;
}CAN_UPDATE_FLAG;

typedef struct
{
	unsigned f_rx_data:1;
	unsigned f_rx_finish_dada:1;
	unsigned f_rx_reset_req:1;
}_CAN_UPD_RX_APP_FLAG;

typedef union
{
	_CAN_UPD_RX_APP_FLAG field;
	u8 byte;
}CAN_UPD_RX_APP_FLAG;

typedef struct
{
	unsigned f_rx_ack:1;
	unsigned f_rx_nack:1;
}_CAN_UPD_RX_CAN_FLAG;

typedef union
{
	_CAN_UPD_RX_CAN_FLAG field;
	u8 byte;
}CAN_UPD_RX_CAN_FLAG;

extern CAN_UPD_RX_APP_FLAG CanUpdRxAppFlag;
#define CAN_UPD_RX_APP_DATA						CanUpdRxAppFlag.field.f_rx_data
#define CAN_UPD_RX_APP_FINISH_DATA				CanUpdRxAppFlag.field.f_rx_finish_dada
#define CAN_UPD_RX_APP_RESET_REQ					CanUpdRxAppFlag.field.f_rx_reset_req


extern CAN_UPD_RX_CAN_FLAG CanUpdRxCanFlag;
#define CAN_UPD_RX_CAN_ACK						CanUpdRxCanFlag.field.f_rx_ack
#define CAN_UPD_RX_CAN_NACK						CanUpdRxCanFlag.field.f_rx_nack

u8 IsReqCanUpdate(void);
void CanUpdateStart(void);
void CanUpdate_AppDataService(u8 *rx_buff);
void CanBoxUpdatePro(void);
#endif
#endif


