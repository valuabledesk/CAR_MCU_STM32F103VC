#include "public.h"

#if CAN_FUN_IKCO_K132==1
u8 CanRxBaseFlag;
u8 CanReversFlag;
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;

CAN_MAIN_STATE    CanMainState;
CAN_MAIN_FLAG     CanMainFlag;


CAN_RX_INFO CanRxInfo;
CAN_TX_INFO CanTxInfo;
u32 CanMainTimer;
u32 CanNoDataTimer;

u32 extend_camera_use_flag=1;
u32 DRVM_KeyPressedFlag;// DRVM button had pressed
u32 ReverseGearTimer; // for gear quickly switch
u32 gear_value;
u32 gear_bak;
u16 gear_timer;
u8 e_warn;
u8 Mic_flag=1;
u8 hu_sta;
u8 e_sta=1;
void CAN_IKCO_PostMessage(CAN_POST_MESSAGE_INDEX index)//将信息放在发送缓存里面
{
	u8 data[8]={0};
	switch(index)
	{
		case cam_test1:
			data[0]=0x00;
			data[1]=0x88;
		  data[2]=0xcc;
			CAN1_TxFrame(0x666,data,8);
			break;
		default:
			break;
	}
}

void CAN_IKCO_Rx_Message(void)//接收函数
{
	u8 i;
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		switch(message.ID)
		{
			case CAN_ID_BCM_MEDIA:
				CanRxInfo.Point_MSG=message.Data[1];
				CanRxInfo.Door=message.Data[3];
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_POINTER_MESSAGE);
				break;
			case CAN_ID_BCM_CLUSTER:
				CanRxInfo.DayNightStatus=message.Data[3]>>5&0x01;
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_BASEINFO);
				break;
			case CAN_ID_BCM_NETWORK:
				
				break;
			case CAN_ID_BCM_BAOADCAST:
				
				break;
			case CAN_ID_BCM_PARKING:
				CanRxInfo.ParkingAidAssistant[0]=(0x7f&(message.Data[0]>>1))|((message.Data[5]<<6)&0x80);
			  CanRxInfo.ParkingAidAssistant[1]=(message.Data[1]&0x03)|((message.Data[1]>>1)&0x0c)|((message.Data[2]<<4)&0x30)|((message.Data[2]<<3)&0xc0);
			  if(message.Data[5]&0x02)CanReversFlag=1;
			  else CanReversFlag=0;
			  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_PARKING_AID_ASSISTANT);
				break;
			case CAN_ID_BCM_DATA_SLOW:
				CanRxInfo.OnBoard[0]=message.Data[2];
			  CanRxInfo.OnBoard[1]=message.Data[3];
			  CanRxInfo.OnBoard[2]=message.Data[4];
			  CanRxInfo.Temperature=message.Data[6];
			  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_ON_BOARD);  
			  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_BASEINFO);
				break;
			case CAN_ID_BCM_DATA_SLOW2:
				
				break;
			case CAN_ID_BCM_DATA_SLOW3:
				CanRxInfo.TimeSetting[0]=message.Data[0]>>7;
			  CanRxInfo.TimeSetting[1]=message.Data[0]&0x7f;
			  CanRxInfo.TimeSetting[2]=message.Data[1]>>4&0x01;
			  CanRxInfo.TimeSetting[3]=message.Data[1]&0x0f;
			  CanRxInfo.TimeSetting[4]=message.Data[2]&0x3f;
			  CanRxInfo.TimeSetting[5]=message.Data[3]&0x1f;
			  CanRxInfo.TimeSetting[6]=message.Data[4]&0x3f;
			  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_TIME_SETTING);
			  //CAN_IKCO_TxAppDataPro(CAN_RX_TIME_SETTING,u8 *buffer,u16 *length)
				break;
			case CAN_ID_BCM_SPEED:
				
				break;
			case CAN_ID_BCM_CONSUMPTION:
				CanRxInfo.OnBoard[3]=message.Data[1];
			  CanRxInfo.OnBoard[4]=message.Data[2];
			  CanRxInfo.OnBoard[5]=message.Data[3];
			  CanRxInfo.OnBoard[6]=message.Data[4];
			  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_ON_BOARD);
				break;
			case CAN_ID_BCM_TRIP_INFOS1:
				for(i=0;i<5;i++)
			  {
					CanRxInfo.Trip1[i]=message.Data[i];
				}
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_TRIP1);
				break;
			case CAN_ID_BCM_TRIP_INFOS2:
				for(i=0;i<5;i++)
			  {
					CanRxInfo.Trip2[i]=message.Data[i];
				}
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_RX_TRIP2);
				break;
			case CAN_ID_MMS_DIAGNOSTIC_REQUEST:
				
				break;
			case CAN_ID_BCM_VIN_WMI:
				
				break;
			case CAN_ID_BCM_VIN_VDS:
				
				break;
			case CAN_ID_BCM_VIN_VIS:
				
				break;
			case CAN_ID_ICN_INFO:
				
				break;
			case CAN_ID_ATC_ACK:
				
				break;
			case CAN_ID_ATC_INFO:
				
				break;
			case CAN_ID_ATC_SUPERVISION:
				break;
			default:
				break;
		}
		//message.DLC;
		//CAN_IKCO_PostMessage(cam_test1);
	}
}
void CAN_IKCO_Tx_Message(void)//发送函数
{
	u8 data[8];
	u8 buf_length;
	MESSAGE*nEvt;
	nEvt=GetMessage(MAIN_CAN_MODULE);
	if(nEvt->ID==NO_EVT)
	{
		return;
	}
	switch(nEvt->prm)
	{
		case CAN_ID_MMS_DATE_TIME:
			buf_length=5;
		  data[0]=(CanTxInfo.TimeSetting[0]<<7)&0x80+(CanTxInfo.TimeSetting[1]&0x7f);
		  data[1]=(CanTxInfo.TimeSetting[2]<<4)&0x10+CanTxInfo.TimeSetting[3]&0x0f;
		  data[2]=CanTxInfo.TimeSetting[4]&0x3f;
		  data[3]=CanTxInfo.TimeSetting[5]&0x1f;
		  data[4]=CanTxInfo.TimeSetting[6]&0x3f;
			break;
		case CAN_ID_MMS_CONFIG:
			buf_length=8;
		  data[0]=(CanTxInfo.ConfigurationInfos[0]<<2)&0x04;//+(CanTxInfo.ConfigurationInfos[1]&0x7f);
		  data[1]=(CanTxInfo.ConfigurationInfos[0]>>4)&0x40+(CanTxInfo.ConfigurationInfos[1]>>1)&0x38;
		  data[2]=(CanTxInfo.ConfigurationInfos[0]<<0)&0x02;
		  data[3]=(CanTxInfo.ConfigurationInfos[0]<<5)&0x80+(CanTxInfo.ConfigurationInfos[1]<<3)&0x80;
		  data[4]=(CanTxInfo.ConfigurationInfos[0]<<3)&0xc0;
		  data[5]=(CanTxInfo.ConfigurationInfos[0]>>2)&0x08+(CanTxInfo.ConfigurationInfos[1]<<4)&0x60;
			break;
		case CAN_ID_MMS_FAULT:
			break;
		case CAN_ID_MMS_DIAGNOSTIC_ANSWER:
			break;
		case CAN_ID_MMS_SUPER:
			break;
		case CAN_ID_MMS_VERSION:
			break;
		default:
			break;
	}
	CAN1_TxFrame(nEvt->prm,data,buf_length);
		//message.DLC;
		//CAN_IKCO_PostMessage(cam_test1);
}
void CAN_IKCO_RxAppDataPro(u8 *buffer)
{
	u8 i;
	u8 cmd_id;
	//u8 *ptr;
	u8 length=0;
	cmd_id=buffer[1];
	switch(cmd_id)
	{
		case CAN_TX_TIME_SETTING://CAN_ID_MMS_DATE_TIME:
			length=7;
		  for(i=0;i<length;i++)
		  {
			  CanTxInfo.TimeSetting[i]=buffer[3+i];
			}
			PostMessage(MAIN_CAN_MODULE,MCU_RX_APP_COPYDATA,CAN_ID_MMS_DATE_TIME);
			break;
		case CAN_TX_Configuration_Infos:
			length=2;
		  for(i=0;i<length;i++)
		  {
			  CanTxInfo.ConfigurationInfos[0]=buffer[3+i];
			}
			PostMessage(MAIN_CAN_MODULE,MCU_RX_APP_COPYDATA,CAN_ID_MMS_CONFIG);
			break;
		default:
			length=0;
			break;
	}
	/*
	if(length)//内置can此算法可能不适用
	{
		for(i=0;i<length;i++)
		{
			ptr[i]=buffer[i+3];
		}
		PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,cmd_id);
	}
	*/
}

