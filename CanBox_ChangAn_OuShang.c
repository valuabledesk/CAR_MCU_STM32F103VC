#include "public.h"

#if CAN_ADAPTER==1
#if CANBOX_CHANGAN_OUSHANG==1

C_OuShang_CAN_RX_INFO C_OuShang_CanAdapterRxInfo;
C_OuShang_CAN_TX_INFO C_OuShang_CanAdapterTxInfo;

const u8 C_OuShang_SteerKeyTab[C_OuShang_WHEEL_KEY_NUM][4]=
{
	/*
	0:只有短按功能
	1:有长按功能，但长按按键没有连续功能
	2:有长按功能，并且长按按键有连续功能
	3:短按按键，但长按有连续功能
	*/

	{CANKEY_OFF,	NO_KEY,					NO_KEY,					0},
	{CANKEY_1,		UICC_VOLUME_UP,			NO_KEY,			3},
	{CANKEY_2,		UICC_VOLUME_DOWN,		NO_KEY,			3},
	{CANKEY_3,		UICC_SKIPB,				NO_KEY,			    	7},	
	{CANKEY_4,		UICC_SKIPF,				NO_KEY,			    	7},	
	{CANKEY_5,	  UICC_MUTE	,			NO_KEY,						0},
	{CANKEY_6,	  UICC_SOURCE,				NO_KEY,						0},//模式键
	{CANKEY_7,		UICC_BT_ACPTCALL,			  NO_KEY,						0},
	{CANKEY_8,	  UICC_BT_HUNGUPCALL,		    NO_KEY,						5},
	{CANKEY_9,	  UICC_FM,		    NO_KEY,						0},//待定
	{CANKEY_10,	  UICC_FICTITIOUS_POWER_OFF,		    NO_KEY,						0},//待定
	{CANKEY_11,	  NO_KEY,		    NO_KEY,						0},
	{CANKEY_12,	  NO_KEY,		    NO_KEY,						0},
	{CANKEY_13,	  NO_KEY,		    NO_KEY,						0},
	{CANKEY_14,	  NO_KEY,		    NO_KEY,						0},
	{CANKEY_15,	  NO_KEY,		    NO_KEY,						0},
	{CANKEY_16,	  NO_KEY,		    NO_KEY,						0},
	{CANKEY_17,	  UICC_VOLUME_UP,		    NO_KEY,						0},
	{CANKEY_18,	  UICC_VOLUME_DOWN,		    NO_KEY,						0},
	{CANKEY_19,	  UICC_HOME,		  NO_KEY,						0},
	{CANKEY_20,	  UICC_OPEN_SOUND,		NO_KEY,						0},//MIC_语音键
};


void C_OuShang_TxGetDataCmd(u8 cmd)
{
	CanFunTxBuffer[0]=C_OuShang_CAN_HEAD_CODE;
	CanFunTxBuffer[1]=C_OuShang_TX_REQUEST_CMD;
	CanFunTxBuffer[2]=0x02;
	CanFunTxBuffer[3]=cmd;
	CanFunTxBuffer[4]=0;
	CanFunTxBuffer[5]=(CanFunTxBuffer[1]+CanFunTxBuffer[2]+CanFunTxBuffer[3]+CanFunTxBuffer[4])^0xFF;
  CanBoxUartTxFarmat(CanFunTxBuffer,6);
}

void C_OuShang_TxStartEndCmd(u8 start_end)
{
	CanFunTxBuffer[0]=C_OuShang_CAN_HEAD_CODE;
	CanFunTxBuffer[1]=C_OuShang_TX_START_END_CMD;
	CanFunTxBuffer[2]=0x01;
	if(0x01==start_end)
	{
		CanFunTxBuffer[3]=0x01;
	}
	else
	{
		CanFunTxBuffer[3]=0x00;
	}
	CanFunTxBuffer[4]=(CanFunTxBuffer[1]+CanFunTxBuffer[2]+CanFunTxBuffer[3])^0xFF;
  CanBoxUartTxFarmat(CanFunTxBuffer,5);
}

