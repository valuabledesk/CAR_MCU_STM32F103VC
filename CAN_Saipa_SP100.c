#include "public.h"

#if CAN_FUN_SAIPA_SP100 == 1
#define CAN_AUTOTEST 0
u32 CANSleepTime;
u32 CANSleepTime_NOW;
u8 CANSleepFlag=1;

CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_TX_INFO CanTxInfo;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
u32 CanMainTimer = T5S_1;
u32 CanNoDataTimer;
u32 CanCheckErrorTimer;

u16 CanTxTimer;
u8 CanTxErrorCounter;
u8 CanNoTxCounter;
u8 CAN_TURN_STATE;

u8 CAN_BacklightDutyCycle[] = {70, 14, 18, 28, 39, 49, 56, 70};
u8 CAN_LEDDutyCycle[] = {100, 20, 25, 40, 55, 70, 80, 100};
u16 ICMRxTimer;

u16 CanInitTxTimer;
CAN_NETWORK_MANAGEMENT NM = {.R = 0x04, .L = 0x04, .S = 0x04};
u16 CanNMTimer;
u16 BCMRxTimer;
u16 NoBCMACCOffTimer;

u8 diagMode;
CAN_DIAGNOSTIC_DATA CANDiagData;
// = {.HUTechnicalNumber = {'S', 'T', '2', '8', '4', '2', '8', '0', '5', '1'},
//									.crouseManufacturingDate = {'2', '0', '2', '0', '1', '0', '0', '1'},
//									.carModel = 0x02,
//									.carOptions.byte = 0x88,
//									.illuminationControl = 0x01,
//									.introLogo = 0x03};
u8 CANDiagData_Default_HUTechnicalNumber[] = {'S', 'T', '2', '8', '4', '2', '8', '0', '5', '1', 0, 0, 0, 0};
u8 CANDiagData_Default_crouseManufacturingDate[] = {'2', '0', '2', '0', '1', '0', '0', '1'};
u8 IDWaitForWrite;
u8 lengthWaitForWrite;
u8 lengthRecForWrite;
u8 DiagSessionTimer;
u8 hardwareResetTimer;

u8 F_DataWaitForRead;
u16 lengthWaitForRead;
u8 lengthReaded;
u8 IDWaitForRead;
u8 *pDataWaitForRead;
u8 indexWaitForRead;
u8 waitForReadTimer;

#if CAN_AUTOTEST == 1
u8 CANAutotestReverse;
u16 CANAutotestTimer;
#endif

#if TEST_CAN_FUN == 1
u32 CanTestTimer;
int test_time;
int test;
#endif

void Saipa_SP100_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8] = {0};

	switch (index)
	{
	case CAN_POST_MSG_MMU:
		data[0] = RTC_TimeInfo.seconds;
		data[1] = RTC_TimeInfo.minutes;
		data[2] = ((RTC_TimeInfo.hours == 0) ? 12 : (RTC_TimeInfo.hours > 12) ? RTC_TimeInfo.hours - 12
																			  : RTC_TimeInfo.hours) |
				  ((CanTxInfo.mmu_info.timeFormat12 == 0) ? 0 : (CanTxInfo.mmu_info.timeFormat12 == 1 && RTC_TimeInfo.hours >= 12) ? (2 << 6)
																																   : (1 << 6));
		data[3] = !CANDiagData.carOptions.field.BSD;
		if (APP_Status == APP_READY)
		{
			data[4] = CanTxInfo.mmu_info.day;
			data[5] = CanTxInfo.mmu_info.month;
			data[6] = CanTxInfo.mmu_info.year | CanTxInfo.mmu_info.dateFormatIranian << 7;
		}
		else
		{
			data[4] = RTC_TimeInfo.day;
			data[5] = RTC_TimeInfo.month;
			data[6] = RTC_TimeInfo.year;
		}
		CAN1_TxFrame(CAN_ID_MMU, data, 8);
		break;
	case CAN_POST_MSG_NM:
		//		if (NM.current_state == NM_BUS_SLEEP && CanTxInfo.nm_info.byte_1.field.nm_sleep_indication != 1)
		//		{
		//			break;
		//		}
//		data[0] = CanTxInfo.nm_info.dest_id;
		if (CanTxInfo.nm_info.byte_1.field.nm_alive)
		{
			data[0] = MMU_SOURCE_ID;
		}
		else
		{
			data[0] = NM.L;
		}
		data[1] = CanTxInfo.nm_info.byte_1.byte | NM.Sleep.ack << 5 | NM.Sleep.ind << 4;
		CAN1_TransBytefraem(CAN_ID_NM, data, 8);
		NM.NMMessageTransmitted = 1;
		NM.TXMessageType.byte = data[1];
//		CAN1_TxFrame(CAN_ID_NM, data, 8);
		break;
	case CAN_POST_MSG_PHYSICAL_RES:
		data[0] = CanTxInfo.diag_info.PCI;
		data[1] = CanTxInfo.diag_info.byte_1;
		data[2] = CanTxInfo.diag_info.byte_2;
		data[3] = CanTxInfo.diag_info.byte_3;
		data[4] = CanTxInfo.diag_info.byte_4;
		data[5] = CanTxInfo.diag_info.byte_5;
		data[6] = CanTxInfo.diag_info.byte_6;
		data[7] = CanTxInfo.diag_info.byte_7;
		CAN1_TxFrame(CAN_ID_PHYSICAL_RES, data, 8);
		DiagSessionTimer = T200MS_1;
		break;
#if CAN_AUTOTEST == 1
	case CAN_POST_MSG_BODY_1_AUTO_TEST:
		data[4] = CANAutotestReverse << 3;
		break;
#endif
	default:
		break;
	}
}

