#include "public.h"

#if CAN_FUN_HYUNDAI_BN7i==1||CAN_FUN_HYUNDAI_CRETA==1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
CAN_RX_INFO CanRxInfo;
CAN_TX_INFO CanTxInfo;
u32 CanMainTimer;
u32 CanNoDataTimer;
u16 Reverse_Timer;
u16 CanTxEpsTimer;
u16 CanTxRadarTimer;
u16 CanTxGearTimer;

u16 CanTxBaseTimer;
u16 CanTxBatteryTimer;
u16 CanTxEcallTimer;
u16 CanTxMicTimer;

u32 CanTxStaTimer=T300S_1;
u32 extend_camera_use_flag=1;
u32 DRVM_KeyPressedSta;
u32 DRVM_KeyPressedBak;
u32 DRVM_KeyPressedFlag;// DRVM button had pressed
u32 ReverseGearTimer; // for gear quickly switch
u32 gear_value;
u32 gear_bak;
u32 Reverse_flag;
u16 gear_timer;
u8 sta_flag;
u8 e_warn;
u8 Mic_flag=1;
u8 hu_sta;
u8 e_sta=1;
u8 FLAG_Panel_LED=0;
#if TEST_CAN_FUN==1
u16 CanTxTestTimer;
int test_time;
u32 test;
u32 test1;
u32 test2;
u32 light_temp;
u32 light_printf;
#endif




u8 Hyundai_BN7i_TxRvmFlag;
u8 Hyundai_BN7i_TxRvmTimer;
u8 Hyundai_BN7i_TxRvmCounter;
void Hyundai_BN7i_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8]={0};
	switch(index)
	{
		case CAN_POST_MSG_HU_RVM_E_00:
		{
			data[0]=CanTxInfo.hu_rvm_e_00.byte_0.byte;
			data[1]=CanTxInfo.hu_rvm_e_00.byte_1.byte;
			CAN1_TxFrame(CAN_ID_HU_RVM_E_00,data,8);
		}
		break;
			
		case CAN_POST_MSG_HU_ECALL_W_00:
		{	data[0]=CanTxInfo.hu_ecall_e_00.byte_0.field.f_warning;
			CAN1_TxFrame(CAN_ID_ECALL_HU_E_01,data,1);
		}
		break;
		
		case CAN_POST_MSG_HU_ECALL_S_00:
		{
			data[0]=CanTxInfo.hu_ecall_e_00.byte_0.field.f_mode;
			CAN1_TxFrame(CAN_ID_HU_TMU_E_01,data,1);
		}
		break;

		case CAN_POST_MSG_HU_ECALL_V_00:
		{
			data[0]=CanTxInfo.hu_ecall_e_00.byte_2.byte;
			CAN1_TxFrame(CAN_POST_HU_ECALL_P_00,data,1);
		}
		break;

		case CAN_POST_MSG_HU_ECALL_C_00:
		{
			data[0]=CanTxInfo.hu_ecall_e_00.byte_1.byte;
			CAN1_TxFrame(CAN_POST_HU_Car_PE_01,data,1);
		}
		break;

		default:
			break;
	}
}

