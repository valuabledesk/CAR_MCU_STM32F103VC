#ifndef _CAN_HAIMA_8S_H_
#define _CAN_HAIMA_8S_H_
#if CAN_FUN_HAIMA_8S == 1

#define CAN_RX_BUFFER_LENGTH 400
#define CAN_TX_BUFFER_LENGTH 100
#define CAN_TX_QUEUE_LENGTH 10

/*************** Receive ID********************/
#define CAN_ID_AVM 0x360
#define CAN_ID_T_BOX_9 0x620
#define CAN_ID_ESP_2 0x090
#define CAN_ID_ICM_1 0x298
#define CAN_ID_ICM_2 0x290
#define CAN_ID_ICM_3 0x470
#define CAN_ID_ACP 0x428
#define CAN_ID_TPMS_1 0x440
#define CAN_ID_TPMS_2 0x450
#define CAN_ID_BCM_1 0x300
#define CAN_ID_BCM_2 0x320
#define CAN_ID_CCM 0x420
#define CAN_ID_CCM_2 0x454
#define CAN_ID_EPS 0x430
#define CAN_ID_MRR_2 0x353
#define CAN_ID_EMS_4 0x373
#define CAN_ID_SCM_1 0x495
#define CAN_ID_APM_1 0x390
#define CAN_ID_MPC_1 0x308
#define CAN_ID_SAS 0x080
#define CAN_ID_LCAS 0x284
#define CAN_ID_IAL 0x4A8
#define CAN_ID_TCU_2 0x144

/*************** Transmit ID********************/
#define CAN_ID_DVD_1 0x29F
#define CAN_ID_DVD_4 0x608
#define CAN_ID_DVD_5 0x60B
#define CAN_ID_DVD_6 0x60E
#define CAN_ID_DVD_7 0x61B
#define CAN_ID_DVD_8 0x61E
#define CAN_ID_DVD_A 0x472
#define CAN_ID_DVD_B 0x473
#define CAN_ID_DVD_E 0x476
#define CAN_ID_DVD_F 0x477
#define CAN_ID_DVD_G 0x478
#define CAN_ID_DVD_H 0x479
#define CAN_ID_DVD_I 0x47A
#define CAN_ID_DVD_NM 0x516
#define CAN_ID_BCM_INFO_02 0x0BA

#define CAN_TX_ID_COUNT 15

/***************APP Cmd***********************/
#define HAIMA_8S_RX_AVM_INFO 0x20
// #define HAIMA_8S_RX_TBOX_INFO 0x21
#define HAIMA_8S_RX_CCM_INFO 0x21
#define HAIMA_8S_RX_ESP_INFO 0x22
#define HAIMA_8S_RX_BASE_INFO 0x23
#define HAIMA_8S_RX_RADAR_INFO 0x24
#define HAIMA_8S_RX_ICM_INFO 0x25
#define HAIMA_8S_RX_ACP_INFO 0x26
#define HAIMA_8S_RX_TPMS_INFO 0x27
#define HAIMA_8S_RX_BCM_INFO 0x28
#define HAIMA_8S_RX_TCU_INFO 0x29
// #define HAIMA_8S_RX_CCM_INFO 0x29
#define HAIMA_8S_RX_EPS_INFO 0x2A
#define HAIMA_8S_RX_MRR_INFO 0x2B
#define HAIMA_8S_RX_EMS_INFO 0x2C
#define HAIMA_8S_RX_SCM_INFO 0x2D
#define HAIMA_8S_RX_APM_INFO 0x2E
#define HAIMA_8S_RX_MPC_INFO 0x2F
#define HAIMA_8S_RX_SAS_INFO 0x30
#define HAIMA_8S_RX_LCAS_INFO 0x31
#define HAIMA_8S_RX_IAL_INFO 0x32

#define HAIMA_8S_TX_REQ_CMD 0x90
#define HAIMA_8S_TX_CCM_CMD 0x8A
#define HAIMA_8S_TX_AVM_CMD 0x8B
#define HAIMA_8S_TX_VOICE_CMD 0x8C
#define HAIMA_8S_TX_ADAS_CMD 0x8D
#define HAIMA_8S_TX_OTS_CMD 0x8E

#define HAIMA_8S_TX_PHONE_NUMBER_CMD 0x81
#define HAIMA_8S_TX_PHONE_NAME_CMD 0x82
#define HAIMA_8S_TX_ID3_CMD 0x83
#define HAIMA_8S_TX_PHONE_STATE_CMD 0x84

#define HAIMA_8S_HEAD_CODE 0x2E

typedef enum
{
	CAN_MAIN_IDLE = 0,
	CAN_MAIN_CFG,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
	CAN_MAIN_SLEEP_CFG,
	CAN_MAIN_SLEEP
} CAN_MAIN_STATE;

