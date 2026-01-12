#include "public.h"

#if AHD_360_FUN==1

AHD_360_RX_INFO AHD_360_RxInfo;
AHD_360_TX_INFO AHD_360_TxInfo;
AHD_360_FLAG AHD_360_Flag;
AHD_360_RX_BUFFER AHD_360_RxBuffer;
AHD_360_WORK_STATE AHD_360_WorkState;
u16 AHD_360_WorkTimer;
u16 AHD_360_ResendCounter;
u16 AHD_360_ResendTimer;
u8 AHD_360_TxBuffer[MAX_AHD_360_TX_BUFFER_LENGTH];
u8 AHD_360_TxLength;

void AHD_360_TxLinkCmd(u8 start_end)
{
	AHD_360_TxBuffer[0]=AHD_360_HEAD_CODE;						
	AHD_360_TxBuffer[1]=AHD_360_TX_LINK_CMD;	
	AHD_360_TxBuffer[2]=0x01;						
	if(0x01==start_end)
	{
		AHD_360_TxBuffer[3]=0x01;					
	}
	else
	{
		AHD_360_TxBuffer[3]=0x00;					
	}									
	AHD_360_TxBuffer[4]=(AHD_360_TxBuffer[1]+AHD_360_TxBuffer[2]+AHD_360_TxBuffer[3])^0xFF;

#if defined(AUTOCHIPS_AC781X)
	UART6_SendData(AHD_360_TxBuffer,5);
#elif defined(HDSC_HC32F460)
	UART4_SendData(AHD_360_TxBuffer,5);
#elif defined(HDSC_HC32L072)
	UART0_SendData(AHD_360_TxBuffer,5);
#elif defined(STM32_F103VC)
	UART3_SendData(AHD_360_TxBuffer,5);
#endif
}

void AHD_360_TxAck(u8 ack)
{
	u8 tx_ack;

	tx_ack=ack;
		
#if defined(AUTOCHIPS_AC781X)
	UART6_SendData(&tx_ack,1);
#elif defined(HDSC_HC32F460)
	UART4_SendData(&tx_ack,1);
#elif defined(HDSC_HC32L072)
	UART0_SendData(&tx_ack,1);
#elif defined(STM32_F103VC)
	UART3_SendData(&tx_ack,1);
#endif
}

void AHD_360_StartFrame(void)
{
	AHD_360_ResendCounter=0;
	AHD_360_ResendTimer=0;
	F_AHD_360_TX_BUFFER_FULL=1;
	F_AHD_360_TX_ACK_CHECK=1;
	
#if defined(AUTOCHIPS_AC781X)
	UART6_SendData(AHD_360_TxBuffer,AHD_360_TxLength);
#elif defined(HDSC_HC32F460)
	UART4_SendData(AHD_360_TxBuffer,AHD_360_TxLength);
#elif defined(HDSC_HC32L072)
	UART0_SendData(AHD_360_TxBuffer,AHD_360_TxLength);
#elif defined(STM32_F103VC)
	UART3_SendData(AHD_360_TxBuffer,AHD_360_TxLength);
#endif
}

void AHD_360_TxFarmat(u8 *pbuf, u8 length)
{
#if defined(AUTOCHIPS_AC781X)
	UART6_SendData(pbuf,length);
#elif defined(HDSC_HC32F460)
	UART4_SendData(pbuf,length);
#elif defined(HDSC_HC32L072)
	UART0_SendData(pbuf,length);
#elif defined(STM32_F103VC)
	UART3_SendData(pbuf,length);
#endif
}

