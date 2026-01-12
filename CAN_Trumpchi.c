#include "public.h"

#if CAN_FUN_TRUMPCHI==1
CAN_RX_BUFFER CanRxBuffer;
CAN_RX_BUFFER CanRxBuffer2;
CAN_TX_BUFFER CanTxBuffer;
CAN_TX_BUFFER CanTxBuffer2;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_TX_INFO CanTxInfo;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
u32 CanMainTimer;
u32 CanMainTimer2;
u32 CanNoDataTimer;
u32 CanCheckErrorTimer;
u16 InfoKeyPressTimer;
u16 InfoKeyReleaseTimer;
u8 InfoKeyLongPressFlag;
u16 CanTxTimer;
u16 CanTxTimer1;
u16 CanTxTimer2;
u16 CanTxTimer3;
u8 CanTxErrorCounter;
u8 CanNoTxCounter;
u8 TestTxTimer;
u8 TestTxTimer2;
u8 Settingbuffer[100];
u8 Settingbufferbak[100];
CAN_KEY_INFO Trumpchi_CanKeyInfo;

const u8 Trumpchi_PanelKeyTab[5][4]=
{
	{0,					NO_KEY,					NO_KEY,						0},
	{1,					UICC_SOURCE,				NO_KEY,						0},
	{2,					UICC_MENU,				NO_KEY,						0},
	{3,					UICC_TFT_STANDBY,		NO_KEY,			    			0},	
	{4,					UICC_CLOCK,				SYSTEM_POWER_OFF_KEY,		1},	
};

void Trumpchi_KeyScan(void)
{
	if(Trumpchi_CanKeyInfo.KeyStatus==1)
	{
		if(Trumpchi_CanKeyInfo.CanKeyCode!=Trumpchi_CanKeyInfo.bkCanKeyCode)
		{
			Trumpchi_CanKeyInfo.bkCanKeyCode=Trumpchi_CanKeyInfo.CanKeyCode;		  
			Trumpchi_CanKeyInfo.bkLongKeyCode=Trumpchi_CanKeyInfo.LongKeyCode;
			Trumpchi_CanKeyInfo.bkShortKeyCode=Trumpchi_CanKeyInfo.ShortKeyCode;
			Trumpchi_CanKeyInfo.bkKeyProperty=Trumpchi_CanKeyInfo.KeyProperty;
			Trumpchi_CanKeyInfo.ShortPressHoldTime=T1S_1;
			Trumpchi_CanKeyInfo.LongPressHoldTime=T2S_1;
			Trumpchi_CanKeyInfo.F_HoldPress=0;	
		}
	}
	else if(Trumpchi_CanKeyInfo.KeyStatus==0)
	{
		if(0==Trumpchi_CanKeyInfo.bkKeyProperty)
		{
			if(Trumpchi_CanKeyInfo.ShortPressHoldTime)
			{
				PostKeyCode(Trumpchi_CanKeyInfo.bkShortKeyCode,Trumpchi_CanKeyInfo.key_source);
			}
		}
		else if(1==Trumpchi_CanKeyInfo.bkKeyProperty)
		{
			if(0==Trumpchi_CanKeyInfo.F_HoldPress)
			{
				if(Trumpchi_CanKeyInfo.ShortPressHoldTime)
				{
					PostKeyCode(Trumpchi_CanKeyInfo.bkShortKeyCode,Trumpchi_CanKeyInfo.key_source);
				}
			}
		}
		FormatMemery((u8 *)&Trumpchi_CanKeyInfo,sizeof(Trumpchi_CanKeyInfo));					  
	}
}

void Trumpchi_CanKeyTimer(void)
{
	if(Trumpchi_CanKeyInfo.ShortPressHoldTime>0)
	{
		Trumpchi_CanKeyInfo.ShortPressHoldTime--;
	}
	if(Trumpchi_CanKeyInfo.LongPressHoldTime>0)
	{
		Trumpchi_CanKeyInfo.LongPressHoldTime--;
		if(Trumpchi_CanKeyInfo.LongPressHoldTime==0)
		{
			if(1==Trumpchi_CanKeyInfo.KeyProperty)
			{
				Trumpchi_CanKeyInfo.F_HoldPress=1;
				PostKeyCode(Trumpchi_CanKeyInfo.LongKeyCode,Trumpchi_CanKeyInfo.key_source);
			} 
		}
	}
}

void Trumpchi_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8];
	
	switch(index)
	{
		case CAN_POST_MSG_ACU_0:
			data[0]=0;
			data[1]=0;
			data[2]=CanTxInfo.acu_1_a_info.byte_2.byte;
			data[3]=CanTxInfo.acu_1_a_info.byte_3.byte;
			data[4]=CanTxInfo.acu_1_a_info.byte_4.byte;
			data[5]=CanTxInfo.acu_1_a_info.byte_5.byte;
			data[6]=0;
			data[7]=0;
			CAN2_TxFrame(CAN_ID_ACU_1_A,data,8);
			break;
		case CAN_POST_MSG_ACU_1:
			data[0]=CanTxInfo.acu_2_a_info.byte_0.byte;
			data[1]=CanTxInfo.acu_2_a_info.byte_1.byte;
			data[2]=CanTxInfo.acu_2_a_info.byte_2.byte;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN2_TxFrame(CAN_ID_ACU_2_A,data,8);
			break;
		case CAN_POST_MSG_ACU_2:
			data[0]=CanTxInfo.acu_3_a_info.reserved_0;
			data[1]=CanTxInfo.acu_3_a_info.reserved_1;
			data[2]=CanTxInfo.acu_3_a_info.byte_2.byte;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;			
			CAN2_TxFrame(CAN_ID_ACU_3_A,data,8);
			break;
		case CAN_POST_MSG_ACU_3:
			data[0]=CanTxInfo.acu_2_b_info.byte_0.byte;
			data[1]=CanTxInfo.acu_2_b_info.byte_1.byte;
			data[2]=CanTxInfo.acu_2_b_info.byte_2.byte;
			data[3]=CanTxInfo.acu_2_b_info.byte_3.byte;
			data[4]=0;
			data[5]=CanTxInfo.acu_2_b_info.byte_5.byte;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_ACU_2_B,data,8);
			break;
		case CAN_POST_MSG_ACU_4:
			data[0]=CanTxInfo.acu_4_b_info.byte_0.byte;
			data[1]=CanTxInfo.acu_4_b_info.byte_1.byte;
			data[2]=CanTxInfo.acu_4_b_info.byte_2.byte;
			data[3]=CanTxInfo.acu_4_b_info.byte_3.byte;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_ACU_4_B,data,8);
			break;
		case CAN_POST_MSG_ACU_5:
			data[0]=CanTxInfo.acu_5_b_info.byte_0.byte;
			data[1]=CanTxInfo.acu_5_b_info.reserved_1;
			data[2]=CanTxInfo.acu_5_b_info.byte_2.byte;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_ACU_5_B,data,8);
			break;
		case CAN_POST_MSG_ACU_6:
			data[0]=CanTxInfo.acu_10_b_info.byte_0.byte;
			data[1]=CanTxInfo.acu_10_b_info.byte_1.byte;
			data[2]=CanTxInfo.acu_10_b_info.byte_2.byte;
			data[3]=CanTxInfo.acu_10_b_info.byte_3.byte;
			data[4]=CanTxInfo.acu_10_b_info.byte_4.byte;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_ACU_10_B,data,8);
			break;
		case CAN_POST_MSG_ACU_7:
			data[0]=CanTxInfo.acu_16_b_info.byte_0.byte;
			data[1]=CanTxInfo.acu_16_b_info.byte_1.byte;
			data[2]=CanTxInfo.acu_16_b_info.byte_2.byte;
			data[3]=CanTxInfo.acu_16_b_info.byte_3.byte;
			data[4]=CanTxInfo.acu_16_b_info.reserved_4;
			data[5]=CanTxInfo.acu_16_b_info.reserved_5;
			data[6]=CanTxInfo.acu_16_b_info.byte_6.byte;
			data[7]=CanTxInfo.acu_16_b_info.byte_7.byte;
			CAN1_TxFrame(CAN_ID_ACU_16_B,data,8);
			break;
		case CAN_POST_MSG_ACU_8:
			data[0]=0;
			data[1]=CanTxInfo.acu_17_b_info.byte_1.byte;
			data[2]=0;
			data[3]=CanTxInfo.acu_17_b_info.byte_3.byte;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_ACU_17_B,data,8);
			break;
		case CAN_POST_MSG_ACU_9:
			data[0]=CanTxInfo.acu_hvac_1_b_info.byte_0.byte;
			data[1]=CanTxInfo.acu_hvac_1_b_info.byte_1.byte;
			data[2]=CanTxInfo.acu_hvac_1_b_info.byte_2.byte;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_ACU_HVAC_1_B,data,8);
			break;
		case CAN_POST_MSG_ACU_10:
			data[0]=0;
			data[1]=0;
			data[2]=0;
			data[3]=0;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_ACU_11_B,data,8);
			break;
		default:
			break;
	}
}

