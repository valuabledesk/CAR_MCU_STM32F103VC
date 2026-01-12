#ifndef _APP_COM_H_
#define _APP_COM_H_

#define HEAD_ADDRESS_APP	       0xA0
#define HEAD_ADDRESS_MCU		0x55

#define MAX_APP_RX_BUFFER_LENGTH		1000
#define MAX_APP_TX_BUFFER_LENGTH		500
#define MIN_APP_RX_LENGTH				6
#define MAX_APP_RX_LENGTH				150

#define MCU_TX_CMD					       0x01
#define MCU_TX_RADIOINFO			       0x02
#define MCU_TX_RDS_INFO 			        0x04
#define MCU_TX_RDS_PTY			               0x05
#define MCU_TX_DISC_STATE			       0x06
#define MCU_TX_PASSWORDSETTING		0x07
#define MCU_TX_RDSSETTING			       0x08
#define MCU_TX_GENSETTING			       0x09
#define MCU_TX_SYSSETTING			       0x0b
#define MCU_TX_CLOCK		                     0x0c
#define MCU_TX_FAVORLIST				0X0d
#define MCU_TX_FREQLIST			       0x0e
#define MCU_TX_RDS_PS					0x0f
#define MCU_TX_RDS_RT					0x10
#define MCU_TX_PSNAME_LIST			0x1b
#define MCU_TX_VOLUME				       0x15	
#define MCU_TX_RADIO_SMETER		       0x16
#define MCU_TX_CAN_BOX_INFO		       0x17
#define MCU_TX_RDS_PI					0x18
#define MCU_TX_MCU_VERSION			0x19	
#define MCU_TX_MCU_REFRESH_CFM            0x1C
#define MCU_TX_CAMERA				       0x20
#define MCU_TX_APP_UI_TYPE			       0x21
#define MCU_TX_VERSION_REQ			0x29
#define MCU_TX_APP_TEST_MODE_INFO      0x2A //MCU相关出厂设置信息
#define MCU_TX_STEERKEY_STATE		       0x2f///0x0a
#define MCU_TX_MACHINE_MISC_STATE     	0x30
#define MCU_TX_BACKUP_DATA                   	0x31
#define MCU_TX_FMT_INFO				0x34
#define MCU_TX_CAN_UPDATE_INFO		0x36
#define MCU_TX_DAB_LIST				0x39
#define MCU_TX_DAB_CUR_INFO			0x40
#define MCU_TX_DAB_TEXT				0x41
#define MCU_TX_DAB_SEARCH_INFO		0x42
#define MCU_TX_DAB_MOT_INFO			0x43
#define MCU_TX_DAB_VERSION_INFO		0x44
#define MCU_TX_DAB_UPDATE_CMD		0x45
#define MCU_TX_DAB_SIGNAL				0x46
#define MCU_TX_DAB_SF_INFO			0x47
#define MCU_TX_DAB_REFERESH_STATE	0x48
#define MCU_TX_DAB_TEST_MODE_INFO	0x49
#define MCU_TX_DAB_MOT_ERROR			0x4A
#define MCU_TX_DAB_CLOCK				0x4B
#define MCU_TX_DAB_TPEG_INFO			0x4C
#define MCU_TX_DAB_TPEG_STATE_INFO	0x4D
#define MCU_TX_DAB_ECC_INFO			0x4E

#define MCU_TX_RADIO_FREQ_LIST		0x50
#define MCU_TX_RADIO_PS_NAME_LIST	0x51
#define MCU_TX_RDS_TIME				0x52
#define MCU_TX_DUAL_SIM_DATA			0x53
#define MCU_TX_DUAL_MCM_DATA			0x54
#define MCU_TX_DSP_DATA				0x55

#define MCU_TX_MCU_TYPE				0x60
#define MCU_TX_CAN_MULTIPLE_TYPE				0x61
#define MCU_TX_SMART_LOCK				0x62
#define MCU_TX_RADAR_HAIMA_S7				0x63

#define MCU_TX_BT_TEST_CMD				0x70
#define MCU_TX_WIFI_TEST_CMD		0x71
#define MCU_TX_SCREEN_TEST_CMD		0x72
#define MCU_TX_AUTO_TEST_CMD					0x73
#define MCU_TX_AUTO_START_CMD		  0x74
#define MCU_TX_FACTORY_RESET_CMD	0x75
#define MCU_TX_AHD_360_INFO				0x80

