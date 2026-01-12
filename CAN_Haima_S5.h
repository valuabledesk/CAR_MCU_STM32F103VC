#ifndef _CAN_HAIMA_S5_
#define _CAN_HAIMA_S5_
#if CAN_FUN_HAIMA_S5==1

#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		100


#define CAN_ID_VEHICLE_WARNING	0x58B
#define CAN_ID_BCM_INFO			0x300
#define CAN_ID_TCU_INFO			0x103
#define CAN_ID_STEER_INFO		0x80
#define CAN_ID_ESP_PT_FrP03 0x3E1



#define HAIMA_S5_RX_VEHICLE_WARING_INFO		0x36
#define HAIMA_S5_TX_AVM_CMD					0xC6


#define HAIMA_S5_HEAD_CODE					0x2E

typedef enum
{
	VEHICLE_WARNING_NONE =                               0x00,            //NONE（无告警信息）
	VEHICLE_WARNING_KEEP_KEY_CLOSE =                     0x01,          //Please keep the key close to the start button（请将钥匙靠近启动按钮）
	VEHICLE_WARNING_KEEP_P_N =                           0x02,            //Please keep in P or N shift gear（请将档位置于 P档或 N 档）
	VEHICLE_WARNING_CLUTCH_PRESS_STARTBUTTON =           0x03,             //Please step on clutch and press start button to start engine（请踩下离合踏板，按启动按键启动发动机）
	VEHICLE_WARNING_BREAKS_PRESS_STARTBUTTON =           0x04,           // Please brakes and press start button to start engine（请踩下刹车踏板，按启动按键启动发动机）
	VEHICLE_WARNING_KEEP_P =                             0x05,           //  Please keep in P shift gear（请将档位置于 P 档）
	VEHICLE_WARNING_KEEP_N_PRESS_STARTBUTTON =           0x06,          //  Please keep in N shift gear and press start button（请将档位置于 N 档并按下启动按键）
	VEHICLE_WARNING_PRESS_STARTBUTTON =                  0x07                   //Please press start button（请按下启动按键）
}PEPS_VEHICLE_WARNING_STATUS;


typedef enum
{
	CANBOX_WARNING_NONE =                       0x00,              //NONE（无告警信息）
	CANBOX_WARNING_KEY_NOT_DETECTED =           0x01,
	CANBOX_WARNING_REPLACE_KEY_BATTERY =        0x02,
	CANBOX_WARNING_KEEP_KEY_CLOSE =             0x03,             //Please keep the key close to the start button（请将钥匙靠近启动按钮）
	CANBOX_WARNING_PRESS_STARTBUTTON =          0x04,             //Please press start button（请按下启动按键）
	CANBOX_WARNING_BREAKS_PRESS_STARTBUTTON =   0x05,             // Please brakes and press start button to start engine（请踩下刹车踏板，按启动按键启动发动机）
	CANBOX_WARNING_CLUTCH_PRESS_STARTBUTTON =   0x06,             //Please step on clutch and press start button to start engine（请踩下离合踏板，按启动按键启动发动机）
	CANBOX_WARNING_KEEP_P =                     0x07,             //  Please keep in P shift gear（请将档位置于 P 档）
	CANBOX_WARNING_KEEP_N_PRESS_STARTBUTTON =   0x08,             //  Please keep in N shift gear and press start button（请将档位置于 N 档并按下启动按键）
	CANBOX_WARNING_KEEP_P_N =                   0x09,             //Please keep in P or N shift gear（请将档位置于 P档或 N 档）
	CANBOX_WARNING_KEEP_P_CAR_GLIDE =           0x0A              //Please keep in P shift,otherwise car will glide
}VEHICLE_WARNING_INFO_TypeDef;

typedef enum
{
	CANBOX_CAMERA_SWITCH =              0x01,
	CANBOX_CAMERA_EXIT =                0x02,
	CANBOX_CAMERA_KEY_PREES =           0x03,
	CANBOX_CAMERA_KEY_RELEASE =         0x04
}CANBOX_BVS_KEY_CMD;


typedef enum
{
	CAN_MAIN_IDLE=0,
	CAN_MAIN_CFG,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
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
	unsigned f_warn_flag:1;
	unsigned f_CarGlideWarning:1;
}_CAN_MAIN_FLAG;


typedef struct
{
	VEHICLE_WARNING_INFO_TypeDef Vehicle_Warning_Status;
	
}CAN_RX_INFO;


typedef union
{
	_CAN_MAIN_FLAG field;
	u8 byte;
}CAN_MAIN_FLAG;

extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_MAIN_FLAG CanMainFlag;

extern u8 AccPowerDet;
extern u8 AccWirePowerStatus;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init

#define F_GLIDE_ALLOW					CanMainFlag.field.f_CarGlideWarning
#define	F_WARN_FLAG					CanMainFlag.field.f_warn_flag


void Haima_S5_MainPro(void);
void Haima_S5_RxAppDataPro(u8 *buffer);
void Haima_S5_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);

#endif
#endif
