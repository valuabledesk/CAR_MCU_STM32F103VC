#include "public.h"
#include "time.h"

#if RTC_MODULE==RTC_BM8563ESA
RTC_DATE_TIME_TYPE_DEF RTC_TimeInfo;
u8 RTC_WriteData[7];
u8 RTC_ReadData[7];


void RTC_Write(u8 addr,u8 *data,u8 lenth)
{
	u32 i;

	GPIO_I2C_Start();
	GPIO_I2C_SendByte(RTC_WRITE_ADDRESS);
	GPIO_I2C_WaitACK();
	GPIO_I2C_SendByte(addr);
	GPIO_I2C_WaitACK();
	for(i=0;i<lenth;i++)
	{
		GPIO_I2C_SendByte(data[i]);
		GPIO_I2C_WaitACK();
	}
	GPIO_I2C_Stop();
}

void RTC_Read(u8 addr,u8 *data,u8 length)
{
	u32 i;
	
	GPIO_I2C_Start();
	GPIO_I2C_SendByte(RTC_WRITE_ADDRESS);
	GPIO_I2C_WaitACK();
	GPIO_I2C_SendByte(addr);
	GPIO_I2C_WaitACK();

	GPIO_I2C_Start();
	GPIO_I2C_SendByte(RTC_READ_ADDRESS);
	GPIO_I2C_WaitACK();

	for(i=0;i<length;i++)
	{
		data[i]=GPIO_I2C_ReceiveByte();
		if(i==(length-1))
		{
			GPIO_I2C_NACK();
		}
		else
		{
			GPIO_I2C_ACK();
		}
	}
	GPIO_I2C_Stop();
}

void RTC_SetTime(RTC_DATE_TIME_TYPE_DEF time)
{	
	if(time.seconds>59)
	{
		time.seconds=0;
	}
	RTC_WriteData[0]=((time.seconds/10)<<4)|(time.seconds%10);
	
	if(time.minutes>59)
	{
		time.minutes=0;
	}
	RTC_WriteData[1]=((time.minutes/10)<<4)|(time.minutes%10);
	
	if(time.hours>23)
	{
		time.hours=0;
	}
	RTC_WriteData[2]=((time.hours/10)<<4)|(time.hours%10);
	
	if(time.day>31)
	{
		time.day=1;
	}
	RTC_WriteData[3]=((time.day/10)<<4)|(time.day%10);

	if(time.week_day>6)
	{
		time.week_day=0;
	}
	RTC_WriteData[4]=time.week_day;

	if(time.month>12)
	{
		time.month=1;
	}
	RTC_WriteData[5]=((time.month/10)<<4)|(time.month%10);	

	if(time.year>99)
	{
		time.year=0;
	}
	RTC_WriteData[6]=((time.year/10)<<4)|(time.year%10);	
	RTC_Write(RTC_DATE_ADDRESS,RTC_WriteData,7);

	RTC_TimeInfo = time;
}

RTC_DATE_TIME_TYPE_DEF RTC_ReadTime(void)
{
	RTC_DATE_TIME_TYPE_DEF time;

	RTC_Read(RTC_DATE_ADDRESS,RTC_ReadData,7);

	time.seconds=(((RTC_ReadData[0]&0x70)>>4)*10)+(RTC_ReadData[0]&0x0F);
	time.minutes=(((RTC_ReadData[1]&0x70)>>4)*10)+(RTC_ReadData[1]&0x0F);
	time.hours=(((RTC_ReadData[2]&0x30)>>4)*10)+(RTC_ReadData[2]&0x0F);
	time.day=(((RTC_ReadData[3]&0x30)>>4)*10)+(RTC_ReadData[3]&0x0F);
	time.week_day=RTC_ReadData[4];
	time.month=(((RTC_ReadData[5]&0x10)>>4)*10)+(RTC_ReadData[5]&0x0F);
	time.year=(((RTC_ReadData[6]&0xF0)>>4)*10)+(RTC_ReadData[6]&0x0F);

	return time;
}

void RTC_Init(void)
{
	RTC_DATE_TIME_TYPE_DEF time;

	time.year=23;
	time.month  = 1;
	time.day = 1;
	time.week_day=0x01;
	time.hours= 0;
	time.minutes= 0;
	time.seconds= 0;

	RTC_SetTime(time);
}

void RTC_UpdateTime(u32 time)
{
	RTC_DATE_TIME_TYPE_DEF rtc_time;
	struct tm *time_pointer;
	struct tm time_info;
	u32 time_data;
	

	time_data=time;
	time_pointer=localtime(&time_data);
	time_info=*time_pointer;

	if(time_info.tm_year>100)
	{
		time_info.tm_year-=100;
	}
	else
	{
		time_info.tm_year=0;
	}
	rtc_time.year= time_info.tm_year;
	rtc_time.month= time_info.tm_mon+1;
	rtc_time.day= time_info.tm_mday;
	rtc_time.week_day= time_info.tm_wday;
	rtc_time.hours= time_info.tm_hour;
	rtc_time.minutes=time_info.tm_min;
	rtc_time.seconds=time_info.tm_sec;

	RTC_SetTime(rtc_time);	
}

u32 RTC_ConvertTime(RTC_DATE_TIME_TYPE_DEF time)
{
	u32 time_data;
	struct tm time_info;

	time_info.tm_year=time.year+100;
	time_info.tm_mon=time.month-1;
	time_info.tm_mday=time.day;
	time_info.tm_wday=time.week_day;
	time_info.tm_hour=time.hours;
	time_info.tm_min=time.minutes;
	time_info.tm_sec=time.seconds;

	time_data = mktime(&time_info);
	return time_data;
}
#endif


