#ifndef _CAN_POSITRON_VW_H_
#define _CAN_POSITRON_VW_H_
#if CAN_FUN_POSITRON_VW==1

#define CAN_RX_BUFFER_LENGTH 							400
#define CAN_TX_BUFFER_LENGTH 						600
#define CAN_TEST_BUFFER_LENGTH 							320



#define CAN_ID_BAM_CM                 	0x1CECFFFB
#define CAN_ID_BAM_DA            				0x1CEBFFFB
#define CAN_ID_TEST                 				0x18E6C864
#define CAN_ID_TEST_ANSWER            				0x18E664C8


#define CAN_ID_TIME            				0x18FEE6EE
#define CAN_ID_CL       					    0x18D0EE21
#define CAN_ID_VEHICLE      					0x18FFF621
#define CAN_ID_VEHICLE_ANSWER       					0x18FFF6FB
#define CAN_ID_PHYSICAL       						0x18DAFBFA
#define CAN_ID_PHYSICAL_ANSWER       				0x18DAFAFB
#define CAN_ID_FUNCTIONAL       					0x18DBFFFA
#define CAN_ID_FUNCTIONAL_ANSWER       				0x18DBFAFF

#define CAN_ID_INTERNET       						0x18EA00FA
#define CAN_ID_INTERNET_ANSWER       				0x18EAFA00

#define CAN_ID_DM1	       							0x18EAFB21
#define CAN_ID_DM1_ALL	       						0x18EAFF21
#define CAN_ID_DM1_ANSWER	       					0x18FECAFB

#define CAN_ID_BSG											0x18FF3B21


#define CAN_ID_ICH2									0x18FF3821

#define CAN_ID_NAVIGATION       					0x18FFD7FB
#define CAN_ID_PHONE_NAVI								0x18FFD8FB

#define CAN_ID_VEHICLE_SPEED						0x18FF2521
#define CAN_ID_PARKING_CAMERA					0x18FF3D21
#define CAN_ID_MM_CMD_01							0x18FF4090
#define CAN_ID_TEL_CMD_01							0x18FF4190
#define CAN_ID_MM_FBK_01							0x18FF50FB
#define CAN_ID_MM_FBK_02							0x18FF51FB
#define CAN_ID_MM_FBK_03							0x18FF52FB
#define CAN_ID_TEL_RSP_01							0x18FF56FB
#define CAN_ID_TRIP_METER							0x18FF6821
#define CAN_ID_INSTANCE								0x18FF6A21
#define CAN_ID_DRV_GRADE							0x18FF6B21
#define CAN_ID_TRIP_SPEED							0x18FF6C21
#define CAN_ID_TRIP_TIME									0x18FF7121
#define CAN_ID_ADJ_LEVEL							0x18FF7221
#define CAN_ID_ADJ_LEVEL_ANSWER				0x18FF72FB

#define CAN_ID_OIL_AUTO								0x18FF7821
#define CAN_ID_AXLE_WEIGHT					 0x18FFC821
#define CAN_ID_MAINT								0x18FFCE21

#define CAN_ID_USBNODE							0x18FFFF01


#define Positron_VW_RX_BASE_INO						0x20
#define Positron_VW_RX_SRC_INO						0x21
#define Positron_VW_RX_RAD_INO						0x22
#define Positron_VW_RX_VOL_INO						0x23
#define Positron_VW_RX_TEL_INO						0x24
#define Positron_VW_RX_MED_INO 						0x25
#define Positron_VW_RX_AXLEWEIGHT_INO				0x26
#define Positron_VW_RX_WEIGHT_INO					0x27
#define Positron_VW_RX_CONSUMP_INO					0x28
#define Positron_VW_RX_TRIP_INO						0x29
#define Positron_VW_RX_TRIP_TIME_INO				0x30
#define Positron_VW_RX_AUTONOMY_INO      			0x31
#define Positron_VW_RX_MAIN_INO           			0x32
#define Positron_VW_RX_DRV_GRADE_INO      			0x33
#define Positron_VW_RX_TEST_INO      				0x3B
#define Positron_VW_RX_CHECK_UDS_INO				0x35
#define Positron_VW_RX_SETTING_UDS_INO 				0x36
#define Positron_VW_RX_INFORMATION_UDS_INO 			0x37
#define Positron_VW_RX_LANGUAGE_INO 				0x38
#define Positron_VW_RX_CAMERA_INO 				0x3A
#define Positron_VW_RX_TEST_BT_INO 				0x3C
#define Positron_VW_RX_DATE_INO 				0x3D
#define Positron_VW_RX_TIME_INO 				0x3E
#define Positron_VW_RX_UDS_FLAG_INO 				0x42//0x3F
#define Positron_VW_RX_USB_MODE					0x43
#define Positron_VW_RX_PKS_INO					0x44












#define Positron_VW_TX_SRC_CMD						0x20
#define Positron_VW_TX_RADIO_CMD					0x21
#define Positron_VW_TX_TEL_CMD						0x22
#define Positron_VW_TX_AUTO_CMD						0x23
#define Positron_VW_TX_CON_SRC_CMD 				0x25
#define Positron_VW_TX_FILES_CMD					0x31
#define Positron_VW_TX_INF_CMD						0x33
#define Positron_VW_TX_UDS_CMD						0x34
#define Positron_VW_TX_VEHICLE_CMD				0x35
#define Positron_VW_TX_TEST_SET_CMD			  0x36
#define Positron_VW_TX_UDS_FLAG_CMD			  0x38
#define Positron_VW_TX_PKS_CMD			  0x39







#define Positron_VW_HEAD_CODE						0x2E

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
	SRC_CTRL_CMD_NONE=0x00,
	SRC_CTRL_CMD_RADIO_FM=0x01,
	SRC_CTRL_CMD_USB=0x03,
	SRC_CTRL_CMD_BT=0x04,
	SRC_CTRL_CMD_AA=0x05,
	SRC_CTRL_CMD_CP=0x06,
	SRC_CTRL_CMD_NUM
}SRC_CMD;

