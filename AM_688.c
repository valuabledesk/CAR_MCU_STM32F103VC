#include "public.h"	

#if AM_688_UART_FUN==1
u8 door_tx_buffer[8];
u8 door_rx_buffer[4];
u16 BatteryVoltageTxTimer;
u16 DoorLockStateTxTimer;
u8 Am_688UartAccOnFlag;
u8 Am_688UartAccOffFlag;
u8 DoorsLockSet;
u8 BatteryVoltage;
u8 DoorLockState;
u8 acc_power_off;
u8 acc_power_off_flag;

AM_688_UART_RX_BUFFER Am_688UartRxBuffer;
u8 Am_688UartWakeUpFlag;

const u8 AccOnMessage[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x20,0x03,0x01,0x01,0xDB,0xAA,0xFF};
const u8 AccOffMessage[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x21,0x03,0x02,0x02,0xDC,0xAA,0xFF};
const u8 DoorLockInvalidMessage[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x22,0x03,0x03,0x03,0x00,0xAA,0xFF};
const u8 DoorLockValidMessage[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x23,0x03,0x04,0x04,0x01,0xAA,0xFF};

//const u8 SleepTimeMessage_03[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x20,0x03,0x03,0x01,0xDB,0xAA,0xFF};
const u8 SleepTimeMessage_07[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x20,0x03,0x07,0x01,0xDB,0xAA,0xFF};
const u8 SleepTimeMessage_30[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x20,0x03,0x1e,0x01,0xDB,0xAA,0xFF};
const u8 SleepTimeMessage_60[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x20,0x03,0x3c,0x01,0xDB,0xAA,0xFF};

const u8 CarLockMessage[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x20,0x03,0x02,0x02,0xDC,0xAA,0xFF};

const u8 AllowsAccessMessage[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x20,0x03,0x04,0x04,0x01,0xAA,0xFF};
const u8 ShowMessage[AM_688_UART_RX_ACC_DATA_LENGTH]={0x23,0x20,0x03,0x03,0x03,0x00,0xAA,0xFF};
const u8 SystemStatusMessage[AM_688_UART_RX_ACC_DATA_LENGTH]={0xAA,0x26,0x53,0x59,0x53,0x3F,0xAA,0x27};

void Am_688UartDataInt(void)
{
	u32 i;

	for(i=0;i<MAX_AM_688_UART_RX_BUFFER_LENGTH;i++)
	{
		Am_688UartRxBuffer.data[i]=0;
	}
	Am_688UartRxBuffer.head=0;
	Am_688UartRxBuffer.tail=0;
	Am_688UartAccOnFlag=0;
	Am_688UartAccOffFlag=0;
}

void Am_688UartClearAccFlag(void)
{
	Am_688UartAccOnFlag=0;
	Am_688UartAccOffFlag=0;
}

