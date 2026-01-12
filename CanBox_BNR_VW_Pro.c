#include "public.h"	

#if CANBOX_BNR_VW==1
B_VW_CAN_RX_INFO B_VW_CanAdapterRxInfo;
B_VW_CAN_TX_INFO B_VW_CanAdapterTxInfo;
u8 B_VW_RequestTimer;
B_VW_REQUEST_INDEX B_VW_RequestIndex;
u16 B_VW_AmpResetTimer;
u8 B_VW_TxEpsTimer;
u8 CanReversFlag;

const u8 B_VM_SteerKeyTab[B_VW_WHEEL_KEY_NUM][4]=
{
/*
0:只有短按功能
1:有长按功能，但长按按键没有连续功能
2:有长按功能，并且长按按键有连续功能
3:短按按键，但长按有连续功能
*/
	{CANKEY_OFF,	NO_KEY,					NO_KEY,						0},
	{CANKEY_1,		UICC_VOLUME_UP,			NO_KEY,						3},
	{CANKEY_2,		UICC_VOLUME_DOWN,		NO_KEY,						3},
	{CANKEY_3,		UICC_SKIPF,				UICC_NEXT_LONG,				1},
	{CANKEY_4,		UICC_SKIPB,	 			UICC_PREV_LONG,				1},
	{CANKEY_5,		UICC_BT_ACPTCALL,	       UICC_BT_HUNGUPCALL,		1},
	{CANKEY_6,		UICC_MUTE,				NO_KEY,			                     0},
	{CANKEY_7,		UICC_SOURCE,			NO_KEY,		                            0},
	{CANKEY_8,		NO_KEY,				       NO_KEY,		                            0},
	{CANKEY_9,		UICC_PLAY_PAUSE,		NO_KEY,		                            0},
};

const u8 B_VW_RefreashTab[]=
{										
	B_VW_RX_BASIC_INFO,			
	B_VW_RX_CAR_INFO,		
	B_VW_RX_VERSION_INFO,
	B_VW_RX_SCREEN_TYPE,
};

void B_VW_TxStartEndCmd(u8 start_end)
{
	CanFunTxBuffer[0]=0x2E;
	CanFunTxBuffer[1]=B_VW_TX_START_END_CMD;
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

void B_VW_TxSourceOffCmd(void)
{	
	CanFunTxBuffer[0]=0x2E;
	CanFunTxBuffer[1]=B_VW_TX_SOURCE_INFO;
	CanFunTxBuffer[2]=0x02;
	CanFunTxBuffer[3]=0x00;
	CanFunTxBuffer[4]=0x00;
	CanFunTxBuffer[5]=(CanFunTxBuffer[1]+CanFunTxBuffer[2]+CanFunTxBuffer[3]+CanFunTxBuffer[4])^0xFF;	
  CanBoxUartTxFarmat(CanFunTxBuffer,6);
}

void B_VW_TxAck(u8 ack)
{	
    CanBoxUartTxFarmat(&ack,1);
}

void CanBox_MainEvtPro_B_VW(void)
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
			CanBoxWorkTimer=T300MS_10;
			CanBoxWorkState=B_VW_TX_START_COMMAND;
			break;
		case CAN_POWER_OFF:
			PostMessage(SUB_CAN_MODULE,B_VW_CMD_SOURCE_OFF_CMD,OFF);	
			break;
		case CAN_ACC_OFF:
			CanBoxWorkState=B_VW_TX_SOURCE_OFF;
			break;
		case CAN_EMERGENCY_OFF:
			CanBoxWorkState=B_VW_POWER_OFF;
			break;
		case CAN_RX_APP_DATA:
			PostMessage(SUB_CAN_MODULE,B_VW_CMD_APP_DATA,nEvt->prm);
			break;
		default:
			break;
	}
}

