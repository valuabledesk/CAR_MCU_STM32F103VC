#ifndef _CAN_GOLF_1535_H
#define _CAN_GOLF_1535_H

#if CAN_FUN_GOLF_1535==1
#define CAN_RX_BUFFER_LENGTH 		400
#define CAN_TX_BUFFER_LENGTH 		100

#define CAN_ID_BMS_TOTAL_INFO			0x18F810F3
#define CAN_ID_BMS_VOL_INFO				0x18F811F3
#define CAN_ID_BMS_TEMP_INFO			0x18F812F3
#define CAN_ID_BMS_STATE_INFO			0x18F813F3
#define CAN_ID_BMS_CUR_INFO				0x18F814F3
#define CAN_ID_BMS_FAULT_INFO			0x18F815F3

#define CAN_ID_GEAR_INFO					0x10F8109A
#define CAN_ID_SPEED_INFO					0x226

#define GOLF_1535_HEAD_CODE					0x2E

#define GOLF_1535_BMS_TOTAL_INFO			0x20
#define GOLF_1535_BMS_VOL_INFO				0x21
#define GOLF_1535_BMS_TEMP_INFO				0x22
#define GOLF_1535_BMS_STATE_INFO			0x23
#define GOLF_1535_BMS_CUR_INFO				0x24
#define GOLF_1535_BMS_FAULT_INFO			0x25
#define GOLF_1535_GEAR_INFO						0x26
#define GOLF_1535_SPEED_INFO					0x27
#define GOLF_BMS_SINGLE_CELL_VOL			0x28
#define GOLF_BMS_SINGLE_CELL_TEMP			0x29

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
	u16 bms_totalvol;
	u16 bms_totalcur;
	u8 bms_soc;
	u8 bms_soh;
	u16 bms_insulation;
}CAN_BMS_TOTAL_INFO;

typedef struct
{
	u16 bms_maxcellvol;
	u8 bms_maxcellvolnum;
	u8 bms_maxcellvolboxnum;
	u16 bms_mincellvol;
	u8 bms_mincellvolnum;
	u8 bms_mincellvolboxnum;  
}CAN_BMS_CELL_VOL_INFO;

typedef struct
{
	u16 bms_maxcelltemp;
	u8 bms_maxcelltempnum;
	u8 bms_maxcelltempboxnum;
	u8 bms_mincelltemp;
	u8 bms_mincelltempnum;
	u8 bms_mincelltempboxnum;
	u8 reserve;  
}CAN_BMS_CELL_TEMP_INFO;

typedef struct
{
	u8 bms_chglinestate;
	u8 bms_chgtype;
	u8 bms_chgstate;
	u8 bms_mainrlystate;
	u8 bms_negrlystate;
	u8 bms_chgrlystate;
	u16 reserve;
}CAN_BMS_CHARGE_STATE;

typedef struct
{
	u16 bms_max_chgcur;
	u16 bms_maxdischgcur;
	u16 bms_maxfeedbackcur;
	u16 bms_ratedcapacity;
}CAN_BMS_MAX_CUR_INFO;

typedef struct
{
	unsigned f_bms_totalvolhighalarm:2;
	unsigned f_bms_totalvollowalarm:2;
	unsigned f_bms_singlevolhighalarm:2;
	unsigned f_bms_singlevollowalarm:2;
}_CAN_BMS_FAULT_INFO_BYTE_0;

typedef union
{
	_CAN_BMS_FAULT_INFO_BYTE_0 field;
	u8 byte;
}CAN_BMS_FAULT_INFO_BYTE_0;

typedef struct
{
	unsigned f_bms_singlevoldiffhighalarm:2;
	unsigned f_bms_temphighalarm:2;
	unsigned f_bms_templowalarm:2;
	unsigned f_bms_tempdiffhighalarm:2;
}_CAN_BMS_FAULT_INFO_BYTE_1;

typedef union
{
	_CAN_BMS_FAULT_INFO_BYTE_1 field;
	u8 byte;
}CAN_BMS_FAULT_INFO_BYTE_1;

