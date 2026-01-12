#ifndef _CAN_CHERY_TIGGO7_H_
#define _CAN_CHERY_TIGGO7_H_
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_TIGGO_5==1||CAN_FUN_CHERY_TIGGO_7==1||CAN_FUN_CHERY_ARRIZO_6==1||CAN_FUN_CHERY_TIGGO_2==1||CAN_FUN_CHERY_ARRIZO_5==1||CAN_FUN_CHERY_TIGGO_5X_T19==1

#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		100
#define CAN_TX_BUFFER_MEDIAinfo_LENGTH      12
/*************** Receive ID********************/
#define CAN_ID_BCM_4					0x392
#define CAN_ID_BCM_5					0x51B
#define CAN_ID_ICM_1					0x430
#define CAN_ID_ICM_2					0x452
#define CAN_ID_ICM_3					0x453
#define CAN_ID_BCM_ABS_G				0x2C0
#define CAN_ID_BCM_SAM_1_G			0x39C
#define CAN_ID_NMm_BCM  				0x600
#define CAN_ID_NMm_ICM  				0x614
#define CAN_ID_NMm_RADAR  			0x61F
#define CAN_ID_CLM_2 					0x535
#define CAN_ID_AVM_1 					0x438
#define CAN_ID_IPM_1 					0x4F1
#define CAN_ID_IPM_2    					0x51A
#define CAN_ID_PEPS_2    				0x412
#define CAN_ID_LDW_1    					0x423
#define CAN_ID_ICM_4                    0x64D
#define CAN_ID_BCM_SAM_2_G				0x340
#define CAN_ID_DIAGNOSTIC_RX_ID			0x74A
#define CAN_ID_BCM_PEPS_G				0x3E6
#define CAN_ID_BCM_EPB_G				0x4F6
#define CAN_ID_BCM_7					0x5EA
#define CAN_ID_BCM_10 					0x5F0

/*************** Transmit ID********************/
#define CAN_ID_RRM_1  					0x515
#define CAN_ID_RRM_2  					0x516
#define CAN_ID_RRM_3  					0x517
#define CAN_ID_RRM_4  					0x519
#define CAN_ID_RRM_5  					0x64A
#define CAN_ID_RRM_6 					0x432
#define CAN_ID_RRM_7  					0x4F8
#define CAN_ID_RRM_9  					0x4F9
#define CAN_ID_NMm_RRM  				0x618
#define CAN_ID_DIAGNOSTIC_TX_ID			0x75A

/***************APP Cmd***********************/
#define CHERY_TIGGO7_RX_BASIC_INFO				0x11
#define CHERY_TIGGO7_RX_DETAIL_INFO				0x12
#define CHERY_TIGGO7_RX_TPMS_INFO				0x13
#define CHERY_TIGGO7_RX_DRIVING_INFO				0x15
#define CHERY_TIGGO7_RX_TIME_INFO				0x23
#define CHERY_TIGGO7_RX_AIR_INFO					0x31
#define CHERY_TIGGO7_RX_AIR_KEY					0x32							
#define CHERY_TIGGO7_RX_RADAR_INFO				0x41
#define CHERY_TIGGO7_RX_CONTROL_INFO			0x87
#define CHERY_TIGGO7_RX_AVM_INFO					0xE8

#define CHERY_TIGGO7_TX_MACHINE_INFO			0x91
#define CHERY_TIGGO7_TX_TEXT_INFO				0x92
#define CHERY_TIGGO7_TX_REQUEST_CMD				0x6A
#define CHERY_TIGGO7_TX_CONTROL_CMD				0x8C
#define CHERY_TIGGO7_TX_LANGUAGE_CMD			0x9A
#define CHERY_TIGGO7_TX_TIME_SET_CMD				0xCB
#define CHERY_TIGGO7_TX_AIR_SET_CMD				0x3D
#define CHERY_TIGGO7_TX_AVM_CMD					0x2C

#define TIGGO7_HEAD_CODE0             	0x5A
#define TIGGO7_HEAD_CODE1             	0xA5