void CanBox_MainEvtPro_C_OuShang(void)
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
		{
			CanBoxWorkTimer=T300MS_10;
			CanBoxWorkState=C_OuShang_TX_START_COMMAND;
		}
		break;

		case CAN_POWER_OFF:
			break;
		
		case CAN_ACC_OFF:
		{
			CanBoxWorkState=C_OuShang_TX_END_COMMAND;
		}
		break;
		
		case CAN_EMERGENCY_OFF:
		{
				CanBoxWorkState=C_OuShang_POWER_OFF;
		}
		break;
		case CAN_RX_APP_DATA:
		{
				PostMessage(SUB_CAN_MODULE,C_OuShang_CMD_APP_DATA,nEvt->prm);
		}
		break;
		
		default:
			break;
	}
}

void CanBox_RxAck_C_OuShang(u8 rx_ack)
{
	switch(rx_ack)
	{
		case C_OuShang_RX_ACK:
		{
			F_EXIST_CANBOX=1;
			F_CAN_TX_BUFFER_FULL=0;
			F_CAN_TX_ACK_CHECK=0;
			if(C_OuShang_WAIT_START_ACK==CanBoxWorkState)
			{
				C_OuShang_TxGetDataCmd(C_OuShang_RX_AIR_INFO);
				CanBoxWorkState=C_OuShang_WORK_NORMAL;
			}
			else if(C_OuShang_WAIT_END_ACK==CanBoxWorkState)
			{
				CanBoxWorkState=C_OuShang_POWER_OFF;
			}
		}
		break;
		
		case C_OuShang_RX_NACK_NO_SUPPORT:
		{
			F_CAN_TX_BUFFER_FULL=0;
			F_CAN_TX_ACK_CHECK=0;
		}
		break;
		
		case C_OuShang_RX_NACK_ERR_CHECKSUM:
		case C_OuShang_RX_NACK_BUSY:
		{
				F_CAN_TX_ACK_CHECK=1;
		}
		break;
		
		default:
			break;
	}
}

void CanBox_RxService_C_OuShang(u8 *data)
{
	u8 tx_ack;
	u8 data_type;
	u32 i;
	
	data_type=data[1];
	tx_ack=C_OuShang_RX_ACK;
	switch(data_type)
	{
		case C_OuShang_RX_STEER_KEY:
		{
			if(data[3]<C_OuShang_WHEEL_KEY_NUM) 
			{
				CanKeyInfo.CanKeyCode=data[3];
				CanKeyInfo.KeyStatus=data[4];	
				CanKeyInfo.KeyCode=C_OuShang_SteerKeyTab[CanKeyInfo.CanKeyCode][1];
				CanKeyInfo.LongKeyCode=C_OuShang_SteerKeyTab[CanKeyInfo.CanKeyCode][2];	
				CanKeyInfo.KeyProperty=C_OuShang_SteerKeyTab[CanKeyInfo.CanKeyCode][3]; 
				CanKeyInfo.key_source=STEER;
				CanKeyScan();
			}
		}
		break;
		
		case C_OuShang_RX_AIR_INFO:
		{
			for(i=0;i<4;i++)
			{
				C_OuShang_CanAdapterRxInfo.air_info[i]=data[3+i];
			}
		  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_AIR_INFO);
		}
		break;

		case C_OuShang_RX_R_RADER_INFO:
		{
			for(i=0;i<4;i++)
			{
				C_OuShang_CanAdapterRxInfo.r_rader_info[i]=data[3+i];
			}
		  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_R_RADER_INFO);
		}
		break;

		case C_OuShang_RX_F_RADER_INFO:
		{
			for(i=0;i<4;i++)
			{
				C_OuShang_CanAdapterRxInfo.f_rader_info[i]=data[3+i];
			}
		  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_F_RADER_INFO);
		}
		break;

		case C_OuShang_RX_EPS_INFO:
		{
			C_OuShang_CanAdapterRxInfo.eps_info[0]=data[3];
			C_OuShang_CanAdapterRxInfo.eps_info[1]=data[4];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_EPS_INFO);
		}
		break;
#if MODEL==LINUX_1307WSC_69
#else
		case C_OuShang_RX_R_VIDEO_INFO://右方视频
		{
			C_OuShang_CanAdapterRxInfo.r_video_info=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_R_VIDEO_INFO);
