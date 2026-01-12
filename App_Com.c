#include "public.h"	

extern const u8 McuSourceChangeTab[NUM_OF_SOURCE];
extern const u8 AppSourceChangeTab[APP_NUM_OF_SOURCE];
extern const struct DecodeUnit pCanFunMain[];

#if MODEL== ANDROID_Q133_00||MODEL== ANDROID_Q133_01||MODEL== ANDROID_Q133_uni
extern u8 tps2549_Flag;
#endif
MCU_RX_BUFFER McuRxBuffer;
u8 ver[29];
u8 McuTxBuffer[MAX_APP_TX_BUFFER_LENGTH];
APP_FLAG APP_Flag;
APP_STATUS APP_Status;
#if MODEL==LINUX_D095_55
PASSWORD_FLAG PasswordFlag = {.field.f_state = 1};
#else
PASSWORD_FLAG PasswordFlag;
#endif
APP_UART_FLAG AppUartFlag;
u8 Data_Length_IN_Buffer;
u8 nMediaPlayPackage;
u8 Uart_Rx_Seq_Num;
u8 Uart_Tx_Seq_Num;
u16 Uart_ReSend_Timer;	
u8 Uart_ReSend_Counter;
u16 Uart_Tx_counter;
u8 *Uart_Tx_Ptr;
u32 gFlashPushNum;
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
u8 TxClockTimer;
u8 AppBackupData[APP_BACKUP_DATA_LENGTH+1];
u8 AppBackupData_Bak[APP_BACKUP_DATA_LENGTH+1];
#endif
u32 MCU_RxAppPacketCounter;
u32 MCU_TxAppPacketCounter;
u32 MCU_Rx_ACK_Counter;
u8 video_protocol[32];
u8 video_lenght;
u8 F_IAP_AppCom;

void Mcu_Ack_Tx(u8 ackchar)
{
	u8 buf[6];
	u8 i;
	u8 checksum=0;	

	buf[0]=HEAD_ADDRESS_MCU;
	buf[1]=HEAD_ADDRESS_APP;
	buf[2]=Uart_Rx_Seq_Num;
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
	if(Uart_Tx_counter==0)
	{
		UART3_SendData(buf,6);
	}
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
	UART2_SendData(buf,6);
#else
    	UART4_SendData(buf,6);
#endif
#elif defined(STM32F401xx)
	UART6_SendData(buf,6);
#elif defined(HDSC_HC32F448)
	UART2_SendData(buf, 6);
#endif
}

void SetPacket(void)
{
	u8 i;
	u8 PacketChecksum=HEAD_ADDRESS_MCU;	
	
	for(i=1;i<Data_Length_IN_Buffer;i++)
	{
		PacketChecksum^=McuTxBuffer[i];  
	}
	McuTxBuffer[5]=(PacketChecksum^0xff);
}

void Usart_Com_Tx_Tick(void)
{	
#if defined(AUTOCHIPS_AC781X)
	UART4_SendData(McuTxBuffer,Data_Length_IN_Buffer);
#elif defined(HDSC_HC32F460)
	UART3_SendData(McuTxBuffer,Data_Length_IN_Buffer);
#elif defined(HDSC_HC32L072)
	UART3_SendData(McuTxBuffer,Data_Length_IN_Buffer);
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
	UART2_SendData(McuTxBuffer,Data_Length_IN_Buffer);
#else
    	UART4_SendData(McuTxBuffer,Data_Length_IN_Buffer);
#endif
#elif defined(STM32F401xx)
	UART6_SendData(McuTxBuffer,Data_Length_IN_Buffer);
#elif defined(HDSC_HC32F448)
	UART2_SendData(McuTxBuffer, Data_Length_IN_Buffer);
#endif
}

void APP_Ack_Check(void)
{  
	if(Uart_Tx_Seq_Num==Uart_Rx_Seq_Num
		||Uart_Tx_Seq_Num==Uart_Rx_Seq_Num+1)
	{
		F_UART_TX_BUFF_FULL=0;
		F_UART_TX_ACK_CHECK=0;
	}
}

void AppTimer_100msEntry(void)
{
  
}

void Usart_TxStart(void)
{
	Uart_Tx_counter=Data_Length_IN_Buffer;
	Uart_Tx_Ptr=McuTxBuffer;
#if defined(AUTOCHIPS_AC781X)
	UART_SendByte(UART4,*Uart_Tx_Ptr);
	UART_SetTxIntEn(UART4, 1);
	Uart_Tx_counter--;
	Uart_Tx_Ptr++;
#elif defined(HDSC_HC32F460)
	USART_FuncCmd(M4_USART3,UsartTxEmptyInt,Enable);
	USART_SendData(M4_USART3,*Uart_Tx_Ptr);
	Uart_Tx_counter--;
	Uart_Tx_Ptr++;	
#elif defined(HDSC_HC32L072)
	Uart_EnableIrq(M0P_UART3,UartTxIrq);
	Uart_SendDataIt(M0P_UART3,*Uart_Tx_Ptr);
	Uart_Tx_counter--;
	Uart_Tx_Ptr++;	
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
	USART_SendData(USART2,*Uart_Tx_Ptr);
	Uart_Tx_counter--;
	Uart_Tx_Ptr++;
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);	
#else
	USART_SendData(UART4,*Uart_Tx_Ptr);
	Uart_Tx_counter--;
	Uart_Tx_Ptr++;
	USART_ITConfig(UART4, USART_IT_TXE, ENABLE);	
#endif
#elif defined(STM32F401xx)
	UART_SendByte(USART6,*Uart_Tx_Ptr);
	Uart_Tx_counter--;
	Uart_Tx_Ptr++;
	USART_ITConfig(USART6, USART_IT_TXE, ENABLE);
#elif defined(HDSC_HC32F448)
	USART_WriteData(CM_USART2, *Uart_Tx_Ptr);
	Uart_Tx_counter--;
	Uart_Tx_Ptr++;
	USART_FuncCmd(CM_USART2, USART_FLAG_TX_EMPTY, ENABLE);
#endif
}

void Usart_StartFrame(void)
{
	Uart_ReSend_Counter=0;
	Uart_ReSend_Timer=0;
	F_UART_TX_BUFF_FULL=1;
	F_UART_TX_ACK_CHECK=1;
	Usart_TxStart();
}

