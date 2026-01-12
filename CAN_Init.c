#include "public.h"

#if CAN_FUNCTION==1
void CAN1_SetErrorFlag(void)
{
	RTC->BKP_DR2=0x12345678;
}
void CAN1_ClearErrorFlag(void)
{
	RTC->BKP_DR2=0x0;
}
u8 CAN1_GetErrorFlag(void)
{
	u8 result=0;
	if(RTC->BKP_DR2==0x12345678)
	{
		result=1;
	}
	return result;
}

int32_t CAN1_IRQnTask(uint32_t event, uint32_t wparam, uint32_t lparam)
{
	if(event&CAN_EVENT_RECVMSG)
	{
		if(CAN_IsMsgInReceiveBuf(CAN1))
		{
			u32 i;
			CAN_MSG_INFO RxMessage;
			CAN_MESSAGE_INFO message;
			CAN_MessageRead(CAN1,&RxMessage);
			message.ID=RxMessage.ID;
			message.DLC=RxMessage.DLC;
			message.IDE=RxMessage.IDE;
			message.RTR=RxMessage.RTR;
			for(i=0;i<8;i++)
			{
				message.Data[i]=RxMessage.Data[i];
			}
			if(((CanRxBuffer.tail+1)% CAN_RX_BUFFER_LENGTH)!=CanRxBuffer.head)
			{
				CanRxBuffer.message[CanRxBuffer.tail]=message;
				CanRxBuffer.tail=(CanRxBuffer.tail+1)%CAN_RX_BUFFER_LENGTH;
			}
		}
	}
	F_CAN_INTERRUPT=1;
	return 1;
}

int32_t SPM_IRQnTask(uint32_t wparam, uint32_t lparam)
{
	if(wparam&0x80)
	{
		F_CAN_SLEEP=0;
	}
	return 1;
}

