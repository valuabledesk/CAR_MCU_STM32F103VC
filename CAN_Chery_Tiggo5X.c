#include "public.h"

#if CAN_FUN_CHERY_TIGGO_5X==1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_TX_INFO CanTxInfo;
CAN_TX_INFO CanTxInfoBak;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanCheckErrorTimer;
u32 CanOverSpeedTimer;
u32 CanTimeInfoTimer;
u32 CanAirInfoTimer;
u32 CanBaseInfoTimer;
u32 CanTxAppTimer;
u32 CanTxCanTimer;

u32 CanTxAirTimer;
u16 AvmCalibrationTimeout;
u16 AvmCalibrationTimer;
u8 AvmCalibrationFlag;
u8 CanTxTimer;
u8 CanTurnOnVolume;

int CanTimeSyncRec;
int CanTimeSyncRec_Bak;
int RtcTimeSyncRec;

u8 CanTimeSyncDelay;
u8 FictitiousPowerOffFlag;


void Tiggo5X_PostMessage(CAN_POST_MESSAGE_INDEX index);

void unicode_to_utf8(u16 *unic, u8 *pOutput, u8 *length)                             
{ 
	*length = 0;

	while(*unic&&(*length)<=40)
	{
		if((*unic)<=0x0000007F) 
		{ 
			*(pOutput++)=((*unic)&0x7F); 
			(*length)++;
		} 
		else if(((*unic)>=0x00000080)&&((*unic)<=0x000007FF)) 
		{ 
			*(pOutput++)=(((*unic)>>6)&0x1F)|0xC0; 
			*(pOutput++)=((*unic)&0x3F)|0x80; 
			(*length) += 2;
		} 
		else if (((*unic)>=0x00000800)&&((*unic)<=0x0000FFFF)) 
		{ 
			*(pOutput++)=(((*unic)>>12)&0x0F)|0xE0; 
			*(pOutput++)=(((*unic)>>6)&0x3F)|0x80;
			*(pOutput++)=((*unic)&0x3F)|0x80; 
			(*length)+=3;
		} 
		unic++;
	}
	if(*unic&&(*length)>=40)	
	{
		*pOutput++=0xE2;
		*pOutput++=0x80;
		*pOutput++=0xA6;
		(*length)+=3;
	}
} 

u8 Tiggo5X_TimerVerify(CAN_MESSAGE_INFO message)
{
    u8 result=1;
    CAN_TIME_INFO TimeInfo={0};

    TimeInfo.hour=message.Data[0];
    TimeInfo.min=message.Data[1];
    
    TimeInfo.sec=(message.Data[2]&0x03);
    TimeInfo.sec<<=4;
    TimeInfo.sec+=((message.Data[3]&0xF0)>>4);

    if(TimeInfo.hour<=23&&TimeInfo.min<=59&&TimeInfo.sec<=59)
    {
        result=0;
    }

    return result;
}