void AHD_360_RxAck(u8 rx_ack)
{
	switch(rx_ack)
	{
		case AHD_360_RX_ACK:
			F_AHD_360_TX_BUFFER_FULL=0;
			F_AHD_360_TX_ACK_CHECK=0;
			if(AHD_360_WAIT_START_ACK==AHD_360_WorkState)
			{
				AHD_360_WorkState=AHD_360_WORK_NORMAL;
			}
			else if(AHD_360_WAIT_END_ACK==AHD_360_WorkState)
			{
				AHD_360_WorkState=AHD_360_POWER_OFF;
			}
			break;
		case AHD_360_RX_NACK_NO_SUPPORT:
			F_AHD_360_TX_BUFFER_FULL=0;
			F_AHD_360_TX_ACK_CHECK=0;
			break;
		case AHD_360_RX_NACK_ERR_CHECKSUM:
		case AHD_360_RX_NACK_BUSY:
			F_AHD_360_TX_ACK_CHECK=1;
			break;
		default:
			break;
	}
}

void AHD_360_RxService(u8 *data)
{
	u8 tx_ack;
	u8 data_type;
	u32 i;
	
	data_type=data[1];
	tx_ack=AHD_360_RX_ACK;
	switch(data_type)
	{
		case AHD_360_RX_INIT_INFO:
			AHD_360_RxInfo.init_info=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_AHD_360_INFO,AHD_360_RX_INIT_INFO);	
			break;
		case AHD_360_RX_VERSION_INFO:
			for(i=0;i<AHD_360_VERSION_LENGTH;i++)
			{
				AHD_360_RxInfo.version_info[i]=data[3+i];
			}
			PostMessage(NAVI_MODULE,MCU_TX_AHD_360_INFO,AHD_360_RX_VERSION_INFO);	
			break;
		case AHD_360_RX_STATE_INFO:
			AHD_360_RxInfo.view_state=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_AHD_360_INFO,AHD_360_RX_STATE_INFO);	
			break;
		case AHD_360_RX_MENU_INFO:
			AHD_360_RxInfo.menu_state=data[3];
			PostMessage(NAVI_MODULE,MCU_TX_AHD_360_INFO,AHD_360_RX_MENU_INFO);
			break;
		default:
			tx_ack=AHD_360_RX_NACK_NO_SUPPORT;
			break;
	}
	AHD_360_TxAck(tx_ack);
}

