#include "public.h"

#if CAN_FUN_ZHIZI_NE3==1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_TX_INFO CanTxInfo;
u32 CanMainTimer;
u32 CanTxTimer1;
u32 CanTxTimer2;
u32 CanTxTimer3;
u32 CanNoDataTimer;
u32 CanCheckErrorTimer;
u32 CAN_RX_AVM_Timer;
u16 CanTxTimer;
u8 CanTxErrorCounter;
u8 CanNoTxCounter;
u8 OverTimerFlag=0;
CAN_KEY_INFO ZhiZi_NE3_CanKeyInfo;
u8 Control_MMI_Flag;
u8 Reverse_Display_Flag=0;
u16 CanReverseNoDataTimer;

const u8 ZhiZi_NE3_PanelKeyTab[14][4]=
{
	{0,					NO_KEY,							NO_KEY,							0},
	{1,					UICC_VOLUME_DOWN,		UICC_VOLUME_DOWN,		3},
	{2,					UICC_SKIPF,					NO_KEY,							1},
	{3,					UICC_SOURCE,				NO_KEY,			    		1},	
	{4,					NO_KEY,							NO_KEY,							0},
	{5,					UICC_OPEN_SOUND,		NO_KEY,							5},
	{6,					UICC_BT_ACPTCALL,		UICC_BT_HUNGUPCALL,	1},
	{7,					UICC_VOLUME_UP,			UICC_VOLUME_UP,			3},
	{8,					UICC_SKIPB,					NO_KEY,							1},
	{9,					UICC_LEFT,					NO_KEY,							0},
	{10,				UICC_RIGHT,					NO_KEY,							0},
	{11,				UICC_MUTE,					NO_KEY,							0},
	{12,				UICC_MENU,					NO_KEY,							0},
	{13,				UICC_BACK,					NO_KEY,							0},
};

void ZhiZi_NE3_CanKeyTimer(void)
{
	if(ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime>0)
	{
		ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime--;
		if(ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime==0)
		{
			if(1==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
				ZhiZi_NE3_CanKeyInfo.F_HoldPress=1;
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.LongKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
			}
			else if(2==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
					ZhiZi_NE3_CanKeyInfo.F_HoldPress=1;
					ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime=CAN_REPEAT_KEY_TIME;					
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.LongKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
			}
			else if(3==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
				ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime=CAN_REPEAT_KEY_TIME;
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
			}
			else if(6==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
				ZhiZi_NE3_CanKeyInfo.F_HoldPress=1;
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.LongKeyCode,0x40|ZhiZi_NE3_CanKeyInfo.key_source);
			}
			else if(7==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
				ZhiZi_NE3_CanKeyInfo.F_HoldPress=1;
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,0xC0|ZhiZi_NE3_CanKeyInfo.key_source);
			}   
		}
	}
}