typedef enum
{
	CON_CTRL_CMD_NONE=0x00,
	CON_CTRL_CMD_CP=0x01,
	CON_CTRL_CMD_AA=0x02,
	CON_CTRL_CMD_NUM
}CON_CMD;

typedef enum
{
	INF_CTRL_CMD_NONE=0x00,
	INF_CTRL_CMD_ALL=0x01,
	INF_CTRL_CMD_SWITCH=0x02,
}INFL_CMD;

typedef enum
{
	AUT_CMD_NONE=0x00,
	AUT_CTRL_CMD_DOOR=0x01,
	AUT_CTRL_CMD_WIPER=0x02,
	AUT_CTRL_CMD_LANGUAGE=0x03,
	AUT_CTRL_CMD_NAVI=0x04,
}AUT_CMD;


	
typedef enum
{
	RADIO_CMD_NONE=0x00,
	RADIO_USER_CMD_SEEK=0x01,
	RADIO_USER_CMD_MEDIA=0x02,
	MEDIA_CMD_SRC=0x03,
	RADIO_CMD_CONTROL=0x04,
	MEDIA_CMD_CONTROL=0x05,
	RADIO_USER_CMD_MAX_VOL=0x06,
	RADIO_USER_CMD_CUR_VOL=0x07,
	RADIO_USER_AS_COUNTER,
	RADIO_CMD_NUM
}RADIO_CMD;
typedef enum
{
	TEL_CMD_NONE=0x00,
	TEL_CTRL_CMD_BAT=0x01,
	TEL_CTRL_CMD_NET=0x02,
	TEL_CTRL_CMD_PHONE=0x03,
	TEL_CTRL_CMD_FIE=0x04,
	TEL_CTRL_CMD_PTT,
	TEL_CMD_NUM
}TEL_CMD;

typedef enum
{
	FILE_CMD_NONE=0x00,
	FILE_CMD_MUSIC=0x01,
	FILE_CMD_NAVI_STREET=0x02,
	FILE_CMD_NAVI_DIS=0x03,
	FILE_CMD_NET=0x05,
	FILE_CMD_TEL,
	FILE_CMD_TIME_TEL,
	FILE_CMD_DTC_NUM_ACT,
	FILE_CMD_DTC_NUM_PAS,
	FILE_CMD_DTC_NUM_NEV,
	FILE_CMD_DTC_ACT,
	FILE_CMD_DTC_PAS,
	FILE_CMD_DTC_NEV,
	FILE_CMD_DTC_PA_ACT,
	FILE_CMD_DTC_NUM_PA_ACT,
	FILE_CMD_HW,
	FILE_CMD_VER_HW,
	FILE_CMD_SW,
	FILE_CMD_VER_SW,
	FILE_CMD_DM1=0x15,
	FILE_CMD_NAME_BT,
	FILE_CMD_CON_NAME_BT,
	FILE_CMD_BT_MAC,
	FILE_CMD_NET_MAC,
	FILE_CMD_NET_TCP,
	FILE_CMD_HD_VD_OP,
	FILE_CMD_LA_LO_DE,
	FILE_CMD_WIFI_MAC,
	FILE_CMD_BN,
	FILE_CMD_UN,
	FILE_CMD_TEST_MARK,
	FILE_CMD_MAN_TIME,
	FILE_CMD_MCU,
	FILE_CMD_NUM
}FILE_CMD;


typedef enum
{
	UDS_CMD_NONE=0x00,
	UDS_CMD_NAVI,
	UDS_CMD_NET,
	UDS_CMD_DRV,
	UDS_CMD_TRIP,
	UDS_CMD_DOOR,
	UDS_CMD_WEIG,
	UDS_CMD_PARKING_CAMERA,
	UDS_CMD_PARKING_SENSOR,
	UDS_CMD_UNIT_MENU,
	UDS_CMD_AD_ADB_BLUE,
	UDS_CMD_VOLKS,
	UDS_CMD_NUM
}UDS_CMD;


typedef enum
{
	VEHICLE_CMD_NONE=0x00,
	VEHICLE_CMD_TYPE=0x01,
	VEHICLE_CMD_DISP=0x02,
	VEHICLE_CMD_LANG,
	VEHICLE_CMD_UNI_DIS,
	VEHICLE_CMD_UNI_SPE,
	VEHICLE_CMD_UNI_PRE,
	VEHICLE_CMD_UNI_CON,
	VEHICLE_CMD_RESET,
	VEHICLE_CMD_AUTO_ILL,
	VEHICLE_CMD_NUM
}VEHICLE_CMD;

typedef enum
{
	TEST_CMD_TREBLE=0x00,
	TEST_CMD_MID=0x01,
	TEST_CMD_BASS=0x02,
	TEST_CMD_USB_CONNECT_TYPE=0x0C,
	TEST_CMD_GPS_STA,//d
	TEST_CMD_GPS_NUM,//e
	TEST_CMD_WIFI_CON_STA,//f
	TEST_BTN_STA,//10
	TEST_CMD_DISPLAY_STA,//11
	TEST_CMD_TOUCH_STA,//12
	TEST_CMD_TOUCH_LOC,//13
	TEST_CMD_GPS_SNR,//14
	TEST_CMD_MAF_VER,//15
	TEST_CMD_BEP_STA,//16
	TEST_CMD_WIF_STA,//17
	TEST_CMD_HOTSOPT_STA,//18
	TEST_CMD_ETH_STA,//19
	TEST_CMD_USB_STA,//1a
	TEST_CMD_BT_STA,//1b
	TEST_CMD_MIC_STA,//1c
	TEST_CMD_IGO_STA,//1d
	TEST_CMD_NUM
}TEST_CMD;


