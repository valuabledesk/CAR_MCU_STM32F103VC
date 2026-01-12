#include "public.h"

#if CAN_FUN_HAIMA_S5==1
CAN_RX_INFO CanRxInfo;
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_MAIN_FLAG CanMainFlag;
CAN_MAIN_STATE CanMainState;

u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanTxTimer;
u32 CanTxPowerOffTimer;
u16 CanActivetyCounter;
u16 Camera_key_counter;
u16 AccWire_Sampling_Counter;
u8 Vehicle_Warning_Ctrl_Status;
u8 CanActivetyStatus;
u8 AccWirePowerStatus;
u8 AccPowerDet;
u32 CanTxPowerOffCounter;
#if TEST_CAN_FUN==1
u32 CanTestTimer;
int test_time;
int test;
#endif


void Haima_Se_AvmSwitch(void)
{
	
}

void Haima_S5_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;
		u8 temp;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_VEHICLE_WARNING:
				CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_NONE;
				
				if(((message.Data[2]&0xF0)>>4)==0x03)
				{
					CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_KEY_NOT_DETECTED;
				}
				else if(((message.Data[2]&0xF0)>>4)==0x05)
				{
					CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_REPLACE_KEY_BATTERY;
				}
				else if((message.Data[3]&0x0F)<=0x07&&(message.Data[3]&0x0F)>=0x01)
				{
					switch(message.Data[3]&0x0F)
					{
						case VEHICLE_WARNING_KEEP_KEY_CLOSE:
							CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_KEEP_KEY_CLOSE;
							break;
						case VEHICLE_WARNING_KEEP_P_N:
							CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_KEEP_P_N;
							break;
						case VEHICLE_WARNING_CLUTCH_PRESS_STARTBUTTON:
							CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_CLUTCH_PRESS_STARTBUTTON;
							break;
						case VEHICLE_WARNING_BREAKS_PRESS_STARTBUTTON:
							CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_BREAKS_PRESS_STARTBUTTON;
							break;
						case VEHICLE_WARNING_KEEP_P:
							CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_KEEP_P;
							break;
						case VEHICLE_WARNING_KEEP_N_PRESS_STARTBUTTON:
							CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_KEEP_N_PRESS_STARTBUTTON;
							break;
						case VEHICLE_WARNING_PRESS_STARTBUTTON:
							CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_PRESS_STARTBUTTON;
							break;
						default :
							CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_NONE;
							break;    
					}
				}

				if(CanRxInfo.Vehicle_Warning_Status==CANBOX_WARNING_NONE)
				{
					switch(message.Data[4]&0x03)
					{
						case 0x00:
							F_WARN_FLAG=0;
							CanRxInfo.Vehicle_Warning_Status=CANBOX_WARNING_NONE;
							break;
						case 0x01:
							if(F_WARN_FLAG==1&&F_GLIDE_ALLOW==1)
							{
								CanRxInfo.Vehicle_Warning_Status = CANBOX_WARNING_KEEP_P_CAR_GLIDE;
								F_WARN_FLAG=0;
							}
							else
							{
								CanRxInfo.Vehicle_Warning_Status=CANBOX_WARNING_NONE;
							}
							break;
						case 0x02:
						case 0x03:
							F_WARN_FLAG=1;
							CanRxInfo.Vehicle_Warning_Status=CANBOX_WARNING_NONE;
							break;
						default:
							CanRxInfo.Vehicle_Warning_Status=CANBOX_WARNING_NONE;
							break;
					}
				}


				
				if(Vehicle_Warning_Ctrl_Status != CanRxInfo.Vehicle_Warning_Status)
				{
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S5_RX_VEHICLE_WARING_INFO);
				}
				Vehicle_Warning_Ctrl_Status = CanRxInfo.Vehicle_Warning_Status;
				break;
			case CAN_ID_TCU_INFO:
				if(message.Data[4]==0xF0)
				{
					CanGeneralCtrlFlag.field.reverse_on_off = 0;
					F_GLIDE_ALLOW=0;
				}
				else if((message.Data[4]) == 0x0A)
				{
					CanGeneralCtrlFlag.field.reverse_on_off = 1;
					F_GLIDE_ALLOW=1;
				}
				else
				{
					CanGeneralCtrlFlag.field.reverse_on_off = 0;
					F_GLIDE_ALLOW=1;
				}
				break;
			case CAN_ID_BCM_INFO:
				
				break;
			case CAN_ID_ESP_PT_FrP03:
				if((message.Data[6] >> 5) == 1)
				{
					CanGeneralCtrlFlag.field.parking_on_off = 1;
				}
				else
				{
					CanGeneralCtrlFlag.field.parking_on_off = 0;
				}
				break;
			default:
				break;
		
		}
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
		CanNoDataTimer=T3S_1;//T60S_1;

		if(CanActivetyStatus==0)
		{
			CanActivetyCounter++;
			if(CanActivetyCounter>3)
			{
				CanActivetyStatus = 1;
				CanActivetyCounter = 0;
			}
		}
	}
}


