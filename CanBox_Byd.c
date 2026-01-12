#include "public.h"

#if CAN_ADAPTER==1
#if CANBOX_BYD==1
BYD_CAN_RX_INFO BYDCanAdapterRxInfo;
BYD_CAN_TX_INFO BYDCanAdapterTxInfo;
BYD_TIME BydTime;
BYD_TIME BydTimeBak;
u8 BydTimeInitFlag;

const u8 BYD_SteerKeyTab[BYD_WHEEL_KEY_NUM][4]=
{
/*
0:只有短按功能
1:有长按功能，但长按按键没有连续功能
2:有长按功能，并且长按按键有连续功能
3:短按按键，但长按有连续功能
*/
	{CANKEY_OFF,	NO_KEY,					NO_KEY,						0},
	{CANKEY_1,		UICC_VOLUME_UP,			NO_KEY,						0},
	{CANKEY_2,		NO_KEY,		NO_KEY,						0},
	{CANKEY_3,		NO_KEY,				NO_KEY,			    			0},	
	{CANKEY_4,		UICC_VOLUME_DOWN,				NO_KEY,			    			0},	
	{CANKEY_5,	    NO_KEY,					NO_KEY,						0},
	{CANKEY_6,	   	NO_KEY,					NO_KEY,						0},
	{CANKEY_7,		UICC_UP,			NO_KEY,						0},
	{CANKEY_8,	    UICC_SKIPB,		NO_KEY,						5},
	{CANKEY_9,		NO_KEY,	       				NO_KEY,						0},
	{CANKEY_10,		UICC_DOWN,					NO_KEY,						0},
	{CANKEY_11,		UICC_SKIPF,					NO_KEY,			        		0},
	{CANKEY_12,		UICC_BT_ACPTCALL,	       				NO_KEY,						0},
	{CANKEY_13,		UICC_BT_ACPTCALL,/*电话长按*/					NO_KEY,		                		0},
	{CANKEY_14,		NO_KEY,/*音响短按*/	       				NO_KEY,						0},
	{CANKEY_15,		NO_KEY,	/*音响长按*/				NO_KEY,		                		0},
	{CANKEY_16,		UICC_SOURCE,	/*模式键短按*/				NO_KEY,			        		5},
	{CANKEY_17,		UICC_SOURCE,	/*模式键长按*/       	NO_KEY,						0},
	{CANKEY_18,		NO_KEY,		NO_KEY,		                		0},
	{CANKEY_19,		UICC_OPEN_SOUND,	/*语音输入键短按*/				NO_KEY,			    			0},	
	{CANKEY_20,		UICC_OPEN_SOUND_LONG,	/*语音输入键长按*/				NO_KEY,			    			0},	
	{CANKEY_21,		UICC_HOME,	/*HOME短按*/			NO_KEY,		                		0},
	{CANKEY_22,		UICC_MENU,	/*HOME长按*/				NO_KEY,		                		0},
	{CANKEY_23,		UICC_BACK,	/*BACK短按*/				NO_KEY,		       				0},
	{CANKEY_24,		UICC_BACK,	/*BACK长按*/				NO_KEY,		       				0},
	{CANKEY_25,		UICC_MUTE,	/*POWER短按（静音）*/				NO_KEY,		       				0},
	{CANKEY_26,		NO_KEY,/*POWER长按（关机）*/						SYSTEM_POWER_OFF_KEY,			        		1},
	{CANKEY_27,		UICC_TFT_STANDBY,/*关屏 短按*/		       	NO_KEY,						0},
	{CANKEY_28,		NO_KEY,			NO_KEY,		                		0},
	{CANKEY_29,		UICC_BT_HUNGUPCALL,		/*挂电话短按*/				NO_KEY,			    			0},
	{CANKEY_30,		UICC_BT_HUNGUPCALL,	/*挂电话长按*/					NO_KEY,			    			0},	
	{CANKEY_31,		NO_KEY,	/*弹出空调设置界面*/				NO_KEY,		                		0},
	{CANKEY_32,		NO_KEY,	/*进入/退出360*/				NO_KEY,		                		0},
	{CANKEY_33,		NO_KEY,	/*前视*/				NO_KEY,		       				0},
	{CANKEY_34,		NO_KEY,	/*后视*/				NO_KEY,		       				0},
	{CANKEY_35,		NO_KEY,	/*左视*/					NO_KEY,		       				0},
	
	
};