void CanBox_RxAck_B_VW(u8 rx_ack)
{
	switch(rx_ack)
	{
		case RX_ACK:
			F_EXIST_CANBOX=1;
			F_CAN_TX_BUFFER_FULL=0;
			F_CAN_TX_ACK_CHECK=0;
			if(B_VW_WAIT_START_ACK==CanBoxWorkState)
			{
				CanBoxWorkState=B_VW_WORK_NORMAL;
			}
			else if(B_VW_WAIT_SOURCE_OFF_ACK==CanBoxWorkState)
			{
				CanBoxWorkState=B_VW_TX_END_COMMAND;
			}
			else if(B_VW_WAIT_END_ACK==CanBoxWorkState)
			{
				CanBoxWorkState=B_VW_POWER_OFF;
			}
			break;
		case RX_NACK_NO_SUPPORT:
			F_CAN_TX_BUFFER_FULL=0;
			F_CAN_TX_ACK_CHECK=0;
			break;
		case RX_NACK_ERR_CHECKSUM:
		case RX_NACK_BUSY:
			F_CAN_TX_ACK_CHECK=1;
			break;
		default:
			break;
	}
}

void CanBox_RxService_B_VW(u8 *data)
{
	u8 i;
	u8 tx_ack;
	u8 data_type;
	
	data_type=data[1];
	tx_ack=RX_ACK;
	switch(data_type)
	{
		case B_VW_RX_REQUEST_INFO:
			B_VW_CanAdapterRxInfo.request_info=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_REQUEST_INFO);
			break;
		case B_VW_RX_LIGHT_INFO:
			{
				u32 value;

				if(data[3])
				{
					B_VW_CanAdapterRxInfo.light_info=data[3];
					value=(100*B_VW_CanAdapterRxInfo.light_info)/255;
#if defined(STM32_F103VC)
#if PANEL_LED_CTRL_BY_GPIO==0
					if(value!=KeyLedDutyCycle
						&&F_LIGHTING_FLAG)
					{
						KeyLedDutyCycle=value;
						KeyPwmConfig(KEY_LIGHT_MID_BRIGHT);
						PanelKeyLightState=KEY_LIGHT_MID_BRIGHT;
					}
#endif
#else
					if(value!=KeyLedDutyCycle
						&&F_LIGHTING_FLAG)
					{
						KeyLedDutyCycle=value;
						KeyPwmConfig(KEY_LIGHT_MID_BRIGHT);
						PanelKeyLightState=KEY_LIGHT_MID_BRIGHT;
					}
#endif
					KeyLedDutyCycle=value;  
				}
			}
			break;
		case B_VW_RX_SPEED_INFO:
			B_VW_CanAdapterRxInfo.speed[0]=data[3];
			B_VW_CanAdapterRxInfo.speed[1]=data[4];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_SPEED_INFO);
			break;
		case B_VW_RX_STEER_KEY:	
			if(data[3]<B_VW_WHEEL_KEY_NUM) 
			{
				CanKeyInfo.CanKeyCode=data[3];
				CanKeyInfo.KeyStatus=data[4];	
				CanKeyInfo.KeyCode=B_VM_SteerKeyTab[ CanKeyInfo.CanKeyCode][1];
				CanKeyInfo.LongKeyCode=B_VM_SteerKeyTab[ CanKeyInfo.CanKeyCode][2];	
				CanKeyInfo.KeyProperty=B_VM_SteerKeyTab[ CanKeyInfo.CanKeyCode][3]; 
				CanKeyInfo.key_source=STEER;
				CanKeyScan();   	
			}
			break;
		case B_VW_RX_AIR_INFO:
			B_VW_CanAdapterRxInfo.air_info[0]=data[3];
			B_VW_CanAdapterRxInfo.air_info[1]=data[4];
			B_VW_CanAdapterRxInfo.air_info[2]=data[5];
			B_VW_CanAdapterRxInfo.air_info[3]=data[6];
			B_VW_CanAdapterRxInfo.air_info[4]=data[7];
			B_VW_CanAdapterRxInfo.air_info[5]=data[8];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_AIR_INFO);
			break;
		case B_VW_RX_REAR_RADAR_INFO:
			B_VW_CanAdapterRxInfo.rear_radar_info[0]=data[3];
			B_VW_CanAdapterRxInfo.rear_radar_info[1]=data[4];
			B_VW_CanAdapterRxInfo.rear_radar_info[2]=data[5];
			B_VW_CanAdapterRxInfo.rear_radar_info[3]=data[6];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_REAR_RADAR_INFO);
			break;
		case B_VW_RX_FRONT_RADAR_INFO:
			B_VW_CanAdapterRxInfo.front_radar_info[0]=data[3];
			B_VW_CanAdapterRxInfo.front_radar_info[1]=data[4];
			B_VW_CanAdapterRxInfo.front_radar_info[2]=data[5];
			B_VW_CanAdapterRxInfo.front_radar_info[3]=data[6];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_FRONT_RADAR_INFO);				
			break;
		case B_VW_RX_BASIC_INFO:
			B_VW_CanAdapterRxInfo.basic_info[0]=data[3];
			B_VW_CanAdapterRxInfo.basic_info[1]=data[4];
			CanGeneralCtrlFlag.field.reverse_on_off=GetBit((B_VW_CanAdapterRxInfo.basic_info[0]),0);
			if(CanGeneralCtrlFlag.field.reverse_on_off)
			{
				CanReversFlag=1;
			}
			else
			{
				CanReversFlag=0;
			}
			CanGeneralCtrlFlag.field.parking_on_off=!GetBit((B_VW_CanAdapterRxInfo.basic_info[0]),1);
			CanGeneralCtrlFlag.field.ill_onoff=GetBit((B_VW_CanAdapterRxInfo.basic_info[0]),2);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_BASIC_INFO);
			break;
		case B_VW_RX_PARKING_INFO:
			B_VW_CanAdapterRxInfo.parking_info[0]=data[3];
			B_VW_CanAdapterRxInfo.parking_info[1]=data[4];
			if(CanDisableTimer==0)
			{
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_PARKING_INFO);
			}
			break;
		case B_VW_RX_EPS_INFO:
			{
				u32 temp;
				u32 old_index;
				u32 now_index;

				temp = (B_VW_CanAdapterRxInfo.eps_info[1])*256+B_VW_CanAdapterRxInfo.eps_info[0];
				temp &= 0xFFFF;
				if (temp & 0x8000)
				{
					temp = 0xFFFF - temp + 1;
					old_index=(temp*35)/11016 + 36;
				}
				else
				{
					old_index=(temp*35)/11016;
				}
				temp=(data[4])*256+data[3];
				temp&=0xFFFF;
				if(temp&0x8000)
				{
					temp=0xFFFF - temp + 1;
					now_index=(temp*35)/11016 + 36;
				}
				else
				{
					now_index=(temp*35)/11016;
				}
				if(Get_Reverse_Det_Flag)
				{
					if(old_index!=now_index)
				{
						if(B_VW_TxEpsTimer==0)
						{
							B_VW_CanAdapterRxInfo.eps_info[0]=data[3];
							B_VW_CanAdapterRxInfo.eps_info[1]=data[4];
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_EPS_INFO);
							B_VW_TxEpsTimer=T500MS_10;
				}
			}
					else
					{
						B_VW_CanAdapterRxInfo.eps_info[0]=data[3];
						B_VW_CanAdapterRxInfo.eps_info[1]=data[4];
					}
				}
				else
				{
					B_VW_CanAdapterRxInfo.eps_info[0]=0;
					B_VW_CanAdapterRxInfo.eps_info[1]=0;
				}
			}