void Haima_S5_RxAppDataPro(u8 *buffer)
{

	u8 cmd_id;
	cmd_id=buffer[1];

	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	
	switch(cmd_id)
	{
		case HAIMA_S5_TX_AVM_CMD:
			if(buffer[3]==0x02)
			{
				switch(buffer[4])
				{
					case CANBOX_CAMERA_SWITCH:
						CAMERA_KEY_PRESS;
						Camera_key_counter = 200;
						break;
					case CANBOX_CAMERA_EXIT:
						CAMERA_KEY_PRESS;
						Camera_key_counter = 6000;
						break;
					case CANBOX_CAMERA_KEY_PREES:
						CAMERA_KEY_PRESS;
						break;
					case CANBOX_CAMERA_KEY_RELEASE:
						CAMERA_KEY_RELASE;
						break;
					default: 
						break;    
				}
			}
			break;
		default:
			break;
	}
}

void Haima_S5_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
		u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case HAIMA_S5_RX_VEHICLE_WARING_INFO:
			buffer[2]=0x02;
			buffer[3]=CanRxInfo.Vehicle_Warning_Status;
			buffer[4]=0x00;
			break;
		default:
			flag=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=HAIMA_S5_HEAD_CODE;
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

void HaiMa_S5_PowerSw(void)
{
	if(AccWirePowerStatus)
    {
		if(ACC_DET_LEVEL==0)
        {
            AccWire_Sampling_Counter = T50MS_1;
        }
        if(AccWire_Sampling_Counter)
        {
            AccWire_Sampling_Counter--;
			if(AccWire_Sampling_Counter == 0)
			{
				PostMessage(NAVI_MODULE, MCU_TX_CMD, WORD(UICC_NAVI, 0));
			}
        }
        else
        {
            AccWirePowerStatus = 0;
			PostKeyCode(UICC_FORCE_POWER_OFF, PANEL);
			CanTxPowerOffTimer=0;
			CanTxPowerOffCounter=0;
        }
    }
    else
	{
		if(ACC_DET_LEVEL==0)
		{
			if(AccWire_Sampling_Counter)
			{
				AccWire_Sampling_Counter--;
				if(AccWire_Sampling_Counter == 0)
				{
					PostMessage(NAVI_MODULE, MCU_TX_CMD, WORD(UICC_NAVI, 1));
				}
			}
			else
			{
				AccWirePowerStatus = 1;
				//CanBox_Tx_Data.Canbox_Tx_Vehicle_Base_Info.Parking_Acc_Status.Parking_Acc_State_bit.Acc_status = 1;
			}
		}
		else
		{
			AccWire_Sampling_Counter = T50MS_1;
		}
	}
	if(AccWirePowerStatus==0)
	{
		CanTxPowerOffTimer++;
		if(CanTxPowerOffTimer>=T2S_1)
		{
			CanTxPowerOffTimer=0;
			if(CanTxPowerOffCounter<3)
			{
				PostKeyCode(UICC_FORCE_POWER_OFF, PANEL);
				CanTxPowerOffCounter++;
			}
		}
	}
	else
	{
		CanTxPowerOffTimer=0;
		CanTxPowerOffCounter=0;
	}

	if(CanActivetyStatus||AccWirePowerStatus)
	{
		AccPowerDet = 0;
	}
	else
	{
		AccPowerDet = 1;
	}
}

