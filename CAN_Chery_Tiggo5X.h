#ifndef _CAN_CHERY_TIGGO5x_H_
#define _CAN_CHERY_TIGGO5x_H_
#if CAN_FUN_CHERY_TIGGO_5X==1

#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		100
#define CAN_TX_BUFFER_MEDIAinfo_LENGTH      12
/*************** Receive ID********************/
#define CAN_ID_BCM_4					0x392
#define CAN_ID_ICM_2					0x452
#define CAN_ID_ICM_3					0x453
#define CAN_ID_BCM_SAM_1_G			0x39C
#define CAN_ID_IPM_2    					0x51A
#define CAN_ID_PEPS_2    				0x412
#define CAN_ID_AVM					0x440

/*************** Transmit ID********************/
#define CAN_ID_RRM_1  					0x515
#define CAN_ID_RRM_2  					0x516
#define CAN_ID_RRM_3  					0x517
#define CAN_ID_RRM_4  					0x519
#define CAN_ID_RRM_5  					0x4F8

/***************APP Cmd***********************/
#define CHERY_TIGGO5X_RX_BASIC_INFO				0x11
#define CHERY_TIGGO5X_RX_DETAIL_INFO				0x12
#define CHERY_TIGGO5X_RX_AIR_INFO					0x31
#define CHERY_TIGGO5X_RX_CONTROL_INFO			0x87
#define CHERY_TIGGO5X_RX_AVM_INFO				0xE8

#define CHERY_TIGGO5X_TX_MACHINE_INFO			0x91
#define CHERY_TIGGO5X_TX_REQUEST_CMD			0x6A
#define CHERY_TIGGO5X_TX_CONTROL_CMD			0x8C
#define CHERY_TIGGO5X_TX_LANGUAGE_CMD			0x9A
#define CHERY_TIGGO5X_TX_TIME_SET_CMD			0xCB
#define CHERY_TIGGO5X_TX_AIR_SET_CMD			0x3D

#define TIGGO5X_HEAD_CODE0             	0x5A
#define TIGGO5X_HEAD_CODE1             	0xA5

/******************************************************/
#define MAX_MEDIA_ID3_INFO_LENGTH		100

typedef enum
{
	CAN_POST_MSG_NONE=0,
	CAN_POST_MSG_RRM_1,
	CAN_POST_MSG_RRM_2,
	CAN_POST_MSG_RRM_3,
	CAN_POST_MSG_RRM_4,
	CAN_POST_MSG_RRM_5,
}CAN_POST_MESSAGE_INDEX;

typedef enum
{
	MEDIA_SOURCE_OFF=0x00,
	MEDIA_SOURCE_TUNER=0x01,
	MEDIA_SOURCE_AUX=0x0C,
	MEDIA_SOURCE_USB=0x0D,
	MEDIA_SOURCE_SD=0x19,
	MEDIA_SOURCE_IPOD=0x16,
	MEDIA_SOURCE_BT_MUSIC=0x85
}MEDIA_SOURCE_TYPE;

typedef enum
{
	AIR_CMD_NONE=0x00,
	AIR_CMD_AC_MAX=0x01,
	AIR_CMD_WIND_SPEED=0x02,
	AIR_CMD_WIND_MODEL=0x03,
	AIR_CMD_TEMP=0x04,
	AIR_CMD_AUTO_CLEAN=0x05,
	AIR_CMD_AUTO_VENTILATION=0x06,
	AIR_CMD_AC=0x07,
	AIR_CMD_SW=0x08,
	AIR_CMD_CIRCLE=0x09,
}AIR_CTRL_CMD;