/******************************************************/
#define MAX_MEDIA_ID3_INFO_LENGTH		100

#define MAX_SIDE_VIEW_SPEED		20
#define MAX_AVM_SPEED              		27
#define MAX_PARKING_SPEED			0
#define CHERY_AIR_DISABLE_TIME				T1S_1

typedef enum
{
	CAN_POST_MSG_NONE=0,
	CAN_POST_MSG_RRM_1,
	CAN_POST_MSG_RRM_2,
	CAN_POST_MSG_RRM_3,
	CAN_POST_MSG_RRM_4,
	CAN_POST_MSG_RRM_5,
	CAN_POST_MSG_RRM_6,
	CAN_POST_MSG_RRM_7,
	CAN_POST_MSG_RRM_9,
	CAN_POST_MSG_NMM_RRM,
	CAN_POST_MSG_DIAGNOSTIC,
	CAN_POST_MSG_MAX_INDEX
}CAN_POST_MESSAGE_INDEX;

typedef enum
{
	AIR_CMD_NONE=0x00,
	AIR_CMD_ON_OFF=0x01,
	AIR_CMD_AC=0x02,
	AIR_CMD_DUAL=0x03,
	AIR_CMD_AUTO=0x04,
	AIR_CMD_FRONT_DEFROST=0x05,
	AIR_CMD_CIRCLE=0x07,
	AIR_CMD_WIND_UP=0x0B,
	AIR_CMD_WIND_DOWN=0x0C,
	AIR_CMD_LEFT_TEMP_UP=0x0D,
	AIR_CMD_LEFT_TEMP_DOWN=0x0E,
	AIR_CMD_RIGHT_TEMP_UP=0x0F,
	AIR_CMD_RIGHT_TEMP_DOWN=0x10,
	AIR_CMD_WIND_BODY=0x19,
	AIR_CMD_WIND_BODY_FEET=0x1A,
	AIR_CMD_WIND_WIN_FEET=0x1B,	
	AIR_CMD_WIND_FEET=0x1C,
	AIR_CMD_OPEN_SCREEN=0x1D,
	AIR_CMD_CLOSE_SCREEN=0x1E,
	AIR_CMD_BLOW_ADVANCE_ON=0x1F,
	AIR_CMD_BLOW_DELAY_OFF=0x20,
	AIR_CMD_AC_MAX=0x21,
	AIR_CMD_WIND_VALUE=0x22,
	AIR_CMD_LEFT_TEMP_VALUE=0x23
}AIR_CTRL_CMD;

typedef enum
{
	WIND_OFF     			=   (u8)0x00,   //壽
	WIND_AUTO   				=   (u8)0x01,	//赻雄
	WIND_FEET    			=   (u8)0x03,	//斯褐
	WIND_BODY_FEET 			=   (u8)0x05,	//斯旯斯褐
	WIND_BODY 				=   (u8)0x06,	//斯旯
	WIND_FRONT_WIN				=   (u8)0x07,
	WIND_FRONT_WIN_FEET 	=   (u8)0x0C,	//斯ヶ敦斯褐
	WIND_FRONT_WIN_BODY	    =   (u8)0x0D,	//斯ヶ敦斯旯
	WIND_FRONT_WIN_BODY_FEET	=   (u8)0x0E	//斯ヶ敦斯旯斯褐	
}WIND_MODE_TYPE;

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
	CAN_MAIN_TX_MEDIA_1,
	CAN_MAIN_TX_MEDIA_2,
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

typedef struct
{
	u8 tx_ready;
	u8 tx_line;
	u8 pack_num;
	u8 text_1_len;
	u8 text_1[MAX_MEDIA_ID3_INFO_LENGTH];				//unicode
	u8 text_2_len;
	u8 text_2[MAX_MEDIA_ID3_INFO_LENGTH];
}MEDIA_ID3_INFO;