typedef struct
{
	unsigned f_bms_chgcurhighalarm:2;
	unsigned f_bms_dischgcurhighalarm:2;
	unsigned f_bms_insulationlowalarm:2;
	unsigned f_bms_soclowalarm:2;
}_CAN_BMS_FAULT_INFO_BYTE_2;

typedef union
{
	_CAN_BMS_FAULT_INFO_BYTE_2 field;
	u8 byte;
}CAN_BMS_FAULT_INFO_BYTE_2;

typedef struct
{
	unsigned f_bms_vcucomalarm:2;
	unsigned f_bms_obccomalarm:2;
	unsigned reserve:4;
}_CAN_BMS_FAULT_INFO_BYTE_3;

typedef union
{
	_CAN_BMS_FAULT_INFO_BYTE_3 field;
	u8 byte;
}CAN_BMS_FAULT_INFO_BYTE_3;

typedef struct
{
	CAN_BMS_FAULT_INFO_BYTE_0 byte0;
	CAN_BMS_FAULT_INFO_BYTE_1 byte1;
	CAN_BMS_FAULT_INFO_BYTE_2 byte2;
	CAN_BMS_FAULT_INFO_BYTE_3 byte3;
	u8 bms_cellnumber;
	u8 bms_tempnumber;
	u16 reserve;
}CAN_BMS_FAULT_INFO;

typedef struct
{
	u16 bms_single_n1_cellvol;
	u16 bms_single_n2_cellvol;
	u16 bms_single_n3_cellvol;
	u16 bms_single_n4_cellvol;
}CAN_BMS_SINGLE_CELL_VOL;

typedef struct
{
	u8 bms_single_m1_celltemp;
	u8 bms_single_m2_celltemp;
	u8 bms_single_m3_celltemp;
	u8 bms_single_m4_celltemp;
	u8 bms_single_m5_celltemp;
	u8 bms_single_m6_celltemp;
	u8 bms_single_m7_celltemp;
	u8 bms_single_m8_celltemp;
}CAN_BMS_SINGLE_CELL_TEMP;

typedef struct
{
	CAN_BMS_TOTAL_INFO bms_total_info;
	CAN_BMS_CELL_VOL_INFO bms_cell_vol_info;
	CAN_BMS_CELL_TEMP_INFO bms_cell_temp_info;
	CAN_BMS_CHARGE_STATE bms_charge_state;
	CAN_BMS_MAX_CUR_INFO bms_max_cur_info;
	CAN_BMS_FAULT_INFO bms_fault_info;
	CAN_BMS_SINGLE_CELL_VOL bms_single_cell_vol;
	CAN_BMS_SINGLE_CELL_TEMP bms_single_cell_temp;
}CAN_BMS_INFO;

typedef struct
{
	u8 gear_position;
	u16 motor_rpm;
	u8 fault;
}GEAR_INFO;

typedef struct
{
	u16 vehicle_speed;
}SPEED_INFO;

typedef	struct
{
	GEAR_INFO gear_info;
	SPEED_INFO speed_info;
}CAN_BASE_INFO;

typedef struct
{
	CAN_BMS_INFO bms_info;
	CAN_BASE_INFO base_info;
}CAN_RX_INFO;

typedef struct
{
	unsigned f_can_sleep:1;
	unsigned f_can_interrupt:1;
	unsigned f_can_rx_data:1;
	unsigned f_can_init:1;
	unsigned f_warn_flag:1;
	unsigned f_CarGlideWarning:1;
}_CAN_MAIN_FLAG;

typedef union
{
	_CAN_MAIN_FLAG field;
	u8 byte;
}CAN_MAIN_FLAG;

extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;
extern CAN_MAIN_FLAG CanMainFlag;
extern u8 CanTxErrorCounter;
extern u8 CanNoTxCounter;

#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init

#define F_GLIDE_ALLOW					CanMainFlag.field.f_CarGlideWarning
#define	F_WARN_FLAG					CanMainFlag.field.f_warn_flag

void Golf_1535_Rx_Message(void);
void Golf_1535_RxAppDataPro(u8 *buffer);
void Golf_1535_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
void Golf_1535_MainPro(void);

#endif
#endif