void AHD_360_RxAnalyse(void)
{
	u16 start=AHD_360_RxBuffer.head;
	u16 end=AHD_360_RxBuffer.tail;
	u8 data[AHD_360_MAX_RX_DATA_LENGTH];
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
			buffer_data_length=MAX_AHD_360_RX_BUFFER_LENGTH-i+end;
		}		

		if(buffer_data_length)
		{
			if(AHD_360_HEAD_CODE==AHD_360_RxBuffer.data[i])
			{
				if(buffer_data_length>=AHD_360_MIN_RX_DATA_LENGTH)
				{
					packet_length_index=i+2;
					if(packet_length_index>=MAX_AHD_360_RX_BUFFER_LENGTH)
					{
						packet_length_index-=MAX_AHD_360_RX_BUFFER_LENGTH;
					}
					packet_length=AHD_360_RxBuffer.data[packet_length_index]+4;			//s数据包长度
					
					packet_checksum_index=i+packet_length-1;							//
					if(packet_checksum_index>=MAX_AHD_360_RX_BUFFER_LENGTH)
					{
						packet_checksum_index-=MAX_AHD_360_RX_BUFFER_LENGTH;
					}
					packet_checksum=AHD_360_RxBuffer.data[packet_checksum_index];			//校验和
					
					if(packet_length<=AHD_360_MAX_RX_DATA_LENGTH)							//最大接收到的长度
					{
						if(buffer_data_length>=packet_length)							//缓冲区内至少有一包数据
						{
							checksum=0;
							packet_counter=i+1;
							for(j=0;j<(packet_length-2);j++)							//累加数据和
							{
								checksum+=AHD_360_RxBuffer.data[packet_counter];
								packet_counter++;
								if(packet_counter>=MAX_AHD_360_RX_BUFFER_LENGTH)
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
									data[j]=AHD_360_RxBuffer.data[packet_counter];		//将数据存入data中
									AHD_360_RxBuffer.data[packet_counter]=0;
									packet_counter++;
									if(packet_counter>=MAX_AHD_360_RX_BUFFER_LENGTH)
									{
										packet_counter=0;
									}
								}
								AHD_360_RxBuffer.head=packet_counter;
								AHD_360_RxService(data);
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
			else if(AHD_360_RX_ACK==AHD_360_RxBuffer.data[i]
					||AHD_360_RX_NACK_NO_SUPPORT==AHD_360_RxBuffer.data[i]
					||AHD_360_RX_NACK_ERR_CHECKSUM==AHD_360_RxBuffer.data[i]
					||AHD_360_RX_NACK_BUSY==AHD_360_RxBuffer.data[i])
			{
				AHD_360_RxAck(AHD_360_RxBuffer.data[i]);
			}
		}
		else
		{
			break;
		}
		i++;
		if(i>=MAX_AHD_360_RX_BUFFER_LENGTH)
		{
			i=0;
		}
		AHD_360_RxBuffer.head=i;
	}	
}

void AHD_360_TxService(void)
{
	u8 i;
	u8 length=0;
	u8 checksum=0;
	MESSAGE*nEvt;	

	if(F_AHD_360_TX_BUFFER_FULL==0)
	{
		nEvt=GetMessage(SUB_AHD_360_MODULE);
		if(nEvt->ID==NO_EVT)
		{
			return;
		}
		
		switch(nEvt->ID)
		{
			case AHD_360_CMD_APP_DATA:
				AHD_360_TxBuffer[0]=AHD_360_HEAD_CODE;	
				switch(LSB(nEvt->prm))
				{
					case AHD_360_TX_REQUEST_CMD:
						AHD_360_TxBuffer[1]=AHD_360_TX_REQUEST_CMD;
						AHD_360_TxBuffer[2]=0x01;
						AHD_360_TxBuffer[3]=AHD_360_TxInfo.request_info;
						break;
					case AHD_360_TX_VIEW_SET_CMD:
						AHD_360_TxBuffer[1]=AHD_360_TX_VIEW_SET_CMD;
						AHD_360_TxBuffer[2]=0x01;
						AHD_360_TxBuffer[3]=AHD_360_TxInfo.view_set_cmd;						
						break;
					case AHD_360_TX_MENU_SET_CMD:
						AHD_360_TxBuffer[1]=AHD_360_TX_MENU_SET_CMD;
						AHD_360_TxBuffer[2]=0x01;
						AHD_360_TxBuffer[3]=AHD_360_TxInfo.menu_set_cmd;	
						break;
					case AHD_360_TX_TOUCH_PRESS_CMD:
						AHD_360_TxBuffer[1]=AHD_360_TX_TOUCH_CMD;
						AHD_360_TxBuffer[2]=0x03;
						AHD_360_TxBuffer[3]=AHD_360_TxInfo.touch_press_cmd[0];	
						AHD_360_TxBuffer[4]=AHD_360_TxInfo.touch_press_cmd[1];	
						AHD_360_TxBuffer[5]=AHD_360_TxInfo.touch_press_cmd[2];	
						break;
					case AHD_360_TX_TOUCH_RELEASE_CMD:
						AHD_360_TxBuffer[1]=AHD_360_TX_TOUCH_CMD;
						AHD_360_TxBuffer[2]=0x03;
						AHD_360_TxBuffer[3]=AHD_360_TxInfo.touch_release_cmd[0];	
						AHD_360_TxBuffer[4]=AHD_360_TxInfo.touch_release_cmd[1];	
						AHD_360_TxBuffer[5]=AHD_360_TxInfo.touch_release_cmd[2];	
						break;
					case AHD_360_TX_REVERSE_STATE:
						AHD_360_TxBuffer[1]=AHD_360_TX_REVERSE_STATE;
						AHD_360_TxBuffer[2]=0x01;
						AHD_360_TxBuffer[3]=AHD_360_TxInfo.reverse_state;
						break;
					case AHD_360_TX_LIGHT_STATE:
						AHD_360_TxBuffer[1]=AHD_360_TX_LIGHT_STATE;
						AHD_360_TxBuffer[2]=0x01;
						AHD_360_TxBuffer[3]=AHD_360_TxInfo.light_state;						
						break;
					default:
						AHD_360_TxBuffer[2]=0;
						break;
				}
				length=AHD_360_TxBuffer[2]+3;
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
				checksum+=AHD_360_TxBuffer[i];
			}
			checksum^=0xFF;
			AHD_360_TxBuffer[length]=checksum;
			AHD_360_TxLength=length+1;
			AHD_360_StartFrame();      
		}
	}
}

void AHD_360_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;

	cmd_id=buffer[1];
	switch(cmd_id)
	{
		case AHD_360_TX_REQUEST_CMD:
			AHD_360_TxInfo.request_info=buffer[3];
			PostMessage(MAIN_AHD_360_MODULE,AHD_360_EVENT_RX_APP_DATA,AHD_360_TX_REQUEST_CMD);
			break;
		case AHD_360_TX_VIEW_SET_CMD:
			AHD_360_TxInfo.view_set_cmd=buffer[3];
			PostMessage(MAIN_AHD_360_MODULE,AHD_360_EVENT_RX_APP_DATA,AHD_360_TX_VIEW_SET_CMD);
			break;
		case AHD_360_TX_MENU_SET_CMD:
			AHD_360_TxInfo.menu_set_cmd=buffer[3];	
			PostMessage(MAIN_AHD_360_MODULE,AHD_360_EVENT_RX_APP_DATA,AHD_360_TX_MENU_SET_CMD);
			break;
		case AHD_360_TX_TOUCH_CMD:
			if(buffer[5])
			{
				AHD_360_TxInfo.touch_press_cmd[0]=buffer[3];
				AHD_360_TxInfo.touch_press_cmd[1]=buffer[4];
				AHD_360_TxInfo.touch_press_cmd[2]=buffer[5];
				PostMessage(MAIN_AHD_360_MODULE,AHD_360_EVENT_RX_APP_DATA,AHD_360_TX_TOUCH_PRESS_CMD);
			}
			else
			{
				AHD_360_TxInfo.touch_release_cmd[0]=buffer[3];
				AHD_360_TxInfo.touch_release_cmd[1]=buffer[4];
				AHD_360_TxInfo.touch_release_cmd[2]=buffer[5];
				PostMessage(MAIN_AHD_360_MODULE,AHD_360_EVENT_RX_APP_DATA,AHD_360_TX_TOUCH_RELEASE_CMD);
			}		
			break;
		case AHD_360_TX_REVERSE_STATE:
			AHD_360_TxInfo.reverse_state=buffer[3];	
			PostMessage(MAIN_AHD_360_MODULE,AHD_360_EVENT_RX_APP_DATA,AHD_360_TX_REVERSE_STATE);
			break;
		case AHD_360_TX_LIGHT_STATE:
			AHD_360_TxInfo.light_state=buffer[3];	
			PostMessage(MAIN_AHD_360_MODULE,AHD_360_EVENT_RX_APP_DATA,AHD_360_TX_LIGHT_STATE);
			break;
		default:	
			break;
	}
}

