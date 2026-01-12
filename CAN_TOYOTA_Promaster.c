#include "public.h"
#if CAN_FUN_TOYOTA_PROMASTER==1
TOYOTA_CAN_RX_INFO Toyota_Can_Rx_Info;


u8 CanRxBaseFlag;
u8 CanRxWarningFlag;
u32 CanTxDataTimer;

CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;

CAN_MAIN_STATE    CanMainState;
CAN_MAIN_FLAG     CanMainFlag;
//CAN_WARNING_DATA  CanWarningData;
//CAN_TIRE_STATE    CanTireState;
//CAN_AIRBAG_STATE  Can_Airbag_State;

//CAN_BASE_DATA CanBaseData;
/*
CAN_RX_INFO CanRxInfo;
CAN_TX_INFO CanTxInfo;
*/
u32 CanMainTimer;
u32 CanNoDataTimer;
u16 CanTxEpsTimer;
u16 CanTxRadarTimer;
u16 CanTxGearTimer;

u16 CanTxBaseTimer;
u16 CanTxBatteryTimer;
u16 CanTxEcallTimer;
u16 CanTxMicTimer;

//u32 CanTxStaTimer=T5min_2;
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
void CAN_TOYOTA_PostMessage(CAN_POST_MESSAGE_INDEX index)//将信息放在发送缓存里面
{
	u8 data[8]={0};
	switch(index)
	{
		default:
			break;
	}
}

u32 TestCANCounter;
void CAN_TOYOTA_Rx_Message(void)//接收函数
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		switch(message.ID)
		{
			case CAN_ID_RX1:
#if MODEL==LINUX_2389W_65
				if(message.Data[5] >= 0x80 && message.Data[5] <= 0x96)
				{
					Toyota_Can_Rx_Info.turn=0;
				  Toyota_Can_Rx_Info.steer_angle[0]=(message.Data[5]-0x80);
			    Toyota_Can_Rx_Info.steer_angle[1]=(message.Data[6]);
				}
				else
				{
          Toyota_Can_Rx_Info.turn=1;
				  Toyota_Can_Rx_Info.steer_angle[0]=(~message.Data[5]);
			    Toyota_Can_Rx_Info.steer_angle[1]=(~message.Data[6]);
				}
#else
			if(message.Data[0]&0x08)//数据需要取反
				{
					Toyota_Can_Rx_Info.turn=1;
				  Toyota_Can_Rx_Info.steer_angle[0]=(~message.Data[1]);
			    Toyota_Can_Rx_Info.steer_angle[1]=(~message.Data[0]&0x0f);
				}
				else
				{
					Toyota_Can_Rx_Info.turn=0;
				  Toyota_Can_Rx_Info.steer_angle[0]=(message.Data[1]);
			    Toyota_Can_Rx_Info.steer_angle[1]=(message.Data[0]&0x0f);
				}
				TestCANCounter++;
#endif
				if(CanTxDataTimer==0)
				{
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_STEER_ANNGLE);
					CanTxDataTimer=100;
				}
				break;
			default:
				break;
		}
	}
}

void CAN_TOYOTA_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id=buffer[1];
	switch(cmd_id)
	{
		default:
			break;
	}
}

u32 TestCANCounter2;
void CAN_TOYOTA_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case CAN_STEER_ANNGLE:
			buffer[2]=0x03;
		  buffer[3]=Toyota_Can_Rx_Info.turn;
			buffer[4]=Toyota_Can_Rx_Info.steer_angle[0];
		  buffer[5]=Toyota_Can_Rx_Info.steer_angle[1];
		TestCANCounter2++;
			break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=TOYOTA_HEAD_CODE;
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

void CAN_TOYOTA_MainPro(void)//1ms ?~{!B~}??????
{
	
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
	
	if(CanTxDataTimer)
	{
		CanTxDataTimer--;
	}
	
	CAN_TOYOTA_Rx_Message();
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
			//CAN_IC_POWER_ON;
			F_CAN_INIT=1;
			CanMainState=CAN_MAIN_INIT;
		  break;

		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			CanMainState=CAN_MAIN_NORMAL;
		  break;

		case CAN_MAIN_NORMAL:
			if(Get_ACC_Det_Flag==0)
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
				break;
			}
			/*
			if(CanRxBaseFlag==1)
			{
				//CanRxFlag=0;
				CanRxBaseFlag=0;
			  //PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_BASE_INFO);
			}
			if(CanRxWarningFlag==1)
			{
				//CanRxFlag=0;
				CanRxWarningFlag=0;
			  //PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CAN_WARNING_INFO);
			}
		
			if(CanNoDataTimer)
			{
				CanNoDataTimer--;
				if(CanNoDataTimer==0)
				{
					F_CAN_RX_DATA=0;
					CanMainState=CAN_MAIN_IDLE;
				}
			}
			if(CanTxBatteryTimer)
			{
				CanTxBatteryTimer--;
			}
		
			if(CanTxEcallTimer)
			{
				CanTxEcallTimer--;	
			}
			
			if(CanTxGearTimer)
			{
				CanTxGearTimer--;
			}
			
			if(CanTxBaseTimer)
			{
				CanTxBaseTimer--;
			}
			
			if(CanTxMicTimer)
			{
				CanTxMicTimer--;
			}
			*/
		  break;
		case CAN_MAIN_SLEEP_CFG:
			CAN1_ClearRxMessage();
			CAN_IC_STANDBY_ON;
			F_CAN_SLEEP=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_SLEEP;
			break;
		case CAN_MAIN_SLEEP:
#if CAN_WAKEUP_FUN==1
			if(F_CAN_SLEEP==0
				||F_CAN_INTERRUPT)
#else
			if(Get_ACC_Det_Flag)
#endif
			{
				CAN_IC_STANDBY_OFF;
				F_CAN_SLEEP=0;
				CanMainState=CAN_MAIN_INIT;
			}
			break;
		default:
			break;
	}
}
#endif

