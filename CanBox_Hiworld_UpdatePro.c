#include "public.h"
#if CANBOX_UPDATE_FUN_HIWORLD==1
CANBOX_UPDATE_STATE CanBoxUpdateState;
CAN_UPDATE_FLAG CanUpdateFlag;
u16 CanUpdateDataIndex;
u8 CanUpdateResendTimer;
u8 CanUpdateResendCounter;

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

void CanUpdate_TxCanReset(void)
{
	u8 data[7];

	data[0]=0x5A;
	data[1]=0xA5;
	data[2]=0x02;
	data[3]=0xE0;
	data[4]=0x00;
	data[5]=0x00;
	data[6]=data[2]+data[3]+data[4]+data[5]-1;

	CanUpdate_TxCanData(data,7);
}

void CanUpdate_TxCanKeyWord(void)
{
	u8 data[4];

	data[0]=0x19;
	data[1]=0x78;
	data[2]=0x02;
	data[3]=0x17;

	CanUpdate_TxCanData(data,4);	
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
						CanUpdate_TxCanData((data+2),136);
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
		case MCU_NOTIFY_UPDATE_ERROR:
			McuTxBuffer[4]=10;
			McuTxBuffer[6]=2;
			McuTxBuffer[8]=MCU_NOTIFY_UPDATE_ERROR;
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
		CanUpdateResendCounter=0;
		CanUpdateResendTimer=0;		
		F_UART_TX_BUFF_FULL=1;
		F_UART_TX_ACK_CHECK=1;	
		Usart_TxStart();	
	}	
}

void CanUpdate_ResendAppPro(void)
{
	if(CanUpdateResendTimer>=T200MS_10)
	{  	
		CanUpdateResendTimer=0;
		if(++CanUpdateResendCounter<3)
		{
			Usart_TxStart();
		}
		else
		{
			CanUpdateResendCounter=0;
			F_UART_TX_BUFF_FULL=0;
			F_UART_TX_ACK_CHECK=0;
		}
	}
}

void CanUpdate_RxCanDataPro(u8 *data)
{
	switch(data[0])
	{
		case CAN_CMD_UPDATE_CHECK:
			if(CANBOX_UPDATE_WAIT_REQUEST==CanBoxUpdateState)
			{
				CanBoxUpdateState=CANBOX_UPDATE_TX_KEY_WORD;
			}
			break;
		case CAN_CMD_UPDATE_END:
			if(CANBOX_UPDATE_HANDLING==CanBoxUpdateState)
			{
				CanBoxUpdateState=CANBOX_UPDATE_END;
				PostMessage(NAVI_MODULE, MCU_NOTIFY_UPDATE_OK,0);
			}
			break;
		case CAN_CMD_UPDATE_ERROR:
			if(CANBOX_UPDATE_HANDLING==CanBoxUpdateState)
			{
				CanBoxUpdateState=CANBOX_UPDATE_RESET_CANBOX;
				PostMessage(NAVI_MODULE, MCU_NOTIFY_UPDATE_ERROR,0);
			}				
			break;
		case CAN_CMD_UPDATE_REQ_DATA:
			if(CANBOX_UPDATE_HANDLING==CanBoxUpdateState)
			{
				CanUpdateDataIndex++;
				PostMessage(NAVI_MODULE, MCU_SEND_REQUEST_CMD,0);
			}
			break;
		case CAN_CMD_UPDATE_BEGIN_0:
			if(CAN_CMD_UPDATE_BEGIN_1==data[1])
			{
				if(CANBOX_UPDATE_HANDLING==CanBoxUpdateState)
				{
					CanUpdateDataIndex=0;
					PostMessage(NAVI_MODULE, MCU_SEND_REQUEST_CMD,0);
				}
			}
			break;
		default:
			break;
	}
}

