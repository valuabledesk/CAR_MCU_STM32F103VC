#include "public.h"

#if CAN_FUN_PEUGEOT_207==1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
DIALOG_INFO DialogInfo;
DIALOG_INFO DialogInfoBak;
DIALOG_MESSAGE_BUFFER DialogMessageBuffer;
DIALOG_MESSAGE_NOW DialogMessageNow;
DIALOG_MESSAGE_TX_STATE DialogMessageTxState;
DIALOG_MESSAGE_TX_FLAG DialogTxFlag;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
u32 DialogFrameID;
u32 CanMainTimer;
u32 CanNormalTimer;
u32 CanNoDataTimer;
u16 CanTxTimer1;
u16 CanTxTimer2;
u8 DialogTimerExclusion;
u8 DialogTimerWait;
u8 DialogTimerTimeout;
u8 RadarLevel[3];
u8 RadarLevelBak[3];
u8 ReverseFlag_EcoMux;
u8 ReverseFlag_SMS;
u8 Peugeot207_Date;


u32 Trip_Mileage_Current;
u8 Trip_Switch_status;
DIALOG_TRIP_INFO Trip_info1_Bak;
DIALOG_TRIP_INFO Trip_info2_Bak;


void GregorianToPersian(int *j_year,int *j_month,int *j_day,int g_year,int g_month,int g_day)
{

    int g_days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int j_days_in_month[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
    int gy, gm, gd;
    int jy, jm, jd;
    long g_day_no, j_day_no;
    int j_np;

    int i;

    gy = g_year-1600;
    gm = g_month-1;
    gd = g_day-1;

    g_day_no = 365*gy+(gy+3)/4-(gy+99)/100+(gy+399)/400;
    for (i=0;i<gm;++i)
        g_day_no += g_days_in_month[i];
    if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
        /* leap and after Feb */
        ++g_day_no;
    g_day_no += gd;

    j_day_no = g_day_no-79;

    j_np = j_day_no / 12053;
    j_day_no %= 12053;

    jy = 979+33*j_np+4*(j_day_no/1461);
    j_day_no %= 1461;

    if (j_day_no >= 366) {
        jy += (j_day_no-1)/365;
        j_day_no = (j_day_no-1)%365;  //
    }

    for (i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i) {
        j_day_no -= j_days_in_month[i];
    }

    jm = i+1;
    jd = j_day_no+1;

    *j_year = jy;
    *j_month = jm;
    *j_day = jd;


}


	

void PostDialogMessage(DIALOG_DATA_FRAME *message,u32 frame_num)
{
	if((DialogMessageBuffer.num+frame_num)<MAX_DIALOG_MESSAGE_NUM
		&&frame_num<=MAX_DIALOG_FRAME_NUM)
	{
		u32 i;

		DialogFrameID++;
		for(i=0;i<frame_num;i++)
		{
			DialogMessageBuffer.message[DialogMessageBuffer.tail]=*message;
			DialogMessageBuffer.message[DialogMessageBuffer.tail].frame_id=DialogFrameID;
			DialogMessageBuffer.tail=(DialogMessageBuffer.tail+1)%MAX_DIALOG_MESSAGE_NUM;
			message++;
		}
		DialogMessageBuffer.num+=frame_num;
	}
}

DIALOG_MESSAGE GetDialogMessage(void)
{
	DIALOG_MESSAGE message;
	u32 frame_id;
	u32 i;
	u32 j;

	FormatMemery(&message.frame_num,sizeof(DIALOG_MESSAGE));
	if(DialogMessageBuffer.num)
	{
		frame_id=DialogMessageBuffer.message[DialogMessageBuffer.head].frame_id;
		for(i=0;i<MAX_DIALOG_FRAME_NUM;i++)
		{
			if(frame_id==DialogMessageBuffer.message[DialogMessageBuffer.head].frame_id)
			{
				message.frame[i]=DialogMessageBuffer.message[DialogMessageBuffer.head];

				DialogMessageBuffer.message[DialogMessageBuffer.head].frame_id=0;
				DialogMessageBuffer.message[DialogMessageBuffer.head].byte1.byte=0;
				DialogMessageBuffer.message[DialogMessageBuffer.head].data_id=0;
				for(j=0;j<MAX_DIALOG_FRAME_DATA_LENGTH;j++)
				{
					DialogMessageBuffer.message[DialogMessageBuffer.head].data[j]=0;
				}
				
				DialogMessageBuffer.head=(DialogMessageBuffer.head+1)%MAX_DIALOG_MESSAGE_NUM;
				DialogMessageBuffer.num--;
			}
			else
			{
				break;
			}
		}
		message.frame_num=i;
	}
	return message;
}

void ClearDialogMessage(void)
{
	u32 i;
	u32 j;
	
	DialogMessageBuffer.head=0;
	DialogMessageBuffer.tail=0;
	DialogMessageBuffer.num=0;
	for(i=0;i<MAX_DIALOG_MESSAGE_NUM;i++)
	{
		DialogMessageBuffer.message[i].frame_id=0;
		DialogMessageBuffer.message[i].byte1.byte=0;
		DialogMessageBuffer.message[i].data_id=0;
		for(j=0;j<MAX_DIALOG_FRAME_NUM;j++)
		{
			DialogMessageBuffer.message[i].data[j]=0;
		}
	}
}

void DialogMessageTxPro(void)
{
	if(DialogTimerTimeout)
	{
		DialogTimerTimeout--;
	}
	if(DialogTimerWait)
	{
		DialogTimerWait--;
	}
	if(DialogTimerExclusion)
	{
		DialogTimerExclusion--;
	}
	switch(DialogMessageTxState)
	{
		case DIALOG_MSG_IDLE:
			{
				DIALOG_MESSAGE message;
				u32 i;
				
				if(DialogTimerExclusion)
				{
					break;
				}
				message=GetDialogMessage();
				DialogMessageNow.index=0;
				for(i=0;i<MAX_DIALOG_FRAME_NUM;i++)
				{
					DialogMessageNow.frame[i]=message.frame[i];
				}
				DialogMessageNow.frame_num=message.frame_num;
				if(DialogMessageNow.frame_num)
				{
					DialogMessageTxState=DIALOG_MSG_TX;
					DialogTimerTimeout=T60MS_1;
				}
			}
			break;
		case DIALOG_MSG_TX:
			{
				u8 data[8];
				u32 i;

				if(DialogTimerExclusion)
				{
					break;
				}

				data[0]=DialogMessageNow.frame[DialogMessageNow.index].byte1.byte;
				data[1]=DialogMessageNow.frame[DialogMessageNow.index].data_id;
				for(i=0;i<MAX_DIALOG_FRAME_DATA_LENGTH;i++)
				{
					data[i+2]=DialogMessageNow.frame[DialogMessageNow.index].data[i];
				}
				CAN1_TxFrame(CAN_ID_MMS_MESSAGE,data,8);
				DialogTxFlag.byte=0;
				DialogTimerWait=T20MS_1;
				DialogTimerExclusion=T50MS_1;
				DialogMessageTxState=DIALOG_MSG_WAIT;
			}
			break;
		case DIALOG_MSG_WAIT:
			if(DialogTxFlag.byte==DialogMessageNow.frame[DialogMessageNow.index].byte1.byte)
			{
				DialogMessageNow.index++;
				if(DialogMessageNow.index==DialogMessageNow.frame_num)
				{
					DialogMessageTxState=DIALOG_MSG_IDLE;
				}
				else
				{
					DialogMessageTxState=DIALOG_MSG_TX;
					DialogTimerTimeout=T60MS_1;
				}
			}
			else
			{
				if(DialogTimerTimeout==0)
				{
					DialogMessageTxState=DIALOG_MSG_IDLE;
				}
				else if(DialogTimerWait==0)
				{
					DialogMessageTxState=DIALOG_MSG_TX;
					DialogTimerExclusion=0;
				}
			}
			break;
		default:
			break;
	}
}

void Peugeot207_TripCompare(void)
{
	if(DialogInfo.Trip_status.Trip_info1_flag)
	{
		DialogInfo.Trip_status.Trip_info1.Trip_Distance = 
				Trip_Mileage_Current - CanRxInfo.trip_info.Total_info1.Total_distance;
				
		DialogInfo.Trip_status.Trip_info1.Trip_Duration = CanRxInfo.trip_info.Total_info1.Total_duration/60;
	
		if(DialogInfo.Trip_status.Trip_info1.Trip_Duration)
		{
			DialogInfo.Trip_status.Trip_info1.Trip_Speed = 
				DialogInfo.Trip_status.Trip_info1.Trip_Distance * 60 / DialogInfo.Trip_status.Trip_info1.Trip_Duration;
		}
	
		if(!strcmp_equal((u8*)&Trip_info1_Bak.Trip_Distance,(u8*)&DialogInfo.Trip_status.Trip_info1.Trip_Distance,6))
		{
			Mem_strcpy((u8*)&Trip_info1_Bak.Trip_Distance,(u8*)&DialogInfo.Trip_status.Trip_info1.Trip_Distance,6);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_TRIP_INFO1);
		}
	}

	if(DialogInfo.Trip_status.Trip_info2_flag)
	{
		DialogInfo.Trip_status.Trip_info2.Trip_Distance = 
				Trip_Mileage_Current - CanRxInfo.trip_info.Total_info2.Total_distance;
			
		DialogInfo.Trip_status.Trip_info2.Trip_Duration = CanRxInfo.trip_info.Total_info2.Total_duration/60;

		if(DialogInfo.Trip_status.Trip_info2.Trip_Duration)
		{
			DialogInfo.Trip_status.Trip_info2.Trip_Speed = 
				DialogInfo.Trip_status.Trip_info2.Trip_Distance * 60 / DialogInfo.Trip_status.Trip_info2.Trip_Duration;
		}
		
		if(!strcmp_equal((u8*)&Trip_info2_Bak.Trip_Distance,(u8*)&DialogInfo.Trip_status.Trip_info2.Trip_Distance,6))
		{
			Mem_strcpy((u8*)&Trip_info2_Bak.Trip_Distance,(u8*)&DialogInfo.Trip_status.Trip_info2.Trip_Distance,6);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_TRIP_INFO2);
		}
	}

}