void Tiggo5X_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8];
	
	switch(index)
	{
		case CAN_POST_MSG_RRM_1:
			data[0]=CanTxInfo.rrm_1_info.byte_1.byte;
			data[1]=CanTxInfo.rrm_1_info.byte_2.byte;
			data[2]=MSB(CanTxInfo.rrm_1_info.byte_34.word);
			data[3]=LSB(CanTxInfo.rrm_1_info.byte_34.word);
			data[4]=CanTxInfo.rrm_1_info.reserved_5;
			data[5]=CanTxInfo.rrm_1_info.reserved_6;
			data[6]=CanTxInfo.rrm_1_info.reserved_7;
			data[7]=CanTxInfo.rrm_1_info.reserved_8;
			CAN1_TxFrame(CAN_ID_RRM_1,data,8);		
			break;
		case CAN_POST_MSG_RRM_2:
			data[0]=CanTxInfo.rrm_2_info.byte_1.byte;
			data[1]=CanTxInfo.rrm_2_info.frequence_fm_h;
			data[2]=CanTxInfo.rrm_2_info.frequence_fm_l;
			data[3]=CanTxInfo.rrm_2_info.frequence_am_h;
			data[4]=CanTxInfo.rrm_2_info.frequence_am_l;
			data[5]=CanTxInfo.rrm_2_info.volume;
	            	data[6]=CanTxInfo.rrm_2_info.reserved_7;
	            	data[7]=CanTxInfo.rrm_2_info.byte_8.byte;
			CAN1_TxFrame(CAN_ID_RRM_2,data,8);
			break;
		case CAN_POST_MSG_RRM_3:
			data[0]=CanTxInfo.rrm_3_info.hour;
			data[1]=CanTxInfo.rrm_3_info.min;
			data[2]=CanTxInfo.rrm_3_info.instrument_back_light;
			data[3]=CanTxInfo.rrm_3_info.second;
			data[4]=0;
			data[5]=0;
			data[6]=0;
			data[7]=0;
			CAN1_TxFrame(CAN_ID_RRM_3,data,8);
			break;
		case CAN_POST_MSG_RRM_4:		
			data[0]=CanTxInfo.rrm_4_info.byte_1.byte;
			data[1]=CanTxInfo.rrm_4_info.byte_2.byte;
			data[2]=CanTxInfo.rrm_4_info.reserved_3;
			data[3]=CanTxInfo.rrm_4_info.reserved_4;
			data[4]=CanTxInfo.rrm_4_info.byte_5.byte;
			data[5]=CanTxInfo.rrm_4_info.byte_6.byte;
			data[6]=CanTxInfo.rrm_4_info.byte_7.byte;
			data[7]=CanTxInfo.rrm_4_info.reserved_8;
			CAN1_TxFrame(CAN_ID_RRM_4,data,8);
			break;
		case CAN_POST_MSG_RRM_5:
			data[0]=CanTxInfo.rrm_5_info.reserved_1;
			data[1]=CanTxInfo.rrm_5_info.byte_2.byte;
			data[2]=CanTxInfo.rrm_5_info.reserved_3;
			data[3]=CanTxInfo.rrm_5_info.reserved_4;
			data[4]=CanTxInfo.rrm_5_info.reserved_5;
			data[5]=CanTxInfo.rrm_5_info.reserved_6;
			data[6]=CanTxInfo.rrm_5_info.reserved_7;
			data[7]=CanTxInfo.rrm_5_info.reserved_8;
			CAN1_TxFrame(CAN_ID_RRM_5,data,8);
			break;	
		default:
			break;
	}
}

