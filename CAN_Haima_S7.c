#include "public.h"

#if CAN_FUN_HAIMA_S7==1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_TX_INFO CanTxInfo;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
HAIMA_S7_INFO_KEY_DET_STATE InfoKeyState;
u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanCheckErrorTimer;


u16 InfoKeyPressTimer;
u16 InfoKeyReleaseTimer;
u8 InfoKeyLongPressFlag;
u8 InfoKeyTimer;
u8 CanTxTimer;
u8 CanTxErrorCounter;
u8 CanNoTxCounter;
u8 CAN_TURN_STATE;

u32 CanAccOffDetTimer;
u8 F_CanNoWakeUp;

//u8 CAN_ID_GW_counter;
#if TEST_CAN_FUN==1
u32 CanTestTimer;
int test_time;
int test;
#endif



void Haima_S7_PostMessage(CAN_POST_MESSAGE_INDEX index);

const uchar Haima_S7_Message_Mask[3][8]=
{
	0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0xFC,
	0x00,0x00,0x70,0x3B,0xE0,0x06,0x00,0x00,
	0x3C,0x00,0x37,0x00,0x00,0x00,0x00,0x00
};
u8 Haima_S7_CheckTxMessage(u32 id,u8 *data)
{
	u8 *ptr;
	u32 i;
	u8 result=1;
	if(id==CAN_ID_IST_0)
	{
		ptr=(u8 *)&Haima_S7_Message_Mask[0][0];
	}
	else if(id==CAN_ID_IST_1)
	{
		ptr=(u8 *)&Haima_S7_Message_Mask[1][0];
	}
	else if(id==CAN_ID_IST_2)
	{
		ptr=(u8 *)&Haima_S7_Message_Mask[2][0];
	}
	else
	{
		result=0;
	}
	for(i=0;i<8;i++)
	{
		data[i]&=ptr[i];
	}
	return result;
}
void Haima_S7_InfoKeyScan(void)
{
	u32 adc_value;
	u32 port;

	if(CanRxInfo.base_info.byte_2.field.f_power_level==0)
	{
		InfoKeyState=INFO_KEY_IDLE;
		InfoKeyPressTimer=0;
		InfoKeyReleaseTimer=0;
		InfoKeyLongPressFlag=0;
		CanTxInfo.ist_2_info.byte_1.field.f_key_con_for_icm=0;
		return;
	}
	
	adc_value=Get_Adc(ADCH_WHEEL_KEY1);
	if(adc_value>3590
		&&adc_value<3910)
	{
		port=1;
	}
	else
	{
		port=0;
	}
	InfoKeyPressTimer++;
	InfoKeyReleaseTimer++;
	
	switch(InfoKeyState)
	{
		case INFO_KEY_IDLE:
			if(port==0)
			{
				InfoKeyPressTimer=0;
			}
			if(InfoKeyPressTimer>T60MS_10)
			{
				InfoKeyState=INFO_KEY_PRESSED;
				InfoKeyPressTimer=0;
				InfoKeyReleaseTimer=0;
				InfoKeyLongPressFlag=0;
			}
			break;
		case INFO_KEY_PRESSED:
			if(port)
			{
				InfoKeyReleaseTimer=0;
			}
			else
			{
				InfoKeyPressTimer=0;
			}
			
			if(InfoKeyReleaseTimer>SHORT_PRESS_TIME)
			{
				InfoKeyPressTimer=0;
				InfoKeyState=INFO_KEY_IDLE;
				if(InfoKeyLongPressFlag==0)
				{
					CanTxInfo.ist_2_info.byte_1.field.f_key_con_for_icm=1;
					Haima_S7_PostMessage(CAN_POST_MSG_IST_2);
					CanTxInfo.ist_2_info.byte_1.field.f_key_con_for_icm=0;
				}
			}
			else if(InfoKeyLongPressFlag==0)
			{
				if(InfoKeyPressTimer>REPEAT_HOLD_PRESS_TIME)
				{
					InfoKeyLongPressFlag=1;
					CanTxInfo.ist_2_info.byte_1.field.f_key_con_for_icm=2;
					Haima_S7_PostMessage(CAN_POST_MSG_IST_2);
					CanTxInfo.ist_2_info.byte_1.field.f_key_con_for_icm=0;
				}
			}
			break;
		default:
			break;
	}
}

