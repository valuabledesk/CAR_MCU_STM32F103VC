#include "public.h"

#if CAN_FUN_MAHINDRA_SCORPIO11 == 1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_TX_INFO CanTxInfo;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanCheckErrorTimer;

u16 CanTxTimer;
u8 CanTxErrorCounter;
u8 CanNoTxCounter;
u8 CAN_TURN_STATE;

#if TEST_CAN_FUN == 1
u32 CanTestTimer;
int test_time;
int test;
#endif

void Mahindra_SCORPIO11_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8] = {0};

	switch (index)
	{
	case CAN_POST_MSG_IS_3:
		data[0] = RTC_TimeInfo.year;
		data[1] = RTC_TimeInfo.month | 0x10;
		data[2] = RTC_TimeInfo.day;
		data[3] = RTC_TimeInfo.hours;
		data[4] = RTC_TimeInfo.minutes;
		CAN1_TxFrame(CAN_ID_IS_3, data, 8);
		break;
	case CAN_POST_MSG_IS_4:
		data[0] = CanTxInfo.is_4_info.byte_0.byte & 0x64;
		data[1] = CanTxInfo.is_4_info.byte_1.byte & 0x64;
	default:
		break;
	}
}

void Mahindra_SCORPIO11_Rx_Message(void)
{
	if (CanRxBuffer.head != CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message = CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID = 0;
		CanRxBuffer.head = (CanRxBuffer.head + 1) % CAN_RX_BUFFER_LENGTH;

		switch (message.ID)
		{
		case CAN_ID_EMS_1:
			// if (message.Data[5]&0x0F == 0x07)
			// {
			// 	CanGeneralCtrlFlag.field.reverse_on_off = 1;
			// }
			break;
		case CAN_ID_MBFM_1:
			CanGeneralCtrlFlag.field.reverse_on_off = (message.Data[4] & 0x80) >> 7;
			CanGeneralCtrlFlag.field.parking_on_off = (message.Data[0] & 0x04) >> 2;
			CanRxInfo.fatc_info.ambt_temp = message.Data[7];
			CanRxInfo.base_info.byte_0.field.f_door = message.Data[4] & 0x3F;
			CanRxInfo.base_info.byte_1.byte = message.Data[6];
			break;
		case CAN_ID_FATC_1:
			CanRxInfo.fatc_info.byte_0.field.mode = message.Data[2] & 0x07;
			CanRxInfo.fatc_info.byte_0.field.blower = (message.Data[2] & 0xF0) >> 4;
			CanRxInfo.fatc_info.byte_0.field.f_auto = message.Data[5] & 0x01;
			CanRxInfo.fatc_info.drv_temp = message.Data[3];
			CanRxInfo.fatc_info.psg_temp = message.Data[4];
			CanRxInfo.fatc_info.byte_3.field.dual = (message.Data[5] & 0x04) >> 2;
			CanRxInfo.fatc_info.byte_3.field.econ = (message.Data[5] & 0x10) >> 4;
			CanRxInfo.fatc_info.byte_3.field.ac = (message.Data[6] & 0x02) >> 1;
			CanRxInfo.fatc_info.byte_3.field.r_ac = (message.Data[6] & 0x08) >> 3;
			CanRxInfo.fatc_info.byte_3.field.cycle = (message.Data[6] & 0x40) >> 6;
			if ((message.Data[7] & 0x03) == 0 || (message.Data[7] & 0x03) == 2)
			{
				CanRxInfo.fatc_info.byte_3.field.on_off = 0;
			}
			else if ((message.Data[7] & 0x03) == 1)
			{
				CanRxInfo.fatc_info.byte_3.field.on_off = 1;
			}
			if (!strcmp_equal(&CanRxInfo.fatc_info.byte_0.byte, &CanRxInfoBak.fatc_info.byte_0.byte, sizeof(CAN_FATC_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.fatc_info.byte_0.byte, &CanRxInfo.fatc_info.byte_0.byte, sizeof(CAN_FATC_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, MAHINDRA_SCORPIO11_RX_FATC_INFO);
			}
			break;
		case CAN_ID_MBFM_5:
			CanRxInfo.tpms_info.tpms_learnt = message.Data[0] & 0x1F;
			CanRxInfo.tpms_info.byte_1.byte = message.Data[1];
			CanRxInfo.tpms_info.high_pres_alert = (message.Data[4] & 0x7E) >> 1;
			CanRxInfo.tpms_info.byte_3.byte = message.Data[3];
			CanRxInfo.tpms_info.high_temp_alert = message.Data[2] & 0x1F;
			CanRxInfo.tpms_info.leakage_alert = message.Data[5] & 0x1F;
			CanRxInfo.tpms_info.tpme_system_fault = message.Data[6] & 0x1F;
			break;
		case CAN_ID_MBFM_6:
			CanRxInfo.tpms_info.fl_pres = message.Data[0];
			CanRxInfo.tpms_info.fl_temp = message.Data[4];
			CanRxInfo.tpms_info.fr_pres = message.Data[1];
			CanRxInfo.tpms_info.fr_temp = message.Data[5];
			CanRxInfo.tpms_info.rl_pres = message.Data[2];
			CanRxInfo.tpms_info.rl_temp = message.Data[6];
			CanRxInfo.tpms_info.rr_pres = message.Data[3];
			CanRxInfo.tpms_info.rr_temp = message.Data[7];
			if (!strcmp_equal(&CanRxInfo.tpms_info.tpms_learnt, &CanRxInfoBak.tpms_info.tpms_learnt, sizeof(CAN_TPMS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.tpms_info.tpms_learnt, &CanRxInfo.tpms_info.tpms_learnt, sizeof(CAN_TPMS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, MAHINDRA_SCORPIO11_RX_TPMS_INFO);
			}
			break;
		case CAN_ID_MBFM_7:
			CanRxInfo.tpms_info.spare_pres = message.Data[5];
			CanRxInfo.tpms_info.spare_temp = message.Data[6];
			CanRxInfo.base_info.byte_0.byte |= (message.Data[0] & 0x03) << 6;
			CanTxInfo.is_4_info.byte_0.field.auto_lamp = message.Data[0] & 0x01;
			CanTxInfo.is_4_info.byte_1.field.auto_rain = (message.Data[0] & 0x02) >> 1;
			break;
		case CAN_ID_RPAS_1:
			CanRxInfo.base_info.byte_2.field.bar_left = (message.Data[2] & 0xF0) >> 4;
			CanRxInfo.base_info.byte_2.field.bar_right = (message.Data[3] & 0xF0) >> 4;
			if (!strcmp_equal(&CanRxInfo.base_info.byte_0.byte, &CanRxInfoBak.base_info.byte_0.byte, sizeof(CAN_BASE_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.base_info.byte_0.byte, &CanRxInfo.base_info.byte_0.byte, sizeof(CAN_BASE_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, MAHINDRA_SCORPIO11_RX_BASE_INFO);
			}
			break;
		default:
			break;
		}
		// CanRxInfo.base_info.byte_0.field.f_can_ready = 1;
		if (F_CAN_RX_DATA == 0)
		{
			// PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, MAHINDRA_SCORPIO11_RX_BASIC_INFO);
		}
		F_CAN_RX_DATA = 1;
		F_CAN_SLEEP = 0;
		CanNoDataTimer = T30S_1;
		CAN1_ClearErrorTimer();
	}
}

void Mahindra_SCORPIO11_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id = buffer[1];

	if (Get_ACC_Det_Flag == 0)
	{
		return;
	}

	switch (cmd_id)
	{
	case MAHINDRA_SCORPIO11_TX_REQ_CMD:
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, MAHINDRA_SCORPIO11_RX_FATC_INFO);
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, MAHINDRA_SCORPIO11_RX_TPMS_INFO);
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, MAHINDRA_SCORPIO11_RX_BASE_INFO);
		break;
	case MAHINDRA_SCORPIO11_TX_BASE_CMD:
		switch (buffer[3])
		{
		case BASE_AUTO_LAMP:
			CanTxInfo.is_4_info.byte_0.field.auto_lamp = buffer[4];
			Mahindra_SCORPIO11_PostMessage(CAN_POST_MSG_IS_4);
			break;
		case BASE_AUTP_RAIN:
			CanTxInfo.is_4_info.byte_1.field.auto_rain = buffer[4];
			Mahindra_SCORPIO11_PostMessage(CAN_POST_MSG_IS_4);
			break;
		}
		break;
	default:
		break;
	}
}

void Mahindra_SCORPIO11_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length)
{
	u8 i;
	u8 checksum = 0;
	u8 flag = 1;

	switch (cmd_id)
	{
	case MAHINDRA_SCORPIO11_RX_FATC_INFO:
		buffer[2] = 0x05;
		buffer[3] = CanRxInfo.fatc_info.byte_0.byte;
		buffer[4] = CanRxInfo.fatc_info.drv_temp;
		buffer[5] = CanRxInfo.fatc_info.psg_temp;
		buffer[6] = CanRxInfo.fatc_info.byte_3.byte;
		buffer[7] = CanRxInfo.fatc_info.ambt_temp;
		break;
	case MAHINDRA_SCORPIO11_RX_TPMS_INFO:
		buffer[2] = 0x11;
		buffer[3] = CanRxInfo.tpms_info.tpms_learnt;
		buffer[4] = CanRxInfo.tpms_info.byte_1.byte;
		buffer[5] = CanRxInfo.tpms_info.high_pres_alert;
		buffer[6] = CanRxInfo.tpms_info.byte_3.byte;
		buffer[7] = CanRxInfo.tpms_info.high_temp_alert;
		buffer[8] = CanRxInfo.tpms_info.leakage_alert;
		buffer[9] = CanRxInfo.tpms_info.tpme_system_fault;
		buffer[10] = CanRxInfo.tpms_info.fl_pres;
		buffer[11] = CanRxInfo.tpms_info.fl_temp;
		buffer[12] = CanRxInfo.tpms_info.fr_pres;
		buffer[13] = CanRxInfo.tpms_info.fr_temp;
		buffer[14] = CanRxInfo.tpms_info.rl_pres;
		buffer[15] = CanRxInfo.tpms_info.rl_temp;
		buffer[16] = CanRxInfo.tpms_info.rr_pres;
		buffer[17] = CanRxInfo.tpms_info.rr_temp;
		buffer[18] = CanRxInfo.tpms_info.spare_pres;
		buffer[19] = CanRxInfo.tpms_info.spare_temp;
		break;
	case MAHINDRA_SCORPIO11_RX_BASE_INFO:
		buffer[2] = 0x03;
		buffer[3] = CanRxInfo.base_info.byte_0.byte;
		buffer[4] = CanRxInfo.base_info.byte_1.byte;
		buffer[5] = CanRxInfo.base_info.byte_2.byte;
		break;
	default:
		flag = 0;
		break;
	}
	if (flag)
	{
		buffer[0] = MAHINDRA_SCORPIO11_HEAD_CODE;
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

void Mahindra_SCORPIO11_CanReset(void)
{
	CanMainState = CAN_MAIN_IDLE;
}

void Mahindra_SCORPIO11_Timeout_Handler(void)
{
	F_CAN_RX_DATA = 0;
}

void Mahindra_SCORPIO11_MainPro(void)
{
	if (CanMainTimer)
	{
		CanMainTimer--;
	}

	if (CanNoDataTimer)
	{
		CanNoDataTimer--;
		if (CanNoDataTimer == 0)
		{
			Mahindra_SCORPIO11_Timeout_Handler();
		}
	}
	if (CanTxTimer)
	{
		CanTxTimer--;
	}
#if 0
	if (CanErrorTimer)
	{
		if (AppUpdating)
		{
			CanErrorTimer++;
		}
		CanErrorTimer--;
		if (CanErrorTimer == 0 && CAN1_GetErrorFlag() == 0)
		{
			CAN1_SetErrorFlag();
			CAN_IC_POWER_OFF;
			SystemReset();
		}
	}
#endif

	if (CanMainState == CAN_MAIN_NORMAL)
	{
#if MODEL==LINUX_1276_MG
		if(CAN_ErrorStatusGet())
#else
		if (CAN_GetFlagStatus(CAN1, CAN_FLAG_EWG) || CAN_GetFlagStatus(CAN1, CAN_FLAG_BOF) || CAN_GetReceiveErrorCounter(CAN1) >= 127 || CAN_GetLSBTransmitErrorCounter(CAN1) >= 127)
#endif
		{
			CanCheckErrorTimer++;
			if (CanCheckErrorTimer >= T2S_1)
			{
				CanCheckErrorTimer = 0;
				CanMainState = CAN_MAIN_IDLE;
				if (F_CAN_RX_DATA == 1)
					Mahindra_SCORPIO11_Timeout_Handler();
			}
		}
		else
		{
			CanCheckErrorTimer = 0;
		}
	}

	Mahindra_SCORPIO11_Rx_Message();
	if (F_CAN_INIT)
	{
		CAN1_Transmit();
	}

	switch (CanMainState)
	{
	case CAN_MAIN_IDLE:
		F_CAN_INIT = 0;
		CanMainState = CAN_MAIN_CFG;
		break;
	case CAN_MAIN_CFG:
		CAN1_Init();
		CanTxErrorCounter = 0;
		CanNoTxCounter = 0;
		CanMainState = CAN_MAIN_INIT;
		break;
	case CAN_MAIN_INIT:
		CAN1_ClearTxMessage();
		F_CAN_SLEEP = 0;
		F_CAN_RX_DATA = 1;
		F_CAN_INTERRUPT = 0;
		CanMainState = CAN_MAIN_NORMAL;
		CanNoDataTimer = T60S_1;
		CanTxTimer = 0;
		break;
	case CAN_MAIN_NORMAL:
#if CAN_WAKEUP_FUN == 1
		if (F_CAN_RX_DATA == 0)
#else
		if (Get_ACC_Det_Flag == 0)
#endif
		{
			CanMainState = CAN_MAIN_SLEEP_CFG;
			break;
		}
		if (Get_ACC_Det_Flag)
		{
			if (APP_READY == APP_Status)
			{
				if (CanMainTimer == 0)
				{
					CanMainTimer = T5S_1;
				}
			}
			if (CanTxTimer == 0)
			{
				CanTxTimer = T500MS_1;
				Mahindra_SCORPIO11_PostMessage(CAN_POST_MSG_IS_3);
			}
		}
		break;
	case CAN_MAIN_SLEEP_CFG:
		CAN1_ClearRxMessage();
		CAN_IC_STANDBY_ON;
		CAN_IC_POWER_OFF;
		F_CAN_SLEEP = 1;
		F_CAN_INTERRUPT = 0;
		CanMainState = CAN_MAIN_SLEEP;
		break;
	case CAN_MAIN_SLEEP:
#if CAN_WAKEUP_FUN == 1
		if (F_CAN_SLEEP == 0 || F_CAN_INTERRUPT)
#else
		if (Get_ACC_Det_Flag)
#endif
		{
			CAN_IC_STANDBY_OFF;
			CAN_IC_POWER_ON;
			F_CAN_SLEEP = 0;
			CanMainState = CAN_MAIN_INIT;
		}
		break;
	default:
		break;
	}
}

#endif
