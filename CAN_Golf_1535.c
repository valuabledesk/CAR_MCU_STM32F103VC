#include "public.h"

#if CAN_FUN_GOLF_1535==1
//CAN_RX_INFO CanRxInfo;
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_MAIN_FLAG CanMainFlag;
CAN_MAIN_STATE CanMainState;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;

u8 CanTxErrorCounter;
u8 CanNoTxCounter;
u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanTxTimer;

void Golf_1535_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		
		if((message.ID>>16)==0x18F8&&(message.ID&0xFF)==0xF3&&(0x16<((message.ID>>8)&0xFF))&&(((message.ID>>8)&0xFF)<0x50))//0x18F817F3...0x18F849F3
		{
			CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n1_cellvol=((message.Data[0]<<8)|message.Data[1]);
			CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n2_cellvol=((message.Data[2]<<8)|message.Data[3]);
			CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n3_cellvol=((message.Data[4]<<8)|message.Data[5]);
			CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n4_cellvol=((message.Data[6]<<8)|message.Data[7]);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_BMS_SINGLE_CELL_VOL);
		}
		else if((message.ID>>16)==0x18F8&&(message.ID&0xFF)==0xF3&&(0x49<((message.ID>>8)&0xFF)))//&&(((message.ID>>8)&0xFF)<0x100))//0x18F850F3...0x18F8FFF3
		{
			CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m1_celltemp=message.Data[0];
			CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m2_celltemp=message.Data[1];
			CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m3_celltemp=message.Data[2];
			CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m4_celltemp=message.Data[3];
			CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m5_celltemp=message.Data[4];
			CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m6_celltemp=message.Data[5];
			CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m7_celltemp=message.Data[6];
			CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m8_celltemp=message.Data[7];
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_BMS_SINGLE_CELL_TEMP);
		}
		else
		{
			switch(message.ID)
			{
				case CAN_ID_BMS_TOTAL_INFO:
					CanRxInfo.bms_info.bms_total_info.bms_totalvol=((message.Data[0]<<8)|message.Data[1]);
					CanRxInfo.bms_info.bms_total_info.bms_totalcur=((message.Data[2]<<8)|message.Data[3]);
					CanRxInfo.bms_info.bms_total_info.bms_soc=message.Data[4];
					CanRxInfo.bms_info.bms_total_info.bms_soh=message.Data[5];
					CanRxInfo.bms_info.bms_total_info.bms_insulation=((message.Data[6]<<8)|message.Data[7]);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_1535_BMS_TOTAL_INFO);
					break;
				case CAN_ID_BMS_VOL_INFO:
					CanRxInfo.bms_info.bms_cell_vol_info.bms_maxcellvol=((message.Data[0]<<8)|message.Data[1]);
					CanRxInfo.bms_info.bms_cell_vol_info.bms_maxcellvolnum=message.Data[2];
					CanRxInfo.bms_info.bms_cell_vol_info.bms_maxcellvolboxnum=message.Data[3];
					CanRxInfo.bms_info.bms_cell_vol_info.bms_mincellvol=((message.Data[4]<<8)|message.Data[5]);
					CanRxInfo.bms_info.bms_cell_vol_info.bms_mincellvolnum=message.Data[6];
					CanRxInfo.bms_info.bms_cell_vol_info.bms_mincellvolboxnum=message.Data[7];
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_1535_BMS_VOL_INFO);
					break;
				case CAN_ID_BMS_TEMP_INFO:
					CanRxInfo.bms_info.bms_cell_temp_info.bms_maxcelltemp=message.Data[0];
					CanRxInfo.bms_info.bms_cell_temp_info.bms_maxcelltempnum=message.Data[1];
					CanRxInfo.bms_info.bms_cell_temp_info.bms_maxcelltempboxnum=message.Data[2];
					CanRxInfo.bms_info.bms_cell_temp_info.bms_mincelltemp=message.Data[3];
					CanRxInfo.bms_info.bms_cell_temp_info.bms_mincelltempnum=message.Data[4];
					CanRxInfo.bms_info.bms_cell_temp_info.bms_mincelltempboxnum=message.Data[5];
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_1535_BMS_TEMP_INFO);
					break;
				case CAN_ID_BMS_STATE_INFO:
					CanRxInfo.bms_info.bms_charge_state.bms_chglinestate=message.Data[0];
					CanRxInfo.bms_info.bms_charge_state.bms_chgtype=message.Data[1];
					CanRxInfo.bms_info.bms_charge_state.bms_chgstate=message.Data[2];
					CanRxInfo.bms_info.bms_charge_state.bms_mainrlystate=message.Data[3];
					CanRxInfo.bms_info.bms_charge_state.bms_negrlystate=message.Data[4];
					CanRxInfo.bms_info.bms_charge_state.bms_chgrlystate=message.Data[5];
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_1535_BMS_STATE_INFO);
					break;
				case CAN_ID_BMS_CUR_INFO:
					CanRxInfo.bms_info.bms_max_cur_info.bms_max_chgcur=((message.Data[0]<<8)|message.Data[1]);
					CanRxInfo.bms_info.bms_max_cur_info.bms_maxdischgcur=((message.Data[2]<<8)|message.Data[3]);
					CanRxInfo.bms_info.bms_max_cur_info.bms_maxfeedbackcur=((message.Data[4]<<8)|message.Data[5]);
					CanRxInfo.bms_info.bms_max_cur_info.bms_ratedcapacity=((message.Data[6]<<8)|message.Data[7]);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_1535_BMS_CUR_INFO);
					break;
				case CAN_ID_BMS_FAULT_INFO:
					CanRxInfo.bms_info.bms_fault_info.byte0.byte=message.Data[0];
					CanRxInfo.bms_info.bms_fault_info.byte1.byte=message.Data[1];
					CanRxInfo.bms_info.bms_fault_info.byte2.byte=message.Data[2];
					CanRxInfo.bms_info.bms_fault_info.byte3.byte=message.Data[3];
					CanRxInfo.bms_info.bms_fault_info.bms_cellnumber=message.Data[4];
					CanRxInfo.bms_info.bms_fault_info.bms_tempnumber=message.Data[5];
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_1535_BMS_FAULT_INFO);
					break;
				case CAN_ID_GEAR_INFO:
					CanRxInfo.base_info.gear_info.gear_position=message.Data[0];
					CanRxInfo.base_info.gear_info.motor_rpm=((message.Data[2]<<8)|message.Data[3]);
					CanRxInfo.base_info.gear_info.fault=message.Data[3];
				  if(CanRxInfo.base_info.gear_info.gear_position&0x02)
					{
						CanGeneralCtrlFlag.field.reverse_on_off=1;
					}
					else
					{
						CanGeneralCtrlFlag.field.reverse_on_off=0;
					}
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_1535_GEAR_INFO);
					break;
				case CAN_ID_SPEED_INFO:
					CanRxInfo.base_info.speed_info.vehicle_speed=((message.Data[2]<<8)|message.Data[3]);
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,GOLF_1535_SPEED_INFO);
					break;
				default:
					break;
			}
		}
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
		CanNoDataTimer=T3S_1;//T30S_1;
		CAN1_ClearErrorTimer();
	}
}