void ZhiZi_NE3_KeyScan(void)
{
	if(ZhiZi_NE3_CanKeyInfo.KeyStatus==1)
	{
		if(ZhiZi_NE3_CanKeyInfo.CanKeyCode!=ZhiZi_NE3_CanKeyInfo.bkCanKeyCode)
		{
			ZhiZi_NE3_CanKeyInfo.bkCanKeyCode=ZhiZi_NE3_CanKeyInfo.CanKeyCode;		  
			ZhiZi_NE3_CanKeyInfo.bkLongKeyCode=ZhiZi_NE3_CanKeyInfo.LongKeyCode;
			ZhiZi_NE3_CanKeyInfo.bkShortKeyCode=ZhiZi_NE3_CanKeyInfo.ShortKeyCode;
			ZhiZi_NE3_CanKeyInfo.bkKeyProperty=ZhiZi_NE3_CanKeyInfo.KeyProperty;
			if(ZhiZi_NE3_CanKeyInfo.KeyProperty==0)
			{
				ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime=0;
				ZhiZi_NE3_CanKeyInfo.F_HoldPress=0;
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
			}
			else if(ZhiZi_NE3_CanKeyInfo.KeyProperty==3)
			{
				ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime=CAN_LONG_KEY_TIME;
				ZhiZi_NE3_CanKeyInfo.F_HoldPress=0;
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
			}
			else if(ZhiZi_NE3_CanKeyInfo.KeyProperty==5)
			{
				ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime=0;
				ZhiZi_NE3_CanKeyInfo.F_HoldPress=0;
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,0x40|ZhiZi_NE3_CanKeyInfo.key_source);				
			}
			else if(ZhiZi_NE3_CanKeyInfo.KeyProperty==7)
			{
				ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime=CAN_LONG_KEY_TIME;
				ZhiZi_NE3_CanKeyInfo.F_HoldPress=0;
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,0x40|ZhiZi_NE3_CanKeyInfo.key_source);	
			}
			else if(ZhiZi_NE3_CanKeyInfo.KeyProperty==1
				||ZhiZi_NE3_CanKeyInfo.KeyProperty==2
				||ZhiZi_NE3_CanKeyInfo.KeyProperty==6)
			{
				ZhiZi_NE3_CanKeyInfo.ShortPressHoldTime=CAN_LONG_KEY_TIME;
				ZhiZi_NE3_CanKeyInfo.F_HoldPress=0;			
			}
		}
	}
	else if(ZhiZi_NE3_CanKeyInfo.KeyStatus==0)
	{
		if(ZhiZi_NE3_CanKeyInfo.CanKeyCode!=0)
		{
			if(1==ZhiZi_NE3_CanKeyInfo.KeyProperty
				||2==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
				if(0==ZhiZi_NE3_CanKeyInfo.F_HoldPress)
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
				}
			}
			else if(5==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
			}
			else if(6==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
				if(ZhiZi_NE3_CanKeyInfo.F_HoldPress)
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.LongKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
				}
				else
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
				}
			}
			else if(7==ZhiZi_NE3_CanKeyInfo.KeyProperty)
			{
				if(ZhiZi_NE3_CanKeyInfo.F_HoldPress)
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,0x80|ZhiZi_NE3_CanKeyInfo.key_source);
				}
				else
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.ShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
				}
			}			
		}
		else
		{
			if(1==ZhiZi_NE3_CanKeyInfo.bkKeyProperty
				||2==ZhiZi_NE3_CanKeyInfo.bkKeyProperty)
			{
				if(0==ZhiZi_NE3_CanKeyInfo.F_HoldPress)
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.bkShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
				}
			}
			else if(5==ZhiZi_NE3_CanKeyInfo.bkKeyProperty)
			{
				PostKeyCode(ZhiZi_NE3_CanKeyInfo.bkShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
			}
			else if(6==ZhiZi_NE3_CanKeyInfo.bkKeyProperty)
			{
				if(ZhiZi_NE3_CanKeyInfo.F_HoldPress)
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.bkLongKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
				}
				else
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.bkShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
				}
			}
			else if(7==ZhiZi_NE3_CanKeyInfo.bkKeyProperty)
			{
				if(ZhiZi_NE3_CanKeyInfo.F_HoldPress)
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.bkShortKeyCode,0x80|ZhiZi_NE3_CanKeyInfo.key_source);
				}
				else
				{
					PostKeyCode(ZhiZi_NE3_CanKeyInfo.bkShortKeyCode,ZhiZi_NE3_CanKeyInfo.key_source);
				}
			}
		}
		FormatMemery((u8 *)&ZhiZi_NE3_CanKeyInfo,sizeof(ZhiZi_NE3_CanKeyInfo));					  
	}
}