#define MCU_TX_CAN_SYSMODE			0X9F//SUBID
#define MCU_TX_APP_RDS_AUDIO                0xd2
#define MCU_TX_APP_RDS_AF_LIST             0xd3
#define MCU_TX_UUID_DATA				0xd4
#define MCU_TX_ACR_IR_INFO				0xd5
#define MCU_TX_TEMPERATURE			0xd6
#define MCU_TX_DAB_FM_RADIO_PARAM	0xd7
#define MCU_TX_MISC_INFO				0xd8
#define MCU_TX_HW_VERSION				0xd9
#define MCU_TX_DPA_INFO				0xdA

#define MCU_RX_REQUEST_STORE_DATA      0x11//APP请求MCU存储数据段
#define MCU_RX_DAB_CMD      				0x12//APP请求MCU存储数据段
#define MCU_RX_MISC_INFO_CMD                 0x13
#define MCU_RX_AHD_360_CMD			0x20

#define MCU_RX_USB_REBOOT   0x93


#define MCU_RX_CMD					       0xC0
#define MCU_RX_STATUS				       0xC1
#define MCU_RX_SETTING				       0xC2
#define MCU_RX_GPS_TIME			       0xC3
#define MCU_RX_MEDIA_INFO     		       0xC4 
#define MCU_RX_APP_COPYDATA                  0xC5
#define MCU_RX_REFLASHCMD			       0XC6
#define MCU_RX_RADIOGETINFO		       0xC7
#define MCU_RX_RADIOFREQINFO		       0xC8
#define MCU_RX_MEMU_WHEELSTY		0xC9
#define MCU_RX_COORDINATE                       0XCA
#define MCU_RX_MACHINE_TYPE       		0XCB
#define MCU_RX_TOUCH_DATA				0xCC
#define MCU_RX_APP_VERSION			0xCD
#define MCU_RX_TEST_MODE_INFO               0xCF
#define MCU_RX_FMT_CMD				 0xD0
#define MCU_RX_CAN_UPDATE_INFO		 0xD1
#define MCU_RX_DAB_COMMAND			0xD2
#define MCU_RX_DAB_UPDATE_CMD		0xD3
#define MCU_RX_SYSTEM_TIME			0xD4
#define MCU_RX_SMART_LOCK_COPYDATA			0xD5
#define MCU_RX_DAB_SID						0xD6
#define MCU_RX_9288_REINIT_CMD	0xD7
#define MCU_RX_DPA_CMD					0xD8
#define MCU_RX_BT_INFO                               0xe6
#define MCU_RX_SYSTERM_VOLUME                0xe7
#define MCU_RX_MEMU_PANNELSTY		  0xe8
#define MCU_RX_DSP_CMD        			0xe9
#define MCU_RX_OS_UPGRADE                        0xF7
#define MCU_RX_APP_STARTOK                      0xF6
#define MCU_RX_OS_UI_TYPE                         0xF5
#define MCU_RX_DUAL_MCM_DATA                    0xEB
#define MCU_RX_DUAL_SIM2_DATA                    0xEB
#define MCU_RX_BT_TEST_STATE			0xEC
#define MCU_RX_ACR_IR_INFO					0xED
#define MCU_RX_WIFI_TEST_CMD    			0xEF
#define MCU_RX_AUTO_TEST_CMD					0xF0
#define MCU_RX_DAB_ANT_POWER_CMD					0xF1


#define MCU_TXRX_ACK				        0xff
#define MCU_TXRX_ReverseACK		        0xfe
#define MCU_TXRX_NACK_NG			        0xf0
#define MCU_TXRX_NACK_NO_SUPPORT   	 0xf3
#define MCU_TXRX_NACK_BUSY			 0xfc


#define AIR_INFO_INDEX                 			0x01			
#define Radar_INFO_INDEX					0x02
#define General_INFO_INDEX          			0x03
#define SysTime_INFO_INDEX         			0x04
#define Exception_INFO_INDEX       			0x05
#define Alarm_INFO_INDEX             			0x06
#define Rear_Radar_INFO_INDEX				0x07
#define Front_Radar_INFO_INDEX				0x08
#define CAR_SETTING_INFO_INDEX			0x09
#define CAR_EPS_INFO_INDEX					0x0A
#define CAR_SPEED_MEMORY_INDEX			0x0B
#define CAR_VERSION_INFO_INDEX			0x0C

