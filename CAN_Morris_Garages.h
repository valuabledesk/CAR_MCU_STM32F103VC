#ifndef _CAN_Morris_Garages_H_
#define _CAN_Morris_Garages_H_
#if CAN_FUN_MORRIS_GARAGES==1

#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		100

/*************** Receive ID********************/
#define CAN_ID_REVERSE				0x35A
#define CAN_ID_PARKING				0x2D1
#define CAN_ID_ILLUMI				0x46A

/*************** Transmit ID********************/
#define CAN_ID_SETTING_1				0x465
#define CAN_ID_SETTING_2				0x466
#define CAN_ID_SETTING_3				0x0D6
#define CAN_ID_AIR						0x361
#define CAN_ID_TIME					0x541

/***************APP Cmd***********************/
#define Morris_Garages_RX_AIR_INFO					0x20
#define Morris_Garages_RX_BASIC_INFO				0x21


#define Morris_Garages_TX_SETTING_CMD				0x81
#define Morris_Garages_TX_AIR_CMD					0x82
#define Morris_Garages_TX_TIME_CMD					0x83

#define Morris_Garages_HEAD_CODE					0x2E

typedef enum
{
	CAN_MAIN_IDLE=0,
	CAN_MAIN_CFG,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
	CAN_MAIN_SLEEP_CFG,
	CAN_MAIN_SLEEP
}CAN_MAIN_STATE;

typedef enum
{
	CAN_POST_MSG_NONE=0,
	CAN_POST_MSG_SETTING_1,
	CAN_POST_MSG_SETTING_2,
	CAN_POST_MSG_SETTING_3,
	CAN_POST_MSG_AIR,
	CAN_POST_MSG_TIME,
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
	unsigned f_reserved:6;
	unsigned f_follow_me_home:1;
	unsigned f_reserved_7:1;
}_CAN_SETTING_1_INFO_BYTE_1;

typedef union
{
	_CAN_SETTING_1_INFO_BYTE_1 field;
	u8 byte;
}CAN_SETTING_1_INFO_BYTE_1;

typedef struct
{	
	unsigned f_reserved:3;
	unsigned f_search_car:1;
	unsigned f_reserved_47:4;
}_CAN_SETTING_1_INFO_BYTE_2;

typedef union
{
	_CAN_SETTING_1_INFO_BYTE_2 field;
	u8 byte;
}CAN_SETTING_1_INFO_BYTE_2;

typedef struct
{	
	unsigned f_reserved:2;
	unsigned f_near_car_unlock:1;
	unsigned f_reserved_37:5;
}_CAN_SETTING_1_INFO_BYTE_5;

typedef union
{
	_CAN_SETTING_1_INFO_BYTE_5 field;
	u8 byte;
}CAN_SETTING_1_INFO_BYTE_5;

typedef struct
{	
	unsigned f_reserved:1;
	unsigned f_remote_unclock:1;
	unsigned f_reserved_27:6;
}_CAN_SETTING_1_INFO_BYTE_6;

typedef union
{
	_CAN_SETTING_1_INFO_BYTE_6 field;
	u8 byte;
}CAN_SETTING_1_INFO_BYTE_6;

typedef struct
{
	CAN_SETTING_1_INFO_BYTE_1 byte_1;
	CAN_SETTING_1_INFO_BYTE_2 byte_2;
	CAN_SETTING_1_INFO_BYTE_5 byte_5;
	CAN_SETTING_1_INFO_BYTE_6 byte_6;
}CAN_SETTING_1_INFO;

typedef struct
{	
	unsigned f_reserved:6;
	unsigned f_rearview_mirror:1;
	unsigned f_reserved_7:1;
}_CAN_SETTING_2_INFO_BYTE_7;

typedef union
{
	_CAN_SETTING_2_INFO_BYTE_7 field;
	u8 byte;
}CAN_SETTING_2_INFO_BYTE_7;

typedef struct
{
	CAN_SETTING_2_INFO_BYTE_7 byte_7;
}CAN_SETTING_2_INFO;

typedef struct
{	
	unsigned f_reserved:2;
	unsigned f_vehicle_stability_control:1;
	unsigned f_reserved_37:5;
}_CAN_SETTING_3_INFO_BYTE_0;

typedef union
{
	_CAN_SETTING_3_INFO_BYTE_0 field;
	u8 byte;
}CAN_SETTING_3_INFO_BYTE_0;

typedef struct
{
	CAN_SETTING_3_INFO_BYTE_0 byte_0;
}CAN_SETTING_3_INFO;