void Peugeot207_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_NMM_C_1:
				{
					u32 temp;

					temp=(message.Data[0]&0x07);

					switch(temp)
					{
						case 0:
							F_CAN_RX_SLEEP=1;
							CanNormalTimer=T10S_1;
							break;
						case 1:
							F_CAN_RX_NORMAL=1;
							CanNormalTimer=T60S_1;
							break;
						case 2:
							F_CAN_RX_ENTER_SLEEP=1;
							CanNormalTimer=T10S_1;
							break;
						case 3:
							F_CAN_RX_WAKEUP=1;
							CanNormalTimer=T60S_1;
							break;
						default:
							break;
					}
				}
				break;
			case CAN_ID_CCNC1_C:
				CanRxInfo.base_info.byte_1.field.f_start_status=(message.Data[4]&0x03);
				CanRxInfo.base_info.byte_2.field.f_bonnet=!GetBit((message.Data[4]),2);
				break;
			case CAN_ID_FEI_F:
				if(CanRxInfo.base_info.byte_1.field.f_start_status>1)
				{
					ReverseFlag_SMS=GetBit((message.Data[0]),4);
				}
				else
				{
					ReverseFlag_SMS=0;
				}
				break;
			case CAN_ID_NMM_C_2:
				{
					u32 temp;

					temp=(message.Data[0]&0x07);

					switch(temp)
					{
						case 0:
							F_CAN_RX_SLEEP=1;
							CanNormalTimer=T10S_1;
							break;
						case 1:
							F_CAN_RX_NORMAL=1;
							CanNormalTimer=T60S_1;
							break;
						case 2:
							F_CAN_RX_ENTER_SLEEP=1;
							CanNormalTimer=T10S_1;
							break;
						case 3:
							F_CAN_RX_WAKEUP=1;
							CanNormalTimer=T60S_1;
							break;
						default:
							break;
					}
				}
				break;
			case CAN_ID_MTC_SGL:
				CanRxInfo.cluster_info.warning_info1.field.f_change_engine_oil=GetBit((message.Data[0]),0);
				CanRxInfo.cluster_info.warning_info1.field.f_change_air_filter=GetBit((message.Data[0]),1);
				CanRxInfo.cluster_info.warning_info1.field.f_change_oil_filter=GetBit((message.Data[0]),2);
				break;
			case CAN_ID_BACKL_IC:
				{
					u32 temp;
					u32 value;
					
					CanRxInfo.base_info.byte_1.field.f_illumi_level=message.Data[0]&0x07;
					switch(CanRxInfo.base_info.byte_1.field.f_illumi_level)
					{
						case 0:
							temp=5;
							break;
						case 1:
							temp=20;
							break;
						case 2:
							temp=35;
							break;
						case 3:
							temp=50;
							break;
						case 4:
							temp=65;
							break;
						case 5:
							temp=80;
							break;
						case 6:
							temp=100;
							break;
						default:
							temp=100;
							break;
					}
					value=KEY_LED_PERCENT_MIN+(((KEY_LED_PERCENT_MAX-KEY_LED_PERCENT_MIN)*temp)/100);
					CanGeneralCtrlFlag.field.illumi_level=value;
				}
				break;
			case CAN_ID_CCNGW1_C:
#if MODEL==LINUX_D068_55||MODEL==LINUX_D065_55
				CanRxInfo.radar_info.byte_2.field.f_buzzer_warning=(message.Data[5]&0x03);
				CanRxInfo.radar_info.distance=message.Data[6];
				CanRxInfo.radar_info.byte_1.field.f_error_sensor_1=GetBit((message.Data[5]),2);
				CanRxInfo.radar_info.byte_1.field.f_error_sensor_2=GetBit((message.Data[5]),3);
				CanRxInfo.radar_info.byte_1.field.f_error_sensor_3=GetBit((message.Data[5]),4);
				CanRxInfo.radar_info.byte_1.field.f_error_sensor_4=GetBit((message.Data[5]),5);
				CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_1=(message.Data[7]&0x03);
				CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_2=((message.Data[7]&0x0C)>>2);
				CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_3=((message.Data[7]&0x30)>>4);
				CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_4=((message.Data[7]&0xC0)>>6);
				if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_1==0)
				{
					CanRxInfo.radar_info.distance_1=30;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_1==1)
				{
					CanRxInfo.radar_info.distance_1=80;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_1==2)
				{
					CanRxInfo.radar_info.distance_1=130;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_1==3)
				{
					CanRxInfo.radar_info.distance_1=0xFF;
				}
				if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_2==0)
				{
					CanRxInfo.radar_info.distance_2=30;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_2==1)
				{
					CanRxInfo.radar_info.distance_2=80;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_2==2)
				{
					CanRxInfo.radar_info.distance_2=130;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_2==3)
				{
					CanRxInfo.radar_info.distance_2=0xFF;
				}
				if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_3==0)
				{
					CanRxInfo.radar_info.distance_3=30;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_3==1)
				{
					CanRxInfo.radar_info.distance_3=80;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_3==2)
				{
					CanRxInfo.radar_info.distance_3=130;
				}
				else if(CanRxInfo.radar_info.byte_3.field.f_buzzer_warning_3==3)
				{
					CanRxInfo.radar_info.distance_3=0xFF;
				}
				if(CanRxInfo.radar_info.distance_1>150)
				{
					RadarLevel[0]=3;
				}
				else
				{
					RadarLevel[0]=CanRxInfo.radar_info.distance_1/51;
				}
				if(CanRxInfo.radar_info.distance_2>150)
				{
					RadarLevel[1]=3;
				}
				else
				{
					RadarLevel[1]=CanRxInfo.radar_info.distance_2/51;
				}
				if(CanRxInfo.radar_info.distance_3>150)
				{
					RadarLevel[2]=3;
				}
				else
				{
					RadarLevel[2]=CanRxInfo.radar_info.distance_3/51;
				}
				
				CanRxInfo.cluster_info.engine_rpm_info.byte[0]=message.Data[1];
				CanRxInfo.cluster_info.engine_rpm_info.byte[1]=message.Data[0];
				CanRxInfo.cluster_info.speed_info.byte[0]=message.Data[3]&0x0F;
				CanRxInfo.cluster_info.speed_info.byte[1]=message.Data[2];
#endif
				break;
			case CAN_ID_VIN1_MM:
				{
					u32 i;
					
					for(i=0;i<8;i++)
					{
						CanRxInfo.vin_info[i]=message.Data[i];
					}
				}
				break;
			case CAN_ID_LS_BCM_HS3:
				CanRxInfo.base_info.byte_1.field.f_start_status=(message.Data[3]&0x03);
				CanRxInfo.base_info.byte_2.field.f_front_left_door=GetBit((message.Data[1]),0);
				CanRxInfo.base_info.byte_2.field.f_front_right_door=GetBit((message.Data[1]),1);
				CanRxInfo.base_info.byte_2.field.f_rear_left_door=GetBit((message.Data[1]),2);
				CanRxInfo.base_info.byte_2.field.f_rear_right_door=GetBit((message.Data[1]),3);
				CanRxInfo.base_info.byte_2.field.f_trunk=GetBit((message.Data[1]),4);
				CanRxInfo.base_info.byte_2.field.f_bonnet=GetBit((message.Data[1]),5);
				CanGeneralCtrlFlag.field.ill_onoff = GetBit((message.Data[0]),2);
				break;
			case CAN_ID_ICN_INFO1:
				CanRxInfo.cluster_info.remaining_distance_info.byte[0]=(message.Data[1]&0x0F);
				CanRxInfo.cluster_info.remaining_distance_info.byte[1]=message.Data[0];
				CanRxInfo.cluster_info.average_speed=message.Data[2];
				break;
			case CAN_ID_VIN2_MM:
				{
					u32 i;
					
					for(i=0;i<8;i++)
					{
						CanRxInfo.vin_info[i+8]=message.Data[i];
					}
				}
				break;
			case CAN_ID_PASD_C:
				break;
			case CAN_ID_VIN3_MM:
				{
					u32 i;
					
					for(i=0;i<8;i++)
					{
						CanRxInfo.vin_info[i+16]=message.Data[i];
					}
				}
				break;
			case CAN_ID_FAM_INFO:
				if(CanRxInfo.base_info.byte_1.field.f_start_status>1)
				{
					ReverseFlag_EcoMux=GetBit((message.Data[1]),0);
				}
				else
				{
					ReverseFlag_EcoMux=0;
				}
				break;
			case CAN_ID_FDS_D:
				CanRxInfo.base_info.byte_2.field.f_front_left_door=!GetBit((message.Data[0]),5);
				CanRxInfo.base_info.byte_2.field.f_front_right_door=!GetBit((message.Data[1]),0);
				break;
			case CAN_ID_RDS_R:
				CanRxInfo.base_info.byte_2.field.f_rear_left_door=!GetBit((message.Data[1]),0);
				CanRxInfo.base_info.byte_2.field.f_rear_right_door=!GetBit((message.Data[1]),1);
				CanRxInfo.base_info.byte_2.field.f_trunk=!GetBit((message.Data[1]),2);
				break;
			case CAN_ID_CLUSTER_ODO:
				{
					u32 temp;
					u32 value;
					
					CanRxInfo.base_info.byte_1.field.f_illumi_level=message.Data[4]&0x07;
					Trip_Mileage_Current = ((message.Data[3]<<24) + (message.Data[2]<<16) + (message.Data[1]<<8) + message.Data[0])/1000;
#if MODEL==LINUX_P058_55
					CanRxInfo.cluster_info.speed_info.byte[0]=message.Data[7]&0x0F;
					CanRxInfo.cluster_info.speed_info.byte[1]=message.Data[6];
					CanRxInfo.cluster_info.warning_info5.field.f_lowFuel_level_warning = GetBit(message.Data[5],0);
#endif
					switch(CanRxInfo.base_info.byte_1.field.f_illumi_level)
					{
						case 1:
							temp=5;
							break;
						case 2:
							temp=20;
							break;
						case 3:
							temp=35;
							break;
						case 4:
							temp=50;
							break;
						case 5:
							temp=65;
							break;
						case 6:
							temp=80;
							break;
						case 7:
							temp=100;
							break;
						default:
							temp=100;
							break;
					}
					value=KEY_LED_PERCENT_MIN+(((KEY_LED_PERCENT_MAX-KEY_LED_PERCENT_MIN)*temp)/100);
					CanGeneralCtrlFlag.field.illumi_level=value;
					TFT_Backlight_CAN_Level = ((temp*(BACKLIGHT_PERCENT_MAX-BACKLIGHT_PERCENT_MIN))/100)+BACKLIGHT_PERCENT_MIN;
				}
				break;
			case CAN_ID_FOS_F:
				if(message.Data[0]&0x03)
				{
					CanRxInfo.cluster_info.warning_info2.field.f_main_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info2.field.f_main_lamps=0;
				}
				if(message.Data[0]&0x0C)
				{
					CanRxInfo.cluster_info.warning_info2.field.f_dipped_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info2.field.f_dipped_lamps=0;
				}
				if(message.Data[0]&0xC0)
				{
					CanRxInfo.cluster_info.warning_info2.field.f_indicator_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info2.field.f_indicator_lamps=0;
				}
				if(message.Data[1]&0x03)
				{
					CanRxInfo.cluster_info.warning_info2.field.f_fog_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info2.field.f_fog_lamps=0;
				}
				break;
			case CAN_ID_ROS_R:
				if(message.Data[0]&0x03)
				{
					CanRxInfo.cluster_info.warning_info3.field.f_stop_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info3.field.f_stop_lamps=0;
				}
				if(message.Data[0]&0x0C)
				{
					CanRxInfo.cluster_info.warning_info3.field.f_reverse_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info3.field.f_reverse_lamps=0;
				}
				if(message.Data[0]&0xC0)
				{
					CanRxInfo.cluster_info.warning_info3.field.f_indicator_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info3.field.f_indicator_lamps=0;
				}
				if(message.Data[1]&0x03)
				{
					CanRxInfo.cluster_info.warning_info3.field.f_fog_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info3.field.f_fog_lamps=0;
				}
				break;
			case CAN_ID_BCM_EMS67:
				CanRxInfo.cluster_info.engine_rpm_info.byte[0]=message.Data[2];
				CanRxInfo.cluster_info.engine_rpm_info.byte[1]=message.Data[1];
				CanRxInfo.cluster_info.battery_voltage = message.Data[7];
				//if(message.Data[2]>0||message.Data[1]>0)
				if(CanRxInfo.cluster_info.engine_rpm_info.engine_rpm>500)
				{
					CanRxInfo.trip_info.Rpm_engine_flag=1;
					//CanRxInfo.trip_info.Total_info1.Total_duration++;
					//CanRxInfo.trip_info.Total_info2.Total_duration++;
				}
				else
				{
					CanRxInfo.trip_info.Rpm_engine_flag=0;
				}
				break;
			case CAN_ID_BCM_PAS:
				CanRxInfo.radar_info.byte_2.field.f_buzzer_warning=((message.Data[0]&0x1C)>>2);
				CanRxInfo.radar_info.distance_1=message.Data[1];
				CanRxInfo.radar_info.distance_2=message.Data[3];
				CanRxInfo.radar_info.distance_3=message.Data[2];
				CanRxInfo.radar_info.byte_1.field.f_error_sensor_1=GetBit((message.Data[5]),0);
				CanRxInfo.radar_info.byte_1.field.f_error_sensor_2=GetBit((message.Data[5]),1);
				CanRxInfo.radar_info.byte_1.field.f_error_sensor_3=GetBit((message.Data[5]),2);
				if(CanRxInfo.radar_info.distance_1>150)
				{
					RadarLevel[0]=3;
				}
				else
				{
					RadarLevel[0]=CanRxInfo.radar_info.distance_1/51;
				}
				if(CanRxInfo.radar_info.distance_2>150)
				{
					RadarLevel[1]=3;
				}
				else
				{
					RadarLevel[1]=CanRxInfo.radar_info.distance_2/51;
				}
				if(CanRxInfo.radar_info.distance_3>150)
				{
					RadarLevel[2]=3;
				}
				else
				{
					RadarLevel[2]=CanRxInfo.radar_info.distance_3/51;
				}
				break;
			case CAN_ID_LS_BCM_OS:
#if MODEL==LINUX_D068_55||MODEL==LINUX_D065_55
				if(message.Data[1]&0x08)
				{
					CanRxInfo.cluster_info.warning_info3.field.f_stop_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info3.field.f_stop_lamps=0;
				}
				if(message.Data[1]&0x04)
				{
					CanRxInfo.cluster_info.warning_info3.field.f_reverse_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info3.field.f_reverse_lamps=0;
				}
				if(message.Data[1]&0x02)
				{
					CanRxInfo.cluster_info.warning_info3.field.f_fog_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info3.field.f_fog_lamps=0;
				}
#else
				CanRxInfo.cluster_info.warning_info4.field.f_LH_Indicator_Lamp = GetBit(message.Data[0],0);
				CanRxInfo.cluster_info.warning_info4.field.f_RH_Indicator_Lamp = GetBit(message.Data[0],1);
				CanRxInfo.cluster_info.warning_info4.field.f_Side_Lamp = GetBit(message.Data[1],0);
				CanRxInfo.cluster_info.warning_info4.field.f_Rear_Fog_Lamp = GetBit(message.Data[1],1);
				CanRxInfo.cluster_info.warning_info4.field.f_Reverse_Lamp = GetBit(message.Data[1],2);
				CanRxInfo.cluster_info.warning_info4.field.f_Stop_Lamp = GetBit(message.Data[1],3);
#endif
				break;
			case CAN_ID_FAM_OS:
#if MODEL==LINUX_D068_55||MODEL==LINUX_D065_55
				if(message.Data[0]&0x0C)
				{
					CanRxInfo.cluster_info.warning_info2.field.f_main_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info2.field.f_main_lamps=0;
				}
				if(message.Data[0]&0x03)
				{
					CanRxInfo.cluster_info.warning_info2.field.f_dipped_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info2.field.f_dipped_lamps=0;
				}	
				if(message.Data[0]&0x20)
				{
					CanRxInfo.cluster_info.warning_info2.field.f_fog_lamps=1;
				}
				else
				{
					CanRxInfo.cluster_info.warning_info2.field.f_fog_lamps=0;
				}
#else
				CanRxInfo.cluster_info.warning_info5.field.f_LH_Dipped_Lamp = GetBit(message.Data[0],0);
				CanRxInfo.cluster_info.warning_info5.field.f_RH_Dipped_Lamp = GetBit(message.Data[0],1);
				CanRxInfo.cluster_info.warning_info5.field.f_LH_Main_Lamp = GetBit(message.Data[0],2);
				CanRxInfo.cluster_info.warning_info5.field.f_RH_Main_Lamp = GetBit(message.Data[0],3);
				CanRxInfo.cluster_info.warning_info5.field.f_Front_Fog_lamp = GetBit(message.Data[0],5);