void ZhiZi_NE3_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8]={0};
	switch(index)
	{
		case CAN_POST_MSG_IVI_ST:
			data[0]=CanTxInfo.screen_info.byte_0.byte;
			data[1]=CanTxInfo.screen_info.byte_1.byte;
			data[2]=0;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_Ext_TxFrame(CAN_ID_IVI_STATUS,data,8);
			break;
		case CAN_POST_MSG_IVI_POS:
			data[0]=LSB(CanTxInfo.ivi_st.x_position);
			data[1]=MSB(CanTxInfo.ivi_st.x_position);
			data[2]=LSB(CanTxInfo.ivi_st.y_position);
			data[3]=MSB(CanTxInfo.ivi_st.y_position);
			data[4]=CanTxInfo.ivi_st.byte_4.byte;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_Ext_TxFrame(CAN_ID_IVI_POS,data,8);
			break;
		case CAN_POST_MSG_IVI_DSW:
			data[0]=CanTxInfo.setting_cmd.byte_0.byte;
			data[1]=CanTxInfo.setting_cmd.byte_1.byte;
			data[2]=0;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_Ext_TxFrame(CAN_ID_DSW,data,8);
			break;
		case CAN_POST_MSG_IVI_SOFT:
			data[0]=CanTxInfo.soft_version.soft_ver_byte0;
			data[1]=CanTxInfo.soft_version.soft_ver_byte1;
			data[2]=CanTxInfo.soft_version.soft_ver_byte2;
			data[3]=CanTxInfo.soft_version.soft_ver_byte3;
			data[4]=CanTxInfo.soft_version.soft_ver_byte4;
			data[5]=CanTxInfo.soft_version.soft_ver_byte5;
			data[6]=CanTxInfo.soft_version.soft_ver_byte6;
			data[7]=CanTxInfo.soft_version.soft_ver_byte7;
			CAN1_Ext_TxFrame(CAN_ID_IVI_SOFT,data,8);
			break;
		case CAN_POST_MSG_IVI_HARD:
			data[0]=CanTxInfo.hard_version.hard_ver_byte0;
			data[1]=CanTxInfo.hard_version.hard_ver_byte1;
			data[2]=CanTxInfo.hard_version.hard_ver_byte2;
			data[3]=CanTxInfo.hard_version.hard_ver_byte3;
			data[4]=CanTxInfo.hard_version.hard_ver_byte4;
			data[5]=CanTxInfo.hard_version.hard_ver_byte5;
			data[6]=CanTxInfo.hard_version.hard_ver_byte6;
			data[7]=CanTxInfo.hard_version.hard_ver_byte7;
			CAN1_Ext_TxFrame(CAN_ID_IVI_HARD,data,8);
			break;
		case CAN_POST_MSG_IVI_SoftPartNum:
			data[0]=CanTxInfo.softpartnum_version.softpartnum_ver_byte0;
			data[1]=CanTxInfo.softpartnum_version.softpartnum_ver_byte1;
			data[2]=CanTxInfo.softpartnum_version.softpartnum_ver_byte2;
			data[3]=CanTxInfo.softpartnum_version.softpartnum_ver_byte3;
			data[4]=CanTxInfo.softpartnum_version.softpartnum_ver_byte4;
			data[5]=CanTxInfo.softpartnum_version.softpartnum_ver_byte5;
			data[6]=CanTxInfo.softpartnum_version.softpartnum_ver_byte6;
			data[7]=CanTxInfo.softpartnum_version.softpartnum_ver_byte7;
			CAN1_Ext_TxFrame(CAN_ID_IVI_SOFTPARTNUM,data,8);
			break;
		case CAN_POST_MSG_IVI_TimeSet:
			data[0]=CanTxInfo.time_set.time_set_byte0;
			data[1]=CanTxInfo.time_set.time_set_byte1;
			data[2]=CanTxInfo.time_set.time_set_byte2;
			data[3]=CanTxInfo.time_set.time_set_byte3;
			data[4]=CanTxInfo.time_set.time_set_byte4;
			data[5]=CanTxInfo.time_set.time_set_byte5;
			data[6]=CanTxInfo.time_set.time_set_byte6;
			data[7]=0;
			CAN1_Ext_TxFrame(CAN_ID_IVI_TIMESET,data,8);
			break;
		default:
			break;
	}
}

