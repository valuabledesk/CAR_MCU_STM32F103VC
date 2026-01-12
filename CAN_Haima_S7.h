#ifndef _CAN_HAIMA_S7_H_
#define _CAN_HAIMA_S7_H_
#if CAN_FUN_HAIMA_S7==1

#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		100

/*************** Receive ID********************/
#define CAN_ID_TEST 0x666   //this ID is convenient for engineers to test other funtions

#define CAN_ID_SAS						0x080
#define CAN_ID_GW						0x1F7
#define CAN_ID_BCM						0x22C
#define CAN_ID_HVAC					0x562
#define CAN_ID_PEPS						0x58B
#define CAN_ID_SVM						0x591
#define CAN_ID_DIAG_IST_REQ			0x761
#define CAN_ID_DIAG_FUNC_REQ			0x7DF

#define CAN_ID_SPEED     			0x120
#define CAN_ID_THROTTLE     			0x1AA
#define CAN_ID_GEAR     			0x265
/*************** Transmit ID********************/
#define CAN_ID_IST_0					0x540
#define CAN_ID_IST_1					0x541
#define CAN_ID_IST_2					0x539
#define CAN_ID_DIAG_IST_RESP			0x769

/***************APP Cmd***********************/
#define HAIMA_S7_RX_AIR_INFO				0x23
#define HAIMA_S7_RX_BASIC_INFO			0x28
#define HAIMA_S7_RX_AVM_INFO				0x50
#define HAIMA_S7_RX_SPEED_INFO			0x24
#define HAIMA_S7_RX_THROTTLE_INFO		0x25
#define HAIMA_S7_RX_GEAR_INFO				0x26

#define HAIMA_S7_TX_REQ_CMD					0x90
#define HAIMA_S7_TX_AIR_CMD					0x8A
#define HAIMA_S7_TX_AVM_CMD					0x8B

#define HAIMA_S7_HEAD_CODE					0x2E

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
	CAN_POST_MSG_IST_0,
	CAN_POST_MSG_IST_1,
	CAN_POST_MSG_IST_2,
	CAN_POST_MSG_DIAG_IST_RESP,
	CAN_POST_MSG_MAX_INDEX
}CAN_POST_MESSAGE_INDEX;

typedef enum 
{
	AIR_KEY_OFF=0,          
	AIR_KEY_WIND_SPEED,      
	AIR_KEY_TEMP,   
	AIR_KEY_WIND_MODE_1, 
	AIR_KEY_AC,      
	AIR_KEY_CIRCLE,
	AIR_KEY_REAR_DEFROST,       
	AIR_KEY_FRONT_DEFROST,     
	AIR_KEY_WIND_MODE_2,     
	AIR_KEY_AUTO,
	AIR_KEY_MAX
} HAIMA_S7_AIR_KEY_INDEX;

typedef enum
{
	INFO_KEY_IDLE=0,
	INFO_KEY_PRESSED
}HAIMA_S7_INFO_KEY_DET_STATE;
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
	unsigned f_front_defrost:1;
	unsigned f_rear_defrost:1;
	unsigned f_reserved_2:1;
	unsigned f_auto:1;
	unsigned f_reserved_4:1;
	unsigned f_circle:1;
	unsigned f_ac:1;
	unsigned f_on_off:1;
}_CAN_AIR_INFO_BYTE_1;

