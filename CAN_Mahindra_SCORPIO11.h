#ifndef _CAN_MAHINDRA_SCORPIO11_H_
#define _CAN_MAHINDRA_SCORPIO11_H_
#if CAN_FUN_MAHINDRA_SCORPIO11 == 1

#define CAN_RX_BUFFER_LENGTH 400
#define CAN_TX_BUFFER_LENGTH 100

/*************** Receive ID********************/
#define CAN_ID_EMS_1 0x124
#define CAN_ID_MBFM_1 0x348
#define CAN_ID_FATC_1 0x300
#define CAN_ID_MBFM_5 0x214
#define CAN_ID_MBFM_6 0x218
#define CAN_ID_MBFM_7 0x21C
#define CAN_ID_RPAS_1 0x22C
// #define CAN_ID_CHASSIS 0x110
// #define CAN_ID_BODY_1 0x310
// #define CAN_ID_BODY_2 0x320
// #define CAN_ID_BODY_3 0x401
// #define CAN_ID_ASSIST 0x340
// #define CAN_ID_TPMS_1 0x410
// #define CAN_ID_TPMS_2 0x420
// #define CAN_ID_PHYSICAL_REQ 0x762

// #define CAN_ID_ICM 0x220

/*************** Transmit ID********************/
#define CAN_ID_IS_3 0x3CA
#define CAN_ID_IS_4 0x3CB

/***************APP Cmd***********************/
#define MAHINDRA_SCORPIO11_RX_BASE_INFO 0x20
#define MAHINDRA_SCORPIO11_RX_FATC_INFO 0x21
#define MAHINDRA_SCORPIO11_RX_TPMS_INFO 0x27
// #define MAHINDRA_SCORPIO11_RX_ASSIST_INFO 0x23
// #define MAHINDRA_SCORPIO11_RX_TPMS_INFO 0x24

#define MAHINDRA_SCORPIO11_TX_REQ_CMD 0x90
#define MAHINDRA_SCORPIO11_TX_BASE_CMD 0x8A

#define MAHINDRA_SCORPIO11_HEAD_CODE 0x2E

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
	CAN_POST_MSG_IS_1,
	CAN_POST_MSG_IS_2,
	CAN_POST_MSG_IS_3,
	CAN_POST_MSG_IS_4,
	CAN_POST_MSG_MAX_INDEX,
} CAN_POST_MESSAGE_INDEX;

typedef enum
{
	BASE_AUTO_LAMP = 1,
	BASE_AUTP_RAIN,
} MAHINDRA_CSORPIO11_BASE_KEY_INDEX;

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
	unsigned tpms_signal_missing : 4;
	unsigned tpms_program_mode : 4;
} _CAN_TPMS_INFO_BYTE_1;

typedef union
{
	_CAN_TPMS_INFO_BYTE_1 field;
	u8 byte;
} CAN_TPMS_INFO_BYTE_1;

typedef struct
{
	unsigned low_pres_alert : 5;
	unsigned spare_tyre_swap : 3;
} _CAN_TPMS_INFO_BYTE_3;

typedef union
{
	_CAN_TPMS_INFO_BYTE_3 field;
	u8 byte;
} CAN_TPMS_INFO_BYTE_3;

typedef struct
{

	u8 tpms_learnt;
	CAN_TPMS_INFO_BYTE_1 byte_1;
	u8 high_pres_alert;
	CAN_TPMS_INFO_BYTE_3 byte_3;
	u8 high_temp_alert;
	u8 leakage_alert;
	u8 tpme_system_fault;
	u8 fl_pres;
	u8 fl_temp;
	u8 fr_pres;
	u8 fr_temp;
	u8 rl_pres;
	u8 rl_temp;
	u8 rr_pres;
	u8 rr_temp;
	u8 spare_pres;
	u8 spare_temp;
} CAN_TPMS_INFO;

typedef struct
{
	unsigned mode : 3;
	unsigned blower : 4;
	unsigned f_auto : 1;
} _CAN_FATC_INFO_BYTE_0;

typedef union
{
	_CAN_FATC_INFO_BYTE_0 field;
	u8 byte;
} CAN_FATC_INFO_BYTE_0;

typedef struct
{
	unsigned dual : 1;
	unsigned econ : 1;
	unsigned ac : 1;
	unsigned r_ac : 1;
	unsigned cycle : 1;
	unsigned on_off : 1;
	unsigned reserved : 2;
} _CAN_FATC_INFO_BYTE_3;

typedef union
{
	_CAN_FATC_INFO_BYTE_3 field;
	u8 byte;
} CAN_FATC_INFO_BYTE_3;

typedef struct
{
	CAN_FATC_INFO_BYTE_0 byte_0;
	u8 drv_temp;
	u8 psg_temp;
	CAN_FATC_INFO_BYTE_3 byte_3;
	u8 ambt_temp;
} CAN_FATC_INFO;

typedef struct
{
	unsigned f_door : 6;
	unsigned f_auto_lamp : 1;
	unsigned f_auto_rain : 1;
} _CAN_BASE_INFO_BYTE_0;

typedef union
{
	_CAN_BASE_INFO_BYTE_0 field;
	u8 byte;
} CAN_BASE_INFO_BYTE_0;

typedef struct
{
	unsigned drv_belt : 2;
	unsigned psg_belt : 2;
	unsigned reserved : 4;
} _CAN_BASE_INFO_BYTE_1;

typedef union
{
	_CAN_BASE_INFO_BYTE_1 field;
	u8 byte;
} CAN_BASE_INFO_BYTE_1;

typedef struct
{
	unsigned bar_left : 4;
	unsigned bar_right : 4;
} _CAN_BASE_INFO_BYTE_2;

typedef union
{
	_CAN_BASE_INFO_BYTE_2 field;
	u8 byte;
} CAN_BASE_INFO_BYTE_2;

typedef struct
{
	CAN_BASE_INFO_BYTE_0 byte_0;
	CAN_BASE_INFO_BYTE_1 byte_1;
	CAN_BASE_INFO_BYTE_2 byte_2;
} CAN_BASE_INFO;

typedef struct
{
	CAN_TPMS_INFO tpms_info;
	CAN_FATC_INFO fatc_info;
	CAN_BASE_INFO base_info;
} CAN_RX_INFO;

typedef struct
{
	unsigned reserved : 7;
	unsigned auto_lamp : 1;
} _CAN_IS_4_INFO_BYTE_0;

typedef union
{
	_CAN_IS_4_INFO_BYTE_0 field;
	u8 byte;
} CAN_IS_4_INFO_BYTE_0;

typedef struct
{
	unsigned reserved : 7;
	unsigned auto_rain : 1;
} _CAN_IS_4_INFO_BYTE_1;

typedef union
{
	_CAN_IS_4_INFO_BYTE_1 field;
	u8 byte;
} CAN_IS_4_INFO_BYTE_1;

typedef struct
{
	CAN_IS_4_INFO_BYTE_0 byte_0;
	CAN_IS_4_INFO_BYTE_1 byte_1;
} CAN_IS_4_INFO;

typedef struct
{
	CAN_IS_4_INFO is_4_info;
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
extern CAN_TX_INFO CanTxInfo;
extern CAN_MAIN_FLAG CanMainFlag;

#define F_CAN_SLEEP CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT CanMainFlag.field.f_can_init

void Mahindra_SCORPIO11_MainPro(void);
void Mahindra_SCORPIO11_RxAppDataPro(u8 *buffer);
void Mahindra_SCORPIO11_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length);

#endif
#endif