void Trumpchi_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;
		u8 temp;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_BCM_BCAN_1:
				CanRxInfo.base_info.byte_0.field.f_front_cover=((message.Data[1]&0x10)>>4);
				CanRxInfo.base_info.byte_0.field.f_trunk=((message.Data[1]&0x20)>>5);
				CanRxInfo.base_info.byte_0.field.f_left_rear_door=((message.Data[1]&0x04)>>2);
				CanRxInfo.base_info.byte_0.field.f_right_rear_door=((message.Data[1]&0x08)>>3);
				CanRxInfo.base_info.byte_0.field.f_left_front_door=message.Data[1]&0x01;
				CanRxInfo.base_info.byte_0.field.f_right_front_door=((message.Data[1]&0x02)>>1);
				CanRxInfo.base_info.byte_1.field.f_left_signal_status=message.Data[2]&0x01;
				CanRxInfo.base_info.byte_1.field.f_right_signal_status=((message.Data[2]&0x04)>>2);
				if((message.Data[3]&0x01)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_illumi_status=1;
					CanGeneralCtrlFlag.field.ill_onoff=1;
				}
				else if((message.Data[3]&0x01)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_illumi_status=0;
					CanGeneralCtrlFlag.field.ill_onoff=0;
				}
				if(!strcmp_equal(&CanRxInfo.base_info.byte_0.byte,&CanRxInfoBak.base_info.byte_0.byte,sizeof(CAN_BASE_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.base_info.byte_0.byte,&CanRxInfo.base_info.byte_0.byte,sizeof(CAN_BASE_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_BASIC_INFO);
				}
				break;
			case CAN_ID_BCM_BCAN_2:
				if((message.Data[4]&0x01)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_parking_status=1;
					CanGeneralCtrlFlag.field.parking_on_off=1; 
				}
				else if((message.Data[4]&0x01)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_parking_status=0;
					CanGeneralCtrlFlag.field.parking_on_off=0; 
				}
				if(((message.Data[4]&0x80)>>7)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_reverse_status=1;
					CanGeneralCtrlFlag.field.reverse_on_off=1;
				}
				else if(((message.Data[4]&0x80)>>7)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_reverse_status=0;
					CanGeneralCtrlFlag.field.reverse_on_off=0;
				}
				if(!strcmp_equal(&CanRxInfo.base_info.byte_0.byte,&CanRxInfoBak.base_info.byte_0.byte,sizeof(CAN_BASE_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.base_info.byte_0.byte,&CanRxInfo.base_info.byte_0.byte,sizeof(CAN_BASE_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_BASIC_INFO);
				}
				break;
			case CAN_ID_BCM_BCAN_4:
				if((message.Data[0]&0x04)>>2==0)
				{
					CanRxInfo.setting_info.byte_0.field.f_remote_unlock=1;
				}
				else if((message.Data[0]&0x04)>>2==1)
				{
					CanRxInfo.setting_info.byte_0.field.f_remote_unlock=2;
				}
				if((message.Data[0]&0x10)>>4==0)
				{
					CanRxInfo.setting_info.byte_0.field.f_auto_door_unlock=2;
				}
				else if((message.Data[0]&0x10)>>4==1)
				{
					CanRxInfo.setting_info.byte_0.field.f_auto_door_unlock=1;
				}
				if((message.Data[1]&0x80)>>7==0)
				{
					CanRxInfo.setting_info.byte_2.field.f_outside_rear_view_mirro_auto_floding=2;
				}
				else if((message.Data[1]&0x80)>>7==1)
				{
					CanRxInfo.setting_info.byte_2.field.f_outside_rear_view_mirro_auto_floding=1;
				}
				if((message.Data[0]&0x01)==0)
				{
					CanRxInfo.setting_info.byte_2.field.f_remote_control_window_sunroof=2;
				}
				else if((message.Data[0]&0x01)==1)
				{
					CanRxInfo.setting_info.byte_2.field.f_remote_control_window_sunroof=1;
				}
				if((message.Data[3]&0x02)>>1==0)
				{
					CanRxInfo.setting_info.byte_9.field.f_auto_wiper=2;
				}
				else if((message.Data[3]&0x02)>>1==1)
				{
					CanRxInfo.setting_info.byte_9.field.f_auto_wiper=1;
				}
				if((message.Data[1]&0x08)>>3==0)
				{
					CanRxInfo.setting_info.byte_10.field.f_wiper_maintanence=2;
				}
				else if((message.Data[1]&0x08)>>3==1)
				{
					CanRxInfo.setting_info.byte_10.field.f_wiper_maintanence=1;
				}
				if((message.Data[1]&0x07)==1)
				{
					CanRxInfo.setting_info.byte_6.field.f_auto_light_sensitivity=3;
				}
				else if((message.Data[1]&0x07)==2)
				{
					CanRxInfo.setting_info.byte_6.field.f_auto_light_sensitivity=2;
				}
				else if((message.Data[1]&0x07)==3)
				{
					CanRxInfo.setting_info.byte_6.field.f_auto_light_sensitivity=1;
				}
				if((message.Data[1]&0x10)>>4==0)
				{
					CanRxInfo.setting_info.byte_10.field.f_auto_rear_wipe_function=2;
				}
				else if((message.Data[1]&0x10)>>4==1)
				{
					CanRxInfo.setting_info.byte_10.field.f_auto_rear_wipe_function=1;
				}
				if((message.Data[0]&0xC0)>>6==0)
				{
					CanRxInfo.setting_info.byte_1.field.f_light_to_home=1;
				}
				else if((message.Data[0]&0xC0)>>6==1)
				{
					CanRxInfo.setting_info.byte_1.field.f_light_to_home=2;
				}
				else if((message.Data[0]&0xC0)>>6==2)
				{
					CanRxInfo.setting_info.byte_1.field.f_light_to_home=3;
				}
				if((message.Data[0]&0x02)>>1==0)
				{
					CanRxInfo.setting_info.byte_1.field.f_fog_light_for_turning=2;
				}
				else if((message.Data[0]&0x02)>>1==1)
				{
					CanRxInfo.setting_info.byte_1.field.f_fog_light_for_turning=1;
				}
				if((message.Data[1]&0x20)>>5==0)
				{
					CanRxInfo.setting_info.byte_4.field.f_head_light_for_daytime=2;
				}
				else if((message.Data[1]&0x20)>>5==1)
				{
					CanRxInfo.setting_info.byte_4.field.f_head_light_for_daytime=1;
				}
				if((message.Data[1]&0x40)>>6==0)
				{
					CanRxInfo.setting_info.byte_2.field.f_lock_unlock_whistle_remind=2;
				}
				else if((message.Data[1]&0x40)>>6==1)	
				{
					CanRxInfo.setting_info.byte_2.field.f_lock_unlock_whistle_remind=1;
				}
				if((message.Data[3]&0x01)==0)
				{
					CanRxInfo.setting_info.byte_6.field.f_interior_ambient_light=2;
				}
				else if((message.Data[3]&0x01)==1)
				{
					CanRxInfo.setting_info.byte_6.field.f_interior_ambient_light=1;
				}
				break;
			case CAN_ID_PEPS_6:
				if((message.Data[1]&0x40)>>6==0)
				{
					CanRxInfo.setting_info.byte_0.field.f_automatically_lock=2;
				}
				else if((message.Data[1]&0x40)>>6==1)
				{
					CanRxInfo.setting_info.byte_0.field.f_automatically_lock=1;
				}
				if((message.Data[2]&0x04)>>2==0)
				{
					CanRxInfo.setting_info.byte_0.field.f_automatically_unlock=2;
				}
				else if((message.Data[2]&0x04)>>2==1)
				{
					CanRxInfo.setting_info.byte_0.field.f_automatically_unlock=1;
				}
				if((message.Data[2]&0x03)==0)
				{
					CanRxInfo.setting_info.byte_1.field.f_smart_trunk=1;
				}
				else if((message.Data[2]&0x03)==1)
				{
					CanRxInfo.setting_info.byte_1.field.f_smart_trunk=2;
				}
				else if((message.Data[2]&0x03)==2)
				{
					CanRxInfo.setting_info.byte_1.field.f_smart_trunk=3;
				}
				if((message.Data[0]&0x40)>>6==0)
				{
					CanRxInfo.setting_info.byte_6.field.f_smart_welcome_light=2;
				}
				else if((message.Data[0]&0x40)>>6==1)
				{
					CanRxInfo.setting_info.byte_6.field.f_smart_welcome_light=1;
				}
				CanRxInfo.setting_info.byte_8.field.f_time_remote_electricity_on=message.Data[0]&0x3F;
				CanRxInfo.setting_info.byte_9.field.f_time_remote_power_on=message.Data[1]&0x3F;
				break;
			case CAN_ID_MSM_1:
				if((message.Data[0]&0xC0)>>6==0)
				{
					CanRxInfo.setting_info.byte_2.field.f_rear_view_mirro_flip_position_setting=2;
					CanRxInfo.setting_info.byte_3.field.f_manual_rear_view_mirro_flip_of_reversing=2;
				}
				else if((message.Data[0]&0xC0)>>6==1)
				{
					CanRxInfo.setting_info.byte_2.field.f_rear_view_mirro_flip_position_setting=2;
					CanRxInfo.setting_info.byte_3.field.f_manual_rear_view_mirro_flip_of_reversing=1;
				}
				else if((message.Data[0]&0xC0)>>6==2)
				{
					CanRxInfo.setting_info.byte_2.field.f_rear_view_mirro_flip_position_setting=1;
					CanRxInfo.setting_info.byte_3.field.f_manual_rear_view_mirro_flip_of_reversing=2;
				}
				if((message.Data[0]&0x01)==0)
				{
					CanRxInfo.seat_setting_info.f_seat_welcome_function=2;
				}
				else if((message.Data[0]&0x01)==1)
				{
					CanRxInfo.seat_setting_info.f_seat_welcome_function=1;
				}
				if((message.Data[0]&0x02)>>1==0)
				{
					CanRxInfo.seat_setting_info.f_key_recognition=2;
				}
				else if((message.Data[0]&0x02)>>1==1)
				{
					CanRxInfo.seat_setting_info.f_key_recognition=1;
				}
				break;
			case CAN_ID_HVSM_1:
				if((message.Data[1]&0x08)>>3==0)
				{
					CanRxInfo.seat_setting_info.f_front_left_seat_heating_ventilating_auto_mode=2;
				}
				else if((message.Data[1]&0x08)>>3==1)
				{
					CanRxInfo.seat_setting_info.f_front_left_seat_heating_ventilating_auto_mode=1;
				}
				if((message.Data[1]&0x80)>>7==0)
				{
					CanRxInfo.seat_setting_info.f_front_right_seat_heating_ventilating_auto_mode=2;
				}
				else if((message.Data[1]&0x80)>>7==1)
				{
					CanRxInfo.seat_setting_info.f_front_right_seat_heating_ventilating_auto_mode=1;
				}
				break;
			case CAN_ID_GW_MRR_1_B:
				if((message.Data[4]&0x01)==0)
				{
					CanRxInfo.setting_info.byte_4.field.f_forward_collision_warning=1;
				}
				else if((message.Data[4]&0x01)==1)
				{
					CanRxInfo.setting_info.byte_4.field.f_forward_collision_warning=2;
				}
				if((message.Data[5]&0x18)>>3==0)
				{
					CanRxInfo.setting_info.byte_5.field.f_forward_collision_warning_distance=1;
				}
				else if((message.Data[5]&0x18)>>3==1)
				{
					CanRxInfo.setting_info.byte_5.field.f_forward_collision_warning_distance=2;
				}
				else if((message.Data[5]&0x18)>>3==2)
				{
					CanRxInfo.setting_info.byte_5.field.f_forward_collision_warning_distance=3;
				}
				if((message.Data[5]&0x02)>>1==0)
				{
					CanRxInfo.setting_info.byte_5.field.f_autonomous_emergency_braking=1;
				}
				else if((message.Data[5]&0x02)>>1==1)
				{
					CanRxInfo.setting_info.byte_5.field.f_autonomous_emergency_braking=2;
				}
				break;
			case CAN_ID_GW_EPS_1_B:
				if((message.Data[0]&0x06)>>1==1)
				{
					CanRxInfo.setting_info.byte_5.field.f_steering_mode=2;
				}
				else if((message.Data[0]&0x06)>>1==2)
				{
					CanRxInfo.setting_info.byte_5.field.f_steering_mode=3;
				}
				else if((message.Data[0]&0x06)>>1==3)
				{
					CanRxInfo.setting_info.byte_5.field.f_steering_mode=1;
				}
				break;
			case CAN_ID_HVACF_1:
				CanRxInfo.air_info.byte_1.field.f_AC=((message.Data[0]&0x40)>>6)&(message.Data[0]&0x01);
				CanRxInfo.air_info.byte_1.field.f_AUTO=((message.Data[3]&0x40)>>6);
				CanRxInfo.air_info.byte_1.field.f_ION=((message.Data[6]&0x40)>>6);
				CanRxInfo.air_info.byte_1.field.f_rear_defrost=((message.Data[0]&0x04)>>2);
				CanRxInfo.air_info.byte_2.field.f_fan_speed=message.Data[7]&0x07;
				CanRxInfo.air_info.byte_2.field.f_internal_external_circulation=((message.Data[5]&0x60)>>5);
				CanRxInfo.air_info.byte_2.field.f_3zone=((message.Data[6]&0x04)>>2);
				CanRxInfo.air_info.byte_2.field.f_dual=((message.Data[3]&0x20)>>5);
				CanRxInfo.air_info.byte_2.field.f_ac_max=((message.Data[0]&0x80)>>7);
				CanRxInfo.air_info.byte_1.field.f_wind_exit_mode=(message.Data[4]&0x07);
				CanRxInfo.air_info.byte_1.field.f_display_request=((message.Data[5]&0x80)>>7);
				for(temp=0;temp<29;temp++)
				{
					if(((message.Data[6]&0x3E)>>1)==temp)
					{
						CanRxInfo.air_info.byte_3.field.f_left_temperature=2*temp+1;
					}
				}
				for(temp=0;temp<29;temp++)
				{
					if((((message.Data[6]&0x01)<<4)|((message.Data[7]&0xF0)>>4))==temp)
					{
						CanRxInfo.air_info.byte_4.field.f_right_temperature=2*temp+1;
					}
				}
				if(!strcmp_equal(&CanRxInfo.air_info.byte_0.byte,&CanRxInfoBak.air_info.byte_0.byte,sizeof(CAN_AIR_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.air_info.byte_0.byte,&CanRxInfo.air_info.byte_0.byte,sizeof(CAN_AIR_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_AIR_INFO);
				}
				break;
			case CAN_ID_HVACF_3:
				if((message.Data[0]&0x01)==0)
				{
					CanRxInfo.air_canditioning_info.byte_2.filed.f_compressor_status=1;
				}
				else if((message.Data[0]&0x01)==1)
				{
					CanRxInfo.air_canditioning_info.byte_2.filed.f_compressor_status=2;
				}
				if((message.Data[0]&0x02)>>1==0)
				{
					CanRxInfo.air_canditioning_info.byte_0.filed.f_frs_rec_auto_mode=1;
				}
				else if((message.Data[0]&0x02)>>1==1)
				{
					CanRxInfo.air_canditioning_info.byte_0.filed.f_frs_rec_auto_mode=2;
				}
				if((message.Data[0]&0x0C)>>2==0)
				{
					CanRxInfo.air_canditioning_info.byte_0.filed.f_comfort_curve=1;
				}
				else if((message.Data[0]&0x0C)>>2==1)
				{
					CanRxInfo.air_canditioning_info.byte_0.filed.f_comfort_curve=2;
				}
				else if((message.Data[0]&0x0C)>>2==2)
				{
					CanRxInfo.air_canditioning_info.byte_0.filed.f_comfort_curve=3;
				}
				if((message.Data[5]&0x18)>>3==0)
				{
					CanRxInfo.air_canditioning_info.byte_0.filed.f_fan_speed_of_auto_mode=1;
				}
				else if((message.Data[5]&0x18)>>3==1)
				{
					CanRxInfo.air_canditioning_info.byte_0.filed.f_fan_speed_of_auto_mode=2;
				}
				else if((message.Data[5]&0x18)>>3==2)
				{
					CanRxInfo.air_canditioning_info.byte_0.filed.f_fan_speed_of_auto_mode=3;
				}
				break;
			case CAN_ID_ICM_1_B:
				CanRxInfo.backlight_info.f_level=((message.Data[6]&0x1C)>>2);
				break;
			case CAN_ID_ICM_3_B:
				CanRxInfo.setting_info.byte_11.field.f_instantaneous_speed=message.Data[0];
				break;
			case CAN_ID_ICM_4_B:
				if((message.Data[0]&0x60)>>5==0)
				{
					CanRxInfo.setting_info.byte_7.field.f_warning_sound_volume=1;
				}
				else if((message.Data[0]&0x60)>>5==1)
				{
					CanRxInfo.setting_info.byte_7.field.f_warning_sound_volume=2;
				}
				else if((message.Data[0]&0x60)>>5==2)
				{
					CanRxInfo.setting_info.byte_7.field.f_warning_sound_volume=3;
				}
				CanRxInfo.setting_info.byte_7.field.f_speed_warning=message.Data[0]&0x1F;
				break;
			case CAN_ID_GW_1_B:
				if((message.Data[7]&0x80)>>7==0)
				{
					CanRxInfo.setting_info.byte_8.field.f_transport_mode=2;
				}
				else if((message.Data[7]&0x80)>>7==1)
				{
					CanRxInfo.setting_info.byte_8.field.f_transport_mode=1;
				}
				break;
			case CAN_ID_LIGHT_1:
				if((message.Data[2]&0x01)==0)
				{
					CanRxInfo.setting_info.byte_5.field.f_smart_high_beam=2;
				}
				else if((message.Data[2]&0x01)==1)
				{
					CanRxInfo.setting_info.byte_5.field.f_smart_high_beam=1;
				}
				break;
			case CAN_ID_GW_SAS_1_B:
				CanRxInfo.eps_info.byte_0.field.f_steer_wheel_angle_msb=message.Data[3];
				CanRxInfo.eps_info.byte_1.field.f_steer_wheel_angle_lsb=message.Data[4];
				break;
			case CAN_ID_FCP_3:
				{
					u8 key_code=0;
					u8 key_status=0;
					u8 temp=0;

					if(message.Data[0]&0x10)
					{
						temp++;
						key_code=2;
					}
					
					if(message.Data[0]&0x04)
					{
						temp++;
						key_code=1;
					}
					
					if(message.Data[0]&0x01)
					{
						temp++;
						key_code=4;
					}
					
					if(message.Data[7]&0x40)
					{
						temp++;
						key_code=3;
					}
					
					if(key_code)
					{
						key_status=1;
					}

					if(temp>1)
					{
						break;
					}
					Trumpchi_CanKeyInfo.CanKeyCode=key_code;
					Trumpchi_CanKeyInfo.KeyStatus=key_status;	
					Trumpchi_CanKeyInfo.ShortKeyCode=Trumpchi_PanelKeyTab[Trumpchi_CanKeyInfo.CanKeyCode][1];
					Trumpchi_CanKeyInfo.LongKeyCode=Trumpchi_PanelKeyTab[Trumpchi_CanKeyInfo.CanKeyCode][2];	
					Trumpchi_CanKeyInfo.KeyProperty=Trumpchi_PanelKeyTab[Trumpchi_CanKeyInfo.CanKeyCode][3]; 
					Trumpchi_CanKeyInfo.key_source=PANEL;
					Trumpchi_KeyScan();   
				}
				break;
			case CAN_ID_FCP_5:
				CanRxInfo.setting_info.byte_6.field.f_forward_collision_warning_button=((message.Data[0]&0x04)>>2);
				break;
			case CAN_ID_PANEL_1:
				if(message.Data[0]&0x40)
				{
					PostKeyCode(UICC_VOLUME_UP, PANEL);
				}
				if(message.Data[0]&0x80)
				{
					PostKeyCode(UICC_VOLUME_DOWN, PANEL);
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

void Trumpchi_Rx_Message_2(void)
{
	if(CanRxBuffer2.head!=CanRxBuffer2.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer2.message[CanRxBuffer2.head];
		CanRxBuffer2.message[CanRxBuffer2.head].ID=0;
		CanRxBuffer2.head=(CanRxBuffer2.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_PCS_1:
				if((message.Data[7]&0x01)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_display=1;
					CanGeneralCtrlFlag.field.camera_on_off=1;
				}
				else if((message.Data[7]&0x01)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_display=0;
					CanGeneralCtrlFlag.field.camera_on_off=0;
				}
				break;
			case CAN_ID_BSD_1:
				CanRxInfo.setting_info.byte_3.field.f_blind_spot_detection=message.Data[0]&0x03;
				break;
			case CAN_ID_IFC_1:
				CanRxInfo.setting_info.byte_4.field.f_cruise_mode=((message.Data[1]&0xC0)>>6);
				CanRxInfo.setting_info.byte_4.field.f_lane_assist_mode=((message.Data[2]&0xC0)>>6);
				if((message.Data[3]&0x03)==0)
				{
					CanRxInfo.setting_info.byte_10.field.f_lane_assist=2;
				}
				else if((message.Data[3]&0x03)==1)
				{
					CanRxInfo.setting_info.byte_10.field.f_lane_assist=1;
				}
				break;
			case CAN_ID_PAS_1:
				CanRxInfo.rear_radar_info.byte_0.field.f_sensor_voice=((message.Data[0]&0xF0)>>4);
				CanRxInfo.rear_radar_info.byte_0.field.f_sensor_mode=((message.Data[1]&0x0E)>>1);
				CanRxInfo.rear_radar_info.byte_1.field.f_rear_left_sensor=message.Data[5]&0x03;
				CanRxInfo.rear_radar_info.byte_2.field.f_rear_left_middle_sensor=message.Data[3]&0x07;
				CanRxInfo.rear_radar_info.byte_3.field.f_rear_right_middle_sensor=message.Data[2]&0x07;
				CanRxInfo.rear_radar_info.byte_4.field.f_rear_right_sensor=message.Data[4]&0x03;
				break;
			case CAN_ID_PAS_2:
				CanRxInfo.front_radar_info.byte_0.field.f_front_right_sensor=message.Data[0]&0x03;
				CanRxInfo.front_radar_info.byte_1.field.f_front_left_sensor=message.Data[1]&0x03;
				break;
			case CAN_ID_WCM_1:
				if((message.Data[1]&0x0C)>>2==0)
				{
					CanRxInfo.setting_info.byte_3.field.f_wireless_charge=1;
				}
				else
				{
					CanRxInfo.setting_info.byte_3.field.f_wireless_charge=2;
				}
				CanRxInfo.setting_info.byte_3.field.f_wireless_charge_state=message.Data[1]&0x03;
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

void Trumpchi_SettingDataCompare(void)
{
	Settingbuffer[3]=0;
	Settingbuffer[4]=0;
	Settingbuffer[5]=CanRxInfo.air_canditioning_info.byte_2.filed.f_compressor_status;
	Settingbuffer[6]=CanRxInfo.air_canditioning_info.byte_0.filed.f_frs_rec_auto_mode;
	Settingbuffer[7]=CanRxInfo.air_canditioning_info.byte_0.filed.f_comfort_curve;
	Settingbuffer[8]=CanRxInfo.seat_setting_info.f_front_left_seat_heating_ventilating_auto_mode;
	Settingbuffer[9]=CanRxInfo.seat_setting_info.f_front_right_seat_heating_ventilating_auto_mode;
	Settingbuffer[10]=CanRxInfo.setting_info.byte_7.field.f_speed_warning;
	Settingbuffer[11]=CanRxInfo.setting_info.byte_7.field.f_warning_sound_volume;
	Settingbuffer[12]=CanRxInfo.setting_info.byte_8.field.f_time_remote_electricity_on;
	Settingbuffer[13]=CanRxInfo.setting_info.byte_9.field.f_time_remote_power_on;
	Settingbuffer[14]=CanRxInfo.setting_info.byte_5.field.f_steering_mode;
	Settingbuffer[15]=CanRxInfo.setting_info.byte_0.field.f_remote_unlock;
	Settingbuffer[16]=0;
	Settingbuffer[17]=CanRxInfo.setting_info.byte_0.field.f_auto_door_unlock;
	Settingbuffer[18]=CanRxInfo.setting_info.byte_2.field.f_remote_control_window_sunroof;
	Settingbuffer[19]=CanRxInfo.setting_info.byte_10.field.f_wiper_maintanence;
	Settingbuffer[20]=CanRxInfo.setting_info.byte_10.field.f_auto_rear_wipe_function;
	Settingbuffer[21]=CanRxInfo.setting_info.byte_1.field.f_light_to_home;
	Settingbuffer[22]=CanRxInfo.setting_info.byte_1.field.f_fog_light_for_turning;
	Settingbuffer[23]=CanRxInfo.setting_info.byte_4.field.f_head_light_for_daytime;
	Settingbuffer[24]=CanRxInfo.setting_info.byte_6.field.f_auto_light_sensitivity;
	Settingbuffer[25]=0;
	Settingbuffer[26]=0;
	Settingbuffer[27]=CanRxInfo.air_info.byte_1.field.f_ION;
	Settingbuffer[28]=CanRxInfo.seat_setting_info.f_seat_welcome_function;
	Settingbuffer[29]=CanRxInfo.seat_setting_info.f_key_recognition;
	Settingbuffer[30]=CanRxInfo.setting_info.byte_2.field.f_outside_rear_view_mirro_auto_floding;
	Settingbuffer[31]=CanRxInfo.setting_info.byte_2.field.f_lock_unlock_whistle_remind;
	Settingbuffer[32]=CanRxInfo.setting_info.byte_0.field.f_automatically_lock;
	Settingbuffer[33]=CanRxInfo.setting_info.byte_0.field.f_automatically_unlock;
	Settingbuffer[34]=CanRxInfo.setting_info.byte_2.field.f_rear_view_mirro_flip_position_setting;
	Settingbuffer[35]=CanRxInfo.setting_info.byte_3.field.f_manual_rear_view_mirro_flip_of_reversing;
	Settingbuffer[36]=CanRxInfo.setting_info.byte_6.field.f_smart_welcome_light;
	Settingbuffer[37]=0;
	Settingbuffer[38]=0;
	Settingbuffer[39]=CanRxInfo.setting_info.byte_6.field.f_interior_ambient_light;	
	Settingbuffer[40]=0;
	Settingbuffer[41]=CanRxInfo.air_canditioning_info.byte_0.filed.f_fan_speed_of_auto_mode;
	Settingbuffer[42]=CanRxInfo.setting_info.byte_1.field.f_smart_trunk;
	Settingbuffer[43]=CanRxInfo.setting_info.byte_9.field.f_auto_wiper;
	Settingbuffer[44]=0;
	Settingbuffer[45]=0;
	Settingbuffer[46]=CanRxInfo.setting_info.byte_5.field.f_smart_high_beam;
	Settingbuffer[47]=CanRxInfo.setting_info.byte_3.field.f_wireless_charge;
	Settingbuffer[48]=CanRxInfo.setting_info.byte_5.field.f_autonomous_emergency_braking;
	Settingbuffer[49]=CanRxInfo.setting_info.byte_4.field.f_cruise_mode;
	Settingbuffer[50]=CanRxInfo.setting_info.byte_4.field.f_forward_collision_warning;
	Settingbuffer[51]=CanRxInfo.setting_info.byte_5.field.f_forward_collision_warning_distance;
	Settingbuffer[52]=CanRxInfo.setting_info.byte_10.field.f_lane_assist;
	Settingbuffer[53]=CanRxInfo.setting_info.byte_4.field.f_lane_assist_mode;
	Settingbuffer[54]=0;
	Settingbuffer[55]=0;
	Settingbuffer[56]=0;
	Settingbuffer[57]=0;
	Settingbuffer[58]=0;
	Settingbuffer[59]=0;
	Settingbuffer[60]=0;
	Settingbuffer[61]=0;
	Settingbuffer[62]=0;
	Settingbuffer[63]=0;
	Settingbuffer[64]=CanRxInfo.setting_info.byte_6.field.f_forward_collision_warning_button;
	Settingbuffer[65]=0;
	Settingbuffer[66]=CanRxInfo.setting_info.byte_8.field.f_transport_mode;
	Settingbuffer[67]=0;
	Settingbuffer[68]=0;
	Settingbuffer[69]=CanRxInfo.setting_info.byte_3.field.f_blind_spot_detection;
	Settingbuffer[70]=0;
	Settingbuffer[71]=0;
	Settingbuffer[72]=0;
	Settingbuffer[73]=CanRxInfo.setting_info.byte_3.field.f_wireless_charge_state;
	Settingbuffer[74]=CanRxInfo.setting_info.byte_11.field.f_instantaneous_speed;
	
	if(strcmp_equal(Settingbuffer,Settingbufferbak,100)==0)
	{
		Mem_strcpy(Settingbufferbak,Settingbuffer,100);
		PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_SETTING_1);
	}
}

void Trumpchi_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id=buffer[1];

	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	
	switch(cmd_id)
	{
		case TRUMPCHI_TX_SETTING_CMD_1:
			switch(buffer[3])
			{
				case 0x00:
					break;
				case 0x01:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_10_b_info.byte_4.field.f_language_setting=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_6);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_10_b_info.byte_4.field.f_language_setting=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_6);
					}
					else if(buffer[4]==0x05)
					{
						CanTxInfo.acu_10_b_info.byte_4.field.f_language_setting=5;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_6);
					}
					break;
				case 0x02:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_compressor_status=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_compressor_status=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_0.field.f_compressor_status=0;
					break;
				case 0x03:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_frs_rec_auto_mode=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_frs_rec_auto_mode=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_0.field.f_compressor_status=0;
					break;
				case 0x04:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_comfort_curve=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_comfort_curve=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_comfort_curve=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_0.field.f_comfort_curve=0;
					break;
				case 0x05:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_1.field.f_main_driver_auto_heat=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_1.field.f_main_driver_auto_heat=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_1.field.f_main_driver_auto_heat=0;
					break;
				case 0x06:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_1.field.f_co_drive_auto_heat=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_1.field.f_co_drive_auto_heat=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_1.field.f_co_drive_auto_heat=0;
					break;
				case 0x07:				
					CanTxInfo.acu_2_b_info.byte_4.field.f_speed_warning=buffer[4]&0x1F;
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					CanTxInfo.acu_2_b_info.byte_4.field.f_speed_warning=0;
					break;
				case 0x08:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_4.field.f_warning_sound_volume=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_4.field.f_warning_sound_volume=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_2_b_info.byte_4.field.f_warning_sound_volume=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_4.field.f_warning_sound_volume=0;
					break;
				case 0x09:
					CanTxInfo.acu_2_b_info.byte_6.field.f_time_remote_electricity_on=buffer[4]&0x3F;
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					CanTxInfo.acu_2_b_info.byte_6.field.f_time_remote_electricity_on=0;
					break;
				case 0x0A:
					CanTxInfo.acu_2_b_info.byte_7.field.f_time_remote_power_on=buffer[4]&0x3F;
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					CanTxInfo.acu_2_b_info.byte_7.field.f_time_remote_power_on=0;
					break;
				case 0x0B:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_5_b_info.byte_0.field.f_steering_mode=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_5_b_info.byte_0.field.f_steering_mode=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_5_b_info.byte_0.field.f_steering_mode=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					CanTxInfo.acu_5_b_info.byte_0.field.f_steering_mode=0;
					break;
				case 0x0C:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_0.field.f_remote_unlock=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_0.field.f_remote_unlock=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_0.field.f_remote_unlock=0;
					break;
				case 0x0D:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_0.field.f_high_speed_auto_lock=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_0.field.f_high_speed_auto_lock=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_0.field.f_high_speed_auto_lock=0;
					break;
				case 0x0E:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_1.field.f_auto_door_unlock=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_1.field.f_auto_door_unlock=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_1.field.f_auto_door_unlock=0;
					break;
				case 0x0F:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_0.field.f_remote_control_window_sunroof=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_0.field.f_remote_control_window_sunroof=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_0.field.f_remote_control_window_sunroof=0;
					break;
				case 0x10:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_2.field.f_wiper_maintanence=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_2.field.f_wiper_maintanence=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_2.field.f_wiper_maintanence=0;
					break;
				case 0x11:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_2.field.f_auto_rear_wipe_function=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_2.field.f_auto_rear_wipe_function=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_2.field.f_auto_rear_wipe_function=0;
					break;
				case 0x12:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_1.field.f_light_to_home=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_1.field.f_light_to_home=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_4_b_info.byte_1.field.f_light_to_home=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_1.field.f_light_to_home=0;
					break;
				case 0x13:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_0.field.f_fog_light_for_turning=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_0.field.f_fog_light_for_turning=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_0.field.f_fog_light_for_turning=0;
					break;
				case 0x14:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_2.field.f_head_light_for_daytime=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_2.field.f_head_light_for_daytime=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_2.field.f_head_light_for_daytime=0;
					break;
				case 0x15:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_1.field.f_auto_light_sensitivity=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_1.field.f_auto_light_sensitivity=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_4_b_info.byte_1.field.f_auto_light_sensitivity=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_1.field.f_auto_light_sensitivity=0;
					break;
				case 0x16:
					break;
				case 0x17:
					break;
				case 0x18:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_ion_mode=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_0.field.f_ion_mode=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_0.field.f_ion_mode=0;
					break;
				case 0x19:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_2.field.f_seat_welcome_function=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_2.field.f_seat_welcome_function=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_2.field.f_seat_welcome_function=0;
					break;
				case 0x1A:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_2.field.f_key_recognition=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_2.field.f_key_recognition=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_2.field.f_key_recognition=0;
					break;
				case 0x1B:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_2.field.f_outside_rear_view_mirro_auto_floding=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_2.field.f_outside_rear_view_mirro_auto_floding=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_2.field.f_outside_rear_view_mirro_auto_floding=0;
					break;
				case 0x1C:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_2.field.f_lock_unlock_whistle_remind=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_2.field.f_lock_unlock_whistle_remind=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_2.field.f_lock_unlock_whistle_remind=0;
					break;
				case 0x1D:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_5.field.f_automatically_lock=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_5.field.f_automatically_lock=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_5.field.f_automatically_lock=0;
					break;
				case 0x1E:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_5.field.f_automatically_unlock=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_5.field.f_automatically_unlock=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_5.field.f_automatically_unlock=0;
					break;
				case 0x1F:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_17_b_info.byte_3.field.f_rear_view_mirro_flip_position_setting=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_17_b_info.byte_3.field.f_rear_view_mirro_flip_position_setting=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
					}
					CanTxInfo.acu_17_b_info.byte_3.field.f_rear_view_mirro_flip_position_setting=0;
					break;
				case 0x20:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_17_b_info.byte_3.field.f_rear_view_mirro_flip_position_setting=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_17_b_info.byte_3.field.f_rear_view_mirro_flip_position_setting=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
					}
					CanTxInfo.acu_17_b_info.byte_3.field.f_rear_view_mirro_flip_position_setting=0;
					break;
				case 0x21:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_2.field.f_smart_welcome_light=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_2.field.f_smart_welcome_light=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_2.field.f_smart_welcome_light=0;
					break;
				case 0x22:
					break;
				case 0x23:
					break;
				case 0x24:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_3.field.f_ambient_light_control=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_3.field.f_ambient_light_control=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_3.field.f_ambient_light_control=0;
					break;
				case 0x25:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_3.field.f_air_quality_sensor=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_3.field.f_air_quality_sensor=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_2_b_info.byte_3.field.f_air_quality_sensor=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_3.field.f_air_quality_sensor=0;
					break;
				case 0x26:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_17_b_info.byte_1.field.f_fan_speed_of_auto_mode=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_17_b_info.byte_1.field.f_fan_speed_of_auto_mode=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_17_b_info.byte_1.field.f_fan_speed_of_auto_mode=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
					}
					CanTxInfo.acu_17_b_info.byte_1.field.f_fan_speed_of_auto_mode=0;
					break;
				case 0x27:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_b_info.byte_3.field.f_smart_trunk=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_b_info.byte_3.field.f_smart_trunk=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_2_b_info.byte_3.field.f_smart_trunk=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					}
					CanTxInfo.acu_2_b_info.byte_3.field.f_smart_trunk=0;
					break;
				case 0x28:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_4_b_info.byte_3.field.f_auto_wiper=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_4_b_info.byte_3.field.f_auto_wiper=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_4);
					}
					CanTxInfo.acu_4_b_info.byte_3.field.f_auto_wiper=0;
					break;
				case 0x29:
					for(int i=0;i<8;i++)
					{
						if((buffer[4]&0x07)==i)
						{
							CanTxInfo.acu_17_b_info.byte_0.field.f_ial_brightness=i;
							Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
						}
					}
					break;
				case 0x2A:
					for(int i=0;i<32;i++)
					{
						if((buffer[4]&0x1F)==i)
						{
							CanTxInfo.acu_17_b_info.byte_1.field.f_ial_color=i;
							Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
						}
					}
					break;
				case 0x2B:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_a_info.byte_1.field.f_smart_high_beam=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_a_info.byte_1.field.f_smart_high_beam=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					CanTxInfo.acu_2_a_info.byte_1.field.f_smart_high_beam=0;
					break;
				case 0x2C:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_3_a_info.byte_2.field.f_wcm_status=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_2);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_3_a_info.byte_2.field.f_wcm_status=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_2);
					}
					CanTxInfo.acu_3_a_info.byte_2.field.f_wcm_status=0;
					break;
				case 0x2D:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_5_b_info.byte_2.field.f_autonomous_emergency_braking=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_5_b_info.byte_2.field.f_autonomous_emergency_braking=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					CanTxInfo.acu_5_b_info.byte_2.field.f_autonomous_emergency_braking=0;
					break;
				case 0x2E:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_a_info.byte_1.field.f_cruise_mode=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_a_info.byte_1.field.f_cruise_mode=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					CanTxInfo.acu_2_a_info.byte_1.field.f_cruise_mode=0;
					break;
				case 0x2F:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_5_b_info.byte_2.field.f_forward_collision_warning_status=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_5_b_info.byte_2.field.f_forward_collision_warning_status=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					CanTxInfo.acu_5_b_info.byte_2.field.f_forward_collision_warning_status=0;
					break;
				case 0x30:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_5_b_info.byte_2.field.f_forward_collision_warning_distance=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_5_b_info.byte_2.field.f_forward_collision_warning_distance=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_5_b_info.byte_2.field.f_forward_collision_warning_distance=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_5);
					}
					CanTxInfo.acu_5_b_info.byte_2.field.f_forward_collision_warning_distance=0;
					break;
				case 0x31:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_a_info.byte_0.field.f_lane_assist=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_a_info.byte_0.field.f_lane_assist=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					CanTxInfo.acu_2_a_info.byte_0.field.f_lane_assist=0;
					break;
				case 0x32:
					if(buffer[4]==0x01)
					{
						CanTxInfo.acu_2_a_info.byte_2.field.f_lane_assist_mode=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.acu_2_a_info.byte_2.field.f_lane_assist_mode=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.acu_2_a_info.byte_2.field.f_lane_assist_mode=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					CanTxInfo.acu_2_a_info.byte_2.field.f_lane_assist_mode=0;
					break;
				case 0x33:
					break;
				case 0x34:
					break;
				case 0x35:
					break;
				case 0x36:
					break;
				case 0x37:
					break;
				case 0x38:
					break;
				case 0x39:
					break;
				case 0x3A:
					break;
				case 0x3B:
					break;
				case 0x3C:
					break;	
				case 0x3D:
					break;
				case 0x3E:

					break;
				case 0x3F:
					break;
				case 0x40:
					if(buffer[4]==1)
					{
						CanTxInfo.acu_2_a_info.byte_5.field.f_dow_switch=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.acu_2_a_info.byte_5.field.f_dow_switch=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					CanTxInfo.acu_2_a_info.byte_5.field.f_dow_switch=0;
					break;
				case 0x41:
					if(buffer[4]==1)
					{
						CanTxInfo.acu_2_a_info.byte_5.field.f_rcta_switch=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.acu_2_a_info.byte_5.field.f_rcta_switch=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_1);
					}
					CanTxInfo.acu_2_a_info.byte_5.field.f_rcta_switch=0;
					break;
				case 0x42:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_3_a_info.byte_2.field.f_bsd_switch=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_2);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_3_a_info.byte_2.field.f_bsd_switch=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_2);
					}
					CanTxInfo.acu_3_a_info.byte_2.field.f_bsd_switch=0;
					break;
				case 0x43:
					break;
				case 0x44:
					break;
				case 0x45:
					CanTxInfo.acu_2_b_info.byte_5.field.f_time_mode=buffer[4];
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_3);
					break;
				case 0x46:
					break;
				case 0x47:
					CanTxInfo.acu_17_b_info.byte_3.field.f_rear_view_mirro_angle_save=buffer[4];
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_8);
					CanTxInfo.acu_17_b_info.byte_3.field.f_rear_view_mirro_angle_save=0;
					break;
				default:
					break;
			}
			break;
		case TRUMPCHI_TX_SETTING_CMD_3:
			switch(buffer[3])
			{
				case 0x01:
					break;
				case 0x02:
					break;
				case 0x03:
					break;
				case 0x04:
					break;
				case 0x05:
					break;
				case 0x06:
					break;
				case 0x07:
					break;
				case 0x08:
					break;
				case 0x09:
					
					break;
				case 0x0A:
					
					break;
				case 0x0B:
					
					break;
				case 0x0C:
					
					break;
				default:
					break;
			}
			break;
		case TRUMPCHI_TX_AIR_CMD:
			switch(buffer[3])
			{
				case 0x00:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_off=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_off=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_off=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x01:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_auto=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_auto=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_auto=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x02:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_mode=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_mode=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_mode=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x03:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_front_defrost=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_front_defrost=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_0.field.f_hvacf_front_defrost=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x04:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_rear_defrost=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_rear_defrost=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_rear_defrost=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x05:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_dual=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_dual=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_dual=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x06:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_ion=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_ion=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_ion=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x07:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_fan_inc=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_fan_inc=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_1.field.f_hvacf_fan_inc=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x08:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_fan_dec=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_fan_dec=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_fan_dec=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x09:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x0A:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_ac=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_ac=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_ac=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x0B:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_ac_max=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_ac_max=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_ac_max=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x0C:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_3.field.f_hvacf_temp_inc=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_3.field.f_hvacf_temp_inc=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_3.field.f_hvacf_temp_inc=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x0D:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_3.field.f_hvacf_temp_dec=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_3.field.f_hvacf_temp_dec=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_3.field.f_hvacf_temp_dec=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x0E:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_left_temp_inc=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_left_temp_inc=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_left_temp_inc=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x0F:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_left_temp_dec=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_left_temp_dec=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_left_temp_dec=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x10:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_right_temp_inc=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_right_temp_inc=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_right_temp_inc=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x11:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_right_temp_dec=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_right_temp_dec=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_6.field.f_hvacf_front_right_temp_dec=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x12:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_7.field.f_hvacf_triple_zone=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_7.field.f_hvacf_triple_zone=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_7.field.f_hvacf_triple_zone=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x13:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x14:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_2.field.f_hvacf_circulation=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x15:
					if(buffer[4]==0)
					{
						CanTxInfo.acu_16_b_info.byte_7.field.f_hvacf_rear=0;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					else if(buffer[4]==1)
					{
						CanTxInfo.acu_16_b_info.byte_7.field.f_hvacf_rear=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					CanTxInfo.acu_16_b_info.byte_7.field.f_hvacf_rear=0;
					TestTxTimer2=TEST_AIR_KEY_TIME;
					CanTxTimer1=T1S_1;
					break;
				case 0x16:
					if(buffer[4]==1)
					{
						CanTxInfo.acu_hvac_1_b_info.byte_1.field.f_hvacf_wind_speed=1;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.acu_hvac_1_b_info.byte_1.field.f_hvacf_wind_speed=2;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					}
					else if(buffer[4]==3)
					{
						CanTxInfo.acu_hvac_1_b_info.byte_1.field.f_hvacf_wind_speed=3;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					}
					else if(buffer[4]==4)
					{
						CanTxInfo.acu_hvac_1_b_info.byte_1.field.f_hvacf_wind_speed=4;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					}
					else if(buffer[4]==5)
					{
						CanTxInfo.acu_hvac_1_b_info.byte_1.field.f_hvacf_wind_speed=5;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					}
					else if(buffer[4]==6)
					{
						CanTxInfo.acu_hvac_1_b_info.byte_1.field.f_hvacf_wind_speed=6;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					}
					else if(buffer[4]==7)
					{
						CanTxInfo.acu_hvac_1_b_info.byte_1.field.f_hvacf_wind_speed=7;
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					}
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					CanTxInfo.acu_hvac_1_b_info.byte_1.field.f_hvacf_wind_speed=0;
					break;
				case 0x17:
					CanTxInfo.acu_hvac_1_b_info.byte_0.field.f_hvacf_driver_temp=buffer[4];
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					CanTxInfo.acu_hvac_1_b_info.byte_0.field.f_hvacf_driver_temp=0x1D;
					break;
				case 0x18:
					CanTxInfo.acu_hvac_1_b_info.byte_2.field.f_hvacf_psn_temp=buffer[4];
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
					CanTxInfo.acu_hvac_1_b_info.byte_2.field.f_hvacf_psn_temp=0x1D;
					break;
				default:
					break;
			}
			break;
		case TRUMPCHI_TX_SETTING_CMD_4:
			break;
		case TRUMPCHI_TX_REQUEST_CMD:
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_AIR_INFO);			
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_BASIC_INFO);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_REAR_RADAR);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_FRONT_RADAR);
			break;
		case TRUMPCHI_TX_AVM_CMD_1:
			{
				u16 temp;
				
				if(buffer[3]==1)
				{
					CanTxInfo.acu_1_a_info.byte_2.field.f_screen_touch_status=1;
				}
				else if(buffer[3]==2)
				{
					CanTxInfo.acu_1_a_info.byte_2.field.f_screen_touch_status=2;
				}
				
				temp=buffer[6];
				temp<<=8;
				temp|=buffer[7];
				temp&=0x0FFF;
				CanTxInfo.acu_1_a_info.byte_4.field.f_y_1=temp&0x000F;
				CanTxInfo.acu_1_a_info.byte_3.field.f_y=((temp&0x0FF0)>>4);
				
				temp=buffer[4];
				temp<<=8;
				temp|=buffer[5];
				temp&=0x0FFF;
				CanTxInfo.acu_1_a_info.byte_4.field.f_x_1=((temp&0x0F00)>>8);
				CanTxInfo.acu_1_a_info.byte_5.field.f_x=(temp&0x00FF);
				Trumpchi_PostMessage(CAN_POST_MSG_ACU_0);
				Trumpchi_PostMessage(CAN_POST_MSG_ACU_0);
				Trumpchi_PostMessage(CAN_POST_MSG_ACU_0);
				CanTxInfo.acu_1_a_info.byte_2.field.f_screen_touch_status=0;
				CanTxInfo.acu_1_a_info.byte_3.byte=0x2D;
				CanTxInfo.acu_1_a_info.byte_4.byte=0x05;
				CanTxInfo.acu_1_a_info.byte_5.byte=0x00;
				if(buffer[3]==1)
				{
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_0);
				}
				else if(buffer[3]==2)
				{
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_0);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_0);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_0);
				}
			}
			break;
		default:
			break;
	}
}

