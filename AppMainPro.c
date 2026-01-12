#include "public.h"
u16 AppMainTimer;
POWER_ON_TX_INDEX AppMessageCounter;
OS_WORK_STATE OS_WorkState;
APP_UPDATE_STATE AppUpdateState;
u16 AppUpdateTimer;
u16 AppUpdateDetTimer;
u16 AppUpdateDetTimerA;
u16 AppUpdateDetTimerB;
u16 APPMonitorTimer;
u16 AppReadyTimer;
#if SUZUKI_UART_FUN==1
u16 AppWaitPowerOffTimer;
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
u16 AppCheckAccTimer;
u16 AppCheckCanTimer;
#endif
u8 Emmc_Startup;

u8 AppUpdateFlag;
u8 AppUpdateFlagA;
u8 AppUpdateFlagB;
u8 AppUpdateFlagC;
u8 AppUpdateFlagD;
u8 AppUpdateStatusB;
u8 AppResetCounter;
u8 AppUpdating=0;

const u8 PostAppMessage[]=
{
	0,
	MCU_TX_MCU_VERSION,
	MCU_TX_CLOCK,
	MCU_TX_VOLUME,
	MCU_TX_DISC_STATE,	
#if CANBOX_FUNC_MULTIPLE==1
	MCU_TX_CAN_MULTIPLE_TYPE,
#endif
#if MODEL==LINUX_N039_DZ
	MCU_TX_HW_VERSION,
#endif		
};

void APPMonitorPro(void)
{
 	if(!Is_Machine_Power
		||APP_READY!=APP_Status
		||AppUpdateState!=APP_UPDATE_IDLE
		||F_CLOSE_BEAT_HEART_CHECK) 
	{
		APPMonitorTimer=APP_MONITOR_TIME;
		return;
	}
	if(APPMonitorTimer) 
	{
		APPMonitorTimer--;
		if(0==APPMonitorTimer)
		{
			SystemReset();
		}
	}
}

#if PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM||PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM\
	||COMPATIBLE_WITH_NANDFLASH_EMMC_FUN==1
void AppUpdateGpioConfig(void)
{
#if defined(AUTOCHIPS_AC781X)
	GPIO_SetFunc(GPIO_HWCFG2_PIN, GPIOMUX_FUNC0);
	GPIO_SetFunc(GPIO_HWCFG3_PIN, GPIOMUX_FUNC0);

	GPIO_SetDir(GPIO_HWCFG2_PIN,OUTPUT);
	GPIO_SetDir(GPIO_HWCFG3_PIN,OUTPUT);
#elif defined(HDSC_HC32F460)
	stc_port_init_t stc_port_init;
	
	FormatMemery((u8 *)(&stc_port_init),sizeof(stc_port_init_t));
	stc_port_init.enPinMode=Pin_Mode_Out;
	stc_port_init.enPinDrv=Pin_Drv_H;
	
	PORT_Init(GPIO_HWCFG2_PORT,GPIO_HWCFG2_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_HWCFG2_PORT,GPIO_HWCFG2_PIN,Func_Gpio,Disable);

	PORT_Init(GPIO_HWCFG3_PORT,GPIO_HWCFG3_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_HWCFG3_PORT,GPIO_HWCFG3_PIN,Func_Gpio,Disable);
#elif defined(HDSC_HC32L072)
	stc_gpio_cfg_t stc_gpio_cfg;

	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,1); 

	FormatMemery((u8 *)(&stc_gpio_cfg),sizeof(stc_gpio_cfg_t));
	
	Gpio_Init(GPIO_HWCFG2_PORT,GPIO_HWCFG2_PIN,&stc_gpio_cfg);
	Gpio_SetAfMode(GPIO_HWCFG2_PORT,GPIO_HWCFG2_PIN,GpioAf0);

	Gpio_Init(GPIO_HWCFG3_PORT,GPIO_HWCFG3_PIN,&stc_gpio_cfg);
	Gpio_SetAfMode(GPIO_HWCFG3_PORT,GPIO_HWCFG3_PIN,GpioAf0);
