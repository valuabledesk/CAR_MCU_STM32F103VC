#include "public.h"	

#if CANBOX_BNR_UPDATE_FUN==1
CANBOX_UPDATE_STATE CanBoxUpdateState;
CAN_UPDATE_FLAG CanUpdateFlag;
CAN_UPD_RX_APP_FLAG CanUpdRxAppFlag;
CAN_UPD_RX_CAN_FLAG CanUpdRxCanFlag;
u32 CanUpdateDataAddress;
u32 CanupdateReadAddress;
u16 CanUpdateDataIndex;
u16 CanUpdateTimer;
u8 CanUpdateData[CAN_BNR_UPDATE_DATA_LENGTH];
u8 CanUpdateTxAppEnable;
u8 CanUpdateTxAppCmd;
u8 CanUpdateTxSyncCounter;
u8 CanUpdateRxNAckCounter;
u8 CanUpdateResendCounter;

u8 IsReqCanUpdate(void)
{
	return(CanUpdateFlag.field.F_req_can_update);
}

void CanUpdateStart(void)
{
	CanUpdateFlag.field.F_req_can_update=1;
	CanBoxUpdateState=CAN_UPD_START;
}

void CanUpdate_BNR_ReadCmd(void)
{
	CanFunTxBuffer[0]=CAN_BNR_UPDATE_READ;	
	CanFunTxBuffer[1]=0xEE;
    CanBoxUartTxFarmat(CanFunTxBuffer,2);
}

void CanUpdate_BNR_ResetCmd(void)
{
	CanFunTxBuffer[0]=CAN_BNR_UPDATE_RESET;	
	CanFunTxBuffer[1]=0xDE;
    CanBoxUartTxFarmat(CanFunTxBuffer,2);
}

void CanUpdate_BNR_WriteCmd(void)
{
	CanFunTxBuffer[0]=CAN_BNR_UPDATE_WRITE;	
	CanFunTxBuffer[1]=0xCE;
    CanBoxUartTxFarmat(CanFunTxBuffer,2);
}

void CanUpdate_BNR_ReadAddress(void)
{
	CanFunTxBuffer[0]=(CanupdateReadAddress&0xFF000000)>>24;	
	CanFunTxBuffer[1]=(CanupdateReadAddress&0x00FF0000)>>16;
	CanFunTxBuffer[2]=(CanupdateReadAddress&0x0000FF00)>>8;
	CanFunTxBuffer[3]=CanupdateReadAddress&0x000000FF;
	CanFunTxBuffer[4]=(CanFunTxBuffer[0]^CanFunTxBuffer[1]^CanFunTxBuffer[2]^CanFunTxBuffer[3]);

    CanBoxUartTxFarmat(CanFunTxBuffer,5);
}

void CanUpdate_BNR_ResetAddress(void)
{
	CanFunTxBuffer[0]=(CAN_BNR_UPDATE_START_ADDRESS&0xFF000000)>>24;	
	CanFunTxBuffer[1]=(CAN_BNR_UPDATE_START_ADDRESS&0x00FF0000)>>16;
	CanFunTxBuffer[2]=(CAN_BNR_UPDATE_START_ADDRESS&0x0000FF00)>>8;
	CanFunTxBuffer[3]=CAN_BNR_UPDATE_START_ADDRESS&0x000000FF;
	CanFunTxBuffer[4]=(CanFunTxBuffer[0]^CanFunTxBuffer[1]^CanFunTxBuffer[2]^CanFunTxBuffer[3]);

    CanBoxUartTxFarmat(CanFunTxBuffer,5);
}

void CanUpdate_BNR_WriteAddress(void)
{
	CanFunTxBuffer[0]=(CanUpdateDataAddress&0xFF000000)>>24;	
	CanFunTxBuffer[1]=(CanUpdateDataAddress&0x00FF0000)>>16;
	CanFunTxBuffer[2]=(CanUpdateDataAddress&0x0000FF00)>>8;
	CanFunTxBuffer[3]=CanUpdateDataAddress&0x000000FF;
	CanFunTxBuffer[4]=(CanFunTxBuffer[0]^CanFunTxBuffer[1]^CanFunTxBuffer[2]^CanFunTxBuffer[3]);

    CanBoxUartTxFarmat(CanFunTxBuffer,5);
}