void AHD_360_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 *ptr;
	u8 counter;
	u8 i;
	u8 checksum;
	
	buffer[0]=AHD_360_HEAD_CODE;
	buffer[1]=cmd_id;
	switch(cmd_id)
	{
		case AHD_360_RX_INIT_INFO:	
			ptr=&AHD_360_RxInfo.init_info;
			*length=1;
			break;
		case AHD_360_RX_VERSION_INFO:	
			ptr=&AHD_360_RxInfo.version_info[0];
			*length=AHD_360_VERSION_LENGTH;
			break;
		case AHD_360_RX_STATE_INFO:
			ptr=&AHD_360_RxInfo.view_state;
			*length=1;
			break;
		case AHD_360_RX_MENU_INFO:
			ptr=&AHD_360_RxInfo.menu_state;
			*length=1;
			break;
		default:
			*length=0;
			break;
	}
	if(*length>=1)
	{	
		buffer[2]=*length;
		checksum=buffer[1]+buffer[2];
		counter=*length-1;
		for(i=0;i<=counter;i++)
		{
			buffer[i+3]=ptr[i];		
			checksum+=buffer[i+3];
		}
		buffer[i+3]=(~checksum)^0xFF;
		*length+=4;
	}	
}

void AHD_360_ResendPro(void)	
{
	if(F_AHD_360_TX_ACK_CHECK)
	{
		AHD_360_ResendTimer++;
		if(AHD_360_ResendTimer==T100MS_10)
		{
			AHD_360_ResendTimer=0;
			AHD_360_ResendCounter++;
			if(AHD_360_ResendCounter>AHD_360_RESEND_TIMES)
			{
				AHD_360_ResendCounter=0;
				F_AHD_360_TX_ACK_CHECK=0;
				F_AHD_360_TX_BUFFER_FULL=0;
			}
			else
			{	
                		AHD_360_TxFarmat(AHD_360_TxBuffer,AHD_360_TxLength);
			}
		}
	}
}

