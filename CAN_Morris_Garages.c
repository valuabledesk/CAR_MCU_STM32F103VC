#include "public.h"

#if CAN_FUN_MORRIS_GARAGES==1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_TX_INFO CanTxInfo;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanCheckErrorTimer;

u8 CanTxTimer;
u8 CanTxErrorCounter;
u8 CanNoTxCounter;

void Morris_Garages_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8];
	
	switch(index)
	{
		case CAN_POST_MSG_SETTING_1:
			data[0]=0;
			data[1]=CanTxInfo.setting_1_info.byte_1.byte;
			data[2]=CanTxInfo.setting_1_info.byte_2.byte;
			data[3]=0;
			data[4]=0;
			data[5]=CanTxInfo.setting_1_info.byte_5.byte;
			data[6]=CanTxInfo.setting_1_info.byte_6.byte;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_SETTING_1,data,8);
			break;
		case CAN_POST_MSG_SETTING_2:
			data[0]=0;
			data[1]=0;
			data[2]=0;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=CanTxInfo.setting_2_info.byte_7.byte;
			CAN1_TxFrame(CAN_ID_SETTING_2,data,8);
			break;
		case CAN_POST_MSG_SETTING_3:
			data[0]=CanTxInfo.setting_3_info.byte_0.byte;
			data[1]=0;
			data[2]=0;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_SETTING_3,data,8);
			break;
		case CAN_POST_MSG_AIR:
			data[0]=0xFF;
			data[1]=CanTxInfo.air_info.byte_1.byte;
			data[2]=0;
			data[3]=CanTxInfo.air_info.byte_3.byte;
			data[4]=0;
			data[5]=CanTxInfo.air_info.byte_5.byte;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_AIR,data,8);
			break;
		case CAN_POST_MSG_TIME:
			data[0]=CanTxInfo.time_info.byte_0.byte;
			data[1]=CanTxInfo.time_info.byte_1.byte;
			data[2]=CanTxInfo.time_info.byte_2.byte;
			data[3]=CanTxInfo.time_info.byte_3.byte;
			data[4]=CanTxInfo.time_info.byte_4.byte;
			data[5]=CanTxInfo.time_info.byte_5.byte;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_TIME,data,8);
			break;
		default:
			break;
	}
}

