#include "public.h"
#if A2B_AD2433_FUN==1

A2B_PRO_DATA A2B_ProData;

const u8 AD2433_DefaultRegValue[MAX_A2B_REGISTER_NUM]=
{
	0x50,// Register Address 0x00 
	0x00,// Register Address 0x01 
	0xAD,// Register Address 0x02 
	0x35,// Register Address 0x03 
	0x00,// Register Address 0x04 
	0x03,// Register Address 0x05 
	0x00,// Register Address 0x06 
	0x00,// Register Address 0x07 
	0x00,// Register Address 0x08 
	0x00,// Register Address 0x09 
	0x00,// Register Address 0x0A 
	0x00,// Register Address 0x0B 
	0x00,// Register Address 0x0C 
	0x00,// Register Address 0x0D 
	0x00,// Register Address 0x0E 
	0x40,// Register Address 0x0F 
	0x00,// Register Address 0x10 
	0x00,// Register Address 0x11 
	0x00,// Register Address 0x12 
	0x00,// Register Address 0x13 
	0x00,// Register Address 0x14 
	0x00,// Register Address 0x15 
	0x00,// Register Address 0x16 
	0x00,// Register Address 0x17 
	0x00,// Register Address 0x18 
	0x00,// Register Address 0x19 
	0x00,// Register Address 0x1A 
	0x00,// Register Address 0x1B 
	0x00,// Register Address 0x1C 
	0x00,// Register Address 0x1D 
	0x00,// Register Address 0x1E 
	0x00,// Register Address 0x1F 
	0x00,// Register Address 0x20 
	0x00,// Register Address 0x21 
	0x00,// Register Address 0x22 
	0x00,// Register Address 0x23 
	0x00,// Register Address 0x24 
	0x00,// Register Address 0x25 
	0x00,// Register Address 0x26 
	0x00,// Register Address 0x27 
	0x00,// Register Address 0x28 
	0x80,// Register Address 0x29 
	0x00,// Register Address 0x2A 
	0x00,// Register Address 0x2B 
	0x00,// Register Address 0x2C 
	0x00,// Register Address 0x2D 
	0x00,// Register Address 0x2E 
	0x00,// Register Address 0x2F 
	0x00,// Register Address 0x30 
	0x00,// Register Address 0x31 
	0x00,// Register Address 0x32 
	0x00,// Register Address 0x33 
	0x00,// Register Address 0x34 
	0x00,// Register Address 0x35 
	0x00,// Register Address 0x36 
	0x00,// Register Address 0x37 
	0x00,// Register Address 0x38 
	0x00,// Register Address 0x39 
	0x00,// Register Address 0x3A 
	0x00,// Register Address 0x3B 
	0x00,// Register Address 0x3C 
	0x00,// Register Address 0x3D 
	0x00,// Register Address 0x3E 
	0x00,// Register Address 0x3F 
	0x00,// Register Address 0x40 
	0x00,// Register Address 0x41 
	0x00,// Register Address 0x42 
	0x00,// Register Address 0x43 
	0x00,// Register Address 0x44 
	0x00,// Register Address 0x45 
	0x00,// Register Address 0x46 
	0x00,// Register Address 0x47 
	0x00,// Register Address 0x48 
	0x00,// Register Address 0x49 
	0x00,// Register Address 0x4A 
	0x00,// Register Address 0x4B 
	0x00,// Register Address 0x4C 
	0x00,// Register Address 0x4D 
	0x00,// Register Address 0x4E 
	0x00,// Register Address 0x4F 
	0x00,// Register Address 0x50 
	0x00,// Register Address 0x51 
	0x01,// Register Address 0x52 
	0x00,// Register Address 0x53 
	0x00,// Register Address 0x54 
	0x00,// Register Address 0x55 
	0x01,// Register Address 0x56 
	0x00,// Register Address 0x57 
	0x00,// Register Address 0x58 
	0x00,// Register Address 0x59 
	0x00,// Register Address 0x5A 
	0x00,// Register Address 0x5B 
	0x00,// Register Address 0x5C 
	0x00,// Register Address 0x5D 
	0x00,// Register Address 0x5E 
	0x00,// Register Address 0x5F 
	0x00,// Register Address 0x60 
	0x00,// Register Address 0x61 
	0x00,// Register Address 0x62 
	0x00,// Register Address 0x63 
	0x00,// Register Address 0x64 
	0x00,// Register Address 0x65 
	0x00,// Register Address 0x66 
	0x00,// Register Address 0x67 
	0x00,// Register Address 0x68 
	0x00,// Register Address 0x69 
	0x00,// Register Address 0x6A 
	0x00,// Register Address 0x6B 
	0x00,// Register Address 0x6C 
	0x00,// Register Address 0x6D 
	0x00,// Register Address 0x6E 
	0x00,// Register Address 0x6F 
	0x00,// Register Address 0x70 
	0x00,// Register Address 0x71 
	0x00,// Register Address 0x72 
	0x00,// Register Address 0x73 
	0x00,// Register Address 0x74 
	0x00,// Register Address 0x75 
	0x00,// Register Address 0x76 
	0x00,// Register Address 0x77 
	0x00,// Register Address 0x78 
	0x00,// Register Address 0x79 
	0x00,// Register Address 0x7A 
	0x00,// Register Address 0x7B 
	0x00,// Register Address 0x7C 
	0x00,// Register Address 0x7D 
	0x00,// Register Address 0x7E 
	0x00,// Register Address 0x7F 
	0x00,// Register Address 0x80 
	0x00,// Register Address 0x81 
	0x00,// Register Address 0x82 
	0x00,// Register Address 0x83 
	0x00,// Register Address 0x84 
	0x00,// Register Address 0x85 
	0x00,// Register Address 0x86 
	0x00,// Register Address 0x87 
	0x00,// Register Address 0x88 
	0x00,// Register Address 0x89 
	0x00,// Register Address 0x8A 
	0x00,// Register Address 0x8B 
	0x00,// Register Address 0x8C 
	0x00,// Register Address 0x8D 
	0x00,// Register Address 0x8E 
	0x00,// Register Address 0x8F 
	0x00,// Register Address 0x90 
	0x02,// Register Address 0x91 
	0x00,// Register Address 0x92 
	0x00,// Register Address 0x93 
	0x00,// Register Address 0x94 
	0x00,// Register Address 0x95 
	0x02,// Register Address 0x96 
	0x02,// Register Address 0x97 
	0x00,// Register Address 0x98 
	0x00,// Register Address 0x99 
	0x00,// Register Address 0x9A 
	0x00,// Register Address 0x9B 
	0x00,// Register Address 0x9C 
	0x00,// Register Address 0x9D 
	0x00,// Register Address 0x9E 
	0x00,// Register Address 0x9F 
	0x00,// Register Address 0xA0 
	0x00,// Register Address 0xA1 
	0x00,// Register Address 0xA2 
	0x00,// Register Address 0xA3 
	0x00,// Register Address 0xA4 
	0x00,// Register Address 0xA5 
	0x00,// Register Address 0xA6 
	0x00,// Register Address 0xA7 
	0x00,// Register Address 0xA8 
	0x00,// Register Address 0xA9 
	0x00,// Register Address 0xAA 
	0x00,// Register Address 0xAB 
	0x00,// Register Address 0xAC 
	0x00,// Register Address 0xAD 
	0x00,// Register Address 0xAE 
	0x00,// Register Address 0xAF 
	0x00,// Register Address 0xB0 
	0x00,// Register Address 0xB1 
	0x00,// Register Address 0xB2 
	0x00,// Register Address 0xB3 
	0x00,// Register Address 0xB4 
	0x00,// Register Address 0xB5 
	0x00,// Register Address 0xB6 
	0x00,// Register Address 0xB7 
	0xFF,// Register Address 0xB8 
	0xFF,// Register Address 0xB9 
	0xFF,// Register Address 0xBA 
	0xFF,// Register Address 0xBB 
	0xFF,// Register Address 0xBC 
	0xFF,// Register Address 0xBD 
	0xFF,// Register Address 0xBE 
	0xFF,// Register Address 0xBF 
	0x00,// Register Address 0xC0 
	0x01,// Register Address 0xC1 
	0x02,// Register Address 0xC2 
	0x03,// Register Address 0xC3 
	0x04,// Register Address 0xC4 
	0x05,// Register Address 0xC5 
	0x06,// Register Address 0xC6 
	0x07,// Register Address 0xC7 
	0x08,// Register Address 0xC8 
	0x09,// Register Address 0xC9 
	0x0A,// Register Address 0xCA 
	0x0B,// Register Address 0xCB 
	0x0C,// Register Address 0xCC 
	0x0D,// Register Address 0xCD 
	0x0E,// Register Address 0xCE 
	0x0F,// Register Address 0xCF 
	0x10,// Register Address 0xD0 
	0x11,// Register Address 0xD1 
	0x12,// Register Address 0xD2 
	0x13,// Register Address 0xD3 
	0x14,// Register Address 0xD4 
	0x15,// Register Address 0xD5 
	0x16,// Register Address 0xD6 
	0x17,// Register Address 0xD7 
	0x18,// Register Address 0xD8 
	0x19,// Register Address 0xD9 
	0x1A,// Register Address 0xDA 
	0x1B,// Register Address 0xDB 
	0x1C,// Register Address 0xDC 
	0x1D,// Register Address 0xDD 
	0x1E,// Register Address 0xDE 
	0x1F,// Register Address 0xDF 
	0x00,// Register Address 0xE0 
	0x00,// Register Address 0xE1 
	0x00,// Register Address 0xE2 
	0x00,// Register Address 0xE3 
	0x00,// Register Address 0xE4 
	0x00,// Register Address 0xE5 
	0x00,// Register Address 0xE6 
	0x00,// Register Address 0xE7 
	0x00,// Register Address 0xE8 
	0x00,// Register Address 0xE9 
	0x00,// Register Address 0xEA 
	0x00,// Register Address 0xEB 
	0x00,// Register Address 0xEC 
	0x00,// Register Address 0xED 
	0x00,// Register Address 0xEE 
	0x00,// Register Address 0xEF 
	0x00,// Register Address 0xF0 
	0x00,// Register Address 0xF1 
	0x00,// Register Address 0xF2 
	0x00,// Register Address 0xF3 
	0x00,// Register Address 0xF4 
	0x00,// Register Address 0xF5 
	0x00,// Register Address 0xF6 
	0x00,// Register Address 0xF7 
	0x00,// Register Address 0xF8 
	0x00,// Register Address 0xF9 
	0x00,// Register Address 0xFA 
	0x00,// Register Address 0xFB 
	0x00,// Register Address 0xFC 
	0x00,// Register Address 0xFD 
	0x00,// Register Address 0xFE 
	0x00,// Register Address 0xFF 
	0x00,// Register Address 0x100
	0x00,// Register Address 0x101
	0x00,// Register Address 0x102
	0x00,// Register Address 0x103
	0x00,// Register Address 0x104
	0x00,// Register Address 0x105
	0x00,// Register Address 0x106
	0x00,// Register Address 0x107
	0x00,// Register Address 0x108
	0x00,// Register Address 0x109
	0x00,// Register Address 0x10A
	0x00,// Register Address 0x10B
	0x00,// Register Address 0x10C
	0x00,// Register Address 0x10D
	0x00,// Register Address 0x10E
	0x00,// Register Address 0x10F
	0x00,// Register Address 0x110
	0x00,// Register Address 0x111
	0x00,// Register Address 0x112
	0x00,// Register Address 0x113
	0x00,// Register Address 0x114
	0x00,// Register Address 0x115
	0x00,// Register Address 0x116
	0x00,// Register Address 0x117
	0x00,// Register Address 0x118
	0x00,// Register Address 0x119
	0x00,// Register Address 0x11A
	0x00,// Register Address 0x11B
	0x00,// Register Address 0x11C
	0x00,// Register Address 0x11D
	0x00,// Register Address 0x11E
	0x00,// Register Address 0x11F
	0x00,// Register Address 0x120
	0xFF,// Register Address 0x121
	0x00,// Register Address 0x122
	0x00,// Register Address 0x123
	0xFF,// Register Address 0x124
	0x00,// Register Address 0x125
	0x00,// Register Address 0x126
	0xFF,// Register Address 0x127
	0x00,// Register Address 0x128
	0x00,// Register Address 0x129
	0xFF,// Register Address 0x12A
	0x00,// Register Address 0x12B
	0x00,// Register Address 0x12C
	0xFF,// Register Address 0x12D
	0x00,// Register Address 0x12E
	0x00,// Register Address 0x12F
	0xFF,// Register Address 0x130
	0x00,// Register Address 0x131
	0x00,// Register Address 0x132
	0xFF,// Register Address 0x133
	0x00,// Register Address 0x134
	0x00,// Register Address 0x135
	0x00,// Register Address 0x136
	0x00,// Register Address 0x137
	0x00,// Register Address 0x138
	0x00,// Register Address 0x139
	0x00,// Register Address 0x13A
	0x00,// Register Address 0x13B
	0x00,// Register Address 0x13C
	0x00,// Register Address 0x13D
	0x00,// Register Address 0x13E
	0x00,// Register Address 0x13F
	0x00,// Register Address 0x140
	0x00,// Register Address 0x141
	0x00,// Register Address 0x142
	0x00,// Register Address 0x143
	0x00,// Register Address 0x144
	0x00,// Register Address 0x145
	0x00,// Register Address 0x146
	0x00,// Register Address 0x147
	0x00,// Register Address 0x148
	0x00,// Register Address 0x149
	0x00,// Register Address 0x14A
	0x00,// Register Address 0x14B
	0x00,// Register Address 0x14C
	0x00,// Register Address 0x14D
	0x00,// Register Address 0x14E
	0x00,// Register Address 0x14F
};