//			PostMessage(NAVI_MODULE,MCU_TX_ARM2_EPS_INFO,0);
			break;
		case B_VW_RX_AMP_INFO:	
			for(i=0;i<8;i++)
			{
				B_VW_CanAdapterRxInfo.amp_info[i]=data[3+i];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_AMP_INFO);
			break;
		case B_VW_RX_VERSION_INFO:
			for(i=0;i<16;i++)
			{
				B_VW_CanAdapterRxInfo.version_info[i]=data[3+i];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_VERSION_INFO);
			break;
		case B_VW_RX_CAR_INFO:
			B_VW_CanAdapterRxInfo.car_info[0]=data[3];
			if(B_VW_CanAdapterRxInfo.car_info[0]==0x02)
			{
				for(i=1;i<13;i++)
				{
					B_VW_CanAdapterRxInfo.car_info[i]=data[3+i];
				}
			}
			else if(B_VW_CanAdapterRxInfo.car_info[0]==0x01)
			{
				B_VW_CanAdapterRxInfo.car_info[1]=data[4];
				B_VW_CanAdapterRxInfo.car_info[2]=data[5];
			}
			else
			{
				B_VW_CanAdapterRxInfo.car_info[1]=data[4];
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_CAR_INFO);
			break;
		case B_VW_RX_TURN_SIGNAL_LAMP:
			B_VW_CanAdapterRxInfo.turn_signal_lamp_info=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_TURN_SIGNAL_LAMP);
			break;
		case B_VW_RX_UPDATE_INFO:
			B_VW_CanAdapterRxInfo.update_info=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_UPDATE_INFO);
			break;
		case B_VW_RX_SCREEN_TYPE:
			B_VW_CanAdapterRxInfo.screen_type=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_SCREEN_TYPE);
			break;
		case B_VW_RX_LEFT_RADAR_INFO:
			B_VW_CanAdapterRxInfo.left_radar_info[0]=data[3];
			B_VW_CanAdapterRxInfo.left_radar_info[1]=data[4];
			B_VW_CanAdapterRxInfo.left_radar_info[2]=data[5];
			B_VW_CanAdapterRxInfo.left_radar_info[3]=data[6];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_LEFT_RADAR_INFO);
			break;
		case B_VW_RX_RIGHT_RADAR_INFO:
			B_VW_CanAdapterRxInfo.right_radar_info[0]=data[3];
			B_VW_CanAdapterRxInfo.right_radar_info[1]=data[4];
			B_VW_CanAdapterRxInfo.right_radar_info[2]=data[5];
			B_VW_CanAdapterRxInfo.right_radar_info[3]=data[6];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_RIGHT_RADAR_INFO);
			break;
		default:
			tx_ack=RX_NACK_NO_SUPPORT;
			break;
	}
	B_VW_TxAck(tx_ack);
}