typedef struct
{
	u8 display;
	u8 on_off;
	u8 ac;
	u8 auto_mode;
	u8 circle;
	u8 dual;
	u8 wind_mode;
	u8 wind_speed;
	u8 right_temperature;
	u8 left_temperature;	
	u8 out_temperature;
#if CAN_FUN_CHERY_TIGGO_3==1
	u8 blow_advance_on;
	u8 blow_delay_off;	
#endif
#if CAN_FUN_CHERY_ARRIZO_6==1
	u8 ac_max;
#endif
}AIR_CONDITION_INFO;

/************************* MCU->APP ***********************/
typedef struct
{
	unsigned f_acc:1;		
	unsigned f_illumi:1;		
	unsigned f_reverse:1;		
	unsigned f_parking:1;	
	unsigned f_light_detect:1;
	unsigned f_reserved_57:3;		
}_CAN_BASE_INFO_BYTE_1;

typedef union
{
	_CAN_BASE_INFO_BYTE_1 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_1;

typedef struct
{	
	CAN_BASE_INFO_BYTE_1 byte_1;
	u8 reserved_2;
	u8 reserved_3;
	u8 reserved_4;
	u8 reserved_5;
	u8 reserved_6;
	u8 swa_msb;
	u8 swa_lsb;
	u8 reserved_9;
	u8 reserved_10;
}CAN_BASE_INFO;

typedef struct
{
	unsigned f_hood:1;		
	unsigned f_reserved_12:2;
	unsigned f_trunk:1;			
	unsigned f_rr_doo:1;
	unsigned f_lr_door:1;
	unsigned f_passenger_door:1;
	unsigned f_driver_door:1;
}_CAN_DETAIL_INFO_BYTE_3;

typedef union
{
	_CAN_DETAIL_INFO_BYTE_3 field;
	u8 byte;
}CAN_DETAIL_INFO_BYTE_3;

typedef struct
{	
	u8 reserved_1;	
	u8 reserved_2;
	CAN_DETAIL_INFO_BYTE_3 byte_3;
	u8 reserved_4;
	u8 reserved_5;
	u8 reserved_6;
	u8 reserved_7;    		
	u8 reserved_8;				
	u8 reserved_9;				
	u8 reserved_10;
}CAN_DETAIL_INFO;

typedef struct
{
	unsigned f_reserved_02:3;
	unsigned f_auto:1;
	unsigned f_reserved_4	:1;
	unsigned f_ac_max:1;	
	unsigned f_on_off	:1;
	unsigned f_disp:1;		
}_CAN_AIR_INFO_BYTE_1;

typedef union
{
	_CAN_AIR_INFO_BYTE_1 field;	
	u8 byte;
}CAN_AIR_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved_01:2;
	unsigned f_dual:1;
	unsigned f_reserved_3	:1;
	unsigned f_circle:1;	
	unsigned f_reserved_5	:1;	
	unsigned f_ac:1;
	unsigned f_reserved_7	:1;		
}_CAN_AIR_INFO_BYTE_2;

typedef union
{
	_CAN_AIR_INFO_BYTE_2 field;	
	u8 byte;
}CAN_AIR_INFO_BYTE_2;

typedef struct
{
	unsigned f_reserved_03:4;
	unsigned f_front_defrost:1;	
	unsigned f_rear_defrost:1;	
	unsigned f_reserved_67:2;	
}_CAN_AIR_INFO_BYTE_3;

typedef union
{
	_CAN_AIR_INFO_BYTE_3 field;	
	u8 byte;
}CAN_AIR_INFO_BYTE_3;

typedef struct
{
	unsigned f_blow_advance_on:1;
	unsigned f_blow_delay_off	:1;		
	unsigned f_filter_change:1;
	unsigned f_reserved_37:5;	
}_CAN_AIR_INFO_BYTE_4;

typedef union
{
	_CAN_AIR_INFO_BYTE_4 field;	
	u8 byte;
}CAN_AIR_INFO_BYTE_4;

typedef struct
{
	CAN_AIR_INFO_BYTE_1 byte_1;				
	CAN_AIR_INFO_BYTE_2 byte_2;
	CAN_AIR_INFO_BYTE_3 byte_3;
	CAN_AIR_INFO_BYTE_4 byte_4;
	u8 wind_mode;	
	u8 wind_speed;	
	u8 left_temperature;	
	u8 right_temperature; 
	u8 reserved_9;				
	u8 reserved_10;
	u8 reserved_11;
	u8 out_temperature;
}CAN_AIR_INFO;