/***********************************数据保存**********************************/
//总数据包分拆后每个单元的数据量，每次通讯发送或接收的数据量
#define MCU_STORE_DATA_UNIT_SIZE    		50   
//总数据包分拆后单元数据包数目
#define MCU_STORE_DATA_UNIT_COUNT    		17  
#define MCU_STORE_DATA_ALL_DATA_SIZE    	((MCU_STORE_DATA_UNIT_SIZE) * (MCU_STORE_DATA_UNIT_COUNT))  
#define APP_BACKUP_DATA_LENGTH			128


//触摸屏按键状态
#define TOUCH_STATE_DOWN	 			0//按键按下
#define TOUCH_STATE_UP	 	 			1//按键释放

/***********************************关于防盗密码**********************************/
//对应UICC_DIGIT_KEY_TS密码状态参数
#define CUSTOM_PASSWORD_OK  		0x55
#define SUPPER_PASSWORD_OK  		0xAA
#define SYSYTEM_LOCKED  			0x99

//对应UICC_OPEN_MENU的参数
#define WINCE_SECURITY_CODE_MENU 		1
#define WINCE_SUPER_CODE_MENU 			2
#define WINCE_LOCKED_MENU 				3
/***********************************关于防盗密码**********************************/


/***********************************关于Can 升级**********************************/
#define MCU_NOTIFY_CAN_UPD_READY				0x01
#define MCU_REQ_CAN_UPD_DATA					0x02
#define MCU_NOTIFY_CAN_UPD_OK				0x03
#define MCU_NOTIFY_CAN_UPD_NG				0x04
/***********************************关于Can 升级**********************************/

#if defined(AUTOCHIPS_AC781X)
#ifdef FLASH_SIZE_64K
#define FLASH_EEPROM_ADDR   (0x0800F800u)
#elif defined(FLASH_SIZE_256K)
#define FLASH_EEPROM_ADDR   (0x0803F000u)
#else
#define FLASH_EEPROM_ADDR   (0x0801F000u)
#endif
#elif defined(HDSC_HC32F460)
#if PLATFORM_TYPE==UNISOC_PLATFORM
#define FLASH_EEPROM_ADDR   (0x0007E000u)
#else
#define FLASH_EEPROM_ADDR   (0x0003E000u)
#endif
#elif defined(HDSC_HC32L072)
#define FLASH_EEPROM_ADDR   (0x0001FE00u)
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
#define FLASH_EEPROM_ADDR   (0x0801F800u)
#else
#define FLASH_EEPROM_ADDR   (0x0803F800u)
#endif
#elif defined(STM32F401xx)
#define FLASH_EEPROM_ADDR   (0x0803Fc00u)
#endif

typedef enum tag_SID_MISC_INFO_T
{
    SID_MISC_BEGIN = 0,
    SID_MISC_AVM_CAM_POWER,
    SID_MISC_END
}SID_MISC_INFO_T;

typedef enum
{
	SID_IIS_ALBUM_INFO,
	SID_IIS_ARTIST_INFO,
	SID_IIS_TITLE_INFO
}EN_ID3_INFO_SUBID;

typedef enum
{
	MISC_CMD_BEGIN = 0,
	MISC_PANNEL_LED_RGB,    //面板灯颜色设置。其后依次跟R、G、B的值，每一颜色元素占1Byte, 参数共3byte  Buddy 2013-4-17 9:34
	MISC_AUDIO_BREAK,// 声音插播信息一个字节参数，在收音源下，有声音插播时其参数为1，插播结束参数为0.
	MISC_CAPACITOR_SCREEN_KEY,   //参数见tag_CAPACITOR_SCEEN_KEY
	MISC_REQ_EJECT,
	MISC_FRONT_CAMERA_POWER,
	MISC_REQ_RST_DEV,
	MISC_REQ_SPEC_RADIO_FREQ,
	MISC_REQ_CAN_INFO,
	MISC_REAR_CAMERA_POWER,
	MISC_DVR_USB_MODE,
	MISC_DVR_RESET_REQ,
	MISC_DSA_POWER_CTRL,
	MISC_AUDIO_CH_SWITCH,
	MISC_REQ_UUID,
	MISC_REQ_VERSION,
	MISC_AVM_CAMERA_POWER,
	MISC_REQ_HW_VERSION,
	MISG_MULTI_VIDEO_PROTOCOL,//摄像头发送数据
	MISC_SOC_BOOT_MODE,
	MISC_CMD_END
}MISC_CMD_INDEX;