typedef enum
{
	CAN_POST_MSG_NONE = 0,
	CAN_POST_MSG_DVD_1,
	CAN_POST_MSG_DVD_4,
	CAN_POST_MSG_DVD_5,
	CAN_POST_MSG_DVD_6,
	CAN_POST_MSG_DVD_7,
	CAN_POST_MSG_DVD_8,
	CAN_POST_MSG_DVD_A,
	CAN_POST_MSG_DVD_B,
	CAN_POST_MSG_DVD_E,
	CAN_POST_MSG_DVD_F,
	CAN_POST_MSG_DVD_G,
	CAN_POST_MSG_DVD_H,
	CAN_POST_MSG_DVD_I,
	CAN_POST_MSG_DVD_NM,
	CAN_POST_MSG_TEST,
	CAN_POST_MSG_MAX_INDEX
} CAN_POST_MESSAGE_INDEX;

typedef enum
{
	CCM_ON_OFF = 0,
	CCM_AUTO,
	CCM_FL_TEMPERATURE,
	CCM_DUAL,
	CCM_FR_TEMPERATURE,
	CCM_BLOWER_VOL,
	CCM_AC,
	CCM_MAXAC,
	CCM_CYCLE,
	CCM_F_DEFROST,
	CCM_R_DEFROST = 10,
	CCM_AIR_CLEAN,
	CCM_AIR_DISTRIBUTION,
	OTS_DRIVER_SEAT_HEATING,
	OTS_PASSEGER_SEAT_HEATING,
} HAIMA_8S_CCM_KEY_INDEX;

typedef enum
{
	VOICE_FL_WIN = 0,
	VOICE_FR_WIN,
	VOICE_RL_WIN,
	VOICE_RR_WIN,
	VOICE_FL_SEAT,
	VOICE_SEAT_COURT,
	VOICE_SEAT_POSITION,
	VOICE_SUNROOF,
	VOICE_CURTAIN,
	VOICE_WIPER,
	VOICE_R_VMIRROR = 10,
	VOICE_WASHER,
	VOICE_LIGHT,
	VOICE_DOOR,
} HAIMA_8S_VOICE_KEY_INDEX;

typedef enum
{
	ADAS_NO_FUN = 0,
	ADAS_BLIND_SURPERVISE,
	ADAS_LCAS,
	ADAS_DOOR_OPEN_WARN,
	ADAS_LCAS_CAL,
	ADAS_PCW,
	ADAS_AEB,
	ADAS_SENSITIVITY,
	ADAS_LKS,
	ADAS_EPS,
	ADAS_LANE_DEPARTURE = 10,
	ADAS_F_RADAR,
} HAIMA_8S_ADAS_KEY_INDEX;

typedef enum
{
	OTS_NO_FUN = 0,
	OTS_FOLLOW_ME_HOME,
	OTS_RESERVED,
	OTS_RESERVED_3,
	OTS_FOLLOW_ME_HOME_DELAY_TIME,
	OTS_IAL,
	OTS_IAL_MODE,
	OTS_IAL_BRIGHTNESS,
	OTS_IAL_COLOR,
	OTS_DOOR_LOCK,
	OTS_ROOM_LAMP,
	OTS_DAYTIME_LAMP,
} HAIMA_8S_OTS_KEY_INDEX;

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
	u8 head;
	u8 tail;
	u8 delay[CAN_TX_QUEUE_LENGTH];
	u8 message[CAN_TX_QUEUE_LENGTH][10];
} CAN_TX_QUEUE;

typedef struct
{
	u16 ID;
	u8 timer;
} CAN_TX_TIMER;

typedef struct
{
	unsigned f_parking_guide_line : 1;
	unsigned f_video_out : 3;
	unsigned f_color_set : 3;
	unsigned reserved : 1;
} _CAN_AVM_INFO_BYTE_0;

typedef union
{
	_CAN_AVM_INFO_BYTE_0 field;
	u8 byte;
} CAN_AVM_INFO_BYTE_0;

typedef struct
{
	unsigned f_sd_card : 3;
	unsigned f_avm_guides : 1;
	unsigned f_lane_departure : 3;
	unsigned reserved : 1;
} _CAN_AVM_INFO_BYTE_1;

typedef union
{
	_CAN_AVM_INFO_BYTE_1 field;
	u8 byte;
} CAN_AVM_INFO_BYTE_1;

typedef struct
{
	CAN_AVM_INFO_BYTE_0 byte_0;
	CAN_AVM_INFO_BYTE_1 byte_1;
} CAN_AVM_INFO;

typedef struct
{
	unsigned f_ecall : 3;
	unsigned f_icall : 3;
	unsigned reserved : 2;
} _CAN_TBOX_INFO_BYTE_0;

typedef union
{
	_CAN_TBOX_INFO_BYTE_0 field;
	u8 byte;
} CAN_TBOX_INFO_BYTE_0;

typedef struct
{
	CAN_TBOX_INFO_BYTE_0 byte_0;
} CAN_TBOX_INFO;

typedef struct
{
	unsigned speed_L5 : 5;
	unsigned reserved : 3;
} _CAN_ESP_INFO_BYTE_1;

