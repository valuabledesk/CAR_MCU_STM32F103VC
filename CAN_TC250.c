#include "public.h"

#if CAN_FUN_TC250 == 1
CAN_RX_INFO CanRxInfo = {.vehicel_info.region = 0xff};
CAN_RX_INFO CanRxInfoBak;
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_TX_INFO CanTxInfo;
CAN_TX_INFO CanTxInfoBak;
CAN_MAIN_FLAG CanMainFlag;
CAN_MAIN_STATE CanMainState;

u32 CANMainTimer;
u32 CANNoDataTimer;
u32 CANTxTimer;
u32 CANCheckErrorTimer;

u8 HVACSwitch;

u8 CCMReceived;

u8 fTMUReceived;
u16 TMUReceivedTimer;
u8 fCCMReceived;
u16 CCMReceivedTimer;

u8 dateRequested;
u32 CANDateReqTimer;
u32 CAN_TimerData;

u8 vehicleInfoRequested;
u32 CANVehicleInfoReqTimer;

u16 CANDiagnosticTimer;

RTC_DATE_TIME_TYPE_DEF CANTime;

u16 adcv;

u8 panelKeyPressed;
u16 timerPressed;

u8 temperatureVaild;
u8 ACMemory;

u8 test1[] = {0x10, 0x0b, 0x00, 0x02, 0xff, 0x7a, 0xff, 0x00};
u8 test2[] = {0x01, 0x43, 0x4b, 0x35, 0x30, 0x34, 0x30, 0x43};
u8 test3[] = {0x02, 0x48, 0x2d, 0x45, 0x55, 0xff, 0x30, 0x43};
#define NEW_TC250 1
void TC250_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	if (!Get_ACC_Det_Flag)
	{
		return;
	}

	u8 data[8] = {0};

	switch (index)
	{
	case CAN_POST_MSG_HVAC:
		data[0] = CanTxInfo.hvac_info.temperature;
		data[1] = CanTxInfo.hvac_info.byte_1.byte;
		// 		data[2] = CanTxInfo.hvac_info.airDistribution;
		// 		data[3] = CanTxInfo.hvac_info.ac;
		// #if NEW_TC250 == 1
		// 		data[4] = CanTxInfo.hvac_info.HVACControlCommand;
		// #endif
		CAN1_Ext_TxFrame(CAN_ID_HVAC, data, 8);
		break;
	// case CAN_POST_MSG_SSC:
	// 	data[0] = CanTxInfo.ssc_info.acc_ign;
	// 	data[1] = CanTxInfo.ssc_info.dimming;
	// 	CAN1_Ext_TxFrame(CAN_ID_SSC, data, 8);
	// 	break;
	case CAN_POST_MSG_DATE_REQ:
		data[0] = 0x89;
		data[1] = 0xff;
		CAN1_Ext_TxFrame(CAN_ID_DATE_REQ, data, 8);
		break;
	case CAN_POST_MSG_VEHICLE_INFO_REQ:
		data[0] = 0x7a;
		data[1] = 0xff;
		CAN1_Ext_TxFrame(CAN_ID_VEHICLE_INFO_REQ, data, 8);
		break;
	default:
		break;
	}
}

