#include "public.h"
#if A2B_SLAVE_ADI_AMP_BOARD==1
A2B_SLAVE_DEVICE_INIT_STATE ADI_AMP_DeviceInitState[MAX_A2B_SLAVE_NODE_NUM][ADI_AMP_BOARD_DEVICE_NUM];
SSM3582_IC_INFO ADI_AMP_SSM3582_IcInfo[MAX_A2B_SLAVE_NODE_NUM][ADI_AMP_BOARD_DEVICE_NUM];
A2B_SLAVE_NODE_LIST ADI_AMP_NodeList;

void ADI_AMP_0_NodeInit(void);
void ADI_AMP_1_NodeInit(void);
void ADI_AMP_2_NodeInit(void);
void ADI_AMP_3_NodeInit(void);
void ADI_AMP_4_NodeInit(void);
void ADI_AMP_5_NodeInit(void);
void ADI_AMP_6_NodeInit(void);
void ADI_AMP_7_NodeInit(void);
void ADI_AMP_8_NodeInit(void);
void ADI_AMP_9_NodeInit(void);
void ADI_AMP_10_NodeInit(void);
void ADI_AMP_11_NodeInit(void);
void ADI_AMP_12_NodeInit(void);
void ADI_AMP_13_NodeInit(void);
void ADI_AMP_14_NodeInit(void);
void ADI_AMP_15_NodeInit(void);

void ADI_AMP_0_SSM3582_0_StartInit(void);
void ADI_AMP_0_SSM3582_0_InitPro(void);
u8 ADI_AMP_0_SSM3582_0_IsInitEnd(void);

void ADI_AMP_0_SSM3582_1_StartInit(void);
void ADI_AMP_0_SSM3582_1_InitPro(void);
u8 ADI_AMP_0_SSM3582_1_IsInitEnd(void);

const u8 ADI_AMP_NodeIndexTab[MAX_A2B_SLAVE_NODE_NUM]=
{
#if A2B_PATH_TYPE==A2B_PATH_M2AMP
	0x00,
#elif A2B_PATH_TYPE==A2B_PATH_M2AD2428WB2AMP
	0x01,
#elif A2B_PATH_TYPE==A2B_PATH_M2AMP2AD2428WB
	0x00,
#else
	0x00,
#endif
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF
};

#if A2B_PATH_TYPE==A2B_PATH_M2AMP
const u8 ADI_AMP_0_NodeParamTab[][2]=
{
	0x0B,0x80, // REG_A2B_LDNSLOTS
	0x42,0x03, // REG_A2B_I2SCFG
	0x65,0x0F, // REG_A2B_DNMASK0
	0x1B,0x00, // REG_A2B_INTMSK0
	0x1C,0x00, // REG_A2B_INTMSK1
	0x1E,0xFF, // REG_A2B0_BECCTL
	0xFF,0xFF  // END
};
#elif A2B_PATH_TYPE==A2B_PATH_M2AD2428WB2AMP
const u8 ADI_AMP_0_NodeParamTab[][2]=
{
	0x0B,0x80, // REG_A2B_LDNSLOTS
	0x42,0x03, // REG_A2B_I2SCFG
	0x65,0x0F, // REG_A2B_DNMASK0
	0x1B,0x00, // REG_A2B_INTMSK0
	0x1C,0x00, // REG_A2B_INTMSK1
	0x1E,0xFF, // REG_A2B0_BECCTL
	0xFF,0xFF  // END
};
#elif A2B_PATH_TYPE==A2B_PATH_M2AMP2AD2428WB
const u8 ADI_AMP_0_NodeParamTab[][2]=
{
	0x0B,0x80, // REG_A2B_LDNSLOTS
	0x0D,0x02, // REG_A2B_DNSLOTS
	0x42,0x03, // REG_A2B_I2SCFG
	0x60,0x03, // REG_A2B_UPMASK0
	0x65,0x03, // REG_A2B_DNMASK0
	0x1B,0x00, // REG_A2B_INTMSK0
	0x1C,0x00, // REG_A2B_INTMSK1
	0x1E,0xFF, // REG_A2B0_BECCTL
	0xFF,0xFF  // END
};
#else
const u8 ADI_AMP_0_NodeParamTab[][2]=
{
	0x0B,0x80, // REG_A2B_LDNSLOTS
	0x42,0x03, // REG_A2B_I2SCFG
	0x65,0x0F, // REG_A2B_DNMASK0
	0x1B,0x00, // REG_A2B_INTMSK0
	0x1C,0x00, // REG_A2B_INTMSK1
	0x1E,0xFF, // REG_A2B0_BECCTL
	0xFF,0xFF  // END
};
#endif

