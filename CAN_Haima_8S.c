#include "public.h"

#if CAN_FUN_HAIMA_8S == 1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_TX_INFO CanTxInfo;
CAN_TX_INFO CanTxInfoBak;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanCheckErrorTimer;

u16 CanTxTimer;
u8 CanTxErrorCounter;
u8 CanNoTxCounter;
u8 CanTxQueueTimer;
// u16 CanTxBufferTickCounter;
// CAN_TX_QUEUE CanTxQueue;
// u8 DequeueTimer;
// u8 SkipEnqueue;
u8 CANTurnState;
u8 CANTurnStateBak;
u8 CANTurnStateTimer;
u8 wireless_charge;

u8 Haima8S_Keycode;
u8 Haima8S_SWC_SW;
u16 Haima8S_SWC_Timeout;

u8 haima_8s_temp;

u8 acp_times;

CAN_TX_TIMER CanTxTimerDict[CAN_TX_ID_COUNT] = {
	{CAN_ID_DVD_1, 100},
	{CAN_ID_DVD_4, 0},
	{CAN_ID_DVD_5, 0},
	{CAN_ID_DVD_6, 0},
	{CAN_ID_DVD_7, 0},
	{CAN_ID_DVD_8, 20},
	{CAN_ID_DVD_A, 50},
	{CAN_ID_DVD_B, 50},
	{CAN_ID_DVD_E, 50},
	{CAN_ID_DVD_F, 100},
	{CAN_ID_DVD_G, 100},
	{CAN_ID_DVD_H, 100},
	{CAN_ID_DVD_I, 100},
	{CAN_ID_DVD_NM, 0},
	{CAN_ID_BCM_INFO_02, 0}};
#if TEST_CAN_FUN == 1
u32 CanTestTimer;
int test_time;
int test;
#endif

void Haima_8S_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8] = {0};

	switch (index)
	{
	case CAN_POST_MSG_DVD_1:
		// data[0] = CanTxInfo.dvd_1_info.byte_0.byte;
		// data[1] = CanTxInfo.dvd_1_info.byte_1.byte;
		data[2] = CanTxInfo.dvd_1_info.byte_2.byte;
		data[3] = CanTxInfo.dvd_1_info.byte_3.byte;
		data[4] = CanTxInfo.dvd_1_info.byte_4.byte;
		data[5] = CanTxInfo.dvd_1_info.byte_5.byte;
		data[6] = CanTxInfo.dvd_1_info.byte_6.byte;
		data[7] = CanTxInfo.dvd_1_info.follow_me_home_delay_time;
		CAN1_TxFrame(CAN_ID_DVD_1, data, 8);
		break;
	case CAN_POST_MSG_DVD_4:
		data[0] = RTC_TimeInfo.seconds;
		data[1] = RTC_TimeInfo.minutes;
		data[2] = RTC_TimeInfo.hours;
		data[3] = RTC_TimeInfo.day;
		data[4] = RTC_TimeInfo.month;
		data[5] = RTC_TimeInfo.year;
		CAN1_TxFrame(CAN_ID_DVD_4, data, 8);
		break;
	case CAN_POST_MSG_DVD_8:
		data[0] = CanTxInfo.dvd_8_info.byte_0.byte;
		data[1] = CanTxInfo.dvd_8_info.byte_1.byte;
		data[2] = CanTxInfo.dvd_8_info.bt_second;
		data[3] = CanTxInfo.dvd_8_info.bt_minute;
		data[4] = CanTxInfo.dvd_8_info.bt_hour;
		data[5] = CanTxInfo.dvd_8_info.freq_H8;
		data[6] = CanTxInfo.dvd_8_info.byte_6.byte;
		data[7] = CanTxInfo.dvd_8_info.volume;
		CAN1_TxFrame(CAN_ID_DVD_8, data, 8);
		break;
	case CAN_POST_MSG_DVD_A:
		data[0] = CanTxInfo.dvd_A_info.phone_number_0;
		data[1] = CanTxInfo.dvd_A_info.phone_number_1;
		data[2] = CanTxInfo.dvd_A_info.phone_number_2;
		data[3] = CanTxInfo.dvd_A_info.phone_number_3;
		data[4] = CanTxInfo.dvd_A_info.phone_number_4;
		data[5] = CanTxInfo.dvd_A_info.phone_number_5;
		data[6] = CanTxInfo.dvd_A_info.phone_number_6;
		data[7] = CanTxInfo.dvd_A_info.phone_number_7;
		CAN1_TxFrame(CAN_ID_DVD_A, data, 8);
		break;
	case CAN_POST_MSG_DVD_B:
		data[0] = CanTxInfo.dvd_B_info.byte_0.byte;
		data[1] = CanTxInfo.dvd_B_info.byte_1;
		data[2] = CanTxInfo.dvd_B_info.byte_2;
		data[3] = CanTxInfo.dvd_B_info.byte_3;
		data[4] = CanTxInfo.dvd_B_info.byte_4;
		data[5] = CanTxInfo.dvd_B_info.byte_5;
		data[6] = CanTxInfo.dvd_B_info.byte_6;
		data[7] = CanTxInfo.dvd_B_info.byte_7;
		CAN1_TxFrame(CAN_ID_DVD_B, data, 8);
		break;
	case CAN_POST_MSG_DVD_E:
		data[0] = CanTxInfo.dvd_E_info.byte_0.byte;
		data[1] = CanTxInfo.dvd_E_info.byte_1;
		data[2] = CanTxInfo.dvd_E_info.byte_2;
		data[3] = CanTxInfo.dvd_E_info.byte_3;
		data[4] = CanTxInfo.dvd_E_info.byte_4;
		data[5] = CanTxInfo.dvd_E_info.byte_5;
		data[6] = CanTxInfo.dvd_E_info.byte_6;
		data[7] = CanTxInfo.dvd_E_info.byte_7;
		CAN1_TxFrame(CAN_ID_DVD_E, data, 8);
		break;
	case CAN_POST_MSG_DVD_F:
		// data[0] = CanTxInfo.dvd_F_info.byte_0.byte;
		// data[1] = CanTxInfo.dvd_F_info.byte_1.byte;
		// data[2] = CanTxInfo.dvd_F_info.byte_2.byte;
		// data[3] = CanTxInfo.dvd_F_info.byte_3.byte;
		data[4] = CanTxInfo.dvd_F_info.byte_4.byte;
		data[5] = CanTxInfo.dvd_F_info.byte_5.byte;
		// data[6] = CanTxInfo.dvd_F_info.byte_6.byte;
		data[7] = CanTxInfo.dvd_F_info.byte_7.byte;
		CAN1_TxFrame(CAN_ID_DVD_F, data, 8);
		break;
	case CAN_POST_MSG_DVD_G:
		data[0] = CanTxInfo.dvd_G_info.byte_0.byte;
		data[1] = CanTxInfo.dvd_G_info.byte_1.byte;
		data[2] = CanTxInfo.dvd_G_info.byte_2.byte;
		data[3] = CanTxInfo.dvd_G_info.byte_3.byte;
		data[4] = CanTxInfo.dvd_G_info.byte_4.byte;
		data[5] = CanTxInfo.dvd_G_info.byte_5.byte;
		data[6] = CanTxInfo.dvd_G_info.f_ial_brightness;
		data[7] = CanTxInfo.dvd_G_info.f_ial_color;
		CAN1_TxFrame(CAN_ID_DVD_G, data, 8);
		break;
	case CAN_POST_MSG_DVD_I:
		data[0] = CanTxInfo.dvd_I_info.byte_0.byte;
		data[1] = CanTxInfo.dvd_I_info.byte_1.byte;
		data[2] = CanTxInfo.dvd_I_info.f_driver_seat_ctrl;
		data[3] = CanTxInfo.dvd_I_info.byte_3.byte;
		CAN1_TxFrame(CAN_ID_DVD_I, data, 8);
		break;
	case CAN_POST_MSG_TEST:
		data[4] = wireless_charge;
		CAN1_TxFrame(CAN_ID_BCM_INFO_02, data, 8);
		break;
	default:
		break;
	}
}

