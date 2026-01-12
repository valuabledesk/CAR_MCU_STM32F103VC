#ifndef _AUTO_TEST_PRO_H_
#define _AUTO_TEST_PRO_H_

#if FACTORY_AUTO_TEST_FUN==1
#define AUTO_TEST_HEADCODE1_0					's'
#define AUTO_TEST_HEADCODE1_1					'S'

#define AUTO_TEST_HEADCODE2_0					't'
#define AUTO_TEST_HEADCODE2_1					'T'

#define AUTO_TEST_RX_MAX_LENGTH			40
#define AUTO_TEST_TX_MAX_LENGTH			40
#define AUTO_TEST_TX_CMD_LENGTH         		11
#define AUTO_TEST_FR_LENGTH             		14
#define APP_VERSION_MAX_LENGTH			30
#define OS_VERSION_MAX_LENGTH				25
#define DVP_VERSION_MAX_LENGTH			15
#define SERVO_VERSION_MAX_LENGTH			15
#define MCU_VERSION_MAX_LENGTH			30
#define UNIT_CODE_LENGTH					28

#define WIFI_SSID_MAX_LENGTH        30
#define WIFI_PASSWORD_MAX_LENGTH        30
#define AUTO_TEST_RX_APP_LENGTH			10

//#define SCREEN_TEST_OFF     0X00
//#define SCREEN_TEST_ON      0X01

#define AutoTest_Start_End	0xB1


#define AutoTest_Start_End	0xB1
//second cmd
//#define AUTO_TEST_BLE_TPMS_CMD       0x030
#define	AT_RADIO_CMD_CURRENT_FREQ      0x0100
#define	AT_RADIO_CMD_INIT              0x0101
#define	AT_RADIO_CMD_STEP_UP           0x0102
#define	AT_RADIO_CMD_STEP_DOWN         0x0103
#define	AT_RADIO_CMD_AM                0x0104
#define	AT_RADIO_CMD_PRESET            0x0105
#define	AT_RADIO_CMD_DX_LOC            0x0106
#define	AT_RADIO_CMD_SEEK_UP           0x0107
#define	AT_RADIO_CMD_ST                0x0108

////TPMS third cmd
#define AT_BleTPMS_CMD_SEARCH_MAC 		0x0300
#define AT_BleTPMS_CMD_CHECK_SCREEN   0x0301
#define AT_BleTPMS_CMD_JUNM_TO_TPMS   0x0302
#define AT_BleTPMS_CMD_GET_DATA       0x0303


typedef enum
{
	AUTO_TEST_RX_HEADCODE1=0,
	AUTO_TEST_RX_HEADCODE2,
	AUTO_TEST_RX_LENGTH,
	AUTO_TEST_RX_LENGTH1,
	AUTO_TEST_RX_CMD,
	AUTO_TEST_RX_CMD1,
	AUTO_TEST_RX_DATA,
	AUTO_TEST_RX_CHECKSUM,
	AUTO_TEST_RX_CHECKSUM1
}AUTO_TEST_RX_STATE;
typedef enum
{
	AT_BT_CMD_NONE=0,
	AT_BT_CMD_CONNECT,
	AT_BT_CMD_DISCONNECT,
	AT_BT_CMD_HUNGUP,
	AT_BT_CMD_DIAL_MENU,
	AT_BT_CMD_A2DP_MENU,
	AT_BT_CMD_OPEN_INTERNAL_MIC,
	AT_BT_CMD_OPEN_EXTERNAL_MIC,
	AT_BT_CMD_CHECK_ADDRESS,
	AT_BT_CMD_NUM
}AUTO_TEST_BT_CMD;

typedef enum//wifi以及以太网测试
{
	AT_InternetWifi_CMD_NONE=0,
	AT_InternetWifi_CMD_OPEN_INTERNET,
	AT_InternetWifi_CMD_CLOSE_INTERNET,
	AT_InternetWifi_CMD_OPEN_WIFI,
	AT_InternetWifi_CMD_CLOSE_WIFI,
	AT_InternetWifi_CMD_CONNECT_WIFI,
	AT_InternetWifi_CMD_IP,
	AT_InternetWifi_CMD_SSID,
	AT_InternetWifi_CMD_PASSWORD
}AUTO_TEST_InternetWifi_CMD;

typedef enum//查询按键代码
{
	AT_BUTTON_CMD_NONE=0,
	AT_BUTTON_CMD_ASK_CODE
}AUTO_TEST_BUTTON_CMD;

typedef enum//屏幕测试
{
	AT_SCREEN_CMD_NONE=0,
	AT_SCREEN_CMD_SCREEN_TEST,
	AT_SCREEN_CMD_SHOW_BLACK,
	AT_SCREEN_CMD_SHOW_WHITE,
	AT_SCREEN_CMD_SHOW_RED,
	AT_SCREEN_CMD_SHOW_GREEN,
	AT_SCREEN_CMD_SHOW_BLUE,
	AT_SCREEN_CMD_TOUCH
}AUTO_TEST_SCREEN_CMD;