void CAN1_Init(void)
{
	CAN_Config CAN_ConfigStructure = {0};
	CAN_BaudrateConfig CAN_BaudrateConfigStructure = {0};

	GPIO_SetFunc(GPIO_CAN1_RX_PIN,1);//CAN1_TX
	GPIO_SetFunc(GPIO_CAN1_TX_PIN,1);//CAN1_RX

	CAN_ConfigStructure.autoReset = ENABLE;//
	CAN_ConfigStructure.canMode = CAN_MODE_NORMAL;//通信模式
	CAN_ConfigStructure.clockSrc = 0;//CAN_CLKSRC_AHB
	CAN_ConfigStructure.interruptEnable = ENABLE;
	CAN_ConfigStructure.ROM = DISABLE;
	CAN_ConfigStructure.TPSS = 0;//PTB 单次发送模式 高优先级
	CAN_ConfigStructure.TSMODE = 0;//0:PTB,1:STB
	CAN_ConfigStructure.TSSS = ENABLE;//STB 单次发送模式 次优先级

	//BandRate = (48M / (S_PRESC + 1) / ((S_SEG_1 + 2) + (S_SEG_2 + 1))) 
	//                                                                    tSeg1                tSeg2     
	//采样点 = (tSeg1 / (tSeg1 + tSeg2))
#if CAN_FUN_PEUGEOT_207==1
	/*********************** 125K **************************/
	CAN_BaudrateConfigStructure.S_PRESC = 15;
	CAN_BaudrateConfigStructure.S_SEG_1 = 16;
	CAN_BaudrateConfigStructure.S_SEG_2 =5;
	CAN_BaudrateConfigStructure.S_SJW = 3;
#elif CAN_FUN_HYUNDAI_TUCSON==1
	CAN_BaudrateConfigStructure.S_PRESC = 19;
	CAN_BaudrateConfigStructure.S_SEG_1 = 16;
	CAN_BaudrateConfigStructure.S_SEG_2 =5;
	CAN_BaudrateConfigStructure.S_SJW = 3;
#else
	/*********************** 500K **************************/
	CAN_BaudrateConfigStructure.S_PRESC = 5;
	CAN_BaudrateConfigStructure.S_SEG_1 = 11;
	CAN_BaudrateConfigStructure.S_SEG_2 = 2;
	CAN_BaudrateConfigStructure.S_SJW = 2;
#endif

	CAN_Initialize(CAN1, &CAN_ConfigStructure, &CAN_BaudrateConfigStructure);
	CAN_SetEventCallBack(CAN1, CAN1_IRQnTask);
	
	CAN1->BIT.RESET = 1;
#if CAN_FUN_PEUGEOT_207==1
	CAN_SetFilter(CAN1,0,CAN_ID_NMM_C_1,0x00000000,1);
	CAN_SetFilter(CAN1,1,CAN_ID_FEI_F,0x00000000,1);
	
	CAN_SetFilter(CAN1,2,CAN_ID_PASD_C,0x00000000,1);
	CAN_SetFilter(CAN1,3,CAN_ID_FAM_INFO,0x00000000,1);
	CAN_SetFilter(CAN1,4,CAN_ID_BCM_PAS,0x00000000,1);
	CAN_SetFilter(CAN1,5,CAN_ID_BCM_EMS67,0x00000000,1);
	CAN_SetFilter(CAN1,6,CAN_ID_CCNC1_C,0x00000700,1);
	CAN_SetFilter(CAN1,7,(CAN_ID_VIN1_MM&0xFFFFFF30),0x000000C0,1);
	CAN_SetFilter(CAN1,8,(CAN_ID_NMM_C_2&0xFFFFFFF6),0x00000009,1);
	CAN_SetFilter(CAN1,9,(CAN_ID_LS_BCM_HS3&0xFFFFFFF6),0x00000009,1);
	CAN_SetFilter(CAN1,10,(CAN_ID_FDS_D&0xFFFFFFFC),0x00000003,1);
	CAN_SetFilter(CAN1,11,(CAN_ID_FOS_F&0xFFFFFFF3),0x0000000C,1);
	CAN_SetFilter(CAN1,12,(CAN_ID_LS_BCM_OS&0xFFFFFFFC),0x00000003,1);
	CAN_SetFilter(CAN1,13,CAN_ID_BACKL_IC,0x00000000,1);
	CAN_SetFilter(CAN1,14,CAN_ID_CLUSTER_ODO,0x00000007,1);
	CAN_SetFilter(CAN1,15,CAN_ID_CCN_TPMS_SMS,0x00000000,1);
#elif CAN_FUN_HAIMA_S7==1
	CAN_SetFilter(CAN1,0,CAN_ID_GW,0x00000000,1);
	CAN_SetFilter(CAN1,1,CAN_ID_BCM,0x00000000,1);
	CAN_SetFilter(CAN1,2,CAN_ID_HVAC,0x00000000,1);
	CAN_SetFilter(CAN1,3,CAN_ID_PEPS,0x00000000,1);
	CAN_SetFilter(CAN1,4,CAN_ID_SVM,0x00000000,1);
	CAN_SetFilter(CAN1,5,CAN_ID_DIAG_IST_REQ,0x00000000,1);
	CAN_SetFilter(CAN1,6,CAN_ID_SPEED,0x00000000,1);
	CAN_SetFilter(CAN1,7,CAN_ID_THROTTLE,0x00000000,1);
	CAN_SetFilter(CAN1,8,CAN_ID_GEAR,0x00000000,1);
#elif CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_TIGGO_5==1||CAN_FUN_CHERY_TIGGO_7==1||CAN_FUN_CHERY_ARRIZO_6==1||CAN_FUN_CHERY_TIGGO_2==1||CAN_FUN_CHERY_ARRIZO_5==1||CAN_FUN_CHERY_TIGGO_5X_T19==1
	CAN_SetFilter(CAN1,0,CAN_ID_BCM_4,0x00000000,1);
	CAN_SetFilter(CAN1,1,CAN_ID_ICM_1,0x00000000,1);
	CAN_SetFilter(CAN1,2,CAN_ID_ICM_2,0x00000000,1);
	CAN_SetFilter(CAN1,3,CAN_ID_NMm_BCM,0x00000000,1);
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_ARRIZO_5==1
	CAN_SetFilter(CAN1,4,CAN_ID_CLM_2,0x00000000,1);
	CAN_SetFilter(CAN1,5,CAN_ID_IPM_2,0x00000000,1);
	CAN_SetFilter(CAN1,6,CAN_ID_PEPS_2,0x00000000,1);
	CAN_SetFilter(CAN1,7,CAN_ID_ICM_3,0x00000000,1);
	CAN_SetFilter(CAN1,8,CAN_ID_BCM_SAM_1_G,0x00000000,1);
	CAN_SetFilter(CAN1,9,CAN_ID_BCM_ABS_G,0x00000000,1);
	CAN_SetFilter(CAN1,10,CAN_ID_DIAGNOSTIC_RX_ID,0x00000000,1);
#if MODEL==LINUX_Q068_00
	CAN_SetFilter(CAN1,11,CAN_ID_BCM_10,0x00000000,1);
#endif
#elif CAN_FUN_CHERY_TIGGO_5==1||CAN_FUN_CHERY_TIGGO_7==1
	CAN_SetFilter(CAN1,4,CAN_ID_CLM_2,0x00000000,1);
	CAN_SetFilter(CAN1,5,CAN_ID_IPM_2,0x00000000,1);	
	CAN_SetFilter(CAN1,6,CAN_ID_AVM_1,0x00000000,1);
	CAN_SetFilter(CAN1,7,CAN_ID_IPM_1,0x00000000,1);
	CAN_SetFilter(CAN1,8,CAN_ID_BCM_5,0x00000000,1);
	CAN_SetFilter(CAN1,9,CAN_ID_ICM_3,0x00000000,1);
	CAN_SetFilter(CAN1,10,CAN_ID_BCM_SAM_1_G,0x00000000,1);
	CAN_SetFilter(CAN1,11,CAN_ID_BCM_ABS_G,0x00000000,1);
#if MODEL==LINUX_Q068_21||MODEL==LINUX_Q068A_21
	CAN_SetFilter(CAN1,12,CAN_ID_BCM_7,0x00000000,1);
#if 0
	CAN_SetFilter(CAN1,13,CAN_ID_BCM_EPB_G,0x00000000,1);
#endif
#endif
#elif CAN_FUN_CHERY_ARRIZO_6==1
	CAN_SetFilter(CAN1,4,CAN_ID_IPM_2,0x00000000,1);
	CAN_SetFilter(CAN1,5,CAN_ID_AVM_1,0x00000000,1);
	CAN_SetFilter(CAN1,6,CAN_ID_LDW_1,0x00000000,1);
	CAN_SetFilter(CAN1,7,CAN_ID_ICM_3,0x00000000,1);
	CAN_SetFilter(CAN1,8,CAN_ID_BCM_SAM_1_G,0x00000000,1);
	CAN_SetFilter(CAN1,9,CAN_ID_BCM_ABS_G,0x00000000,1);
	CAN_SetFilter(CAN1,10,CAN_ID_ICM_4,0x00000000,1);
	CAN_SetFilter(CAN1,11,CAN_ID_BCM_PEPS_G,0x00000000,1);
#elif CAN_FUN_CHERY_TIGGO_2==1
    CAN_SetFilter(CAN1,4,CAN_ID_BCM_SAM_1_G,0x00000000,1);
    CAN_SetFilter(CAN1,5,CAN_ID_BCM_ABS_G,0x00000000,1);
    CAN_SetFilter(CAN1,6,CAN_ID_ICM_3,0x00000000,1);
#endif
#elif CAN_FUN_HAIMA_S5==1
	CAN_SetFilter(CAN1,0,CAN_ID_VEHICLE_WARNING,0x00000000,1);
	CAN_SetFilter(CAN1,1,CAN_ID_BCM_INFO,0x00000000,1);
	CAN_SetFilter(CAN1,2,CAN_ID_TCU_INFO,0x00000000,1);
	CAN_SetFilter(CAN1,3,CAN_ID_STEER_INFO,0x00000000,1);
#elif CAN_FUN_HYUNDAI_TUCSON==1
	CAN_SetFilter(CAN1,0,CAN_ID_ALARM,0x00000000,1);
	CAN_SetFilter(CAN1,1,CAN_ID_BRIGHTNESS,0x00000000,1);
	CAN_SetFilter(CAN1,2,CAN_ID_DOOR_STATUS,0x00000000,1);
	CAN_SetFilter(CAN1,3,CAN_ID_PARKING_SENSORS,0x00000000,1);
	CAN_SetFilter(CAN1,4,CAN_ID_VEHICLE_INDICATIONS,0x00000000,1);
#else
#endif
	CAN1->BIT.RESET = 0;
#if CAN_WAKEUP_FUN==1||CAN_FUN_HAIMA_S5==1
	SPM_EnableModuleWakeup(SPM_MODULE_CAN1,1);
	SPM_EnableModuleSPMIRQ(SPM_MODULE_CAN1,1);
	SPM_SetSPMIRQHandler(SPM_IRQnTask);
#endif
	CAN1_ClearTxMessage();
	CAN1_ClearRxMessage();
	F_CAN_INIT=1;

#if MODEL==LINUX_D068_55||MODEL==LINUX_D078_55||MODEL==LINUX_P058_55||MODEL==LINUX_D065_55
#if MODEL==LINUX_P058_55
#else
	GPIO_SetFunc(GPIO_CAN_POWER_PIN, GPIOMUX_FUNC0);
	GPIO_SetDir(GPIO_CAN_POWER_PIN,OUTPUT);
	CAN_IC_POWER_ON;
	Delay_ms(250);
#endif
	GPIO_SetFunc(GPIO_CAN_STANDBY_PIN,GPIOMUX_FUNC0);//CAN1_STDBY
	GPIO_SetDir(GPIO_CAN_STANDBY_PIN,OUTPUT);
	CAN_IC_STANDBY_OFF;
	
	GPIO_SetFunc(GPIO_CAN_EN_PIN,GPIOMUX_FUNC0);// CAN_EN
	GPIO_SetDir(GPIO_CAN_EN_PIN,OUTPUT);
	CAN_IC_ENABLE;
	GPIO_SetFunc(GPIO_CAN_ERR_SIG_PIN,GPIOMUX_FUNC0);// CAN_ERR
	GPIO_SetDir(GPIO_CAN_ERR_SIG_PIN,INPUT);
#elif MODEL==LINUX_6178_58
	GPIO_SetFunc(GPIO_CAN_POWER_PIN, GPIOMUX_FUNC0);
	GPIO_SetDir(GPIO_CAN_POWER_PIN,OUTPUT);
	CAN_IC_POWER_ON;
	
	GPIO_SetFunc(GPIO_CAN_STANDBY_PIN,GPIOMUX_FUNC0);//CAN1_STDBY
	GPIO_SetDir(GPIO_CAN_STANDBY_PIN,OUTPUT);
	CAN_IC_STANDBY_OFF;
#elif MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
	GPIO_SetFunc(GPIO_CAN_STANDBY_PIN,GPIOMUX_FUNC0);//CAN1_STDBY
	GPIO_SetDir(GPIO_CAN_STANDBY_PIN,OUTPUT);
	CAN_IC_STANDBY_OFF;
#else
	GPIO_SetFunc(GPIO_CAN_STANDBY_PIN,GPIOMUX_FUNC0);//CAN1_STDBY
	GPIO_SetDir(GPIO_CAN_STANDBY_PIN,OUTPUT);
	CAN_IC_STANDBY_OFF;
#endif
}