typedef struct
{
	unsigned f_blow_mode:2;
	unsigned f_air_sw:1;
	unsigned f_temperature:5;
}_CAN_AIR_INFO_BYTE_1;

typedef union
{
	_CAN_AIR_INFO_BYTE_1 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved:4;
	unsigned f_speed:3;
	unsigned f_reserved_7:1;
}_CAN_AIR_INFO_BYTE_3;

typedef union
{
	_CAN_AIR_INFO_BYTE_3 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_3;

typedef struct
{
	unsigned f_reserved:2;
	unsigned f_AC:1;
	unsigned f_reserved_35:3;
	unsigned f_internal_external_cir:1;
	unsigned f_reserved7:1;
}_CAN_AIR_INFO_BYTE_5;

typedef union
{
	_CAN_AIR_INFO_BYTE_5 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_5;

typedef struct
{
	CAN_AIR_INFO_BYTE_1 byte_1;
	CAN_AIR_INFO_BYTE_3 byte_3;
	CAN_AIR_INFO_BYTE_5 byte_5;
}CAN_AIR_INFO;

typedef struct
{
	unsigned f_year:6;
	unsigned f_reserved:2;
}_CAN_TIME_INFO_BYTE_0;

typedef union
{
	_CAN_TIME_INFO_BYTE_0 field;
	u8 byte;
}CAN_TIME_INFO_BYTE_0;

typedef struct
{
	unsigned f_month:4;
	unsigned f_reserved:4;
}_CAN_TIME_INFO_BYTE_1;

typedef union
{
	_CAN_TIME_INFO_BYTE_1 field;
	u8 byte;
}CAN_TIME_INFO_BYTE_1;

typedef struct
{
	unsigned f_day:5;
	unsigned f_reserved:3;
}_CAN_TIME_INFO_BYTE_2;

typedef union
{
	_CAN_TIME_INFO_BYTE_2 field;
	u8 byte;
}CAN_TIME_INFO_BYTE_2;

typedef struct
{
	unsigned f_hour:5;
	unsigned f_reserved:3;
}_CAN_TIME_INFO_BYTE_3;

typedef union
{
	_CAN_TIME_INFO_BYTE_3 field;
	u8 byte;
}CAN_TIME_INFO_BYTE_3;

typedef struct
{
	unsigned f_minute:6;
	unsigned f_reserved:2;
}_CAN_TIME_INFO_BYTE_4;

typedef union
{
	_CAN_TIME_INFO_BYTE_4 field;
	u8 byte;
}CAN_TIME_INFO_BYTE_4;

typedef struct
{
	unsigned f_second:6;
	unsigned f_time_mode:2;
}_CAN_TIME_INFO_BYTE_5;

typedef union
{
	_CAN_TIME_INFO_BYTE_5 field;
	u8 byte;
}CAN_TIME_INFO_BYTE_5;

typedef struct
{
	CAN_TIME_INFO_BYTE_0 byte_0;
	CAN_TIME_INFO_BYTE_1 byte_1;
	CAN_TIME_INFO_BYTE_2 byte_2;
	CAN_TIME_INFO_BYTE_3 byte_3;
	CAN_TIME_INFO_BYTE_4 byte_4;
	CAN_TIME_INFO_BYTE_5 byte_5;
}CAN_TIME_INFO;

typedef struct
{
	CAN_SETTING_1_INFO setting_1_info;
	CAN_SETTING_2_INFO setting_2_info;
	CAN_SETTING_3_INFO setting_3_info;
	CAN_AIR_INFO air_info;
	CAN_TIME_INFO time_info;
}CAN_TX_INFO;

typedef struct
{
	unsigned f_reverse_state:1;
	unsigned f_parking_state:1;
	unsigned f_illumi_state:1;
}_CAN_BASE_INFO_BYTE_0;

typedef union
{
	_CAN_BASE_INFO_BYTE_0 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_0;

typedef struct
{
	CAN_BASE_INFO_BYTE_0 byte_0;
}CAN_BASE_INFO;

typedef struct
{
	CAN_BASE_INFO base_info;
}CAN_RX_INFO;

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
extern u8 CanTxErrorCounter;
extern u8 CanNoTxCounter;
extern CAN_MAIN_FLAG CanMainFlag;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT			CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init

void Morris_Garages_MainPro(void);
void Morris_Garages_RxAppDataPro(u8 *buffer);
void Morris_Garages_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
u8 Morris_Garages_CheckTxMessage(u32 id,u8 *data);
void Morris_Garages_CanReset(void);


#endif
#endif