typedef enum
{
	CAN_POST_MSG_NONE=0,
	CAN_POST_MSG_HU_SRC_00,
	CAN_POST_MSG_HU_RAD_00,
	CAN_POST_MSG_HU_TEL_00,
	CAN_POST_MSG_HU_TEXT_00,
	CAN_POST_MSG_HU_ECL_S_00,
	CAN_POST_TEST,
	CAN_POST_DOOR,
	CAN_POST_WIPER,
	CAN_POST_TEXT,
	CAN_POST_UDS,
	CAN_POST_NAVI,
	CAN_POST_DM1,
	CAN_POST_DIS,
	CAN_POST_LANGUAGE,
	CAN_POST_TEL,
	CAN_POST_DA_BAM,
	CAN_POST_CM_BAM,
	CAN_POST_MSG_HU_DM1_00,
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
	u8 head;
	u8 tail;
	u8 length;
	CAN_MESSAGE_INFO message[CAN_TX_BUFFER_LENGTH];
}CAN_TX_15MS_BUFFER;
typedef struct
{
	u8 head;
	u8 tail;
	u8 length;
	CAN_MESSAGE_INFO message[CAN_TX_BUFFER_LENGTH];
}CAN_TX_200MS_BUFFER;

typedef struct
{
	u8 head;
	u8 tail;
	u8 length;
	CAN_MESSAGE_INFO message[CAN_TX_BUFFER_LENGTH];
}CAN_TX_1S_BUFFER;

typedef struct
{
	u8 head;
	u8 tail;
	u8 length;
	CAN_MESSAGE_INFO message[CAN_TX_BUFFER_LENGTH];
}CAN_TX_60MS_BUFFER;

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
	unsigned f_power:2;	
	unsigned f_parking:2;
	unsigned reserved_12:4;	
}_CAN_BASE_INFO_BYTE_0;