#elif defined(STM32_F103VC)
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_HWCFG2_PIN;
	GPIO_Init(GPIO_HWCFG2_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_HWCFG3_PIN;
	GPIO_Init(GPIO_HWCFG3_PORT, &GPIO_InitStructure);
#if defined(STM32F10X_MD)
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_HWCFG2_PIN;
	GPIO_Init(GPIO_HWCFG2_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_HWCFG3_PIN;
	GPIO_Init(GPIO_HWCFG3_PORT, &GPIO_InitStructure);
#endif
#elif defined(STM32F401xx)
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT; 
	GPIO_InitStructure.GPIO_Pin = GPIO_HWCFG2_PIN;
	GPIO_Init(GPIO_HWCFG2_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_HWCFG3_PIN;
	GPIO_Init(GPIO_HWCFG3_PORT, &GPIO_InitStructure);
#endif
	F_UART_INIT_FALG=0;
}
#endif

#if PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM
void AppStartUpGpioConfig(void)
{
	stc_gpio_cfg_t stc_gpio_cfg;

	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,1); 

	FormatMemery((u8 *)(&stc_gpio_cfg),sizeof(stc_gpio_cfg_t));
	
	stc_gpio_cfg.enDir=GpioDirIn;
	
	Gpio_Init(GPIO_HWCFG2_PORT,GPIO_HWCFG2_PIN,&stc_gpio_cfg);
	Gpio_SetAfMode(GPIO_HWCFG2_PORT,GPIO_HWCFG2_PIN,GpioAf0);
	
	Gpio_Init(GPIO_HWCFG3_PORT,GPIO_HWCFG3_PIN,&stc_gpio_cfg);
	Gpio_SetAfMode(GPIO_HWCFG3_PORT,GPIO_HWCFG3_PIN,GpioAf0);
	
	F_UART_INIT_FALG=0;
}
#endif

#if COMPATIBLE_WITH_NANDFLASH_EMMC_FUN==1
void Startup_Mode_Detect()
{
	u8 port1;
	u8 port2;
	port1=HWCFG2_PIN_LEVEL;
	port2=HWCFG3_PIN_LEVEL;
	
	if(port1&&port2)
	{
		AppUpdateGpioConfig();
		HWCFG2_HIGH_LEVEL;
		HWCFG3_LOW_LEVEL;
	}
	else if((port1==0)&&port2)
	{
		Emmc_Startup=1;
	}
}
#endif

void AppUpdateStart(void)
{
	Hard_Mute();
	AppUpdateState=APP_UPDATE_RESET_ON;
	AppUpdateTimer=T500MS_10;
	AppReadyTimer=0;
}

void AppUpdateDetPro(void)
{
	u8 port;
	
	if(nPowerState!=POWER_NORMAL_RUN)
	{
		AppUpdateFlag=0;
		AppUpdateDetTimer=T6S_10;
		return;
	}
	
	port=APP_UPDATE_DET_LEVEL;
	if(AppUpdateDetTimer)
	{
		AppUpdateDetTimer--;
	}
	if(AppUpdateDetTimer==0)
	{
		if(!port)
		{
			AppUpdateFlag=1;
		}
		else
		{
			AppUpdateFlag=0;
		}
	}
	if((port&&(!AppUpdateFlag))
		||((!port)&&AppUpdateFlag))
	{
		AppUpdateDetTimer=T1S_10;
	}
}

#if PLATFORM_TYPE!=SUNPLUS_8368U_MOTORCYCLE_PLATFORM
void AppUpdateDetSteerKey(void)
{
	u8 port;
	u16 temp1;
	u16 temp2;
	u8 level1;
	u8 level2;
	
	if(nPowerState!=POWER_NORMAL_RUN)
	{
		AppUpdateFlagA=0;
		AppUpdateDetTimerA=T5S_10;
		return;
	}
#if MODEL==LINUX_Y039_55||MODEL==LINUX_N039_DZ||MODEL==LINUX_1295WH_PC||MODEL==LINUX_2339WA_93||MODEL==LINUX_2349WA_93||MODEL==LINUX_Y049_55
	temp1=Get_Adc(ADCH_WHEEL_KEY1);
	temp2=temp1;
#else
	temp1=Get_Adc(ADCH_WHEEL_KEY1);
	temp2=Get_Adc(ADCH_WHEEL_KEY2);
#endif
	if(temp1<320)
	{
		level1=1;
	}
	else
	{
		level1=0;
	}
	if(temp2<320)
	{
		level2=1;
	}
	else
	{
		level2=0;
	}

	port = level1&level2;
	if(AppUpdateDetTimerA)
	{
		AppUpdateDetTimerA--;
	}
	if(AppUpdateDetTimerA==0)
	{
		if(port)
		{
			AppUpdateFlagA=1;
		}
		else
		{
			AppUpdateFlagA=0;
		}
	}
	if((port&&AppUpdateFlagA)
		||((!port)&&(!AppUpdateFlagA)))
	{
		AppUpdateDetTimerA=T5S_10;
	}
}
#endif

void AppUpdatePro(void)
{
	AppUpdateDetPro();
#if PLATFORM_TYPE!=SUNPLUS_8368U_MOTORCYCLE_PLATFORM
#if 0//CPU_SUNPLUS_8368XU==1
#else
	AppUpdateDetSteerKey();
#endif
#endif
	
	if(AppUpdateTimer)
	{
		AppUpdateTimer--;
	}

#ifndef FLASH_SIZE_64K	
	AppUpdateDetTimerB++;
	if(AppUpdateDetTimerB>T15S_10)
	{
		AppUpdateFlagB=0;
		AppUpdateStatusB=0;
	}
#endif
	switch(AppUpdateState)
	{
		case APP_UPDATE_IDLE:
			if(AppUpdateTimer)
			{
				break;
			}
#if AIM_915_916_FUN==1
#if defined(AUTOCHIPS_AC781X)
	        if(RTC->BKP_DR1==0xA343FBEA)
#elif defined(HDSC_HC32F460)
#elif defined(HDSC_HC32L072)
#elif defined(STM32_F103VC)
#endif
	        {
				AppUpdateState = APP_UPDATE_ESCAPE;
				AppUpdateTimer=T8S_10;
				break;    
	        }
#endif        	
			if(AppUpdateFlag==1
			    ||AppUpdateFlagA==1
			    ||AppUpdateFlagC==1
				||AppUpdateFlagD==1)
			{
				AppUpdating=1;
				Hard_Mute();
				AppUpdateState=APP_UPDATE_RESET_ON;
				AppUpdateTimer=T500MS_10;
				AppReadyTimer=0;
			}
			break;
		case APP_UPDATE_RESET_ON:
			if(AppUpdateTimer)
			{
				break;
			}
#if APP_MAIN_DEBUG_FUN==1
	printf("APP_UPDATE_RESET_ON\r\n");
#endif
#if PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM||PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM
			AppUpdateGpioConfig();
			HWCFG2_LOW_LEVEL;
			HWCFG3_LOW_LEVEL;
#elif PLATFORM_TYPE==SUNPLUS_8368P_PLATFORM
#if COMPATIBLE_WITH_NANDFLASH_EMMC_FUN==1
			AppUpdateGpioConfig();
#endif
			HWCFG2_LOW_LEVEL;
			HWCFG3_LOW_LEVEL;
#else
#if APP_UPDATE_BY_USB==1
			HWCFG2_LOW_LEVEL;
			HWCFG3_HIGH_LEVEL;	
#else
			HWCFG2_HIGH_LEVEL;
			HWCFG3_LOW_LEVEL;	
#endif
#endif
#if PLATFORM_TYPE==UNISOC_PLATFORM
			UNI7870_RESET_ON;
#else
			MT3360_RESET_ON;
#endif
#if AIM_915_916_FUN==1			
			TURN_OFF_SYSTEM_POWER;
#endif
			AppUpdateTimer=T100MS_10;
			AppUpdateState=APP_UPDATE_RESET_OFF;
			break;
		case APP_UPDATE_RESET_OFF:
			if(AppUpdateTimer)
			{
				break;
			}
#if APP_MAIN_DEBUG_FUN==1
	printf("APP_UPDATE_RESET_OFF\r\n");
#endif
#if PLATFORM_TYPE==UNISOC_PLATFORM
	UNI7870_RESET_OFF;
#else
	MT3360_RESET_OFF;
#endif
#if AIM_915_916_FUN==1
            TURN_ON_SYSTEM_POWER;
			AIM_Init_StatusToConfig(1);
#endif
			AppUpdateTimer=T2S_10;
			AppUpdateState=APP_UPDATE_START;
			break;
		case APP_UPDATE_START:
			if(AppUpdateTimer)
			{
				break;
			}
#if APP_MAIN_DEBUG_FUN==1
			printf("APP_UPDATE_START\r\n");
#endif
#if PLATFORM_TYPE==SUNPLUS_8388_PLATFORM
			HWCFG2_HIGH_LEVEL;
			HWCFG3_HIGH_LEVEL;	
#elif PLATFORM_TYPE==SUNPLUS_8368P_PLATFORM
			if(Emmc_Startup)
			{
				HWCFG2_LOW_LEVEL;
				HWCFG3_HIGH_LEVEL;
			}
			else
			{
				HWCFG2_HIGH_LEVEL;
				HWCFG3_LOW_LEVEL;	
			}			
#elif PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			AppUpdateTimer=T1S_10;
#endif
			AppUpdateState=APP_UPDATE_WAIT;
			break;
		case APP_UPDATE_WAIT:
#if APP_MAIN_DEBUG_FUN==1
	printf("APP_UPDATE_WAIT\r\n");
#endif
#if PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM
			if(APP_UPDATE_DET_LEVEL==0)
			{
				AppUpdateTimer=T1S_10;
			}
			else if(AppUpdateTimer==0)
			{
#if 0
				//SoftReset();
#else
#if defined(AUTOCHIPS_AC781X)
				USART4_InitConfig(115200);
#elif defined(HDSC_HC32F460)
				USART3_InitConfig(115200);
#elif defined(HDSC_HC32L072)
				USART3_InitConfig(115200);
#elif defined(STM32_F103VC)
#if defined(STM32F10X_MD)
				UART2_InitConfig(115200);
#else
                UART4_InitConfig(115200);
#endif
#elif defined(STM32F401xx)
				USART6_InitConfig(115200);		
#endif
				AppUpdateState=APP_UPDATE_END;
				AppUpdateFlagC=0;
#if APP_MAIN_DEBUG_FUN==1
				printf("APP_UPDATE_END\r\n");
#endif
#endif
			}
#endif
#if AIM_915_916_FUN==1
			AppUpdateState=APP_UPDATE_JUGEMENT;
			GPIO_I2C3_PortInit();
			AppUpdateTimer=T50S_10;
#endif
			AppUpdateFlagD=0;
			break;
#if AIM_915_916_FUN==1
		case APP_UPDATE_JUGEMENT:
			if(AppUpdateTimer==0)
			{
				u8 param_com_915;
				u8 param_com_916;
                AppUpdateTimer = 100;
                param_com_915 = AIM_915_ReadReg(0x0C);
                param_com_916 = AIM_916_ReadReg(0x07);
                if(param_com_915!=0x05&&param_com_916!=0x18)
                {
                    AppUpdateState = APP_UPDATE_END;
                    gFlashPushNum = 0xA343FBEA;
#if defined(AUTOCHIPS_AC781X)
	        		RTC->BKP_DR1 = gFlashPushNum;
#elif defined(HDSC_HC32F460)
#elif defined(HDSC_HC32L072)
#elif defined(STM32_F103VC)
#endif
					Reset_IO();
					StopDevice();
					Delay_ms(3000);
					SoftReset();
				}
			}
			break;    
		case APP_UPDATE_ESCAPE:
			if(AppUpdateTimer==0)
			{
#if defined(AUTOCHIPS_AC781X)
                gFlashPushNum = 0xFFFFFFFF;
                RTC->BKP_DR1=gFlashPushNum;
#elif defined(HDSC_HC32F460)
#elif defined(HDSC_HC32L072)
#elif defined(STM32_F103VC)
#endif
				AppUpdateState = APP_UPDATE_END;
#if APP_MAIN_DEBUG_FUN==1
				printf("APP_UPDATE_ESCAPE\r\n");
#endif
			}
			break;
#endif			
		case APP_UPDATE_END:
#if APP_MAIN_DEBUG_FUN==1
			printf("APP_UPDATE_END\r\n");
#endif
			break;
		default:
			break;
	}
}

void OsWorkOn(void)
{
	OS_WorkState=OS_WAIT_ARM2_OK;
}

void OsWorkOff(void)
{
	OS_WorkState=OS_WORK_IDLE;
}

#if PLATFORM_TYPE==NXP_IMAX8_PLATFORM||PLATFORM_TYPE==UNISOC_PLATFORM
void APP_MainPro(void)
{
#if MCU_ACK_MESSAGE_MODE==1
	Mcu_Ack_Tx_Pro();
#endif
	if(F_UART_TX_ACK_CHECK)
	{
		Uart_ReSend_Timer++;
		if(Uart_ReSend_Timer==T200MS_10)
		{  	
			Uart_ReSend_Timer=0;
			if(Uart_Tx_counter==0)
			{
				if(++Uart_ReSend_Counter<3)
				{
					Usart_TxStart();
				}
				else
				{
					Uart_ReSend_Counter=0;
					F_UART_TX_BUFF_FULL=0;
					F_UART_TX_ACK_CHECK=0;
				}
			}
		}
	}
	else if(!F_UART_TX_BUFF_FULL)
	{
		McuTxService();       
	}

	if(AppMainTimer)
	{
		AppMainTimer--;
	}
	if(APP_READY!=APP_Status) //add2.28
	{
		AppReadyTimer--;
		if(AppReadyTimer==0)
		{		
				SystemReset();
		}
	}
	else if(APP_READY==APP_Status)
	{
		AppReadyTimer=T30S_10;
	}
	
	
			
		
	      //add2.28*/
	switch(OS_WorkState)
	{
		case OS_WORK_IDLE:
			break;
		case OS_WAIT_ARM2_OK:
#if POHM_REMEMBER_FAKE_OFF_FUN==1
			if(GetPowerOneHourModeFakeOffFlag()==0)
#endif
#if MODEL== ANDROID_Q133_00||MODEL== ANDROID_Q133_01
			if(AccPinStatus)
#endif
			{
				PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);//原200，开机能早点亮屏
			}
			OS_WorkState=OS_WAIT_APP_READY;
			break;
		case OS_WAIT_APP_READY:
			if(APP_READY==APP_Status)
			{
				Hard_UMute(); 
				F_AppInit_OK=1;
				F_Mcu_Restart=0;
				OS_WorkState=OS_WORK_NORMAL;
#if POWER_ONE_HOUR_MODE_FUN==1
				SetPowerOnOkFlag(1);
#endif
			}
			break;
		case OS_WORK_NORMAL:
			break;
		default:
			break;
	}
 }
 #else