typedef union
{
	_CAN_ESP_INFO_BYTE_1 field;
	u8 byte;
} CAN_ESP_INFO_BYTE_1;

typedef struct
{
	u8 speed_H8;
	CAN_ESP_INFO_BYTE_1 byte_1;
} CAN_ESP_INFO;

typedef struct
{
	unsigned f_can_ready : 1;
	unsigned reserved : 5;
	unsigned remain_oil_H2 : 2;
} _CAN_BASE_INFO_BYTE_0;

typedef union
{
	_CAN_BASE_INFO_BYTE_0 field;
	u8 byte;
} CAN_BASE_INFO_BYTE_0;

typedef struct
{
	CAN_BASE_INFO_BYTE_0 byte_0;
	u8 remain_oil_L8;
	u8 aver_fuel_consumption;
	u8 remain_mileage;
	u8 total_mileage_H;
	u8 total_mileage_M;
	u8 total_mileage_L;
	u8 remain_maintenance_mileage;
} CAN_BASE_INFO;

typedef struct
{
	unsigned f_rl_radar : 3;
	unsigned f_rlm_radar : 3;
	unsigned reserved : 2;
} _CAN_RADAR_INFO_BYTE_0;

typedef union
{
	_CAN_RADAR_INFO_BYTE_0 field;
	u8 byte;
} CAN_RADAR_INFO_BYTE_0;

typedef struct
{
	unsigned f_rrm_radar : 3;
	unsigned f_rr_radar : 3;
	unsigned f_f_radar : 1;
	unsigned reserved : 1;
} _CAN_RADAR_INFO_BYTE_1;

typedef union
{
	_CAN_RADAR_INFO_BYTE_1 field;
	u8 byte;
} CAN_RADAR_INFO_BYTE_1;

typedef struct
{
	CAN_RADAR_INFO_BYTE_0 byte_0;
	CAN_RADAR_INFO_BYTE_1 byte_1;
} CAN_RADAR_INFO;

typedef struct
{
	unsigned f_icm_theme : 3;
	unsigned f_phone_name_req : 1;
	unsigned f_current_road_req : 1;
	unsigned f_turn_road_req : 1;
	unsigned f_id3_req : 1;
	unsigned reserved : 1;
} _CAN_ICM_INFO_BYTE_0;

typedef union
{
	_CAN_ICM_INFO_BYTE_0 field;
	u8 byte;
} CAN_ICM_INFO_BYTE_0;

typedef struct
{
	CAN_ICM_INFO_BYTE_0 byte_0;
	u8 gear;
} CAN_ICM_INFO;

typedef struct
{
	unsigned f_acp_ctrl : 2;
	unsigned reserved : 6;
} _CAN_ACP_INFO_BYTE_0;

typedef union
{
	_CAN_ACP_INFO_BYTE_0 field;
	u8 byte;
} CAN_ACP_INFO_BYTE_0;

typedef struct
{
	unsigned vol_rorate_dir : 2;
	unsigned vol_rorate_times : 5;
	unsigned reserved : 1;
} _CAN_ACP_INFO_BYTE_1;

typedef union
{
	_CAN_ACP_INFO_BYTE_1 field;
	u8 byte;
} CAN_ACP_INFO_BYTE_1;

typedef struct
{
	CAN_ACP_INFO_BYTE_0 byte_0;
	CAN_ACP_INFO_BYTE_1 byte_1;
} CAN_ACP_INFO;

typedef struct
{
	unsigned f_fl_tp : 2;
	unsigned f_fr_tp : 2;
	unsigned f_rl_tp : 2;
	unsigned f_rr_tp : 2;
} _CAN_TPMS_INFO_BYTE_0;

typedef union
{
	_CAN_TPMS_INFO_BYTE_0 field;
	u8 byte;
} CAN_TPMS_INFO_BYTE_0;

typedef struct
{
	CAN_TPMS_INFO_BYTE_0 byte_0;
	u8 fl_tp;
	u8 fr_tp;
	u8 rl_tp;
	u8 rr_tp;
	u8 fl_tt;
	u8 fr_tt;
	u8 rl_tt;
	u8 rr_tt;
} CAN_TPMS_INFO;

typedef struct
{
	unsigned f_fl_door_lock : 1;
	unsigned f_fr_door_lock : 1;
	unsigned f_rl_door_lock : 1;
	unsigned f_rr_door_lock : 1;
	unsigned f_trunk_ajar : 1;
	unsigned reserved : 1;
	// unsigned f_tail_lamp : 1;
	// unsigned low_beam : 1;
	// unsigned f_r_fog_lamp : 1;
	// unsigned f_f_fog_lamp : 1;
	unsigned f_turn_lamp : 2;
} _CAN_BCM_INFO_BYTE_0;

typedef union
{
	_CAN_BCM_INFO_BYTE_0 field;
	u8 byte;
} CAN_BCM_INFO_BYTE_0;

