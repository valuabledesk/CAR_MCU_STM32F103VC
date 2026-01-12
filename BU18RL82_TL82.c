#include "public.h"
#if BU18RL82_FUN==1

BU18TL82_STATE BU18TL82State;
u16 BU18TL82Timer;
u16 Read_TL_Buffer[48][2];
u16 Read_RL_Buffer[35][2];
u8 Read_All_Register_Flag;
u16 CCL_LINK_DATA;
#if MODEL==LINUX_2339WA_93||MODEL==LINUX_N039_DZ||MODEL==LINUX_2349WA_93
const u16 BU18TL82_Register[][2] =
{
   {0x0013,0x1a},  
   {0x0014,0x08},  
   {0x0016,0x00},  //I2C_A on CLL0 
   {0x0017,0x01},  //I2C_B on CLL1
   {0x0021,0x08},  
   {0x0023,0x03}, //09 ; 
   {0x0024,0x09}, // 09 ; 
   {0x0025,0x01},  
   {0x0045,0x00},  
   {0x0046,0x05},  
   {0x004b,0xd0},  
   {0x004c,0x02}, 

   {0x002a,0x18}, //In  BL_PWM
   {0x002d,0x00}, // OUT  CTP_INT
   {0x0030,0x18}, // In  AX5511_EN
   {0x003f,0x18},// In  CTP_RST
   {0x02a7,0x02},//  GPIO0 to RL
   {0x002e,0x03},// GPIO1 from RL
   {0x02a9,0x04},// GPIO2 to RL
   {0x02AE,0x09},//  GPO7 to RL

   {0x0053,0x00},//00
   {0x0054,0xc0},  

   {0x022b,0xf5}, // 78
   {0x022c,0x49},//77
   {0x022d,0x27},//27
   {0x022e,0x80},  
   {0x0018,0x00},  
   {0x0019,0x00},  

   {0x0225,0x00},  //SSCG0 off
   {0x0325,0x00},  //SSCG0 off

   {0x0296,0x06},  
   {0x0297,0x0d},  
   {0x028e,0x03},  
   {0x0274,0x30},  
   {0x0275,0x20},  
   {0x0374,0x30}, 
   {0x0375,0x20}, 
   {0x027C,0x5D},//CTP addr CLL lane0 
   {0x027D,0x70}, // CTP addr CLL lane0


   {0x0109,0x80},
#if MODEL==LINUX_N039_DZ
	 {0x010A,0x00},
#else
   {0x010A,0x80},
#endif
	 
   {0x037C,0x5D}, // CTP addr CLL lane1 
   {0x037D,0x71},//  CTP addr CLL lane1
   {0x0109,0x80}, 
   {0x0061,0x01}, 
   {0x0060,0x01},
   {0x0000,0x00}
};
#else
const u16 BU18TL82_Register[][2] =
{
	{0x0013,0x1a},
	{0x0014,0x00},
	{0x0021,0x08},
	{0x0023,0x09},
	{0x0025,0x01},
	{0x0045,0x00},//{0x0045,0x00},//分辨率低8位
	{0x0046,0x04},//{0x0046,0x02},//
	{0x004b,0x58},//
	{0x004c,0x02},//
	
	{0x002a,0x18},//In  BL_PWM
	{0x002d,0x00},//OUT CTP_INT
	{0x0030,0x18},//In AX5511_EN
	{0x003f,0x18},//In CTP_RST
	{0x02a7,0x02},//GPIO0 to RL
	{0x002e,0x03},//GPIO1 from RL
	{0x02a9,0x04},//GPIO2 to RL
	{0x02AE,0x09},//GPO7 to RL
	
	{0x0053,0x00},
	{0x0054,0xc0},
	
	{0x022b,0x3b},
	{0x022c,0x57},
	{0x022d,0x1e},
	{0x022e,0x80},
	{0x0018,0xa5},
	{0x0019,0x69},
	{0x0267,0x3d},
	{0x0268,0x2c},
	{0x0269,0x2c},
	{0x026a,0x2c},
	{0x026b,0x2c},
	{0x0367,0x3d},
	{0x0368,0x2c},
	{0x0369,0x2c},
	{0x036a,0x2c},
	{0x036b,0x2c},
	{0x0018,0x00},
	{0x0019,0x00},
	
	{0x0296,0x04},
	{0x0297,0x09},
	{0x028e,0x02},
	{0x0274,0x30},
	{0x0275,0x20},
	{0x027C,0x5D},//CTP addr 
	{0x027D,0x70},//CTP addr
	{0x0109,0x80},
	{0x0061,0x01},
	{0x0060,0x01},
	
	{0x0000,0x00}
};
#endif