void ZhiZi_NE3_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_CGW_VEHINFO1:
				CanReverseNoDataTimer=T500MS_1;
				CanRxInfo.base_info.vehicle_speed=message.Data[0];
				CanRxInfo.base_info.vehicle_speed<<=8;
				CanRxInfo.base_info.vehicle_speed|=message.Data[1];
				if(Reverse_Display_Flag==1)
				{
					if(message.Data[2]==0xDF)
					{
						CanGeneralCtrlFlag.field.reverse_on_off=1;
					}
					else
					{
						CanGeneralCtrlFlag.field.reverse_on_off=0;
					}
				}
				switch(message.Data[2])
				{
					case 0x7D:
						CanRxInfo.veh_setting_info.vehicle_gears=0x00;
						break;
					case 0xDF:
						CanRxInfo.veh_setting_info.vehicle_gears=0x01;
						break;
					case 0x7E:
						CanRxInfo.veh_setting_info.vehicle_gears=0x02;
						break;
					case 0x7F:
						CanRxInfo.veh_setting_info.vehicle_gears=0x03;
						break;
					case 0x80:
						CanRxInfo.veh_setting_info.vehicle_gears=0x04;
						break;
					case 0x81:
						CanRxInfo.veh_setting_info.vehicle_gears=0x05;
						break;
					case 0x82:
						CanRxInfo.veh_setting_info.vehicle_gears=0x06;
						break;
					case 0x83:
						CanRxInfo.veh_setting_info.vehicle_gears=0x07;
						break;
					case 0xFA:
						CanRxInfo.veh_setting_info.vehicle_gears=0x08;
						break;
					case 0xFC:
						CanRxInfo.veh_setting_info.vehicle_gears=0x09;
						break;
					case 0xFE:
						CanRxInfo.veh_setting_info.vehicle_gears=0x0A;
						break;
					case 0xFF:
						CanRxInfo.veh_setting_info.vehicle_gears=0x0B;
						break;
					default:
						break;
				}
				if(!strcmp_equal(&CanRxInfo.veh_setting_info.byte_0.byte,&CanRxInfoBak.veh_setting_info.byte_0.byte,sizeof(CAN_VEH_SETTING_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.veh_setting_info.byte_0.byte,&CanRxInfo.veh_setting_info.byte_0.byte,sizeof(CAN_VEH_SETTING_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_SETTING_CMD);
				}
				break;
			case CAN_ID_EVT_TD:
				CanRxInfo.time_info.second=message.Data[0];
				CanRxInfo.time_info.minutes=message.Data[1];
				CanRxInfo.time_info.hours=message.Data[2];
				CanRxInfo.time_info.day=message.Data[4];
				CanRxInfo.time_info.month=message.Data[3];
				CanRxInfo.time_info.year=message.Data[5];
				CanRxInfo.time_info.minute_offset=message.Data[6];
				CanRxInfo.time_info.hour_offset=message.Data[7];
				break;
			case CAN_ID_BPDU_OUTCTRLST:
				CanRxInfo.veh_setting_info.byte_1.field.f_position_light_st=(message.Data[0]&0x03);
				CanRxInfo.veh_setting_info.byte_1.field.f_low_beam_st=(message.Data[1]&0x03);
				if(!strcmp_equal(&CanRxInfo.veh_setting_info.byte_0.byte,&CanRxInfoBak.veh_setting_info.byte_0.byte,sizeof(CAN_VEH_SETTING_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.veh_setting_info.byte_0.byte,&CanRxInfo.veh_setting_info.byte_0.byte,sizeof(CAN_VEH_SETTING_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_SETTING_CMD);
				}
				break;
			case CAN_ID_BPDU_VEHPWRSTS:
				CanRxInfo.veh_setting_info.byte_1.field.f_Ignition_gear_position=(message.Data[0]&0x07);
				if(!strcmp_equal(&CanRxInfo.veh_setting_info.byte_0.byte,&CanRxInfoBak.veh_setting_info.byte_0.byte,sizeof(CAN_VEH_SETTING_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.veh_setting_info.byte_0.byte,&CanRxInfo.veh_setting_info.byte_0.byte,sizeof(CAN_VEH_SETTING_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_SETTING_CMD);
				}
				break;
			case CAN_ID_BPDU_MFLCTRL:
				{
					u8 key_code=0;
					u8 key_status=0;
					u8 temp=0;
					if((message.Data[0]&0xC0)==0)
					{
						Control_MMI_Flag=0;
					}
					else
					{
						Control_MMI_Flag=1;
					}
					if(Control_MMI_Flag)
					{
						if(message.Data[0]&0x01)
						{
							temp++;
							key_code=1;
						}					
						if(message.Data[0]&0x04)
						{
							temp++;
							key_code=2;
						}
						if(message.Data[0]&0x10)
						{
							temp++;
							key_code=3;
						}
						if(message.Data[1]&0x40)
						{
							temp++;
							key_code=5;
						}
						if(message.Data[2]&0x01)
						{
							temp++;
							key_code=6;
						}
						if(message.Data[3]&0x40)
						{
							temp++;
							key_code=7;
						}
						if(message.Data[4]&0x01)
						{
							temp++;
							key_code=8;
						}
						if(message.Data[5]&0x10)
						{
							temp++;
							key_code=9;
						}
						if(message.Data[5]&0x40)
						{
							temp++;
							key_code=10;
						}
						if(message.Data[6]&0x01)
						{
							temp++;
							key_code=11;
						}
						if(message.Data[6]&0x04)
						{
							temp++;
							key_code=12;
						}
						if(message.Data[6]&0x10)
						{
							temp++;
							key_code=13;
						}
						
						if(key_code)
						{
							key_status=1;
						}
						
						
						if(temp>1)
						{
							break;
						}

						ZhiZi_NE3_CanKeyInfo.CanKeyCode=key_code;
						ZhiZi_NE3_CanKeyInfo.KeyStatus=key_status;	
						ZhiZi_NE3_CanKeyInfo.ShortKeyCode=ZhiZi_NE3_PanelKeyTab[ZhiZi_NE3_CanKeyInfo.CanKeyCode][1];
						ZhiZi_NE3_CanKeyInfo.LongKeyCode=ZhiZi_NE3_PanelKeyTab[ZhiZi_NE3_CanKeyInfo.CanKeyCode][2];	
						ZhiZi_NE3_CanKeyInfo.KeyProperty=ZhiZi_NE3_PanelKeyTab[ZhiZi_NE3_CanKeyInfo.CanKeyCode][3]; 
						ZhiZi_NE3_CanKeyInfo.key_source=STEER;
						ZhiZi_NE3_KeyScan();  						
					}
				}
				break;
			case CAN_ID_CGW_ADAS_INFO:
				CanRxInfo.veh_setting_info.byte_0.field.f_aeb_st=(message.Data[0]&0x0F);
				CanRxInfo.veh_setting_info.byte_0.field.f_ldw_st=((message.Data[0]&0xF0)>>4);
				if(!strcmp_equal(&CanRxInfo.veh_setting_info.byte_0.byte,&CanRxInfoBak.veh_setting_info.byte_0.byte,sizeof(CAN_VEH_SETTING_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.veh_setting_info.byte_0.byte,&CanRxInfo.veh_setting_info.byte_0.byte,sizeof(CAN_VEH_SETTING_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_SETTING_CMD);
				}
				break;
			case CAN_ID_AVM_REQ:
				if(Reverse_Display_Flag==2)
				{
					CAN_RX_AVM_Timer=T1S_1;
					CanRxInfo.avm_request=message.Data[0];
					if(!strcmp_equal(&CanRxInfo.avm_request,&CanRxInfoBak.avm_request,sizeof(CanRxInfo.avm_request)))
						{
							Mem_strcpy(&CanRxInfoBak.avm_request,&CanRxInfo.avm_request,sizeof(CanRxInfo.avm_request));
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_AVM_REQ);
						}
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

void ZhiZi_NE3_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id=buffer[1];
	
	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	
	switch(cmd_id)
	{
		case ZHIZI_NE3_TX_IVI_ST:
			CanTxInfo.screen_info.byte_0.field.f_display_mode=buffer[3];
			CanTxInfo.screen_info.byte_1.field.f_avm_req=buffer[4];
			ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_ST);
			break;
		case ZHIZI_NE3_TX_IVI_POS:
			CanTxInfo.ivi_st.x_position=buffer[3];
			CanTxInfo.ivi_st.x_position<<=8;
			CanTxInfo.ivi_st.x_position|=buffer[4];
			CanTxInfo.ivi_st.y_position=buffer[5];
			CanTxInfo.ivi_st.y_position<<=8;
			CanTxInfo.ivi_st.y_position|=buffer[6];
			CanTxInfo.ivi_st.byte_4.field.f_touch_st=buffer[7];
			ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_POS);
			break;
		case ZHIZI_NE3_TX_SETTING:
			CanTxInfo.setting_cmd.byte_0.field.f_aeb_fun=buffer[3];
			CanTxInfo.setting_cmd.byte_1.field.f_ldw_fun=buffer[4];
			CanTxInfo.setting_cmd.byte_1.field.f_bsd_sw=buffer[5];
			ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_DSW);
			break;
		case ZHIZI_NE3_TX_SOFT_VER:
			CanTxInfo.soft_version.soft_ver_byte0=buffer[3];
			CanTxInfo.soft_version.soft_ver_byte1=buffer[4];
			CanTxInfo.soft_version.soft_ver_byte2=buffer[5];
			CanTxInfo.soft_version.soft_ver_byte3=buffer[6];
			CanTxInfo.soft_version.soft_ver_byte4=buffer[7];
			CanTxInfo.soft_version.soft_ver_byte5=buffer[8];
			CanTxInfo.soft_version.soft_ver_byte6=buffer[9];
			CanTxInfo.soft_version.soft_ver_byte7=buffer[10];
			ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_SOFT);
			break;
		case ZHIZI_NE3_TX_HARD_VER:
			CanTxInfo.hard_version.hard_ver_byte0=buffer[3];
			CanTxInfo.hard_version.hard_ver_byte1=buffer[4];
			CanTxInfo.hard_version.hard_ver_byte2=buffer[5];
			CanTxInfo.hard_version.hard_ver_byte3=buffer[6];
			CanTxInfo.hard_version.hard_ver_byte4=buffer[7];
			CanTxInfo.hard_version.hard_ver_byte5=buffer[8];
			CanTxInfo.hard_version.hard_ver_byte6=buffer[9];
			CanTxInfo.hard_version.hard_ver_byte7=buffer[10];
			ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_HARD);
			break;
		case ZHIZI_NE3_TX_HIDE_SETTING:
			Reverse_Display_Flag=buffer[3];
			EEPROM_Save_ReverseFunSet();
			CanTxInfo.screen_info.byte_0.field.f_display_mode=0;
			break;
		case ZHIZI_NE3_TX_SOFT_PART_NUM_VER:
			CanTxInfo.softpartnum_version.softpartnum_ver_byte0=buffer[3];
			CanTxInfo.softpartnum_version.softpartnum_ver_byte1=buffer[4];
			CanTxInfo.softpartnum_version.softpartnum_ver_byte2=buffer[5];
			CanTxInfo.softpartnum_version.softpartnum_ver_byte3=buffer[6];
			CanTxInfo.softpartnum_version.softpartnum_ver_byte4=buffer[7];
			CanTxInfo.softpartnum_version.softpartnum_ver_byte5=buffer[8];
			CanTxInfo.softpartnum_version.softpartnum_ver_byte6=buffer[9];
			CanTxInfo.softpartnum_version.softpartnum_ver_byte7=buffer[10];
			ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_SoftPartNum);
			break;
		case ZHIZI_NE3_TX_IVI_TIME_SET:
			CanTxInfo.time_set.time_set_byte0=buffer[3];
			CanTxInfo.time_set.time_set_byte1=buffer[4];
			CanTxInfo.time_set.time_set_byte2=buffer[5];
			CanTxInfo.time_set.time_set_byte3=buffer[6];
			CanTxInfo.time_set.time_set_byte4=buffer[7];
			CanTxInfo.time_set.time_set_byte5=buffer[8];
			CanTxInfo.time_set.time_set_byte6=buffer[9];
			ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_TimeSet);
			break;
		default:
			break;
	}
}