const u8 A2B_SlaveNodeDiscovery[2]=
{
	0x94,
	0x94
};

void A2B_IrqCallback(void)
{
	F_IRQ_PIN_REQ=1;
}

void A2B_GpioInit(void)
{
	stc_port_init_t stc_port_init;
	stc_port_pub_set_t stc_port_pub_set;
	stc_exint_config_t stc_exti_config;
	stc_irq_regi_conf_t stc_irq_regi_conf;

/**********************************************************************************/
/*                                                                                                                                                    */
/*                                                 Output                                                                           */
/*                                                                                                                                                    */
/**********************************************************************************/
	FormatMemery((u8 *)(&stc_port_init),sizeof(stc_port_init_t));
	stc_port_init.enPinMode=Pin_Mode_Out;
	stc_port_init.enPinDrv=Pin_Drv_H;	
	
	PORT_Init(GPIO_A2B_MASTER_POWER_CTRL_PORT,GPIO_A2B_MASTER_POWER_CTRL_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_MASTER_POWER_CTRL_PORT,GPIO_A2B_MASTER_POWER_CTRL_PIN,Func_Gpio,Disable);

	PORT_Init(GPIO_A2B_MASTE_RESET_PORT,GPIO_A2B_MASTE_RESET_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_MASTE_RESET_PORT,GPIO_A2B_MASTE_RESET_PIN,Func_Gpio,Disable);

	PORT_Init(GPIO_A2B_SLAVE_POWER_CTRL_PORT,GPIO_A2B_SLAVE_POWER_CTRL_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_POWER_CTRL_PORT,GPIO_A2B_SLAVE_POWER_CTRL_PIN,Func_Gpio,Disable);	

	PORT_Init(GPIO_A2B_SLAVE_AMP_PD_PORT,GPIO_A2B_SLAVE_AMP_PD_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_AMP_PD_PORT,GPIO_A2B_SLAVE_AMP_PD_PIN,Func_Gpio,Disable);	

	PORT_Init(GPIO_A2B_SLAVE_AMP_MUTE_PORT,GPIO_A2B_SLAVE_AMP_MUTE_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_AMP_MUTE_PORT,GPIO_A2B_SLAVE_AMP_MUTE_PIN,Func_Gpio,Disable);

	PORT_Init(GPIO_A2B_SLAVE_AMP_STBY_PORT,GPIO_A2B_SLAVE_AMP_STBY_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_AMP_STBY_PORT,GPIO_A2B_SLAVE_AMP_STBY_PIN,Func_Gpio,Disable);

/**********************************************************************************/
/*																																					  */
/*													Input																			   */
/*																																					  */
/**********************************************************************************/

	FormatMemery((u8 *)(&stc_port_pub_set),sizeof(stc_port_pub_set_t));
	FormatMemery((u8 *)(&stc_port_init),sizeof(stc_port_init_t));
	stc_port_pub_set.enReadWait=WaitCycle3;
	stc_port_init.enPinMode=Pin_Mode_In;

	PORT_PubSetting(&stc_port_pub_set);

	PORT_Init(GPIO_A2B_SLAVE_AMP_FAULT_PORT,GPIO_A2B_SLAVE_AMP_FAULT_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_AMP_FAULT_PORT,GPIO_A2B_SLAVE_AMP_FAULT_PIN,Func_Gpio,Disable);

	PORT_Init(GPIO_A2B_SLAVE_AMP_WARNNING_PORT,GPIO_A2B_SLAVE_AMP_WARNNING_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_AMP_WARNNING_PORT,GPIO_A2B_SLAVE_AMP_WARNNING_PIN,Func_Gpio,Disable);

	/**********************************************************************************/
	/*																																					  */
	/*												Interrupt																			   */
	/*																																					  */
	/**********************************************************************************/

	FormatMemery((u8 *)(&stc_port_init),sizeof(stc_port_init_t));
	FormatMemery((u8 *)(&stc_exti_config),sizeof(stc_exint_config_t));
	FormatMemery((u8 *)(&stc_irq_regi_conf),sizeof(stc_irq_regi_conf_t));	

	stc_port_init.enPinMode=Pin_Mode_In;
	stc_port_init.enExInt=Enable;
	PORT_Init(GPIO_A2B_MASTER_IRQ_PORT,GPIO_A2B_MASTER_IRQ_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_MASTER_IRQ_PORT,GPIO_A2B_MASTER_IRQ_PIN,Func_Gpio,Disable);

	stc_exti_config.enFilterEn=Disable;
	stc_exti_config.enExtiLvl=ExIntRisingEdge;
	stc_exti_config.enExitCh=A2B_IRQ_PIN_EXINT;
	EXINT_Init(&stc_exti_config);

	stc_irq_regi_conf.enIntSrc=A2B_IRQ_PIN_INT_SRC;
	stc_irq_regi_conf.enIRQn=A2B_IRQ_PIN_IRQn;
	stc_irq_regi_conf.pfnCallback=&A2B_IrqCallback;
	enIrqRegistration(&stc_irq_regi_conf);

	NVIC_ClearPendingIRQ(stc_irq_regi_conf.enIRQn);
	NVIC_SetPriority(stc_irq_regi_conf.enIRQn,DDL_IRQ_PRIORITY_DEFAULT);
	NVIC_EnableIRQ(stc_irq_regi_conf.enIRQn);		
}