u8 CAN1_Transmit(void)
{
	CAN_MESSAGE_INFO TxMessage;
	CAN_MSG_INFO message;
	u32 i;
	u8 result=0;

	if(CanTxBuffer.length)
	{
		if(!CAN_IsTransmitBusy(CAN1, TRANSMIT_SECONDARY)) 
		{
			FormatMemery((u8 *) &TxMessage, sizeof(TxMessage));
			TxMessage=CanTxBuffer.message[CanTxBuffer.head];
			message.ID=TxMessage.ID;
			message.RTR=TxMessage.RTR;
			message.IDE=TxMessage.IDE;
			message.DLC=TxMessage.DLC;
			for(i=0;i<8;i++)
			{
				message.Data[i]=TxMessage.Data[i];
			}
#if CAN_FUN_HAIMA_S7==1
			if(Haima_S7_CheckTxMessage(message.ID,(u8 *)&message.Data[0]))
			{
				if(!CAN_MessageSend(CAN1,&message,TRANSMIT_SECONDARY))
				{
					CanTxBuffer.head=(CanTxBuffer.head+1)%CAN_TX_BUFFER_LENGTH;
					CanTxBuffer.length--;
					result=1;
				}
			}
			else
			{
				CanTxBuffer.head=(CanTxBuffer.head+1)%CAN_TX_BUFFER_LENGTH;
				CanTxBuffer.length--;
			}
#else
			if(!CAN_MessageSend(CAN1,&message,TRANSMIT_SECONDARY))
			{
				CanTxBuffer.head=(CanTxBuffer.head+1)%CAN_TX_BUFFER_LENGTH;
				CanTxBuffer.length--;
				result=1;
			}
#endif
		}
	}
	return result;
}

void CAN1_TransBytefraem(u32 ID,u8 *data,u8 length)
{
    CAN_MSG_INFO TxMessage;
    FormatMemery((u8 *) &TxMessage, sizeof(TxMessage));
    
	TxMessage.ID=ID;
	TxMessage.IDE=CAN_IDE_STD;
	TxMessage.RTR=CAN_RTR_STD;
	TxMessage.DLC=length;
	Mem_strcpy(TxMessage.Data,data,length);
	CAN_MessageSend(CAN1,&TxMessage,TRANSMIT_SECONDARY);
}

#endif