void CanUpdate_RxCanAnalyse(void)
{
	u16 start=CanFunRxBuffer.head;
	u16 end=CanFunRxBuffer.tail;
	u8 data[2];
	u16 buffer_data_length;
	u16 i;
	u16 j;
	
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

		if(buffer_data_length>=1)
		{
			if(CAN_CMD_UPDATE_CHECK==CanFunRxBuffer.data[i]
				||CAN_CMD_UPDATE_END==CanFunRxBuffer.data[i]
				||CAN_CMD_UPDATE_ERROR==CanFunRxBuffer.data[i]
				||CAN_CMD_UPDATE_REQ_DATA==CanFunRxBuffer.data[i])
			{
				data[0]=CanFunRxBuffer.data[i];
				CanFunRxBuffer.data[i]=0;
				CanUpdate_RxCanDataPro(data);
				CanFunRxBuffer.head=i+1;
				if(CanFunRxBuffer.head>=MAX_CAN_RX_BUFFER_LENGTH)
				{
					CanFunRxBuffer.head=0;
				}
				break;
			}
			else if(CAN_CMD_UPDATE_BEGIN_0==CanFunRxBuffer.data[i])
			{
				if(buffer_data_length>=2)
				{
					j=i+1;
					if(j>=MAX_CAN_RX_BUFFER_LENGTH)
					{
						j=0;
					}
					if(CAN_CMD_UPDATE_BEGIN_1==CanFunRxBuffer.data[j])
					{
						data[0]=CanFunRxBuffer.data[i];
						data[1]=CanFunRxBuffer.data[j];
						CanUpdate_RxCanDataPro(data);
						CanFunRxBuffer.data[i]=0;
						CanFunRxBuffer.data[j]=0;
						CanFunRxBuffer.head=j+1;
						if(CanFunRxBuffer.head>=MAX_CAN_RX_BUFFER_LENGTH)
						{
							CanFunRxBuffer.head=0;
						}
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
	while(1)
	{
		if(F_CAN_TASK_10MS)
		{
			F_CAN_TASK_10MS=0;
			CanUpdateResendTimer++;
		}
#if defined(AUTOCHIPS_AC781X)
        WDOG_Feed();
#elif defined(HDSC_HC32F460)
        SWDT_RefreshCounter();
#elif defined(HDSC_HC32L072)
        Wdt_Feed();
#elif defined(STM32_F103VC)
        IWDG_ReloadCounter();
#endif

		APP_DataAnalyse();
		CanUpdate_RxCanAnalyse();
		if(F_UART_TX_ACK_CHECK)
		{
			CanUpdate_ResendAppPro();
		}
		else
		{
			CanUpdate_TxAppDataPro();       
		}
		
		switch(CanBoxUpdateState)
		{
			case CANBOX_UPDATE_IDLE:
				break;
			case CANBOX_UPDATE_READY:
				CanUpdateDataIndex=0;
 				CanUpdateResendTimer=0;
				CanUpdateResendCounter=0;
				CanFunRxBuffer.head=0;
				CanFunRxBuffer.tail=0;
				FormatMemery(CanFunRxBuffer.data,MAX_CAN_RX_BUFFER_LENGTH);
				ClearMessage(NAVI_MODULE);  
				PostMessage(NAVI_MODULE, MCU_NOTIFY_READY,0);
				CanBoxUpdateState=CANBOX_UPDATE_RESET_CANBOX;
				break;
			case CANBOX_UPDATE_RESET_CANBOX:
				CanUpdate_TxCanReset();
				CanBoxUpdateState=CANBOX_UPDATE_WAIT_REQUEST;
				break;
			case CANBOX_UPDATE_WAIT_REQUEST:
				break;
			case CANBOX_UPDATE_TX_KEY_WORD:
				CanUpdate_TxCanKeyWord();
				CanBoxUpdateState=CANBOX_UPDATE_HANDLING;
				break;
			case CANBOX_UPDATE_HANDLING:
				break;
			case CANBOX_UPDATE_END:
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

