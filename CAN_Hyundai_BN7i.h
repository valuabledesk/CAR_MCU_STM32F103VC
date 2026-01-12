#ifndef _CAN_HYUNDAI_BN7I_H_
#define _CAN_HYUNDAI_BN7I_H_
#if CAN_FUN_HYUNDAI_BN7i==1||CAN_FUN_HYUNDAI_CRETA==1

#define CAN_RX_BUFFER_LENGTH 							400
#define CAN_TX_BUFFER_LENGTH 							100

#define CAN_ID_ECALL_HU_E_01						0x046

#define CAN_ID_TMU_HU_E_01							0x040
#define CAN_ID_MKBD_HU_E_02							0x0B2
#define CAN_ID_MKBD_HU_E_03							0x0B3
#define CAN_ID_HU_TMU_E_01							0x0FA


#define CAN_ID_GW_RVM_PE_00							0x126
#define CAN_ID_ECALL_CLU_PE_01						0x141


#define CAN_ID_GW_CLU_PE							0x158
#define CAN_ID_GW_HU_PE_01							0x15E
#define CAN_ID_GW_CHASSIS_PE_1						0x169
#define CAN_ID_GW_CAR_INFO_PE						0x16A

#define CAN_ID_GW_USM_PE_04							0x17D
#define CAN_ID_GW_HU_PE_06							0x17F
#define CAN_ID_GW_HU_PE_07							0x19D
#define CAN_ID_GW_HU_PE_09							0x19F

#define CAN_ID_CLU_HU_PE_01							0x1DF
#define CAN_ID_DATC_P_02							0x531
#define CAN_ID_GW_CLU_P								0x56E
#define CAN_POST_HU_ECALL_P_00						0x571
#define CAN_POST_HU_Car_PE_01						0x171
#define CAN_POST_HU_Mic_PE_01	  				0x173

#define CAN_ID_GW_HU_P_00							0x59A

#define CAN_ID_HU_RVM_E_00							0x058	
#define HYUNDAI_BN7i_RX_BASE_INO						0x20
#define HYUNDAI_BN7i_RX_EPS_INO						0x21
#define HYUNDAI_BN7i_RX_RADAR_INO					0x22
#define HYUNDAI_BN7i_RX_DRIVING_INO					0x23
#define HYUNDAI_BN7i_RX_AVM_INO						0x24
#define HYUNDAI_BN7i_RX_BATTERY_INO					0x26
#define HYUNDAI_BN7i_RX_GEAR_INO					0x28

#define HYUNDAI_BN7i_TX_AVM_CMD						0x20
#define HYUNDAI_BN7i_RX_ECALL_INO					0x29
#define HYUNDAI_BN7i_TX_ECALL_CMD					0x25
#define HYUNDAI_BN7i_TX_VIN_CMD						0x27



#define HYUNDAI_BN7i_HEAD_CODE						0x2E

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
	AVM_CTRL_CMD_NONE=0x00,
	AVM_CTRL_CMD_OFF=0x01,
	AVM_CTRL_CMD_VIEW_SW=0x02,
	AVM_CTRL_CMD_SELECT_MENU=0x03,
	AVM_CTRL_CMD_GUIDE_LINE=0x04,
	AVM_CTRL_CMD_DRVM=0x05,
	AVM_CTRL_CMD_EXTEND_CAMERA=0x06,
	AVM_CTRL_CMD_NUM
}AVM_CTRL_CMD;
	typedef enum
{
	VIN_CTRL_CMD_NONE=0x00,
	VIN_CTRL_CMD_ON=0x01,
	VIN_CTRL_CMD_AVNT_ON=0x02,
	VIN_CTRL_CMD_SELECT_INDEX=0x03,
	VIN_CTRL_CMD_NUM
}VIN_CTRL_CMD;
	typedef enum
{
	AVM_VIEW_CMD_REAR_VIEW=0x1,
	AVM_VIEW_CMD_REAR_TOP_VIEW=0x2,
	AVM_VIEW_CMD_DRVM_VIEW=0x3,
}AVM_VIEW_CMD;
	typedef enum
{
	ECALL_MODE_CMD_STATUS=0x01,
	ECALL_MODE_CMD_WARNING=0x02,
	ECALL_MODE_CMD_VER=0x03,
	ECALL_MODE_CMD_MIC=0x04,
	ECALL_MODE_CMD_ARM=0x05,
	ECALL_MODE_CMD_NUM
}ECALL_MODE_CMD;
typedef enum
{
	CAN_POST_MSG_NONE=0,
	CAN_POST_MSG_HU_RVM_E_00,
	CAN_POST_MSG_HU_RVM_E2_00,
	CAN_POST_MSG_HU_ECALL_E_00,
	CAN_POST_MSG_HU_ECALL_W_00,
	CAN_POST_MSG_HU_ECALL_S_00,
	CAN_POST_MSG_HU_ECALL_V_00,
	CAN_POST_MSG_HU_ECALL_C_00,
	CAN_POST_MSG_MAX_INDEX
}CAN_POST_MESSAGE_INDEX;

