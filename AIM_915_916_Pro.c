#include "public.h"

#if AIM_915_916_FUN==1

u8 AIM_915_ID;
u8 AIM_916_ID;
u8 AIM_916_buffer[8];
u8 AIM_915_buffer[8];
u16 Aim_Step_TimerCounter;
AIM_INIT_STATUS Aim_Init_Status = AIM_INIT_IDLE;
u8 AIM_915_0x07_ID;
u8 AIM_915_0x08_ID;
u8 AIM_Init_counter;

u8 AIM_915_ReadReg(u8 reg)
{
	u8 data;
	
	GPIO_I2C3_Start();
	GPIO_I2C3_SendByte(0x18);
	Delay_us(20);
	GPIO_I2C3_WaitACK();
	GPIO_I2C3_SendByte(reg);
	Delay_us(20);
	GPIO_I2C3_WaitACK();
	GPIO_I2C3_Stop();
	GPIO_I2C3_Start();
	GPIO_I2C3_SendByte(0x19);
	Delay_us(20);
	GPIO_I2C3_WaitACK();
	data=GPIO_I2C3_ReceiveByte();
	Delay_us(20);
	GPIO_I2C3_NACK();
	GPIO_I2C3_Stop();	
	return data;

}

u8 AIM_915_WriteReg(u8 reg,u8 data)
{   
	u8 result=0;
	GPIO_I2C3_Start();
	GPIO_I2C3_SendByte(0x18);
	Delay_us(20);

	result = GPIO_I2C3_WaitACK();
	GPIO_I2C3_SendByte(reg);
	Delay_us(20);

	result = GPIO_I2C3_WaitACK();
	GPIO_I2C3_SendByte(data);
	Delay_us(20);

	result = GPIO_I2C3_WaitACK();
	GPIO_I2C3_Stop();
	
	return result;
}

u8 AIM_916_ReadReg(u8 reg)
{
    u8 data;
	
	GPIO_I2C3_Start();
	GPIO_I2C3_SendByte(0x58);
	Delay_us(20);
	GPIO_I2C3_WaitACK();
	GPIO_I2C3_SendByte(reg);
	Delay_us(20);
	GPIO_I2C3_WaitACK();
	
	GPIO_I2C3_Stop();
	GPIO_I2C3_Start();
	GPIO_I2C3_SendByte(0x59);
	Delay_us(20);
	GPIO_I2C3_WaitACK();

	data=GPIO_I2C3_ReceiveByte();
	Delay_us(20);
	GPIO_I2C3_NACK();
	GPIO_I2C3_Stop();	
	return data;
}

u8 AIM_916_WriteReg(u8 reg,u8 data)
{
    u8 result=0;    
	GPIO_I2C3_Start();
	GPIO_I2C3_SendByte(0x58);
	Delay_us(20);

	result = GPIO_I2C3_WaitACK();

	GPIO_I2C3_SendByte(reg);
	Delay_us(20);

	result = GPIO_I2C3_WaitACK();


	GPIO_I2C3_SendByte(data);
	Delay_us(20);

	result = GPIO_I2C3_WaitACK();

	GPIO_I2C3_Stop();
	return result;
}

int AIM_Init_915_Internal(void)
{
    /***915****/

    if(AIM_915_WriteReg(0x66, 0x56) == 0)
        return -1;
    if(AIM_915_WriteReg(0x67, 0x00) == 0)
        return -1;
    
    if(AIM_915_WriteReg(0x66, 0x50) == 0)
        return -1;
    if(AIM_915_WriteReg(0x67, 0xBD)== 0)
        return -1;
    
    if(AIM_915_WriteReg(0x06, 0x58)== 0)
        return -1;
    if(AIM_915_WriteReg(0x07, 0xBA)== 0)
        return -1;
    if(AIM_915_WriteReg(0x08, 0xBA)== 0)
        return -1;
    
    if(AIM_915_WriteReg(0x17, 0x0E)== 0)
        return -1;
    
    if(AIM_915_WriteReg(0x20, 0x01)== 0)
        return -1;
    if(AIM_915_WriteReg(0x0F, 0x05)== 0)
        return -1;
    if(AIM_915_WriteReg(0x0E, 0x33)== 0)
        return -1;
    if(AIM_915_WriteReg(0x0D, 0x03)== 0)
        return -1;  
    return 1; 


}

int AIM_Init_916_Internal(void)
{
    /****916****/
    
    if(AIM_916_WriteReg(0x66, 0x50)== 0)
        return -1;
    if(AIM_916_WriteReg(0x07, 0x01)== 0)
        return -1;
    if(AIM_916_WriteReg(0x07, 0x18)== 0)
        return -1;
    
    
    if(AIM_916_WriteReg(0x66, 0x6E)== 0)
        return -1;
    if(AIM_916_WriteReg(0x67, 0x04)== 0)
        return -1;
    
    if(AIM_916_WriteReg(0x66, 0x50)== 0)
        return -1;
    if(AIM_916_WriteReg(0x67, 0x80)== 0)
        return -1;
    
    if(AIM_916_WriteReg(0x66, 0x56)== 0)
        return -1;
    if(AIM_916_WriteReg(0x67, 0x1D)== 0)
        return -1;
    

 
    return 1;    
}


void AIM_Init_StatusToConfig(u8 mode)
{
    if(mode==0)
    {
        Aim_Init_Status=AIM_INIT_START;
        AIM_915_PDB_CTRL_HOLD;
        POWER_SCREEN_OFF;
        Aim_Step_TimerCounter=T1S5_10;//T1S5_10;
    }
    else if(mode==1)
    {
        Aim_Init_Status=AIM_INIT_START;
        AIM_915_PDB_CTRL_HOLD;
        POWER_SCREEN_OFF;
        Aim_Step_TimerCounter=T1S_10;
    }
}

