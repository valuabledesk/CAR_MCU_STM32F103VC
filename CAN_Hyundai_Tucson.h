#ifndef _CAN_HYUNDAI_TUCSON_H_
#define _CAN_HYUNDAI_TUCSON_H_
#if CAN_FUN_HYUNDAI_TUCSON==1
#define CAN_RX_BUFFER_LENGTH 							400
#define CAN_TX_BUFFER_LENGTH 							100

#define CAN_ID_ALARM									0x15E
#define CAN_ID_BRIGHTNESS								0x1DF
#define CAN_ID_DOOR_STATUS							0x15D
#define CAN_ID_PARKING_SENSORS						0x167
#define CAN_ID_VEHICLE_INDICATIONS					0x169

#define HYUNDAI_TUCSON_RX_ALARM_STATUS				0x20
#define HYUNDAI_TUCSON_RX_BRIGHTNESS				0x21
#define HYUNDAI_TUCSON_RX_DOOR_STATUS				0x22
#define HYUNDAI_TUCSON_RX_RADAR						0x23

#define HYUNDAI_TUCSON_TX_REQ_CMD					0x90

#define HYUNDAI_TUCSON_HEAD_CODE					0x2E

typedef enum
{
	CAN_MAIN_IDLE=0,
	CAN_MAIN_CFG,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
	CAN_MAIN_WAIT_SLEEP,
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
}_CAN_MAIN_FLAG;

typedef union
{
	_CAN_MAIN_FLAG field;
	u8 byte;
}CAN_MAIN_FLAG;

typedef struct
{
	unsigned f_driver_door:1;
	unsigned f_passenger_door:1;
	unsigned f_rear_left_door:1;
	unsigned f_rear_right_door:1;
	unsigned f_tail_gate:1;
	unsigned reserved_5_7:3;
}_DOOR_STATUS;

typedef union
{
	_DOOR_STATUS field;
	u8 byte;
}DOOR_STATUS;

typedef struct
{
	u8 rear_left;
	u8 rear_center;
	u8 rear_right;
	u8 front_left;
	u8 front_center;
	u8 front_right;	
}PARKING_SENSOR;

typedef struct
{
	u8 alarm;
	u8 brightness;
	DOOR_STATUS door_status;
	PARKING_SENSOR parking_sensor;
}CAN_RX_INFO;

extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_MAIN_FLAG CanMainFlag;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init

void Hyundai_Tucson_MainPro(void);
void Hyundai_Tucson_RxAppDataPro(u8 *buffer);
void Hyundai_Tucson_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);


#endif
#endif

