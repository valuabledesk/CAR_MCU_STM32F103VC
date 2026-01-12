#include "public.h"							   
u16 MainTickCounter;
iapfun jump2app; 

#if defined(AUTOCHIPS_AC781X)
void iap_load_app(u32 appxaddr)
{
    if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)
	{ 	
		gFlashPushNum = 0xA055FAFA;
		CKGEN_Enable(CLK_RTC, ENABLE);
		CKGEN_SoftReset(SRST_RTC, 1);
		RTC->BKP_DR1 = gFlashPushNum;
		EFLASH_UnlockCtrl();
		EFLASH_PageErase(FLASH_EEPROM_ADDR);
		EFLASH_PageProgram(FLASH_EEPROM_ADDR,&gFlashPushNum,1);
		EFLASH_LockCtrl();
	    Hard_Mute();
	    
        TIMER_DeInit(TIMER1);
        TIMER_DeInit(TIMER2);
	    ADC_DeInit(ADC);
		ADC_Cmd(ADC,DISABLE);	

    	CKGEN_Enable(CLK_UART2, DISABLE);
    	CKGEN_Enable(CLK_UART4, DISABLE);
    	CKGEN_Enable(CLK_UART6, DISABLE);
#if DUAL_DAB_FUN==1
		CKGEN_Enable(CLK_UART3, DISABLE);
    		CKGEN_Enable(CLK_UART5, DISABLE);
#endif
    	CKGEN_Enable(CLK_RTC, DISABLE);

        PWM_ModuleDisable(PWM0);
        PWM_ModuleDisable(PWM1);
        //PWM_ModuleDisable(PWM2);
        PWM_ModuleDisable(PWM3);
		CAN_Uninitialize(CAN1);
		Gpio_AccIntDisable();
#if STANDBY_WHEN_POWER_OFF==1
		Gpio_PowerIntDisable();
#endif
#if ILLUMI_WHEN_STANDBY==1||ILLUMI_DETECT_MODE==ILLUMI_PWM_DETECT
		Gpio_IllumiIntDisable();
#endif
#if REVERSE_DETECT_MODE==REVERSE_PWM_DETECT||STANDBY_WHEN_POWER_OFF==1||TOUCH_DET_FUN==1
		Gpio_ReverseIntDisable();
#endif
#if PARKING_DETECT_MODE==PARKING_PWM_DETECT
		Gpio_ParkingIntDisable();
#endif
		Gpio_EncoderIntDisable();
#if REMOTE_FUNCTION == 1	
		Gpio_RemoteIntDisable();
#endif
#if MODEL==LINUX_Y038_55||MODEL==LINUX_Y028_55||MODEL==LINUX_D078_55
		Gpio_IllumiPwmSigIntDisable();
#endif
#if SUZUKI_UART_FUN==1
		Gpio_SuzukiUartIntDisable();
#endif
		jump2app=(iapfun)*(vu32*)(appxaddr+4);					
		__set_MSP(*(vu32*)appxaddr);
		jump2app();									
	}
}
#elif defined(HDSC_HC32F460)
#define SRAM_BASE             			0x1FFF8000
#define RAM_SIZE                    			0x2F000

void EFM_SetEraseProgramMode(u32 mode)
{
	M4_EFM->FWMC_f.PEMOD=mode; 
}

u8 EFM_GetCacheStatus(void)
{
	return M4_EFM->FRMC_f.CACHE;
}

u8 EFM_WaitForOperationDone(u32 timeout)
{
	u32 delay=0;
	u8 result=0;

	while(delay<timeout)
	{
		if(EFM_GetFlagStatus(EFM_FLAG_RDY))
		{
			result=1;
			break;
		}
		delay++;
	}
	if(EFM_GetFlagStatus(EFM_FLAG_EOP))
	{
		EFM_ClearFlag(EFM_FLAG_EOP);
	}

	if(EFM_GetFlagStatus(EFM_FLAG_COLERR)
		||EFM_GetFlagStatus(EFM_FLAG_PGMISMTCH)
		||EFM_GetFlagStatus(EFM_FLAG_PGSZERR)
		||EFM_GetFlagStatus(EFM_FLAG_PEPRTERR)
		||EFM_GetFlagStatus(EFM_FLAG_WRPERR))
	{
		EFM_ClearFlag(EFM_FLAG_COLERR|EFM_FLAG_PGMISMTCH|EFM_FLAG_PGSZERR|EFM_FLAG_PEPRTERR|EFM_FLAG_WRPERR);
		result=0;
	}
	return result;
}

u8 EFM_WriteFlash(u32 addr,u8 *buffer,u32 length)
{
	u32 word_length;
	u32 *write_buff=(u32 *)buffer;
	volatile u32 *flash_addr=(u32 *)addr;
	u32 i;
	u8 temp;
	u8 result=0;

	if((addr%4u)==0
		&&(length%4u)==0)
	{
		word_length=length/4u;
		EFM_Unlock();
		result=EFM_WaitForOperationDone(1000);
		if(result)
		{
			temp=EFM_GetCacheStatus();
			EFM_InstructionCacheCmd(Disable);
			EFM_ErasePgmCmd(Enable); 
			EFM_SetEraseProgramMode(EFM_MODE_SINGLEPROGRAMRB);
			for(i=0;i<word_length;i++)
			{
				*flash_addr=write_buff[i];
				while(!EFM_GetFlagStatus(EFM_FLAG_RDY))
				{
				}
				if(EFM_GetFlagStatus(EFM_FLAG_PGMISMTCH))
				{
					result=0;
					break;
				}
				flash_addr++;
				EFM_ClearFlag(EFM_FLAG_EOP);
			}
			EFM_SetEraseProgramMode(EFM_MODE_READONLY);
			EFM_ErasePgmCmd(Disable); 
			EFM_InstructionCacheCmd((en_functional_state_t)temp);
		}
		EFM_Lock();
	}
	return result;
}

u8 EFM_EraseSector(u32 addr)
{
	u8 result;
	u8 temp;
	
	EFM_Unlock();
	result=EFM_WaitForOperationDone(1000);
	
	if(result)
	{
		temp=EFM_GetCacheStatus();
		EFM_InstructionCacheCmd(Disable);
		EFM_ErasePgmCmd(Enable);    
		EFM_SetEraseProgramMode(EFM_MODE_SECTORERASE);
		*(volatile u32 *)(addr)=0xFFFFFFFF;
		result=EFM_WaitForOperationDone(1000);
		EFM_SetEraseProgramMode(EFM_MODE_READONLY);
		EFM_ErasePgmCmd(Disable); 
		EFM_InstructionCacheCmd((en_functional_state_t)temp);
	}
	EFM_Lock();
	return result;
}

void EraseUserArea(u32 erase_addr,u8 page_num)
{
	u32 i;

	for (i=0;i<page_num;i++)
	{
		EFM_EraseSector((erase_addr+i*8*1024));
	}
}