void BYD_TxStartEndCmd(u8 start_end)
{
	CanFunTxBuffer[0]=BYD_CAN_HEAD_CODE;
	CanFunTxBuffer[1]=BYD_TX_START_END_CMD;
	CanFunTxBuffer[2]=0x01;
	if(0x01==start_end)
		{
			CanFunTxBuffer[3]=0x01; 				//Start
		}
		else
		{
			CanFunTxBuffer[3]=0x00; 				//End
		}											//Checksum
		CanFunTxBuffer[4]=(CanFunTxBuffer[1]+CanFunTxBuffer[2]+CanFunTxBuffer[3])^0xFF;
		CanBoxUartTxFarmat(CanFunTxBuffer,5);
	}
void BYD_TxAck(u8 ack)
{	
	CanBoxUartTxFarmat(&ack,1);
}
void BYD_TimerPro(void)
{
	u32 time_sec;
	u32 time_min;
	u32 time_hour;
	BYD_TIME temp;

	if(BydTime.counter!=RTC_TimerData)
	{
		time_sec=RTC_TimerData-BydTime.counter;
		BydTime.counter=RTC_TimerData;
		time_hour=((time_sec%(3600*24))/3600);
		time_min=((time_sec%3600)/60);
		time_sec=(time_sec%60);
		temp=BydTime;
		if(temp.mode_12_24)
		{
			if(temp.time_am_pm==0)
			{
				if(temp.time_hour==12)
				{
					temp.time_hour=0;
				}
			}
			else
			{
				if(temp.time_hour!=12)
				{
					temp.time_hour+=12;
				}
			}
		}
		temp.time_hour+=time_hour;
		temp.time_min+=time_min;
		temp.time_sec+=time_sec;
		if(temp.time_sec>=60)
		{
			temp.time_sec-=60;
			temp.time_min++;
		}
		if(temp.time_min>=60)
		{
			temp.time_min-=60;
			temp.time_hour++;
		}
		if(temp.time_hour>=24)
		{
			temp.time_hour-=24;
		}
		
		if(temp.mode_12_24)
		{
			if(temp.time_hour==0)
			{
				temp.time_hour=12;
				temp.time_am_pm=0;
			}
			else if(temp.time_hour<12)
			{
				temp.time_am_pm=0;
			}
			else if(temp.time_hour==12)
			{
				temp.time_am_pm=1;
			}
			else
			{
				temp.time_hour-=12;
				temp.time_am_pm=1;
			}
		}
		if(temp.time_am_pm!=BydTime.time_am_pm
			||temp.time_hour!=BydTime.time_hour
			||temp.time_min!=BydTime.time_min)
		{
			if(nPowerState!=POWER_NORMAL_RUN
				||Get_ACC_Det_Flag==0)
			{
				PostMessage(SUB_CAN_MODULE,BYD_CMD_PWR_OFF_TIME,0);
			}
		}
		BydTime=temp;
	}
}


void CanBox_MainEvtPro_BYD(void)
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
			if(nEvt->prm==0)
			{
				CanBoxWorkTimer=T300MS_10;
				CanBoxWorkState=BYD_TX_START_COMMAND;
			}
			else if(nEvt->prm==0xFF)
			{

				PostMessage(SUB_CAN_MODULE,BYD_CMD_PWR_ON_SOURCE,0);
			}
			break;
		case CAN_POWER_OFF:
			PostMessage(SUB_CAN_MODULE,BYD_CMD_SOURCE_OFF,OFF);	
			break;
		case CAN_ACC_OFF:
			CanBoxWorkState=BYD_TX_SOURCE_OFF;
			break;
		case CAN_EMERGENCY_OFF:
			CanBoxWorkState=BYD_POWER_OFF;
			break;
		case CAN_RX_APP_DATA:
			if(nPowerState==POWER_NORMAL_RUN)
			{
				PostMessage(SUB_CAN_MODULE,BYD_CMD_APP_DATA,nEvt->prm);
			}
			break;
		default:
			break;
	}
}

