#include "public.h"
#if CANBOX_UPDATE_FUN_GOLF==1
CANBOX_UPDATE_STATE CanBoxUpdateState;
CAN_UPDATE_FLAG CanUpdateFlag;
u16 CanUpdateChecksum;
u16 CanUpdateDataIndex;
u16 CanUpdateTimeout;
u8 CanUpdateTimer;


u8 IsReqCanUpdate(void)
{
	return(CanUpdateFlag.field.F_req_can_update);
}

void CanUpdateStart(void)
{
	CanUpdateFlag.field.F_req_can_update=1;
	CanBoxUpdateState=CANBOX_UPDATE_READY;
}

void CanUpdate_TxCanData(u8 *buff,u8 length)
{
	u8 i;
	
	if(length<=MAX_CAN_TX_BUFFER_LENGTH)
	{	
		for(i=0;i<length;i++)
		{
			CanFunTxBuffer[i]=buff[i];
		}
		CanFunTxLength=length;
		CanBox_StartFrame();
	}
}

void CanUpdate_TxCanCMD(CAN_UPDATE_TX_CMD comID_sub)
{
	u8 data[6];

	data[0] = SOF1;
	data[1] = SOF2;
	data[2] = 0x01;
	data[3] = 0x01;
	data[4] = comID_sub;
	data[5]=(data[2]+data[3]+data[4]-1)&0xFF;

	CanUpdate_TxCanData(data,data[2]+5);	
}

void CanUpdate_TxEnterIap(void)
{
	CanFunTxBuffer[0]=R_GOLF_A_CAN_HEAD_CODE;
	CanFunTxBuffer[1]=CAN_UPDATE_TX_REQ_ENTER_IAP;
	CanFunTxBuffer[2]=2;
	CanFunTxBuffer[3]=0;
	CanFunTxBuffer[4]=0;
	CanFunTxBuffer[5]=(CAN_UPDATE_TX_REQ_ENTER_IAP+2)^0xFF;
	CanFunTxLength=6;
	CanBox_StartFrame();
}

void CanUpdate_TxCanIndexData(u8 *buffer,u8 length)
{
	u8 data[MAX_CAN_TX_BUFFER_LENGTH];
	u8 i;
	u8 can_tx_checksum;

	data[0] = SOF1;
	data[1] = SOF2;
	data[2] = length+1;
	data[3] = 0x01;
	data[4] = CAN_UPDATE_TX_DATA;
	can_tx_checksum =data[2]+data[3]+ data[4];
	for (i = 0; i < length; i++)
	{
		data[i+5] = buffer[i];
		can_tx_checksum += data[i+5];
	}
	can_tx_checksum=(can_tx_checksum-1)&0xFF;
	data[i+5] = can_tx_checksum;
	CanUpdate_TxCanData(data,data[2]+5);	
}

void CanUpdate_TxCanChecksum(u16 checksum)
{
	u8 data[8];
	u8 can_tx_checksum;

	data[0] = SOF1;
	data[1] = SOF2;
	data[2] = 0x03;
	data[3] = 0x01;
	data[4] = CAN_UPDATE_TX_CHECKSUM;
	data[5] = MSB(checksum);
	data[6] = LSB(checksum);
	can_tx_checksum =data[2]+data[3]+data[4]+data[5]+data[6];
	can_tx_checksum=(can_tx_checksum-1)&0xFF;
	data[7] = can_tx_checksum;
	CanUpdate_TxCanData(data,8);	
}