#endif
				break;
			case CAN_ID_TEMP_AMBT:
				CanRxInfo.base_info.Ambient_Temperature = message.Data[0];
				break;	
			//case CAN_ID_CCN_TPMS_SMS:
			//case CAN_ID_CCN_TPMS_ECO:
			case CAN_ID_CCN_TPMS_COMMON:
				CanRxInfo.tpms_info.Tpms_ID = ((message.Data[0]>>4)&0x07)+0x01;
				CanRxInfo.tpms_info.Tpms_TirePressure = message.Data[2];
				CanRxInfo.tpms_info.Tpms_Temperature = message.Data[3];
				CanRxInfo.tpms_info.Tpms_Warning.field.f_SystemStatus = (message.Data[0]&0x07)==0?0:1;
				CanRxInfo.tpms_info.Tpms_Warning.field.f_TireInformation = message.Data[0]>>7;
				CanRxInfo.tpms_info.Tpms_Warning.field.f_TireLeakage = (message.Data[1])&0x03;
				CanRxInfo.tpms_info.Tpms_Warning.field.f_LearningStatus = (message.Data[1]>>2)&0x03;
				CanRxInfo.tpms_info.Tpms_Warning.field.f_TirePresstureStatus = (message.Data[1]>>4)&0x03;
				CanRxInfo.tpms_info.Tpms_Warning.field.f_TireTemperatureStatus = (message.Data[1]>>6&0x03)==0?0:1;
				CanRxInfo.tpms_info.Tpms_Warning.field.f_TireBatteryPowerStatus = (message.Data[5])&0x03;
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_TPMS_INFO);
				break;
			default:
				break;
		}
		F_CAN_RX_DATA=1;
		CanNoDataTimer=T60S_1;
		CAN1_ClearErrorTimer();
	}
}