int AIM_Clock_Switch(u8 mode)
{
    if(mode==0)
    {
        if(AIM_915_WriteReg(0x66, 0x68) == 0)
            return -1;
        
        if(AIM_915_WriteReg(0x67, 0x03) == 0)
            return -1;

        if(AIM_915_WriteReg(0x66, 0x5B) == 0)
            return -1;
        
        if(AIM_915_WriteReg(0x67, 0x23) == 0)
            return -1;

        
        if(AIM_915_WriteReg(0x66, 0x51) == 0)
            return -1;
        
        if(AIM_915_WriteReg(0x67, 0xD1) == 0)
            return -1;
    }
    else if(mode==1)
    {
        if(AIM_915_WriteReg(0x66, 0x68) == 0)
            return -1;
        
        if(AIM_915_WriteReg(0x67, 0x00) == 0)
            return -1;
        if(AIM_915_WriteReg(0x66, 0x5B) == 0)
            return -1;
        
        if(AIM_915_WriteReg(0x67, 0x63) == 0)
            return -1;
    }
    return 1;
}


void AIM_Init_Step(void)
{
    static u16 Aim_init_num=0;
    
    if(Aim_Step_TimerCounter)
    {
        Aim_Step_TimerCounter--;
        return;
    }
    switch(Aim_Init_Status)
    {
        case AIM_INIT_IDLE:
            break;
        case AIM_INIT_START:
            AIM_915_PDB_CTRL_RELEASE;
            Aim_Step_TimerCounter = T100MS_10;
            Aim_Init_Status=AIM_INIT_CONFIG;
            break;
        case AIM_INIT_CONFIG:
            GPIO_I2C3_PortInit();
            Aim_init_num=0;
            AIM_Init_counter = 0;
            Aim_Init_Status=AIM_INIT_FUNC;
            
            AIM_Clock_Switch(0);
            //Aim_Step_TimerCounter = T100MS_10;
            break;
        case AIM_INIT_FUNC:
            if(AIM_Init_915_Internal()==1)
            {
                Aim_Init_Status = AIM_INIT_RESUME;
                POWER_SCREEN_ON;
                Aim_Step_TimerCounter = T400MS_10;
            }
            break;
        case AIM_INIT_SCREEN_ON:
            POWER_SCREEN_ON;
            Aim_Step_TimerCounter = T50MS_10;
            Aim_Init_Status=AIM_INIT_RESUME;
            break;
        case AIM_INIT_RESUME:
            AIM_916_ID = AIM_916_ReadReg(0x50);
            if(AIM_916_ID==0xFC)
            {
                if(AIM_Init_916_Internal() == 1)
                {
                    Aim_Init_Status=AIM_INIT_EXIT;
                    Aim_Step_TimerCounter = T200MS_10;
                    AIM_Clock_Switch(1);
                    
                }  
                else
                {
                    Aim_Step_TimerCounter = T100MS_10;
                    Aim_Init_Status=AIM_INIT_ERROR;
                }
                Aim_init_num++;
                if(Aim_init_num > 5)
                {
                    Aim_Init_Status=AIM_INIT_ERROR;
                }
            }
            else
            {
                //Aim_Init_Status=AIM_INIT_ERROR;
                Aim_Init_Status=AIM_INIT_SCREEN_OFF;
                AIM_Init_counter++;
                if(AIM_Init_counter>5)
                {
                	Aim_Init_Status=AIM_INIT_ERROR;
                }
            }
            break;
        case AIM_INIT_EXIT:
            AIM_916_WriteReg(0x1F, 0x03);
            AIM_916_WriteReg(0x1E, 0x55);//AIM_916_WriteReg(0x1E, 0x95);//
            AIM_916_WriteReg(0x1D, 0x09);
            AIM_915_0x07_ID = AIM_915_ReadReg(0x07);
            AIM_915_0x08_ID = AIM_915_ReadReg(0x08);
            GPIO_SetDir(GPIO_I2C3_SCL_PIN, INPUT);
	        GPIO_SetDir(GPIO_I2C3_SDA_PIN, INPUT);
	        Aim_Init_Status=AIM_INIT_NORMAL;
            break;
        case AIM_INIT_SCREEN_OFF:
            POWER_SCREEN_OFF;
            Aim_Step_TimerCounter = T50MS_10;
            Aim_Init_Status=AIM_INIT_SCREEN_ON;
            break;
        case AIM_INIT_NORMAL:
            break;
        case AIM_INIT_ERROR:
            SystemReset();
            break;
        default:
            break;
    }
}

void AIM_read_test(void)
{
    AIM_915_buffer[0] = AIM_915_ReadReg(0x06);
    AIM_915_buffer[1] = AIM_915_ReadReg(0x07);
    AIM_915_buffer[2] = AIM_915_ReadReg(0x08);
    AIM_915_buffer[3] = AIM_915_ReadReg(0x17);
    AIM_915_buffer[4] = AIM_915_ReadReg(0x20);
    AIM_915_buffer[5] = AIM_915_ReadReg(0x0F);
    AIM_915_buffer[6] = AIM_915_ReadReg(0x0E);
    AIM_915_buffer[7] = AIM_915_ReadReg(0x0D);
    AIM_915_ID = AIM_915_ReadReg(0x0C);

    AIM_916_buffer[0] = AIM_916_ReadReg(0x07);
    AIM_916_buffer[1] = AIM_916_ReadReg(0x1F);
    AIM_916_buffer[2] = AIM_916_ReadReg(0x1E);
    AIM_916_buffer[3] = AIM_916_ReadReg(0x1D);   
}

#endif