void Am_688UartRxService(u8 *data)
{
	u8 buffer[4];
	u8 i;
	u16 sleep_time;
	if(strcmp_equal(data,(u8 *)AccOnMessage,8))
	{
		Am_688UartAccOnFlag=1;
		Am_688UartAccOffFlag=0;
		buffer[0]=0x23;
		buffer[1]=0x20;
		buffer[2]=0xAA;
		buffer[3]=0xFF;	
    //UART0_SendData(buffer,4);
	}
	else if(strcmp_equal(data,(u8 *)AccOffMessage,8))
	{
		Am_688UartAccOnFlag=0;
		Am_688UartAccOffFlag=1;
		buffer[0]=0x23;
		buffer[1]=0x21;
		buffer[2]=0xAA;
		buffer[3]=0xFF;
    //UART0_SendData(buffer,4);
	}
	else if(strcmp_equal(data,(u8 *)DoorLockInvalidMessage,8))
	{
		buffer[0]=0x23;
		buffer[1]=0x22;
		buffer[2]=0xAA;
		buffer[3]=0xFF;
    //UART0_SendData(buffer,4);	
		DoorLockState=0;
	}
	else if(strcmp_equal(data,(u8 *)DoorLockValidMessage,8))
	{
		buffer[0]=0x23;
		buffer[1]=0x23;
		buffer[2]=0xAA;
		buffer[3]=0xFF;
    //UART0_SendData(buffer,4);
		DoorLockState=1;
	}
	else if(strcmp_equal(data,(u8 *)SleepTimeMessage_07,8)||strcmp_equal(data,(u8 *)SleepTimeMessage_30,8)||strcmp_equal(data,(u8 *)SleepTimeMessage_60,8))
	{
		if(data[3]==0x07)sleep_time=data[3];
		else if(data[3]==0x1E)sleep_time=data[3];
		else if(data[3]==0x3C)sleep_time=data[3];
		SYSTEM_ACC_DELAY_TIME=sleep_time*10;
		SYSTEM_ACC_OFF_TIME=SYSTEM_ACC_DELAY_TIME+30;
		buffer[0]=0xAB;
		buffer[1]=data[3];
		buffer[2]=0x00;
		buffer[3]=0xFF;
#if defined(HDSC_HC32L072)
    UART0_SendData(buffer,4);
#elif defined(STM32_F103VC)
    UART3_SendData(buffer,4);
#endif		

	}
	else if(strcmp_equal(data,(u8 *)CarLockMessage,8))
	{
		buffer[0]=0xAB;
		buffer[1]=0x02;
		buffer[2]=0x00;
		buffer[3]=0xFF;
		acc_power_off=1;
#if defined(HDSC_HC32L072)
	  UART0_SendData(buffer,4);
#elif defined(STM32_F103VC)
    UART3_SendData(buffer,4);
#endif	

	}
	else if(strcmp_equal(data,(u8 *)AllowsAccessMessage,8))
	{
		buffer[0]=0xAB;
		buffer[1]=0x04;
		buffer[2]=0x00;
		buffer[3]=0xFF;
    //UART0_SendData(buffer,4);

	}
	else if(strcmp_equal(data,(u8 *)ShowMessage,8))
	{
		buffer[0]=0xAB;
		buffer[1]=0x03;
		buffer[2]=0x00;
		buffer[3]=0xFF;
    //UART0_SendData(buffer,4);

	}
	
	else if(data[0]==0xAA&&data[2]==0xFF)
	{
		BatteryVoltage=data[1];
	}
	for(i=0;i<8;i++)
	{
		door_tx_buffer[i]=data[i];
	}
#if MODEL==LINUX_1297WS_65HSE
	PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,0);
#else
	PostMessage(NAVI_MODULE,MCU_TX_SMART_LOCK,0);
#endif
}