void FLASH_Write(u32 write_addr,u32 *buffer,u32 num_to_write)	
{
	EFM_WriteFlash(write_addr,((u8 *)buffer),(num_to_write*4));
}

void iap_load_app(u32 appxaddr)
{
	stc_port_init_t stc_port_init;
	u32 stack_top=*((volatile u32 *)appxaddr);
	u32 jump_address;
	
	if((stack_top > SRAM_BASE)&&(stack_top<=(SRAM_BASE+RAM_SIZE)))
	{
		gFlashPushNum = 0xA055FAFA;
		EraseUserArea(FLASH_EEPROM_ADDR,1);
		FLASH_Write(FLASH_EEPROM_ADDR,&gFlashPushNum,1);
		RMU_ClrResetFlag();

		Hard_Mute();

		TIMERA_DeInit(M4_TMRA1);
		TIMERA_IrqCmd(M4_TMRA1,TimeraIrqOverflow,Disable);
		TIMERA_ClearFlag(M4_TMRA1,TimeraFlagOverflow);
		TIMERA_Cmd(M4_TMRA1,Disable);
		PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIMA1,Disable);
		enIrqResign(TIMERA_1_OVF_IRQn);
		NVIC_ClearPendingIRQ(TIMERA_1_OVF_IRQn);
		NVIC_DisableIRQ(TIMERA_1_OVF_IRQn);
		
		TIMERA_DeInit(M4_TMRA2);
		TIMERA_Cmd(M4_TMRA2,Disable);
		PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIMA2,Disable);
		
		TIMERA_DeInit(M4_TMRA3);
		TIMERA_Cmd(M4_TMRA3,Disable);
		PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIMA3,Disable);
		
		TIMERA_DeInit(M4_TMRA4);
		TIMERA_Cmd(M4_TMRA4,Disable);
		PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIMA4,Disable);
		
#if REMOTE_FUNCTION==1
		Timer6_DeInit(M4_TMR61);
		Timer6_ConfigIrq(M4_TMR61,Timer6INTENB,Disable);
		Timer6_StopCount(M4_TMR61);
		PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIM61,Disable);
		enIrqResign(TIMER6_1_GCMB_IRQn);
		NVIC_ClearPendingIRQ(TIMER6_1_GCMB_IRQn);
		NVIC_DisableIRQ(TIMER6_1_GCMB_IRQn);
#endif
		RTC_DeInit();
		enIrqResign(RTC_PERIOD_IRQn);
		NVIC_ClearPendingIRQ(RTC_PERIOD_IRQn);
		NVIC_DisableIRQ(RTC_PERIOD_IRQn);
		CLK_Xtal32Cmd(Disable);

		ADC_DeInit(M4_ADC1);
		PWC_Fcg3PeriphClockCmd(PWC_FCG3_PERIPH_ADC1,Disable);

		USART_DeInit(M4_USART1);
		PWC_Fcg1PeriphClockCmd(PWC_FCG1_PERIPH_USART1,Disable);
		
		USART_DeInit(M4_USART3);
		USART_FuncCmd(M4_USART3,UsartTx,Disable);
		USART_FuncCmd(M4_USART3,UsartTxEmptyInt,Disable);
		USART_FuncCmd(M4_USART3,UsartRx,Disable);
		USART_FuncCmd(M4_USART3,UsartRxInt,Disable);
		PWC_Fcg1PeriphClockCmd(PWC_FCG1_PERIPH_USART3,Disable);
		enIrqResign(UART_3_RI_IRQn);
		NVIC_ClearPendingIRQ(UART_3_RI_IRQn);
		NVIC_DisableIRQ(UART_3_RI_IRQn);
		enIrqResign(UART_3_TI_IRQn);
		NVIC_ClearPendingIRQ(UART_3_TI_IRQn);
		NVIC_DisableIRQ(UART_3_TI_IRQn);
		enIrqResign(UART_3_EI_IRQn);
		NVIC_ClearPendingIRQ(UART_3_EI_IRQn);
		NVIC_DisableIRQ(UART_3_EI_IRQn);
		
		USART_DeInit(M4_USART4);
		USART_FuncCmd(M4_USART4,UsartTx,Disable);
		USART_FuncCmd(M4_USART4,UsartRx,Disable);
		USART_FuncCmd(M4_USART4,UsartRxInt,Disable);
		PWC_Fcg1PeriphClockCmd(PWC_FCG1_PERIPH_USART4,Disable);
		enIrqResign(UART_4_RI_IRQn);
		NVIC_ClearPendingIRQ(UART_4_RI_IRQn);
		NVIC_DisableIRQ(UART_4_RI_IRQn);
		enIrqResign(UART_4_EI_IRQn);
		NVIC_ClearPendingIRQ(UART_4_EI_IRQn);
		NVIC_DisableIRQ(UART_4_EI_IRQn);

       	CAN_IrqCmd(CanRxIrqEn,Disable);
    	CAN_IrqCmd(CanBusErrorIrqEn,Disable);
		NVIC_ClearPendingIRQ(CAN_INT_IRQn);
		NVIC_DisableIRQ(CAN_INT_IRQn);

		Gpio_EncoderIntDisable();
		Gpio_AccIntDisable();
#if STANDBY_WHEN_POWER_OFF==1
		Gpio_PowerIntDisable();
#endif
#if STANDBY_WHEN_POWER_OFF==1||TOUCH_DET_FUN==1||REVERSE_DETECT_MODE==REVERSE_PWM_DETECT
		Gpio_ReverseIntDisable();
#endif
#if ILLUMI_DETECT_MODE==ILLUMI_PWM_DETECT||ILLUMI_WHEN_STANDBY==1
		Gpio_IllumiIntDisable();
#endif
#if PARKING_DETECT_MODE==PARKING_PWM_DETECT
		Gpio_ParkingIntDisable();
#endif
#if MODEL==LINUX_Y038_55||MODEL==LINUX_Y028_55||MODEL==LINUX_D078_55
		Gpio_IllumiPwmSigIntDisable();
#endif
#if SUZUKI_UART_FUN==1
		Gpio_SuzukiUartIntDisable();
#endif
#if CAN_WAKEUP_FUN==1||CAN_FUN_HAIMA_S5==1
		Gpio_CanIntDisable();