#if MODEL==LINUX_2339WA_93||MODEL==LINUX_N039_DZ||MODEL==LINUX_2349WA_93
const u16 BU18RL82_Register[][2] =
{
   {0x0011,0x03},
   {0x0012,0x01},
   {0x0013,0x00},
   {0x001f,0x02},
   {0x0031,0x70}, //CTP addr.
   {0x0032,0x5D},// CTP addr.
   {0x003f,0x70},// CTP addr.
   {0x0040,0x5D},// CTP addr.
#if MODEL==LINUX_N039_DZ
	 {0x0057,0x10},// GPIO0 output BL_PWM
#else
   {0x0057,0x00},// GPIO0 output BL_PWM
#endif
   {0x0058,0x02},// GPO0 from TL
   {0x0059,0x00},// GPO0 from TL
   {0x005a,0x18},// GPIO1 inpput CTP_INT
   {0x042c,0x03},// GPI1 to TL
   {0x005d,0x00},// GPIO2 output AX5511_EN
#if MODEL==LINUX_2349WA_93
   {0x005e,0x04},//04 GPO2 from TL
#else
   {0x005e,0x01},//04 GPO2 from TL
#endif
   {0x005f,0x00},//GPO2 from TL
   {0x006c,0x00},// GPO7 output CTP_RST
   {0x006d,0x09},//09 GPO7 to from

   {0x0073,0x00}, 
   {0x0074,0x05}, 
   {0x0079,0x03},//01
   {0x007b,0xd0}, 
   {0x007c,0x02},
   {0x0081,0x01},  
   {0x0082,0x14},
   {0x0084,0x58},
   {0x0086,0x02},
   {0x0087,0x17},
   {0x0088,0x00},

   {0x00d0,0x00}, 
   {0x0429,0x0a},
   {0x045d,0x01},

   {0x0091,0x01},
   {0x0090,0x01}, 
   {0x0000,0x00}
};	
#else        
const u16 BU18RL82_Register[][2] =
{
	{0x0011,0x0b},
	{0x0012,0x00},
	{0x0013,0x00},//{0x0013,0x01},
	{0x001f,0x02},
	{0x0031,0x70},//CTP addr
	{0x0032,0x5D},//CTP addr
	      
	{0x0057,0x00},//GPIO0 output BL_PWM
	{0x0058,0x02},//GPO0 from TL
	{0x0059,0x00},//GPO0 from TL
	{0x005a,0x18},//GPIO1 inpput CTP_INT
	{0x042c,0x03},//GPI1 to TL
	{0x005d,0x00},//GPIO2 output AX5511_EN
	{0x005e,0x01},//GPO2 from TL//{0x005e,0x04},//GPO2 from TL
	{0x005f,0x00},//GPO2 from TL
	{0x006c,0x00},//GPO3 output CTP_RST
	{0x006d,0x09},//GPO3 to from
	      
	{0x0073,0x00},//{0x0073,0x00},//
	{0x0074,0x04},//{0x0074,0x02},//
	{0x0079,0x01},
	{0x007b,0x58},//分辨率600
	{0x007c,0x02},//
	{0x0081,0x01},
	{0x0082,0x14},
	{0x0084,0x94},
	{0x0086,0x0a},
	{0x0087,0x0d},
	{0x0088,0x00},
	//{0x00d0,0x40},
	//{0x00d8,0x00},
	//{0x00d9,0x04},
	{0x0429,0x0a},
	{0x045d,0x01},
	
	{0x0091,0x01},
	{0x0090,0x01},
	
	{0x0000,0x00}
};
#endif