void Haima_8S_PostMessage_3Times(CAN_POST_MESSAGE_INDEX index)
{
	Haima_8S_PostMessage(index);
	Haima_8S_PostMessage(index);
	Haima_8S_PostMessage(index);
}

void Haima_8S_Rx_Message(void)
{
	if (CanRxBuffer.head != CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message = CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID = 0;
		CanRxBuffer.head = (CanRxBuffer.head + 1) % CAN_RX_BUFFER_LENGTH;

		switch (message.ID)
		{
		// case CAN_ID_AVM:
		// 	CanRxInfo.avm_info.byte_0.field.f_parking_guide_line = message.Data[0] & 0x01;
		// 	CanRxInfo.avm_info.byte_0.field.f_video_out = (message.Data[1] & 0x0E) >> 1;
		// 	CanRxInfo.avm_info.byte_0.field.f_color_set = message.Data[2] & 0x07;
		// 	CanRxInfo.avm_info.byte_1.field.f_sd_card = (message.Data[2] & 0x38) >> 3;
		// 	CanRxInfo.avm_info.byte_1.field.f_avm_guides = (message.Data[2] & 0x40) >> 6;
		// 	CanRxInfo.avm_info.byte_1.field.f_lane_departure = message[3] & 0x07;
		// 	break;
		// case CAN_ID_T_BOX_9:
		// 	CanRxInfo.tbox_info.byte_0.byte = message.Data[0] & 0x3F;
		// 	break;
		case CAN_ID_ESP_2:
			if ((message.Data[1] & 0x04) >> 2 == 0)
				break;
			CanRxInfo.esp_info.speed_H8 = message.Data[0];
			CanRxInfo.esp_info.byte_1.field.speed_L5 = (message.Data[1] & 0xF8) >> 3;
			if (!strcmp_equal(&CanRxInfo.esp_info.speed_H8, &CanRxInfoBak.esp_info.speed_H8, sizeof(CAN_ESP_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.esp_info.speed_H8, &CanRxInfo.esp_info.speed_H8, sizeof(CAN_ESP_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_ESP_INFO);
			}
			break;
		case CAN_ID_ICM_1:
			CanGeneralCtrlFlag.field.reverse_on_off = (message.Data[0] & 0x10) >> 4;
			CanRxInfo.base_info.byte_0.field.remain_oil_H2 = message.Data[2] & 0x3;
			CanRxInfo.base_info.remain_oil_L8 = message.Data[3];
			CanRxInfo.base_info.aver_fuel_consumption = message.Data[1];
			CanRxInfo.base_info.remain_mileage = message.Data[4];
			CanRxInfo.base_info.total_mileage_H = message.Data[5];
			CanRxInfo.base_info.total_mileage_M = message.Data[6];
			CanRxInfo.base_info.total_mileage_L = message.Data[7];
			if (!strcmp_equal(&CanRxInfo.base_info.byte_0.byte, &CanRxInfoBak.base_info.byte_0.byte, sizeof(CAN_BASE_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.base_info.byte_0.byte, &CanRxInfo.base_info.byte_0.byte, sizeof(CAN_BASE_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_BASE_INFO);
			}
			break;
		case CAN_ID_ICM_2:
			CanRxInfo.radar_info.byte_0.byte = message.Data[3] & 0x3F;
			CanRxInfo.radar_info.byte_1.byte = message.Data[4] & 0x3F;
			CanRxInfo.radar_info.byte_1.field.f_f_radar = (message.Data[6] & 0x80) >> 7;
			CanRxInfo.icm_info.byte_0.field.f_icm_theme = (message.Data[6] & 0x70) >> 4;
			CanRxInfo.base_info.remain_maintenance_mileage = message.Data[5] & 0x7F;
			if (!strcmp_equal(&CanRxInfo.radar_info.byte_0.byte, &CanRxInfoBak.radar_info.byte_0.byte, sizeof(CAN_RADAR_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.radar_info.byte_0.byte, &CanRxInfo.radar_info.byte_0.byte, sizeof(CAN_RADAR_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_RADAR_INFO);
			}
			break;
		case CAN_ID_ICM_3:
			CanRxInfo.icm_info.byte_0.field.f_phone_name_req = message.Data[0] & 0x01;
			CanRxInfo.icm_info.byte_0.field.f_current_road_req = (message.Data[0] & 0x02) >> 1;
			CanRxInfo.icm_info.byte_0.field.f_turn_road_req = (message.Data[0] & 0x04) >> 2;
			CanRxInfo.icm_info.byte_0.field.f_id3_req = (message.Data[0] & 0x10) >> 4;
//			if (CanRxInfo.icm_info.byte_0.byte >> 3 != 0)
//			{
//				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_ICM_INFO);	
//			}
			break;
		case CAN_ID_ACP:
		{
			if (strcmp_equal(&CanRxInfo.acp_info.byte_0.byte, &CanRxInfoBak.acp_info.byte_0.byte, sizeof(CAN_ACP_INFO)))
			{
				acp_times++;
			}
			else
			{
				Mem_strcpy(&CanRxInfoBak.acp_info.byte_0.byte, &CanRxInfo.acp_info.byte_0.byte, sizeof(CAN_ACP_INFO));
				acp_times = 1;
			}
			if (acp_times < 3)
				break;
			acp_times = 0;
			// CanRxInfo.acp_info.byte_0.field.f_acp_ctrl = message.Data[5] & 0x03;
			if ((message.Data[5] & 0x03) == 1)
			{
				if (F_FICTITIOUS_POWER_OFF)
				{
					PostKeyCode(UICC_FICTITIOUS_POWER_OFF, PANEL);
				}

				else
				{
					PostKeyCode(UICC_MUTE, PANEL);
				}
			}
			else if ((message.Data[5] & 0x03) == 2)
			{
				PostKeyCode(UICC_FICTITIOUS_POWER_OFF, PANEL);
			}
			u8 times = ((message.Data[6] & 0xF8) >> 3);
			if ((message.Data[6] & 0x03) == 1)
			{
				// TurnOn_Volume += times;
				// PostMessage(NAVI_MODULE, MCU_TX_VOLUME, 0);
				while (times--)
				{
					PostKeyCode(UICC_VOLUME_UP, PANEL);
				}
			}
			else if ((message.Data[6] & 0x03) == 2)
			{
				while (times--)
				{
					PostKeyCode(UICC_VOLUME_DOWN, PANEL);
				}
			}
			break;
		}
		case CAN_ID_TPMS_1:
			CanRxInfo.tpms_info.byte_0.byte = message.Data[4];
			CanRxInfo.tpms_info.fl_tp = message.Data[0];
			CanRxInfo.tpms_info.fr_tp = message.Data[1];
			CanRxInfo.tpms_info.rl_tp = message.Data[2];
			CanRxInfo.tpms_info.rr_tp = message.Data[3];
			if (!strcmp_equal(&CanRxInfo.tpms_info.byte_0.byte, &CanRxInfoBak.tpms_info.byte_0.byte, sizeof(CAN_TPMS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.tpms_info.byte_0.byte, &CanRxInfo.tpms_info.byte_0.byte, sizeof(CAN_TPMS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_TPMS_INFO);
			}
			break;
		case CAN_ID_TPMS_2:
			CanRxInfo.tpms_info.fl_tt = message.Data[0];
			CanRxInfo.tpms_info.fr_tt = message.Data[1];
			CanRxInfo.tpms_info.rl_tt = message.Data[2];
			CanRxInfo.tpms_info.rr_tt = message.Data[3];
			break;
		case CAN_ID_BCM_1:
			// CanRxInfo.bcm_info.byte_0.byte = message.Data[0] & 0x01;
			// CanRxInfo.bcm_info.byte_0.byte = (message.Data[0] & 0x01) | (message.Data[1] & 0x07) << 1 | (message.Data[2] & 0x01) << 4;
			CanRxInfo.bcm_info.byte_0.byte = (message.Data[1] & 0xF0) >> 4 | (message.Data[2] & 0x01) << 4;
			// CanRxInfo.bcm_info.byte_0.byte = message.Data[0];
			if (CANTurnState && (message.Data[0] & 0xC0) >> 6 == 0)
			{
				CANTurnStateTimer++;
				if (CANTurnStateTimer >= 5)
					CANTurnState = 0;
			}
			else
			{
				CANTurnStateTimer = 0;
				CANTurnState = (message.Data[0] & 0xC0) >> 6;
				CANTurnState = (CANTurnState == 3) ? 0 : CANTurnState;
			}
			if (CANTurnStateBak != CANTurnState)
			{
				PostMessage(NAVI_MODULE,MCU_TX_CMD,WORD(UICC_TURN_SIGNAL,CANTurnState));
				CANTurnStateBak = CANTurnState;
			}
			// CanRxInfo.bcm_info.byte_1.byte = (message.Data[1] & 0x07) | ((message[2] & 0xF8) >> 3);
			CanRxInfo.bcm_info.byte_2.field.f_adas = message.Data[4] & 0x01;
			CanRxInfo.bcm_info.byte_2.field.f_f_wiper = (message.Data[4] & 0x0C) >> 2;
			CanRxInfo.bcm_info.byte_2.field.f_windscreen_washing = (message.Data[4] & 0x30) >> 4;
			CanRxInfo.bcm_info.byte_2.field.f_trunk_lock = (message.Data[5] & 10) >> 4;
			CanRxInfo.bcm_info.byte_2.field.f_day_running_light = (message.Data[6] & 0x10) >> 4;
			// CanRxInfo.bcm_info.byte_3.field.f_power_mode = (message.Data[6] & 0x0C) >> 2;
			if ((message.Data[4] & 0x80) >> 7 | (message.Data[0] & 0x04) >> 2 | (message.Data[0] & 0x08) >> 3)
			{
				CanGeneralCtrlFlag.field.ill_onoff = 1;
			}
			else
			{
				CanGeneralCtrlFlag.field.ill_onoff = 0;
			}
			if (!strcmp_equal(&CanRxInfo.bcm_info.byte_0.byte, &CanRxInfoBak.bcm_info.byte_0.byte, sizeof(CAN_BCM_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.bcm_info.byte_0.byte, &CanRxInfo.bcm_info.byte_0.byte, sizeof(CAN_BCM_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_BCM_INFO);
			}
			break;
		case CAN_ID_BCM_2:
			CanRxInfo.bcm_info.byte_3.field.f_follow_me_home = (message.Data[0] & 0x04) >> 2;
			CanTxInfo.dvd_1_info.byte_5.field.follow_me_home = CanRxInfo.bcm_info.byte_3.field.f_follow_me_home;
			CanRxInfo.bcm_info.byte_3.byte &= ~(0x0F << 3);
			CanRxInfo.bcm_info.byte_3.byte |= (message.Data[5] & 0x0F) << 3;
			CanRxInfo.bcm_info.follow_me_home_delay_time = message.Data[1];
			CanTxInfo.dvd_1_info.follow_me_home_delay_time = CanRxInfo.bcm_info.follow_me_home_delay_time;
			break;
		case CAN_ID_CCM:
			CanRxInfo.ccm_info.byte_0.byte = message.Data[0];
			CanRxInfo.ccm_info.byte_1.byte = message.Data[6];
			CanRxInfo.ccm_info.byte_1.field.f_max_ac = (message.Data[6] & 0x08) >> 3;
			CanRxInfo.ccm_info.byte_1.field.blower_vol = (message.Data[2] & 0xF0) >> 4;
			CanRxInfo.ccm_info.byte_2.byte = message.Data[4];
			CanRxInfo.ccm_info.ambient_temp = message.Data[5];
			CanRxInfo.ccm_info.byte_4.byte = message.Data[7];
			if (!strcmp_equal(&CanRxInfo.ccm_info.byte_0.byte, &CanRxInfoBak.ccm_info.byte_0.byte, sizeof(CAN_CCM_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.ccm_info.byte_0.byte, &CanRxInfo.ccm_info.byte_0.byte, sizeof(CAN_CCM_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_CCM_INFO);
			}
			break;
		case CAN_ID_CCM_2:
			CanRxInfo.ccm_info.pm25_H = message.Data[0];
			CanRxInfo.ccm_info.byte_6.byte = message.Data[1];
			CanRxInfo.ccm_info.byte_7.field.f_pm25_filter = message.Data[2] & 0x03;
			// if (!strcmp_equal(&CanRxInfo.ccm_info.byte_0.byte, &CanRxInfoBak.ccm_info.byte_0.byte, sizeof(CAN_CCM_INFO)))
			// {
			// 	Mem_strcpy(&CanRxInfoBak.ccm_info.byte_0.byte, &CanRxInfo.ccm_info.byte_0.byte, sizeof(CAN_CCM_INFO));
			// 	PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_CCM_INFO);
			// }
			break;
		case CAN_ID_EPS:
			CanRxInfo.eps_info.f_eps = (message.Data[0] & 0x60) >> 5;
			if (!strcmp_equal(&CanRxInfo.eps_info.f_eps, &CanRxInfoBak.eps_info.f_eps, sizeof(CAN_EPS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.eps_info.f_eps, &CanRxInfo.eps_info.f_eps, sizeof(CAN_EPS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_EPS_INFO);
			}
			break;
		case CAN_ID_MRR_2:
			CanRxInfo.mrr_info.byte_0.byte = (message.Data[3] & 0x38) >> 3;
			if (!strcmp_equal(&CanRxInfo.mrr_info.byte_0.byte, &CanRxInfoBak.mrr_info.byte_0.byte, sizeof(CAN_MRR_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.mrr_info.byte_0.byte, &CanRxInfo.mrr_info.byte_0.byte, sizeof(CAN_MRR_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_MRR_INFO);
			}
			break;
		case CAN_ID_EMS_4:
			CanRxInfo.ems_info.engine_temp = message.Data[1];
			CanRxInfo.ems_info.byte_0.field.f_engine_temp_vdl = (message.Data[5] & 0x40) >> 6;
			CanRxInfo.ems_info.byte_0.field.f_epcs = (message.Data[6] & 0x10) >> 4;
			if (!strcmp_equal(&CanRxInfo.ems_info.byte_0.byte, &CanRxInfoBak.ems_info.byte_0.byte, sizeof(CAN_EMS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.ems_info.byte_0.byte, &CanRxInfo.ems_info.byte_0.byte, sizeof(CAN_EMS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_EMS_INFO);
			}
			break;
		case CAN_ID_SCM_1:
			CanRxInfo.scm_info.byte_0.byte = message.Data[0];
			CanRxInfo.scm_info.byte_1.byte = message.Data[4];
			if (!strcmp_equal(&CanRxInfo.scm_info.byte_0.byte, &CanRxInfoBak.scm_info.byte_0.byte, sizeof(CAN_SCM_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.scm_info.byte_0.byte, &CanRxInfo.scm_info.byte_0.byte, sizeof(CAN_SCM_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_SCM_INFO);
			}
			break;
		case CAN_ID_APM_1:
			CanRxInfo.apm_info.byte_0.byte = message.Data[1];
			CanRxInfo.apm_info.byte_1.byte = message.Data[2];
			if (!strcmp_equal(&CanRxInfo.apm_info.byte_0.byte, &CanRxInfoBak.apm_info.byte_0.byte, sizeof(CAN_APM_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.apm_info.byte_0.byte, &CanRxInfo.apm_info.byte_0.byte, sizeof(CAN_APM_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_APM_INFO);
			}
			break;
		case CAN_ID_MPC_1:
			CanRxInfo.mpc_info.byte_0.byte = message.Data[0];
			CanTxInfo.dvd_1_info.byte_3.field.adas = CanRxInfo.mpc_info.byte_0.field.f_lks;
			if (!strcmp_equal(&CanRxInfo.mpc_info.byte_0.byte, &CanRxInfoBak.mpc_info.byte_0.byte, sizeof(CAN_MPC_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.mpc_info.byte_0.byte, &CanRxInfo.mpc_info.byte_0.byte, sizeof(CAN_MPC_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_MPC_INFO);
			}
			break;
		case CAN_ID_SAS:
			// CanRxInfo.sas_info.byte_0.byte = message.Data[1];
			// CanRxInfo.sas_info.steering_speed = message.Data[2];
			CanRxInfo.sas_info.steering_angle_H = message.Data[3];
			CanRxInfo.sas_info.steering_angle_L = message.Data[4];
			if (!strcmp_equal(&CanRxInfo.sas_info.steering_angle_L, &CanRxInfoBak.sas_info.steering_angle_L, sizeof(CAN_SAS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.sas_info.steering_angle_L, &CanRxInfo.sas_info.steering_angle_L, sizeof(CAN_SAS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_SAS_INFO);
			}
			break;
		case CAN_ID_LCAS:
			CanRxInfo.lcas_info.byte_0.byte = (message.Data[0] & 0xFC) >> 2;
			CanRxInfo.lcas_info.byte_0.field.f_lcas_cal_process = (message.Data[1] & 0x04) >> 2;
			if (!strcmp_equal(&CanRxInfo.lcas_info.byte_0.byte, &CanRxInfoBak.lcas_info.byte_0.byte, sizeof(CAN_LCAS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.lcas_info.byte_0.byte, &CanRxInfo.lcas_info.byte_0.byte, sizeof(CAN_LCAS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_LCAS_INFO);
			}
			break;
		case CAN_ID_IAL:
			CanRxInfo.ial_info.byte_0.byte = message.Data[0];
			CanRxInfo.ial_info.f_ial_brightness = message.Data[1];
			CanRxInfo.ial_info.f_ial_color = message.Data[2];
			if (!strcmp_equal(&CanRxInfo.ial_info.byte_0.byte, &CanRxInfoBak.ial_info.byte_0.byte, sizeof(CAN_IAL_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.ial_info.byte_0.byte, &CanRxInfo.ial_info.byte_0.byte, sizeof(CAN_IAL_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_IAL_INFO);
			}
			break;
		case CAN_ID_TCU_2:
			CanRxInfo.icm_info.gear = message.Data[2];
			if (!strcmp_equal(&CanRxInfo.icm_info.byte_0.byte, &CanRxInfoBak.icm_info.byte_0.byte, sizeof(CAN_ICM_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.icm_info.byte_0.byte, &CanRxInfo.icm_info.byte_0.byte, sizeof(CAN_ICM_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_ICM_INFO);
			}
		default:
			break;
		}
		if(CanRxInfo.base_info.byte_0.field.f_can_ready == 0)
		{
			CanRxInfo.base_info.byte_0.field.f_can_ready = 1;
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_BASE_INFO);
		}
		F_CAN_RX_DATA = 1;
		F_CAN_SLEEP = 0;
		CanNoDataTimer = T30S_1;
		CAN1_ClearErrorTimer();
	}
}

// void Haima_8S_Enqueue(u8 *buffer, u8 delay)
// {
// 	if ((CanTxQueue.tail + 1) % CAN_TX_QUEUE_LENGTH != CanTxQueue.head)
// 	{
// 		CanTxQueue.delay[CanTxQueue.tail] = delay;
// 		CanTxQueue.message[CanTxQueue.tail] = buffer;
// 		CanTxQueue.tail = (CanTxQueue.tail + 1) & CAN_TX_QUEUE_LENGTH;
// 	}
// }

// void Haima_8S_Enqueue_2times(u8 *buffer, u8 delay)
// {
// 	if (!SkipEnqueue)
// 	{
// 		Haima_8S_Enqueue(buffer, delay);
// 		Haima_8S_Enqueue(buffer, delay);
// 	}
// }

// void Haima_8S_Dequque(void)
// {
// 	DequeueTimer++;
// 	if (DequeueTimer == CanTxQueue.delay[CanTxQueue.head])
// 	{
// 		SkipEnqueue = 1;
// 		Haima_8S_RxAppDataPro(CanTxQueue.message[CanTxQueue.head]);
// 		CanTxQueue.head = (CanTxQueue.head + 1) % CAN_TX_QUEUE_LENGTH;
// 		DequeueTimer = 0;
// 	}
// }

void Haima_8S_ICM_Info_Format(u8 *buffer, CAN_ICM_DISP_INFO *obj, CAN_POST_MESSAGE_INDEX CAN_ID)
{
	u8 length = buffer[2];
	u8 frames = ceil((float)length / DATAS_PER_FRAME);
	u8 index = 0;
	for (u8 i = 0; i < frames; i++)
	{
		if (i == 0)
		{
			if (frames == 1)
			{
				obj->byte_0.byte = 0;
				Mem_strcpy(&obj->byte_1, &buffer[3], length);
				for (u8 j = length % DATAS_PER_FRAME; j < DATAS_PER_FRAME; j++)
				{
					*(&obj->byte_1 + j) = 0xFF;
				}
			}
			else
			{
				obj->byte_0.field.type = 0x01;
				obj->byte_0.field.dlc = frames;
				Mem_strcpy(&obj->byte_1, &buffer[3], DATAS_PER_FRAME);
				index += DATAS_PER_FRAME;
			}
		}
		else if (i == frames - 1)
		{
			obj->byte_0.field.type = 0x03;
			obj->byte_0.field.dlc = i + 1;
			Mem_strcpy(&obj->byte_1, &buffer[3 + index], length % DATAS_PER_FRAME);
			for (u8 j = length % DATAS_PER_FRAME; j < DATAS_PER_FRAME; j++)
			{
				*(&obj->byte_1 + j) = 0xFF;
			}
		}
		else
		{
			obj->byte_0.field.type = 0x02;
			obj->byte_0.field.dlc = i + 1;
			Mem_strcpy(&obj->byte_1, &buffer[3 + index], DATAS_PER_FRAME);
			index += DATAS_PER_FRAME;
		}
		Haima_8S_PostMessage(CAN_ID);
	}
}

void Haima_8S_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id = buffer[1];

	if (Get_ACC_Det_Flag == 0)
	{
		return;
	}

	switch (cmd_id)
	{
	case HAIMA_8S_TX_REQ_CMD:
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_CCM_INFO);
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_ESP_INFO);
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_BASE_INFO);
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_SAS_INFO);
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_TPMS_INFO);
		PostMessage(NAVI_MODULE, MCU_TX_CMD,WORD(UICC_TURN_SIGNAL, CANTurnState));
		break;
	case HAIMA_8S_TX_CCM_CMD:
		// if (!SkipEnqueue)
		// 	Haima_8S_Enqueue_2times(buffer, 10);
		switch (buffer[3])
		{
		case CCM_ON_OFF:
			if (buffer[4] == 1)
			{
				CanTxInfo.dvd_G_info.byte_0.field.f_ccm_set = 1;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
				CanTxInfo.dvd_G_info.byte_0.field.f_ccm_set = 0;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			}
			break;
		case CCM_AUTO:
			if (buffer[4] == 1)
			{
				CanTxInfo.dvd_G_info.byte_0.field.f_auto = 1;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
				CanTxInfo.dvd_G_info.byte_0.field.f_auto = 0;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			}
			break;
		case CCM_FL_TEMPERATURE:
			CanTxInfo.dvd_G_info.byte_0.field.fl_temp = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_0.field.fl_temp = 0x3F;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case CCM_DUAL:
			if (buffer[4] == 1)
			{
				CanTxInfo.dvd_G_info.byte_1.field.f_dual = 1;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
				CanTxInfo.dvd_G_info.byte_1.field.f_dual = 0;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			}
			break;
		case CCM_FR_TEMPERATURE:
			CanTxInfo.dvd_G_info.byte_1.field.fr_temp = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_1.field.fr_temp = 0x3F;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case CCM_BLOWER_VOL:
			CanTxInfo.dvd_G_info.byte_2.field.blower_vol = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_2.field.blower_vol = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case CCM_AC:
			if (buffer[4] == 1)
			{
				CanTxInfo.dvd_G_info.byte_2.field.f_ac = 1;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
				CanTxInfo.dvd_G_info.byte_2.field.f_ac = 0;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			}
			break;
		case CCM_MAXAC:
			if (buffer[4] == 1)
			{
				CanTxInfo.dvd_G_info.byte_2.field.f_maxac = 1;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
				CanTxInfo.dvd_G_info.byte_2.field.f_maxac = 0;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			}
			break;
		case CCM_CYCLE:
			CanTxInfo.dvd_G_info.byte_2.field.f_cycle = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_2.field.f_cycle = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case CCM_F_DEFROST:
			if (buffer[4] == 1)
			{
				CanTxInfo.dvd_G_info.byte_3.field.f_f_defrost = 1;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
				CanTxInfo.dvd_G_info.byte_3.field.f_f_defrost = 0;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			}
			break;
		case CCM_R_DEFROST:
			if (buffer[4] == 1)
			{
				CanTxInfo.dvd_G_info.byte_3.field.f_r_defrost = 1;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
				CanTxInfo.dvd_G_info.byte_3.field.f_r_defrost = 0;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			}
			break;
		case CCM_AIR_CLEAN:
			if (buffer[4] == 1)
			{
				CanTxInfo.dvd_G_info.byte_3.field.f_air_clean = 1;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
				CanTxInfo.dvd_G_info.byte_3.field.f_air_clean = 0;
				Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			}
			break;
		case CCM_AIR_DISTRIBUTION:
			CanTxInfo.dvd_G_info.byte_4.field.f_air_distribution = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_4.field.f_air_distribution = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case OTS_DRIVER_SEAT_HEATING:
			CanTxInfo.dvd_1_info.byte_6.field.driver_seat_heating = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_6.field.driver_seat_heating = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
		case OTS_PASSEGER_SEAT_HEATING:
			CanTxInfo.dvd_1_info.byte_6.field.passeger_seat_heating = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_6.field.passeger_seat_heating = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
		default:
			break;
		}
		break;
	case HAIMA_8S_TX_VOICE_CMD:
		// if (!SkipEnqueue)
		// 	Haima_8S_Enqueue_2times(buffer, 10);
		switch (buffer[3])
		{
		case VOICE_FL_WIN:
			CanTxInfo.dvd_I_info.byte_0.field.f_fl_window = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			CanTxInfo.dvd_I_info.byte_0.field.f_fl_window = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			break;
		case VOICE_FR_WIN:
			CanTxInfo.dvd_I_info.byte_0.field.f_fr_window = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			CanTxInfo.dvd_I_info.byte_0.field.f_fl_window = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			break;
		case VOICE_RL_WIN:
			CanTxInfo.dvd_I_info.byte_1.field.f_rl_window = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			CanTxInfo.dvd_I_info.byte_1.field.f_rl_window = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			break;
		case VOICE_RR_WIN:
			CanTxInfo.dvd_I_info.byte_1.field.f_rr_window = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			CanTxInfo.dvd_I_info.byte_1.field.f_rr_window = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			break;
		case VOICE_FL_SEAT:
			CanTxInfo.dvd_I_info.f_driver_seat_ctrl = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			CanTxInfo.dvd_I_info.f_driver_seat_ctrl = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			break;
		case VOICE_SEAT_COURT:
			CanTxInfo.dvd_I_info.byte_3.field.f_seat_court = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			CanTxInfo.dvd_I_info.byte_3.field.f_seat_court = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			break;
		case VOICE_SEAT_POSITION:
			CanTxInfo.dvd_I_info.byte_3.field.f_seat_position = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			CanTxInfo.dvd_I_info.byte_3.field.f_seat_position = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_I);
			break;
		case VOICE_SUNROOF:
			CanTxInfo.dvd_F_info.byte_7.field.sun_roof = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			CanTxInfo.dvd_F_info.byte_7.field.sun_roof = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			break;
		case VOICE_CURTAIN:
			CanTxInfo.dvd_F_info.byte_7.field.curtain = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			CanTxInfo.dvd_F_info.byte_7.field.curtain = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			break;
		case VOICE_WIPER:
			CanTxInfo.dvd_F_info.byte_7.field.wiper = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			CanTxInfo.dvd_F_info.byte_7.field.wiper = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			break;
		case VOICE_R_VMIRROR:
			CanTxInfo.dvd_F_info.byte_4.field.rear_mirror = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			CanTxInfo.dvd_F_info.byte_4.field.rear_mirror = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			break;
		case VOICE_WASHER:
			CanTxInfo.dvd_F_info.byte_4.field.washer = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			CanTxInfo.dvd_F_info.byte_4.field.washer = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			break;
		case VOICE_LIGHT:
			CanTxInfo.dvd_F_info.byte_5.field.light = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			CanTxInfo.dvd_F_info.byte_5.field.light = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			break;
		case VOICE_DOOR:
			CanTxInfo.dvd_F_info.byte_5.field.door = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			CanTxInfo.dvd_F_info.byte_5.field.door = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_F);
			break;
		default:
			break;
		}
		break;
	case HAIMA_8S_TX_OTS_CMD:
		// if (!SkipEnqueue)
		// 	Haima_8S_Enqueue_2times(buffer, 10);
		switch (buffer[3])
		{
		case OTS_FOLLOW_ME_HOME:
			CanTxInfo.dvd_1_info.byte_5.field.follow_me_home = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
			//		case OTS_DRIVER_SEAT_HEATING:
			//			CanTxInfo.dvd_1_info.byte_6.field.driver_seat_heating = buffer[4];
			//			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			//			CanTxInfo.dvd_1_info.byte_6.field.driver_seat_heating = 0;
			//			break;
			//		case OTS_PASSEGER_SEAT_HEATING:
			//			CanTxInfo.dvd_1_info.byte_6.field.passeger_seat_heating = buffer[4];
			//			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			//			CanTxInfo.dvd_1_info.byte_6.field.passeger_seat_heating = 0;
			//			break;
		case OTS_FOLLOW_ME_HOME_DELAY_TIME:
			CanTxInfo.dvd_1_info.follow_me_home_delay_time = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
		case OTS_IAL:
			CanTxInfo.dvd_G_info.byte_5.field.f_ial = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_5.field.f_ial = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case OTS_IAL_MODE:
			CanTxInfo.dvd_G_info.byte_5.field.f_ial_mode = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_5.field.f_ial_mode = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case OTS_IAL_BRIGHTNESS:
			CanTxInfo.dvd_G_info.f_ial_brightness = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.f_ial_brightness = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case OTS_IAL_COLOR:
			CanTxInfo.dvd_G_info.f_ial_color = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.f_ial_color = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			break;
		case OTS_DOOR_LOCK:
			CanTxInfo.dvd_G_info.byte_3.field.f_door_lock_ctrl = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_3.field.f_door_lock_ctrl = 0;
			break;
		case OTS_ROOM_LAMP:
			CanTxInfo.dvd_G_info.byte_3.field.f_room_lamp = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_3.field.f_room_lamp = 0;
			break;
		case OTS_DAYTIME_LAMP:
			CanTxInfo.dvd_G_info.byte_3.field.f_daytime_lamp = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_G);
			CanTxInfo.dvd_G_info.byte_3.field.f_daytime_lamp = 0;
			break;
		default:
			break;
		}
		break;
	case HAIMA_8S_TX_ADAS_CMD:
		// if (!SkipEnqueue)
		// 	Haima_8S_Enqueue_2times(buffer, 10);
		switch (buffer[3])
		{
		case ADAS_BLIND_SURPERVISE:
			CanTxInfo.dvd_1_info.byte_2.field.blind_surpervise = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_2.field.blind_surpervise = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
		case ADAS_LCAS:
			CanTxInfo.dvd_1_info.byte_2.field.lca = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_2.field.lca = 0;
			break;
		case ADAS_DOOR_OPEN_WARN:
			CanTxInfo.dvd_1_info.byte_2.field.door_open_warn = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_2.field.door_open_warn = 0;
			break;
		case ADAS_LCAS_CAL:
			CanTxInfo.dvd_1_info.byte_2.field.lcas_cal = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_2.field.lcas_cal = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
		case ADAS_PCW:
			CanTxInfo.dvd_1_info.byte_3.field.pcw = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_3.field.pcw = 0;
			break;
		case ADAS_AEB:
			CanTxInfo.dvd_1_info.byte_3.field.aeb = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_3.field.aeb = 0;
			break;
		case ADAS_SENSITIVITY:
			CanTxInfo.dvd_1_info.byte_3.field.adas_senstivity = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_3.field.adas_senstivity = 0;
			break;
		case ADAS_LKS:
			CanTxInfo.dvd_1_info.byte_3.field.adas = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
		case ADAS_EPS:
			CanTxInfo.dvd_1_info.byte_4.field.eps = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_4.field.eps = 0;
			break;
		case ADAS_LANE_DEPARTURE:
			CanTxInfo.dvd_1_info.byte_4.field.lane_departure = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_4.field.lane_departure = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
		case ADAS_F_RADAR:
			CanTxInfo.dvd_1_info.byte_4.field.f_radar = buffer[4];
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			CanTxInfo.dvd_1_info.byte_4.field.f_radar = 0;
			Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_1);
			break;
		default:
			break;
		}
		break;
	case HAIMA_8S_TX_PHONE_NAME_CMD:
		Haima_8S_ICM_Info_Format(buffer, &CanTxInfo.dvd_B_info, CAN_POST_MSG_DVD_B);
		break;
	case HAIMA_8S_TX_ID3_CMD:
		if (FrontSource != SOURCE_TUNER)
			Haima_8S_ICM_Info_Format(buffer, &CanTxInfo.dvd_E_info, CAN_POST_MSG_DVD_E);
		break;
	case HAIMA_8S_TX_PHONE_NUMBER_CMD:
		Mem_strcpy(&CanTxInfo.dvd_A_info.phone_number_0, &buffer[3], sizeof(CAN_DVD_A_INFO));
		Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_A);
		break;
//	case HAIMA_8S_TX_PHONE_STATE_CMD:
//		calling_state = (buffer[4] == 4) ? 1
//										: (buffer[4] != 8) ? 0
//										: calling_state;
		break;
	default:
		break;
	}
	// SkipEnqueue = 0;
}

void Haima_8S_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length)
{
	u8 i;
	u8 checksum = 0;
	u32 flag = 1;

	switch (cmd_id)
	{
	case HAIMA_8S_RX_AVM_INFO:
		buffer[2] = 0x02;
		buffer[3] = CanRxInfo.avm_info.byte_0.byte;
		buffer[4] = CanRxInfo.avm_info.byte_1.byte;
		break;
		//	case HAIMA_8S_RX_TBOX_INFO:
		//		buffer[2] = 0x01;
		//		buffer[3] = CanRxInfo.tbox_info.byte_0;
		//		break;
	case HAIMA_8S_RX_ESP_INFO:
		buffer[2] = 0x02;
		buffer[3] = CanRxInfo.esp_info.speed_H8;
		buffer[4] = CanRxInfo.esp_info.byte_1.byte;
		break;
	case HAIMA_8S_RX_BASE_INFO:
		buffer[2] = 0x08;
		buffer[3] = CanRxInfo.base_info.byte_0.byte;
		buffer[4] = CanRxInfo.base_info.remain_oil_L8;
		buffer[6] = CanRxInfo.base_info.aver_fuel_consumption;
		buffer[6] = CanRxInfo.base_info.remain_mileage;
		buffer[7] = CanRxInfo.base_info.total_mileage_H;
		buffer[8] = CanRxInfo.base_info.total_mileage_M;
		buffer[9] = CanRxInfo.base_info.total_mileage_L;
		buffer[10] = CanRxInfo.base_info.remain_maintenance_mileage;
		break;
	case HAIMA_8S_RX_RADAR_INFO:
		buffer[2] = 0x02;
		buffer[3] = CanRxInfo.radar_info.byte_0.byte;
		buffer[4] = CanRxInfo.radar_info.byte_1.byte;
		break;
	case HAIMA_8S_RX_ICM_INFO:
		buffer[2] = 0x02;
		buffer[3] = CanRxInfo.icm_info.byte_0.byte;
		buffer[4] = CanRxInfo.icm_info.gear;
		break;
	case HAIMA_8S_RX_ACP_INFO:
		buffer[2] = 0x02;
		buffer[3] = CanRxInfo.acp_info.byte_0.byte;
		buffer[4] = CanRxInfo.acp_info.byte_1.byte;
		break;
	case HAIMA_8S_RX_TPMS_INFO:
		buffer[2] = 0x05;//0x09;
		buffer[3] = CanRxInfo.tpms_info.byte_0.byte;
		buffer[4] = CanRxInfo.tpms_info.fl_tp;
		buffer[5] = CanRxInfo.tpms_info.fr_tp;
		buffer[6] = CanRxInfo.tpms_info.rl_tp;
		buffer[7] = CanRxInfo.tpms_info.rr_tp;
//		buffer[8] = CanRxInfo.tpms_info.fl_tt;
//		buffer[9] = CanRxInfo.tpms_info.fr_tt;
//		buffer[10] = CanRxInfo.tpms_info.rl_tt;
//		buffer[11] = CanRxInfo.tpms_info.rr_tt;
		break;
	case HAIMA_8S_RX_BCM_INFO:
		buffer[2] = 0x05;
		buffer[3] = CanRxInfo.bcm_info.byte_0.byte;
		buffer[4] = CanRxInfo.bcm_info.byte_1.byte;
		buffer[5] = CanRxInfo.bcm_info.byte_2.byte;
		buffer[6] = CanRxInfo.bcm_info.byte_3.byte;
		buffer[7] = CanRxInfo.bcm_info.follow_me_home_delay_time;
		break;
	case HAIMA_8S_RX_CCM_INFO:
		buffer[2] = 0x08;
		buffer[3] = CanRxInfo.ccm_info.byte_0.byte;
		buffer[4] = CanRxInfo.ccm_info.byte_1.byte;
		buffer[5] = CanRxInfo.ccm_info.byte_2.byte;
		buffer[6] = CanRxInfo.ccm_info.ambient_temp;
		buffer[7] = CanRxInfo.ccm_info.byte_4.byte;
		buffer[8] = CanRxInfo.ccm_info.pm25_H;
		buffer[9] = CanRxInfo.ccm_info.byte_6.byte;
		buffer[10] = CanRxInfo.ccm_info.byte_7.byte;
		break;
	case HAIMA_8S_RX_EPS_INFO:
		buffer[2] = 0x01;
		buffer[3] = CanRxInfo.eps_info.f_eps;
	case HAIMA_8S_RX_MRR_INFO:
		buffer[2] = 0x01;
		buffer[3] = CanRxInfo.mrr_info.byte_0.byte;
	case HAIMA_8S_RX_EMS_INFO:
		buffer[2] = 0x02;
		buffer[3] = CanRxInfo.ems_info.byte_0.byte;
		buffer[4] = CanRxInfo.ems_info.engine_temp;
		break;
	case HAIMA_8S_RX_SCM_INFO:
		buffer[2] = 0x02;
		buffer[3] = CanRxInfo.scm_info.byte_0.byte;
		buffer[4] = CanRxInfo.scm_info.byte_1.byte;
		break;
	case HAIMA_8S_RX_APM_INFO:
		buffer[2] = 0x02;
		buffer[3] = CanRxInfo.apm_info.byte_0.byte;
		buffer[4] = CanRxInfo.apm_info.byte_1.byte;
		break;
	case HAIMA_8S_RX_MPC_INFO:
		buffer[2] = 0x01;
		buffer[3] = CanRxInfo.mpc_info.byte_0.byte;
		break;
	case HAIMA_8S_RX_SAS_INFO:
		buffer[2] = 0x02;
		// buffer[3] = CanRxInfo.sas_info.byte_0;
		// buffer[4] = CanRxInfo.sas_info.steering_speed;
		buffer[3] = CanRxInfo.sas_info.steering_angle_L;
		buffer[4] = CanRxInfo.sas_info.steering_angle_H;
		break;
	case HAIMA_8S_RX_LCAS_INFO:
		buffer[2] = 0x01;
		buffer[3] = CanRxInfo.lcas_info.byte_0.byte;
		break;
	case HAIMA_8S_RX_IAL_INFO:
		buffer[2] = 0x03;
		buffer[3] = CanRxInfo.ial_info.byte_0.byte;
		buffer[4] = CanRxInfo.ial_info.f_ial_brightness;
		buffer[5] = CanRxInfo.ial_info.f_ial_color;
		break;
	default:
		flag = 0;
		break;
	}
	if (flag)
	{
		buffer[0] = HAIMA_8S_HEAD_CODE;
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

void Haima_8S_ICM_CTRL(void)
{
	if (Haima8S_SWC_SW && ++ Haima8S_SWC_Timeout >= T5S_1)
	{
		Haima8S_SWC_SW = 0;
	}
	CanTxInfo.dvd_8_info.byte_0.field.keycode = (Haima8S_Keycode == UICC_VOLUME_UP)		? 0x01
												: (Haima8S_Keycode == UICC_VOLUME_DOWN) ? 0x02
												: (Haima8S_Keycode == UICC_INFO)		? 0x03
												: (Haima8S_Keycode == UICC_SKIPB)		? 0x04
												: (Haima8S_Keycode == UICC_SKIPF)		? 0x05
																						: 0x00;
	CanTxInfo.dvd_8_info.byte_0.field.f_ctrl_sw = Haima8S_SWC_SW;
	CanTxInfo.dvd_8_info.byte_1.field.source = ((FrontSource == SOURCE_TUNER) && (radio_band < FM_BAND_NUM))	? 0x02
											   : ((FrontSource == SOURCE_TUNER) && (radio_band >= FM_BAND_NUM)) ? 0x01
											   : (FrontSource == SOURCE_BT_MUSIC)								? 0x03
											   : (FrontSource == SOURCE_USB)									? 0x04
																												: 0x00;
	CanTxInfo.dvd_8_info.byte_1.field.phone_st = (BT_INFO.mstate == BT_INCOMING)		? 0x01
												 : (BT_INFO.mstate == BT_DIALING)		? 0x03
												 : (BT_INFO.mstate == BT_CALLING_PHONE) ? 0x02
																						: 0x00;
	if (SeekProcState == Seek_Idle)
	// if(!TunerSeekBreak())
	{
		CanTxInfo.dvd_8_info.freq_H8 = (radio_band < FM_BAND_NUM) ? ((radio_freq / 10) >> 4)
																  : (radio_freq >> 4);
		CanTxInfo.dvd_8_info.byte_6.field.freq_L4 = (radio_band < FM_BAND_NUM) ? ((radio_freq / 10) & 0x0F)
																			   : (radio_freq & 0x0F);
	}
	CanTxInfo.dvd_8_info.volume = TurnOn_Volume;

	if (!strcmp_equal(&CanTxInfo.dvd_8_info.byte_0.byte, &CanTxInfoBak.dvd_8_info.byte_0.byte, sizeof(CAN_DVD_8_INFO)))
	{
		Mem_strcpy(&CanTxInfoBak.dvd_8_info.byte_0.byte, &CanTxInfo.dvd_8_info.byte_0.byte, sizeof(CAN_DVD_8_INFO));
		Haima_8S_PostMessage_3Times(CAN_POST_MSG_DVD_8);
	}
}

void Haima_8S_CanReset(void)
{
	CanMainState = CAN_MAIN_IDLE;
}

void Haima_8S_Timeout_Handler(void)
{
	F_CAN_RX_DATA = 0;
	CanRxInfo.base_info.byte_0.field.f_can_ready = 0;
	// CanRxInfo.base_info.byte_2.field.f_power_level = 0;
	// FormatMemery(&CanRxInfoBak.air_info.byte_1.byte, sizeof(CanRxInfoBak));
	PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, HAIMA_8S_RX_BASE_INFO);
	// AIR_LED_POWER_OFF;
	// CanGeneralCtrlFlag.field.power_level = 0;
	CanMainState = CAN_MAIN_IDLE;
}

void Haima_8S_MainPro(void)
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
			Haima_8S_Timeout_Handler();
		}
	}
	if (CanTxTimer)
	{
		CanTxTimer--;
	}
	if (CanTxQueueTimer != 0xFF)
	{
		CanTxQueueTimer++;
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
		if (CAN_GetFlagStatus(CAN1, CAN_FLAG_EWG) || CAN_GetFlagStatus(CAN1, CAN_FLAG_EWG) || CAN_GetFlagStatus(CAN1, CAN_FLAG_BOF) || CAN_GetReceiveErrorCounter(CAN1) >= 127 || CAN_GetLSBTransmitErrorCounter(CAN1) >= 127)
		{
			CanCheckErrorTimer++;
			if (CanCheckErrorTimer >= T2S_1)
			{
				CanCheckErrorTimer = 0;
				CanMainState = CAN_MAIN_IDLE;
				if (F_CAN_RX_DATA == 1)
					Haima_8S_Timeout_Handler();
			}
		}
		else
		{
			CanCheckErrorTimer = 0;
		}
	}

	Haima_8S_Rx_Message();
	if (F_CAN_INIT)
	{
		for (u8 i = 0; i < CAN_TX_ID_COUNT; i++)
		{
			if (CanTxTimerDict[i].ID == CanTxBuffer.message[CanTxBuffer.head].ID)
			{
				if (CanTxTimerDict[i].timer / 2 <= CanTxQueueTimer || CanTxTimerDict[i].timer == 0)
				{
					CAN1_Transmit();
					CanTxQueueTimer = 0;
				}
				break;
			}
		}
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

		CanTxInfo.dvd_G_info.byte_0.field.fl_temp = 0x3F;
		CanTxInfo.dvd_G_info.byte_1.field.fr_temp = 0x3F;

		break;
	case CAN_MAIN_NORMAL:
#if CAN_WAKEUP_FUN == 1
		if (F_CAN_RX_DATA == 0)
#else
		if (Get_ACC_Det_Flag == 0)
#endif
		{
#if TEST_CAN_FUN == 1

			// CanMainState=CAN_MAIN_SLEEP_CFG;
#else
			CanMainState = CAN_MAIN_SLEEP_CFG;
#endif
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
				CanTxTimer = T1S_1 / 2;
				Haima_8S_PostMessage(CAN_POST_MSG_DVD_4);
			}
			Haima_8S_ICM_CTRL();
		}
		break;
	case CAN_MAIN_SLEEP_CFG:
		CAN1_ClearRxMessage();
		CAN_IC_STANDBY_ON;
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
			F_CAN_SLEEP = 0;
			CanMainState = CAN_MAIN_INIT;
		}
		break;
	default:
		break;
	}
}

#endif