typedef enum tag_MACHINE_MISC_STATE_T
{
	MACHINE_STATE_BEGIN,

	MACHINE_STATE_PARKING = MACHINE_STATE_BEGIN,    //拉手刹停车
	
	MACHINE_STATE_REVERSE,    //倒车
	MACHINE_STATE_ILLUMINATION,    //大灯开
	MACHINE_STATE_B_NORMAL,  //电池正常
	MACHINE_STATE_POWER_ON,    //关机
	MACHINE_STATE_B_OFF,    //断B+
	
	MACHINE_STATE_PANEL_RESET,    //面板复位
	MACHINE_STATE_SOFT_MUTE,//请求soft mute
	MACHINE_STATE_ACC,//ACC 标记
	MACHINE_STATE_HDMI_PLUG,  // 1:插入 0:拔掉
	MACHINE_STATE_URGENT_OFF,    //紧急关机
	
	MACHINE_STATE_TYRE_ALARM,  // 胎压模块报警
	MACHINE_STATE_IPOD_PLUG,
	MACHINE_STATE_RADIO_FAV,
	MACHINE_STATE_B_WARN,
	MACHINE_STATE_TEMP_WARN,
	
	MACHINE_STATE_G_SENSOR_WARN,
	MACHINE_STATE_B_IGNITION,
	MACHINE_STATE_POWER_KEY,
	MACHINE_STATE_REVERSE_PRO,
	MACHINE_STATE_BATTERY_VOLTAGE,
	
	MACHINE_STATE_AUX_IN,
	MACHINE_STATE_DOOR_LOCK_STATE,
	MACHINE_STATE_FICTITIOUS_POWER_OFF,
	MACHINE_STATE_SPEED,
	MACHINE_STATE_SLEEP,
	
	MACHINE_STATE_END
}MACHINE_MISC_STATE_T, *P_MACHINE_MISC_STATE_T;

//RDS 声音种类。MC_SID_RDS_SOUND后的第一个参数 zwh 2012-8-27 17:00
typedef enum tag_RDS_SOUND_TYPE_T
{
	RDS_SOUND_TYPE_BEGIN = 0,   //just for begin flag
	RDS_SOUND_TYPE_TA = RDS_SOUND_TYPE_BEGIN,
	RDS_SOUND_TYPE_ALARM,
	RDS_SOUND_TYPE_PTY,
	RDS_SOUND_TYPE_END
}RDS_SOUND_TYPE_T, *P_RDS_SOUND_TYPE_T;

//RDS声音动作。 MC_SID_RDS_SOUND后的第二个参数
typedef enum tag_RDS_SOUND_ACTION_T
{
	RDS_SOUND_ACTION_BEGIN = 0x00,
	RDS_SOUND_ACTION_END = 0x01
}RDS_SOUND_ACTION_T, *P_RDS_SOUND_ACTION_T;

typedef enum
{
	DATATYPE_DEF_MODEL=0X80,
	DATATYPE_DEF_CANVER=0X81
}CAN_SYS_DATATYPE_DEF;

typedef enum
{
	APP_STARTING	=0,
	APP_READY	=2,
	APP_MENU_ON	=3,
	APP_MENU_OFF	=4,
	APP_POWEROFF_READY	=10,
	APP_CAMERA_ON=16,
	APP_CAMERA_OFF=17	
}APP_STATUS;

