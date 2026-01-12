#ifndef _AHD_360_PRO_H_
#define _AHD_360_PRO_H_

#if AHD_360_FUN==1

#define AHD_360_HEAD_CODE			0x2E

#define AHD_360_MAX_RX_DATA_LENGTH				80	
#define AHD_360_MIN_RX_DATA_LENGTH				5	

#define MAX_AHD_360_RX_BUFFER_LENGTH			500
#define MAX_AHD_360_TX_BUFFER_LENGTH			160

#define AHD_360_RESEND_TIMES						3

#define AHD_360_VERSION_LENGTH					0x17

#define AHD_360_RX_INIT_INFO						0x10
#define AHD_360_RX_VERSION_INFO					0x20
#define AHD_360_RX_STATE_INFO						0x21
#define AHD_360_RX_MENU_INFO						0x22

#define AHD_360_TX_LINK_CMD						0x80
#define AHD_360_TX_REQUEST_CMD					0x81
#define AHD_360_TX_VIEW_SET_CMD					0x82
#define AHD_360_TX_MENU_SET_CMD					0x83
#define AHD_360_TX_TOUCH_CMD						0x84
#define AHD_360_TX_REVERSE_STATE					0x85
#define AHD_360_TX_LIGHT_STATE					0x86
#define AHD_360_TX_TOUCH_PRESS_CMD				0x90
#define AHD_360_TX_TOUCH_RELEASE_CMD			0x91

#define AHD_360_RX_ACK								0xFF
#define AHD_360_RX_NACK_ERR_CHECKSUM			0xF0
#define AHD_360_RX_NACK_NO_SUPPORT				0xF3
#define AHD_360_RX_NACK_BUSY						0xFC

#define AHD_360_CMD_APP_DATA						0x01

typedef enum
{
	AHD_360_IDLE=0,
	AHD_360_TX_START_COMMAND,
	AHD_360_WAIT_START_ACK,
	AHD_360_WORK_NORMAL,
	AHD_360_TX_END_COMMAND,
	AHD_360_WAIT_END_ACK,
	AHD_360_POWER_OFF
}AHD_360_WORK_STATE;

typedef enum
{
	AHD_360_EVENT_NONE=0,
	AHD_360_EVENT_POWER_ON,
	AHD_360_EVENT_POWER_OFF,
	AHD_360_EVENT_ACC_OFF,
	AHD_360_EVENT_EMERGENCY_OFF,
	AHD_360_EVENT_RX_APP_DATA,
	AHD_360_EVENT_ALL
}AHD_360_EVENT;

typedef struct
{
	u8 init_info;
	u8 version_info[AHD_360_VERSION_LENGTH];
	u8 view_state;
	u8 menu_state;	
}AHD_360_RX_INFO;

typedef struct
{
	u8 request_info;
	u8 view_set_cmd;
	u8 menu_set_cmd;
	u8 touch_press_cmd[3];
	u8 touch_release_cmd[3];
	u8 reverse_state;
	u8 light_state;
}AHD_360_TX_INFO;

typedef struct
{
	unsigned f_tx_buffer_full:1;
	unsigned f_tx_ack_check:1;
	unsigned reserve:6;
}_AHD_360_FLAG;

typedef union
{
	_AHD_360_FLAG field;
	u8 byte;
}AHD_360_FLAG;

typedef struct
{
	u16 head;
	u16 tail;
	u8 data[MAX_AHD_360_RX_BUFFER_LENGTH];
}AHD_360_RX_BUFFER;

extern AHD_360_RX_BUFFER AHD_360_RxBuffer;

extern AHD_360_FLAG AHD_360_Flag;
#define F_AHD_360_TX_BUFFER_FULL			AHD_360_Flag.field.f_tx_buffer_full
#define F_AHD_360_TX_ACK_CHECK			AHD_360_Flag.field.f_tx_ack_check

void AHD_360_MainPro(void);
void AHD_360_RxAppDataPro(u8 *buffer);
void AHD_360_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);

#endif
#endif

