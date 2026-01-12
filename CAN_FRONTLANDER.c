#include "public.h"

#if CAN_FUN_FRONTLANDER == 1
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_TX_INFO CanTxInfo;
CAN_MAIN_FLAG CanMainFlag;
CAN_MAIN_STATE CanMainState;

u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanTxTimer;

u16 TurnSignalTimer;
u8 TurnSignal;

u16 SettingTxTimer;
u8 SettingTxCount;


void Frontlander_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	if (!Get_ACC_Det_Flag)
	{
		return;
	}

	u8 data[8] = {0};

	switch (index)
	{
//	case CAN_POST_MSG_525:
//		data[6] = CanTxInfo.setting_info.fuelConsumptionUnit;
//		CAN1_TxFrame(CAN_ID_525, data, 8);
//		break;
	case CAN_POST_MSG_6F9:
		data[2] = CanTxInfo.setting_info.setting_1.byte_2;
		data[3] = CanTxInfo.setting_info.setting_1.byte_3;
		data[4] = CanTxInfo.setting_info.setting_1.byte_4;
		CAN1_TxFrame(CAN_ID_6F9, data, 8);
		break;
//	case CAN_POST_MSG_315:
//		if (CanTxInfo.setting_info.timeFormat12H)
//		{
//			
//		}
//		else
//		{
//			data[0] = RTC_TimeInfo.hours;
//		}
//		data[1] = RTC_TimeInfo.minutes;
//		data[2] = RTC_TimeInfo.seconds * 4 + 1;
//		CAN1_TxFrame(CAN_ID_315, data, 8);
//		break;
	default:
		break;
	}
}

void Frontlander_PostMessage_2_times(CAN_POST_MESSAGE_INDEX index)
{
	Frontlander_PostMessage(index);
	Frontlander_PostMessage(index);
}

void Frontlander_Rx_Message(void)
{
	if (CanRxBuffer.head != CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message = CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID = 0;
		CanRxBuffer.head = (CanRxBuffer.head + 1) % CAN_RX_BUFFER_LENGTH;

		switch (message.ID)
		{
		case CAN_ID_2A1:
			if ((message.Data[4] & 0x07) == 0x01)
			{
				CanGeneralCtrlFlag.field.parking_on_off = 1;
				CanGeneralCtrlFlag.field.reverse_on_off = 0;
			}
			else if ((message.Data[4] & 0x07) == 0x02)
			{
				CanGeneralCtrlFlag.field.reverse_on_off = 1;
				CanGeneralCtrlFlag.field.parking_on_off = 0;
			}
			else
			{
				CanGeneralCtrlFlag.field.parking_on_off = 0;
				CanGeneralCtrlFlag.field.reverse_on_off = 0;
			}
			break;
		case CAN_ID_622:
			if (message.Data[3] >> 5 == 1)
			{
				CanGeneralCtrlFlag.field.ill_onoff = 1;
			}
			else
			{
				CanGeneralCtrlFlag.field.ill_onoff = 0;
			}
			break;
		case CAN_ID_2E5:
			if ((message.Data[3] & 0x30) == 0x10) //left
			{
				TurnSignal = 1;
			}
			else if ((message.Data[3] & 0x30) == 0x20) //right
			{
				TurnSignal = 2;
			}
			else
			{
				TurnSignal = 0;
			}
			break;
		case CAN_ID_610:
			CanRxInfo.base_info.speed = message.Data[3];
			CanRxInfo.base_info.fuelConsumption = message.Data[5] << 8 | message.Data[6];
			break;
		case CAN_ID_525:
			CanRxInfo.base_info.remainRange = message.Data[2] << 8 | message.Data[3];
			CanRxInfo.base_info.latestConsumption = message.Data[1] << 8 | message.Data[0];
			break;
		case CAN_ID_618:
			CanRxInfo.base_info.tripDistance = message.Data[5] << 8 | message.Data[6];
			break;
		case CAN_ID_63B:
			CanRxInfo.base_info.tripDuration = message.Data[4] << 24 | message.Data[5] << 16 | message.Data[6] << 8 | message.Data[7];
			break;
		default:
			break;
		}
		F_CAN_RX_DATA = 1;
		F_CAN_SLEEP = 0;
		CanNoDataTimer = T3S_1; // T60S_1;
	}
}

