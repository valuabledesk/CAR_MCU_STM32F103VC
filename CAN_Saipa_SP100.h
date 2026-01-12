#ifndef _CAN_SAIPA_SP100_H_
#define _CAN_SAIPA_SP100_H_
#if CAN_FUN_SAIPA_SP100 == 1

#define CAN_RX_BUFFER_LENGTH 400
#define CAN_TX_BUFFER_LENGTH 100

/*************** Receive ID********************/
#define CAN_ID_EMS_1 0x101
#define CAN_ID_CHASSIS 0x110
#define CAN_ID_BODY_1 0x310
#define CAN_ID_BODY_2 0x320
#define CAN_ID_BODY_3 0x401
#define CAN_ID_ASSIST 0x340
#define CAN_ID_TPMS_1 0x410
#define CAN_ID_TPMS_2 0x420
#define CAN_ID_PHYSICAL_REQ 0x762
#define CAN_ID_BCM_NM 0x501

#define CAN_ID_ICM 0x220
#define CAN_ID_ICM_NM 0x502

/*************** Transmit ID********************/
#define CAN_ID_MMU 0x430
#define CAN_ID_NM 0x504
#define CAN_ID_PHYSICAL_RES 0x722

/***************APP Cmd***********************/
#define SAIPA_SP100_RX_EMS_INFO 0x20
#define SAIPA_SP100_RX_CHASSIS_INFO 0x21
#define SAIPA_SP100_RX_BODY_INFO 0x22
#define SAIPA_SP100_RX_ASSIST_INFO 0x23
#define SAIPA_SP100_RX_TPMS_INFO 0x24
#define SAIPA_SP100_DIAGNOSTIC 0x25

#define SAIPA_SP100_TX_REQ_CMD 0x90
#define SAIPA_SP100_TX_MMU_CMD 0x8A

#define SAIPA_SP100_HEAD_CODE 0x2E

#define MMU_SOURCE_ID 0x04

#define T_TYP 100
#define T_MAX 260
#define T_ERROR 1000
#define T_WAITBUSSLEEP 1500
#define T_SLEEPACK	2000

#define RX_LIMIT 4
#define TX_LIMIT 8

typedef struct
{
	u8 bussleep;
	u8 limphome;
	u8 configurationstable;
} NETWORK_MANAGEMENT_NETWORKSTATUS;

typedef struct
{
	u8 ind;
	u8 ack;
	u8 ack_recieved;
	u8 ind_recieved;
} NETWORK_MANAGEMENT_SLEEP;

typedef struct
{
	u8 marker;
} NETWORK_MANAGEMENT_DESTINATION;

typedef struct
{
	u8 present;
	u8 limphome;
} NETWORK_MANAGEMENT_CONFIG;

typedef enum
{
	TTyp,
	TMax,
	TError,
	TWaitBusSleep,
	TSleepACK,
} ALARM_TYPE;

typedef enum
{
	NMOff,
	NMInit,
	NMNormal,
	NMBusSleep,
	NMInitReset,
	NMTwbsNormal,
	NMReset,
	NMInitLimpHome,
	NMLimpHome,
	NMNormalPrepSleep,
	NMInitBusSleep,
	NMLimpHomePrepSleep,
	NMTwbsLimpHome,
	NMSendSleepACK,
} CAN_NM_STATE;

typedef struct
{
	unsigned Alive : 1;
	unsigned Ring : 1;
	unsigned Limphome : 1;
	unsigned reserved : 1;
	unsigned SleepInd : 1;
	unsigned SleepAck : 1;
	unsigned reserved_ : 2;
} _MESSAGE_TYpe;

typedef union
{
	u8 byte;
	_MESSAGE_TYpe field;
} MESSAGE_TYpe;

typedef struct
{
	u8 L;
	u8 R;
	u8 S;
	u8 D;
	u16 Timer;
	u8 NMrxcount;
	u8 NMtxcount;
	CAN_NM_STATE current_state;
	CAN_NM_STATE previous_state;
	NETWORK_MANAGEMENT_NETWORKSTATUS Networkstatus;
	NETWORK_MANAGEMENT_SLEEP Sleep;
	NETWORK_MANAGEMENT_DESTINATION Destination;
	NETWORK_MANAGEMENT_CONFIG Config;
	u8 f_Ring;
	u8 f_Skipped_Checking;
	u8 f_Sleep_Indication;
	u8 f_Sleep_Indication_NO_ACC;

	u8 TTypTimer;
	u16 TMaxTimer;
	u16 TErrorTimer;
	u16 TWaitBusSleepTimer;
	u16 TSendSleepAckTimer;
	u8 timeoutTTyp;
	u8 timeoutTMax;
	u8 timeoutTError;
	u8 timeoutTWaitBusSleep;
	u8 timeoutTSendSleepAck;

	u8 limphomemarket;

	u8 NMMessageTransmitted;
	u8 NMMessageRecieved;
	MESSAGE_TYpe TXMessageType;
	MESSAGE_TYpe RXMessageType;
	u8 RXSender;

	u8 NMReceived;

	u8 gotoModeBusSleep;
	u8 gotoModeAwake;
	
	u8 ACCStatus;
} CAN_NETWORK_MANAGEMENT;