void TC250_Rx_Message(void)
{
	if (CanRxBuffer.head != CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message = CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID = 0;
		CanRxBuffer.head = (CanRxBuffer.head + 1) % CAN_RX_BUFFER_LENGTH;

		switch (message.ID)
		{
		case CAN_ID_CCM:
			temperatureVaild |= 0x01;
			CanRxInfo.ccm_info.ac = message.Data[0] & 0x01;
			CanRxInfo.ccm_info.fanSpeed = message.Data[0] >> 1 & 0x07;
			CanRxInfo.ccm_info.airDistribution = message.Data[0] >> 4 & 0x03;
			CanRxInfo.ccm_info.indoorTemperature = message.Data[1];
			CanRxInfo.ccm_info.settingTemperature = message.Data[2];
			// CanRxInfo.ccm_info.HAVCOn = message.Data[1] >> 7;
			// if (!strcmp_equal(&CanRxInfo.ccm_info.ac, &CanRxInfoBak.ccm_info.ac, sizeof(CAN_CCM_INFO)))
			if (CanRxInfo.ccm_info.indoorTemperature != CanRxInfoBak.ccm_info.indoorTemperature)
			{
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
				CanRxInfoBak.ccm_info.indoorTemperature = CanRxInfo.ccm_info.indoorTemperature;
			}
			// 	//				CCMReceived = 1;
			// 	if (CanRxInfo.ccm_info.fanSpeed == 0)
			// 	{
			// 		HVACSwitch = 0;
			// 	}
			// 	else
			// 	{
			// 		HVACSwitch = 1;
			// 	}
			// 	// if (APP_Status == APP_READY)
			// 	// {
			// 	// 	PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
			// 	// 	// if (!strcmp_equal(&CanRxInfo.ccm_info.ac, &CanRxInfoBak.ccm_info.ac, 4))
			// 	// 	// {
			// 	// 	// 	PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_PANEL_PRESSED);
			// 	// 	// }
			// 	// }
			// 	Mem_strcpy(&CanRxInfoBak.ccm_info.ac, &CanRxInfo.ccm_info.ac, sizeof(CAN_CCM_INFO));
			// }
			if (CanTxInfo.hvac_info.byte_1.field.HVACControlCommand == 1 && CanTxInfo.hvac_info.byte_1.field.ac == CanRxInfo.ccm_info.ac && CanTxInfo.hvac_info.byte_1.field.fanSpeed == CanRxInfo.ccm_info.fanSpeed && CanTxInfo.hvac_info.byte_1.field.airDistribution == CanRxInfo.ccm_info.airDistribution && CanTxInfo.hvac_info.temperature == CanRxInfo.ccm_info.settingTemperature)
			{
				CanTxInfo.hvac_info.byte_1.field.HVACControlCommand = 0;
			}
			else if (CanTxInfo.hvac_info.byte_1.field.HVACControlCommand == 0)
			{
#if NEW_TC250 == 1
				CanTxInfo.hvac_info.temperature = CanRxInfo.ccm_info.settingTemperature;
#endif
				CanTxInfo.hvac_info.byte_1.field.fanSpeed = CanRxInfo.ccm_info.fanSpeed;
				CanTxInfo.hvac_info.byte_1.field.airDistribution = CanRxInfo.ccm_info.airDistribution;
				CanTxInfo.hvac_info.byte_1.field.ac = CanRxInfo.ccm_info.ac;
				if (!strcmp_equal(&CanTxInfo.hvac_info.temperature, &CanTxInfoBak.hvac_info.temperature, sizeof(CAN_HVAC_INFO)))
				{
					Mem_strcpy(&CanTxInfoBak.hvac_info.temperature, &CanTxInfo.hvac_info.temperature, sizeof(CAN_HVAC_INFO));
					PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
				}
				if (CanRxInfo.ccm_info.fanSpeed == 0)
				{
					HVACSwitch = 0;
				}
				else
				{
					HVACSwitch = 1;
				}
			}
			CCMReceivedTimer = T2S_1;
			if (!fCCMReceived)
			{
				fCCMReceived = 1;
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_DIAGNOSTIC);
			}
			break;
		case CAN_ID_INFO2:
			temperatureVaild |= 0x02;
			CanRxInfo.ccm_info.outdoorTemperatureL = message.Data[3];
			CanRxInfo.ccm_info.outdoorTemperatureH = message.Data[4];
			// if (!strcmp_equal(&CanRxInfo.ccm_info.ac, &CanRxInfoBak.ccm_info.ac, sizeof(CAN_CCM_INFO)))
			if (!strcmp_equal(&CanRxInfo.ccm_info.outdoorTemperatureL, &CanRxInfoBak.ccm_info.outdoorTemperatureL, sizeof(u8) * 2))
			{
				Mem_strcpy(&CanRxInfoBak.ccm_info.ac, &CanRxInfo.ccm_info.ac, sizeof(CAN_CCM_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
			}
//			CanRxInfo.time_info.second = message.Data[0];
//			CanRxInfo.time_info.minute = message.Data[1];
//			CanRxInfo.time_info.hour = message.Data[2];

//			if (!strcmp_equal(&CanRxInfo.time_info.second, &RTC_TimeInfo.seconds, sizeof(CAN_TIME)))
//			{
//				Mem_strcpy(&RTC_TimeInfo.seconds, &CanRxInfo.time_info.second, sizeof(CAN_TIME));

//				PostMessage(NAVI_MODULE, MCU_TX_CLOCK, 0);
//			}
#if NEW_TC250 != 1
			CANTime.seconds = message.Data[0];
			CANTime.minutes = message.Data[1];
			CANTime.hours = message.Data[2];
			if (CANTime.seconds > 59 || CANTime.minutes > 59 || CANTime.hours > 23 ||
				CANTime.day > 31 || CANTime.day == 0 || CANTime.month > 12 || CANTime.month == 0 ||
				CANTime.year > 99 || CANTime.year == 0 || CANTime.week_day > 6)
			{
				dateRequested = 0;
				break;
			}
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_TIME_INFO);
#endif
			//			if (CANTime.seconds > 59 || CANTime.minutes > 59 || CANTime.hours > 23 ||
			//				CANTime.day > 31 || CANTime.day == 0 || CANTime.month > 12 || CANTime.month == 0 ||
			//				CANTime.year > 99 || CANTime.year == 0 || CANTime.week_day > 6)
			//			{
			//				dateRequested = 0;
			//				break;
			//			}
			//			RTC_SetTime(CANTime);
			//			if (APP_Status == APP_READY)
			//			{
			//				PostMessage(NAVI_MODULE, MCU_TX_CLOCK, 0);
			//			}
			TMUReceivedTimer = T2S_1;
			if (!fTMUReceived)
			{
				fTMUReceived = 1;
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_DIAGNOSTIC);
			}
			break;
		case CAN_ID_DATE:
			dateRequested = 1;
#if NEW_TC250 == 1
			CANTime.seconds = message.Data[0];
			CANTime.minutes = message.Data[1];
			CANTime.hours = message.Data[2];
#endif
			CANTime.day = message.Data[4];
			CANTime.month = message.Data[5];
			CANTime.year = message.Data[6];
			if (CANTime.seconds > 59 || CANTime.minutes > 59 || CANTime.hours > 23 ||
				CANTime.day > 31 || CANTime.day == 0 || CANTime.month > 12 || CANTime.month == 0 ||
				CANTime.year > 99 || CANTime.week_day > 6)
			{
				dateRequested = 0;
				break;
			}
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_TIME_INFO);
			//			RTC_SetTime(CANTime);
			//			PostMessage(NAVI_MODULE, MCU_TX_CLOCK, 0);
			TMUReceivedTimer = T5S_1;
			if (!fTMUReceived)
			{
				fTMUReceived = 1;
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_DIAGNOSTIC);
			}
			break;
			//		case CAN_ID_ET1:
			//			clusterReceived = 1;
			//			break;
		case CAN_ID_VEHICLE_INFO:
			if (message.Data[0] == 0x10)
			{
				CanRxInfo.vehicel_info.length = message.Data[1];
				memset(CanRxInfo.vehicel_info.data, 0, sizeof(CanRxInfo.vehicel_info.data));
				vehicleInfoRequested = 0;
				CANVehicleInfoReqTimer = T5S_1;
			}
			else if (message.Data[0] <= 3)
			{
				Mem_strcpy(&CanRxInfo.vehicel_info.data[7 * (message.Data[0] - 1)], &message.Data[1], 7);
			}
			if (CanRxInfo.vehicel_info.data[CanRxInfo.vehicel_info.length - 1] && CanRxInfo.vehicel_info.data[1] == 'K')
			{
				if (CanRxInfo.vehicel_info.data[0] == 'L')
				{
					CanRxInfo.vehicel_info.region = 23;
					vehicleInfoRequested = 1;
				}
				else if (CanRxInfo.vehicel_info.data[0] == 'C')
				{
					if (CanRxInfo.vehicel_info.data[CanRxInfo.vehicel_info.length - 2] == 'E' && CanRxInfo.vehicel_info.data[CanRxInfo.vehicel_info.length - 1] == 'U')
					{
						CanRxInfo.vehicel_info.region = 17;
						vehicleInfoRequested = 1;
					}
					else
					{
						CanRxInfo.vehicel_info.region = 0;
						vehicleInfoRequested = 1;
					}
				}
				if (vehicleInfoRequested)
				{
					PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
				}
			}
			break;
		default:
			break;
		}
		F_CAN_RX_DATA = 1;
		F_CAN_SLEEP = 0;
		CANNoDataTimer = T3S_1; // T60S_1;
	}
}