void Haima_S7_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	if(!Get_ACC_Det_Flag)
	{
		return;
	}
	
	u8 data[8];
	
	switch(index)
	{
		case CAN_POST_MSG_IST_0:
			data[0]=CanTxInfo.ist_0_info.reserved_1;
			data[1]=CanTxInfo.ist_0_info.reserved_2;
			data[2]=CanTxInfo.ist_0_info.reserved_3;
			data[3]=CanTxInfo.ist_0_info.reserved_4;
			data[4]=CanTxInfo.ist_0_info.reserved_5;
			data[5]=CanTxInfo.ist_0_info.byte_6.byte;
			data[6]=CanTxInfo.ist_0_info.reserved_7;
			data[7]=CanTxInfo.ist_0_info.byte_8.byte;
			CAN1_TxFrame(CAN_ID_IST_0,data,8);
			break;
		case CAN_POST_MSG_IST_1:
			data[0]=CanTxInfo.ist_1_info.reserved_1;
			data[1]=CanTxInfo.ist_1_info.reserved_2;
			data[2]=CanTxInfo.ist_1_info.byte_3.byte;
			data[3]=CanTxInfo.ist_1_info.byte_4.byte;
			data[4]=CanTxInfo.ist_1_info.byte_5.byte;
			data[5]=CanTxInfo.ist_1_info.byte_6.byte;
			data[6]=CanTxInfo.ist_1_info.reserved_7;
			data[7]=CanTxInfo.ist_1_info.temp;
			CAN1_TxFrame(CAN_ID_IST_1,data,8);
			break;
		case CAN_POST_MSG_IST_2:
			data[0]=CanTxInfo.ist_2_info.byte_1.byte;
			data[1]=CanTxInfo.ist_2_info.reserved_2;
			data[2]=CanTxInfo.ist_2_info.byte_3.byte;
			data[3]=CanTxInfo.ist_2_info.reserved_4;
			CAN1_TxFrame(CAN_ID_IST_2,data,4);
			break;
		case CAN_POST_MSG_DIAG_IST_RESP:
			data[0]=CanTxInfo.diag_ist_resp[0];
			data[1]=CanTxInfo.diag_ist_resp[1];
			data[2]=CanTxInfo.diag_ist_resp[2];
			data[3]=CanTxInfo.diag_ist_resp[3];
			data[4]=CanTxInfo.diag_ist_resp[4];
			data[5]=CanTxInfo.diag_ist_resp[5];
			data[6]=CanTxInfo.diag_ist_resp[6];
			data[7]=CanTxInfo.diag_ist_resp[7];
			CAN1_TxFrame(CAN_ID_DIAG_IST_RESP,data,8);
			break;
		default:
			break;
	}
}