void Am_688Uart_RxAnalyse(void)
{
	u16 start=Am_688UartRxBuffer.head;
	u16 end=Am_688UartRxBuffer.tail;
	u8 data[AM_688_UART_RX_ACC_DATA_LENGTH];
	u16 buffer_data_length;
	u16 packet_counter;
	u16 i;
	u16 j;
	u16 temp1_index;
	u16 temp2_index;
	
	FormatMemery(data,AM_688_UART_RX_ACC_DATA_LENGTH);
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
			buffer_data_length=MAX_AM_688_UART_RX_BUFFER_LENGTH-i+end;
		}
		if(buffer_data_length>=MIN_AM_688_UART_RX_DATA_LENGTH)
		{
			temp1_index=i;
			temp2_index=((i+1)%MAX_AM_688_UART_RX_BUFFER_LENGTH);
			if(Am_688UartRxBuffer.data[temp1_index]==0xA0
				&&(Am_688UartRxBuffer.data[temp2_index]==0xFF||Am_688UartRxBuffer.data[temp2_index]==0x27))
			{
				packet_counter=i;
				for(j=0;j<3;j++)
				{
					data[j]=Am_688UartRxBuffer.data[packet_counter];
					Am_688UartRxBuffer.data[packet_counter]=0;
					packet_counter++;
					if(packet_counter>=MAX_AM_688_UART_RX_BUFFER_LENGTH)
					{
						packet_counter=0;
					}
				}
				Am_688UartRxBuffer.head=packet_counter;
				Am_688UartRxService(data);
				break;
			}
			else if((Am_688UartRxBuffer.data[temp1_index]==0x23
				&&Am_688UartRxBuffer.data[temp2_index]==0x20)||(Am_688UartRxBuffer.data[temp1_index]==0xAA
				&&Am_688UartRxBuffer.data[temp2_index]==0x26))
			{
				if(buffer_data_length>=AM_688_UART_RX_ACC_DATA_LENGTH)
				{
					packet_counter=i;
					for(j=0;j<8;j++)
					{
						data[j]=Am_688UartRxBuffer.data[packet_counter];
						packet_counter++;
						if(packet_counter>=MAX_AM_688_UART_RX_BUFFER_LENGTH)
						{
							packet_counter=0;
						}
					}
					/////////////////////////
					if((strcmp_equal(data,(u8 *)AccOnMessage,8)
						||strcmp_equal(data,(u8*)AccOffMessage,8)
						||strcmp_equal(data,(u8*)DoorLockInvalidMessage,8)
						||strcmp_equal(data,(u8*)DoorLockValidMessage,8)
					
					  ||strcmp_equal(data,(u8*)SleepTimeMessage_07,8)
					  ||strcmp_equal(data,(u8*)SleepTimeMessage_30,8)
					  ||strcmp_equal(data,(u8*)SleepTimeMessage_60,8)
					  ||strcmp_equal(data,(u8*)CarLockMessage,8)
					  ||strcmp_equal(data,(u8*)AllowsAccessMessage,8)
					  ||strcmp_equal(data,(u8*)ShowMessage,8)
					  ||strcmp_equal(data,(u8*)CarLockMessage,8))
					  ||((data[0]==0XAA)&&(data[1]==0X26)&&(data[6]==0XAA)&&(data[7]==0X27)))
					
					
					
					{
						packet_counter=i;
						for(j=0;j<8;j++)
						{
							Am_688UartRxBuffer.data[packet_counter]=0;
							packet_counter++;
							if(packet_counter>=MAX_AM_688_UART_RX_BUFFER_LENGTH)
							{
								packet_counter=0;
							}
						}
						Am_688UartRxBuffer.head=packet_counter;
						Am_688UartRxService(data);
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
		if(i>=MAX_AM_688_UART_RX_BUFFER_LENGTH)
		{
			i=0;
		}
		Am_688UartRxBuffer.head=i;
	}
}

void Am_688UartMainPro(void)
{
	Am_688Uart_RxAnalyse();
	BatteryVoltageTxTimer++;
	if(BatteryVoltageTxTimer>T5S_10)
	{
		BatteryVoltageTxTimer=0;
		NotifyAppStateMsg(MACHINE_STATE_BATTERY_VOLTAGE,BatteryVoltage);
	}
	DoorLockStateTxTimer++;
	if(DoorLockStateTxTimer>T2S_10)
	{
		DoorLockStateTxTimer=0;
		NotifyAppStateMsg(MACHINE_STATE_DOOR_LOCK_STATE,DoorLockState);
	}
}
void Am_688UartSendDoorsLockSet(void)
{
	u8 data[8];
	u32 flag=1;
	data[0]=0xAA;
	data[1]=0x26;
	data[6]=0xAA;
	data[7]=0x27;
	switch(DoorsLockSet)
	{
		case 0:
			data[2]=0xA1;
			data[3]=0xB2;
			data[4]=0xC3;
			data[5]=0xD4;
			break;
		case 1:
			data[2]=0xA2;
			data[3]=0xB3;
			data[4]=0xC4;
			data[5]=0xD5;
			break;
		case 2:
			data[2]=0xA3;
			data[3]=0xB4;
			data[4]=0xC5;
			data[5]=0xD6;
			break;
		case 3:
			data[2]=0xA4;
			data[3]=0xB5;
			data[4]=0xC6;
			data[5]=0xD7;
		  break;
		case 4:
			data[2]=0xA5;
			data[3]=0xB6;
			data[4]=0xC7;
			data[5]=0xD8;
		  break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{
	#if defined(HDSC_HC32L072)
    UART0_SendData(data,8);
  #elif defined(STM32_F103VC)
    UART3_SendData(data,8);
  #endif	
	}
}
#endif





