typedef enum
{
	CTRL_CMD_NONE=0x00,
	CTRL_CMD_URGENCY_BRAKE_WARNING=0X01,	              
	CTRL_CMD_REMOTE_LOCK_FEEDBACK=0X02,               
	CTRL_CMD_VOLUME=0X03,	              
	CTRL_CMD_AUTO_LOCK=   0X04,                   
	CTRL_CMD_HEADLIGHT_DELAY=0X05,	                
	CTRL_CMD_DRL=0X06,	                      
	CTRL_CMD_OVER_SPEED=0X07,             
	CTRL_CMD_BACKLIGHT=0X08,	          
	CTRL_CMD_SIDE_VIEW=0X09,             
	CTRL_CMD_3D_AROUND_VIEW=0X0A,	          
	CTRL_CMD_TRAJECTORY=0X0B,             
	CTRL_CMD_MIRROR_AUTO_FOLD=0X0C,                   
	CTRL_CMD_BLIND_AREA_MONITOR=0X0D,                 
	CTRL_CMD_WELCOM_LIGHT_POLLING=0X0E,    
	CTRL_CMD_PEPS_INTELLIGENT_OPEN=0X0F,               
	CTRL_CMD_PEPS_POLLING=0X10,	            
	CTRL_CMD_BLOW_ADVANCE_ON=0X11,                   
	CTRL_CMD_BLOW_DELAY_OFF=0X12,
	CTRL_CMD_FG_HEAT=0X13,                     
	CTRL_CMD_LDW_ON_OFF=0X14,                      
	CTRL_CMD_LDW_SENSITIVITY=0X15,                      
	CTRL_CMD_MAX_INDEX=0XFF						
}CONTROL_COMMAND_INDEX;

typedef enum
{
	CAN_MAIN_IDLE=0,
	CAN_MAIN_CFG,
	CAN_MAIN_INIT,
	CAN_MAIN_WAIT_ACC,
	CAN_MAIN_TX_POWER_OFF,
	CAN_MAIN_TX_POWER_ON,
	CAN_MAIN_NORMAL,
	CAN_MAIN_WAIT_SLEEP,
	CAN_MAIN_SLEEP_CFG,
	CAN_MAIN_SLEEP
}CAN_MAIN_STATE;

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
	unsigned f_can_ready:1;
	unsigned f_driver_door:1;
	unsigned f_avm_calibration:1;
	unsigned f_can_rx_air:1;
	unsigned f_can_media_allow:1;
	unsigned f_can_media_ack:1;
}_CAN_MAIN_FLAG;

typedef union
{
	_CAN_MAIN_FLAG field;
	u16 word;
}CAN_MAIN_FLAG;

/************************* MCU->APP ***********************/
typedef struct
{
	unsigned f_acc:1;		
	unsigned f_illumi:1;		
	unsigned f_reverse:1;		
	unsigned f_parking:1;	
	unsigned f_reserved_47:4;		
}_CAN_BASE_INFO_BYTE_1;