void Golf_1535_RxAppDataPro(u8 *buffer)
{
//	u8 cmd_id;
//	cmd_id=buffer[1];

//	if(Get_ACC_Det_Flag==0)
//	{
//		return;
//	}
}

void Golf_1535_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case GOLF_1535_BMS_TOTAL_INFO:
			buffer[2]=0x08;
			buffer[3]=(CanRxInfo.bms_info.bms_total_info.bms_totalvol>>8)&0xFF;
			buffer[4]=CanRxInfo.bms_info.bms_total_info.bms_totalvol&0xFF;
			buffer[5]=(CanRxInfo.bms_info.bms_total_info.bms_totalcur>>8)&0xFF;
			buffer[6]=CanRxInfo.bms_info.bms_total_info.bms_totalcur&0xFF;
		  buffer[7]=CanRxInfo.bms_info.bms_total_info.bms_soc;
			buffer[8]=CanRxInfo.bms_info.bms_total_info.bms_soh;
		  buffer[9]=(CanRxInfo.bms_info.bms_total_info.bms_insulation>>8)&0xFF;
			buffer[10]=CanRxInfo.bms_info.bms_total_info.bms_insulation&0xFF;
			break;
		case GOLF_1535_BMS_VOL_INFO:
			buffer[2]=0x08;
			buffer[3]=(CanRxInfo.bms_info.bms_cell_vol_info.bms_maxcellvol>>8)&0xFF;
			buffer[4]=CanRxInfo.bms_info.bms_cell_vol_info.bms_maxcellvol&0xFF;
			buffer[5]=CanRxInfo.bms_info.bms_cell_vol_info.bms_maxcellvolnum;
			buffer[6]=CanRxInfo.bms_info.bms_cell_vol_info.bms_maxcellvolboxnum;
		  buffer[7]=(CanRxInfo.bms_info.bms_cell_vol_info.bms_mincellvol>>8)&0xFF;
			buffer[8]=CanRxInfo.bms_info.bms_cell_vol_info.bms_mincellvol&0xFF;
		  buffer[9]=CanRxInfo.bms_info.bms_cell_vol_info.bms_mincellvolnum;
			buffer[10]=CanRxInfo.bms_info.bms_cell_vol_info.bms_mincellvolboxnum;
			break;
		case GOLF_1535_BMS_TEMP_INFO:
			buffer[2]=0x08;
			buffer[3]=CanRxInfo.bms_info.bms_cell_temp_info.bms_maxcelltemp;
			buffer[4]=CanRxInfo.bms_info.bms_cell_temp_info.bms_maxcelltempnum;
			buffer[5]=CanRxInfo.bms_info.bms_cell_temp_info.bms_maxcelltempboxnum;
			buffer[6]=CanRxInfo.bms_info.bms_cell_temp_info.bms_mincelltemp;
			buffer[7]=CanRxInfo.bms_info.bms_cell_temp_info.bms_mincelltempnum;
			buffer[8]=CanRxInfo.bms_info.bms_cell_temp_info.bms_mincelltempboxnum;
			buffer[9]=0;
			buffer[10]=0;
			break;
		case GOLF_1535_BMS_STATE_INFO:
			buffer[2]=0x08;
			buffer[3]=CanRxInfo.bms_info.bms_charge_state.bms_chglinestate;
			buffer[4]=CanRxInfo.bms_info.bms_charge_state.bms_chgtype;
			buffer[5]=CanRxInfo.bms_info.bms_charge_state.bms_chgstate;
			buffer[6]=CanRxInfo.bms_info.bms_charge_state.bms_mainrlystate;
			buffer[7]=CanRxInfo.bms_info.bms_charge_state.bms_negrlystate;
			buffer[8]=CanRxInfo.bms_info.bms_charge_state.bms_chgrlystate;
			buffer[9]=0;
			buffer[10]=0;
			break;
		case GOLF_1535_BMS_CUR_INFO:
			buffer[2]=0x08;
			buffer[3]=(CanRxInfo.bms_info.bms_max_cur_info.bms_max_chgcur>>8)&0xFF;
			buffer[4]=CanRxInfo.bms_info.bms_max_cur_info.bms_max_chgcur&0xFF;
			buffer[5]=(CanRxInfo.bms_info.bms_max_cur_info.bms_maxdischgcur>>8)&0xFF;
			buffer[6]=CanRxInfo.bms_info.bms_max_cur_info.bms_maxdischgcur&0xFF;
			buffer[7]=(CanRxInfo.bms_info.bms_max_cur_info.bms_maxfeedbackcur>>8)&0xFF;
			buffer[8]=CanRxInfo.bms_info.bms_max_cur_info.bms_maxfeedbackcur&0xFF;
			buffer[9]=(CanRxInfo.bms_info.bms_max_cur_info.bms_ratedcapacity>>8)&0xFF;
			buffer[10]=CanRxInfo.bms_info.bms_max_cur_info.bms_ratedcapacity&0xFF;
			break;
		case GOLF_1535_BMS_FAULT_INFO:
			buffer[2]=0x08;
			buffer[3]=CanRxInfo.bms_info.bms_fault_info.byte0.byte;
			buffer[4]=CanRxInfo.bms_info.bms_fault_info.byte1.byte;
			buffer[5]=CanRxInfo.bms_info.bms_fault_info.byte2.byte;
			buffer[6]=CanRxInfo.bms_info.bms_fault_info.byte3.byte;
			buffer[7]=CanRxInfo.bms_info.bms_fault_info.bms_cellnumber;
			buffer[8]=CanRxInfo.bms_info.bms_fault_info.bms_tempnumber;
			buffer[9]=0;
			buffer[10]=0;
			break;
		case GOLF_BMS_SINGLE_CELL_VOL:
			buffer[2]=0x08;
			buffer[3]=(CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n1_cellvol>>8)&0xFF;
			buffer[4]=CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n1_cellvol&0xFF;
			buffer[5]=(CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n2_cellvol>>8)&0xFF;
			buffer[6]=CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n2_cellvol&0xFF;
			buffer[7]=(CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n3_cellvol>>8)&0xFF;
			buffer[8]=CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n3_cellvol&0xFF;
			buffer[9]=(CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n4_cellvol>>8)&0xFF;
			buffer[10]=CanRxInfo.bms_info.bms_single_cell_vol.bms_single_n4_cellvol&0xFF;
			break;
		case GOLF_BMS_SINGLE_CELL_TEMP:
			buffer[2]=0x08;
			buffer[3]=CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m1_celltemp;
			buffer[4]=CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m2_celltemp;
			buffer[5]=CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m3_celltemp;
			buffer[6]=CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m4_celltemp;
			buffer[7]=CanRxInfo.bms_info.bms_single_cell_temp. bms_single_m5_celltemp;
			buffer[8]=CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m6_celltemp;
			buffer[9]=CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m7_celltemp;
			buffer[10]=CanRxInfo.bms_info.bms_single_cell_temp.bms_single_m8_celltemp;
			break;
		case GOLF_1535_GEAR_INFO:
			buffer[2]=0x08;
			buffer[3]=CanRxInfo.base_info.gear_info.gear_position;
			buffer[4]=(CanRxInfo.base_info.gear_info.motor_rpm>>8)&0xFF;
			buffer[5]=CanRxInfo.base_info.gear_info.motor_rpm&0xFF;
			buffer[6]=CanRxInfo.base_info.gear_info.fault;
			buffer[7]=0;
			buffer[8]=0;
			buffer[9]=0;
			buffer[10]=0;
			break;
		case GOLF_1535_SPEED_INFO:
			buffer[2]=0x08;
			buffer[3]=0;
			buffer[4]=0;
			buffer[5]=(CanRxInfo.base_info.speed_info.vehicle_speed>>8)&0xFF;
			buffer[6]=CanRxInfo.base_info.speed_info.vehicle_speed&0xFF;
			buffer[7]=0;
			buffer[8]=0;
			buffer[9]=0;
			buffer[10]=0;
			break;
	}
	if(flag)
	{	
		buffer[0]=GOLF_1535_HEAD_CODE;
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

void Golf_1535_MainPro(void)
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
	Golf_1535_Rx_Message();
	if(F_CAN_INIT)
	{
		CAN1_Transmit();
	}
	switch(CanMainState)
	{
		case CAN_MAIN_IDLE:
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;
			break;
		case CAN_MAIN_CFG:
			CAN1_Init();
			CanMainState=CAN_MAIN_INIT;
			break;
		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			CAN1_Ext_ClearTxMessage();
			F_CAN_SLEEP=0;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T25S_1;
			break;
		case CAN_MAIN_NORMAL:
			if(Get_ACC_Det_Flag==0)
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
				CanMainTimer = T1S_1;
			}
			break;
		case CAN_MAIN_SLEEP_CFG:
			if (Get_ACC_Det_Flag)
			{
				CanMainState = CAN_MAIN_NORMAL;
			}
			if (CanMainTimer)
			{
				break;
			}
			CAN1_ClearRxMessage();
			CAN1_Ext_ClearTxMessage();
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
			if(Get_ACC_Det_Flag)
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
