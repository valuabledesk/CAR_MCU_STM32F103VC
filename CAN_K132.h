#ifndef _CAN_IKCO_H_
#define _CAN_IKCO_H_
#if CAN_FUN_IKCO_K132==1


#define CAN_RX_BUFFER_LENGTH 							400
#define CAN_TX_BUFFER_LENGTH 							100
/**********************MULTIMEDIA SYSTEM (MMS)***************************/
#define CAN_ID_MMS_DATE_TIME						0x39B//MMS Date&Time Setting
#define CAN_ID_MMS_CONFIG   						0x15B//MMS Configuration Infos
#define CAN_ID_MMS_FAULT    						0x4A4//MMS Fault Report
#define CAN_ID_MMS_DIAGNOSTIC_ANSWER		0x664//MMS Diagnostic Answer
#define CAN_ID_MMS_SUPER   					  	0x524//MMS Supervision
#define CAN_ID_MMS_VERSION    					0x5E4//MMS Version
/**********************BODY CONTROL MODULE (NBCM)**************************/
#define CAN_ID_BCM_MEDIA    						0x1A1//BCM Multimedia Message
#define CAN_ID_BCM_CLUSTER   						0x128//BCM Cluster Info1
#define CAN_ID_BCM_NETWORK   						0x036//Network Management
#define CAN_ID_BCM_BAOADCAST         		0x7FF//Broadcast Diagnostic Request
#define CAN_ID_BCM_PARKING   					  0x0E1//BCM Parking Aid Assistant
#define CAN_ID_BCM_DATA_SLOW    				0x0F6//BCM Data Slow
#define CAN_ID_BCM_DATA_SLOW2   				0x236//BCM Data Slow 2
#define CAN_ID_BCM_DATA_SLOW3   				0x276//BCM Data Slow 3
#define CAN_ID_BCM_SPEED         	    	0x0B6//BCM RPM/Speed Information
#define CAN_ID_BCM_CONSUMPTION   				0x221//BCM Consumption Infos
#define CAN_ID_BCM_TRIP_INFOS1    			0x2A1//BCM Trip Infos 1
#define CAN_ID_BCM_TRIP_INFOS2    			0x261//BCM Trip Infos 2
#define CAN_ID_MMS_DIAGNOSTIC_REQUEST		0x764//MMS Diagnostic Request
#define CAN_ID_BCM_VIN_WMI         	    0x336//VIN World Manufacturer Identification
#define CAN_ID_BCM_VIN_VDS      				0x3B6//VIN Vehicle Descriptor Section
#define CAN_ID_BCM_VIN_VIS        			0x2B6//VIN Vehicle Indicator Section
/**********************Instrument Cluster Node (ICN)**************************/
#define CAN_ID_ICN_INFO    			        0x217//ICN Information
/**********************ATC(Autonomous telematic control)**************************/
#define CAN_ID_ATC_ACK		              0x62C//Fault reports ACK
#define CAN_ID_ATC_INFO    			        0x139//ATC information1
#define CAN_ID_ATC_SUPERVISION		      0x4E3//ATC Supervision



#define IKCO_HEAD_CODE					      	     0x2E
/***send to APP by MCU*****/
#define CAN_RX_PARKING_AID_ASSISTANT         0x50
#define CAN_RX_TIME_SETTING                  0x51
#define CAN_RX_ON_BOARD                      0x52
#define CAN_RX_TRIP1                         0x53
#define CAN_RX_TRIP2                         0x54
#define CAN_RX_POINTER_MESSAGE               0x55
#define CAN_RX_BASEINFO                   	 0x56
/**************/
#define CAN_TX_TIME_SETTING                  0x30
#define CAN_TX_Configuration_Infos           0x31

typedef struct
{
	u8 ParkingAidAssistant[2];
	u8 TimeSetting[7];
	u8 OnBoard[7];
	u8 Trip1[5];
	u8 Trip2[5];
	u8 Point_MSG;
	u8 Temperature;
	u8 Door;
	u8 DayNightStatus;
	/*
	u8 NBCM_BCM_Multimedia_Message[8];
	u8 NBCM_BCM_Cluster_Info1[8];
	u8 NBCM_Network_Management[8];
	u8 NBCM_Broadcast_Diagnostic_Request[8];
	u8 NBCM_BCM_Parking_Aid_Assistant[8];
	u8 NBCM_BCM_Data_Slow[8];
	u8 NBCM_BCM_Data_Slow2[8];
	u8 NBCM_BCM_Data_Slow3[8];
	u8 NBCM_BCM_RPM_Speed_Information[8];
	u8 NBCM_BCM_Consumption_Infos[8];
	u8 NBCM_BCM_Trip_Infos1[8];
	u8 NBCM_BCM_Trip_Infos2[8];
	u8 NBCM_MMS_Diagnostic_Request[8];
	u8 NBCM_VIN_World_Manufacturer_Identification[8];
	u8 NBCM_VIN_Vehicle_Descriptor_Section[8];
	u8 NBCM_VIN_Vehicle_Indicator_Section[8];
	u8 ICN_ICN_Information[8];
	u8 ATC_Fault_reports_ACK[8];
	u8 ATC_ATC_information1[8];
	*/
}CAN_RX_INFO;

typedef struct
{
  u8 TimeSetting[8];
	u8 ConfigurationInfos[8];
	
	
	/*
	u8 MMS_Date_Time_Setting[5];//待使用
	u8 MMS_Configuration_Infos[7];
	u8 MMS_Fault_Report[8];//待使用
	u8 MMS_Diagnostic_Answer[8];
	u8 MMS_Supervision[8];//待使用
	u8 MMS_Version[8];
	*/
}CAN_TX_INFO;

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
typedef enum
{
	CAN_MAIN_IDLE=0,
	CAN_MAIN_CFG,
	CAN_MAIN_POWER_OFF,
	CAN_MAIN_POWER_ON,
	CAN_MAIN_INIT,
	CAN_MAIN_NORMAL,
	CAN_MAIN_GO_TO_SLEEP,
	CAN_MAIN_SLEEP_CFG,
	CAN_MAIN_SLEEP
}CAN_MAIN_STATE;



typedef enum
{
	CAN_POST_MSG_NONE=0,
	cam_test1,
	cam_test2,
	CAN_POST_MSG_MAX_INDEX
}CAN_POST_MESSAGE_INDEX;
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


extern CAN_RX_BUFFER CanRxBuffer;
extern CAN_TX_BUFFER CanTxBuffer;

//extern CAN_BASE_DATA     CanBaseData;
//extern CAN_WARNING_DATA  CanWarningData;
extern CAN_MAIN_FLAG     CanMainFlag;
//extern CAN_AIRBAG_STATE  Can_Airbag_State;

extern CAN_RX_INFO CanRxInfo;
extern CAN_TX_INFO CanTxInfo;
extern u8 CAN_RX_LENHTH[32];
extern u8 CanReversFlag;
#define F_CAN_SLEEP				CanMainFlag.field.f_can_sleep
#define F_CAN_INTERRUPT		CanMainFlag.field.f_can_interrupt
#define F_CAN_RX_DATA			CanMainFlag.field.f_can_rx_data
#define F_CAN_INIT				CanMainFlag.field.f_can_init
void CAN_IKCO_RxAppDataPro(u8 *buffer);
void CAN_IKCO_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length);
void CAN_IKCO_MainPro(void);

void CAN_IKCO_PostMessage(CAN_POST_MESSAGE_INDEX index);
#endif
#endif