//typedef enum
//{
//	AT_RADIO_CMD_CURRENT_FREQ=0x10,
//	AT_RADIO_CMD_INIT,
//	AT_RADIO_CMD_STEP_UP,
//	AT_RADIO_CMD_STEP_DOWN,
//	AT_RADIO_CMD_AM,
//	AT_RADIO_CMD_PRESET,
//	AT_RADIO_CMD_DX_LOC,
//	AT_RADIO_CMD_SEEK_UP,
//	AT_RADIO_CMD_ST,
//}AUTO_TEST_RADIO_CMD;


typedef struct
{
	unsigned F_EnterAutoTestFlag		:1;
	unsigned F_AutoTestRxOk			:1;
}_AUTO_TEST_FLAG;

typedef union
{
	_AUTO_TEST_FLAG field;
	u16 flag;
}AUTO_TEST_FLAG;

typedef struct
{
	u16 total_play_track;     //总曲目数
	u16 cur_play_track;     //当前曲目
	u8 source_type;          // Source表
	u8 media_type;           ////媒体类型
	u8 PlayState;              //播放源状态	
	u8 guage; //播放进度 当前播放时间/总时间 =(0-100)
	u8 folder;
}MEDIAPLAYINFO;

typedef struct
{
	unsigned f_connect:1;
	unsigned f_hungup:1;
	unsigned f_audio_menu:1;
	unsigned f_internal_mic:1;
	unsigned f_adress_right:1;
}_AUTO_TEST_BT_FLAG;
typedef union
{
	_AUTO_TEST_BT_FLAG field;
	u8 byte;
}AUTO_TEST_BT_INFO;

typedef struct//新增
{
	unsigned f_connect:1;
	unsigned f_ping:1;
	//unsigned f_audio_menu:1;
	//unsigned f_internal_mic:1;
	//unsigned f_adress_right:1;
}AUTO_TEST_WIFI_FLAG;

typedef struct
{
	u8 flag;
	u8 code[UNIT_CODE_LENGTH+1];
}UNIT_CODE_DATA;
extern u8 SCREEN_SUB_COMMAND;
extern u8 PARAM_LENGTH;
extern MEDIAPLAYINFO MediaPlayInfo;
extern AUTO_TEST_RX_STATE AutoTestRxState;
extern u8 *AutoTest_RxPtr;
extern u8 *AutoTest_TxPtr;
extern u8 AutoTest_RxLength;
extern u8 Autotest_TxLength;
extern u8 Autotest_RxCounter;
extern u8 Autotest_ErCounter;
extern u8 Autotest_KeyCode;
extern u8 GetVersionTimer;
extern u8 GetVersionCounter;
extern u8 AutoTestTxBuffer[AUTO_TEST_TX_MAX_LENGTH];
extern u8 AutoTestRxBuffer[AUTO_TEST_RX_MAX_LENGTH];

extern u8 AutoTestAppVersion[APP_VERSION_MAX_LENGTH];
extern u8 AutoTestOsVersion[OS_VERSION_MAX_LENGTH];
extern u8 AutoTestDvpVersion[DVP_VERSION_MAX_LENGTH];
extern u8 AutoTestServoVersion[SERVO_VERSION_MAX_LENGTH];
extern u8 AutoTestBTAddr[6];
extern u8 AutoTestBTCheckAddr[6];
extern u8 AutoTestIP_Addr[15];//新增待定
extern u8 AutoTestWifiSSID[WIFI_SSID_MAX_LENGTH];
extern u8 AutoTestWifiPassword[WIFI_PASSWORD_MAX_LENGTH];
extern u8 AutoTestRxAppBuffer[AUTO_TEST_RX_APP_LENGTH];

extern AUTO_TEST_FLAG AutoTestFlag;
#define  F_AUTOTEST_READY AutoTestFlag.field.F_EnterAutoTestFlag
#define  F_AUTOTEST_RX_OK AutoTestFlag.field.F_AutoTestRxOk

extern UNIT_CODE_DATA UnitCodeData;
extern AUTO_TEST_BT_INFO AutoTestBtInfo;
extern AUTO_TEST_WIFI_FLAG AutoTestWifiFlag;//新增
void AutoTestRxInterrupt(u8 data);
void AutoTestEnterRxInterrupt(u8 data);
void AutoTestEnableRxInterrupt(void);
void AutoTestUnitCodeLoad(void);
u8 IsAutoTestUnitCodeExist(void);
void AutoTestUnitCodeSave(void);
void	AutoTestSpeed_Pro(void);
void AutoTestMainPro(void);
extern void AutoTestRxApp(void);
u8 AutoAscii2Hex(u8 data);
#endif
#endif