void Haima_S7_Rx_Message(void)
{
	if(F_CanNoWakeUp)
	{
		return;
	}
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;
		u8 temp;
		u16 speed;
		//u8 i;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
/*
			case CAN_ID_SPEED:
				for(i=0;i<8;i++)
			  {
					CanRxData.speed[i]=message.Data[i];
				}
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_SPEED_INFO);
			  break;
			case CAN_ID_THROTTLE:
				for(i=0;i<8;i++)
			  {
					CanRxData.throttle[i]=message.Data[i];
				}
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_THROTTLE_INFO);
			  break;
			case CAN_ID_GEAR:
				for(i=0;i<8;i++)
			  {
					CanRxData.gear[i]=message.Data[i];
				}
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_GEAR_INFO);
			  break;
*/
      case CAN_ID_TEST:
				CAN_TURN_STATE=message.Data[0]&0x03;
				//CAN_TURN_RIGHT=(0x01&message.Data[0]);
			  //CAN_TURN_LEFT=0x01&(message.Data[0]>>1);
				break;
      case CAN_ID_SAS:
				if(message.Data[4]==0 && message.Data[3]==0)
					break;
				CanRxInfo.base_info.byte_7.field.steering_wheel_angle_L=message.Data[3];
			  CanRxInfo.base_info.byte_8.field.steering_wheel_angle_H=message.Data[4];
				//PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_BASIC_INFO);
				break;
			case CAN_ID_GW:
//				CAN_ID_GW_counter++;
				temp=(message.Data[3]&0x0F);
				switch(temp)
				{
					case 0:
						CanRxInfo.base_info.byte_2.field.f_gear=0;
						break;
					case 5:
						CanRxInfo.base_info.byte_2.field.f_gear=1;
						break;
					case 6:
						CanRxInfo.base_info.byte_2.field.f_gear=2;
						break;
					case 7:
						CanRxInfo.base_info.byte_2.field.f_gear=3;
						break;
					case 8:
						CanRxInfo.base_info.byte_2.field.f_gear=4;
						break;
					case 4:
						CanRxInfo.base_info.byte_2.field.f_gear=5;
						break;
					default:
						break;
				}
				if(CanRxInfo.base_info.byte_2.field.f_gear==3)
				{
					CanGeneralCtrlFlag.field.reverse_on_off=1;
				}
				else
				{
					CanGeneralCtrlFlag.field.reverse_on_off=0;
				}
				
				if(CanRxInfo.base_info.byte_2.field.f_gear==1)
				{
					CanGeneralCtrlFlag.field.parking_on_off=0;
				}
				else
				{
					CanGeneralCtrlFlag.field.parking_on_off=1;
				}
				speed=((message.Data[6]&0x1F)<<8)|message.Data[7];
				CanRxInfo.base_info.byte_3.field.speed1=speed>>8;
				CanRxInfo.base_info.byte_4.field.speed2=speed&0xff;
				CanRxInfo.base_info.byte_5.field.current_gear=message.Data[1]&0x0F;
//				if(CAN_ID_GW_counter==2)
				{
//				CAN_ID_GW_counter=0;
//				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_BASIC_INFO);
				}
				break;
			case CAN_ID_BCM:
				CanRxInfo.base_info.byte_1.field.f_front_left_door=(message.Data[1]&0x01);
				CanRxInfo.base_info.byte_1.field.f_fornt_right_door=((message.Data[1]&0x02)>>1);
				CanRxInfo.base_info.byte_1.field.f_rear_left_door=((message.Data[1]&0x04)>>2);
				CanRxInfo.base_info.byte_1.field.f_rear_right_door=((message.Data[1]&0x08)>>3);
				CanRxInfo.base_info.byte_1.field.f_rear_door=((message.Data[1]&0x10)>>4);
				if(!strcmp_equal(&CanRxInfo.base_info.byte_1.byte,&CanRxInfoBak.base_info.byte_1.byte,sizeof(CAN_BASE_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.base_info.byte_1.byte,&CanRxInfo.base_info.byte_1.byte,sizeof(CAN_BASE_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_BASIC_INFO);
				}
				break;
			case CAN_ID_HVAC:
				if(((message.Data[0]&0x02)>>1))
				{
					CanRxInfo.air_info.byte_1.field.f_on_off=0;
				}
				else
				{
					CanRxInfo.air_info.byte_1.field.f_on_off=1;
				}
				CanRxInfo.air_info.byte_1.field.f_circle=(message.Data[2]&0x01);
				if((message.Data[3]&0x20))
				{
					CanRxInfo.air_info.byte_1.field.f_front_defrost=1;
				}
				else
				{
					CanRxInfo.air_info.byte_1.field.f_front_defrost=0;
				}
				CanRxInfo.air_info.byte_1.field.f_rear_defrost=((message.Data[3]&0x40)>>6);
				CanRxInfo.air_info.byte_1.field.f_ac=((message.Data[3]&0x80)>>7);
				CanRxInfo.air_info.byte_1.field.f_auto=((message.Data[3]&0x08)>>3);

				if(message.Data[2]&0x10)
				{
					CanRxInfo.air_info.wind_mode=3;
				}
				else if(message.Data[2]&0x04)
				{
					CanRxInfo.air_info.wind_mode=4;
				}
				else if(message.Data[2]&0x02)
				{
					CanRxInfo.air_info.wind_mode=2;
				}
				else if(message.Data[3]&0x10)
				{
					CanRxInfo.air_info.wind_mode=1;
				}
				else if(message.Data[3]&0x20)
				{
					CanRxInfo.air_info.wind_mode=5;
				}
				else
				{
					CanRxInfo.air_info.wind_mode=0;
				}
				CanRxInfo.air_info.wind_speed=(message.Data[4]&0x1F);
				temp=message.Data[6];
				if(temp<=115)
				{
					CanRxInfo.air_info.temperature=0x00;
				}
				else if(temp>144)
				{
					CanRxInfo.air_info.temperature=0x1E;
				}
				else
				{
					CanRxInfo.air_info.temperature=temp-115;
				}
				CanRxInfo.air_info.out_temperature=message.Data[7];
				if(!strcmp_equal(&CanRxInfo.air_info.byte_1.byte,&CanRxInfoBak.air_info.byte_1.byte,sizeof(CAN_AIR_INFO)))
				{
					if(CanRxInfo.air_info.byte_1.field.f_on_off)
					{
						if(CanRxInfo.air_info.byte_1.field.f_front_defrost)
						{
							AIR_F_WIN_LED_ON;
						}
						else
						{
							AIR_F_WIN_LED_OFF;
						}
						
						if(CanRxInfo.air_info.byte_1.field.f_rear_defrost)
						{
							AIR_R_WIN_LED_ON;
						}
						else
						{
							AIR_R_WIN_LED_OFF;
						}

						if(CanRxInfo.air_info.byte_1.field.f_ac)
						{
							AIR_AC_LED_ON;
						}
						else
						{
							AIR_AC_LED_OFF;
						}

						if(CanRxInfo.air_info.byte_1.field.f_auto)
						{
							AIR_AUTO_LED_ON;
						}
						else
						{
							AIR_AUTO_LED_OFF;
						}
				
						if(CanRxInfo.air_info.byte_1.field.f_circle)
						{
							AIR_CIRCLE_LED_ON;
						}
						else
						{
							AIR_CIRCLE_LED_OFF;
						}
						
						switch(CanRxInfo.air_info.wind_mode)
						{
							case 1:
								AIR_UP_WIND_LED_OFF;
								AIR_PARALLEL_WIND_LED_ON;
								AIR_DOWN_WIND_LED_OFF;
								break;
							case 2:
								AIR_UP_WIND_LED_OFF;
								AIR_PARALLEL_WIND_LED_ON;
								AIR_DOWN_WIND_LED_ON;
								break;
							case 3:
								AIR_UP_WIND_LED_OFF;
								AIR_PARALLEL_WIND_LED_OFF;
								AIR_DOWN_WIND_LED_ON;
								break;
							case 4:
								AIR_UP_WIND_LED_ON;
								AIR_PARALLEL_WIND_LED_OFF;
								AIR_DOWN_WIND_LED_ON;
								break;
							case 5:
								AIR_UP_WIND_LED_ON;
								AIR_PARALLEL_WIND_LED_OFF;
								AIR_DOWN_WIND_LED_OFF;
								break;
							default:
								AIR_UP_WIND_LED_OFF;
								AIR_PARALLEL_WIND_LED_OFF;
								AIR_DOWN_WIND_LED_OFF;
								break;
						}
					}
					else
					{
						AIR_F_WIN_LED_OFF;
						AIR_R_WIN_LED_OFF;
						AIR_AC_LED_OFF;
						AIR_AUTO_LED_OFF;
						AIR_UP_WIND_LED_OFF;
						AIR_PARALLEL_WIND_LED_OFF;
						AIR_DOWN_WIND_LED_OFF;
						if(CanRxInfo.air_info.byte_1.field.f_circle)
						{
							AIR_CIRCLE_LED_ON;
						}
						else
						{
							AIR_CIRCLE_LED_OFF;
						}
					}
					Mem_strcpy(&CanRxInfoBak.air_info.byte_1.byte,&CanRxInfo.air_info.byte_1.byte,sizeof(CAN_AIR_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_AIR_INFO);
				}
				break;
			case CAN_ID_PEPS:
				CanRxInfo.base_info.byte_2.field.f_power_level=message.Data[4]&0x07;
				CanGeneralCtrlFlag.field.power_level=CanRxInfo.base_info.byte_2.field.f_power_level;
				if(CanRxInfo.base_info.byte_2.field.f_power_level)
				{
					CanTxInfo.ist_2_info.byte_1.field.f_acc_vol_ind=1;
				}
				else
				{
					CanTxInfo.ist_2_info.byte_1.field.f_acc_vol_ind=0;
				}
				if(CanRxInfo.base_info.byte_2.field.f_power_level!=CanRxInfoBak.base_info.byte_2.field.f_power_level)
				{
					CanRxInfoBak.base_info.byte_2.field.f_power_level=CanRxInfo.base_info.byte_2.field.f_power_level;
					if(CanRxInfo.base_info.byte_2.field.f_power_level>1)
					{
						AIR_LED_POWER_ON;
					}
					else
					{
						AIR_LED_POWER_OFF;
					}
				}
				break;
			case CAN_ID_SVM:
				CanRxInfo.avm_info.byte_1.field.f_avm_on_off=((message.Data[7]&0x80)>>7);
				CanRxInfo.avm_info.byte_1.field.f_camera_status=(message.Data[7]&0x0F);
				CanRxInfo.avm_info.byte_2.field.f_guide_on_off=((message.Data[6]&0x40)>>6);
				if(!strcmp_equal(&CanRxInfo.avm_info.byte_1.byte,&CanRxInfoBak.avm_info.byte_1.byte,sizeof(CAN_AVM_INFO)))
				{
					if(CanRxInfo.avm_info.byte_1.field.f_avm_on_off!=CanRxInfoBak.avm_info.byte_1.field.f_avm_on_off
						&&CanRxInfo.avm_info.byte_1.field.f_avm_on_off
						&&CanGeneralCtrlFlag.field.reverse_on_off==0)
					{
						PostKeyCode(UICC_CAMERA,0x10);
					}
					Mem_strcpy(&CanRxInfoBak.avm_info.byte_1.byte,&CanRxInfo.avm_info.byte_1.byte,sizeof(CAN_AVM_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_AVM_INFO);
				}
				if(CanRxInfo.avm_info.byte_1.field.f_avm_on_off)
				{
					CanGeneralCtrlFlag.field.camera_on_off=1;
				}
				else
				{
					CanGeneralCtrlFlag.field.camera_on_off=0;
				}
				break;
			case CAN_ID_DIAG_IST_REQ:

					if(message.Data[0]==0x02
						&&message.Data[1]==0x10
						&&message.Data[2]==0x01)
					{
					CanTxInfo.diag_ist_resp[0]=0x02;
						CanTxInfo.diag_ist_resp[1]=0x50;
						CanTxInfo.diag_ist_resp[2]=0x01;
					CanTxInfo.diag_ist_resp[3]=0xFF;
					CanTxInfo.diag_ist_resp[4]=0xFF;
					CanTxInfo.diag_ist_resp[5]=0xFF;
					CanTxInfo.diag_ist_resp[6]=0xFF;
					CanTxInfo.diag_ist_resp[7]=0xFF;
					Haima_S7_PostMessage(CAN_POST_MSG_DIAG_IST_RESP);
					}
					else if(message.Data[0]==0x04
						&&message.Data[1]==0x14
						&&message.Data[2]==0xFF)
					{
					CanTxInfo.diag_ist_resp[0]=0x03;
					CanTxInfo.diag_ist_resp[1]=0x7F;
					CanTxInfo.diag_ist_resp[2]=0x14;
					CanTxInfo.diag_ist_resp[3]=0x78;
					CanTxInfo.diag_ist_resp[4]=0xFF;
					CanTxInfo.diag_ist_resp[5]=0xFF;
					CanTxInfo.diag_ist_resp[6]=0xFF;
					CanTxInfo.diag_ist_resp[7]=0xFF;
					Haima_S7_PostMessage(CAN_POST_MSG_DIAG_IST_RESP);
						CanTxInfo.diag_ist_resp[0]=0x01;
						CanTxInfo.diag_ist_resp[1]=0x54;
					CanTxInfo.diag_ist_resp[2]=0xFF;
					CanTxInfo.diag_ist_resp[3]=0xFF;
					CanTxInfo.diag_ist_resp[4]=0xFF;
					CanTxInfo.diag_ist_resp[5]=0xFF;
					CanTxInfo.diag_ist_resp[6]=0xFF;
					CanTxInfo.diag_ist_resp[7]=0xFF;
					Haima_S7_PostMessage(CAN_POST_MSG_DIAG_IST_RESP);
					}
					else if(message.Data[0]==0x02
						&&message.Data[1]==0x3E
						&&message.Data[2]==0x00)
					{
						CanTxInfo.diag_ist_resp[0]=0x02;
						CanTxInfo.diag_ist_resp[1]=0x7E;
						CanTxInfo.diag_ist_resp[2]=0x00;
					CanTxInfo.diag_ist_resp[3]=0xFF;
					CanTxInfo.diag_ist_resp[4]=0xFF;
					CanTxInfo.diag_ist_resp[5]=0xFF;
					CanTxInfo.diag_ist_resp[6]=0xFF;
					CanTxInfo.diag_ist_resp[7]=0xFF;
					Haima_S7_PostMessage(CAN_POST_MSG_DIAG_IST_RESP);
					}
					else if(message.Data[0]==0x03
						&&message.Data[1]==0x19
						&&message.Data[2]==0x01)
					{
						CanTxInfo.diag_ist_resp[0]=0x06;
						CanTxInfo.diag_ist_resp[1]=0x59;
						CanTxInfo.diag_ist_resp[2]=0x01;
						CanTxInfo.diag_ist_resp[3]=0x3B;
						CanTxInfo.diag_ist_resp[4]=0x00;
						CanTxInfo.diag_ist_resp[5]=0x00;
						CanTxInfo.diag_ist_resp[6]=0x00;
					CanTxInfo.diag_ist_resp[7]=0xFF;
					Haima_S7_PostMessage(CAN_POST_MSG_DIAG_IST_RESP);
					}		
				else if(message.Data[0]==0x03
					&&message.Data[1]==0x19
					&&message.Data[2]==0x02
					&&message.Data[3]==0x09)
					{
					CanTxInfo.diag_ist_resp[0]=0x03;
					CanTxInfo.diag_ist_resp[1]=0x59;
					CanTxInfo.diag_ist_resp[2]=0x02;
					CanTxInfo.diag_ist_resp[3]=0x39;
					CanTxInfo.diag_ist_resp[4]=0xFF;
					CanTxInfo.diag_ist_resp[5]=0xFF;
					CanTxInfo.diag_ist_resp[6]=0xFF;
					CanTxInfo.diag_ist_resp[7]=0xFF;
						Haima_S7_PostMessage(CAN_POST_MSG_DIAG_IST_RESP);
				}
				break;
			default:
				break;
		}
		CanRxInfo.base_info.byte_2.field.f_can_ready=1;
		if(F_CAN_RX_DATA == 0)
		{
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_S7_RX_BASIC_INFO);
		}
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
//		if(Get_ACC_Det_Flag==0)
//		{
//			CanNoDataTimer=T100MS_1;
//		}
//		else
		{
			CanNoDataTimer=T30S_1;
		}
//		if(Get_ACC_Det_Flag==0 && CanAccDetTimer < 0x800)
//		{
//			CanAccDetTimer ++;
//		}
//		else if(Get_ACC_Det_Flag)
//		{
//			CanAccDetTimer = 0;
//		}
		CAN1_ClearErrorTimer();
	}
	else if(!Get_ACC_Det_Flag && CanNoDataTimer>T3S_1)
	{
		CanNoDataTimer=T3S_1;
	}
}

void Haima_S7_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id=buffer[1];

	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	
	switch(cmd_id)
	{
		case HAIMA_S7_TX_REQ_CMD:
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_BASIC_INFO);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_AIR_INFO);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_AVM_INFO);
			break;
		case HAIMA_S7_TX_AIR_CMD:
			switch(buffer[3])
			{
				case AIR_KEY_OFF:
						CanTxInfo.ist_1_info.byte_5.field.f_air_close=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
						CanTxInfo.ist_1_info.byte_5.field.f_air_close=0;
					break;
				case AIR_KEY_WIND_SPEED:
					if(buffer[4]==1)
					{
						CanTxInfo.ist_0_info.byte_8.field.f_add_speed=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_0);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.ist_0_info.byte_8.field.f_dec_speed=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_0);
					}
					else if(buffer[4] >= 0x11 && buffer[4] <= 0x17)
					{
						CanTxInfo.ist_1_info.byte_5.field.wind_speed = buffer[4] & 0x0F;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					CanTxInfo.ist_1_info.byte_5.field.wind_speed = 0;
					CanTxInfo.ist_0_info.byte_8.field.f_add_speed=0;
					CanTxInfo.ist_0_info.byte_8.field.f_dec_speed=0;
					break;
				case AIR_KEY_TEMP:
					if(buffer[4]==1)
					{
						CanTxInfo.ist_0_info.byte_6.field.f_add_temp=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_0);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.ist_0_info.byte_6.field.f_dec_temp=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_0);
					}
					else if(buffer[4] >= 0x72 && buffer[4] <= 0x90)
					{
						CanTxInfo.ist_1_info.temp = buffer[4];
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					CanTxInfo.ist_0_info.byte_6.field.f_add_temp=0;
					CanTxInfo.ist_0_info.byte_6.field.f_dec_temp=0;
					CanTxInfo.ist_1_info.temp = 0xA0;
					break;
				case AIR_KEY_WIND_MODE_1:
					if(buffer[4])
					{
						CanTxInfo.ist_0_info.byte_8.field.f_wind_mode=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_0);
						CanTxInfo.ist_0_info.byte_8.field.f_wind_mode=0;
					}
					break;
				case AIR_KEY_AC:
					if(buffer[4]==1)
					{
						CanTxInfo.ist_1_info.byte_6.field.f_ac=2;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.ist_1_info.byte_6.field.f_ac=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					CanTxInfo.ist_1_info.byte_6.field.f_ac=0;
					break;
				case AIR_KEY_CIRCLE:
					if(buffer[4]==1)
					{
						CanTxInfo.ist_1_info.byte_4.field.f_circle=2;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.ist_1_info.byte_4.field.f_circle=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					CanTxInfo.ist_1_info.byte_4.field.f_circle=0;
					break;
				case AIR_KEY_REAR_DEFROST:
					if(buffer[4]==1)
					{
						CanTxInfo.ist_1_info.byte_4.field.f_rear_defrost=2;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.ist_1_info.byte_4.field.f_rear_defrost=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					CanTxInfo.ist_1_info.byte_4.field.f_rear_defrost=0;
					break;
				case AIR_KEY_FRONT_DEFROST:
					if(buffer[4]==1)
					{
						CanTxInfo.ist_1_info.byte_5.field.f_front_defrost=2;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.ist_1_info.byte_5.field.f_front_defrost=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					}
					CanTxInfo.ist_1_info.byte_5.field.f_front_defrost=0;
					break;
				case AIR_KEY_WIND_MODE_2:
					if(buffer[4]>0
						&&buffer[4]<5)
					{
						CanTxInfo.ist_1_info.byte_3.field.f_wind_mode=buffer[4];
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
						CanTxInfo.ist_1_info.byte_3.field.f_wind_mode=0;
					}
					break;
				case AIR_KEY_AUTO:
					if(buffer[4])
					{
						CanTxInfo.ist_1_info.byte_4.field.f_auto=1;
						Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
						CanTxInfo.ist_1_info.byte_4.field.f_auto=0;
					}
					break;
				default:
					break;
			}
			break;
		case HAIMA_S7_TX_AVM_CMD:
			if(buffer[3]>0
				&&buffer[3]<7)
			{
				if((buffer[3]==0x01&&CanRxInfo.avm_info.byte_1.field.f_avm_on_off==1)
					||(buffer[3]==0x02&&CanRxInfo.avm_info.byte_1.field.f_avm_on_off==0))
				{
					break;
				}
				CanTxInfo.ist_2_info.byte_3.field.f_touch_key=buffer[3];
				Haima_S7_PostMessage(CAN_POST_MSG_IST_2);
				CanTxInfo.ist_2_info.byte_3.field.f_touch_key=0;
			}
			else if(buffer[3]==7)
			{
				CanTxInfo.ist_2_info.byte_3.field.f_avm_guide_set=2;
				Haima_S7_PostMessage(CAN_POST_MSG_IST_2);
				CanTxInfo.ist_2_info.byte_3.field.f_avm_guide_set=0;
			}
			else if(buffer[3]==8)
			{
				CanTxInfo.ist_2_info.byte_3.field.f_avm_guide_set=1;
				Haima_S7_PostMessage(CAN_POST_MSG_IST_2);
				CanTxInfo.ist_2_info.byte_3.field.f_avm_guide_set=0;
			}
			break;
		default:
			break;
	}
}