void CanUpdate_AppDataService(u8 *rx_buff)
{
	u8 sub_id;
	u8 *data;
	u8 type;
	u16 temp;
	
	Uart_Rx_Seq_Num=rx_buff[2]; 
	type=rx_buff[3];
	sub_id=rx_buff[6]; 
	data=&rx_buff[7]; 
	if(type<MCU_TXRX_NACK_NG)
	{   
		Mcu_Ack_Tx(MCU_TXRX_ACK);
	}
	
	switch(type)
	{
		case MCU_RX_CAN_UPDATE_INFO:
			switch(sub_id)
			{
				case APP_REQ_ENTER_CAN_UPDATE:
					PostMessage(NAVI_MODULE, MCU_NOTIFY_READY,0);
					break;
				case APP_SEND_CAN_UPDATE_DATA:
					temp=data[0];
					temp<<=8;
					temp|=data[1];
					if(temp==CanUpdateDataIndex)
					{
						CanUpdate_TxCanIndexData(data,130);
					}
					break;
				case APP_SEND_CAN_UPDATE_CHECK:
					if(CANBOX_UPDATE_HANDLING==CanBoxUpdateState)
					{
						CanUpdateChecksum=data[0];
						CanUpdateChecksum<<=8;
						CanUpdateChecksum|=data[1];
						CanUpdate_TxCanChecksum(CanUpdateChecksum);
						CanBoxUpdateState = CANBOX_UPDATE_WAIT_END;
						CanUpdateTimer=T500MS_100;
					}
					break;			
				case APP_SEND_CAN_UPDATE_RESET:
					if(CANBOX_UPDATE_END==CanBoxUpdateState)
					{
						CanBoxUpdateState=CANBOX_UPDATE_RESET;
					}
					break;
				default:
					break;
			}
			break;
		case MCU_TXRX_ACK:
			APP_Ack_Check();
			break;
		default:
			break;
	}
}

void CanUpdate_TxAppDataPro(void)
{
	MESSAGE*nEvt;	
	nEvt=GetMessage(NAVI_MODULE);
	
	if(nEvt->ID==NO_EVT)
	{
		return;
	}
	
	switch(nEvt->ID)
	{
		case MCU_NOTIFY_READY:
			McuTxBuffer[4]=10;
			McuTxBuffer[6]=2;
			McuTxBuffer[8]=MCU_NOTIFY_READY;
			McuTxBuffer[9]=0xAA;
			break;
		case MCU_SEND_REQUEST_CMD:
			McuTxBuffer[4]=12;
			McuTxBuffer[6]=4;
			McuTxBuffer[8]=MCU_SEND_REQUEST_CMD;
			McuTxBuffer[9]=MSB(CanUpdateDataIndex);
			McuTxBuffer[10]=LSB(CanUpdateDataIndex);
			McuTxBuffer[11]=0xAA;
			break;
		case MCU_NOTIFY_UPDATE_OK:
			McuTxBuffer[4]=10;
			McuTxBuffer[6]=2;
			McuTxBuffer[8]=MCU_NOTIFY_UPDATE_OK;
			McuTxBuffer[9]=0xAA;
			break;
		default:
			McuTxBuffer[4]=0;
			break;
	}

	if(McuTxBuffer[4])
	{
		Uart_Tx_Seq_Num++;
		Data_Length_IN_Buffer=McuTxBuffer[4];
		
		McuTxBuffer[0]=HEAD_ADDRESS_MCU;
		McuTxBuffer[1]=HEAD_ADDRESS_APP;
		McuTxBuffer[2]=Uart_Tx_Seq_Num;
		McuTxBuffer[3]=0;
		McuTxBuffer[5]=0;
		McuTxBuffer[7]=MCU_TX_CAN_UPDATE_INFO;	
		SetPacket(); 	
		F_UART_TX_BUFF_FULL=1;
		Usart_TxStart();	
	}	
}

void CanUpdate_Tx_Ack(u8 ackchar)
{
	u8 buf[6];
	u8 i;
	u8 checksum=0;	

	buf[0]=SOF1;
	buf[1]=SOF2;
	buf[2]=0x01;
	buf[3]=ackchar;
	buf[4]=0x00;
	for(i=2;i < buf[2]+4; i++)
	{
		checksum+=buf[i]; 
	}
	checksum=(checksum-1)&0xFF;
	buf[5]=checksum;
	CanUpdate_TxCanData(buf,6); 
}