const u16 TL_color_screen[][2] =
{
	{0x0409, 0x71},  //TL82 Pattern Gen setting
	{0x040A, 0xb0},//TL82 Pattern Gen Set
	{0x040B, 0xFF},//Vertical Gray Scale Color Bar  
	{0x040C, 0xFF},  
	{0x040D, 0xFF},  
	{0x040E, 0x2D},//TL82 Pattern Gen Set  
	{0x040F, 0xFF},//Vertical Gray Scale Color Bar
	{0x0410, 0xFF},
	{0x0411, 0xFF},  
	{0x0412, 0xAD},//TL82 Pattern Gen Set  
	{0x0413, 0xFF},//Vertical Gray Scale Color Bar  
	{0x0414, 0xFF},  
	{0x0415, 0xFF},  
	{0x0416, 0xB0},//TL82 Pattern Gen Set
	{0x0417, 0xFF},//Vertical Gray Scale Color Bar
	{0x0418, 0xFF},  
	{0x0419, 0xFF},  
	{0x041A, 0xBC},//TL82 Pattern Gen Set  
	{0x041B, 0xFF},//Vertical Gray Scale Color Bar  
	{0x041C, 0xFF},  
	{0x041D, 0xFF},
	{0x041E, 0xBD},//TL82 Pattern Gen Set
	{0x041F, 0xFF},//Vertical Gray Scale Color Bar  
	{0x0420, 0xFF},  
	{0x0421, 0xFF},  
	{0x0444, 0x14},  
	{0x0445, 0x00},  
	{0x0446, 0x23},
	
  {0x0000, 0x00},
};
const u16 RL_color_screen[][2] =
{
	{0x0609, 0x51},  //TL82 Pattern Gen setting
	{0x060A, 0x2C},//RL82 Pattern Gen Set
	{0x060B, 0xFF},//Vertical Gray Scale Color Bar
	{0x060C, 0xFF},
	{0x060D, 0xFF},
	{0x060E, 0x2D},//RL82 Pattern Gen Set
	{0x060F, 0xFF},//Vertical Gray Scale Color Bar
	{0x0610, 0xFF},
	{0x0611, 0xFF},
	{0x0612, 0xAD},//RL82 Pattern Gen Set
	{0x0613, 0xFF},//Vertical Gray Scale Color Bar
	{0x0614, 0xFF},
	{0x0615, 0xFF},
	{0x0616, 0xB0},//RL82 Pattern Gen Set
	{0x0617, 0xFF},//Vertical Gray Scale Color Bar
	{0x0618, 0xFF},
	{0x0619, 0xFF},
	{0x061A, 0xBC},//RL82 Pattern Gen Set
	{0x061B, 0xFF},//Vertical Gray Scale Color Bar
	{0x061C, 0xFF},
	{0x061D, 0xFF},
	{0x061E, 0xBD},//RL82 Pattern Gen Set
	{0x061F, 0xFF},//Vertical Gray Scale Color Bar
	{0x0620, 0xFF},
	{0x0621, 0xFF},
	{0x0644, 0x14},
	{0x0645, 0x00},
	{0x0646, 0x23},
	
  {0x0000, 0x00},
};
void BU18xL82_Write(u16 addr,u8 data, u8 device_addr)
{
	GPIO_I2C3_Start();	
	GPIO_I2C3_SendByte(device_addr);
	GPIO_I2C3_WaitACK();

	GPIO_I2C3_SendByte(addr>>8);
	GPIO_I2C3_WaitACK();
	GPIO_I2C3_SendByte(addr);
	GPIO_I2C3_WaitACK();
	
	GPIO_I2C3_SendByte(data);
	GPIO_I2C3_WaitACK();	
	GPIO_I2C3_Stop();
}

u8 BU18xL82_Read(u16 addr, u8 device_addr)
{
	u8 result  =0;
	
	GPIO_I2C3_Start();	
	GPIO_I2C3_SendByte(device_addr);
	GPIO_I2C3_WaitACK();
	GPIO_I2C3_SendByte(addr>>8);
	GPIO_I2C3_WaitACK();
	GPIO_I2C3_SendByte(addr);
	GPIO_I2C3_WaitACK();
	//GPIO_I2C3_Stop(); 

	GPIO_I2C3_Start();	
	GPIO_I2C3_SendByte(device_addr|0x01);
	GPIO_I2C3_WaitACK();
	result=GPIO_I2C3_ReceiveByte();	
	GPIO_I2C3_NACK();	
	GPIO_I2C3_Stop();
	return result;
}
void BU18xL82_Read_All_Register(void)
{
	u8 i;
	for(i=0;;i++)
	{
		if(BU18TL82_Register[i][0]==0)break;
		Read_TL_Buffer[i][0]=BU18TL82_Register[i][0];
		Read_TL_Buffer[i][1]=BU18xL82_Read(BU18TL82_Register[i][0], BU18TL82_Add);
	}
			
	for(i=0;;i++)
	{
		if(BU18RL82_Register[i][0]==0)break;
		Read_RL_Buffer[i][0]=BU18RL82_Register[i][0];
		Read_RL_Buffer[i][1]=BU18xL82_Read(BU18RL82_Register[i][0], BU18RL82_Add);
	}
}

#if MODEL==LINUX_2339WA_93||MODEL==LINUX_N039_DZ||MODEL==LINUX_2349WA_93
void BU18xL82_PowerOn(void)
{
		BU18TL82State=BU18TL82_SETP_1V2_ON;
}
#endif