typedef struct
{
	unsigned f_over_speed:1;		
	unsigned f_trajectory:1;			
	unsigned f_3d_around_view:1;			
	unsigned f_side_view:1;
	unsigned f_drl:1;			
	unsigned f_head_light_delay:1;
	unsigned f_auto_lock:1;
	unsigned f_reserved_7	:1;		
}_CAN_CTRL_FEEDBACK_INFO_BYTE_1;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_1 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved_05:6;	
	unsigned f_mirror_auto_fold:1;
	unsigned f_back_light:1;
}_CAN_CTRL_FEEDBACK_INFO_BYTE_2;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_2 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_2;

typedef struct
{
	unsigned f_3d_around_view:1;	
	unsigned f_side_view:1;
	unsigned f_drl:1;		
	unsigned f_head_light_delay:1;
	unsigned f_auto_lock:1;
	unsigned f_remote_lock_feedback:2;
	unsigned F_Urgency_Brake_Warning	:1;
}_CAN_CTRL_FEEDBACK_INFO_BYTE_3;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_3 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_3;

typedef struct
{
	unsigned f_over_speed:5;
	unsigned f_mirror_auto_fold:1;
	unsigned f_trajectory:2;
}_CAN_CTRL_FEEDBACK_INFO_BYTE_4;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_4 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_4;

typedef struct
{
	unsigned f_fg_heat:1; 
	unsigned f_peps_polling:1;  
	unsigned f_peps_intelligent_open:1;
	unsigned f_welcom_light_polling:1;
	unsigned f_instrument_backlight:4;	
}_CAN_CTRL_FEEDBACK_INFO_BYTE_5;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_5 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_5;

typedef struct
{
	unsigned f_ldw_switch:1;  
	unsigned f_ldw_sensitivity:2;  
	unsigned f_reserved_37:5;
}_CAN_CTRL_FEEDBACK_INFO_BYTE_6;

typedef union
{
	_CAN_CTRL_FEEDBACK_INFO_BYTE_6 field;	
	u8 byte;
}CAN_CTRL_FEEDBACK_INFO_BYTE_6;

typedef struct
{



	CAN_CTRL_FEEDBACK_INFO_BYTE_1 enable_flag1;		
	CAN_CTRL_FEEDBACK_INFO_BYTE_2 enable_flag2;	
	CAN_CTRL_FEEDBACK_INFO_BYTE_3 byte_3;	
	CAN_CTRL_FEEDBACK_INFO_BYTE_4 byte_4;	
	CAN_CTRL_FEEDBACK_INFO_BYTE_5 byte_5;
	CAN_CTRL_FEEDBACK_INFO_BYTE_6 byte_6;
	u8 cluster_size;			
	u8 reserved_8;      		
}CAN_CTRL_FEEDBACK_INFO;

typedef struct
{
	u8 avm_exist;					
	u8 reserved_2;				
	u8 right_camera_state;	
	u8 avm_state;		
	u8 left_camera_state;	
	u8 camera_view_state;
	u8 reserved_7;	
}CAN_AVM_INFO;

typedef struct
{
	unsigned f_low_fuel_warning:1;
	unsigned f_reserved17:7;
}_CAN_DRIVE_INFO_BYTE_3;

typedef union
{
	_CAN_DRIVE_INFO_BYTE_3 field;	
	u8 byte;
}CAN_DRIVE_INFO_BYTE_3;

typedef struct
{
	u8 fuel_level;
	u8 average_fuel_consumption;
	CAN_DRIVE_INFO_BYTE_3 byte_3;
	u16 speed;
	u32 total_odometer;
}CAR_DRIVE_INFO;

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
	unsigned f_left_front			:1;
	unsigned f_right_front		:1;
	unsigned f_left_rear			:1;
	unsigned f_right_rear			:1;
}_CAN_TPMS_INO_BYTE_7;

