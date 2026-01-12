#ifndef _CAN_TC250_
#define _CAN_TC250_
#if CAN_FUN_TC250 == 1

#define CAN_RX_BUFFER_LENGTH 400
#define CAN_TX_BUFFER_LENGTH 100

#define CAN_ID_CCM 0x18FF312C
#define CAN_ID_INFO2 0x18FFDD1B
#define CAN_ID_DATE 0x18FF891B
#define CAN_ID_ET1 0x18FEEE13
#define CAN_ID_VEHICLE_INFO 0x18FF7A1B

#define CAN_ID_HVAC 0x18FEEE28
#define CAN_ID_SSC 0x18FDD028
#define CAN_ID_DATE_REQ 0x18EA1B28
#define CAN_ID_VEHICLE_INFO_REQ 0x18EA1B28

#define TC250_RX_CCM_INFO 0x21
#define TC250_PANEL_PRESSED 0x22
#define TC250_DIAGNOSTIC 0x23
#define TC250_RX_TIME_INFO 0x24
#define TC250_BEEP 0x25

#define TC250_TX_HVAC_CMD 0x8A
#define TC250_TX_REQ_CMD 0x90

#define TC250_HEAD_CODE 0x2E

typedef enum
{
	CAN_POST_MSG_NONE = 0,
	CAN_POST_MSG_HVAC,
	CAN_POST_MSG_SSC,
	CAN_POST_MSG_DATE_REQ,
	CAN_POST_MSG_VEHICLE_INFO_REQ,
} CAN_POST_MESSAGE_INDEX;

typedef enum
{
	HVAC_NONE,
	HVAC_TEMPERATURE,
	HVAC_FAN_SPEED,
	HVAC_AIR_DISTRIBUTION,
	HVAC_AC,
	HVAC_ON_OFF,
} TC250_HVAC_INDEX;

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

// #if NEW_TC250 == 1
// typedef struct
// {
// 	unsigned ac : 1;
// 	unsigned fanSpeed : 3;
// 	unsigned airDistribution : 2;
// 	unsigned reserved : 2;
// } _CAN_CCM_INFO_BYTE_0;

// typedef union
// {
// 	_CAN_CCM_INFO_BYTE_0 field;
// 	u8 byte;
// } CAN_CCM_INFO_BYTE_0;

// typedef struct
// {
// 	CAN_CCM_INFO_BYTE_0 byte_0;
// 	u8 fanSpeed;
// 	u8 airDistribution;
// 	u8 settingTemperature;

// 	u8 indoorTemperature;
// 	u8 outdoorTemperatureL;
// 	u8 outdoorTemperatureH;
// } CAN_CCM_INFO;
// #else
typedef struct
{
	u8 ac;
	u8 fanSpeed;
	u8 airDistribution;
	u8 settingTemperature;
	u8 HVACOn;
	
	u8 indoorTemperature;
	u8 outdoorTemperatureL;
	u8 outdoorTemperatureH;
} CAN_CCM_INFO;
// #endif

typedef struct
{
	u8 second;
	u8 minute;
	u8 hour;
} CAN_TIME;

typedef struct
{
	u8 region;
	u8 data[21];
	u8 length;	
} VEHICLE_INFO;

typedef struct
{
	CAN_CCM_INFO ccm_info;
	CAN_TIME time_info;
	VEHICLE_INFO vehicel_info;
} CAN_RX_INFO;

typedef struct
{
	unsigned fanSpeed : 3;
	unsigned airDistribution : 2;
	unsigned ac : 1;
	unsigned HVACControlCommand : 1;
	unsigned HVACOn : 1;
} _CAN_HVAC_INFO_BYTE_1;

typedef union
{
	_CAN_HVAC_INFO_BYTE_1 field;
	u8 byte;
} CAN_HVAC_INFO_BYTE_1;

typedef struct
{
	u8 temperature;
	CAN_HVAC_INFO_BYTE_1 byte_1;
	// u8 fanSpeed;
	// u8 airDistribution;
	// u8 ac;
	// u8 HVACControlCommand;
} CAN_HVAC_INFO;

// typedef struct
// {
// 	u8 acc_ign;
// 	u8 dimming;
// } CAN_SSC_INFO;

typedef struct
{
	CAN_HVAC_INFO hvac_info;
	// CAN_SSC_INFO ssc_info;
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

void TC250_MainPro(void);
void TC250_RxAppDataPro(u8 *buffer);
void TC250_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length);
void TC250_Panel_HVAC_Ctrl(u8 cmd, u8 keyvalue);

#endif
#endif