#endif
		
		PORT_DebugPortSetting(TRST|TDI|TDO_SWO,Disable);
		FormatMemery((u8 *)(&stc_port_init),sizeof(stc_port_init_t));
		stc_port_init.enPinMode=Pin_Mode_Out;
		stc_port_init.enPinDrv=Pin_Drv_H;
		#if MODEL== ANDROID_Q133_uni
		PORT_Init(GPIO_PANEL_20KHZ_PWM1_PORT,GPIO_PANEL_20KHZ_PWM1_PIN,&stc_port_init);
		PORT_SetFunc(GPIO_PANEL_20KHZ_PWM1_PORT,GPIO_PANEL_20KHZ_PWM1_PIN,Func_Gpio,Disable);
		PORT_SetBits(GPIO_PANEL_20KHZ_PWM1_PORT,GPIO_PANEL_20KHZ_PWM1_PIN);
		
		PORT_Init(GPIO_PANEL_20KHZ_PWM2_PORT,GPIO_PANEL_20KHZ_PWM2_PIN,&stc_port_init);
		PORT_SetFunc(GPIO_PANEL_20KHZ_PWM2_PORT,GPIO_PANEL_20KHZ_PWM2_PIN,Func_Gpio,Disable);
		PORT_SetBits(GPIO_PANEL_20KHZ_PWM2_PORT,GPIO_PANEL_20KHZ_PWM2_PIN);
		
		PORT_Init(GPIO_PANEL_20KHZ_PWM4_PORT,GPIO_PANEL_20KHZ_PWM4_PIN,&stc_port_init);
		PORT_SetFunc(GPIO_PANEL_20KHZ_PWM4_PORT,GPIO_PANEL_20KHZ_PWM4_PIN,Func_Gpio,Disable);
		PORT_SetBits(GPIO_PANEL_20KHZ_PWM4_PORT,GPIO_PANEL_20KHZ_PWM4_PIN);
		
		PORT_Init(GPIO_PWM3_PORT,GPIO_PWM3_PIN,&stc_port_init);
		PORT_SetFunc(GPIO_PWM3_PORT,GPIO_PWM3_PIN,Func_Gpio,Disable);
		PORT_SetBits(GPIO_PWM3_PORT,GPIO_PWM3_PIN);
		
		#else
		PORT_Init(GPIO_TFT_BL_PWM_PORT,GPIO_TFT_BL_PWM_PIN,&stc_port_init);
		PORT_SetFunc(GPIO_TFT_BL_PWM_PORT,GPIO_TFT_BL_PWM_PIN,Func_Gpio,Disable);
		PORT_SetBits(GPIO_TFT_BL_PWM_PORT,GPIO_TFT_BL_PWM_PIN);
		#endif
		jump_address=*(volatile u32 *)(appxaddr+4);
		jump2app=(func_ptr_t)jump_address;
		__set_MSP(*(volatile u32 *)appxaddr);
		jump2app();
	}
}
#elif defined(HDSC_HC32L072)
#define SRAM_BASE				((uint32_t)0x20000000)
#define RAM_SIZE                   	 	0x8000ul  
void iap_load_app(u32 appxaddr)
{
	uint32_t u32StackTop = *((__IO uint32_t *)appxaddr);
	u32 jump_address;

	if ((u32StackTop > SRAM_BASE) && (u32StackTop <= (SRAM_BASE + RAM_SIZE)))
	{
		stc_gpio_cfg_t stc_gpio_cfg;
		
		gFlashPushNum=0xA055FAFA;
		Flash_SectorErase(FLASH_EEPROM_ADDR);
		Flash_WriteWord(FLASH_EEPROM_ADDR, gFlashPushNum);

		Hard_Mute();
#if MODEL==LINUX_N047_01||MODEL==LINUX_1299U_21
#else
		Timer_0_Deinit();
#endif
		Timer_1_Deinit();
#if REMOTE_FUNCTION==1
		Timer_2_Deinit();
#endif
		Reset_RstPeripheral0(ResetMskBaseTim);
		Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim,0); 
		Timer_3_Deinit();
#if MODEL==LINUX_N047_01
#else
		Timer_5_Deinit();
#endif
		Reset_RstPeripheral0(ResetMskAdvTim);
		Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim,0); 
		
		Adc_Deinit_HC32L072();
		USART0_Deinit();
		USART3_Deinit();
		LPUSART1_Deinit();
		
		RTC_Deinit_HC32L072();
#if MODEL==LINUX_N047_01
#else
		Gpio_EncoderIntDisable();
#endif
		Gpio_AccIntDisable();
#if STANDBY_WHEN_POWER_OFF==1
		Gpio_PowerIntDisable();
#endif
#if MODEL==LINUX_N047_01
#else
		Gpio_ReverseIntDisable();
#endif
#if MODEL==LINUX_N047_01
#else
		Gpio_IllumiIntDisable();
		Gpio_ParkingIntDisable();
#endif
#if MODEL==LINUX_Y038_55
		Gpio_IllumiPwmSigIntDisable();
#endif
#if FMT_FUNCTION==1
			F_FMT_WORK_MODE=0;
			FMT_Freq=9810;
			F_FMT_AUDIO_MODE=0;
			EEPROM_Save_FMT_Param();
			EEPROM_Save_FMT_SetTransmitMode();
			EEPROM_Save_FMT_SetAudioMode();
#endif
#if SUZUKI_UART_FUN==1
		Gpio_SuzukiUartIntDisable();
#endif
		EnableNvic(PORTA_IRQn,IrqLevel3,0);
		EnableNvic(PORTB_IRQn,IrqLevel3,0);
		EnableNvic(PORTC_E_IRQn,IrqLevel3,0);
		EnableNvic(PORTD_F_IRQn,IrqLevel3,0);

		FormatMemery((u8 *)(&stc_gpio_cfg),sizeof(stc_gpio_cfg_t));
		stc_gpio_cfg.enDir=GpioDirOut;
		Gpio_Init(GPIO_TFT_BL_PWM_PORT,GPIO_TFT_BL_PWM_PIN,&stc_gpio_cfg);
		Gpio_SetAfMode(GPIO_TFT_BL_PWM_PORT,GPIO_TFT_BL_PWM_PIN,GpioAf0);
		Gpio_SetIO(GPIO_TFT_BL_PWM_PORT,GPIO_TFT_BL_PWM_PIN);

		jump_address=*(volatile u32 *)(appxaddr+4);
		jump2app=(func_ptr_t)jump_address;
		__set_MSP(*(volatile u32 *)appxaddr);
		jump2app();
	}
}
#elif defined(STM32_F103VC)
u32 gFlashPushNumbak;

void iap_load_app(u32 appxaddr)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    __disable_irq();

    gFlashPushNum=0xA055;
    BKP_WriteBackupRegister(BKP_DR1,0xA055);
    FLASH_Unlock();
    FLASH_ErasePage(FLASH_EEPROM_ADDR);
    FLASH_ProgramHalfWord(FLASH_EEPROM_ADDR,gFlashPushNum);
    FLASH_Lock();
    gFlashPushNumbak = *((vu32*)FLASH_EEPROM_ADDR);