#if MODEL==LINUX_P085_RK
#else
			if(((C_OuShang_CanAdapterRxInfo.r_video_info&0x80)>>7)==1)
			{
				CanGeneralCtrlFlag.field.camera_on_off=1;
			}
			else
			{
				CanGeneralCtrlFlag.field.camera_on_off=0;
			}
#endif
		}
		break;
#endif

		case C_OuShang_RX_P_VIDEO_INFO://全景视频
		{
			C_OuShang_CanAdapterRxInfo.p_video_info=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_P_VIDEO_INFO);
			if(((C_OuShang_CanAdapterRxInfo.p_video_info&0x80)>>7)==1)
			{
				CanGeneralCtrlFlag.field.reverse_on_off=1;
			}
			else
			{
				CanGeneralCtrlFlag.field.camera_on_off=1;
				CanGeneralCtrlFlag.field.reverse_on_off=0;
			}
		}
		break;
		
		case C_OuShang_RX_P_TIRE_INFO://胎压基本信息
		{
			for(i=0;i<8;i++)
			{
				C_OuShang_CanAdapterRxInfo.tire_pressure_info[i]=data[3+i];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_P_TIRE_INFO);
		}
		break;

		case C_OuShang_RX_W_TIRE_INFO://胎压报警信息
		{
			for(i=0;i<4;i++)
			{
				C_OuShang_CanAdapterRxInfo.tire_warning_info[i]=data[3+i];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_W_TIRE_INFO);
		}
		break;	
		
		case C_OuShang_RX_BASIC_INFO:
		{
			for(i=0;i<3;i++)
			{
				C_OuShang_CanAdapterRxInfo.basic_info[i]=data[3+i];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_BASIC_INFO);
		}
		break;
		
		case C_OuShang_RX_BACKLIGHT_INFO:
		{
			C_OuShang_CanAdapterRxInfo.backlight_info=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_BACKLIGHT_INFO);
		}
		break;
		
		case C_OuShang_RX_LIGHT_INFO:
		{
			C_OuShang_CanAdapterRxInfo.light_info=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_LIGHT_INFO);
		}
		break;
		
		case C_OuShang_RX_SETTING_INFO:
		{
			for(i=0;i<2;i++)
			{
				C_OuShang_CanAdapterRxInfo.setting_info[i]=data[3+i];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_SETTING_INFO);
		}
		break;
		
		case C_OuShang_RX_VERSION_INFO:               //数据长度为假定值，具体待定
		{
			for(i=0;i<32;i++)
			{
			  C_OuShang_CanAdapterRxInfo.version_info[i]=data[3+i];
			}
		  PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,C_OuShang_RX_VERSION_INFO);
		}
		break;
		
		default:
			tx_ack=C_OuShang_RX_NACK_NO_SUPPORT;
			break;
	}
	CanBoxUartTxFarmat(&tx_ack,1);
}

