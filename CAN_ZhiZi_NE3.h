#ifndef _CAN_ZhiZi_NE3_H_
#define _CAN_ZhiZi_NE3_H_
#if CAN_FUN_ZHIZI_NE3==1

#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		100

#define CAN_REPEAT_KEY_TIME					80
#define CAN_LONG_KEY_TIME						1400	

/*************** Receive ID********************/
#define CAN_ID_CGW_VEHINFO1			0x18FF0325
#define CAN_ID_EVT_TD						0x18FEE6EB
#define CAN_ID_BPDU_OUTCTRLST		0x18FDCD21
#define CAN_ID_BPDU_VEHPWRSTS		0x18FFDA21
#define CAN_ID_BPDU_MFLCTRL			0x18FFDB21
#define CAN_ID_CGW_ADAS_INFO		0x18FFEA25
#define CAN_ID_AVM_REQ					0x18FF81EF
/*************** Transmit ID********************/
#define CAN_ID_IVI_STATUS				0x1CFFFBE2
#define CAN_ID_IVI_POS					0x1CFF5BE2
#define CAN_ID_DSW							0x18FFACE2
#define CAN_ID_DM1							0x18FECAE2
#define CAN_ID_IVI_BAM					0x18ECFFE2
#define CAN_ID_IVI_IP_DT				0x18EBFFE2
#define CAN_ID_IVI_SOFT					0x18FEDAE2
#define CAN_ID_IVI_HARD					0x18FF00E2
#define CAN_ID_IVI_SOFTPARTNUM			0x18FFFDE2
#define CAN_ID_IVI_TIMESET				0x18FF01E2
/***************APP Cmd***********************/
#define ZHIZI_NE3_TX_IVI_ST						0x20
#define ZHIZI_NE3_TX_IVI_POS					0x21
#define ZHIZI_NE3_TX_SETTING					0x22
#define ZHIZI_NE3_TX_SOFT_VER					0x23
#define ZHIZI_NE3_TX_HARD_VER					0x24
#define ZHIZI_NE3_TX_HIDE_SETTING				0x25
#define ZHIZI_NE3_TX_SOFT_PART_NUM_VER			0x26
#define ZHIZI_NE3_TX_IVI_TIME_SET				0x27

#define ZHIZI_NE3_RX_BASE_INFO					0x20
#define ZHIZI_NE3_RX_TIME_INFO					0x21
#define ZHIZI_NE3_RX_SETTING_CMD				0x22
#define ZHIZI_NE3_RX_AVM_REQ					0x23
#define ZHIZI_NE3_RX_STEER_CMD				0x24

#define ZhiZi_NE3_HEAD_CODE						0x2E

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
	CAN_POST_MSG_IVI_ST,
	CAN_POST_MSG_IVI_POS,
	CAN_POST_MSG_IVI_DSW,
	CAN_POST_MSG_IVI_DM1,
	CAN_POST_MSG_IVI_BAM,
	CAN_POST_MSG_IVI_TP_DT,
	CAN_POST_MSG_IVI_SOFT,
	CAN_POST_MSG_IVI_HARD,
	CAN_POST_MSG_IVI_SoftPartNum,
	CAN_POST_MSG_IVI_TimeSet,
	CAN_POST_MSG_MAX_INDEX
}CAN_POST_MESSAGE_INDEX;

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

typedef struct
{
	u16 vehicle_speed;
}CAN_BASE_INFO;

typedef struct
{
	unsigned f_aeb_st:4;
	unsigned f_ldw_st:4;
}_CAN_VEH_SETTING_INFO_BYTE_0;

typedef union
{
	_CAN_VEH_SETTING_INFO_BYTE_0 field;
	u8 byte;
}CAN_VEH_SETTING_INFO_BYTE_0;

typedef struct
{
	unsigned f_position_light_st:2;
	unsigned f_low_beam_st:2;
	unsigned f_Ignition_gear_position:3;
	unsigned reserved:1;
}_CAN_VEH_SETTING_INFO_BYTE_1;

typedef union
{
	_CAN_VEH_SETTING_INFO_BYTE_1 field;
	u8 byte;
}CAN_VEH_SETTING_INFO_BYTE_1;

typedef struct
{
	CAN_VEH_SETTING_INFO_BYTE_0 byte_0;
	CAN_VEH_SETTING_INFO_BYTE_1 byte_1;
	u8 vehicle_gears;
}CAN_VEH_SETTING_INFO;

typedef struct
{
	u8 second;
	u8 minutes;
	u8 hours;
	u8 day;
	u8 month;
	u8 year;
	u8 minute_offset;
	u8 hour_offset;
	u8 time_updata;
}CAN_TIME_INFO;

typedef struct
{
	CAN_BASE_INFO base_info;
	CAN_VEH_SETTING_INFO veh_setting_info;
	CAN_TIME_INFO time_info;
	u8 avm_request;
}CAN_RX_INFO;