void A2B_GpioReset(void)
{
	stc_port_init_t stc_port_init;
	stc_port_pub_set_t stc_port_pub_set;

	FormatMemery((u8 *)(&stc_port_pub_set),sizeof(stc_port_pub_set_t));
	FormatMemery((u8 *)(&stc_port_init),sizeof(stc_port_init_t));
	stc_port_pub_set.enReadWait=WaitCycle3;
	stc_port_init.enPinMode=Pin_Mode_In;

	PORT_PubSetting(&stc_port_pub_set);
	
	PORT_Init(GPIO_A2B_MASTER_POWER_CTRL_PORT,GPIO_A2B_MASTER_POWER_CTRL_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_MASTER_POWER_CTRL_PORT,GPIO_A2B_MASTER_POWER_CTRL_PIN,Func_Gpio,Disable);

	PORT_Init(GPIO_A2B_MASTE_RESET_PORT,GPIO_A2B_MASTE_RESET_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_MASTE_RESET_PORT,GPIO_A2B_MASTE_RESET_PIN,Func_Gpio,Disable);

	PORT_Init(GPIO_A2B_SLAVE_POWER_CTRL_PORT,GPIO_A2B_SLAVE_POWER_CTRL_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_POWER_CTRL_PORT,GPIO_A2B_SLAVE_POWER_CTRL_PIN,Func_Gpio,Disable);	

	PORT_Init(GPIO_A2B_SLAVE_AMP_PD_PORT,GPIO_A2B_SLAVE_AMP_PD_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_AMP_PD_PORT,GPIO_A2B_SLAVE_AMP_PD_PIN,Func_Gpio,Disable);	

	PORT_Init(GPIO_A2B_SLAVE_AMP_MUTE_PORT,GPIO_A2B_SLAVE_AMP_MUTE_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_AMP_MUTE_PORT,GPIO_A2B_SLAVE_AMP_MUTE_PIN,Func_Gpio,Disable);

	PORT_Init(GPIO_A2B_SLAVE_AMP_STBY_PORT,GPIO_A2B_SLAVE_AMP_STBY_PIN,&stc_port_init);
	PORT_SetFunc(GPIO_A2B_SLAVE_AMP_STBY_PORT,GPIO_A2B_SLAVE_AMP_STBY_PIN,Func_Gpio,Disable);	
}