void TC250_RxAppDataPro(u8 *buffer)
{

	u8 cmd_id;
	cmd_id = buffer[1];

	// if (Get_ACC_Det_Flag == 0 || fCCMReceived == 0)
	// {
	// 	return;
	// }

	switch (cmd_id)
	{
	case TC250_TX_HVAC_CMD:
		//		if (CCMReceivedTimer <= T1S5_1)
		//		{
		//			return;
		//		}
		switch (buffer[3])
		{
		case HVAC_TEMPERATURE:
			if (buffer[4] >= 16 && buffer[4] <= 32)
			{
				CanTxInfo.hvac_info.temperature = buffer[4] + 40;
			}
			// TC250_PostMessage(CAN_POST_MSG_HVAC);
			break;
		case HVAC_FAN_SPEED:
			if (buffer[4] >= 0 && buffer[4] <= 5)
			{
				if (CanTxInfo.hvac_info.byte_1.field.fanSpeed == 0 && buffer[4] > 0)
				{
					if (ACMemory)
					{
						CanTxInfo.hvac_info.byte_1.field.ac = ACMemory;
					}
				}
				CanTxInfo.hvac_info.byte_1.field.fanSpeed = buffer[4];
				// fanSpeedMemory = CanTxInfo.hvac_info.byte_1.field.fanSpeed;
				if (CanTxInfo.hvac_info.byte_1.field.fanSpeed == 0)
				{
					CanTxInfo.hvac_info.byte_1.field.ac = 0;
				}
			}
			// TC250_PostMessage(CAN_POST_MSG_HVAC);
			break;
		case HVAC_AIR_DISTRIBUTION:
			if (buffer[4] >= 0 && buffer[4] <= 2)
			{
				CanTxInfo.hvac_info.byte_1.field.airDistribution = buffer[4];
			}
			//			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
			break;
		case HVAC_AC:
			if (buffer[4] <= 1)
			{
				CanTxInfo.hvac_info.byte_1.field.ac = buffer[4];
				ACMemory = CanTxInfo.hvac_info.byte_1.field.ac;
				if (CanTxInfo.hvac_info.byte_1.field.ac && CanTxInfo.hvac_info.byte_1.field.fanSpeed == 0)
				{
					CanTxInfo.hvac_info.byte_1.field.fanSpeed = 1;
				}
			}
			// TC250_PostMessage(CAN_POST_MSG_HVAC);
			break;
		default:
			break;
		}
		CanTxInfo.hvac_info.byte_1.field.HVACControlCommand = 1;
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
		break;
	case TC250_TX_REQ_CMD:
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
		//		PostMessage(NAVI_MODULE, MCU_TX_CLOCK, 0);
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_DIAGNOSTIC);

		dateRequested = 0;
		TC250_PostMessage(CAN_POST_MSG_DATE_REQ);
		break;
	default:
		break;
	}
}