typedef struct
{
	unsigned reserved : 4;
	unsigned f_escl_power_supply : 2;
	unsigned f_escl_lock : 2;
} _CAN_BCM_INFO_BYTE_1;

typedef union
{
	_CAN_BCM_INFO_BYTE_1 field;
	u8 byte;
} CAN_BCM_INFO_BYTE_1;

typedef struct
{
	unsigned f_adas : 1;
	unsigned f_f_wiper : 2;
	unsigned f_windscreen_washing : 2;
	unsigned reverse : 1; // unsigned f_high_beam : 1;
	unsigned f_trunk_lock : 1;
	unsigned f_day_running_light : 1;
} _CAN_BCM_INFO_BYTE_2;

typedef union
{
	_CAN_BCM_INFO_BYTE_2 field;
	u8 byte;
} CAN_BCM_INFO_BYTE_2;

typedef struct
{
	unsigned f_power_mode : 2;
	unsigned f_follow_me_home : 1;
	unsigned f_door_lock_ctrl : 1;
	unsigned f_search_car_beep_num : 1;
	unsigned f_room_lamp : 1;
	unsigned f_daytime_lamp : 1;
	unsigned reserved : 1;
} _CAN_BCM_INFO_BYTE_3;

typedef union
{
	_CAN_BCM_INFO_BYTE_3 field;
	u8 byte;
} CAN_BCM_INFO_BYTE_3;

typedef struct
{
	CAN_BCM_INFO_BYTE_0 byte_0;
	CAN_BCM_INFO_BYTE_1 byte_1;
	CAN_BCM_INFO_BYTE_2 byte_2;
	CAN_BCM_INFO_BYTE_3 byte_3;
	u8 follow_me_home_delay_time;
} CAN_BCM_INFO;

typedef struct
{
	unsigned fl_temp : 6;
	unsigned f_cycle : 2;
} _CAN_CCM_INFO_BYTE_0;

typedef union
{
	_CAN_CCM_INFO_BYTE_0 field;
	u8 byte;
} CAN_CCM_INFO_BYTE_0;

typedef struct
{
	unsigned blower_vol : 4;
	unsigned f_ccm : 1;
	unsigned f_max_ac : 1;
	unsigned f_auto : 1;
	unsigned f_ac : 1;
} _CAN_CCM_INFO_BYTE_1;

typedef union
{
	_CAN_CCM_INFO_BYTE_1 field;
	u8 byte;
} CAN_CCM_INFO_BYTE_1;

typedef struct
{
	unsigned f_ambient_temp : 1;
	unsigned f_air_distribution : 3;
	unsigned f_f_defrost : 1;
	unsigned f_r_defrost : 1;
	unsigned reserved : 2;
} _CAN_CCM_INFO_BYTE_2;

typedef union
{
	_CAN_CCM_INFO_BYTE_2 field;
	u8 byte;
} CAN_CCM_INFO_BYTE_2;

typedef struct
{
	unsigned fr_temp : 6;
	unsigned f_dual : 1;
	unsigned f_hmi_req : 1;
} _CAN_CCM_INFO_BYTE_4;

typedef union
{
	_CAN_CCM_INFO_BYTE_4 field;
	u8 byte;
} CAN_CCM_INFO_BYTE_4;

typedef struct
{

	unsigned f_air_clean : 2;
	unsigned reserved : 1;
	unsigned f_pm25 : 3;
	unsigned pm25_L : 2;
} _CAN_CCM_INFO_BYTE_6;

typedef union
{
	_CAN_CCM_INFO_BYTE_6 field;
	u8 byte;
} CAN_CCM_INFO_BYTE_6;

typedef struct
{
	unsigned f_pm25_filter : 2;
	unsigned reserved : 6;
} _CAN_CCM_INFO_BYTE_7;

typedef union
{
	_CAN_CCM_INFO_BYTE_7 field;
	u8 byte;
} CAN_CCM_INFO_BYTE_7;

typedef struct
{
	CAN_CCM_INFO_BYTE_0 byte_0;
	CAN_CCM_INFO_BYTE_1 byte_1;
	CAN_CCM_INFO_BYTE_2 byte_2;
	u8 ambient_temp;
	CAN_CCM_INFO_BYTE_4 byte_4;
	u8 pm25_H;
	CAN_CCM_INFO_BYTE_6 byte_6;
	CAN_CCM_INFO_BYTE_7 byte_7;
} CAN_CCM_INFO;

typedef struct
{
	u8 f_eps;
} CAN_EPS_INFO;

typedef struct
{
	unsigned f_pebs_text : 1;
	unsigned f_pcw : 1;
	unsigned f_aeb : 1;
	unsigned reserved : 5;
} _CAN_MRR_INFO_BYTE_0;

typedef union
{
	_CAN_MRR_INFO_BYTE_0 field;
	u8 byte;
} CAN_MRR_INFO_BYTE_0;

typedef struct
{
	CAN_MRR_INFO_BYTE_0 byte_0;
} CAN_MRR_INFO;