void Peugeot207_Tx_Message(void)
{
	MESSAGE*nEvt;		
	
	nEvt=GetMessage(SUB_CAN_MODULE);
	if(nEvt->ID==NO_EVT)
	{
		return;
	}

	switch(nEvt->ID)
	{
		case PEUGEOT_207_RX_APP_DATA:
			switch(LSB(nEvt->prm))
			{
				case PEUGEOT_207_TX_SOURCE_INFO:
					if(!strcmp_equal(&DialogInfo.source_info.data[0],&DialogInfoBak.source_info.data[0],2))
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.source_info=DialogInfo.source_info;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=2;
						message.data_id=DIALOG_ID_SOURCE;
						message.data[0]=DialogInfo.source_info.data[0];
						message.data[1]=DialogInfo.source_info.data[1];
						PostDialogMessage(&message,1);
					}
					break;
				case PEUGEOT_207_TX_PLAY_INFO:
					if(DialogInfo.play_info.field.mode!=DialogInfoBak.play_info.field.mode)
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.play_info.field.mode=DialogInfo.play_info.field.mode;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=1;
						message.data_id=DIALOG_ID_PLAY_MODE;
						message.data[0]=DialogInfo.play_info.field.mode;
						PostDialogMessage(&message,1);
					}
					if(DialogInfo.play_info.field.status!=DialogInfoBak.play_info.field.status)
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.play_info.field.status=DialogInfo.play_info.field.status;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=1;
						message.data_id=DIALOG_ID_STATUS;
						message.data[0]=DialogInfo.play_info.field.status;
						PostDialogMessage(&message,1);
					}
					if(DialogInfoBak.play_info.field.media_type!=DialogInfo.play_info.field.media_type
						||DialogInfoBak.play_info.field.folder_number!=DialogInfo.play_info.field.folder_number
						||DialogInfoBak.play_info.field.track_number_H!=DialogInfo.play_info.field.track_number_H
						||DialogInfoBak.play_info.field.track_number_L!=DialogInfo.play_info.field.track_number_L
						||DialogInfoBak.play_info.field.min!=DialogInfo.play_info.field.min
						||DialogInfoBak.play_info.field.sec!=DialogInfo.play_info.field.sec)
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.play_info.field.media_type=DialogInfo.play_info.field.media_type;
						DialogInfoBak.play_info.field.folder_number=DialogInfo.play_info.field.folder_number;
						DialogInfoBak.play_info.field.track_number_H=DialogInfo.play_info.field.track_number_H;
						DialogInfoBak.play_info.field.track_number_L=DialogInfo.play_info.field.track_number_L;
						DialogInfoBak.play_info.field.min=DialogInfo.play_info.field.min;
						DialogInfoBak.play_info.field.sec=DialogInfo.play_info.field.sec;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=6;
						message.data_id=DIALOG_ID_MEDIA_INFO;
						message.data[0]=DialogInfo.play_info.field.media_type;
						message.data[1]=DialogInfo.play_info.field.folder_number;
						message.data[2]=DialogInfo.play_info.field.track_number_H;
						message.data[3]=DialogInfo.play_info.field.track_number_L;
						message.data[4]=DialogInfo.play_info.field.min;
						message.data[5]=DialogInfo.play_info.field.sec;
						PostDialogMessage(&message,1);
					}
					break;
				case PEUGEOT_207_TX_RADIO_INFO:
					if(DialogInfoBak.radio_info.field.pty!=DialogInfo.radio_info.field.pty)
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.radio_info.field.pty=DialogInfo.radio_info.field.pty;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=1;
						message.data_id=DIALOG_ID_RDS_TYPE;
						message.data[0]=DialogInfo.radio_info.field.pty;
						PostDialogMessage(&message,1);
					}
					if(DialogInfoBak.radio_info.field.preset_save!=DialogInfo.radio_info.field.preset_save)
					{
						DIALOG_DATA_FRAME message;
						
						DialogInfoBak.radio_info.field.preset_save=DialogInfo.radio_info.field.preset_save;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=1;
						message.data_id=DIALOG_ID_MEMORY_PRESET;
						message.data[0]=DialogInfo.radio_info.field.preset_save;
						PostDialogMessage(&message,1);
					}
					if(DialogInfoBak.radio_info.field.search_state!=DialogInfo.radio_info.field.search_state
						||DialogInfoBak.radio_info.field.search_type!=DialogInfo.radio_info.field.search_type)
					{
						DIALOG_DATA_FRAME message;
						
						DialogInfoBak.radio_info.field.search_state=DialogInfo.radio_info.field.search_state;
						DialogInfoBak.radio_info.field.search_type=DialogInfo.radio_info.field.search_type;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=2;
						message.data_id=DIALOG_ID_SEARCH_STATION;
						message.data[0]=DialogInfoBak.radio_info.field.search_type;
						message.data[1]=DialogInfoBak.radio_info.field.search_state;
						PostDialogMessage(&message,1);
					}
					if(DialogInfoBak.radio_info.field.band!=DialogInfo.radio_info.field.band
						||DialogInfoBak.radio_info.field.freq_H!=DialogInfo.radio_info.field.freq_H
						||DialogInfoBak.radio_info.field.freq_L!=DialogInfo.radio_info.field.freq_L
						||DialogInfoBak.radio_info.field.unit!=DialogInfo.radio_info.field.unit
						||DialogInfoBak.radio_info.field.preset!=DialogInfo.radio_info.field.preset)
					{
						DIALOG_DATA_FRAME message;
						
						DialogInfoBak.radio_info.field.band=DialogInfo.radio_info.field.band;
						DialogInfoBak.radio_info.field.freq_H=DialogInfo.radio_info.field.freq_H;
						DialogInfoBak.radio_info.field.freq_L=DialogInfo.radio_info.field.freq_L;
						DialogInfoBak.radio_info.field.unit=DialogInfo.radio_info.field.unit;
						DialogInfoBak.radio_info.field.preset=DialogInfo.radio_info.field.preset;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=5;
						message.data_id=DIALOG_ID_RADIO_INFO;
						message.data[0]=DialogInfoBak.radio_info.field.band;
						message.data[1]=DialogInfoBak.radio_info.field.freq_H;
						message.data[2]=DialogInfoBak.radio_info.field.freq_L;
						message.data[3]=DialogInfoBak.radio_info.field.unit;
						message.data[4]=DialogInfoBak.radio_info.field.preset;
						PostDialogMessage(&message,1);
					}
					break;
				case PEUGEOT_207_TX_TEXT_INFO:
					if(MSB(nEvt->prm)<TEXT_TYPE_NUM)
					{
						DIALOG_DATA_FRAME message;
						u32 length=0;
						u32 i;
						u8 index;

						index=MSB(nEvt->prm);
						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=1;
						message.data_id=DIALOG_ID_TEXT_TYPE;
						message.data[0]=index;
						PostDialogMessage(&message,1);

						for(i=0;i<MAX_DIALOG_TEXT_LENGTH;i++)
						{
							if(DialogInfo.text_info[index][i])
							{
								length=i+1;
							}
						}
						if(length)
						{
							u32 frame_index;
							u32 frame_num;
							u32 byte_num;
							u32 data_length;
							u32 counter;
							DIALOG_DATA_FRAME text_message[MAX_DIALOG_FRAME_NUM];
							
							FormatMemery((u8*)&text_message[0].frame_id,sizeof(text_message));
							counter=length;
							frame_index=0;
							for(;counter;)
							{
								frame_num=(counter/MAX_DIALOG_FRAME_DATA_LENGTH)+((counter%6==0)?0:1);
								byte_num=counter;
								data_length=((counter<MAX_DIALOG_FRAME_DATA_LENGTH)?counter:MAX_DIALOG_FRAME_DATA_LENGTH);

								text_message[frame_index].byte1.field.frame_num=frame_num;
								text_message[frame_index].byte1.field.byte_num=byte_num;
								text_message[frame_index].data_id=DIALOG_ID_TEXT_TYPE;
								for(i=0;i<data_length;i++)
								{
									text_message[frame_index].data[i]=DialogInfo.text_info[index][i+(frame_index*6)];
								}
								counter-=data_length;
								frame_index++;
							}
							PostDialogMessage(text_message,frame_index);
						}
					}
					break;
				case PEUGEOT_207_TX_EQ_INFO:
					if(DialogInfo.eq_info!=DialogInfoBak.eq_info)
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.eq_info=DialogInfo.eq_info;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=1;
						message.data_id=DIALOG_ID_EQUALIZER;
						message.data[0]=DialogInfo.eq_info;
						PostDialogMessage(&message,1);
					}
					break;
				case PEUGEOT_207_TX_SETUP_INFO:
					if(!strcmp_equal(&DialogInfo.setup_mode[0],&DialogInfoBak.setup_mode[0],2))
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.setup_mode[0]=DialogInfo.setup_mode[0];
						DialogInfoBak.setup_mode[1]=DialogInfo.setup_mode[1];

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=2;
						message.data_id=DIALOG_ID_SETUP_MODE;
						message.data[0]=DialogInfoBak.setup_mode[0];
						message.data[1]=DialogInfoBak.setup_mode[1];
						PostDialogMessage(&message,1);
					}
					break;
				case PEUGEOT_207_TX_VOLUME_INFO:
					if(!strcmp_equal(&DialogInfo.volume_info[0],&DialogInfoBak.volume_info[0],2))
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.volume_info[0]=DialogInfo.volume_info[0];
						DialogInfoBak.volume_info[1]=DialogInfo.volume_info[1];

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=2;
						message.data_id=DIALOG_ID_VOLUME_LEVEL;
						message.data[0]=DialogInfoBak.volume_info[0];
						message.data[1]=DialogInfoBak.volume_info[1];
						PostDialogMessage(&message,1);
					}
					break;
				case PEUGEOT_207_TX_BT_INFO:
					if(DialogInfo.bt_status!=DialogInfoBak.bt_status)
					{
						DIALOG_DATA_FRAME message;

						DialogInfoBak.bt_status=DialogInfo.bt_status;

						FormatMemery((u8*)&message.frame_id,sizeof(DIALOG_DATA_FRAME));
						message.byte1.field.frame_num=1;
						message.byte1.field.byte_num=1;
						message.data_id=DIALOG_ID_BLUETOOTH;
						message.data[0]=DialogInfo.bt_status;
						PostDialogMessage(&message,1);
					}
					break;
				case PEUGEOT_207_TX_REQ_CMD:
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_BASE_INFO);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_CLUSTER_INFO);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_VIN_INFO);
					break;
				default:
					break;
			}
			break;
		case PEUGEOT_207_DATE_DATA:
			{
				u8 data[8];

				u16 Time_Year;

				data[0] = RTC_TimeInfo.seconds;
				data[1] = RTC_TimeInfo.minutes;
				data[2] = RTC_TimeInfo.hours;
				data[3] = RTC_TimeInfo.day;
				data[4] = RTC_TimeInfo.month;
				Time_Year = RTC_TimeInfo.year + 2000;

				if(DialogInfo.date_status.field.Date_region==0)
				{
					int per_year,per_day,per_month,gre_year,gre_month,gre_day;
					gre_year = Time_Year;
					gre_month = RTC_TimeInfo.month;
					gre_day = RTC_TimeInfo.day;
					GregorianToPersian(&per_year,&per_month,&per_day,gre_year,gre_month,gre_day);
					data[3] = per_day;
					data[4] = per_month;
					Time_Year = per_year;
				}
				
				if(DialogInfo.date_status.field.Time_meridiem)
				{
					Time_Year = (0x60<<8) + Time_Year;
				}
				else
				{
					
					if(RTC_TimeInfo.hours>12)
					{
						data[2] = RTC_TimeInfo.hours - 12;
					}
					Time_Year = (0x40<<8) + Time_Year;
				}
				
				data[5] = LSB(Time_Year);
				data[6] = MSB(Time_Year);
				//CAN1_TxFrame(CAN_ID_MMS_TIME_DATE,data,8);
				CAN1_TransBytefraem(CAN_ID_MMS_TIME_DATE,data,8);
			}
			break;
		case PEUGEOT_207_TRIPS_WITCH_INFO:
			Trip_Switch_status = nEvt->prm;
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_SWITCH_INFO);
			break;
		default:
			break;
	}
}

void Peugeot207_MainEvtPro(void)
{
       MESSAGE*nEvt;	
	
	nEvt=GetMessage(MAIN_CAN_MODULE);
	if(nEvt->ID==CAN_EVENT_NONE)
	{
		return;
	}
	switch(nEvt->ID)
	{
		case CAN_POWER_ON:
			break;
		case CAN_RX_APP_DATA:
			PostMessage(SUB_CAN_MODULE,PEUGEOT_207_RX_APP_DATA,nEvt->prm);
			break;
		default:
			break;
	}
}