void TC250_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length)
{
	u8 i;
	u8 checksum = 0;
	u32 flag = 1;

	switch (cmd_id)
	{
	case TC250_RX_CCM_INFO:
		buffer[2] = 0x08;
		// buffer[3] = CanRxInfo.ccm_info.ac;
		// buffer[4] = CanRxInfo.ccm_info.fanSpeed;
		// buffer[5] = CanRxInfo.ccm_info.airDistribution;
		buffer[3] = CanTxInfo.hvac_info.byte_1.field.ac;
		buffer[4] = CanTxInfo.hvac_info.byte_1.field.fanSpeed;
		buffer[5] = CanTxInfo.hvac_info.byte_1.field.airDistribution;
		buffer[6] = CanRxInfo.ccm_info.indoorTemperature;
		if (CanRxInfo.vehicel_info.region == 0 && (CanRxInfo.ccm_info.outdoorTemperatureH & 0x10) == 0)
		{

			float odt = (CanRxInfo.ccm_info.outdoorTemperatureH << 8 | CanRxInfo.ccm_info.outdoorTemperatureL) * 0.1 - 76;
			odt = 32 + odt * 1.8;
			odt = (odt + 76) * 10;
			if (odt < 0)
			{
				buffer[7] = 0x00;
				buffer[8] = 0x10;
			}
			else
			{
				buffer[7] = odt;
				buffer[8] = ((u32)odt >> 8 & 0x0f) | 0x10;
			}
		}
		else
		{
			buffer[7] = CanRxInfo.ccm_info.outdoorTemperatureL;
			buffer[8] = CanRxInfo.ccm_info.outdoorTemperatureH;
		}
		// #if NEW_TC250 == 1
		// 		buffer[9] = CanRxInfo.ccm_info.settingTemperature;
		// #else
		buffer[9] = CanTxInfo.hvac_info.temperature;
		buffer[10] = temperatureVaild;
		// #endif
		break;
	case TC250_PANEL_PRESSED:
		buffer[2] = 0x00;
		break;
	case TC250_DIAGNOSTIC:
		buffer[2] = 0x04;
		adcv = Get_Adc(ADCH_BATTERY_VOLT_DET) * 33 * 6 / 4095;
		buffer[3] = adcv;
		buffer[4] = CAN_StatusGet(CanBusoff);
		buffer[5] = fCCMReceived & fTMUReceived;
		//		if (Reg_Buffer[17].value == 0x00)
		//		{
		//			buffer[6] = 0x01;
		//		}
		//		else
		//		{
		//			buffer[6] = 0x00;
		//		}
		break;
	case TC250_RX_TIME_INFO:
		buffer[2] = 0x04;
		CAN_TimerData = RTC_ConvertTime(CANTime);
		buffer[3] = (CAN_TimerData & 0xFF000000) >> 24;
		buffer[4] = (CAN_TimerData & 0x00FF0000) >> 16;
		buffer[5] = (CAN_TimerData & 0x0000FF00) >> 8;
		buffer[6] = CAN_TimerData & 0x000000FF;
		break;
	case TC250_BEEP:
		buffer[2] = 0;
		break;
	default:
		flag = 0;
		break;
	}
	if (flag)
	{
		buffer[0] = TC250_HEAD_CODE;
		buffer[1] = cmd_id;
		*length = buffer[2] + 4;
		for (i = 0; i < (buffer[2] + 2); i++)
		{
			checksum += buffer[i + 1];
		}
		buffer[i + 1] = checksum;
	}
	else
	{
		*length = 0;
	}
}