typedef struct
{
	unsigned f_engine_temp_vdl : 1;
	unsigned f_epcs : 1;
	unsigned reserved : 6;
} _CAN_EMS_INFO_BYTE_0;

typedef union
{
	_CAN_EMS_INFO_BYTE_0 field;
	u8 byte;
} CAN_EMS_INFO_BYTE_0;

typedef struct
{
	CAN_EMS_INFO_BYTE_0 byte_0;
	u8 engine_temp;
} CAN_EMS_INFO;

typedef struct
{
	unsigned reserved : 2;
	unsigned f_passenger_seat_heating : 3;
	unsigned f_driver_seat_heating : 3;
} _CAN_SCM_INFO_BYTE_0;

typedef union
{
	_CAN_SCM_INFO_BYTE_0 field;
	u8 byte;
} CAN_SCM_INFO_BYTE_0;

typedef struct
{
	unsigned f_seat_court : 1;
	unsigned reserved : 3;
	unsigned f_seat_position : 3;
	unsigned reserved_7 : 1;
} _CAN_SCM_INFO_BYTE_1;

typedef union
{
	_CAN_SCM_INFO_BYTE_1 field;
	u8 byte;
} CAN_SCM_INFO_BYTE_1;

typedef struct
{
	CAN_SCM_INFO_BYTE_0 byte_0;
	CAN_SCM_INFO_BYTE_1 byte_1;
} CAN_SCM_INFO;

typedef struct
{
	unsigned f_fl_win : 3;
	unsigned f_fr_win : 3;
	unsigned reserved : 2;
} _CAN_APM_INFO_BYTE_0;

typedef union
{
	_CAN_APM_INFO_BYTE_0 field;
	u8 byte;
} CAN_APM_INFO_BYTE_0;

typedef struct
{
	unsigned f_rl_win : 3;
	unsigned f_rr_win : 3;
	unsigned reserved : 2;
} _CAN_APM_INFO_BYTE_1;

typedef union
{
	_CAN_APM_INFO_BYTE_1 field;
	u8 byte;
} CAN_APM_INFO_BYTE_1;

typedef struct
{
	CAN_APM_INFO_BYTE_0 byte_0;
	CAN_APM_INFO_BYTE_1 byte_1;
} CAN_APM_INFO;

typedef struct
{
	unsigned reserved : 4;
	unsigned f_lks : 2;
	unsigned lks_sensitivity : 2;
} _CAN_MPC_INFO_BYTE_0;

typedef union
{
	_CAN_MPC_INFO_BYTE_0 field;
	u8 byte;
} CAN_MPC_INFO_BYTE_0;

typedef struct
{
	CAN_MPC_INFO_BYTE_0 byte_0;
} CAN_MPC_INFO;

typedef struct
{
	unsigned f_sas : 1;
	unsigned f_sas_cal : 1;
	unsigned reserved : 6;
} _CAN_SAS_INFO_BYTE_0;

typedef union
{
	_CAN_SAS_INFO_BYTE_0 field;
	u8 byte;
} CAN_SAS_INFO_BYTE_0;

typedef struct
{
	// CAN_SAS_INFO_BYTE_0 byte_0;
	// u8 steering_speed;
	u8 steering_angle_L;
	u8 steering_angle_H;
} CAN_SAS_INFO;

typedef struct
{
	unsigned f_blind_surpervise : 1;
	unsigned f_lca : 1;
	unsigned f_door_open_warn : 1;
	unsigned reserved : 1;
	unsigned f_lcas_cal : 2;
	unsigned f_lcas_cal_process : 2;
} _CAN_LCAS_INFO_BYTE_0;

typedef union
{
	_CAN_LCAS_INFO_BYTE_0 field;
	u8 byte;
} CAN_LCAS_INFO_BYTE_0;

typedef struct
{
	CAN_LCAS_INFO_BYTE_0 byte_0;
} CAN_LCAS_INFO;

typedef struct
{
	unsigned f_ial : 1;
	unsigned reserved : 4;
	unsigned f_ial_mode : 3;
} _CAN_IAL_INFO_BYTE_0;

typedef union
{
	_CAN_IAL_INFO_BYTE_0 field;
	u8 byte;
} CAN_IAL_INFO_BYTE_0;

typedef struct
{
	CAN_IAL_INFO_BYTE_0 byte_0;
	u8 f_ial_brightness;
	u8 f_ial_color;
} CAN_IAL_INFO;

typedef struct
{
	CAN_AVM_INFO avm_info;
	CAN_TBOX_INFO tbox_info;
	CAN_ESP_INFO esp_info;
	CAN_BASE_INFO base_info;
	CAN_RADAR_INFO radar_info;
	CAN_ICM_INFO icm_info;
	CAN_ACP_INFO acp_info;
	CAN_TPMS_INFO tpms_info;
	CAN_BCM_INFO bcm_info;
	CAN_CCM_INFO ccm_info;
	CAN_EPS_INFO eps_info;
	CAN_MRR_INFO mrr_info;
	CAN_EMS_INFO ems_info;
	CAN_SCM_INFO scm_info;
	CAN_APM_INFO apm_info;
	CAN_MPC_INFO mpc_info;
	CAN_SAS_INFO sas_info;
	CAN_LCAS_INFO lcas_info;
	CAN_IAL_INFO ial_info;
} CAN_RX_INFO;

