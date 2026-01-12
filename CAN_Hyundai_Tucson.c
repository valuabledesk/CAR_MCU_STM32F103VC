#include "public.h"

#if CAN_FUN_HYUNDAI_TUCSON==1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
u32 CanMainTimer;
u32 CanNoDataTimer;
#if TEST_HYUNDAI_TUCSON_CAN==1
u32 CanTestTimer1;
u32 CanTestTimer2;
u32 CanTestBrightness;
u32 CanTestReverseParking;
u8 CanTestParkingFlag;
u8 CanTestParkingTimer;
u8 CanTestParkingLevel;
void CanTestTxBrightnessMessage(void)
{
	u8 data[8]={0};
	data[6]=CanTestBrightness;
	data[6]<<=3;
	CAN1_TxFrame(CAN_ID_BRIGHTNESS,data,8);	
}
void CanTestTxReverseMessage(void)
{
	u8 data[8]={0};
	data[0]=CanTestReverseParking;
	CAN1_TxFrame(CAN_ID_VEHICLE_INDICATIONS,data,8);	
}
void CanTestPro(void)
{
	CanTestTimer1++;
	if(CanTestTimer1==T2S_1)
	{
		CanTestTimer1=0;
		if(CanTestBrightness==0)
		{
			CanTestBrightness=1;
		}
		else if(CanTestBrightness==1)
		{
			CanTestBrightness=21;
		}
		else if(CanTestBrightness==21)
		{
			CanTestBrightness=1;
		}
		CanTestTxBrightnessMessage();
	}
	CanTestTimer2++;
	if(CanTestTimer2==T5S_1)
	{
		CanTestTimer2=0;
		if(CanTestReverseParking==0)
		{
			CanTestReverseParking=7;
			CanTestParkingFlag=0;
		}
		else if(CanTestReverseParking==7)
		{
			CanTestReverseParking=0xFF;
			CanTestParkingFlag=0;
		}
		else if(CanTestReverseParking==0xFF)
		{
			CanTestReverseParking=0;
			CanTestParkingFlag=1;
		}
		CanTestTxReverseMessage();
	}
	CanTestParkingTimer++;
	if(CanTestParkingTimer==T200MS_1)
	{
		CanTestParkingTimer=0;
		if(CanTestParkingFlag==0)
		{
			if(CanTestParkingLevel==0)
			{
				RearCameraOn();
				CanTestParkingLevel=1;
			}
			else
			{
				RearCameraOff();
				CanTestParkingLevel=0;
			}
		}
	}
}
#endif

void Hyundai_Tucson_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_ALARM:
				CanRxInfo.alarm=(message.Data[0]&0x04)>>2;
				if(CanRxInfo.alarm!=CanRxInfoBak.alarm)
				{
					CanRxInfoBak.alarm=CanRxInfo.alarm;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_ALARM_STATUS);
				}
				break;
			case CAN_ID_BRIGHTNESS:
				{
					u32 temp;
					u32 tft_bright_level;
				CanRxInfo.brightness=(message.Data[6]&0xF8)>>3;
					if(CanRxInfo.brightness)
					{
						CanRxInfo.brightness-=1;
					}
					if(CanRxInfo.brightness>20)
					{
						CanRxInfo.brightness=20;
					}
				if(CanRxInfo.brightness!=CanRxInfoBak.brightness)
				{
					CanRxInfoBak.brightness=CanRxInfo.brightness;
						//PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_BRIGHTNESS);
					}
					temp=(CanRxInfo.brightness*100)/20;
					temp=KEY_LED_PERCENT_MIN+(((KEY_LED_PERCENT_MAX-KEY_LED_PERCENT_MIN)*temp)/100);
					CanGeneralCtrlFlag.field.illumi_level=temp;
					if(F_BACKLIGHT_TYPE==BACKLIGHT_AUTO)
					{
						TFT_Brightness=CanRxInfo.brightness;
						TFT_Brightness_illumine=CanRxInfo.brightness;
						tft_bright_level=((CanRxInfo.brightness*(BACKLIGHT_PERCENT_MAX-BACKLIGHT_PERCENT_MIN))/SYS_BRIGHTNESS_VALUE_MAX)+BACKLIGHT_PERCENT_MIN;				
						TFT_Backlight_Level=tft_bright_level;
					}
				}
				break;
			case CAN_ID_DOOR_STATUS:
				CanRxInfo.door_status.field.f_driver_door=((message.Data[0]&0x04)>>2);
				CanRxInfo.door_status.field.f_passenger_door=(message.Data[0]&0x01);
				CanRxInfo.door_status.field.f_rear_left_door=((message.Data[1]&0x10)>>4);
				CanRxInfo.door_status.field.f_rear_right_door=((message.Data[1]&0x40)>>6);
				CanRxInfo.door_status.field.f_tail_gate=(message.Data[2]&0x01);
				if(CanRxInfo.door_status.byte!=CanRxInfoBak.door_status.byte)
				{
					CanRxInfoBak.door_status.byte=CanRxInfo.door_status.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_DOOR_STATUS);
				}
				break;
			case CAN_ID_PARKING_SENSORS:
				CanRxInfo.parking_sensor.rear_left=(message.Data[7]&0x03);
				CanRxInfo.parking_sensor.rear_center=((message.Data[7]&0x0C)>>2);
				CanRxInfo.parking_sensor.rear_right=((message.Data[7]&0x30)>>4);
				CanRxInfo.parking_sensor.front_left=(message.Data[6]&0x03);
				CanRxInfo.parking_sensor.front_center=((message.Data[6]&0x0C)>>2);
				CanRxInfo.parking_sensor.front_right=((message.Data[6]&0x30)>>4);
				break;
			case CAN_ID_VEHICLE_INDICATIONS:
				switch((message.Data[0]&0x0F))
				{
					case 0:
						CanGeneralCtrlFlag.field.parking_on_off=1;
						CanGeneralCtrlFlag.field.reverse_on_off=0;
						break;
					case 7:
						CanGeneralCtrlFlag.field.reverse_on_off=1;
						CanGeneralCtrlFlag.field.parking_on_off=0;
						break;
					default:
						CanGeneralCtrlFlag.field.reverse_on_off=0;
						CanGeneralCtrlFlag.field.parking_on_off=0;
						break;
				}

				break;
			default:
				break;
		}
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
		CanNoDataTimer=T300S_1;
		CAN1_ClearErrorTimer();
	}
}