typedef union
{
	_CAN_BASE_INFO_BYTE_1 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_1;

typedef struct
{	
	CAN_BASE_INFO_BYTE_1 byte_1;
	u8 swa_msb;
	u8 swa_lsb;
}CAN_BASE_INFO;

typedef struct
{
	unsigned f_hood:1;
	unsigned f_lock_state:1;
	unsigned f_reserved:1;
	unsigned f_trunk:1;			
	unsigned f_rr_door:1;
	unsigned f_lr_door:1;
	unsigned f_passenger_door:1;
	unsigned f_driver_door:1;
}_CAN_DETAIL_INFO_BYTE_1;

typedef union
{
	_CAN_DETAIL_INFO_BYTE_1 field;
	u8 byte;
}CAN_DETAIL_INFO_BYTE_1;

typedef struct
{	
	CAN_DETAIL_INFO_BYTE_1 byte_1;
}CAN_DETAIL_INFO;

typedef struct
{
	unsigned f_ac_req_cmd:1;
	unsigned f_ac_req_display:1;
	unsigned f_ac_max:1;	
	unsigned f_on_off	:1;
	unsigned f_disp:1;	
	unsigned f_wind_speed:3;
}_CAN_AIR_INFO_BYTE_1;

typedef union
{
	_CAN_AIR_INFO_BYTE_1 field;	
	u8 byte;
}CAN_AIR_INFO_BYTE_1;

typedef struct
{
	unsigned f_wind_mode:3;
	unsigned f_temperature:5;
}_CAN_AIR_INFO_BYTE_2;

typedef union
{
	_CAN_AIR_INFO_BYTE_2 field;	
	u8 byte;
}CAN_AIR_INFO_BYTE_2;

typedef struct
{
	unsigned f_auto_clean:1;
	unsigned f_atuo_ventilation:1;		
	unsigned f_internal_external_cir:1;
	unsigned f_reserved_37:5;	
}_CAN_AIR_INFO_BYTE_3;

typedef union
{
	_CAN_AIR_INFO_BYTE_3 field;	
	u8 byte;
}CAN_AIR_INFO_BYTE_3;

typedef struct
{
	CAN_AIR_INFO_BYTE_1 byte_1;				
	CAN_AIR_INFO_BYTE_2 byte_2;
	CAN_AIR_INFO_BYTE_3 byte_3;
}CAN_AIR_INFO;

typedef struct
{
	unsigned f_defense_reminder:2;		
	unsigned f_daytime_driving_sta:1;			
	unsigned f_auto_lock:1;			
	unsigned f_intelligent_lock:1;
	unsigned f_welcome_light:1;			
	unsigned f_reserved_67:2;		
}_CAN_CTRL_FEEDBACK_INFO_BYTE_1;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_1 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_1;

typedef struct
{
	unsigned f_over_speed:5;	
	unsigned f_reserved_67:3;
}_CAN_CTRL_FEEDBACK_INFO_BYTE_2;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_2 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_2;

typedef struct
{
	unsigned f_instrument_backlight:4;	
	unsigned f_reserved_47:4;
}_CAN_CTRL_FEEDBACK_INFO_BYTE_3;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_3 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_3;

typedef struct
{
	CAN_CTRL_FEEDBACK_INFO_BYTE_1 byte_1;	
	CAN_CTRL_FEEDBACK_INFO_BYTE_2 byte_2;
	CAN_CTRL_FEEDBACK_INFO_BYTE_3 byte_3;
}CAN_CTRL_FEEDBACK_INFO;

typedef struct
{
	unsigned f_lr_info:6;	
	unsigned f_reserved_67:2;
}_CAN_AVM_INFO_BYTE_1;

typedef union
{
	_CAN_AVM_INFO_BYTE_1 field;	
	u8 byte;
}CAN_AVM_INFO_BYTE_1;

typedef struct
{
	unsigned f_rmr_info:6;	
	unsigned f_reserved_67:2;
}_CAN_AVM_INFO_BYTE_2;

typedef union
{
	_CAN_AVM_INFO_BYTE_2 field;	
	u8 byte;
}CAN_AVM_INFO_BYTE_2;

typedef struct
{
	unsigned f_lmr_info:6;	
	unsigned f_reserved_67:2;
}_CAN_AVM_INFO_BYTE_3;

typedef union
{
	_CAN_AVM_INFO_BYTE_3 field;	
	u8 byte;
}CAN_AVM_INFO_BYTE_3;

typedef struct
{
	unsigned f_rr_info:6;	
	unsigned f_reserved_67:2;
}_CAN_AVM_INFO_BYTE_4;

typedef union
{
	_CAN_AVM_INFO_BYTE_4 field;	
	u8 byte;
}CAN_AVM_INFO_BYTE_4;

typedef struct
{
	unsigned f_lf_info:5;	
	unsigned f_reserved_57:3;
}_CAN_AVM_INFO_BYTE_5;

typedef union
{
	_CAN_AVM_INFO_BYTE_5 field;	
	u8 byte;
}CAN_AVM_INFO_BYTE_5;

typedef struct
{
	unsigned f_rf_info:5;	
	unsigned f_reserved_57:3;
}_CAN_AVM_INFO_BYTE_6;

typedef union
{
	_CAN_AVM_INFO_BYTE_6 field;	
	u8 byte;
}CAN_AVM_INFO_BYTE_6;

typedef struct
{
	unsigned f_rmf_info:5;	
	unsigned f_radar_voice:3;
}_CAN_AVM_INFO_BYTE_7;

typedef union
{
	_CAN_AVM_INFO_BYTE_7 field;	
	u8 byte;
}CAN_AVM_INFO_BYTE_7;

typedef struct
{
	unsigned f_lmf_info:5;	
	unsigned f_reserved_57:3;
}_CAN_AVM_INFO_BYTE_8;

typedef union
{
	_CAN_AVM_INFO_BYTE_8 field;	
	u8 byte;
}CAN_AVM_INFO_BYTE_8;

typedef struct
{
	CAN_AVM_INFO_BYTE_1 byte_1;	
	CAN_AVM_INFO_BYTE_2 byte_2;	
	CAN_AVM_INFO_BYTE_3 byte_3;	
	CAN_AVM_INFO_BYTE_4 byte_4;	
	CAN_AVM_INFO_BYTE_5 byte_5;	
	CAN_AVM_INFO_BYTE_6 byte_6;	
	CAN_AVM_INFO_BYTE_7 byte_7;	
	CAN_AVM_INFO_BYTE_8 byte_8;	
}CAN_AVM_INFO;

typedef struct
{
	u8 hour;
	u8 min;
	u8 sec;
	u8 year;
	u8 month;
	u8 day;
}CAN_TIME_INFO;

typedef struct
{
	CAN_AIR_INFO air_info;
	CAN_BASE_INFO base_info;
	CAN_AVM_INFO avm_info;
	CAN_DETAIL_INFO detail_info;
	CAN_CTRL_FEEDBACK_INFO ctrl_feedback_info;
	CAN_TIME_INFO time_info;
}CAN_RX_INFO;

/************************* MCU->CAN BUS ***********************/
typedef struct
{
	unsigned f_reserved_01:2;	
	unsigned f_auto_lock:2;
	unsigned f_reserved_4:1;
	unsigned f_remote_lock_feedback:2;
	unsigned f_reserved_7	:1;	
}_CAN_RRM_1_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_1_INFO_BYTE_1 field;
	u8 byte;
}CAN_RRM_1_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved_01:2;
	unsigned f_drl:2;
	unsigned f_reserved_47:4;	
}_CAN_RRM_1_INFO_BYTE_2;