void Haima_S7_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
/*
		case HAIMA_S7_RX_SPEED_INFO:
			buffer[2]=0x08;
		  for(i=0;i<8;i++)
		  {
				buffer[3+i]=CanRxData.speed[i];
			}
		  break;
		case HAIMA_S7_RX_THROTTLE_INFO:
			buffer[2]=0x08;
		  for(i=0;i<8;i++)
		  {
				buffer[3+i]=CanRxData.throttle[i];
			}
		  break;
		case HAIMA_S7_RX_GEAR_INFO:
			buffer[2]=0x08;
		  for(i=0;i<8;i++)
		  {
				buffer[3+i]=CanRxData.gear[i];
			}
		  break;*/
		case HAIMA_S7_RX_AIR_INFO:
			buffer[2]=0x06;
			buffer[3]=CanRxInfo.air_info.byte_1.byte;
			buffer[4]=CanRxInfo.air_info.wind_mode;
			buffer[5]=CanRxInfo.air_info.wind_speed;
			buffer[6]=CanRxInfo.air_info.reserved_3;
			buffer[7]=CanRxInfo.air_info.temperature;
			buffer[8]=CanRxInfo.air_info.out_temperature;
			break;		   
		case HAIMA_S7_RX_BASIC_INFO:
			buffer[2]=0x08;
			buffer[3]=CanRxInfo.base_info.byte_1.byte;
			buffer[4]=CanRxInfo.base_info.byte_2.byte;
			buffer[5]=CanRxInfo.base_info.byte_3.byte;
			buffer[6]=CanRxInfo.base_info.byte_4.byte;
		  buffer[7]=CanRxInfo.base_info.byte_5.byte;
			buffer[8]=CanRxInfo.base_info.byte_6.byte;
		  buffer[9]=CanRxInfo.base_info.byte_7.byte;
			buffer[10]=CanRxInfo.base_info.byte_8.byte;
			break;
		case HAIMA_S7_RX_AVM_INFO:
			buffer[2]=0x02;
			buffer[3]=CanRxInfo.avm_info.byte_1.byte;
			buffer[4]=CanRxInfo.avm_info.byte_2.byte;
			break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=HAIMA_S7_HEAD_CODE;
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