#define MCU_SOFTWARE_VERSION_TYPE		3
void McuTxService(void)
{
	u8 buff_array[300];
	u8 *ptr2=&buff_array[0];
	u16 length=0;
	u16 j=0;
	MESSAGE*nEvt;
	
	nEvt=GetMessage(NAVI_MODULE);
	
	if(nEvt->ID==NO_EVT)
	{
		return;
	}

	if(!F_AppInit_OK
		&&nEvt->ID!=MCU_TX_CAN_BOX_INFO
#if 0
		&&nEvt->ID!=MCU_TX_CAN_SYSMODE
		&&nEvt->ID!=MCU_TX_APP_UI_TYPE
#endif
		&&nEvt->ID!=MCU_TX_MACHINE_MISC_STATE
		&&nEvt->ID!=MCU_TX_UUID_DATA
#if CHECK_MCU_UPDATE_FILE_TYPE==1
		&&nEvt->ID!=MCU_TX_MCU_TYPE
#endif
		)  
	{
		return;
	}
	MCU_TxAppPacketCounter++;
#if APP_COM_DEBUG_FUN==1
	printf("McuTxService:ID=0x%02x,seq_num=%d\r\n",nEvt->ID,(Uart_Tx_Seq_Num+1));
#endif
	switch(nEvt->ID)
	{
		case MCU_TX_MCU_REFRESH_CFM:
			length=1;
//			Set_IAP_Mode;
			F_IAP_InitSystem = 0x9a;
			F_IAP_Power = 0xbc;
#if APP_COM_DEBUG_FUN==1
			printf("Set_IAP_Mode\r\n");
#endif
			IAP_Timer=0;
			break;
		case MCU_TX_VOLUME:
			buff_array[0]=TurnOn_Volume;	
			length =2;
			break;
#if TUNER_FUNCTION==1
		case MCU_TX_RADIOINFO:
			buff_array[0]=radio_band;
			buff_array[1]=radio_curpreset ;
#if TUNER_TYPE==TDA7703_TUNER
			if(Seek_In_Idle()
				||nEvt->prm==0)
			{
				buff_array[2]=(u8)(radio_freq &0x00ff);
				buff_array[3]=(u8)((radio_freq &0xff00)>>8);
			}
			else
			{
				buff_array[2]=(u8)(nEvt->prm &0x00ff);
				buff_array[3]=(u8)((nEvt->prm &0xff00)>>8);
			}
#elif TUNER_TYPE==MULTIPLE_TUNER
#if MULTIPLE_TUNER_SUBSET==ST_TUNER
			if(MULTIPLE_TUNER_TYPE==TDA7703_TUNER)
			{
				if(Seek_In_Idle()
					||nEvt->prm==0)
				{
					buff_array[2]=(u8)(radio_freq &0x00ff);
					buff_array[3]=(u8)((radio_freq &0xff00)>>8);
				}
				else
				{
					buff_array[2]=(u8)(nEvt->prm &0x00ff);
					buff_array[3]=(u8)((nEvt->prm &0xff00)>>8);
				}
			}
			else
			{
				buff_array[2]=(u8)(radio_freq &0x00ff);
				buff_array[3]=(u8)((radio_freq &0xff00)>>8);
			}
#else
			buff_array[2]=(u8)(radio_freq &0x00ff);
			buff_array[3]=(u8)((radio_freq &0xff00)>>8);
#endif
#else
#if TUNER_TYPE == TDA7708_TUNER
			u8 region;
			u16 min_freq;
			if(radio_band<BAND_AM1)
			{
				if(AREA_OIRT==radio_region&&BAND_FM1==radio_band)
				{
					region=AREA_EASTERN_EUROPE;
				}
				else
				{
					region=radio_region;
				}
				min_freq=FM_Min_Freq[region];
			}
			else
			{
				min_freq=AM_Min_Freq[radio_region];
			}
			if(radio_freq<min_freq)
			{
				return;
			}
#endif
			buff_array[2]=(u8)(radio_freq &0x00ff);
			buff_array[3]=(u8)((radio_freq &0xff00)>>8);			
#endif
			buff_array[4]=AudioFlag.byte;
			buff_array[5]=RadioSeekFlag.byte;
			buff_array[6]=radio_as_count;
			length=7+1;
#if SUPPORT_RDS==1
			if(radio_band<BAND_AM1)
			{
				buff_array[7]=(u8)((RadioRdsInfo.band_info[radio_band].pi&0xFF00)>>8);
				buff_array[8]=(u8)(RadioRdsInfo.band_info[radio_band].pi&0x00FF);
				length=9+1;
			}
#endif
			break;
#ifndef FLASH_SIZE_64K
		case MCU_TX_FAVORLIST:
			{
				u8 preset_index=0;
				u8 buff_index=0;

				for(preset_index=0;preset_index<MAX_BAND_SAVE_PRESET_NUM;preset_index++)
				{
					buff_array[buff_index]=radio_favor_list[radio_band][preset_index];
					buff_index++;
				}
				length=buff_index+1;
			}			
			break;
#endif
		case MCU_TX_FREQLIST:							
			{
				u8 preset_index=0;
				u8 buff_index=0;

				for(preset_index=0;preset_index<MAX_BAND_SAVE_PRESET_NUM;preset_index++)
				{
					buff_array[buff_index]=MSB(radio_memfreq[radio_band][preset_index]);
					buff_index++;
					buff_array[buff_index]=LSB(radio_memfreq[radio_band][preset_index]);
					buff_index++;
				}
#if MODEL== ANDROID_Q133_00||MODEL== ANDROID_Q133_01||MODEL== ANDROID_Q133_uni		
				buff_array[12]=radio_as_count;
				length=preset_index*2+2;//1;
#else			
                length=preset_index*2+1;
#endif					
			}
			break;
		case MCU_TX_RADIO_FREQ_LIST:
			{
				u8 band_index=0;
				u8 preset_index=0;
				u8 buff_index=0;

				for(band_index=0;band_index<MAX_BAND_NUM;band_index++)
				{
					for(preset_index=0;preset_index<MAX_BAND_SAVE_PRESET_NUM;preset_index++)
					{
						buff_array[buff_index]=MSB(radio_memfreq[band_index][preset_index]);
						buff_index++;
						buff_array[buff_index]=LSB(radio_memfreq[band_index][preset_index]);
						buff_index++;
					}
				}
#if MODEL== ANDROID_Q133_00||MODEL== ANDROID_Q133_01||MODEL== ANDROID_Q133_uni||MODEL==ANDROID_129EW_00||MODEL==ANDROID_137E_01
				buff_array[60]=Fm_as_counter;
				buff_array[61]=Am_as_counter;
				length =MAX_BAND_NUM*preset_index*2+3;//1
#elif MODEL==ANDROID_151E_TW
				buff_array[buff_index] = RadioASStruct.FM_AS_counter[RadioASStruct.region_index];
				buff_index++;
				buff_array[buff_index] = RadioASStruct.AM_AS_counter[RadioASStruct.region_index];
				length = MAX_BAND_NUM*preset_index * 2 + 3;
#else
				length =MAX_BAND_NUM*preset_index*2+1;
#endif				
			}
			break;
		case MCU_TX_RADIO_SMETER:
			length=2;
			ptr2=(u8 *)&RadioSmeterDisp;
			break;	
#endif
		case MCU_TX_CMD:
			buff_array[0]=(u8)(nEvt->prm>>8);
			buff_array[1]=(u8)nEvt->prm;
			if(buff_array[0]==UICC_FRONT_SRC)
			{
				buff_array[1]=McuSourceChangeTab[(u8)nEvt->prm];
				buff_array[2]=FrontSourceChild;
				length =4;
			}
#if APP_COM_DEBUG_FUN==1
			else if(buff_array[0]==UICC_SOURCE)
			{
				printf("send UICC_SOURCE\r\n");
			}
#endif	
			else
			{
				length =3;
			}
			break;
		case MCU_TX_CAMERA:
			if(nEvt->prm==OFF)
			{
				F_OS_ReverseAck=0;
				nEvt->prm=Camera_Over;
#if APP_COM_DEBUG_FUN==1
				printf("Tx App Reverse Off\r\n");
#endif
			}
			else
			{
				if(F_OS_ReverseAck==0)
				{
					F_OS_ReverseAck=0; 
				}
				nEvt->prm=Camera_Signal;
#if APP_COM_DEBUG_FUN==1
				printf("Tx App Reverse On\r\n");
#endif
			}
			buff_array[0]=(u8)nEvt->prm;	
			length=2;
			break;
#if DVD_FUNCTION==1
		case MCU_TX_DISC_STATE:
			buff_array[0]=Loader_State;
			length =2;		
			break;
#endif
		case MCU_TX_CLOCK:
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
			buff_array[0] = RTC_TimeInfo.year;
			buff_array[1] = RTC_TimeInfo.month;
			buff_array[2] = RTC_TimeInfo.day;
			buff_array[3] = RTC_TimeInfo.week_day;
			buff_array[4] = RTC_TimeInfo.hours;
			buff_array[5] = RTC_TimeInfo.minutes;
			buff_array[6] = RTC_TimeInfo.seconds;
			length = 7+1;
#else
#if APP_COM_DEBUG_FUN==1
			printf("MCU_TX_CLOCK:%d,%d,%d,%d:%d\r\n",RTC_TimeInfo.year,RTC_TimeInfo.month,RTC_TimeInfo.day,RTC_TimeInfo.hours,RTC_TimeInfo.minutes);
#endif	
			RTC_TimerData=RTC_ConvertTime(RTC_TimeInfo);
			buff_array[0]=(RTC_TimerData&0xFF000000)>>24;
			buff_array[1]=(RTC_TimerData&0x00FF0000)>>16;
			buff_array[2]=(RTC_TimerData&0x0000FF00)>>8;
			buff_array[3]=RTC_TimerData&0x000000FF;
			length =4+1;
#if APP_COM_DEBUG_FUN==1
			printf("MCU_TX_CLOCK HEX:%x,%x,%x,%x\r\n",buff_array[0],buff_array[1],buff_array[2],buff_array[3]);
#endif
#endif
			break;
		case MCU_TX_MCU_VERSION:
#if MCU_SOFTWARE_VERSION_TYPE==1
			length=sizeof(MCU_VERSION);
			Mem_strcpy(buff_array,MCU_VERSION,length);
			length+=1;
#elif MCU_SOFTWARE_VERSION_TYPE==2
			length=sizeof(MCU_VERSION);
			Mem_strcpy(buff_array,MCU_VERSION,length);
			buff_array[length-1]='.';
#ifdef FLASH_SIZE_64K
			buff_array[length]='M';
#elif defined(FLASH_SIZE_256K)
			buff_array[length]='Q';
#else
			buff_array[length]='O';
#endif
#if TUNER_TYPE==TEF6686_TUNER
			buff_array[length+1]='L';
#elif TUNER_TYPE==TEF6657_TUNER
			buff_array[length+1]='A';
#elif TUNER_TYPE==TEF6851_TUNER
			buff_array[length+1]='T';
#elif TUNER_TYPE==TDA7786_TUNER
			buff_array[length+1]='E';
#elif TUNER_TYPE==TDA7708_TUNER
			buff_array[length+1]='S';
#elif TUNER_TYPE==TDA7703_TUNER
			buff_array[length+1]='H';
#elif TUNER_TYPE==SI4745_TUNER
			buff_array[length+1]='W';
#elif TUNER_TYPE==SI4755_TUNER
			buff_array[length+1]='X';
#elif TUNER_TYPE==MULTIPLE_TUNER
			if(MULTIPLE_TUNER_TYPE==TEF6686_TUNER)
			{
				buff_array[length+1]='L';
			}
			else if(MULTIPLE_TUNER_TYPE==TEF6657_TUNER)
			{
				buff_array[length+1]='A';
			}
			else if(MULTIPLE_TUNER_TYPE==TEF6851_TUNER)
			{
				buff_array[length+1]='T';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7786_TUNER)
			{
				buff_array[length+1]='E';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7708_TUNER)
			{
				buff_array[length+1]='S';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7703_TUNER)
			{
				buff_array[length+1]='H';
			}
			else if(MULTIPLE_TUNER_TYPE==SI4745_TUNER)
			{
				buff_array[length+1]='W';
			}
			else if(MULTIPLE_TUNER_TYPE==SI4755_TUNER)
			{
				buff_array[length+1]='X';
			}
#endif
			buff_array[length+2]=0;
			length+=4;
#elif MCU_SOFTWARE_VERSION_TYPE==3
#if PLATFORM_TYPE == REALTEK_RTD1861B_PLATFORM
			buff_array[0]='R';
			buff_array[1]='T';
#else
			//Platform Type,SP:sunplus platform
			buff_array[0]='S';
			buff_array[1]='P';
#endif			
			buff_array[2]='_';
			
			// MCU type, A:AutoChips MCU, H:HDSC MCU
#if defined(AUTOCHIPS_AC781X)
			buff_array[3]='A';
#elif defined(HDSC_HC32F460)||defined(HDSC_HC32L072)||defined(HDSC_HC32F448)
			buff_array[3]='H';
#elif defined(STM32_F103VC)
#if defined(GEEHY_F103_HD)
            		buff_array[3]='G';
#else
            		buff_array[3]='S';
#endif
#elif defined(STM32F401xx)
			buff_array[3]='S';
#endif

			buff_array[4]='_';

			//Software SN,Data and Version
			length=sizeof(MCU_SN_DATA_VERSION);
			Mem_strcpy(&buff_array[5],(u8*)MCU_SN_DATA_VERSION,(length-1));
			
			buff_array[5+length-1]='.';
			
			// MCU sub type
#if defined(AUTOCHIPS_AC781X)
			buff_array[6+length-1]='A';
#elif defined(HDSC_HC32F460)
			buff_array[6+length-1]='A';
#elif defined(HDSC_HC32L072)
			buff_array[6+length-1]='B';
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
			buff_array[6+length-1]='D';
#else
            		buff_array[6+length-1]='A';
#endif
#elif defined(STM32F401xx)
			buff_array[6+length-1]='E';
#elif defined(HDSC_HC32F448)
			buff_array[6+length-1]='C';
#endif

			// MCU Pin num
#if defined(AUTOCHIPS_AC781X)
#if MODEL==LINUX_F018A_21||MODEL==LINUX_K028A_21||MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
			buff_array[7+length-1]='K';
#else
			buff_array[7+length-1]='J';
#endif
#elif defined(HDSC_HC32F460)
			buff_array[7+length-1]='J';
#elif defined(HDSC_HC32L072)
			buff_array[7+length-1]='J';
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
			buff_array[7+length-1]='J';
#else
            		buff_array[7+length-1]='P';
#endif
#elif defined(STM32F401xx)
			buff_array[7+length-1]='J';
#elif defined(HC32F448)
			buff_array[7+length-1]='K';
#endif

			//Flash Size
#if defined(AUTOCHIPS_AC781X)
#ifdef FLASH_SIZE_64K
			buff_array[8+length-1]='M';
#elif defined(FLASH_SIZE_256K)
			buff_array[8+length-1]='Q';
#else
			buff_array[8+length-1]='O';
#endif
#elif defined(HDSC_HC32F460)
			buff_array[8+length-1]='Q';
#elif defined(HDSC_HC32L072)
			buff_array[8+length-1]='O';
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
			buff_array[8+length-1]='O';
#elif MODEL==LINUX_1349W_YS
                buff_array[8+length-1]='S';
#else
            		buff_array[8+length-1]='Q';
#endif
#elif defined(STM32F401xx)
			buff_array[8+length-1]='Q';
#elif defined(HDSC_HC32F448)
			buff_array[8+length-1]='Q';
#endif

			buff_array[9+length-1]='.';

			//Tuner Type
#if TUNER_TYPE==TEF6686_TUNER
			buff_array[10+length-1]='L';
#elif TUNER_TYPE==TEF6657_TUNER
			buff_array[10+length-1]='A';
#elif TUNER_TYPE==TEF6851_TUNER
			buff_array[10+length-1]='T';
#elif TUNER_TYPE==TDA7786_TUNER
			buff_array[10+length-1]='E';
#elif TUNER_TYPE==TDA7708_TUNER
#if ADD_FUNCTION==1
			buff_array[10+length-1]=' ';
			buff_array[11+length-1]='S';
#else
			buff_array[10+length-1]='S';
#endif
#elif TUNER_TYPE==TDA7703_TUNER
			buff_array[10+length-1]='H';
#elif TUNER_TYPE==SI4745_TUNER
			buff_array[10+length-1]='W';
#elif TUNER_TYPE==SI4755_TUNER
			buff_array[10+length-1]='X';
#elif TUNER_TYPE==MULTIPLE_TUNER
			if(MULTIPLE_TUNER_TYPE==TEF6686_TUNER)
			{
				buff_array[10+length-1]='L';
			}
			else if(MULTIPLE_TUNER_TYPE==TEF6657_TUNER)
			{
				buff_array[10+length-1]='A';
			}
			else if(MULTIPLE_TUNER_TYPE==TEF6851_TUNER)
			{
				buff_array[10+length-1]='T';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7786_TUNER)
			{
				buff_array[10+length-1]='E';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7708_TUNER)
			{
				buff_array[10+length-1]='S';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7703_TUNER)
			{
				buff_array[10+length-1]='H';
			}
			else if(MULTIPLE_TUNER_TYPE==SI4745_TUNER)
			{
				buff_array[10+length-1]='W';
			}
			else if(MULTIPLE_TUNER_TYPE==SI4755_TUNER)
			{
				buff_array[10+length-1]='X';
			}
			else
			{
				buff_array[10+length-1]=' ';
			}
#elif TUNER_TYPE==NONE_TUNER
			buff_array[10+length-1]='0';
#endif
#if ADD_FUNCTION==1
			buff_array[12+length-1]=0;
#else
			buff_array[11+length-1]=0;
#endif			
			for(j=0;j<28;j++)
			{
				ver[j]=buff_array[j];
			}
			
			length+=12;
#endif
			ptr2=buff_array;
			break;
#if D_WHEELKEY_STY==1
		case MCU_TX_STEERKEY_STATE:
			{
				u8 tab_index;
				u8 key_index;
				

				tab_index=MSB(nEvt->prm);
				key_index=LSB(nEvt->prm);
				buff_array[0]=STUDY_STEER_KEY_FLAG[0];
				buff_array[1]=STUDY_STEER_KEY_FLAG[1];
				buff_array[2]=STUDY_STEER_KEY_FLAG[2];
				buff_array[3]=STUDY_STEER_KEY_FLAG[3];
				buff_array[4]=tab_index;
				buff_array[5]=STUDY_STEER_KEY_TAB[tab_index][key_index].short_press_key;
				buff_array[6]=MSB(STUDY_STEER_KEY_TAB[tab_index][key_index].large_r_value);
				buff_array[7]=LSB(STUDY_STEER_KEY_TAB[tab_index][key_index].large_r_value);
				buff_array[8]=MSB(STUDY_STEER_KEY_TAB[tab_index][key_index].small_r_value);

				buff_array[9]=LSB(STUDY_STEER_KEY_TAB[tab_index][key_index].small_r_value);				
				ptr2=buff_array;
				length=11;
			}
			break;
#endif
#ifndef FLASH_SIZE_64K
		case MCU_TX_GENSETTING:	
#if TUNER_FUNCTION==1
			buff_array[0] = radio_region;
#else
			buff_array[0] = 0;
#endif
#if ENABLE_SECURITY_CODE==1
			buff_array[1] =PasswordFlag.byte;
#else
			buff_array[1] =0;
#endif
#if MODEL==ANDROID_151E_TW
			buff_array[2] = MSB(FM_Min_Freq[radio_region]);
			buff_array[3] = LSB(FM_Min_Freq[radio_region]);
			buff_array[4] = MSB(FM_Max_Freq[radio_region]);
			buff_array[5] = LSB(FM_Max_Freq[radio_region]);
			buff_array[6] = FM_FreqStep[radio_region];
			buff_array[7] = MSB(AM_Min_Freq[radio_region]);
			buff_array[8] = LSB(AM_Min_Freq[radio_region]);
			buff_array[9] = MSB(AM_Max_Freq[radio_region]);
			buff_array[10] = LSB(AM_Max_Freq[radio_region]);
			buff_array[11] = AM_FreqStep[radio_region];
			length=13;
#else
			length=3;
#endif
			break;
#endif
		case MCU_TX_MACHINE_MISC_STATE:
			length=3;
			buff_array[0]=(u8)(nEvt->prm>>8);
			buff_array[1]=(u8)nEvt->prm;
			break;
#if 0
		case MCU_TX_PASSWORDSETTING:
			buff_array[0]=nEvt->prm;
			length=1+1;
			break;
		case MCU_TX_APP_UI_TYPE:
			buff_array[0]=App_UIType;
			length=1+1;
			break;
#endif
#if PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
		case MCU_TX_CAN_BOX_INFO:
			buff_array[0]=MOTORCYCLE_MESSAGE_HEAD_CODE;
			buff_array[1]=nEvt->prm;
			switch(nEvt->prm)
			{
				case MOTORCYCLE_BASIC_INFO:
					buff_array[2]=0x06;
					buff_array[3]=MSB(EngineSpeed);
					buff_array[4]=LSB(EngineSpeed);
					buff_array[5]=MotorCycleSpeed;
					buff_array[6]=FuelOilValue;
					buff_array[7]=TemperatureValue;
					buff_array[8]=BatteryVoltage;
					buff_array[9]=0;
					
					length=11;
					break;
				case MOTORCYCLE_STATUS_INFO:
					buff_array[2]=0x03;

					buff_array[3]=0;
					if(F_LEFT_LAMP)
					{
						buff_array[3]|=0x01;
					}
					if(F_RIGHT_LAMP)
					{
						buff_array[3]|=0x02;
					}
					if(F_HIGH_BEAM)
					{
						buff_array[3]|=0x04;
					}
					
					buff_array[4]=0;
					if(F_ENGINE_TROUBLE)
					{
						buff_array[4]|=0x01;
					}
					if(F_ABS_TROUBLE)
					{
						buff_array[4]|=0x02;
					}
					if(F_OIL_TROUBLE)
					{
						buff_array[4]|=0x04;
					}
					buff_array[5]=F_LIGHT_STATUS;
					buff_array[6]=0;

					length=8;
					break;
				default:
					length=0;
					break;
			}
			break;
#endif
#if CAN_ADAPTER==1||CAN_FUNCTION==1
		case MCU_TX_CAN_BOX_INFO:
			{
				u16 can_buff_length;
				(*pCanFunMain[CurSelCanBoxModel].tx_app_pro)(nEvt->prm,buff_array,&can_buff_length);  
				length=can_buff_length+1;
			}
			break;
#endif
#if AM_688_UART_FUN==1
  #if MODEL==LINUX_1297WS_65HSE
    case MCU_TX_CAN_BOX_INFO:
	#else
    case MCU_TX_SMART_LOCK:
  #endif
			buff_array[0]=door_tx_buffer[0];
			buff_array[1]=door_tx_buffer[1];
			buff_array[2]=door_tx_buffer[2];	
			buff_array[3]=door_tx_buffer[3];
			buff_array[4]=door_tx_buffer[4];
			buff_array[5]=door_tx_buffer[5];
			buff_array[6]=door_tx_buffer[6];
			buff_array[7]=door_tx_buffer[7];
			length=9;
		break;
#endif
#if RADAR_HAIMA_S7_FUN==1
		case MCU_TX_RADAR_HAIMA_S7:
			buff_array[0]=nEvt->prm;
		  buff_array[1]=radar_info[0][nEvt->prm&0x0f];
			buff_array[2]=radar_info[1][nEvt->prm&0x0f];
		  length=4;
			break;
#endif
#if 0
		case MCU_TX_APP_TEST_MODE_INFO:	
#if TUNER_TYPE==MULTIPLE_TUNER
#if MULTIPLE_TUNER_SUBSET==NXP_TUNER
			if(MULTIPLE_TUNER_TYPE==TEF6686_TUNER
				||MULTIPLE_TUNER_TYPE==TEF6657_TUNER
				||MULTIPLE_TUNER_TYPE==TEF6851_TUNER)
			{
				length=sizeof(TunerTestItem_TEF6686);
				Mem_strcpy(&buff_array[0],&TunerTestItem_TEF6686.data[0],length);
			}
#else
			if(MULTIPLE_TUNER_TYPE==TDA7786_TUNER)
			{
				length=sizeof(TunerTestItem_TDA7786);
				Mem_strcpy(&buff_array[0],&TunerTestItem_TDA7786.data[0],length);
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7708_TUNER)
			{
				length=sizeof(TunerTestItem_TDA7708);
				Mem_strcpy(&buff_array[0],&TunerTestItem_TDA7708.data[0],length);
			}
#if ST_TUNER_INCLUDE_TDA7703==1			
			else if(MULTIPLE_TUNER_TYPE==TDA7703_TUNER)
			{
				length=sizeof(TunerTestItem_TDA7703);
				Mem_strcpy(&buff_array[0],&TunerTestItem_TDA7703.data[0],length);
			}
#endif
#endif
#else
			length=sizeof(TunerTestItem);
			Mem_strcpy(&buff_array[0],&TunerTestItem.data[0],length);
#endif
			length+=1;
			break;
#endif
#if SUPPORT_RDS==1
		case  MCU_TX_RDS_INFO:
			buff_array[0]=MSB(RDSDIspIconInfo.word);
			buff_array[1]=LSB(RDSDIspIconInfo.word);
			length=sizeof(RDSDIspIconInfo)+1;
			break;
		case  MCU_TX_RDS_PTY:
			buff_array[0]=RadioRdsInfo.PTY;
			buff_array[1]=RDS_UserSelectedPTY;
			length=3;
			break;
		case MCU_TX_RDS_PS:
#if MODEL==ANDROID_Q133_00||MODEL==ANDROID_Q133_01||MODEL== ANDROID_Q133_uni			
			Mem_strcpy(buff_array,&RadioRdsInfo.band_info[radio_band].ps[0],16);
			length=14+1;
#else
			Mem_strcpy(buff_array,&RadioRdsInfo.band_info[radio_band].ps[0],8);
			length=8+1;
#endif		
			break;
		case MCU_TX_RDS_RT	:
			ptr2=(u8 *)&RadioRdsInfo.RT[0];
			length=sizeof(RadioRdsInfo.RT)+1;
			break;
		case MCU_TX_RDS_PI:
			if(radio_band<BAND_AM1)
			{
				buff_array[0]=MSB(RadioRdsInfo.band_info[radio_band].pi);
				buff_array[1]=LSB(RadioRdsInfo.band_info[radio_band].pi);
				for(j=0;j<MAX_BAND_SAVE_PRESET_NUM;j++)
				{
					buff_array[((j+1)*2)]=MSB(RadioRdsInfo.preset_info[radio_band][j].pi);
					buff_array[((j+1)*2+1)]=LSB(RadioRdsInfo.preset_info[radio_band][j].pi);					
				}
				length=j*2+2+1;
			}
			else
			{
				length=0;
			}
			break;
		case MCU_TX_APP_RDS_AUDIO:
			buff_array[0]=(u8)(nEvt->prm>>8);
			buff_array[1]=(u8)nEvt->prm;
			length=2+1;
			break;
		case MCU_TX_PSNAME_LIST:
			{
				u8 preset_index=0;
				u8 counter=0;
				u8 num=0;
				u8 *ps_list;

				if(radio_band<BAND_AM1)
				{		
					counter=0;
					for(preset_index=0;preset_index<MAX_BAND_SAVE_PRESET_NUM;preset_index++)
					{
						ps_list=&RadioRdsInfo.preset_info[radio_band][preset_index].ps[0];
						for(num=0;num<8;num++)
						{
							buff_array[counter]=*ps_list;
							ps_list++;
							counter++;				
						}
					}
					length=preset_index*8+1;
				}
				else
				{
					length=0;
				}
			}
			break;
		case MCU_TX_RADIO_PS_NAME_LIST:
			{
				u8 preset_index=0;
				u8 counter=0;
				u8 num=0;
				u8 *ps_list;
				u8 band_index=0;

				if(radio_band<BAND_AM1)
				{		
					counter=0;
					for(band_index=0;band_index<FM_BAND_NUM;band_index++)
					{
						for(preset_index=0;preset_index<MAX_BAND_SAVE_PRESET_NUM;preset_index++)
						{
							ps_list=&RadioRdsInfo.preset_info[band_index][preset_index].ps[0];
							for(num=0;num<8;num++)
							{
								buff_array[counter]=*ps_list;
								ps_list++;
								counter++;				
							}
						}
					}
					length=FM_BAND_NUM*preset_index*8+1;
				}
				else
				{
					length=0;
				}
			}
			break;
		case MCU_TX_APP_RDS_AF_LIST:
			if(radio_band<BAND_AM1)
			{
				for(j=0;j<25;j++)
				{
					buff_array[j]=RadioRdsInfo.band_info[radio_band].af_freq[j];
				}
				length=26;
			}
			break;
		case MCU_TX_RDS_TIME:
			buff_array[0]=Clock.hour;
			buff_array[1]=Clock.min;
			buff_array[2]=Clock.offset;
			buff_array[3]=((Clock.mjd&0xFF000000)>>24);
			buff_array[4]=((Clock.mjd&0x00FF0000)>>16);
			buff_array[5]=((Clock.mjd&0x0000FF00)>>8);
			buff_array[6]=(Clock.mjd&0x000000FF);
			length=8;
			break;
#endif
#if UUID_FUNCTION==1
		case MCU_TX_UUID_DATA:
			if(IsUUID_CodeExist())
			{
				buff_array[0]=UUID_Code[0];
				buff_array[1]=UUID_Code[1];
				buff_array[2]=UUID_Code[2];	
				buff_array[3]=UUID_Code[3];
				buff_array[4]=UUID_Code[4];
				buff_array[5]=UUID_Code[5];
				buff_array[6]=UUID_Code[6];
				buff_array[7]=UUID_Code[7];
				length=9;
			}
			else
			{
				length=1;
			}
			break;
#endif
#if DUAL_DAB_FUN==1
		case MCU_TX_DAB_LIST:
			{
				u8 list_counter;
				u8 programe_index=(u8)nEvt->prm;
				
				if(programe_index<MAX_KS_PROGRAM_NUM)
				{
					buff_array[0]=MSB(KeyStonePlayList.program_data[programe_index].index);
					buff_array[1]=LSB(KeyStonePlayList.program_data[programe_index].index);
					buff_array[2]=KeyStonePlayList.program_data[programe_index].frequence;
					buff_array[3]=KeyStonePlayList.program_data[programe_index].sc_id;
					buff_array[4]=KeyStonePlayList.program_data[programe_index].service_id>>24;
					buff_array[5]=KeyStonePlayList.program_data[programe_index].service_id>>16;
					buff_array[6]=KeyStonePlayList.program_data[programe_index].service_id>>8;
					buff_array[7]=KeyStonePlayList.program_data[programe_index].service_id;
					buff_array[8]=MSB(KeyStonePlayList.program_data[programe_index].ensemble_id);
					buff_array[9]=LSB(KeyStonePlayList.program_data[programe_index].ensemble_id);
					buff_array[10]=KeyStonePlayList.program_data[programe_index].program_type;
					for(list_counter=0;list_counter<34;list_counter++)
					{
						buff_array[list_counter+11]=KeyStonePlayList.program_data[programe_index].ensemble_name[list_counter];
					}
					for(list_counter=0;list_counter<34;list_counter++)
					{
						buff_array[list_counter+45]=KeyStonePlayList.program_data[programe_index].program_name[list_counter];
					}
					length=80;
#if APP_COM_DEBUG_FUN==1
					printf("DAB Tx list %x\r\n",programe_index);
#endif	
				}
			}
			break;
		case MCU_TX_DAB_CUR_INFO:
			{
				u8 cur_counter;
				
				buff_array[0]=MSB(KS_PlayInfo.index);
				buff_array[1]=LSB(KS_PlayInfo.index);
				buff_array[2]=KS_PlayInfo.frequence;
				buff_array[3]=KS_PlayInfo.sc_id;
				buff_array[4]=KS_PlayInfo.service_id>>24;
				buff_array[5]=KS_PlayInfo.service_id>>16;
				buff_array[6]=KS_PlayInfo.service_id>>8;
				buff_array[7]=KS_PlayInfo.service_id;
				buff_array[8]=MSB(KS_PlayInfo.ensemble_id);
				buff_array[9]=LSB(KS_PlayInfo.ensemble_id);
				buff_array[10]=KS_PlayInfo.program_type;
				for(cur_counter=0;cur_counter<34;cur_counter++)
				{
					buff_array[cur_counter+11]=KS_PlayInfo.ensemble_name[cur_counter];
				}
				for(cur_counter=0;cur_counter<34;cur_counter++)
				{
					buff_array[cur_counter+45]=KS_PlayInfo.program_name[cur_counter];
				}
				length=80;
#if APP_COM_DEBUG_FUN==1
				printf("DAB Tx current info\r\n");
#endif	
			}
			break;
		case MCU_TX_DAB_TEXT:
			{
				u16 text_counter;
				
				for(text_counter=0;text_counter<258;text_counter++)
				{
					buff_array[text_counter]=KS_PlayInfo.program_text[text_counter];
				}
				length=241;
			}
			break;
		case MCU_TX_DAB_SEARCH_INFO:
			{
				u8 dab_search_type=(u8)nEvt->prm;
				u16 search_temp;

				buff_array[0]=dab_search_type;
				switch(dab_search_type)
				{
					case 0x00:
					case 0x01:
					case 0x03:
						buff_array[1]=0x00;
						buff_array[2]=0x00;
						length=4;
#if APP_COM_DEBUG_FUN==1
						printf("Tx DAB search info %x\r\n",dab_search_type);
#endif	
						break;
					case 0x02:
						search_temp=KS_CurrentInfo[keyStoneSubDAB].search_frequence;
						search_temp=(search_temp*100)/40;
						buff_array[1]=(u8)search_temp;
						buff_array[2]=KS_CurrentInfo[keyStoneSubDAB].search_program_num;
						length=4;
#if APP_COM_DEBUG_FUN==1
						printf("Tx DAB search info %x:%x,%x\r\n",dab_search_type,buff_array[1],buff_array[2]);
#endif	
						break;
					default:
						break;
				}
			}
			break;
		case MCU_TX_DAB_MOT_INFO:
			{
				u8 mot_data_length;
				u8 mot_data_counter;
				u8 mot_data_buffer[MAX_KS_MOT_DATA_LENGTH];

				KS_GetMotEvent(mot_data_buffer,&mot_data_length);
				
				if(mot_data_length)
				{
					length=mot_data_length+1;	
					if(KS_CMD_HEADER==mot_data_buffer[0]
						&&KS_CMD_TAIL==mot_data_buffer[mot_data_length-1])
					{
#if APP_COM_DEBUG_FUN==1
						u16 segment_number=0;
						u16 transport_id=0;
						u16 packet_number=0;
						if(0x03==mot_data_buffer[1]
							&&0x00==mot_data_buffer[2])
						{
							segment_number=mot_data_buffer[7];
							segment_number<<=8;
							segment_number+=mot_data_buffer[8];
							
							transport_id=mot_data_buffer[9];
							transport_id<<=8;
							transport_id+=mot_data_buffer[10];
							
							packet_number=mot_data_buffer[11];
							printf("Tx S=%x,T=%x,P=%x\r\n",segment_number,transport_id,packet_number);
						}
#endif
						for(mot_data_counter=0;mot_data_counter<mot_data_length;mot_data_counter++)
						{
							buff_array[mot_data_counter]=mot_data_buffer[mot_data_counter];
						}
					}
					else
					{
						length=0;
#if APP_COM_DEBUG_FUN==1
						printf("MOT Data Error!!!!\r\n");
#endif
					}
				}
			}
			break;
		case MCU_TX_DAB_TPEG_INFO:
			{
				u8 tpeg_data_length;
				u8 tpeg_data_counter;
				u8 tpeg_data_buffer[MAX_KS_TPEG_DATA_LENGTH];

				KS_GetTpegEvent(tpeg_data_buffer,&tpeg_data_length);
				
				if(tpeg_data_length)
				{
					length=tpeg_data_length+1;	
					if(KS_CMD_HEADER==tpeg_data_buffer[0]
						&&KS_CMD_TAIL==tpeg_data_buffer[tpeg_data_length-1])
					{
						for(tpeg_data_counter=0;tpeg_data_counter<tpeg_data_length;tpeg_data_counter++)
						{
							buff_array[tpeg_data_counter]=tpeg_data_buffer[tpeg_data_counter];
						}
					}
					else
					{
						length=0;
#if APP_COM_DEBUG_FUN==1
						printf("TPEG Data Error!!!!\r\n");
#endif
					}
				}
			}
			break;
		case MCU_TX_DAB_VERSION_INFO:
			{
				u8 version_counter;
				u8 data_counter=0;

				for(version_counter=0;version_counter<MAX_KS_VERSION_LENGTH;version_counter++)
				{
					buff_array[data_counter]=KS_Version[keyStoneMainDAB][version_counter];
					data_counter++;
				}
				for(version_counter=0;version_counter<MAX_KS_VERSION_LENGTH;version_counter++)
				{
					buff_array[data_counter]=KS_Version[keyStoneSubDAB][version_counter];
					data_counter++;
				}	
				length=MAX_KS_VERSION_LENGTH*2+1;
			}
			break;
		case MCU_TX_DAB_SIGNAL:
			buff_array[0]=MSB(nEvt->prm);
			buff_array[1]=LSB(nEvt->prm);
			buff_array[2]=KS_CurrentInfo[keyStoneMainDAB].status;
			buff_array[3]=KS_CurrentInfo[keyStoneMainDAB].volume;
			length=5;
			break;
		case MCU_TX_DAB_SF_INFO:
			buff_array[0]=LSB(nEvt->prm);
			if(LSB(nEvt->prm)==1)
			{
				buff_array[1]=KS_PlayInfo.frequence;
				buff_array[2]=MSB(KS_PlayInfo.ensemble_id);
				buff_array[3]=LSB(KS_PlayInfo.ensemble_id);
				buff_array[4]=KS_PlayInfo.service_id>>24;
				buff_array[5]=KS_PlayInfo.service_id>>16;
				buff_array[6]=KS_PlayInfo.service_id>>8;
				buff_array[7]=KS_PlayInfo.service_id;
				buff_array[8]=KS_CurrentInfo[keyStoneSubDAB].signal_quality;	
				buff_array[9]=KS_CurrentInfo[keyStoneSubDAB].signal_rssi;	
			}
			else
			{
				buff_array[1]=KeyStoneSFListBak.frequence;
				buff_array[2]=MSB(KeyStoneSFListBak.ensemble_id);
				buff_array[3]=LSB(KeyStoneSFListBak.ensemble_id);
				buff_array[4]=KeyStoneSFListBak.service_id>>24;
				buff_array[5]=KeyStoneSFListBak.service_id>>16;
				buff_array[6]=KeyStoneSFListBak.service_id>>8;
				buff_array[7]=KeyStoneSFListBak.service_id;
				buff_array[8]=KeyStoneSFListBak.signal_quality;	
				buff_array[9]=KeyStoneSFListBak.signal_rssi;	
			}
			for(j=0;j<5;j++)
			{
				buff_array[10+j]=0;
			}			
			for(j=0;j<5&&j<KS_SF_FreqListNum;j++)
			{
				buff_array[10+j]=KS_SF_FreqList[j];
			}			
			length=16;
			break;
		case MCU_TX_DAB_REFERESH_STATE:
			buff_array[0]=MSB(nEvt->prm);
			buff_array[1]=LSB(nEvt->prm);
			length=3;
			break;
		case MCU_TX_DAB_TEST_MODE_INFO:
			buff_array[0]=nEvt->prm;
			if(buff_array[0])
			{
				buff_array[1]=0;
				buff_array[2]=0;
			}
			else
			{
				buff_array[1]=keyStoneMainDAB;
				buff_array[2]=keyStoneSubDAB;
			}
			length=4;
			break;
		case MCU_TX_DAB_MOT_ERROR:
			buff_array[0]=0;
			length=2;
			break;
		case MCU_TX_DAB_CLOCK:
			buff_array[0]=0xFE;
			buff_array[1]=KS_RTC_CMD;
			buff_array[2]=CMD_RTC_GetClock;
			buff_array[3]=0x00;
			buff_array[4]=0x00;
			buff_array[5]=0x07;
			buff_array[6]=KS_Clock.second;
			buff_array[7]=KS_Clock.min;
			buff_array[8]=KS_Clock.hour;
			buff_array[9]=KS_Clock.day;
			buff_array[10]=KS_Clock.week;
			buff_array[11]=KS_Clock.month;
			buff_array[12]=KS_Clock.year;
			buff_array[13]=0xFD;
			length=15;
			break;
		case MCU_TX_DAB_TPEG_STATE_INFO:
			buff_array[0]=KS_TpegUpdateDataBak.country_code[0];
			buff_array[1]=KS_TpegUpdateDataBak.country_code[1];
			buff_array[2]=KS_TpegUpdateDataBak.country_code[2];
			buff_array[3]=KS_TpegUpdateDataBak.status;
			buff_array[4]=KS_TpegUpdateDataBak.freq_index;
			buff_array[5]=KS_TpegUpdateDataBak.ecc;
			buff_array[6]=MSB(KS_TpegUpdateDataBak.eid);
			buff_array[7]=LSB(KS_TpegUpdateDataBak.eid);
			buff_array[8]=((KS_TpegUpdateDataBak.sid&0xFF000000)>>24);
			buff_array[9]=((KS_TpegUpdateDataBak.sid&0x00FF0000)>>16);
			buff_array[10]=((KS_TpegUpdateDataBak.sid&0x0000FF00)>>8);
			buff_array[11]=(KS_TpegUpdateDataBak.sid&0x000000FF);
			buff_array[12]=KS_TpegUpdateDataBak.quality;
			buff_array[13]=KS_TpegUpdateDataBak.rssi;
			buff_array[14]=KS_TpegUpdateDataBak.tpeg_type;
			buff_array[15]=KS_TpegSettingInfo.flag;
			length=17;
			break;
		case MCU_TX_DAB_ECC_INFO:
			buff_array[0]=KS_PlayInfo.ecc;
			buff_array[1]=KS_PlayInfo.country_id;
			buff_array[2]=MSB(KS_PlayInfo.ensemble_id);
			buff_array[3]=LSB(KS_PlayInfo.ensemble_id);
			buff_array[4]=KS_PlayInfo.service_id>>24;
			buff_array[5]=KS_PlayInfo.service_id>>16;
			buff_array[6]=KS_PlayInfo.service_id>>8;
			buff_array[7]=KS_PlayInfo.service_id;
			length=9;
			break;
#endif
#if DAB_UPDATE_FUN==1
		case MCU_TX_DAB_UPDATE_CMD:
			buff_array[0]=1;
			length=2;
			F_KS_UPDATE_REQ=1;
			break;
#endif
#if FACTORY_AUTO_TEST_FUN==1
		case MCU_TX_VERSION_REQ:
			buff_array[0]=MSB(nEvt->prm);
			buff_array[1]=LSB(nEvt->prm);
			length=3;
			break;
		case MCU_TX_BT_TEST_CMD:
			length=8;
			FormatMemery(buff_array,sizeof(buff_array));
			buff_array[0]=nEvt->prm;
			switch(nEvt->prm)
			{
				case AT_BT_CMD_CONNECT:
					buff_array[1]=AutoTestBTAddr[0];
					buff_array[2]=AutoTestBTAddr[1];
					buff_array[3]=AutoTestBTAddr[2];
					buff_array[4]=AutoTestBTAddr[3];
					buff_array[5]=AutoTestBTAddr[4];
					buff_array[6]=AutoTestBTAddr[5];
					break;
				case AT_BT_CMD_DISCONNECT:
				case AT_BT_CMD_HUNGUP:
				case AT_BT_CMD_DIAL_MENU:
				case AT_BT_CMD_A2DP_MENU:
				case AT_BT_CMD_OPEN_INTERNAL_MIC:
				case AT_BT_CMD_OPEN_EXTERNAL_MIC:
					break;
				case AT_BT_CMD_CHECK_ADDRESS:
					buff_array[1]=AutoTestBTCheckAddr[0];
					buff_array[2]=AutoTestBTCheckAddr[1];
					buff_array[3]=AutoTestBTCheckAddr[2];
					buff_array[4]=AutoTestBTCheckAddr[3];
					buff_array[5]=AutoTestBTCheckAddr[4];
					buff_array[6]=AutoTestBTCheckAddr[5];
					break;
				default:
					length=0;
					break;
			}
			break;
		case MCU_TX_WIFI_TEST_CMD:
			length=PARAM_LENGTH+2;
			buff_array[0]=nEvt->prm;
			switch(nEvt->prm)
			{
				case AT_InternetWifi_CMD_CLOSE_INTERNET:
				case AT_InternetWifi_CMD_OPEN_INTERNET:
				case AT_InternetWifi_CMD_CLOSE_WIFI:
				case AT_InternetWifi_CMD_OPEN_WIFI:
				case AT_InternetWifi_CMD_CONNECT_WIFI:
					break;
				case AT_InternetWifi_CMD_IP:
					for(j=0;j<PARAM_LENGTH;j++)
				  {
						buff_array[j]=AutoTestIP_Addr[j];
					}
					break;
				case AT_InternetWifi_CMD_SSID:
				case AT_InternetWifi_CMD_PASSWORD:
					break;
				default :
					length=0;
					break;
			}
		  break;
		case MCU_TX_SCREEN_TEST_CMD:
			length=3;
			buff_array[0]=nEvt->prm;
		  buff_array[1]=SCREEN_SUB_COMMAND;
		  break;
		case MCU_TX_AUTO_TEST_CMD:
			length=3;
			buff_array[0]=(nEvt->prm)>>8;
			buff_array[1]=(nEvt->prm)&0xFF;
			//buff_array[2]=MSB(nEvt->prm);
			switch(buff_array[0])
			{
				case 0x01:
					switch(buff_array[1])
					{
						case 0x05:
							buff_array[2]=AutoAscii2Hex(AutoTestRxBuffer[7]);
							length++;
							break;
						case 0x06:
							buff_array[2]=AutoAscii2Hex(AutoTestRxBuffer[7]);
							length++;
							break;
						default :
							break;
					}
				case 0x03:
					switch(buff_array[1])
					{
						case 0x00:
							for(int i = 0;i<12;i++)
							{
								buff_array[2+i] = AutoTestRxBuffer[7+i];
								length++;
							}
						break;
						case 0x03:
							for(int i = 0;i<13;i++)
							{
								buff_array[2+i] = AutoTestRxBuffer[7+i];
								length++;
							}
						break;
					}
					break;
				default:
					break;
			}
			break;
/*
		case MCU_TX_AUTO_START_CMD:
			length=1;
			break;
		case MCU_TX_FACTORY_RESET_CMD:
			length=1;
			break;
*/
#endif
#if DUAL_SIM_FUN==1
		case MCU_TX_DUAL_SIM_DATA:
			if(nEvt->prm==SIM_CMD_STEERING_WHEEL)
			{
				buff_array[0]=DualSimData.steering_wheel[0];
				buff_array[1]=DualSimData.steering_wheel[1];
				buff_array[2]=DualSimData.steering_wheel[2];
				buff_array[3]=DualSimData.steering_wheel[3];
				buff_array[4]=DualSimData.steering_wheel[4];
				buff_array[5]=DualSimData.steering_wheel[5];
				buff_array[6]=DualSimData.steering_wheel[6];
				length=8;
			}
			else if(nEvt->prm==SIM_CMD_BSD)
			{
				buff_array[0]=DualSimData.bsd[0];
				buff_array[1]=DualSimData.bsd[1];
				buff_array[2]=DualSimData.bsd[2];
				buff_array[3]=DualSimData.bsd[3];
				buff_array[4]=DualSimData.bsd[4];
				buff_array[5]=DualSimData.bsd[5];
				length=7;
			}
			else if(nEvt->prm==SIM_CMD_CAMERA)
			{
				buff_array[0]=DualSimData.camera[0];
				buff_array[1]=DualSimData.camera[1];
				buff_array[2]=DualSimData.camera[2];
				buff_array[3]=DualSimData.camera[3];
				buff_array[4]=DualSimData.camera[4];
				length=6;
			}
			else if(nEvt->prm==SIM_CMD_SPEED_RPM)
			{
				buff_array[0]=DualSimData.speed_rpm[0];
				buff_array[1]=DualSimData.speed_rpm[1];
				buff_array[2]=DualSimData.speed_rpm[2];
				buff_array[3]=DualSimData.speed_rpm[3];
				buff_array[4]=DualSimData.speed_rpm[4];
				buff_array[5]=DualSimData.speed_rpm[5];
				length=7;
			}
			break;
#endif
#if DUAL_SIM2_FUN==1
		case MCU_TX_DUAL_SIM_DATA:
			if(nEvt->prm==SIM_CMD_STEERING_WHEEL)
			{
				buff_array[0]=DualSimData.steering_wheel[0];
				buff_array[1]=DualSimData.steering_wheel[1];
				buff_array[2]=DualSimData.steering_wheel[2];
				buff_array[3]=DualSimData.steering_wheel[3];
				buff_array[4]=DualSimData.steering_wheel[4];
				buff_array[5]=DualSimData.steering_wheel[5];
				buff_array[6]=DualSimData.steering_wheel[6];
				length=8;
			}
			else if(nEvt->prm==SIM_CMD_BSD_WARNING)
			{
				buff_array[0]=DualSimData.bsd_warning[0];
				buff_array[1]=DualSimData.bsd_warning[1];
				buff_array[2]=DualSimData.bsd_warning[2];
				buff_array[3]=DualSimData.bsd_warning[3];
				buff_array[4]=DualSimData.bsd_warning[4];
				buff_array[5]=DualSimData.bsd_warning[5];
				buff_array[6]=DualSimData.bsd_warning[6];
				length=8;
			}
			else if(nEvt->prm==SIM_CMD_BSD_FAULT)
			{
				buff_array[0]=DualSimData.bsd_fault[0];
				buff_array[1]=DualSimData.bsd_fault[1];
				buff_array[2]=DualSimData.bsd_fault[2];
				buff_array[3]=DualSimData.bsd_fault[3];
				buff_array[4]=DualSimData.bsd_fault[4];
				length=6;
			}
			else if(nEvt->prm==SIM_CMD_BSD_SENSOR)
			{
				buff_array[0]=DualSimData.bsd_sensor[0];
				buff_array[1]=DualSimData.bsd_sensor[1];
				buff_array[2]=DualSimData.bsd_sensor[2];
				buff_array[3]=DualSimData.bsd_sensor[3];
				buff_array[4]=DualSimData.bsd_sensor[4];
				length=6;
			}
			else if(nEvt->prm==SIM_CMD_BSD_DISTANCE)
			{
				buff_array[0]=DualSimData.bsd_distance[0];
				buff_array[1]=DualSimData.bsd_distance[1];
				buff_array[2]=DualSimData.bsd_distance[2];
				buff_array[3]=DualSimData.bsd_distance[3];
				buff_array[4]=DualSimData.bsd_distance[4];
				buff_array[5]=DualSimData.bsd_distance[5];
				buff_array[6]=DualSimData.bsd_distance[6];
				buff_array[7]=DualSimData.bsd_distance[7];
				buff_array[8]=DualSimData.bsd_distance[8];
				buff_array[9]=DualSimData.bsd_distance[9];
				buff_array[10]=DualSimData.bsd_distance[10];
				buff_array[11]=DualSimData.bsd_distance[11];
				length=13;
			}
			else if(nEvt->prm==SIM_CMD_BSD_TPMS)
			{
				u32 tpms_counter;
				
				for(tpms_counter=0;tpms_counter<SIM_TPMS_DATA_LENGTH;tpms_counter++)
				{
					buff_array[tpms_counter]=DualSimData.tpms[tpms_counter];
				}
				length=SIM_TPMS_DATA_LENGTH+1;
			}
			else if(nEvt->prm==SIM_CMD_AGS_DRR)
			{
				buff_array[0]=DualSimData.ags_data_req_response[0];
				buff_array[1]=DualSimData.ags_data_req_response[1];
				buff_array[2]=DualSimData.ags_data_req_response[2];
				buff_array[3]=DualSimData.ags_data_req_response[3];
				buff_array[4]=DualSimData.ags_data_req_response[4];
				length=6;
			}
			else if(nEvt->prm==SIM_CMD_AGS_CR)
			{
				buff_array[0]=DualSimData.ags_ctrl_response[0];
				buff_array[1]=DualSimData.ags_ctrl_response[1];
				buff_array[2]=DualSimData.ags_ctrl_response[2];
				buff_array[3]=DualSimData.ags_ctrl_response[3];
				buff_array[4]=DualSimData.ags_ctrl_response[4];
				length=6;
			}
			else if(nEvt->prm==SIM_CMD_AGS_DISP)
			{
				buff_array[0]=DualSimData.ags_disp[0];
				buff_array[1]=DualSimData.ags_disp[1];
				buff_array[2]=DualSimData.ags_disp[2];
				buff_array[3]=DualSimData.ags_disp[3];
				buff_array[4]=DualSimData.ags_disp[4];
				buff_array[5]=DualSimData.ags_disp[5];
				buff_array[6]=DualSimData.ags_disp[6];
				buff_array[7]=DualSimData.ags_disp[7];
				buff_array[8]=DualSimData.ags_disp[8];
				buff_array[9]=DualSimData.ags_disp[9];
				buff_array[10]=DualSimData.ags_disp[10];
				length=12;
			}
			else if(nEvt->prm==SIM_CMD_AGS_CVG)
			{
				buff_array[0]=DualSimData.ags_ctrl_value_get[0];
				buff_array[1]=DualSimData.ags_ctrl_value_get[1];
				buff_array[2]=DualSimData.ags_ctrl_value_get[2];
				buff_array[3]=DualSimData.ags_ctrl_value_get[3];
				buff_array[4]=DualSimData.ags_ctrl_value_get[4];
				buff_array[5]=DualSimData.ags_ctrl_value_get[5];
				buff_array[6]=DualSimData.ags_ctrl_value_get[6];
				buff_array[7]=DualSimData.ags_ctrl_value_get[7];
				buff_array[8]=DualSimData.ags_ctrl_value_get[8];
				buff_array[9]=DualSimData.ags_ctrl_value_get[9];
				buff_array[10]=DualSimData.ags_ctrl_value_get[10];
				buff_array[11]=DualSimData.ags_ctrl_value_get[11];
				buff_array[12]=DualSimData.ags_ctrl_value_get[12];
				buff_array[13]=DualSimData.ags_ctrl_value_get[13];
				length=15;
			}
			else if(nEvt->prm==SIM_CMD_AGS_RR)
			{
				buff_array[0]=DualSimData.ags_reset_resp[0];
				buff_array[1]=DualSimData.ags_reset_resp[1];
				buff_array[2]=DualSimData.ags_reset_resp[2];
				buff_array[3]=DualSimData.ags_reset_resp[3];
				buff_array[4]=DualSimData.ags_reset_resp[4];
				length=6;
			}
			else if(nEvt->prm==SIM_CMD_AGS_MCR)
			{
				buff_array[0]=DualSimData.ags_manual_ctrl_resp[0];
				buff_array[1]=DualSimData.ags_manual_ctrl_resp[1];
				buff_array[2]=DualSimData.ags_manual_ctrl_resp[2];
				buff_array[3]=DualSimData.ags_manual_ctrl_resp[3];
				buff_array[4]=DualSimData.ags_manual_ctrl_resp[4];
				length=6;
			}
			else if(nEvt->prm==SIM_CMD_RV_DISP)
			{
				buff_array[0]=DualSimData.rv_display[0];
				buff_array[1]=DualSimData.rv_display[1];
				buff_array[2]=DualSimData.rv_display[2];
				buff_array[3]=DualSimData.rv_display[3];
				buff_array[4]=DualSimData.rv_display[4];
				buff_array[5]=DualSimData.rv_display[5];
				length=7;
			}
			else if(nEvt->prm==SIM_CMD_RV_OPTIONS)
			{
				buff_array[0]=DualSimData.rv_options[0];
				buff_array[1]=DualSimData.rv_options[1];
				buff_array[2]=DualSimData.rv_options[2];
				buff_array[3]=DualSimData.rv_options[3];
				buff_array[4]=DualSimData.rv_options[4];
				buff_array[5]=DualSimData.rv_options[5];
				buff_array[6]=DualSimData.rv_options[6];
				length=8;
			}
			else if(nEvt->prm==SIM_COM_AGS_ALIVE)
			{
				buff_array[0]=DualSimData.ags_alive[0];
				buff_array[1]=DualSimData.ags_alive[1];
				buff_array[2]=DualSimData.ags_alive[2];
				buff_array[3]=DualSimData.ags_alive[3];
				buff_array[4]=DualSimData.ags_alive[4];
				length=6;
			}
			break;
#endif
#if DUAL_MCM_FUN==1
		case MCU_TX_DUAL_MCM_DATA:
			if(MSB(nEvt->prm)==MCM_CMD_INFO)
			{  
				Mem_strcpy(buff_array,DualMCMTxData,LSB(nEvt->prm));
				length=LSB(nEvt->prm)+1;
			}
			break;
#endif
#if CHECK_MCU_UPDATE_FILE_TYPE==1
		case MCU_TX_MCU_TYPE:
#if defined(AUTOCHIPS_AC781X)
#ifdef FLASH_SIZE_64K
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
			buff_array[0]='8';
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
			buff_array[0]='9';
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
			buff_array[0]='A';
#endif
#elif defined(FLASH_SIZE_256K)
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
			buff_array[0]='B';
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
			buff_array[0]='C';
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
			buff_array[0]='D';
#endif
#else
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
			buff_array[0]='4';
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
			buff_array[0]='5';
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
			buff_array[0]='6';
#elif PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			buff_array[0]='K';
#endif
#endif
#elif defined(HDSC_HC32F460)
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
			buff_array[0]='E';
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
			buff_array[0]='F';
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
			buff_array[0]='G';
#elif PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			buff_array[0]='L';
#elif PLATFORM_TYPE==REALTEK_RTD1861B_PLATFORM
			buff_array[0]='S';
#elif PLATFORM_TYPE==SUNPLUS_8368P_PLATFORM
			buff_array[0]='T';
#endif
#elif defined(HDSC_HC32L072)
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
			buff_array[0]='H';
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
			buff_array[0]='I';
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
			buff_array[0]='J';
#elif PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			buff_array[0]='M';
#elif PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM
      buff_array[0]='S';
#endif
#elif defined(STM32_F103VC)
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
			buff_array[0]='0';
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
#if defined(STM32F10X_MD)
			buff_array[0]='N';
#endif
#elif PLATFORM_TYPE==SUNPLUS_8368P_PLATFORM
			buff_array[0]='O';
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM
			buff_array[0]='P';
#elif PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM
      buff_array[0]='R';
#endif
#elif defined(STM32F401xx)
#if PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM
			buff_array[0]='Q';
#endif
#elif defined(HDSC_HC32F448)
#if PLATFORM_TYPE==UNISOC_PLATFORM
			buff_array[0]='Q';
#endif
#endif
#if TUNER_TYPE==TEF6686_TUNER
			buff_array[1]='L';
#elif TUNER_TYPE==TEF6657_TUNER
			buff_array[1]='A';
#elif TUNER_TYPE==TEF6851_TUNER
			buff_array[1]='T';
#elif TUNER_TYPE==TDA7786_TUNER
			buff_array[1]='E';
#elif TUNER_TYPE==TDA7708_TUNER
			buff_array[1]='S';
#elif TUNER_TYPE==TDA7703_TUNER
			buff_array[1]='H';
#elif TUNER_TYPE==SI4745_TUNER
			buff_array[1]='W';
#elif TUNER_TYPE==SI4755_TUNER
			buff_array[1]='X';
#elif TUNER_TYPE==MULTIPLE_TUNER
			if(MULTIPLE_TUNER_TYPE==TEF6686_TUNER)
			{
				buff_array[1]='L';
			}
			else if(MULTIPLE_TUNER_TYPE==TEF6657_TUNER)
			{
				buff_array[1]='A';
			}
			else if(MULTIPLE_TUNER_TYPE==TEF6851_TUNER)
			{
				buff_array[1]='T';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7786_TUNER)
			{
				buff_array[1]='E';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7708_TUNER)
			{
				buff_array[1]='S';
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7703_TUNER)
			{
				buff_array[1]='H';
			}
			else if(MULTIPLE_TUNER_TYPE==SI4745_TUNER)
			{
				buff_array[1]='W';
			}
			else if(MULTIPLE_TUNER_TYPE==SI4755_TUNER)
			{
				buff_array[1]='X';
			}
#endif
#if TUNER_FUNCTION==0
			length=2;
#else
			length=3;
#endif
			break;
#endif
#if CANBOX_FUNC_MULTIPLE==1
#if MODEL==LINUX_1295W_ET||MODEL==LINUX_1305W_GB
		case MCU_TX_CAN_MULTIPLE_TYPE:
			if(CanBoxMultType==MAC_RAISE_FIAT)
			{
				buff_array[0]=0;
			}
			else if(CanBoxMultType==MAC_RAISE_JEEP)
			{
				buff_array[0]=1;
			}
			else
			{
				break;
			}
			length=2;
			break;
#elif MODEL==LINUX_1295_69
		case MCU_TX_CAN_MULTIPLE_TYPE:
			if(CanBoxMultType==MAC_GENERAL)
			{
				buff_array[0]=0;
			}
			else if(CanBoxMultType==MAC_FIAT_SCUDO)
			{
				buff_array[0]=1;
			}
			else
			{
				break;
			}
			length=2;
			break;
#elif MODEL==LINUX_1425LW_PW||MODEL==LINUX_1495LW_PW
		case MCU_TX_CAN_MULTIPLE_TYPE:
			if(CanBoxMultType==MAC_SIMPLE_FORD)
			{
				buff_array[0]=0;
			}
			else if(CanBoxMultType==MAC_SIMPLE_TOYOTA)
			{
				buff_array[0]=1;
			}
			else if(CanBoxMultType==MAC_SIMPLE_MITSUBISHI)
			{
				buff_array[0]=2;
			}
			else if(CanBoxMultType==MAC_SIMPLE_RN)
			{
				buff_array[0]=3;
			}
			else if(CanBoxMultType==MAC_SIMPLE_VW)
			{
				buff_array[0]=4;
			}
			else if(CanBoxMultType==MAC_NISSAN_TEANA)
			{
				buff_array[0]=5;
			}
			else
			{
				break;
			}
			length=2;
			break;
#elif MODEL==LINUX_1307W_14
		case MCU_TX_CAN_MULTIPLE_TYPE:
			if(CanBoxMultType==MAC_MM_GOLF)
			{
				buff_array[0]=0;
			}
			else if(CanBoxMultType==MAC_MM_GOLF_A)
			{
				buff_array[0]=1;
			}
			else
			{
				break;
			}
			length=2;
			break;
#else
		case MCU_TX_CAN_MULTIPLE_TYPE:
			if(CanBoxMultType==MAC_RAISE_JAC)
			{
				buff_array[0]=0;
			}
			else if(CanBoxMultType==MAC_RAISE_GW)
			{
				buff_array[0]=1;
			}
			else
			{
				break;
			}
			length=2;
			break;
#endif			
#endif
#if AHD_360_FUN==1
		case MCU_TX_AHD_360_INFO:
			{	
				u16 ahd_buff_length;
 				AHD_360_TxAppDataPro(nEvt->prm,buff_array,&ahd_buff_length);
				length=ahd_buff_length+1;
			}
			break;
#endif
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
		case MCU_TX_BACKUP_DATA:
			{
				u32 backup_index;
				for(backup_index=0;backup_index<APP_BACKUP_DATA_LENGTH;backup_index++)
				{
					buff_array[backup_index]=AppBackupData[backup_index];
				}
				length=APP_BACKUP_DATA_LENGTH+1;
			}
			break;
#endif
#if FMT_FUNCTION==1
		case MCU_TX_FMT_INFO:
			buff_array[0]=F_FMT_WORK_MODE;
			buff_array[1]=MSB(FMT_Freq);
			buff_array[2]=LSB(FMT_Freq);
			buff_array[3]=F_FMT_AUDIO_MODE;
			length=5;
			break;
#endif
#if BU32107_FUN==1
		case MCU_TX_DSP_DATA:
   			buff_array[0]=DSP_Data.audio_ch;
			buff_array[1]=DSP_Data.volume;
			buff_array[2]=DSP_Data.eq_mode;
			buff_array[3]=DSP_Data.eq_band_value[0];
			buff_array[4]=DSP_Data.eq_band_value[1];
			buff_array[5]=DSP_Data.eq_band_value[2];
			buff_array[6]=DSP_Data.eq_band_value[3];
			buff_array[7]=DSP_Data.eq_band_value[4];
			buff_array[8]=DSP_Data.eq_band_value[5];
			buff_array[9]=DSP_Data.eq_band_value[6];
			buff_array[10]=DSP_Data.eq_band_value[7];
			buff_array[11]=DSP_Data.eq_band_value[8];
			buff_array[12]=DSP_Data.eq_band_value[9];
			buff_array[13]=DSP_Data.eq_band_value[10];
			buff_array[14]=DSP_Data.eq_band_value[11];
			buff_array[15]=DSP_Data.eq_band_value[12];
			buff_array[16]=DSP_Data.eq_band_value[13];
			buff_array[17]=DSP_Data.eq_band_value[14];
			buff_array[18]=DSP_Data.eq_band_value[15];
			buff_array[19]=DSP_Data.fade;
			buff_array[20]=DSP_Data.balance;
			buff_array[21]=DSP_Data.on_off;
			buff_array[22]=DSP_Data.background_volume;
			buff_array[23]=0x00;
			length=25;
			break;
#endif

#if ACR_IR_KEY_FUN==1
		case MCU_TX_ACR_IR_INFO:
			buff_array[0]=MSB(nEvt->prm);
			buff_array[1]=LSB(nEvt->prm);
			length=3;		
			break;
#endif
#if MODEL==LINUX_1465_16||MODEL==LINUX_1345W_CP1||MODEL==LINUX_1345W_CP2||MODEL==LINUX_1345W_65HINO||MODEL==LINUX_1327W_65HINO||MODEL==LINUX_1465W_16M||MODEL==LINUX_1325W_53||MODEL==LINUX_1365W_PCDN
		case MCU_TX_TEMPERATURE:
			buff_array[0]=TemperatureValue1;
			buff_array[1]=TemperatureValue2;
			length=3;
			break;
#endif
#if DAB_FM_FUN==1
		case MCU_TX_DAB_FM_RADIO_PARAM:		
			buff_array[0]=Found_Station_flag;
			buff_array[1]=Radio.SMeter;
			buff_array[2]=Radio.Usn;
			buff_array[3]=DAB_FM_Flag;
			buff_array[4]=MSB(radio_freq);
			buff_array[5]=LSB(radio_freq);
			length=7;
			break;
#endif
		case MCU_TX_MISC_INFO:
			buff_array[0]=MSB(nEvt->prm);
			switch(buff_array[0])
			{
				case SID_MISC_AVM_CAM_POWER:
					buff_array[1]=LSB(nEvt->prm);
					length=3;
					break;
				default:
					length=0;
					break;
			}
			break;
#if MODEL==LINUX_N039_DZ
		case MCU_TX_HW_VERSION:
			{
				u8 i;
				u8 step=120;
				u16 a[10]={740,1016,1315,1658,1948};
				u16 ADC_current;
				ADC_current=Get_Adc(ADCH_PANEL_KEY1);
				
				for(i=0;i<10;i++)
				{
					if((a[i]-step)<ADC_current&&ADC_current<a[i]+step)
					{
						buff_array[0]='V';
						buff_array[1]='1';
						buff_array[2]='.';
						buff_array[3]='0';
						buff_array[4]='.';
						if(i==0)
						{
							buff_array[5]='0';
						}
						else if(i==1)
						{
							buff_array[5]='1';
						}
						else if(i==2)
						{
							buff_array[5]='2';
						}
						else if(i==3)
						{
							buff_array[5]='3';
						}
						else if(i==4)
						{
							buff_array[5]='4';
						}
						else if(i==5)
						{
							buff_array[5]='5';
						}
						length=7;
						break;
					}
				}
#if TPA6304_Q1_FUN==1&&TAS6424M_Q1_FUN==1
				if(i<4)
				{
					TPA6304_Flag=1;
					TPA6304_Init();
				}
				else
				{
					TAS6424_Flag=1;
					TAS6424_Init();
				}
#elif TPA6304_Q1_FUN==1
				TPA6304_Flag=1;
				TPA6304_Init();
#elif TAS6424M_Q1_FUN==1
				TAS6424_Flag=1;
				TAS6424_Init();	
#endif							
			}
			break;
#endif
		case MCU_TX_DPA_INFO:
			{
#if TPA6304_Q1_FUN==1
#if MODEL==LINUX_N039_DZ
				if(TPA6304_Flag)
#endif
				{
					u8 reg_index=0;
					u8 buff_index=1;
					
					buff_array[0]=TX_DAP_INFO;
					for(reg_index=0;reg_index<MAX_TPA6304REG_BUFFER_NUM;reg_index++)
					{
						buff_array[buff_index]=TPA6304_Reg_Buffer[reg_index].address;
						buff_index++;
						buff_array[buff_index]=TPA6304_Reg_Buffer[reg_index].value;
						buff_index++;
					}
					if(buff_index<80)
					{
						for(;buff_index<81;buff_index++)
						{
							buff_array[buff_index]=0;
						}
					}
					length=0x51;
				}
#endif

#if TAS6424M_Q1_FUN==1
#if MODEL==LINUX_N039_DZ
				if(TAS6424_Flag)
#endif
				{
					u8 reg_index=0;
					u8 buff_index=1;
					
					buff_array[0]=(u8)nEvt->prm;
					if(buff_array[0]==TX_DAP_INFO)
					{
						for(reg_index=0;reg_index<MAX_REG_BUFFER_NUM;reg_index++)
						{
							buff_array[buff_index]=Reg_Buffer[reg_index].address;
							buff_index++;
							buff_array[buff_index]=Reg_Buffer[reg_index].value;
							buff_index++;
						}
						if(buff_index<80)
						{
							for(;buff_index<81;buff_index++)
							{
								buff_array[buff_index]=0;
							}
						}
					}
					else if(buff_array[0]==TX_DAP_DC_RESULT)//AMP DC Load Dignostic result
					{	
						for(reg_index=0;reg_index<16;reg_index++)
						{
							buff_array[buff_index]=DC_DIAG_RESULT[reg_index];
							buff_index++;
						}
						if(buff_index<80)
						{
							for(;buff_index<81;buff_index++)
							{
								buff_array[buff_index]=0;
							}
						}
					}
					else if(buff_array[0]==TX_DAP_AC_RESULT)//AMP AC Load Dignostic result
					{	
						for(reg_index=0;reg_index<64;reg_index++)
						{
							buff_array[buff_index]=AC_DIAG_RESULT[reg_index];
							buff_index++;
						}
						if(buff_index<80)
						{
							for(;buff_index<81;buff_index++)
							{
								buff_array[buff_index]=0;
							}
						}
					}
					else if(buff_array[0]==TX_DAP_FAULTS)//AMP faults
					{		
						for(reg_index=0;reg_index<5;reg_index++)
						{
							buff_array[buff_index]=TAS6424_FAULT[reg_index];
							buff_index++;
						}
						if(buff_index<80)
						{
							for(;buff_index<81;buff_index++)
							{
								buff_array[buff_index]=0;
							}
						}
					}
					else if(buff_array[0]==TX_DAP_WARNINGS)//AMP warnings
					{
						for(reg_index=0;reg_index<5;reg_index++)
						{
							buff_array[buff_index]=TAS6424_WARNING[reg_index];
							buff_index++;
						}
						if(buff_index<80)
						{
							for(;buff_index<81;buff_index++)
							{
								buff_array[buff_index]=0;
							}
						}
					}
					else if(buff_array[0]==TX_DAP_STATUS)//AMP status
					{		
						buff_array[buff_index]=TAS6424_STATUS;
						buff_index++;
						
						if(buff_index<80)
						{
							for(;buff_index<81;buff_index++)
							{
								buff_array[buff_index]=0;
							}
						}			
					}
					length=0x51;
				}
#endif
			}
			break;
		default:
			return;
	}
	Uart_Tx_Seq_Num++;
	Data_Length_IN_Buffer=length+8;
	if((length+8)>MAX_APP_TX_BUFFER_LENGTH
		||length>MAX_APP_TX_BUFFER_LENGTH
		||length==0)
	{
		return;
	}
#if APP_COM_DEBUG_FUN==1
	printf("McuTxService:tx data:ID=%x\r\n",nEvt->ID);
	printf("McuTxService:tx data:prm=%x\r\n",nEvt->prm);
#endif	
	McuTxBuffer[0]=HEAD_ADDRESS_MCU;
	McuTxBuffer[1]=HEAD_ADDRESS_APP;
	McuTxBuffer[2]=Uart_Tx_Seq_Num;
	McuTxBuffer[3]=0;//ID Fixed 00
	McuTxBuffer[4]=Data_Length_IN_Buffer;//len
	McuTxBuffer[5]=0;//checksum_bk   部计算checksum
	McuTxBuffer[6]=length;
	McuTxBuffer[7]=nEvt->ID;		
	for(j=0;j<length-1;j++)
	{
		McuTxBuffer[8+j]=*ptr2++; 
	}
	McuTxBuffer[8+j]=0xAA;//last byte	
	SetPacket(); 
	Usart_StartFrame();			
}