void CanBox_RxAck_BYD(u8 rx_ack)
{
	switch(rx_ack)
	{
		case BYD_RX_ACK:
			F_EXIST_CANBOX=1;
			F_CAN_TX_BUFFER_FULL=0;
			F_CAN_TX_ACK_CHECK=0;
			if(BYD_WAIT_START_ACK==CanBoxWorkState)
			{
				CanBoxWorkState=BYD_WORK_NORMAL;
			}
			else if(BYD_WAIT_END_ACK==CanBoxWorkState)
			{
				CanBoxWorkState=BYD_POWER_OFF;
			}
			break;
		case BYD_RX_NACK_NO_SUPPORT:
			F_CAN_TX_BUFFER_FULL=0;
			F_CAN_TX_ACK_CHECK=0;
			break;
		case BYD_RX_NACK_ERR_CHECKSUM:
		case BYD_RX_NACK_BUSY:
			F_CAN_TX_ACK_CHECK=1;
			break;
		default:
			break;
	}
}

void CanBox_RxService_BYD(u8 *data)
{
	u8 tx_ack;
	u8 data_type;
	u32 i;
	
	data_type=data[1];
	tx_ack=BYD_RX_ACK;
	switch(data_type)
	{
		case BYD_RX_VOICE_BROAD_INFO:
			for(i=0;i<9;i++)
			{
				BYDCanAdapterRxInfo.voice_info=data[i+3];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_VOICE_BROAD_INFO);
			break;
			
		case BYD_RX_WINDOW_INFO:
			 BYDCanAdapterRxInfo.window_info[0] = data[3];
			 BYDCanAdapterRxInfo.window_info[1]= data[4];
			 if(data[4]&0x80)
			{
				CanGeneralCtrlFlag.field.camera_on_off=1;
			}
			else
			{
				CanGeneralCtrlFlag.field.camera_on_off=0;
			}
			break;
			
		case BYD_RX_PM25_INFO:
			for(i=0;i<2;i++)
			{
				BYDCanAdapterRxInfo.pm25_info[i]=data[i+3];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_PM25_INFO);
			break;
			
		case BYD_RX_PANORAMA_INFO:
			for(i=0;i<2;i++)
			{
				BYDCanAdapterRxInfo.panorama_info=data[i+3];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_PANORAMA_INFO);
			break;
			
		case BYD_RX_CAMERA_CONTROL:			
			BYDCanAdapterRxInfo.camera_control_info =data[3];
			 if(data[3]&0x40)
			{
				CanGeneralCtrlFlag.field.reverse_on_off=1;
			}
			else
			{
				CanGeneralCtrlFlag.field.reverse_on_off=0;
			}
			break;
			
		case BYD_RX_DRIVING_INFO:
			for(i=0;i<6;i++)
			{
				BYDCanAdapterRxInfo.driving_info[i]=data[i+3];
			}
			
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_DRIVING_INFO);
			break;
			
		case BYD_RX_FRONT_RADAR_INFO:
			for(i=0;i<6;i++)
			{
				BYDCanAdapterRxInfo.front_radar_info[i]=data[i+3];
			}
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_FRONT_RADAR_INFO);
			
			break;
		case BYD_RX_REAR_RADAR_INFO:
			for(i=0;i<6;i++)
			{
				BYDCanAdapterRxInfo.rear_radar_info[i]=data[i+3];
			}
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_REAR_RADAR_INFO);
			
			break;
		
		
		case BYD_RX_STEER_KEY:
			if(data[3]<BYD_WHEEL_KEY_NUM) 
			{
				CanKeyInfo.CanKeyCode=data[3];
				CanKeyInfo.KeyStatus=data[4];	
				CanKeyInfo.KeyCode=BYD_SteerKeyTab[CanKeyInfo.CanKeyCode][1];
				CanKeyInfo.LongKeyCode=BYD_SteerKeyTab[CanKeyInfo.CanKeyCode][2];	
				CanKeyInfo.KeyProperty=BYD_SteerKeyTab[CanKeyInfo.CanKeyCode][3]; 
				CanKeyInfo.key_source=STEER;
				CanKeyScan();  
			}
			break;

		case BYD_RX_BASIC_INFO:
			BYDCanAdapterRxInfo.baseinfo[0] = data[3];
			 BYDCanAdapterRxInfo.baseinfo[1]= data[4];
			 if(data[3]&0x01)
			{
				CanGeneralCtrlFlag.field.reverse_on_off=1;
			}
			else
			{
				CanGeneralCtrlFlag.field.reverse_on_off=0;
			}
			 if(data[4]&0x02)
			{
				CanGeneralCtrlFlag.field.parking_on_off=0;
			}
			else
			{
				CanGeneralCtrlFlag.field.parking_on_off=1;
			}
			break;

		case BYD_RX_SPEED:
			for(i=0;i<6;i++)
			{
				BYDCanAdapterRxInfo.speed_info[i]=data[i+3];
			}
			
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_SPEED);
			break;

		case BYD_RX_CAR_INFO:
			for(i=0;i<5;i++)
			{
				BYDCanAdapterRxInfo.car_info[i]=data[i+3];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_CAR_INFO);
			break;
		
		case BYD_RX_AIR_INFO:
			for(i=0;i<9;i++)
			{
				BYDCanAdapterRxInfo.air_info[i]=data[i+3];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_AIR_INFO);
			break;
		
		case BYD_RX_EPS_INFO:
			for(i=0;i<2;i++)
			{
				BYDCanAdapterRxInfo.eps_info[i]=data[i+3];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,BYD_RX_EPS_INFO);
			break;

		default:
			tx_ack=BYD_RX_NACK_NO_SUPPORT;
			break;
	}
	BYD_TxAck(tx_ack);
}