void A2B_I2cInit(void)
{
}

u8 A2B_I2C_WaitACK(void)
{
	u8 result =1;
	
	SCL_L;                 
	GPIO_I2Cwait();
	SDA_H;
	GPIO_I2Cwait();
	SCL_H;
	// i2c clock stretching	
	for(;;)
	{
		if(SCL_READ)
		{
			break;
		}
	}	
	GPIO_I2Cwait();
	if(SDA_READ)
	{
		result=0;
	}
	SCL_L;
	GPIO_I2Cwait();
	
	return result;
}

void A2B_I2C_ACK(void)
{        
	SCL_L;
    GPIO_I2Cwait();
    SDA_L;
    GPIO_I2Cwait();
    SCL_H;
	// i2c clock stretching	
	for(;;)
	{
		if(SCL_READ)
		{
			break;
		}
	}	
    GPIO_I2Cwait();
    SCL_L;
    GPIO_I2Cwait();
	SDA_H;	
}

void A2B_I2C_NACK(void)
{        
	SCL_L;
	GPIO_I2Cwait();
	SDA_H;
	GPIO_I2Cwait();
	SCL_H;
	// i2c clock stretching	
	for(;;)
	{
		if(SCL_READ)
		{
			break;
		}
	}	
	GPIO_I2Cwait();
	SCL_L;
	GPIO_I2Cwait();
}

void A2B_I2C_WriteRegAddr(u8 device_addr,u8 reg_addr)
{
	// start
	GPIO_I2C_Start();
	// w device_addr
	GPIO_I2C_SendByte(device_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// w reg_addr
	GPIO_I2C_SendByte(reg_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// stop
	GPIO_I2C_Stop();
}

void A2B_I2C_SingleWrite(u8 device_addr,u8 reg_addr,u8 reg_value)
{
	// start
	GPIO_I2C_Start();
	// w device_addr
	GPIO_I2C_SendByte(device_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// w reg_addr
	GPIO_I2C_SendByte(reg_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// w reg_value
	GPIO_I2C_SendByte(reg_value);
	// wait ack
	A2B_I2C_WaitACK();
	// stop
	GPIO_I2C_Stop();
}

u8 A2B_I2C_SingleRead(u8 device_addr,u8 reg_addr)
{	
	u8 value;
	// start
	GPIO_I2C_Start();
	// w device_addr
	GPIO_I2C_SendByte(device_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// w reg_addr
	GPIO_I2C_SendByte(reg_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// start
	GPIO_I2C_Start();
	// w (device_addr|0x01)
	GPIO_I2C_SendByte(device_addr|0x01);
	// wait ack
	A2B_I2C_WaitACK();
	// r 1 byte
	value=GPIO_I2C_ReceiveByte();
	// nack
	A2B_I2C_NACK();
	// stop	
	GPIO_I2C_Stop();

	return value;
}

u8 A2B_I2C_SingleReadDirect(u8 device_addr)
{	
	u8 value;
	// start
	GPIO_I2C_Start();
	// w (device_addr|0x01)
	GPIO_I2C_SendByte(device_addr|0x01);
	// wait ack
	A2B_I2C_WaitACK();
	// r 1 byte
	value=GPIO_I2C_ReceiveByte();
	// nack
	A2B_I2C_NACK();
	// stop	
	GPIO_I2C_Stop();

	return value;
}

void A2B_I2C_BurstWrite(u8 device_addr,u8 start_reg_addr,u8 length,u8 *reg_value)
{	
	u8 i;
	
	// start
	GPIO_I2C_Start();
	// w device_addr
	GPIO_I2C_SendByte(device_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// w reg_addr
	GPIO_I2C_SendByte(start_reg_addr);
	// wait ack
	A2B_I2C_WaitACK();
	
	for(i=0;i<length;i++)
	{
		// w reg_value
		GPIO_I2C_SendByte(reg_value[i]);
		// wait ack
		A2B_I2C_WaitACK();
	}
	GPIO_I2C_Stop();
}

void A2B_I2C_BurstRead(u8 device_addr,u8 start_reg_addr,u8 length,u8 *reg_value)
{
	u8 i;
	
	// start
	GPIO_I2C_Start();
	// w device_addr
	GPIO_I2C_SendByte(device_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// w reg_addr
	GPIO_I2C_SendByte(start_reg_addr);
	// wait ack
	A2B_I2C_WaitACK();
	// start
	GPIO_I2C_Start();
	// w (device_addr|0x01)
	GPIO_I2C_SendByte(device_addr|0x01);
	// wait ack
	A2B_I2C_WaitACK();

	for(i=0;i<length;i++)
	{
		// 	r 1 byte
		reg_value[i]=GPIO_I2C_ReceiveByte();

		// 	ack/nack
		if(i==(length-1))
		{
			A2B_I2C_NACK();
		}
		else
		{
			A2B_I2C_ACK();
		}
	}
	// stop	
	GPIO_I2C_Stop();	
}

void A2B_I2C_BurstReadDirect(u8 device_addr,u8 length,u8 *reg_value)
{	
	u8 i;
	
	// start
	GPIO_I2C_Start();
	// w (device_addr|0x01)
	GPIO_I2C_SendByte(device_addr|0x01);
	// wait ack
	A2B_I2C_WaitACK();
	
	for(i=0;i<length;i++)
	{
		// 	r 1 byte
		reg_value[i]=GPIO_I2C_ReceiveByte();

		// 	ack/nack
		if(i==(length-1))
		{
			A2B_I2C_NACK();
		}
		else
		{
			A2B_I2C_ACK();
		}
	}
	// stop	
	GPIO_I2C_Stop();
}

void A2B_I2C_SingleWriteMaterNode(u16 reg_addr,u8 reg_value)
{
	if(reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_MMRPAGE,0x01);
	}
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,(u8)(reg_addr&0xFF),reg_value);
	if(reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_MMRPAGE,0x00);
	}	
}

u8 A2B_I2C_SingleReadMaterNode(u16 reg_addr)
{
	u8 value;
	
	if(reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_MMRPAGE,0x01);
	}
	value=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BASE_ADDR,(u8)(reg_addr&0xFF));
	if(reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_MMRPAGE,0x00);
	}	
	return value;
}

void A2B_I2C_BurstWriteMaterNode(u16 start_reg_addr,u8 length,u8 *reg_value)
{
	if(start_reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_MMRPAGE,0x01);
	}
	A2B_I2C_BurstWrite(A2B_I2C_DERVICE_BASE_ADDR,(u8)(start_reg_addr&0xFF),length,reg_value);
	if(start_reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_MMRPAGE,0x00);
	}
}

void A2B_I2C_BurstReadMaterNode(u16 start_reg_addr,u8 length,u8 *reg_value)
{
	if(start_reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_MMRPAGE,0x01);
	}
	A2B_I2C_BurstRead(A2B_I2C_DERVICE_BASE_ADDR,(u8)(start_reg_addr&0xFF),length,reg_value);
	if(start_reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_MMRPAGE,0x00);
	}
}