void Morris_Garages_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_REVERSE:
				if((message.Data[2]&0x02)>>1==1)
				{
					CanRxInfo.base_info.byte_0.field.f_reverse_state=1;
					CanGeneralCtrlFlag.field.reverse_on_off=1;
				}
				else if((message.Data[2]&0x02)>>1==0)
				{
					CanRxInfo.base_info.byte_0.field.f_reverse_state=0;
					CanGeneralCtrlFlag.field.reverse_on_off=0;
				}
				if(!strcmp_equal(&CanRxInfo.base_info.byte_0.byte,&CanRxInfoBak.base_info.byte_0.byte,sizeof(CAN_BASE_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.base_info.byte_0.byte,&CanRxInfo.base_info.byte_0.byte,sizeof(CAN_BASE_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Morris_Garages_RX_BASIC_INFO);
				}
				break;
			case  CAN_ID_PARKING:
				if((message.Data[1]&0x10)>>4==1)
				{
					CanRxInfo.base_info.byte_0.field.f_parking_state=1;
					CanGeneralCtrlFlag.field.parking_on_off=1; 
				}
				else if((message.Data[1]&0x10)>>4==0)
				{
					CanRxInfo.base_info.byte_0.field.f_parking_state=0;
					CanGeneralCtrlFlag.field.parking_on_off=0; 
				}
				if(!strcmp_equal(&CanRxInfo.base_info.byte_0.byte,&CanRxInfoBak.base_info.byte_0.byte,sizeof(CAN_BASE_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.base_info.byte_0.byte,&CanRxInfo.base_info.byte_0.byte,sizeof(CAN_BASE_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Morris_Garages_RX_BASIC_INFO);
				}
				break;
			case CAN_ID_ILLUMI:
				if((message.Data[7]&0x80)>>7==1)
				{
					CanRxInfo.base_info.byte_0.field.f_illumi_state=1;
					CanGeneralCtrlFlag.field.ill_onoff=1;
				}
				else if(message.Data[7]&0x80==0)
				{
					CanRxInfo.base_info.byte_0.field.f_illumi_state=0;
					CanGeneralCtrlFlag.field.ill_onoff=0;
				}
				if(!strcmp_equal(&CanRxInfo.base_info.byte_0.byte,&CanRxInfoBak.base_info.byte_0.byte,sizeof(CAN_BASE_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.base_info.byte_0.byte,&CanRxInfo.base_info.byte_0.byte,sizeof(CAN_BASE_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Morris_Garages_RX_BASIC_INFO);
				}
				break;
			default:
				break;
		}
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
		CanNoDataTimer=T30S_1;
		CAN1_ClearErrorTimer();
	}
}


void Morris_Garages_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case Morris_Garages_RX_BASIC_INFO:
			buffer[2]=0x05;
			buffer[3]=CanRxInfo.base_info.byte_0.byte;
			break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=Morris_Garages_HEAD_CODE;
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

void Morris_Garages_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id=buffer[1];

	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	
	switch(cmd_id)
	{
		case Morris_Garages_TX_SETTING_CMD:
			switch(buffer[3])
			{
				case 0x00:
					CanTxInfo.setting_1_info.byte_1.field.f_follow_me_home=buffer[4];
					Morris_Garages_PostMessage(CAN_POST_MSG_SETTING_1);
					break;
				case 0x01:
					CanTxInfo.setting_1_info.byte_2.field.f_search_car=buffer[4];
					Morris_Garages_PostMessage(CAN_POST_MSG_SETTING_1);
					break;
				case 0x02:
					CanTxInfo.setting_1_info.byte_6.field.f_remote_unclock=buffer[4];
					Morris_Garages_PostMessage(CAN_POST_MSG_SETTING_1);
					break;
				case 0x03:
					CanTxInfo.setting_1_info.byte_5.field.f_near_car_unlock=buffer[4];
					Morris_Garages_PostMessage(CAN_POST_MSG_SETTING_1);
					break;
				case 0x04:
					CanTxInfo.setting_2_info.byte_7.field.f_rearview_mirror=buffer[4];
					Morris_Garages_PostMessage(CAN_POST_MSG_SETTING_2);
					break;
				case 0x05:
					if(buffer[4]==0x00)
					{
						CanTxInfo.setting_3_info.byte_0.field.f_vehicle_stability_control=1;
						Morris_Garages_PostMessage(CAN_POST_MSG_SETTING_3);
					}
					else if(buffer[4]==0x01)
					{
						CanTxInfo.setting_3_info.byte_0.field.f_vehicle_stability_control=0;
						Morris_Garages_PostMessage(CAN_POST_MSG_SETTING_3);
					}
					break;
				default:
					break;
			}
			break;
		case Morris_Garages_TX_AIR_CMD:
			CanTxInfo.air_info.byte_1.field.f_temperature=buffer[3]&0x0F;
			CanTxInfo.air_info.byte_1.field.f_blow_mode=buffer[4]&0x07;
			CanTxInfo.air_info.byte_3.field.f_speed=buffer[5]&0x07;
			CanTxInfo.air_info.byte_5.field.f_internal_external_cir=buffer[6];
			CanTxInfo.air_info.byte_5.field.f_AC=buffer[7];
			CanTxInfo.air_info.byte_1.field.f_air_sw=buffer[8];
			Morris_Garages_PostMessage(CAN_POST_MSG_AIR);
			break;
		case Morris_Garages_TX_TIME_CMD:
			CanTxInfo.time_info.byte_0.field.f_year=buffer[3]&0x3F;
			CanTxInfo.time_info.byte_1.field.f_month=buffer[4]&0x0F;
			CanTxInfo.time_info.byte_2.field.f_day=buffer[5]&0x1F;
			CanTxInfo.time_info.byte_3.field.f_hour=buffer[6]&0x1F;
			CanTxInfo.time_info.byte_4.field.f_minute=buffer[7]&0x3F;
			CanTxInfo.time_info.byte_5.field.f_second=buffer[8]&0x3F;
			CanTxInfo.time_info.byte_5.field.f_time_mode=(buffer[9]&0xC0)>>6;
			Morris_Garages_PostMessage(CAN_POST_MSG_TIME);
			break;
		default:
			break;
	}
}


void Morris_Garages_MainPro(void)
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
	if(CanNoDataTimer)
	{
		CanNoDataTimer--;
		if(CanNoDataTimer==0)
		{
			F_CAN_RX_DATA=0;
		}
	}
	if(CanTxTimer)
	{
		CanTxTimer--;
	}

#if defined(STM32_F103VC)
	if(CanMainState==CAN_MAIN_NORMAL)
	{
		if(CAN_GetFlagStatus(CAN1,CAN_FLAG_EWG)
			||CAN_GetFlagStatus(CAN1,CAN_FLAG_EWG)
			||CAN_GetFlagStatus(CAN1,CAN_FLAG_BOF)
			||CAN_GetReceiveErrorCounter(CAN1)>=127
			||CAN_GetLSBTransmitErrorCounter(CAN1)>=127)
		{
			CanCheckErrorTimer++;
			if(CanCheckErrorTimer>=T2S_1)
			{
				CanCheckErrorTimer=0;
				CanMainState=CAN_MAIN_IDLE;
			}
		}
		else
		{
			CanCheckErrorTimer=0;
		}
	}
#elif defined(AUTOCHIPS_AC781X)
	if(CanMainState==CAN_MAIN_NORMAL)
	{
		if(CAN1->BIT.RESET)
		{
			CanCheckErrorTimer++;
			if(CanCheckErrorTimer>=T2S_1)
			{
				CanCheckErrorTimer=0;
				CanMainState=CAN_MAIN_IDLE;
			}
		}
		else
		{
			CanCheckErrorTimer=0;
		}
	}
#endif

	Morris_Garages_Rx_Message();
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
			CanTxErrorCounter=0;
			CanNoTxCounter=0;
			CanMainState=CAN_MAIN_INIT;
			break;
		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			F_CAN_SLEEP=0;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T60S_1;
			CanTxTimer=0;
			break;
		case CAN_MAIN_NORMAL:
#if CAN_WAKEUP_FUN==1
			if(F_CAN_RX_DATA==0)
#else
			if(Get_ACC_Det_Flag==0)
#endif
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
				break;
			}
			if(Get_ACC_Det_Flag)
			{
				if(APP_READY==APP_Status)
				{
					if(CanMainTimer==0)
					{
						CanMainTimer=T5S_1;
					}
				}
			}
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

