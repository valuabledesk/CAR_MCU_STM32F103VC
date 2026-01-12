#ifndef _CAN_PEUGEOT_207_H_
#define _CAN_PEUGEOT_207_H_

#if CAN_FUN_PEUGEOT_207==1

#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		((u8)100)

#define CAN_ID_NMM_C_1				0x08F
#define CAN_ID_CCNC1_C				0x10F
#define CAN_ID_FEI_F				0x11B
#define CAN_ID_NMM_C_2				0x181
#define CAN_ID_MTC_SGL				0x188
#define CAN_ID_BACKL_IC				0x197
#define CAN_ID_CCNGW1_C				0x20F
#define CAN_ID_VIN1_MM				0x210
#define CAN_ID_LS_BCM_HS3			0x241
#define CAN_ID_ICN_INFO1			0x248
#define CAN_ID_VIN2_MM				0x250
#define CAN_ID_PASD_C				0x280
#define CAN_ID_VIN3_MM				0x2D0
#define CAN_ID_FAM_INFO				0x2C2
#define CAN_ID_FDS_D				0x319
#define CAN_ID_RDS_R				0x31A
#define CAN_ID_CLUSTER_ODO			0x361
#define CAN_ID_FOS_F				0x384
#define CAN_ID_ROS_R				0x388
#define CAN_ID_BCM_EMS67			0x443
#define CAN_ID_BCM_PAS				0x539
#define CAN_ID_LS_BCM_OS			0x541
#define CAN_ID_FAM_OS				0x542

#define CAN_ID_TEMP_AMBT			0x364
#define CAN_ID_MMS_TIME_DATE		0x3E2

#define CAN_ID_CCN_TPMS_SMS		0x308
#define CAN_ID_CCN_TPMS_ECO		0x40F
#define CAN_ID_CCN_TPMS_COMMON	0x40F

/*****TX_ID*************/
#define CAN_ID_MMS_MESSAGE			0x362



#define PEUGEOT_207_HEAD_CODE		0x2E

#define PEUGEOT_207_RX_BASE_INFO		0x20
#define PEUGEOT_207_RX_RADAR_INFO	0x21
#define PEUGEOT_207_RX_CLUSTER_INFO	0x22
#define PEUGEOT_207_RX_VIN_INFO		0x23
#define PEUGEOT_207_RX_SWITCH_INFO		0x24
#define PEUGEOT_207_RX_TRIP_INFO1		0x25
#define PEUGEOT_207_RX_TRIP_INFO2		0x26
#define PEUGEOT_207_RX_TPMS_INFO		0X28


#define PEUGEOT_207_TX_SOURCE_INFO	0xC0
#define PEUGEOT_207_TX_PLAY_INFO		0xC1
#define PEUGEOT_207_TX_RADIO_INFO	0xC2
#define PEUGEOT_207_TX_TEXT_INFO		0xC3
#define PEUGEOT_207_TX_EQ_INFO		0xC4
#define PEUGEOT_207_TX_SETUP_INFO	0xC5
#define PEUGEOT_207_TX_VOLUME_INFO	0xC6
#define PEUGEOT_207_TX_BT_INFO		0xC7
#define PEUGEOT_207_TX_REQ_CMD		0xC8
#define PEUGEOT_207_TX_TIME_INFO	0xC9
#define PEUGEOT_207_TX_INFO_RESET	0xCA

#define MAX_DIALOG_FRAME_DATA_LENGTH	0x06
#define MIN_DIALOG_FRAME_NUM				0x01
#define MAX_DIALOG_FRAME_NUM				0x05
#define MAX_DIALOG_DATA_LENGTH			((MAX_DIALOG_FRAME_DATA_LENGTH)*(MAX_DIALOG_FRAME_NUM))
#define MAX_DIALOG_MESSAGE_NUM			200

#define MAX_DIALOG_TEXT_LENGTH			30

#define PEUGEOT_207_RX_APP_DATA			0x01
#define PEUGEOT_207_DATE_DATA			0x02
#define PEUGEOT_207_TRIPS_WITCH_INFO			0x03

#define DIALOG_ID_SOURCE					0x01
#define DIALOG_ID_PLAY_MODE				0x02
#define DIALOG_ID_STATUS					0x03
#define DIALOG_ID_TEXT_TYPE				0x04
#define DIALOG_ID_RDS_TYPE					0x05
#define DIALOG_ID_VOLUME_LEVEL			0x06
#define DIALOG_ID_EQUALIZER				0x07
#define DIALOG_ID_SETUP_MODE				0x08
#define DIALOG_ID_MEMORY_PRESET			0x0A
#define DIALOG_ID_SEARCH_STATION			0x0B
#define DIALOG_ID_BLUETOOTH				0x0C
#define DIALOG_ID_MEDIA_INFO				0x20
#define DIALOG_ID_RADIO_INFO				0x21