void A2B_I2C_SingleWriteSlaveNode(u8 node_index,u16 reg_addr,u8 reg_value,u8 f_broadcast)
{
	u8 node_adr;

	node_adr=(node_index&0x0F);
	if(f_broadcast)
	{
		node_adr|=0x80;
	}
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	if(reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_MMRPAGE,0x01);
	}
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,(u8)(reg_addr&0xFF),reg_value);
	if(reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_MMRPAGE,0x00);
	}	
}

u8 A2B_I2C_SingleReadSlaveNode(u8 node_index,u16 reg_addr)
{
	u8 value;
	u8 node_adr;

	node_adr=(node_index&0x0F);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	if(reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_MMRPAGE,0x01);
	}
	value=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,(u8)(reg_addr&0xFF));
	if(reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_MMRPAGE,0x00);
	}	
	return value;
}

void A2B_I2C_BurstWriteSlaveNode(u8 node_index,u16 start_reg_addr,u8 length,u8 *reg_value,u8 f_broadcast)
{
	u8 node_adr;

	node_adr=(node_index&0x0F);
	if(f_broadcast)
	{
		node_adr|=0x80;
	}
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	if(start_reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_MMRPAGE,0x01);
	}
	A2B_I2C_BurstWrite(A2B_I2C_DERVICE_BUS_ADDR,(u8)(start_reg_addr&0xFF),length,reg_value);
	if(start_reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_MMRPAGE,0x00);
	}
}

void A2B_I2C_BurstReadSlaveNode(u8 node_index,u16 start_reg_addr,u8 length,u8 *reg_value)
{
	u8 node_adr;

	node_adr=(node_index&0x0F);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	if(start_reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_MMRPAGE,0x01);
	}	
	A2B_I2C_BurstRead(A2B_I2C_DERVICE_BUS_ADDR,(u8)(start_reg_addr&0xFF),length,reg_value);
	if(start_reg_addr&0x100)
	{
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_MMRPAGE,0x00);
	}	
}

void A2B_I2C_SingleWriteRemoteDevice(u8 node_index,u8 remote_device_addr,u8 reg_addr,u8 reg_value)
{
	u8 node_adr;

	node_adr=(node_index&0x0F);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_CHIP,remote_device_addr);
	node_adr|=0x20;
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,reg_addr,reg_value);
}

u8 A2B_I2C_SingleReadRemoteDevice(u8 node_index,u8 remote_device_addr,u8 reg_addr)
{	
	u8 value;
	u8 node_adr;
	
	node_adr=(node_index&0x0F);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_CHIP,remote_device_addr);
	node_adr|=0x20;
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_WriteRegAddr(A2B_I2C_DERVICE_BUS_ADDR,reg_addr);
	value=A2B_I2C_SingleReadDirect(A2B_I2C_DERVICE_BUS_ADDR);
	return value;
}

u8 A2B_I2C_SingleReadRemoteDeviceRepeated(u8 node_index,u8 remote_device_addr,u8 reg_addr)
{
	u8 value;
	u8 node_adr;
	
	node_adr=(node_index&0x0F);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_CHIP,remote_device_addr);
	node_adr|=0x20;
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	value=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,reg_addr);
	return value;
}

void A2B_I2C_BurstWriteRemoteDevice(u8 node_index,u8 remote_device_addr,u8 length,u8 start_reg_addr,u8 *reg_value)
{
	u8 node_adr;

	node_adr=(node_index&0x0F);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_CHIP,remote_device_addr);
	node_adr|=0x20;
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_BurstWrite(A2B_I2C_DERVICE_BUS_ADDR,start_reg_addr,length,reg_value);
}

void A2B_I2C_BurstReadRemoteDevice(u8 node_index,u8 remote_device_addr,u8 length,u8 start_reg_addr,u8 *reg_value)
{
	u8 node_adr;
	
	node_adr=(node_index&0x0F);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_CHIP,remote_device_addr);
	node_adr|=0x20;
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_WriteRegAddr(A2B_I2C_DERVICE_BUS_ADDR,start_reg_addr);
	A2B_I2C_BurstReadDirect(A2B_I2C_DERVICE_BUS_ADDR,length,reg_value);
}

void A2B_I2C_BurstReadRemoteDeviceRepeated(u8 node_index,u8 remote_device_addr,u8 length,u8 start_reg_addr,u8 *reg_value)
{
	u8 node_adr;
	
	node_adr=(node_index&0x0F);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_CHIP,remote_device_addr);
	node_adr|=0x20;
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
	A2B_I2C_BurstRead(A2B_I2C_DERVICE_BUS_ADDR,start_reg_addr,length,reg_value);
}

void A2B_DiscoveryStart(void)
{
	u32 i;
	
	FormatMemery((u8 *)&A2B_ProData,sizeof(A2B_ProData));

#if A2B_SLAVE_ADI_AMP_BOARD==1
	ADI_AMP_NodeListInit();
	for(i=0;i<ADI_AMP_NodeList.node_num&&A2B_ProData.node_list.node_num<MAX_A2B_SLAVE_NODE_NUM;i++)
	{
		if(ADI_AMP_NodeList.list[i].node_index!=0xFF)
		{
			A2B_ProData.node_list.list[ADI_AMP_NodeList.list[i].node_index]=ADI_AMP_NodeList.list[i];
			A2B_ProData.node_list.node_num++;
		}
	}
#endif
#if A2B_SLAVE_ADI_AD2428WB_BOARD==1
	ADI_AD2428WB_NodeListInit();
	for(i=0;i<ADI_AD2428WB_NodeList.node_num&&A2B_ProData.node_list.node_num<MAX_A2B_SLAVE_NODE_NUM;i++)
	{
		if(ADI_AD2428WB_NodeList.list[i].node_index!=0xFF)
		{
			A2B_ProData.node_list.list[ADI_AD2428WB_NodeList.list[i].node_index]=ADI_AD2428WB_NodeList.list[i];
			A2B_ProData.node_list.node_num++;
		}
	}
#endif
	
	for(i=0;i<MAX_A2B_REGISTER_NUM;i++)
	{
		A2B_ProData.register_value[i]=AD2433_DefaultRegValue[i];
	}
	A2B_ProData.discovery_data.state=A2B_DISC_POWER_OFF;
}