//    printf("gFlashPushNumbak = %x",gFlashPushNumbak);
    if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)
    { 
        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);  
        USART_ITConfig(USART2, USART_IT_RXNE, DISABLE); 
        USART_ITConfig(USART3, USART_IT_RXNE, DISABLE); 
        USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);  
        USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
        USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);  
        TIM_ITConfig(TIM1,TIM_IT_CC2,DISABLE);  
        TIM_ITConfig(TIM1,TIM_IT_CC3,DISABLE);  
        TIM_ITConfig(TIM1,TIM_IT_CC4,DISABLE);  
        TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);   
        TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
        Gpio_AccIntDisable();
        Gpio_EncoderIntDisable();
        Gpio_ParkingIntDisable();
        Gpio_ReverseIntDisable();
        Gpio_IllumiIntDisable();
        Gpio_PowerIntDisable();
#if MODEL==LINUX_Y038_55||MODEL==LINUX_Y028_55||MODEL==LINUX_D078_55||MODEL==LINUX_2289_31||MODEL==LINUX_2289_03||MODEL==LINUX_Y039_55||MODEL==LINUX_2289_31||MODEL==LINUX_Y049_55
		Gpio_IllumiPwmSigIntDisable();
#endif
#if MODEL == LINUX_2289_31||MODEL==LINUX_2289_03
		Gpio_SpeedIntDisable();
#endif
#if CAN_FUNCTION==1
		CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE); 
		CAN_ITConfig(CAN2,CAN_IT_FMP0, DISABLE);
		CAN_DeInit(CAN1);  
		CAN_DeInit(CAN2);
#endif
        USART_Cmd(USART1,DISABLE);
        USART_Cmd(USART2,DISABLE);
        USART_Cmd(USART3,DISABLE);
        USART_Cmd(UART4,DISABLE);
        USART_Cmd(UART5,DISABLE);
        TIM_Cmd(TIM1,DISABLE); 
        TIM_Cmd(TIM2,DISABLE); 
        TIM_Cmd(TIM3,DISABLE); 
        TIM_Cmd(TIM4,DISABLE); 
        ADC_Cmd(ADC1,DISABLE);  
        RTC_StopAlarm();
        
        Hard_Mute();
        
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;      
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
        GPIO_Init(GPIOB,&GPIO_InitStructure);   
        TFT_CCFL_ON;
        
        Delay_ms(10);
        
        jump2app=(iapfun)*(vu32*)(appxaddr+4);                  
        __set_MSP(*(vu32*)appxaddr);
        jump2app();                                 
    }
}
#elif defined(STM32F401xx)
void iap_load_app(u32 appxaddr)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    __disable_irq();

    gFlashPushNum=0xA055FAFA;
    RTC_WriteBackupRegister(RTC_BKP_DR1,0xA055FAFA);
	
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)
	{ 
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);	 
		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);	 
		USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);	

		TIM_ITConfig( TIM3,TIM_IT_Update|TIM_IT_CC4,DISABLE);
		TIM_Cmd(TIM5,DISABLE); 	
		TIM_Cmd(TIM3,DISABLE); 

		Gpio_AccIntDisable();
		Gpio_EncoderIntDisable();
    Gpio_ReverseIntDisable();
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_USART6, DISABLE);
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_ADC1,DISABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM6,DISABLE); 

		RCC_RTCCLKCmd(DISABLE);	
		USART_Cmd(USART1,DISABLE);
		USART_Cmd(USART2,DISABLE);
		USART_Cmd(USART6,DISABLE);

		AUDIO_MUTE_ON;
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 	
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		
		Delay_ms(10);
		
		jump2app=(iapfun)*(vu32*)(appxaddr+4);							
		__set_MSP(*(vu32*)appxaddr);
		jump2app();								
	}
	else
	{
	    while(1)
	    {
	        ;
	    }
	}
}
#elif defined(HDSC_HC32F448)
#define FLASH_IAP_ADDR 0x00000000
#define RAM_SIZE 0x10000//64KB
#define FLASH_EEPROM_ADDR (0x0003E000u)
#define EFM_SECTOR0_NUM (0U)

void EFM_SetEraseProgramMode(u32 mode)
{
	EFM_SetOperateMode(mode);
}

u8 EFM_GetCacheStatus(void)
{
	uint32_t u32Tmp;
	u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_FRMC_CRST | EFM_FRMC_PREFETE | EFM_FRMC_DCACHE | EFM_FRMC_ICACHE);
	return u32Tmp;
}

u8 EFM_WaitForOperationDone(u32 timeout)
{
	u32 delay=0;
	u8 result=0;

	while(delay<timeout)
	{
		if(EFM_GetStatus(EFM_FLAG_RDY))
		{
			result=1;
			break;
		}
		delay++;
	}
	if(EFM_GetStatus(EFM_FLAG_OPTEND))
	{
		EFM_ClearStatus(EFM_FLAG_OPTEND);
	}

	if(EFM_GetStatus(EFM_FLAG_COLERR)
		||EFM_GetStatus(EFM_FLAG_PGMISMTCH)
		||EFM_GetStatus(EFM_FLAG_PGSZERR)
		||EFM_GetStatus(EFM_FLAG_PEPRTERR)
		||EFM_GetStatus(EFM_FLAG_OTPWERR))
	{
		EFM_ClearStatus(EFM_FLAG_COLERR|EFM_FLAG_PGMISMTCH|EFM_FLAG_PGSZERR|EFM_FLAG_PEPRTERR|EFM_FLAG_OTPWERR);
		result=0;
	}
	return result;
}

u8 EFM_WriteFlash(u32 addr,u8 *buffer,u32 length)
{
	u32 word_length;
	u32 *write_buff=(u32 *)buffer;
	volatile u32 *flash_addr=(u32 *)addr;
	u32 i;
	u8 temp;
	u8 result=0;

	if((addr%4u)==0
		&&(length%4u)==0)
	{
		word_length=length/4u;
		EFM_REG_Unlock();
		result=EFM_WaitForOperationDone(1000);
		if(result)
		{
			temp=EFM_GetCacheStatus();
			EFM_ICacheCmd(DISABLE);
			EFM_FWMC_Cmd(ENABLE);
			EFM_SequenceSectorOperateCmd(EFM_SECTOR0_NUM, 32U, ENABLE);
			EFM_SetEraseProgramMode(EFM_MD_PGM_SINGLE);
			for(i=0;i<word_length;i++)
			{
				*flash_addr=write_buff[i];
				while(!EFM_GetStatus(EFM_FLAG_RDY))
				{
				}
				if(EFM_GetStatus(EFM_FLAG_PGMISMTCH))
				{
					result=0;
					break;
				}
				flash_addr++;
				EFM_ClearStatus(EFM_FLAG_OPTEND);
			}
			EFM_SetEraseProgramMode(EFM_MD_READONLY);
			EFM_SequenceSectorOperateCmd(EFM_SECTOR0_NUM, 32U, DISABLE);
			EFM_FWMC_Cmd(DISABLE);
			EFM_ICacheCmd((en_functional_state_t)temp);
		}
		EFM_REG_Lock();
	}
	return result;
}

