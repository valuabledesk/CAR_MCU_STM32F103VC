#include "public.h"	

u32 MCU_Tx_ACK_Counter;
ACK_MSGQUEUE ACK_MessageQueue;

void ACK_PostMessage(u8 ack,u8 seq_num)
{
	if(ACK_MessageQueue.num<ACK_QUEUE_LENGTH)
	{
		ACK_MessageQueue.queue[ACK_MessageQueue.tail].ack=ack;
		ACK_MessageQueue.queue[ACK_MessageQueue.tail].seq_num=seq_num;
		ACK_MessageQueue.num++;
		ACK_MessageQueue.tail++;
		if(ACK_MessageQueue.tail>=ACK_QUEUE_LENGTH)
		{
			ACK_MessageQueue.tail=0;
		}
	}
}

ACK_MESSAGE ACK_GetMessage(void)
{
	ACK_MESSAGE temp;

	temp.ack=0;
	temp.seq_num=0;

	if(ACK_MessageQueue.num!=0)
	{
		temp.ack=ACK_MessageQueue.queue[ACK_MessageQueue.head].ack;
		temp.seq_num=ACK_MessageQueue.queue[ACK_MessageQueue.head].seq_num;
		
		ACK_MessageQueue.queue[ACK_MessageQueue.head].ack=0;
		ACK_MessageQueue.queue[ACK_MessageQueue.head].seq_num=0;
		
		ACK_MessageQueue.head++;
		if(ACK_MessageQueue.head>=ACK_QUEUE_LENGTH)
		{
			ACK_MessageQueue.head=0;
		}
		ACK_MessageQueue.num--;
		if(0==ACK_MessageQueue.num)
		{
			ACK_MessageQueue.head=0;
			ACK_MessageQueue.tail=0;
		}	
	}
	return temp;
}

void ACK_ClearMessage(void)
{
	u32 i;

	ACK_MessageQueue.num=0;
	ACK_MessageQueue.head=0;
	ACK_MessageQueue.tail=0;
	for(i=0;i<ACK_QUEUE_LENGTH;i++)
	{
		ACK_MessageQueue.queue[i].ack=0;
		ACK_MessageQueue.queue[i].seq_num=0;
	}
}

void Mcu_Ack_Tx_1(u8 ackchar,u8 seq)
{
	u8 buf[6];
	u8 i;
	u8 checksum=0;	

	buf[0]=HEAD_ADDRESS_MCU;
	buf[1]=HEAD_ADDRESS_APP;
	buf[2]=seq;
	buf[3]=ackchar;
	buf[4]=6;
	for(i=0;i<=4;i++)
	{
	checksum^=buf[i]; 
	}
	checksum^=0xff;
	buf[5]=checksum;
#if defined(AUTOCHIPS_AC781X)
	UART4_SendData(buf,6);
#elif defined(HDSC_HC32F460)
	UART3_SendData(buf,6);
#elif defined(HDSC_HC32L072)
	UART3_SendData(buf,6);
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
	UART2_SendData(buf,6);
#else
	UART4_SendData(buf,6);
#endif
#elif defined(STM32F401xx)
	UART6_SendData(buf,6);
#endif
	MCU_Tx_ACK_Counter++;
#if APP_COM_DEBUG_FUN==1
	printf("Mcu_Ack_Tx_1:seq_num=%d\r\n",seq);
#endif
}

void Mcu_Ack_Tx_Pro(void)
{
	if(Uart_Tx_counter==0)
	{
		ACK_MESSAGE temp;

		temp=ACK_GetMessage();
		if(temp.ack)
		{
			Mcu_Ack_Tx_1(temp.ack,temp.seq_num);
		}
	}
}