void McuRxService(u8 *rx_buff)
{
	u8 length;
	u8 nGRoupID;
	u8 *data;
	
	length=rx_buff[4];
	Uart_Rx_Seq_Num=rx_buff[2]; 
	nGRoupID=rx_buff[3]; 
	data=&rx_buff[6]; 
	if(nGRoupID<MCU_TXRX_NACK_NO_SUPPORT)
	{   
#if MCU_ACK_MESSAGE_MODE==1
		ACK_PostMessage(MCU_TXRX_ACK,Uart_Rx_Seq_Num);
#else
		Mcu_Ack_Tx(MCU_TXRX_ACK);
#endif
		MCU_RxAppPacketCounter++;
#if APP_COM_DEBUG_FUN==1
		printf("McuRxService:ID=0x%02x,seq=%d\r\n",nGRoupID,Uart_Rx_Seq_Num);
		printf("McuRxService: data[0]=%x\r\n",data[0]);
#endif	
	}	
	switch (nGRoupID)
	{
#ifndef FLASH_SIZE_64K
		case MCU_RX_DAB_CMD:
			if(data[0]==DAB_RESET_CMD)
			{
				PostMessage(MMI_MODULE, UICC_EVT_MMI_DAB_RESET, 0);
			}
			break;
#endif
#if 0
		case MCU_RX_OS_UI_TYPE:
			PostMessage(NAVI_MODULE, MCU_TX_APP_UI_TYPE,0);
			break;
		case MCU_RX_APP_STARTOK:
			F_OS_UPGRADE=0;
			F_ARM2_STARTOK=1;
			F_AppPowerOn=1; 
#if APP_COM_DEBUG_FUN==1
			printf("mcu rx ARM2 ok\r\n");
#endif	
			break;
		case MCU_RX_OS_UPGRADE://///OS升级
			F_OS_UPGRADE=1;
			F_ARM2_STARTOK=ON;
			break;
#endif
		case MCU_TXRX_ReverseACK:
			F_OS_ReverseAck=1;
			break;
		case MCU_TXRX_ACK	:
			APP_Ack_Check();
			MCU_Rx_ACK_Counter++;
#if APP_COM_DEBUG_FUN==1
			printf("McuRxService:Ack:seq=%d\r\n",Uart_Rx_Seq_Num);
#endif	
			break;
		case MCU_RX_GPS_TIME:
			{
#if RTC_TIMER_FUN==1
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
				RTC_DATE_TIME_TYPE_DEF time;
				time.year=data[0];
				time.month=data[1];
				time.day=data[2];
				time.week_day=data[3];
				time.hours=data[4];
				time.minutes=data[5];
				time.seconds=data[6];
				RTC_UpdateTime(time);
				TxClockTimer=2;
#else
				RTC_TimerData=data[0];
				RTC_TimerData<<=8;
				RTC_TimerData|=data[1];
				RTC_TimerData<<=8;
				RTC_TimerData|=data[2];	
				RTC_TimerData<<=8;
				RTC_TimerData|=data[3];
				RTC_UpdateTime(RTC_TimerData);
#if APP_COM_DEBUG_FUN==1
				printf("MCU_RX_GPS_TIME:time=%x\r\n",RTC_TimerData);
#endif	
#endif			
#endif	
			}
			break;
			case MCU_RX_CMD:
#if APP_COM_DEBUG_FUN==1
			printf("MCU_RX_CMD:keycode=%x\r\n",data[0]);
#endif	
			if(data[0]==UICC_FRONT_ZONE_TS)
			{
				//此命令带2个参数
				PostMessage(MMI_MODULE,data[0],(u8)data[1]<<8|data[2]);
			}
			else
			{
				PostMessage(MMI_MODULE, data[0],(u8)*(data+1)<<8|TOUCH_SCREEN);
			}
			if(data[0]==0x00)
			{
				APPMonitorTimer=APP_MONITOR_TIME;
#if CHECK_MCU_UPDATE_FILE_TYPE==1
				PostMessage(NAVI_MODULE,MCU_TX_MCU_TYPE,0);
#endif
			}
			break;
		case MCU_RX_STATUS:
			PostMessage(MMI_MODULE,UICC_WINCE_READY, (u8) data[0]<<8);
#if CHECK_MCU_UPDATE_FILE_TYPE==1
			PostMessage(NAVI_MODULE,MCU_TX_MCU_TYPE,0);
#endif
			break;
#if TUNER_FUNCTION==1
		case MCU_RX_RADIOFREQINFO:
			PostMessage(TUNER_MODULE, EVT_TUN_FREQ,WORD( data[0],data[1]));
			break;
		case MCU_RX_RADIOGETINFO:
			F_AppInit_OK=1;
			PostMessage(TUNER_MODULE,EVT_TUN_ALL_INFO,0);
			break;
#endif
		case MCU_RX_REFLASHCMD:
			if(data[0]==0x01
#if CHECK_MCU_UPDATE_FILE_TYPE==1
#if defined(AUTOCHIPS_AC781X)
#ifdef FLASH_SIZE_64K
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
				&&data[1]=='8'
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
				&&data[1]=='9'
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
				&&data[1]=='A'
#endif
#elif defined(FLASH_SIZE_256K)
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
				&&data[1]=='B'
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
				&&data[1]=='C'
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
				&&data[1]=='D'
#endif
#else
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
				&&data[1]=='4'
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
				&&data[1]=='5'
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
				&&data[1]=='6'
#elif PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM	
				&&data[1]=='K'
#endif
#endif
#elif defined(HDSC_HC32F460)
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
				&&data[1]=='E'
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
				&&data[1]=='F'
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
				&&data[1]=='G'
#elif PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
				&&data[1]=='L'
#elif PLATFORM_TYPE==REALTEK_RTD1861B_PLATFORM
				&&data[1]=='S'
#elif PLATFORM_TYPE==SUNPLUS_8368P_PLATFORM
				&&data[1]=='T'				
#endif
#elif defined(HDSC_HC32L072)
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
				&&data[1]=='H'
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM			
				&&data[1]=='I'
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM	
				&&data[1]=='J'
#elif PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
				&&data[1]=='M'
#elif PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM
				&&data[1]=='S'
#endif
#elif defined(STM32_F103VC)
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
				&&data[1]=='0'
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
#if defined(STM32F10X_MD)
				&&data[1]=='N'
#endif
#elif PLATFORM_TYPE==SUNPLUS_8368P_PLATFORM
				&&data[1]=='O'
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM
				&&data[1]=='P'
#elif PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM
        &&data[1]=='R'
#endif
#elif defined(STM32F401xx)
#if PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM
				&&data[1]=='Q'
#endif
#elif defined(HDSC_HC32F448)
#if PLATFORM_TYPE==UNISOC_PLATFORM
//				&&data[1]=='Q'
#endif
#endif
#endif
				)
			{
				F_AppInit_OK=1;
				APP_Status=APP_READY;
				F_IAP_AppCom = 0x78;
#if APP_COM_DEBUG_FUN==1
			printf("MCU_RX_REFLASHCMD\r\n");
#endif
				PostMessage(NAVI_MODULE,MCU_TX_MCU_REFRESH_CFM,0);	
			}	
			break;
		case MCU_RX_SETTING:
			PostMessage(MMI_MODULE,UICC_EVT_MMI_GEN_SETTING,((u8)data[0])<<8|data[1]);
			break;
#if 0
		case MCU_RX_COORDINATE:
			{
#if AVT_ISDB_FUN==1
				u8 key_source;
				u8 Key_State;

				key_source=AppSourceChangeTab[data[0]];
				Key_State=data[1];
				if(key_source==SOURCE_DTV
					&&Key_State==TOUCH_STATE_UP)
				{
					u8 dtv_data[9];
					
					dtv_data[0]=0x55;
					dtv_data[1]=0x06;
					dtv_data[2]=0x02;
					dtv_data[3]=0x02;
					dtv_data[4]=data[2];
					dtv_data[5]=data[3];
					dtv_data[6]=data[4];
					dtv_data[7]=data[5];
					dtv_data[8]=dtv_data[0]+dtv_data[1]+dtv_data[2]+dtv_data[3]+dtv_data[4]+dtv_data[5]+dtv_data[6]+dtv_data[7];	
					UART5_SendData(dtv_data,9);
				}
#endif
			}
			break;
#endif
		case MCU_RX_MEMU_WHEELSTY:
			PostMessage(MMI_MODULE, UICC_STEERKEY_STY, data[0]);
			break;
#if 0
		case MCU_RX_MEMU_PANNELSTY:
			PostMessage(MMI_MODULE,UICC_PANELKEY_STY,(u8)data[0]<<8|data[1]);
			break;
#endif
		case MCU_RX_BT_INFO:
			BT_INFO.mstate=(BT_MAINSTATE)data[0];
#if TUNER_FUNCTION==1
#if TUNER_TYPE==TDA7703_TUNER
#elif TUNER_TYPE==MULTIPLE_TUNER
			if(MULTIPLE_TUNER_TYPE==TDA7703_TUNER)
			{
			}
			else
			{
			    if(BT_INFO.mstate==BT_INCOMING
					||BT_INFO.mstate==BT_DIALING
					||BT_INFO.mstate==BT_CALLING_PHONE)
				{
					if(RadioMuteState==0)
					{
						RadioMute(ON);
					}
				}
				else
				{
					if(RadioMuteState)
					{
						if(IsTunerPowerOn()
						&&SeekProcState==Seek_Idle)
						{
							RadioMute(OFF);
						}
					}
				}
			}
#else
			if(BT_INFO.mstate==BT_INCOMING
				||BT_INFO.mstate==BT_DIALING
				||BT_INFO.mstate==BT_CALLING_PHONE)
			{
				if(RadioMuteState==0)
				{
					RadioMute(ON);
				}
			}
			else
			{
				if(RadioMuteState)
				{
					if(IsTunerPowerOn()
					&&SeekProcState==Seek_Idle)
					{
						RadioMute(OFF);
					}
				}
			}
#endif
#endif
			break;
#if CAN_ADAPTER==1||CAN_FUNCTION==1
		case MCU_RX_APP_COPYDATA:
#if MODEL==LINUX_1295W_93
			rx_data_length=length-6;
#endif
			(*pCanFunMain[CurSelCanBoxModel].rx_app_pro)(data);    
			break;
#endif
#if AM_688_UART_FUN==1
   #if MODEL==LINUX_1297WS_65HSE
		case 	MCU_RX_APP_COPYDATA:
   #else
        case 	MCU_RX_SMART_LOCK_COPYDATA:
   #endif
			door_rx_buffer[0]=data[0];
		  door_rx_buffer[1]=data[1];
		  door_rx_buffer[2]=data[2];
		  door_rx_buffer[3]=data[3];
		#if defined(HDSC_HC32L072)
		  UART0_SendData(door_rx_buffer,4);
    #elif defined(STM32_F103VC)
      UART3_SendData(door_rx_buffer,4);
    #endif	
			break;
#endif
		case MCU_RX_MACHINE_TYPE:
			break;
#if 0
		case MCU_RX_TEST_MODE_INFO:
#if TUNER_TYPE==MULTIPLE_TUNER
#if MULTIPLE_TUNER_SUBSET==NXP_TUNER
			if(MULTIPLE_TUNER_TYPE==TEF6686_TUNER
				||MULTIPLE_TUNER_TYPE==TEF6657_TUNER
				||MULTIPLE_TUNER_TYPE==TEF6851_TUNER)
			{
				length=sizeof(TunerTestItem_TEF6686);
				Mem_strcpy(&TunerTestItem_TEF6686.data[0],data,length);
			}
#else
			if(MULTIPLE_TUNER_TYPE==TDA7786_TUNER)
			{
				length=sizeof(TunerTestItem_TDA7786);
				Mem_strcpy(&TunerTestItem_TDA7786.data[0],data,length);
			}
			else if(MULTIPLE_TUNER_TYPE==TDA7708_TUNER)
			{
				length=sizeof(TunerTestItem_TDA7708);
				Mem_strcpy(&TunerTestItem_TDA7708.data[0],data,length);
			}
#if ST_TUNER_INCLUDE_TDA7703==1
			else if(MULTIPLE_TUNER_TYPE==TDA7703_TUNER)
			{
				length=sizeof(TunerTestItem_TDA7703);
				Mem_strcpy(&TunerTestItem_TDA7703.data[0],data,length);
			}
#endif
#endif
#else
			length=sizeof(TunerTestItem);
			Mem_strcpy(&TunerTestItem.data[0],data,length);
#endif
			break;
#endif
		case MCU_RX_SYSTERM_VOLUME:
			TurnOn_Volume=data[0];
#if CAN_ADAPTER==1
#if CANBOX_SIMPLE_HONDA==1
			PostMessage(MAIN_CAN_MODULE,CAN_RX_APP_DATA,S_HONDA_TX_VOLUME_INFO);
#endif
#endif
			break;
		case MCU_RX_MISC_INFO_CMD:
			if(MISC_AUDIO_BREAK==data[0])
			{
			}
#ifndef FLASH_SIZE_64K
			else if(MISC_PANNEL_LED_RGB==data[0])
			{
				COLOR_SETTING temp;
				
				temp.red=(u16)data[1]*MAX_COLOR_LED_LEVEL/0xff;
				temp.green=(u16)data[2]*MAX_COLOR_LED_LEVEL/0xff;
				temp.blue=(u16)data[3]*MAX_COLOR_LED_LEVEL/0xff;
				if(ColorSetting.red!=temp.red
					||ColorSetting.green!=temp.green
					||ColorSetting.blue!=temp.blue)
				{
					ColorSetting=temp;
					nRedPwmCounter=0;
					nGreenPwmCounter=0;
					nBluePwmCounter=0;
				}
			}
			else if(MISC_CAPACITOR_SCREEN_KEY==data[0])
			{    
			}
			else if(MISC_REQ_EJECT==data[0])
			{
				PostMessage(MMI_MODULE,UICC_EJECT,PANEL);  
			}
			else if(MISC_FRONT_CAMERA_POWER==data[0])
			{
				PostMessage(MMI_MODULE,UICC_CAMERA_POWER,WORD(FRONT_CAMERA_POWER,data[1]));   	
			}
#endif
			else if(MISC_REAR_CAMERA_POWER==data[0])
			{
				PostMessage(MMI_MODULE,UICC_CAMERA_POWER,WORD(REAR_CAMERA_POWER,data[1]));   	
			}
			else if(MISC_AVM_CAMERA_POWER==data[0])
			{
				PostMessage(MMI_MODULE,UICC_CAMERA_POWER,WORD(CAMERA_POWER,data[1]));   	
			}
#if TUNER_FUNCTION==1
#ifndef FLASH_SIZE_64K
			else if(MISC_REQ_SPEC_RADIO_FREQ==data[0])
			{
				PostMessage(TUNER_MODULE,EVT_TUN_FAV_FREQ,data[1]);		
			}
#endif
#endif
#if PLATFORM_TYPE == SUNPLUS_8368PU_PLATFORM
			else if(MISC_SOC_BOOT_MODE == data[0])
			{
				if(data[1] == 0x04)
				{
					AppUpdateState=APP_UPDATE_RESET_ON;
				}
			}
#endif
#if CAN_ADAPTER==1
			else if(MISC_REQ_CAN_INFO==data[0])
			{
				CanBox_RefreashStart();			
			}
#endif
#if UUID_FUNCTION==1
			else if(MISC_REQ_UUID==data[0])
			{
				PostMessage(NAVI_MODULE, MCU_TX_UUID_DATA,0);
			}
#endif
			else if(MISC_REQ_VERSION==data[0])
			{
				PostMessage(NAVI_MODULE, MCU_TX_MCU_VERSION,0);
			}
#if MODEL==LINUX_1475_21||MODEL==LINUX_1475_CP||MODEL==LINUX_1479_21	//add		
			else if(MISG_MULTI_VIDEO_PROTOCOL==data[0])
			{
				u8 i=0;
				video_lenght=data[1];
				for(i=0;i<video_lenght;i++)
				{
					video_protocol[i]=data[2+i];
				}
		  UART2_SendData(video_protocol,video_lenght);
			}
#endif
#if MODEL==LINUX_N039_DZ
			else if(MISC_REQ_HW_VERSION==data[0])
			{
				PostMessage(NAVI_MODULE, MCU_TX_HW_VERSION,0);
			}
#endif			
			break;
			
			
	#if	USB_TPS2549_FUN	 ==1
		case MCU_RX_USB_REBOOT://test USB
				if(data[1]==0x00)
				{
					TPS2549_PowerOff();
				}
				else if(data[1]==0x01)
				{
					TPS2549_PowerOn();
				}
				else if(data[1]==0x02)
				{
					TPS2549_POWER_CTL_OFF;
					tps2549_Flag = 1;
				}
		
		break;
	#endif	
		
			
					
			
#if DUAL_DAB_FUN==1
		case MCU_RX_DAB_COMMAND:
			switch(data[0])
			{
				case 0x01:
					PostMessage(DAB_MODULE,EVT_KS_AS,0);
					break;
				case 0x02:
					PostMessage(DAB_MODULE,EVT_KS_AS_CANCEL,0);
					break;
				case 0x03:
					PostMessage(DAB_MODULE,EVT_KS_SELECT,data[1]);
					break;
				case 0x80:
					PostMessage(DAB_MODULE,EVT_KS_REQ_LIST,0);
					break;
				case 0x04:
					KS_DirectPlayInfo.frequence=data[1];
					
					KS_DirectPlayInfo.service_id=data[2];
					KS_DirectPlayInfo.service_id<<=8;
					KS_DirectPlayInfo.service_id|=data[3];
					KS_DirectPlayInfo.service_id<<=8;
					KS_DirectPlayInfo.service_id|=data[4];
					KS_DirectPlayInfo.service_id<<=8;
					KS_DirectPlayInfo.service_id|=data[5];

					KS_DirectPlayInfo.sc_id=data[6];
					
					KS_DirectPlayInfo.ensemble_id=data[7];
					KS_DirectPlayInfo.ensemble_id<<=8;
					KS_DirectPlayInfo.ensemble_id|=data[8];
					
					PostMessage(DAB_MODULE,EVT_KS_DIRECT_PLAY,0);
					break;
				case 0x05:
					PostMessage(DAB_MODULE,EVT_KS_SF_ON_OFF,data[1]);
					break;
				case 0x07:
					KS_TpegSettingInfo.country_code[0]=data[1];
					KS_TpegSettingInfo.country_code[1]=data[2];
					KS_TpegSettingInfo.country_code[2]=data[3];
					KS_TpegSettingInfo.type=data[4];
					PostMessage(DAB_MODULE,EVT_KS_TPEG_SETTING,0);
					break;
				case 0x81:
					PostMessage(DAB_MODULE,EVT_KS_REQ_TEST_MODE_INFO,0);
					break;
				case 0x82:
					PostMessage(DAB_MODULE,EVT_KS_DAB_SWITCH,0);
					break;
				case 0x83:
					PostMessage(DAB_MODULE,EVT_KS_REQ_SOFT_VERSION,0);
					break;
				case 0x84:
					PostMessage(DAB_MODULE,EVT_KS_GET_CLOCK,1);
					break;
				case 0x85:
					PostMessage(DAB_MODULE,EVT_KS_TPEG_TIME,data[1]);
					break;
				case 0x86:
					if(data[1]==0x01)
					{
						PostMessage(DAB_MODULE,EVT_KS_TPEG_RX_EVENT,0);
					}
					break;
				default:
					break;
			}
			break;
		case MCU_RX_DAB_UPDATE_CMD:
			if(CMD_KS_ENTER_UPDATE==data[0])
			{
				PostMessage(NAVI_MODULE, MCU_TX_DAB_UPDATE_CMD,CMD_KS_UPDATE_READY);
			}
			break;
#endif
#if FACTORY_AUTO_TEST_FUN==1
		case MCU_RX_MEDIA_INFO:
			MediaPlayInfo.cur_play_track=data[5];
			break;
		case MCU_RX_APP_VERSION:
			{
				u8 counter;
				u8 version_index=0;
				u8 version_length;
				
				for(counter=0;counter<APP_VERSION_MAX_LENGTH;counter++)
				{
					AutoTestAppVersion[counter]=0x20;
				}
				for(counter=0;counter<OS_VERSION_MAX_LENGTH;counter++)
				{
					AutoTestOsVersion[counter]=0x20;
				}
				for(counter=0;counter<DVP_VERSION_MAX_LENGTH;counter++)
				{
					AutoTestDvpVersion[counter]=0x20;
				}
				version_length=data[0];
				version_index=1;
				for(counter=0;counter<version_length;counter++)
				{
					if(counter<APP_VERSION_MAX_LENGTH)
					{
						AutoTestAppVersion[counter]=data[version_index];
					}
					version_index++;
				}

				version_length=data[version_index];
				version_index++;
				for(counter=0;counter<version_length;counter++)
				{
					if(counter<OS_VERSION_MAX_LENGTH)
					{
						AutoTestOsVersion[counter]=data[version_index];
					}
					version_index++;
				}	

				version_length=data[version_index];
				version_index++;
				for(counter=0;counter<version_length;counter++)
				{
					if(counter<DVP_VERSION_MAX_LENGTH)
					{
						AutoTestDvpVersion[counter]=data[version_index];
					}
					version_index++;
				}		
				GetVersionTimer=0;
				GetVersionCounter=0;
				F_VERSION_VALID=1;
			}
			break;
		case MCU_RX_BT_TEST_STATE:
			switch(data[0])
			{
				case 0x01:
					if(0x01==data[1])
					{
						AutoTestBtInfo.field.f_connect=1;
					}
					break;
				case 0x02:
					if(0x01==data[1])
					{
						AutoTestBtInfo.field.f_connect=0;
					}
					break;
				case 0x03:
					if(0x01==data[1])
					{
						AutoTestBtInfo.field.f_hungup=0;
					}
					break;
				case 0x04:
					if(0x01==data[1])
					{
						AutoTestBtInfo.field.f_audio_menu=0;
					}
					break;
				case 0x05:
					if(0x01==data[1])
					{
						AutoTestBtInfo.field.f_audio_menu=1;
					}
					break;
				case 0x06:
					if(0x01==data[1])
					{
						AutoTestBtInfo.field.f_internal_mic=1;
					}
					break;
				case 0x07:
					if(0x01==data[1])
					{
						AutoTestBtInfo.field.f_internal_mic=0;
					}
					break;
				case 0x08:
					if(0x01==data[1])
					{
						AutoTestBtInfo.field.f_adress_right=1;
					}
					else
					{
						AutoTestBtInfo.field.f_adress_right=0;
					}
					break;
				
				default:
					break;
			}
			break;
		case MCU_RX_WIFI_TEST_CMD://新增，待完善
			switch (data[0])
			{
				u8 counter;
//				case 0x05:
//					AutoTestWifiFlag.f_connect=data[1];
//					break;
//				case 0x06:
//					AutoTestWifiFlag.f_ping=data[1];
//					break;
				case 0x07:
					AutoTestWifiSSID[0] = 0x00;
					for(counter=0;counter<WIFI_SSID_MAX_LENGTH;counter++)
					{
						if(data[counter+2] == 0x00)
						{
							break;
						}
						AutoTestWifiSSID[counter+1]=data[counter+2];
						AutoTestWifiSSID[0]+=1;
						
					}
					break;
				case 0x08:
					AutoTestWifiPassword[0] = 0x00;
					for(counter=0;counter<WIFI_PASSWORD_MAX_LENGTH;counter++)
					{
						if(data[counter+2] == 0x00)
						{
							break;
						}
						AutoTestWifiPassword[counter+1]=data[counter+2];
						AutoTestWifiPassword[0]+=1;
						
					}
					break;
				default:
					break;
			}
			break;
		case MCU_RX_AUTO_TEST_CMD:
//			u8 counter;
//			for(counter=0, counter<AUTO_TEST_RX_APP_LENGTH, counter++)
//				AutoTestRxAppBuffer[counter]
			Mem_strcpy(AutoTestRxAppBuffer,data,AUTO_TEST_RX_APP_LENGTH);
			AutoTestRxApp();
			break;
#endif
#if CAN_ADAPTER==1
#if CANBOX_BNR_UPDATE_FUN==1||CANBOX_UPDATE_FUN_HIWORLD==1||CANBOX_UPDATE_FUN_GOLF==1||CANBOX_UPDATE_FUN_SIMPLE==1
		case MCU_RX_CAN_UPDATE_INFO:
			if(APP_REQ_ENTER_CAN_UPDATE==data[0])
			{
				CanUpdateStart();
			}
#if MODEL==LINUX_2349WA_93||MODEL==LINUX_2339WA_93
			else if(APP_SEND_UPDATE_END==data[0])
			{
				SystemReset();
			}
#endif
			break;
#endif
#endif	
#if MLINK_FUN==1
		case MCU_RX_TOUCH_DATA:
			if(data[0]<3)
			{
				USB_MirrorTxInfo.touch_data[data[0]].x=data[1];
				USB_MirrorTxInfo.touch_data[data[0]].x<<=8;
				USB_MirrorTxInfo.touch_data[data[0]].x|=data[2];
				USB_MirrorTxInfo.touch_data[data[0]].y=data[3];
				USB_MirrorTxInfo.touch_data[data[0]].y<<=8;
				USB_MirrorTxInfo.touch_data[data[0]].y|=data[4];
				PostMessage(USB_MIRROR_MODULE,CP_MSG_C_TOUCH,data[0]);
			}
			break;
#endif
#if DUAL_MCM_FUN==1
		case MCU_RX_DUAL_MCM_DATA:
			Dual_MCM_TxService(data,length-6);
			break;
#endif
#if DUAL_SIM2_FUN==1
		case MCU_RX_DUAL_SIM2_DATA:
			Dual_SIM_TxService(data,length-6);
			break;
#endif
#if AHD_360_FUN==1
		case MCU_RX_AHD_360_CMD:
			AHD_360_RxAppDataPro(data);
			break;
#endif
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
		case MCU_RX_REQUEST_STORE_DATA:
			{
				u32 backup_index;
				
				for(backup_index=0;backup_index<APP_BACKUP_DATA_LENGTH;backup_index++)
				{
					AppBackupData[backup_index]=data[backup_index];
				}
#if APP_COM_DEBUG_FUN==1
				printf("MCU_RX_REQUEST_STORE_DATA\r\n");
#endif	
			}
			break;
#endif
#if FMT_FUNCTION==1
		case MCU_RX_FMT_CMD:
			if(data[0]==SET_FMT_WORK_MODE_CMD)
			{
				PostMessage(FMT_MODULE,FMT_EVT_SET_WORK_MODE,data[1]);	
			}
			else if(data[0]==SET_FMT_FREQ_CMD)
			{
				PostMessage(FMT_MODULE,FMT_EVT_SET_FREQ,WORD(data[1],data[2]));	
			}
			else if(data[0]==SET_FMT_AUDIO_MODE_CMD)
			{
				PostMessage(FMT_MODULE,FMT_EVT_SET_AUDIO_MODE,data[1]);
			}
			break;
#endif
#if BU32107_FUN==1
		case MCU_RX_DSP_CMD:
			{
				u16 data1_2=0;
				u16 dsp_param;
				
				switch(data[0])
				{
	            	case 1:
						PostMessage(DSP_MODULE,EVT_DSP_AUDIO_CH,data[1]);
						break;
					case 2:
						data1_2|=(data[2]&0x01);//wjp
						data1_2<<=8;
						data1_2|=data[1];
						//PostMessage(DSP_MODULE,EVT_DSP_VOLUME_SET,data[1]);
						PostMessage(DSP_MODULE,EVT_DSP_VOLUME_SET,data1_2);//wjp
						break;
					case 3:
						PostMessage(DSP_MODULE,EVT_DSP_AUDIO_EQ,data[1]);
						break;
					case 4:
						dsp_param=(data[1]&0x0F);
						dsp_param<<=4;
						dsp_param|=(data[2]&0x01);
						dsp_param<<=8;
						dsp_param|=data[3];
						PostMessage(DSP_MODULE,EVT_DSP_AUDIO_BAND,dsp_param);
						break;
					case 5:
						PostMessage(DSP_MODULE,EVT_DSP_AUDIO_FADE_BALANCE,WORD(data[1],data[2]));
						break;
					case 6:
						dsp_param=(data[1]&0x03);
						dsp_param<<=4;
						dsp_param|=(data[2]&0x01);
						dsp_param<<=8;
						dsp_param|=data[3];
						PostMessage(DSP_MODULE,EVT_DSP_AUDIO_3_BAND,dsp_param);
						break;
					case 7:
						PostMessage(DSP_MODULE,EVT_DSP_AUDIO_LOUDNESS,data[1]);
						break;
					case 8:
						PostMessage(DSP_MODULE,EVT_DSP_MIX_ON,data[1]);
						break;
					case 9:
						PostMessage(DSP_MODULE,EVT_DSP_MIX_OFF,data[1]);
						break;
					case 10:
						PostMessage(DSP_MODULE,EVT_DSP_AUDIO_BEEP,data[1]);
						break;
					default:
						break;
				}
			}
			break;
#endif

#if ACR_IR_KEY_FUN==1
		case MCU_RX_ACR_IR_INFO:
			if(data[0]==0x01)
			{
				u32 ir_key_index;
				for(ir_key_index=0;ir_key_index<IR_KEY_NUMBER4;ir_key_index++)
				{
					IR_KeyCode_Map4[ir_key_index].short_key=data[ir_key_index*3+1];
					IR_KeyCode_Map4[ir_key_index].long_key=data[ir_key_index*3+2];
					IR_KeyCode_Map4[ir_key_index].key_type=data[ir_key_index*3+3];
				}
			}
			else if(data[0]==0x02)
			{
				ACR_IR_TestModel=data[1];
			}
			break;
#endif
#if DAB_FM_FUN==1
			case MCU_RX_DAB_SID:
				DAB_SID=data[0];
				DAB_SID<<=8;
				DAB_SID|=data[1];
				break;
#endif
#if MAX9288_FUN==1
#if MODEL==LINUX_G019_G0
		case MCU_RX_9288_REINIT_CMD:
			if(data[0]==1)
			{
				MAX9288_PowerOn();
			}
			break;
#endif
#endif
#if MODEL==LINUX_1276_MG||MODEL==LINUX_1325W_53
		case MCU_RX_DAB_ANT_POWER_CMD:
			if(data[0]==1)
			{
				DAB_ANT_POWER_ON;
			}
			else
			{
				DAB_ANT_POWER_OFF;
			}
			break;
#endif
		case MCU_RX_DPA_CMD:
			if(data[0]==READ_DAP_INFO) 
			{
				PostMessage(NAVI_MODULE, MCU_TX_DPA_INFO,0);
			}
#if TAS6424M_Q1_FUN == 1
			if(data[0]==DC_DIAG_REQUEST || data[0]==AC_DIAG_REQUEST || data[0]==AMP_STATUS_REQUEST)
			{
				PostMessage(TAS6424_MODULE, data[0],0);
			}
#endif
			break;
		default:
			break;
	}
#if APP_COM_DEBUG_FUN==1
	printf("McuRxService:end\r\n");
#endif	
} 