#if A2B_DISCOVERY_FLOW_MODE==A2B_SIMPLE_DISCOVERY_FLOW
void A2B_DiscoveryPro(void)
{
	if(A2B_ProData.discovery_data.timer)
	{
		A2B_ProData.discovery_data.timer--;
	}

	switch(A2B_ProData.discovery_data.state)
	{
		case A2B_DISC_IDLE:
			break;
		case A2B_DISC_POWER_OFF:
			A2B_I2cInit();
			A2B_GpioInit();
			A2B_MASTER_POWER_OFF;
			A2B_MASTER_RESET_ON;
			A2B_ProData.discovery_data.state=A2B_DISC_POWER_ON;
			A2B_ProData.discovery_data.timer=T10S_10;					
			break;
		case A2B_DISC_POWER_ON:
			if(A2B_ProData.discovery_data.timer)
			{
				break;
			}	
			A2B_MASTER_POWER_ON;
			A2B_ProData.discovery_data.state=A2B_DISC_RESET_OFF;
			A2B_ProData.discovery_data.timer=T10S_10;			
			break;
		case A2B_DISC_RESET_OFF:
			if(A2B_ProData.discovery_data.timer)
			{
				break;
			}
			A2B_MASTER_RESET_OFF;
			A2B_ProData.discovery_data.state=A2B_DISC_SOFT_RESET;
			A2B_ProData.discovery_data.timer=T100MS_10;	
			break;
		case A2B_DISC_SOFT_RESET:
			if(A2B_ProData.discovery_data.timer)
			{
				break;
			}			
			{
				u8 reg_value;

				reg_value=A2B_ProData.register_value[AD2433_REG_CONTROL];
				reg_value|=0x04;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_CONTROL,reg_value);
				A2B_ProData.discovery_data.state=A2B_DISC_CFG_NODE_TO_MASTER;
			}
			break;
		case A2B_DISC_CFG_NODE_TO_MASTER:
			{
				u8 reg_value;

				A2B_ProData.vendor=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_VENDOR);
				A2B_ProData.product=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_PRODUCT);
				A2B_ProData.version=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_VERSION);

				// For the master node, the A2B_I2SGCFG register must be programmed before discovery 
				// and not be modified afte discovery
				reg_value=0x20;
				reg_value&=A2B_I2S_SYCN_INV_CFG_MASK;
				reg_value|=A2B_I2S_SYCN_INV_CFG;
				A2B_ProData.register_value[AD2433_REG_I2SGCFG]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_I2SGCFG,reg_value);

				reg_value=A2B_ProData.register_value[AD2433_REG_CONTROL];
				reg_value|=0x80;
				A2B_ProData.register_value[AD2433_REG_CONTROL]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_CONTROL,reg_value);
				
				A2B_ProData.discovery_data.state=A2B_DISC_WAIT_PLL_LOCKED;
				A2B_ProData.discovery_data.timer=T6S_10;		
			}
			break;
		case A2B_DISC_WAIT_PLL_LOCKED:	
			if(F_IRQ_PIN_REQ)
			{
				u8 interrupt_type;
				
				F_IRQ_PIN_REQ=0;
				
				interrupt_type=A2B_I2C_SingleReadMaterNode(AD2433_REG_INTTYPE);
				printf("A2B interrupt type:%x\r\n",interrupt_type);
				if(interrupt_type==AD2433_INT_PLL_LOCKED)
				{
					u8 reg_value;
					
					A2B_ProData.register_value[AD2433_REG_RESPCYCS]=A2B_SlaveNodeDiscovery[0];
					A2B_I2C_SingleWriteMaterNode(AD2433_REG_RESPCYCS,A2B_ProData.register_value[AD2433_REG_RESPCYCS]);
					
					reg_value=A2B_ProData.register_value[AD2433_REG_CONTROL];
					reg_value|=0x01;
					A2B_I2C_SingleWriteMaterNode(AD2433_REG_CONTROL,reg_value);
					
					A2B_ProData.register_value[AD2433_REG_INTMSK0]=A2B_INTERRUPT_MASK_0;
					A2B_ProData.register_value[AD2433_REG_INTMSK1]=A2B_INTERRUPT_MASK_1;
					A2B_ProData.register_value[AD2433_REG_INTMSK2]=A2B_INTERRUPT_MASK_2;
					A2B_I2C_BurstWriteMaterNode(AD2433_REG_INTMSK0,3,&A2B_ProData.register_value[AD2433_REG_INTMSK0]);
					
					reg_value=A2B_ProData.register_value[AD2433_REG_CONTROL];
					reg_value&=A2B_XCVRBINV_CFG_MASK;
					reg_value|=A2B_XCVRBINV_CFG;
					A2B_ProData.register_value[AD2433_REG_CONTROL]=reg_value;
					A2B_I2C_SingleWriteMaterNode(AD2433_REG_CONTROL,reg_value);
					A2B_ProData.discovery_data.state=A2B_DISC_CHECK_HPSW_CFG;
					A2B_ProData.discovery_data.timer=0;
				}
			}
			else if(A2B_ProData.discovery_data.timer==0)
			{
				A2B_ProData.discovery_data.state=A2B_DISC_POWER_OFF;
			}
			break;
		case A2B_DISC_CHECK_HPSW_CFG:
			if(A2B_ProData.discovery_data.timer)
			{
				break;
			}			
			{
				u8 reg_value;
				
				reg_value=A2B_I2C_SingleReadMaterNode(AD2433_REG_SWSTAT2);
				reg_value&=0x38;
				reg_value>>=3;
				if(reg_value==A2B_HIGH_POWER_SWITCH_CFG)
				{
					A2B_ProData.discovery_data.state=A2B_DISC_START_FIND_FIRST_NODE;
					A2B_ProData.discovery_data.node_counter=0;
					A2B_ProData.node_num=0;
				}
				else
				{
					A2B_ProData.discovery_data.state=A2B_DISC_SET_HPSW_CFG;
				}
			}
			break;
		case A2B_DISC_SET_HPSW_CFG:
			{
				u8 reg_value;

				reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL2];
				reg_value&=A2B_HPSW_CFG_MASK;
				reg_value|=A2B_HIGH_POWER_SWITCH_CFG;
				A2B_ProData.register_value[AD2433_REG_SWCTL2]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL2,reg_value);

				reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL];
				reg_value|=0x02;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,reg_value);

				A2B_ProData.discovery_data.state=A2B_DISC_CHECK_HPSW_CFG;
				A2B_ProData.discovery_data.timer=T100MS_10;
			}
			break;
		case A2B_DISC_START_FIND_FIRST_NODE:
			{
				u8 reg_value;
#if 0
#if A2B_HIGH_POWER_SWITCH_CFG==A2B_HPSW_CFG_MODE_0
				reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL];
				reg_value|=0x01;
				A2B_ProData.register_value[AD2433_REG_SWCTL]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,reg_value);
#elif A2B_HIGH_POWER_SWITCH_CFG==A2B_HPSW_CFG_MODE_4
				A2B_ProData.register_value[AD2433_REG_SWCTL5]=0x01;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL5,A2B_ProData.register_value[AD2433_REG_SWCTL5]);

				reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL];
				reg_value|=0x11;
				A2B_ProData.register_value[AD2433_REG_SWCTL]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,reg_value);				
#endif
#else
				reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL];
				reg_value|=0x01;
				A2B_ProData.register_value[AD2433_REG_SWCTL]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,reg_value);
