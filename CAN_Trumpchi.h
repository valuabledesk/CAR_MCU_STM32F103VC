#ifndef _CAN_Trumpchi_H_
#define _CAN_Trumpchi_H_
#if CAN_FUN_TRUMPCHI==1

#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		100

/*************** Receive ID********************/
#define CAN_ID_PANEL_1					0x259	
#define CAN_ID_LIGHT_1					0x310
#define CAN_ID_GW_MRR_1_B				0x312
#define CAN_ID_BCM_BCAN_1				0x318
#define CAN_ID_BCM_BCAN_2				0x25D
#define CAN_ID_BCM_BCAN_4				0x31C
#define CAN_ID_HVACF_1					0x320
#define CAN_ID_HVACF_3					0x31D
#define CAN_ID_PEPS_6						0x31F
#define CAN_ID_ICM_1_B					0x34B
#define CAN_ID_ICM_3_B					0x352
#define CAN_ID_ICM_4_B					0x31E
#define CAN_ID_GW_SAS_1_B				0x33D
#define CAN_ID_MSM_1						0x341
#define CAN_ID_PAS_1						0x343
#define CAN_ID_PAS_2						0x347
#define CAN_ID_PCS_1						0x344
#define CAN_ID_GW_EPS_1_B				0x348
#define CAN_ID_HVSM_1					0x34E
#define CAN_ID_FCP_3						0x355
#define CAN_ID_FCP_5						0x35B
#define CAN_ID_IFC_1						0x3A3
#define CAN_ID_BSD_1						0x3A4
#define CAN_ID_WCM_1						0x3B5
#define CAN_ID_GW_1_B					0x3C8
/*************** Transmit ID********************/
#define CAN_ID_ACU_1_A					0x054
#define CAN_ID_ACU_2_A					0x082
#define CAN_ID_ACU_3_A					0x083
#define CAN_ID_ACU_2_B					0x03D
#define CAN_ID_ACU_4_B					0x03E
#define CAN_ID_ACU_5_B					0x081
#define CAN_ID_ACU_10_B					0x35A
#define CAN_ID_ACU_11_B					0x3C5
#define CAN_ID_ACU_16_B					0x3D2
#define CAN_ID_ACU_17_B					0x037
#define CAN_ID_ACU_HVAC_1_B				0x3F6
/***************APP Cmd***********************/
#define TRUMPCHI_RX_AIR_INFO								0x10
#define TRUMPCHI_RX_BACKLIGHT								0x14
#define TRUMPCHI_RX_BASIC_INFO								0x24
#define TRUMPCHI_RX_EPS_INFO								0x31
#define TRUMPCHI_RX_REAR_RADAR								0x32
#define TRUMPCHI_RX_FRONT_RADAR							0x33
#define TRUMPCHI_RX_SETTING_1								0x52
#define TRUMPCHI_RX_ACK										0xFF
#define TRUMPCHI_RX_NACK_ERR_CHECKSUM					0xF0
#define TRUMPCHI_RX_NACK_NO_SUPPORT						0xF3
#define TRUMPCHI_RX_NACK_BUSY								0xFC

#define TRUMPCHI_TX_AVM_KEY								0x82
#define TRUMPCHI_TX_SETTING_CMD_1							0x83
#define TRUMPCHI_TX_AVM_ON_OFF							0x84
#define TRUMPCHI_TX_SETTING_CMD_2							0x85
#define TRUMPCHI_TX_COMPASS_INFO							0x86
#define TRUMPCHI_TX_SETTING_CMD_3							0x88
#define TRUMPCHI_TX_REQUEST_CMD							0x90
#define TRUMPCHI_TX_AVM_SWITCH							0xA7
#define TRUMPCHI_TX_AIR_CMD								0xA8
#define TRUMPCHI_TX_SETTING_CMD_4							0xA9
#define TRUMPCHI_TX_MEDIA_INFO								0xC0
#define TRUMPCHI_TX_AVM_CMD_1								0xC7
#define TRUMPCHI_TX_TIME_CMD								0xC8
#define TRUMPCHI_TX_AVM_CMD_2								0xC9

#define Trumpchi_HEAD_CODE					0x2E

#define TEST_AIR_KEY_TIME		T100MS_1

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
	CAN_POST_MSG_ACU_0,
	CAN_POST_MSG_ACU_1,
	CAN_POST_MSG_ACU_2,
	CAN_POST_MSG_ACU_3,
	CAN_POST_MSG_ACU_4,
	CAN_POST_MSG_ACU_5,
	CAN_POST_MSG_ACU_6,
	CAN_POST_MSG_ACU_7,
	CAN_POST_MSG_ACU_8,
	CAN_POST_MSG_ACU_9,
	CAN_POST_MSG_ACU_10,
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
	unsigned f_reserved:8;
}_CAN_AIR_INFO_BYTE_0;