typedef struct
{
	unsigned f_display_mode:4;
	unsigned f_display_ready:4;
}_CAN_SCREEN_INFO_BYTE_0;

typedef union
{
	_CAN_SCREEN_INFO_BYTE_0 field;
	u8 byte;
}CAN_SCREEN_INFO_BYTE_0;

typedef struct
{
	unsigned f_avm_req:2;
	unsigned f_reserved:6;
}_CAN_SCREEN_INFO_BYTE_1;

typedef union
{
	_CAN_SCREEN_INFO_BYTE_1 field;
	u8 byte;
}CAN_SCREEN_INFO_BYTE_1;

typedef struct
{
	CAN_SCREEN_INFO_BYTE_0 byte_0;
	CAN_SCREEN_INFO_BYTE_1 byte_1;
}CAN_SCREEN_INFO;

typedef struct
{
	unsigned f_touch_st:2;
	unsigned f_reserved:6;
}_CAN_IVI_ST_BYTE_4;

typedef union
{
	_CAN_IVI_ST_BYTE_4 field;
	u8 byte;
}CAN_IVI_ST_BYTE_4;

typedef struct
{
	u16 x_position;
	u16 y_position;
	CAN_IVI_ST_BYTE_4 byte_4;
}CAN_IVI_ST;

typedef struct
{
	unsigned f_aeb_fun:2;
	unsigned f_reserved:6;
}_CAN_SETTING_CMD_BYTE_0;

typedef union
{
	_CAN_SETTING_CMD_BYTE_0 field;
	u8 byte;
}CAN_SETTING_CMD_BYTE_0;

typedef struct
{
	unsigned f_reserved_01:2;
	unsigned f_ldw_fun:2;
	unsigned f_bsd_sw:4;
}_CAN_SETTING_CMD_BYTE_1;

typedef union
{
	_CAN_SETTING_CMD_BYTE_1 field;
	u8 byte;
}CAN_SETTING_CMD_BYTE_1;

typedef struct
{
	CAN_SETTING_CMD_BYTE_0 byte_0;
	CAN_SETTING_CMD_BYTE_1 byte_1;
}CAN_SETTING_CMD;

typedef struct
{
	u8 soft_ver_byte0;
	u8 soft_ver_byte1;
	u8 soft_ver_byte2;
	u8 soft_ver_byte3;
	u8 soft_ver_byte4;
	u8 soft_ver_byte5;
	u8 soft_ver_byte6;
	u8 soft_ver_byte7;
}CAN_SOFT_VERSION;

typedef struct
{
	u8 hard_ver_byte0;
	u8 hard_ver_byte1;
	u8 hard_ver_byte2;
	u8 hard_ver_byte3;
	u8 hard_ver_byte4;
	u8 hard_ver_byte5;
	u8 hard_ver_byte6;
	u8 hard_ver_byte7;
}CAN_HARD_VERSION;

typedef struct
{
	u8 softpartnum_ver_byte0;
	u8 softpartnum_ver_byte1;
	u8 softpartnum_ver_byte2;
	u8 softpartnum_ver_byte3;
	u8 softpartnum_ver_byte4;
	u8 softpartnum_ver_byte5;
	u8 softpartnum_ver_byte6;
	u8 softpartnum_ver_byte7;
}CAN_SOFT_PART_NUM_VERSION;

typedef struct
{
	u8 time_set_byte0;
	u8 time_set_byte1;
	u8 time_set_byte2;
	u8 time_set_byte3;
	u8 time_set_byte4;
	u8 time_set_byte5;
	u8 time_set_byte6;
}CAN_TIME_SET;


typedef struct
{
	CAN_SCREEN_INFO screen_info;
	CAN_IVI_ST ivi_st;
	CAN_SETTING_CMD setting_cmd;
	CAN_SOFT_VERSION soft_version;
	CAN_HARD_VERSION	hard_version;
	CAN_SOFT_PART_NUM_VERSION softpartnum_version;
	CAN_TIME_SET time_set;
}CAN_TX_INFO;

typedef struct
{
	u8 CanKeyCode;
	u8 LongKeyCode;
	u8 ShortKeyCode;
	u8 KeyProperty;
	
	u8 bkCanKeyCode;
	u8 bkLongKeyCode;
	u8 bkShortKeyCode;
	u8 bkKeyProperty;
	
	u8 KeyStatus;	
	u16 ShortPressHoldTime;
	u16 LongPressHoldTime;
	u8 F_HoldPress; 
	u8 key_source;	
}CAN_KEY_INFO;

extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern u8 CanTxErrorCounter;
extern u8 CanNoTxCounter;
extern CAN_MAIN_FLAG CanMainFlag;
extern u8 Reverse_Display_Flag;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init

void ZhiZi_NE3_MainPro(void);
void ZhiZi_NE3_RxAppDataPro(u8 *buffer);
void ZhiZi_NE3_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);

#endif
#endif