void Tiggo5X_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_BCM_4:
				if(((message.Data[6]&0x60)>>5)==0x00)
				{
					CanRxInfo.ctrl_feedback_info.byte_1.field.f_defense_reminder=0x02;
				}
				else if(((message.Data[6]&0x60)>>5)==0x01)
				{
					CanRxInfo.ctrl_feedback_info.byte_1.field.f_defense_reminder=0x00;
				}
				else if(((message.Data[6]&0x60)>>5)==0x02)
				{
					CanRxInfo.ctrl_feedback_info.byte_1.field.f_defense_reminder=0x01;
				}

				if((message.Data[4]&0x08)>>3)
				{
					CanRxInfo.base_info.byte_1.field.f_reverse=1;
				}
				else
				{
					CanRxInfo.base_info.byte_1.field.f_reverse=0;
				}
				CanGeneralCtrlFlag.field.reverse_on_off=CanRxInfo.base_info.byte_1.field.f_reverse;
				
				if((message.Data[1]&0x10)>>4)	
				{
					CanRxInfo.base_info.byte_1.field.f_illumi=1;
				}
				else
				{
					CanRxInfo.base_info.byte_1.field.f_illumi=0;
				}
				CanGeneralCtrlFlag.field.ill_onoff=CanRxInfo.base_info.byte_1.field.f_illumi;
				
				if((message.Data[1]&0x08)>>3)
				{
					CanRxInfo.base_info.byte_1.field.f_parking=1;
				}
				else
				{
					CanRxInfo.base_info.byte_1.field.f_parking=0;
				}
				CanGeneralCtrlFlag.field.parking_on_off=CanRxInfo.base_info.byte_1.field.f_parking;
				
				CanRxInfo.base_info.byte_1.field.f_acc=((message.Data[0]&0x30)>>4);
				CanRxInfo.detail_info.byte_1.field.f_lock_state=((message.Data[3]&0x80)>>7);
				CanRxInfo.detail_info.byte_1.field.f_trunk=((message.Data[3]&0x40)>>6);
				CanRxInfo.detail_info.byte_1.field.f_lr_door=((message.Data[3]&0x20)>>5);
				CanRxInfo.detail_info.byte_1.field.f_rr_door=((message.Data[3]&0x10)>>4);
				CanRxInfo.detail_info.byte_1.field.f_hood=((message.Data[3]&0x04)>>2);
				CanRxInfo.detail_info.byte_1.field.f_passenger_door=((message.Data[3]&0x02)>>1);
				if(message.Data[3]&0x01)
				{
					CanRxInfo.detail_info.byte_1.field.f_driver_door=1;
					F_DRIVER_DOOR_STATE=1;
				}
				else
				{
					CanRxInfo.detail_info.byte_1.field.f_driver_door=0;
					F_DRIVER_DOOR_STATE=0;
				}
					
				CanRxInfo.ctrl_feedback_info.byte_1.field.f_daytime_driving_sta=(message.Data[7]&0x04)>>2;

				CanRxInfo.ctrl_feedback_info.byte_1.field.f_auto_lock=(message.Data[7]&0x01);			
				break;
			case CAN_ID_ICM_2:	
				if(CanOverSpeedTimer==0)
				{
					CanRxInfo.ctrl_feedback_info.byte_2.field.f_over_speed=((message.Data[3])&0x7C)>>2;
				}			
				break;
			case CAN_ID_ICM_3:
				CanRxInfo.ctrl_feedback_info.byte_3.field.f_instrument_backlight=(message.Data[3]&0x0F);
				if(Tiggo5X_TimerVerify(message))
				{
					break;
				}
				CanRxInfo.time_info.hour=message.Data[0];
				CanRxInfo.time_info.min=message.Data[1];

				CanRxInfo.time_info.sec=(message.Data[2]&0x03);
				CanRxInfo.time_info.sec<<=4;
				CanRxInfo.time_info.sec+=((message.Data[3]&0xF0)>>4);

				if(CanTimeInfoTimer)
				{
					break;
				}
				if(CanTimeSyncDelay)
				{
					CanTimeSyncDelay--;
				}
				CanTimeSyncRec=CanRxInfo.time_info.hour*60*60+CanRxInfo.time_info.min*60+CanRxInfo.time_info.sec;
				
				if(F_RTC_READ_STATUS==1
					&&nPowerState==POWER_NORMAL_RUN
					&&CanTimeInfoTimer==0
					&&CanTimeSyncDelay==0)
				{
					RtcTimeSyncRec=RTC_TimeInfo.hours*60*60+RTC_TimeInfo.minutes*60+RTC_TimeInfo.seconds;
					if(abs(CanTimeSyncRec-CanTimeSyncRec_Bak)<=1||abs(CanTimeSyncRec-CanTimeSyncRec_Bak)>=86399)
					{
						if(abs(RtcTimeSyncRec-CanTimeSyncRec)>5&&abs(RtcTimeSyncRec-CanTimeSyncRec)<86395)
						{
							CanTxInfo.rrm_3_info.hour=RTC_TimeInfo.hours;
							CanTxInfo.rrm_3_info.min=RTC_TimeInfo.minutes;
							CanTxInfo.rrm_3_info.second=RTC_TimeInfo.seconds;
							Tiggo5X_PostMessage(CAN_POST_MSG_RRM_3);
							CanTxInfo.rrm_3_info.hour=0xFF;
							CanTxInfo.rrm_3_info.min=0xFF;
							CanTxInfo.rrm_3_info.second=0xFF;
							CanTimeInfoTimer=T2S_1;
							CanTimeSyncDelay=4;
						}
					}
					else
					{
						//ÉèÖÃÊ±¼ä
						RTC_TimeInfo.hours=CanRxInfo.time_info.hour;
						RTC_TimeInfo.minutes=CanRxInfo.time_info.min;
						RTC_TimeInfo.seconds = CanRxInfo.time_info.sec;
#if RTC_TIMER_FUN==1
						RTC_SetTime(RTC_TimeInfo);
#endif
						PostMessage(NAVI_MODULE, MCU_TX_CLOCK,0);
					}
				
				}
				CanTimeSyncRec_Bak=CanTimeSyncRec;
				break;

			case CAN_ID_BCM_SAM_1_G:
		
				if(CanRxInfo.base_info.byte_1.field.f_reverse)
				{
					u16 temp_old;
					u16 temp_now;
					u16 index_old;
					u16 index_now;

					temp_old=CanRxInfo.base_info.swa_msb;
					temp_old<<=8;
					temp_old+=CanRxInfo.base_info.swa_lsb;

					CanRxInfo.base_info.swa_msb=message.Data[0];
					CanRxInfo.base_info.swa_lsb=message.Data[1];
				
					temp_now=CanRxInfo.base_info.swa_msb;
					temp_now<<=8;
					temp_now+=CanRxInfo.base_info.swa_lsb;

					if(temp_old>=0xA1C0)
					{
						index_old=23;
					}
					else if(temp_old>0x8000)
					{
						index_old=((23*(temp_old-0x8000))/(0xA1C0-0x8000));
					}
					else if(temp_old==0x8000)
					{
						index_old=0;
					}
					else if(temp_old>0x5E40)
					{
						index_old=24+((23*(0x8000-temp_old))/(0x8000-0x5E40));
					}
					else
					{
						index_old=46;
					}

					if(temp_now>=0xA1C0)
					{
						index_now=23;
					}
					else if(temp_now>0x8000)
					{
						index_now=((23*(temp_now-0x8000))/(0xA1C0-0x8000));
					}
					else if(temp_now==0x8000)
					{
						index_now=0;
					}
					else if(temp_now>0x5E40)
					{
						index_now=24+((23*(0x8000-temp_now))/(0x8000-0x5E40));
					}
					else
					{
						index_now=46;
					}
					
					if(index_now!=index_old)
					{
						if(CanBaseInfoTimer==0)
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_BASIC_INFO);
							CanBaseInfoTimer=T500MS_1;
						}
						else
						{
							CanRxInfo.base_info.swa_msb=0x80;
							CanRxInfo.base_info.swa_lsb=0x00;
						}
					}
				}
				break;
			case CAN_ID_IPM_2:
				CanRxInfo.air_info.byte_1.field.f_ac_req_cmd=((message.Data[2]&0x20)>>5);
				CanRxInfo.air_info.byte_1.field.f_ac_req_display=((message.Data[2]&0x08)>>3);
				CanRxInfo.air_info.byte_1.field.f_ac_max=((message.Data[3]&0x80)>>7);
				CanRxInfo.air_info.byte_1.field.f_on_off=((message.Data[3]&0x02)>>1);
				CanRxInfo.air_info.byte_1.field.f_disp=(message.Data[4]&0x01);
				CanRxInfo.air_info.byte_1.field.f_wind_speed=(message.Data[2]&0x07);
				CanRxInfo.air_info.byte_2.field.f_wind_mode=((message.Data[3]&0x70)>>4);
				CanRxInfo.air_info.byte_2.field.f_temperature=((message.Data[4]&0xF8)>>3);
				CanRxInfo.air_info.byte_3.field.f_auto_clean=((message.Data[4]&0x04)>>2);
				CanRxInfo.air_info.byte_3.field.f_atuo_ventilation=((message.Data[4]&0x02)>>1);
				CanRxInfo.air_info.byte_3.field.f_internal_external_cir=((message.Data[5]&0x04)>>2);
				if(!strcmp_equal(&CanRxInfo.air_info.byte_1.byte,&CanRxInfoBak.air_info.byte_1.byte,sizeof(CAN_AIR_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.air_info.byte_1.byte,&CanRxInfo.air_info.byte_1.byte,sizeof(CAN_AIR_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_AIR_INFO);
				}
				break;
			case CAN_ID_PEPS_2:
				CanRxInfo.ctrl_feedback_info.byte_1.field.f_intelligent_lock=((message.Data[0]&0x10)>>4) ;
				CanRxInfo.ctrl_feedback_info.byte_1.field.f_welcome_light=((message.Data[0]&0x04)>>2);
				break;
			case CAN_ID_AVM:
				CanRxInfo.avm_info.byte_1.field.f_lr_info=(message.Data[0]&0x3F);
				CanRxInfo.avm_info.byte_2.field.f_rmr_info=(message.Data[1]&0x3F);
				CanRxInfo.avm_info.byte_3.field.f_lmr_info=(message.Data[2]&0x3F);
				CanRxInfo.avm_info.byte_4.field.f_rr_info=(message.Data[3]&0x3F);
				CanRxInfo.avm_info.byte_5.field.f_lf_info=(message.Data[4]&0x1F);
				CanRxInfo.avm_info.byte_6.field.f_rf_info=(message.Data[5]&0x1F);
				CanRxInfo.avm_info.byte_7.field.f_rmf_info=(message.Data[6]&0x1F);
				CanRxInfo.avm_info.byte_7.field.f_radar_voice=(message.Data[6]&0xE0);
				CanRxInfo.avm_info.byte_8.field.f_lmf_info=(message.Data[7]&0x1F);
				if(!strcmp_equal(&CanRxInfo.avm_info.byte_1.byte,&CanRxInfoBak.avm_info.byte_1.byte,sizeof(CAN_AVM_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.avm_info.byte_1.byte,&CanRxInfo.avm_info.byte_1.byte,sizeof(CAN_AVM_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_AVM_INFO);
				}
				break;
			default:
				break;
		}
#if CAN_WAKEUP_FUN==1
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
		CanNoDataTimer=T600S_1;
#endif
		CAN1_ClearErrorTimer();
	}
}

void Tiggo5X_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	u8 flag=1;
	cmd_id=buffer[3];

	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	switch(cmd_id)
	{
		case CHERY_TIGGO5X_TX_MACHINE_INFO:
			switch(buffer[4])
			{	
				case MEDIA_SOURCE_TUNER:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x01;
					if(radio_band<BAND_AM1)
					{
						CanTxInfo.rrm_2_info.byte_1.field.f_fm_am=0x01;
						CanTxInfo.rrm_2_info.frequence_fm_h=MSB(radio_freq*2);
						CanTxInfo.rrm_2_info.frequence_fm_l=LSB(radio_freq*2);
					}
					else
					{
						CanTxInfo.rrm_2_info.byte_1.field.f_fm_am=0x02;
						CanTxInfo.rrm_2_info.frequence_am_h=MSB(radio_freq);
						CanTxInfo.rrm_2_info.frequence_am_l=LSB(radio_freq);
					}
					if(F_TUN_Seeking|F_TUN_ASing|F_TUN_Scaning)
					{
						CanTxInfo.rrm_2_info.byte_1.field.f_as=0x02;
					}
					else
					{
						CanTxInfo.rrm_2_info.byte_1.field.f_as=0x01;
					}
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_USB:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x02;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_SD:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x07;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_BT_MUSIC:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x05;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_OFF:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x00;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x00;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				default:
					flag=0;
					break;
			}
			if(flag)
			{
				CanTxInfoBak.rrm_2_info.byte_1.field.f_source=CanTxInfo.rrm_2_info.byte_1.field.f_source;
				Tiggo5X_PostMessage(CAN_POST_MSG_RRM_2);
			}
			break;
		case CHERY_TIGGO5X_TX_REQUEST_CMD:
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_AIR_INFO);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_CONTROL_INFO);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_AVM_INFO);
			break;
		case CHERY_TIGGO5X_TX_CONTROL_CMD:
			switch(buffer[4])
			{	              
				case CTRL_CMD_REMOTE_LOCK_FEEDBACK:
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_1_info.byte_1.field.f_remote_lock_feedback=0x02;
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_1_info.byte_1.field.f_remote_lock_feedback=0x03;
					}
					else if(buffer[5]==2)
					{
						CanTxInfo.rrm_1_info.byte_1.field.f_remote_lock_feedback=0x01;
					}
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_1);
					break;
				case CTRL_CMD_VOLUME:
					CanTxInfo.rrm_2_info.volume=buffer[5];
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_2);
					break;
				case CTRL_CMD_AUTO_LOCK:
					CanTxInfo.rrm_1_info.byte_1.field.f_auto_lock=buffer[5];
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_1);
					break;
				case CTRL_CMD_DRL:
					CanTxInfo.rrm_1_info.byte_2.field.f_drl=buffer[5];
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_1);
#if CAN_DEBUG_FUN==1
					printf("CTRL_CMD_DRL:param=%x\r\n",buffer[5]);