typedef enum
{
	APP_SOURCE_TUNER=0, //Radio
	APP_SOURCE_DVD=1, 
	APP_SOURCE_DVDC=2, //CDC
	APP_SOURCE_ATV=3,
	APP_SOURCE_NAVI=4,
	APP_SOURCE_AUX=5, //AUX IN 1
	APP_SOURCE_DTV=6,
	APP_SOURCE_SD=7,
	APP_SOURCE_XM=8, 
	APP_SOURCE_IPOD=9,
	APP_SOURCE_USB=10,
	APP_SOURCE_CAMERA=11,
	APP_SOURCE_TAIL_AUX=12, //AUX IN 2
	APP_SOURCE_BT=13,
	APP_SOURCE_SIRIUS=14,
	APP_SOURCE_HDRADIO=15,
	APP_SOURCE_INTERNET=16, 
	APP_SOURCE_AVOFF=17, //source off
	APP_SOURCE_ISR_RADIO=18,
	APP_SOURCE_ISR_HDRADIO=19,
	APP_SOURCE_CMMB=20,
	APP_SOURCE_SETUP=21,
	APP_SOURCE_EQ=22,
	APP_SOURCE_UPDATE=23,
	APP_SOURCE_VOLBAR=24,
	APP_SOURCE_INFOBAR=25,
	APP_SOURCE_WB=26,
	APP_SOURCE_DAB=27,
	APP_SOURCE_TEST_MODE=28,
	APP_SOURCE_CAR_BUS = 29,
	APP_SOURCE_ALARM_DOG = 30,
	APP_SOURCE_DRIVE_RECORDER = 31,
	APP_SOURCE_INTERNET_MUSIC_PLAYER = 32,
	APP_SOURCE_WIFI_DISPLAY = 33,
	APP_SOURCE_DISP_CTRL = 34,
	APP_SOURCE_CALENDAR =35,
	APP_SOURCE_WALLPAPER=36,
	APP_SOURCE_CACULATOR=37,
	APP_SOURCE_GOBANG=38,			//wu zi qi
	APP_SOURCE_PUZZLE=39,	
	APP_SOURCE_CARPHONE=40,
	APP_SOURCE_AIRCONTROL=41,
	APP_SOURCE_RADAR=42,
	APP_SOURCE_ICAR=43,
	APP_SOURCE_COLORKEY=44,
	APP_SOURCE_FRONT_CAMERA=45,
	APP_SOURCE_WiFi=46,
	APP_SOURCE_USER_MANUAL=47,
	APP_SOURCE_CARNET=48,
	APP_SOURCE_TPMS=49,
	APP_SOURCE_PROMPT_MESSAGE=50,
	APP_SOURCE_DDAB=51,
	APP_SOURCE_ANDROID_AUTO=52,		
	APP_SOURCE_CARPLAY=53,		
	APP_SOURCE_AUTOLINK=54,     
	APP_SOURCE_CARLIFE=55,     
	APP_SOURCE_BT_MUSIC=56,   
	APP_SOURCE_GYROSCOPE=57,
	APP_SOURCE_AUDIO_NONE=58,
	APP_SOURCE_DEMO=59,
	APP_SOURCE_WEBLINK=60,
	APP_SOURCE_MCLLINK=61,
	APP_SOURCE_MCMBOX=62,
	APP_SOURCE_GUIDE=63,
	APP_SOURCE_DEVICELIST=64,
	APP_SOURCE_FMT=65,
	APP_SOURCE_HOMEVIEW=66,
	APP_NUM_OF_SOURCE
}APP_SOURCE_TYPE;

typedef enum
{
	GPIO_MONITOR_IDLE=0,
	GPIO_MONITOR_DETECT,
	GPIO_MONITOR_CHECK
}GPIO_MONITOR_STATE;

typedef enum
{
	DAB_PI_INFO=0,
	DAB_RESET_CMD,
	DAB_CMD_NUM
}DAB_CMD_INDEX;

typedef enum
{
	SET_FMT_WORK_MODE_CMD=0x01,
	SET_FMT_FREQ_CMD=0x02,
	SET_FMT_AUDIO_MODE_CMD=0x03
}RX_FMT_CMD_INDEX;

typedef enum
{
	READ_DAP_INFO=0x01,
	DC_DIAG_REQUEST=0x02,
	AC_DIAG_REQUEST=0x03,
	AMP_STATUS_REQUEST=0x04,
}RX_DPA_CMD_INDEX;
typedef enum
{
	TX_DAP_INFO=0x01,
	TX_DAP_DC_RESULT=0x02,
	TX_DAP_AC_RESULT=0x03,
	TX_DAP_FAULTS=0x04,
	TX_DAP_WARNINGS=0x05,
	TX_DAP_STATUS=0x06
}TX_DPA_INFO_INDEX;
typedef struct
{
	u16 head;
	u16 tail;
	u8 data[MAX_APP_RX_BUFFER_LENGTH];
}MCU_RX_BUFFER;

