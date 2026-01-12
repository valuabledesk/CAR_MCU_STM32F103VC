#ifndef _APP_COM_ACK_PRO_H_
#define _APP_COM_ACK_PRO_H_

#define ACK_QUEUE_LENGTH      200

typedef struct
{
	u8 ack;
	u8 seq_num;
}ACK_MESSAGE;

typedef struct
{
	u8 head;
	u8 tail;
	u8 num;
	ACK_MESSAGE queue[ACK_QUEUE_LENGTH];
}ACK_MSGQUEUE;

void ACK_PostMessage(u8 ack,u8 seq_num);
ACK_MESSAGE ACK_GetMessage(void);
void ACK_ClearMessage(void);
void Mcu_Ack_Tx_Pro(void);
#endif