void ZhiZi_NE3_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case ZHIZI_NE3_RX_BASE_INFO:
			buffer[2]=0x02;
			buffer[3]=MSB(CanRxInfo.base_info.vehicle_speed);
			buffer[4]=LSB(CanRxInfo.base_info.vehicle_speed);
			break;
		case ZHIZI_NE3_RX_TIME_INFO:
			buffer[2]=0x09;
			buffer[3]=CanRxInfo.time_info.second;
			buffer[4]=CanRxInfo.time_info.minutes;
			buffer[5]=CanRxInfo.time_info.hours;
			buffer[6]=CanRxInfo.time_info.day;
			buffer[7]=CanRxInfo.time_info.month;
			buffer[8]=CanRxInfo.time_info.year;
			buffer[9]=CanRxInfo.time_info.minute_offset;
			buffer[10]=CanRxInfo.time_info.hour_offset;
			buffer[11]=CanRxInfo.time_info.time_updata;
			break;
		case ZHIZI_NE3_RX_STEER_CMD:
			break;
		case ZHIZI_NE3_RX_SETTING_CMD:
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.veh_setting_info.byte_0.byte;
			buffer[4]=CanRxInfo.veh_setting_info.byte_1.byte;
			buffer[5]=CanRxInfo.veh_setting_info.vehicle_gears;
			break;
		case ZHIZI_NE3_RX_AVM_REQ:
			if(Reverse_Display_Flag==2)
			{
				buffer[2]=0x01;
				buffer[3]=CanRxInfo.avm_request;
			}
			break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=ZhiZi_NE3_HEAD_CODE;
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