typedef union
{
	_CAN_BASE_INFO_BYTE_0 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_0;





typedef struct
{	
	CAN_BASE_INFO_BYTE_0 byte_0;
	u8 f_sel_sta_mem;
	u8 f_ill;
}CAN_BASE_INFO;

typedef struct
{	
	u8 navi_icon ;
	u8 navi_line1[16] ;
	u8 navi_line2[16] ;
}CAN_NAVI_INFO;

typedef struct
{	
	u8 years;
	u8 months;
	u8 days;
}CAN_DATE_INFO;

typedef struct
{	
	u8 hours;
	u8 minutes;
}CAN_TIME_INFO;

typedef struct
{
	unsigned f_med_con:5;
	unsigned f_med_up:1;
	unsigned f_cp_med_up:1;
}_CAN_MED_INFO_BYTE_0;

typedef union
{
	_CAN_MED_INFO_BYTE_0 field;
	u8 byte;
}CAN_MED_INFO_BYTE_0;



typedef struct
{	
	CAN_MED_INFO_BYTE_0 byte_0;
}CAN_MED_INFO;


typedef struct
{	
	unsigned dri_time_hour_h:6 ;
	unsigned f_reserved_47:2;	
}_CAN_TRIP_TIME_INFO_0;

typedef union
{
	_CAN_TRIP_TIME_INFO_0 field;
	u8 byte;
}CAN_TRIP_TIME_INFO_0;


typedef struct
{	
	unsigned tra_time_hour_h:6 ;
	unsigned f_reserved_16:2;	
}_CAN_TRIP_TIME_INFO_1;

typedef union
{
	_CAN_TRIP_TIME_INFO_1 field;
	u8 byte;
}CAN_TRIP_TIME_INFO_1;

typedef struct
{	
	u8 dri_time_hour_l;
	u8 dri_time_min;
	u8 tra_time_hour_l;
	u8 tra_time_min;
	CAN_TRIP_TIME_INFO_0 byte_0;
	CAN_TRIP_TIME_INFO_1 byte_1;
}CAN_TRIP_TIME_INFO;


typedef struct
{	
	u8 band;
	u8 slot;
	u8 fre_h;
	u8 fre_l;
}CAN_STORE_INFO;

typedef struct
{	
	unsigned f_vo_h:1 ;
	unsigned reverse_1:7;	
}_CAN_UDS_ERROR_INFO_0;

typedef union
{
	_CAN_UDS_ERROR_INFO_0 field;
	u8 byte;
}CAN_UDS_ERROR_INFO_0;

typedef struct
{	
	unsigned f_vo_l:1;	
	unsigned reverse_1:7;	
}_CAN_UDS_ERROR_INFO_1;

typedef union
{
	_CAN_UDS_ERROR_INFO_1 field;
	u8 byte;
}CAN_UDS_ERROR_INFO_1;

typedef struct
{	
	unsigned f_tune:1;	
	unsigned reverse_1:7;	
}_CAN_UDS_ERROR_INFO_2;

typedef union
{
	_CAN_UDS_ERROR_INFO_2 field;
	u8 byte;
}CAN_UDS_ERROR_INFO_2;

typedef struct
{	
	unsigned f_dsp:1;
	unsigned reverse_1:7;	
}_CAN_UDS_ERROR_INFO_3;

typedef union
{
	_CAN_UDS_ERROR_INFO_3 field;
	u8 byte;
}CAN_UDS_ERROR_INFO_3;

typedef struct
{	

	CAN_UDS_ERROR_INFO_0 byte_0;
	CAN_UDS_ERROR_INFO_1 byte_1;
	CAN_UDS_ERROR_INFO_2 byte_2;
	CAN_UDS_ERROR_INFO_3 byte_3;
	
	
}CAN_UDS_ERROR_INFO;


typedef struct
{	
	unsigned rd_act_num:1 ;
	unsigned rd_pas_num:1;	
	unsigned rd_not_ocr_num:1;
	unsigned rd_act:1 ;
	unsigned rd_pas:1;	
	unsigned rd_not_ocr:1;
	unsigned rd_act_pas_num:1;
	unsigned rd_act_pas:1;
}_CAN_UDS_INFO_0;

typedef union
{
	_CAN_UDS_INFO_0 field;
	u8 byte;
}CAN_UDS_INFO_0;

typedef struct
{	
	unsigned vehc_type:4 ;
	unsigned navi_offline: 1;
	unsigned net_con:1;
	unsigned dri_gra_en:1;
	unsigned tri_veh_en:1;
}_CAN_UDS_INFO_1;

typedef union
{
	_CAN_UDS_INFO_1 field;
	u8 byte;
}CAN_UDS_INFO_1;

typedef struct
{	
	unsigned door_en:1 ;
	unsigned wipe_en:1 ;
	unsigned wei_en:1 ;
	unsigned lev_en:1 ;	
	unsigned camera_en:1;
	unsigned sensor_en:1;
	unsigned unit_en:1;
	unsigned ad_blue_auto_en:1;
}_CAN_UDS_INFO_2;

typedef union
{
	_CAN_UDS_INFO_2 field;
	u8 byte;
}CAN_UDS_INFO_2;

typedef struct
{	
	unsigned navi_offline_req: 1;
	unsigned net_con_req:1;
	unsigned dri_gra_req:1;
	unsigned tri_veh_req:1;
	unsigned wip_dor_req:1;
	unsigned wei_lev_req:1;
	unsigned camera_req:1;
	unsigned sensor_req:1;
}_CAN_UDS_INFO_3;

typedef union
{
	_CAN_UDS_INFO_3 field;
	u8 byte;
}CAN_UDS_INFO_3;

typedef struct
{	
	unsigned hard_num_req:1 ;
	unsigned hard_ver_num_req:1;	
	unsigned soft_num_req:1;
	unsigned soft_ver_num_req:1;
	unsigned dm1_req:1;
	unsigned model_req:1;
	unsigned unit_menu_req:1;
	unsigned ad_blue_auto_req:1;
}_CAN_UDS_INFO_4;

typedef union
{
	_CAN_UDS_INFO_4 field;
	u8 byte;
}CAN_UDS_INFO_4;

typedef struct
{	
	unsigned chome_volks_en:1 ;
}_CAN_UDS_INFO_5;

typedef union
{
	_CAN_UDS_INFO_5 field;
	u8 byte;
}CAN_UDS_INFO_5;

typedef struct
{	
	unsigned chome_volks_req:1 ;
}_CAN_UDS_INFO_6;

typedef union
{
	_CAN_UDS_INFO_6 field;
	u8 byte;
}CAN_UDS_INFO_6;

typedef struct
{	
	u8 length;
	u8 sid;
	u8 mode_h;
	u8 mode_l;
	u8 d[6];
	u8 dtc_h;
	u8 dtc_m;
	u8 dtc_l;
	CAN_UDS_INFO_0 byte_0;
	CAN_UDS_INFO_1 byte_1;
	CAN_UDS_INFO_2 byte_2;	
	CAN_UDS_INFO_3 byte_3;
	CAN_UDS_INFO_4 byte_4;	
	CAN_UDS_INFO_5 byte_5;
	CAN_UDS_INFO_6 byte_6;
}CAN_UDS_INFO;


typedef struct
{
	unsigned f_set_radio:8;		
}_CAN_RADIO_INFO_BYTE_0;
typedef union
{
	_CAN_RADIO_INFO_BYTE_0 field;
	u8 byte;
}CAN_RADIO_INFO_BYTE_0;

typedef struct
{	
	CAN_RADIO_INFO_BYTE_0 byte_0;
	
	
}CAN_RAD_INFO;

typedef struct
{
	unsigned f_src_select:4;	
	unsigned reserved_17:4;	
}_CAN_SOURCE_INFO_BYTE_0;

typedef union
{
	_CAN_SOURCE_INFO_BYTE_0 field;
	u8 byte;
}CAN_SOURCE_INFO_BYTE_0;
typedef struct
{	
	CAN_SOURCE_INFO_BYTE_0 byte_0;
}CAN_SRC_INFO;


typedef struct
{
	unsigned f_set_vol:2;	
	unsigned reserved_18:2;	
	unsigned f_set_vol_sta:1;
	unsigned reserved_19:3;	
}_CAN_VOL_INFO_BYTE_0;

typedef union
{
	_CAN_VOL_INFO_BYTE_0 field;
	u8 byte;
}CAN_VOL_INFO_BYTE_0;





typedef struct
{	
	CAN_VOL_INFO_BYTE_0 byte_0;
}CAN_VOL_INFO;


typedef struct
{
	unsigned f_tel_cmd:5;	
	unsigned reserved_19:1;
	unsigned f_tel_up:1;	
	unsigned f_tel_cp_up:1;
}_CAN_TEL_INFO_BYTE_0;

typedef union
{
	_CAN_TEL_INFO_BYTE_0 field;
	u8 byte;
}CAN_TEL_INFO_BYTE_0;




typedef struct
{	
	CAN_TEL_INFO_BYTE_0 byte_0;
}CAN_TEL_INFO;



typedef struct
{	
	unsigned f_wipe :1 ;
	unsigned f_door_open_sta:1 ;
	unsigned totalweight_sta:1;	
	unsigned main_typ:2;
}_CAN_VEHICLE_INFO_BYTE_0;//bit 0 1 empty change data type

typedef union
{
	_CAN_VEHICLE_INFO_BYTE_0 field;
	u8 byte;
}CAN_VEHICLE_INFO_BYTE_0;





typedef struct
{	
	CAN_VEHICLE_INFO_BYTE_0 byte_0;
	

	
}CAN_VEHICLE_INFO;


typedef struct
{	
	unsigned f_language:3 ;
}_CAN_LANGUAGE_INFO_BYTE_0;

typedef union
{
	_CAN_LANGUAGE_INFO_BYTE_0 field;
	u8 byte;
}CAN_LANGUAGE_INFO_BYTE_0;

typedef struct
{	
	unsigned f_dis_md:2 ;
}_CAN_LANGUAGE_INFO_BYTE_1;

typedef union
{
	_CAN_LANGUAGE_INFO_BYTE_1 field;
	u8 byte;
}CAN_LANGUAGE_INFO_BYTE_1;

typedef struct
{	
	unsigned f_dis_uni:1 ;
	unsigned f_spe_uni:1 ;
	unsigned f_pre_uni:1 ;
	unsigned f_con_uni:2 ;
}_CAN_LANGUAGE_INFO_BYTE_2;

typedef union
{
	_CAN_LANGUAGE_INFO_BYTE_2 field;
	u8 byte;
}CAN_LANGUAGE_INFO_BYTE_2;



typedef struct
{	
	CAN_LANGUAGE_INFO_BYTE_0 byte_0;
	CAN_LANGUAGE_INFO_BYTE_1 byte_1;
	CAN_LANGUAGE_INFO_BYTE_2 byte_2;

	
}CAN_LANGUAGE_INFO;

typedef struct
{	
	unsigned main_remain_sta:1;
	unsigned f_reserved_20:7;	
}_CAN_REMAIN_INFO_BYTE_0;

typedef union
{
	_CAN_REMAIN_INFO_BYTE_0 field;
	u8 byte;
}CAN_REMAIN_INFO_BYTE_0;

typedef struct
{	
	u8 main_remain_dt_l;
	u8 main_remain_dt_h;
	CAN_REMAIN_INFO_BYTE_0 byte_0;
}CAN_REMAIN_INFO;


typedef struct
{	
	unsigned auto_dt_h:6 ;
	unsigned f_reserved_21:2;	
}_CAN_AUTO_INFO_BYTE_0;

typedef union
{
	_CAN_AUTO_INFO_BYTE_0 field;
	u8 byte;
}CAN_AUTO_INFO_BYTE_0;

typedef struct
{	
	unsigned ad_blue_auto_dt_h:6 ;
	unsigned f_reserved_22:2;	
}_CAN_AUTO_INFO_BYTE_1;

typedef union
{
	_CAN_AUTO_INFO_BYTE_1 field;
	u8 byte;
}CAN_AUTO_INFO_BYTE_1;

typedef struct
{	
	u8 auto_dt;
	u8 ad_blue_auto_dt;
	CAN_AUTO_INFO_BYTE_0 byte_0;
	CAN_AUTO_INFO_BYTE_1 byte_1;
	
}CAN_AUTO_INFO;


typedef struct
{	
	unsigned instant_con_h:2 ;
	unsigned avg_con_h:2 ;
	unsigned fuel_liter_h:2 ;
	unsigned f_reserved_23:2;	
}_CAN_CONSUMP_INFO_BYTE_0;

typedef union
{
	_CAN_CONSUMP_INFO_BYTE_0 field;
	u8 byte;
}CAN_CONSUMP_INFO_BYTE_0;

typedef struct
{	
	u8 instant_con;
	u8 avg_con;
	u8 fuel_liter;
	CAN_CONSUMP_INFO_BYTE_0 byte_0;
}CAN_CONSUMP_INFO;

typedef struct
{	
	unsigned axleweight1_h:2 ;
	unsigned axleweight2_h:2 ;
	unsigned axleweight3_h:2 ;
	unsigned axleweight4_h:2 ;
}_CAN_AXLEWEIGHT_INFO_BYTE_0;

typedef union
{
	_CAN_AXLEWEIGHT_INFO_BYTE_0 field;
	u8 byte;
}CAN_AXLEWEIGHT_INFO_BYTE_0;

typedef struct
{	
	unsigned axleweight1_st:1 ;
	unsigned axleweight2_st:1 ;
	unsigned axleweight3_st:1 ;
	unsigned axleweight4_st:1 ;
}_CAN_AXLEWEIGHT_INFO_BYTE_1;

typedef union
{
	_CAN_AXLEWEIGHT_INFO_BYTE_1 field;
	u8 byte;
}CAN_AXLEWEIGHT_INFO_BYTE_1;

typedef struct
{	
	u8 axleweight1;
	u8 axleweight2;
	u8 axleweight3;
	u8 axleweight4;
	CAN_AXLEWEIGHT_INFO_BYTE_0 byte_0 ;
	CAN_AXLEWEIGHT_INFO_BYTE_1 byte_1 ;
}CAN_AXLEWEIGHT_INFO;

 
typedef struct
{	
	unsigned level_adj_h:6 ;
	unsigned f_reserved_23:2;	
}_CAN_WEIGHT_INFO_BYTE_0;

typedef union
{
	_CAN_WEIGHT_INFO_BYTE_0 field;
	u8 byte;
}CAN_WEIGHT_INFO_BYTE_0;


typedef struct
{	
	unsigned totalweight_h:2 ;
	unsigned f_reserved_24:6;	
}_CAN_WEIGHT_INFO_BYTE_1;

typedef union
{
	_CAN_WEIGHT_INFO_BYTE_1 field;
	u8 byte;
}CAN_WEIGHT_INFO_BYTE_1;

typedef struct
{	
	u8  level_adj;
	u8 totalweight;
	CAN_WEIGHT_INFO_BYTE_0 byte_0;
	CAN_WEIGHT_INFO_BYTE_1 byte_1;
}CAN_WEIGHT_INFO;

typedef struct
{	
	u8 	drive_avg_grad_bar;
	u8 	drive_grad_acc;
	u8 	drive_grad_gear;
	u8 	drive_grad_brak;
	
}CAN_GRAD_INFO;


typedef struct
{	
	unsigned trip_avg_speed_h:4 ;
	unsigned trip_meter_h:1 ;
	unsigned f_reserved_25:3;	
}_CAN_SPEED_INFO_BYTE_0;

typedef union
{
	_CAN_SPEED_INFO_BYTE_0 field;
	u8 byte;
}CAN_SPEED_INFO_BYTE_0;

typedef struct
{	
	u8 vehicle_speed;
	u8 trip_avg_speed;
	CAN_SPEED_INFO_BYTE_0 byte_0;
	u8 trip_meter_l;
	u8 trip_meter_m;
}CAN_SPEED_INFO;


typedef struct
{			
	unsigned f_parking_brake:2;
	unsigned reserved_26:6;
	
}_CAN_GEAR_BYTE_0;

typedef union
{
	_CAN_GEAR_BYTE_0 field;
	u8 byte;
}CAN_GEAR_BYTE_0;

typedef struct
{	
	CAN_GEAR_BYTE_0 byte_0;
}CAN_GEAR_INFO;






typedef struct
{	
	u8 pid;
	u8 sid;
}CAN_TEST_INFO;


typedef struct
{	
	u8 order;
	u8 minus;
	u8 gain;
}CAN_TEST_SETTING_INFO;









typedef struct
{	
	u8 set_hour;
	u8 set_min;
}CAN_CLOCK_INFO;


typedef struct
{		
	unsigned re_sys:1;
	unsigned re_sen:1;
	unsigned re_fre:1;
	unsigned re_band:1;
}_CAN_RADIO_BYTE_0;


typedef union
{
	_CAN_RADIO_BYTE_0 field;
	u8 byte;
}CAN_RADIO_BYTE_0;


typedef struct
{	
	unsigned clr_band:5;
}_CAN_RADIO_BYTE_1;


typedef union
{
	_CAN_RADIO_BYTE_1 field;
	u8 byte;
}CAN_RADIO_BYTE_1;


typedef struct
{	
	u8 set_radio;
	u8 set_sen;
	u8 set_fre_h;
	u8 set_fre_l;
	u8 set_band;
	u8 set_loud;
	u8 set_seek;//2
	u8 set_search_band;//5
	CAN_RADIO_BYTE_0 byte_0;	
	CAN_RADIO_BYTE_0 byte_1;	
}CAN_RADIO_INFO;


typedef struct
{	
	u8 sta;
	u8 set_sen;
	u8 set_fre_h;
	u8 set_fre_l;
	u8 set_band;
	u8 set_loud;
	u8 set_seek;//2
	u8 set_search_band;//5		
}CAN_BT_INFO;

typedef struct
{	
	u8 r_inten;
	u8 l_inten;
	u8 r_exten;
	u8 l_exten;
		
}CAN_CAMERA_INFO;


typedef struct
{	
	unsigned req_bt_name:1;
	unsigned req_con_bt_name:1;	
	unsigned req_bt_mac:1;	
	unsigned req_usb_con:1;	
	unsigned req_clear_bt_con:1;	
}_CAN_REQ_INFO_0;

typedef union
{
	_CAN_REQ_INFO_0 field;
	u8 byte;
}CAN_REQ_INFO_0;

typedef struct
{	
	CAN_REQ_INFO_0 byte_0;
		
}CAN_REQ_INFO;



typedef struct
{	

	CAN_BASE_INFO base_info;
	CAN_BASE_INFO base_info_bak;
	CAN_MED_INFO med_info;
	CAN_MED_INFO med_info_bak;
	CAN_GEAR_INFO gear_info;
	CAN_GEAR_INFO gear_info_bak;
	CAN_TEL_INFO tel_info;
	CAN_TEL_INFO tel_info_bak;
	CAN_VOL_INFO vol_info;
	CAN_VOL_INFO vol_info_bak;
	CAN_VEHICLE_INFO vehicle_info;
	CAN_VEHICLE_INFO vehicle_info_bak;
	CAN_LANGUAGE_INFO language_info;
	CAN_LANGUAGE_INFO language_info_bak;
	CAN_TEST_INFO test_info;
	CAN_TEST_INFO test_info_bak;
	CAN_REQ_INFO req_info;
	CAN_REQ_INFO req_info_bak;
	CAN_UDS_INFO uds_info;
	CAN_UDS_INFO uds_info_bak;
	CAN_UDS_ERROR_INFO uds_error_info;
	CAN_UDS_ERROR_INFO uds_error_info_bak;
	CAN_NAVI_INFO navi_info;
	CAN_NAVI_INFO navi_info_bak;
	CAN_CAMERA_INFO camera_info;
	CAN_CAMERA_INFO camera_info_bak;
	CAN_TIME_INFO time_info;
	CAN_TIME_INFO time_info_bak;
	CAN_DATE_INFO date_info;
	CAN_DATE_INFO date_info_bak;
	
	

	CAN_REMAIN_INFO remain_info;
	CAN_REMAIN_INFO remain_info_bak;
	CAN_CONSUMP_INFO consump_info;
	CAN_CONSUMP_INFO consump_info_bak;
	CAN_AUTO_INFO			auto_info;
	CAN_AUTO_INFO			auto_info_bak;
	CAN_TRIP_TIME_INFO trip_time_info;
	CAN_TRIP_TIME_INFO trip_time_info_bak;
	CAN_SPEED_INFO speed_info;
	CAN_SPEED_INFO speed_info_bak;
	CAN_WEIGHT_INFO weight_info;
	CAN_WEIGHT_INFO weight_info_bak;
	CAN_AXLEWEIGHT_INFO axleweight_info;
	CAN_AXLEWEIGHT_INFO axleweight_info_bak;
	CAN_GRAD_INFO grad_info;
	CAN_GRAD_INFO	grad_info_bak;
	CAN_RAD_INFO rad_info;
	CAN_RAD_INFO rad_info_bak;
	CAN_SRC_INFO src_info;
	CAN_SRC_INFO src_info_bak;
	CAN_STORE_INFO store_info;
	CAN_STORE_INFO store_info_bak;

	CAN_CLOCK_INFO clock_info;
	CAN_CLOCK_INFO clock_info_bak;
	CAN_RADIO_INFO radio_info;
	CAN_RADIO_INFO radio_info_bak;	

	CAN_TEST_SETTING_INFO test_set_info;
	CAN_TEST_SETTING_INFO test_set_info_bak;
	

	
}CAN_RX_INFO;


typedef struct
{	
	u8 pid;
	u8 d[8];
}CAN_TX_HU_TEST;


typedef struct
{		
	u8 d[8];
}CAN_TX_HU_UDS;


typedef struct
{	
	
	u8 act_num;
	u8 pas_num;
	u8 act_pas_num;
	u8 no_ocr_num;
	u8 dtc[160];
	u8 pas_dtc[12];
	u8 act_pas_dtc[12];
	u8 no_ocr_dtc[21];
	u8 num[160];
	u8 d[8];
	u8 dm[8];
}CAN_TX_HU_TEXT;


typedef struct
{	
	u8 navi_icon ;
	u8 navi_line1[16] ;
	u8 navi_line2[16] ;
}CAN_TX_HU_NAVI;


typedef struct
{
	unsigned reserved_2:3;
	unsigned f_bt:1;	
	unsigned f_usb:1;
	unsigned reserved_77:1;
	unsigned f_aa:1;
	unsigned f_cp:1;
}_CAN_HU_SRC_BYTE_0;


typedef union
{
	_CAN_HU_SRC_BYTE_0 field;
	u8 byte;
}CAN_HU_SRC_BYTE_0;


typedef struct
{
	unsigned reserved_7:3;	
	unsigned f_bt_aud_pared:1;	
	unsigned f_usb_con:1;
	unsigned reserved_3:1;
	unsigned f_aa_con:1;
	unsigned f_cp_con:1;	
}_CAN_HU_SRC_BYTE_1;


typedef union
{
	_CAN_HU_SRC_BYTE_1 field;
	u8 byte;
}CAN_HU_SRC_BYTE_1;


typedef struct
{
	unsigned f_fm:1;
	unsigned reserved_4:4;
	unsigned f_am_and_mw:1;		
	//unsigned reserved_77:2;
}_CAN_SOURCE_BYTE_2;


typedef union
{
	_CAN_SOURCE_BYTE_2 field;
	u8 byte;
}CAN_HU_SRC_BYTE_2;


typedef struct
{
	
	unsigned reserved_5:7;
	unsigned f_bt:1;		
}_CAN_SOURCE_BYTE_3;

typedef union
{
	_CAN_SOURCE_BYTE_3 field;
	u8 byte;
}CAN_HU_SRC_BYTE_3;


typedef struct
{
unsigned reserved_6:3;
	unsigned f_usb:1;
	//unsigned reserved_77:4;
	
	
}_CAN_SOURCE_BYTE_4;


typedef union
{
	_CAN_SOURCE_BYTE_4 field;
	u8 byte;
}CAN_HU_SRC_BYTE_4;


typedef struct
{
	unsigned f_preset_dig:8;
	
}_CAN_SOURCE_BYTE_5;


typedef union
{
	_CAN_SOURCE_BYTE_5 field;
	u8 byte;
}CAN_HU_SRC_BYTE_5;


typedef struct
{
	unsigned f_pow_mode_res:2;
	unsigned f_src_sel_res:6;		
	
}_CAN_SOURCE_BYTE_6;


typedef union
{
	_CAN_SOURCE_BYTE_6 field;
	u8 byte;
}CAN_HU_SRC_BYTE_6;


typedef struct
{	
	CAN_HU_SRC_BYTE_0 byte_0;
	CAN_HU_SRC_BYTE_1 byte_1;
	CAN_HU_SRC_BYTE_2 byte_2;
	CAN_HU_SRC_BYTE_3 byte_3;
	CAN_HU_SRC_BYTE_4 byte_4;
	CAN_HU_SRC_BYTE_5 byte_5;
	CAN_HU_SRC_BYTE_6 byte_6;
}CAN_HU_SRC_S_00;


typedef struct
{
	u8 f[8];
}CAN_HU_SRC_F_00;


typedef struct
{
	unsigned f_cur_vol:8;		
	
}_CAN_HU_RAD_BYTE_0;


typedef union
{
	_CAN_HU_RAD_BYTE_0 field;
	u8 byte;
}CAN_HU_RAD_BYTE_0;


typedef struct
{
	unsigned f_max_vol:8;	
	
}_CAN_HU_RAD_BYTE_1;


typedef union
{
	_CAN_HU_RAD_BYTE_1 field;
	u8 byte;
}CAN_HU_RAD_BYTE_1;


typedef struct
{
	unsigned f_rad_fb:8;

	
	
}_CAN_HU_RAD_BYTE_2;


typedef union
{
	_CAN_HU_RAD_BYTE_2 field;
	u8 byte;
}CAN_HU_RAD_BYTE_2;


typedef struct
{
		unsigned f_med_fb:8;		
}_CAN_HU_RAD_BYTE_3;


typedef union
{
	_CAN_HU_RAD_BYTE_3 field;
	u8 byte;
}CAN_HU_RAD_BYTE_3;


typedef struct
{
	unsigned f_rad_seek:4;
	unsigned reserved_8:4;

}_CAN_HU_RAD_BYTE_4;


typedef union
{
	_CAN_HU_RAD_BYTE_4 field;
	u8 byte;
}CAN_HU_RAD_BYTE_4;


typedef struct
{
	unsigned reserved_9:4;
	unsigned f_med_inf :4 ;
}_CAN_HU_RAD_BYTE_5;

typedef union
{
	_CAN_HU_RAD_BYTE_5 field;
	u8 byte;
}CAN_HU_RAD_BYTE_5;


typedef struct
{	
	CAN_HU_RAD_BYTE_0 byte_0;
	CAN_HU_RAD_BYTE_1 byte_1;
	CAN_HU_RAD_BYTE_2 byte_2;
	CAN_HU_RAD_BYTE_3 byte_3;
	CAN_HU_RAD_BYTE_4 byte_4;
	CAN_HU_RAD_BYTE_5 byte_5;	
	u8 RADIO_AS_COUNTER;
}CAN_HU_RAD_S_00;


typedef struct
{
	unsigned f_tel_sta:8;			
}_CAN_HU_TEL_BYTE_0;


typedef union
{
	_CAN_HU_TEL_BYTE_0 field;
	u8 byte;
}CAN_HU_TEL_BYTE_0;


typedef struct
{
	unsigned f_pow_sta:7;
	unsigned f_chg_sta:1 ;
}_CAN_HU_TEL_BYTE_1;


typedef union
{
	_CAN_HU_TEL_BYTE_1 field;
	u8 byte;
}CAN_HU_TEL_BYTE_1;


typedef struct
{
	unsigned f_fie_str:8;	
}_CAN_HU_TEL_BYTE_2;


typedef union
{
	_CAN_HU_TEL_BYTE_2 field;
	u8 byte;
}CAN_HU_TEL_BYTE_2;


typedef struct
{
	
		unsigned f_tel_sta:3;
		unsigned f_net_sta:2;
		unsigned f_call_mod:1;
		unsigned f_ptt_act:1;
		unsigned reserved_10:1;	
}_CAN_HU_TEL_BYTE_3;


typedef union
{
	_CAN_HU_TEL_BYTE_3 field;
	u8 byte;
}CAN_HU_TEL_BYTE_3;


typedef struct
{
	unsigned f_bt_sta:3;
	unsigned reserved_11:5;
}_CAN_HU_TEL_BYTE_4;


typedef union
{
	_CAN_HU_TEL_BYTE_4 field;
	u8 byte;
}CAN_HU_TEL_BYTE_4;


typedef struct
{
	unsigned f_com_data:8;
}_CAN_HU_TEL_BYTE_5;


typedef union
{
	_CAN_HU_TEL_BYTE_5 field;
	u8 byte;
}CAN_HU_TEL_BYTE_5;


typedef struct
{	
	CAN_HU_TEL_BYTE_0 byte_0;
	CAN_HU_TEL_BYTE_1 byte_1;
	CAN_HU_TEL_BYTE_2 byte_2;
	CAN_HU_TEL_BYTE_3 byte_3;
	CAN_HU_TEL_BYTE_4 byte_4;
	CAN_HU_TEL_BYTE_5 byte_5;
}CAN_HU_TEL_S_00;


typedef struct
{
	unsigned f_bat:7;	
	unsigned f_bat_con:1;	
}_CAN_HU_BAT_BYTE_0;


typedef union
{
	_CAN_HU_BAT_BYTE_0 field;
	u8 byte;
}CAN_HU_BAT_BYTE_0;


typedef struct
{	
	CAN_HU_BAT_BYTE_0 byte_0;	
}CAN_HU_BAT_S_00;


typedef struct
{
	unsigned f_ecl:7;	
}_CAN_HU_ECL_BYTE_0;


typedef union
{
	_CAN_HU_ECL_BYTE_0 field;
	u8 byte;
}CAN_HU_ECL_BYTE_0;


typedef struct
{	
	CAN_HU_ECL_BYTE_0 byte_0;
}CAN_HU_ECL_S_00;


typedef struct
{
	unsigned f_con:1;	
	unsigned f_reset:1;	
	unsigned f_door:1;	
	unsigned f_wiper:1;
	unsigned f_dis:2;
	unsigned spe_uni:1;
	unsigned pre_uni:1;
}_CAN_HU_AUT_BYTE_0;


typedef union
{
	_CAN_HU_AUT_BYTE_0 field;
	u8 byte;
}CAN_HU_AUT_BYTE_0;

typedef struct
{
	unsigned dis_uni:1;	
	unsigned language:3;	
}_CAN_HU_AUT_BYTE_1;


typedef union
{
	_CAN_HU_AUT_BYTE_1 field;
	u8 byte;
}CAN_HU_AUT_BYTE_1;


typedef struct
{	
	CAN_HU_AUT_BYTE_0 byte_0;
	CAN_HU_AUT_BYTE_1 byte_1;
	u8 f_ill;
}CAN_HU_AUT_S_00;










typedef struct
{
	CAN_HU_SRC_S_00 hu_src_0;
	CAN_HU_RAD_S_00 hu_rad_0;
	CAN_HU_TEL_S_00 hu_tel_0;
	CAN_HU_BAT_S_00 hu_bat_0;
	CAN_HU_ECL_S_00 hu_ecl_0;
	CAN_HU_AUT_S_00 hu_aut_0;
	CAN_TX_HU_TEST hu_tes_0;
	CAN_TX_HU_TEXT hu_tex_0;
	CAN_TX_HU_UDS hu_uds_0;
	CAN_TX_HU_NAVI hu_navi_0;	
		

}CAN_TX_INFO;
extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_TX_15MS_BUFFER CanTxBuffer3;
extern CAN_TX_200MS_BUFFER CanTxBuffer4;
extern CAN_TX_1S_BUFFER CanTxBuffer5;
extern CAN_TX_60MS_BUFFER CanTxBuffer6;
extern CAN_TX_INFO CanTxInfo;
extern CAN_MAIN_FLAG CanMainFlag;
extern u8 uds_power_flag;
extern u8 uds_time;
extern u8 Uds_error;
extern u16		UdsTimer;
extern u8 DM1_flag;
extern u8 dm_flag;
extern u8 A_ILL_Flag;
extern u8 BSG_off_flag;
extern u8 ACC_ex_BSG_flag;
extern u8 send_add;


typedef enum
{
	FLAG_rev_INIT=0,
	FLAG_rev_level0=1,
	FLAG_rev_level1=2,
	FLAG_rev_level2=3,
	FLAG_rev_level3=4,
	FLAG_rev_PKS=5,
	BEEP_OVER=6
}DSP_MODE;

extern DSP_MODE beep_status;
extern u8 flag_camere_start;
extern u8 RST_BSP_FLAG;
extern CAN_RX_INFO CanRxBuffer_bak;
extern u8 PKS_OK;
extern u8 test_flag;

extern u8 DTC_DSP_flag;
extern u8 DTC_TUNER_flag;









void Positron_VW_Rx_Message(void);

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init
void Positron_VW_MainPro(void);
void Positron_VW_UdsPro(void);
void Positron_VW_AutoTestPro(void);
void Positron_VW_AutoTestStartCheck(void);
void Positron_VW_AutoTestCheck(void);
void Positron_VW_ManySendmessage(void);
void Positron_VW_BamSendmessage(void);
void  Positron_VW_AutoTestSendmessage(void);
void Positron_VW_UDS_Security(void);
void Positron_VW_RxAppDataPro(u8 *buffer);
void Positron_VW_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
void encipher( u8 *seed, u8 *c_key);
#endif
#endif