typedef union
{
	_CAN_TPMS_INO_BYTE_7 field;
	u8 byte;
}CAN_TPMS_INO_BYTE_7;

typedef struct
{
	u8 system_fail_status;
	u8 warning_lamp_status;
	u8 left_front_warning;
	u8 right_front_warning;
	u8 left_rear_warning;
	u8 right_rear_warning;
	CAN_TPMS_INO_BYTE_7 byte_7;
	u8 left_front_temperature;
	u8 right_front_temperature;
	u8 left_rear_temperature;
	u8 right_rear_temperature;
	u8 left_front_pressure;
	u8 right_front_pressure;
	u8 left_rear_pressure;
	u8 right_rear_pressure;
}CAN_TPMS_INO;

typedef struct
{
	CAN_AIR_INFO air_info;
	CAN_BASE_INFO base_info;
	CAN_AVM_INFO avm_info;
	CAN_DETAIL_INFO detail_info;
	CAN_CTRL_FEEDBACK_INFO ctrl_feedback_info;
	CAR_DRIVE_INFO drive_info;
	CAN_TIME_INFO time_info;
	CAN_TPMS_INO tpms_info;
}CAN_RX_INFO;

/************************* MCU->CAN BUS ***********************/
#if CAN_FUN_CHERY_ARRIZO_5==1
typedef struct
{
	unsigned f_reserved	:5;	
	unsigned f_remote_lock_feedback:2;
}_CAN_RRM_1_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_1_INFO_BYTE_1 field;
	u8 byte;
}CAN_RRM_1_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved	:4;	
	unsigned f_AidTurningIllumination:2;
	unsigned f_HazardLampForUrgencyBrake:2;
}_CAN_RRM_1_INFO_BYTE_2;

typedef union
{
	_CAN_RRM_1_INFO_BYTE_2 field;
	u8 byte;
}CAN_RRM_1_INFO_BYTE_2;

typedef struct
{
	unsigned f_reserved_01	:2;	
	unsigned f_Display:2;
	unsigned f_DisplayValidData:1;
	unsigned f_reserved_5 :3;
}_CAN_RRM_1_INFO_BYTE_3;

typedef union
{
	_CAN_RRM_1_INFO_BYTE_3 field;
	u8 byte;
}CAN_RRM_1_INFO_BYTE_3;


typedef struct
{
	CAN_RRM_1_INFO_BYTE_1 byte_1;
	CAN_RRM_1_INFO_BYTE_2 byte_2;
	CAN_RRM_1_INFO_BYTE_3 byte_3;
	u8 reserved_4;
}CAN_RRM_1_INFO;

#else
typedef struct
{
	unsigned f_reserved_01	:2;	
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
	unsigned f_head_light_delay:2;
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
	unsigned f_language:5;	
	unsigned f_remote_trunk_only:2;
	unsigned f_reserved_14_15:2;
}_CAN_RRM_1_INFO_BYTE_34;

typedef union
{
	_CAN_RRM_1_INFO_BYTE_34 field;
	u16 word;
}CAN_RRM_1_INFO_BYTE_34;

typedef struct
{
	unsigned f_blind_area_monitoring:2;	
	unsigned f_mirror_auto_fold:2;
	unsigned f_reserved_47:4;	
}_CAN_RRM_1_INFO_BYTE_8;

typedef union
{
	_CAN_RRM_1_INFO_BYTE_8 field;	
	u8 byte;
}CAN_RRM_1_INFO_BYTE_8;

typedef struct
{
	CAN_RRM_1_INFO_BYTE_1 byte_1;
	CAN_RRM_1_INFO_BYTE_2 byte_2;
	CAN_RRM_1_INFO_BYTE_34 byte_34;
	u8 reserved_5;
	u8 reserved_6;
	u8 reserved_7;
	CAN_RRM_1_INFO_BYTE_8 byte_8;
}CAN_RRM_1_INFO;
#endif

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