// typedef struct
// {
// 	unsigned reserved : 1;
// 	unsigned f_parking_guide_line : 2;
// 	unsigned reserved_3 : 2;
// 	unsigned f_color_set : 3;
// } _CAN_DVD_1_INFO_BYTE_0;

// typedef union
// {
// 	_CAN_DVD_1_INFO_BYTE_0 field;
// 	u8 byte;
// } CAN_DVD_1_INFO_BYTE_0;

// typedef struct
// {
// 	unsigned f;
// } _CAN_DVD_1_INFO_BYTE_1;

// typedef union
// {
// 	_CAN_DVD_1_INFO_BYTE_1 field;
// 	u8 byte;
// } CAN_DVD_1_INFO_BYTE_1;

typedef struct
{
	unsigned blind_surpervise : 1;
	unsigned lca : 1;
	unsigned door_open_warn : 1;
	unsigned lcas_cal : 1;
	unsigned reserved : 4;
} _CAN_DVD_1_INFO_BYTE_2;

typedef union
{
	_CAN_DVD_1_INFO_BYTE_2 field;
	u8 byte;
} CAN_DVD_1_INFO_BYTE_2;

typedef struct
{
	unsigned pcw : 1;
	unsigned aeb : 1;
	unsigned adas_senstivity : 2;
	unsigned adas : 2;
	unsigned reserved : 2;
} _CAN_DVD_1_INFO_BYTE_3;

typedef union
{
	_CAN_DVD_1_INFO_BYTE_3 field;
	u8 byte;
} CAN_DVD_1_INFO_BYTE_3;

typedef struct
{
	unsigned eps : 2;
	unsigned reserved : 1;
	unsigned lane_departure : 2;
	unsigned reserved_5 : 1;
	unsigned f_radar : 2;
} _CAN_DVD_1_INFO_BYTE_4;

typedef union
{
	_CAN_DVD_1_INFO_BYTE_4 field;
	u8 byte;
} CAN_DVD_1_INFO_BYTE_4;

typedef struct
{
	unsigned language : 5;
	unsigned avm_guides : 2;
	unsigned follow_me_home : 1;
} _CAN_DVD_1_INFO_BYTE_5;

typedef union
{
	_CAN_DVD_1_INFO_BYTE_5 field;
	u8 byte;
} CAN_DVD_1_INFO_BYTE_5;

typedef struct
{
	unsigned driver_seat_heating : 3;
	unsigned passeger_seat_heating : 3;
	unsigned reserved : 2;
} _CAN_DVD_1_INFO_BYTE_6;

typedef union
{
	_CAN_DVD_1_INFO_BYTE_6 field;
	u8 byte;
} CAN_DVD_1_INFO_BYTE_6;

typedef struct
{
	// CAN_DVD_1_INFO_BYTE_0 byte_0;
	// CAN_DVD_1_INFO_BYTE_1 byte_1;
	CAN_DVD_1_INFO_BYTE_2 byte_2;
	CAN_DVD_1_INFO_BYTE_3 byte_3;
	CAN_DVD_1_INFO_BYTE_4 byte_4;
	CAN_DVD_1_INFO_BYTE_5 byte_5;
	CAN_DVD_1_INFO_BYTE_6 byte_6;
	u8 follow_me_home_delay_time;
} CAN_DVD_1_INFO;

typedef struct
{
	u8 second;
	u8 minute;
	u8 hour;
	u8 day;
	u8 month;
	u8 year;
} CAN_DVD_4_INFO;

typedef struct
{
	unsigned keycode : 3;
	unsigned f_ctrl_sw : 1;
	unsigned bt_st : 2;
	unsigned reservede : 1;
	unsigned f_icm_navi : 1;
} _CAN_DVD_8_INFO_BYTE_0;

typedef union
{
	_CAN_DVD_8_INFO_BYTE_0 field;
	u8 byte;
} CAN_DVD_8_INFO_BYTE_0;

typedef struct
{
	unsigned source : 4;
	unsigned phone_st : 2;
	unsigned reserved : 2;
} _CAN_DVD_8_INFO_BYTE_1;

typedef union
{
	_CAN_DVD_8_INFO_BYTE_1 field;
	u8 byte;
} CAN_DVD_8_INFO_BYTE_1;

typedef struct
{
	unsigned reserved : 4;
	unsigned freq_L4 : 4;
} _CAN_DVD_8_INFO_BYTE_6;

typedef union
{
	_CAN_DVD_8_INFO_BYTE_6 field;
	u8 byte;
} CAN_DVD_8_INFO_BYTE_6;