typedef enum
{
	CAN_DIAG_INIT = 0,
	CAN_MAIN_IDLE,
	CAN_MAIN_CFG,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
	CAN_MAIN_SLEEP_CFG,
	CAN_MAIN_GOTO_SLEEP,
	CAN_MAIN_SLEEP
} CAN_MAIN_STATE;

typedef enum
{
	CAN_POST_MSG_NONE = 0,
	CAN_POST_MSG_MMU,
	CAN_POST_MSG_NM,
	CAN_POST_MSG_PHYSICAL_RES,
	CAN_POST_MSG_BODY_1_AUTO_TEST,
	CAN_POST_MSG_MAX_INDEX,
} CAN_POST_MESSAGE_INDEX;

#define DIAGNOSTIC_SID_START_DIAG_SESSION_POSITIVE 0x10
#define DIAGNOSTIC_SID_CLEAR_DTC 0x14
#define DIAGNOSTIC_SID_READ_DTC 0x17
#define DIAGNOSTIC_SID_READ_DATA_BY_LOCAL_IDENTIFIER 0x21
#define DIAGNOSTIC_SID_ACTUATORS 0x30
#define DIAGNOSTIC_SID_TESETER 0x3e
#define DIAGNOSTIC_SID_WRITE_DATA_BY_LOCAL_IDENTIFIER 0x3B
#define DIAGNOSTIC_SID_ECU_RESET 0x11
#define DIAGNOSTIC_SID_NR 0x7F

#define DIAGNOSTIC_DATA_ID_HU_CROUSE_CODE 0x70
#define DIAGNOSTIC_DATA_ID_DU_CROUSE_CODE 0x71
#define DIAGNOSTIC_DATA_ID_HU_TECHNICAL_NUMBER 0x72
#define DIAGNOSTIC_DATA_ID_DU_TECHNICAL_NUMBER 0x73
#define DIAGNOSTIC_DATA_ID_CROUSE_MANUFACTURING_DATE 0x74
#define DIAGNOSTIC_DATA_ID_PRODUCT_SERIAL_NUMBER 0x75
#define DIAGNOSTIC_DATA_ID_VEHICLE_IDENTIFICATION_NUMBER 0x78
#define DIAGNOSTIC_DATA_ID_CUSTOMER_EOL_OPERATION_DATE 0x79
#define DIAGNOSTIC_DATA_ID_AFTERSALES_LAST_OPERATION_DATE 0x7a
#define DIAGNOSTIC_DATA_ID_CAR_MODEL 0x7b
#define DIAGNOSTIC_DATA_ID_CAR_OPTIONS 0x7c
#define DIAGNOSTIC_DATA_ID_HANDBRAKE_CONTROL 0x7d
#define DIAGNOSTIC_DATA_ID_REVERSE_GEAR_CONTROL 0x7e
#define DIAGNOSTIC_DATA_ID_ILLUMINATION_CONTROL 0x7f
#define DIAGNOSTIC_DATA_ID_FAULTS_DISPLAY 0x80
#define DIAGNOSTIC_DATA_ID_INTRO_LOGO 0x85

typedef struct
{
	unsigned Transmission : 1;
	unsigned OAT : 1;
	unsigned RPA : 1;
	unsigned BSD : 1;
	unsigned TPMS : 1;
	unsigned reserve : 2;
	unsigned Dynamic_guideline_control : 1;
} _CAR_OPTION;

typedef union
{
	_CAR_OPTION field;
	u8 byte;
} CAR_OPTION;

typedef struct
{
	u8 HUTechnicalNumber[14];
	u8 crouseManufacturingDate[8];
	u8 HUCrouseCode[12];
	u8 DUCrouseCode[12];
	u8 DUTechnicalNumber[14];
	u8 productSerialNumber[17];
	u8 vehicleIdentificationNumber[17];
	u8 VINWritten;
	u8 customerEOLOperationDate[8];
	u8 aftersalesLastOperationDate[8];
	u8 carModel;
	CAR_OPTION carOptions;
	u8 handbrakeControl;
	u8 reverseGearControl;
	u8 illuminationControl;
	u8 faultsDisplay;
	u8 introLogo;
} CAN_DIAGNOSTIC_DATA;

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
	u8 veh_speed;
	u8 eng_speed_L8;
	u8 eng_speed_H5;
	u8 powerDistributionStep;
} CAN_EMS_INFO;