void Peugeot207_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	u8 i;
	u8 length=0;
	u8 *ptr;
	cmd_id=buffer[1];

	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	
	switch(cmd_id)
	{
		case PEUGEOT_207_TX_SOURCE_INFO:
			ptr=&DialogInfo.source_info.data[0];
			length=2;
			break;
		case PEUGEOT_207_TX_PLAY_INFO:
			ptr=&DialogInfo.play_info.data[0];
			length=8;
			break;
		case PEUGEOT_207_TX_RADIO_INFO:
			ptr=&DialogInfo.radio_info.data[0];
			length=9;
			break;
		case PEUGEOT_207_TX_TEXT_INFO:
			if(buffer[3]<TEXT_TYPE_NUM)
			{
				for(i=0;i<MAX_DIALOG_TEXT_LENGTH;i++)
				{
					DialogInfo.text_info[buffer[3]][i]=0;
				}
				
				for(i=0;i<(buffer[2]-1)&&i<MAX_DIALOG_TEXT_LENGTH;i++)
				{
					DialogInfo.text_info[buffer[3]][i]=buffer[i+4];
				}
				PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,WORD(buffer[3],cmd_id));
			}
			break;
		case PEUGEOT_207_TX_EQ_INFO:
			ptr=&DialogInfo.eq_info;
			length=1;
			break;
		case PEUGEOT_207_TX_SETUP_INFO:
			ptr=&DialogInfo.setup_mode[0];
			length=2;
			break;
		case PEUGEOT_207_TX_VOLUME_INFO:
			ptr=&DialogInfo.volume_info[0];
			length=2;
			break;
		case PEUGEOT_207_TX_BT_INFO:
			ptr=&DialogInfo.bt_status;
			length=1;
			break;
		case PEUGEOT_207_TX_REQ_CMD:
			PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,PEUGEOT_207_TX_REQ_CMD);
			break;
		case PEUGEOT_207_TX_TIME_INFO:
#if MODEL==LINUX_P058_55
			Peugeot207_Date = buffer[3];
			EEPROM_Save_DateInfo();
			DialogInfo.date_status.field.Date_region = GetBit(Peugeot207_Date,0);
			DialogInfo.date_status.field.Time_meridiem = GetBit(Peugeot207_Date,4);
#endif
		case PEUGEOT_207_TX_INFO_RESET:
			if(buffer[3]==0x01)
			{
				DialogInfo.Trip_status.Trip_info1_flag = 1;
				FormatMemery((u8*)&DialogInfo.Trip_status.Trip_info1.Trip_Distance, sizeof(DialogInfo.Trip_status.Trip_info1));
				CanRxInfo.trip_info.Total_info1.Total_distance = Trip_Mileage_Current;
				CanRxInfo.trip_info.Total_info1.Total_duration = 0;
				
			}
			else if(buffer[3]==0x02)
			{
				DialogInfo.Trip_status.Trip_info2_flag = 1;
				FormatMemery((u8*)&DialogInfo.Trip_status.Trip_info2.Trip_Distance, sizeof(DialogInfo.Trip_status.Trip_info2));
				CanRxInfo.trip_info.Total_info2.Total_distance = Trip_Mileage_Current;
				CanRxInfo.trip_info.Total_info2.Total_duration = 0;
			}
			
			break;
		default:
			break;
	}
	if(length)
	{
		for(i=0;i<length;i++)
		{
			*ptr=buffer[i+3];
		}
		PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,cmd_id);
	}
}

void Peugeot207_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case PEUGEOT_207_RX_BASE_INFO:
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.base_info.byte_1.byte;
			buffer[4]=CanRxInfo.base_info.byte_2.byte;
			buffer[5]=CanRxInfo.base_info.Ambient_Temperature;
			break;		   
		case PEUGEOT_207_RX_RADAR_INFO:
			buffer[2]=0x08;
			buffer[3]=CanRxInfo.radar_info.byte_1.byte;
			buffer[4]=CanRxInfo.radar_info.byte_2.byte;
			buffer[5]=CanRxInfo.radar_info.byte_3.byte;
			buffer[6]=CanRxInfo.radar_info.distance;
			buffer[7]=CanRxInfo.radar_info.distance_1;
			buffer[8]=CanRxInfo.radar_info.distance_2;
			buffer[9]=CanRxInfo.radar_info.distance_3;
			buffer[10]=CanRxInfo.radar_info.distance_4;
			break;
		case PEUGEOT_207_RX_CLUSTER_INFO:
			buffer[2]=0x0A;
			buffer[3]=CanRxInfo.cluster_info.speed_info.byte[0];
			buffer[4]=CanRxInfo.cluster_info.speed_info.byte[1];
			buffer[5]=CanRxInfo.cluster_info.engine_rpm_info.byte[0];
			buffer[6]=CanRxInfo.cluster_info.engine_rpm_info.byte[1];
			buffer[7]=CanRxInfo.cluster_info.average_speed;
			buffer[8]=CanRxInfo.cluster_info.remaining_distance_info.byte[0];
			buffer[9]=CanRxInfo.cluster_info.remaining_distance_info.byte[1];
			buffer[10]=CanRxInfo.cluster_info.warning_info1.byte;
			buffer[11]=CanRxInfo.cluster_info.warning_info2.byte;
			buffer[12]=CanRxInfo.cluster_info.warning_info3.byte;
			break;
		case PEUGEOT_207_RX_VIN_INFO:
			buffer[2]=0x18;
			for(i=0;i<buffer[2];i++)
			{
				buffer[i+3]=CanRxInfo.vin_info[i];
			}
			break;
		case PEUGEOT_207_RX_SWITCH_INFO:
			buffer[2]=0x01;
			buffer[3]=Trip_Switch_status;
			break;
		case PEUGEOT_207_RX_TRIP_INFO1:
			buffer[2]=0x06;
			buffer[3]=MSB(DialogInfo.Trip_status.Trip_info1.Trip_Speed);
			buffer[4]=LSB(DialogInfo.Trip_status.Trip_info1.Trip_Speed);
			buffer[5]=MSB(DialogInfo.Trip_status.Trip_info1.Trip_Duration);
			buffer[6]=LSB(DialogInfo.Trip_status.Trip_info1.Trip_Duration);
			buffer[7]=MSB(DialogInfo.Trip_status.Trip_info1.Trip_Distance);
			buffer[8]=LSB(DialogInfo.Trip_status.Trip_info1.Trip_Distance);
			break;
		case PEUGEOT_207_RX_TRIP_INFO2:
			buffer[2]=0x06;
			buffer[3]=MSB(DialogInfo.Trip_status.Trip_info2.Trip_Speed);
			buffer[4]=LSB(DialogInfo.Trip_status.Trip_info2.Trip_Speed);
			buffer[5]=MSB(DialogInfo.Trip_status.Trip_info2.Trip_Duration);
			buffer[6]=LSB(DialogInfo.Trip_status.Trip_info2.Trip_Duration);
			buffer[7]=MSB(DialogInfo.Trip_status.Trip_info2.Trip_Distance);
			buffer[8]=LSB(DialogInfo.Trip_status.Trip_info2.Trip_Distance);
			break;
		case PEUGEOT_207_RX_TPMS_INFO:
			buffer[2]=0x05;
			buffer[3]=CanRxInfo.tpms_info.Tpms_ID;
			buffer[4]=CanRxInfo.tpms_info.Tpms_TirePressure;
			buffer[5]=CanRxInfo.tpms_info.Tpms_Temperature;
			buffer[6]=LSB(CanRxInfo.tpms_info.Tpms_Warning.byte);
			buffer[7]=MSB(CanRxInfo.tpms_info.Tpms_Warning.byte);
			break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=PEUGEOT_207_HEAD_CODE;
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