void TC250_Panel_HVAC_Ctrl(u8 cmd, u8 keyvalue)
{
	// if (!fCCMReceived)
	// {
	// 	return;
	// }

	if (keyvalue == 0)
	{
		panelKeyPressed = 0;
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_BEEP);
		if (cmd != UICC_0)
		{
			return;
		}
	}
	else if (keyvalue == 0x40 && (panelKeyPressed == 0 || panelKeyPressed == cmd))
	{
		panelKeyPressed = cmd;
		timerPressed = T300MS_1;
	}
	switch (cmd)
	{
	case UICC_0:
		CanTxInfo.hvac_info.byte_1.field.ac ^= 1;
		ACMemory = CanTxInfo.hvac_info.byte_1.field.ac;
		if (CanTxInfo.hvac_info.byte_1.field.fanSpeed == 0 && CanTxInfo.hvac_info.byte_1.field.ac)
		{
			CanTxInfo.hvac_info.byte_1.field.fanSpeed = 1;
			HVACSwitch = 1;
		}
		break;
	case UICC_1:
		//		if (!HVACSwitch)
		//		{
		//			return;
		//		}
		if (CanTxInfo.hvac_info.temperature > 0x38)
		{
			CanTxInfo.hvac_info.temperature--;
#if NEW_TC250 != 1
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_PANEL_PRESSED);
#endif
		}
		break;
	case UICC_2:
		//		if (!HVACSwitch)
		//		{
		//			return;
		//		}
		if (CanTxInfo.hvac_info.temperature < 0x48)
		{
			CanTxInfo.hvac_info.temperature++;
#if NEW_TC250 != 1
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_PANEL_PRESSED);
#endif
		}
		break;
	case UICC_3:
		//		if (!HVACSwitch)
		//		{
		//			HVACSwitch = 1;
		//			if (CanTxInfo.hvac_info.fanSpeed == 0)
		//			{
		//				CanTxInfo.hvac_info.fanSpeed = 1;
		//			}
		//		}
		//		else
		if (CanTxInfo.hvac_info.byte_1.field.fanSpeed > 0)
		{
			// fanSpeedMemory = CanTxInfo.hvac_info.byte_1.field.fanSpeed;
			CanTxInfo.hvac_info.byte_1.field.fanSpeed--;
			if (CanTxInfo.hvac_info.byte_1.field.fanSpeed == 0)
			{
				CanTxInfo.hvac_info.byte_1.field.ac = 0;
			}
		}
		break;
	case UICC_4:
		if (CanTxInfo.hvac_info.byte_1.field.fanSpeed < 5)
		{
			if (CanTxInfo.hvac_info.byte_1.field.fanSpeed == 0)
			{
				if (ACMemory)
				{
					CanTxInfo.hvac_info.byte_1.field.ac = ACMemory;
				}
			}
			CanTxInfo.hvac_info.byte_1.field.fanSpeed++;
		}
		break;
		//	case UICC_6:
		//		CanTxInfo.hvac_info.airDistribution = (CanTxInfo.hvac_info.airDistribution + 1) % 2;
		//		break;
		//	case UICC_7:
		//		break;
	}
	//	if (APP_Status == APP_READY)
	//	{
	//		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
	//		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_PANEL_PRESSED);
	//	}
	// TC250_PostMessage(CAN_POST_MSG_HVAC);
	// if (TX_flag == 1)
	{
		CanTxInfo.hvac_info.byte_1.field.HVACControlCommand = 1;
		if (APP_Status == APP_READY)
		{
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_RX_CCM_INFO);
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_PANEL_PRESSED);
		}
	}
}
u8 sendtest;
void TC250_MainPro(void)
{
	if (CANMainTimer)
	{
		CANMainTimer--;
	}
	if (CANTxTimer)
	{
		CANTxTimer--;
	}
	if (CANDateReqTimer)
	{
		CANDateReqTimer--;
	}
	if (CANDiagnosticTimer)
	{
		CANDiagnosticTimer--;
	}
	if (TMUReceivedTimer)
	{
		TMUReceivedTimer--;
		if (!TMUReceivedTimer)
		{
			fTMUReceived = 0;
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_DIAGNOSTIC);
		}
	}
	if (CCMReceivedTimer)
	{
		CCMReceivedTimer--;
		if (!CCMReceivedTimer)
		{
			temperatureVaild &= 0xfe;
			fCCMReceived = 0;
			CanTxInfo.hvac_info.byte_1.field.HVACControlCommand = 1;
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_DIAGNOSTIC);
		}
	}
	if (timerPressed)
	{
		timerPressed--;
	}
	if (CANVehicleInfoReqTimer)
	{
		CANVehicleInfoReqTimer--;
	}