#endif
				A2B_ProData.register_value[AD2433_REG_DISCVRY]=A2B_SlaveNodeDiscovery[A2B_ProData.discovery_data.node_counter];
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_DISCVRY,A2B_ProData.register_value[AD2433_REG_DISCVRY]);

				A2B_ProData.discovery_data.state=A2B_DISC_WAIT_FIRST_NODE;
				A2B_ProData.discovery_data.timer=T10S_10;
			}
			break;
		case A2B_DISC_WAIT_FIRST_NODE:	
			if(F_IRQ_PIN_REQ)
			{
				u8 interrupt_type;
				u8 intpend2;
				
				F_IRQ_PIN_REQ=0;
				
				interrupt_type=A2B_I2C_SingleReadMaterNode(AD2433_REG_INTTYPE);
				printf("A2B interrupt type:%x\r\n",interrupt_type);
				intpend2=A2B_I2C_SingleReadMaterNode(AD2433_REG_INTPND2);
				if(interrupt_type==AD2433_INT_DSCDONE
					||(intpend2&0x01))
				{
					A2B_ProData.discovery_data.state=A2B_DISC_FIRST_SET_EXT_SWITCS_MODE;
				}
			}
			else if(A2B_ProData.discovery_data.timer==0)
			{
				A2B_ProData.swstat=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_SWSTAT);
				A2B_ProData.swstat2=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_SWSTAT2);
				A2B_ProData.discstat=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_DISCSTAT);				
				A2B_ProData.discovery_data.state=A2B_DISC_ERROR;			
			}
			break;
		case A2B_DISC_FIRST_SET_EXT_SWITCS_MODE:
			{
				u8 reg_value;
#if 0				
#if A2B_HIGH_POWER_SWITCH_CFG==A2B_HPSW_CFG_MODE_0				
				reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL];
				reg_value|=0x20;
				A2B_ProData.register_value[AD2433_REG_SWCTL]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,reg_value);
#elif A2B_HIGH_POWER_SWITCH_CFG==A2B_HPSW_CFG_MODE_4
				reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL];
				reg_value&=0xEF;
				reg_value|=0x20;
				A2B_ProData.register_value[AD2433_REG_SWCTL]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,reg_value);
#endif
#else
				reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL];
				reg_value|=0x20;
				A2B_ProData.register_value[AD2433_REG_SWCTL]=reg_value;
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,reg_value);
#endif
				A2B_ProData.node_num=1;

				A2B_ProData.discovery_data.state=A2B_DISC_GET_NODE_INFO;
			}
			break;
		case A2B_DISC_OTHER_CFG_SLAVE_NODE:
			{
#if 0
				u8 reg_value[3];

				reg_value[0]=A2B_INTERRUPT_MASK_0;
				reg_value[1]=A2B_INTERRUPT_MASK_1;
				reg_value[2]=A2B_INTERRUPT_MASK_2;	
				A2B_I2C_BurstWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_INTMSK0,3,reg_value,0);

				reg_value[0]=AD2433_DefaultRegValue[AD2433_REG_CONTROL];
				reg_value[0]&=A2B_XCVRBINV_CFG_MASK;
				reg_value[0]|=A2B_XCVRBINV_CFG;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_CONTROL,reg_value[0],0);
				A2B_ProData.discovery_data.state=A2B_DISC_OTHER_CHECK_HPSW_CFG;
#else
				u8 reg_value[2];

				reg_value[0]=A2B_INTERRUPT_MASK_0;
				reg_value[1]=A2B_INTERRUPT_MASK_1;
				A2B_I2C_BurstWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_INTMSK0,2,reg_value,0);

				reg_value[0]=AD2433_DefaultRegValue[AD2433_REG_CONTROL];
				reg_value[0]&=A2B_XCVRBINV_CFG_MASK;
				reg_value[0]|=A2B_XCVRBINV_CFG;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_CONTROL,reg_value[0],0);

				A2B_ProData.discovery_data.state=A2B_DISC_START_FIND_OTHER_NODE;
#endif
		}
			break;
		case A2B_DISC_OTHER_CHECK_HPSW_CFG:
			if(A2B_ProData.discovery_data.timer)
			{
				break;
			}			
			{
				u8 reg_value;
				
				reg_value=A2B_I2C_SingleReadSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWSTAT2);
				reg_value&=0x38;
				reg_value>>=3;
				if(reg_value==A2B_HIGH_POWER_SWITCH_CFG)
				{
					A2B_ProData.discovery_data.state=A2B_DISC_START_FIND_OTHER_NODE;
				}
				else
				{
					A2B_ProData.discovery_data.state=A2B_DISC_OTHER_SET_HPSW_CFG;
				}
			}			
			break;
		case A2B_DISC_OTHER_SET_HPSW_CFG:
			{
				u8 reg_value;

				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL2];
				reg_value&=A2B_HPSW_CFG_MASK;
				reg_value|=A2B_HIGH_POWER_SWITCH_CFG;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL2,reg_value,0);

				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
				reg_value|=0x02;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);

				A2B_ProData.discovery_data.state=A2B_DISC_OTHER_CHECK_HPSW_CFG;
				A2B_ProData.discovery_data.timer=T100MS_10;
			}			
			break;
		case A2B_DISC_START_FIND_OTHER_NODE:
			{
				u8 reg_value;
#if 0				
#if A2B_HIGH_POWER_SWITCH_CFG==A2B_HPSW_CFG_MODE_0				
				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
				reg_value|=0x01;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);
#elif A2B_HIGH_POWER_SWITCH_CFG==A2B_HPSW_CFG_MODE_4
				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL5];
				reg_value|=0x01;	
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL5,reg_value,0);

				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
				reg_value|=0x11;	
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);				
#endif
#else
				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
				reg_value|=0x01;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);
#endif
				A2B_ProData.register_value[AD2433_REG_DISCVRY]=A2B_SlaveNodeDiscovery[A2B_ProData.discovery_data.node_counter+1];
				A2B_I2C_SingleWriteMaterNode(AD2433_REG_DISCVRY,A2B_ProData.register_value[AD2433_REG_DISCVRY]);

				A2B_ProData.discovery_data.state=A2B_DISC_WAIT_OTHER_NODE;
				A2B_ProData.discovery_data.timer=T100MS_10;				
			}
			break;
		case A2B_DISC_WAIT_OTHER_NODE:
			if(F_IRQ_PIN_REQ)
			{
				u8 interrupt_type;
				
				F_IRQ_PIN_REQ=0;
				
				interrupt_type=A2B_I2C_SingleReadMaterNode(AD2433_REG_INTTYPE);
				if(interrupt_type==AD2433_INT_DSCDONE)
				{
					A2B_ProData.discovery_data.state=A2B_DISC_OTHER_SET_EXT_SWITCS_MODE;
				}
			}
			else if(A2B_ProData.discovery_data.timer==0)
			{
				A2B_ProData.discovery_data.state=A2B_DISC_ERROR;
			}			
			break;
		case A2B_DISC_OTHER_SET_EXT_SWITCS_MODE:
			{
				u8 reg_value;
#if 0				
#if A2B_HIGH_POWER_SWITCH_CFG==A2B_HPSW_CFG_MODE_0					
				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
				reg_value|=0x21;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);
#elif A2B_HIGH_POWER_SWITCH_CFG==A2B_HPSW_CFG_MODE_4
				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
				reg_value|=0x21;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);
#endif
#else
				reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
				reg_value|=0x21;
				A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);