void Peugeot207_MainPro(void)
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
	if(CanNormalTimer)
	{
		CanNormalTimer--;
	}
	if(CanNoDataTimer)
	{
		CanNoDataTimer--;
		if(CanNoDataTimer==0)
		{
			F_CAN_RX_DATA=0;
		}
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
	Peugeot207_MainEvtPro();
	Peugeot207_Rx_Message();
	CAN1_Transmit();

	switch(CanMainState)
	{
		case CAN_MAIN_IDLE:
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;
			F_CAN_SLEEP=0;
			CanGeneralCtrlFlag.field.illumi_level=KEY_LED_PERCENT_MAX;
			break;
		case CAN_MAIN_CFG:
			CAN1_Init();
			if(Get_ACC_Det_Flag)
			{
			CanMainState=CAN_MAIN_INIT;
			}
			else
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}
			break;
		case CAN_MAIN_INIT:
			ClearDialogMessage();
			CAN1_ClearTxMessage();
			FormatMemery(&CanRxInfoBak.base_info.byte_1.byte,sizeof(CanRxInfoBak));
			DialogInfo.date_status.field.Date_region = GetBit(Peugeot207_Date,0);
			DialogInfo.date_status.field.Time_meridiem = GetBit(Peugeot207_Date,4);
			ReverseFlag_SMS=0;
			ReverseFlag_EcoMux=0;
			F_CAN_RX_DATA=0;
			CanMainState=CAN_MAIN_NORMAL;
			break;
		case CAN_MAIN_NORMAL:
			if(ReverseFlag_SMS||ReverseFlag_EcoMux)
			{
				CanRxInfo.base_info.byte_1.field.f_reverse=1;
			}
			else
			{
				CanRxInfo.base_info.byte_1.field.f_reverse=0;
			}
			CanGeneralCtrlFlag.field.reverse_on_off=CanRxInfo.base_info.byte_1.field.f_reverse;
			if(CanGeneralCtrlFlag.field.reverse_on_off==0
				&&Get_Lin_Reverse==0
				&&Get_Reverse_Det_Flag)
			{
				REVERSE_SIGNAL_OFF;
			}
			if(APP_READY==APP_Status)
			{
				if(!strcmp_equal(&CanRxInfo.base_info.byte_1.byte,&CanRxInfoBak.base_info.byte_1.byte,sizeof(CAN_BASE_INFO)))
				{
					Mem_strcpy(&CanRxInfoBak.base_info.byte_1.byte,&CanRxInfo.base_info.byte_1.byte,sizeof(CAN_BASE_INFO));
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_BASE_INFO);
				}

				if(Get_Reverse_Det_Flag)
				{
#if MODEL==LINUX_D068_55||MODEL==LINUX_D065_55
					if(RadarLevel[0]!=RadarLevelBak[0]
						||RadarLevel[1]!=RadarLevelBak[1]
						||RadarLevel[2]!=RadarLevelBak[2])
					{
						RadarLevelBak[0]=RadarLevel[0];
						RadarLevelBak[1]=RadarLevel[1];
						RadarLevelBak[2]=RadarLevel[2];
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_RADAR_INFO);
					}
#else
					if(CanTxTimer1%25==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_RADAR_INFO);
					}
#endif
				}
				else
				{
					RadarLevelBak[0]=0xFF;
					RadarLevelBak[1]=0xFF;
					RadarLevelBak[2]=0xFF;

				}


				CanTxTimer1++;
				if(CanTxTimer1>T1S_1)
				{
					CanTxTimer1=0;
					Peugeot207_TripCompare();
					if(CanRxInfo.trip_info.Rpm_engine_flag&&Get_F_Stop_Car==0)
					{
						CanRxInfo.trip_info.Total_info1.Total_duration++;
						CanRxInfo.trip_info.Total_info2.Total_duration++;
					}

					if(!strcmp_equal(&CanRxInfo.cluster_info.speed_info.byte[0],&CanRxInfoBak.cluster_info.speed_info.byte[0],sizeof(CAN_CLUSTER_INFO)))
					{
						Mem_strcpy(&CanRxInfoBak.cluster_info.speed_info.byte[0],&CanRxInfo.cluster_info.speed_info.byte[0],sizeof(CAN_CLUSTER_INFO));
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_CLUSTER_INFO);
					}

					if(!strcmp_equal(&CanRxInfo.vin_info[0],&CanRxInfoBak.vin_info[0],24))
					{
						Mem_strcpy(&CanRxInfoBak.vin_info[0],&CanRxInfo.vin_info[0],24);
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_VIN_INFO);
					}
					///
					if(CanRxInfo.cluster_info.battery_voltage 
						&& (CanRxInfo.cluster_info.engine_rpm_info.engine_rpm >=500)
						&& CanRxInfo.base_info.byte_1.field.f_start_status==2)
					{
						CanRxInfo.cluster_info.warning_info5.field.f_low_batterVoltage_warning = 1;
					}
					else
					{
						CanRxInfo.cluster_info.warning_info5.field.f_low_batterVoltage_warning = 0;
					}
				}
				
				CanTxTimer2++;
				if(CanTxTimer2>T5S_1)
				{
					CanTxTimer2=0;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_VIN_INFO);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_BASE_INFO);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,PEUGEOT_207_RX_CLUSTER_INFO);
				}
			}
			DialogMessageTxPro();
			Peugeot207_Tx_Message();
			if(Get_ACC_Det_Flag==0)
			{
				CanMainState=CAN_MAIN_GO_TO_SLEEP;
				CanMainTimer=T2S_1;
			}
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
#if CAN_IC_NCV7342==1
				CAN_IC_POWER_OFF;
#endif
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
			CAN1_ClearRxMessage();
			CanMainState=CAN_MAIN_SLEEP;
			break;
		case CAN_MAIN_SLEEP:
			if(Get_ACC_Det_Flag)
			{
#if CAN_IC_NCV7342==1
				CAN_IC_POWER_ON;
#endif
				CAN_IC_ENABLE;
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