void Frontlander_RxAppDataPro(u8 *buffer)
{

	u8 cmd_id;
	cmd_id = buffer[1];

	if (Get_ACC_Det_Flag == 0)
	{
		return;
	}

	switch (cmd_id)
	{
	case FRONTLANDER_TX_SETTING_CMD:
		switch (buffer[3])
		{
		case SETTING_FUEL_CONSUMPTION_UNIT:
			CanTxInfo.setting_info.fuelConsumptionUnit = buffer[4] << 3 | 0xc4;
			Frontlander_PostMessage(CAN_POST_MSG_525);
			break;
		case SETTING_LANGUAGE:
			CanTxInfo.setting_info.language = buffer[4] << 2 | 0x01;
			Frontlander_PostMessage(CAN_POST_MSG_3E0);
		case SETTING_DOORLOCK_FEEDBACK_LIGHT:
			CanTxInfo.setting_info.setting_1.byte_2 = 0x11;
			CanTxInfo.setting_info.setting_1.byte_3 = 0x0d;
			CanTxInfo.setting_info.setting_1.byte_4 = buffer[4];
			break;
		case SETTING_KEY_DOUBLE_UNLOCK:
			CanTxInfo.setting_info.setting_1.byte_2 = 0x11;
			CanTxInfo.setting_info.setting_1.byte_3 = 0x07;
			CanTxInfo.setting_info.setting_1.byte_4 = buffer[4];
			break;
		case SETTING_HRADLAMP_AUTO_ON_SENSITIVITY:
			CanTxInfo.setting_info.setting_1.byte_2 = 0x11;
			CanTxInfo.setting_info.setting_1.byte_3 = 0x40;
			CanTxInfo.setting_info.setting_1.byte_4 = buffer[4];
			break;
		case SETTING_INTER_LIGHT_AUTO_OFF_TIMER:
			CanTxInfo.setting_info.setting_1.byte_2 = 0x11;
			CanTxInfo.setting_info.setting_1.byte_3 = 0x43;
			CanTxInfo.setting_info.setting_1.byte_4 = buffer[4];
			break;
		case SETTING_SMART_REMINDER:
			CanTxInfo.setting_info.setting_1.byte_2 = 0x12;
			CanTxInfo.setting_info.setting_1.byte_3 = 0x50;
			CanTxInfo.setting_info.setting_1.byte_4 = buffer[4];
			break;
		case SETTING_TIME_FORMAT:
			CanTxInfo.setting_info.timeFormat12H = buffer[4];
			break;
		default:
			break;
		}
		if (buffer[3] >= SETTING_DOORLOCK_FEEDBACK_LIGHT && buffer[3] <= SETTING_SMART_REMINDER)
		{
			Frontlander_PostMessage_2_times(CAN_POST_MSG_6F9);
			memset(&CanTxInfo.setting_info.setting_1.byte_2, 0x00, 3);
			// Frontlander_PostMessage_2_times(CAN_POST_MSG_6F9);
			// SettingTxCount += 3;
		}
		break;

		break;
	default:
		break;
	}
}

 void Frontlander_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length)
 {
 	u8 i;
 	u8 checksum = 0;
 	u32 flag = 1;

 	switch (cmd_id)
 	{
 	case FRONTLANDER_RX_BASE_INFO:
 		buffer[2] = 0x0d;
//		buffer[3] = CanRxInfo.base_info.speed;
// 		buffer[4] = CanRxInfo.base_info.fuelConsumption >> 8;
// 		buffer[5] = CanRxInfo.base_info.fuelConsumption & 0xff;
// 		buffer[6] = CanRxInfo.base_info.remainRange >> 8;
// 		buffer[7] = CanRxInfo.base_info.remainRange & 0xff;
// 		buffer[8] = CanRxInfo.base_info.tripDistance >> 8;
// 		buffer[9] = CanRxInfo.base_info.tripDistance & 0xff;
// 		buffer[10] = CanRxInfo.base_info.tripDuration >> 24;
//		buffer[11] = CanRxInfo.base_info.tripDuration >> 16;
//		buffer[12] = CanRxInfo.base_info.tripDuration >> 8;
//		buffer[13] = CanRxInfo.base_info.tripDuration & 0xff;
//		buffer[14] = CanRxInfo.base_info.latestConsumption >> 8;
//		buffer[15] = CanRxInfo.base_info.latestConsumption;
		memset(&buffer[3], 0x11, 13);
 		break;
 	default:
 		flag = 0;
 		break;
 	}
 	if (flag)
 	{
 		buffer[0] = FRONTLANDER_HEAD_CODE;
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

void Frontlander_MainPro(void)
{
	if (CanMainTimer)
	{
		CanMainTimer--;
	}
	if (CanTxTimer)
	{
		CanTxTimer--;
	}

#if CAN_WAKEUP_FUN == 1
	if (CanNoDataTimer)
	{
		CanNoDataTimer--;
		if (CanNoDataTimer == 0)
		{
			F_CAN_RX_DATA = 0;
		}
	}
#endif

	Frontlander_Rx_Message();
	CAN1_Transmit();
	switch (CanMainState)
	{
	case CAN_MAIN_IDLE:
		F_CAN_INIT = 0;
		CanMainState = CAN_MAIN_CFG;
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
		CanNoDataTimer = T25S_1;
		CanTxTimer = 0;

//		HAVCSwitch = 0;
//		CanRxInfo.ccm_info.ac = 0;
//		CanTxInfo.havc_info.ac = 0;
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
#if CAN_DEBUG_FUN == 1
			printf("CAN_MAIN_NORMAL:1\r\n");
#endif
		}
		else
		{
			//			if (APP_READY == APP_Status)
			//			if (CCMReceived || HAVCSwitch)
			//			{
			if (CanTxTimer == 0)
			{
				CanTxTimer = T1S_1;
				Frontlander_PostMessage(CAN_POST_MSG_525);
				Frontlander_PostMessage(CAN_POST_MSG_6F9);
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, FRONTLANDER_RX_BASE_INFO);
			}
			//			}
		}
		break;
	case CAN_MAIN_SLEEP_CFG:
		CAN1_Ext_ClearRxMessage();
		CAN_IC_1_STANDBY_ON;
		F_CAN_SLEEP = 1;
		F_CAN_INTERRUPT = 0;
		CanMainTimer = T100MS_1;
		CanMainState = CAN_MAIN_SLEEP;
#if CAN_DEBUG_FUN == 1
		printf("CAN_MAIN_SLEEP_CFG\r\n");
#endif
		break;
	case CAN_MAIN_SLEEP:
		if (CanMainTimer)
		{
			break;
		}
#if CAN_WAKEUP_FUN == 1
		if (F_CAN_SLEEP == 0 || F_CAN_INTERRUPT)
#else
		if (Get_ACC_Det_Flag)
#endif
		{
			CAN_IC_1_STANDBY_OFF;
			F_CAN_SLEEP = 0;
			CanMainState = CAN_MAIN_INIT;
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