#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_ARRIZO_6==1||MODEL==LINUX_Q068A_21
typedef struct
{
	unsigned f_year:7;
	unsigned f_month:4;
	unsigned f_day:5;
}_CAN_RRM_3_INFO_BYTE_67;

typedef union
{
	_CAN_RRM_3_INFO_BYTE_67 field;	
	u16 word;
}CAN_RRM_3_INFO_BYTE_67;

typedef struct
{
	u8 hour;
	u8 min;
	u8 instrument_back_light;
	u8 second;
	u8 reserved_5;
	CAN_RRM_3_INFO_BYTE_67 byte_67;
	u8 reserved_8;
}CAN_RRM_3_INFO;
#else
typedef struct
{
	u8 hour;
	u8 min;
	u8 instrument_back_light;
	u8 second;
}CAN_RRM_3_INFO;
#endif

#if CAN_FUN_CHERY_TIGGO_3==1
typedef struct
{
	unsigned f_reserved_0	:1;
	unsigned f_ac:1;
	unsigned f_reserved_27:6;	
}_CAN_RRM_4_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_1 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved_0	:1;
	unsigned f_circle:1;
	unsigned f_reserved_2_13:10;
	unsigned f_air_off:1;
	unsigned f_wind_mode:3;
}_CAN_RRM_4_INFO_BYTE_23;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_23 field;	
	u16 word;
}CAN_RRM_4_INFO_BYTE_23;

typedef struct
{
	unsigned f_reserved_03:4;
	unsigned f_blow_advance_on:2;	
	unsigned f_blow_delay_off	:2;	
}_CAN_RRM_4_INFO_BYTE_6;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_6 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_6;

typedef struct
{
	CAN_RRM_4_INFO_BYTE_1 byte_1;				
	CAN_RRM_4_INFO_BYTE_23 byte_23;
	u8 reserved_4;
	u8 reserved_5;
	CAN_RRM_4_INFO_BYTE_6 byte_6;
	u8 reserved_7;
	u8 reserved_8;
}CAN_RRM_4_INFO;
#elif CAN_FUN_CHERY_ARRIZO_6==1
typedef struct
{
	unsigned f_air_on:1;
	unsigned f_ac:1;
	unsigned f_reserved_2:1;
	unsigned f_wind_speed:3;
	unsigned f_reserved_6:1;
	unsigned f_ac_max:1;
}_CAN_RRM_4_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_1 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved_03:4;
	unsigned f_air_off:1;
	unsigned f_wind_mode:3;	
}_CAN_RRM_4_INFO_BYTE_2;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_2 field;
	u8 byte;
}CAN_RRM_4_INFO_BYTE_2;

typedef struct
{
	unsigned f_reserved_0:1;
	unsigned f_circlen	:1;
	unsigned f_reserved_27:6;	
}_CAN_RRM_4_INFO_BYTE_3;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_3 field;
	u8 byte;
}CAN_RRM_4_INFO_BYTE_3;

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
	CAN_RRM_4_INFO_BYTE_1 byte_1;				
	CAN_RRM_4_INFO_BYTE_2 byte_2;
	CAN_RRM_4_INFO_BYTE_3 byte_3;	
	u8 reserved_4;
	CAN_RRM_4_INFO_BYTE_5 byte_5;
	u8 reserved_6;
}CAN_RRM_4_INFO;
#elif CAN_FUN_CHERY_TIGGO_5==1
typedef struct
{
	unsigned f_air_on:1;
	unsigned f_ac:1;
	unsigned f_reserved_2:1;
	unsigned f_wind_speed:3;
	unsigned f_reserved_67:2;
}_CAN_RRM_4_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_1 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved_0:1;
	unsigned f_circle:1;
	unsigned f_reserved_2_11:10;
	unsigned f_air_off:1;
	unsigned f_wind_mode:3;	
}_CAN_RRM_4_INFO_BYTE_23;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_23 field;
	u16 word;
}CAN_RRM_4_INFO_BYTE_23;

typedef struct
{
	unsigned f_temperature:5;	
	unsigned f_reserved_5_15:11;
}_CAN_RRM_4_INFO_BYTE_45;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_45 field;	
	u16 word;
}CAN_RRM_4_INFO_BYTE_45;