void Haima_S7_CanReset(void)
{
	CanMainState=CAN_MAIN_IDLE;
}

void Haima_S7_Timeout_Handler(void)
{
	F_CAN_RX_DATA = 0;
	CanRxInfo.base_info.byte_2.field.f_can_ready = 0;
	CanRxInfo.base_info.byte_2.field.f_power_level = 0; 
	FormatMemery(&CanRxInfoBak.air_info.byte_1.byte,sizeof(CanRxInfoBak));
	PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_S7_RX_BASIC_INFO);
	AIR_LED_POWER_OFF;
	CanGeneralCtrlFlag.field.power_level = 0;
}

void Haima_S7_MainPro(void)
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}

	if(CanNoDataTimer)
	{
		CanNoDataTimer--;
		printf("%d\n\r", CanNoDataTimer);
		if(CanNoDataTimer==0)
		{
			Haima_S7_Timeout_Handler();
		}
	}
	if(CanTxTimer)
	{
		CanTxTimer--;
	}
#if 1
	if(CanErrorTimer)
	{
		if(AppUpdating)
		{
			CanErrorTimer++;
		}
		CanErrorTimer--;
		if(CanErrorTimer==0
			&&CAN1_GetErrorFlag()==0)
		{
			CAN1_SetErrorFlag();
			CAN_IC_POWER_OFF;
			SystemReset();
		}
	}