typedef struct
{
	CAN_DVD_8_INFO_BYTE_0 byte_0;
	CAN_DVD_8_INFO_BYTE_1 byte_1;
	u8 bt_second;
	u8 bt_minute;
	u8 bt_hour;
	u8 freq_H8;
	CAN_DVD_8_INFO_BYTE_6 byte_6;
	u8 volume;
} CAN_DVD_8_INFO;

typedef struct
{
	u8 phone_number_0;
	u8 phone_number_1;
	u8 phone_number_2;
	u8 phone_number_3;
	u8 phone_number_4;
	u8 phone_number_5;
	u8 phone_number_6;
	u8 phone_number_7;
} CAN_DVD_A_INFO;

typedef struct
{
	unsigned phone_name_type : 2;
	unsigned phone_name_dlc : 6;
} _CAN_DVD_B_INFO_BYTE_0;

typedef union
{
	_CAN_DVD_B_INFO_BYTE_0 field;
	u8 byte;
} CAN_DVD_B_INFO_BYTE_0;

typedef struct
{
	CAN_DVD_B_INFO_BYTE_0 byte_0;
	u8 phone_name_1;
	u8 phone_name_2;
	u8 phone_name_3;
	u8 phone_name_4;
	u8 phone_name_5;
	u8 phone_name_6;
	u8 phone_name_7;
} CAN_DVD_B_INFO;

typedef struct
{
	unsigned id3_type : 2;
	unsigned id3_dlc : 6;
} _CAN_DVD_E_INFO_BYTE_0;

typedef union
{
	_CAN_DVD_E_INFO_BYTE_0 field;
	u8 byte;
} CAN_DVD_E_INFO_BYTE_0;

typedef struct
{
	CAN_DVD_E_INFO_BYTE_0 byte_0;
	u8 id3_1;
	u8 id3_2;
	u8 id3_3;
	u8 id3_4;
	u8 id3_5;
	u8 id3_6;
	u8 id3_7;
} CAN_DVD_E_INFO;

typedef struct
{
	unsigned type : 2;
	unsigned dlc : 6;
} _CAN_ICM_DISP_INFO_BYTE_0;

typedef union
{
	_CAN_ICM_DISP_INFO_BYTE_0 field;
	u8 byte;
}CAN_ICM_DISP_INFO_BYTE_0;

typedef struct
{
	CAN_ICM_DISP_INFO_BYTE_0 byte_0;
	u8 byte_1;
	u8 byte_2;
	u8 byte_3;
	u8 byte_4;
	u8 byte_5;
	u8 byte_6;
	u8 byte_7;
} CAN_ICM_DISP_INFO;

typedef struct
{
	unsigned reserved : 4;
	unsigned rear_mirror : 2;
	unsigned washer : 2;
} _CAN_DVD_F_INFO_BYTE_4;

typedef union
{
	_CAN_DVD_F_INFO_BYTE_4 field;
	u8 byte;
} CAN_DVD_F_INFO_BYTE_4;

typedef struct
{
	unsigned light : 4;
	unsigned door : 4;
} _CAN_DVD_F_INFO_BYTE_5;

typedef union
{
	_CAN_DVD_F_INFO_BYTE_5 field;
	u8 byte;
} CAN_DVD_F_INFO_BYTE_5;

typedef struct
{
	unsigned sun_roof : 3;
	unsigned curtain : 2;
	unsigned wiper : 3;
} _CAN_DVD_F_INFO_BYTE_7;

typedef union
{
	_CAN_DVD_F_INFO_BYTE_7 field;
	u8 byte;
} CAN_DVD_F_INFO_BYTE_7;

typedef struct
{
	CAN_DVD_F_INFO_BYTE_4 byte_4;
	CAN_DVD_F_INFO_BYTE_5 byte_5;
	CAN_DVD_F_INFO_BYTE_7 byte_7;
} CAN_DVD_F_INFO;

typedef struct
{
	unsigned f_ccm_set : 1;
	unsigned f_auto : 1;
	unsigned fl_temp : 6;
} _CAN_DVD_G_INFO_BYTE_0;

typedef union
{
	_CAN_DVD_G_INFO_BYTE_0 field;
	u8 byte;
} CAN_DVD_G_INFO_BYTE_0;

typedef struct
{
	unsigned f_dual : 1;
	unsigned reserved : 1;
	unsigned fr_temp : 6;
} _CAN_DVD_G_INFO_BYTE_1;

typedef union
{
	_CAN_DVD_G_INFO_BYTE_1 field;
	u8 byte;
} CAN_DVD_G_INFO_BYTE_1;

typedef struct
{
	unsigned blower_vol : 4;
	unsigned f_ac : 1;
	unsigned f_maxac : 1;
	unsigned f_cycle : 2;
} _CAN_DVD_G_INFO_BYTE_2;

typedef union
{
	_CAN_DVD_G_INFO_BYTE_2 field;
	u8 byte;
} CAN_DVD_G_INFO_BYTE_2;