void Hyundai_BN7i_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			
			case CAN_ID_ECALL_HU_E_01:
			{
				CanRxInfo.ecall_info.byte_2.field.ecall_fail=(message.Data[0]&0x03);				
			}
			break;
			
			
			case CAN_ID_ECALL_CLU_PE_01:
			{
				CanRxInfo.ecall_info.byte_1.field.ecall_warning=(message.Data[0]&0x03);				
			}
			break;
			
			case CAN_ID_TMU_HU_E_01:
			{
				CanRxInfo.ecall_info.byte_0.field.ecall_mode=((message.Data[3]&0x1C)>>2);
				if(CanRxInfo.ecall_info.byte_0.field.ecall_mode==1||CanRxInfo.ecall_info.byte_0.field.ecall_mode==3)
				{
					hu_sta=1;
				}
			}				
			break;

			case CAN_ID_MKBD_HU_E_02:
			{
				CanRxInfo.knob_info.vol_knob_value=message.Data[0];
				CanRxInfo.knob_info.vol_knob_click=(message.Data[1]&0x03);
				CanRxInfo.knob_info.tune_knob_value=message.Data[2];
				CanRxInfo.knob_info.tune_knob_click=(message.Data[3]&0x03);
				CanRxInfo.knob_info.reset_key=(message.Data[4]&0x03);

				if(CanRxInfo.knob_info.vol_knob_value!=CanRxInfo.knob_info_bak.vol_knob_value)
				{
					if((CanRxInfo.knob_info.vol_knob_value&0x80)==0
						&&(CanRxInfo.knob_info_bak.vol_knob_value&0x80)==0)
					{
						if(CanRxInfo.knob_info.vol_knob_value>CanRxInfo.knob_info_bak.vol_knob_value)
						{
							PostKeyCode(UICC_VOLUME_UP,PANEL);
						}
						else
						{
							PostKeyCode(UICC_VOLUME_DOWN,PANEL);
						}
					}
					else if((CanRxInfo.knob_info.vol_knob_value&0x80)
						&&(CanRxInfo.knob_info_bak.vol_knob_value&0x80))
					{
						if(CanRxInfo.knob_info.vol_knob_value>CanRxInfo.knob_info_bak.vol_knob_value)
						{
							PostKeyCode(UICC_VOLUME_DOWN,PANEL);
						}
						else
						{
							PostKeyCode(UICC_VOLUME_UP,PANEL);
						}
					}
					else if((CanRxInfo.knob_info.vol_knob_value&0x80)
						&&(CanRxInfo.knob_info_bak.vol_knob_value&0x80)==0)
					{
						PostKeyCode(UICC_VOLUME_DOWN,PANEL);
					}
					else if((CanRxInfo.knob_info.vol_knob_value&0x80)==0
						&&(CanRxInfo.knob_info_bak.vol_knob_value&0x80))
					{
						PostKeyCode(UICC_VOLUME_UP,PANEL);
					}
					CanRxInfo.knob_info_bak.vol_knob_value=CanRxInfo.knob_info.vol_knob_value;
				}
				
				if(CanRxInfo.knob_info.vol_knob_click!=CanRxInfo.knob_info_bak.vol_knob_click)
				{
					if(CanRxInfo.knob_info.vol_knob_click==0x01)
					{
						PostKeyCode(UICC_POWER_MUTE,PANEL);
					}
					else if(CanRxInfo.knob_info.vol_knob_click==0x02)
					{
						PostKeyCode(SYSTEM_POWER_OFF_KEY,PANEL);
					}
					CanRxInfo.knob_info_bak.vol_knob_click=CanRxInfo.knob_info.vol_knob_click;
				}

				if(CanRxInfo.knob_info.tune_knob_value!=CanRxInfo.knob_info_bak.tune_knob_value)
				{
					if((CanRxInfo.knob_info.tune_knob_value&0x80)==0
						&&(CanRxInfo.knob_info_bak.tune_knob_value&0x80)==0)
					{
						if(CanRxInfo.knob_info.tune_knob_value>CanRxInfo.knob_info_bak.tune_knob_value)
						{
							PostKeyCode(UICC_SMART_CW,PANEL);
						}
						else
						{
							PostKeyCode(UICC_SMART_CCW,PANEL);
						}
					}
					else if((CanRxInfo.knob_info.tune_knob_value&0x80)
						&&(CanRxInfo.knob_info_bak.tune_knob_value&0x80))
					{
						if(CanRxInfo.knob_info.tune_knob_value>CanRxInfo.knob_info_bak.tune_knob_value)
						{
							PostKeyCode(UICC_SMART_CCW,PANEL);
						}
						else
						{
							PostKeyCode(UICC_SMART_CW,PANEL);
						}
					}
					else if((CanRxInfo.knob_info.tune_knob_value&0x80)
						&&(CanRxInfo.knob_info_bak.tune_knob_value&0x80)==0)
					{
						PostKeyCode(UICC_SMART_CCW,PANEL);
					}
					else if((CanRxInfo.knob_info.tune_knob_value&0x80)==0
						&&(CanRxInfo.knob_info_bak.tune_knob_value&0x80))
					{
						PostKeyCode(UICC_SMART_CW,PANEL);
					}
					CanRxInfo.knob_info_bak.tune_knob_value=CanRxInfo.knob_info.tune_knob_value;
				}

				if(CanRxInfo.knob_info.tune_knob_click!=CanRxInfo.knob_info_bak.tune_knob_click)
				{
					if(CanRxInfo.knob_info.tune_knob_click==0x01)
					{
						PostKeyCode(UICC_CLOCK,PANEL);
					}
					else if(CanRxInfo.knob_info.tune_knob_click==0x02)
					{
						PostKeyCode(UICC_TFT_STANDBY,PANEL);
					}
					CanRxInfo.knob_info_bak.tune_knob_click=CanRxInfo.knob_info.tune_knob_click;
				}

				if(CanRxInfo.knob_info.reset_key!=CanRxInfo.knob_info_bak.reset_key)
				{
					if(CanRxInfo.knob_info.reset_key==0x01)
					{
						SystemReset();
					}
					CanRxInfo.knob_info_bak.reset_key=CanRxInfo.knob_info.reset_key;
				}
			}
			break;
			
			case CAN_ID_MKBD_HU_E_03:
			{
				CanRxInfo.panel_key_info.byte_0.field.f_map_key=(message.Data[0]&0x03);
				CanRxInfo.panel_key_info.byte_0.field.f_navi_key=((message.Data[0]&0x0C)>>2);
				CanRxInfo.panel_key_info.byte_0.field.f_radio_key=((message.Data[0]&0x30)>>4);
				CanRxInfo.panel_key_info.byte_0.field.f_media_key=((message.Data[0]&0xC0)>>6);
				CanRxInfo.panel_key_info.byte_1.field.f_skipf_key=(message.Data[1]&0x03);
				CanRxInfo.panel_key_info.byte_1.field.f_skipb_key=((message.Data[1]&0x0C)>>2);
				CanRxInfo.panel_key_info.byte_1.field.f_custom_key=((message.Data[1]&0x30)>>4);
				CanRxInfo.panel_key_info.byte_1.field.f_setup_key=((message.Data[1]&0xC0)>>6);

				if(CanRxInfo.panel_key_info.byte_0.field.f_map_key!=CanRxInfo.panel_key_info_bak.byte_0.field.f_map_key)
				{
					if(CanRxInfo.panel_key_info.byte_0.field.f_map_key==0x01)
					{
					}
					else if(CanRxInfo.panel_key_info.byte_0.field.f_map_key==0x02)
					{
					}
					CanRxInfo.panel_key_info_bak.byte_0.field.f_map_key=CanRxInfo.panel_key_info.byte_0.field.f_map_key;
				}

				if(CanRxInfo.panel_key_info.byte_0.field.f_navi_key!=CanRxInfo.panel_key_info_bak.byte_0.field.f_navi_key)
				{
					if(CanRxInfo.panel_key_info.byte_0.field.f_navi_key==0x01)
					{
						PostKeyCode(UICC_NAVI,PANEL);
					}
					else if(CanRxInfo.panel_key_info.byte_0.field.f_navi_key==0x02)
					{
					}
					CanRxInfo.panel_key_info_bak.byte_0.field.f_navi_key=CanRxInfo.panel_key_info.byte_0.field.f_navi_key;
				}

				if(CanRxInfo.panel_key_info.byte_0.field.f_radio_key!=CanRxInfo.panel_key_info_bak.byte_0.field.f_radio_key)
				{
					if(CanRxInfo.panel_key_info.byte_0.field.f_radio_key==0x01)
					{
						PostKeyCode(UICC_TUNER,PANEL);
					}
					else if(CanRxInfo.panel_key_info.byte_0.field.f_radio_key==0x02)
					{
					}
					CanRxInfo.panel_key_info_bak.byte_0.field.f_radio_key=CanRxInfo.panel_key_info.byte_0.field.f_radio_key;
				}

				if(CanRxInfo.panel_key_info.byte_0.field.f_media_key!=CanRxInfo.panel_key_info_bak.byte_0.field.f_media_key)
				{
					if(CanRxInfo.panel_key_info.byte_0.field.f_media_key==0x01)
					{
						PostKeyCode(UICC_MEDIA,PANEL);
					}
					else if(CanRxInfo.panel_key_info.byte_0.field.f_media_key==0x02)
					{
					}
					CanRxInfo.panel_key_info_bak.byte_0.field.f_media_key=CanRxInfo.panel_key_info.byte_0.field.f_media_key;
				}

				if(CanRxInfo.panel_key_info.byte_1.field.f_skipf_key!=CanRxInfo.panel_key_info_bak.byte_1.field.f_skipf_key)
				{
					if(CanRxInfo.panel_key_info.byte_1.field.f_skipf_key==0x01)
					{
						PostKeyCode(UICC_SKIPF,PANEL);
					}
					else if(CanRxInfo.panel_key_info.byte_1.field.f_skipf_key==0x02)
					{
						PostKeyCode(UICC_NEXT_LONG,PANEL);
					}
					CanRxInfo.panel_key_info_bak.byte_1.field.f_skipf_key=CanRxInfo.panel_key_info.byte_1.field.f_skipf_key;
				}

				if(CanRxInfo.panel_key_info.byte_1.field.f_skipb_key!=CanRxInfo.panel_key_info_bak.byte_1.field.f_skipb_key)
				{
					if(CanRxInfo.panel_key_info.byte_1.field.f_skipb_key==0x01)
					{
						PostKeyCode(UICC_SKIPB,PANEL);
					}
					else if(CanRxInfo.panel_key_info.byte_1.field.f_skipb_key==0x02)
					{
						PostKeyCode(UICC_PREV_LONG,PANEL);
					}
					CanRxInfo.panel_key_info_bak.byte_1.field.f_skipb_key=CanRxInfo.panel_key_info.byte_1.field.f_skipb_key;
				}
				
				if(CanRxInfo.panel_key_info.byte_1.field.f_custom_key!=CanRxInfo.panel_key_info_bak.byte_1.field.f_custom_key)
				{
					if(CanRxInfo.panel_key_info.byte_1.field.f_custom_key==0x01)
					{
					}
					else if(CanRxInfo.panel_key_info.byte_1.field.f_custom_key==0x02)
					{
					}
					CanRxInfo.panel_key_info_bak.byte_1.field.f_custom_key=CanRxInfo.panel_key_info.byte_1.field.f_custom_key;
				}

				if(CanRxInfo.panel_key_info.byte_1.field.f_setup_key!=CanRxInfo.panel_key_info_bak.byte_1.field.f_setup_key)
				{
					if(CanRxInfo.panel_key_info.byte_1.field.f_setup_key==0x01)
					{
						PostKeyCode(UICC_SETUP,PANEL);
					}
					else if(CanRxInfo.panel_key_info.byte_1.field.f_setup_key==0x02)
					{
						PostKeyCode(UICC_SETUP_LONG,PANEL);
					}
					CanRxInfo.panel_key_info_bak.byte_1.field.f_setup_key=CanRxInfo.panel_key_info.byte_1.field.f_setup_key;
				}
			}
			break;

			case CAN_ID_GW_CLU_PE:
			{
				//CanRxInfo.gear_info.byte_1.field.f_tgs_r_mt=((message.Data[1]&0x40)>>6);//message.Data[1]&0xC0
				if(message.Data[1]==0x40||message.Data[1]==0x50||message.Data[1]==0x70)
				{
					CanRxInfo.gear_info.byte_1.field.f_tgs_r_mt=1;
				}
				else
				{
					CanRxInfo.gear_info.byte_1.field.f_tgs_r_mt=0;
				}
			}				
			break;

			case CAN_ID_GW_HU_PE_01:
			{
				if(((message.Data[6]&0xC0)>>6)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_hood=1;
				}
				else if(((message.Data[6]&0xC0)>>6)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_hood=0;
				}
			}
			break;
			
			case CAN_ID_GW_CHASSIS_PE_1:
			{
				CanRxInfo.gear_info.byte_0.field.f_tgs_gear_at=(message.Data[0]&0x0F);
				CanRxInfo.gear_info.byte_0.field.f_gear=((message.Data[1]&0x78)>>3);
				CanRxInfo.gear_info.byte_1.field.f_parking_brake=((message.Data[0]&0x30)>>4);
				CanRxInfo.gear_info.byte_1.field.f_ems_r_mt=((message.Data[6]&0x0C)>>2);
				CanRxInfo.gear_info.byte_1.field.f_parking_brake_epb=((message.Data[6]&0xE0)>>5);
				CanRxInfo.battery_info.byte_1.field.f_battery_eng=(message.Data[2]&0x07);
			}	
			break;
			
			case CAN_ID_GW_CAR_INFO_PE:
			{
				CanRxInfo.base_info.byte_2.field.f_av_tail=(message.Data[0]&0x03);
			}
			break;

			case CAN_ID_GW_HU_PE_06:
			{
				if((message.Data[0]&0x03)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_driver_door=1;
				}
				else if((message.Data[0]&0x03)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_driver_door=0;
				}
				
				if(((message.Data[0]&0x0C)>>2)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_passenger_door=1;
				}
				else if(((message.Data[0]&0x0C)>>2)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_passenger_door=0;
				}

				if(((message.Data[0]&0x30)>>4)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_lr_door=1;
				}
				else if(((message.Data[0]&0x30)>>4)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_lr_door=0;
				}

				if(((message.Data[0]&0xC0)>>6)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_rr_door=1;
				}
				else if(((message.Data[0]&0xC0)>>6)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_rr_door=0;
				}

				if((message.Data[2]&0x03)==1)
				{
					CanRxInfo.base_info.byte_1.field.f_trunk=1;
				}
				else if((message.Data[2]&0x03)==0)
				{
					CanRxInfo.base_info.byte_1.field.f_trunk=0;
				}
				
				if(((message.Data[2]&0xC0)>>6)==1)
				{
					CanRxInfo.base_info.byte_2.field.f_auto_light_sensor_state=1;
				}
				else
				{
					CanRxInfo.base_info.byte_2.field.f_auto_light_sensor_state=0;
				}
				if((message.Data[3]&0x03)==1
					||((message.Data[3]&0x30)>>4)==1
					||((message.Data[3]&0xC0)>>6)==1)
				{
					CanRxInfo.base_info.byte_0.field.f_illumi=1;
				}
				else
				{
					CanRxInfo.base_info.byte_0.field.f_illumi=0;
				}
			}
			break;
			
			case CAN_ID_GW_HU_PE_07:
			{
				CanRxInfo.radar_info.front_left=(message.Data[0]&0x07);
				CanRxInfo.radar_info.front_right=((message.Data[0]&0x38)>>3);
				CanRxInfo.radar_info.front_center=(message.Data[1]&0x07);
				CanRxInfo.radar_info.rear_center=((message.Data[1]&0x38)>>3);
				CanRxInfo.radar_info.rear_left=(message.Data[2]&0x07);
				CanRxInfo.radar_info.rear_right=((message.Data[2]&0x38)>>3);
			}
			break;

			case CAN_ID_DATC_P_02:
				break;
		
			case CAN_ID_GW_CLU_P:
			{
				CanRxInfo.driving_info.vehicle_speed=message.Data[0];
				CanRxInfo.driving_info.odometer=message.Data[1];
				CanRxInfo.driving_info.odometer<<=8;
				CanRxInfo.driving_info.odometer|=message.Data[2];
				CanRxInfo.driving_info.odometer<<=8;
				CanRxInfo.driving_info.odometer|=message.Data[3];
				CanRxInfo.driving_info.cluster_disp_speed_unit=((message.Data[5]&0x60)>>5);
				CanRxInfo.driving_info.cluster_disp_speed=(message.Data[5]&0x01);
				CanRxInfo.driving_info.cluster_disp_speed<<=8;
				CanRxInfo.driving_info.cluster_disp_speed+=message.Data[6];
				CanRxInfo.driving_info.cluster_speed=message.Data[4];
				CanRxInfo.driving_info.cluster_speed<<=1;
				CanRxInfo.driving_info.cluster_speed|=((message.Data[5]&0x80)>>7);
			}
			break;
			
			case CAN_ID_GW_HU_P_00:
			{
				CanRxInfo.eps_info.swa_msb=message.Data[0];
				CanRxInfo.eps_info.swa_lsb=message.Data[1];
			}
			break;

			case CAN_ID_GW_USM_PE_04:
			{
				CanRxInfo.mood_lamp_info.red_value=message.Data[0];
				CanRxInfo.mood_lamp_info.red_value<<=2;
				CanRxInfo.mood_lamp_info.red_value|=((message.Data[1]&0xC0)>>6);
				CanRxInfo.mood_lamp_info.green_value=(message.Data[1]&0x3F);
				CanRxInfo.mood_lamp_info.green_value<<=4;
				CanRxInfo.mood_lamp_info.green_value|=((message.Data[2]&0xF0)>>4);
				CanRxInfo.mood_lamp_info.green_value=(message.Data[2]&0x0F);
				CanRxInfo.mood_lamp_info.green_value<<=6;
				CanRxInfo.mood_lamp_info.green_value|=((message.Data[3]&0xFC)>>2);
				CanRxInfo.mood_lamp_info.brightness=(message.Data[4]&0x0F);
			}
			break;
			
			case CAN_ID_GW_RVM_PE_00:
			{
				CanRxInfo.avm_info.rvm_mode=(message.Data[0]&0x0F);
				CanRxInfo.avm_info.rvm_type=((message.Data[0]&0xF0)>>4);
				CanRxInfo.avm_info.rvm_guide_line=((message.Data[1]&0xC0)>>6);
				CanRxInfo.avm_info.rvm_state=((message.Data[3]&0x1C)>>2);
				CanRxInfo.avm_info.rvm_drv_state=(message.Data[3]&0x03);
				
				if(Reverse_flag==0)//Reverse camera open,can not open DRVM .
				{
					if(CanRxInfo.avm_info.rvm_drv_state==2||CanRxInfo.avm_info.rvm_drv_state==1)
					{
						DRVM_KeyPressedFlag=1;
					}
					else
					{
						DRVM_KeyPressedFlag=0;
					}
				}
				else
				{
					DRVM_KeyPressedFlag=0;
				}				
				
				if(0==strcmp_equal(&CanRxInfo.avm_info.rvm_mode,&CanRxInfo.avm_info_bak.rvm_mode,sizeof(CAN_AVM_INFO)))
				{
					CanRxInfo.avm_info_bak=CanRxInfo.avm_info;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_AVM_INO);
				}
			}
			break;
			
			default:
				break;
		}
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
		CanNoDataTimer=T5S_1;
		CAN1_ClearErrorTimer();
	}
}