u8 EFM_EraseSector(u32 addr)
{
	u8 result;
	u8 temp;
	

	EFM_REG_Unlock();
	result=EFM_WaitForOperationDone(1000);
	
	if(result)
	{
		temp=EFM_GetCacheStatus();
		EFM_ICacheCmd(DISABLE);
		EFM_FWMC_Cmd(ENABLE);
		EFM_SequenceSectorOperateCmd(EFM_SECTOR0_NUM, 32U, ENABLE);
		EFM_SetEraseProgramMode(EFM_MD_ERASE_SECTOR);
		*(  u32 *)(addr)=0xFFFFFFFF;
		result=EFM_WaitForOperationDone(1000);
		EFM_SetEraseProgramMode(EFM_MD_READONLY);
		EFM_SequenceSectorOperateCmd(EFM_SECTOR0_NUM, 32U, DISABLE);
    EFM_FWMC_Cmd(DISABLE);
		EFM_ICacheCmd((en_functional_state_t)temp);
	}
	EFM_REG_Lock();
	return result;
}

void EraseUserArea(u32 erase_addr,u8 page_num)
{
	u32 i;

	for (i=0;i<page_num;i++)
	{
		EFM_EraseSector((erase_addr+i*8*1024));
	}
}

void FLASH_Write(u32 write_addr,u32 *buffer,u32 num_to_write)	
{
	EFM_WriteFlash(write_addr,((u8 *)buffer),(num_to_write*4));
}

void iap_load_app(u32 appxaddr)
{
	stc_gpio_init_t stcGpioInit;
	u32 stack_top=*((volatile u32 *)appxaddr);
	u32 jump_address;
	
	if((stack_top > SRAM_BASE)&&(stack_top<=(SRAM_BASE+RAM_SIZE)))
	{
		gFlashPushNum = 0xA055FAFA;
		EraseUserArea(FLASH_EEPROM_ADDR,1);
		FLASH_Write(FLASH_EEPROM_ADDR,&gFlashPushNum,1);
		RMU_ClearStatus();
		
		TMRA_DeInit(CM_TMRA_5);
		TMRA_IntCmd(CM_TMRA_5, TMRA_INT_OVF, DISABLE);
		TMRA_ClearStatus(CM_TMRA_5, TMRA_FLAG_OVF);
		TMRA_Stop(CM_TMRA_5);
		FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_5, DISABLE);
		INTC_IrqSignOut(TIMERA_5_OVF_IRQn);
		NVIC_ClearPendingIRQ(TIMERA_5_OVF_IRQn);
		NVIC_DisableIRQ(TIMERA_5_OVF_IRQn);
		
		TMRA_DeInit(CM_TMRA_1);
		TMRA_Stop(CM_TMRA_1);
		FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_1, DISABLE);
		
		TMRA_DeInit(CM_TMRA_2);
		TMRA_Stop(CM_TMRA_2);
		FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_2, DISABLE);
		
		TMRA_DeInit(CM_TMRA_3);
		TMRA_Stop(CM_TMRA_4);
		FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_4, DISABLE);
		
		TMRA_DeInit(CM_TMRA_4);
		TMRA_Stop(CM_TMRA_4);
		FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_4, DISABLE);
		
		TMR6_DeInit(CM_TMR6_1);
		TMR6_Stop(CM_TMR6_1);
		FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_1, DISABLE);
		
		RTC_DeInit();
		INTC_IrqSignOut(RTC_PERIOD_IRQn);
		NVIC_ClearPendingIRQ(RTC_PERIOD_IRQn);
		NVIC_DisableIRQ(RTC_PERIOD_IRQn);
		CLK_Xtal32Cmd(DISABLE);
		
		ADC_DeInit(CM_ADC1);
		FCG_Fcg3PeriphClockCmd(PWC_FCG3_ADC1, DISABLE);


		USART_DeInit(CM_USART4);
		FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_USART4, DISABLE);
		
		USART_DeInit(CM_USART1);
		USART_FuncCmd(CM_USART1,USART_TX,DISABLE);
		USART_FuncCmd(CM_USART1,USART_FLAG_TX_EMPTY,DISABLE);
		USART_FuncCmd(CM_USART1,USART_RX,DISABLE);
		USART_FuncCmd(CM_USART1,USART_INT_RX,DISABLE);
		FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_USART1, DISABLE);
		INTC_IrqSignOut(USART1_RX_FULL_IRQn);
		NVIC_ClearPendingIRQ(USART1_RX_FULL_IRQn);
		NVIC_DisableIRQ(USART1_RX_FULL_IRQn);
		INTC_IrqSignOut(USART1_TX_EMPTY_IRQn);
		NVIC_ClearPendingIRQ(USART1_TX_EMPTY_IRQn);
		NVIC_DisableIRQ(USART1_TX_EMPTY_IRQn);
		INTC_IrqSignOut(USART1_RX_ERR_IRQn);
		NVIC_ClearPendingIRQ(USART1_RX_ERR_IRQn);
		NVIC_DisableIRQ(USART1_RX_ERR_IRQn);
		
		USART_DeInit(CM_USART2);
		USART_FuncCmd(CM_USART2,USART_TX,DISABLE);
		USART_FuncCmd(CM_USART2,USART_FLAG_TX_EMPTY,DISABLE);
		USART_FuncCmd(CM_USART2,USART_RX,DISABLE);
		USART_FuncCmd(CM_USART2,USART_INT_RX,DISABLE);
		FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_USART2, DISABLE);
		INTC_IrqSignOut(USART2_RX_FULL_IRQn);
		NVIC_ClearPendingIRQ(USART2_RX_FULL_IRQn);
		NVIC_DisableIRQ(USART2_RX_FULL_IRQn);
		INTC_IrqSignOut(USART2_TX_EMPTY_IRQn);
		NVIC_ClearPendingIRQ(USART2_TX_EMPTY_IRQn);
		NVIC_DisableIRQ(USART2_TX_EMPTY_IRQn);
		INTC_IrqSignOut(USART2_RX_ERR_IRQn);
		NVIC_ClearPendingIRQ(USART2_RX_ERR_IRQn);
		NVIC_DisableIRQ(USART2_RX_ERR_IRQn);

//		CAN_IrqCmd(CanRxIrqEn,Disable);
//		CAN_IrqCmd(CanBusErrorIrqEn,Disable);
//		NVIC_ClearPendingIRQ(CAN_INT_IRQn);
//		NVIC_DisableIRQ(CAN_INT_IRQn);

		Gpio_EncoderIntDisable();
		Gpio_AccIntDisable();