void ZhiZi_NE3_AVM_Ready(void)
{
	if(Reverse_Display_Flag==2)
	{
		if(BU18TL82State==BU18TL82_SETP_INIT_OK)
		{
			CanTxInfo.screen_info.byte_0.field.f_display_ready=1;
		}
		else
		{
			CanTxInfo.screen_info.byte_0.field.f_display_ready=2;
		}
		if(CAN_RX_AVM_Timer==0)
		{
			CanRxInfo.avm_request=2;
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_AVM_REQ);
		}
	}
	else
	{
		CanTxInfo.screen_info.byte_0.field.f_display_ready=0;
	}
}

void ZhiZi_NE3_MainPro(void)
{
#if CAN_BUS_OFF_FUN==1
	if(Bus_Off_Flag)
	{
		return;
	}
#endif
	
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
	if(CanTxTimer1)
	{
		CanTxTimer1--;
	}
	if(CanTxTimer2)
	{
		CanTxTimer2--;
	}
	if(CanTxTimer3)
	{
		CanTxTimer3--;
	}
	if(CanReverseNoDataTimer)
	{
		CanReverseNoDataTimer--;
	}
	if(CAN_RX_AVM_Timer)
	{
		CAN_RX_AVM_Timer--;
	}
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
	ZhiZi_NE3_AVM_Ready();
	ZhiZi_NE3_Rx_Message();
	if(F_CAN_INIT)
	{
		CAN1_Ext_Transmit();
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
			CanMainTimer=T2S_1;
			break;
		case CAN_MAIN_INIT:
			CAN1_Ext_ClearTxMessage();
			F_CAN_SLEEP=0;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T30S_1;
			CanRxInfo.time_info.time_updata=0;
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
					if(CanTxTimer1==0)
					{	
						CanTxTimer1=T1S_1;
						ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_SOFT);
						ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_HARD);
						ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_SoftPartNum);
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_SETTING_CMD);
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_BASE_INFO);
						if(!strcmp_equal(&CanRxInfo.time_info.second,&CanRxInfoBak.time_info.second,8))
						{
							OverTimerFlag=0;
							Mem_strcpy(&CanRxInfoBak.time_info.second,&CanRxInfo.time_info.second,8);
							CanRxInfo.time_info.time_updata=0;
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_TIME_INFO);
						}
						else
						{
							OverTimerFlag++;
							if(OverTimerFlag>10)
							{
								OverTimerFlag=10;
								CanRxInfo.time_info.time_updata=1;
							}
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,ZHIZI_NE3_RX_TIME_INFO);
						}
					}
					ZhiZi_NE3_CanKeyTimer();
				}
				if(CanTxTimer2==0)
				{
					CanTxTimer2=T50MS_1;
					ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_DSW);
				}
				if(CanTxTimer3==0)
				{
					CanTxTimer3=T100MS_1;
					ZhiZi_NE3_PostMessage(CAN_POST_MSG_IVI_ST);
				}
				if(CanReverseNoDataTimer==0)
				{
					CanGeneralCtrlFlag.field.reverse_on_off=0;
				}
			}	
			break;
		case CAN_MAIN_SLEEP_CFG:
			CAN1_Ext_ClearRxMessage();
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
				F_CAN_SLEEP=0;
				CAN_IC_STANDBY_OFF;
				CanMainState=CAN_MAIN_INIT;
			}
			break;
		default:
			break;
	}
}
#endif