void APP_MainPro(void)
{
	if(!Is_Machine_Power) 
	{
		nMediaPlayPackage=0;
		return;
	}
#if PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM||PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
	if(F_UART_INIT_FALG==0)
	{
		Uart_ReSend_Counter=0;
		Uart_Tx_counter=0;
		F_UART_TX_BUFF_FULL=0;
		F_UART_TX_ACK_CHECK=0;
	}
	else
#endif
	if(F_UART_TX_ACK_CHECK)
	{
		Uart_ReSend_Timer++;
		if(Uart_ReSend_Timer==T200MS_10)
		{  	
			Uart_ReSend_Timer=0;
			if(Uart_Tx_counter==0)
			{
				if(++Uart_ReSend_Counter<3)
				{
					Usart_TxStart();
				}
				else
				{
					Uart_ReSend_Counter=0;
					F_UART_TX_BUFF_FULL=0;
					F_UART_TX_ACK_CHECK=0;
				}
			}
		}
	}
	else if(!F_UART_TX_BUFF_FULL)
	{
		McuTxService();       
	}

	if(AppMainTimer)
	{
		AppMainTimer--;
	}
#if SUZUKI_UART_FUN==1
	if(AppWaitPowerOffTimer)
	{
		AppWaitPowerOffTimer--;
	}
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
	if(AppCheckCanTimer)
	{
		AppCheckCanTimer--;
	}
#endif

#if UBOOT_FUN==1//CPU_SUNPLUS_8368XU==1
#else
#if PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368PU_PLATFORM
#if MODEL==LINUX_1475_21||MODEL==LINUX_1475_CP||MODEL==LINUX_1479_21
if(!F_CLOSE_BEAT_HEART_CHECK)
{
		if(APP_READY==APP_Status)
	{
		AppReadyTimer=0;
	}
	else if(AppReadyTimer)
	{
		AppReadyTimer--;
		if(AppReadyTimer==0)
		{
			MT3360_RESET_ON;
			AppUpdateGpioConfig();
			HWCFG2_HIGH_LEVEL;
			HWCFG3_LOW_LEVEL;
			MT3360_RESET_OFF;
			Delay_ms(100);
			USART3_InitConfig(115200);
			AppReadyTimer=T15S_10;
			AppResetCounter++;
			if(AppResetCounter>3)
			{
				SystemReset();
			}
		}
	}
}
#else
	if(APP_READY==APP_Status)
	{
		AppReadyTimer=0;
	}
	else if(AppReadyTimer)
	{
		AppReadyTimer--;
		if(AppReadyTimer==0)
		{
			MT3360_RESET_ON;
			AppUpdateGpioConfig();
			HWCFG2_HIGH_LEVEL;
			HWCFG3_LOW_LEVEL;
			MT3360_RESET_OFF;
			Delay_ms(100);
#if defined(AUTOCHIPS_AC781X)
			USART4_InitConfig(115200);//yuan
#elif defined(HDSC_HC32F460)
			USART3_InitConfig(115200);//yuan
#elif defined(HDSC_HC32L072)
			USART3_InitConfig(115200);
#elif defined(STM32_F103VC)
			UART4_InitConfig(115200);
#elif defined(STM32F401xx)
			USART6_InitConfig(115200);
#endif
			AppReadyTimer=T15S_10;
			AppResetCounter++;
			if(AppResetCounter>3)
			{
				SystemReset();
			}
		}
	}
#endif
#elif PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM||MODEL==LINUX_Q088_58||MODEL==LINUX_P058_55||MODEL== ANDROID_Q133_uni
#else
	if(APP_READY==APP_Status)
	{
		AppReadyTimer=0;
	}
	else if(AppReadyTimer)
	{
		AppReadyTimer--;
		if(AppReadyTimer==0)
		{
#if AIM_915_916_FUN==1
            		SystemReset();
#else
#if UBOOT_FUN==1
			//MT3360_RESET_ON;//uboot
#else
			MT3360_RESET_ON;
#endif
			Delay_ms(10);
			MT3360_RESET_OFF;
			AppReadyTimer=T15S_10;
			AppResetCounter++;
			if(AppResetCounter>3)
			{
				SystemReset();
			}
#endif
		}
	}
#endif
#endif

	AppUpdatePro();
#ifndef FLASH_SIZE_64K
#if 0//CPU_SUNPLUS_8368XU==1
#else
#if UBOOT_FUN==1
			//APPMonitorPro();//uboot
#else
			APPMonitorPro();//uboot
#endif
#endif
#endif
	switch(OS_WorkState)
	{
		case OS_WORK_IDLE:
			break;
		case OS_WAIT_ARM2_OK:
			if(1==F_ARM2_STARTOK)
			{
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_WAIT_ARM2_OK-->OS_WAIT_APP_READY\r\n");
#endif	
				OS_WorkState=OS_WAIT_APP_READY;
				ClearMessage(NAVI_MODULE);  
				if(F_Reverse_PowerOn)
				{
					if(Get_Reverse_Det_Flag)
					{
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,50);
					}
				}
				else
				{
					if(1
#if FICTITIOUS_POWER_OFF_FUN==1 && MODEL!=LINUX_D095_55
						&&0==F_FICTITIOUS_POWER_OFF
#endif
#if ILLUMI_WHEN_STANDBY==1
						&&0==ILLUMI_WAKEUP
#endif
						)
					{
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
#if MODEL==LINUX_1386_02
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,30);
#else
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,20);
#endif
#elif PLATFORM_TYPE==REALTEK_RTD1861B_PLATFORM
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,110);
#else
#if MODEL==LINUX_Q088_58||MODEL==LINUX_1435_11
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,90);
#elif MODEL==LINUX_Q088_CHL
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,200);
#elif MODEL==LINUX_6255W_57||MODEL==LINUX_6255W_AA57||MODEL==LINUX_1295WH_PC||MODEL==LINUX_1275W_CP||MODEL==LINUX_1345W_CP||MODEL==LINUX_9325W_25||MODEL==LINUX_6259_57
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,7);
#elif MODEL==LINUX_G019_G0
			if(F_AppPowerOn)
			{
					PostMessage(MMI_MODULE,UICC_TFT_AWAKE,80);
					AppMainTimer=T100MS_10;
			}
			else
			{
					PostMessage(MMI_MODULE,UICC_TFT_AWAKE,30);
			}