#if MODEL==LINUX_2339WA_93||MODEL==LINUX_N039_DZ||MODEL==LINUX_2349WA_93
void BU18xL82_AccOff(void)
{
		BU18TL82State=BU18TL82_SETP_ACC_OFF;
}
#endif

void BU18xL82_Main_Pro(void)
{
	u8 i;
	
#if MODEL==LINUX_2339WA_93||MODEL==LINUX_N039_DZ||MODEL==LINUX_2349WA_93
#else
	if(!Main_Power()) 
	{
		BU18TL82State=BU18TL82_SETP_1V2_ON;
		return;
	}
#endif
	
	if(BU18TL82Timer)
	{
		BU18TL82Timer--;
	}
	switch(BU18TL82State)
	{
		case BU18TL82_IDLE:
			break;
		case BU18TL82_SETP_1V2_ON:
			VDD_1V2_ON;
			BU_RESET_LOW;
		  BU18TL82Timer=T10MS_10;
		  BU18TL82State=BU18TL82_SETP_BU_RESET;
			break;
		case BU18TL82_SETP_BU_RESET:
			if(BU18TL82Timer)
			{
				break;	
			}
			BU_RESET_HIGH;
			BU18TL82Timer=T30MS_10;//T40MS_10;
			BU18TL82State=BU18TL82_SETP_BU18TL82_INIT;
			break;
		case BU18TL82_SETP_BU18TL82_INIT:
			if(BU18TL82Timer)
			{
				break;	
			}
			for(i=0;;i++)
			{
				if(BU18TL82_Register[i][0]==0)break;
				BU18xL82_Write(BU18TL82_Register[i][0],BU18TL82_Register[i][1], BU18TL82_Add);
			}
			BU18TL82Timer=T150MS_10;
			BU18TL82State=BU18TL82_SETP_BU18RL82_INIT;
			break;
		case BU18TL82_SETP_BU18RL82_INIT:
			if(BU18TL82Timer)
			{
				break;	
			}
			for(i=0;;i++)
			{
				if(BU18RL82_Register[i][0]==0)break;
				BU18xL82_Write(BU18RL82_Register[i][0],BU18RL82_Register[i][1], BU18RL82_Add);
				Read_RL_Buffer[i][0]=BU18RL82_Register[i][0];
				Read_RL_Buffer[i][1]=BU18xL82_Read(BU18RL82_Register[i][0], BU18RL82_Add);
			}
      BU18TL82State=BU18TL82_SETP_SELECT_IIC;
		  break;
		case BU18TL82_SETP_SELECT_IIC://old P079 need to skip this step
			BU18xL82_Write(0x0016,0x01, BU18TL82_Add);
		  BU18xL82_Write(0x0017,0x00, BU18TL82_Add);
			BU18TL82State=BU18TL82_SETP_INIT_OK;
			break;
		case BU18TL82_SETP_INIT_OK:
			if(Read_All_Register_Flag)
			{
				Read_All_Register_Flag=0;
				BU18xL82_Read_All_Register();
			}
			if(BU18TL82Timer)
			{
				break;
			}
#if MODEL==LINUX_N039_DZ	
			if(!BU_ERROR_DET)
#endif
			{
				CCL_LINK_DATA=BU18xL82_Read(0x0131, BU18TL82_Add);
				if(CCL_LINK_DATA==0x80)
				{
					BU18xL82_Write(0x0105,0x01,BU18TL82_Add);
					CCL_LINK_DATA=BU18xL82_Read(0x0131, BU18TL82_Add);
					if(CCL_LINK_DATA==0)
					{
						BU18TL82State=BU18TL82_SETP_1V2_ON;
					}
				}
			}
			BU18TL82Timer=T500MS_10;
			break;
		case BU18TL82_SETP_ACC_OFF:
			BU18xL82_Write(0x0016,0x00, BU18TL82_Add);
		  BU18xL82_Write(0x0017,0x01, BU18TL82_Add);
			BU18TL82Timer=T10MS_10;
			BU18TL82State=BU18TL82_SETP_ACC_OFF2;
		case BU18TL82_SETP_ACC_OFF2:
			if(BU18TL82Timer)
			{
				break;	
			}
			BU18xL82_Write(0x0058,0x00,BU18RL82_Add);
			BU18TL82State=BU18TL82_SETP_SHUTDOWN;
			break;
		case BU18TL82_SETP_SHUTDOWN:
			break;
		default:
			break;
	}
	
}

#endif
