void CanUpdate_BNR_Data(void)
{
	u8 i;
	u8 checksum;

	CanFunTxBuffer[0]=CAN_BNR_UPDATE_DATA_LENGTH-1;
	checksum=CanFunTxBuffer[0];
	for(i=0;i<CAN_BNR_UPDATE_DATA_LENGTH;i++)
	{
		CanFunTxBuffer[i+1]=CanUpdateData[i];
		checksum^=CanFunTxBuffer[i+1];
	}
	CanFunTxBuffer[129]=checksum;
    CanBoxUartTxFarmat(CanFunTxBuffer,130);
}

void CanUpdate_BNR_SYNC(void)
{
	CanFunTxBuffer[0]=CAN_BNR_UPDATE_SYNC;	
    CanBoxUartTxFarmat(CanFunTxBuffer,1);
}

void CanUpdateTxAppStart(void)
{
	CanUpdateTxAppEnable=0;
	CanUpdateTxAppCmd=0;	
	Usart_TxStart();
}

void CanUpdate_AppDataService(u8 *rx_buff)
{
	u8 nGRoupID;
	u8 sub_id;
	u8 *data;
	u16 temp;
	u8 length;
	u16 i;
	
	Uart_Rx_Seq_Num=rx_buff[2]; 
	nGRoupID=rx_buff[3]; 
	length=rx_buff[4];
	sub_id=rx_buff[6]; 
	data=&rx_buff[7]; 
	if(nGRoupID<MCU_TXRX_NACK_NG)
	{   
		Mcu_Ack_Tx(MCU_TXRX_ACK);
	}
	
	switch(nGRoupID)
	{
		case MCU_RX_CAN_UPDATE_INFO:
			switch(sub_id)
			{
				case APP_REQ_ENTER_CAN_UPDATE:
					CanUpdateTxAppEnable=1;
					CanUpdateTxAppCmd=MCU_NOTIFY_CAN_UPD_READY;	
					break;
				case APP_SEND_CAN_UPD_DATA:
					temp=data[0];
					temp<<=8;
					temp+=data[1];
					if(temp==CanUpdateDataIndex
						&&((length-9)==CAN_BNR_UPDATE_DATA_LENGTH))
					{
						CAN_UPD_RX_APP_DATA=1;
						for(i=0;i<CAN_BNR_UPDATE_DATA_LENGTH;i++)
						{
							CanUpdateData[i]=data[2+i];
						}
					}
					break;
				case APP_SEND_CAN_UPD_END:
					temp=data[0];
					temp<<=8;
					temp+=data[1];	
					if(temp==CanUpdateDataIndex
						&&((length-13)==CAN_BNR_UPDATE_DATA_LENGTH))
					{
						CAN_UPD_RX_APP_FINISH_DATA=1;
						for(i=0;i<CAN_BNR_UPDATE_DATA_LENGTH;i++)
						{
							CanUpdateData[i]=data[2+i];
						}
					}
					break;
				case APP_SEND_CAN_UPD_RESET:
					CAN_UPD_RX_APP_RESET_REQ=1;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void CanUpdateTxAppPro(void)
{
	u8 tx_flag=1;
	
	if(CanUpdateTxAppEnable==0
		||CanUpdateTxAppCmd==0
		||Uart_Tx_counter)
	{
		return;
	}
	
	McuTxBuffer[0]=HEAD_ADDRESS_MCU;
	McuTxBuffer[1]=HEAD_ADDRESS_APP;
	McuTxBuffer[2]=Uart_Tx_Seq_Num++;
	McuTxBuffer[3]=0x00;
	McuTxBuffer[5]=0;
	McuTxBuffer[7]=MCU_TX_CAN_UPDATE_INFO;
	McuTxBuffer[8]=CanUpdateTxAppCmd;
	
	switch(CanUpdateTxAppCmd)
	{
		case MCU_NOTIFY_CAN_UPD_READY:
		case MCU_NOTIFY_CAN_UPD_OK:
		case MCU_NOTIFY_CAN_UPD_NG:
			McuTxBuffer[4]=10;
			McuTxBuffer[6]=2;
			McuTxBuffer[9]=0xAA;
			break;
		case MCU_REQ_CAN_UPD_DATA:
			McuTxBuffer[4]=12;
			McuTxBuffer[6]=4;
			McuTxBuffer[9]=MSB(CanUpdateDataIndex);
			McuTxBuffer[10]=LSB(CanUpdateDataIndex);
			McuTxBuffer[11]=0xAA;
			break;
		default:
			tx_flag=0;
			break;
	}
	if(tx_flag)
	{
		Data_Length_IN_Buffer=McuTxBuffer[4];
		SetPacket();
		CanUpdateTxAppStart();	
	}
}

void CanUpdateRxSlavePro(void)
{
	u16 start=CanFunRxBuffer.head;
	u16 end=CanFunRxBuffer.tail;
	u16 i;
	u8 flag=0;

	for(i=start;i!=end;)
	{		
		if(CanFunRxBuffer.data[i]==CAN_BNR_UPDATE_ACK
			||CanFunRxBuffer.data[i]==CAN_BNR_UPDATE_NACK)
		{
			if(CanFunRxBuffer.data[i]==CAN_BNR_UPDATE_ACK)
			{
				CAN_UPD_RX_CAN_ACK=1;
			}
			else
			{
				CAN_UPD_RX_CAN_NACK=1;
			}	
			flag=1;
		}
		CanFunRxBuffer.data[i]=0;
		i++;
		if(i>=MAX_CAN_RX_BUFFER_LENGTH)
		{
			i=0;
		}
		CanFunRxBuffer.head=i;	
		if(flag)
		{
			break;
		}
	}
}

void CanUpdateClearSlaveData(void)
{
	u16 start=CanFunRxBuffer.head;
	u16 end=CanFunRxBuffer.tail;
	u16 i;

	for(i=start;i!=end;)
	{
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
#if CAN_DEBUG_FUN == 1
		printf("CAN UPDATE START! \r\n");
#endif
	while(1)
	{
		if(F_CAN_TASK_10MS)
		{
			F_CAN_TASK_10MS=0;
			if(CanUpdateTimer)
			{
				CanUpdateTimer--;
			}
			switch(CanBoxUpdateState)
			{
				case CAN_UPD_IDLE:
					break;
				case CAN_UPD_START:
					CanUpdateTxAppEnable=1;
					CanUpdateTxAppCmd=MCU_NOTIFY_CAN_UPD_READY;		
					CanUpdateDataAddress=CAN_BNR_UPDATE_START_ADDRESS;
					CanUpdateDataIndex=0;
					CanUpdateTxSyncCounter=0;
					CanUpdateTimer=0;
					CanUpdateResendCounter=0;
					CanUpdateFlag.field.F_can_update_result=0;
					CanUpdateFlag.field.F_can_update_reset=0;
					CanBoxUpdateState=CAN_UPD_TX_SYNC_SEQ;
					break;
				case CAN_UPD_TX_SYNC_SEQ:
					if(CanUpdateTimer)
					{
						break;
					}
					CanUpdate_BNR_SYNC();
					CanUpdateClearSlaveData();
					CanUpdateTimer=T100MS_10;
					CanUpdateTxSyncCounter++;
					if(CanUpdateTxSyncCounter>20)
					{
						CanUpdateTxSyncCounter=0;
						CanUpdateRxNAckCounter=0;
						CanUpdRxAppFlag.byte=0;
						CanUpdRxCanFlag.byte=0;
						CanUpdateTimer=0;
						CanUpdateClearSlaveData();
						CanBoxUpdateState=CAN_UPD_TX_SYNC;
					}
					break;
				case CAN_UPD_TX_SYNC:
					CanUpdate_BNR_SYNC();
					CanUpdateTxSyncCounter++;
					CanUpdateTimer=T100MS_10;
					CanBoxUpdateState=CAN_UPD_WAIT_SYNC;
					break;
				case CAN_UPD_WAIT_SYNC:
					if(CAN_UPD_RX_CAN_ACK)
					{
						CAN_UPD_RX_CAN_ACK=0;
						CanBoxUpdateState=CAN_UPD_REQ_APP_DATA;
						CanUpdateTimer=T2S_10;
					}
					else if(CAN_UPD_RX_CAN_NACK)
					{
						CAN_UPD_RX_CAN_NACK=0;
						CanUpdateRxNAckCounter++;
						if(CanUpdateRxNAckCounter>10)
						{
							CanBoxUpdateState=CAN_UPD_REQ_APP_DATA;
						}
						else
						{
							CanBoxUpdateState=CAN_UPD_TX_SYNC;
						}
					}
					else if(0==CanUpdateTimer)
					{
						CanBoxUpdateState=CAN_UPD_TX_SYNC;
					}
					break;
				case CAN_UPD_REQ_APP_DATA:
					if(CanUpdateTimer)
					{
						break;
					}
					CanUpdateTxAppEnable=1;
					CanUpdateTxAppCmd=MCU_REQ_CAN_UPD_DATA;
					CanUpdateTimer=T400MS_10;
					CanBoxUpdateState=CAN_UPD_WAIT_APP_DATA;
					break;
				case CAN_UPD_WAIT_APP_DATA:
					if(CAN_UPD_RX_APP_DATA
						||CAN_UPD_RX_APP_FINISH_DATA)
					{
						CAN_UPD_RX_APP_DATA=0;
						CanUpdateDataAddress=CAN_BNR_UPDATE_START_ADDRESS+(CanUpdateDataIndex*128);
						CanBoxUpdateState=CAN_UPD_TX_W_CMD;
						CanUpdateResendCounter=0;
						CanUpdateTimer=0;
					}
					else if(0==CanUpdateTimer)
					{
						CanBoxUpdateState=CAN_UPD_REQ_APP_DATA;
					}
					break;
				case CAN_UPD_TX_W_CMD:
					CanUpdateResendCounter++;
					if(CanUpdateResendCounter>100)
					{
						CanBoxUpdateState=CAN_UPD_TX_RESET_CMD;
					}
					else
					{
						CAN_UPD_RX_CAN_ACK=0;
						CAN_UPD_RX_CAN_NACK=0;
						CanUpdate_BNR_WriteCmd();
						CanBoxUpdateState=CAN_UPD_WAIT_W_CMD_ACK;
						CanUpdateTimer=T2S_10;
					}
					break;
				case CAN_UPD_WAIT_W_CMD_ACK:
					if(CAN_UPD_RX_CAN_ACK)
					{
						CAN_UPD_RX_CAN_ACK=0;
						CanBoxUpdateState=CAN_UPD_TX_W_ADDR;
						CanUpdateTimer=0;
					}
					else if(CAN_UPD_RX_CAN_NACK)
					{
						CAN_UPD_RX_CAN_NACK=0;
						CanBoxUpdateState=CAN_UPD_TX_W_CMD;
						CanUpdateTimer=0;
					}
					else if(0==CanUpdateTimer)
					{
						CanBoxUpdateState=CAN_UPD_TX_W_CMD;
					}
					break;
				case CAN_UPD_TX_W_ADDR:
					CAN_UPD_RX_CAN_ACK=0;
					CAN_UPD_RX_CAN_NACK=0;
					CanUpdate_BNR_WriteAddress();
					CanBoxUpdateState=CAN_UPD_WAIT_W_ADDR_ACK;
					CanUpdateTimer=T2S_10;
					break;
				case CAN_UPD_WAIT_W_ADDR_ACK:
					if(CAN_UPD_RX_CAN_ACK)
					{
						CAN_UPD_RX_CAN_ACK=0;
						CanBoxUpdateState=CAN_UPD_TX_DATA;
						CanUpdateTimer=0;
					}
					else if(CAN_UPD_RX_CAN_NACK)
					{
						CAN_UPD_RX_CAN_NACK=0;
						CanBoxUpdateState=CAN_UPD_TX_W_CMD;
						CanUpdateTimer=0;
					}
					else if(0==CanUpdateTimer)
					{
						CanBoxUpdateState=CAN_UPD_TX_W_CMD;
					}				
					break;
				case CAN_UPD_TX_DATA:
					CAN_UPD_RX_CAN_ACK=0;
					CAN_UPD_RX_CAN_NACK=0;
					CanUpdate_BNR_Data();
					CanBoxUpdateState=CAN_UPD_WAIT_DATA_ACK;
					CanUpdateTimer=T2S_10;				
					break;
				case CAN_UPD_WAIT_DATA_ACK:
					if(CAN_UPD_RX_CAN_ACK)
					{
						CAN_UPD_RX_CAN_ACK=0;
						if(CAN_UPD_RX_APP_FINISH_DATA)
						{
							CanUpdateDataAddress=CAN_BNR_UPDATE_START_ADDRESS;
							CanBoxUpdateState=CAN_UPD_TX_RESET_CMD;
							CanUpdateResendCounter=0;
							CanUpdateFlag.field.F_can_update_result=1;
						}
						else
						{
							CanBoxUpdateState=CAN_UPD_REQ_APP_DATA;
							CanUpdateDataIndex++;
						}
						CanUpdateTimer=0;
					}
					else if(CAN_UPD_RX_CAN_NACK)
					{
						CAN_UPD_RX_CAN_NACK=0;
						CanBoxUpdateState=CAN_UPD_TX_W_CMD;
						CanUpdateTimer=0;
					}
					else if(0==CanUpdateTimer)
					{
						CanBoxUpdateState=CAN_UPD_TX_W_CMD;
					}
					break;
				case CAN_UPD_TX_RESET_CMD:
					CanUpdateResendCounter++;
					if(CanUpdateResendCounter>5)
					{
						CanBoxUpdateState=CAN_UPD_RESET_WAIT;
						CAN_UPD_RX_APP_RESET_REQ=0;
						if(CanUpdateFlag.field.F_can_update_result)
						{
							CanUpdateTxAppEnable=1;
							CanUpdateTxAppCmd=MCU_NOTIFY_CAN_UPD_OK;						
						}
						else
						{
							CanUpdateTxAppEnable=1;
							CanUpdateTxAppCmd=MCU_NOTIFY_CAN_UPD_NG;						
						}
					}
					else
					{
						CAN_UPD_RX_CAN_ACK=0;
						CAN_UPD_RX_CAN_NACK=0;
						CanUpdate_BNR_ResetCmd();
						CanBoxUpdateState=CAN_UPD_WAIT_RESTET_CMD_ACK;
						CanUpdateTimer=T2S_10;
					}
					break;
				case CAN_UPD_WAIT_RESTET_CMD_ACK:
					if(CAN_UPD_RX_CAN_ACK)
					{
						CAN_UPD_RX_CAN_ACK=0;
						CanBoxUpdateState=CAN_UPD_TX_RESET_ADDR;
						CanUpdateTimer=0;
					}
					else if(CAN_UPD_RX_CAN_NACK)
					{
						CAN_UPD_RX_CAN_NACK=0;
						CanBoxUpdateState=CAN_UPD_TX_RESET_CMD;
						CanUpdateTimer=0;
					}
					else if(0==CanUpdateTimer)
					{
						CanBoxUpdateState=CAN_UPD_TX_RESET_CMD;
						CanUpdateTimer=0;
					}
					break;
				case CAN_UPD_TX_RESET_ADDR:
					CAN_UPD_RX_CAN_ACK=0;
					CAN_UPD_RX_CAN_NACK=0;
					CanUpdate_BNR_WriteAddress();
					CanBoxUpdateState=CAN_UPD_WAIT_RESET_ADDR_ACK;
					CanUpdateTimer=T2S_10;
					break;
				case CAN_UPD_WAIT_RESET_ADDR_ACK:
					if(CAN_UPD_RX_CAN_ACK)
					{
						CAN_UPD_RX_CAN_ACK=0;
						CanBoxUpdateState=CAN_UPD_RESET_WAIT;
						CAN_UPD_RX_APP_RESET_REQ=0;
						CanUpdateFlag.field.F_can_update_reset=1;
						if(CanUpdateFlag.field.F_can_update_result
							&&CanUpdateFlag.field.F_can_update_reset)
						{
							CanUpdateTxAppEnable=1;
							CanUpdateTxAppCmd=MCU_NOTIFY_CAN_UPD_OK;						
						}
						else
						{
							CanUpdateTxAppEnable=1;
							CanUpdateTxAppCmd=MCU_NOTIFY_CAN_UPD_NG;						
						}
					}
					else if(CAN_UPD_RX_CAN_NACK)
					{
						CAN_UPD_RX_CAN_NACK=0;
						CanBoxUpdateState=CAN_UPD_TX_RESET_CMD;
						CanUpdateTimer=0;
					}
					else if(0==CanUpdateTimer)
					{
						CanBoxUpdateState=CAN_UPD_TX_RESET_CMD;
					}				
					break;
				case CAN_UPD_RESET_WAIT:
					if(CAN_UPD_RX_APP_RESET_REQ)
					{
						CanBoxUpdateState=CAN_UPD_RESTART;
					}
					break;
				case CAN_UPD_RESTART:
					SystemReset();
					break;
				default:
					break;
			}
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
		CanUpdateRxSlavePro();     
		CanUpdateTxAppPro();  
	}
}

#endif