const u8 ADI_AMP_0_SSM3582_0_ParamTab[][2]=
{
	0x04,0xA0, 
	0x05,0x8B, 
	0x06,0x02, 
	0x07,0x40, 
	0x08,0x40, 
	0x09,0x10,
	0x0A,0x0F,
	0x0B,0x00,
	0x0C,0x01,
	0x0E,0xA0,
	0x0F,0x51,
	0x10,0x22,
	0x11,0xA8,
	0x12,0x51,
	0x13,0x22,
	0x14,0xFF,
	0x15,0xFF,
	0x16,0x00,
	0x17,0x30,
	0x1C,0x00,
	0xFF,0xFF  // END
};

const u8 ADI_AMP_0_SSM3582_1_ParamTab[][2]=
{
	0x04,0xA0, 
	0x05,0x8B, 
	0x06,0x02, 
	0x07,0x40, 
	0x08,0x40, 
	0x09,0x10,
	0x0A,0x0F,
	0x0B,0x00,
	0x0C,0x01,
	0x0E,0xA0,
	0x0F,0x51,
	0x10,0x22,
	0x11,0xA8,
	0x12,0x51,
	0x13,0x22,
	0x14,0xFF,
	0x15,0xFF,
	0x16,0x00,
	0x17,0x30,
	0x1C,0x00,
	0xFF,0xFF  // END
};

const A2B_SLAVE_DEVICE_FUN pADI_AMP_0_DeviceInitTab[ADI_AMP_BOARD_DEVICE_NUM]=
{
	ADI_AMP_0_SSM3582_0_StartInit,ADI_AMP_0_SSM3582_0_InitPro,ADI_AMP_0_SSM3582_0_IsInitEnd,
	ADI_AMP_0_SSM3582_1_StartInit,ADI_AMP_0_SSM3582_1_InitPro,ADI_AMP_0_SSM3582_1_IsInitEnd
};

const pSlaveNodeInitFun pADI_AMP_NodeInitFunTab[MAX_A2B_SLAVE_NODE_NUM]=
{
	ADI_AMP_0_NodeInit,
	ADI_AMP_1_NodeInit,
	ADI_AMP_2_NodeInit,
	ADI_AMP_3_NodeInit,
	ADI_AMP_4_NodeInit,
	ADI_AMP_5_NodeInit,
	ADI_AMP_6_NodeInit,
	ADI_AMP_7_NodeInit,	
	ADI_AMP_8_NodeInit,
	ADI_AMP_9_NodeInit,
	ADI_AMP_10_NodeInit,
	ADI_AMP_11_NodeInit,
	ADI_AMP_12_NodeInit,
	ADI_AMP_13_NodeInit,
	ADI_AMP_14_NodeInit,
	ADI_AMP_15_NodeInit		
};

const A2B_SLAVE_DEVICE_FUN *pADI_AMP_DeviceInitTab[MAX_A2B_SLAVE_NODE_NUM]=
{
	pADI_AMP_0_DeviceInitTab,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,	
	NULL,
	NULL,
	NULL,	
};

void ADI_AMP_NodeListInit(void)
{
	u32 i;

	FormatMemery((u8 *)&ADI_AMP_NodeList,sizeof(ADI_AMP_NodeList));
	
	ADI_AMP_NodeList.node_num=ADI_AMP_BOARD_NUM;
	for(i=0;i<ADI_AMP_BOARD_NUM;i++)
	{
		ADI_AMP_NodeList.list[i].node_index=ADI_AMP_NodeIndexTab[i];
		ADI_AMP_NodeList.list[i].node_int_fun=pADI_AMP_NodeInitFunTab[i];
		ADI_AMP_NodeList.list[i].device_item.device_num=ADI_AMP_BOARD_DEVICE_NUM;
		ADI_AMP_NodeList.list[i].device_item.ptr=(A2B_SLAVE_DEVICE_FUN *)pADI_AMP_DeviceInitTab[i];
		ADI_AMP_NodeList.list[i].node_info.vendor=A2B_AD2428_VENDOR;
		ADI_AMP_NodeList.list[i].node_info.product=A2B_AD2428_PRODUCT;
		ADI_AMP_NodeList.list[i].node_info.version=A2B_AD2428_VERSION;
	}	
}

void ADI_AMP_0_NodeInit(void)
{
	u32 i;
	
	A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,ADI_AMP_NodeIndexTab[0]);
	for(i=0;;i++)
	{
		if(ADI_AMP_0_NodeParamTab[i][0]==0xFF
			&&ADI_AMP_0_NodeParamTab[i][1]==0xFF)
		{
			break;
		}
		A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,(u8)(ADI_AMP_0_NodeParamTab[i][0]&0xFF),ADI_AMP_0_NodeParamTab[i][1]);
	}
}

void ADI_AMP_1_NodeInit(void)
{
}

void ADI_AMP_2_NodeInit(void)
{
}

void ADI_AMP_3_NodeInit(void)
{
}

void ADI_AMP_4_NodeInit(void)
{
}

void ADI_AMP_5_NodeInit(void)
{
}

void ADI_AMP_6_NodeInit(void)
{
}

void ADI_AMP_7_NodeInit(void)
{
}