typedef union
{
	_CAN_AIR_INFO_BYTE_1 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_1;

typedef struct
{
	CAN_AIR_INFO_BYTE_1 byte_1;
	u8 wind_mode;
	u8 wind_speed;
	u8 reserved_3;
	u8 temperature;
	u8 out_temperature;
}CAN_AIR_INFO;

typedef struct
{
	unsigned f_reserved_02:3;
	unsigned f_rear_door:1;
	unsigned f_rear_left_door:1;
	unsigned f_rear_right_door:1;
	unsigned f_front_left_door:1;
	unsigned f_fornt_right_door:1;
}_CAN_BASE_INFO_BYTE_1;

typedef union
{
	_CAN_BASE_INFO_BYTE_1 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_1;

typedef struct
{
	unsigned f_gear:4;
	unsigned f_power_level:3;
	unsigned f_can_ready:1;
}_CAN_BASE_INFO_BYTE_2;

typedef union
{
	_CAN_BASE_INFO_BYTE_2 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_2;

typedef struct
{
	
	unsigned speed1:5;
	unsigned speed0:3;
	
}_CAN_BASE_INFO_BYTE_3;

typedef union
{
	_CAN_BASE_INFO_BYTE_3 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_3;

typedef struct
{
	
	unsigned speed2:8;
	
}_CAN_BASE_INFO_BYTE_4;

typedef union
{
	_CAN_BASE_INFO_BYTE_4 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_4;

typedef struct
{
	unsigned current_gear:8;
}_CAN_BASE_INFO_BYTE_5;
typedef union
{
	_CAN_BASE_INFO_BYTE_5 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_5;
typedef struct
{
	unsigned throttle:8;
}_CAN_BASE_INFO_BYTE_6;
typedef union
{
	_CAN_BASE_INFO_BYTE_6 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_6;
///////////////////////////////////////
typedef struct
{
	unsigned  steering_wheel_angle_L:8;
}_CAN_BASE_INFO_BYTE_7;
typedef union
{
	_CAN_BASE_INFO_BYTE_7 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_7;
typedef struct
{
	unsigned steering_wheel_angle_H:8;
}_CAN_BASE_INFO_BYTE_8;
typedef union
{
	_CAN_BASE_INFO_BYTE_8 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_8;

typedef struct
{
	CAN_BASE_INFO_BYTE_1 byte_1;
	CAN_BASE_INFO_BYTE_2 byte_2;
	CAN_BASE_INFO_BYTE_3 byte_3;
	CAN_BASE_INFO_BYTE_4 byte_4;
	CAN_BASE_INFO_BYTE_5 byte_5;
	CAN_BASE_INFO_BYTE_6 byte_6;
	
	CAN_BASE_INFO_BYTE_7 byte_7;
	CAN_BASE_INFO_BYTE_8 byte_8;
}CAN_BASE_INFO;

typedef struct
{
	unsigned f_camera_status:4;
	unsigned f_reserved_46:3;
	unsigned f_avm_on_off:1;
}_CAN_AVM_INFO_BYTE_1;

typedef union
{
	_CAN_AVM_INFO_BYTE_1 field;
	u8 byte;
}CAN_AVM_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved_05:6;
	unsigned f_guide_on_off:1;
	unsigned f_reserved_7:1;
}_CAN_AVM_INFO_BYTE_2;

typedef union
{
	_CAN_AVM_INFO_BYTE_2 field;
	u8 byte;
}CAN_AVM_INFO_BYTE_2;

typedef struct
{
	CAN_AVM_INFO_BYTE_1 byte_1;
	CAN_AVM_INFO_BYTE_2 byte_2;

}CAN_AVM_INFO;

typedef struct
{
	CAN_AIR_INFO air_info;
	CAN_BASE_INFO base_info;
	CAN_AVM_INFO avm_info;
}CAN_RX_INFO;

typedef struct
{
	unsigned f_add_temp:2;
	unsigned f_dec_temp:2;
	unsigned f_reserved_47:4;
}_CAN_IST_0_INFO_BYTE_6;

typedef union
{
	_CAN_IST_0_INFO_BYTE_6 field;
	u8 byte;
}CAN_IST_0_INFO_BYTE_6;

typedef struct
{
	unsigned f_reserved_01:2;
	unsigned f_wind_mode:2;
	unsigned f_add_speed:2;
	unsigned f_dec_speed:2;
}_CAN_IST_0_INFO_BYTE_8;

typedef union
{
	_CAN_IST_0_INFO_BYTE_8 field;
	u8 byte;
}CAN_IST_0_INFO_BYTE_8;

typedef struct
{
	u8 reserved_1;
	u8 reserved_2;
	u8 reserved_3;
	u8 reserved_4;
	u8 reserved_5;
	CAN_IST_0_INFO_BYTE_6 byte_6;
	u8 reserved_7;
	CAN_IST_0_INFO_BYTE_8 byte_8;
}CAN_IST_0_INFO;

typedef struct
{
	unsigned f_reserved_03:4;
	unsigned f_wind_mode:3;
	unsigned f_reserved_7:1;
}_CAN_IST_1_INFO_BYTE_3;

typedef union
{
	_CAN_IST_1_INFO_BYTE_3 field;
	u8 byte;
}CAN_IST_1_INFO_BYTE_3;

typedef struct
{
	unsigned f_circle:2;
	unsigned f_reserved_2:1;
	unsigned f_auto:1;
	unsigned f_rear_defrost:2;
	unsigned f_reserved_67:2;
}_CAN_IST_1_INFO_BYTE_4;

typedef union
{
	_CAN_IST_1_INFO_BYTE_4 field;
	u8 byte;
}CAN_IST_1_INFO_BYTE_4;

typedef struct
{
	unsigned wind_speed:5;
	unsigned f_front_defrost:2;
	unsigned f_air_close:1;
}_CAN_IST_1_INFO_BYTE_5;

typedef union
{
	_CAN_IST_1_INFO_BYTE_5 field;
	u8 byte;
}CAN_IST_1_INFO_BYTE_5;

typedef struct
{
	unsigned f_reserved_0:1;
	unsigned f_ac:2;
	unsigned f_reserved_27:5;
}_CAN_IST_1_INFO_BYTE_6;

typedef union
{
	_CAN_IST_1_INFO_BYTE_6 field;
	u8 byte;
}CAN_IST_1_INFO_BYTE_6;

typedef struct
{
	u8 reserved_1;
	u8 reserved_2;
	CAN_IST_1_INFO_BYTE_3 byte_3;
	CAN_IST_1_INFO_BYTE_4 byte_4;
	CAN_IST_1_INFO_BYTE_5 byte_5;
	CAN_IST_1_INFO_BYTE_6 byte_6;
	u8 reserved_7;
	u8 temp;
}CAN_IST_1_INFO;

typedef struct
{
	unsigned f_reserved_01:2;
	unsigned f_key_con_for_icm:2;
	unsigned f_acc_vol_ind:2;
	unsigned f_reserved_67:2;
}_CAN_IST_2_INFO_BYTE_1;

typedef union
{
	_CAN_IST_2_INFO_BYTE_1 field;
	u8 byte;
}CAN_IST_2_INFO_BYTE_1;

typedef struct
{
	unsigned f_touch_key:3;
	unsigned f_reserved_3:1;
	unsigned f_avm_guide_set:2;
	unsigned f_reserved_67:2;
}_CAN_IST_2_INFO_BYTE_3;

typedef union
{
	_CAN_IST_2_INFO_BYTE_3 field;
	u8 byte;
}CAN_IST_2_INFO_BYTE_3;

typedef struct
{
	CAN_IST_2_INFO_BYTE_1 byte_1;
	u8 reserved_2;
	CAN_IST_2_INFO_BYTE_3 byte_3;
	u8 reserved_4;
}CAN_IST_2_INFO;

typedef struct
{
	CAN_IST_0_INFO ist_0_info;
	CAN_IST_1_INFO ist_1_info;
	CAN_IST_2_INFO ist_2_info;
	u8 diag_ist_resp[8];
}CAN_TX_INFO;

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
extern CAN_RX_INFO CanRxInfo;
extern u8 CAN_TURN_STATE;

extern u8 F_CanNoWakeUp;
extern CAN_MAIN_STATE CanMainState;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT			CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init

void Haima_S7_MainPro(void);
void Haima_S7_RxAppDataPro(u8 *buffer);
void Haima_S7_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
u8 Haima_S7_CheckTxMessage(u32 id,u8 *data);
void Haima_S7_CanReset(void);


#endif
#endif