void Hyundai_Tucson_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case HYUNDAI_TUCSON_RX_ALARM_STATUS:
			buffer[2]=0x01;
			buffer[3]=CanRxInfo.alarm;
			break;		   
		case HYUNDAI_TUCSON_RX_BRIGHTNESS:
			buffer[2]=0x01;
			buffer[3]=CanRxInfo.brightness;
			break;
		case HYUNDAI_TUCSON_RX_DOOR_STATUS:
			buffer[2]=0x01;
			buffer[3]=CanRxInfo.door_status.byte;
			break;
		case HYUNDAI_TUCSON_RX_RADAR:
			buffer[2]=0x06;
			buffer[3]=CanRxInfo.parking_sensor.rear_left;
			buffer[4]=CanRxInfo.parking_sensor.rear_center;
			buffer[5]=CanRxInfo.parking_sensor.rear_right;
			buffer[6]=CanRxInfo.parking_sensor.front_left;
			buffer[7]=CanRxInfo.parking_sensor.front_center;
			buffer[8]=CanRxInfo.parking_sensor.front_right;
			break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=HYUNDAI_TUCSON_HEAD_CODE;
		buffer[1]=cmd_id;
		*length=buffer[2]+4;
		for(i=0;i<(buffer[2]+2);i++)
		{
			checksum+=buffer[i+1];
		}
		buffer[i+1]=checksum;
	}
	else
	{
		*length=0;
	}
}

void Hyundai_Tucson_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;

	cmd_id=buffer[1];
	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	switch(cmd_id)
	{
		case HYUNDAI_TUCSON_TX_REQ_CMD:
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_ALARM_STATUS);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_BRIGHTNESS);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_DOOR_STATUS);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_RADAR);
			break;
		default:
			break;
	}
}

void Hyundai_Tucson_MainPro(void)
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
	
	if(CanNoDataTimer)
	{
		CanNoDataTimer--;
		if(CanNoDataTimer==0)
		{
			F_CAN_RX_DATA=0;
		}
	}

	Hyundai_Tucson_Rx_Message();
	if(F_CAN_INIT)
	{
	CAN1_Transmit();
	}
	switch(CanMainState)
	{
		case CAN_MAIN_IDLE:
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;
			CanGeneralCtrlFlag.field.illumi_level=KEY_LED_PERCENT_MAX;
			break;
		case CAN_MAIN_CFG:
			CAN1_Init();
			CanMainState=CAN_MAIN_INIT;
			break;
		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			F_CAN_SLEEP=0;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T30S_1;
			break;
		case CAN_MAIN_NORMAL:
#if TEST_HYUNDAI_TUCSON_CAN==1
			CanTestPro();
#else
			if(F_CAN_RX_DATA==0)
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}
			else if(Get_ACC_Det_Flag==0)
			{
				CanMainState=CAN_MAIN_WAIT_SLEEP;
			}
			else
			{
				if(Get_Reverse_Det_Flag)
				{
					if(CanMainTimer==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_RADAR);
						CanMainTimer=T500MS_1;
					}
				}
				else if(CanMainTimer==0)
				{
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_ALARM_STATUS);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_BRIGHTNESS);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HYUNDAI_TUCSON_RX_DOOR_STATUS);
					CanMainTimer=T5S_1;
				}
			}
#endif
			break;
		case CAN_MAIN_WAIT_SLEEP:
			if(F_CAN_RX_DATA==0)
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}
			else if(Get_ACC_Det_Flag==1)
			{	
				CanMainState=CAN_MAIN_NORMAL;
			}
			break;
		case CAN_MAIN_SLEEP_CFG:
			CAN1_ClearRxMessage();
			CAN_IC_STANDBY_ON;
			F_CAN_SLEEP=1;
			F_CAN_INTERRUPT=0;
			CanMainTimer=T100MS_1;
			CanMainState=CAN_MAIN_SLEEP;
			break;
		case CAN_MAIN_SLEEP:
			if(CanMainTimer)
			{
				break;
			}
			if(F_CAN_SLEEP==0
				||F_CAN_INTERRUPT)
			{
				CAN_IC_STANDBY_OFF;
				F_CAN_SLEEP=0;
				CanMainState=CAN_MAIN_INIT;
			}
			break;
		default:
			break;
	}
}

#endif