#elif MODEL==ANDROID_Q133_00||MODEL==ANDROID_Q133_01
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,30);
#elif MODEL==LINUX_2229W_65||MODEL==LINUX_2389W_65
        PostMessage(MMI_MODULE,UICC_TFT_AWAKE,35);
#else
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,70);
#endif
#endif
					}
				}
			}
			break;
		case OS_WAIT_APP_READY:
#if MODEL==LINUX_G019_G0
			if(AppMainTimer)
			{
				break;
			}
#endif
			if(APP_READY==APP_Status)
			{
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_WAIT_APP_READY-->OS_POST_MESSAGE\r\n");
#endif	
				AppMessageCounter=POWER_ON_TX_RESET_STATE;
				OS_WorkState=OS_POST_MESSAGE;
#if RTC_TIMER_FUN==1
				RTC_TimeInfo=RTC_ReadTime();
#endif
				if(0==IS_CCFL_EN
					&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
					&&0==F_FICTITIOUS_POWER_OFF
#endif
#if ILLUMI_WHEN_STANDBY==1
					&&0==ILLUMI_WAKEUP
#endif
					)
				{
					PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
				}
#if FICTITIOUS_POWER_OFF_FUN==1
				if(F_FICTITIOUS_POWER_OFF)
				{
					POWER_LED_ON;
				}
#endif
#if MLINK_FUN==1
				PostMessage(USB_MIRROR_MODULE,CP_MSG_C_INIT,0);
#endif
			}
			else if(Get_Reverse_Det_Flag
#if MODEL==LINUX_1318_11||MODEL==LINUX_1318C_11||MODEL==LINUX_1338_11||MODEL==LINUX_1348_11||MODEL==LINUX_1337_11||MODEL==LINUX_1347_11\
	||MODEL==LINUX_1188_11||MODEL==LINUX_1188C_11||MODEL==LINUX_1188CT_11||MODEL==LINUX_1337C_11||MODEL==LINUX_1347C_11||MODEL==LINUX_1188D_11\
	||MODEL==LINUX_M078_40||MODEL==LINUX_1317_11||MODEL==LINUX_1187_11||MODEL==LINUX_1315_11\
			||MODEL==LINUX_1347CK_11TH||MODEL==LINUX_1377C_11||MODEL==LINUX_1345A_11||MODEL==LINUX_1378C_11||MODEL==LINUX_1488C_11||MODEL==LINUX_1377WC_11\
			||MODEL==LINUX_1379UC_11||MODEL==LINUX_1489UC_11
				&&F_Reverse_PowerOn
#endif  
			)
			{
				if(CAMERA_FRONT==CameraInfo.reverse_mode)
				{
#if MODEL==LINUX_1269_21||MODEL==LINUX_9289_21||MODEL==LINUX_1475_21||MODEL==LINUX_1479_21
					RearCameraOn();
					FrontCameraOn();
#elif MODEL==LINUX_2309_02||MODEL==LINUX_2309A_02||MODEL==LINUX_1275W_MG||MODEL==LINUX_N039_DZ||MODEL==LINUX_1277_33||MODEL==LINUX_1349W_YS||MODEL==LINUX_2409_31
#else
					RearCameraOff();
					FrontCameraOn();
#endif
				}
				else
				{
#if MODEL==LINUX_1269_21||MODEL==LINUX_9289_21||MODEL==LINUX_1475_21||MODEL==LINUX_1479_21
					RearCameraOn();
					FrontCameraOn();
#elif MODEL==LINUX_2309_02||MODEL==LINUX_2309A_02||MODEL==LINUX_1275W_MG||MODEL==LINUX_N039_DZ||MODEL==LINUX_1277_33||MODEL==LINUX_2409_31||MODEL==LINUX_1349W_YS
#else
					FrontCameraOff();
					RearCameraOn();
#if MODEL==LINUX_1379UC_11||MODEL==LINUX_1489UC_11
					LeftCameraOn();
					RightCameraOn();
#endif
#endif
				}
				if(0==IS_CCFL_EN
					&&0==PowerOpenScreenTimer)
				{
					PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
				}
				OS_WorkState=OS_WAIT_REVERSE_END;
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_WAIT_APP_READY-->OS_REVERSE_APP_READY\r\n");
#endif
			}