void CanUpdate_RxCanDataPro(u8 *data)
{
	u8 nGRoupID,sub_id;

	nGRoupID = data[1]; 
	sub_id = data[2];

	if (nGRoupID == 0x02)
	{
		//CanUpdate_Tx_Ack(MCU_TXRX_ACK);
	}
	
	if (nGRoupID == 0x02&&sub_id < 0x20)
	{	
		switch(sub_id)
		{	
			case CAN_UPDATE_RX_ENTER_IAP:
				if (CanBoxUpdateState==CANBOX_UPDATE_WAIT_ENTER_IAP)
				{
					CanBoxUpdateState = CANBOX_UPDATE_REFLASH_CANBOX;
				}
				break;
			case CAN_UPDATE_RX_KEY_REQ:
				if(CanBoxUpdateState==CANBOX_UPDATE_WAIT_REQUEST)
				{
					CanBoxUpdateState = CANBOX_UPDATE_TX_UNLOCK;
				}
				else if(CanBoxUpdateState==CANBOX_UPDATE_HANDLING)
				{

					CanUpdate_TxCanCMD(CAN_UPDATE_TX_UNLOCK_CMD);
				}
				else if(CanBoxUpdateState==CANBOX_UPDATE_WAIT_END)
				{
					CanBoxUpdateState = CANBOX_UPDATE_TX_UNLOCK;
				}
				break;
			case CAN_UPDATE_RX_DATA_REQ:
				CanBoxUpdateState=CANBOX_UPDATE_HANDLING;
				CanUpdateDataIndex = WORD(data[3],data[4]);
				PostMessage(NAVI_MODULE, MCU_SEND_REQUEST_CMD,0);
				break;
			case CAN_UPDATE_RX_RESET_REQ:
				CanUpdate_TxCanCMD(CAN_UPDATE_TX_RESET);
				if(CanBoxUpdateState==CANBOX_UPDATE_WAIT_END)
				{
					CanBoxUpdateState=CANBOX_UPDATE_END;
					CanUpdateTimer=T500MS_100;
				}
				PostMessage(NAVI_MODULE, MCU_NOTIFY_UPDATE_OK,0);
				break;
			default:
				break;	
		}
	}
}