void CAN_IKCO_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	switch(cmd_id)
	{
		case CAN_RX_PARKING_AID_ASSISTANT:
			buffer[2]=0x02;
			buffer[3]=CanRxInfo.ParkingAidAssistant[0];
			buffer[4]=CanRxInfo.ParkingAidAssistant[1];
			break;
		case CAN_RX_TIME_SETTING:
			buffer[2]=0x07;
			buffer[3]=CanRxInfo.TimeSetting[0];
			buffer[4]=CanRxInfo.TimeSetting[1];
			buffer[5]=CanRxInfo.TimeSetting[2];
			buffer[6]=CanRxInfo.TimeSetting[3];
		  buffer[7]=CanRxInfo.TimeSetting[4];
			buffer[8]=CanRxInfo.TimeSetting[5];
		  buffer[9]=CanRxInfo.TimeSetting[6];
			break;  
    case CAN_RX_ON_BOARD:
			buffer[2]=0x07;
			buffer[3]=CanRxInfo.OnBoard[0];
			buffer[4]=CanRxInfo.OnBoard[1];
			buffer[5]=CanRxInfo.OnBoard[2];
			buffer[6]=CanRxInfo.OnBoard[3];
		  buffer[7]=CanRxInfo.OnBoard[4];
			buffer[8]=CanRxInfo.OnBoard[5];
		  buffer[9]=CanRxInfo.OnBoard[6];
			break;
		case CAN_RX_TRIP1:
			buffer[2]=0x05;
			buffer[3]=CanRxInfo.Trip1[0];
			buffer[4]=CanRxInfo.Trip1[1];
			buffer[5]=CanRxInfo.Trip1[2];
			buffer[6]=CanRxInfo.Trip1[3];
		  buffer[7]=CanRxInfo.Trip1[4];
			break;
		case CAN_RX_TRIP2:
			buffer[2]=0x05;
			buffer[3]=CanRxInfo.Trip2[0];
			buffer[4]=CanRxInfo.Trip2[1];
			buffer[5]=CanRxInfo.Trip2[2];
			buffer[6]=CanRxInfo.Trip2[3];
		  buffer[7]=CanRxInfo.Trip2[4];
			break;
		case CAN_RX_POINTER_MESSAGE:
			buffer[2]=0x02;
			buffer[3]=CanRxInfo.Point_MSG;
			buffer[4]=CanRxInfo.Door;
			break;
		case CAN_RX_BASEINFO:
			buffer[2]=0x02;
			buffer[3]=CanRxInfo.Temperature;
			buffer[4]=CanRxInfo.DayNightStatus;
			break;
		default:
			{
				flag=0;
			}
			break;
	}
	if(flag)
	{	
		buffer[0]=IKCO_HEAD_CODE;
		buffer[1]=cmd_id;
		*length=buffer[2]+4;
		for(i=0;i<(buffer[2]+2);i++)
		{
			checksum+=buffer[i+1];
		}
		buffer[i+1]=checksum;
	}
	else
	{
		*length=0;
	}
}