#if MODEL==LINUX_2359W_PC
			else if(CameraInfo.reverse_setting)
			{;}
#endif
			else if(ReversPreProFlag
#if MODEL==LINUX_1318_11||MODEL==LINUX_1318C_11||MODEL==LINUX_1338_11||MODEL==LINUX_1348_11||MODEL==LINUX_1337_11||MODEL==LINUX_1347_11||MODEL==LINUX_1188_11||MODEL==LINUX_1188C_11||MODEL==LINUX_1188CT_11||MODEL==LINUX_1337C_11||MODEL==LINUX_1347C_11||MODEL==LINUX_1188D_11||MODEL==LINUX_M078_40||MODEL==LINUX_1317_11||MODEL==LINUX_1187_11||MODEL==LINUX_1315_11||MODEL==LINUX_1307W_14\
			||MODEL==LINUX_1347CK_11TH||MODEL==LINUX_1377C_11||MODEL==LINUX_1345A_11||MODEL==LINUX_1378C_11||MODEL==LINUX_1488C_11||MODEL==LINUX_1377WC_11||MODEL==LINUX_1305W_14B||MODEL==LINUX_1379UC_11||MODEL==LINUX_1489UC_11
				&&F_Reverse_PowerOn
#endif  
				)
			{
				if(CAMERA_FRONT==CameraInfo.reverse_mode)
				{
#if MODEL==LINUX_1269_21||MODEL==LINUX_9289_21||MODEL==LINUX_1475_21||MODEL==LINUX_1479_21
					RearCameraOn();
					FrontCameraOn();
#elif MODEL==LINUX_2309_02||MODEL==LINUX_2309A_02||MODEL==LINUX_1275W_MG||MODEL==LINUX_N039_DZ||MODEL==LINUX_1277_33||MODEL==LINUX_2409_31||MODEL==LINUX_1349W_YS
#else
					RearCameraOff();
					FrontCameraOn();
#endif
				}
				else
				{
#if MODEL==LINUX_1269_21||MODEL==LINUX_9289_21||MODEL==LINUX_1475_21||MODEL==LINUX_1479_21
					RearCameraOn();
					FrontCameraOn();
#elif MODEL==LINUX_2309_02||MODEL==LINUX_2309A_02||MODEL==LINUX_1275W_MG||MODEL==LINUX_N039_DZ||MODEL==LINUX_1277_33||MODEL==LINUX_2409_31||MODEL==LINUX_1349W_YS
#else
					FrontCameraOff();
					RearCameraOn();
#if MODEL==LINUX_1379UC_11||MODEL==LINUX_1489UC_11
					LeftCameraOn();
					RightCameraOn();
#endif
#endif
				}
				OS_WorkState=OS_CHECK_REVERSE_ON;
				AppMainTimer=T10S_10;
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_WAIT_APP_READY-->OS_CHECK_REVERSE_ON\r\n");
#endif
			}
#if SUZUKI_UART_FUN==1
			if(UART_WAKEUP)
			{
				if(Get_ACC_Det_Flag)
				{
					UART_WAKEUP=0;
					SuzukiUartWakeUpFlag = 0;
					if(0==IS_CCFL_EN
						&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
						&&0==F_FICTITIOUS_POWER_OFF
#endif
						)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_DISP_MESSAGE,0));
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,70);
					}
				}
			}
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
			if(F_CAN_WAKEUP_POWER_ON)
			{
				if(Get_ACC_Det_Flag)
				{
					F_CAN_WAKEUP_POWER_ON=0;
					if(0==IS_CCFL_EN
						&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
						&&0==F_FICTITIOUS_POWER_OFF
#endif
						)
					{
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
					}
				}
			}
#endif
			break;
		case OS_CHECK_REVERSE_ON:
			if(Get_Reverse_Det_Flag
				||0==AppMainTimer)
			{
				OS_WorkState=OS_WAIT_REVERSE_END;
				if(Get_Reverse_Det_Flag)
				{
					PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
				}
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_CHECK_REVERSE_ON-->OS_REVERSE_APP_READY\r\n");
#endif
			}
			else if(ReversPreProFlag==0
				&&IsSystemManualOff==0
				&&F_Reverse_PowerOn==0
#if FICTITIOUS_POWER_OFF_FUN==1
				&&0==F_FICTITIOUS_POWER_OFF
#endif				
				)
			{
				OS_WorkState=OS_WAIT_APP_READY;
				PostMessage(MMI_MODULE,UICC_TFT_AWAKE,50);
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_CHECK_REVERSE_ON-->OS_WAIT_APP_READY\r\n");
#endif
			}
			break;
		case OS_WAIT_REVERSE_END:
#if MODEL==LINUX_G019_G0
			if(APP_READY==APP_Status)
			{
				Hard_UMute();
			}
#endif
#if MODEL==LINUX_1277_33
			if (APP_READY == APP_Status)
			{
				OS_WorkState = OS_WAIT_APP_READY;
			}