void AHD_360_Initial(void)
{
	AHD_360_Flag.byte=0;
	ClearMessage(SUB_AHD_360_MODULE);
}

void AHD_360_MainEventPro(void)
{
       MESSAGE*nEvt;	
	
	nEvt=GetMessage(MAIN_AHD_360_MODULE);
	if(nEvt->ID==AHD_360_EVENT_NONE)
	{
		return;
	}
	switch(nEvt->ID)
	{
		case AHD_360_EVENT_POWER_ON:
			AHD_360_WorkTimer=T300MS_10;
			AHD_360_WorkState=AHD_360_TX_START_COMMAND;
			break;
		case AHD_360_EVENT_POWER_OFF:
			break;
		case AHD_360_EVENT_ACC_OFF:
			AHD_360_WorkState=AHD_360_TX_END_COMMAND;
			break;
		case AHD_360_EVENT_EMERGENCY_OFF:
			AHD_360_WorkState=AHD_360_POWER_OFF;
			break;
		case AHD_360_EVENT_RX_APP_DATA:
			if(nPowerState==POWER_NORMAL_RUN)
			{
				PostMessage(SUB_AHD_360_MODULE,AHD_360_CMD_APP_DATA,nEvt->prm);
			}
			break;
		default:
			break;
	}
}

void AHD_360_MainPro(void)
{
	AHD_360_MainEventPro();
	AHD_360_RxAnalyse();
	
	if(AHD_360_WorkTimer)
	{
		AHD_360_WorkTimer--;
	}
	
	switch(AHD_360_WorkState)
	{
		case AHD_360_IDLE:
			break;
		case AHD_360_TX_START_COMMAND:
			if(AHD_360_WorkTimer)
			{
				break;
			}
			AHD_360_Initial();
			AHD_360_TxLinkCmd(0x01);
			AHD_360_WorkState=AHD_360_WAIT_START_ACK;
			AHD_360_WorkTimer=T300MS_10;
			break;
		case AHD_360_WAIT_START_ACK:
			if(AHD_360_WorkTimer==0)
			{
				AHD_360_WorkState=AHD_360_TX_START_COMMAND;
			}
			break;
		case AHD_360_WORK_NORMAL:
			AHD_360_TxService();
			AHD_360_ResendPro();
			break;
		case AHD_360_TX_END_COMMAND:
			AHD_360_TxLinkCmd(0);
			AHD_360_WorkState=AHD_360_WAIT_END_ACK;
			AHD_360_WorkTimer=T300MS_10;
			break;
		case AHD_360_WAIT_END_ACK:
			if(AHD_360_WorkTimer==0)
			{
				AHD_360_WorkState=AHD_360_TX_END_COMMAND;
			}
			break;
		case AHD_360_POWER_OFF:
			AHD_360_WorkState=AHD_360_IDLE;
			break;
		default:
			break;
	}
}
#endif