void Hyundai_BN7i_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id=buffer[1];
	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	switch(cmd_id)
	{
		case HYUNDAI_BN7i_TX_AVM_CMD:
		{
			switch(buffer[3])
			{
				case AVM_CTRL_CMD_OFF:
				{
					CanTxInfo.hu_rvm_e_00.byte_0.field.f_camera_off=0x01;
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_RVM_E_00);
					Hyundai_BN7i_TxRvmFlag=1;
					Hyundai_BN7i_TxRvmCounter=0;
					//CanRxInfo.base_info.byte_0.field.f_reverse=0;
					CanGeneralCtrlFlag.field.reverse_on_off=0;
				}
				break;

				case AVM_CTRL_CMD_VIEW_SW:
				{
					CanTxInfo.hu_rvm_e_00.byte_0.field.f_view_sw=0x01;
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_RVM_E_00);
					Hyundai_BN7i_TxRvmFlag=1;
					Hyundai_BN7i_TxRvmCounter=0;
				}
				break;

				case AVM_CTRL_CMD_SELECT_MENU:
				{
					if(buffer[4]==0x01
						||buffer[4]==0x02
						||buffer[4]==0x03)
					{
						CanTxInfo.hu_rvm_e_00.byte_1.field.f_select_menu=buffer[4];
						Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_RVM_E_00);
						Hyundai_BN7i_TxRvmFlag=1;
						Hyundai_BN7i_TxRvmCounter=0;
					}
				}
				break;

				case AVM_CTRL_CMD_GUIDE_LINE:
				{
					if(buffer[4]==0x00)
					{
						CanTxInfo.hu_rvm_e_00.byte_1.field.f_guide_line=1;
					}
					else
					{
						CanTxInfo.hu_rvm_e_00.byte_1.field.f_guide_line=2;
					}
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_RVM_E_00);
					Hyundai_BN7i_TxRvmFlag=1;
					Hyundai_BN7i_TxRvmCounter=0;
				}
				break;

				case AVM_CTRL_CMD_DRVM:					
					break;
				
				case AVM_CTRL_CMD_EXTEND_CAMERA:
				{	
					if(buffer[4]==0x00)
					{
						extend_camera_use_flag=0;
					}
					else if (buffer[4]==0x01) 
					{
						extend_camera_use_flag=1;
					}
				}
				break;	
			}
		}
		break;
			
		case HYUNDAI_BN7i_TX_ECALL_CMD:
		{
			switch(buffer[3])
			{
				case ECALL_MODE_CMD_STATUS:
				{
					if(buffer[4]==0x00)
					{
					CanTxInfo.hu_ecall_e_00.byte_0.field.f_mode=0x00;
					CanTxInfo.hu_ecall_e_00.byte_1.field.f_status=0x00;
					}
					else if(buffer[4]==0x01)
					{
						CanTxInfo.hu_ecall_e_00.byte_0.field.f_mode=0x01;
						CanTxInfo.hu_ecall_e_00.byte_1.field.f_status=0x01;
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.hu_ecall_e_00.byte_0.field.f_mode=0x02;
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.hu_ecall_e_00.byte_0.field.f_mode=0x03;
						CanTxInfo.hu_ecall_e_00.byte_1.field.f_status=0x02;
					}
					else if(buffer[4]==0x04)
					{
						CanTxInfo.hu_ecall_e_00.byte_0.field.f_mode=0x04;
					}
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_ECALL_E_00);
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_ECALL_S_00);
					CanTxInfo.hu_ecall_e_00.byte_0.field.f_mode=0;
					CanTxInfo.hu_ecall_e_00.byte_1.field.f_status=0;
				}
				break;
				
				case ECALL_MODE_CMD_WARNING:
				{
					if(buffer[4]==0x01)
					{
						CanTxInfo.hu_ecall_e_00.byte_0.field.f_warning=0x01;
					}
					else
					{
						CanTxInfo.hu_ecall_e_00.byte_0.field.f_warning=0x00;
					}
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_ECALL_W_00);
					CanTxInfo.hu_ecall_e_00.byte_0.field.f_warning=0;
				}
				break;
				
				case ECALL_MODE_CMD_VER:
				{
					if(buffer[4]==0x0)
					{
						e_sta=0;
					}
					else if(buffer[4]==0x1)
					{
						e_sta=1;
					}
				}
				break;
				
				case ECALL_MODE_CMD_MIC:
				{
					if(buffer[4]==0x0)
					{
						Mic_flag=0;
					}
					else if(buffer[4]==0x1)
					{
						Mic_flag=1;
						
						
					}
				}
					break;

				case ECALL_MODE_CMD_ARM:
				{
					if(buffer[4]==0x0)
					{
						CanTxInfo.hu_ecall_e_00.byte_1.field.f_arm=0x0;
					}
					else if(buffer[4]==0x1)
					{
						CanTxInfo.hu_ecall_e_00.byte_1.field.f_arm=0x1;
					}
					else if(buffer[4]==0x2)
					{
						CanTxInfo.hu_ecall_e_00.byte_1.field.f_arm=0x2;
					}
					else if(buffer[4]==0x3)
					{
						CanTxInfo.hu_ecall_e_00.byte_1.field.f_arm=0x3;
					}
					else if(buffer[4]==0x4)
					{
						CanTxInfo.hu_ecall_e_00.byte_1.field.f_arm=0x4;
					}
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_ECALL_C_00);
				}
				break;
				
				default:
					break;
			}
		}
			break;
	
	case HYUNDAI_BN7i_TX_VIN_CMD:
	{		
			switch(buffer[3])
			{
				case VIN_CTRL_CMD_ON:
				{
					CanTxInfo.hu_ecall_e_00.byte_2.field.f_vin_status=0x01;
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_ECALL_V_00);
					CanTxInfo.hu_ecall_e_00.byte_2.field.f_vin_status=0;
				}
				break;

				case VIN_CTRL_CMD_AVNT_ON:
				{
					CanTxInfo.hu_ecall_e_00.byte_2.field.f_avnt_option=0x01;
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_ECALL_V_00);
					CanTxInfo.hu_ecall_e_00.byte_2.field.f_avnt_option=0;
				}
				break;

				case VIN_CTRL_CMD_SELECT_INDEX:
				{
					if(buffer[4]==0x01
						||buffer[4]==0x02
						||buffer[4]==0x03)
					{
						CanTxInfo.hu_ecall_e_00.byte_2.field.f_vin_index=buffer[4];
						Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_ECALL_V_00);
						CanTxInfo.hu_ecall_e_00.byte_2.field.f_vin_index=0;
					}
				}
				break;	
			}
		}
		break;
		
		default:
			break;
	}
}