#endif
			if(0==Get_Reverse_Det_Flag)
			{
#ifndef FLASH_SIZE_64K
				if(CameraInfo.reverse_delay_time)
				{
					AppMainTimer=CameraInfo.reverse_delay_time*(1000/10);
					OS_WorkState=OS_WAIT_F_REVERSE_END;
#if APP_MAIN_DEBUG_FUN==1
					printf("OS_WAIT_REVERSE_END-->OS_WAIT_F_REVERSE_END\r\n");
#endif
				}
				else
#endif
				{
					if(1==F_Reverse_PowerOn)
					{
						CCFL_Power_OnOff(0);	
						OS_WorkState=OS_CHECK_REVERSE_END;
						AppMainTimer=POWET_OFF_REVERSE_CHECK_TIME;
#if APP_MAIN_DEBUG_FUN==1
						printf("OS_WAIT_REVERSE_END-->OS_CHECK_REVERSE_END\r\n");
#endif
					}
					else
					{
						OS_WorkState=OS_WAIT_APP_READY;	
#if FICTITIOUS_POWER_OFF_FUN==1
						if(F_FICTITIOUS_POWER_OFF)
						{
							CCFL_Power_OnOff(0);
						}
#endif
#if ILLUMI_WHEN_STANDBY==1
						if(ILLUMI_WAKEUP)
						{
							CCFL_Power_OnOff(0);
						}
#endif
#if APP_MAIN_DEBUG_FUN==1
						printf("OS_WAIT_REVERSE_END-->OS_WAIT_APP_READY\r\n");
#endif						
					}
				}
				ReversPreProFlag=0;
			}
			else
			{
				if(0==IS_CCFL_EN
					&&0==PowerOpenScreenTimer)
				{
					PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
				}
			}
			break;
#ifndef FLASH_SIZE_64K
		case OS_WAIT_F_REVERSE_END:
			if(0==AppMainTimer)
			{
				if(1==F_Reverse_PowerOn)
				{
					CCFL_Power_OnOff(0);	
					OS_WorkState=OS_CHECK_REVERSE_END;
					AppMainTimer=POWET_OFF_REVERSE_CHECK_TIME;
#if APP_MAIN_DEBUG_FUN==1
					printf("OS_WAIT_F_REVERSE_END-->OS_CHECK_REVERSE_END\r\n");
#endif	
				}
				else
				{
					OS_WorkState=OS_WAIT_APP_READY;
#if FICTITIOUS_POWER_OFF_FUN==1
					if(F_FICTITIOUS_POWER_OFF)
					{
						CCFL_Power_OnOff(0);
					}
#endif
#if ILLUMI_WHEN_STANDBY==1
					if(ILLUMI_WAKEUP)
					{
						CCFL_Power_OnOff(0);
					}
#endif
#if APP_MAIN_DEBUG_FUN==1
					printf("OS_WAIT_F_REVERSE_END-->OS_WAIT_APP_READY\r\n");
#endif	
				}
			}
			else if(1==Get_Reverse_Det_Flag)
			{
				OS_WorkState=OS_WAIT_REVERSE_END;
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_WAIT_F_REVERSE_END-->OS_WAIT_REVERSE_END\r\n");
#endif	
			}
			break;
#endif
		case OS_CHECK_REVERSE_END:
			if(AppMainTimer)
			{
				if(Get_Reverse_Det_Flag)
				{
					CCFL_Power_OnOff(1);
					OS_WorkState=OS_WAIT_REVERSE_END;
#if APP_MAIN_DEBUG_FUN==1
					printf("OS_CHECK_REVERSE_END-->%x\r\n",OS_WorkState);
#endif						
				}
				else if(F_Reverse_PowerOn==0&&IsSystemManualOff==0)
				{
					OS_WorkState=OS_WAIT_APP_READY;	
#if APP_MAIN_DEBUG_FUN==1
					printf("OS_CHECK_REVERSE_END-->OS_WAIT_APP_READY\r\n");
#endif	
				}
			}
			else
			{
				F_Reverse_PowerOn=0;		
				PostMessage(POWER_MODULE,EVT_POWER_OFF,POWEROFF_FROM_MANNED); 	
				ReversPreProFlag=0;
				OS_WorkState=OS_WORK_IDLE;	
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_CHECK_REVERSE_END-->OS_WORK_IDLE\r\n");
#endif	
			}
			break;
		case OS_POST_MESSAGE:
#if FICTITIOUS_POWER_OFF_FUN==1 && MODEL!=LINUX_D095_55
			if(F_FICTITIOUS_POWER_OFF
				&&Get_Reverse_Det_Flag==0)
			{
				if(IS_CCFL_EN)
				{
					CCFL_Power_OnOff(0);
				}
			}
#endif
#if ILLUMI_WHEN_STANDBY==1
			if(ILLUMI_WAKEUP)
			{
				if(IS_CCFL_EN)
				{
					CCFL_Power_OnOff(0);
				}
			}
#endif
#if SUZUKI_UART_FUN==1
			if(UART_WAKEUP)
			{
				if(Get_ACC_Det_Flag)
				{
					UART_WAKEUP=0;
					SuzukiUartWakeUpFlag = 0;
					if(0==IS_CCFL_EN
						&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
						&&0==F_FICTITIOUS_POWER_OFF
#endif
						)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_DISP_MESSAGE,0));
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,70);
					}
				}
			}
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
			if(F_CAN_WAKEUP_POWER_ON)
			{
				if(Get_ACC_Det_Flag)
				{
					F_CAN_WAKEUP_POWER_ON=0;
					if(0==IS_CCFL_EN
						&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
						&&0==F_FICTITIOUS_POWER_OFF
#endif
					)
					{
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
					}
				}
			}