void Trumpchi_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case TRUMPCHI_RX_AIR_INFO:
			buffer[2]=0x05;
			buffer[3]=0;
			buffer[4]=CanRxInfo.air_info.byte_1.byte;
			buffer[5]=CanRxInfo.air_info.byte_2.byte;
			buffer[6]=CanRxInfo.air_info.byte_3.byte;
			buffer[7]=CanRxInfo.air_info.byte_4.byte;
			break;
		case TRUMPCHI_RX_BASIC_INFO:
			buffer[2]=0x02;
			buffer[3]=CanRxInfo.base_info.byte_0.byte;
			buffer[4]=CanRxInfo.base_info.byte_1.byte;
			break;
		case TRUMPCHI_RX_REAR_RADAR:
			buffer[2]=5;
			buffer[3]=CanRxInfo.rear_radar_info.byte_0.byte;
			buffer[4]=CanRxInfo.rear_radar_info.byte_1.byte;
			buffer[5]=CanRxInfo.rear_radar_info.byte_2.byte;
			buffer[6]=CanRxInfo.rear_radar_info.byte_3.byte;
			buffer[7]=CanRxInfo.rear_radar_info.byte_4.byte;
			break;		
		case TRUMPCHI_RX_FRONT_RADAR:
			buffer[2]=2;
			buffer[3]=CanRxInfo.front_radar_info.byte_0.byte;
			buffer[4]=CanRxInfo.front_radar_info.byte_1.byte;
			break;
		case TRUMPCHI_RX_EPS_INFO:
			buffer[2]=2;
			buffer[3]=CanRxInfo.eps_info.byte_0.byte;
			buffer[4]=CanRxInfo.eps_info.byte_1.byte;
			break;
		case TRUMPCHI_RX_SETTING_1:
			buffer[2]=0x48;
			buffer[3]=0;
			buffer[4]=0;
			buffer[5]=CanRxInfo.air_canditioning_info.byte_2.filed.f_compressor_status;
			buffer[6]=CanRxInfo.air_canditioning_info.byte_0.filed.f_frs_rec_auto_mode;
			buffer[7]=CanRxInfo.air_canditioning_info.byte_0.filed.f_comfort_curve;
			buffer[8]=CanRxInfo.seat_setting_info.f_front_left_seat_heating_ventilating_auto_mode;
			buffer[9]=CanRxInfo.seat_setting_info.f_front_right_seat_heating_ventilating_auto_mode;
			buffer[10]=CanRxInfo.setting_info.byte_7.field.f_speed_warning;
			buffer[11]=CanRxInfo.setting_info.byte_7.field.f_warning_sound_volume;
			buffer[12]=CanRxInfo.setting_info.byte_8.field.f_time_remote_electricity_on;
			buffer[13]=CanRxInfo.setting_info.byte_9.field.f_time_remote_power_on;
			buffer[14]=CanRxInfo.setting_info.byte_5.field.f_steering_mode;
			buffer[15]=CanRxInfo.setting_info.byte_0.field.f_remote_unlock;
			buffer[16]=0;
			buffer[17]=CanRxInfo.setting_info.byte_0.field.f_auto_door_unlock;
			buffer[18]=CanRxInfo.setting_info.byte_2.field.f_remote_control_window_sunroof;
			buffer[19]=CanRxInfo.setting_info.byte_10.field.f_wiper_maintanence;
			buffer[20]=CanRxInfo.setting_info.byte_10.field.f_auto_rear_wipe_function;
			buffer[21]=CanRxInfo.setting_info.byte_1.field.f_light_to_home;
			buffer[22]=CanRxInfo.setting_info.byte_1.field.f_fog_light_for_turning;
			buffer[23]=CanRxInfo.setting_info.byte_4.field.f_head_light_for_daytime;
			buffer[24]=CanRxInfo.setting_info.byte_6.field.f_auto_light_sensitivity;
			buffer[25]=0;
			buffer[26]=0;
			buffer[27]=CanRxInfo.air_info.byte_1.field.f_ION;
			buffer[28]=CanRxInfo.seat_setting_info.f_seat_welcome_function;
			buffer[29]=CanRxInfo.seat_setting_info.f_key_recognition;
			buffer[30]=CanRxInfo.setting_info.byte_2.field.f_outside_rear_view_mirro_auto_floding;
			buffer[31]=CanRxInfo.setting_info.byte_2.field.f_lock_unlock_whistle_remind;
			buffer[32]=CanRxInfo.setting_info.byte_0.field.f_automatically_lock;
			buffer[33]=CanRxInfo.setting_info.byte_0.field.f_automatically_unlock;
			buffer[34]=CanRxInfo.setting_info.byte_2.field.f_rear_view_mirro_flip_position_setting;
			buffer[35]=CanRxInfo.setting_info.byte_3.field.f_manual_rear_view_mirro_flip_of_reversing;
			buffer[36]=CanRxInfo.setting_info.byte_6.field.f_smart_welcome_light;
			buffer[37]=0;
			buffer[38]=0;
			buffer[39]=CanRxInfo.setting_info.byte_6.field.f_interior_ambient_light;	
			buffer[40]=0;
			buffer[41]=CanRxInfo.air_canditioning_info.byte_0.filed.f_fan_speed_of_auto_mode;
			buffer[42]=CanRxInfo.setting_info.byte_1.field.f_smart_trunk;
			buffer[43]=CanRxInfo.setting_info.byte_9.field.f_auto_wiper;
			buffer[44]=0;
			buffer[45]=0;
			buffer[46]=CanRxInfo.setting_info.byte_5.field.f_smart_high_beam;
			buffer[47]=CanRxInfo.setting_info.byte_3.field.f_wireless_charge;
			buffer[48]=CanRxInfo.setting_info.byte_5.field.f_autonomous_emergency_braking;
			buffer[49]=CanRxInfo.setting_info.byte_4.field.f_cruise_mode;
			buffer[50]=CanRxInfo.setting_info.byte_4.field.f_forward_collision_warning;
			buffer[51]=CanRxInfo.setting_info.byte_5.field.f_forward_collision_warning_distance;
			buffer[52]=CanRxInfo.setting_info.byte_10.field.f_lane_assist;
			buffer[53]=CanRxInfo.setting_info.byte_4.field.f_lane_assist_mode;
			buffer[54]=0;
			buffer[55]=0;
			buffer[56]=0;
			buffer[57]=0;
			buffer[58]=0;
			buffer[59]=0;
			buffer[60]=0;
			buffer[61]=0;
			buffer[62]=0;
			buffer[63]=0;
			buffer[64]=CanRxInfo.setting_info.byte_6.field.f_forward_collision_warning_button;
			buffer[65]=0;
			buffer[66]=CanRxInfo.setting_info.byte_8.field.f_transport_mode;
			buffer[67]=0;
			buffer[68]=0;
			buffer[69]=CanRxInfo.setting_info.byte_3.field.f_blind_spot_detection;
			buffer[70]=0;
			buffer[71]=0;
			buffer[72]=0;
			buffer[73]=CanRxInfo.setting_info.byte_3.field.f_wireless_charge_state;
			buffer[74]=CanRxInfo.setting_info.byte_11.field.f_instantaneous_speed;
			break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=Trumpchi_HEAD_CODE;
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