#endif
					break;
				case CTRL_CMD_OVER_SPEED:
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_1_info.byte_34.field.f_over_speed=0x3F;
					}
					else
					{
						CanTxInfo.rrm_1_info.byte_34.field.f_over_speed=buffer[5];
					}
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_1);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_1);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_1);
					CanTxInfo.rrm_1_info.byte_34.field.f_over_speed = 0x00;
					CanOverSpeedTimer=T3S_1;
					break;
				case CTRL_CMD_BACKLIGHT:
					CanTxInfo.rrm_3_info.instrument_back_light=buffer[5];
					CanTxInfo.rrm_3_info.hour=0xFF;
					CanTxInfo.rrm_3_info.min=0xFF;
					CanTxInfo.rrm_3_info.second=0xFF;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_3);
					CanTxInfo.rrm_3_info.instrument_back_light=0x00;
					break;
				case CTRL_CMD_WELCOM_LIGHT_POLLING:
					CanTxInfo.rrm_5_info.byte_2.field.f_welcom_light_polling=buffer[5];
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_5);
					CanTxInfo.rrm_5_info.byte_2.field.f_welcom_light_polling=0x00;
					break;
				case CTRL_CMD_PEPS_POLLING:
					CanTxInfo.rrm_5_info.byte_2.field.f_peps_polling=buffer[5];
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_5);
					CanTxInfo.rrm_5_info.byte_2.field.f_peps_polling=0x00;
					break;			
				default:
					break;
			}
			break;
		case CHERY_TIGGO5X_TX_LANGUAGE_CMD:
			if(buffer[4]==0x01)
			{
				CanTxInfo.rrm_1_info.byte_34.field.f_language=0x02;
			}
			else if(buffer[4] == 0x02)
			{
				CanTxInfo.rrm_1_info.byte_34.field.f_language=0x01;
			}
			Tiggo5X_PostMessage(CAN_POST_MSG_RRM_1);	
			CanTxInfo.rrm_1_info.byte_34.field.f_language=0x00;
			break;
		case CHERY_TIGGO5X_TX_TIME_SET_CMD:
			CanTxInfo.rrm_3_info.hour=buffer[4];
			CanTxInfo.rrm_3_info.min=buffer[5];
			CanTxInfo.rrm_3_info.second=buffer[6];
			Tiggo5X_PostMessage(CAN_POST_MSG_RRM_3);
			CanTxInfo.rrm_3_info.hour=0xFF;
			CanTxInfo.rrm_3_info.min=0xFF;
			CanTxInfo.rrm_3_info.second=0xFF;

			CanTimeInfoTimer=T2S_1;
			CanTimeSyncDelay=4;
			break;
		case CHERY_TIGGO5X_TX_AIR_SET_CMD:
			switch(buffer[4])
			{
				case AIR_CMD_AC_MAX:
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_4_info.byte_1.field.f_ac_max=0x02;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_4_info.byte_1.field.f_ac_max=0x01;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_1.field.f_ac_max=0x00;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					break;
				case AIR_CMD_WIND_SPEED:
					CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=buffer[5];
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=0x00;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					break;
				case AIR_CMD_WIND_MODEL:
					CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=buffer[5];
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=0x07;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					break;
				case AIR_CMD_TEMP:
					CanTxInfo.rrm_4_info.byte_5.field.f_temperature=buffer[5];
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_5.field.f_temperature=0x00;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					break;
				case AIR_CMD_AUTO_CLEAN:
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_auto_clear=0x02;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_auto_clear=0x01;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_6.field.f_auto_clear=0x00;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					break;
				case AIR_CMD_AUTO_VENTILATION:
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_auto_ventilation=0x02;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_auto_ventilation=0x01;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_6.field.f_auto_ventilation=0x00;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					break;
				case AIR_CMD_AC:
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_ac=0x02;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_ac=0x01;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_6.field.f_ac=0x00;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);					
					break;
				case AIR_CMD_SW:
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_air_sw=0x02;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_air_sw=0x01;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_6.field.f_air_sw=0x00;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);					
					break;
				case AIR_CMD_CIRCLE:
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_4_info.byte_7.field.f_circle=0x01;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_4_info.byte_7.field.f_circle=0x02;
						Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_7.field.f_circle=0x00;
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);					
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void Tiggo5X_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 error_flag=0;
	u8 checksum=0;
	
	*length=0;
	buffer[0]=TIGGO5X_HEAD_CODE0;	
	buffer[1]=TIGGO5X_HEAD_CODE1;	
	buffer[3]=cmd_id;
	checksum+=buffer[3];
	switch(cmd_id)
	{
		case CHERY_TIGGO5X_RX_BASIC_INFO:
			buffer[2]=3;
			buffer[4]=CanRxInfo.base_info.byte_1.byte;
			buffer[5]=CanRxInfo.base_info.swa_msb;
			buffer[6]=CanRxInfo.base_info.swa_lsb;
			break;
		case CHERY_TIGGO5X_RX_DETAIL_INFO:
			buffer[2]=1;
			buffer[4]=CanRxInfo.detail_info.byte_1.byte;
			break;
		case CHERY_TIGGO5X_RX_AIR_INFO:
			buffer[2]=3;
			buffer[4]=CanRxInfo.air_info.byte_1.byte;
			buffer[5]=CanRxInfo.air_info.byte_2.byte;
			buffer[6]=CanRxInfo.air_info.byte_3.byte;
			break;
		case CHERY_TIGGO5X_RX_CONTROL_INFO:
			buffer[2]=3;
			buffer[4]=CanRxInfo.ctrl_feedback_info.byte_1.byte;
			buffer[5]=CanRxInfo.ctrl_feedback_info.byte_2.byte;
			buffer[6]=CanRxInfo.ctrl_feedback_info.byte_3.byte;
#if CAN_DEBUG_FUN==1
			printf("CHERY_TIGGO5X_RX_CONTROL_INFO:byte3=%x,byte4=%x\r\n",buffer[6],buffer[7]);
#endif
			break;
		case CHERY_TIGGO5X_RX_AVM_INFO:
			buffer[2]=8;
			buffer[4]=CanRxInfo.avm_info.byte_1.byte;
			buffer[5]=CanRxInfo.avm_info.byte_2.byte;
			buffer[6]=CanRxInfo.avm_info.byte_3.byte;
			buffer[7]=CanRxInfo.avm_info.byte_4.byte;
			buffer[8]=CanRxInfo.avm_info.byte_5.byte;
			buffer[9]=CanRxInfo.avm_info.byte_6.byte;
			buffer[10]=CanRxInfo.avm_info.byte_7.byte;
			buffer[11]=CanRxInfo.avm_info.byte_8.byte;
			break;
		default:
			error_flag=1;
			break;
	}
	if(error_flag==0)
	{
		checksum+=buffer[2];
		for(i=0;i<buffer[2];i++)
		{
			checksum+=buffer[i+4];
		}
		checksum-=1;
		checksum&=0xFF;
		*length=buffer[2]+5;
		buffer[(*length)-1]=checksum;
	}
}