#endif
			if(AppMessageCounter<NUM_OF_POWER_ON_TX)
			{
				if(!IsMessageFull(NAVI_MODULE))
				{				
					switch(AppMessageCounter)
					{
						case POWER_ON_TX_MCU_VERSION:
						case POWER_ON_TX_CLOCK:
						case POWER_ON_TX_VOLUME:
						case POWER_ON_TX_DISC_STATE:
#if CANBOX_FUNC_MULTIPLE==1
						case POWER_ON_TX_CAN_MULTIPLE:
#endif
#if MODEL==LINUX_N039_DZ
						case POWER_ON_TX_HW_VERSION:
#endif						
							PostMessage(NAVI_MODULE, PostAppMessage[AppMessageCounter],0);
							break;
						case POWER_ON_TX_RESET_STATE:
							if(F_Mcu_Restart)
							{
								if((ResetSource&POR_PDR_RESET)
									||(ResetSource&LPWR_RESET))
								{
									NotifyAppStateMsg(MACHINE_STATE_B_OFF,1);							
#if ENABLE_SECURITY_CODE==1
									if(PASSWORD_STATE)
									{
										if(GET_LOCK_SCREEN)
										{
											CLR_PASSWORD;
										}
										else
										{
											SET_PASSWORD;
										}
										EEPROM_SavePWSetting();
									}								
#endif
								}
								else if(ResetSource&SOFTWARE_RESET)
								{
#if MODEL == LINUX_D095_55
									SET_PASSWORD;
#endif
								}
								else if((ResetSource&IWDG_RESET)
									||(ResetSource&WWDG_RESET))
								{
								}
								else if(ResetSource&RESET_PIN_RESET)
								{
									NotifyAppStateMsg(MACHINE_STATE_PANEL_RESET,1);
								}
								F_Mcu_Restart=0;
#if EJECT_DISC_AFTER_RESET==1
								PostKeyCode(UICC_EJECT,PANEL);
#endif
#if MODEL==LINUX_1465_16||MODEL==LINUX_1307W_14||MODEL==LINUX_1505W_14||MODEL==LINUX_1277_33||MODEL==LINUX_1465W_16M||MODEL==LINUX_1305W_14B
								FrontSource=SOURCE_HOMEVIEW;
#endif
							}	
#if ENABLE_SECURITY_CODE==1
							if(GET_LOCK_SCREEN)
							{
								LockScreenTimer=T30S_100;
								PostMessage(NAVI_MODULE,MCU_TX_CMD,(u16)(UICC_OPEN_MENU<<8|WINCE_LOCKED_MENU));
							}
							else if(GET_PASSWORD)
							{
								PostMessage(NAVI_MODULE,MCU_TX_CMD,(u16)(UICC_OPEN_MENU<<8|WINCE_SECURITY_CODE_MENU));
							}
#endif

							break;
						case POWER_ON_TX_REVERSE_OFF:
							if(Get_Reverse_Det_Flag==0)
							{
								NotifyAppStateMsg(MACHINE_STATE_REVERSE,OFF);
								REVERSE_SIGNAL_OFF;
							}
							break;
						case POWER_ON_TX_PARKING_STATE:
							if(PARKING_IGNORE==F_PARKING_TYPE)
							{
								NotifyAppStateMsg(MACHINE_STATE_PARKING,ON);
							}
							else
							{
								NotifyAppStateMsg(MACHINE_STATE_PARKING,Get_F_Stop_Car);
							}
							break;
						case POWER_ON_TX_ILLUME_STATE:
							NotifyAppStateMsg(MACHINE_STATE_ILLUMINATION,F_LIGHTING_FLAG);	
							break;
#if MODEL==LINUX_D068_55||MODEL==LINUX_D078_55||MODEL==LINUX_P058_55||MODEL==LINUX_6178_58||MODEL==LINUX_D065_55||MODEL==LINUX_D095_55
						case POWER_ON_TX_AUX_STATE:
							NotifyAppStateMsg(MACHINE_STATE_AUX_IN,Get_F_Auxin_Det);	
							break;
#endif
#if MODEL==LINUX_2289_31||MODEL==LINUX_2289_03
						case POWER_ON_TX_SPEED_STATE:
							NotifyAppStateMsg(MACHINE_STATE_SPEED,Speed_Value);
							break;
#endif
						default:
							break;
					}
					AppMessageCounter++;
					if(NUM_OF_POWER_ON_TX==AppMessageCounter)
					{
						OS_WorkState=OS_POST_SOURCE;
#if APP_MAIN_DEBUG_FUN==1
						printf("OS_POST_MESSAGE-->OS_POST_SOURCE\r\n");
#endif	
					}
				}
			}
			break;
		case OS_POST_SOURCE:
#if SUZUKI_UART_FUN==1
			if(UART_WAKEUP)
			{
				if(Get_ACC_Det_Flag)
				{
					UART_WAKEUP=0;
					SuzukiUartWakeUpFlag = 0;
					if(0==IS_CCFL_EN
						&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
						&&0==F_FICTITIOUS_POWER_OFF
#endif
						)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_DISP_MESSAGE,0));
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,70);
					}
				}
			}
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
			if(F_CAN_WAKEUP_POWER_ON)
			{
				if(Get_ACC_Det_Flag)
				{
					F_CAN_WAKEUP_POWER_ON=0;
					if(0==IS_CCFL_EN
						&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
						&&0==F_FICTITIOUS_POWER_OFF
#endif
					)
					{
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
					}
				}
			}
#endif
#if ENABLE_SECURITY_CODE==1
#if MODEL==LINUX_D095_55
			if(F_CAN_WAKEUP_POWER_ON && !Get_ACC_Det_Flag)
			{

				AppCheckAccTimer=0;
				if(F_CAN_SLEEP
					||AppCheckCanTimer==0)
				{
					F_CAN_WAKEUP_POWER_ON=0;
					DisableKeyProFlag=1;
				}
			}
#endif
			if(GET_PASSWORD||GET_LOCK_SCREEN)
			{
				break;
			}
#endif
			if(!IsMessageFull(NAVI_MODULE))
			{
				if(SOURCE_NAVI==FrontSource||SOURCE_MYCAR==FrontSource)
				{
					FrontSource=Backup_Source;
				}
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
#else
				else if(SOURCE_BT==FrontSource
					&&FrontSourceChild!=2)
				{
					FrontSource=Backup_Source;
					FrontSourceChild=Backup_SourceChild;
				}
#endif
				PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FRONT_SRC,FrontSource));
#if FICTITIOUS_POWER_OFF_FUN==1
#if FICTITIOUS_POWER_PRINT_FUN==1
				printf("SOURCE_BT==FrontSource, OS_POST_SOURCE\r\n");
#endif
				PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,F_FICTITIOUS_POWER_OFF));
#endif
				OS_WorkState=OS_HARD_UNMUTE;
				if(0
#if FICTITIOUS_POWER_OFF_FUN==1
					||F_FICTITIOUS_POWER_OFF
#endif
#if ILLUMI_WHEN_STANDBY==1
					||ILLUMI_WAKEUP
#endif
					
					)
				{
					AppMainTimer=500;
				}
				else
				{
					AppMainTimer=200;
				}
#if FACTORY_AUTO_TEST_FUN==1
				if(F_VERSION_VALID==0)
				{
					GetVersionTimer=T2S_100;
					GetVersionCounter=0;
				}
#endif
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_POST_SOURCE-->OS_HARD_UNMUTE\r\n");
#endif	
			}
			break;
		case OS_HARD_UNMUTE:
#if SUZUKI_UART_FUN==1
			if(UART_WAKEUP)
			{
				if(Get_ACC_Det_Flag)
				{
					UART_WAKEUP=0;
					SuzukiUartWakeUpFlag = 0;
					if(0==IS_CCFL_EN
						&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
						&&0==F_FICTITIOUS_POWER_OFF
#endif
						)
					{
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
					}
				}
			}
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
			if(F_CAN_WAKEUP_POWER_ON)
			{
				if(Get_ACC_Det_Flag)
				{
					F_CAN_WAKEUP_POWER_ON=0;
					if(0==IS_CCFL_EN
						&&0==PowerOpenScreenTimer
#if FICTITIOUS_POWER_OFF_FUN==1
						&&0==F_FICTITIOUS_POWER_OFF
#endif
					)
					{
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);
					}
				}
			}