void Trumpchi_MainPro(void)
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
	if(CanMainTimer2)
	{
		CanMainTimer2--;
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
	
#if 0
	if(CanErrorTimer)
	{
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

	Trumpchi_Rx_Message();
	Trumpchi_Rx_Message_2();
	if(F_CAN_INIT)
	{
		CAN1_Transmit();
		TestTxTimer++;
		if(TestTxTimer>10)
		{
			TestTxTimer=0;
			CAN2_Transmit();
		}
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
			CAN2_ClearTxMessage();
			F_CAN_SLEEP=0;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T60S_1;
			CanTxTimer=0;
			CanTxInfo.acu_16_b_info.byte_0.byte=0xAA;
			CanTxInfo.acu_16_b_info.byte_1.byte=0xAA;
			CanTxInfo.acu_16_b_info.byte_2.byte=0xAA;
			CanTxInfo.acu_16_b_info.byte_3.byte=0x0A;
			CanTxInfo.acu_16_b_info.reserved_4=0x00;
			CanTxInfo.acu_16_b_info.reserved_5=0x00;
			CanTxInfo.acu_16_b_info.byte_6.byte=0xAA;
			CanTxInfo.acu_16_b_info.byte_7.byte=0xAA;
			CanTxInfo.acu_2_b_info.byte_4.field.f_speed_warning=0x1F;
			CanTxInfo.acu_hvac_1_b_info.byte_0.field.f_hvacf_driver_temp=0x1D;
			CanTxInfo.acu_hvac_1_b_info.byte_2.field.f_hvacf_psn_temp=0x1D;
			CanTxInfo.acu_hvac_1_b_info.byte_0.field.f_reserved=0x07;
			CanTxInfo.acu_17_b_info.byte_1.field.f_ial_color=0x00;
			CanTxInfo.acu_2_b_info.byte_0.field.f_compressor_status=0x00;
			CanTxInfo.acu_2_b_info.byte_4.field.f_speed_warning=0x1F;
			CanTxInfo.acu_4_b_info.byte_0.field.f_high_speed_auto_lock=0x00;
			CanTxInfo.acu_4_b_info.byte_2.field.f_wiper_maintanence=0x00;
			CanTxInfo.acu_4_b_info.byte_2.field.f_auto_rear_wipe_function=0x00;
			CanTxInfo.acu_4_b_info.byte_1.field.f_light_to_home=0x00;
			CanTxInfo.acu_4_b_info.byte_0.field.f_fog_light_for_turning=0x00;
			CanTxInfo.acu_4_b_info.byte_2.field.f_head_light_for_daytime=0x00;
			CanTxInfo.acu_2_b_info.byte_0.field.f_ion_mode=0x00;
			CanTxInfo.acu_2_b_info.byte_3.field.f_air_quality_sensor=0x00;
			CanTxInfo.acu_5_b_info.byte_2.field.f_autonomous_emergency_braking=0x00;
			CanTxInfo.acu_2_a_info.byte_1.field.f_cruise_mode=0x00;
			CanTxInfo.acu_2_a_info.byte_0.field.f_lane_assist=0x00;
			CanTxInfo.acu_2_a_info.byte_2.field.f_lane_assist_mode=0x00;
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
					Trumpchi_SettingDataCompare();
					if(CanMainTimer2==0)
					{
						if(CanGeneralCtrlFlag.field.reverse_on_off)
						{
							CanMainTimer2=T500MS_1;
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_REAR_RADAR);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_FRONT_RADAR);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_EPS_INFO);
						}
						else
						{
							CanMainTimer2=T1S_1;
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_REAR_RADAR);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_FRONT_RADAR);
						}
					}
					if(CanMainTimer==0)
					{
						CanMainTimer=T5S_1;
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_BASIC_INFO);
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_AIR_INFO);
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,TRUMPCHI_RX_SETTING_1);
					}
				}
				if(TestTxTimer2)
				{
					TestTxTimer2--;
					if(TestTxTimer2==0)
					{
						Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
					}
				}
				if(CanTxTimer==0)
				{
					CanTxTimer=T200MS_1;
					
					CanTxInfo.acu_10_b_info.byte_0.field.f_time_year=RTC_TimeInfo.year;
					CanTxInfo.acu_10_b_info.byte_1.field.f_time_month=RTC_TimeInfo.month;
					CanTxInfo.acu_10_b_info.byte_1.field.f_time_day_1=((RTC_TimeInfo.day&0x01F)>>1);
					CanTxInfo.acu_10_b_info.byte_2.field.f_time_day_2=(RTC_TimeInfo.day&0x01);
					CanTxInfo.acu_10_b_info.byte_2.field.f_time_hour=(RTC_TimeInfo.hours);
					CanTxInfo.acu_10_b_info.byte_2.field.f_time_minute_1=((RTC_TimeInfo.minutes&0x3F)>>4);
					CanTxInfo.acu_10_b_info.byte_3.field.f_time_minute_2=(RTC_TimeInfo.minutes&0x0F);
					CanTxInfo.acu_10_b_info.byte_3.field.f_time_second_1=((RTC_TimeInfo.seconds&0x3F)>>2);
					CanTxInfo.acu_10_b_info.byte_4.field.f_time_second_2=(RTC_TimeInfo.seconds&0x03);
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_6);
				}
				if(CanTxTimer1==0)
				{
					CanTxTimer1=T200MS_1;
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_7);
				}
				if(CanTxTimer2==0)
				{
					CanTxTimer2=T200MS_1;
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_9);
				}
				if(CanTxTimer3==0)
				{
					CanTxTimer3=T100MS_1;
					Trumpchi_PostMessage(CAN_POST_MSG_ACU_10);
				}
				Trumpchi_CanKeyTimer();
			}
			break;
		case CAN_MAIN_SLEEP_CFG:
			CAN1_ClearRxMessage();
			CAN2_ClearRxMessage();
			CAN_IC_STANDBY_ON;
			CAN2_IC_STANDBY_ON;
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
				CAN2_IC_STANDBY_OFF;
				F_CAN_SLEEP=0;
				CanMainState=CAN_MAIN_INIT;
			}
			break;
		default:
			break;
	}
}


#endif