void Saipa_SP100_Diagnostic_Data_Write(u8 *buffer, u8 index)
{
	u8 length;
	u8 writeFinish = 0;
	if (lengthWaitForWrite > 7)
	{
		length = 7;
	}
	else
	{
		length = lengthWaitForWrite;
		writeFinish = 1;
	}
	lengthRecForWrite = (lengthRecForWrite > 7) ? (lengthRecForWrite - 7) : 0;
	if (lengthWaitForWrite)
	{
		switch (IDWaitForWrite)
		{
		case DIAGNOSTIC_DATA_ID_HU_CROUSE_CODE:
			Mem_strcpy(&CANDiagData.HUCrouseCode[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
			break;
		case DIAGNOSTIC_DATA_ID_DU_CROUSE_CODE:
			Mem_strcpy(&CANDiagData.DUCrouseCode[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
			break;
		case DIAGNOSTIC_DATA_ID_HU_TECHNICAL_NUMBER:
			Mem_strcpy(&CANDiagData.HUTechnicalNumber[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
		case DIAGNOSTIC_DATA_ID_DU_TECHNICAL_NUMBER:
			Mem_strcpy(&CANDiagData.DUTechnicalNumber[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
			break;
		case DIAGNOSTIC_DATA_ID_CROUSE_MANUFACTURING_DATE:
			Mem_strcpy(&CANDiagData.crouseManufacturingDate[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
			break;
		case DIAGNOSTIC_DATA_ID_PRODUCT_SERIAL_NUMBER:
			Mem_strcpy(&CANDiagData.productSerialNumber[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
			break;
		case DIAGNOSTIC_DATA_ID_VEHICLE_IDENTIFICATION_NUMBER:
			Mem_strcpy(&CANDiagData.vehicleIdentificationNumber[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
			if	(lengthWaitForWrite == 0)
			{
				CANDiagData.VINWritten = 1;
			}
			break;
		case DIAGNOSTIC_DATA_ID_CUSTOMER_EOL_OPERATION_DATE:
			Mem_strcpy(&CANDiagData.customerEOLOperationDate[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
			break;
		case DIAGNOSTIC_DATA_ID_AFTERSALES_LAST_OPERATION_DATE:
			Mem_strcpy(&CANDiagData.aftersalesLastOperationDate[4 + (index - 1) * 7], &buffer[1], length);
			lengthWaitForWrite -= length;
			break;
		}
	}
	if (lengthRecForWrite == 0)
	{
		CanTxInfo.diag_info.PCI = 0x02;
		CanTxInfo.diag_info.byte_1 = DIAGNOSTIC_SID_WRITE_DATA_BY_LOCAL_IDENTIFIER + 0x40;
		CanTxInfo.diag_info.byte_2 = IDWaitForWrite;
		Saipa_SP100_PostMessage(CAN_POST_MSG_PHYSICAL_RES);
		EEPROM_Save_CANDiagnostic();
		PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_DIAGNOSTIC);
	}
}

void Saipa_SP100_Diagnostic_Data_Read()
{
	if (F_DataWaitForRead == 0)
	{
		CanTxInfo.diag_info.PCI = 0x10 | ((lengthWaitForRead + 2) >> 8);
		CanTxInfo.diag_info.byte_1 = (lengthWaitForRead + 2) & 0xff;
		CanTxInfo.diag_info.byte_2 = DIAGNOSTIC_SID_READ_DATA_BY_LOCAL_IDENTIFIER + 0x40;
		CanTxInfo.diag_info.byte_3 = IDWaitForRead;
		Mem_strcpy(&CanTxInfo.diag_info.byte_4, &pDataWaitForRead[0], 4);
		lengthWaitForRead -= 4;
		lengthReaded = 4;
		if (lengthWaitForRead)
		{
			F_DataWaitForRead = 1;
			indexWaitForRead = 1;
		}
	}
	else
	{
		memset(&CanTxInfo.diag_info.byte_1, 0xaa, 7);
		CanTxInfo.diag_info.PCI = 0x20 | indexWaitForRead;
		indexWaitForRead++;
		if (lengthWaitForRead > 7)
		{
			Mem_strcpy(&CanTxInfo.diag_info.byte_1, &pDataWaitForRead[lengthReaded], 7);
			lengthWaitForRead -= 7;
			lengthReaded += 7;
			waitForReadTimer = T100MS_1;
		}
		else
		{
			F_DataWaitForRead = 0;
			Mem_strcpy(&CanTxInfo.diag_info.byte_1, &pDataWaitForRead[lengthReaded], lengthWaitForRead);
			lengthReaded += lengthWaitForRead;
			lengthWaitForRead = 0;
			indexWaitForRead = 0;
		}
	}
	Saipa_SP100_PostMessage(CAN_POST_MSG_PHYSICAL_RES);
}

void Saipa_SP100_Diagnostic(u8 *buffer)
{
	u8 SID;
	u8 sendLongData = 0;
	u8 diagResLength;
	u8 NRC = 0;
	//	if (buffer[1] != DIAGNOSTIC_SID_START_DIAG_SESSION_POSITIVE || !diagMode)
	//	{
	//		return;
	//	}
	memset(&CanTxInfo.diag_info.byte_2, 0xaa, 6);
	if (buffer[0] >> 4 == 2)
	{
		Saipa_SP100_Diagnostic_Data_Write(buffer, buffer[0] & 0x0f);
		return;
	}
	else if (buffer[0] >> 4 == 0)
	{
		SID = buffer[1];
	}
	else
	{
		SID = buffer[2];
	}
	CanTxInfo.diag_info.byte_1 = SID + 0x40;
	diagResLength = 1;
	//	if (diagMode == 0 && (SID == DIAGNOSTIC_SID_WRITE_DATA_BY_LOCAL_IDENTIFIER || SID == DIAGNOSTIC_SID_ECU_RESET || SID == DIAGNOSTIC_SID_READ_DTC || SID == DIAGNOSTIC_SID_CLEAR_DTC))
	//	{
	//		NRC = 0x7f;
	//	}
	//	else
	{
		switch (SID)
		{
		case DIAGNOSTIC_SID_START_DIAG_SESSION_POSITIVE:
			diagMode = 1;
			CanTxInfo.diag_info.byte_2 = 0x90; // Diag mode
			diagResLength++;
			break;
		case DIAGNOSTIC_SID_READ_DATA_BY_LOCAL_IDENTIFIER:
		{
			switch (buffer[2])
			{
			case DIAGNOSTIC_DATA_ID_HU_CROUSE_CODE:
				pDataWaitForRead = CANDiagData.HUCrouseCode;
				lengthWaitForRead = sizeof(CANDiagData.HUCrouseCode);
				break;
			case DIAGNOSTIC_DATA_ID_DU_CROUSE_CODE:
				pDataWaitForRead = CANDiagData.DUCrouseCode;
				lengthWaitForRead = sizeof(CANDiagData.DUCrouseCode);
				break;
			case DIAGNOSTIC_DATA_ID_HU_TECHNICAL_NUMBER:
				pDataWaitForRead = CANDiagData.HUTechnicalNumber;
				lengthWaitForRead = sizeof(CANDiagData.HUTechnicalNumber);
				break;
			case DIAGNOSTIC_DATA_ID_DU_TECHNICAL_NUMBER:
				pDataWaitForRead = CANDiagData.DUTechnicalNumber;
				lengthWaitForRead = sizeof(CANDiagData.DUTechnicalNumber);
				break;
			case DIAGNOSTIC_DATA_ID_CROUSE_MANUFACTURING_DATE:
				pDataWaitForRead = CANDiagData.crouseManufacturingDate;
				lengthWaitForRead = sizeof(CANDiagData.crouseManufacturingDate);
				break;
			case DIAGNOSTIC_DATA_ID_PRODUCT_SERIAL_NUMBER:
				pDataWaitForRead = CANDiagData.productSerialNumber;
				lengthWaitForRead = sizeof(CANDiagData.productSerialNumber);
				break;
			case DIAGNOSTIC_DATA_ID_VEHICLE_IDENTIFICATION_NUMBER:
				pDataWaitForRead = CANDiagData.vehicleIdentificationNumber;
				lengthWaitForRead = sizeof(CANDiagData.vehicleIdentificationNumber);
				break;
			case DIAGNOSTIC_DATA_ID_CUSTOMER_EOL_OPERATION_DATE:
				pDataWaitForRead = CANDiagData.customerEOLOperationDate;
				lengthWaitForRead = sizeof(CANDiagData.customerEOLOperationDate);
				break;
			case DIAGNOSTIC_DATA_ID_AFTERSALES_LAST_OPERATION_DATE:
				pDataWaitForRead = CANDiagData.aftersalesLastOperationDate;
				lengthWaitForRead = sizeof(CANDiagData.aftersalesLastOperationDate);
				break;
			case DIAGNOSTIC_DATA_ID_CAR_MODEL:
				CanTxInfo.diag_info.byte_3 = CANDiagData.carModel;
				diagResLength++;
				break;
			case DIAGNOSTIC_DATA_ID_CAR_OPTIONS:
				CanTxInfo.diag_info.byte_3 = CANDiagData.carOptions.byte;
				diagResLength++;
				break;
			case DIAGNOSTIC_DATA_ID_HANDBRAKE_CONTROL:
				CanTxInfo.diag_info.byte_3 = CANDiagData.handbrakeControl;
				diagResLength++;
				break;
			case DIAGNOSTIC_DATA_ID_REVERSE_GEAR_CONTROL:
				CanTxInfo.diag_info.byte_3 = CANDiagData.reverseGearControl;
				diagResLength++;
				break;
			case DIAGNOSTIC_DATA_ID_ILLUMINATION_CONTROL:
				CanTxInfo.diag_info.byte_3 = CANDiagData.illuminationControl;
				diagResLength++;
				break;
			case DIAGNOSTIC_DATA_ID_FAULTS_DISPLAY:
				CanTxInfo.diag_info.byte_3 = CANDiagData.faultsDisplay;
				diagResLength++;
				break;
			case DIAGNOSTIC_DATA_ID_INTRO_LOGO:
				CanTxInfo.diag_info.byte_3 = CANDiagData.introLogo;
				diagResLength++;
				break;
			default:
				return;
			}
			if (buffer[2] < DIAGNOSTIC_DATA_ID_CAR_MODEL)
			{
				IDWaitForRead = buffer[2];
				Saipa_SP100_Diagnostic_Data_Read();
				return;
			}
			else
			{
				CanTxInfo.diag_info.byte_2 = buffer[2];
				diagResLength++;
			}
			break;
		}
		case DIAGNOSTIC_SID_WRITE_DATA_BY_LOCAL_IDENTIFIER:
		{
			if (buffer[0] >> 4 == 0x01 && buffer[2] < DIAGNOSTIC_DATA_ID_CAR_MODEL)
			{
				lengthRecForWrite = buffer[1] - 6;
				switch (buffer[3])
				{
				case DIAGNOSTIC_DATA_ID_HU_CROUSE_CODE:
					Mem_strcpy(CANDiagData.HUCrouseCode, &buffer[4], 4);
					lengthWaitForWrite = 8;
					break;
				case DIAGNOSTIC_DATA_ID_DU_CROUSE_CODE:
					Mem_strcpy(CANDiagData.DUCrouseCode, &buffer[4], 4);
					lengthWaitForWrite = 8;
					break;
				case DIAGNOSTIC_DATA_ID_HU_TECHNICAL_NUMBER:
					Mem_strcpy(CANDiagData.HUTechnicalNumber, &buffer[4], 4);
					lengthWaitForWrite = 10;
					break;
				case DIAGNOSTIC_DATA_ID_DU_TECHNICAL_NUMBER:
					Mem_strcpy(CANDiagData.DUTechnicalNumber, &buffer[4], 4);
					lengthWaitForWrite = 10;
					break;
				case DIAGNOSTIC_DATA_ID_CROUSE_MANUFACTURING_DATE:
					Mem_strcpy(CANDiagData.crouseManufacturingDate, &buffer[4], 4);
					lengthWaitForWrite = 4;
					break;
				case DIAGNOSTIC_DATA_ID_PRODUCT_SERIAL_NUMBER:
					Mem_strcpy(CANDiagData.productSerialNumber, &buffer[4], 4);
					lengthWaitForWrite = 13;
					break;
				case DIAGNOSTIC_DATA_ID_VEHICLE_IDENTIFICATION_NUMBER:
					if (CANDiagData.VINWritten)
					{
						NRC = 0x31;
					}
					else
					{
						Mem_strcpy(CANDiagData.vehicleIdentificationNumber, &buffer[4], 4);
						lengthWaitForWrite = 13;
					}
					break;
				case DIAGNOSTIC_DATA_ID_CUSTOMER_EOL_OPERATION_DATE:
					Mem_strcpy(CANDiagData.customerEOLOperationDate, &buffer[4], 4);
					lengthWaitForWrite = 4;
					break;
				case DIAGNOSTIC_DATA_ID_AFTERSALES_LAST_OPERATION_DATE:
					Mem_strcpy(CANDiagData.aftersalesLastOperationDate, &buffer[4], 4);
					lengthWaitForWrite = 4;
					break;
				}
				if (NRC == 0)
				{
					IDWaitForWrite = buffer[3];
					CanTxInfo.diag_info.PCI = 0x30; // Flow control
					CanTxInfo.diag_info.byte_1 = 0;
					CanTxInfo.diag_info.byte_2 = 0x0A;
					Saipa_SP100_PostMessage(CAN_POST_MSG_PHYSICAL_RES);
					return;
				}
			}
			else
			{
				switch (buffer[2])
				{
				case DIAGNOSTIC_DATA_ID_CAR_MODEL:
					if (buffer[3] == 0x02 || buffer[3] == 0x03)
					{
						CANDiagData.carModel = buffer[3];
					}
					else
					{
						NRC = 0x31;
					}
					break;
				case DIAGNOSTIC_DATA_ID_CAR_OPTIONS:
					CANDiagData.carOptions.byte = buffer[3];
					break;
				case DIAGNOSTIC_DATA_ID_HANDBRAKE_CONTROL:
					CANDiagData.handbrakeControl = buffer[3];
					break;
				case DIAGNOSTIC_DATA_ID_REVERSE_GEAR_CONTROL:
					CANDiagData.reverseGearControl = buffer[3];
					break;
				case DIAGNOSTIC_DATA_ID_ILLUMINATION_CONTROL:
					CANDiagData.illuminationControl = buffer[3];
					break;
				case DIAGNOSTIC_DATA_ID_FAULTS_DISPLAY:
					CANDiagData.faultsDisplay = buffer[3];
					break;
				case DIAGNOSTIC_DATA_ID_INTRO_LOGO:
					CANDiagData.introLogo = buffer[3];
					break;
				default:
					NRC = 0x12;
					break;
				}
				CanTxInfo.diag_info.byte_2 = buffer[2];
				diagResLength++;
				EEPROM_Save_CANDiagnostic();
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_DIAGNOSTIC);
			}
			break;
		}
		case DIAGNOSTIC_SID_CLEAR_DTC:
			CanTxInfo.diag_info.byte_2 = buffer[2];
			CanTxInfo.diag_info.byte_3 = buffer[3];
			diagResLength += 2;
			break;
		case DIAGNOSTIC_SID_READ_DTC:
			CanTxInfo.diag_info.byte_2 = 0;
			diagResLength++;
			break;
		case DIAGNOSTIC_SID_ACTUATORS:
			CanTxInfo.diag_info.byte_2 = buffer[2];
			if (buffer[3] == 0)
			{
				CanTxInfo.diag_info.byte_3 = 0x01;
				switch (buffer[2])
				{
				case 0x01:
					break;
				case 0x02:
					PostKeyCode(UICC_VOLUME_UP, REMOTE);
					break;
				case 0x03:
					PostKeyCode(UICC_VOLUME_DOWN, REMOTE);
					break;
				case 0x04:
					PostKeyCode(UICC_MUTE, REMOTE);
					break;
				case 0x05:
					PostKeyCode(UICC_BEEP_ONLY_TS, REMOTE);
					break;
				default:
					NRC = 0x12;
					break;
				}
			}
			else
			{
				CanTxInfo.diag_info.byte_3 = buffer[3];
			}
			CanTxInfo.diag_info.byte_4 = 0;
			diagResLength += 3;
			break;
		case DIAGNOSTIC_SID_TESETER:
			break;
		case DIAGNOSTIC_SID_ECU_RESET:
			if (buffer[2] == 0xb0)
			{
				hardwareResetTimer = T200MS_1;
			}
			else
			{
				NRC = 0x12;
			}
			break;
		default:
			NRC = 0x11;
			break;
		}
	}
	if (NRC)
	{
		diagResLength = 3;
		CanTxInfo.diag_info.byte_1 = DIAGNOSTIC_SID_NR;
		CanTxInfo.diag_info.byte_2 = SID;
		CanTxInfo.diag_info.byte_3 = NRC;
	}
	CanTxInfo.diag_info.PCI = diagResLength;
	Saipa_SP100_PostMessage(CAN_POST_MSG_PHYSICAL_RES);
}

void Saipa_SP100_Rx_Message(void)
{
	if (CanRxBuffer.head != CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message = CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID = 0;
		CanRxBuffer.head = (CanRxBuffer.head + 1) % CAN_RX_BUFFER_LENGTH;
		//		printf("CAN RX: %x, ", message.ID);
		//		for(int i=0; i<8; i++)
		//		{
		//			printf("%x ", message.Data[i]);
		//			if(i==7)
		//				printf("\n\r");
		//		}
		switch (message.ID)
		{
			//		case CAN_ID_TEST:
			//			break;
		case CAN_ID_EMS_1:
			CanRxInfo.ems_info.veh_speed = message.Data[0];
			CanRxInfo.ems_info.eng_speed_L8 = message.Data[1];
			CanRxInfo.ems_info.eng_speed_H5 = message.Data[2] & 0x1F;
			if (!strcmp_equal(&CanRxInfo.ems_info.veh_speed, &CanRxInfoBak.ems_info.veh_speed, sizeof(CAN_EMS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.ems_info.veh_speed, &CanRxInfo.ems_info.veh_speed, sizeof(CAN_EMS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_EMS_INFO);
			}
			break;
		case CAN_ID_CHASSIS:
			CanRxInfo.chassis_info.steering_wheel_angle_L8 = message.Data[1];
			CanRxInfo.chassis_info.steering_wheel_angle_H8 = message.Data[2];
			CanRxInfo.chassis_info.f_parking_brake_activation = (message.Data[5] & 0x04) >> 2;
			CanGeneralCtrlFlag.field.parking_on_off = (message.Data[5] & 0x04) >> 2;
			if (!strcmp_equal(&CanRxInfo.chassis_info.steering_wheel_angle_L8, &CanRxInfoBak.chassis_info.steering_wheel_angle_L8, sizeof(CAN_CHASSIS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.chassis_info.steering_wheel_angle_L8, &CanRxInfo.chassis_info.steering_wheel_angle_L8, sizeof(CAN_CHASSIS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_CHASSIS_INFO);
			}
			break;
		case CAN_ID_BODY_1:
			CanRxInfo.body_info.f_door = (message.Data[2] & 0x7F) ^ 0x3F;
			CanRxInfo.body_info.outdoor_ambient_temperature = message.Data[3];
			CanRxInfo.ems_info.powerDistributionStep = message.Data[0] & 0x03;
			CanGeneralCtrlFlag.field.reverse_on_off = (message.Data[4] & 0x08) >> 3;
			if (!strcmp_equal(&CanRxInfo.body_info.f_door, &CanRxInfoBak.body_info.f_door, sizeof(CAN_BODY_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.body_info.f_door, &CanRxInfo.body_info.f_door, sizeof(CAN_BODY_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_BODY_INFO);
			}
			break;
		case CAN_ID_BODY_2:
			CanRxInfo.body_info.byte_2.field.f_position_lamps = (message.Data[0] & 0x30) >> 4;
			CanRxInfo.body_info.byte_2.field.f_seat_belt_led = (message.Data[5] & 0xF0) >> 4;
			if ((message.Data[0] & 0x30) >> 4 == 1)
			{
				CanGeneralCtrlFlag.field.ill_onoff = 1;
			}
			else
			{
				CanGeneralCtrlFlag.field.ill_onoff = 0;
			}
			// if (!strcmp_equal(&CanRxInfo.body_info.f_door, &CanRxInfoBak.body_info.f_door, sizeof(CAN_BODY_INFO)))
			// {
			// 	Mem_strcpy(&CanRxInfoBak.body_info.f_door, &CanRxInfo.body_info.f_door, sizeof(CAN_BODY_INFO));
			// 	PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_BODY_INFO);
			// }
			break;
		case CAN_ID_BODY_3:
			CanRxInfo.body_info.odo_L8 = message.Data[4];
			CanRxInfo.body_info.odo_ML8 = message.Data[5];
			CanRxInfo.body_info.odo_MH8 = message.Data[6];
			CanRxInfo.body_info.odo_H8 = message.Data[7];
			//			if (!strcmp_equal(&CanRxInfo.body_info.f_door, &CanRxInfoBak.body_info.f_door, sizeof(CAN_BODY_INFO)))
			//			{
			//				Mem_strcpy(&CanRxInfoBak.body_info.f_door, &CanRxInfo.body_info.f_door, sizeof(CAN_BODY_INFO));
			//				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_BODY_INFO);
			//			}
			break;
		case CAN_ID_ASSIST:
			CanRxInfo.assist_info.byte_0.byte = message.Data[0];
			CanRxInfo.assist_info.rpa_rl_dist = message.Data[1];
			CanRxInfo.assist_info.rpa_rr_dist = message.Data[2];
			CanRxInfo.assist_info.f_bsd = message.Data[3];
			CanRxInfo.assist_info.bsd_rl_dist_L8 = message.Data[4];
			CanRxInfo.assist_info.byte_5.byte = message.Data[5];
			CanRxInfo.assist_info.bsd_rr_dist_L8 = message.Data[6];
			CanRxInfo.assist_info.byte_5.field.bsd_rr_dist_H1 = message.Data[7] & 0x01;
			if (!strcmp_equal(&CanRxInfo.assist_info.byte_0.byte, &CanRxInfoBak.assist_info.byte_0.byte, sizeof(CAN_ASSIST_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.assist_info.byte_0.byte, &CanRxInfo.assist_info.byte_0.byte, sizeof(CAN_ASSIST_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_ASSIST_INFO);
			}
			break;
		case CAN_ID_TPMS_1:
			CanRxInfo.tpms_info.fl_pres = message.Data[0];
			CanRxInfo.tpms_info.fl_temp = message.Data[1];
			CanRxInfo.tpms_info.fr_pres = message.Data[2];
			CanRxInfo.tpms_info.fr_temp = message.Data[3];
			CanRxInfo.tpms_info.rl_pres = message.Data[4];
			CanRxInfo.tpms_info.rl_temp = message.Data[5];
			CanRxInfo.tpms_info.rr_pres = message.Data[6];
			CanRxInfo.tpms_info.rr_temp = message.Data[7];
			if (!strcmp_equal(&CanRxInfo.tpms_info.fl_pres, &CanRxInfoBak.tpms_info.fl_pres, sizeof(CAN_TPMS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.tpms_info.fl_pres, &CanRxInfo.tpms_info.fl_pres, sizeof(CAN_TPMS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_TPMS_INFO);
			}
			break;
		case CAN_ID_TPMS_2:
			CanRxInfo.tpms_info.f_tpms_error = message.Data[1];
			CanRxInfo.tpms_info.f_tpms_self_local = message.Data[2];
			CanRxInfo.tpms_info.f_fl = message.Data[3];
			CanRxInfo.tpms_info.f_fr = message.Data[4];
			CanRxInfo.tpms_info.f_rl = message.Data[5];
			CanRxInfo.tpms_info.f_rr = message.Data[6];
			if (!strcmp_equal(&CanRxInfo.tpms_info.fl_pres, &CanRxInfoBak.tpms_info.fl_pres, sizeof(CAN_TPMS_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.tpms_info.fl_pres, &CanRxInfo.tpms_info.fl_pres, sizeof(CAN_TPMS_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_TPMS_INFO);
			}
			break;
		case CAN_ID_PHYSICAL_REQ:
			DiagSessionTimer = T200MS_1;
			if (message.Data[0] == 0x30)
			{
				if (F_DataWaitForRead)
				{
					F_DataWaitForRead = 2;
				}
				break;
			}
			Saipa_SP100_Diagnostic(message.Data);
			break;
		case CAN_ID_BCM_NM:
			BCMRxTimer = T2S_1;
		case CAN_ID_ICM_NM:
			// NM.NMrxcount = 0;
			NM.NMMessageRecieved = 1;
			NM.NMReceived=1;
			NM.RXMessageType.byte = message.Data[1];
			NM.S = message.ID & 0xFF;
			NM.D = message.Data[0];
			if (NM.Networkstatus.bussleep && NM.S == 0x01 && !NM.RXMessageType.field.SleepAck && !NM.RXMessageType.field.SleepInd)
			{
				NM.gotoModeAwake = 1;
			}
			else if (((NM.D == MMU_SOURCE_ID && NM.RXMessageType.field.Ring && NM.current_state == NMNormal) || NM.current_state == NMLimpHome) && NM.RXMessageType.field.SleepInd)
			{
				NM.gotoModeBusSleep = 1;
			}
			// if (message.Data[1] >> 2 != 1)
			// {
			// 	if ((NM.L == NM.R) ||
			// 		(NM.L < NM.R && (NM.S < NM.L || NM.S >= NM.R)) ||
			// 		(NM.L >= NM.R && (NM.S < NM.L && NM.S >= NM.R)))
			// 	{
			// 		NM.L = NM.S;
			// 	}
			// }
			// if (NM.current_state == NM_NORMAL)
			// {
			// 	if (message.Data[0] == 0x04 && (message.Data[1] & 0x02))
			// 	{
			// 		NM.f_Ring = 1;
			// 		CanTxInfo.nm_info.byte_1.field.nm_ring = 1;
			// 	}
			// 	else
			// 	{
			// 		NM.f_Skipped_Checking = 1;
			// 	}
			// }
			// if (NM.D == MMU_SOURCE_ID && !Get_ACC_Det_Flag)
			// {
			// 	if ((message.Data[1] & 0x30) == 0x30)
			// 	{
			// 		CanNoDataTimer = T300MS_1;
			// 		return;
			// 	}
			// 	else if ((message.Data[1] & 0x10) >> 4)
			// 	{

			// 		if (NM.f_Sleep_Indication_NO_ACC == 2 && NM.S == 0x02)
			// 		{
			// 			NM.f_Sleep_Indication_NO_ACC = 3;
			// 			break;
			// 		}
			// 		NM.f_Sleep_Indication = 1;
			// 		NM.current_state = NM_BUS_SLEEP;
			// 		NM.NMtxcount = 0;
			// 		CanNMTimer = 0;
			// 		break;
			// 	}
			// }
			// if (NM.current_state == NM_LIMPHOME)
			// {
			// 	NM.current_state = NM_INIT;
			// }
			// NM.f_Sleep_Indication = 0;
			break;
		case CAN_ID_ICM:
			CanRxInfo.body_info.byte_2.field.low_fuel_lamp_status = (message.Data[5] & 0x30) >> 4;
			if (!strcmp_equal(&CanRxInfo.body_info.f_door, &CanRxInfoBak.body_info.f_door, sizeof(CAN_BODY_INFO)))
			{
				Mem_strcpy(&CanRxInfoBak.body_info.f_door, &CanRxInfo.body_info.f_door, sizeof(CAN_BODY_INFO));
				PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_BODY_INFO);
			}
			TFT_Backlight_CAN_Level = CAN_BacklightDutyCycle[message.Data[0] >> 5 & 0x07];
			CanGeneralCtrlFlag.field.illumi_level = CAN_LEDDutyCycle[message.Data[0] >> 5 & 0x07];
			ICMRxTimer = T300MS_1;
			break;
		default:
			break;
		}
		// CanRxInfo.base_info.byte_0.field.f_can_ready = 1;
		// if (F_CAN_RX_DATA == 0)
		// {
		// 	PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_BASIC_INFO);
		// }
		F_CAN_RX_DATA = 1;
		F_CAN_SLEEP = 0;
		CanNoDataTimer = T2S_1;
		CAN1_ClearErrorTimer();
	}
}

void Saipa_SP100_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id = buffer[1];

	if (Get_ACC_Det_Flag == 0)
	{
		return;
	}

	switch (cmd_id)
	{
	case SAIPA_SP100_TX_REQ_CMD:
		break;	
	case SAIPA_SP100_TX_MMU_CMD:
		CanTxInfo.mmu_info.timeFormat12 = buffer[3];
		CanTxInfo.mmu_info.dateFormatIranian = buffer[4];
		CanTxInfo.mmu_info.f_bsd_switch = buffer[6];
		CanTxInfo.mmu_info.day = buffer[9];
		CanTxInfo.mmu_info.month = buffer[8];
		CanTxInfo.mmu_info.year = buffer[7];
		Saipa_SP100_PostMessage(CAN_POST_MSG_MMU);
		break;
	default:
		break;
	}
}

void Saipa_SP100_TxAppDataPro(u8 cmd_id, u8 *buffer, u16 *length)
{
	u8 i;
	u8 checksum = 0;
	u8 flag = 1;

	switch (cmd_id)
	{
	case SAIPA_SP100_RX_EMS_INFO:
		buffer[2] = 0x04;
		buffer[3] = CanRxInfo.ems_info.veh_speed;
		buffer[4] = CanRxInfo.ems_info.eng_speed_L8;
		buffer[5] = CanRxInfo.ems_info.eng_speed_H5;
		buffer[6] = CanRxInfo.ems_info.powerDistributionStep;
		break;
	case SAIPA_SP100_RX_CHASSIS_INFO:
		buffer[2] = 0x03;
		buffer[3] = CanRxInfo.chassis_info.steering_wheel_angle_L8;
		buffer[4] = CanRxInfo.chassis_info.steering_wheel_angle_H8;
		buffer[5] = CanRxInfo.chassis_info.f_parking_brake_activation;
		break;
	case SAIPA_SP100_RX_BODY_INFO:
		buffer[2] = 0x07;
		buffer[3] = CanRxInfo.body_info.f_door;
		buffer[4] = CanRxInfo.body_info.outdoor_ambient_temperature;
		if (CANDiagData.faultsDisplay & 0x01)
		{
			buffer[5] = CanRxInfo.body_info.byte_2.byte & 0x3f;
		}
		else
		{
			buffer[5] = CanRxInfo.body_info.byte_2.byte;
		}
		buffer[6] = CanRxInfo.body_info.odo_L8;
		buffer[7] = CanRxInfo.body_info.odo_ML8;
		buffer[8] = CanRxInfo.body_info.odo_MH8;
		buffer[9] = CanRxInfo.body_info.odo_H8;
		break;
	case SAIPA_SP100_RX_ASSIST_INFO:
		buffer[2] = 0x07;
		buffer[3] = CanRxInfo.assist_info.byte_0.byte;
		buffer[4] = CanRxInfo.assist_info.rpa_rl_dist;
		buffer[5] = CanRxInfo.assist_info.rpa_rr_dist;
		buffer[6] = CanRxInfo.assist_info.f_bsd;
		buffer[7] = CanRxInfo.assist_info.bsd_rl_dist_L8;
		buffer[8] = CanRxInfo.assist_info.byte_5.byte;
		buffer[9] = CanRxInfo.assist_info.bsd_rr_dist_L8;
		break;
	case SAIPA_SP100_RX_TPMS_INFO:
		buffer[2] = 0x0E;
		buffer[3] = CanRxInfo.tpms_info.fl_pres;
		buffer[4] = CanRxInfo.tpms_info.fl_temp;
		buffer[5] = CanRxInfo.tpms_info.fr_pres;
		buffer[6] = CanRxInfo.tpms_info.fr_temp;
		buffer[7] = CanRxInfo.tpms_info.rl_pres;
		buffer[8] = CanRxInfo.tpms_info.rl_temp;
		buffer[9] = CanRxInfo.tpms_info.rr_pres;
		buffer[10] = CanRxInfo.tpms_info.rr_temp;
		buffer[11] = CanRxInfo.tpms_info.f_tpms_error;
		buffer[12] = CanRxInfo.tpms_info.f_tpms_self_local;
		buffer[13] = CanRxInfo.tpms_info.f_fl;
		buffer[14] = CanRxInfo.tpms_info.f_fr;
		buffer[15] = CanRxInfo.tpms_info.f_rl;
		buffer[16] = CanRxInfo.tpms_info.f_rr;
		break;
	case SAIPA_SP100_DIAGNOSTIC:
		buffer[2] = 0x03;
		buffer[3] = CANDiagData.carOptions.byte;
		buffer[4] = F_CAN_RX_DATA;
		buffer[5] = CANDiagData.carModel;
		break;
	default:
		flag = 0;
		break;
	}
	if (flag)
	{
		buffer[0] = SAIPA_SP100_HEAD_CODE;
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

void NM_Send_Alive_Message()
{
	CanTxInfo.nm_info.byte_1.field.nm_alive = 1;
	Saipa_SP100_PostMessage(CAN_POST_MSG_NM);
	CanTxInfo.nm_info.byte_1.field.nm_alive = 0;
}

void NM_Send_Ring_Message(u8 withBitSleepAck)
{
	CanTxInfo.nm_info.byte_1.field.nm_ring = 1;
	if (withBitSleepAck)
	{
		CanTxInfo.nm_info.byte_1.field.nm_sleep_ack = 1;
	}

	Saipa_SP100_PostMessage(CAN_POST_MSG_NM);
	CanTxInfo.nm_info.byte_1.field.nm_ring = 0;
	CanTxInfo.nm_info.byte_1.field.nm_sleep_ack = 0;
}

void NM_Send_LimpHome_Message()
{
	CanTxInfo.nm_info.byte_1.field.nm_limphome = 1;
	Saipa_SP100_PostMessage(CAN_POST_MSG_NM);
	CanTxInfo.nm_info.byte_1.field.nm_limphome = 0;
}

void NM_Set_Alarm(ALARM_TYPE alarmType)
{
	switch (alarmType)
	{
	case TTyp:
		NM.TTypTimer = T_TYP;
		break;
	case TMax:
		NM.TMaxTimer = T_MAX;
		break;
	case TError:
		NM.TErrorTimer = T_ERROR;
		break;
	case TWaitBusSleep:
		NM.TWaitBusSleepTimer = T_WAITBUSSLEEP;
		break;
	case TSleepACK:
		NM.TSendSleepAckTimer = T_SLEEPACK;
		break;
	default:
		break;
	}
}
void NM_Cancel_Alarm(ALARM_TYPE alarmType)
{
	switch (alarmType)
	{
	case TTyp:
		NM.TTypTimer = 0;
		NM.timeoutTTyp = 0;
		break;
	case TMax:
		NM.TMaxTimer = 0;
		NM.timeoutTMax = 0;
		break;
	case TError:
		NM.TErrorTimer = 0;
		NM.timeoutTError = 0;
		break;
	case TWaitBusSleep:
		NM.TWaitBusSleepTimer = 0;
		NM.timeoutTWaitBusSleep = 0;
		break;
	default:
		break;
	}
}

void Determine_Logical_Successor()
{
	if ((NM.L == NM.R) ||
		(NM.L < NM.R && (NM.S < NM.L || NM.S >= NM.R)) ||
		(NM.L >= NM.R && (NM.S < NM.L && NM.S >= NM.R)))
	{
		NM.L = NM.S;
	}
}

u8 Determination_Skipped_Node()
{
	if (!((NM.S == NM.D) || (NM.R == NM.D) || (NM.S == NM.R)) &&
		((NM.D < NM.R && NM.S >= NM.D && NM.S < NM.R) ||
		 (NM.D >= NM.R && ((NM.S < NM.R) || (NM.S >= NM.D)))))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Normal_Standard_NM()
{
	NM.NMrxcount = 0;
	NM.Destination.marker = 0;
	if (NM.RXMessageType.field.Limphome)
	{
		NM.Config.limphome = NM.RXSender;
		// Update network status
	}
	else
	{
		NM.Config.present = NM.RXSender;
		// Update network status
		Determine_Logical_Successor();
		if (NM.RXMessageType.field.Ring)
		{
			NM_Cancel_Alarm(TMax);
			NM_Cancel_Alarm(TTyp);
			if (NM.D == MMU_SOURCE_ID)
			{
				NM_Set_Alarm(TTyp);
				NM.Destination.marker = 1;
			}
			else
			{
				NM_Set_Alarm(TMax);
				if (Determination_Skipped_Node())
				{
					if (NM.Networkstatus.bussleep)
					{
						NM.Sleep.ind = 1;
					}
					NM_Send_Alive_Message();
					NM.NMtxcount++;
				}
			}
		}
		else
		{
			if (NM.D == MMU_SOURCE_ID)
			{
				NM.Destination.marker = 1;
			}
			NM.Networkstatus.configurationstable = 0;
		}
	}
}

void NM_Set_State(CAN_NM_STATE targetSate)
{
	NM.previous_state = NM.current_state;
	NM.current_state = targetSate;
}

void Saipa_SP100_Network_Mangement(void)
{
	if (NM.TTypTimer)
	{
		NM.TTypTimer--;
		if (NM.TTypTimer == 0)
		{
			NM.timeoutTTyp = 1;
		}
	}
	if (NM.TMaxTimer)
	{
		NM.TMaxTimer--;
		if (NM.TMaxTimer == 0)
		{
			NM.timeoutTMax = 1;
		}
	}
	if (NM.TErrorTimer)
	{
		NM.TErrorTimer--;
		if (NM.TErrorTimer == 0)
		{
			NM.timeoutTError = 1;
		}
	}
	if (NM.TWaitBusSleepTimer)
	{
		NM.TWaitBusSleepTimer--;
		if (NM.TWaitBusSleepTimer == 0)
		{
			NM.timeoutTWaitBusSleep = 1;
		}
	}
	if(NM.TSendSleepAckTimer)
	{
		NM.TSendSleepAckTimer--;
		if (NM.TSendSleepAckTimer == 0)
		{
			NM.timeoutTSendSleepAck = 1;
		}
	}
	
	if (BCMRxTimer && CanMainState == CAN_MAIN_NORMAL)
	{
		BCMRxTimer--;
	}
	switch (NM.current_state)
	{
	case NMOff:
		if (NM.gotoModeAwake || CanMainState == CAN_MAIN_NORMAL)
		{
			NM_Set_State(NMInit);
		}
		break;
	case NMInit:
		if (NM.previous_state != NMBusSleep)
		{
			NM.Networkstatus.bussleep = 0;
			NM.Sleep.ack = 0;
			NM.Sleep.ind = 0;
			// Initilize the bus hardware D_Init(�,BusInit)
		}
		NM.Networkstatus.limphome = 0;
		NM_Set_State(NMInitReset);
		break;
	case NMInitReset:
		if (NM.previous_state != NMNormal && NM.previous_state != NMTwbsNormal && NM.previous_state != NMNormalPrepSleep)
		{
			NM.NMrxcount = 0;
			NM.NMtxcount = 0;
			NM.Destination.marker = 0;
			// Enable application communication(D_Online)
		}
		NM.Config.present = MMU_SOURCE_ID;
		NM.L = MMU_SOURCE_ID;
		NM.NMrxcount++;
		// Initialize the NMPDU(OpCode,Data)
		NM_Set_State(NMReset);
		break;
	case NMReset:
		NM_Send_Alive_Message();
		NM.NMtxcount++;
		if (NM.NMrxcount <= RX_LIMIT && NM.NMtxcount <= TX_LIMIT)
		{
			NM_Set_Alarm(TTyp);
			NM_Set_State(NMNormal);
		}
		else
		{
			NM_Set_State(NMInitLimpHome);
		}
		break;
	case NMInitLimpHome:
		NM_Set_Alarm(TError);
		NM.Networkstatus.limphome = 1;
		NM.limphomemarket = 1;
		NM_Set_State(NMLimpHome);
		break;
	case NMNormal:
		if (NM.timeoutTTyp)
		{
			NM.timeoutTTyp = 0;

			NM_Cancel_Alarm(TMax);
			NM_Set_Alarm(TMax);
			if (NM.Networkstatus.bussleep == 1)
			{
				NM.Sleep.ind = 1;
			}
			NM_Send_Ring_Message(0);
			NM.NMtxcount++;
			if (NM.NMtxcount <= TX_LIMIT)
			{
				NM.Networkstatus.configurationstable = 1;
			}
			else
			{
				NM_Set_State(NMInitLimpHome);
				break;
			}
		}
		if (NM.NMMessageTransmitted) // Any NM message is transmitted successfully
		{
			NM.NMMessageTransmitted = 0;

			NM.NMtxcount = 0;
			if (NM.TXMessageType.field.Ring)
			{
				NM_Cancel_Alarm(TMax);
				NM_Cancel_Alarm(TTyp);
				NM_Set_Alarm(TMax);
				if (NM.TXMessageType.field.SleepInd && NM.Networkstatus.bussleep == 1)
				{
					NM.Sleep.ack = 1;
					NM_Set_State(NMNormalPrepSleep);
					break;
				}
			}
		}
		if (NM.NMMessageRecieved)
		{
			NM.NMMessageRecieved = 0;

			Normal_Standard_NM();
			if (NM.RXMessageType.field.SleepAck && NM.Networkstatus.bussleep)
			{
				NM_Set_State(NMInitBusSleep);
				break;
			}
			else
			{
				if(NM.Destination.marker)
				{
					NM.Sleep.ind = NM.RXMessageType.field.SleepInd;
				}
			}
		}
		if (NM.timeoutTMax)
		{
			NM.timeoutTMax = 0;

			NM.Sleep.ind = 0;
			NM.Sleep.ack = 0;
			NM_Set_State(NMInitReset);
			break;
		}
		if (NM.gotoModeBusSleep)
		{
			NM.gotoModeBusSleep = 0;
			NM.Networkstatus.bussleep = 1;
		}
		if (NM.gotoModeAwake)
		{
			NM.gotoModeAwake = 0;
			NM.Networkstatus.bussleep = 0;
		}
		break;
	case NMNormalPrepSleep:
		if (NM.timeoutTTyp)
		{
			NM.timeoutTTyp = 0;

			NM_Send_Ring_Message(1);
		}
		if (NM.NMMessageTransmitted && NM.TXMessageType.field.Ring)
		{
			NM.NMMessageTransmitted = 0;

			NM_Set_State(NMInitBusSleep);
			break;
		}
		if (NM.NMMessageRecieved)
		{
			NM.NMMessageRecieved = 0;

			Normal_Standard_NM();
			if (NM.RXMessageType.field.SleepInd)
			{
				if (NM.RXMessageType.field.SleepAck == 1)
				{
					NM_Set_State(NMInitBusSleep);
					break;
				}
			}
			else
			{
				NM.Sleep.ack = 0;
				NM_Set_State(NMNormal);
				break;
			}
		}
		if (NM.timeoutTMax)
		{
			NM.timeoutTMax = 0;

			NM.Sleep.ind = 0;
			NM.Sleep.ack = 0;
			NM_Set_State(NMInitReset);
			break;
		}
		if (NM.gotoModeAwake)
		{
			NM.gotoModeAwake = 0;
			NM.Networkstatus.bussleep = 0;
			NM.Sleep.ack = 0;
			NM_Set_State(NMNormal);
			break;
		}
		break;
	case NMInitBusSleep:
		// Disable application communication (D_Offline)
		NM_Set_Alarm(TWaitBusSleep);
		if (NM.previous_state == NMLimpHome || NM.previous_state == NMLimpHomePrepSleep)
		{
			NM_Set_State(NMTwbsLimpHome);
		}
		else
		{
			NM_Set_State(NMTwbsNormal);
		}
		break;
	case NMTwbsNormal:
		if (NM.timeoutTWaitBusSleep)
		{
			NM.timeoutTWaitBusSleep = 0;
			// Initilize the sleep mode of bus hardware D_Init(�,BusSleep)
			NM_Set_State(NMBusSleep);
			break;
		}
		if (NM.NMMessageRecieved)
		{
			if (NM.Sleep.ind != 1)
			{
				NM.Sleep.ind = 0;
				NM.Sleep.ack = 0;
				NM_Cancel_Alarm(TWaitBusSleep);
				// Enable application communication(D_Online)
				NM_Set_State(NMInitReset);
				break;
			}
		}
		if (NM.gotoModeAwake)
		{
			NM.gotoModeAwake = 0;
			NM.Networkstatus.bussleep = 0;
			NM.Sleep.ind = 0;
			NM.Sleep.ack = 0;
			NM_Cancel_Alarm(TWaitBusSleep);
			// Enable application communication(D_Online)
			NM_Set_State(NMInitReset);
			break;
		}
		break;
	case NMLimpHome:
		if (NM.timeoutTError)
		{
			NM.timeoutTError = 0;

			// Enable application communication (D_Online)
			if (NM.Networkstatus.bussleep == 1)
			{
				//NM_Set_Alarm(TMax);
				NM_Set_Alarm(TSleepACK);
				NM.Sleep.ind = 1;
				NM_Send_LimpHome_Message();
				NM.limphomemarket = 1;
				//NM_Set_State(NMLimpHomePrepSleep);//wjp
				NM_Set_State(NMSendSleepACK);//wjp
				break;
			}
			else
			{
				NM_Set_Alarm(TError);
				NM_Send_LimpHome_Message();
				NM.NMMessageTransmitted = 0;
				NM.limphomemarket = 1;
			}
		}
		if (NM.NMMessageRecieved)
		{
			NM.NMMessageRecieved = 0;
			if (NM.Networkstatus.bussleep && NM.Sleep.ack)
			{

				NM_Set_State(NMInitBusSleep);
				break;
			}
			if (NM.limphomemarket)
			{
				NM_Cancel_Alarm(TError);
				NM.Networkstatus.limphome = 0;
				NM.limphomemarket = 0;
				NM_Set_State(NMInitReset);
				break;
			}
		}
		if (NM.NMMessageTransmitted)
		{
			NM.NMMessageTransmitted = 0;

			if (NM.TXMessageType.field.Limphome)
			{
				NM.limphomemarket = 0;
			}
		}
		if (NM.gotoModeBusSleep)
		{
			NM.gotoModeBusSleep = 0;
			NM.Networkstatus.bussleep = 1;
		}
		if (NM.gotoModeAwake)
		{
			NM.gotoModeAwake = 0;
			NM.Networkstatus.bussleep = 0;
		}
		break;
		
	case NMSendSleepACK:
	{
		if(NM.timeoutTSendSleepAck)
		{
			NM.timeoutTSendSleepAck=0;
			NM_Set_Alarm(TMax);
			NM.Sleep.ack=1;
			NM_Send_LimpHome_Message();//wjp
			NM_Set_State(NMLimpHomePrepSleep);
			break;
		}
	}
		
	case NMLimpHomePrepSleep:
		if (NM.timeoutTMax)
		{
			NM.timeoutTMax = 0;
			NM_Set_State(NMInitBusSleep);
			break;
		}
		if (NM.NMMessageRecieved)
		{
			NM.NMMessageRecieved = 0;
			if (NM.Sleep.ind != 1)
			{
				NM_Set_State(NMLimpHome);
				break;
			}
		}
		if (NM.gotoModeAwake)
		{
			NM.gotoModeAwake = 0;
			NM.Networkstatus.bussleep = 0;
			NM_Set_State(NMLimpHome);
			break;
		}
		break;
	case NMTwbsLimpHome:
		if (NM.timeoutTWaitBusSleep)
		{
			NM.timeoutTWaitBusSleep = 0;
			// Initilize the sleep mode of bus hardware D_Init(�,BusSleep
			NM_Set_State(NMBusSleep);
			break;
		}
		if (NM.NMMessageRecieved)
		{
			NM.NMMessageRecieved = 0;

			if (NM.Sleep.ind == 0)
			{
				NM_Cancel_Alarm(TWaitBusSleep);
				NM_Set_State(NMLimpHome);
				break;
			}
		}
		if (NM.gotoModeAwake)
		{
			NM.gotoModeAwake = 0;
			NM.Networkstatus.bussleep = 0;
			NM_Set_State(NMLimpHome);
			break;
		}
		break;
	case NMBusSleep:
		if (NM.gotoModeAwake || Get_ACC_Det_Flag)
		{
			NM.gotoModeAwake = 0;
			NM.Networkstatus.bussleep = 0;
			NM.Sleep.ind = 0;
			NM.Sleep.ack = 0;
			NM_Set_State(NMInit);
		}
		break;
	}
}

void Saipa_SP100_CANDiagnostic_LoadDefaultData()
{
	memset(&CANDiagData.HUTechnicalNumber, 0xff, sizeof(CANDiagData));
	Mem_strcpy(CANDiagData.HUTechnicalNumber, CANDiagData_Default_HUTechnicalNumber, sizeof(CANDiagData.HUTechnicalNumber));
	Mem_strcpy(CANDiagData.crouseManufacturingDate, CANDiagData_Default_crouseManufacturingDate, sizeof(CANDiagData.HUTechnicalNumber));
	CANDiagData.carModel = 0x02;
	CANDiagData.carOptions.byte = 0x88;
	CANDiagData.handbrakeControl = 0;
	CANDiagData.reverseGearControl = 0;
	CANDiagData.illuminationControl = 0x01;
	CANDiagData.faultsDisplay = 0;
	CANDiagData.introLogo = 0;
	CANDiagData.VINWritten = 0;
	EEPROM_Save_CANDiagnostic();
}

void Saipa_SP100_MainPro(void)
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
			F_CAN_RX_DATA = 0;
			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_DIAGNOSTIC);
		}
	}
	if (CanTxTimer)
	{
		CanTxTimer--;
	}
	if (waitForReadTimer && F_DataWaitForRead == 2)
	{
		waitForReadTimer--;
	}
	if (waitForReadTimer == 0 && F_DataWaitForRead == 2)
	{
		Saipa_SP100_Diagnostic_Data_Read();
	}
	if (DiagSessionTimer)
	{
		DiagSessionTimer--;
		if (DiagSessionTimer == 0)
		{
			diagMode = 0;
		}
	}
	if (hardwareResetTimer)
	{
		hardwareResetTimer--;
		if (hardwareResetTimer == 0)
		{
			SystemReset();
		}
	}
	if (ICMRxTimer)
	{
		ICMRxTimer--;
		if (ICMRxTimer == 0)
		{
			TFT_Backlight_CAN_Level = 70;
			CanGeneralCtrlFlag.field.illumi_level = 100;
		}
	}
	if (CanMainState == CAN_MAIN_NORMAL)
	{
		if (CAN_GetFlagStatus(CAN1, CAN_FLAG_EWG) || CAN_GetFlagStatus(CAN1, CAN_FLAG_BOF) || CAN_GetReceiveErrorCounter(CAN1) >= 127 || CAN_GetLSBTransmitErrorCounter(CAN1) >= 127)
		{
			CanCheckErrorTimer++;
			if (CanCheckErrorTimer >= T5S_1)
			{
				CanCheckErrorTimer = 0;
				CanMainState = CAN_MAIN_IDLE;
			}
		}
		else
		{
			CanCheckErrorTimer = 0;
		}
	}

	Saipa_SP100_Rx_Message();
	Saipa_SP100_Network_Mangement();
	if (F_CAN_INIT)
	{
		CAN1_Transmit();
	}
	if (!NM.ACCStatus && Get_ACC_Det_Flag)
	{
		NM.ACCStatus = Get_ACC_Det_Flag;
		NM.gotoModeAwake = 1;
	}
	else if (NM.ACCStatus && !Get_ACC_Det_Flag)
	{
		NM.ACCStatus = Get_ACC_Det_Flag;
	}
	//	if (APP_READY == APP_Status)
	//	{

	//		if (CanInitTxTimer <= T10S_1)
	//		{
	//			CanInitTxTimer++;
	//		}
	//		if (CanInitTxTimer == T10S_1)
	//		{
	//			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_EMS_INFO);
	//			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_CHASSIS_INFO);
	//			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_BODY_INFO);
	//			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_ASSIST_INFO);
	//			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_TPMS_INFO);
	//			PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_DIAGNOSTIC);
	//		}
	//	}

	switch (CanMainState)
	{
	case CAN_DIAG_INIT:
		if (!EEPROM_ValidFlag && CanMainTimer)
		{
			break;
		}
		CanMainTimer = 0;
		if (!EEPROM_Load_CANDiagnostic())
		{
			Saipa_SP100_CANDiagnostic_LoadDefaultData();
		}
		CanMainState = CAN_MAIN_IDLE;
		break;
	case CAN_MAIN_IDLE:
		F_CAN_INIT = 0;
		CanMainState = CAN_MAIN_CFG;
		NM.current_state = NMOff;
		break;
	case CAN_MAIN_CFG:
		CAN1_Init();
		CANSleepTime=0xFFFFFFFF;
		CANSleepFlag=1;
		CanTxErrorCounter = 0;
		CanNoTxCounter = 0;
		CanMainState = CAN_MAIN_INIT;
		TFT_Backlight_CAN_Level = 70;
		CanGeneralCtrlFlag.field.illumi_level = 100;
		break;
	case CAN_MAIN_INIT:
		CAN1_ClearTxMessage();
		F_CAN_SLEEP = 0;
		//		F_CAN_RX_DATA = 1;
		F_CAN_INTERRUPT = 0;
		CanMainState = CAN_MAIN_NORMAL;
		CanNoDataTimer = T2S_1;
		BCMRxTimer = T2S_1;
		NoBCMACCOffTimer = T2S_1;
		CanTxTimer = 0;
		CanInitTxTimer = 0;
//		NM.f_Sleep_Indication_NO_ACC = 0;
		NM.gotoModeAwake = 1;
		break;
	case CAN_MAIN_NORMAL: 
		if (CanTxTimer == 0 && NM.Networkstatus.bussleep != 1 && NM.NMReceived == 1)
		{
			CanTxTimer = T1S_1; // 2000;//T10MS_1;
			Saipa_SP100_PostMessage(CAN_POST_MSG_MMU);
		}
#if CAN_WAKEUP_FUN == 1
		if (F_CAN_RX_DATA == 0 && Get_ACC_Det_Flag == 0)
#else
		if (Get_ACC_Det_Flag == 0)
#endif
		{
			NM.NMReceived=0;
			NM.gotoModeBusSleep = 1;
			CanMainTimer = T5S_1;//wjp
			CanMainState = CAN_MAIN_SLEEP_CFG;
			// 	if (NM.current_state != NM_BUS_SLEEP && NM.current_state != NM_OFF)
			// 	{
			// 		NM.current_state = NM_BUS_SLEEP;
			// 		NM.f_Sleep_Indication = 1;
			// 		NM.NMtxcount = 0;
			// 		CanNMTimer = 0;
			// 	}
			break;
		}
		else if (Get_ACC_Det_Flag == 0 && BCMRxTimer == 0 && NoBCMACCOffTimer
				 //&& NM.f_Sleep_Indication_NO_ACC == 0
		)
		{
			NoBCMACCOffTimer--;
			if (NoBCMACCOffTimer == 0)
			{
				NM.gotoModeBusSleep = 1;
			}
		}
		else if (Get_ACC_Det_Flag)
		{
			NoBCMACCOffTimer = T2S_1;
			// NM.f_Sleep_Indication_NO_ACC = 0;
			if (APP_READY == APP_Status)
			{
				if (CanMainTimer == 0)
				{
					CanMainTimer = T6S_1;
					if (F_CAN_RX_DATA)
					{
						PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_EMS_INFO);
						PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_CHASSIS_INFO);
						PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_BODY_INFO);
						PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_ASSIST_INFO);
						PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_RX_TPMS_INFO);
						PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_DIAGNOSTIC);
					}
					else
					{
						PostMessage(NAVI_MODULE, MCU_TX_CAN_BOX_INFO, SAIPA_SP100_DIAGNOSTIC);
					}
				}
			}
#if CAN_AUTOTEST == 1
			if (CANAutotestTimer)
			{
				CANAutotestTimer--;
			}
			if ((CANAutotestTimer % 100) == 0)
			{
				Saipa_SP100_PostMessage(CAN_POST_MSG_BODY_1_AUTO_TEST);
			}
			if (CANAutotestTimer == 0)
			{
				CANAutotestTimer = T3S_1;
				CANAutotestReverse = !CANAutotestReverse;
			}
#endif
		}
		break;
	case CAN_MAIN_SLEEP_CFG:
		if (CanMainTimer)
		{
			break;
		}
		if (EEPROM_ValidFlag)
		{
			EEPROM_Save_CANDiagnostic();
		}
		CAN1_ClearRxMessage();
		CAN_IC_STANDBY_ON;
		CAN_IC_POWER_OFF;
		F_CAN_SLEEP = 1;
		F_CAN_INTERRUPT = 0;
		CanMainTimer = T100MS_1;
		CANSleepTime=RTC_GetCounter();
		CanMainState = CAN_MAIN_SLEEP;
		break;
	case CAN_MAIN_GOTO_SLEEP:
		if (CanMainTimer)
		{
			break;
		}
		CAN_IC_DISABLE;
		CanMainState = CAN_MAIN_SLEEP;
		break;
	case CAN_MAIN_SLEEP:
#if CAN_WAKEUP_FUN == 1
		if (F_CAN_SLEEP == 0 || F_CAN_INTERRUPT || Get_ACC_Det_Flag)
#else
		if (Get_ACC_Det_Flag)
#endif
		{
			CAN_IC_STANDBY_OFF;
			CAN_IC_POWER_ON;
			CAN_IC_ENABLE;
			F_CAN_SLEEP = 0;
			F_CAN_RX_DATA = 1;
			CanMainState = CAN_MAIN_CFG;
		}
		break;
	default:
		break;
	}
}

#endif