typedef union
{
	_CAN_RRM_1_INFO_BYTE_2 field;	
	u8 byte;
}CAN_RRM_1_INFO_BYTE_2;

typedef struct
{
	unsigned f_reserved_0	:1;	
	unsigned f_over_speed:6;	
	unsigned f_language:2;	
	unsigned f_reserved_9_15:7;
}_CAN_RRM_1_INFO_BYTE_34;

typedef union
{
	_CAN_RRM_1_INFO_BYTE_34 field;
	u16 word;
}CAN_RRM_1_INFO_BYTE_34;

typedef struct
{
	CAN_RRM_1_INFO_BYTE_1 byte_1;
	CAN_RRM_1_INFO_BYTE_2 byte_2;
	CAN_RRM_1_INFO_BYTE_34 byte_34;
	u8 reserved_5;
	u8 reserved_6;
	u8 reserved_7;
	u8 reserved_8;
}CAN_RRM_1_INFO;

typedef struct
{
	unsigned f_fm_am:2;	
	unsigned f_as:2;	
	unsigned f_source	:3;
	unsigned f_rrm_on:1;
}_CAN_RRM_2_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_2_INFO_BYTE_1 field;
	u8 byte;
}CAN_RRM_2_INFO_BYTE_1;

typedef struct
{
	unsigned f_disp:2;	
	unsigned f_reserved_27:6;
}_CAN_RRM_2_INFO_BYTE_8;

typedef union
{
	_CAN_RRM_2_INFO_BYTE_8 field;
	u8 byte;
}CAN_RRM_2_INFO_BYTE_8;

