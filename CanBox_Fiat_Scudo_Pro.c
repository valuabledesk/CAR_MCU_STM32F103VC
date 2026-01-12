#include "public.h"

#if CAN_ADAPTER==1
#if CANBOX_FIAT_SCUDO==1

FIAT_SCUDO_CAN_TX_INFO FiatScudoCanAdapterTxInfo;

void CanBox_MainEvtPro_FIAT_SCUDO(void)
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
			CanBoxWorkState=FIAT_SCUDO_TX_START_COMMAND;
			break;
		case CAN_POWER_OFF:
			break;
		case CAN_ACC_OFF:
			CanBoxWorkState=FIAT_SCUDO_TX_END_COMMAND;
			break;
		case CAN_EMERGENCY_OFF:
			CanBoxWorkState=FIAT_SCUDO_POWER_OFF;
			break;
		case CAN_RX_APP_DATA:
			PostMessage(SUB_CAN_MODULE,FIAT_SCUDO_CMD_APP_DATA,nEvt->prm);
			break;
		default:
			break;
	}
}

void CanBox_TxService_FIAT_SCUDO(void)
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
			case FIAT_SCUDO_CMD_APP_DATA:
				CanFunTxBuffer[0]=FIAT_SCUDO_CAN_HEAD_CODE;	
				CanFunTxBuffer[1]=LSB(nEvt->prm);
				switch(CanFunTxBuffer[1])
				{
					case FIAT_SCUDO_RX_SET_INFO:
						switch(MSB(nEvt->prm))
						{
							case 0x01:
								CanFunTxBuffer[2]=2;
								CanFunTxBuffer[3]=FiatScudoCanAdapterTxInfo.security_cmd[0];
								CanFunTxBuffer[4]=FiatScudoCanAdapterTxInfo.security_cmd[1];
								break;
							case 0x02:
								CanFunTxBuffer[2]=2;
								CanFunTxBuffer[3]=FiatScudoCanAdapterTxInfo.accompaniment_lighting[0];
								CanFunTxBuffer[4]=FiatScudoCanAdapterTxInfo.accompaniment_lighting[1];
								break;
							case 0x03:
								CanFunTxBuffer[2]=2;
								CanFunTxBuffer[3]=FiatScudoCanAdapterTxInfo.reception_lighting[0];
								CanFunTxBuffer[4]=FiatScudoCanAdapterTxInfo.reception_lighting[1];
								break;
							case 0x04:
								CanFunTxBuffer[2]=2;
								CanFunTxBuffer[3]=FiatScudoCanAdapterTxInfo.language_cmd[0];
								CanFunTxBuffer[4]=FiatScudoCanAdapterTxInfo.language_cmd[1];
								break;
							case 0x05:
								CanFunTxBuffer[2]=2;
								CanFunTxBuffer[3]=FiatScudoCanAdapterTxInfo.distance[0];
								CanFunTxBuffer[4]=FiatScudoCanAdapterTxInfo.distance[1];
								break;
							case 0x06:
								CanFunTxBuffer[2]=2;
								CanFunTxBuffer[3]=FiatScudoCanAdapterTxInfo.temperature[0];
								CanFunTxBuffer[4]=FiatScudoCanAdapterTxInfo.temperature[1];
								break;
							default:
								CanFunTxBuffer[2]=0;
								break;
						}
						break;
					case FIAT_SCUDO_RX_TIME_INFO:
						CanFunTxBuffer[2]=7;
						for(i=0;i<7;i++)
						{
							CanFunTxBuffer[3+i]=FiatScudoCanAdapterTxInfo.time[i];
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

void CanBox_MainPro_FIAT_SCUDO(void)
{
	CanBox_MainEvtPro_FIAT_SCUDO();
	
	if(CanBoxWorkTimer)
	{
		CanBoxWorkTimer--;
	}
	switch(CanBoxWorkState)
	{
		case FIAT_SCUDO_IDLE:
			break;
		case FIAT_SCUDO_TX_START_COMMAND:
			if(CanBoxWorkTimer)
			{
				break;
			}
			CanBox_Initial();
			CanBoxWorkState=FIAT_SCUDO_WORK_NORMAL;
			break;
		case FIAT_SCUDO_WORK_NORMAL:
			CanBox_TxService_FIAT_SCUDO();
			break;
		case FIAT_SCUDO_TX_END_COMMAND:
			break;
		case FIAT_SCUDO_POWER_OFF:
			CanBoxWorkState=FIAT_SCUDO_IDLE;
			break;
		default:
			break;
	}
}

void FIAT_SCUDO_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	u8 *ptr;
	u8 length=0;
	u8 i;
	u16 temp=0;

	cmd_id=buffer[1];
	switch(cmd_id)
	{
		case FIAT_SCUDO_RX_SET_INFO:
			if(buffer[3]==0x07)
			{
				ptr=&FiatScudoCanAdapterTxInfo.security_cmd[0];
				temp=0x0100;
			}
			else if(buffer[3]==0x11)
			{
				ptr=&FiatScudoCanAdapterTxInfo.accompaniment_lighting[0];
				temp=0x0200;
			}
			else if(buffer[3]==0x12)
			{
				ptr=&FiatScudoCanAdapterTxInfo.reception_lighting[0];
				temp=0x0300;
			}
			else if(buffer[3]==0x53)
			{
				ptr=&FiatScudoCanAdapterTxInfo.language_cmd[0];
				temp=0x0400;
			}
			else if(buffer[3]==0x70)
			{
				ptr=&FiatScudoCanAdapterTxInfo.distance[0];
				temp=0x0500;
			}
			else if(buffer[3]==0x72)
			{
				ptr=&FiatScudoCanAdapterTxInfo.temperature[0];
				temp=0x0600;
			}
			length=2;				
			break;
		case FIAT_SCUDO_RX_TIME_INFO:
			ptr=&FiatScudoCanAdapterTxInfo.time[0];
			length=7;
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
		PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,cmd_id|temp);
	}
}

void FIAT_SCUDO_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
}
#endif
#endif