void CanBox_RxAnalyse_BYD(void)
{
	u16 start=CanFunRxBuffer.head;
	u16 end=CanFunRxBuffer.tail;
	u8 data[BYD_MAX_CAN_RX_DATA_LENGTH];
	u16 buffer_data_length;
	u16 i;
	u16 j;
	u16 packet_length;
	u16 packet_length_index;
	u16 packet_checksum_index;
	u16 packet_counter;
	u8 packet_checksum;
	u8 checksum;
	
	for(i=start;i!=end;)
	{
		if(end==i)
		{
			buffer_data_length=0;
		}
		else if(end>i)
		{
			buffer_data_length=end-i;
		}
		else
		{
			buffer_data_length=MAX_CAN_RX_BUFFER_LENGTH-i+end;
		}		

		if(buffer_data_length)
		{
			if(BYD_CAN_HEAD_CODE==CanFunRxBuffer.data[i])
			{
				if(buffer_data_length>=BYD_MIN_CAN_RX_DATA_LENGTH)
				{
					packet_length_index=i+2;
					if(packet_length_index>=MAX_CAN_RX_BUFFER_LENGTH)
					{
						packet_length_index-=MAX_CAN_RX_BUFFER_LENGTH;
					}
					packet_length=CanFunRxBuffer.data[packet_length_index]+4;			//s数据包长度
					
					packet_checksum_index=i+packet_length-1;							//
					if(packet_checksum_index>=MAX_CAN_RX_BUFFER_LENGTH)
					{
						packet_checksum_index-=MAX_CAN_RX_BUFFER_LENGTH;
					}
					packet_checksum=CanFunRxBuffer.data[packet_checksum_index];			//校验和
					
					if(packet_length<=BYD_MAX_CAN_RX_DATA_LENGTH)							//最大接收到的长度
					{
						if(buffer_data_length>=packet_length)							//缓冲区内至少有一包数据
						{
							checksum=0;
							packet_counter=i+1;
							for(j=0;j<(packet_length-2);j++)							//累加数据和
							{
								checksum+=CanFunRxBuffer.data[packet_counter];
								packet_counter++;
								if(packet_counter>=MAX_CAN_RX_BUFFER_LENGTH)
								{
									packet_counter=0;
								}
							}
							checksum^=0xFF;
							if(packet_checksum==checksum)								//接收到的数据和和接收到的校验和数据相等
							{
								packet_counter=i;
								for(j=0;j<packet_length;j++)
								{
									data[j]=CanFunRxBuffer.data[packet_counter];		//将数据存入data中
									CanFunRxBuffer.data[packet_counter]=0;
									packet_counter++;
									if(packet_counter>=MAX_CAN_RX_BUFFER_LENGTH)
									{
										packet_counter=0;
									}
								}
								CanFunRxBuffer.head=packet_counter;
								CanBox_RxService_BYD(data);
								break;
							}
						}
						else
						{
							break;
						}
					}					
				}
				else
				{
					break;
				}
			}
			else if(BYD_RX_ACK==CanFunRxBuffer.data[i]
					||BYD_RX_NACK_ERR_CHECKSUM==CanFunRxBuffer.data[i]
					||BYD_RX_NACK_NO_SUPPORT==CanFunRxBuffer.data[i]
					||BYD_RX_NACK_BUSY==CanFunRxBuffer.data[i])
			{
				CanBox_RxAck_BYD(CanFunRxBuffer.data[i]);
			}
		}
		else
		{
			break;
		}
		i++;
		if(i>=MAX_CAN_RX_BUFFER_LENGTH)
		{
			i=0;
		}
		CanFunRxBuffer.head=i;
	}	
}