void APP_DataAnalyse(void)
{
	u16 start=McuRxBuffer.head;
	u16 end=McuRxBuffer.tail;
	u8 data[MAX_APP_RX_LENGTH];
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
			buffer_data_length=MAX_APP_RX_BUFFER_LENGTH-i+end;
		}
		
		if(buffer_data_length>=MIN_APP_RX_LENGTH)
		{
			head_code1_index=i;
			head_code2_index=i+1;
			if(head_code2_index>=MAX_APP_RX_BUFFER_LENGTH)
			{
				head_code2_index-=MAX_APP_RX_BUFFER_LENGTH;
			}
			if(HEAD_ADDRESS_APP==McuRxBuffer.data[head_code1_index]
				&&HEAD_ADDRESS_MCU==McuRxBuffer.data[head_code2_index])
			{
				packet_length_index=i+4;
				if(packet_length_index>=MAX_APP_RX_BUFFER_LENGTH)
				{
					packet_length_index-=MAX_APP_RX_BUFFER_LENGTH;
				}
				packet_length=McuRxBuffer.data[packet_length_index];
				if(packet_length<=MAX_APP_RX_LENGTH)
				{
					if(buffer_data_length>=packet_length)
					{
						checksum=0;
						packet_counter=i;
						for(j=0;j<packet_length;j++)
						{
							checksum^=McuRxBuffer.data[packet_counter];
							data[j]=McuRxBuffer.data[packet_counter];
							packet_counter++;
							if(packet_counter>=MAX_APP_RX_BUFFER_LENGTH)
							{
								packet_counter=0;
							}
						}
						if(0xFF==checksum)
						{
							McuRxBuffer.head=packet_counter;
							packet_counter=i;
							for(j=0;j<packet_length;j++)
							{
								McuRxBuffer.data[packet_counter]=0;
								packet_counter++;
								if(packet_counter>=MAX_APP_RX_BUFFER_LENGTH)
								{
									packet_counter=0;
								}
							}
#if DAB_UPDATE_FUN==1
							if(F_KS_UPDATE_REQ)
							{
								KS_UpdateAppDataPro(data);
							}
							else
#endif
#if CANBOX_UPDATE_FUN_HIWORLD==1||CANBOX_BNR_UPDATE_FUN==1||CANBOX_UPDATE_FUN_GOLF==1||CANBOX_UPDATE_FUN_SIMPLE==1
							if(IsReqCanUpdate())
							{
								CanUpdate_AppDataService(data);
							}
							else
#endif
							{
								McuRxService(data);
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
		}
		else
		{
			break;
		}
		McuRxBuffer.data[i]=0;
		i++;
		if(i>=MAX_APP_RX_BUFFER_LENGTH)
		{
			i=0;
		}
		McuRxBuffer.head=i;
	}
}

void NotifyAppStateMsg(MACHINE_MISC_STATE_T state,u8 prm)
{	
	PostMessage(NAVI_MODULE,MCU_TX_MACHINE_MISC_STATE,(((u16)state)<<8)|prm);	
}

void NAVI_Reset_Hold(void)  				
{
#if PLATFORM_TYPE==UNISOC_PLATFORM
	UNI7870_RESET_ON;
#else
	MT3360_RESET_ON;
#endif
	OsWorkOff(); 
}	

void NAVI_Reset_Release(void)      			
{
#if PLATFORM_TYPE==UNISOC_PLATFORM
	UNI7870_RESET_OFF;
#else
	MT3360_RESET_OFF;
#endif
	OsWorkOn();
}

void NAVI_Off(void)           					
{
#if APP_COM_DEBUG_FUN==1
	printf("NAVI_off\r\n");
#endif
	APP_Flag.byte=0x00;
	APP_Status =APP_STARTING;
#if POWER_ONE_HOUR_MODE_FUN==1
	SetPowerOnOkFlag(0);
#endif
}	

void NAVI_Init(void)
{
	u32 i;
	McuRxBuffer.head=0;
	McuRxBuffer.tail=0;
	for(i=0;i<MAX_APP_RX_BUFFER_LENGTH;i++)
	{
		McuRxBuffer.data[i]=0;
	}
#if MCU_ACK_MESSAGE_MODE==1
	ACK_ClearMessage();
#endif
	APP_Flag.byte=0x00;
	AppUartFlag.byte=0x00;
#if APP_COM_DEBUG_FUN==1
	printf("NAVI_Init\r\n");
#endif
	APP_Status=APP_STARTING;
	OS_WorkState=OS_WORK_IDLE;
	Data_Length_IN_Buffer=0;
	Uart_Rx_Seq_Num=0;
	Uart_Tx_Seq_Num=0;
	Uart_ReSend_Timer=0;
	Uart_Tx_counter=0;
}

#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
void AppBackupDataSave(void)
{
	u32 i;
	u32 j;
#if APP_COM_DEBUG_FUN==1
	printf("AppBackupDataSave:start\r\n");
#endif	
	for(i=0;i<APP_BACKUP_DATA_LENGTH;i++)
	{
		if(AppBackupData[i]!=AppBackupData_Bak[i])
		{
			break;
		}
	}
	if(i<APP_BACKUP_DATA_LENGTH)
	{
		for(j=0;j<APP_BACKUP_DATA_LENGTH;j++)
		{
			AppBackupData_Bak[j]=AppBackupData[j];
		}
		EEPROM_Save_AppBackupData();
#if APP_COM_DEBUG_FUN==1
		printf("AppBackupDataSave:end\r\n");
#endif	
	}
}
void AppBackupDataResetClear(void)
{
	u32 i;
#if APP_COM_DEBUG_FUN==1
	printf("AppBackupDataResetClear:start\r\n");
#endif	
	for(i=0;i<(APP_BACKUP_DATA_LENGTH-1);i++)
	{
		AppBackupData[i]=0;
		AppBackupData_Bak[i]=0;
	}
	EEPROM_Save_AppBackupData();
#if APP_COM_DEBUG_FUN==1
	printf("AppBackupDataResetClear:end\r\n");
#endif	
}
void AppBackupDataUpdateClear(void)
{
	u32 i;
#if APP_COM_DEBUG_FUN==1
	printf("AppBackupDataUpdateClear:start\r\n");
#endif
	for(i=0;i<APP_BACKUP_DATA_LENGTH;i++)
	{
		AppBackupData[i]=0;
		AppBackupData_Bak[i]=0;
	}
	EEPROM_Save_AppBackupData();
#if APP_COM_DEBUG_FUN==1
	printf("AppBackupDataUpdateClear:end\r\n");
#endif
}
#endif