typedef struct
{
	unsigned f_f_defrost : 1;
	unsigned f_r_defrost : 1;
	unsigned f_air_clean : 1;
	unsigned reserved : 1;
	unsigned f_door_lock_ctrl : 1;
	unsigned f_search_car_beep_num : 1;
	unsigned f_room_lamp : 1;
	unsigned f_daytime_lamp : 1;
} _CAN_DVD_G_INFO_BYTE_3;

typedef union
{
	_CAN_DVD_G_INFO_BYTE_3 field;
	u8 byte;
} CAN_DVD_G_INFO_BYTE_3;

typedef struct
{
	unsigned f_air_distribution : 3;
	unsigned reserved : 5;
} _CAN_DVD_G_INFO_BYTE_4;

typedef union
{
	_CAN_DVD_G_INFO_BYTE_4 field;
	u8 byte;
} CAN_DVD_G_INFO_BYTE_4;

typedef struct
{
	unsigned f_ial : 2;
	unsigned f_ial_mode : 3;
	unsigned reserved : 3;
} _CAN_DVD_G_INFO_BYTE_5;

typedef union
{
	_CAN_DVD_G_INFO_BYTE_5 field;
	u8 byte;
} CAN_DVD_G_INFO_BYTE_5;

typedef struct
{
	CAN_DVD_G_INFO_BYTE_0 byte_0;
	CAN_DVD_G_INFO_BYTE_1 byte_1;
	CAN_DVD_G_INFO_BYTE_2 byte_2;
	CAN_DVD_G_INFO_BYTE_3 byte_3;
	CAN_DVD_G_INFO_BYTE_4 byte_4;
	CAN_DVD_G_INFO_BYTE_5 byte_5;
	u8 f_ial_brightness;
	u8 f_ial_color;
} CAN_DVD_G_INFO;

typedef struct
{
	unsigned f_fl_window : 3;
	unsigned f_fr_window : 3;
	unsigned reserved : 2;
} _CAN_DVD_I_INFO_BYTE_0;

typedef union
{
	_CAN_DVD_I_INFO_BYTE_0 field;
	u8 byte;
} CAN_DVD_I_INFO_BYTE_0;

typedef struct
{
	unsigned f_rl_window : 3;
	unsigned f_rr_window : 3;
	unsigned reserved : 2;
} _CAN_DVD_I_INFO_BYTE_1;

typedef union
{
	_CAN_DVD_I_INFO_BYTE_1 field;
	u8 byte;
} CAN_DVD_I_INFO_BYTE_1;

typedef struct
{
	unsigned f_seat_court : 1;
	unsigned reserved : 3;
	unsigned f_seat_position : 4;
} _CAN_DVD_I_INFO_BYTE_3;

typedef union
{
	_CAN_DVD_I_INFO_BYTE_3 field;
	u8 byte;
} CAN_DVD_I_INFO_BYTE_3;

typedef struct
{
	CAN_DVD_I_INFO_BYTE_0 byte_0;
	CAN_DVD_I_INFO_BYTE_1 byte_1;
	u8 f_driver_seat_ctrl;
	CAN_DVD_I_INFO_BYTE_3 byte_3;
} CAN_DVD_I_INFO;

typedef struct
{
	CAN_DVD_1_INFO dvd_1_info;
	CAN_DVD_4_INFO dvd_4_info;
	CAN_DVD_8_INFO dvd_8_info;
	CAN_DVD_A_INFO dvd_A_info;
	CAN_ICM_DISP_INFO dvd_B_info;
	CAN_ICM_DISP_INFO dvd_E_info;
	CAN_DVD_F_INFO dvd_F_info;
	CAN_DVD_G_INFO dvd_G_info;
	CAN_DVD_I_INFO dvd_I_info;
} CAN_TX_INFO;

typedef struct
{
	unsigned f_can_sleep : 1;
	unsigned f_can_interrupt : 1;
	unsigned f_can_rx_data : 1;
	unsigned f_can_init : 1;
} _CAN_MAIN_FLAG;

typedef union
{
	_CAN_MAIN_FLAG field;
	u8 byte;
} CAN_MAIN_FLAG;

extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern u8 CanTxErrorCounter;
extern u8 CanNoTxCounter;
extern CAN_MAIN_FLAG CanMainFlag;
extern CAN_RX_INFO CanRxInfo;

extern u8 Haima8S_Keycode;
extern u8 Haima8S_SWC_SW;
extern u16 Haima8S_SWC_Timeout;

#define F_CAN_SLEEP CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT CanMainFlag.field.f_can_init

void Haima_8S_MainPro(void);
void Haima_8S_RxAppDataPro(u8 *buffer);
void Haima_8S_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length);
u8 Haima_8S_CheckTxMessage(u32 id, u8 *data);
void Haima_8S_CanReset(void);

#define DATAS_PER_FRAME 7

#endif
#endif
