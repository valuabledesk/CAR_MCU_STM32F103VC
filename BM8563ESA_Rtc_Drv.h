#ifndef _BM8563ESA_RTC_DRV_H_
#define _BM8563ESA_RTC_DRV_H_

#if RTC_MODULE==RTC_BM8563ESA

#define RTC_READ_ADDRESS            0xA3
#define RTC_WRITE_ADDRESS          0xA2

#define RTC_DATE_ADDRESS          0x02


typedef struct
{
	u8 seconds;    // in the 0-59 range
	u8 minutes;    // in the 0-59 range
	u8 hours;      // in the 0-23 range
	u8 week_day;    //in the 0-6 range
	u8 day;      //in the 1-12 range
	u8 month;       // in the 1-31 range
	u8 year;       //in the 0-99 range                      
}RTC_DATE_TIME_TYPE_DEF;

extern RTC_DATE_TIME_TYPE_DEF RTC_TimeInfo;

void RTC_Init(void);
RTC_DATE_TIME_TYPE_DEF RTC_ReadTime(void);
void RTC_SetTime(RTC_DATE_TIME_TYPE_DEF time);
void RTC_UpdateTime(u32 time);
u32 RTC_ConvertTime(RTC_DATE_TIME_TYPE_DEF time);

#endif
#endif