void CAN_IKCO_MainPro(void)//1ms ?~{!B~}??????
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
	if(F_CAN_INIT)
	{
		CAN1_Transmit();
	}
	switch(CanMainState)
	{
		
		case CAN_MAIN_IDLE:
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;
		  break;
		case CAN_MAIN_CFG:
			CAN1_Init();
			CanMainState=CAN_MAIN_POWER_OFF;
			CanMainTimer=T2S_1;
		  break;
		case CAN_MAIN_POWER_OFF:
			if(CanMainTimer)
			{
				break;
			}
			//CAN_IC_POWER_OFF;
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_POWER_ON;
			CanMainTimer=T2S_1;
		  break;
		case CAN_MAIN_POWER_ON:
			if(CanMainTimer)
			{
				break;
			}
			CAN_IC_POWER_ON;
			CAN_IC_POWER_ON2;
			CAN_IC_STANDBY_OFF;
			CanMainState=CAN_MAIN_INIT;
		  break;
		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			CanMainState=CAN_MAIN_NORMAL;
			F_CAN_INIT=1;
			break;
		case CAN_MAIN_NORMAL:
#if CAN_WAKEUP_FUN == 1
			if (F_CAN_RX_DATA == 0)
#else
			if (Get_ACC_Det_Flag == 0)
#endif
			{	
				CanMainState = CAN_MAIN_GO_TO_SLEEP;
				CanMainTimer=T2S_1;
				break;
			}
			if(CanRxBaseFlag==1)
			{
				CanRxBaseFlag=0;
			}
			CAN_IKCO_Rx_Message();
			CAN_IKCO_Tx_Message();
			/*
			if(CanNoDataTimer)
			{
				CanNoDataTimer--;
				if(CanNoDataTimer==0)
				{
					F_CAN_RX_DATA=0;
					CanMainState=CAN_MAIN_IDLE;
				}
			}
			*/
			break;
		case CAN_MAIN_GO_TO_SLEEP:
			if(Get_ACC_Det_Flag)
			{
				CanMainState=CAN_MAIN_NORMAL;
			}
			else if(CanMainTimer==0)
			{
				CAN_IC_STANDBY_ON;
				F_CAN_SLEEP=1;
				CanMainState=CAN_MAIN_SLEEP_CFG;
				CanMainTimer=T1S5_1;
			}
			break;
		case CAN_MAIN_SLEEP_CFG:
			if(CanMainTimer)
			{
				break;
			}
			CAN_IC_DISABLE;
			CAN_IC_POWER_OFF;
			CAN_IC_POWER_OFF2;
			CAN1_ClearRxMessage();
			CanMainState=CAN_MAIN_SLEEP;
			break;
		case CAN_MAIN_SLEEP:
#if CAN_WAKEUP_FUN == 1
			if (F_CAN_SLEEP == 0 || F_CAN_INTERRUPT)
#else
			if (Get_ACC_Det_Flag)
#endif
			{
				F_CAN_SLEEP = 0;
				CAN_IC_ENABLE;
				CAN_IC_STANDBY_OFF;
				CanMainState = CAN_MAIN_POWER_ON;
			}
			  break;
		default:
			break;
	}
}
#endif