void CanBox_TxService_BYD(void)
{
	u8 i;
	u8 length=0;
	u8 checksum=0;
	MESSAGE*nEvt;	

	if(F_CAN_TX_BUFFER_FULL==0)
	{
		nEvt=GetMessage(SUB_CAN_MODULE);
		if(nEvt->ID==NO_EVT)
		{
			return;
		}
		switch(nEvt->ID)
		{
			case BYD_CMD_APP_DATA:
				CanFunTxBuffer[0]=BYD_CAN_HEAD_CODE;	
				CanFunTxBuffer[1]=LSB(nEvt->prm);
				switch(CanFunTxBuffer[1])
				{
					case BYD_TX_RIGHT_CAMERA_INFO:
						CanFunTxBuffer[2]=21;
						for(i=0;i<21;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.right_camera_info;
						}
						break;
					case BYD_TX_PM25_CHECK_CMD:
						CanFunTxBuffer[2]=2;
						for(i=0;i<2;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.pm25_check_cmd;
						}
						break;
					
					case BYD_TX_DRIVE_CONTROL_INFO:
						CanFunTxBuffer[2]=3;
						for(i=0;i<3;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.drive_control_info[i];
						}
						break;
					case BYD_TX_TIME_INFO:
						CanFunTxBuffer[2]=7;
						for(i=0;i<7;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.time_info[i];
						}
						break;
					case BYD_TX_WINDOW_CONTROL_INFO:
						CanFunTxBuffer[2]=21;
						for(i=0;i<21;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.window_control_info;
						}
						break;
					
					case BYD_TX_START_END_CMD:
						CanFunTxBuffer[2]=10;
						for(i=0;i<10;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.start_cmd;
						}
						break;
					case BYD_TX_DRIVER_SETTING_CMD:
						CanFunTxBuffer[2]=8;
						for(i=0;i<8;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.driver_setting_cmd[i];
						}
						break;
					case BYD_TX_AIR_CONTROL_INFO:
						CanFunTxBuffer[2]=21;
						for(i=0;i<21;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.air_control_info[i];
						}
						break;
					case BYD_TX_LOCATION_INFO:
						CanFunTxBuffer[2]=21;
						for(i=0;i<21;i++)
						{
							CanFunTxBuffer[3+i]=BYDCanAdapterTxInfo.location_info[i];
						}
						break;
					default:
						CanFunTxBuffer[2]=0;
						break;
				}
				length=CanFunTxBuffer[2]+3;
				if(length==3)
				{
					length=0;
				}
				break;
			default:
				length=0;
				break;
		}
		if(length!=0)
		{
			for(i=1;i<length;i++)
			{
				checksum+=CanFunTxBuffer[i];
			}
			checksum^=0xFF;
			CanFunTxBuffer[length]=checksum;
			CanFunTxLength=length+1;
			CanBox_StartFrame();      
		}
	}
}