typedef struct
{
	CAN_RRM_2_INFO_BYTE_1 byte_1;
	u8 frequence_fm_h;
	u8 frequence_fm_l;
	u8 frequence_am_h;
	u8 frequence_am_l;
	u8 volume;
	u8 reserved_7;
	CAN_RRM_2_INFO_BYTE_8 byte_8;
}CAN_RRM_2_INFO;

typedef struct
{
	u8 hour;
	u8 min;
	u8 instrument_back_light;
	u8 second;
}CAN_RRM_3_INFO;

typedef struct
{
	unsigned f_reserved_02:3;
	unsigned f_wind_speed:3;
	unsigned f_ac_max:2;
}_CAN_RRM_4_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_1 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved_04:5;
	unsigned f_wind_mode:3;	
}_CAN_RRM_4_INFO_BYTE_2;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_2 field;
	u8 byte;
}CAN_RRM_4_INFO_BYTE_2;

typedef struct
{
	unsigned f_temperature:5;
	unsigned f_reserved_57:3;	
}_CAN_RRM_4_INFO_BYTE_5;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_5 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_5;

typedef struct
{
	unsigned f_air_sw:2;
	unsigned f_ac:2;
	unsigned f_auto_ventilation:2;
	unsigned f_auto_clear:2;	
}_CAN_RRM_4_INFO_BYTE_6;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_6 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_6;

typedef struct
{
	unsigned f_reserved_01:2;
	unsigned f_circle:2;
	unsigned f_reserved_47:4;	
}_CAN_RRM_4_INFO_BYTE_7;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_7 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_7;

typedef struct
{
	CAN_RRM_4_INFO_BYTE_1 byte_1;				
	CAN_RRM_4_INFO_BYTE_2 byte_2;
	u8 reserved_3;	
	u8 reserved_4;
	CAN_RRM_4_INFO_BYTE_5 byte_5;
	CAN_RRM_4_INFO_BYTE_6 byte_6;
	CAN_RRM_4_INFO_BYTE_7 byte_7;
	u8 reserved_8;
}CAN_RRM_4_INFO;

typedef struct
{
	unsigned f_welcom_light_polling:2;	
	unsigned f_reserved_23:2;
	unsigned f_peps_polling:2;  	
	unsigned f_reserved_67:2;	
}_CAN_RRM_5_INFO_BYTE_2;

typedef union
{
	_CAN_RRM_5_INFO_BYTE_2 field;	
	u8 byte;
}CAN_RRM_5_INFO_BYTE_2;

typedef struct
{
	u8 reserved_1;
	CAN_RRM_5_INFO_BYTE_2 byte_2;
	u8 reserved_3;
	u8 reserved_4;
	u8 reserved_5;
	u8 reserved_6;
	u8 reserved_7;
	u8 reserved_8;
}CAN_RRM_5_INFO;

typedef struct
{
	CAN_RRM_1_INFO rrm_1_info;
	CAN_RRM_2_INFO rrm_2_info;
	CAN_RRM_3_INFO rrm_3_info;
	CAN_RRM_4_INFO rrm_4_info;
	CAN_RRM_5_INFO rrm_5_info;
}CAN_TX_INFO;

/***************************************************************/

extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_MAIN_FLAG CanMainFlag;
extern CAN_TX_INFO CanTxInfo;


#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init
#define F_CAN_READY			CanMainFlag.field.f_can_ready
#define F_DRIVER_DOOR_STATE	CanMainFlag.field.f_driver_door
#define F_AVM_CALIBRATION		CanMainFlag.field.f_avm_calibration
#define F_CAN_RX_AIR_INFO		CanMainFlag.field.f_can_rx_air

void Tiggo5X_MainPro(void);
void Tiggo5X_RxAppDataPro(u8 *buffer);
void Tiggo5X_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
void Tiggo5X_PostMessage(CAN_POST_MESSAGE_INDEX index);

#endif
#endif