#define CAN_IC_NCV7342						0


typedef enum
{
	DIALOG_MSG_IDLE=0,
	DIALOG_MSG_TX,
	DIALOG_MSG_WAIT
}DIALOG_MESSAGE_TX_STATE;

typedef enum
{
	TEXT_FILE_NAME=0,
	TEXT_FOLDER_NAME,
	TEXT_ID3_TITLE,
	TEXT_ID3_ARTIST,
	TEXT_ID3_ALBUM,
	TEXT_RDS_TEXT,
	TEXT_CONTACT_NAME,
	TEXT_CONTACT_NUMBER,
	TEXT_GENERAL_TEXT,
	TEXT_SW_VERSION,
	TEXT_NULL_TEXT,
	TEXT_TYPE_NUM
}DIALOG_TEXT_TYPE;

typedef enum
{
	CAN_MAIN_IDLE=0,
	CAN_MAIN_CFG,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
	CAN_MAIN_GO_TO_SLEEP,
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
	unsigned f_reverse:1;
	unsigned f_illumi:1;
	unsigned f_parking:1;
	unsigned f_start_status:2;
	unsigned f_illumi_level:3;
}_CAN_BASE_INFO_BYTE_1;

typedef union
{
	_CAN_BASE_INFO_BYTE_1 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_1;

typedef struct
{
	unsigned f_front_left_door:1;
	unsigned f_front_right_door:1;
	unsigned f_rear_left_door:1;
	unsigned f_rear_right_door:1;
	unsigned f_trunk:1;
	unsigned f_bonnet:1;
}_CAN_BASE_INFO_BYTE_2;

typedef union
{
	_CAN_BASE_INFO_BYTE_2 field;
	u8 byte;
}CAN_BASE_INFO_BYTE_2;

typedef struct
{
	CAN_BASE_INFO_BYTE_1 byte_1;
	CAN_BASE_INFO_BYTE_2 byte_2;
	float Ambient_Temperature;
}CAN_BASE_INFO;

typedef struct
{
	unsigned f_error_sensor_1:1;
	unsigned f_error_sensor_2:1;
	unsigned f_error_sensor_3:1;
	unsigned f_error_sensor_4:1;
}_CAN_RADAR_INFO_BYTE_1;

typedef union
{
	_CAN_RADAR_INFO_BYTE_1 field;
	u8 byte;
}CAN_RADAR_INFO_BYTE_1;

typedef struct
{
	unsigned f_buzzer_warning:2;
	unsigned f_reserved:6;
}_CAN_RADAR_INFO_BYTE_2;

typedef union
{
	_CAN_RADAR_INFO_BYTE_2 field;
	u8 byte;
}CAN_RADAR_INFO_BYTE_2;

typedef struct
{
	unsigned f_buzzer_warning_1:2;
	unsigned f_buzzer_warning_2:2;
	unsigned f_buzzer_warning_3:2;
	unsigned f_buzzer_warning_4:2;
}_CAN_RADAR_INFO_BYTE_3;

typedef union
{
	_CAN_RADAR_INFO_BYTE_3 field;
	u8 byte;
}CAN_RADAR_INFO_BYTE_3;

typedef struct
{
	CAN_RADAR_INFO_BYTE_1 byte_1;
	CAN_RADAR_INFO_BYTE_2 byte_2;
	CAN_RADAR_INFO_BYTE_3 byte_3;
	u8 distance;
	u8 distance_1;
	u8 distance_2;
	u8 distance_3;
	u8 distance_4;
}CAN_RADAR_INFO;

typedef union
{
	u16 speed;
	u8 byte[2];
}_CAN_CLUSTER_SPEED_INFO;

typedef union
{
	u16 engine_rpm;
	u8 byte[2];
}_CAN_CLUSTER_ENGINE_RPM_INFO;

typedef union
{
	u16 remaining_distance;
	u8 byte[2];
}_CAN_CLUSTER_MILEAGE_INFO;

typedef struct
{
	unsigned reserved0:1;
	unsigned f_change_oil_filter:1;
	unsigned f_change_engine_oil:1;
	unsigned f_change_air_filter:1;
	unsigned reserved4_7:4;
}_CAN_CLUSTER_WARNING_FLAG1;

typedef union
{
	_CAN_CLUSTER_WARNING_FLAG1 field;
	u8 byte;
}_CAN_CLUSTER_WARNING_INFO1;

typedef struct
{
	unsigned f_main_lamps:1;
	unsigned f_dipped_lamps:1;
	unsigned f_indicator_lamps:1;
	unsigned f_fog_lamps:1;
	unsigned reserved4_7:4;
}_CAN_CLUSTER_WARNING_FLAG2;
typedef union
{
	_CAN_CLUSTER_WARNING_FLAG2 field;
	u8 byte;
}_CAN_CLUSTER_WARNING_INFO2;
typedef struct
{
	unsigned f_stop_lamps:1;
	unsigned f_reverse_lamps:1;
	unsigned f_indicator_lamps:1;
	unsigned f_fog_lamps:1;
	unsigned reserved4_7:4;
}_CAN_CLUSTER_WARNING_FLAG3;
typedef union
{
	_CAN_CLUSTER_WARNING_FLAG3 field;
	u8 byte;
}_CAN_CLUSTER_WARNING_INFO3;

typedef struct
{
	unsigned f_LH_Indicator_Lamp:1;
	unsigned f_RH_Indicator_Lamp:1;
	unsigned f_Side_Lamp:1;
	unsigned f_Rear_Fog_Lamp:1;
	unsigned f_Reverse_Lamp:1;
	unsigned f_Stop_Lamp:1;
	unsigned reserved6_7:2;
}_CAN_CLUSTER_WARNING_FLAG4;
typedef union
{
	_CAN_CLUSTER_WARNING_FLAG4 field;
	u8 byte;
}_CAN_CLUSTER_WARNING_INFO4;

typedef struct
{
	unsigned f_LH_Dipped_Lamp:1;
	unsigned f_RH_Dipped_Lamp:1;
	unsigned f_LH_Main_Lamp:1;
	unsigned f_RH_Main_Lamp:1;
	unsigned f_Front_Fog_lamp:1;
	unsigned f_lowFuel_level_warning:1;
	unsigned f_low_batterVoltage_warning:1;
	unsigned reserved7:1;
}_CAN_CLUSTER_WARNING_FLAG5;
typedef union
{
	_CAN_CLUSTER_WARNING_FLAG5 field;
	u8 byte;
}_CAN_CLUSTER_WARNING_INFO5;


typedef struct
{
	_CAN_CLUSTER_SPEED_INFO speed_info;
	_CAN_CLUSTER_ENGINE_RPM_INFO engine_rpm_info;
	u8 battery_voltage;
	u8 average_speed;
	_CAN_CLUSTER_MILEAGE_INFO remaining_distance_info;
	_CAN_CLUSTER_WARNING_INFO1 warning_info1;
	_CAN_CLUSTER_WARNING_INFO2 warning_info2;
	_CAN_CLUSTER_WARNING_INFO3 warning_info3;
	_CAN_CLUSTER_WARNING_INFO4 warning_info4;
	_CAN_CLUSTER_WARNING_INFO5 warning_info5;
}CAN_CLUSTER_INFO;

typedef struct
{
	u32 Total_distance;
	u32 Total_duration;
}CAN_TOTAL_INFO_Tydedef;

typedef struct
{
	u8 Rpm_engine_flag;
	CAN_TOTAL_INFO_Tydedef Total_info1;
	CAN_TOTAL_INFO_Tydedef Total_info2;
}CAN_TOTAL_INFO;

typedef struct
{
	unsigned f_SystemStatus:1;
	unsigned f_TireInformation:1;
	unsigned f_TireLeakage:1;
	unsigned f_LearningStatus:2;
	unsigned f_TirePresstureStatus:2;
	unsigned f_TireTemperatureStatus:1;
	unsigned f_TireBatteryPowerStatus:1;
	unsigned reserved:7;
	
}_CAN_TPMS_FLAG;

typedef union
{
	_CAN_TPMS_FLAG field;
	u16 byte;
}_CAN_TPMS_byte;

typedef struct
{
	u8 Tpms_ID;
	u8 Tpms_TirePressure;
	u8 Tpms_Temperature;
	_CAN_TPMS_byte Tpms_Warning;
}CAN_TPMS_INFO;

typedef struct
{
	CAN_BASE_INFO base_info;
	CAN_RADAR_INFO radar_info;
	CAN_CLUSTER_INFO cluster_info;
	u8 vin_info[24];
	CAN_TOTAL_INFO trip_info;
	CAN_TPMS_INFO tpms_info;
}CAN_RX_INFO;

typedef struct
{
	unsigned byte_num:5;
	unsigned frame_num:3;
}_DIALOG_DATA_BYTE_1;

typedef union
{
	_DIALOG_DATA_BYTE_1 field;
	u8 byte;
}DIALOG_DATA_BYTE_1;

typedef struct
{
	u32 frame_id;
	DIALOG_DATA_BYTE_1 byte1;
	u8 data_id;
	u8 data[MAX_DIALOG_FRAME_DATA_LENGTH];
}DIALOG_DATA_FRAME;

typedef struct
{
	u8 head;
	u8 tail;
	u8 num;
	DIALOG_DATA_FRAME message[MAX_DIALOG_MESSAGE_NUM];
}DIALOG_MESSAGE_BUFFER;

typedef struct
{
	u8 frame_num;
	DIALOG_DATA_FRAME frame[MAX_DIALOG_FRAME_NUM];
}DIALOG_MESSAGE;

typedef struct
{
	u8 index;
	u8 frame_num;
	DIALOG_DATA_FRAME frame[MAX_DIALOG_FRAME_NUM];
}DIALOG_MESSAGE_NOW;

typedef struct
{
	unsigned byte_num:5;
	unsigned frame_num:3;
}_DIALOG_MESSAGE_TX_FLAG;

typedef union
{
	_DIALOG_MESSAGE_TX_FLAG field;
	u8 byte;
}DIALOG_MESSAGE_TX_FLAG;


//Data ID = 0x01
typedef struct
{
	u8 source;
	u8 status;
}_DIALOG_SOURCE_INFO;

typedef union
{
	_DIALOG_SOURCE_INFO source_info;
	u8 data[2];
}DIALOG_SOURCE_INFO;

//Data ID = 0x02,Data ID = 0x03,Data ID = 0x20
typedef struct
{
	u8 status;// Data ID = 0x03,Status
	u8 mode;// Data ID = 0x02,Play Mode
	u8 media_type;// Data ID = 0x20,byte 2
	u8 folder_number;// Data ID = 0x20,byte 3
	u8 track_number_H;// Data ID = 0x20,byte 4
	u8 track_number_L;// Data ID = 0x20,byte 5
	u8 min;// Data ID = 0x20,byte 6
	u8 sec;// Data ID = 0x20,byte 7
}_DIALOG_PLAY_INFO;

typedef union
{
	_DIALOG_PLAY_INFO field;
	u8 data[8];
}DIALOG_PLAY_INFO;

typedef struct
{
	u8 band;//Data ID = 0x21,byte2
	u8 freq_H;//Data ID = 0x21,byte3
	u8 freq_L;//Data ID = 0x21,byte4
	u8 unit;//Data ID = 0x21,byte5
	u8 preset;//Data ID = 0x21,byte6
	u8 preset_save;//Data ID = 0x0A
	u8 search_type;//Data ID = 0x0B,byte2
	u8 search_state;//Data ID = 0x0B,byte3
	u8 pty;//Data ID = 0x05
}_DIALOG_RADIO_INFO;

typedef union
{
	_DIALOG_RADIO_INFO field;
	u8 data[9];
}DIALOG_RADIO_INFO;


typedef struct
{
	unsigned  Date_region :1;
	unsigned  Time_meridiem :1;
	unsigned  reserved:6;
}_DIALOG_DATE_TIME_INFO;

typedef union
{
	_DIALOG_DATE_TIME_INFO field;
	u8 byte;
}DIALOG_DATE_TIME_INFO;


typedef struct
{
	u16 Trip_Distance;
	u16 Trip_Speed;
	u16 Trip_Duration;
}DIALOG_TRIP_INFO;


typedef struct
{
	u8 Trip_info1_flag;
	u8 Trip_info2_flag;
	DIALOG_TRIP_INFO Trip_info1;
	DIALOG_TRIP_INFO Trip_info2;
}DIALOG_TRIP_Status;


typedef struct
{
	DIALOG_SOURCE_INFO source_info;
	DIALOG_PLAY_INFO play_info;
	DIALOG_RADIO_INFO radio_info;
	u8 text_info[TEXT_TYPE_NUM][MAX_DIALOG_TEXT_LENGTH];
	u8 eq_info;//Data ID = 0x07
	u8 volume_info[2];//Data ID = 0x06
	u8 setup_mode[2];//Data ID = 0x08
	u8 bt_status;//Data ID = 0x0C
	DIALOG_DATE_TIME_INFO date_status;
	DIALOG_TRIP_Status Trip_status;
}DIALOG_INFO;

typedef struct
{
	unsigned f_can_sleep:1;
	unsigned f_can_interrupt:1;
	unsigned f_can_rx_wakeup:1;
	unsigned f_can_rx_normal:1;
	unsigned f_can_rx_enter_sleep:1;
	unsigned f_can_rx_sleep:1;
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
extern CAN_MAIN_FLAG CanMainFlag;
extern u8 Peugeot207_Date;


#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_WAKEUP		CanMainFlag.field.f_can_rx_wakeup
#define F_CAN_RX_NORMAL		CanMainFlag.field.f_can_rx_normal
#define F_CAN_RX_ENTER_SLEEP	CanMainFlag.field.f_can_rx_enter_sleep
#define F_CAN_RX_SLEEP			CanMainFlag.field.f_can_rx_sleep
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init


void Peugeot207_MainPro(void);
void Peugeot207_RxAppDataPro(u8 *buffer);
void Peugeot207_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
#endif
#endif