void Haima_S5_MainPro(void)
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
	if(CanTxTimer)
	{
		CanTxTimer--;
	}

	if(Camera_key_counter)
    {
        if(Camera_key_counter == 1)
        {
            CAMERA_KEY_RELASE;
        }
        Camera_key_counter--;    
    }
//#if CAN_WAKEUP_FUN==1
	if(CanNoDataTimer)
	{
		CanNoDataTimer--;
		if(CanNoDataTimer==0)
		{
			F_CAN_RX_DATA=0;
		}
	}
//#endif
	HaiMa_S5_PowerSw();

	Haima_S5_Rx_Message();
	CAN1_Transmit();
	switch(CanMainState)
	{
		case CAN_MAIN_IDLE:
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;

			AccWirePowerStatus = 1;
			CanTxPowerOffTimer=0;
			CanTxPowerOffCounter=0;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_IDLE\r\n");
#endif
			break;
		case CAN_MAIN_CFG:
			CAN1_Init();
			CanMainState=CAN_MAIN_INIT;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_CFG\r\n");
#endif
			break;
		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			F_CAN_SLEEP=0;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;

			F_WARN_FLAG=0;
			F_GLIDE_ALLOW=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T25S_1;
			CanTxTimer=0;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_INIT\r\n");
#endif
			break;
		case CAN_MAIN_NORMAL:
			if(F_CAN_RX_DATA==0)
			{
#if TEST_CAN_FUN==1

				//CanMainState=CAN_MAIN_SLEEP_CFG;
#else
			CanMainState=CAN_MAIN_SLEEP_CFG;
#endif
#if CAN_DEBUG_FUN==1
				printf("CAN_MAIN_NORMAL:1\r\n");
#endif
			}
			else
			{
				if(APP_READY==APP_Status && ACC_DET_LEVEL==0)
				{
					if(CanMainTimer==0)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,HAIMA_S5_RX_VEHICLE_WARING_INFO);
						CanMainTimer=T1S_1;
					}
					if(CanTxTimer==0)
					{
						u8 can_data0[2] = {0x01,0x00};
						u8 can_data1[4] = {0x10,0x00,0x00,0x00};
						CAN1_TxFrame(0x539,can_data0,2);
						CAN1_TxFrame(0x539,can_data1,4);
						CanTxTimer=T100MS_1;
						
					}
				}

			}
#if TEST_CAN_FUN==1
		if(CanTestTimer==0)
			{
					CanTestTimer=T2S_1;
					
				
			}	
			if(CanTestTimer)
			{
				CanTestTimer--;
				if(CanTestTimer==0)
				{
					if(test==0x30)
					{
						test=0;
					}
					else test=0x30;
					CanTestTimer=T2S_1;
				}
			}
			if(test_time)
			{
				test_time--;
				if(test_time==0)
				{
					u8 data[8]={0};

					data[2]=test;
					CAN1_TxFrame(CAN_ID_VEHICLE_WARNING,data,8);
					test_time=T100MS_1;
					
				}
			}			
			if(test_time==0)
			{
					test_time=T100MS_1;
					
				
			}
#endif
			
			
			break;
		case CAN_MAIN_SLEEP_CFG:
			CAN1_ClearRxMessage();
			CAN_IC_STANDBY_ON;
			F_CAN_SLEEP=1;
			F_CAN_INTERRUPT=0;
			CanActivetyStatus = 0;
			CanMainTimer=T100MS_1;
			CanMainState=CAN_MAIN_SLEEP;
#if CAN_DEBUG_FUN==1
			printf("CAN_MAIN_SLEEP_CFG\r\n");
#endif
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
#if CAN_DEBUG_FUN==1
				printf("CAN_MAIN_SLEEP\r\n");
#endif
			}
			break;
		default:
			break;
	}
}

#endif