typedef union
{
	_CAN_AIR_INFO_BYTE_0 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_0;

typedef struct
{	
	unsigned f_AC:1;
	unsigned f_ION:1;
	unsigned f_AUTO:1;
	unsigned f_wind_exit_mode:3;
	unsigned f_rear_defrost:1;
	unsigned f_display_request:1;
}_CAN_AIR_INFO_BYTE_1;

typedef union
{
	_CAN_AIR_INFO_BYTE_1 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_1;

typedef struct
{	
	unsigned f_fan_speed:3;
	unsigned f_internal_external_circulation:2;
	unsigned f_3zone:1;
	unsigned f_dual:1;
	unsigned f_ac_max:1;
}_CAN_AIR_INFO_BYTE_2;

typedef union
{
	_CAN_AIR_INFO_BYTE_2 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_2;

typedef struct
{	
	unsigned f_left_temperature:8;
}_CAN_AIR_INFO_BYTE_3;

typedef union
{
	_CAN_AIR_INFO_BYTE_3 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_3;

typedef struct
{	
	unsigned f_right_temperature:8;
}_CAN_AIR_INFO_BYTE_4;

typedef union
{
	_CAN_AIR_INFO_BYTE_4 field;
	u8 byte;
}CAN_AIR_INFO_BYTE_4;

typedef struct
{	
	CAN_AIR_INFO_BYTE_0 byte_0;
	CAN_AIR_INFO_BYTE_1 byte_1;
	CAN_AIR_INFO_BYTE_2 byte_2;
	CAN_AIR_INFO_BYTE_3 byte_3;
	CAN_AIR_INFO_BYTE_4 byte_4;
}CAN_AIR_INFO;

typedef struct
{
	unsigned f_level:3;
	unsigned f_reserved:5;
}CAN_BACKLIGHT_INFO;

typedef struct
{
	unsigned f_front_cover:1;
	unsigned f_trunk:1;
	unsigned f_left_rear_door:1;
	unsigned f_right_rear_door:1;
	unsigned f_left_front_door:1;
	unsigned f_right_front_door:1;
	unsigned f_reserved:2;
}_CAN_BASE_INFO_BYTE_0;

typedef union
{
	_CAN_BASE_INFO_BYTE_0 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_0;

typedef struct
{
	unsigned f_reverse_status:1;
	unsigned f_parking_status:1;
	unsigned f_left_signal_status:1;
	unsigned f_right_signal_status:1;
	unsigned f_illumi_status:1;
	unsigned f_display:1;
	unsigned f_reserved:2;
}_CAN_BASE_INFO_BYTE_1;

typedef union
{
	_CAN_BASE_INFO_BYTE_1 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_1;

typedef struct
{
	CAN_BASE_INFO_BYTE_0 byte_0;
	CAN_BASE_INFO_BYTE_1 byte_1;
}CAN_BASE_INFO;

typedef struct
{
	unsigned f_steer_wheel_angle_msb:8;
}_CAN_EPS_INFO_BYTE_0;

typedef union
{
	_CAN_EPS_INFO_BYTE_0 field;
	u8 byte;
}CAN_EPS_INFO_BYTE_0;

typedef struct
{
	unsigned f_steer_wheel_angle_lsb:8;
}_CAN_EPS_INFO_BYTE_1;

typedef union
{
	_CAN_EPS_INFO_BYTE_1 field;
	u8 byte;
}CAN_EPS_INFO_BYTE_1;

typedef struct
{
	CAN_EPS_INFO_BYTE_0 byte_0;
	CAN_EPS_INFO_BYTE_1 byte_1;
}CAN_EPS_INFO;

typedef struct
{
	unsigned f_reserved:1;
	unsigned f_sensor_voice:4;
	unsigned f_sensor_mode:3;
}_CAN_REAR_RADAR_INFO_BYTE_0;

typedef union
{
	_CAN_REAR_RADAR_INFO_BYTE_0 field;
	u8 byte;
}CAN_REAR_RADAR_INFO_BYTE_0;

typedef struct
{
	unsigned f_rear_left_sensor:8;
}_CAN_REAR_RADAR_INFO_BYTE_1;

typedef union
{
	_CAN_REAR_RADAR_INFO_BYTE_1 field;
	u8 byte;
}CAN_REAR_RADAR_INFO_BYTE_1;

typedef struct
{
	unsigned f_rear_left_middle_sensor:8;
}_CAN_REAR_RADAR_INFO_BYTE_2;

typedef union
{
	_CAN_REAR_RADAR_INFO_BYTE_2 field;
	u8 byte;
}CAN_REAR_RADAR_INFO_BYTE_2;

typedef struct
{
	unsigned f_rear_right_middle_sensor:8;
}_CAN_REAR_RADAR_INFO_BYTE_3;

typedef union
{
	_CAN_REAR_RADAR_INFO_BYTE_3 field;
	u8 byte;
}CAN_REAR_RADAR_INFO_BYTE_3;

typedef struct
{
	unsigned f_rear_right_sensor:8;
}_CAN_REAR_RADAR_INFO_BYTE_4;

typedef union
{
	_CAN_REAR_RADAR_INFO_BYTE_4 field;
	u8 byte;
}CAN_REAR_RADAR_INFO_BYTE_4;

typedef struct
{
	CAN_REAR_RADAR_INFO_BYTE_0 byte_0;
	CAN_REAR_RADAR_INFO_BYTE_1 byte_1;
	CAN_REAR_RADAR_INFO_BYTE_2 byte_2;
	CAN_REAR_RADAR_INFO_BYTE_3 byte_3;
	CAN_REAR_RADAR_INFO_BYTE_4 byte_4;
}CAN_REAR_RADAR_INFO;

typedef struct
{
	unsigned f_front_right_sensor:8;
}_CAN_FRONT_RADAR_INFO_BYTE_0;

typedef union
{
	_CAN_FRONT_RADAR_INFO_BYTE_0 field;
	u8 byte;
}CAN_FRONT_RADAR_INFO_BYTE_0;

typedef struct
{
	unsigned f_front_left_sensor:8;
}_CAN_FRONT_RADAR_INFO_BYTE_1;

typedef union
{
	_CAN_FRONT_RADAR_INFO_BYTE_1 field;
	u8 byte;
}CAN_FRONT_RADAR_INFO_BYTE_1;

typedef struct
{
	CAN_FRONT_RADAR_INFO_BYTE_0 byte_0;
	CAN_FRONT_RADAR_INFO_BYTE_1 byte_1;
}CAN_FRONT_RADAR_INFO;

typedef struct
{
	unsigned f_reserved:8;
}CAN_NEW_ENERGY_SETTING_INFO;

typedef struct
{
	unsigned f_reserved:8;
}CAN_CONTROL_INFO;

typedef struct
{	
	unsigned f_remote_unlock:2;
	unsigned f_auto_door_unlock:2;
	unsigned f_automatically_lock:2;
	unsigned f_automatically_unlock:2;
}_CAN_SETTING_INFO_BYTE_0;

typedef union
{
	_CAN_SETTING_INFO_BYTE_0 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_0;

typedef struct
{	
	unsigned f_smart_trunk:2;
	unsigned f_light_to_home:2;
	unsigned f_fog_light_for_turning:2;
	unsigned reserved:2;
}_CAN_SETTING_INFO_BYTE_1;

typedef union
{
	_CAN_SETTING_INFO_BYTE_1 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_1;

typedef struct
{
	unsigned f_rear_view_mirro_flip_position_setting:2;	
	unsigned f_outside_rear_view_mirro_auto_floding:2;	
	unsigned f_lock_unlock_whistle_remind:2;
	unsigned f_remote_control_window_sunroof:2;
}_CAN_SETTING_INFO_BYTE_2;

typedef union
{
	_CAN_SETTING_INFO_BYTE_2 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_2;

typedef struct
{	
	unsigned f_wireless_charge:2;
	unsigned f_blind_spot_detection:2;
	unsigned f_manual_rear_view_mirro_flip_of_reversing:2;
	unsigned f_wireless_charge_state:2;
}_CAN_SETTING_INFO_BYTE_3;

typedef union
{
	_CAN_SETTING_INFO_BYTE_3 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_3;

typedef struct
{	
	unsigned f_cruise_mode:2;
	unsigned f_lane_assist_mode:2;
	unsigned f_forward_collision_warning:2;
	unsigned f_head_light_for_daytime:2;
}_CAN_SETTING_INFO_BYTE_4;

typedef union
{
	_CAN_SETTING_INFO_BYTE_4 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_4;

typedef struct
{	
	unsigned f_forward_collision_warning_distance:2;
	unsigned f_autonomous_emergency_braking:2;
	unsigned f_steering_mode:2;
	unsigned f_smart_high_beam:2;
}_CAN_SETTING_INFO_BYTE_5;

typedef union
{
	_CAN_SETTING_INFO_BYTE_5 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_5;


typedef struct
{	
	unsigned f_smart_welcome_light:2;
	unsigned f_interior_ambient_light:2;
	unsigned f_auto_light_sensitivity:3;
	unsigned f_forward_collision_warning_button:1;
}_CAN_SETTING_INFO_BYTE_6;

typedef union
{
	_CAN_SETTING_INFO_BYTE_6 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_6;

typedef struct
{	
	unsigned f_speed_warning:5;
	unsigned f_warning_sound_volume:2;
}_CAN_SETTING_INFO_BYTE_7;

typedef union
{
	_CAN_SETTING_INFO_BYTE_7 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_7;

typedef struct
{	
	unsigned f_time_remote_electricity_on:6;
	unsigned f_transport_mode:2;
}_CAN_SETTING_INFO_BYTE_8;

typedef union
{
	_CAN_SETTING_INFO_BYTE_8 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_8;

typedef struct
{	
	unsigned f_time_remote_power_on:6;
	unsigned f_auto_wiper:2;
}_CAN_SETTING_INFO_BYTE_9;

typedef union
{
	_CAN_SETTING_INFO_BYTE_9 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_9;

typedef struct
{	
	unsigned f_wiper_maintanence:2;
	unsigned f_auto_rear_wipe_function:2;
	unsigned f_lane_assist:2;
}_CAN_SETTING_INFO_BYTE_10;

typedef union
{
	_CAN_SETTING_INFO_BYTE_10 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_10;

typedef struct
{	
	unsigned f_instantaneous_speed:8;
}_CAN_SETTING_INFO_BYTE_11;

typedef union
{
	_CAN_SETTING_INFO_BYTE_11 field;
	u8 byte;
}CAN_SETTING_INFO_BYTE_11;

typedef struct
{	
	CAN_SETTING_INFO_BYTE_0 byte_0;
	CAN_SETTING_INFO_BYTE_1 byte_1;
	CAN_SETTING_INFO_BYTE_2 byte_2;
	CAN_SETTING_INFO_BYTE_3 byte_3;
	CAN_SETTING_INFO_BYTE_4 byte_4;
	CAN_SETTING_INFO_BYTE_5 byte_5;
	CAN_SETTING_INFO_BYTE_6 byte_6;
	CAN_SETTING_INFO_BYTE_7 byte_7;
	CAN_SETTING_INFO_BYTE_8 byte_8;
	CAN_SETTING_INFO_BYTE_9 byte_9;
	CAN_SETTING_INFO_BYTE_10 byte_10;
	CAN_SETTING_INFO_BYTE_11 byte_11;
}CAN_SETTING_INFO;

typedef struct
{
	unsigned f_fan_speed_of_auto_mode:2;	
	unsigned f_frs_rec_auto_mode:2;
	unsigned	f_comfort_curve:2;
	unsigned f_pm2:2;
}_CAN_AIR_CONDITIONING_INFO_BYTE_0;

typedef union
{
	_CAN_AIR_CONDITIONING_INFO_BYTE_0 filed;
	u8 byte;
}CAN_AIR_CONDITIONING_INFO_BYTE_0;

typedef struct
{
	unsigned f_pm5:8;	
}_CAN_AIR_CONDITIONING_INFO_BYTE_1;

typedef union
{
	_CAN_AIR_CONDITIONING_INFO_BYTE_1 filed;
	u8 byte;
}CAN_AIR_CONDITIONING_INFO_BYTE_1;

typedef struct
{
	unsigned f_compressor_status:2;	
}_CAN_AIR_CONDITIONING_INFO_BYTE_2;

typedef union
{
	_CAN_AIR_CONDITIONING_INFO_BYTE_2 filed;
	u8 byte;
}CAN_AIR_CONDITIONING_INFO_BYTE_2;

typedef struct
{
	CAN_AIR_CONDITIONING_INFO_BYTE_0 byte_0;
	CAN_AIR_CONDITIONING_INFO_BYTE_1 byte_1;
	CAN_AIR_CONDITIONING_INFO_BYTE_2 byte_2;
}CAN_AIR_CONDITIONING_INFO;

typedef struct
{
	unsigned f_seat_welcome_function:2;
	unsigned f_key_recognition:2;
	unsigned f_front_left_seat_heating_ventilating_auto_mode:2;
	unsigned f_front_right_seat_heating_ventilating_auto_mode:2;
}CAN_SEAT_SETTING_INFO;

typedef struct
{
	CAN_AIR_INFO air_info;
	CAN_BACKLIGHT_INFO backlight_info;
	CAN_BASE_INFO base_info;
	CAN_EPS_INFO eps_info;
	CAN_REAR_RADAR_INFO rear_radar_info;
	CAN_FRONT_RADAR_INFO front_radar_info;
	CAN_NEW_ENERGY_SETTING_INFO new_energy_setting_info;
	CAN_CONTROL_INFO control_info;
	CAN_SETTING_INFO setting_info;
	CAN_AIR_CONDITIONING_INFO air_canditioning_info;
	CAN_SEAT_SETTING_INFO seat_setting_info;
}CAN_RX_INFO;

typedef struct
{
	unsigned f_reserved_03:4;
	unsigned f_screen_touch_status:2;
	unsigned f_reserved:2;
}_CAN_ACU_1_A_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_1_A_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_1_A_INFO_BYTE_2;

typedef struct
{
	unsigned f_y:8;
}_CAN_ACU_1_A_INFO_BYTE_3;

typedef union
{
	_CAN_ACU_1_A_INFO_BYTE_3 field;
	u8 byte;
}CAN_ACU_1_A_INFO_BYTE_3;

typedef struct
{
	unsigned f_x_1:4;
	unsigned f_y_1:4;
}_CAN_ACU_1_A_INFO_BYTE_4;

typedef union
{
	_CAN_ACU_1_A_INFO_BYTE_4 field;
	u8 byte;
}CAN_ACU_1_A_INFO_BYTE_4;

typedef struct
{
	unsigned f_x:8;
}_CAN_ACU_1_A_INFO_BYTE_5;

typedef union
{
	_CAN_ACU_1_A_INFO_BYTE_5 field;
	u8 byte;
}CAN_ACU_1_A_INFO_BYTE_5;

typedef struct
{
	u8 reserved_0;
	u8 reserved_1;
	CAN_ACU_1_A_INFO_BYTE_2 byte_2;
	CAN_ACU_1_A_INFO_BYTE_3 byte_3;
	CAN_ACU_1_A_INFO_BYTE_4 byte_4;
	CAN_ACU_1_A_INFO_BYTE_5 byte_5;
	u8 reserved_6;
}CAN_ACU_1_A_INFO;

typedef struct
{
	unsigned f_lane_assist:2;
	unsigned f_reserved:6;
}_CAN_ACU_2_A_INFO_BYTE_0;

typedef union
{
	_CAN_ACU_2_A_INFO_BYTE_0 field;
	u8 byte;
}CAN_ACU_2_A_INFO_BYTE_0;

typedef struct
{
	unsigned f_cruise_mode:2;
	unsigned f_reserved:4;
	unsigned f_smart_high_beam:2;
}_CAN_ACU_2_A_INFO_BYTE_1;

typedef union
{
	_CAN_ACU_2_A_INFO_BYTE_1 field;
	u8 byte;
}CAN_ACU_2_A_INFO_BYTE_1;

typedef struct
{
	unsigned f_lane_assist_mode:2;
	unsigned f_reserved:6;
}_CAN_ACU_2_A_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_2_A_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_2_A_INFO_BYTE_2;

typedef struct
{
	unsigned f_reserved_0:2;
	unsigned f_rcta_switch:2;
	unsigned f_dow_switch:2;
	unsigned f_reserved:2;
}_CAN_ACU_2_A_INFO_BYTE_5;

typedef union
{
	_CAN_ACU_2_A_INFO_BYTE_5 field;
	u8 byte;
}CAN_ACU_2_A_INFO_BYTE_5;

typedef struct
{
	CAN_ACU_2_A_INFO_BYTE_0 byte_0;
	CAN_ACU_2_A_INFO_BYTE_1 byte_1;
	CAN_ACU_2_A_INFO_BYTE_2 byte_2;
	u8 reserved_3;
	u8 reserved_4;
	CAN_ACU_2_A_INFO_BYTE_5 byte_5;
}CAN_ACU_2_A_INFO;

typedef struct
{
	unsigned f_reserved:3;
	unsigned f_wcm_status:2;
	unsigned f_bsd_switch:2;
	unsigned f_reserved_7:1;
}_CAN_ACU_3_A_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_3_A_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_3_A_INFO_BYTE_2;

typedef struct
{
	u8 reserved_0;
	u8 reserved_1;
	CAN_ACU_3_A_INFO_BYTE_2 byte_2;
}CAN_ACU_3_A_INFO;

typedef struct
{
	unsigned f_compressor_status:2;
	unsigned f_frs_rec_auto_mode:2;
	unsigned f_comfort_curve:2;
	unsigned f_ion_mode:2;
}_CAN_ACU_2_B_INFO_BYTE_0;

typedef union
{
	_CAN_ACU_2_B_INFO_BYTE_0 field;
	u8 byte;
}CAN_ACU_2_B_INFO_BYTE_0;

typedef struct
{
	unsigned f_main_driver_auto_heat:2;
	unsigned f_co_drive_auto_heat:2;
	unsigned f_reserved:4;
}_CAN_ACU_2_B_INFO_BYTE_1;

typedef union
{
	_CAN_ACU_2_B_INFO_BYTE_1 field;
	u8 byte;
}CAN_ACU_2_B_INFO_BYTE_1;

typedef struct
{
	unsigned f_seat_welcome_function:2;
	unsigned f_key_recognition:2;
	unsigned f_outside_rear_view_mirro_auto_floding:2;
	unsigned f_smart_welcome_light:2;
}_CAN_ACU_2_B_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_2_B_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_2_B_INFO_BYTE_2;

typedef struct
{
	unsigned f_smart_trunk:2;
	unsigned f_air_quality_sensor:2;
	unsigned f_reserved:4;
}_CAN_ACU_2_B_INFO_BYTE_3;

typedef union
{
	_CAN_ACU_2_B_INFO_BYTE_3 field;
	u8 byte;
}CAN_ACU_2_B_INFO_BYTE_3;

typedef struct
{
	unsigned f_speed_warning:5;
	unsigned f_warning_sound_volume:2;
	unsigned f_reserved:1;
}_CAN_ACU_2_B_INFO_BYTE_4;

typedef union
{
	_CAN_ACU_2_B_INFO_BYTE_4 field;
	u8 byte;
}CAN_ACU_2_B_INFO_BYTE_4;

typedef struct
{
	unsigned f_time_mode:2;
	unsigned f_reserved:2;
	unsigned f_automatically_lock:2;
	unsigned f_automatically_unlock:2;
}_CAN_ACU_2_B_INFO_BYTE_5;

typedef union
{
	_CAN_ACU_2_B_INFO_BYTE_5 field;
	u8 byte;
}CAN_ACU_2_B_INFO_BYTE_5;

typedef struct
{
	unsigned f_time_remote_electricity_on:6;
	unsigned f_reserved:2;
}_CAN_ACU_2_B_INFO_BYTE_6;

typedef union
{
	_CAN_ACU_2_B_INFO_BYTE_6 field;
	u8 byte;
}CAN_ACU_2_B_INFO_BYTE_6;

typedef struct
{
	unsigned f_time_remote_power_on:6;
	unsigned f_reserved:2;
}_CAN_ACU_2_B_INFO_BYTE_7;

typedef union
{
	_CAN_ACU_2_B_INFO_BYTE_7 field;
	u8 byte;
}CAN_ACU_2_B_INFO_BYTE_7;

typedef struct
{
	CAN_ACU_2_B_INFO_BYTE_0 byte_0;
	CAN_ACU_2_B_INFO_BYTE_1 byte_1;
	CAN_ACU_2_B_INFO_BYTE_2 byte_2;
	CAN_ACU_2_B_INFO_BYTE_3 byte_3;
	CAN_ACU_2_B_INFO_BYTE_4 byte_4;
	CAN_ACU_2_B_INFO_BYTE_5 byte_5;
	CAN_ACU_2_B_INFO_BYTE_6 byte_6;
	CAN_ACU_2_B_INFO_BYTE_7 byte_7;
}CAN_ACU_2_B_INFO;

typedef struct
{
	unsigned f_remote_control_window_sunroof:2;
	unsigned f_fog_light_for_turning:2;
	unsigned f_remote_unlock:2;
	unsigned f_high_speed_auto_lock:2;
}_CAN_ACU_4_B_INFO_BYTE_0;

typedef union
{
	_CAN_ACU_4_B_INFO_BYTE_0 field;
	u8 byte;
}CAN_ACU_4_B_INFO_BYTE_0;

typedef struct
{
	unsigned f_auto_door_unlock:2;
	unsigned f_light_to_home:2;
	unsigned f_auto_light_sensitivity:3;
	unsigned f_reserved:1;
}_CAN_ACU_4_B_INFO_BYTE_1;

typedef union
{
	_CAN_ACU_4_B_INFO_BYTE_1 field;
	u8 byte;
}CAN_ACU_4_B_INFO_BYTE_1;

typedef struct
{
	unsigned f_wiper_maintanence:2;
	unsigned f_auto_rear_wipe_function:2;
	unsigned f_head_light_for_daytime:2;
	unsigned f_lock_unlock_whistle_remind:2;
}_CAN_ACU_4_B_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_4_B_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_4_B_INFO_BYTE_2;

typedef struct
{
	unsigned f_ambient_light_control:2;
	unsigned f_auto_wiper:2;
	unsigned f_reserved:4;
}_CAN_ACU_4_B_INFO_BYTE_3;

typedef union
{
	_CAN_ACU_4_B_INFO_BYTE_3 field;
	u8 byte;
}CAN_ACU_4_B_INFO_BYTE_3;

typedef struct
{
	CAN_ACU_4_B_INFO_BYTE_0 byte_0;
	CAN_ACU_4_B_INFO_BYTE_1 byte_1;
	CAN_ACU_4_B_INFO_BYTE_2 byte_2;
	CAN_ACU_4_B_INFO_BYTE_3 byte_3;
}CAN_ACU_4_B_INFO;

typedef struct
{
	unsigned f_steering_mode:2;
	unsigned f_reserved:6;
}_CAN_ACU_5_B_INFO_BYTE_0;

typedef union
{
	_CAN_ACU_5_B_INFO_BYTE_0 field;
	u8 byte;
}CAN_ACU_5_B_INFO_BYTE_0;

typedef struct
{
	unsigned f_forward_collision_warning_distance:2;
	unsigned f_forward_collision_warning_status:2;
	unsigned f_autonomous_emergency_braking:2;
	unsigned f_reserved:2;
}_CAN_ACU_5_B_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_5_B_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_5_B_INFO_BYTE_2;

typedef struct
{
	CAN_ACU_5_B_INFO_BYTE_0 byte_0;
	u8 reserved_1;
	CAN_ACU_5_B_INFO_BYTE_2 byte_2;
}CAN_ACU_5_B_INFO;

typedef struct
{
	unsigned f_time_year:8;
}_CAN_ACU_10_B_INFO_BYTE_0;

typedef union
{
	_CAN_ACU_10_B_INFO_BYTE_0 field;
	u8 byte;
}CAN_ACU_10_B_INFO_BYTE_0;

typedef struct
{
	unsigned f_time_day_1:4;
	unsigned f_time_month:4;
}_CAN_ACU_10_B_INFO_BYTE_1;

typedef union
{
	_CAN_ACU_10_B_INFO_BYTE_1 field;
	u8 byte;
}CAN_ACU_10_B_INFO_BYTE_1;

typedef struct
{
	unsigned f_time_minute_1:2;
	unsigned f_time_hour:5;
	unsigned f_time_day_2:1;
}_CAN_ACU_10_B_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_10_B_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_10_B_INFO_BYTE_2;

typedef struct
{
	unsigned f_time_second_1:4;
	unsigned f_time_minute_2:4;
}_CAN_ACU_10_B_INFO_BYTE_3;

typedef union
{
	_CAN_ACU_10_B_INFO_BYTE_3 field;
	u8 byte;
}CAN_ACU_10_B_INFO_BYTE_3;

typedef struct
{
	unsigned f_language_setting:6;
	unsigned f_time_second_2:2;
}_CAN_ACU_10_B_INFO_BYTE_4;

typedef union
{
	_CAN_ACU_10_B_INFO_BYTE_4 field;
	u8 byte;
}CAN_ACU_10_B_INFO_BYTE_4;

typedef struct
{
	CAN_ACU_10_B_INFO_BYTE_0 byte_0;
	CAN_ACU_10_B_INFO_BYTE_1 byte_1;
	CAN_ACU_10_B_INFO_BYTE_2 byte_2;
	CAN_ACU_10_B_INFO_BYTE_3 byte_3;
	CAN_ACU_10_B_INFO_BYTE_4 byte_4;
}CAN_ACU_10_B_INFO;

typedef struct
{
	unsigned f_hvacf_off:1;
	unsigned f_reserved1:1;
	unsigned f_hvacf_auto:1;
	unsigned f_reserved3:1;
	unsigned f_hvacf_mode:1;
	unsigned f_reserved5:1;
	unsigned f_hvacf_front_defrost:1;
	unsigned f_reserved7:1;
}_CAN_ACU_16_B_INFO_BYTE_0;

typedef union
{
	_CAN_ACU_16_B_INFO_BYTE_0 field;
	u8 byte;
}CAN_ACU_16_B_INFO_BYTE_0;

typedef struct
{
	unsigned f_hvacf_rear_defrost:1;
	unsigned f_reserved1:1;
	unsigned f_hvacf_dual:1;
	unsigned f_reserved3:1;
	unsigned f_hvacf_ion:1;
	unsigned f_reserved5:1;
	unsigned f_hvacf_fan_inc:1;
	unsigned f_reserved7:1;
}_CAN_ACU_16_B_INFO_BYTE_1;

typedef union
{
	_CAN_ACU_16_B_INFO_BYTE_1 field;
	u8 byte;
}CAN_ACU_16_B_INFO_BYTE_1;

typedef struct
{
	unsigned f_hvacf_fan_dec:1;
	unsigned f_reserved1:1;
	unsigned f_hvacf_circulation:1;
	unsigned f_reserved3:1;
	unsigned f_hvacf_ac:1;
	unsigned f_reserved5:1;
	unsigned f_hvacf_ac_max:1;
	unsigned f_reserved7:1;
}_CAN_ACU_16_B_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_16_B_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_16_B_INFO_BYTE_2;

typedef struct
{
	unsigned f_hvacf_temp_inc:1;
	unsigned f_reserved1:1;
	unsigned f_hvacf_temp_dec:1;
	unsigned f_reserved37:5;
}_CAN_ACU_16_B_INFO_BYTE_3;

typedef union
{
	_CAN_ACU_16_B_INFO_BYTE_3 field;
	u8 byte;
}CAN_ACU_16_B_INFO_BYTE_3;

typedef struct
{
	unsigned f_hvacf_front_left_temp_inc:1;
	unsigned f_reserved1:1;
	unsigned f_hvacf_front_left_temp_dec:1;
	unsigned f_reserved3:1;
	unsigned f_hvacf_front_right_temp_inc:1;
	unsigned f_reserved5:1;
	unsigned f_hvacf_front_right_temp_dec:1;
	unsigned f_reserved7:1;
}_CAN_ACU_16_B_INFO_BYTE_6;

typedef union
{
	_CAN_ACU_16_B_INFO_BYTE_6 field;
	u8 byte;
}CAN_ACU_16_B_INFO_BYTE_6;

typedef struct
{
	unsigned f_hvacf_triple_zone:1;
	unsigned f_reserved1:1;
	unsigned f_hvacf_inner_circulation:1;
	unsigned f_reserved3:1;
	unsigned f_hvacf_outer_circulation:1;
	unsigned f_reserved5:1;
	unsigned f_hvacf_rear:1;
	unsigned f_reserved7:1;
}_CAN_ACU_16_B_INFO_BYTE_7;

typedef union
{
	_CAN_ACU_16_B_INFO_BYTE_7 field;
	u8 byte;
}CAN_ACU_16_B_INFO_BYTE_7;

typedef struct
{
	CAN_ACU_16_B_INFO_BYTE_0 byte_0;
	CAN_ACU_16_B_INFO_BYTE_1 byte_1;
	CAN_ACU_16_B_INFO_BYTE_2 byte_2;
	CAN_ACU_16_B_INFO_BYTE_3 byte_3;
	u8 reserved_4;
	u8 reserved_5;
	CAN_ACU_16_B_INFO_BYTE_6 byte_6;
	CAN_ACU_16_B_INFO_BYTE_7 byte_7;
}CAN_ACU_16_B_INFO;

typedef struct
{
	unsigned f_reserved:2;
	unsigned f_ial_brightness:6;
}_CAN_ACU_17_B_INFO_BYTE_0;

typedef union
{
	_CAN_ACU_17_B_INFO_BYTE_0 field;
	u8 byte;
}CAN_ACU_17_B_INFO_BYTE_0;

typedef struct
{
	unsigned f_ial_color:6;
	unsigned f_fan_speed_of_auto_mode:2;
}_CAN_ACU_17_B_INFO_BYTE_1;

typedef union
{
	_CAN_ACU_17_B_INFO_BYTE_1 field;
	u8 byte;
}CAN_ACU_17_B_INFO_BYTE_1;

typedef struct
{
	unsigned f_rear_view_mirro_flip_position_setting:2;
	unsigned f_rear_view_mirro_angle_save:2;
	unsigned f_reserved:4;
}_CAN_ACU_17_B_INFO_BYTE_3;

typedef union
{
	_CAN_ACU_17_B_INFO_BYTE_3 field;
	u8 byte;
}CAN_ACU_17_B_INFO_BYTE_3;

typedef struct
{
	CAN_ACU_17_B_INFO_BYTE_0 byte_0;
	CAN_ACU_17_B_INFO_BYTE_1 byte_1;
	u8 reserved_2;
	CAN_ACU_17_B_INFO_BYTE_3 byte_3;
}CAN_ACU_17_B_INFO;

typedef struct
{
	unsigned f_hvacf_driver_temp:5;
	unsigned f_reserved:3;
}_CAN_ACU_HVAC_1_B_INFO_BYTE_0;

typedef union
{
	_CAN_ACU_HVAC_1_B_INFO_BYTE_0 field;
	u8 byte;
}CAN_ACU_HVAC_1_B_INFO_BYTE_0;

typedef struct
{
	unsigned f_hvacf_wind_speed:4;
	unsigned f_reserved:4;
}_CAN_ACU_HVAC_1_B_INFO_BYTE_1;

typedef union
{
	_CAN_ACU_HVAC_1_B_INFO_BYTE_1 field;
	u8 byte;
}CAN_ACU_HVAC_1_B_INFO_BYTE_1;

typedef struct
{
	unsigned f_reserved:3;
	unsigned f_hvacf_psn_temp:5;
}_CAN_ACU_HVAC_1_B_INFO_BYTE_2;

typedef union
{
	_CAN_ACU_HVAC_1_B_INFO_BYTE_2 field;
	u8 byte;
}CAN_ACU_HVAC_1_B_INFO_BYTE_2;

typedef struct
{
	CAN_ACU_HVAC_1_B_INFO_BYTE_0 byte_0;
	CAN_ACU_HVAC_1_B_INFO_BYTE_1 byte_1;
	CAN_ACU_HVAC_1_B_INFO_BYTE_2 byte_2;
}CAN_ACU_HVAC_1_B_INFO;

typedef struct
{
	CAN_ACU_1_A_INFO acu_1_a_info;
	CAN_ACU_2_A_INFO acu_2_a_info;
	CAN_ACU_3_A_INFO acu_3_a_info;
	CAN_ACU_2_B_INFO acu_2_b_info;
	CAN_ACU_4_B_INFO acu_4_b_info;
	CAN_ACU_5_B_INFO acu_5_b_info;
	CAN_ACU_10_B_INFO acu_10_b_info;
	CAN_ACU_16_B_INFO acu_16_b_info;
	CAN_ACU_17_B_INFO acu_17_b_info;
	CAN_ACU_HVAC_1_B_INFO acu_hvac_1_b_info;
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
extern CAN_RX_BUFFER CanRxBuffer2;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_TX_BUFFER CanTxBuffer2;
extern u8 CanTxErrorCounter;
extern u8 CanNoTxCounter;
extern CAN_MAIN_FLAG CanMainFlag;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT			CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init

void Trumpchi_MainPro(void);
void Trumpchi_RxAppDataPro(u8 *buffer);
void Trumpchi_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
u8 Trumpchi_CheckTxMessage(u32 id,u8 *data);
void Trumpchi_CanReset(void);


#endif
#endif