#endif
#if defined(STM32_F103VC)
	if(CanMainState==CAN_MAIN_NORMAL && Get_ACC_Det_Flag)
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
				if(F_CAN_RX_DATA == 1)
					Haima_S7_Timeout_Handler();
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

	Haima_S7_Rx_Message();
	if(F_CAN_INIT)
	{
		CAN1_Transmit();
	}

	switch(CanMainState)
	{
		case CAN_MAIN_IDLE:
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_IDLE\r\n");
#endif
			break;
		case CAN_MAIN_CFG:
			CAN1_Init();
			CanTxErrorCounter=0;
			CanNoTxCounter=0;
			CanMainState=CAN_MAIN_INIT;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_CFG\r\n");
#endif
			break;
		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			FormatMemery(&CanRxInfoBak.air_info.byte_1.byte,sizeof(CanRxInfoBak));
			F_CAN_SLEEP=1;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			CanAccOffDetTimer = 0;
			F_CanNoWakeUp=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T60S_1;
			CanTxTimer=0;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_INIT\r\n");
#endif
			break;
		case CAN_MAIN_NORMAL:
#if CAN_WAKEUP_FUN==1
			if(!Get_ACC_Det_Flag)
			{
				CanAccOffDetTimer ++;
				if(CanAccOffDetTimer == T300S_1)
				{
					F_CAN_RX_DATA = 0;
					F_CanNoWakeUp = 1;
				}
			}
			else
			{
				CanAccOffDetTimer = 0;
			}
			if(F_CAN_RX_DATA==0 && !Get_ACC_Det_Flag)
#else
			if(Get_ACC_Det_Flag==0)
#endif
			{
#if TEST_CAN_FUN==1

				//CanMainState=CAN_MAIN_SLEEP_CFG;
#else
				CanMainState=CAN_MAIN_SLEEP_CFG;
#endif
				break;
			}
			if(Get_ACC_Det_Flag)
			{
				if(APP_READY==APP_Status)
				{
					if(CanMainTimer==0)
					{
						CanMainTimer=T5S_1;
//							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_AVM_INFO);
//							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_BASIC_INFO);
//							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S7_RX_AIR_INFO);
					}
				}
				if(CanTxTimer==0)
				{
					CanTxTimer=T100MS_1;
					Haima_S7_PostMessage(CAN_POST_MSG_IST_0);
					Haima_S7_PostMessage(CAN_POST_MSG_IST_1);
					Haima_S7_PostMessage(CAN_POST_MSG_IST_2);
				}
				InfoKeyTimer++;
				if(InfoKeyTimer>T10MS_1)
				{
					InfoKeyTimer=0;
					Haima_S7_InfoKeyScan();
				}
			}
#if TEST_CAN_FUN==1
			if(CanTestTimer==0)
			{
					CanTestTimer=T8S_1;
					
				
			}	
			if(CanTestTimer)
			{
				CanTestTimer--;
				if(CanTestTimer==0)
				{
					if(test!=7)
					{
						test++;
					}
					else test =1;
					CanTestTimer=T8S_1;
				}
			}
			if(test_time)
			{
				test_time--;
				if(test_time==0)
				{
					u8 data[8]={0};

					data[3]=test;
					CAN1_TxFrame(CAN_ID_GW,data,8);
					test_time=T100MS_1;
					
				}
			}			
			if(test_time==0)
			{
					test_time=T100MS_1;
					
				
			}
#endif		
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_NORMAL\r\n");
#endif
			break;
		case CAN_MAIN_SLEEP_CFG:
			CAN1_ClearRxMessage();
			CAN_IC_STANDBY_ON;
			F_CAN_SLEEP=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_SLEEP;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_SLEEP_CFG\r\n");
#endif
			break;
		case CAN_MAIN_SLEEP:
#if CAN_WAKEUP_FUN==1
			if((F_CAN_SLEEP==0 || F_CAN_INTERRUPT) || (F_CanNoWakeUp && Get_ACC_Det_Flag))
#else
			if(Get_ACC_Det_Flag)
#endif
			{
				CAN_IC_STANDBY_OFF;
				F_CAN_SLEEP=0;
				CanMainState=CAN_MAIN_INIT;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_SLEEP1\r\n");
#endif
			}
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_SLEEP2\r\n");
#endif
			break;
		default:
			break;
	}
}


#endif