void CanBox_MainPro_BYD(void)
{
	CanBox_MainEvtPro_BYD();
	CanBox_RxAnalyse_BYD();
	
	if(CanBoxWorkTimer)
	{
		CanBoxWorkTimer--;
	}
	switch(CanBoxWorkState)
	{
		case BYD_IDLE:
			break;
		case BYD_TX_START_COMMAND:
			if(CanBoxWorkTimer)
			{
				break;
			}
			CanBox_Initial();
			BYD_TxStartEndCmd(0x01);
			CanBoxWorkState=BYD_WAIT_START_ACK;
			CanBoxWorkTimer=T300MS_10;
			break;
		case BYD_WAIT_START_ACK:
			if(CanBoxWorkTimer==0)
			{
				CanBoxWorkState=BYD_TX_START_COMMAND;
			}
			break;
		case BYD_WORK_NORMAL:
			CanBox_TxService_BYD();
			break;
		case BYD_TX_END_COMMAND:
			BYD_TxStartEndCmd(0);
			CanBoxWorkState=BYD_WAIT_END_ACK;
			CanBoxWorkTimer=T300MS_10;
			break;
		case BYD_WAIT_END_ACK:
			if(CanBoxWorkTimer==0)
			{
				CanBoxWorkState=BYD_TX_END_COMMAND;
			}
			break;
		case BYD_POWER_OFF:
			CanBoxWorkState=BYD_IDLE;
			break;
		default:
			break;
	}
}

void BYD_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	u8 *ptr;
	u8 length=0;
	u8 i;

	cmd_id=buffer[1];
	switch(cmd_id)
	{
		
		case BYD_TX_RIGHT_CAMERA_INFO:
			BYDCanAdapterTxInfo.right_camera_info=0;
			ptr=&BYDCanAdapterTxInfo.right_camera_info;
			length=buffer[2];
			if(length>21)
			{
				length=21;
			}
			break;
		case BYD_TX_PM25_CHECK_CMD:
			BYDCanAdapterTxInfo.pm25_check_cmd=0;
			ptr=&BYDCanAdapterTxInfo.pm25_check_cmd;
			length=buffer[2];
			if(length>21)
			{
				length=21;
			}
			break;
		case BYD_TX_DRIVE_CONTROL_INFO:
			for(i=0;i<16;i++)
			{
				BYDCanAdapterTxInfo.drive_control_info[i]=0;
			}
			ptr=&BYDCanAdapterTxInfo.drive_control_info[0];
			length=buffer[2];
			if(length>15)
			{
				length=15;
			}
			break;
		case BYD_TX_TIME_INFO:
			for(i=0;i<8;i++)
			{
				BYDCanAdapterTxInfo.time_info[i]=0;
			}
			ptr=&BYDCanAdapterTxInfo.time_info[0];
			length=buffer[2];
			if(length>7)
			{
				length=7;
			}
			break;
		case BYD_TX_WINDOW_CONTROL_INFO:
			BYDCanAdapterTxInfo.window_control_info=0;
			ptr=&BYDCanAdapterTxInfo.window_control_info;
			length=buffer[2];
			if(length>21)
			{
				length=21;
			}
			break;
		case BYD_TX_START_END_CMD:
			BYDCanAdapterTxInfo.start_cmd=0;
			ptr=&BYDCanAdapterTxInfo.start_cmd;
			length=buffer[2];
			if(length>10)
			{
				length=10;
			}
			break;
		case BYD_TX_DRIVER_SETTING_CMD:
			for(i=0;i<3;i++)
			{
				BYDCanAdapterTxInfo.driver_setting_cmd[i]=0;
			}
			ptr=&BYDCanAdapterTxInfo.driver_setting_cmd[0];
			length=buffer[2];
			if(length>2)
			{
				length=2;
			}
			break;
		case BYD_TX_AIR_CONTROL_INFO:
			for(i=0;i<3;i++)
			{
				BYDCanAdapterTxInfo.air_control_info[i]=0;
			}
			ptr=&BYDCanAdapterTxInfo.air_control_info[0];
			length=buffer[2];
			if(length>2)
			{
				length=2;
			}
			break;
		case BYD_TX_LOCATION_INFO:
			for(i=0;i<5;i++)
			{
				BYDCanAdapterTxInfo.location_info[i]=0;
			}
			ptr=&BYDCanAdapterTxInfo.location_info[0];
			length=buffer[2];
			if(length>4)
			{
				length=4;
			}
			break;
		
		default:
			length=0;	
			break;
	}
	if(length)
	{
		for(i=0;i<length;i++)
		{
			ptr[i]=buffer[i+3];
		}
		PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,cmd_id);
	}
}