void CanBox_RxAnalyse_B_VW(void)
{
	u16 start=CanFunRxBuffer.head;
	u16 end=CanFunRxBuffer.tail;
	u8 data[B_VW_MAX_CAN_RX_DATA_LENGTH];
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
			if(BNR_CAN_HEAD_CODE==CanFunRxBuffer.data[i])
			{
				if(buffer_data_length>=B_VW_MIN_CAN_RX_DATA_LENGTH)
				{
					packet_length_index=i+2;
					if(packet_length_index>=MAX_CAN_RX_BUFFER_LENGTH)
					{
						packet_length_index-=MAX_CAN_RX_BUFFER_LENGTH;
					}
					packet_length=CanFunRxBuffer.data[packet_length_index]+4;
					
					packet_checksum_index=i+packet_length-1;
					if(packet_checksum_index>=MAX_CAN_RX_BUFFER_LENGTH)
					{
						packet_checksum_index-=MAX_CAN_RX_BUFFER_LENGTH;
					}
					packet_checksum=CanFunRxBuffer.data[packet_checksum_index];
					
					if(packet_length<=B_VW_MAX_CAN_RX_DATA_LENGTH)
					{
						if(buffer_data_length>=packet_length)
						{
							checksum=0;
							packet_counter=i+1;
							for(j=0;j<(packet_length-2);j++)
							{
								checksum+=CanFunRxBuffer.data[packet_counter];
								packet_counter++;
								if(packet_counter>=MAX_CAN_RX_BUFFER_LENGTH)
								{
									packet_counter=0;
								}
							}
							checksum^=0xFF;
							if(packet_checksum==checksum)
							{
								packet_counter=i;
								for(j=0;j<packet_length;j++)
								{
									data[j]=CanFunRxBuffer.data[packet_counter];
									CanFunRxBuffer.data[packet_counter]=0;
									packet_counter++;
									if(packet_counter>=MAX_CAN_RX_BUFFER_LENGTH)
									{
										packet_counter=0;
									}
								}
								CanFunRxBuffer.head=packet_counter;
								CanBox_RxService_B_VW(data);
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
			else if(RX_ACK==CanFunRxBuffer.data[i]
					||RX_NACK_NO_SUPPORT==CanFunRxBuffer.data[i]
					||RX_NACK_ERR_CHECKSUM==CanFunRxBuffer.data[i]
					||RX_NACK_BUSY==CanFunRxBuffer.data[i])
			{
				CanBox_RxAck_B_VW(CanFunRxBuffer.data[i]);
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

void CanBox_TxService_B_VW(void)
{
	u8 i;
	u8 length=0;
	u8 checksum=0;
	MESSAGE*nEvt;	
	u8 temp;	
	
	if(F_CAN_TX_BUFFER_FULL==0)
	{
		nEvt=GetMessage(SUB_CAN_MODULE);
		if(nEvt->ID==NO_EVT)
		{
			return;
		}
		switch(nEvt->ID)
		{
			case B_VW_CMD_SOURCE_OFF_CMD:
				CanFunTxBuffer[0]=0x2E;	
				CanFunTxBuffer[1]=B_VW_TX_SOURCE_INFO;
				CanFunTxBuffer[2]=0x02;
				CanFunTxBuffer[3]=0x00;
				CanFunTxBuffer[4]=0x00;
				length=5;
				break;
			case B_VW_CMD_APP_DATA:
				CanFunTxBuffer[0]=0x2E;	
				CanFunTxBuffer[1]=LSB(nEvt->prm);
				switch(LSB(nEvt->prm))
				{
					case B_VW_TX_REQUEST_CMD:
						temp=MSB(nEvt->prm);
						CanFunTxBuffer[2]=2;
						switch(temp)
						{
							case B_VW_REQ_APP_DATA:
								CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.request_cmd[0];
								CanFunTxBuffer[4]=B_VW_CanAdapterTxInfo.request_cmd[1];
								break;
							case B_VW_REQ_CAR_INFO_1:
							case B_VW_REQ_CAR_INFO_2:
							case B_VW_REQ_CAR_INFO_3:
								CanFunTxBuffer[3]=B_VW_RX_CAR_INFO;
								CanFunTxBuffer[4]=temp;
								break;
							case B_VW_REQ_VERSION:
								CanFunTxBuffer[3]=B_VW_RX_VERSION_INFO;
								CanFunTxBuffer[4]=0x00;	
								break;
							case B_VW_REQ_BASIC_INFO:
								CanFunTxBuffer[3]=B_VW_RX_BASIC_INFO;
								CanFunTxBuffer[4]=0x00;		
								break;
							case B_VW_REQ_EPS_INFO:
								CanFunTxBuffer[3]=B_VW_RX_EPS_INFO;
								CanFunTxBuffer[4]=0x00;									
								break;
							default:
								CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.request_cmd[0];
								CanFunTxBuffer[4]=B_VW_CanAdapterTxInfo.request_cmd[1];
								break;
						}
						break;
					case B_VW_TX_SOURCE_INFO:
						CanFunTxBuffer[2]=2;
						CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.source_info[0];
						CanFunTxBuffer[4]=B_VW_CanAdapterTxInfo.source_info[1];
						break;
					case B_VW_TX_RADIO_INFO:
#if MODEL==LINUX_9289_21
#else
						if(B_VW_CanAdapterTxInfo.source_info[0] == 0x01 && B_VW_CanAdapterTxInfo.source_info[1] == 0x01)
						{
							CanFunTxBuffer[2]=4;
							if(radio_band < BAND_AM1)
							{
								B_VW_CanAdapterTxInfo.radio_info[0] =((~0x10)&radio_band) + 1;
							}
							else
							{
								B_VW_CanAdapterTxInfo.radio_info[0] = (0x10|radio_band) - BAND_FM3;
							}
							B_VW_CanAdapterTxInfo.radio_info[1] = LSB(radio_freq);
							B_VW_CanAdapterTxInfo.radio_info[2] = MSB(radio_freq);
							B_VW_CanAdapterTxInfo.radio_info[3] = radio_curpreset;
							
							CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.radio_info[0];
							CanFunTxBuffer[4]=B_VW_CanAdapterTxInfo.radio_info[1];
							CanFunTxBuffer[5]=B_VW_CanAdapterTxInfo.radio_info[2];
							CanFunTxBuffer[6]=B_VW_CanAdapterTxInfo.radio_info[3];
						}
						else
						{
							CanFunTxBuffer[2]=0;
						}
#endif
						break;
					case B_VW_TX_ICON_INFO:
						CanFunTxBuffer[2]=1;
						CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.icon;
						break;
					case B_VW_TX_MEDIA_INFO:
						CanFunTxBuffer[2]=6;
						for(i=0;i<6;i++)
						{
							CanFunTxBuffer[3+i]=B_VW_CanAdapterTxInfo.media_info[i];
						}
						break;
					case B_VW_TX_VOLUME_INFO:
						CanFunTxBuffer[2]=1;
						CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.volume;
						break;
					case B_VW_TX_SETTING_CMD:
						CanFunTxBuffer[2]=2;
						CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.car_set_cmd[0];
						CanFunTxBuffer[4]=B_VW_CanAdapterTxInfo.car_set_cmd[1];
						break;
					case B_VW_TX_AMP_CMD:
						CanFunTxBuffer[2]=2;
						CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.amp_cmd[0];
						CanFunTxBuffer[4]=B_VW_CanAdapterTxInfo.amp_cmd[1];
						break;
					case B_VW_TX_AIR_CMD:
						CanFunTxBuffer[2]=2;
						CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.air_cmd[0];
						CanFunTxBuffer[4]=B_VW_CanAdapterTxInfo.air_cmd[1];						
						break;
					case B_VW_TX_DASHBOARD_CMD:
						CanFunTxBuffer[2]=B_VW_CanAdapterTxInfo.dashboard_info_length[MSB(nEvt->prm)];
						for(i=0;i<B_VW_CanAdapterTxInfo.dashboard_info_length[MSB(nEvt->prm)];i++)
						{
							CanFunTxBuffer[3+i]=B_VW_CanAdapterTxInfo.dashboard_info[MSB(nEvt->prm)][i];
						}
						break;
					case B_VW_TX_ENGINE_TIME_CMD:	
						CanFunTxBuffer[2]=1;
						CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.engine_time_cmd;						
						break;
					case B_VW_TX_SPEED_TIME_CMD:
						CanFunTxBuffer[2]=1;
						CanFunTxBuffer[3]=B_VW_CanAdapterTxInfo.speed_time_cmd;	
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
			case B_VW_CMD_AMP_CMD:
				CanFunTxBuffer[0]=0x2E;	
				CanFunTxBuffer[1]=B_VW_TX_AMP_CMD;
				CanFunTxBuffer[2]=2;
				CanFunTxBuffer[3]=MSB(nEvt->prm);
				CanFunTxBuffer[4]=LSB(nEvt->prm);	
				length=5;
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

void CanBox_MainPro_B_VW(void)
{
	CanBox_MainEvtPro_B_VW();
	CanBox_RxAnalyse_B_VW();
	
	if(CanBoxWorkTimer)
	{
		CanBoxWorkTimer--;
	}
	switch(CanBoxWorkState)
	{
		case B_VW_IDLE:
			break;
		case B_VW_TX_START_COMMAND:
			if(CanBoxWorkTimer)
			{
				break;
			}
			CanBox_Initial();
			B_VW_TxStartEndCmd(1);
			CanBoxWorkState=B_VW_WAIT_START_ACK;
			CanBoxWorkTimer=T300MS_10;
			B_VW_AmpResetTimer=T3S_10;
			break;
		case B_VW_WAIT_START_ACK:
			if(CanBoxWorkTimer==0)
			{
				CanBoxWorkState=B_VW_TX_START_COMMAND;
			}
			break;
		case B_VW_WORK_NORMAL:
			if(OS_WorkState==OS_WORK_NORMAL)
			{				
				B_VW_RequestTimer++;
				if(Get_Reverse_Det_Flag==0)
				{
					if(B_VW_RequestTimer>=100)
					{
						B_VW_RequestTimer=0;
						B_VW_RequestIndex++;
						if(B_VW_RequestIndex==B_VW_REQ_APP_DATA||B_VW_RequestIndex>=B_VW_REQ_EPS_INFO)
						{
							B_VW_RequestIndex=B_VW_REQ_CAR_INFO_1;
						}
						PostMessage(SUB_CAN_MODULE,B_VW_CMD_APP_DATA,WORD(B_VW_RequestIndex,B_VW_TX_REQUEST_CMD));
					}
				}
				else
				{
					if(B_VW_RequestTimer>=20)
					{
						B_VW_RequestTimer=0;
						B_VW_RequestIndex=B_VW_REQ_CAR_INFO_1;
						PostMessage(SUB_CAN_MODULE,B_VW_CMD_APP_DATA,WORD(B_VW_REQ_EPS_INFO,B_VW_TX_REQUEST_CMD));
					}
				}
				if(B_VW_AmpResetTimer)
				{
					B_VW_AmpResetTimer--;
					if(0==B_VW_AmpResetTimer)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,B_VW_RX_AMP_RESET_INFO);
					}
				}
				if(B_VW_TxEpsTimer)
				{
					B_VW_TxEpsTimer--;
				}
			}			
			CanBox_Refreash((u8 *)B_VW_RefreashTab,sizeof(B_VW_RefreashTab));
			CanBox_TxService_B_VW();
			break;
		case B_VW_TX_SOURCE_OFF:
			B_VW_TxSourceOffCmd();
			CanBoxWorkState=B_VW_WAIT_SOURCE_OFF_ACK;
			CanBoxWorkTimer=T300MS_10;			
			break;
		case B_VW_WAIT_SOURCE_OFF_ACK:
			if(CanBoxWorkTimer==0)
			{
				CanBoxWorkState=B_VW_TX_SOURCE_OFF;
			}
			break;
		case B_VW_TX_END_COMMAND:
			B_VW_TxStartEndCmd(0);
			CanBoxWorkState=B_VW_WAIT_END_ACK;
			CanBoxWorkTimer=T300MS_10;
			break;
		case B_VW_WAIT_END_ACK:
			if(CanBoxWorkTimer==0)
			{
				CanBoxWorkState=B_VW_TX_END_COMMAND;
			}
			break;
		case B_VW_POWER_OFF:
			CanBoxWorkState=B_VW_IDLE;
			break;
		default:
			break;
	}
}

void B_VW_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	u8 *ptr;
	u8 length=0;
	u8 i;
	u8 temp = 0;

	cmd_id=buffer[1];
	switch(cmd_id)
	{
		case B_VW_TX_REQUEST_CMD:
			ptr=&B_VW_CanAdapterTxInfo.request_cmd[0];
			length=2;
			break;
		case B_VW_TX_SOURCE_INFO:
			ptr=&B_VW_CanAdapterTxInfo.source_info[0];
			length=2;
			break;
		case B_VW_TX_ICON_INFO:
			ptr=&B_VW_CanAdapterTxInfo.icon;
			length=1;			
			break;
//		case B_VW_TX_RADIO_INFO:
//			ptr=&B_VW_CanAdapterTxInfo.radio_info[0];
//			length=4;
//			break;
		case B_VW_TX_MEDIA_INFO:
			ptr=&B_VW_CanAdapterTxInfo.media_info[0];
			length=6;
			break;
		case B_VW_TX_VOLUME_INFO:
			ptr=&B_VW_CanAdapterTxInfo.volume;
			length=1;
			break;
		case B_VW_TX_SETTING_CMD:
			ptr=&B_VW_CanAdapterTxInfo.car_set_cmd[0];
			length=2;			
			break;
		case B_VW_TX_AMP_CMD:
			PostMessage(SUB_CAN_MODULE,B_VW_CMD_AMP_CMD,WORD(buffer[3],buffer[4]));	
			break;
		case B_VW_TX_AIR_CMD:
			ptr=&B_VW_CanAdapterTxInfo.air_cmd[0];
			length=2;			
			break;
		case B_VW_TX_DASHBOARD_CMD:
			temp = buffer[4]&0x0F;
			ptr=&B_VW_CanAdapterTxInfo.dashboard_info[temp][0];
			length=buffer[2];
			if(length>B_VW_DASHBOARD_LENGTH)
			{
				length=B_VW_DASHBOARD_LENGTH;
			}
			B_VW_CanAdapterTxInfo.dashboard_info_length[temp]=length;
			break;
		case B_VW_TX_ENGINE_TIME_CMD:	
			ptr=&B_VW_CanAdapterTxInfo.engine_time_cmd;
			length=1;
			break;
		case B_VW_TX_SPEED_TIME_CMD:
			ptr=&B_VW_CanAdapterTxInfo.speed_time_cmd;
			length=1;			
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
		PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,WORD(temp,cmd_id));
		if(cmd_id == B_VW_TX_SOURCE_INFO)
		{
			if((B_VW_CanAdapterTxInfo.source_info[0] == 0x01)&&(B_VW_CanAdapterTxInfo.source_info[1] == 0x01))
			{
					PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,B_VW_TX_RADIO_INFO);
			}
		}
	}
}

void B_VW_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 *ptr;
	u8 counter;
	u8 i;
	u8 temp[2];
	u8 checksum;
	
	buffer[0]= BNR_CAN_HEAD_CODE;
	buffer[1]=cmd_id;
	switch(cmd_id)
	{
		case B_VW_RX_REQUEST_INFO:
			ptr=&B_VW_CanAdapterRxInfo.request_info;
			*length=2;	
			break;
		case B_VW_RX_SPEED_INFO:
			ptr=&B_VW_CanAdapterRxInfo.speed[0];
			*length=3;
			break;
		case B_VW_RX_AIR_INFO:
			ptr=&B_VW_CanAdapterRxInfo.air_info[0];
			*length=6;			
			break;
		case B_VW_RX_REAR_RADAR_INFO:
			ptr=&B_VW_CanAdapterRxInfo.rear_radar_info[0];
			*length=5;					
			break;
		case B_VW_RX_FRONT_RADAR_INFO:
			ptr=&B_VW_CanAdapterRxInfo.front_radar_info[0];
			*length=5;	
			break;
		case B_VW_RX_BASIC_INFO:
			ptr=&B_VW_CanAdapterRxInfo.basic_info[0];
			*length=3;	
			break;
		case B_VW_RX_PARKING_INFO:
			ptr=&B_VW_CanAdapterRxInfo.parking_info[0];
			*length=3;
			break;
		case B_VW_RX_EPS_INFO:
			ptr=&B_VW_CanAdapterRxInfo.eps_info[0];
			*length=3;
			break;
		case B_VW_RX_AMP_INFO:
			ptr=&B_VW_CanAdapterRxInfo.amp_info[0];
			*length=9;
			break;
		case B_VW_RX_VERSION_INFO:
			ptr=&B_VW_CanAdapterRxInfo.version_info[0];
			*length=17;
			break;
		case B_VW_RX_CAR_INFO:
			ptr=&B_VW_CanAdapterRxInfo.car_info[0];
			if(B_VW_CanAdapterRxInfo.car_info[0]==0x02)
			{
				*length=14;
			}
			else if(B_VW_CanAdapterRxInfo.car_info[0]==0x01)
			{
				*length=4;
			}
			else
			{
				*length=3;
			}
			break;
		case B_VW_RX_TURN_SIGNAL_LAMP:
			ptr=&B_VW_CanAdapterRxInfo.turn_signal_lamp_info;
			*length=2;	
			break;
		case B_VW_RX_UPDATE_INFO:
			ptr=&B_VW_CanAdapterRxInfo.update_info;
			*length=2;				
			break;
		case B_VW_RX_SCREEN_TYPE:
			ptr=&B_VW_CanAdapterRxInfo.screen_type;
			*length=2;				
			break;
		case B_VW_RX_LEFT_RADAR_INFO:
			ptr=&B_VW_CanAdapterRxInfo.left_radar_info[0];
			*length=5;	
			break;
		case B_VW_RX_RIGHT_RADAR_INFO:
			ptr=&B_VW_CanAdapterRxInfo.right_radar_info[0];
			*length=5;	
			break;
		case B_VW_RX_AMP_RESET_INFO:
			temp[0]=0;
			temp[1]=0;
			ptr=temp;
			*length=3;
			break;
		default:
			*length=0;
			break;
	}
	if(*length>=1)
	{		
		counter=*length-1;
		buffer[2] = counter;
		checksum = buffer[1] + buffer[2];
		for(i=0;i<counter;i++)
		{
			buffer[i+3]=ptr[i];
			checksum += ptr[i];
		}
	}
	*length += 3;
	buffer[i+3] = checksum^0xFF;
}
#endif