typedef struct
{
	u8 steering_wheel_angle_L8;
	u8 steering_wheel_angle_H8;
	u8 f_parking_brake_activation;
} CAN_CHASSIS_INFO;

typedef struct
{
	unsigned f_position_lamps : 2;
	unsigned f_seat_belt_led : 4;
	unsigned low_fuel_lamp_status : 2;
} _CAN_BODY_INFO_BYTE_2;

typedef union
{
	_CAN_BODY_INFO_BYTE_2 field;
	u8 byte;
} CAN_BODY_INFO_BYTE_2;

typedef struct
{
	u8 f_door;
	u8 outdoor_ambient_temperature;
	CAN_BODY_INFO_BYTE_2 byte_2;
	u8 odo_L8;
	u8 odo_ML8;
	u8 odo_MH8;
	u8 odo_H8;
} CAN_BODY_INFO;

typedef struct
{
	unsigned rpa_bsd_mode : 1;
	unsigned f_bsd_switch : 1;
	unsigned f_rpa : 1;
	unsigned f_rpa_rl_s : 1;
	unsigned f_rpa_rr_s : 1;
	unsigned reserved : 3;
} _CAN_ASSIST_INFO_BYTE_0;

typedef union
{
	_CAN_ASSIST_INFO_BYTE_0 field;
	u8 byte;
} CAN_ASSIST_INFO_BYTE_0;

typedef struct
{
	unsigned bsd_rl_dist_H1 : 1;
	unsigned bsd_r_warn_lvl : 2;
	unsigned bsd_l_warn_lvl : 2;
	unsigned reserved : 2;
	unsigned bsd_rr_dist_H1 : 1;
} _CAN_ASSIST_INFO_BYTE_5;

typedef union
{
	_CAN_ASSIST_INFO_BYTE_5 field;
	u8 byte;
} CAN_ASSIST_INFO_BYTE_5;

typedef struct
{
	CAN_ASSIST_INFO_BYTE_0 byte_0;
	u8 rpa_rl_dist;
	u8 rpa_rr_dist;
	u8 f_bsd;
	u8 bsd_rl_dist_L8;
	CAN_ASSIST_INFO_BYTE_5 byte_5;
	u8 bsd_rr_dist_L8;
} CAN_ASSIST_INFO;

typedef struct
{
	u8 fl_pres;
	u8 fl_temp;
	u8 fr_pres;
	u8 fr_temp;
	u8 rl_pres;
	u8 rl_temp;
	u8 rr_pres;
	u8 rr_temp;
	u8 f_tpms_error;
	u8 f_tpms_self_local;
	u8 f_fl;
	u8 f_fr;
	u8 f_rl;
	u8 f_rr;
} CAN_TPMS_INFO;

typedef struct
{
	CAN_EMS_INFO ems_info;
	CAN_CHASSIS_INFO chassis_info;
	CAN_BODY_INFO body_info;
	CAN_ASSIST_INFO assist_info;
	CAN_TPMS_INFO tpms_info;
} CAN_RX_INFO;

typedef struct
{
	u8 timeFormat12;
	u8 dateFormatIranian;
	u8 f_bsd_switch;
	u8 day;
	u8 month;
	u8 year;
} CAN_MMU_INFO;

typedef struct
{
	unsigned nm_alive : 1;
	unsigned nm_ring : 1;
	unsigned nm_limphome : 1;
	unsigned reserved : 1;
	unsigned nm_sleep_indication : 1;
	unsigned nm_sleep_ack : 1;
	unsigned reserved1 : 2;

} _CAN_NM_INFO_BYTE_1;

typedef union
{
	_CAN_NM_INFO_BYTE_1 field;
	u8 byte;
} CAN_NM_INFO_BYTE_1;

typedef struct
{
	u8 dest_id;
	CAN_NM_INFO_BYTE_1 byte_1;
} CAN_NM_INFO;

typedef struct
{
	u8 PCI;
	u8 byte_1;
	u8 byte_2;
	u8 byte_3;
	u8 byte_4;
	u8 byte_5;
	u8 byte_6;
	u8 byte_7;
} CAN_DIAG_INFO;

typedef struct
{
	CAN_MMU_INFO mmu_info;
	CAN_NM_INFO nm_info;
	CAN_DIAG_INFO diag_info;
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
extern CAN_DIAGNOSTIC_DATA CANDiagData;
extern u32 CANSleepTime;
extern u32 CANSleepTime_NOW;
extern u8 CANSleepFlag;
#define F_CAN_SLEEP CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT CanMainFlag.field.f_can_init

void Saipa_SP100_MainPro(void);
void Saipa_SP100_RxAppDataPro(u8 *buffer);
void Saipa_SP100_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length);

#endif
#endif