void Tiggo5X_MainPro(void)
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
#if CAN_WAKEUP_FUN==1
	if(CanNoDataTimer)
	{
		CanNoDataTimer--;
		if(CanNoDataTimer==0)
		{
			F_CAN_RX_DATA=0;
		}
	}
#endif
	if(CanTxCanTimer)
	{
		CanTxCanTimer--;
	}
	if(CanTxAppTimer)
	{
		CanTxAppTimer--;
	}
	if(CanBaseInfoTimer)
	{
		CanBaseInfoTimer--;
	}
	if(CanOverSpeedTimer)
	{
		CanOverSpeedTimer--;
	}
	if(AvmCalibrationTimeout)
	{
		AvmCalibrationTimeout--;
		if(AvmCalibrationTimeout==0)
		{
			AvmCalibrationFlag=0;
		}
	}
	if(CanTimeInfoTimer)
	{
		CanTimeInfoTimer--;
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

	Tiggo5X_Rx_Message();

	if(CanTxTimer)
	{
		CanTxTimer--;
	}
	if(CanTxTimer==0)
	{
		CanTxTimer=T50MS_1;
		if(F_CAN_INIT)
		{
			CAN1_Transmit();
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
			CanMainState=CAN_MAIN_INIT;
			break;
		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			F_CAN_SLEEP=0;
			//F_CAN_SLEEP=1;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			F_CAN_READY=0;
			F_DRIVER_DOOR_STATE=0;
			F_AVM_CALIBRATION=0;
			CanNoDataTimer=T60S_1;
			CanMainState=CAN_MAIN_WAIT_ACC;
			CanMainTimer=T2S_1;
			CanTimeSyncDelay=4;
			break;
		case CAN_MAIN_WAIT_ACC:
			if(Get_ACC_Det_Flag)
			{
				CanMainState=CAN_MAIN_TX_POWER_OFF;
			}
			else if(CanMainTimer==0)
			{
				CanMainState=CAN_MAIN_WAIT_SLEEP;
			}
			break;
		case CAN_MAIN_TX_POWER_OFF:
			FormatMemery(&CanTxInfo.rrm_2_info.byte_1.byte,sizeof(CAN_RRM_2_INFO));
			Tiggo5X_PostMessage(CAN_POST_MSG_RRM_2);
			CanMainState=CAN_MAIN_TX_POWER_ON;
			CanMainTimer=T2S_1;
			break;
		case CAN_MAIN_TX_POWER_ON:
			if(CanMainTimer)
			{
				break;
			}
			CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
			Tiggo5X_PostMessage(CAN_POST_MSG_RRM_2);
			CanMainState=CAN_MAIN_NORMAL;
			FictitiousPowerOffFlag=F_FICTITIOUS_POWER_OFF;
			break;
		case CAN_MAIN_NORMAL:
#if CAN_WAKEUP_FUN==1
			if(F_CAN_RX_DATA==0)
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}
			else 
#endif
			if(Get_ACC_Det_Flag==0)
			{
				CanMainState=CAN_MAIN_WAIT_SLEEP;
			}
			else
			{
				if(APP_READY==APP_Status)
				{
					if(!strcmp_equal(&CanRxInfo.air_info.byte_1.byte,&CanRxInfoBak.air_info.byte_1.byte,sizeof(CAN_AIR_INFO)))
					{
						Mem_strcpy(&CanRxInfoBak.air_info.byte_1.byte,&CanRxInfo.air_info.byte_1.byte,sizeof(CAN_AIR_INFO));
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_AIR_INFO);
#if CAN_DEBUG_FUN==1
						printf("MCU_TX_CAN_BOX_INFO:CHERY_TIGGO5X_RX_AIR_INFO\r\n");
#endif
					}
					if(CanTxAppTimer==0)
					{
						CanTxAppTimer=T5S_1;
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_AIR_INFO);
						}
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_CONTROL_INFO);
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO5X_RX_AVM_INFO);
#if CAN_DEBUG_FUN==1
						printf("MCU_TX_CAN_BOX_INFO:period==5s \r\n");