typedef enum
{
	AUTO_LIGHT_DAY=0,
	AUTO_LIGHT_EVENING=1,
	AUTO_LIGHT_NIGHT=2,
	AUTO_LIGHT_MAX
}AUTO_LIGHT_SENSOR;
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
	unsigned f_tgs_gear_at:4;
	unsigned f_gear:4;	
}_CAN_GEAR_BYTE_0;

typedef union
{
	_CAN_GEAR_BYTE_0 field;
	u8 byte;
}CAN_GEAR_BYTE_0;

typedef struct
{	
	unsigned f_tgs_r_mt:2;		
	unsigned f_ems_r_mt:1;	
	unsigned f_parking_brake:2;
	unsigned f_parking_brake_epb:3;	
}_CAN_GEAR_BYTE_1;

typedef union
{
	_CAN_GEAR_BYTE_1 field;
	u8 byte;
}CAN_GEAR_BYTE_1;

typedef struct
{	
	CAN_GEAR_BYTE_0 byte_0;
	CAN_GEAR_BYTE_1 byte_1;
}CAN_GEAR_INFO;

typedef struct
{
	unsigned f_acc:1;		
	unsigned f_illumi:1;		
	unsigned f_reverse:1;		
	unsigned f_parking:1;	
	unsigned f_light_detect:2;
	unsigned f_reserved_67:4;	
}_CAN_BASE_INFO_BYTE_0;

typedef struct
{
	unsigned f_battery_low:2;
}_CAN_BATTERY_INFO_BYTE_0;
typedef union
{
	_CAN_BATTERY_INFO_BYTE_0 field;
	u8 byte;
}CAN_BATTERY_INFO_BYTE_0;
typedef struct
{
	unsigned f_battery_eng:3;
}_CAN_BATTERY_INFO_BYTE_1;
typedef union
{
	_CAN_BATTERY_INFO_BYTE_1 field;
	u8 byte;
}CAN_BATTERY_INFO_BYTE_1;