#if CAN_WAKEUP_FUN == 1
	if (CANNoDataTimer)
	{
		CANNoDataTimer--;
		if (CANNoDataTimer == 0)
		{
			F_CAN_RX_DATA = 0;
		}
	}
#endif
	//	if (fCCMReceivedPreviousStatus && !fCCMReceived)
	//	{
	//		fCCMReceivedPreviousStatus = fCCMReceived;
	//	}
	//	else if (!fCCMReceivedPreviousStatus && fCCMReceived)
	//	{
	//		fCCMReceivedPreviousStatus = fCCMReceived;
	//		CanTxInfo.hvac_info.byte_1.field.HVACControlCommand = 1;
	//		controlCommandTXTimer = 5;
	//	}
	if (sendtest)
	{
		sendtest = 0;

		//		CanRxBuffer.head = 0;
		//		CanRxBuffer.tail = 3;
		//		CanRxBuffer.message[0].ID = CAN_ID_VEHICLE_INFO;
		//		CanRxBuffer.message[1].ID = CAN_ID_VEHICLE_INFO;
		//		CanRxBuffer.message[2].ID = CAN_ID_VEHICLE_INFO;

		//		Mem_strcpy(&CanRxBuffer.message[0].Data[0], test1, 8);
		//		Mem_strcpy(&CanRxBuffer.message[1].Data[0], test2, 8);
		//		Mem_strcpy(&CanRxBuffer.message[2].Data[0], test3, 8);
	}
	TC250_Rx_Message();
	CAN1_Transmit();
	if (CanTxInfo.hvac_info.byte_1.field.ac)
	{
		AC_LED_ON;
//		if (F_LIGHTING_FLAG && PanelKeyLightState != KEY_LIGHT_CLOSED)
//		{
//			PanelKeyLightState = KEY_LIGHT_CLOSED;
//			KeyPwmConfig(PanelKeyLightState);
//		}
	}
	else
	{
		AC_LED_OFF;
	}
	switch (CanMainState)
	{
	case CAN_MAIN_IDLE:
		F_CAN_INIT = 0;
		CanMainState = CAN_MAIN_CFG;

		CanTxInfo.hvac_info.temperature = 0x3c;
		//		CanRxInfo.ccm_info.settingTemperature = 0x3c;

		CANTime.year = 26;
		CANTime.month = 1;
		CANTime.day = 1;
		CANTime.hours = 0;
		CANTime.minutes = 0;
		CANTime.seconds = 0;
		CANTime.week_day = 4;
#if CAN_DEBUG_FUN == 1
		printf("CAN_MAIN_IDLE\r\n");
#endif
		break;
	case CAN_MAIN_CFG:
		CAN1_Init();
		CanMainState = CAN_MAIN_INIT;
#if CAN_DEBUG_FUN == 1
		printf("CAN_MAIN_CFG\r\n");
#endif
		break;
	case CAN_MAIN_INIT:
		CAN1_Ext_ClearTxMessage();
		F_CAN_SLEEP = 0;
		F_CAN_RX_DATA = 1;
		F_CAN_INTERRUPT = 0;

		CanMainState = CAN_MAIN_NORMAL;
		CANNoDataTimer = T25S_1;
		CANTxTimer = 0;

		dateRequested = 0;

		CanTxInfo.hvac_info.byte_1.field.HVACControlCommand = 1;

//		HVACSwitch = 0;
//		CanRxInfo.ccm_info.ac = 0;
//		CanTxInfo.hvac_info.ac = 0;
// CCMReceived = 0;
#if CAN_DEBUG_FUN == 1
		printf("CAN_MAIN_INIT\r\n");
#endif
		break;
	case CAN_MAIN_NORMAL:
#if CAN_WAKEUP_FUN == 1
		if (F_CAN_RX_DATA == 0)
#else
		if (Get_ACC_Det_Flag == 0)
#endif
		{
			CanMainState = CAN_MAIN_SLEEP_CFG;
			CANMainTimer = T1S_1;
#if CAN_DEBUG_FUN == 1
			printf("CAN_MAIN_NORMAL:1\r\n");
#endif
		}
		else
		{
			if (CAN_StatusGet(CanBusoff) || CAN_RxErrorCntGet() >= 127 || CAN_TxErrorCntGet() >= 127 || M4_CAN->CFG_STAT_f.RESET)
			{
				CANCheckErrorTimer++;
				if (CANCheckErrorTimer >= T2S_1)
				{
					CANCheckErrorTimer = 0;
					CanMainState = CAN_MAIN_CFG;
				}
			}
			else
			{
				CANCheckErrorTimer = 0;
			}

			if (CANDateReqTimer == 0)
			{
				if (dateRequested)
				{
					CANDateReqTimer = T1800S_1;
					TC250_PostMessage(CAN_POST_MSG_DATE_REQ);
				}
				else
				{
					CANDateReqTimer = T2S_1;
					TC250_PostMessage(CAN_POST_MSG_DATE_REQ);
				}
			}
			if (CANVehicleInfoReqTimer == 0 && !vehicleInfoRequested)
			{
				CANVehicleInfoReqTimer = T2S_1;
				TC250_PostMessage(CAN_POST_MSG_VEHICLE_INFO_REQ);
			}
			if (APP_READY == APP_Status)
			{
				if (CANDiagnosticTimer == 0)
				{
					CANDiagnosticTimer = T5S_1;
					PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_DIAGNOSTIC);
				}
			}
			//			if (CCMReceived || HVACSwitch)
			{
				if (CANTxTimer == 0)
				{
					CANTxTimer = T100MS_1;
					TC250_PostMessage(CAN_POST_MSG_HVAC);
					//					PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, TC250_DIAGNOSTIC);
					// if (controlCommandTXTimer > 0 && controlCommandTXTimer < 0xff)
					// {
					// 	controlCommandTXTimer--;
					// }
					// if (CanTxInfo.hvac_info.byte_1.field.HVACControlCommand && controlCommandTXTimer == 0)
					// {
					// 	CanTxInfo.hvac_info.byte_1.field.HVACControlCommand = 0;
					// }
				}
			}
			if (timerPressed == 0 && panelKeyPressed)
			{
				TC250_Panel_HVAC_Ctrl(panelKeyPressed, 0x40);
			}
		}
		break;
	case CAN_MAIN_SLEEP_CFG:
		if (Get_ACC_Det_Flag)
		{
			CanMainState = CAN_MAIN_NORMAL;
		}
		if (CANMainTimer)
		{
			break;
		}
		temperatureVaild = 0;
		CAN1_Ext_ClearRxMessage();
		CAN_IC_STANDBY_ON;
		F_CAN_SLEEP = 1;
		F_CAN_INTERRUPT = 0;
		CANMainTimer = T100MS_1;
		CanMainState = CAN_MAIN_SLEEP;
#if CAN_DEBUG_FUN == 1
		printf("CAN_MAIN_SLEEP_CFG\r\n");
#endif
		break;
	case CAN_MAIN_SLEEP:
		if (CANMainTimer)
		{
			break;
		}
#if CAN_WAKEUP_FUN == 1
		if (F_CAN_SLEEP == 0 || F_CAN_INTERRUPT)
#else
		if (Get_ACC_Det_Flag)
#endif
		{
			CAN_IC_STANDBY_OFF;
			F_CAN_SLEEP = 0;
			CanMainState = CAN_MAIN_CFG;
		}
#if CAN_DEBUG_FUN == 1
		printf("CAN_MAIN_SLEEP\r\n");
#endif
		break;
	default:
		break;
	}
}

#endif