typedef struct
{
	unsigned f_app_init_ok:1;
	unsigned f_app_power_on:1;
	unsigned f_arm2_start_ok:1;
	unsigned f_close_beat_heart_check:1;
	unsigned f_app_menu_on_off:1;
	unsigned f_os_reverse_ack:1;
}_APP_FLAG;

typedef union
{
	_APP_FLAG field;
	u8 byte;
}APP_FLAG;

typedef struct
{
	unsigned f_password:1;
	unsigned f_lock_screen:1;
	unsigned f_state:1;
}_PASSWORD_FLAG;

typedef union
{
	_PASSWORD_FLAG field;
	u8 byte;
}PASSWORD_FLAG;
typedef struct
{
	PASSWORD_FLAG flag;
	u8 checksum;
}EEP_PASSWORD_FLAG;

typedef struct 
{
	unsigned F_tx_buff_Full:1;
	unsigned F_tx_ack_check:1;
	unsigned F_uart_init_flag:1;
}_APP_UART_FLAG;

typedef union
{
	_APP_UART_FLAG field;
	u8 byte;
}APP_UART_FLAG;


extern u8 nMediaPlayPackage;
extern APP_STATUS APP_Status;
extern MCU_RX_BUFFER McuRxBuffer;
extern APP_FLAG APP_Flag;
extern u8 Uart_Rx_Seq_Num;
extern u8 Uart_Tx_Seq_Num;
extern u16 Uart_ReSend_Timer;	
extern u8 Uart_ReSend_Counter;
extern u16 Uart_Tx_counter;
extern u8 *Uart_Tx_Ptr;
extern u8 Data_Length_IN_Buffer;
extern u8 McuTxBuffer[MAX_APP_TX_BUFFER_LENGTH];
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
extern u8 TxClockTimer;
extern u8 AppBackupData[APP_BACKUP_DATA_LENGTH+1];
extern u8 AppBackupData_Bak[APP_BACKUP_DATA_LENGTH+1];
#endif
extern u32 gFlashPushNum;
extern u8 video_protocol[32];

#define F_AppInit_OK					APP_Flag.field.f_app_init_ok
#define F_AppPowerOn			      	APP_Flag.field.f_app_power_on
#define F_ARM2_STARTOK		     		APP_Flag.field.f_arm2_start_ok
#define F_CLOSE_BEAT_HEART_CHECK		APP_Flag.field.f_close_beat_heart_check
#define F_AppMenuOnOff				APP_Flag.field.f_app_menu_on_off
#define F_OS_ReverseAck		       	APP_Flag.field.f_os_reverse_ack

extern APP_UART_FLAG AppUartFlag;
#define F_UART_TX_BUFF_FULL		AppUartFlag.field.F_tx_buff_Full
#define F_UART_TX_ACK_CHECK		AppUartFlag.field.F_tx_ack_check
#define F_UART_INIT_FALG			AppUartFlag.field.F_uart_init_flag

#if ENABLE_SECURITY_CODE==1
extern PASSWORD_FLAG PasswordFlag;
#define PASSWORD_STATE			PasswordFlag.field.f_state

#define SET_PASSWORD				PasswordFlag.field.f_password=1
#define CLR_PASSWORD				PasswordFlag.field.f_password=0
#define GET_PASSWORD				PasswordFlag.field.f_password

#define SET_LOCK_SCREEN			PasswordFlag.field.f_lock_screen=1
#define CLR_LOCK_SCREEN			PasswordFlag.field.f_lock_screen=0
#define GET_LOCK_SCREEN			PasswordFlag.field.f_lock_screen
#endif
extern u8 ver[29];
extern u8 F_IAP_AppCom;
extern u8 F_IAP_InitSystem;
extern u8 F_IAP_Power;

void Usart_TxStart(void);
void Usart_Com_Tx_Tick(void);
void APP_Ack_Check(void);
void APP_DataAnalyse(void);
void McuTxService(void);
void APP_MainPro(void);
void AppTimer_100msEntry(void);
void NAVI_Reset_Hold(void);
void NAVI_Reset_Release(void);
void NAVI_Off(void);
void NotifyAppStateMsg(MACHINE_MISC_STATE_T  state,u8 prm);
void Mcu_Ack_Tx(u8 ackchar);
void SetPacket(void);
void NAVI_Init(void);
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
void AppBackupDataSave(void);
void AppBackupDataResetClear(void);
void AppBackupDataUpdateClear(void);
#endif
#endif