typedef union
{
	_CAN_BASE_INFO_BYTE_0 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_0;

typedef struct
{
	unsigned f_hood:1;		
	unsigned f_trunk:1;			
	unsigned f_rr_door:1;
	unsigned f_lr_door:1;
	unsigned f_passenger_door:1;
	unsigned f_driver_door:1;
	unsigned f_reserved_67:2;	
}_CAN_BASE_INFO_BYTE_1;

typedef union
{
	_CAN_BASE_INFO_BYTE_1 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_1;

typedef struct
{
	unsigned f_av_tail:2;		
	unsigned f_auto_light_sensor_state:1;
	unsigned f_reserved_37:5;	
}_CAN_BASE_INFO_BYTE_2;

typedef union
{
	_CAN_BASE_INFO_BYTE_2 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_2;

typedef struct
{	
	CAN_BASE_INFO_BYTE_0 byte_0;
	CAN_BASE_INFO_BYTE_1 byte_1;
	CAN_BASE_INFO_BYTE_2 byte_2;
}CAN_BASE_INFO;

typedef struct
{	
	CAN_BATTERY_INFO_BYTE_0 byte_0;
	CAN_BATTERY_INFO_BYTE_1 byte_1;
}CAN_BATTERY_INFO;

typedef struct
{	
	u8 vol_knob_value;
	u8 tune_knob_value;
	u8 knob_rotate_counter;
	u8 vol_knob_click;
	u8 tune_knob_click;
	u8 reset_key;
}CAN_KNOB_INFO;

typedef struct
{
	unsigned f_map_key:2;		
	unsigned f_navi_key:1;			
	unsigned f_radio_key:1;
	unsigned f_media_key:1;
}_CAN_PANEL_BYTE_0;

typedef union
{
	_CAN_PANEL_BYTE_0 field;
	u8 byte;
}CAN_PANEL_BYTE_0;

typedef struct
{
	unsigned f_skipb_key:2;		
	unsigned f_skipf_key:1;			
	unsigned f_custom_key:1;
	unsigned f_setup_key:1;
}_CAN_PANEL_BYTE_1;

typedef union
{
	_CAN_PANEL_BYTE_1 field;
	u8 byte;
}CAN_PANEL_BYTE_1;

typedef struct
{	
	CAN_PANEL_BYTE_0 byte_0;
	CAN_PANEL_BYTE_1 byte_1;
}CAN_PANEL_KEY_INFO;

typedef struct
{	
	u8 front_left;
	u8 front_right;
	u8 front_center;
	u8 rear_left;
	u8 rear_right;
	u8 rear_center;
}CAN_RADAR_INFO;

typedef struct
{	
	u8 swa_msb;
	u8 swa_lsb;
}CAN_EPS_INFO;

typedef struct
{
	u32 odometer;
	u16 cluster_speed;
	u16 cluster_disp_speed;
	u8 cluster_disp_speed_unit;
	u8 vehicle_speed;
}CAN_DRIVING_INFO;

typedef struct
{
	u16 red_value;
	u16 green_value;
	u16 blue_value;
	u8 brightness;
}CAN_MOOD_LAMP_INFO;
typedef struct
{
	u8 rvm_mode;
	u8 rvm_type;
	u8 rvm_guide_line;
	u8 rvm_state;
	u8 rvm_drv_state;
	
	
}CAN_AVM_INFO;
typedef struct
{
	unsigned ecall_mode:3;
	
	
}_CAN_ECALL_BYTE_0;

typedef union
{
	_CAN_ECALL_BYTE_0 field;
	u8 byte;
}CAN_ECALL_BYTE_0;

typedef struct
{
	
	unsigned ecall_fail:1;

}_CAN_ECALL_BYTE_2;

typedef union
{
	_CAN_ECALL_BYTE_2 field;
	u8 byte;
}CAN_ECALL_BYTE_2;

typedef struct
{
	
	unsigned ecall_warning:1;
	
}_CAN_ECALL_BYTE_1;
typedef union
{
	_CAN_ECALL_BYTE_1 field;
	u8 byte;
}CAN_ECALL_BYTE_1;


typedef struct
{	
	CAN_ECALL_BYTE_0 byte_0;
	CAN_ECALL_BYTE_1 byte_1;
	CAN_ECALL_BYTE_2 byte_2;
}CAN_ECALL_INFO;










typedef struct
{
	CAN_KNOB_INFO knob_info;
	CAN_KNOB_INFO knob_info_bak;
	CAN_PANEL_KEY_INFO panel_key_info;
	CAN_PANEL_KEY_INFO panel_key_info_bak;
	CAN_BASE_INFO base_info;
	CAN_BASE_INFO base_info_bak;
	CAN_GEAR_INFO gear_info;
	CAN_GEAR_INFO gear_info_bak;
	CAN_RADAR_INFO radar_info;
	CAN_RADAR_INFO radar_info_bak;
	CAN_EPS_INFO eps_info;
	CAN_EPS_INFO eps_info_bak;
	CAN_DRIVING_INFO driving_info;
	CAN_DRIVING_INFO driving_info_bak;
	CAN_MOOD_LAMP_INFO mood_lamp_info;
	CAN_AVM_INFO avm_info;
	CAN_AVM_INFO avm_info_bak;
	CAN_ECALL_INFO ecall_info;
	CAN_ECALL_INFO ecall_info_bak;
	CAN_BATTERY_INFO battery_info;
	CAN_BATTERY_INFO battery_info_bak;
	u8 brightness;
}CAN_RX_INFO;

typedef struct
{
	unsigned f_camera_off:2;
	unsigned f_view_sw:2;
	unsigned f_reserved_47:4;	
}_CAN_HU_RVM_E_00_BYTE_0;
typedef struct
{
	unsigned f_select_menu:6;
	unsigned f_guide_line:2;
}_CAN_HU_RVM_E_00_BYTE_1;
typedef union
{
	_CAN_HU_RVM_E_00_BYTE_0 field;
	u8 byte;
}CAN_HU_RVM_E_00_BYTE_0;
typedef union
{
	_CAN_HU_RVM_E_00_BYTE_1 field;
	u8 byte;
}CAN_HU_RVM_E_00_BYTE_1;
typedef struct
{
	CAN_HU_RVM_E_00_BYTE_0 byte_0;
	CAN_HU_RVM_E_00_BYTE_1 byte_1;
}CAN_HU_RVM_E_00;
typedef struct
{
	unsigned f_mode:3;
	unsigned f_warning:2;
	
	
	
}_CAN_HU_ECALL_E_00_BYTE_0;
typedef struct
{
	unsigned f_status:2;
	unsigned f_arm:3;
}_CAN_HU_ECALL_E_00_BYTE_1;

typedef struct
{
	unsigned f_vin_index:2;
	unsigned f_vin_status:2;
	unsigned f_avnt_option:2;	
}_CAN_HU_ECALL_E_00_BYTE_2;

typedef union
{
	_CAN_HU_ECALL_E_00_BYTE_0 field;
	u8 byte;
}CAN_HU_ECALL_E_00_BYTE_0;
typedef union
{
	_CAN_HU_ECALL_E_00_BYTE_1 field;
	u8 byte;
}CAN_HU_ECALL_E_00_BYTE_1;

typedef union
{
	_CAN_HU_ECALL_E_00_BYTE_2 field;
	u8 byte;
}CAN_HU_ECALL_E_00_BYTE_2;

typedef struct
{
	CAN_HU_ECALL_E_00_BYTE_0 byte_0;
	CAN_HU_ECALL_E_00_BYTE_1 byte_1;
	CAN_HU_ECALL_E_00_BYTE_2 byte_2;
}CAN_HU_ECALL_E_00;

typedef struct
{
	CAN_HU_RVM_E_00 hu_rvm_e_00;
	CAN_HU_ECALL_E_00 hu_ecall_e_00;
}CAN_TX_INFO;
extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_TX_INFO CanTxInfo;
extern CAN_MAIN_FLAG CanMainFlag;

extern u8 FLAG_Panel_LED;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init

void Hyundai_BN7i_MainPro(void);
void Hyundai_BN7i_RxAppDataPro(u8 *buffer);
void Hyundai_BN7i_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);

#endif
#endif