#endif
				A2B_ProData.discovery_data.node_counter++;
				A2B_ProData.node_num++;

				A2B_ProData.discovery_data.state=A2B_DISC_GET_NODE_INFO;			
			}			
			break;
		case A2B_DISC_GET_NODE_INFO:
			{
				u8 node_adr=0;
				SLAVE_NODE_INFO node_info;

				node_adr|=(A2B_ProData.discovery_data.node_counter&0x0F);
				A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,node_adr);
				node_info.vendor=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_VENDOR);
				node_info.product=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_PRODUCT);
				node_info.version=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_VERSION);
				if(node_info.vendor==A2B_ProData.node_list.list[A2B_ProData.discovery_data.node_counter].node_info.vendor
					&&node_info.product==A2B_ProData.node_list.list[A2B_ProData.discovery_data.node_counter].node_info.product
					&&node_info.version==A2B_ProData.node_list.list[A2B_ProData.discovery_data.node_counter].node_info.version)

				{
					if(A2B_ProData.node_num<A2B_ProData.node_list.node_num)
					{
						A2B_ProData.discovery_data.state=A2B_DISC_OTHER_CFG_SLAVE_NODE;
					}
					else
					{
						A2B_ProData.discovery_data.state=A2B_DISC_INIT_SLAVE_NODE;
					}
				}
				else
				{
					if(A2B_ProData.node_num==1)
					{
						u8 reg_value;

						reg_value=A2B_ProData.register_value[AD2433_REG_SWCTL];
						reg_value&=0xFE;
						A2B_ProData.register_value[AD2433_REG_SWCTL]=reg_value;
						A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,reg_value);	

						reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
						reg_value|=0x20;
						reg_value&=0xFE;
						A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);	

						A2B_ProData.discovery_data.state=A2B_DISC_ERROR;
					}
					else
					{
						u8 reg_value;
						
						A2B_ProData.discovery_data.node_counter--;
						A2B_ProData.node_num--;

						reg_value=AD2433_DefaultRegValue[AD2433_REG_SWCTL];
						reg_value|=0x20;
						reg_value&=0xFE;
						A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,reg_value,0);						
						A2B_ProData.discovery_data.state=A2B_DISC_INIT_SLAVE_NODE;
					}
				}
			}
			break;
		case A2B_DISC_INIT_SLAVE_NODE:
			(*A2B_ProData.node_list.list[A2B_ProData.discovery_data.node_counter].node_int_fun)();
			A2B_ProData.discovery_data.state=A2B_DISC_INIT_SLAVE_DEVICE_START;
			A2B_ProData.discovery_data.device_counter=0;
			break;
		case A2B_DISC_INIT_SLAVE_DEVICE_START:
			(*A2B_ProData.node_list.list[A2B_ProData.discovery_data.node_counter].device_item.ptr[A2B_ProData.discovery_data.device_counter].start_init)();
			A2B_ProData.discovery_data.state=A2B_DISC_INIT_SLAVE_DEVICE_WAIT;
			break;
		case A2B_DISC_INIT_SLAVE_DEVICE_WAIT:
			(*A2B_ProData.node_list.list[A2B_ProData.discovery_data.node_counter].device_item.ptr[A2B_ProData.discovery_data.device_counter].init_pro)();
			if((*A2B_ProData.node_list.list[A2B_ProData.discovery_data.node_counter].device_item.ptr[A2B_ProData.discovery_data.device_counter].is_inti_end)())
			{
				A2B_ProData.discovery_data.device_counter++;
				if(A2B_ProData.discovery_data.device_counter==A2B_ProData.node_list.list[A2B_ProData.discovery_data.node_counter].device_item.device_num)
				{
					if(A2B_ProData.discovery_data.node_counter)
					{	
						A2B_ProData.discovery_data.node_counter--;
						A2B_ProData.discovery_data.state=A2B_DISC_INIT_SLAVE_NODE;
					}
					else
					{
						A2B_ProData.discovery_data.state=A2B_DISC_INIT_SLAVE_CFG_ENSW;
					}
				}
				else
				{
					A2B_ProData.discovery_data.state=A2B_DISC_INIT_SLAVE_DEVICE_START;				
				}
			}
			break;
		case A2B_DISC_INIT_SLAVE_CFG_ENSW:
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_NODEADR,A2B_ProData.discovery_data.node_counter);
			A2B_I2C_SingleWriteSlaveNode(A2B_ProData.discovery_data.node_counter,AD2433_REG_SWCTL,0x01,0);	
			A2B_ProData.discovery_data.state=A2B_DISC_INIT_MASTE_NODE;
			break;
		case A2B_DISC_INIT_MASTE_NODE:
			A2B_ProData.register_value[AD2433_REG_SWCTL]=0x01;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_SWCTL,A2B_ProData.register_value[AD2433_REG_SWCTL]);

			A2B_ProData.register_value[AD2433_REG_DNSLOTS]=0x04;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_DNSLOTS,A2B_ProData.register_value[AD2433_REG_DNSLOTS]);
			
			A2B_ProData.register_value[AD2433_REG_I2SCFG]=0x20;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_I2SCFG,A2B_ProData.register_value[AD2433_REG_I2SCFG]);
			
			A2B_ProData.register_value[AD2433_REG_PINCFG]=0x00;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_PINCFG,A2B_ProData.register_value[AD2433_REG_PINCFG]);

			A2B_ProData.register_value[AD2433_REG_INTMSK0]=0x77;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_INTMSK0,A2B_ProData.register_value[AD2433_REG_INTMSK0]);

			A2B_ProData.register_value[AD2433_REG_INTMSK1]=0x78;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_INTMSK1,A2B_ProData.register_value[AD2433_REG_INTMSK1]);

			A2B_ProData.register_value[AD2433_REG_INTMSK2]=0x0F;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_INTMSK2,A2B_ProData.register_value[AD2433_REG_INTMSK2]);

			A2B_ProData.register_value[AD2433_REG_BECCTL]=0xFF;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_BECCTL,A2B_ProData.register_value[AD2433_REG_BECCTL]);

			A2B_I2C_SingleWriteMaterNode(AD2433_REG_NODEADR,0x00);
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_NODEADR,0x00);
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_NODEADR,0x80);
			A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_PLLCTL,0x00);
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_NODEADR,0x00);			

			A2B_ProData.register_value[AD2433_REG_SLOTFMT]=0x66;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_SLOTFMT,A2B_ProData.register_value[AD2433_REG_SLOTFMT]);

			A2B_ProData.register_value[AD2433_REG_DATCTL]=0x03;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_DATCTL,A2B_ProData.register_value[AD2433_REG_DATCTL]);

			A2B_ProData.register_value[AD2433_REG_CONTROL]=0x81;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_CONTROL,A2B_ProData.register_value[AD2433_REG_CONTROL]);

			A2B_I2C_SingleWriteMaterNode(AD2433_REG_NODEADR,(A2B_ProData.node_num-1));
			A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_SWCTL,0x00);

			A2B_ProData.register_value[AD2433_REG_CONTROL]=0x82;
			A2B_I2C_SingleWriteMaterNode(AD2433_REG_CONTROL,A2B_ProData.register_value[AD2433_REG_CONTROL]);			

			A2B_ProData.discovery_data.state=A2B_DISC_OK;
			break;
		case A2B_DISC_OK:
			break;
		case A2B_DISC_ERROR:
			break;
		default:
			break;
	}
}

#elif A2B_DISCOVERY_FLOW_MODE==A2B_OPTIMIZED_DISCOVERY_FLOW
void A2B_DiscoveryPro(void)
{
}
#endif

#endif