#endif
			if(AppMainTimer==0)
			{
				if(0
#if FICTITIOUS_POWER_OFF_FUN==1
					||F_FICTITIOUS_POWER_OFF
#endif
#if ILLUMI_WHEN_STANDBY==1
					||ILLUMI_WAKEUP
#endif
#if SUZUKI_UART_FUN==1
					||UART_WAKEUP
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
					||F_CAN_WAKEUP_POWER_ON
#endif
				)
				{
					if(!IsMessageFull(NAVI_MODULE))
					{
#if FICTITIOUS_POWER_PRINT_FUN==1
						printf("F_FICTITIOUS_POWER_OFF=1 OS_HARD_UNMUTE\r\n");
#endif					
						PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,F_FICTITIOUS_POWER_OFF));
					}
					else
					{
						break;
					}
				}
				else
				{
					if(IsSysUnMute())
					{
						Hard_UMute();	
						EXT_AMP_MUTE_OFF;
					}
#if FMT_FUNCTION==1
					PostMessage(FMT_MODULE,FMT_EVT_SET_WORK_MODE,F_FMT_WORK_MODE);	
#endif
				}
				OS_WorkState=OS_WORK_NORMAL;
#if SUZUKI_UART_FUN==1
				AppWaitPowerOffTimer=T10S_10;
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
				AppCheckAccTimer=0;
				AppCheckCanTimer=T600S_10;
#endif
#if MODEL==LINUX_1269_21||MODEL==LINUX_9289_21
				if(Get_Reverse_Det_Flag==0)
				{
					RearCameraOff();
					FrontCameraOff();					
				}
#endif
#if APP_MAIN_DEBUG_FUN==1
				printf("OS_HARD_UNMUTE-->OS_WORK_NORMAL\r\n");
#endif	
			}
			break;
		case OS_WORK_NORMAL:
#if SUZUKI_UART_FUN==1
			if(UART_WAKEUP)
			{
				if(Get_ACC_Det_Flag)
				{
					UART_WAKEUP=0;
					SuzukiUartWakeUpFlag = 0;
					PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,0));
					PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_DISP_MESSAGE,0));
				}
				else
				{
					if(AppWaitPowerOffTimer==0)
					{
						UART_WAKEUP=0;
					}
					if(!IsMessageFull(NAVI_MODULE)
						&&0==AppMainTimer)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,1));
						AppMainTimer=300;
					}
				}
			}
			else
#endif
#if ILLUMI_WHEN_STANDBY==1
			if(ILLUMI_WAKEUP)
			{
				if(Get_ACC_Det_Flag
					&&IsSystemManualOff==0)
				{
					ILLUMI_WAKEUP=0;
					PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,0));
					CCFL_Power_OnOff(1);
					Hard_UMute();
					EXT_AMP_MUTE_OFF;
				}
				else
				{
					if(F_LIGHTING_FLAG==0)
					{
						ILLUMI_WAKEUP=0;
						if(Get_ACC_Det_Flag
							&&IsSystemManualOff)
						{
							PostMessage(POWER_MODULE,EVT_POWER_OFF,POWEROFF_FROM_MANNED);
						}
					}
					else
					{
						if(!IsMessageFull(NAVI_MODULE)
							&&AppMainTimer==0)	
						{
							PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,1));
							AppMainTimer=300;				
						}
					}
				}
			}
			else
#endif
#if CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1
			if(F_CAN_WAKEUP_POWER_ON)
			{
				if(Get_ACC_Det_Flag)
				{
					AppCheckAccTimer++;
					if(AppCheckAccTimer>T2S_10)
					{
						F_CAN_WAKEUP_POWER_ON=0;
						PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,0));
#if APP_MAIN_DEBUG_FUN==1
						printf("OS_WORK_NORMAL:F_CAN_WAKEUP_POWER_ON=0,power on\r\n");
#endif	
					}
				}
				else
				{
					AppCheckAccTimer=0;
					if(F_CAN_SLEEP
						||AppCheckCanTimer==0)
					{
						F_CAN_WAKEUP_POWER_ON=0;
						DisableKeyProFlag=1;
#if APP_MAIN_DEBUG_FUN==1
						printf("OS_WORK_NORMAL:F_CAN_WAKEUP_POWER_ON=0,power off\r\n");
#endif	
					}
				}
				if(!IsMessageFull(NAVI_MODULE)
					&&0==AppMainTimer
					&&F_CAN_WAKEUP_POWER_ON)
				{
					PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,1));
					AppMainTimer=300;
				}
			}
			else
#endif
#if FICTITIOUS_POWER_OFF_FUN==1
			if(F_FICTITIOUS_POWER_OFF)
			{
				if(!IsMessageFull(NAVI_MODULE)
					&&AppMainTimer==0)	
				{
#if MODEL==LINUX_Y028_55
#else
#if FICTITIOUS_POWER_PRINT_FUN==1
					printf("F_FICTITIOUS_POWER_OFF=1 OS_WORK_NORMAL\r\n");
#endif
					PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_FICTITIOUS_POWER_OFF,F_FICTITIOUS_POWER_OFF));
#endif
					AppMainTimer=300;				
				}
				POWER_LED_ON;
			}
			else 
#endif
			{
#if SUZUKI_UART_FUN==1||(CAN_FUNCTION==1&&CAN_WAKEUP_FUN==1)
				if(SYS_MUTE)
				{
					if(IsSysUnMute()
						&&Seek_In_Idle()
#if LOW_VOLTAGE_DELAY_OFF_FUN==1
						&&LowVoltageProState==LOW_VOLTAGE_IDLE
#endif
						&&nPowerState==POWER_NORMAL_RUN
						&&F_ErrorPower==0
						&&AppUpdateState==APP_UPDATE_IDLE
						&&IsTunerOn
#if TUNER_TYPE==TDA7708_TUNER
						&&(!(FrontSource==SOURCE_TUNER&&STAR_IsPowerOn()==0))
#elif TUNER_TYPE==MULTIPLE_TUNER
						&&(!(MULTIPLE_TUNER_TYPE==TDA7708_TUNER&&FrontSource==SOURCE_TUNER&&STAR_IsPowerOn()==0))
#endif
						)
					{
						Hard_UMute();
						EXT_AMP_MUTE_OFF;
					}
				}
				if(0==IS_CCFL_EN
					&&0==PowerOpenScreenTimer)
				{
					if(F_TFT_STANDBY==0
						&&Get_ACC_Det_Flag
						&&F_ErrorPower==0
						&&nPowerState==POWER_NORMAL_RUN
						&&IsSystemManualOff==0
#if LOW_VOLTAGE_DELAY_OFF_FUN==1
						&&LowVoltageProState==LOW_VOLTAGE_IDLE
#endif
						)
					{
						PostMessage(MMI_MODULE,UICC_TFT_AWAKE,40);	
					}
				}
#endif
			}
			break;
		default:
			OS_WorkState=OS_WORK_IDLE;
			break;
	}
}
#endif