void Hyundai_BN7i_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case HYUNDAI_BN7i_RX_BASE_INO:
		{
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.base_info.byte_0.byte;
			buffer[4]=CanRxInfo.base_info.byte_1.byte;
			buffer[5]=CanRxInfo.base_info.byte_2.byte;
		}
		break;		   
		
		case HYUNDAI_BN7i_RX_EPS_INO:
		{
			buffer[2]=0x02;
			buffer[3]=CanRxInfo.eps_info.swa_msb;
			buffer[4]=CanRxInfo.eps_info.swa_lsb;
		}
		break;

		case HYUNDAI_BN7i_RX_RADAR_INO:
		{
			buffer[2]=0x06;
			buffer[3]=CanRxInfo.radar_info.front_left;
			buffer[4]=CanRxInfo.radar_info.front_right;
			buffer[5]=CanRxInfo.radar_info.front_center;
			buffer[6]=CanRxInfo.radar_info.rear_left;
			buffer[7]=CanRxInfo.radar_info.rear_right;
			buffer[8]=CanRxInfo.radar_info.rear_center;
		}
		break;

		case HYUNDAI_BN7i_RX_DRIVING_INO:
		{
			buffer[2]=0x0A;
			buffer[3]=((CanRxInfo.driving_info.odometer&0xFF000000)>>24);
			buffer[4]=((CanRxInfo.driving_info.odometer&0x00FF0000)>>16);
			buffer[5]=((CanRxInfo.driving_info.odometer&0x0000FF00)>>8);
			buffer[6]=(CanRxInfo.driving_info.odometer&0xFF);
			buffer[7]=((CanRxInfo.driving_info.cluster_speed&0xFF00)>>8);
			buffer[8]=(CanRxInfo.driving_info.cluster_speed&0xFF);
			buffer[9]=((CanRxInfo.driving_info.cluster_disp_speed&0xFF00)>>8);
			buffer[10]=(CanRxInfo.driving_info.cluster_disp_speed&0xFF);
			buffer[11]=CanRxInfo.driving_info.cluster_disp_speed_unit;
			buffer[12]=CanRxInfo.driving_info.vehicle_speed;
		}
		break;

		case HYUNDAI_BN7i_RX_AVM_INO:
		{
			buffer[2]=0x05;
			buffer[3]=CanRxInfo.avm_info.rvm_mode;
			buffer[4]=CanRxInfo.avm_info.rvm_type;
			buffer[5]=CanRxInfo.avm_info.rvm_guide_line;
			buffer[6]=CanRxInfo.avm_info.rvm_state;
			buffer[7]=CanRxInfo.avm_info.rvm_drv_state;
		}
		break;

		case HYUNDAI_BN7i_RX_ECALL_INO:
		{
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.ecall_info.byte_0.byte;
			buffer[4]=CanRxInfo.ecall_info.byte_1.byte;
			buffer[5]=CanRxInfo.ecall_info.byte_2.byte;
		}		
		break;
		
		case HYUNDAI_BN7i_RX_BATTERY_INO:
		{
			buffer[2]=0x01;
			if(CanRxInfo.battery_info.byte_0.field.f_battery_low==0)
			{
				buffer[3]=CanRxInfo.battery_info.byte_0.field.f_battery_low;
			}
			else
			{
				buffer[3]=0;
			}
		}
		break;

		case HYUNDAI_BN7i_RX_GEAR_INO:
		{
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.gear_info.byte_0.byte;
			buffer[4]=CanRxInfo.gear_info.byte_1.byte;
			buffer[5]=CanRxInfo.driving_info.vehicle_speed;
		}			
		break;

		default:
		{
			flag=0;
		}
		break;
	}
	if(flag)
	{	
		buffer[0]=HYUNDAI_BN7i_HEAD_CODE;
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

void Hyundai_BN7i_MainPro(void)//1ms 
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
	
	if(CanTxEpsTimer)
	{
		CanTxEpsTimer--;
	}

	if(CanTxRadarTimer)
	{
		CanTxRadarTimer--;
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
	if(Reverse_flag)
	{
		if(Reverse_Timer)
		{
			Reverse_Timer--;
		}
	}
	if(CanTxMicTimer)
	{
		CanTxMicTimer--;
	}
	if(sta_flag)
	{
		if(CanTxStaTimer)
		{
			CanTxStaTimer--;
		}
	}

	Hyundai_BN7i_Rx_Message();
	if(F_CAN_INIT)
	{
		CAN1_Transmit();
	}
	switch(CanMainState)
	{
		case CAN_MAIN_IDLE:
		{
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;
		}
		break;
		
		case CAN_MAIN_CFG:
		{
			CAN1_Init();
			CanMainState=CAN_MAIN_POWER_OFF;
			CanMainTimer=T2S_1;
		}
		break;

		case CAN_MAIN_POWER_OFF:
		{
			if(CanMainTimer)
			{
				break;
			}
			CAN_IC_POWER_OFF;
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_POWER_ON;
			CanMainTimer=T2S_1;
		}
		break;

		case CAN_MAIN_POWER_ON:
		{
			if(CanMainTimer)
			{
				break;
			}
			CAN_IC_POWER_ON;
			F_CAN_INIT=1;
			CanMainState=CAN_MAIN_INIT;
		}
		break;

		case CAN_MAIN_INIT:
		{
			CAN1_ClearTxMessage();
			CanTxInfo.hu_rvm_e_00.byte_0.byte=0x0F;
			CanTxInfo.hu_rvm_e_00.byte_1.byte=0xFF;
			Hyundai_BN7i_TxRvmTimer=T30MS_1;
			Hyundai_BN7i_TxRvmFlag=0;
			Hyundai_BN7i_TxRvmCounter=0;
			F_CAN_SLEEP=0;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T5S_1;
		}
		break;

		case CAN_MAIN_NORMAL:
		{
			if(CanRxInfo.base_info.byte_0.field.f_illumi)
			{
				CanGeneralCtrlFlag.field.ill_onoff=1;
			}
			else
			{
				CanGeneralCtrlFlag.field.ill_onoff=0;
			}
			if(CanRxInfo.battery_info.byte_1.field.f_battery_eng<3||CanRxInfo.battery_info.byte_1.field.f_battery_eng==7)
			{
				sta_flag=1;
				if(CanTxStaTimer==T10S_1)
				{
					CanRxInfo.battery_info.byte_0.field.f_battery_low=0;
				}
				
				if(CanTxStaTimer==0)
				{
					CanRxInfo.battery_info.byte_0.field.f_battery_low=1;
					CanTxStaTimer=T300S_1;
				}
			}
			else 
			{
				sta_flag=0;
				CanTxStaTimer=T300S_1;
			}
			
#if 0
			if(CanRxInfo.gear_info.byte_1.field.f_tgs_r_mt==1
				||CanRxInfo.gear_info.byte_1.field.f_ems_r_mt==1
				||CanRxInfo.gear_info.byte_0.field.f_tgs_gear_at==0x07
				||CanRxInfo.gear_info.byte_0.field.f_gear==0x07)
			{
				CanRxInfo.base_info.byte_0.field.f_reverse=1;
				CanGeneralCtrlFlag.field.reverse_on_off=1;
			}
			else
			{
				CanRxInfo.base_info.byte_0.field.f_reverse=0;
				CanGeneralCtrlFlag.field.reverse_on_off=0;
			}
#else
			if(gear_bak!=CanRxInfo.gear_info.byte_0.field.f_tgs_gear_at)
			{
				gear_bak=CanRxInfo.gear_info.byte_0.field.f_tgs_gear_at;
				gear_timer=0;
			}
			else
			{
				gear_timer++;
				if(gear_timer>T200MS_1)
				{
					gear_value=CanRxInfo.gear_info.byte_0.field.f_tgs_gear_at;
				}
			}
			
			if(gear_value==0x07||CanRxInfo.gear_info.byte_1.field.f_tgs_r_mt==1)
			{			
				ReverseGearTimer++;
				if(ReverseGearTimer>=T200MS_1)
				{
					// when gear switch to R
					CanRxInfo.base_info.byte_0.field.f_reverse=1;
					Reverse_flag=1;
					CanGeneralCtrlFlag.field.reverse_on_off=1;
					CanGeneralCtrlFlag.field.camera_on_off=0;
					DRVM_KeyPressedFlag=0;
				}
			}
			else if(gear_value!=0x07||CanRxInfo.gear_info.byte_1.field.f_tgs_r_mt!=1)
			{
				// when gear switch to N,D,P
				ReverseGearTimer=0;
				CanRxInfo.base_info.byte_0.field.f_reverse=0;
			
				if(Reverse_flag)//make a limit ,only From R gear to other gear use the function of Extend 
				{
					if(extend_camera_use_flag)
					{
#if CAN_DEBUG_FUN==1
						printf("extend_camera_use_open\r\n");
						printf("Gear=%d,Speed=%d,camera status=%d,reverse status=%d\r\n",gear_value,CanRxInfo.driving_info.vehicle_speed,CanGeneralCtrlFlag.field.camera_on_off,CanGeneralCtrlFlag.field.reverse_on_off);	
#endif	
						// if extend on,when car speed more than 15 or gear switch to P,clear reverse flag
						if(CanRxInfo.driving_info.vehicle_speed>=15
							||CanRxInfo.avm_info.rvm_mode==0)
						{					
							CanGeneralCtrlFlag.field.reverse_on_off=0;
							CanGeneralCtrlFlag.field.camera_on_off=0;
							Reverse_flag=0;
							if(Reverse_flag)
							{
								Reverse_Timer=T500MS_1;
							}	
							DRVM_KeyPressedFlag=0;
						}
					}
					else
					{
						// if extend off,clear reverse flag
						CanGeneralCtrlFlag.field.reverse_on_off=0;
						Reverse_flag=0;
					}
				}
				else
				{
					Reverse_Timer=0;
					CanGeneralCtrlFlag.field.reverse_on_off=0;
				}
				if(Reverse_Timer==0)
				{
					if(gear_value==0x00)
					{
						if(CanRxInfo.avm_info.rvm_mode==9)
						{
							CanGeneralCtrlFlag.field.camera_on_off=1;
						}
						else if(DRVM_KeyPressedFlag
							&&CanRxInfo.avm_info.rvm_mode==2)
						{
							CanGeneralCtrlFlag.field.camera_on_off=1;
							DRVM_KeyPressedFlag=0;
						}
						else if(CanRxInfo.avm_info.rvm_mode==0)
						{
							CanGeneralCtrlFlag.field.camera_on_off=0;
							Reverse_flag=0;
							DRVM_KeyPressedFlag=0;
						}
					}
					else if(gear_value==0x05
						||gear_value==0x06
						||gear_value==0x08
						||gear_value==0x02
						||gear_value==0x03
						||gear_value==0x04
						)
					{
#if CAN_DEBUG_FUN==1
				printf("Gear=%d,Speed=%d,camera status=%d,reverse status=%d\r\n",gear_value,CanRxInfo.driving_info.vehicle_speed,CanGeneralCtrlFlag.field.camera_on_off,CanGeneralCtrlFlag.field.reverse_on_off);	
#endif
						if(DRVM_KeyPressedFlag
							&&CanRxInfo.avm_info.rvm_mode>=2)
						{
#if CAN_DEBUG_FUN==1
					printf("Gear=%d,Speed=%d,camera status=%d,reverse status=%d\r\n",gear_value,CanRxInfo.driving_info.vehicle_speed,CanGeneralCtrlFlag.field.camera_on_off,CanGeneralCtrlFlag.field.reverse_on_off);
#endif
							CanGeneralCtrlFlag.field.camera_on_off=1;							
							DRVM_KeyPressedFlag=0;
						}		
						else if(CanRxInfo.avm_info.rvm_mode==0)
						{
								CanGeneralCtrlFlag.field.camera_on_off=0;
								DRVM_KeyPressedFlag=0;
						}
					}
				}
			}
						
#endif
			if(CanRxInfo.gear_info.byte_1.field.f_parking_brake==2||CanRxInfo.gear_info.byte_1.field.f_parking_brake_epb==2)
			{
				CanRxInfo.base_info.byte_0.field.f_parking=1;
				CanGeneralCtrlFlag.field.parking_on_off=1;
			}
			else
			{
				CanRxInfo.base_info.byte_0.field.f_parking=0;
				CanGeneralCtrlFlag.field.parking_on_off=0;
			}

			if(CanRxInfo.base_info.byte_2.field.f_av_tail==1
				&&CanRxInfo.base_info.byte_2.field.f_auto_light_sensor_state==0)
			{
				FLAG_Panel_LED=0;
				CanRxInfo.base_info.byte_0.field.f_light_detect=AUTO_LIGHT_DAY;
			}
			else if(CanRxInfo.base_info.byte_2.field.f_av_tail==1
				&&CanRxInfo.base_info.byte_2.field.f_auto_light_sensor_state==1)
			{
				FLAG_Panel_LED=1;
				CanRxInfo.base_info.byte_0.field.f_light_detect=AUTO_LIGHT_EVENING;
			}
			else if(CanRxInfo.base_info.byte_2.field.f_av_tail==2
				&&CanRxInfo.base_info.byte_2.field.f_auto_light_sensor_state==1)
			{
				FLAG_Panel_LED=1;
				CanRxInfo.base_info.byte_0.field.f_light_detect=AUTO_LIGHT_NIGHT;
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

			if(Hyundai_BN7i_TxRvmTimer)
			{
				Hyundai_BN7i_TxRvmTimer--;
				if(Hyundai_BN7i_TxRvmTimer==0)
				{
					Hyundai_BN7i_PostMessage(CAN_POST_MSG_HU_RVM_E_00);
					Hyundai_BN7i_TxRvmTimer=T30MS_1;
					
					if(Hyundai_BN7i_TxRvmFlag)
					{
						Hyundai_BN7i_TxRvmCounter++;
						if(Hyundai_BN7i_TxRvmCounter>=3)
						{
							Hyundai_BN7i_TxRvmFlag=0;
							Hyundai_BN7i_TxRvmCounter=0;
							CanTxInfo.hu_rvm_e_00.byte_0.byte=0x0F;
							CanTxInfo.hu_rvm_e_00.byte_1.byte=0xFF;
						}
					}
				}
			}
			
			
			
			
	#if TEST_CAN_FUN==1
			if(CanTxTestTimer==0)
			{
					CanTxTestTimer=T3S_1;
					
				
			}	
		
			if(CanTxTestTimer)
			{
				CanTxTestTimer--;
				if(CanTxTestTimer==0&&TurnOn_Volume==25)
				{
					if(test==7)
					{
						test=0;
					}
					else test=7;
					CanTxTestTimer=T3S_1;
				}
				else if(CanTxTestTimer==0&&TurnOn_Volume==27)
				{
					test++;
					if(test==3)
						{
							test=0;
						}
					switch(test)
					{
					case 0:
						test1=1;
						test2=0;
						break;
					case 1:
						test1=1;
						test2=0x40;
						break;
					case 2:
						test1=2;
						test2=0x40;
						break;
				}
					CanTxTestTimer=T3S_1;
				}
					else if(CanTxTestTimer==0&&TurnOn_Volume==29)
				{
					if(test==0x10)
					{
						test=0x20;
					}
					else test=0x10;
					CanTxTestTimer=T3S_1;
				}
			}
			if(test_time)
			{
				test_time--;
				if(test_time==0&&TurnOn_Volume==25)
				{
					u8 data[8]={0};

					data[0]=test;
					CAN1_TxFrame(CAN_ID_GW_CHASSIS_PE_1,data,8);
					test_time=T1S_1;
					
				}
				if(test_time==0&&TurnOn_Volume==27)
				{
					u8 data[8]={0};

					data[0]=test1;
					
					CAN1_TxFrame(CAN_ID_GW_CAR_INFO_PE,data,8);
					data[2]=test2;
					CAN1_TxFrame(CAN_ID_GW_HU_PE_06,data,8);
					test_time=T1S_1;
					
				}
				if(test_time==0&&TurnOn_Volume==29)
				{
					u8 data[8]={0};

					data[0]=test;
					CAN1_TxFrame(CAN_ID_GW_CHASSIS_PE_1,data,8);
					test_time=T1S_1;
					
				}
			}			
			if(test_time==0)
			{
					test_time=T1S_1;	
			}	
	#endif
			if(Get_ACC_Det_Flag==0)
			{
				CanMainState=CAN_MAIN_GO_TO_SLEEP;
				CanMainTimer=T2S_1;
			}
			else if(APP_READY==APP_Status)
			{
				if(Get_Reverse_Det_Flag)
				{
					if(CanTxEpsTimer==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_EPS_INO);
						CanTxEpsTimer=T500MS_1;
					}
					if(CanTxRadarTimer==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_RADAR_INO);
						CanTxRadarTimer=T500MS_1;
					}
					if(CanTxGearTimer==0)
					{
						CanRxInfo.gear_info_bak.byte_0.byte=CanRxInfo.gear_info.byte_0.byte;
						CanRxInfo.gear_info_bak.byte_1.byte=CanRxInfo.gear_info.byte_1.byte;
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_GEAR_INO);
						CanTxGearTimer=T500MS_1;
					}
					if(0==strcmp_equal(&CanRxInfo.ecall_info.byte_0.byte,&CanRxInfo.ecall_info_bak.byte_0.byte,sizeof(CAN_ECALL_INFO)))
					{
						CanRxInfo.ecall_info_bak.byte_0.byte=CanRxInfo.ecall_info.byte_0.byte;
						CanRxInfo.ecall_info_bak.byte_1.byte=CanRxInfo.ecall_info.byte_1.byte;
						CanRxInfo.ecall_info_bak.byte_2.byte=CanRxInfo.ecall_info.byte_2.byte;
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_ECALL_INO);
						CanTxEcallTimer=T100MS_1;
					}
				}
				else
				{
					if(0==strcmp_equal(&CanRxInfo.ecall_info.byte_0.byte,&CanRxInfo.ecall_info_bak.byte_0.byte,sizeof(CAN_ECALL_INFO)))
					{
						CanRxInfo.ecall_info_bak.byte_0.byte=CanRxInfo.ecall_info.byte_0.byte;
						CanRxInfo.ecall_info_bak.byte_1.byte=CanRxInfo.ecall_info.byte_1.byte;
						CanRxInfo.ecall_info_bak.byte_2.byte=CanRxInfo.ecall_info.byte_2.byte;
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_ECALL_INO);
						CanTxEcallTimer=T100MS_1;
					}
					else if(CanTxEcallTimer==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_ECALL_INO);
						CanTxEcallTimer=T5S_1;
					}
					
					if(0==strcmp_equal(&CanRxInfo.battery_info.byte_0.byte,&CanRxInfo.battery_info_bak.byte_0.byte,sizeof(CAN_BATTERY_INFO)))
					{
						CanRxInfo.battery_info_bak.byte_0.byte=CanRxInfo.battery_info.byte_0.byte;
						CanRxInfo.battery_info_bak.byte_1.byte=CanRxInfo.battery_info.byte_1.byte;
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_BATTERY_INO);
						CanTxBatteryTimer=T200MS_1;
					}
					
					if(CanRxInfo.ecall_info.byte_0.field.ecall_mode==1||CanRxInfo.ecall_info.byte_0.field.ecall_mode==3)
					{
						if(CanRxInfo.ecall_info.byte_2.field.ecall_fail==1)
						{
							e_warn=0;
						}
						else
						{
							e_warn=1;
						}
					}
					else if(CanRxInfo.ecall_info.byte_0.field.ecall_mode==2||CanRxInfo.ecall_info.byte_0.field.ecall_mode==0)
					{
						e_warn=0;
					}
					if(e_sta)
					{
						if(CanTxMicTimer==0)
						{
							u8 data[8]={0};
							if(Mic_flag)
							{
								if(e_warn)
								{
									data[2]=0x00;
								}
								else 
								{
									data[2]=0x20;
								}
							}
							else
							{
								data[2]=0x00;
							}
							CAN1_TxFrame(CAN_POST_HU_Mic_PE_01,data,8);
							CanTxMicTimer=T200MS_1;
						}
					}
					
					if(0==strcmp_equal(&CanRxInfo.base_info.byte_0.byte,&CanRxInfo.base_info_bak.byte_0.byte,sizeof(CAN_BASE_INFO)))
					{
						CanRxInfo.base_info_bak.byte_0.byte=CanRxInfo.base_info.byte_0.byte;
						CanRxInfo.base_info_bak.byte_1.byte=CanRxInfo.base_info.byte_1.byte;
						CanRxInfo.base_info_bak.byte_2.byte=CanRxInfo.base_info.byte_2.byte;
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_BASE_INO);
						CanTxBaseTimer=T600MS_1;
					}
					else if(CanTxBaseTimer==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_BASE_INO);
						CanTxBaseTimer=T5S_1;
					}
					if(0==strcmp_equal(&CanRxInfo.gear_info.byte_0.byte,&CanRxInfo.gear_info_bak.byte_0.byte,sizeof(CAN_GEAR_INFO)))
					{
						CanRxInfo.gear_info_bak.byte_0.byte=CanRxInfo.gear_info.byte_0.byte;
						CanRxInfo.gear_info_bak.byte_1.byte=CanRxInfo.gear_info.byte_1.byte;
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_GEAR_INO);
						
						CanTxGearTimer=T200MS_1;
					}
					else if(CanTxGearTimer==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_BN7i_RX_GEAR_INO);
						CanTxGearTimer=T200MS_1;
					}
				}
			}
		}
		break;
		
		case CAN_MAIN_GO_TO_SLEEP:
		{
			if(Get_ACC_Det_Flag)
			{
				CanMainState=CAN_MAIN_NORMAL;
			}
			else if(CanMainTimer==0)
			{
				CAN_IC_STANDBY_ON;
				F_CAN_SLEEP=1;
	#if TEST_CAN_FUN==1
	#else 
				CanMainState=CAN_MAIN_SLEEP_CFG;
	#endif
				CanMainTimer=T1S5_1;
			}
		}
		break;
		
		case CAN_MAIN_SLEEP_CFG:
		{
			if(CanMainTimer)
			{
				break;
			}
			CAN1_ClearRxMessage();
			CAN_IC_DISABLE;
			F_CAN_SLEEP=1;
			CanMainState=CAN_MAIN_SLEEP;
		}
		break;

		case CAN_MAIN_SLEEP:
		{
			if(Get_ACC_Det_Flag)
			{
				CAN_IC_ENABLE;
				F_CAN_SLEEP=0;
				CAN_IC_STANDBY_OFF;
				CanMainState=CAN_MAIN_INIT;
			}
		}
		break;

		default:
			break;
	}
}
#endif