void ADI_AMP_8_NodeInit(void)
{
}

void ADI_AMP_9_NodeInit(void)
{
}

void ADI_AMP_10_NodeInit(void)
{
}

void ADI_AMP_11_NodeInit(void)
{
}

void ADI_AMP_12_NodeInit(void)
{
}

void ADI_AMP_13_NodeInit(void)
{
}

void ADI_AMP_14_NodeInit(void)
{
}

void ADI_AMP_15_NodeInit(void)
{
}

void ADI_AMP_0_SSM3582_0_StartInit(void)
{
	ADI_AMP_DeviceInitState[0][0]=SLAVE_DEVICE_INIT_START;
}

void ADI_AMP_0_SSM3582_0_InitPro(void)
{
	switch(ADI_AMP_DeviceInitState[0][0])
	{
		case SLAVE_DEVICE_INIT_IDLE:
			break;
		case SLAVE_DEVICE_INIT_START:
			ADI_AMP_DeviceInitState[0][0]=SLAVE_DEVICE_INIT_PRO;
			break;
		case SLAVE_DEVICE_INIT_PRO:
			{
				u32 i;

				A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,ADI_AMP_NodeIndexTab[0]);
				A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_CHIP,0x10);
				A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,(ADI_AMP_NodeIndexTab[0]|0x20));
				ADI_AMP_SSM3582_IcInfo[0][0].vendor=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,0x00);
				ADI_AMP_SSM3582_IcInfo[0][0].device_1=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,0x01);
				ADI_AMP_SSM3582_IcInfo[0][0].device_2=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,0x02);
				ADI_AMP_SSM3582_IcInfo[0][0].revision=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,0x03);
				for(i=0;;i++)
				{
					if(ADI_AMP_0_SSM3582_0_ParamTab[i][0]==0xFF
						&&ADI_AMP_0_SSM3582_0_ParamTab[i][1]==0xFF)
					{
						break;
					}
					A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,ADI_AMP_0_SSM3582_0_ParamTab[i][0],ADI_AMP_0_SSM3582_0_ParamTab[i][1]);
				}
				ADI_AMP_DeviceInitState[0][0]=SLAVE_DEVICE_INIT_END;
			}
			break;
		case SLAVE_DEVICE_INIT_END:
			break;
		default:
			break;
	}
}

u8 ADI_AMP_0_SSM3582_0_IsInitEnd(void)
{
	u8 result=0;

	if(ADI_AMP_DeviceInitState[0][0]==SLAVE_DEVICE_INIT_END)
	{
		result=1;
	}
	return result;
}

void ADI_AMP_0_SSM3582_1_StartInit(void)
{
	ADI_AMP_DeviceInitState[0][1]=SLAVE_DEVICE_INIT_START;
}

void ADI_AMP_0_SSM3582_1_InitPro(void)
{
	switch(ADI_AMP_DeviceInitState[0][1])
	{
		case SLAVE_DEVICE_INIT_IDLE:
			break;
		case SLAVE_DEVICE_INIT_START:
			ADI_AMP_DeviceInitState[0][1]=SLAVE_DEVICE_INIT_PRO;
			break;
		case SLAVE_DEVICE_INIT_PRO:
			{
				u32 i;

				A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,ADI_AMP_NodeIndexTab[0]);
				A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,AD2433_REG_CHIP,0x11);
				A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BASE_ADDR,AD2433_REG_NODEADR,(ADI_AMP_NodeIndexTab[0]|0x20));
				ADI_AMP_SSM3582_IcInfo[0][1].vendor=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,0x00);
				ADI_AMP_SSM3582_IcInfo[0][1].device_1=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,0x01);
				ADI_AMP_SSM3582_IcInfo[0][1].device_2=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,0x02);
				ADI_AMP_SSM3582_IcInfo[0][1].revision=A2B_I2C_SingleRead(A2B_I2C_DERVICE_BUS_ADDR,0x03);
				for(i=0;;i++)
				{
					if(ADI_AMP_0_SSM3582_1_ParamTab[i][0]==0xFF
						&&ADI_AMP_0_SSM3582_1_ParamTab[i][1]==0xFF)
					{
						break;
					}
					A2B_I2C_SingleWrite(A2B_I2C_DERVICE_BUS_ADDR,ADI_AMP_0_SSM3582_1_ParamTab[i][0],ADI_AMP_0_SSM3582_1_ParamTab[i][1]);
				}
				ADI_AMP_DeviceInitState[0][1]=SLAVE_DEVICE_INIT_END;
			}			
			break;
		case SLAVE_DEVICE_INIT_END:
			break;
		default:
			break;
	}

}

u8 ADI_AMP_0_SSM3582_1_IsInitEnd(void)
{
	u8 result=0;

	if(ADI_AMP_DeviceInitState[0][1]==SLAVE_DEVICE_INIT_END)
	{
		result=1;
	}
	return result;

}
#endif

