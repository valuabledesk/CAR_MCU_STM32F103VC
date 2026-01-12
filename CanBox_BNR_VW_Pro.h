#ifndef _CANBOX_BNR_VW_PRO_H_
#define _CANBOX_BNR_VW_PRO_H_
#if CANBOX_BNR_VW==1


#define RX_ACK						              0xFF
#define RX_NACK_ERR_CHECKSUM		              0xF0
#define RX_NACK_NO_SUPPORT						  0xF3
#define RX_NACK_BUSY				              0xFC
#define RX_NACK									  0xFE


#define BNR_CAN_HEAD_CODE						0x2E

#define B_VW_MAX_CAN_RX_DATA_LENGTH			80	
#define B_VW_MIN_CAN_RX_DATA_LENGTH			4

#define B_VW_RX_AMP_RESET_INFO				0x01
#define B_VW_RX_REQUEST_INFO					0x10
#define B_VW_RX_LIGHT_INFO						0x14
#define B_VW_RX_SPEED_INFO					0x16
#define B_VW_RX_STEER_KEY						0x20
#define B_VW_RX_AIR_INFO						0x21
#define B_VW_RX_REAR_RADAR_INFO				0x22
#define B_VW_RX_FRONT_RADAR_INFO				0x23
#define B_VW_RX_BASIC_INFO						0x24
#define B_VW_RX_PARKING_INFO					0x25
#define B_VW_RX_EPS_INFO						0x26
#define B_VW_RX_AMP_INFO						0x27
#define B_VW_RX_VERSION_INFO					0x30
#define B_VW_RX_LEFT_RADAR_INFO				0x32
#define B_VW_RX_RIGHT_RADAR_INFO				0x33
#define B_VW_RX_CAR_INFO						0x41
#define B_VW_RX_TURN_SIGNAL_LAMP				0x70
#define B_VW_RX_UPDATE_INFO					0x7E
#define B_VW_RX_SCREEN_TYPE					0x7F

#define B_VW_TX_START_END_CMD				0x81
#define B_VW_TX_ENGINE_TIME_CMD				0x89
#define B_VW_TX_SPEED_TIME_CMD				0x8A
#define B_VW_TX_REQUEST_CMD					0x90
#define B_VW_TX_SOURCE_INFO					0xC0
#define B_VW_TX_ICON_INFO						0xC1
#define B_VW_TX_RADIO_INFO					0xC2
#define B_VW_TX_MEDIA_INFO					0xC3
#define B_VW_TX_VOLUME_INFO					0xC4
#define B_VW_TX_SETTING_CMD					0xC6
#define B_VW_TX_AMP_CMD						0xA0
#define B_VW_TX_AIR_CMD						0xE0
#define B_VW_TX_DASHBOARD_CMD				0xE1
#define B_VW_TX_UPDATE_CMD					0xEA


#define B_VW_CMD_SOURCE_OFF_CMD			0x01
#define B_VW_CMD_APP_DATA					0x02
#define B_VW_CMD_AMP_CMD					0x03

#define B_VW_WHEEL_KEY_NUM				10

#define B_VW_DASHBOARD_LENGTH			22
#define B_VW_DASHBOARD_LINE_LENGTH			5


typedef enum
{
	B_VW_IDLE=0,
	B_VW_TX_START_COMMAND,
	B_VW_WAIT_START_ACK,
	B_VW_WORK_NORMAL,
	B_VW_TX_SOURCE_OFF,
	B_VW_WAIT_SOURCE_OFF_ACK,
	B_VW_TX_END_COMMAND,
	B_VW_WAIT_END_ACK,
	B_VW_POWER_OFF
}B_VW_WORK_STATE;

typedef enum
{
	B_VW_REQ_APP_DATA=0,
	B_VW_REQ_CAR_INFO_1,
	B_VW_REQ_CAR_INFO_2,
	B_VW_REQ_CAR_INFO_3,
	B_VW_REQ_VERSION,
	B_VW_REQ_BASIC_INFO,
	B_VW_REQ_EPS_INFO,
	B_VW_REQ_NUM
}B_VW_REQUEST_INDEX;

typedef struct
{
	u8 request_info;
	u8 light_info;
	u8 speed[2];
	u8 air_info[6];
	u8 rear_radar_info[4];
	u8 front_radar_info[4];
	u8 left_radar_info[4];
	u8 right_radar_info[4];
	u8 version_info[16];
	u8 basic_info[2];
	u8 parking_info[2];
	u8 amp_info[8];
	u8 eps_info[2];
	u8 car_info[13];
	u8 update_info;
	u8 turn_signal_lamp_info;
	u8 screen_type;
}B_VW_CAN_RX_INFO;

typedef struct
{
	u8 request_cmd[2];
	u8 speed_time_cmd;
	u8 engine_time_cmd;
	u8 source_info[2];
	u8 icon;
	u8 radio_info[4];
	u8 media_info[6];
	u8 volume;
	u8 car_set_cmd[2];
	u8 amp_cmd[2];
	u8 air_cmd[2];
	u8 dashboard_info[B_VW_DASHBOARD_LINE_LENGTH][B_VW_DASHBOARD_LENGTH];
	u8 dashboard_info_length[B_VW_DASHBOARD_LINE_LENGTH];
}B_VW_CAN_TX_INFO;

extern B_VW_CAN_RX_INFO B_VW_CanAdapterRxInfo;
extern B_VW_CAN_TX_INFO B_VW_CanAdapterTxInfo;
extern u16 B_VW_AmpResetTimer;
extern u8 CanReversFlag;

void B_VW_RxAppDataPro(u8 *buffer);
void B_VW_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
void CanBox_MainPro_B_VW(void);


#endif
#endif


