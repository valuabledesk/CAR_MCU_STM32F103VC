#ifndef _AM_688_UART_PRO_H_
#define _AM_688_UART_PRO_H_
#if AM_688_UART_FUN==1

#define MAX_AM_688_UART_RX_BUFFER_LENGTH			100
#define MIN_AM_688_UART_RX_DATA_LENGTH			3
#define AM_688_UART_RX_ACC_DATA_LENGTH			8

typedef struct
{
	u16 head;
	u16 tail;
	u8 data[MAX_AM_688_UART_RX_BUFFER_LENGTH];
}AM_688_UART_RX_BUFFER;

extern u8 door_tx_buffer[8];
extern u8 door_rx_buffer[4];
extern u8 Am_688UartAccOnFlag;
extern u8 Am_688UartAccOffFlag;
extern u8 DoorsLockSet;
extern u8 Am_688UartWakeUpFlag;
extern u8 acc_power_off;
extern u8 acc_power_off_flag;

extern AM_688_UART_RX_BUFFER Am_688UartRxBuffer;

void Am_688UartDataInt(void);
void Am_688UartClearAccFlag(void);
void Am_688UartMainPro(void);
void Am_688UartSendDoorsLockSet(void);
#endif
#endif