void CanBox_RxAnalyse_C_OuShang(void)//有效数据抓取算法
{
	u16 start=CanFunRxBuffer.head;
	u16 end=CanFunRxBuffer.tail;
	u8 data[C_OuShang_MAX_CAN_RX_DATA_LENGTH];
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
			if(C_OuShang_CAN_HEAD_CODE==CanFunRxBuffer.data[i])
			{
				if(buffer_data_length>=C_OuShang_MIN_CAN_RX_DATA_LENGTH)
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
					
					if(packet_length<=C_OuShang_MAX_CAN_RX_DATA_LENGTH)							//最大接收到的长度
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
								CanBox_RxService_C_OuShang(data);
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
			else if(C_OuShang_RX_ACK==CanFunRxBuffer.data[i]
					||C_OuShang_RX_NACK_ERR_CHECKSUM==CanFunRxBuffer.data[i]
					||C_OuShang_RX_NACK_NO_SUPPORT==CanFunRxBuffer.data[i]
					||C_OuShang_RX_NACK_BUSY==CanFunRxBuffer.data[i])
			{
				CanBox_RxAck_C_OuShang(CanFunRxBuffer.data[i]);
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

void CanBox_TxService_C_OuShang(void)
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
			case C_OuShang_CMD_APP_DATA:
			{
				CanFunTxBuffer[0]=C_OuShang_CAN_HEAD_CODE;	
				CanFunTxBuffer[1]=LSB(nEvt->prm);
				switch(CanFunTxBuffer[1])
				{
					case C_OuShang_TX_MAINTENANCE_INFO:
					{
						CanFunTxBuffer[2]=4;
						for(i=0;i<4;i++)
						{
							CanFunTxBuffer[3+i]=C_OuShang_CanAdapterTxInfo.maintenance_cmd[i];
						}
					}
					break;
						
					case C_OuShang_TX_CAR_SETTING_CMD:
					{
						CanFunTxBuffer[2]=2;
					 	CanFunTxBuffer[3]=C_OuShang_CanAdapterTxInfo.car_setting_cmd[0];
			    	CanFunTxBuffer[4]=C_OuShang_CanAdapterTxInfo.car_setting_cmd[1];
					}
					break;					
					
					case C_OuShang_TX_P_TRACK_CMD:
					{
						CanFunTxBuffer[2]=2;
						CanFunTxBuffer[3]=C_OuShang_CanAdapterTxInfo.p_track_cmd[0];
				    CanFunTxBuffer[4]=C_OuShang_CanAdapterTxInfo.p_track_cmd[1];
					}
					break;

					case C_OuShang_TX_AIR_CMD:
					{
						CanFunTxBuffer[2]=6;
						for(i=0;i<6;i++)
						{
							CanFunTxBuffer[3+i]=C_OuShang_CanAdapterTxInfo.air_cmd[i];
						}
					}
					break;

					case C_OuShang_TX_REQUEST_CMD:
					{
						CanFunTxBuffer[2]=2;
						CanFunTxBuffer[3]=C_OuShang_CanAdapterTxInfo.request_cmd[0];//存疑
						CanFunTxBuffer[4]=C_OuShang_CanAdapterTxInfo.request_cmd[1];//存疑
					}
					break;
					  
					case C_OuShang_TX_P_VIDEO_CMD:
					{
						CanFunTxBuffer[2]=1;
					 	CanFunTxBuffer[3]=C_OuShang_CanAdapterTxInfo.p_video_cmd;
					}		      
					break;

					case C_OuShang_TX_TYPE_CMD:
					{
						CanFunTxBuffer[2]=3;
						CanFunTxBuffer[3]=C_OuShang_CanAdapterTxInfo.type_cmd[0];//存疑
						CanFunTxBuffer[4]=C_OuShang_CanAdapterTxInfo.type_cmd[1];//存疑
					}
					break;
					
					case C_OuShang_TX_R_VER_CMD://存疑
					{
						CanFunTxBuffer[2]=1;
						CanFunTxBuffer[3]=1;
					}
					break;
					
				}
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

void CanBox_MainPro_C_OuShang(void)
{
	CanBox_MainEvtPro_C_OuShang();
	CanBox_RxAnalyse_C_OuShang();
	
	if(CanBoxWorkTimer)
	{
		CanBoxWorkTimer--;
	}
	switch(CanBoxWorkState)
	{
		case C_OuShang_IDLE:
			break;
		case C_OuShang_TX_START_COMMAND:
		{
			if(CanBoxWorkTimer)
			{
				break;
			}
			CanBox_Initial();
			//PostMessage(SUB_CAN_MODULE,C_OuShang_CMD_CAR_TYPE,0);
			C_OuShang_TxStartEndCmd(0x01);
			CanBoxWorkState=C_OuShang_WAIT_START_ACK;
			CanBoxWorkTimer=T300MS_10;
		}
		break;
		
		case C_OuShang_WAIT_START_ACK:
		{
			if(CanBoxWorkTimer==0)
			{
				CanBoxWorkState=C_OuShang_TX_START_COMMAND;
			}
		}
		break;
		
		case C_OuShang_WORK_NORMAL:
		{
			CanBox_TxService_C_OuShang();
		}
		break;
		
		case C_OuShang_TX_END_COMMAND:
		{
			C_OuShang_TxStartEndCmd(0);
			CanBoxWorkState=C_OuShang_WAIT_END_ACK;
			CanBoxWorkTimer=T300MS_10;
		}
		break;
		
		case C_OuShang_WAIT_END_ACK:
		{
			if(CanBoxWorkTimer==0)
			{
				CanBoxWorkState=C_OuShang_TX_END_COMMAND;
			}			
		}
		break;
		
		case C_OuShang_POWER_OFF:
		{
			CanBoxWorkState=C_OuShang_IDLE;
		}
		break;
		
		default:
			break;
	}
}


void C_OuShang_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	u8 *ptr;
	u8 length=0;
	u8 i;

	cmd_id=buffer[1];
	switch(cmd_id)
	{
		case C_OuShang_TX_MAINTENANCE_INFO:
		{
			ptr=&C_OuShang_CanAdapterTxInfo.maintenance_cmd[0];
			length=4;				
		}
		break;
		
		case C_OuShang_TX_CAR_SETTING_CMD:
		{
			ptr=&C_OuShang_CanAdapterTxInfo.car_setting_cmd[0];
			length=2;				
		}
		break;

		case C_OuShang_TX_P_TRACK_CMD:
		{
			ptr=&C_OuShang_CanAdapterTxInfo.p_track_cmd[0];
			length=2;
		}
		break;

		case C_OuShang_TX_AIR_CMD:
		{
			ptr=&C_OuShang_CanAdapterTxInfo.air_cmd[0];
			length=6;			
		}
		break;
		
		case C_OuShang_TX_REQUEST_CMD:
		{
			ptr=&C_OuShang_CanAdapterTxInfo.request_cmd[0];
			length=2;			
		}
		break;
		
		case C_OuShang_TX_P_VIDEO_CMD:
		{
			ptr=&C_OuShang_CanAdapterTxInfo.p_video_cmd;
			length=1;
		}		      
		break;
			
		case C_OuShang_TX_TYPE_CMD:
		{
			ptr=&C_OuShang_CanAdapterTxInfo.type_cmd[0];
			length=2;			
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

void C_OuShang_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 *ptr;
	u8 counter;
	u8 i;
	u8 checksum;
	
	buffer[0]=C_OuShang_CAN_HEAD_CODE;
	buffer[1]=cmd_id;
	switch(cmd_id)
	{
		case C_OuShang_RX_AIR_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.air_info[0];
			*length=4;
		}
		break;
		
		case C_OuShang_RX_VERSION_INFO:     //数据宽度为假定值，具体待定
		{
			ptr=&C_OuShang_CanAdapterRxInfo.version_info[0];
			*length=32;
		}
		break;
		
		case C_OuShang_RX_R_RADER_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.r_rader_info[0];
			*length=4;
		}
		break;
			
		case C_OuShang_RX_F_RADER_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.f_rader_info[0];
			*length=4;
		}
		break;
			
		case C_OuShang_RX_EPS_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.eps_info[0];
			*length=2;
		}
		break;
			
		case C_OuShang_RX_R_VIDEO_INFO:
		{
				ptr=&C_OuShang_CanAdapterRxInfo.r_video_info;
			*length=1;
		}
		break;		
			
		case C_OuShang_RX_P_VIDEO_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.p_video_info;
			*length=1;
		}
		break;
			
		case C_OuShang_RX_P_TIRE_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.tire_pressure_info[0];
			*length=8;
		}
		break;	
			
		case C_OuShang_RX_W_TIRE_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.tire_warning_info[0];
			*length=4;
		}
		break;		
			
		case C_OuShang_RX_BASIC_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.basic_info[0];
			*length=3;
		}
		break;			
			
		case C_OuShang_RX_BACKLIGHT_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.backlight_info;
			*length=1;
		}
		break;		
			
		case C_OuShang_RX_LIGHT_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.light_info;
			*length=1;
		}
		break;
			
		case C_OuShang_RX_SETTING_INFO:
		{
			ptr=&C_OuShang_CanAdapterRxInfo.setting_info[0];
			*length=2;
		}
		break;			

		default:
		{
			*length=0;
		}
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