typedef struct
{
	CAN_RRM_4_INFO_BYTE_1 byte_1;				
	CAN_RRM_4_INFO_BYTE_23 byte_23;
	CAN_RRM_4_INFO_BYTE_45 byte_45;	
}CAN_RRM_4_INFO;
#else
typedef struct
{
	unsigned f_air_on:1;
	unsigned f_ac:1;
	unsigned f_auto:1;
	unsigned f_wind_speed:3;
	unsigned f_reserved_67:2;
}_CAN_RRM_4_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_1 field;	
	u8 byte;
}CAN_RRM_4_INFO_BYTE_1;

typedef struct
{
	unsigned f_dual:1;
	unsigned f_circle:1;
	unsigned f_right_temperature_1:5;
	unsigned f_left_temperature_1:5;
	unsigned f_air_off:1;
	unsigned f_wind_mode:3;	
}_CAN_RRM_4_INFO_BYTE_23;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_23 field;
	u16 word;
}CAN_RRM_4_INFO_BYTE_23;

typedef struct
{
	unsigned f_reserved_05:6;
	unsigned f_right_temperature_2:5;
	unsigned f_left_temperature_2:5;
}_CAN_RRM_4_INFO_BYTE_45;

typedef union
{
	_CAN_RRM_4_INFO_BYTE_45 field;	
	u16 word;
}CAN_RRM_4_INFO_BYTE_45;

typedef struct
{
	CAN_RRM_4_INFO_BYTE_1 byte_1;				
	CAN_RRM_4_INFO_BYTE_23 byte_23;
	CAN_RRM_4_INFO_BYTE_45 byte_45;	
}CAN_RRM_4_INFO;
#endif

typedef struct
{
	unsigned f_rrm_display_avm_off:1;
	unsigned f_calibration_req:1;
	unsigned f_reserve_25:4;
	unsigned f_side_view:2;
}_CAN_RRM_6_INFO_BYTE_5;

typedef union
{
	_CAN_RRM_6_INFO_BYTE_5 field;
	u8 byte;
}CAN_RRM_6_INFO_BYTE_5;

typedef struct
{
	unsigned f_reserve_0:1;
	unsigned f_trajectory:3;
	unsigned f_ldw_switch:2;
	unsigned f_3d_around_view:2;
}_CAN_RRM_6_INFO_BYTE_6;

typedef union
{
	_CAN_RRM_6_INFO_BYTE_6 field;
	u8 byte;
}CAN_RRM_6_INFO_BYTE_6;

typedef struct
{
	unsigned f_reserve_03:4;
	unsigned f_touch_event:2;
	unsigned f_ldw_sensitivity:2;
}_CAN_RRM_6_INFO_BYTE_7;

typedef union
{
	_CAN_RRM_6_INFO_BYTE_7 field;
	u8 byte;
}CAN_RRM_6_INFO_BYTE_7;

typedef struct
{
	u8 coordinate_x_h;				
	u8 coordinate_x_l;
	u8 coordinate_y_h;
	u8 coordinate_y_l;
	CAN_RRM_6_INFO_BYTE_5 byte_5;
	CAN_RRM_6_INFO_BYTE_6 byte_6;   
	CAN_RRM_6_INFO_BYTE_7 byte_7;
	u8 reserved_8;
}CAN_RRM_6_INFO;

typedef struct
{
	unsigned f_welcom_light_polling:2;	
	unsigned f_peps_intelligent_open:2;
	unsigned f_peps_polling:2;  	
	unsigned f_reserved_67:2;	
}_CAN_RRM_7_INFO_BYTE_2;

typedef union
{
	_CAN_RRM_7_INFO_BYTE_2 field;	
	u8 byte;
}CAN_RRM_7_INFO_BYTE_2;

typedef struct
{
	unsigned f_fg_heat:2;	
	unsigned f_reserved_27:6;	
}_CAN_RRM_7_INFO_BYTE_8;

