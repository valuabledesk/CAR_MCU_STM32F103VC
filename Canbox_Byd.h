#ifndef _CANBOX_BYD_H_
#define _CANBOX_BYD_H_
#if CAN_ADAPTER==1
#if CANBOX_BYD==1

#define BYD_CAN_HEAD_CODE			0x2E

#define BYD_MAX_CAN_RX_DATA_LENGTH			80	
#define BYD_MIN_CAN_RX_DATA_LENGTH			1	

#define BYD_RX_VOICE_BROAD_INFO 			0x06//语音播报
#define BYD_RX_WINDOW_INFO 					0x07//车窗控制基本设定状态
#define BYD_RX_PM25_INFO					0x14//PM2.5
#define BYD_RX_PANORAMA_INFO 				0x15//360全景系统
#define BYD_RX_CAMERA_CONTROL  				0x17//摄像头开启控制
#define BYD_RX_DRIVING_INFO					0x19//行驶设置
#define BYD_RX_FRONT_RADAR_INFO				0x1d//前雷达
#define BYD_RX_REAR_RADAR_INFO				0x1e//后雷达
#define BYD_RX_STEER_KEY					0x20//方向盘按键
#define BYD_RX_BASIC_INFO						0x24//基本信息
#define BYD_RX_SPEED						0x26//车速信息
#define BYD_RX_CAR_INFO						0x27//车辆设置信息
#define BYD_RX_AIR_INFO						0x28//空调
#define BYD_RX_EPS_INFO						0x29//EPS方向盘转角

#define BYD_RX_ACK							0xFF
#define BYD_RX_NACK_ERR_CHECKSUM			0xF0
#define BYD_RX_NACK_NO_SUPPORT				0xF3
#define BYD_RX_NACK_BUSY					0xFC


#define BYD_TX_RIGHT_CAMERA_INFO			0x09//右室摄像头开启状态
#define BYD_TX_PM25_CHECK_CMD				0x74//PM2.5检测间隔设置
#define BYD_TX_DRIVE_CONTROL_INFO			0x75//车辆设置
#define BYD_TX_TIME_INFO					0x76//多功能屏日期、时间设定
#define BYD_TX_WINDOW_CONTROL_INFO 			0x79//车窗控制设定
#define BYD_TX_START_END_CMD				0x81//Start/end
#define BYD_TX_DRIVER_SETTING_CMD			0x82//行驶设置选项设定
#define BYD_TX_LOCATION_INFO				0xCA//方位海拔信息
#define BYD_TX_AIR_CONTROL_INFO				0xE0//空调控制



#define BYD_CMD_SOURCE_OFF			0x01
#define BYD_CMD_APP_DATA				0x02
#define BYD_CMD_PWR_ON_SOURCE		0x03
#define BYD_CMD_PWR_OFF_TIME			0x04
#define BYD_CMD_CLUSTER_LANGUAGE				0x05

#define BYD_TX_REQUEST_CMD					0x90
#define BYD_TX_SOUND_CMD						0xA9
#define BYD_TX_SOURCE_INFO					0xC0
#define BYD_TX_BT_INFO						0xC5
#define BYD_TX_CAR_TYPE_INFO					0xEE


#define BYD_WHEEL_KEY_NUM					36
#define BYD_PANEL_KEY_NUM					26
#define BYD_TEXT_LENGTH						40


typedef enum
{
	BYD_IDLE=0,
	BYD_TX_START_COMMAND,
	BYD_WAIT_START_ACK,
	BYD_WORK_NORMAL,
	BYD_TX_SOURCE_OFF,
	BYD_WAIT_SOURCE_OFF_ACK,
	BYD_TX_END_COMMAND,
	BYD_WAIT_END_ACK,
	BYD_POWER_OFF
}BYD_WORK_STATE;

typedef struct
{
	u8 voice_info;//语音播报
	u8 window_info[2];//车窗控制基本设定状态
	u8 pm25_info[6];//PM2.5
	u8 panorama_info;//360
	u8 camera_control_info;//摄像头开启控制
	u8 driving_info[2];//行驶
	u8 front_radar_info[4];//前雷达
	u8 rear_radar_info[5];//后雷达
	u8 steer_key_info[2]; //方向盘按键
	u8 baseinfo[2];//基本信息
	u8 speed_info[6];//车速
	u8 car_info[6];//车辆设置信息
	u8 air_info[15];//空调状态
	u8 eps_info[2];//EPS方向盘转角
}BYD_CAN_RX_INFO;

typedef struct
{
	u8 right_camera_info;//右室摄像头开启状态
	u8 pm25_check_cmd;//PM2.5设定
	u8 drive_control_info[15];//车辆设置
	u8 time_info[7];//时间、日期设定
	u8 window_control_info;//车窗控制
	u8 start_cmd;//通信
	u8 driver_setting_cmd[2];//行驶设置选项设定
	u8 air_control_info[2];//空调控制
	u8 location_info[4];//方位海拔信息
}BYD_CAN_TX_INFO;

typedef struct
{
	u8 mode_12_24;// 0:24    1:12
	u8 time_am_pm;// 0:AM   1:PM
	u8 time_hour;
	u8 time_min;
	u8 time_sec;
	u32 counter;
}BYD_TIME;


void CanBox_MainPro_BYD(void);
void BYD_RxAppDataPro(u8 *buffer);
void BYD_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
#endif
#endif
#endif