#endif
					}
				}
				if(CanTxCanTimer==0)
				{
					CanTxCanTimer=T500MS_1;
					if(F_CAN_READY)
					{
	    					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_1);
	    					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_2);
	    					Tiggo5X_PostMessage(CAN_POST_MSG_RRM_4);
					}
				}
				if(CanTurnOnVolume!=TurnOn_Volume)
				{
				    CanTurnOnVolume = TurnOn_Volume;
				    CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
				    Tiggo5X_PostMessage(CAN_POST_MSG_RRM_2);
				}
			}
			break;
		case CAN_MAIN_WAIT_SLEEP:
#if CAN_WAKEUP_FUN==1
			if(F_CAN_RX_DATA==0)
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}

			if(Get_ACC_Det_Flag==1)
			{	
				CanMainState=CAN_MAIN_NORMAL;
				FictitiousPowerOffFlag=F_FICTITIOUS_POWER_OFF;
			}
#else
			if(Get_ACC_Det_Flag==1)
			{	
				CanMainState=CAN_MAIN_NORMAL;
				FictitiousPowerOffFlag=F_FICTITIOUS_POWER_OFF;
			}
			else
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}
#endif

			break;
		case CAN_MAIN_SLEEP_CFG:
			CAN1_ClearRxMessage();
			CAN_IC_STANDBY_ON;
			F_CAN_SLEEP=1;
			F_CAN_INTERRUPT=0;
			CanMainTimer=T100MS_1;
			CanMainState=CAN_MAIN_SLEEP;
			break;
		case CAN_MAIN_SLEEP:
			if(CanMainTimer)
			{
				break;
			}
#if CAN_WAKEUP_FUN==1
			if(F_CAN_SLEEP==0
				||F_CAN_INTERRUPT)
#else
			if(Get_ACC_Det_Flag==1)
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