void CanUpdate_RxCanAnalyse(void)
{
	u16 start=CanFunRxBuffer.head;
	u16 end=CanFunRxBuffer.tail;
	u8 data[MAX_CAN_RX_LENGTH];
	u16 buffer_data_length;
	u16 i;
	u16 j;
	u16 packet_length;
	u16 packet_length_index;
	u16 packet_counter;
	u16 head_code1_index;
	u16 head_code2_index;
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

		if(buffer_data_length>=MIN_CAN_RX_LENGTH)
		{
			head_code1_index=i;
			head_code2_index=i+1;
			if(head_code2_index>=MAX_CAN_RX_BUFFER_LENGTH)
			{
				head_code2_index-=MAX_CAN_RX_BUFFER_LENGTH;
			}
			if(SOF1==CanFunRxBuffer.data[head_code1_index]
				&&SOF2==CanFunRxBuffer.data[head_code2_index])
			{
				packet_length_index=i+2;
				if(packet_length_index>=MAX_CAN_RX_BUFFER_LENGTH)
				{
					packet_length_index-=MAX_CAN_RX_BUFFER_LENGTH;
				}
				packet_length=CanFunRxBuffer.data[packet_length_index]+5;   
				if(packet_length<=MAX_CAN_RX_LENGTH)
				{
					if(buffer_data_length>=(packet_length))
					{
						checksum=0;
						packet_counter=i+2;
						if (packet_counter>=MAX_CAN_RX_BUFFER_LENGTH)
						{
							packet_counter -= MAX_CAN_RX_BUFFER_LENGTH;
						}
						for(j=2;j<packet_length-1;j++)
						{
							checksum+=CanFunRxBuffer.data[packet_counter];
							data[j-2]=CanFunRxBuffer.data[packet_counter];
							packet_counter++;
							if(packet_counter>=MAX_CAN_RX_BUFFER_LENGTH)
							{
								packet_counter=0;
							}
						}
						if(((checksum-1)&0xFF)==CanFunRxBuffer.data[packet_counter])
						{
							CanFunRxBuffer.head=packet_counter;
							packet_counter=i;
							for(j=0;j<packet_length;j++)
							{
								CanFunRxBuffer.data[packet_counter]=0;
								packet_counter++;
								if(packet_counter>=MAX_CAN_RX_BUFFER_LENGTH)
								{
									packet_counter=0;
								}
							}
							CanUpdate_RxCanDataPro(data);
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		else
		{
			break;
		}
		CanFunRxBuffer.data[i]=0;
		i++;
		if(i>=MAX_CAN_RX_BUFFER_LENGTH)
		{
			i=0;
		}
		CanFunRxBuffer.head=i;
	}	
}

void CanBoxUpdatePro(void)
{	
	CanUpdateTimeout=0;
	while(1)
	{
		if(F_SYS_100MS)
		{
			F_SYS_100MS=0;
			if(CanUpdateTimer)
			{
				CanUpdateTimer--;
			}
			CanUpdateTimeout++;
			if(CanUpdateTimeout>T60S_100)
			{
				SystemReset();
			}
		}
		Wdt_Feed();
		APP_DataAnalyse();
		CanUpdate_RxCanAnalyse();
		if(Uart_Tx_counter==0)
		{
			CanUpdate_TxAppDataPro();    
		}
		
		switch(CanBoxUpdateState)
		{
			case CANBOX_UPDATE_IDLE:
				break;
			case CANBOX_UPDATE_READY:
				CanUpdateDataIndex=0;
				CanFunRxBuffer.head=0;
				CanFunRxBuffer.tail=0;
				F_UART_TX_BUFF_FULL=0;
				FormatMemery(CanFunRxBuffer.data,MAX_CAN_RX_BUFFER_LENGTH);
				ClearMessage(NAVI_MODULE);  
				PostMessage(NAVI_MODULE, MCU_NOTIFY_READY,0);
				CanBoxUpdateState=CANBOX_UPDATE_REQ_ENTER_IAP;
				break;
			case CANBOX_UPDATE_REQ_ENTER_IAP:
				CanUpdate_TxEnterIap();
				CanBoxUpdateState=CANBOX_UPDATE_WAIT_ENTER_IAP;
				CanUpdateTimer=T500MS_100;
				break;
			case CANBOX_UPDATE_WAIT_ENTER_IAP:
				CanUpdate_TxCanCMD(CAN_UPDATE_TX_REQ_ENTER_IAP);
				if(CanUpdateTimer==0)
				{
					CanBoxUpdateState=CANBOX_UPDATE_REQ_ENTER_IAP;
				}
				break;		
			case CANBOX_UPDATE_REFLASH_CANBOX:
				CanUpdate_TxCanCMD(CAN_UPDATE_TX_REFLASH_CMD);
				CanBoxUpdateState=CANBOX_UPDATE_WAIT_REQUEST;
				CanUpdateTimer=T500MS_100;
				break;
			case CANBOX_UPDATE_WAIT_REQUEST:
				if(CanUpdateTimer==0)
				{
					CanBoxUpdateState=CANBOX_UPDATE_REFLASH_CANBOX;
				}
				break;
			case CANBOX_UPDATE_TX_UNLOCK:
				CanUpdate_TxCanCMD(CAN_UPDATE_TX_UNLOCK_CMD);
				CanBoxUpdateState=CANBOX_UPDATE_WAIT_UNLOCK;
				CanUpdateTimer = T500MS_100;
				break;
			case CANBOX_UPDATE_WAIT_UNLOCK:
				if(CanUpdateTimer==0)
				{
					CanBoxUpdateState=CANBOX_UPDATE_TX_UNLOCK;
				}
			case CANBOX_UPDATE_HANDLING:
				break;
			case CANBOX_UPDATE_WAIT_END:
				if(CanUpdateTimer==0)
				{
					CanUpdate_TxCanChecksum(CanUpdateChecksum);
					CanUpdateTimer=T500MS_100;	
				}
				break;
			case CANBOX_UPDATE_END:
				if(CanUpdateTimer==0)
				{
					CanUpdateTimeout=0;
					CanUpdateTimer=T500MS_100;	
					PostMessage(NAVI_MODULE, MCU_NOTIFY_UPDATE_OK,0);
				}
				break;
			case CANBOX_UPDATE_RESET:
				SystemReset();
				break;
			default:
				break;
		}
	}
}

#endif

