#ifndef _CAN_FRONTLANDER_
#define _CAN_FRONTLANDER_
#if CAN_FUN_FRONTLANDER == 1

#define CAN_RX_BUFFER_LENGTH 400
#define CAN_TX_BUFFER_LENGTH 100

#define CAN_ID_2E5 0x2e5
#define CAN_ID_622 0x622
#define CAN_ID_2A1 0x2a1
#define CAN_ID_315 0x315
#define CAN_ID_525 0x525
#define CAN_ID_610 0x610
#define CAN_ID_618 0x618
#define CAN_ID_63B 0x63b

#define CAN_ID_3E0 0x3e0
#define CAN_ID_6F9 0x6f9
#define CAN_ID_260 0x260
#define CAN_ID_250 0x250
#define CNN_ID_270 0x270
#define CAN_ID_280 0x280
#define CAN_ID_5A1 0x5a1

#define FRONTLANDER_RX_BASE_INFO 0x21
#define FRONTLANDER_PANEL_PRESSED 0x22

#define FRONTLANDER_TX_SETTING_CMD 0x80
#define FRONTLANDER_TX_SETTING_2_CMD 0x81

#define FRONTLANDER_TX_REQ_CMD 0x90

#define FRONTLANDER_HEAD_CODE 0x2E

typedef enum
{
	CAN_POST_MSG_NONE=0,
	CAN_POST_MSG_525,
	CAN_POST_MSG_3E0,
	CAN_POST_MSG_6F9,
	// CAN_POST_MSG_315,
	CAN_POST_MSG_250,
	CAN_POST_MSG_260,
	CAN_POST_MSG_270,
	CAN_POST_MSG_280,
	CAN_POST_MSG_5A1,
}CAN_POST_MESSAGE_INDEX;

typedef enum
{
	SETTING_NONE,
	SETTING_FUEL_CONSUMPTION_UNIT,
	SETTING_LANGUAGE,
	SETTING_DOORLOCK_FEEDBACK_LIGHT,
	SETTING_KEY_DOUBLE_UNLOCK,
	SETTING_HRADLAMP_AUTO_ON_SENSITIVITY,
	SETTING_INTER_LIGHT_AUTO_OFF_TIMER,
	SETTING_SMART_REMINDER,
	SETTING_TIME_FORMAT,
} FRONTLANDER_SETTING_INDEX;

typedef enum
{
	CAN_MAIN_IDLE = 0,
	CAN_MAIN_CFG,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
	CAN_MAIN_SLEEP_CFG,
	CAN_MAIN_SLEEP
} CAN_MAIN_STATE;

typedef struct
{
	u16 head;
	u16 tail;
	CAN_MESSAGE_INFO message[CAN_RX_BUFFER_LENGTH];
} CAN_RX_BUFFER;

typedef struct
{
	u8 head;
	u8 tail;
	u8 length;
	CAN_MESSAGE_INFO message[CAN_TX_BUFFER_LENGTH];
} CAN_TX_BUFFER;

typedef struct
{
	unsigned f_can_sleep : 1;
	unsigned f_can_interrupt : 1;
	unsigned f_can_rx_data : 1;
	unsigned f_can_init : 1;
} _CAN_MAIN_FLAG;

typedef struct
{
	u8 speed;
	u16 fuelConsumption;
	u16 remainRange;
	u16 tripDistance;
	u32 tripDuration;
	u16 latestConsumption;
} CAN_BASE_INFO;

typedef struct
{
	CAN_BASE_INFO base_info;
} CAN_RX_INFO;

typedef struct
{
	u8 fuelConsumptionUnit;
} CAN_525_INFO;

typedef struct
{
	u8 byte_2;
	u8 byte_3;
	u8 byte_4;
} CAN_SETTING_INFO_1;

typedef struct
{
	u8 fuelConsumptionUnit;
	u8 language;
	u8 timeFormat12H;
	CAN_SETTING_INFO_1 setting_1;
} CAN_SETTING_INFO;

typedef struct
{
	CAN_525_INFO id525_info;
	CAN_SETTING_INFO setting_info;
} CAN_TX_INFO;

typedef union
{
	_CAN_MAIN_FLAG field;
	u8 byte;
} CAN_MAIN_FLAG;

extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_MAIN_FLAG CanMainFlag;

#define F_CAN_SLEEP CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT CanMainFlag.field.f_can_init


void Frontlander_MainPro(void);
void Frontlander_RxAppDataPro(u8 *buffer);
void Frontlander_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length);

#endif
#endif