typedef union
{
	_CAN_RRM_7_INFO_BYTE_8 field;	
	u8 byte;
}CAN_RRM_7_INFO_BYTE_8;

typedef struct
{
	u8 reserved_1;
	CAN_RRM_7_INFO_BYTE_2 byte_2;
	u8 reserved_3;
	u8 reserved_4;
	u8 reserved_5;
	u8 reserved_6;
	u8 reserved_7;
	CAN_RRM_7_INFO_BYTE_8 byte_8;
}CAN_RRM_7_INFO;

typedef struct
{
	unsigned f_reserved_04:5;	
	unsigned f_remote_lock_feedback:3;
}_CAN_RRM_9_INFO_BYTE_1;

typedef union
{
	_CAN_RRM_9_INFO_BYTE_1 field;	
	u8 byte;
}CAN_RRM_9_INFO_BYTE_1;

typedef struct
{
	unsigned f_head_light_delay:2;
	unsigned f_drl :2;
	unsigned f_reserved_47:4;	
}_CAN_RRM_9_INFO_BYTE_2;

typedef union
{
	_CAN_RRM_9_INFO_BYTE_2 field;
	u8 byte;
}CAN_RRM_9_INFO_BYTE_2;

typedef struct
{
	unsigned f_auto_lock:2;
	unsigned f_reserved_27:6;	
}_CAN_RRM_9_INFO_BYTE_3;

typedef union
{
	_CAN_RRM_9_INFO_BYTE_3 field;
	u8 byte;
}CAN_RRM_9_INFO_BYTE_3;

typedef struct
{
	unsigned f_reserved_01:2;
	unsigned f_mirror_auto_fold:2;
	unsigned f_reserved_47:4;	
}_CAN_RRM_9_INFO_BYTE_8;

typedef union
{
	_CAN_RRM_9_INFO_BYTE_8 field;	
	u8 byte;
}CAN_RRM_9_INFO_BYTE_8;

typedef struct
{
	CAN_RRM_9_INFO_BYTE_1 byte_1;
	CAN_RRM_9_INFO_BYTE_2 byte_2;
	CAN_RRM_9_INFO_BYTE_3 byte_3;
	u8 reserved_4;
	u8 reserved_5;
	u8 reserved_6;
	u8 reserved_7;
	CAN_RRM_9_INFO_BYTE_8 byte_8;
}CAN_RRM_9_INFO;

typedef struct
{
	u8 state;				
	u8 counter;	
}CAN_NMm_RRM_INFO;

typedef struct
{
	CAN_RRM_1_INFO rrm_1_info;
	CAN_RRM_2_INFO rrm_2_info;
	CAN_RRM_3_INFO rrm_3_info;
	CAN_RRM_4_INFO rrm_4_info;
	u8 rrm_5_info[8];
	CAN_RRM_6_INFO rrm_6_info;
	CAN_RRM_7_INFO rrm_7_info;
	CAN_RRM_9_INFO rrm_9_info;
	CAN_NMm_RRM_INFO nmm_rrm_info;
	u8 Msg_Diagnostic[8];
}CAN_TX_INFO;

/***************************************************************/

extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_MAIN_FLAG CanMainFlag;
extern CAN_TX_INFO CanTxInfo;
extern u16 AvmCalibrationTimer;




#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init
#define F_CAN_READY			CanMainFlag.field.f_can_ready
#define F_DRIVER_DOOR_STATE	CanMainFlag.field.f_driver_door
#define F_AVM_CALIBRATION		CanMainFlag.field.f_avm_calibration
#define F_CAN_RX_AIR_INFO		CanMainFlag.field.f_can_rx_air
#define F_CAN_MEDIA_ALLOW       CanMainFlag.field.f_can_media_allow
#define F_CAN_MEDIA_ACK         CanMainFlag.field.f_can_media_ack 

void Tiggo7_MainPro(void);
void Tiggo7_RxAppDataPro(u8 *buffer);
void Tiggo7_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
void Tiggo7_PostMessage(CAN_POST_MESSAGE_INDEX index);


#endif
#endif