void BYD_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 *ptr;
	u8 counter;
	u8 i;
	u8 checksum;
	
	buffer[0]=BYD_CAN_HEAD_CODE;
	buffer[1]=cmd_id;
	switch(cmd_id)
	{
		case BYD_RX_VOICE_BROAD_INFO:
			ptr=&BYDCanAdapterRxInfo.voice_info;
			*length=2;
			break;
		case BYD_RX_WINDOW_INFO:
			ptr=&BYDCanAdapterRxInfo.window_info[0];
			*length=6;
			break;
		case BYD_RX_PM25_INFO:
			ptr=&BYDCanAdapterRxInfo.pm25_info[0];
			*length=2;
			break;
		case BYD_RX_PANORAMA_INFO:
			ptr=&BYDCanAdapterRxInfo.panorama_info;
			*length=6;
			break;
		case BYD_RX_CAMERA_CONTROL:
			ptr=&BYDCanAdapterRxInfo.camera_control_info;
			*length=6;
			break;
		case BYD_RX_DRIVING_INFO:
			ptr=&BYDCanAdapterRxInfo.driving_info[0];
			*length=6;
			break;
				case BYD_RX_FRONT_RADAR_INFO:
			ptr=&BYDCanAdapterRxInfo.front_radar_info[0];
			*length=6;
			break;
		case BYD_RX_REAR_RADAR_INFO:
			ptr=&BYDCanAdapterRxInfo.rear_radar_info[0];
			*length=6;
			break;
		case BYD_RX_STEER_KEY:
			ptr=&BYDCanAdapterRxInfo.steer_key_info[0];
			*length=2;
			break;
		case BYD_RX_BASIC_INFO:
			ptr=&BYDCanAdapterRxInfo.baseinfo[0];
			*length=2;
			break;
		case BYD_RX_SPEED:
			ptr=&BYDCanAdapterRxInfo.speed_info[0];
			*length=6;
			break;
		case BYD_RX_CAR_INFO:
			ptr=&BYDCanAdapterRxInfo.car_info[0];
			*length=6;
			break;
		case BYD_RX_AIR_INFO:
			ptr=&BYDCanAdapterRxInfo.air_info[0];
			*length=9;
			break;
		case BYD_RX_EPS_INFO:
			ptr=&BYDCanAdapterRxInfo.eps_info[0];
			*length=2;
			break;
		
		default:
			*length=0;
			break;
	}
	if(*length>=1)
	{	
		buffer[2]=*length;
		checksum=buffer[1]+buffer[2];
		counter=*length;
		for(i=0;i<counter;i++)
		{
			buffer[i+3]=ptr[i];		
			checksum+=buffer[i+3];
		}
		buffer[i+3]=(~checksum)^0xFF;
		*length+=4;
	}	
}
#endif
#endif