//		Gpio_CanIntDisable();
		
		GPIO_SetDebugPort(GPIO_PIN_TRST|GPIO_PIN_TDI|GPIO_PIN_TDO|GPIO_PIN_SWO, DISABLE);
		(void)GPIO_StructInit(&stcGpioInit);
		stcGpioInit.u16PinDrv=PIN_DIR_OUT;
		stcGpioInit.u16PinDir=PIN_HIGH_DRV;
		
		GPIO_Init(GPIO_TFT_BL_PWM_PORT,GPIO_TFT_BL_PWM_PIN,&stcGpioInit);
		GPIO_SetFunc(GPIO_TFT_BL_PWM_PORT, GPIO_TFT_BL_PWM_PIN, GPIO_FUNC_0);
		GPIO_SetPins(GPIO_TFT_BL_PWM_PORT,GPIO_TFT_BL_PWM_PIN);
		
		jump_address=*(volatile u32 *)(appxaddr+4);
		jump2app=(func_ptr_t)jump_address;
		__set_MSP(*(volatile u32 *)appxaddr);
		jump2app();
	}
}
#endif

int main(void)
{
#if defined(AUTOCHIPS_AC781X)
    __ASM(" CPSID i");
#ifdef FLASH_SIZE_64K
	SCB->VTOR = FLASH_IAP_ADDR |(0x3000);
#else
    SCB->VTOR = FLASH_IAP_ADDR |(0x5000);
#endif
	SystemInit();
#elif defined(HDSC_HC32F460)
	ResetMute(); 
	__disable_irq();
	SCB->VTOR = FLASH_IAP_ADDR |(0x6000);
	SystemClockConfig();
#if RTC_TIMER_FUN==1 && PLATFORM_TYPE!=REALTEK_RTD1861B_PLATFORM
	RTC_Init_HC32F460();
#endif
#elif defined(HDSC_HC32L072)
	__disable_irq();
	SystemClockConfig();
	Flash_Init(12,1);
#elif defined(STM32_F103VC)||defined(STM32F401xx)
    __disable_irq();
    SystemInit();	
    SCB->VTOR = FLASH_BASE | 0x4000;
    Delay_init();
#elif defined(HDSC_HC32F448)
	LL_PERIPH_WE(LL_PERIPH_ALL);
	ResetMute(); 
	__disable_irq();
	SCB->VTOR = FLASH_IAP_ADDR |(0x6000);
	SystemClockConfig();
#if RTC_TIMER_FUN==1
	RTC_Init_HC32F448();
#endif	 
#endif	 
	SystemResetCheck();
	HardwareInit();
	#if NAVI_TEST_FUN==1
		TH810_POWER_OFF;
		#endif
#if MULTIPLE_HDMI_FUN==1
	HDMI_IC_TypeDet();
#endif
	SoftWareInit();
#if defined(AUTOCHIPS_AC781X)	
	RTC_WakeupInit();
	WWG_Init();
    __ASM(" CPSIE i");
#elif defined(HDSC_HC32F460)||defined(HDSC_HC32F448)
	__enable_irq();
#elif defined(HDSC_HC32L072)
	WDT_Init_HC32L072();
	__enable_irq();
#elif defined(STM32_F103VC)
    IWDG_Init();
    __enable_irq();
#elif defined(STM32F401xx)
	IWDG_Init();
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	F_RTC_READY=RTC_TimerInit();
	 __enable_irq();
	GPIO_AccIntCfg();
#endif

#if MAIN_DEBUG_FUN==1
	printf("STM32 restart!!!,F_RTC_READY=%x\r\n",F_RTC_READY);
#endif	
	while(1)
	{
		if(F_SYS_1MS)
		{		
			//MS1_counter++;
#if MODEL==LINUX_D089_55||MODEL==LINUX_12S9_AA
			if(ACC_DET_LEVEL)
      {
				ICN_VCC_OFF;
			}
			else
      {
				ICN_VCC_ON;
			}
#endif
			
			
#if defined(AUTOCHIPS_AC781X)
			WDOG_Feed();
#elif defined(HDSC_HC32F460)
			SWDT_RefreshCounter();
#elif defined(HDSC_HC32L072)
			Wdt_Feed();
#elif defined(STM32_F103VC)||defined(STM32F401xx)
            IWDG_ReloadCounter();
#elif defined(HDSC_HC32F448)
			SWDT_FeedDog();
#endif

			F_SYS_1MS=0;
			APP_DataAnalyse();  
			
#if CAN_ADAPTER==1||CAN_FUNCTION==1
			CanBoxMainPro();
#endif
#if CAN_BUS_OFF_FUN==1
			BUS_OFF_MainPro();
#endif
#if LOW_VOLTAGE_DELAY_OFF_FUN==1
			LowVoltagePro();
#endif
#if POWER_ONE_HOUR_MODE_FUN==1
#else
			if(F_EMERGENCY_POWER_DOWN)
			{
#if MAIN_DEBUG_FUN==1
				printf("F_EMERGENCY_POWER_DOWN\r\n");
#endif	
				F_EMERGENCY_POWER_DOWN=0;	
				if(nPowerState!=POWER_SYSTEM_STANDBY)
				{
					EmergencyPowerDown();
#if MAIN_DEBUG_FUN==1
					printf("EmergencyPowerDown()\r\n");
#endif
				}
			}
#endif
		}
		if(F_SYS_5MS==1)
		{
			F_SYS_5MS=0;
#if POWER_ONE_HOUR_MODE_FUN==0   //���imax8һСʱģʽ�򿪣�������
			ACC_On_Detect();
#endif
#if REMOTE_FUNCTION==1
			Watch_IR_Timeout();	
#endif
#if USB_TPS2549_FUN==1		
			TPS2549_WorkPro();
#endif
			// if(Get_IAP_Mode)
			if(F_IAP_AppCom == 0x78 && F_IAP_InitSystem == 0x9a && F_IAP_Power == 0xbc)
			{
				IAP_Timer++;
				if(IAP_Timer>=5)
				{
					EEPROM_Clear();
#if UUID_FUNCTION==1
					if(IsUUID_CodeExist())
					{
						UUID_SaveData();
					}
#endif
#if MODEL== ANDROID_Q133_00||MODEL== ANDROID_Q133_01||MODEL== ANDROID_Q133_uni
					if(IsUNIT_PartExist())
					{
						UNIT_PART_SaveData();
					}
					if(IsUNIT_SerialExist())
					{
						UNIT_SERIAL_SaveData();
					}
#endif
					
#if CANBOX_FUNC_MULTIPLE==1
                    EEPROM_Save_CANboxFunc();
#endif
#if TUNER_FUNCTION==1
#if SAVE_TUNER_INFO_WHEN_B_OFF==1
#if MODEL==LINUX_1465_16||MODEL==LINUX_1465W_16M
					TunerInfoSave();
#else
					TunerDefaultInfoLoad();
#endif
#endif
#endif
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
					AppBackupDataSave();
#endif
					iap_load_app(FLASH_IAP_ADDR);
				}
			}
		}
		if(F_SYS_10MS==1)
		{
			F_SYS_10MS=0;
			Tick_10ms_Pro();
#if POWER_ONE_HOUR_MODE_FUN==0      //���imax8һСʱģʽ�򿪣�������
			ACC_Off_Detect(); 
#endif			
			PowerManage();
#if UPDATE_APP_FUNCTION==1
			Update_Key_Detect();	
#endif
#if MCU_NEED_BEEP_FUN==1
			Beep_Pro();
#endif
#if REMOTE_FUNCTION==1
			IR_Key_Pro();					
#endif
			APP_MainPro();
			KeyScanPro();
#if TUNER_FUNCTION==1			
			Radio_Main();			
#if SUPPORT_RDS==1
			RDS_Module();
#endif 
#endif
#if PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			HighBeamDetect();
			LeftLampDetect();
			RightLampDetect();
#else
			IllumiSignalDetect();  

        ReverseSignalDetect();

#if MODEL==LINUX_2289_31||MODEL==LINUX_2289_03
			SpeedSignalDetect();
#endif
			ParkingSignalDetect();
#endif

#if UUID_FUNCTION==1
			UUID_MainPro();
#endif
#if DUAL_DAB_FUN==1
			KS_MainPro();
#endif
#if DAB_UPDATE_FUN==1
			if(F_KS_UPDATE_REQ)
			{
				IAP_Timer++;
				if(IAP_Timer>=5)
				{
					KeystoneUpdateState=KS_UPD_START;
					KS_UpdateFlag.byte=0;
					KS_UpdateTimer=0;
					F_KS_UPDATE_REQ=1;
					break;
				}
			}
#endif

#if CAN_ADAPTER==1
#if CANBOX_BNR_UPDATE_FUN==1||CANBOX_UPDATE_FUN_HIWORLD==1||CANBOX_UPDATE_FUN_SIMPLE==1||CANBOX_UPDATE_FUN_GOLF==1
			if(IsReqCanUpdate()
#if PLATFORM_TYPE==SUNPLUS_8368U_PLATFORM||PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM||PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
				&&F_UART_INIT_FALG==1
#endif
				)
			{
#if CANBOX_BNR_UPDATE_FUN==1||CANBOX_UPDATE_FUN_SIMPLE==1
				IAP_Timer++;
				if(IAP_Timer>=10)
#endif
				{
					break;
				}
			}			
#endif
#endif

#if FACTORY_AUTO_TEST_FUN==1
			AutoTestMainPro();
#endif 
#if DUAL_SIM_FUN==1||DUAL_SIM2_FUN==1
			Dual_SIM_RxAnalyse();
#endif
#if DUAL_MCM_FUN==1
            Dual_MCM_RxAnalyse();
#endif
#if TOUCH_DET_FUN==1
			TouchDataAnalyse();
#endif
#if SUZUKI_UART_FUN==1
			SuzukiUartMainPro();
#endif
#if AM_688_UART_FUN==1
			Am_688UartMainPro();
#endif
#if MLINK_FUN==1
			USB_MIRROR_Main();
#endif
#if RADAR_HAIMA_S7_FUN==1
  Radar_HaimaS7_UartMainPro();
#endif
#if CH7102_UPD_FUN==1
			CH7102_UpdatePro();
#elif LT8619C_FUN==1
			LT8619C_StartupSeq();
#elif MULTIPLE_HDMI_FUN==1
			CH7102_UpdatePro();
			LT8619C_StartupSeq();
#endif
#if	AIM_915_916_FUN ==1
            AIM_Init_Step();
#endif
#if DVD_FUNCTION==1
			Disc_Main();
#endif
#if PANNEL_DETECT_FUN==1
			PannelDetect();
#endif
#if AHD_360_FUN==1
			AHD_360_MainPro();
#endif
#if CXD4933_FUN==1
            CXD4933_Main_Pro();
#endif
#if BU18RL82_FUN==1
   BU18xL82_Main_Pro();
#endif
#if BU32107_FUN==1
			BU32107_WorkPro();
#endif
#if MAX9288_FUN==1
			MAX9288_InitPro();
#endif
#if MAX96789==1
			MAX_InitPro();
#endif
#if LT9211_FUN==1
			LT9211_WorkPro();
#endif
#if MODEL==LINUX_2389WU_65||MODEL==LINUX_2359W_PC||MODEL==LINUX_2359W_SK||MODEL==LINUX_1529W_01||MODEL==LINUX_1529U_14
			LCD_Reset();
#endif
#if TDA75610_FUN == 1
			TDA75610_Monitor();
#endif
#if TAS6424M_Q1_FUN == 1
#if MODEL==LINUX_N039_DZ
			if(TAS6424_Flag)
			{
				TAS6424_Main_PRO();
			}
#else
			TAS6424_Main_PRO();
#endif
#endif
#if PLATFORM_TYPE==REALTEK_RTD1861B_PLATFORM
			RTC_Init_HC32F460();
#endif
#if A2B_AD2433_FUN==1
			A2B_DiscoveryPro();
#endif
#if LT9211D_FUN == 1
			LT9211D_Main();
#endif
		}
		if(F_SYS_25MS==1)
		{
			F_SYS_25MS=0;
			MMI();
			//ChannelProcess();
#if PLATFORM_TYPE!=SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			Parking_Detect();
#endif
#if SUPPORT_RDS==1
#if TUNER_TYPE==TEF6686_TUNER||TUNER_TYPE==TEF6657_TUNER||TUNER_TYPE==TEF6851_TUNER||TUNER_TYPE==SI4745_TUNER||TUNER_TYPE==SI4755_TUNER
			if(Is_Machine_Power)
			{
				RDSFetchBlockData();
			}
#elif TUNER_TYPE==MULTIPLE_TUNER
#if MULTIPLE_TUNER_SUBSET==NXP_TUNER
			if(Is_Machine_Power
				&&(MULTIPLE_TUNER_TYPE==TEF6686_TUNER||MULTIPLE_TUNER_TYPE==TEF6657_TUNER||MULTIPLE_TUNER_TYPE==TEF6851_TUNER))
			{
				TEF6686_RDSFetchBlockData();
			}
#elif MULTIPLE_TUNER_SUBSET==SILICON_TUNER
			if(Is_Machine_Power
				&&MULTIPLE_TUNER_TYPE==SI4745_TUNER)
			{
				SI47XX_RDSFetchBlockData();();
			}
#endif
#endif
#endif
#if FMT_FUNCTION==1
			FMT_MainPro();
#endif
		}
		if(F_SYS_50MS==1)
		{
			F_SYS_50MS=0;
#if PLATFORM_TYPE!=SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			Illumi_Detect();
			Reverse_Detect();
#endif
#if MODEL==LINUX_D068_55||MODEL==LINUX_D078_55||MODEL==LINUX_P058_55||MODEL==LINUX_6178_58||MODEL==LINUX_D065_55||MODEL==LINUX_D095_55
			AuxIn_Detect();
#endif
#if MODEL==LINUX_F018A_21||MODEL==LINUX_K028A_21||MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21||MODEL==LINUX_1338_21||MODEL==LINUX_1268_03||MODEL==LINUX_1269_21||MODEL==LINUX_1475_21||MODEL==LINUX_9289_21||MODEL==LINUX_1475_CP\
			||MODEL==LINUX_1479_21//||MODEL==LINUX_1299U_21
			TEL_Mute_Detect();
#endif
		}
	if(F_SYS_100MS==1)
		{
			F_SYS_100MS=0;
			Tick_100ms_Pro();
#if PLATFORM_TYPE!=SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			EncoderDataPro();
#if MODEL==ANDROID_Q133_00||MODEL==ANDROID_Q133_01||MODEL== ANDROID_Q133_uni
			if(A_ILL_Flag==0)
			{
				Key_Led_Driver();
			}	 
#else
#if MODEL==LINUX_1488C_11
			if(Key1388LedDelay>0)
			{
				Key1388LedDelay--;
			}
#endif
			Key_Led_Driver(); 
#endif
#endif
#if	NAVI_TEST_FUN==1
		TH810_Power();
#endif			
			MainTickCounter++;
			if(0==(MainTickCounter%30))
			{
#if TEF6686_DEBUG_FUN==1
				printf("%05d:level=%02d,usn=%02d,wam=%02d,offset=%02d,modulation=%02d\r\n",radiostruct_ram.freq,Radio.SMeter,Radio.Usn,Radio.Wam,Radio.Ifc,Radio.Modulation);
#endif
			}
			if(0==(MainTickCounter%10))
			{
#if MAIN_DEBUG_FUN==1
#if AIM_915_916_FUN==1
				printf("STM32 running--Aim_Init_Status=%02x\r\n",Aim_Init_Status);
#else
                printf("STM32 running\r\n");
#endif
#endif
#if RTC_TIMER_FUN==1
                if(nPowerState==POWER_NORMAL_RUN)
                {
					RTC_DATE_TIME_TYPE_DEF read_time;
					read_time=RTC_ReadTime();
					if(!(read_time.year==0
						&&read_time.month==0
						&&read_time.day==0
						&&read_time.hours==0
						&&read_time.minutes==0))
					{
                        RTC_TimeInfo=RTC_ReadTime();
					}
                    F_RTC_READ_STATUS = 1;
#if MODEL == LINUX_P058_55                    
                    PostMessage(SUB_CAN_MODULE,PEUGEOT_207_DATE_DATA,0);
#endif   
#if MAIN_DEBUG_FUN==1
					printf("Time=%d,%d,%d,%d:%d\r\n",RTC_TimeInfo.year,RTC_TimeInfo.month,RTC_TimeInfo.day,RTC_TimeInfo.hours,RTC_TimeInfo.minutes);
#endif                    
                }
                else
                {
                	F_RTC_READ_STATUS=0;
                }
#endif
#if PLATFORM_TYPE==SUNPLUS_8268K_PLATFORM
				if(TxClockTimer)
				{
					TxClockTimer--;
					if(TxClockTimer==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CLOCK,0);
					}
				}
#endif
#if TUNER_FUNCTION==1
				DC_DC_SyncPro();
#endif
#if TPA6304_Q1_FUN==1
#if MODEL==LINUX_N039_DZ
				if(((MainTickCounter%50)==0)&&TPA6304_Flag)
				{
				TPA6304_Monitor();
				}			
#else								
				if((MainTickCounter%50)==0)
				{
				TPA6304_Monitor();
				}
#endif
#endif
#if TAS6424M_Q1_FUN==1
#if MODEL==LINUX_N039_DZ
				if(((MainTickCounter%10)==0)&&TAS6424_Flag)
				{
				TAS6424_Monitor();
				}
#else					
				if((MainTickCounter%10)==0)
				{
				TAS6424_Monitor();
				}
#endif
#endif
			}
#if DUAL_SIM_FUN==1||DUAL_SIM2_FUN==1
			Dual_SIM_100ms_Timer();
#endif
#if PLATFORM_TYPE==SUNPLUS_8368U_MOTORCYCLE_PLATFORM
			Voltage_Error_Detect();
			FuelOilDetect();
			TemperatureDetect();
			EngineTroubleDetect();
			AbsTroubleDetect();
			OilTroubleDetect();
			MotorCycleInfoPro();
#endif
#if MODEL==LINUX_6255W_57||MODEL==LINUX_6255W_AA57||MODEL==LINUX_1295WH_PC||MODEL==LINUX_9325W_25||MODEL==LINUX_1275W_CP||MODEL==LINUX_1345W_CP||MODEL==LINUX_1345W_CP1||MODEL==LINUX_1345W_CP2||MODEL==LINUX_1345W_65HINO\
			||MODEL==LINUX_1327W_65HINO||MODEL==LINUX_1325W_53||MODEL==LINUX_1299U_21||MODEL==LINUX_1529W_01||MODEL==LINUX_1365W_PCDN||MODEL==LINUX_1529U_14
		Fan_Control();
#endif
#if MODEL==LINUX_1465_16||MODEL==LINUX_1345W_CP1||MODEL==LINUX_1345W_CP2||MODEL==LINUX_1345W_65HINO||MODEL==LINUX_1327W_65HINO||MODEL==LINUX_1465W_16M||MODEL==LINUX_1325W_53||MODEL==LINUX_1365W_PCDN
		TemperatureDetect();
#endif
#if DAB_FM_FUN==1
		DAB_FMPro();
#endif
#if MODEL==LINUX_Y039_55||MODEL==LINUX_2309A_02||MODEL==LINUX_1349W_YS||MODEL==LINUX_2409_31||MODEL==LINUX_1379UC_11||MODEL==LINUX_1489UC_11
      TurnSignalDetect();
#endif
#if MODEL==LINUX_1295_69||MODEL==LINUX_1295W_ET||MODEL==LINUX_1305W_GB||MODEL==LINUX_1276_MG
		Amplifier_Ctrl_Delay();
#endif
#if TFT_CMD_FUN==1
		if(NEW_TFT_FLAG)
		{
			TFT_CMD_OutputStart();
		}
#endif
		}	
	}
#if DAB_UPDATE_FUN==1
	if(F_KS_UPDATE_REQ)
	{
		KeystoneUpdatePro();
	}
	else
#endif
#if CAN_ADAPTER == 1
#if CANBOX_BNR_UPDATE_FUN==1||CANBOX_UPDATE_FUN_HIWORLD==1||CANBOX_UPDATE_FUN_SIMPLE==1||CANBOX_UPDATE_FUN_GOLF==1
	if(IsReqCanUpdate())
	{
		CanBoxUpdatePro();	
	}
	else
#endif
#endif
	{
	}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
     
  printf("Wrong parameters value: file %s on line %d\r\n", file, line);

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */
  

