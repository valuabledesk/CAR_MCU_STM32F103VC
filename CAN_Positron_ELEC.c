#include "public.h"

#if CAN_FUN_POSITRON_ELEC==1
u8 DTC_DSP_flag=0;
u8 DTC_TUNER_flag=0;
u32 CanNoDataTimer_sleep;
u32 test_PRO_counter;
u16 UDS_NUM=0;
u8 bsg_bak;
u8 DTC_FLAG_NUM;
u8 DTC_NUM_FLAG;
#if AA_CP_TEST==1
	u8 BSG_off_flag = 1;
#else
	u8 BSG_off_flag = 0;
#endif
u8 test_flag=0;
u8 PKS_OK=0;
static u8 NUM_EOL_VER=1;
u8 EOL_VER_LOCATION[3][10][8];//wjp
u8 DTC_FLAG=0;
u8 USB_MODE=0;
u8 USB_MODE_bak;
u8 APPREADY_REV_FLAG=0;
u16 TIMER_COUNT_APP=0;
u8 RST_BSP_FLAG=0;
DSP_MODE beep_status;
u8 ACC_ex_BSG_flag = 0;
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_TX_15MS_BUFFER CanTxBuffer3;
CAN_TX_200MS_BUFFER CanTxBuffer4;
CAN_TX_1S_BUFFER CanTxBuffer5;
CAN_TX_60MS_BUFFER CanTxBuffer6;
CAN_MAIN_STATE CanMainState;
u8 health_elec;
u8 autonomy_elec;
int UDS_defualt=0;
u8 flag_refresh = 0;
u8 Tx_ill;
u8 APP_OK=0;
u8 test_send_num=0;
u8 box_size;
u8 sta_1ms;
u8 sta_50ms;
u8 sta_70ms;
u8 sta_800ms;
u8 sta_200ms;
u8 length_over;
u16 ver_counter=0;
u16 sm200_counter=4;
u16 sm800_counter=1;
u16 sm50_counter=5;
u16 sm70_counter=2;
u16 defualt_counter=T3S_1;
u16 tel_time=0;
u16 tel_time_bak=0;
u8 bam_num;
u8 uds_clear;
u8 uds_time;
u8 uds_request;
u8 uds_bak;
u8 z;
u8 z_req_ver;
u8 U_BACK;
u8 seek_time;
u8 lang_bak=0;
u8 dis=0;
u8 door=0;
u8 wiper=0;
u8 ill=0xfa;
u8 ill_bak=0xfa;
u8 spe_uni=0;
u8 pre_uni=0;
u8 dis_uni=0;
u8 con_uni=0;
u8 language=0;
u8 bsg_counter;
u8 bsg_counte;
u8 pre_bak=0;
u8 dis_bak;
u8 dis_uni_bak=0;
u8 spe_uni_bak=0;
u8 pre_uni_bak=0;
u8 con_uni_bak=0;
u8 wiper_bak=0;
u8 door_bak=0;
u8 door_counter=0;
u8 wiper_counter=0;
u8 dm_length;
u8 send_add;
u8 many_counter;
u8 data_counter;
u8  chg_counter;
u16 t_counter=1;
u16 r_counter=3;//
u16 med_counter;
u16 fff6_counter;
u16 Uds_defaultTimer;
u8 send_time=0;
u8 send_sta=0;
u8 Test_Sta_flag=0;
u8 MS_100;
u8 p_bak;
u8 m_bak;
u8 t_bak;
u8 vol_bak;
CAN_MAIN_FLAG CanMainFlag;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxBuffer_bak;
CAN_TX_INFO CanTxInfo;
CAN_TX_INFO CanTxInfo_bak;
int j;
int ill_auto;
u8 serch_flag;
u16 freq_bak=0;
u16 freq;
u8 freq_num[9];
u8 chg_flag;
u8 Text_flag=0;
u8 text_num;
u8 Test_sta;
u8 Acc_flag;
u8 flag_f195;
u8 flag_f194;
u8 flag_f192;
u8 flag_Access;
u8 tex[60];
u8 test[60];
u8 send[60];
u8 PGN_L;
u8 PGN_M;
u8 DM1_flag;
u8 navi_sta;
u8 navi_num;
u8 ch_key[8];
u8 check_flag;
u8 Uds_set;
u8 con_flag=1;
u8 set_flag=1;
u16 check_fun;
u32 CanMainTimer;
u32 CanNoDataTimer;
u8 byte_num;
u8 CAN_TEST_TX_BUFFER[CAN_TEST_BUFFER_LENGTH][8];
u8 CAN_TEST_RX_BUFFER[CAN_TEST_BUFFER_LENGTH][8];
u8 send_counter=1;
u8 ser_flag=0;
u8 lang_flag;
u8 r_key[8];
u8 defualt;
u8 dtc_flag;
u8 dm_flag;
u8 dm_num;
u8 bam_flag;
u8 seed_time=0;
u8 A_ILL_Flag;
u8 Test_APP;
u16 CanTxCounter;
u8 tel[35];
const u8 DefaultPrivKeyUds[16] = { 0x1e, 0x0c, 0xac, 0x51, 0x96, 0xa4, 0x3f, 0x51, 0xd9, 0x92, 0xf5, 0x50, 0xf5, 0x4e, 0x43, 0xdd };
u16	UdsTimer=T5S_1;
u16 CanTxTextTimer;
u16 CanTxLanguageTimer;
u16 CanTxManyTimer;
u16 CanTxGearTimer;
u16 CanTxBaseTimer;
u16 CanTxSrcTimer;
u16 CanTxRadTimer;
u16 CanTxMedTimer;
#if TEST_CAN_FUN==1	
u16 Test_Timer;
#endif
u16 CanTxCameraTimer;
u16 CanTxVolTimer;
u16 CanTxTelTimer;
u16 CanTxTripTimer;
u16 CanTxTripTimeTimer;
u16 CanTxAutonomyTimer;
u16 CanTxMaintenanceTimer;
u16 CanTxConsumpTimer;
u16 CanTxWeightTimer;
u16 CanTxAxleWeightTimer;
u32 CanTxAutoTestTimer;
u16 CanTxDriveGradeTimer;
u16 CanTxTimeTimer;
u16 CanTxDateTimer;
u16 CanTxUdsTimer;
u16 CanTxUdsCheckTimer;
u16 Positron_VW_TxTimer;
u16 Positron_VW_TxTelTimer;
u16 Positron_VW_50TxTimer=T50MS_1;
u16 CanTxAutoTimer;
u8 d_loss=0;
u8 test_num;
u8 dtc_num;
u8 d_length;
int data_length;
int data_length_bak;
u8 send_num=1;
u8 many_num=1;
u8 many_num_8=1;
u8 many_num_9=1;
u8 many_num_1=1;
u8 many_num_0=1;
u8 flow_flag;
u8 block_size;
u8 st_min;
u8 sid_bak;
u8 ver_Location;
u8 VER_LOCATION_SEND;
u8 VER_BUFFER[6][20];
u8 DTC_BUFFER[4][50];
u8 dtc_location;
u8 DTC_LOCATION_SEND;
u16 dtc_counter = 0; //dtc scan and save time
u16 EOL_counter = 0; //EOL scan VERTION time
u8 Test_Location;
u8 Test_pid_H;
u8 Test_pid_L;
u8 Test_mode;
u8 Seek_flag;
u8 Uds_flag;
u8 Uds_error;
u8 uds_power_flag;
u8 Test_pid;
u8 Test_eq_flag;
u8 Test_Ill_flag;
u8 Test_Power_flag;
u8 auto_flag;
u8 Check_mode;
u16 CanTxAutoCheckTimer;
u8 sta;
u8 seed[8];
u8 i;
#if DQA_UDS_TEST == 1
u8 ser_ag=1;
u8 Test_Start_flag=1;
#else
u8 ser_ag=0;
u8 Test_Start_flag=0;
#endif

u8 dm[60];
u8 phone[60];
u8 navi[60];
u8 auto_seed[8];
u8 temp;
u32 audio_type_value;
u32 audio_bak;



void Positron_VW_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8]={0};
	if((AccPinStatus&&BSG_off_flag)||(flag_time1_2))
	{
		if(con_flag)
		{
			if(APP_OK)
			{
				switch(index)
				{
					case CAN_POST_MSG_HU_SRC_00:
					{
						data[0]=CanTxInfo.hu_src_0.byte_0.byte;
						data[1]=CanTxInfo.hu_src_0.byte_1.byte;
						data[2]=CanTxInfo.hu_src_0.byte_2.byte;
						data[3]=CanTxInfo.hu_src_0.byte_3.byte;
						data[4]=CanTxInfo.hu_src_0.byte_4.byte;
						data[5]=0;
						data[6]=CanTxInfo.hu_src_0.byte_5.byte;
						data[7]=CanTxInfo.hu_src_0.byte_6.byte;
						CAN1_Ext_TxFrame(CAN_ID_MM_FBK_01,data,8);
					}
					break;
					
					case CAN_POST_MSG_HU_RAD_00:
					{
						data[0]=CanTxInfo.hu_rad_0.byte_0.byte;//当前音量
						data[1]=CanTxInfo.hu_rad_0.byte_1.byte;//最大音量
						data[2]=CanTxInfo.hu_rad_0.byte_2.byte;//车上控制按钮反馈
						data[3]=CanTxInfo.hu_src_0.byte_5.field.f_preset_dig;
						data[4]=CanTxInfo.hu_rad_0.byte_3.byte;//车上媒体切换按钮反馈
						data[5]=CanTxInfo.hu_rad_0.byte_4.byte;//用户控制按钮
						data[6]=CanTxInfo.hu_rad_0.RADIO_AS_COUNTER;//0;//有效台数量
						data[7]=CanTxInfo.hu_rad_0.byte_5.byte;//媒体控制按钮
						CAN1_Ext_TxFrame(CAN_ID_MM_FBK_03,data,8);
					}
					break;
			
					case CAN_POST_TEST:
					{
						for(i=1;i<3;i++)
						{
							CanTxInfo.hu_tes_0.d[i-1]=CAN_TEST_TX_BUFFER[Test_Location][i];//wjp lost FLAG
						}
						if(bam_flag==1)
						{
							for(i=0;i<8;i++)
							{
								data[i]=CanTxInfo.hu_tes_0.d[i];
							}
						}
						else
						{
							data[0]=CanTxInfo.hu_tes_0.pid;
					
							for(i=1;i<8;i++)
							{
								data[i]=CanTxInfo.hu_tes_0.d[i-1];
							}
						}
						
						CAN1_Ext_TxFrame(CAN_ID_TEST_ANSWER,data,8);
					}
					break;
				
					case CAN_POST_DOOR:
					{
						data[0]=CanTxInfo.hu_aut_0.byte_0.byte;
						data[1]=CanTxInfo.hu_aut_0.byte_1.byte;
						CAN1_Ext_TxFrame(CAN_ID_VEHICLE_ANSWER,data,8);
					}
					break;
				
					case CAN_POST_TEXT:
					{
						for(i=0;i<8;i++)
						{
							data[i]=CanTxInfo.hu_tex_0.d[i];
						}
						CAN1_Ext_TxFrame(CAN_ID_MM_FBK_02,data,8);
					}
					break;
					
					case CAN_POST_TEL:
					{
						for(i=0;i<8;i++)
						{
							data[i]=CanTxInfo.hu_tex_0.d[i];
						}
						CAN1_Ext_TxFrame(CAN_ID_TEL_RSP_01,data,8);
					}
					break;
					
					case CAN_POST_NAVI:
					{
						switch(navi_num)
						{
							case 2:
							{
								for(i=0;i<8;i++)
								{
									data[i]=CanTxInfo.hu_tex_0.d[i];
								}
								CAN1_Ext_TxFrame(CAN_ID_NAVIGATION,data,8);
							}
							break;
							
							case 4:
							{
								for(i=0;i<8;i++)
								{
									data[i]=CanTxInfo.hu_tex_0.d[i];
								}
								CAN1_Ext_TxFrame(CAN_ID_PHONE_NAVI,data,8);
							}
							break;
							
						}
					}
					break;
										
					case CAN_POST_UDS:
					{
						if(DTC_FLAG_NUM)
						{
							for(i=0;i<8;i++)
							{
								if(i>=1&&i<=4)
								{
									//data[i]=CanTxInfo.hu_uds_0.d[i];	
									switch(i)
									{
										case 1:
											data[i]=0x59;
										break;
										
										case 2:
											data[i]=0x01;
										break;
										
										case 3:
											data[i]=DTC_NUM_FLAG;
										break;
										
										case 4:
											data[i]=0x01;
										break;
										
										default:
											break;
									}
								}	
								else
								{
									data[i]=CanTxInfo.hu_uds_0.d[i];
								}									
							}
							DTC_FLAG_NUM=0;
						}
						else
						{
							for(i=0;i<8;i++)
							{
								data[i]=CanTxInfo.hu_uds_0.d[i];				
							}		
						}
						switch(Uds_flag)
						{
							case 1:
							{
								CAN1_Ext_TxFrame(CAN_ID_PHYSICAL_ANSWER,data,8);
							}
							break;
							
							case 2:
							{
								CAN1_Ext_TxFrame(CAN_ID_FUNCTIONAL_ANSWER,data,8);
							}
							break;

							case 3:
							{
								CAN1_Ext_TxFrame(CAN_ID_INTERNET_ANSWER,data,8);
							}
							break;
							
						}
					}
					break;
					
					case CAN_POST_DM1:
					{
						for(i=0;i<8;i++)
						{
							data[i]=CanTxInfo.hu_tex_0.dm[i];
						}	
						CAN1_Ext_TxFrame(CAN_ID_DM1_ANSWER,data,8);
					}
					break;
					
					case CAN_POST_CM_BAM:
					{
						if(text_num==5)
						{
							for(i=0;i<8;i++)
							{
								data[i]=CanTxInfo.hu_tex_0.dm[i];
							}
						}
						else
						{
							for(i=0;i<8;i++)
							{
								data[i]=CanTxInfo.hu_tex_0.d[i];
							}
						}
						
						CAN1_Ext_TxFrame(CAN_ID_BAM_CM,data,8);
					}
					break;
					
					case CAN_POST_DA_BAM:
					{
						if(text_num==5)
						{
							for(i=0;i<8;i++)
							{
								data[i]=CanTxInfo.hu_tex_0.dm[i];
							}
						}
						else
						{
							for(i=0;i<8;i++)
							{
								data[i]=CanTxInfo.hu_tex_0.d[i];
							}
						}
						CAN1_Ext_TxFrame(CAN_ID_BAM_DA,data,8);
					}
					break;
					case CAN_ID_STCHARGE_0:
					{
						data[0]=3;
						for(i=1;i<4;i++)
						{
							data[i]=CanTxInfo.hu_charge_0.d[i];
						}
						CAN1_Ext_TxFrame(CAN_ID_STCHARGE,data,4);
					}
						
					default:
						break;
				}
			}
		}			
	}	
}

void Positron_VW_WriteMessage(CAN_POST_MESSAGE_INDEX index)
{
	switch(index)
	{			
		case CAN_POST_MSG_HU_TEL_00:
		{
			send_add=1;
			text_num=3;
			data_length=29;
			send_num=5;
			Positron_VW_BamSendmessage();
		}
		break;
		
		case CAN_POST_MSG_HU_DM1_00:
		{
			send_add=1;
			text_num=5;
			data_length=dm_length;
			send_num=dm_num;
			Positron_VW_BamSendmessage();
		}
		break;
		
		case CAN_POST_MSG_HU_TEXT_00:
		{
			text_num=1;
			send_num=3;
			data_length=16;
			Positron_VW_BamSendmessage();
		}
		break;	
					
		default:
			break;
	}
}

void Positron_VW_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		Test_mode=0;
		
		switch(message.ID)
		{
			case CAN_ID_ENERGY://18FF4221
			{
				CanRxInfo.charge_info.byte_0.field.charge_con_sta=(message.Data[0]&0x0F);
				CanRxInfo.pto_info.byte_0.field.pto_sta=((message.Data[0]&0x30)>>4);
				CanRxInfo.energy_info.byte_0.field.e_automony_h=((message.Data[1]&0xC0)>>6);
				CanRxInfo.energy_info.byte_1.field.e_automony_l =(((message.Data[0]&0xC0)>>6)|((message.Data[1]&0x3F)<<2));
				
//				autonomy_elec=(message.Data[0]&0xC0)>>6;
//				autonomy_elec = autonomy_elec|((message.Data[1]&0x3f)<<2);
//				CanRxInfo.energy_info.byte_1.field.e_automony_l=autonomy_elec;
//				CanRxInfo.energy_info.byte_0.field.e_automony_h=((message.Data[1]&0xC0)>>6);
				
				CanRxInfo.charge_info.byte_3.field.cha_speed=(message.Data[2]&0xFF);
				CanRxInfo.charge_info.byte_2.field.cha_remain_time_l=(message.Data[3]&0xFF);
				CanRxInfo.charge_info.byte_1.field.cha_remain_time_h=(message.Data[4]&0x03);
				CanRxInfo.charge_info.byte_5.field.cha_tol_l=((message.Data[4]&0xFC)>>2);
				CanRxInfo.charge_info.byte_4.field.cha_tol_h=(message.Data[5]&0x0F);
				CanRxInfo.charge_info.byte_7.field.cha_spd_per_l=((message.Data[5]&0xF0)>>4);
				CanRxInfo.charge_info.byte_6.field.cha_spd_per_h=(message.Data[6]&0x3F);
			}
			break;
			
			case CAN_ID_PTO://18FF4321
			{
				CanRxInfo.pto_info.byte_2.field.pro_rpm_l=(message.Data[0]&0xFF);
				CanRxInfo.pto_info.byte_1.field.pro_rpm_h=(message.Data[1]&0xFF);
				CanRxInfo.energy_info.byte_2.field.pro_veh_rat=(message.Data[2]&0xFF);
				CanRxInfo.pto_info.byte_3.field.pto_energy=(message.Data[3]&0xFF);
				CanRxInfo.energy_info.byte_3.field.rec_cha_rat=(message.Data[4]&0xFF);
				CanRxInfo.energy_info.byte_4.field.rec_cur_rat=(message.Data[5]&0xFF);
				CanRxInfo.charge_info.byte_8.field.cha_gain=(message.Data[6]&0xFF);
				CanRxInfo.energy_info.byte_5.field.ins_rec_pow=(message.Data[7]&0xFF);
			}
			break;
			
			case CAN_ID_ENERGY_STA://18FF4421
			{
				CanRxInfo.energy_info.byte_6.field.ave_rec=(message.Data[0]&0xFF);
				CanRxInfo.energy_info.byte_7.field.ave_rec_half=(message.Data[1]&0xFF);
				CanRxInfo.energy_info.byte_8.field.pow_flow=(message.Data[2]&0x03);
				health_elec=(message.Data[2]&0xFC)>>2;
				health_elec=((message.Data[3]&0x03)<<6)|health_elec;
				CanRxInfo.energy_info.byte_9.field.bat_healthy=health_elec;//((message.Data[2]&0xFC)>>2);//message.Data[3]&0x03
			}
			break;
		
			case CAN_ID_CL:
			{
				if(chg_flag==0)
				{
					door=(message.Data[1]&0x01);//door
					wiper=((message.Data[1]&0x02)>>1);//wiper
					spe_uni=((message.Data[1]&0x10)>>4);
					pre_uni=((message.Data[1]&0x20)>>5);
					dis_uni=((message.Data[1]&0x40)>>6);
					language=(message.Data[2]&0x07);
					dis=((message.Data[1]&0x0C)>>2);//display mode
					//((message.Data[2]&0x08)>>3);
					con_uni=((message.Data[2]&0x08)>>3);
					// CAN_POSITRON_Drivers
					CanRxInfo.grad_info.byte_1.field.DriversAvgGradeColor=((message.Data[2]&0xC0)>>6);
					CanRxInfo.grad_info.drive_avg_grad_bar=(message.Data[3]&0xFF);
					CanRxInfo.grad_info.drive_grad_brak=(message.Data[4]&0xFF);
					CanRxInfo.grad_info.drive_grad_gear=(message.Data[5]&0xFF);
					CanRxInfo.grad_info.drive_grad_acc=(message.Data[6]&0xFF);
					CanRxInfo.drives_info.DriversGradeHillDrivingDt=(message.Data[7]&0xFF);
					if(dis_bak==2)
					{
						CanRxInfo.language_info.byte_1.field.f_dis_md=dis;
					}					
					if(door_bak!=door)
					{
						door_bak=door;
						CanRxInfo.vehicle_info.byte_0.field.f_door_open_sta=door_bak;
						CanTxInfo.hu_aut_0.byte_0.field.f_door=door_bak;
					}					
					if(wiper_bak!=wiper)
					{
						wiper_bak=wiper;
						CanRxInfo.vehicle_info.byte_0.field.f_wipe=wiper_bak;
						CanTxInfo.hu_aut_0.byte_0.field.f_wiper=wiper_bak;
					}
					if(spe_uni_bak!=spe_uni)
					{
						spe_uni_bak=spe_uni;
						CanRxInfo.language_info.byte_2.field.f_spe_uni=spe_uni;
					}					
					if(pre_uni_bak!=pre_uni)
					{
						pre_uni_bak=pre_uni;
						CanRxInfo.language_info.byte_2.field.f_pre_uni=pre_uni;
					}					
					if(dis_uni_bak!=dis_uni)
					{						
						dis_uni_bak=dis_uni;
						CanRxInfo.language_info.byte_2.field.f_dis_uni=dis_uni;						
					}			
					if(con_uni_bak!=con_uni)
					{
						con_uni_bak=con_uni;
						CanRxInfo.language_info.byte_2.field.f_con_uni=con_uni;
					}
					if(language)
					{
						if(lang_bak!=language)
						{
							CanRxInfo.language_info.byte_0.field.f_language=language;
							lang_bak=language;
							CanTxInfo.hu_aut_0.byte_1.field.language=language;
						}					
					}
					else
					{
						if(lang_bak!=2)
						{
							CanRxInfo.language_info.byte_0.field.f_language=2;
							lang_bak=2;
							CanTxInfo.hu_aut_0.byte_1.field.language=2;
						}						
					}		
				}				
			}
			break;
			
			case CAN_ID_TIME:
			{
				u8 local_minute_offset=0;
				u8 local_hour_offset=0;
				u8 hours;
				u8 minutes;
				//CanRxInfo.time_info.second=(message.Data[0]&0xFF);//除以%4
				minutes=(message.Data[1]&0xFF);//加1 实车上是对等
				hours=(message.Data[2]&0xFF);//等价  实车上是减3
				CanRxInfo.date_info.months=(message.Data[3]&0xFF);//等价
				CanRxInfo.date_info.days=(message.Data[4]&0xFF);//%4
				CanRxInfo.date_info.years=(message.Data[5]&0xFF);//2024年=0x27=39+1985=2024
				local_minute_offset=0x7D-(message.Data[6]&0xFF);//7D =0 7C=-1; 分差
				local_hour_offset=0x7D-(message.Data[7]&0xFF);//7D =0 7C=-1; 时差
				CanRxInfo.time_info.hours=hours-local_hour_offset;
				CanRxInfo.time_info.minutes=minutes-local_minute_offset;;//等价  		
			}
			break;
			
			case CAN_ID_PARKING_CAMERA:
			{		
				CanRxInfo.remain_info.main_remain_dt_l=(message.Data[0]&0xFF);
				CanRxInfo.remain_info.main_remain_dt_h=(message.Data[1]&0x7F);
				CanRxInfo.vehicle_info.byte_0.field.main_typ=(message.Data[2]&0x03);
				CanRxInfo.remain_info.byte_0.field.main_remain_sta=((message.Data[1]&0x80)>>7);	
				
				CanRxInfo.weight_info.level_adj=(((message.Data[3]&0x03)<<6)|((message.Data[2]&0xFC)>>2));
				CanRxInfo.weight_info.byte_0.field.level_adj_h=((message.Data[3]&0xFC)>>2);
				
				
				ill=(message.Data[4]&0xFF);//light level
				if(ill_bak!=ill)
				{
					ill_bak=ill;							
					CanRxInfo.base_info.f_ill=ill;							
				}					
			}
			break;

			case CAN_ID_ICH2:
			{
				CanRxInfo.axleweight_info.axleweight1=message.Data[0]&0xFF;
				CanRxInfo.axleweight_info.axleweight2=message.Data[1]&0xFF;
				CanRxInfo.axleweight_info.axleweight3=message.Data[2]&0xFF;
				CanRxInfo.axleweight_info.axleweight4=message.Data[3]&0xFF;
				CanRxInfo.axleweight_info.byte_1.field.axleweight1_st=(message.Data[5]&0x03);
				CanRxInfo.axleweight_info.byte_1.field.axleweight2_st=((message.Data[5]&0x0C)>>2);
				CanRxInfo.axleweight_info.byte_1.field.axleweight3_st=((message.Data[5]&0x30)>>4);
				CanRxInfo.axleweight_info.byte_1.field.axleweight4_st=((message.Data[5]&0xC0)>>6);
				CanRxInfo.weight_info.totalweight=(message.Data[6]&0xFF);
				CanRxInfo.weight_info.byte_1.field.totalweight_h=(message.Data[7]&0x03);
				CanRxInfo.vehicle_info.byte_0.field.totalweight_sta=((message.Data[7]&0x04)>>2);
				CanRxInfo.gear_info.byte_0.field.f_parking_brake=((message.Data[7]&0x30)>>4);
				
				if((CanRxInfo.gear_info.byte_0.field.f_parking_brake==1)&&(CanRxInfo.speed_info.vehicle_speed==0))
				{
						CanRxInfo.base_info.byte_0.field.f_parking=1;
						CanGeneralCtrlFlag.field.parking_on_off=1;
				}
				else
				{
						CanRxInfo.base_info.byte_0.field.f_parking=0;
						CanGeneralCtrlFlag.field.parking_on_off=0;
				}
			}
			break;
			
			case CAN_ID_MM_CMD_01:
			{
				u8 p_id=0;
				u8 m_id=0;
				
				p_id=((message.Data[0]&0x30)>>4);
				CanRxInfo.src_info.byte_0.field.f_src_select=(message.Data[3]&0x0F);
				CanRxInfo.rad_info.byte_0.field.f_set_radio=(message.Data[5]&0x8F);
				CanRxInfo.base_info.f_sel_sta_mem=(message.Data[6]&0xFF);
				m_id=(message.Data[7]&0x1F);
				
				if(p_id)
				{					
					p_bak=p_id;
					CanRxInfo.vol_info.byte_0.field.f_set_vol=p_id;
					CanRxInfo.vol_info.byte_0.field.f_set_vol_sta=1;
				}
				else
				{
					CanRxInfo.vol_info.byte_0.field.f_set_vol=0;
					CanRxInfo.vol_info.byte_0.field.f_set_vol_sta=0;
				}
							
				if(m_id==0x11||m_id==0x13)
				{
					m_bak=m_id;
					CanRxInfo.med_info.byte_0.field.f_med_con=m_id;
					CanRxInfo.med_info.byte_0.field.f_cp_med_up=1;
				}
				else if(m_id==0x12||m_id==0x14)
				{
					m_bak=m_id;
					CanRxInfo.med_info.byte_0.field.f_med_con=m_id;
					CanRxInfo.med_info.byte_0.field.f_cp_med_up=0;
				}
				
				if((m_id<0x11)&&(m_id>0))
				{
					m_bak=m_id;
					CanRxInfo.med_info.byte_0.field.f_med_con=m_id;
					CanRxInfo.med_info.byte_0.field.f_med_up=1;
				}
				else if(m_id==0)
				{
					if(m_bak==0x0A||m_bak==0x0B)
					{
						CanRxInfo.med_info.byte_0.field.f_med_con=0;
					}
					else
					{
						CanRxInfo.med_info.byte_0.field.f_med_con=m_bak;
					}
					CanRxInfo.med_info.byte_0.field.f_med_up=0;
				}				
			}
			break;
			
			case CAN_ID_TEL_CMD_01:
			{
				u8 t_id=0;				
				
				if(CanTxInfo.hu_tel_0.byte_3.field.f_tel_sta==0)
				{
					t_id=(message.Data[0]&0xFF);
				}
				else
				{
					if((message.Data[0]&0xFF)==0x05)//有电话来时或者通话中时，不接受获取运营商的指令
					{
						//t_id=t_bak;
					}
					else
					{
						t_id=(message.Data[0]&0xFF);
					}					
				}				
				
				if((t_id>0)&&(t_id<0x10)&&(t_id!=5))
				{
					CanRxInfo.tel_info.byte_0.field.f_tel_up=1;
					CanRxInfo.tel_info.byte_0.field.f_tel_cmd=t_id;
					
					if(t_id==3)
					{
						CanTxInfo.hu_tel_0.byte_3.field.f_tel_sta=0;
						tel_time=0;
					}					
					t_bak=t_id;
				}
				else if(t_id==0)
				{					
					CanRxInfo.tel_info.byte_0.field.f_tel_up=0;
					CanRxInfo.tel_info.byte_0.field.f_tel_cmd=t_bak;
				}
				else if(t_id==5)
				{
					t_bak=0;				
					CanRxInfo.tel_info.byte_0.field.f_tel_up=0;
					CanRxInfo.tel_info.byte_0.field.f_tel_cp_up=0;
					CanRxInfo.tel_info.byte_0.field.f_tel_cmd=t_id;
					tel[5]=t_id;
				}
				else if((t_id>=0x14)&&(t_id<=0x19))
				{					
					t_bak=0;
					CanRxInfo.tel_info.byte_0.field.f_tel_up=0;
					
					if(t_id==0x15||t_id==0x17||t_id==0x19)
					{
						CanRxInfo.tel_info.byte_0.field.f_tel_cp_up=0;						
					}
					else if(t_id==0x14||t_id==0x16||t_id==0x18)
					{					
						CanRxInfo.tel_info.byte_0.field.f_tel_cp_up=1;
						
						if(t_id==0x16)
						{
							CanTxInfo.hu_tel_0.byte_3.field.f_tel_sta=0;
							tel_time=0;
						}
					}					
					CanRxInfo.tel_info.byte_0.field.f_tel_cmd=t_id;
				}
				else 
				{
					CanRxInfo.tel_info.byte_0.field.f_tel_cmd=t_bak;
					CanRxInfo.tel_info.byte_0.field.f_tel_cp_up=0;
					CanRxInfo.tel_info.byte_0.field.f_tel_up=0;
				}			
				CanTxInfo.hu_tel_0.byte_0.field.f_tel_sta=t_id;
			}
			break;	

			case CAN_ID_TEST:
			{
				CanRxInfo.med_info.byte_0.field.f_med_up=0;
				CanRxInfo.tel_info.byte_0.field.f_tel_up=0;
				CanRxInfo.med_info.byte_0.field.f_med_con=0;
				CanRxInfo.tel_info.byte_0.field.f_tel_cmd=0;
				CanRxInfo.test_info.pid=(message.Data[0]&0xFF);
				CanRxInfo.test_info.sid=(message.Data[1]&0xFF);
				Test_pid_H=CanRxInfo.test_info.pid&0xF0;
				Test_pid_L=CanRxInfo.test_info.pid&0x0F;
				Test_Location=(Test_pid_H-0x10)*64+(Test_pid_L-1)*16+(CanRxInfo.test_info.sid-1);
				
				for(i=0;i<8;i++)
				{
					CAN_TEST_RX_BUFFER[Test_Location][i]=(message.Data[i]&0xFF);
				}				
				Test_mode=1;
				Positron_VW_AutoTestStartCheck();
			}
			break;	

			case CAN_ID_PHYSICAL:
			{
				Uds_flag=1;
				Check_mode=1;
				CanRxInfo.uds_info.length=(message.Data[0]&0xFF);
				CanRxInfo.uds_info.sid=(message.Data[1]&0xFF);//功能选择
				
				for(i=0;i<6;i++)
				{
					CanRxInfo.uds_info.d[i]=(message.Data[2+i]&0xFF);//具体数据内容;//全部存储
					CanTxInfo.hu_uds_0.d[i]=0;
				}				
				check_fun=((CanRxInfo.uds_info.d[0])<<8);
				check_fun=check_fun|CanRxInfo.uds_info.d[1];
				
				if((message.Data[0]&0xFF)==0x30)
				{
//					if(flag_f192==1||flag_f194==1||flag_f195==1||flag_Access==1||DTC_FLAG==1)
//					{
						flow_flag=1;
						block_size=(message.Data[1]&0xFF);
						st_min=(message.Data[2]&0xFF);
						CanTxManyTimer=st_min+0x10;
						Positron_VW_ManySendmessage();
						flag_f192=0;
						flag_f194=0;
						flag_f195=0;
						flag_Access=0;
						DTC_FLAG=0;
//					}
				}
				else if(((message.Data[0]&0xFF)==0x10)||((message.Data[0]&0xFF)==0x21))
				{
					Positron_VW_UDS_Security();
				}
				else
				{
					many_num=1;
					Positron_VW_UdsPro();
				}
			}
			break;	
			
			case CAN_ID_FUNCTIONAL:
			{
				Uds_flag=2;
				Check_mode=1;
				CanRxInfo.uds_info.length=(message.Data[0]&0xFF);
				CanRxInfo.uds_info.sid=(message.Data[1]&0xFF);//功能选择
			
				for(i=0;i<6;i++)
				{
					CanRxInfo.uds_info.d[i]=(message.Data[2+i]&0xFF);//具体数据内容;//全部存储
				}
				check_fun=((CanRxInfo.uds_info.d[0])<<8);
				check_fun=check_fun|CanRxInfo.uds_info.d[1];
				
				if((message.Data[0]&0xFF)==0x30)
				{
					flow_flag=1;
					block_size=(message.Data[1]&0xFF);
					st_min=(message.Data[2]&0xFF);
					CanTxManyTimer=st_min+0x10;
					Positron_VW_ManySendmessage();
				}
				else if(((message.Data[0]&0xFF)==0x10)||((message.Data[0]&0xFF)==0x21))
				{
					Positron_VW_UDS_Security();
				}
				else
				{
					many_num=1;
					Positron_VW_UdsPro();
				}
			}
			break;	

			case CAN_ID_INTERNET:
			{
				Uds_flag=3;
				Check_mode=1;
				CanRxInfo.uds_info.length=(message.Data[0]&0xFF);
				CanRxInfo.uds_info.sid=(message.Data[1]&0xFF);//功能选择
			
				for(i=0;i<6;i++)
				{
					CanRxInfo.uds_info.d[i]=(message.Data[2+i]&0xFF);//具体数据内容;//全部存储
				}
				check_fun=((CanRxInfo.uds_info.d[0])<<8);
				check_fun=check_fun|CanRxInfo.uds_info.d[1];
			
				if((message.Data[0]&0xFF)==0x30)
				{
					flow_flag=1;
					block_size=(message.Data[1]&0xFF);
					st_min=(message.Data[2]&0xFF);
					CanTxManyTimer=st_min+0x10;
					Positron_VW_ManySendmessage();
				}
				else if(((message.Data[0]&0xFF)==0x10)||((message.Data[0]&0xFF)==0x21))
				{
					Positron_VW_UDS_Security();
				}
				else
				{
					many_num=1;
					Positron_VW_UdsPro();
				}
			}
			break;		

			case CAN_ID_DM1:
			{		
				if(message.Data[0]==0xCA)
				{
					if(message.Data[1]==0xFE)
					{
						if(message.Data[2]==0)
						{
							Positron_VW_PostMessage(CAN_POST_DM1);
						}
					}
				}
			}
			break;
			
			case CAN_ID_DM1_ALL:
			{		
				if(message.Data[0]==0xCA)
				{
					if(message.Data[1]==0xFE)
					{
						if(message.Data[2]==0)
						{
							Positron_VW_PostMessage(CAN_POST_DM1);
						}
					}
				}
			}
			break;
#if BSG_mode == 1
			case CAN_ID_BSG:
			{
					if(bsg_bak!=(message.Data[0]&0x0F))
					{
						bsg_bak=message.Data[0]&0x0F;
						if((message.Data[0]&0x0F)<0x04&&(message.Data[0]&0x0F)>=0)
						{
							BSG_off_flag=0;
							ACC_ex_BSG_flag = 1;
						}
						else
						{
							if((message.Data[0]&0x0F)>=0x04)

							{
								BSG_off_flag=1;
								flag_time1_2=0;
							}
						}
					}

			}
			break;
#endif
			case CAN_ID_ICG1:
			{
//				CanRxInfo.vhspeed_info.byte_0.field.VehicleSpeed=(message.Data[0]&0xff);
				CanRxInfo.speed_info.vehicle_speed=(message.Data[7]&0xFF);
			}
			break;
			
			case CAN_ID_VDHR:
			{
				
				/* continue to have
				CanRxInfo.vdhr_info.HighResTotalVehicleDist0=(message.Data[0]&0xff);
				CanRxInfo.vdhr_info.HighResTotalVehicleDist1=(message.Data[1]&0xff);
				CanRxInfo.vdhr_info.HighResTotalVehicleDist2=(message.Data[2]&0xff);
				CanRxInfo.vdhr_info.HighResTotalVehicleDist3=(message.Data[3]&0xff);
				*/
			
				CanRxInfo.speed_info.trip_meter_1=(message.Data[4]&0xff);
				CanRxInfo.speed_info.trip_meter_2=(message.Data[5]&0xff);
				CanRxInfo.speed_info.trip_meter_3=(message.Data[6]&0xff);
				CanRxInfo.speed_info.trip_meter_4=(message.Data[7]&0xff);
			}
			break;
			
			case CAN_ID_ICH4:
			{
				CanRxInfo.ich4_info.byte_0.field.TimeHourDt=(message.Data[0]&0x1f);
				CanRxInfo.ich4_info.byte_1.field.TimeMinuteDt_L=((message.Data[0]&0xe0)>>5);
				CanRxInfo.ich4_info.byte_2.field.TimeMinuteDt_H=(message.Data[1]&0x07);
				CanRxInfo.ich4_info.byte_0.field.WeekDayDt=((message.Data[1]&0x38)>>3);
				CanRxInfo.ich4_info.byte_1.field.DateN1Dt=(((message.Data[1]&0xc0)>>6)|((message.Data[2]&0x07)<<2));
				CanRxInfo.ich4_info.byte_2.field.DateN2Dt=((message.Data[2]&0xF8)>>3);
				CanRxInfo.ich4_info.DateYearDt=(message.Data[3]&0xff);
				
				CanRxInfo.trip_time_info.dri_time_hour_l=(message.Data[4]&0xFF);
				CanRxInfo.trip_time_info.byte_0.field.dri_time_hour_h=(message.Data[5]&0x03);
				CanRxInfo.trip_time_info.dri_time_min=((message.Data[5]&0xFC)>>2);
				CanRxInfo.trip_time_info.tra_time_hour_l=(message.Data[6]&0xFF);
				CanRxInfo.trip_time_info.byte_1.field.tra_time_hour_h=(message.Data[7]&0x03);
				CanRxInfo.trip_time_info.tra_time_min=((message.Data[7]&0xFC)>>2);
				
			}
			break;
			
			case CAN_ID_ICH5:
			{
				
				CanRxInfo.consump_info.avg_con=(message.Data[1]&0xFF);
				CanRxInfo.consump_info.instant_con=(message.Data[2]&0xFF);
				CanRxInfo.auto_info.auto_dt=((message.Data[4]&0xFF));
				CanRxInfo.auto_info.byte_0.field.auto_dt_h=(message.Data[5]&0x0F);
				CanRxInfo.speed_info.trip_avg_speed=((message.Data[6]&0x0F)<<4)|((message.Data[5]&0xF0)>>4);
				CanRxInfo.speed_info.byte_0.field.trip_avg_speed_h=((message.Data[6]&0xF0)>>4);
				
				CanRxInfo.grad_info.byte_0.field.DriversGradeBrakingColor=(message.Data[7]&0x03);
				CanRxInfo.grad_info.byte_0.field.DriversGradeGearColor=((message.Data[7]&0x0C)>>2);
				CanRxInfo.grad_info.byte_0.field.DriversGradeAccelerationColor=((message.Data[7]&0x30)>>4);
				CanRxInfo.grad_info.byte_0.field.DriversGradeHillDrivingColor=((message.Data[7]&0xC0)>>6);
			}
			break;
			
			case CAN_ID_USBNODE:
			{
				if(USB_MODE!=(message.Data[0]&0x01))
				{
					USB_MODE=message.Data[0]&0x01;
				}
			}
			break;
			
			default:
				break;
		}
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
		CanNoDataTimer=T5S_1;
		CanNoDataTimer_sleep=T5S_1;
		CAN1_ClearErrorTimer();
	}
}

void Positron_VW_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	cmd_id=buffer[1];
	if(flag_time1_2)
	{}
	else if(AccPinStatus==0||BSG_off_flag==0)
	{
		return;
	}
	
	switch(cmd_id)
	{
		case Positron_VW_TX_SRC_CMD://playing music symbol
		{
			CanTxInfo.hu_src_0.byte_0.byte=0xd8;
			CAN1_Ext_ClearBufferTxMessage();
			
			switch(buffer[3])
			{
				case SRC_CTRL_CMD_RADIO_FM:
				{
					switch(buffer[4])
					{			
						case 1: //等app完善后使用
						{
							CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
							CanTxInfo.hu_src_0.byte_4.field.f_usb=0;
							CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res=0x01;
							CanTxInfo.hu_src_0.byte_1.field.f_aa_con=0;	
							CanTxInfo.hu_src_0.byte_1.field.f_cp_con=0;								
							freq_bak=0;
							
							if(radiostruct_ram.band>2)
							{
								CanTxInfo.hu_src_0.byte_2.field.f_fm=0;
								CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=1;	
							}
							else
							{
								CanTxInfo.hu_src_0.byte_2.field.f_fm=1;
								CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
							}
						}
						break;
						
					}
				}
				break;				
				
				case SRC_CTRL_CMD_BT:
				{
					switch(buffer[4])
					{						
						case 1: //等app完善后使用
						{
							CanTxInfo.hu_src_0.byte_2.field.f_fm=0;
							CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
							CanTxInfo.hu_src_0.byte_3.field.f_bt=1;
							CanTxInfo.hu_src_0.byte_4.field.f_usb=0;				
							CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res=0x05;
							CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=1;
						}
						break;
						
					}			
				}
				break;

				case SRC_CTRL_CMD_USB:
				{
					switch(buffer[4])
					{						
						case 1: //等app完善后使用
						{
							CanTxInfo.hu_src_0.byte_2.field.f_fm=0;
							CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
							CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
							CanTxInfo.hu_src_0.byte_4.field.f_usb=1;				
							CanTxInfo.hu_src_0.byte_1.field.f_usb_con=1;
							CanTxInfo.hu_src_0.byte_1.field.f_aa_con=0;	
							CanTxInfo.hu_src_0.byte_1.field.f_cp_con=0;	
							CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res=0x06;				
						}
						break;		
						
					}
					
			//printf("Write app DM1 data_usb ending to buffer\r\n");
				}
				break;

				case SRC_CTRL_CMD_AA:
				{					
					switch(buffer[4])
					{						
						case 1: //等app完善后使用
						{
							CanTxInfo.hu_src_0.byte_2.field.f_fm=0;
							CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
							CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
							CanTxInfo.hu_src_0.byte_1.field.f_aa_con=1;	
							CanTxInfo.hu_src_0.byte_1.field.f_cp_con=0;	
							CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res=0x08;	
						}
						break;
						
					}
				}
				break;

				case SRC_CTRL_CMD_CP:
				{
					switch(buffer[4])
					{
						case 1:
						{
							CanTxInfo.hu_src_0.byte_2.field.f_fm=0;
							CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
							CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
							CanTxInfo.hu_src_0.byte_1.field.f_aa_con=0;	
							CanTxInfo.hu_src_0.byte_1.field.f_cp_con=1;								
							CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res=0x09;						
						}
						break;
						
					}
				}
				break;
				
			}
		}
		break;
		
		case Positron_VW_TX_CON_SRC_CMD://playing music symbol
		{
			CanTxInfo.hu_src_0.byte_0.byte=0xd8;
			CAN1_Ext_ClearBufferTxMessage();
			CanRxInfo.src_info.byte_0.field.f_src_select=0;
			switch(buffer[3])
			{
				case CON_CTRL_CMD_CP:
				{							
					if(buffer[4]==1)
					{
						CanTxInfo.hu_src_0.byte_1.field.f_cp_con=1;
						CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=4;
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.hu_src_0.byte_1.field.f_cp_con=0;
						
						switch(buffer[5])
						{
							case 1:
							{	
								CanTxInfo.hu_src_0.byte_1.field.f_usb_con=1;
								CanTxInfo.hu_src_0.byte_4.field.f_usb=1;
								if(AccPinStatus)
								{
									if(CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==9)
									{
										CanRxInfo.src_info.byte_0.field.f_src_select=1;
										CanTxInfo.hu_src_0.byte_2.field.f_fm=1;
										CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
										CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
										CanTxInfo.hu_src_0.byte_4.field.f_usb=0;
										freq_bak=0;
									}							
								}
							}
							break;
							
							case 2:
							{
								CanTxInfo.hu_src_0.byte_1.field.f_usb_con=0;
								CanTxInfo.hu_src_0.byte_4.field.f_usb=0;	
								
								if(AccPinStatus)
								{
									if(CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==6\
										||CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==9)
									{
										CanRxInfo.src_info.byte_0.field.f_src_select=1;
										CanTxInfo.hu_src_0.byte_2.field.f_fm=1;
										CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
										CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
										CanTxInfo.hu_src_0.byte_4.field.f_usb=0;
										freq_bak=0;
									}									
								}
							}
							break;
							
						}
						
						switch(buffer[6])
						{
							case 1:
							{	
								CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=1;	
								CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=4;
							}
							break;
							
							case 2:
							{								
								CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=0;
								CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=0;
								
								if(AccPinStatus)
								{
									if(CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==5)
									{
										CanRxInfo.src_info.byte_0.field.f_src_select=1;
										CanTxInfo.hu_src_0.byte_2.field.f_fm=1;
										CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
										CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
										CanTxInfo.hu_src_0.byte_4.field.f_usb=0;
										freq_bak=0;
									}
								}								
							}
							break;
							
							case 3:
							{	
								CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=0;	
								CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=1;
							}
							break;
							
							case 4:
							{	
								CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=0;	
								CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=2;
							}
							break;
							
						}
					}
				}
				break;
				
				case CON_CTRL_CMD_AA:
				{							
					if(buffer[4]==1)
					{
						CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=1;						
						CanTxInfo.hu_src_0.byte_1.field.f_usb_con=1;
						CanTxInfo.hu_src_0.byte_1.field.f_aa_con=1;	
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.hu_src_0.byte_1.field.f_aa_con=0;
						
						switch(buffer[5])
						{
							case 1:
							{	
								CanTxInfo.hu_src_0.byte_1.field.f_usb_con=1;
								CanTxInfo.hu_src_0.byte_4.field.f_usb=1;
								if(AccPinStatus)
								{
									if(CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==8)
									{
										CanRxInfo.src_info.byte_0.field.f_src_select=1;
										CanTxInfo.hu_src_0.byte_2.field.f_fm=1;
										CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
										CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
										CanTxInfo.hu_src_0.byte_4.field.f_usb=0;
										freq_bak=0;
									}
								}
							}
							break;
							
							case 2:
							{
								CanTxInfo.hu_src_0.byte_1.field.f_usb_con=0;
								CanTxInfo.hu_src_0.byte_4.field.f_usb=0;	
								if(power_off_flag==0)
								{
									if(CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==6||CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==9\
									||CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==8)
									{
										CanRxInfo.src_info.byte_0.field.f_src_select=1;
										CanTxInfo.hu_src_0.byte_2.field.f_fm=1;
										CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
										CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
										CanTxInfo.hu_src_0.byte_4.field.f_usb=0;
										freq_bak=0;
									}
								}								
							}
							break;
							
						}
						switch(buffer[6])
						{
							case 1:
							{	
								CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=1;	
								CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=4;
							}
							break;
							
							case 2:
							{								
								CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=0;
								CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=0;
								if(power_off_flag==0)
								{
									if(CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res==5)
									{
										CanRxInfo.src_info.byte_0.field.f_src_select=1;
										CanTxInfo.hu_src_0.byte_2.field.f_fm=1;
										CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
										CanTxInfo.hu_src_0.byte_3.field.f_bt=0;
										CanTxInfo.hu_src_0.byte_4.field.f_usb=0;
										freq_bak=0;
									}
								}								
							}
							break;
							
							case 3:
							{	
								CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=0;	
								CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=1;
							}
							break;
							
							case 4:
							{	
								CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=0;	
								CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=2;
							}
							break;
							
						}
					}
				}
				break;
			}
		}
		break;
				
		case Positron_VW_TX_RADIO_CMD:
		{
			switch(buffer[3])
			{
				case RADIO_USER_CMD_SEEK:
				{
					CanTxInfo.hu_rad_0.byte_4.field.f_rad_seek=buffer[4];
					
					if(buffer[4]==0x03||buffer[4]==0x04)
					{
						Seek_flag=1;
					}					
					if(buffer[4]==0x00)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0;
					}
					else if(buffer[4]==0x01)
					{					
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x01;
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x02;
					}
					else if(buffer[4]==0x03)
					{					
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x03;
					}
					else if(buffer[4]==0x04)
					{					
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x04;
					}					
					Positron_VW_PostMessage(CAN_POST_MSG_HU_RAD_00);
				}
				break;
					
				case RADIO_USER_CMD_MEDIA:
				{
					if(buffer[4]==1)
					{					
						CanTxInfo.hu_rad_0.byte_5.field.f_med_inf=1;
					}
					else if(buffer[4]==2)
					{
						CanTxInfo.hu_rad_0.byte_5.field.f_med_inf=2;
					}
					else if(buffer[4]==3)
					{					
						CanTxInfo.hu_rad_0.byte_5.field.f_med_inf=4;
					}
					else if(buffer[4]==4)
					{					
						CanTxInfo.hu_rad_0.byte_5.field.f_med_inf=8;
					}					
					CanTxInfo.hu_rad_0.byte_5.field.f_med_inf=buffer[4];					
					Positron_VW_PostMessage(CAN_POST_MSG_HU_RAD_00);
					CanTxInfo.hu_rad_0.byte_5.field.f_med_inf=0;	
				}
				break;			

				case MEDIA_CMD_SRC:
				{
					if(buffer[4]==0x00)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0;
					}
					else if(buffer[4]==0x01)
					{					
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x01;
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x02;
					}
					else if(buffer[4]==0x03)
					{					
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x03;
					}
					else if(buffer[4]==0x04)
					{					
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x04;
					}
					Positron_VW_PostMessage(CAN_POST_MSG_HU_RAD_00);
					CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0;
				}
				break;
					
				case RADIO_CMD_CONTROL:
				{
					if(buffer[4]==0x01)
					{
						CanTxInfo.hu_rad_0.byte_2.field.f_rad_fb=0x08;					
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.hu_rad_0.byte_2.field.f_rad_fb=0x09;
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.hu_rad_0.byte_2.field.f_rad_fb=0x0A;
					}
					else if(buffer[4]==0x04)
					{
						CanTxInfo.hu_rad_0.byte_2.field.f_rad_fb=0x0B;
					}
					else if(buffer[4]==0x05)
					{
						CanTxInfo.hu_rad_0.byte_2.field.f_rad_fb=0x80;
					}
					else if(buffer[4]==0x06)
					{
						CanTxInfo.hu_rad_0.byte_2.field.f_rad_fb=0x81;
					}
					else if(buffer[4]==0x00)
					{
						CanTxInfo.hu_rad_0.byte_2.field.f_rad_fb=0;
					}					
					Positron_VW_PostMessage(CAN_POST_MSG_HU_RAD_00);
				}
				break;	

				case MEDIA_CMD_CONTROL:
				{
					if(buffer[4]==0x00)
					{					
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0;
					}
					else if(buffer[4]==0x01)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x01;					
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x02;					
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x0A;					
					}
					else if(buffer[4]==0x04)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x0B;					
					}
					else if(buffer[4]==0x05)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x0D;					
					}
					else if(buffer[4]==0x06)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x11;					
					}
					else if(buffer[4]==0x07)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x12;					
					}
					else if(buffer[4]==0x08)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x13;					
					}
					else if(buffer[4]==0x09)
					{
						CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0x14;
					}					
					Positron_VW_PostMessage(CAN_POST_MSG_HU_RAD_00);
				}
				break;			
				
				case RADIO_USER_CMD_MAX_VOL:
				{
					CanTxInfo.hu_rad_0.byte_1.field.f_max_vol=buffer[4];//最大音量
					Positron_VW_PostMessage(CAN_POST_MSG_HU_RAD_00);
				}
				break;
				
				case RADIO_USER_CMD_CUR_VOL:
				{
					CanTxInfo.hu_rad_0.byte_0.field.f_cur_vol=buffer[4];//当前音量
					Positron_VW_PostMessage(CAN_POST_MSG_HU_RAD_00);
				}
				break;
				
				case RADIO_USER_AS_COUNTER:
   			{
					CanTxInfo.hu_rad_0.RADIO_AS_COUNTER=buffer[4];//有效台数量
					Positron_VW_PostMessage(CAN_POST_MSG_HU_RAD_00);
				}
				break;
			}
		}
		break;
			
		case Positron_VW_TX_TEL_CMD:
		{
			switch(buffer[3])
			{
				case TEL_CTRL_CMD_BAT:
				{
					CanTxInfo.hu_tel_0.byte_1.field.f_pow_sta=buffer[4];
				}
				break;
					
				case TEL_CTRL_CMD_NET:
				{
					CanTxInfo.hu_tel_0.byte_3.field.f_net_sta=buffer[4];
				}
				break;
					
				case TEL_CTRL_CMD_PHONE:
				{
					if(buffer[4]==0x00||buffer[4]==0x04)
					{
						CanTxInfo.hu_tel_0.byte_3.field.f_tel_sta=0;
					}
					else if(buffer[4]==0x01)
					{
						CanTxInfo.hu_tel_0.byte_3.field.f_tel_sta=6;	
					}
					else if(buffer[4]==0x02)
					{
						CanTxInfo.hu_tel_0.byte_3.field.f_tel_sta=4;
					}
					else if(buffer[4]==0x03)
					{
						CanTxInfo.hu_tel_0.byte_3.field.f_tel_sta=3;
					}
				}
				break;		

				case TEL_CTRL_CMD_FIE:
				{
					CanTxInfo.hu_tel_0.byte_2.field.f_fie_str=buffer[4]*6;
				}
				break;
				
				case TEL_CTRL_CMD_PTT:
				{
					CanTxInfo.hu_tel_0.byte_3.field.f_ptt_act=buffer[4];
				}
				break;
						
			}
		}
		break;
			
		case Positron_VW_TX_AUTO_CMD:
		{
			switch(buffer[3])
			{
				case AUT_CTRL_CMD_DOOR:
				{
					if(CanTxInfo.hu_aut_0.byte_0.field.f_door!=buffer[4])
					{
						CanTxInfo.hu_aut_0.byte_0.field.f_door=buffer[4];
						
						if(door_bak!=buffer[4])//判断是否HU主动更改
						{
							door_bak=buffer[4];
							CanRxInfo.vehicle_info.byte_0.field.f_door_open_sta=buffer[4];
							chg_flag=1;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
						}
					}		
				}
				break;
	
				case AUT_CTRL_CMD_WIPER:
				{	
					if(CanTxInfo.hu_aut_0.byte_0.field.f_wiper!=buffer[4])
					{
						CanTxInfo.hu_aut_0.byte_0.field.f_wiper=buffer[4];
						
						if(wiper_bak!=buffer[4])//判断是否HU主动更改
						{
							wiper_bak=buffer[4];
							CanRxInfo.vehicle_info.byte_0.field.f_wipe=buffer[4];
							chg_flag=1;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
						}
					}
				}
				break;	
				
				case AUT_CTRL_CMD_NAVI:
				{			
					navi_sta=buffer[4];
				}
				break;		
				
			}
		}
		break;
			
		case Positron_VW_TX_INF_CMD:
		{
			switch(buffer[3])
			{
				case INF_CTRL_CMD_ALL:
				{
					if(buffer[4]==0x01)
					{					
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_BASE_INO);										
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_SRC_INO);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_RAD_INO);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_VOL_INO);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEL_INO);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_AXLEWEIGHT_INO);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_WEIGHT_INO);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_CONSUMP_INO);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TRIP_INO);
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TRIP_TIME_INO);						
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_AUTONOMY_INO);						
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_MAIN_INO);						
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_DRV_GRADE_INO);			
					}					
				}
				break;
	
				case INF_CTRL_CMD_SWITCH:
				{					
					switch(buffer[4])
					{
						case 0:// base 信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_BASE_INO);
						}
						break;
						
						case 1://Src 信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_SRC_INO);
						}
						break;
							
						case 2://Radio 信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_RAD_INO);
						}
						break;
							
						case 3://VOL信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_VOL_INO);
						}
						break;
							
						case 4://TEL信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEL_INO);
						}
						break;
							
						case 5://AxleWeight信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_AXLEWEIGHT_INO);
						}
						break;
							
						case 6://Weight信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_WEIGHT_INO);
						}
						break;
							
						case 7://Consump信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_CONSUMP_INO);
						}
						break;
							
						case 8://Trip信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TRIP_INO);
						}
						break;
							
						case 9://Trip Time 信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TRIP_TIME_INO);
						}
						break;
							
						case 10://Autonomy信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_AUTONOMY_INO);
						}
						break;

						case 11://Maintenance信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_MAIN_INO);
						}
						break;

						case 12://Drive_Grade信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_DRV_GRADE_INO);
						}
						break;

						case 13://UDS信息
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_INFORMATION_UDS_INO);	
						}
						break;					
		
					}
				}
				break;	
				
			}
		}
		break;
		
		case Positron_VW_TX_FILES_CMD:
		{
			for(i=0;i<60;i++)
			{
				tex[i]=0;
				phone[i]=0;
				navi[i]=0;
			}			
			CanRxInfo.test_set_info.gain=0;
			CanRxInfo.test_set_info.minus=0;
			CanRxInfo.test_set_info.order=0;			
			d_length=buffer[2]-1;
			CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length+d_length;
			
			switch(buffer[3])
			{		
				case FILE_CMD_MUSIC://歌曲信息
				{
					data_length=buffer[2]-1;//total length
					text_num=1;	
					
					for(i=0;i<data_length;i++)
					{
						tex[i]=buffer[i+4];
					}					
					data_length=16;
					send_num=3;
					
					if(navi_sta)
					{
						navi_num=4;
				
						for(i=0;i<data_length;i++)
						{
							phone[i]=tex[i];
							phone[i+16]=tex[i+16];
						}
					}
					CAN1_Ext_ClearBufferTxMessage();
					Positron_VW_BamSendmessage();
				}
				break;
				
				case FILE_CMD_NAVI_STREET://导航街道及距离
				{
					data_length=buffer[2]-1;//total length
					
					for(i=0;i<data_length;i++)
					{
						navi[i]=buffer[i+4];//第一个字节图标
					}					
					data_length_bak=data_length;
					send_num=1;
					
					while(data_length_bak)
					{
						data_length_bak=data_length_bak-7;
						
						if(data_length_bak<0)
						{
							data_length_bak=0;
						}						
						else if(data_length_bak)
						{
							send_num++;
						}
					}
					
					if(send_num<2)
					{
						for(i=0;i<8;i++)
						{
							CanTxInfo.hu_tex_0.d[i]=navi[i];
						}
						navi_num=2;
						Positron_VW_PostMessage(CAN_POST_TEXT);
						send_num=1;
					}
					else
					{
						navi_num=2;
						CAN1_Ext_ClearBufferTxMessage();
						Positron_VW_BamSendmessage();
					}
				}
				break;
				
				case FILE_CMD_NAVI_DIS://导航信息距离信息
				{
					data_length=buffer[2]-1;//total length
					
					for(i=0;i<data_length;i++)
					{
						phone[i]=buffer[i+4];
					}
					data_length_bak=data_length;
					send_num=1;
				
					while(data_length_bak)
					{
						data_length_bak=data_length_bak-7;
					
						if(data_length_bak<0)
						{
							data_length_bak=0;
						}						
						else if(data_length_bak)
						{
							send_num++;
						}
					}
					if(send_num<2)
					{
						for(i=0;i<8;i++)
						{
							CanTxInfo.hu_tex_0.d[i]=phone[i];
						}						
						navi_num=4;
						Positron_VW_PostMessage(CAN_POST_TEXT);
						send_num=1;
					}
					else
					{
						navi_num=4;
						CAN1_Ext_ClearBufferTxMessage();
						Positron_VW_BamSendmessage();
					}
				}
				break;

				case FILE_CMD_NET://网络运营商信息
				{
					CanTxInfo.hu_tel_0.byte_0.byte=buffer[4];
					data_length=buffer[2]-1;//total length
					text_num=3;
					
					for(i=0;i<data_length;i++)
					{
						tex[i]=buffer[i+4];						
						tel[i+5]=tex[i];						
					}					
					
					if(navi_sta)
					{
						navi_num=4;
				
						for(i=0;i<16;i++)
						{
							phone[i]=tex[i];
							phone[i+16]=tex[i+16];
						}
					}
					CAN1_Ext_ClearBufferTxMessage();					
					Positron_VW_BamSendmessage();
				}
				break;

				case FILE_CMD_TEL://电话信息
				{
					u8 tel_flag=0;
					
					tel[0]=buffer[4];
					CanTxInfo.hu_tel_0.byte_0.byte=tel[0];
					data_length=buffer[2]-1;//total length
					text_num=3;
					send_add=1;
					
					for(i=0;i<(data_length-2);i++)
					{
						tex[i]=buffer[i+5];
						tel[i+5]=tex[i];						
					}					
					for(j=16;j<28;j++)
					{
						if(tel[j]==0)
						{
							tel_flag++;
						}
					}
					tel[28]=0x22;
					if(tel_flag==11)
					{
						for(j=17;j<28;j++)
						{
							tel[j]=0xff;
						}
						tel_flag=0;
					}
					else
					{
						tel_flag=0;
					}
					if(navi_sta)
					{
						navi_num=4;
				
						for(i=0;i<16;i++)
						{
							phone[i]=tex[i];
							phone[i+16]=tex[i+16];
						}
					}	
					CAN1_Ext_ClearBufferTxMessage();
					Positron_VW_BamSendmessage();
				}
				break;

				case FILE_CMD_TIME_TEL://电话时长记录信息
				{
					tel[0]=buffer[4];
					CanTxInfo.hu_tel_0.byte_0.byte=tel[0];
					data_length=buffer[2]-1;//total length
					text_num=3;
					send_add=1;
					
					for(i=0;i<data_length;i++)
					{
						tex[i]=buffer[i+5];
						tel[i+5]=tex[i];						
					}
				
					tel_time=tel[5]+tel[6]+tel[7];
					
					if(tel_time_bak!=tel_time)
					{
						tel_time_bak=tel_time;
						CanTxInfo.hu_tel_0.byte_3.field.f_tel_sta=4;
					}
					else
					{
						CanTxInfo.hu_tel_0.byte_0.field.f_tel_sta=0;
						tel_time=0;
					}										
				
					if(navi_sta)
					{
						navi_num=4;
				
						for(i=0;i<3;i++)
						{
							phone[i+32]=tel[i+5];						
						}
					}		
					Positron_VW_BamSendmessage();
				}
				break;
					
				case FILE_CMD_DTC_NUM_ACT://126天内发生过的DTC码的数量
				{	
					DTC_NUM_FLAG=0x09;
					CanTxInfo.hu_uds_0.d[0]=6;			
					CanTxInfo.hu_tex_0.act_num=buffer[4];
					CanTxInfo.hu_uds_0.d[6]=CanTxInfo.hu_tex_0.act_num;
					DTC_FLAG_NUM=1;
					Positron_VW_PostMessage(CAN_POST_UDS);
					CanRxInfo.uds_info.byte_0.field.rd_act_num=0;
				}
				break;
				
				case FILE_CMD_DTC_NUM_PAS://最后一次发生时间已经超过126天的DTC码的数量
				{	
					DTC_NUM_FLAG=0x08;
					CanTxInfo.hu_uds_0.d[0]=6;						
					CanTxInfo.hu_tex_0.pas_num=buffer[4];
					CanTxInfo.hu_uds_0.d[6]=CanTxInfo.hu_tex_0.pas_num;
					DTC_FLAG_NUM=1;
					Positron_VW_PostMessage(CAN_POST_UDS);
					CanRxInfo.uds_info.byte_0.field.rd_pas_num=0;
				}
				break;
				
				case FILE_CMD_DTC_NUM_NEV://未发生过的DTC码的数量
				{
					DTC_NUM_FLAG=0x00;
					CanTxInfo.hu_uds_0.d[0]=6;						
					CanTxInfo.hu_tex_0.no_ocr_num=buffer[4];
					CanTxInfo.hu_uds_0.d[6]=CanTxInfo.hu_tex_0.no_ocr_num;
					DTC_FLAG_NUM=1;
					Positron_VW_PostMessage(CAN_POST_UDS);
					CanRxInfo.uds_info.byte_0.field.rd_not_ocr_num=0;				
				}
				break;
				
				case FILE_CMD_DTC_ACT://126天内发生过的DTC码
				{	
					u8 k=0;
					data_length=d_length+3;				
					dtc_num=d_length/4;
					dtc_location=0;
					for(u8 k=1;k<data_length+2;k++)
						{
							switch(k)
							{
								case 1:
									{
										DTC_BUFFER[dtc_location][k] = data_length;
									}
								break;
								
								case 2:
									{
										DTC_BUFFER[dtc_location][k] = 0x59;
									}
								break;
								
								case 3:
									{
										DTC_BUFFER[dtc_location][k] = 0x02;
									}
								break;
									
								case 4:
									{
										DTC_BUFFER[dtc_location][k] = 0x09;
									}
								break;
								
								default:
								{
									DTC_BUFFER[dtc_location][k]=buffer[k-1];
								}
								break;
							}
						}
					data_length_bak=data_length;
					
					if(dtc_num>1)
					{
						many_num=1;
						
						for(i=0;i<dtc_num;i++)
						{
							switch(i)
							{
								case 0:
								{
									data_length_bak=data_length_bak-6;
									
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}
									else if(data_length_bak)
									{
										many_num++;//??send_num=2
									}
								}
								break;
							
								default:
								{
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak>7)
									{
										many_num++;//??many_num=3
										data_length_bak=data_length_bak-7;
									}	
								}
								break;
							}
						}
					}
					else
					{
						many_num=1;
					}
					DTC_BUFFER[dtc_location][0]=many_num;
					CanRxInfo.uds_info.byte_0.field.rd_act=0;

				}
				break;
				
				case FILE_CMD_DTC_PAS://最后一次发生时间已经超过126天的DTC码 C
				{		
					d_length=buffer[2]-1;
					data_length=d_length+3;
					dtc_location=1;	
					dtc_num=d_length/4;
					for(u8 k=1;k<data_length+2;k++)
						{
							switch(k)
							{
								case 1:
									{
										DTC_BUFFER[dtc_location][k] = data_length;
									}
								break;
								
								case 2:
									{
										DTC_BUFFER[dtc_location][k] = 0x59;
									}
								break;
								
								case 3:
									{
										DTC_BUFFER[dtc_location][k] = 0x02;
									}
								break;
									
								case 4:
									{
										DTC_BUFFER[dtc_location][k] = 0x08;
									}
								break;
								
								default:
								{
									DTC_BUFFER[dtc_location][k]=buffer[k-1];
								}
								break;
							}
						}
					data_length_bak=data_length;
					if(dtc_num>1)
					{
						many_num=1;
						
						for(i=0;i<dtc_num;i++)
						{
							switch(i)
							{
								case 0:
								{
									data_length_bak=data_length_bak-6;
									
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}
									else if(data_length_bak)
									{
										many_num++;
									}
								}
								break;
							
								default:
								{
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak>7)
									{
										many_num++;
										data_length_bak=data_length_bak-7;
									}	
								}
								break;
							}
						}
					}
					else
					{
						many_num=1;
					}
					DTC_BUFFER[dtc_location][0]=many_num;
					CanRxInfo.uds_info.byte_0.field.rd_pas=0;					
				}
				break;

				case FILE_CMD_DTC_NEV://未发生过的DTC码 D
				{	
					u8 k=0;				
					d_length=buffer[2]-1;
					data_length=d_length+3;
					dtc_location = 2;
						for(k=1;k<data_length+2;k++)
						{
							switch(k)
							{
								case 1:
									{
										DTC_BUFFER[dtc_location][k] = data_length;
									}
								break;
								
								case 2:
									{
										DTC_BUFFER[dtc_location][k] = 0x1f;
									}
								break;
								
								case 3:
									{
										DTC_BUFFER[dtc_location][k] = 0x59;
									}
								break;
								
								case 4:
									{
										DTC_BUFFER[dtc_location][k] = 0x02;
									}
								break;

								case 5:
									{
										DTC_BUFFER[dtc_location][k] = 0x00;
									}
								break;
								
								default:
								{
									DTC_BUFFER[dtc_location][k]=buffer[k-2];
								}
								break;
							}
						}
					dtc_num=d_length/4;
					
//					if(dtc_num==0)
//					{
//						for(i=0;i<50;i++)
//						{
//							CanTxInfo.hu_tex_0.dtc[i]=0;
//						}
//					}
					data_length_bak=data_length;
					
					if(dtc_num>1)
					{
						many_num=1;
						for(i=0;i<dtc_num;i++)
						{
							switch(i)
							{
								case 0:
								{
									data_length_bak=data_length_bak-6;
									
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak)
									{
										many_num++;//此时send_num=2
									}
								}
								break;
							
								default:
								{
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}								
									else if(data_length_bak>7)
									{
										many_num++;//此时send_num=3
										data_length_bak=data_length_bak-7;
									}	
								}
								break;
								
							}
						}
					}
					else
					{
						many_num=1;
					}
					DTC_BUFFER[dtc_location][0]=many_num;
					CanRxInfo.uds_info.byte_0.field.rd_not_ocr=0;
				}
				break;
				
				case FILE_CMD_DTC_PA_ACT://126天内发生过的DTC码和最后一次发生时间已经超过126天的DTC码 E->8
				{			
					d_length=buffer[2]-1;
					data_length=d_length+3;
					dtc_location=3;	
					dtc_num=d_length/4;
					for(u8 k=1;k<data_length+2;k++)
						{
							switch(k)
							{
								case 1:
									{
										DTC_BUFFER[dtc_location][k] = data_length;
									}
								break;
								
								case 2:
									{
										DTC_BUFFER[dtc_location][k] = 0x59;
									}
								break;
								
								case 3:
									{
										DTC_BUFFER[dtc_location][k] = 0x02;
									}
								break;
									
								case 4:
									{
										DTC_BUFFER[dtc_location][k] = 0x01;
									}
								break;
								
								default:
								{
									DTC_BUFFER[dtc_location][k]=buffer[k-1];
								}
								break;
							}
						}
//					if(dtc_num==0)
//					{
//						for(i=0;i<50;i++)
//						{
//							CanTxInfo.hu_tex_0.dtc[i]=0;
//						}
//					}
					data_length_bak=data_length;
					if(dtc_num>1)
					{
						many_num=1;
						
						for(i=0;i<dtc_num;i++)
						{
							switch(i)
							{
								case 0:
								{
									data_length_bak=data_length_bak-6;
									
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}
									else if(data_length_bak)
									{
										many_num++;//??send_num=2
									}
								}
								break;
							
								default:
								{
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak>7)
									{
										many_num++;//??many_num=3
										data_length_bak=data_length_bak-7;
									}	
								}
								break;
							}
						}
					}
					else
					{
						many_num=1;
					}
					DTC_BUFFER[dtc_location][0]=many_num;
					CanRxInfo.uds_info.byte_0.field.rd_act_pas=0;
				}
				break;
				
				case FILE_CMD_DTC_NUM_PA_ACT://126天内发生过的DTC码的数量和最后一次发生时间已经超过126天的DTC码的数量
				{
					DTC_NUM_FLAG=0x01;
					CanTxInfo.hu_uds_0.d[0]=6;	
					CanTxInfo.hu_tex_0.act_num=buffer[4];
					CanTxInfo.hu_tex_0.pas_num=buffer[5];
					CanTxInfo.hu_uds_0.d[6]=CanTxInfo.hu_tex_0.pas_num+CanTxInfo.hu_tex_0.act_num;
					DTC_FLAG_NUM=1;
					Positron_VW_PostMessage(CAN_POST_UDS);
					CanRxInfo.uds_info.byte_0.field.rd_act_pas_num=0;
				}
				break;

				case FILE_CMD_HW://设备硬件号
				{			
					u8 k=0;
					
					uds_request=0;
					sta=2;
					d_length=buffer[2]-1;
					data_length=d_length+3;
					ver_Location=2;
					for(k=1;k<=data_length+1;k++)
					{
						switch(k)
						{
							case 1:
							{
								VER_BUFFER[ver_Location][k]=data_length;
							}
							break;

							case 2:
							{
								VER_BUFFER[ver_Location][k]=0x62;
							}
							break;

							case 3:
							{
								VER_BUFFER[ver_Location][k]=0xf1;
							}
							break;

							case 4:
							{
								VER_BUFFER[ver_Location][k]=ver_Location+0x90;
							}
							break;

							default:
							{
								VER_BUFFER[ver_Location][k]=buffer[k-1];
							}
							break;
						}					
					}
					
										
					dtc_num=d_length/4;
					data_length_bak=data_length;
					
					if(dtc_num>1)
					{
						many_num=1;
						
						for(i=0;i<dtc_num;i++)
						{
							switch(i)
							{
								case 0:
								{
									data_length_bak=data_length_bak-6;
									
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak)
									{
										many_num++;//此时send_num=2
									}
								}
								break;
							
								default:
								{
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak>7)
									{
										many_num++;//此时send_num=3
										data_length_bak=data_length_bak-7;
									}	
								}
								break;
								
							}
						}						
					}
					VER_BUFFER[ver_Location][0]=many_num;
					CanRxInfo.uds_info.byte_4.field.hard_num_req=0;
				}
				break;

				case FILE_CMD_VER_HW://设备硬件版本号
				{
					u8 k=0;
					uds_request=0;
					sta=2;
					d_length=buffer[2]-1;
					data_length=d_length+3;
					
					ver_Location=3;
					for(k=1;k<=data_length+1;k++)
					{
						switch(k)
						{
							case 1:
							{
								VER_BUFFER[ver_Location][k]=data_length;
							}
							break;

							case 2:
							{
								VER_BUFFER[ver_Location][k]=0x62;
							}
							break;

							case 3:
							{
								VER_BUFFER[ver_Location][k]=0xf1;
							}
							break;

							case 4:
							{
								VER_BUFFER[ver_Location][k]=ver_Location+0x90;
							}
							break;

							default:
							{
								VER_BUFFER[ver_Location][k]=buffer[k-1];
							}
							break;
						}					
					}
				
					dtc_num=d_length/4;
					data_length_bak=data_length;
					
					if(dtc_num>1)
					{
						many_num=1;
						
						for(i=0;i<dtc_num;i++)
						{
							switch(i)
							{
								case 0:
								{
									data_length_bak=data_length_bak-6;
									
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak)
									{
										many_num++;//此时send_num=2
									}
								}
								break;
							
								default:
								{
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak>7)
									{
										many_num++;//此时send_num=3
										data_length_bak=data_length_bak-7;
									}	
								}
								break;
								
							}
						}
					}
					VER_BUFFER[ver_Location][0]=many_num;
					CanRxInfo.uds_info.byte_4.field.hard_ver_num_req=0;
				}
				break;

				case FILE_CMD_SW://设备软件号
				{
					u8 k=0;
					uds_request=0;
					sta=2;
					d_length=buffer[2]-1;
					data_length=d_length+3;
					
					ver_Location=4;
					for(k=1;k<=data_length+1;k++)
					{
						switch(k)
						{
							case 1:
							{
								VER_BUFFER[ver_Location][k]=data_length;
							}
							break;

							case 2:
							{
								VER_BUFFER[ver_Location][k]=0x62;
							}
							break;

							case 3:
							{
								VER_BUFFER[ver_Location][k]=0xf1;
							}
							break;

							case 4:
							{
								VER_BUFFER[ver_Location][k]=ver_Location+0x90;
							}
							break;

							default:
							{
								VER_BUFFER[ver_Location][k]=buffer[k-1];
							}
							break;
						}					
					}				
					dtc_num=d_length/4;
					data_length_bak=data_length;
					
					if(dtc_num>1)
					{
						many_num=1;
						
						for(i=0;i<dtc_num;i++)
						{
							switch(i)
							{
								case 0:
								{
									data_length_bak=data_length_bak-6;
									
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak)
									{
										many_num++;//此时send_num=2
									}
								}
								break;
							
								default:
								{
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak>7)
									{
										many_num++;//此时send_num=3
										data_length_bak=data_length_bak-7;
									}	
								}
								break;
								
							}
						}
					}
					VER_BUFFER[ver_Location][0]=many_num;
					if(VER_BUFFER[ver_Location][5]!=0x00&&VER_BUFFER[ver_Location][6]!=0x00)
					{
						CanRxInfo.uds_info.byte_4.field.soft_num_req=0;
					}
				}
				break;

				case FILE_CMD_VER_SW://设备软件版本号
				{
					u8 k=0;
					
					uds_request=0;
					sta=2;
					d_length=buffer[2]-1;
					data_length=d_length+3;
					ver_Location=5;
					for(k=1;k<=data_length+1;k++)
					{
						switch(k)
						{
							case 1:
							{
								VER_BUFFER[ver_Location][k]=data_length;
							}
							break;

							case 2:
							{
								VER_BUFFER[ver_Location][k]=0x62;
							}
							break;

							case 3:
							{
								VER_BUFFER[ver_Location][k]=0xf1;
							}
							break;

							case 4:
							{
								VER_BUFFER[ver_Location][k]=ver_Location+0x90;
							}
							break;

							default:
							{
								VER_BUFFER[ver_Location][k]=buffer[k-1];
							}
							break;
						}					
					}				
					dtc_num=d_length/4;
					data_length_bak=data_length;
					
					if(dtc_num>1)
					{
						many_num=1;
						
						for(i=0;i<dtc_num;i++)
						{
							switch(i)
							{
								case 0:
								{
									data_length_bak=data_length_bak-6;
									
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak)
									{
										many_num++;//此时send_num=2
									}
								}
								break;
							
								default:
								{
									if(data_length_bak<0)
									{
										data_length_bak=0;
									}									
									else if(data_length_bak>7)
									{
										many_num++;//此时send_num=3
										data_length_bak=data_length_bak-7;
									}	
								}
								break;
								
							}
						}
					}
					VER_BUFFER[ver_Location][0]=many_num;
					if(VER_BUFFER[ver_Location][5]!=0x00&&VER_BUFFER[ver_Location][6]!=0x00)
					{
						CanRxInfo.uds_info.byte_4.field.soft_ver_num_req=0;
					}
				}
				break;
				
				case FILE_CMD_DM1://DM1消息
				{
					CanRxInfo.uds_info.byte_4.field.dm1_req=0;
					
					for(i=0;i<100;i++)
					{
						dm[i]=0;
					}					
					dm_num=0;
					data_length=buffer[2]-1;//total length
					dm_length=data_length;
					
					for(i=0;i<data_length;i++)
					{
						dm[i]=buffer[i+4];
					}
					
					if(dm[0]==0)
					{
						dm[6]=0xff;
						dm[7]=0xff;
					}
					data_length_bak=data_length;
					send_num=1;
					
					while(data_length_bak)
					{
						data_length_bak=data_length_bak-7;
						
						if(data_length_bak<0)
						{
							data_length_bak=0;
						}						
						else if(data_length_bak)
						{
							send_num++;
						}
					}
					if(send_num<2)
					{
						for(i=0;i<8;i++)
						{
							CanTxInfo.hu_tex_0.dm[i]=dm[i];
						}						
						dm_flag=1;						
						Positron_VW_PostMessage(CAN_POST_DM1);						
						send_num=0;						
					}
					else
					{
						dm_flag=2;
						text_num=5;
						data_length=dm_length;
						dm_num=send_num;
						Positron_VW_BamSendmessage();
					}
				}
				break;

				case FILE_CMD_NAME_BT://查询本机蓝牙名字
				{
					data_length=buffer[2]-1;//total length
					test_num=1;
					test_send_num=data_length/5;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;					
				
				case FILE_CMD_CON_NAME_BT://查询配对设备的蓝牙名字
				{
					data_length=buffer[2]-1;//total length
					test_num=1;
					test_send_num=data_length/5;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}				
					Positron_VW_AutoTestSendmessage();
				}
				break;

				case FILE_CMD_BT_MAC://查询蓝牙MAC地址
				{
					data_length=buffer[2]-1;//total length
					test_num=2;
					test_send_num=data_length/4;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;

				case FILE_CMD_NET_MAC://查询互联网MAC地址
				{
					data_length=buffer[2]-1;//total length
					test_num=2;
					test_send_num=data_length/4;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;
				
				case FILE_CMD_NET_TCP://查询互联网TCP/IP 地址
				{
					data_length=buffer[2]-1;//total length
					test_num=2;
					test_send_num=data_length/4;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;
				
				case FILE_CMD_HD_VD_OP://查询经纬度精度因子
				{
					data_length=buffer[2]-1;//total length
					test_num=5;
					test_send_num=data_length/3;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;

				case FILE_CMD_LA_LO_DE://查询经纬度
				{
					data_length=buffer[2]-1;//total length
					test_num=3;
					test_send_num=data_length/6;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;
				
				case FILE_CMD_WIFI_MAC://查询WIFIMAC地址
				{
					data_length=buffer[2]-1;//total length
					test_num=2;
					test_send_num=data_length/4;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;

				case FILE_CMD_BN://查询第几部分Build Number
				{
					/*data_length=buffer[2]-1;//total length			
					test_send_num=data_length/5;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();*/
					u8 VER_NUM=0;
					data_length=buffer[2]-1;//total length
					VER_NUM=buffer[4];
					EOL_VER_LOCATION[2][VER_NUM][0]=data_length;
					for(u8 i=1;i<data_length+1;i++)
					{
						EOL_VER_LOCATION[2][VER_NUM][i]=buffer[i+3];
					}	
				}
				break;

				case FILE_CMD_UN://查询unit serial Number
				{
					data_length=buffer[2]-1;//total length
					test_num=2;
					test_send_num=data_length/4;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;

				case FILE_CMD_TEST_MARK://查询测试标记
				{
					data_length=buffer[2]-1;//total length									
					test_send_num=data_length/5;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;

				case FILE_CMD_MAN_TIME://查询单元生产时间轴
				{
					data_length=buffer[2]-1;//total length					
					test_send_num=data_length/5;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}					
					Positron_VW_AutoTestSendmessage();
				}
				break;
				
				case FILE_CMD_MCU://查询第几部分MCU 版本号
				{
					/*data_length=buffer[2]-1;//total length			
					test_send_num=data_length/5;

					for(i=0;i<data_length;i++)
					{
						test[i]=buffer[i+4];
					}				
					Positron_VW_AutoTestSendmessage();*/
					u8 VER_NUM=0;
					data_length=buffer[2]-1;//total length
					VER_NUM=buffer[4];
					EOL_VER_LOCATION[1][VER_NUM][0]=data_length;
					for(u8 i=1;i<data_length+1;i++)
					{
						EOL_VER_LOCATION[1][VER_NUM][i]=buffer[i+3];
					}
				}
				break;
				
			}
			
			for(i=0;i<8;i++)
			{
				CanTxInfo.hu_tes_0.d[i]=0;
			}	
		}
		break;
	
		case Positron_VW_TX_UDS_CMD:
		{
			U_BACK=1;
			
			switch(buffer[3])
			{
				case UDS_CMD_NAVI://离线地图模式启用状态
				{
					CanRxInfo.uds_info.byte_3.field.navi_offline_req=0;
//					if(APP_OK==0) 
//					{
//						CanRxInfo.uds_info.byte_1.field.navi_offline=buffer[4];		
//					}
					//CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_1.field.navi_offline;
					CanTxInfo.hu_uds_0.d[4]=buffer[4];
				}
				break;
				
				case UDS_CMD_NET://以太网连接状态
				{
					CanRxInfo.uds_info.byte_3.field.net_con_req=0;
//					if(APP_OK==0) 
//					{
//						CanRxInfo.uds_info.byte_1.field.net_con=buffer[4];
//					}
					//CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_1.field.net_con;	
					CanTxInfo.hu_uds_0.d[4]=buffer[4];
				}
				break;

				case UDS_CMD_DRV://Driver's Grade
				{
					CanTxInfo.hu_uds_0.d[4]=buffer[4];
//					if(APP_OK==0)
//					{
//						CanRxInfo.uds_info.byte_1.field.dri_gra_en=buffer[4];
//					}		
						CanRxInfo.uds_info.byte_3.field.dri_gra_req=0;
				}
				break;

				case UDS_CMD_TRIP://Trip and Vehicle data
				{
					CanTxInfo.hu_uds_0.d[4]=buffer[4];	
//					if(APP_OK==0) {
//					CanRxInfo.uds_info.byte_1.field.tri_veh_en=buffer[4];		}
						CanRxInfo.uds_info.byte_3.field.tri_veh_req=0;					
				}
				break;

				case UDS_CMD_DOOR://门和雨刷器
				{
					CanTxInfo.hu_uds_0.d[0]=5;
					CanRxInfo.uds_info.byte_3.field.wip_dor_req=0;
//					if(APP_OK==0)
//					{
//						switch(buffer[4])
//						{
//							case 0:
//							{
//								CanTxInfo.hu_uds_0.d[4]=0;
//								CanTxInfo.hu_uds_0.d[5]=0;
//								CanRxInfo.uds_info.byte_2.field.door_en=0;
//								CanRxInfo.uds_info.byte_2.field.wipe_en=0;
//							}
//							break;
//							
//							case 1:
//							{
//								CanTxInfo.hu_uds_0.d[4]=1;
//								CanTxInfo.hu_uds_0.d[5]=0;
//								CanRxInfo.uds_info.byte_2.field.door_en=1;
//								CanRxInfo.uds_info.byte_2.field.wipe_en=0;
//							}
//							break;
//							
//							case 2:
//							{
//								CanTxInfo.hu_uds_0.d[4]=0;
//								CanTxInfo.hu_uds_0.d[5]=1;
//								CanRxInfo.uds_info.byte_2.field.door_en=0;
//								CanRxInfo.uds_info.byte_2.field.wipe_en=1;
//							}
//							break;
//							
//							case 3:
//							{
//								CanTxInfo.hu_uds_0.d[4]=1;
//								CanTxInfo.hu_uds_0.d[5]=1;
//								CanRxInfo.uds_info.byte_2.field.door_en=1;
//								CanRxInfo.uds_info.byte_2.field.wipe_en=1;
//							}
//							break;
//						
//						}
//					}
				}
				break;
				
				case UDS_CMD_WEIG://Weight 和 Level
				{
					CanTxInfo.hu_uds_0.d[0]=5;
					CanRxInfo.uds_info.byte_3.field.wei_lev_req=0;
//					if(APP_OK==0)
//					{
//						switch(buffer[4])
//						{
//							case 0:
//							{
//								CanTxInfo.hu_uds_0.d[4]=0;
//								CanTxInfo.hu_uds_0.d[5]=0;
//								CanRxInfo.uds_info.byte_2.field.wei_en=0;
//								CanRxInfo.uds_info.byte_2.field.lev_en=0;
//								
//							}
//							break;
//							
//							case 1:
//							{
//								CanTxInfo.hu_uds_0.d[4]=1;
//								CanTxInfo.hu_uds_0.d[5]=0;
//								CanRxInfo.uds_info.byte_2.field.wei_en=1;
//								CanRxInfo.uds_info.byte_2.field.lev_en=0;
//							}
//							break;
//							
//							case 2:
//							{
//								CanTxInfo.hu_uds_0.d[4]=0;
//								CanTxInfo.hu_uds_0.d[5]=1;
//								CanRxInfo.uds_info.byte_2.field.wei_en=0;
//								CanRxInfo.uds_info.byte_2.field.lev_en=1;
//							}
//							break;
//							
//							case 3:
//							{
//								CanTxInfo.hu_uds_0.d[4]=1;
//								CanTxInfo.hu_uds_0.d[5]=1;
//								CanRxInfo.uds_info.byte_2.field.wei_en=1;
//								CanRxInfo.uds_info.byte_2.field.lev_en=1;
//							}
//							break;
//				
//						}
//					}
				}
				break;
				
				case UDS_CMD_PARKING_CAMERA://PARKING_CAMER
				{
					CanTxInfo.hu_uds_0.d[4]=buffer[4];	
					CanRxInfo.uds_info.byte_3.field.camera_req=0;
//					if(APP_OK==0) {
//						CanRxInfo.uds_info.byte_2.field.camera_en=buffer[4];}
				}
				break;
				
				case UDS_CMD_PARKING_SENSOR://PARKING_SENSO
				{
					CanTxInfo.hu_uds_0.d[4]=buffer[4];	
					CanRxInfo.uds_info.byte_3.field.sensor_req=0;
//					if(APP_OK==0){
//						CanRxInfo.uds_info.byte_2.field.sensor_en=buffer[4];}	
				}
				break;
				
				case UDS_CMD_UNIT_MENU://UNIT MENU
				{
					CanTxInfo.hu_uds_0.d[4]=buffer[4];	
					CanRxInfo.uds_info.byte_4.field.unit_menu_req=0;
//					if(APP_OK==0){
//						CanRxInfo.uds_info.byte_2.field.unit_en=buffer[4];}
				}
				break;
				
				case UDS_CMD_AD_ADB_BLUE://AD_ADB_BLUE
				{
					CanTxInfo.hu_uds_0.d[4]=buffer[4];	
					CanRxInfo.uds_info.byte_4.field.ad_blue_auto_req=0;
//					if(APP_OK==0){
//						CanRxInfo.uds_info.byte_2.field.ad_blue_auto_en=buffer[4];}
				}
				break;
				
				case UDS_CMD_PTO:
				{
					CanTxInfo.hu_uds_0.d[4]=buffer[4];	
					CanRxInfo.uds_info.byte_6.field.pto_req=0;
					CanRxInfo.uds_info.byte_5.field.pto_en=buffer[4];
				}
				break;
				
				case UDS_CMD_VOLKS://Chame|VOLKS
				{
					CanTxInfo.hu_uds_0.d[4]=buffer[4];	
					CanRxInfo.uds_info.byte_6.field.chome_volks_req=0;
				}
				break;
		
			}
			if(UDS_defualt==1)
			{
				if(uds_request)
				{
					if(buffer[3]!=0x01)
					{
						//Positron_VW_PostMessage(CAN_POST_UDS);	
						uds_request=0;
					}					
				}				
			}
		}
		break;
			
		case Positron_VW_TX_VEHICLE_CMD:
		{
			switch(buffer[3])
			{
				case VEHICLE_CMD_TYPE://
				{
					U_BACK=1;
//					if(APP_OK==0){
//					CanRxInfo.uds_info.byte_1.field.vehc_type=buffer[4];}
					CanRxInfo.uds_info.byte_4.field.model_req=0;	
					CanTxInfo.hu_uds_0.d[4]=buffer[4];	
					
					//if(UDS_defualt==1)
					//{
				    //    Positron_VW_PostMessage(CAN_POST_UDS);	
					//}					
				}
				break;
				
				case VEHICLE_CMD_DISP://
				{
					if(CanTxInfo.hu_aut_0.byte_0.field.f_dis!=buffer[4])
					{
						CanTxInfo.hu_aut_0.byte_0.field.f_dis=buffer[4];
						
						
						if(dis_bak!=buffer[4])//判断是否HU主动更改
						{
							dis_bak=buffer[4];
							CanRxInfo.language_info.byte_1.field.f_dis_md=buffer[4];//HU主动更改才会进到这里
							chg_flag=1;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
						}
					}
				}
				break;
				
				case VEHICLE_CMD_LANG://	
				{
					if(CanTxInfo.hu_aut_0.byte_1.field.language!=buffer[4])
					{
						CanTxInfo.hu_aut_0.byte_1.field.language=buffer[4];
						
						if(lang_bak!=buffer[4])//判断是否HU主动更改
						{
							lang_bak=buffer[4];//HU主动更改才会进到这里
							CanRxInfo.language_info.byte_0.field.f_language=buffer[4];
							chg_flag=1;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
						}
					}		
				}
				break;
				
				case VEHICLE_CMD_UNI_DIS://
				{		
					if(CanTxInfo.hu_aut_0.byte_1.field.dis_uni!=buffer[4])
					{
						CanTxInfo.hu_aut_0.byte_1.field.dis_uni=buffer[4];
						
						if(dis_uni_bak!=buffer[4])//判断是否HU主动更改
						{
							dis_uni_bak=buffer[4];
							CanRxInfo.language_info.byte_2.field.f_dis_uni=buffer[4];//HU主动更改才会进到这里
							chg_flag=1;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
						}
					}				
				}
				break;				
				
				case VEHICLE_CMD_UNI_CON:
				{		
					if(CanTxInfo.hu_aut_0.byte_1.field.con_uni!=buffer[4])
					{
						CanTxInfo.hu_aut_0.byte_1.field.con_uni=buffer[4];
						
						if(con_uni_bak!=buffer[4])//判断是否HU主动更改
						{
							con_uni_bak=buffer[4];
							CanRxInfo.language_info.byte_2.field.f_con_uni=buffer[4];//HU主动更改才会进到这里
							chg_flag=1;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
						}
					}				
				}
				break;
				
				case VEHICLE_CMD_UNI_SPE://
				{
					if(CanTxInfo.hu_aut_0.byte_0.field.spe_uni!=buffer[4])
					{
						CanTxInfo.hu_aut_0.byte_0.field.spe_uni=buffer[4];
						
						if(spe_uni_bak!=buffer[4])//判断是否HU主动更改
						{
							spe_uni_bak=buffer[4];							
							CanRxInfo.language_info.byte_2.field.f_spe_uni=buffer[4];//HU主动更改才会进到这里
							chg_flag=1;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
						}
					}					
				}
				break;
				
				case VEHICLE_CMD_UNI_PRE://
				{
					if(CanTxInfo.hu_aut_0.byte_0.field.pre_uni!=buffer[4])
					{
						CanTxInfo.hu_aut_0.byte_0.field.pre_uni=buffer[4];
						
						if(pre_uni_bak!=buffer[4])//判断是否HU主动更改
						{
							pre_uni_bak=buffer[4];							
							CanRxInfo.language_info.byte_2.field.f_pre_uni=buffer[4];//HU主动更改才会进到这里
							chg_flag=1;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
						}
					}			
				}
				break;
				
				case VEHICLE_CMD_RESET://清空Trip 、Consum、Drive Grade 数据按钮
				{
					if(buffer[4]==1)
					{
						CanTxInfo.hu_aut_0.byte_0.field.f_reset=1;			
						chg_flag=1;
					}
				
										
				}
				break;
				
				/*case VEHICLE_CMD_AUTO_ILL://ill auto
				{
					ill_auto=buffer[4];
									
					if(ill_auto==0)
					{
						Tx_ill=0;
					}
					else
					{
						CanTxInfo.hu_aut_0.f_ill=0xfb;
						chg_flag=1;
						CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
					}
				}
				break;	*/		
					
				default:
				break;
			}				
		}
		break;
			
		case Positron_VW_TX_TEST_SET_CMD:
		{
			CanRxInfo.test_set_info.gain=0;
			CanRxInfo.test_set_info.minus=0;
			CanRxInfo.test_set_info.order=0;
			Test_APP=0;
			
			switch(buffer[3])
			{
				case TEST_CMD_TREBLE:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
				
				case TEST_CMD_MID:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;

				
				case TEST_CMD_BASS:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;

				case TEST_CMD_USB_CONNECT_TYPE:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
				
				case TEST_CMD_GPS_STA:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;

				
				case TEST_CMD_GPS_NUM:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;

				case TEST_CMD_WIFI_CON_STA:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
				
				case TEST_BTN_STA:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
					CanTxInfo.hu_tes_0.d[3]=buffer[5];
				}
				break;
		
				case TEST_CMD_DISPLAY_STA:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;

				case TEST_CMD_TOUCH_STA:
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
				
				case TEST_CMD_TOUCH_LOC://触摸点坐标
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];//x
					CanTxInfo.hu_tes_0.d[3]=buffer[5];//x
					CanTxInfo.hu_tes_0.d[4]=buffer[6];//y
					CanTxInfo.hu_tes_0.d[5]=buffer[7];//y
				}
				break;

				case TEST_CMD_GPS_SNR://gps测试点
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
					CanTxInfo.hu_tes_0.d[3]=buffer[5];
					CanTxInfo.hu_tes_0.d[4]=buffer[6];					
				}
				break;

				case TEST_CMD_MAF_VER://生产商软件版本
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
				
				case TEST_CMD_BEP_STA://Beep
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
				
				case TEST_CMD_WIF_STA://Wifi 开关
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;				
				
				case TEST_CMD_HOTSOPT_STA://Wifi 热点开关
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
				
				case TEST_CMD_ETH_STA://Wifi 开关
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;		

				case TEST_CMD_USB_STA://USB playing status
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;	
				
				case TEST_CMD_BT_STA://BT 开关
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
				
				case TEST_CMD_MIC_STA://MIC 开关
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
			
				case TEST_CMD_IGO_STA://IGO 
				{
					CanTxInfo.hu_tes_0.d[2]=buffer[4];
				}
				break;
			}			
			Positron_VW_PostMessage(CAN_POST_TEST);	
		}
		break;	
		
		case Positron_VW_TX_CHARGE_SET_CMD:
		{
			CanTxInfo.hu_charge_0.d[1]=buffer[4];
			CanTxInfo.hu_charge_0.d[2]=buffer[5];
			CanTxInfo.hu_charge_0.d[3]=buffer[6];
			Positron_VW_PostMessage(CAN_ID_STCHARGE_0);
		}
		break;
		
		case Positron_VW_TX_UDS_FLAG_CMD:
		{
			CanRxInfo.uds_info.byte_1.byte=buffer[4];
			CanRxInfo.uds_info.byte_2.byte=buffer[3];
			CanRxInfo.uds_info.byte_5.byte=buffer[5];
		}
		break;
		
		case Positron_VW_TX_PKS_CMD:
		{
			PKS_OK=buffer[2];
		}
		break;	
		
		default:
		break;
	}
}

void Positron_VW_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 checksum=0;
	u32 flag=1;
	
	switch(cmd_id)
	{
		case Positron_VW_RX_BASE_INO:
		{
			buffer[2]=0x04;
			buffer[3]=CanRxInfo.base_info.byte_0.byte;
			buffer[4]=0;
			buffer[5]=CanRxInfo.vehicle_info.byte_0.byte;
			buffer[6]=CanRxInfo.base_info.f_ill;
		}
		break;
			
		case Positron_VW_RX_SRC_INO:
		{
			buffer[2]=0x01;
			buffer[3]=CanRxInfo.src_info.byte_0.byte;
		}
		break;
			
		case Positron_VW_RX_RAD_INO:
		{
			buffer[2]=0x01;
			buffer[3]=CanRxInfo.rad_info.byte_0.byte;
		}
		break;
			
		case Positron_VW_RX_VOL_INO:
		{
			buffer[2]=0x01;
			buffer[3]=CanRxInfo.vol_info.byte_0.byte;
		}
		break;
			
		case Positron_VW_RX_TEL_INO:
		{
			buffer[2]=0x01;
			buffer[3]=CanRxInfo.tel_info.byte_0.byte;
		}
		break;
		
		case Positron_VW_RX_MED_INO:
		{
			buffer[2]=0x01;
			buffer[3]=CanRxInfo.med_info.byte_0.byte;
		}
		break;

		case Positron_VW_RX_AXLEWEIGHT_INO:
		{
			buffer[2]=0x06;
			//buffer[3]=CanRxInfo.axleweight_info.byte_0.byte;
			buffer[3]=0;
			buffer[4]=CanRxInfo.axleweight_info.axleweight1;
			buffer[5]=CanRxInfo.axleweight_info.axleweight2;
			buffer[6]=CanRxInfo.axleweight_info.axleweight3;
			buffer[7]=CanRxInfo.axleweight_info.axleweight4;
			buffer[8]=CanRxInfo.axleweight_info.byte_1.byte;		
		}
		break;

		case Positron_VW_RX_WEIGHT_INO:
		{
			buffer[2]=0x04;
			buffer[3]=CanRxInfo.weight_info.level_adj;
			buffer[4]=CanRxInfo.weight_info.byte_0.byte;
			buffer[5]=CanRxInfo.weight_info.totalweight;
			buffer[6]=CanRxInfo.weight_info.byte_1.byte;
		}
		break;

		case Positron_VW_RX_CONSUMP_INO:
		{
			buffer[2]=0x04;
			buffer[3]=CanRxInfo.consump_info.byte_0.byte;
			buffer[4]=CanRxInfo.consump_info.instant_con;
			buffer[5]=CanRxInfo.consump_info.avg_con;
			buffer[6]=CanRxInfo.consump_info.fuel_liter;
		}
		break;
		
		case Positron_VW_RX_TRIP_INO:
		{
			buffer[2]=0x0B;
			buffer[3]=CanRxInfo.speed_info.byte_0.byte;
			buffer[4]=CanRxInfo.speed_info.vehicle_speed;
			buffer[5]=CanRxInfo.speed_info.trip_avg_speed;
			buffer[6]=CanRxInfo.speed_info.trip_meter_1;
			buffer[7]=CanRxInfo.speed_info.trip_meter_2;	
			buffer[8]=CanRxInfo.speed_info.trip_meter_3;	
			buffer[9]=CanRxInfo.speed_info.trip_meter_4;	
			buffer[10]=CanRxInfo.vdhr_info.HighResTotalVehicleDist0;
			buffer[11]=CanRxInfo.vdhr_info.HighResTotalVehicleDist1;
			buffer[12]=CanRxInfo.vdhr_info.HighResTotalVehicleDist2;
			buffer[13]=CanRxInfo.vdhr_info.HighResTotalVehicleDist3;
		}
		break;
			
		case Positron_VW_RX_TRIP_TIME_INO:
		{
			buffer[2]=0x06;
			buffer[3]=CanRxInfo.trip_time_info.dri_time_hour_l;
			buffer[4]=CanRxInfo.trip_time_info.byte_0.byte;
			buffer[5]=CanRxInfo.trip_time_info.dri_time_min;
			buffer[6]=CanRxInfo.trip_time_info.tra_time_hour_l;
			buffer[7]=CanRxInfo.trip_time_info.byte_1.byte;
			buffer[8]=CanRxInfo.trip_time_info.tra_time_min;
		}
		break;

		case Positron_VW_RX_AUTONOMY_INO:
		{
			buffer[2]=0x04;
			buffer[3]=CanRxInfo.auto_info.auto_dt;
			buffer[4]=CanRxInfo.auto_info.byte_0.field.auto_dt_h;
			buffer[5]=CanRxInfo.auto_info.ad_blue_auto_dt;
			buffer[6]=CanRxInfo.auto_info.byte_1.field.ad_blue_auto_dt_h;
		}
		break;

		case Positron_VW_RX_MAIN_INO:
		{
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.remain_info.main_remain_dt_l;
			buffer[4]=CanRxInfo.remain_info.main_remain_dt_h;
			buffer[5]=CanRxInfo.remain_info.byte_0.byte;
		}
		break;
			
		case Positron_VW_RX_DRV_GRADE_INO:
		{
			buffer[2]=0x06;
			buffer[3]=CanRxInfo.grad_info.drive_avg_grad_bar;
			buffer[4]=CanRxInfo.grad_info.drive_grad_acc;
			buffer[5]=CanRxInfo.grad_info.drive_grad_gear;
			buffer[6]=CanRxInfo.grad_info.drive_grad_brak;
			buffer[7]=CanRxInfo.grad_info.byte_1.field.DriversAvgGradeColor;
			buffer[8]=CanRxInfo.grad_info.byte_0.byte;
		}
		break;

		case Positron_VW_RX_CHECK_UDS_INO:
		{
			buffer[2]=0x04;
			buffer[3]=CanRxInfo.uds_error_info.byte_0.byte;
			buffer[4]=CanRxInfo.uds_error_info.byte_1.byte;
			buffer[5]=CanRxInfo.uds_error_info.byte_2.byte;
			buffer[6]=CanRxInfo.uds_error_info.byte_3.byte;			
		}
		break;
		
		case Positron_VW_RX_SETTING_UDS_INO:
		{
			buffer[2]=0x09;
			buffer[3]=CanRxInfo.uds_info.byte_0.byte;
			buffer[4]=CanRxInfo.uds_info.dtc_h;
			buffer[5]=CanRxInfo.uds_info.dtc_m;
			buffer[6]=CanRxInfo.uds_info.dtc_l;
			buffer[9]=CanRxInfo.uds_info.byte_3.byte;
			buffer[10]=CanRxInfo.uds_info.byte_4.byte;
			buffer[11]=CanRxInfo.uds_info.byte_6.byte;
		}
		break;

		case  Positron_VW_RX_INFORMATION_UDS_INO:
		{
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.uds_info.byte_1.byte;
			buffer[4]=CanRxInfo.uds_info.byte_2.byte;
			buffer[5]=CanRxInfo.uds_info.byte_5.byte;//pto
		}
		break;
		
		case  Positron_VW_RX_LANGUAGE_INO:
		{
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.language_info.byte_0.byte;
			buffer[4]=CanRxInfo.language_info.byte_1.byte;
			buffer[5]=CanRxInfo.language_info.byte_2.byte;
		}
		break;
		
		case  Positron_VW_RX_CAMERA_INO:
		{
			buffer[2]=0x04;
			buffer[3]=CanRxInfo.camera_info.l_exten;
			buffer[4]=CanRxInfo.camera_info.l_inten;
			buffer[5]=CanRxInfo.camera_info.r_inten;
			buffer[6]=CanRxInfo.camera_info.r_exten;		
		}
		break;
		
		case  Positron_VW_RX_TEST_BT_INO:
		{
			buffer[2]=0x16;
			
			for(i=0;i<22;i++)
			{
				buffer[3+i]=send[i];
			}
		}
		break;
			
		case Positron_VW_RX_TEST_INO:
		{
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.test_set_info.order;
			buffer[4]=CanRxInfo.test_set_info.minus;
			buffer[5]=CanRxInfo.test_set_info.gain;
		}
		break; 
		
		case Positron_VW_RX_DATE_INO:
		{
			buffer[2]=0x03;
			buffer[3]=CanRxInfo.date_info.years;
			buffer[4]=CanRxInfo.date_info.months;
			buffer[5]=CanRxInfo.date_info.days;
		}
		break; 
		
		case Positron_VW_RX_TIME_INO:
		{
			buffer[2]=0x02;
			buffer[3]=CanRxInfo.time_info.hours;
			buffer[4]=CanRxInfo.time_info.minutes;
		}
		break; 
		
		case Positron_VW_RX_CHARGE_INO:
		{
			buffer[2]=0x09;
			buffer[3]=CanRxInfo.charge_info.byte_0.byte;
			buffer[4]=CanRxInfo.charge_info.byte_1.byte;
			buffer[5]=CanRxInfo.charge_info.byte_2.byte;
			buffer[6]=CanRxInfo.charge_info.byte_3.byte;
			buffer[7]=CanRxInfo.charge_info.byte_4.byte;
			buffer[8]=CanRxInfo.charge_info.byte_5.byte;
			buffer[9]=CanRxInfo.charge_info.byte_6.byte;
			buffer[10]=CanRxInfo.charge_info.byte_7.byte;
			buffer[11]=CanRxInfo.charge_info.byte_8.byte;
		}
		break; 
		
		case Positron_VW_RX_PTO_INO:
		{
			buffer[2]=0x04;
			buffer[3]=CanRxInfo.pto_info.byte_0.byte;
			buffer[4]=CanRxInfo.pto_info.byte_1.byte;
			buffer[5]=CanRxInfo.pto_info.byte_2.byte;
			buffer[6]=CanRxInfo.pto_info.byte_3.byte;
		}
		break; 
		
		case Positron_VW_RX_ENERGY_INO:
		{
			buffer[2]=0x0A;
			buffer[3]=CanRxInfo.energy_info.byte_0.byte;
			buffer[4]=CanRxInfo.energy_info.byte_1.byte;
			buffer[5]=CanRxInfo.energy_info.byte_2.byte;
			buffer[6]=CanRxInfo.energy_info.byte_3.byte;
			buffer[7]=CanRxInfo.energy_info.byte_4.byte;
			buffer[8]=CanRxInfo.energy_info.byte_5.byte;
			buffer[9]=CanRxInfo.energy_info.byte_6.byte;
			buffer[10]=CanRxInfo.energy_info.byte_7.byte;
			buffer[11]=CanRxInfo.energy_info.byte_8.byte;
			buffer[12]=CanRxInfo.energy_info.byte_9.byte;
		}
		break; 
		
		case Positron_VW_RX_UDS_FLAG_INO:
		{
			buffer[2]=0x01;
			buffer[3]=0x01;
		}
		break;
		
		case Positron_VW_RX_USB_MODE:
		{
			buffer[2]=0x01;
			buffer[3]=USB_MODE;
		}
		break;
		
		case Positron_VW_RX_PKS_INO:
		{
			buffer[2]=0x01;
			buffer[3]=0x01;
		}
		break;
		
		case Positron_VW_RX_TIMES_INO:
		{
			buffer[2]=0x04;
			buffer[3]=CanRxInfo.ich4_info.byte_0.byte;
			buffer[4]=CanRxInfo.ich4_info.byte_1.byte;
			buffer[5]=CanRxInfo.ich4_info.byte_2.byte;
			buffer[6]=CanRxInfo.ich4_info.DateYearDt;
		}
		break;
		
		default:
		{
			flag=0;
		}
		break;
	}
	
	if(flag)
	{	
		buffer[0]=Positron_VW_HEAD_CODE;
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

void Positron_VW_MainPro(void)
{
	EOL_counter++;
	test_PRO_counter++;
	dtc_counter++;
	t_counter++;
	r_counter++;
	fff6_counter++;
	med_counter++;
	sm200_counter++;
	sm50_counter++;
	sm70_counter++;
	sm800_counter++;
	TIMER_COUNT_APP++;
	
	if(CanMainTimer)
	{
		CanMainTimer--;
	}	
	if(Positron_VW_TxTimer)
	{
		Positron_VW_TxTimer--;
	}	
	if(Positron_VW_TxTelTimer)
	{
		Positron_VW_TxTelTimer--;
	}	
	if(CanTxLanguageTimer)
	{
		CanTxLanguageTimer--;
	}	
	if(CanTxSrcTimer)
	{
		CanTxSrcTimer--;
	}
	if(Test_Sta_flag||Test_Power_flag)
	{
		if(CanTxAutoTestTimer)
		{
			CanTxAutoTestTimer--;
		}
	}	
	if(CanTxRadTimer)
	{
		CanTxRadTimer--;
	}
	if(uds_clear||uds_request)
	{
		if(Uds_defaultTimer)
		{
			Uds_defaultTimer--;
		}
	}
	if(CanTxMedTimer)
	{
		CanTxMedTimer--;
	}
	if(Test_Start_flag)//EOL中按键测试自动归位所用
	{
		if(CanTxMedTimer==0)
		{
			CanRxInfo.med_info.byte_0.field.f_med_up=0;
		}
		if(CanTxTelTimer==0)
		{
			CanRxInfo.tel_info.byte_0.field.f_tel_up=0;
		}
		if(CanTxRadTimer==0)
		{
			CanRxInfo.rad_info.byte_0.field.f_set_radio=0;
		}
	}
	
	if(Test_Sta_flag)
	{
		if(CanTxMedTimer==0)
		{
			CanRxInfo.med_info.byte_0.field.f_med_up=0;
		}
		if(CanTxTelTimer==0)
		{
			CanRxInfo.tel_info.byte_0.field.f_tel_up=0;
		}
		if(CanTxRadTimer==0)
		{
			CanRxInfo.rad_info.byte_0.field.f_set_radio=0;
		}
	}
	
	
	if(CanTxCameraTimer)
	{
		CanTxCameraTimer--;
	}
	
	if(CanTxVolTimer)
	{
		CanTxVolTimer--;		
	}
	
	if(CanTxGearTimer)
	{
		CanTxGearTimer--;		
	}	
	
	if(CanTxGearTimer==0)
	{
		CanTxGearTimer=T30S_1000;
	}
	
	if(CanTxVolTimer==0)
	{
		CanTxVolTimer=T10S_1;
	}
	if(CanTxSrcTimer==0)
	{
		CanTxSrcTimer=T30S_1;
	}
	if(Positron_VW_TxTimer==0)
	{
		Positron_VW_TxTimer=T1800S_100;
	}
	
	if(CanTxBaseTimer)
	{
		CanTxBaseTimer--;		
	}
	
	if(CanTxTelTimer)
	{
		CanTxTelTimer--;
	}
	
	if(CanTxTripTimeTimer)
	{
		CanTxTripTimeTimer--;
	}
	
	if(CanTxDriveGradeTimer)
	{
		CanTxDriveGradeTimer--;
	}
	
	if(CanTxAutonomyTimer)
	{
		CanTxAutonomyTimer--;
	}
	
	if(CanTxMaintenanceTimer)
	{
		CanTxMaintenanceTimer--;
	}
	
	if(CanTxConsumpTimer)
	{
		CanTxConsumpTimer--;
	}
	
	if(CanTxWeightTimer)
	{
		CanTxWeightTimer--;
	}
	
	if(CanTxAxleWeightTimer)
	{
		CanTxAxleWeightTimer--;
	}
	
	if(CanTxTripTimer)
	{
		CanTxTripTimer--;
	}
	if(uds_time)
	{
		if(UdsTimer)
		{
			UdsTimer--;
		}
	}
	
	if(CanTxAutoTimer)
	{
		CanTxAutoTimer--;
	}
	if(CanTxUdsTimer)
	{
		CanTxUdsTimer--;
	}
#if TEST_CAN_FUN==1	
	if(Test_Timer)
	{
		Test_Timer--;
	}
#endif	
	if(CanTxDateTimer)
	{
		CanTxDateTimer--;
	}
	if(CanTxTimeTimer)
	{
		CanTxTimeTimer--;
	}
	if(CanTxUdsCheckTimer)
	{
		CanTxUdsCheckTimer--;
	}	
	if(Positron_VW_50TxTimer)
	{
		Positron_VW_50TxTimer--;
	}
	if(CanNoDataTimer_sleep)
	{
		CanNoDataTimer_sleep--;

		if(CanNoDataTimer_sleep==0)
		{
			F_CAN_RX_DATA=0;
		}
	}
	Positron_VW_Rx_Message();
	
	if(F_CAN_INIT)
	{
		if(sm800_counter>800)
		{			
			sta_800ms=CAN1_1S_Transmit();
			if(sta_800ms)
			{
				sm800_counter=0;
			}				
		}
		if(sm200_counter>200)
		{
			sta_200ms=CAN1_200MS_Transmit();
			if(sta_200ms)
			{
				sm200_counter=0;
			}				
		}
		if(sm70_counter>70)
		{
			sta_70ms=CAN1_70MS_Transmit();
			if(sta_70ms)
			{
				sm70_counter=0;
			}			
		}	
		if(sm50_counter>50)
		{	
			sta_50ms=CAN1_50MS_Transmit();
			if(sta_50ms)
			{
				sm50_counter=0;
			}	
		}
		CAN1_Transmit();		
	}

	
	
	switch(CanMainState)
	{
		case CAN_MAIN_IDLE:
		{
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;
		}
		break;
		
		case CAN_MAIN_CFG:
		{
			CAN1_Init();
			CanMainTimer=T2S_1;
			F_CAN_INIT=1;
			CanMainState=CAN_MAIN_INIT;			
		}
		break;		

		case CAN_MAIN_INIT:
		{
			CAN1_Ext_ClearTxMessage();
			F_CAN_SLEEP=0;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			CanMainState=CAN_MAIN_NORMAL;
			CanNoDataTimer=T5S_1;
			CanNoDataTimer_sleep=T5S_1;
		}
		break;

		case CAN_MAIN_NORMAL:
		{
			if(APP_Status==APP_READY)
			{
				if(defualt==0)
				{
					CanRxInfo.uds_info.byte_4.field.dm1_req=1;
					//CanRxInfo.language_info.byte_0.byte=0x01;
					//CanTxInfo.hu_aut_0.byte_1.field.language=1;
					CanRxInfo.base_info.byte_0.field.f_parking=3;
					CanTxInfo.hu_src_0.byte_6.field.f_pow_mode_res=1;
					CanTxInfo.hu_tel_0.byte_1.field.f_pow_sta=0x7f;
					CanTxInfo.hu_tel_0.byte_2.field.f_fie_str=0x63;
					CanTxInfo.hu_src_0.byte_0.byte=0xd8;
					CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res=1;
					//CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=4;
					CanTxInfo.hu_src_0.byte_2.field.f_fm=1;
					//CanTxInfo.hu_aut_0.byte_0.field.f_con=1;
					CanTxInfo.hu_tel_0.byte_3.field.f_net_sta=1;
					//chg_flag=1;
					defualt=1;
				}
			}
			if(CanTxInfo.hu_src_0.byte_1.field.f_aa_con||CanTxInfo.hu_src_0.byte_1.field.f_cp_con)
			{
				CanTxInfo.hu_src_0.byte_1.field.f_bt_aud_pared=1;
				CanTxInfo.hu_src_0.byte_1.field.f_usb_con=1;
				CanTxInfo.hu_src_0.byte_4.field.f_usb=1;
			}
			
			if(IS_CCFL_EN)
			{
				CanTxInfo.hu_src_0.byte_6.field.f_pow_mode_res=1;
			}
			else 
			{
				CanTxInfo.hu_src_0.byte_6.field.f_pow_mode_res=2;
				CanTxInfo.hu_tel_0.byte_4.field.f_bt_sta=0;
			}
			
//			if(CanRxInfo.speed_info.vehicle_speed<=3)
//			{
//				CanRxInfo.language_info.byte_2.field.f_con_uni=1;
//			}
//			else
//			{
//				CanRxInfo.language_info.byte_2.field.f_con_uni=0;
//			}
			
			if(Seek_flag)
			{
				if(RadioSeekFlag.field.f_scaning==0)
				{
					CanTxInfo.hu_rad_0.byte_4.field.f_rad_seek=0;
					Seek_flag=0;
				}
			}
			
		
			if(CanTxInfo.hu_src_0.byte_2.field.f_fm)
			{
				CanTxInfo.hu_src_0.byte_5.field.f_preset_dig=radiostruct_ram.CurrentPreset+radiostruct_ram.band*6;
			}
			else if(CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw)
			{
				CanTxInfo.hu_src_0.byte_5.field.f_preset_dig=radiostruct_ram.CurrentPreset+(radiostruct_ram.band-3)*6;
			}
			else
			{
				CanTxInfo.hu_src_0.byte_5.field.f_preset_dig=0;
			}
			
			if(CanRxInfo.base_info.f_sel_sta_mem)
			{
				PostMessage(TUNER_MODULE, EVT_TUN_SEL_PS,CanRxInfo.base_info.f_sel_sta_mem);
				CanRxInfo.base_info.f_sel_sta_mem=0;
			}
			if(Uds_defaultTimer==0)
			{
				if(uds_request)
				{
					CanRxInfo.uds_info.byte_3.byte=0;
				}
				if(uds_clear)
				{
					CanRxInfo.uds_info.dtc_h=0;
					CanRxInfo.uds_info.dtc_l=0;
					CanRxInfo.uds_info.dtc_m=0;
					uds_clear=0;
				}
			}
				
			if(set_flag)
			{
				if(t_counter%3000)//((t_counter%3000==0)&&(APP_Status==APP_READY))
				{
//					if(uds_time)
//					{
						if(uds_power_flag==1)
						{
								if(CanRxInfo.uds_error_info.byte_1.field.f_vo_l==1)
								{
									CanRxInfo.uds_error_info.byte_1.field.f_vo_l=0;
								}
								CanRxInfo.uds_error_info.byte_0.field.f_vo_h=1;		
						}
						if(uds_power_flag==2)
						{
							CanRxInfo.uds_error_info.byte_1.field.f_vo_l=1;
								if(CanRxInfo.uds_error_info.byte_0.field.f_vo_h==1)
								{
									CanRxInfo.uds_error_info.byte_0.field.f_vo_h=0;			
								}
						}
						if(uds_power_flag==5)
						{
							CanRxInfo.uds_error_info.byte_0.field.f_vo_h=0;
							CanRxInfo.uds_error_info.byte_1.field.f_vo_l=0;
							uds_time=0;
						}
						
						if(DTC_TUNER_flag==3)
						{
							CanRxInfo.uds_error_info.byte_2.field.f_tune=1;
								CanTxInfo.hu_src_0.byte_2.field.f_fm=0;
								CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;
						}
						else
						{
							CanRxInfo.uds_error_info.byte_2.field.f_tune=0;
						}
						
						if(DTC_DSP_flag==1)
						{
							CanRxInfo.uds_error_info.byte_3.field.f_dsp=1;
						}
						else
						{
							CanRxInfo.uds_error_info.byte_3.field.f_dsp=0;
						}
						
						/*
						switch(uds_power_flag)
						{
							case 2:
							{
								CanRxInfo.uds_error_info.byte_1.field.f_vo_l=1;
								if(CanRxInfo.uds_error_info.byte_0.field.f_vo_h==1)
								{
									CanRxInfo.uds_error_info.byte_0.field.f_vo_h=0;			
								}					
							}
							break;
							
							case 1:
							{
								if(CanRxInfo.uds_error_info.byte_1.field.f_vo_l==1)
								{
									CanRxInfo.uds_error_info.byte_1.field.f_vo_l=0;
								}
								CanRxInfo.uds_error_info.byte_0.field.f_vo_h=1;										
							}
							break;
							
							case 3:
							{
								CanRxInfo.uds_error_info.byte_2.field.f_tune=1;
								CanTxInfo.hu_src_0.byte_2.field.f_fm=0;
								CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw=0;						
							}	
							break;
							
							case 4:
							{
								CanRxInfo.uds_error_info.byte_3.field.f_dsp=1;			
							}
							break;
							
							
							case 5:
							{
								CanRxInfo.uds_error_info.byte_0.field.f_vo_h=0;
								CanRxInfo.uds_error_info.byte_1.field.f_vo_l=0;
								if(uds_bak==6)
								{
									uds_time=0;
									uds_power_flag=0;
									uds_bak=0;
								}
								else
								{
									uds_bak++;
								}									
							}
							break;
							
						}
						*/
//					}
//					else
//					{
//						CanRxInfo.uds_error_info.byte_0.field.f_vo_h=0;
//						CanRxInfo.uds_error_info.byte_1.field.f_vo_l=0;
////						CanRxInfo.uds_error_info.byte_3.field.f_dsp=0;
//						CanRxInfo.uds_error_info.byte_2.field.f_tune=0;
//						UdsTimer=T5S_1;
//					}
				}	
			}
			

#if TEST_CAN_FUN==1	
#endif			
			if((t_counter%40)==0)//50
			{
				freq=radiostruct_ram.freq;
				CanTxCounter=CanTxCounter+1;
				if(APP_OK)
				{
					if(chg_flag)
					{
						chg_counter++;
						
						if(0==(chg_counter%30))//40
						{
							CanTxInfo.hu_aut_0.byte_0.field.f_reset=0;
							CanTxInfo.hu_aut_0.byte_0.field.f_con=0;
							chg_flag=0;							
						}						
					}
				}
				else
				{
					CanTxInfo.hu_aut_0.byte_0.field.f_con=0;
					chg_flag=0;
				}
				
				
				if(0==(t_counter%500))	
				{
					if(APP_OK)
					{
						if(send_time==0)
						{
							if(freq_bak!=freq)
							{
								send_time=1;
								serch_flag=1;
								freq=radiostruct_ram.freq;
								freq_bak=freq;
								freq_num[0]=freq_bak/10000+0x30;
								
								if(freq_num[0]==0x30)
								{
									freq_num[0]=0x20;
								}
								
								freq_num[1]=((freq_bak/1000)%10)+0x30;				
								freq_num[2]=freq_bak%1000/100+0x30;				
								freq_num[5]=0x20;
								freq_num[7]=0x48;//H
								freq_num[8]=0x7a;//z
								
								if(CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw)
								{
									if(freq_num[1]==0x30)
									{
										freq_num[1]=0x20;
									}
									freq_num[3]=freq_bak%100/10+0x30;
									freq_num[4]=(freq_bak%10)+0x30;
									
									freq_num[6]=0x6B;//k 
								}
								else if(CanTxInfo.hu_src_0.byte_2.field.f_fm)
								{
									freq_num[3]=0x2e;
									freq_num[4]=freq_bak%100/10+0x30;
									freq_num[6]=0x4D;//M
								}
							}
							else if(Test_Start_flag)
							{
								seek_time=0;
								CanRxInfo.rad_info.byte_0.field.f_set_radio=0;
							}
						}
					}
				}
			}
				
				if(0==(med_counter%180))//replace
				{
					CanTxInfo.hu_rad_0.byte_2.field.f_rad_fb=0;
					CanTxInfo.hu_rad_0.byte_3.field.f_med_fb=0;
					CanTxInfo.hu_rad_0.byte_5.field.f_med_inf=0;
				
					Positron_VW_PostMessage(CAN_POST_MSG_HU_SRC_00);
				}
				if(0==(fff6_counter%180))
				{
					Positron_VW_PostMessage(CAN_POST_DOOR);
				}
				
				if(UDS_defualt==0)
				{
					if(APP_Status==APP_READY)
					{
						defualt_counter--;
						if(defualt_counter==0)
						{						
							if(z_req_ver<7)
							{
								z_req_ver++;
							}
							else
							{
								z_req_ver=0;
							}							
							switch(z_req_ver)
							{
								
								case 1:
								{
									PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_UDS_FLAG_INO);
									defualt_counter=T1S_1;//T200MS_1;//										
								}
								break;
								
								case 2:
								{
									CanRxInfo.uds_info.byte_4.field.soft_num_req=1;
									defualt_counter=T1S_1;//T200MS_1;//
								}
								break;
								
								case 3:
								{
									CanRxInfo.uds_info.byte_4.field.soft_ver_num_req=1;
									defualt_counter=T1S_1;//T200MS_1;//
								}
								break;
								
								case 4:
								{
									CanRxInfo.uds_info.byte_4.field.hard_num_req=1;
									defualt_counter=T1S_1;//T200MS_1;//
								}
								break;
								
								case 5:
								{
									CanRxInfo.uds_info.byte_4.field.hard_ver_num_req=1;
									defualt_counter=T1S_1;//T200MS_1;//
								}
								break;
								
								case 6:
								{
									CanRxInfo.uds_info.byte_6.field.pto_req=1;
									CanRxInfo.uds_info.byte_3.byte=0;
									CanRxInfo.uds_info.byte_4.byte&=0x0C;
									UDS_defualt=1;
									APP_OK=1;
								}
								break;
							}				
						}
					}
				}
				
				
				
			  
				
				 
				if(0==(r_counter%2500))
				{
					if(send_add==0)
					{
						Positron_VW_WriteMessage(CAN_POST_MSG_HU_TEL_00);
					} 
				}
				if(dtc_counter==5000)
				{
					CanRxInfo.uds_info.byte_0.field.rd_act_pas=1; 
					dtc_counter=0;
				}
				else if(dtc_counter==4000)
				{
					CanRxInfo.uds_info.byte_0.field.rd_not_ocr=1;
				}
			 	else if(dtc_counter==4500)
				{
					CanRxInfo.uds_info.byte_0.field.rd_act=1;
				}
				else if(dtc_counter==3500)
				{
					CanRxInfo.uds_info.byte_0.field.rd_pas=1; 
				}
				
				
				if(EOL_counter==1000)
				{
					CanRxInfo.test_set_info.order=0x25;		
					CanRxInfo.test_set_info.minus=NUM_EOL_VER;//CAN_TEST_RX_BUFFER[Test_Location][2];					
					CanRxInfo.test_set_info.gain=1;
				}
				else if(EOL_counter==2000)
				{
					CanRxInfo.test_set_info.order=0x24;		
					CanRxInfo.test_set_info.minus=NUM_EOL_VER;//CAN_TEST_RX_BUFFER[Test_Location][2];					
					CanRxInfo.test_set_info.gain=1;
					NUM_EOL_VER++;
					if(NUM_EOL_VER>0x0A)
					{
						NUM_EOL_VER=1;
					}
					EOL_counter=0;
				}

				if(0==(r_counter%500))
				{
						 if(send_time)
						 {					
								if((RadioSeekFlag.field.f_scaning==0)&&(RadioSeekFlag.field.f_seeking==0))
								{
									CanTxInfo.hu_rad_0.byte_4.field.f_rad_seek=0;
									Seek_flag=0;
									serch_flag=0;
									tex[1]=0x4D;
									tex[2]=0x20;
									
									if(CanTxInfo.hu_src_0.byte_2.field.f_am_and_mw)//am
									{
										tex[0]=0x41;									
									
										for(i=0;i<14;i++)
										{
											if(i<9)
											{
												tex[i+2]=freq_num[i];
											}
											else
											{
												tex[i+2]=0x20;
											}
										}			
										
										if(navi_sta)
										{
											for(i=0;i<36;i++)
											{
												phone[i]=tex[i];
											}
										}
										
										CAN1_Ext_ClearBufferTxMessage();										
										Positron_VW_WriteMessage(CAN_POST_MSG_HU_TEXT_00);
																													
										for(i=0;i<9;i++)
										{
											freq_num[i]=0;
										}										
										send_time=0;
									}
									else if(CanTxInfo.hu_src_0.byte_2.field.f_fm)
									{
										tex[0]=0x46;
										
										for(i=0;i<14;i++)
										{
											if(i<9)
											{
												tex[i+3]=freq_num[i];
											}
											else
											{
												tex[i+3]=0x20;
											}
										}			
										
										if(navi_sta)
										{
											for(i=0;i<36;i++)
											{
												phone[i]=tex[i];
												
												if(phone[i]==0)
												{
													phone[i]=0x20;
												}
											}
										}										
										Positron_VW_WriteMessage(CAN_POST_MSG_HU_TEXT_00);										
										
										for(i=0;i<9;i++)
										{
											freq_num[i]=0;
										}										
										send_time=0;
									}
								}
							}
					 
				}				
				
			if(0==(r_counter%900))
			{
				if(dm_flag==1)
				{
					for(i=0;i<8;i++)
					{
						CanTxInfo.hu_tex_0.dm[i]=dm[i];
					}					
					Positron_VW_PostMessage(CAN_POST_DM1);
				}
				else if(dm_flag==2)
				{
					Positron_VW_WriteMessage(CAN_POST_MSG_HU_DM1_00);
				}
			}				

			if(CanNoDataTimer)
			{
				CanNoDataTimer--;

				if(CanNoDataTimer==0)
				{
					F_CAN_RX_DATA=0;
					CanMainState=CAN_MAIN_IDLE;
				}
			}

			if(CanTxAutoTestTimer==0)
			{
				switch(CAN_TEST_RX_BUFFER[Test_Location][0])
				{
					case 0x12:
					{
						if(Test_Power_flag)
						{
							switch(CAN_TEST_RX_BUFFER[Test_Location][1])
							{
								case 1://hardware reset
								{
									PostMessage(MMI_MODULE,UICC_SYS_RESET,0);
								}
								break;
								
								case 3://factory reset
								{									
									PostMessage(MMI_MODULE,UICC_SYS_RESET,0);
								}
								break;
								
								case 5:
								{
									if(IS_CCFL_EN)
									{								
										PostMessage(DSP_MODULE,EVT_DSP_AUDIO_MUTE,1);
										PostMessage(MMI_MODULE,UICC_FICTITIOUS_POWER_OFF,0);
										KeyPwmConfig(KEY_LIGHT_CLOSED);
									}
									else 
									{
										KeyLedAutoTest=100;
										KeyPwmConfig(KEY_LIGHT_AUTO_TEST);										
										PostMessage(MMI_MODULE,UICC_FICTITIOUS_POWER_OFF,1);
										PostMessage(DSP_MODULE,EVT_DSP_AUDIO_MUTE,0);
									}
								}
								break; 	
								
							}					
							Test_Power_flag=0;
						}
					}
					break;
					
					case 0x41:
					{
						if(Test_Sta_flag)
						{
							switch(CAN_TEST_RX_BUFFER[Test_Location][2])
							{
								case 1:
								{
									if(IS_CCFL_EN)
									{
										CanRxInfo.test_set_info.order=0x2f;
										CanRxInfo.test_set_info.gain=1;											
										PostMessage(DSP_MODULE,EVT_DSP_AUDIO_MUTE,1);
										PostMessage(MMI_MODULE,UICC_FICTITIOUS_POWER_OFF,0);
										KeyPwmConfig(KEY_LIGHT_CLOSED);
										Test_Sta_flag=0;
									}
									else 
									{
										KeyLedAutoTest=100;
										KeyPwmConfig(KEY_LIGHT_AUTO_TEST);
										CanRxInfo.test_set_info.order=0x2f;
										CanRxInfo.test_set_info.gain=0;		
										PostMessage(MMI_MODULE,UICC_FICTITIOUS_POWER_OFF,1);
										PostMessage(DSP_MODULE,EVT_DSP_AUDIO_MUTE,0);
										Test_Sta_flag=0;
									}
								}
								break;
								
								case 2://voice control
								{
									if(CanRxInfo.tel_info.byte_0.field.f_tel_up==0)
									{
										CanRxInfo.tel_info.byte_0.field.f_tel_up=1;
										CanRxInfo.tel_info.byte_0.field.f_tel_cmd=0x0F;
										CanTxAutoTestTimer=CAN_TEST_RX_BUFFER[Test_Location][3];
									}
									else
									{
										CanRxInfo.tel_info.byte_0.field.f_tel_up=0;
										CanRxInfo.tel_info.byte_0.field.f_tel_cmd=0x0F;
										Test_Sta_flag=0;
									}
								}
								break;
								
								case 3: //Volume +
								{
									if(CanRxInfo.vol_info.byte_0.field.f_set_vol_sta==0)
									{
										CanRxInfo.vol_info.byte_0.field.f_set_vol=1;
										CanRxInfo.vol_info.byte_0.field.f_set_vol_sta=1;
										CanTxAutoTestTimer=T300MS_1;
									}
									else
									{
										CanRxInfo.vol_info.byte_0.field.f_set_vol=0;
										CanRxInfo.vol_info.byte_0.field.f_set_vol_sta=0;
										Test_Sta_flag=0;
									}
								}
								break;
								
								case 4://Volume -
								{									
									if(CanRxInfo.vol_info.byte_0.field.f_set_vol_sta==0)
									{
										CanRxInfo.vol_info.byte_0.field.f_set_vol=2;
										CanRxInfo.vol_info.byte_0.field.f_set_vol_sta=1;
										CanTxAutoTestTimer=T300MS_1;
									}
									else
									{
										CanRxInfo.vol_info.byte_0.field.f_set_vol=0;
										CanRxInfo.vol_info.byte_0.field.f_set_vol_sta=0;
										Test_Sta_flag=0;
									}
								}
								break;							
								
							}
						}
					}
					break;
									
				}
			}			
					
			if((AccPinStatus==0||BSG_off_flag==0)&&(flag_time1_2==0))
			{
				CanMainState=CAN_MAIN_GO_TO_SLEEP;
				CanMainTimer=T2S_1;
				CanRxInfo.uds_error_info_bak.byte_1.byte=0x1;
				CanRxInfo.uds_error_info_bak.byte_0.byte=0x1;
			}
			else if(APP_READY==APP_Status)
			{	
				if(0==strcmp_equal(&CanRxInfo.base_info_bak.byte_0.byte,&CanRxInfo.base_info.byte_0.byte,sizeof(CAN_BASE_INFO)))
				{					
					CanRxInfo.base_info_bak.byte_0.byte=CanRxInfo.base_info.byte_0.byte;
					CanRxInfo.base_info_bak.f_sel_sta_mem=CanRxInfo.base_info.f_sel_sta_mem;
					CanRxInfo.base_info_bak.f_ill=CanRxInfo.base_info.f_ill;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_BASE_INO);
					CanTxBaseTimer=T200MS_1;
				}
				if(0==strcmp_equal(&CanRxInfo.pto_info_bak.byte_0.byte,&CanRxInfo.pto_info.byte_0.byte,sizeof(CAN_PTO_INFO)))
				{					
					CanRxInfo.pto_info_bak.byte_0.byte=CanRxInfo.pto_info.byte_0.byte;
					CanRxInfo.pto_info_bak.byte_1.byte=CanRxInfo.pto_info.byte_1.byte;
					CanRxInfo.pto_info_bak.byte_2.byte=CanRxInfo.pto_info.byte_2.byte;
					CanRxInfo.pto_info_bak.byte_3.byte=CanRxInfo.pto_info.byte_3.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_PTO_INO);
					//CanTxPtoTimer=T200MS_1;
				}
				if(0==strcmp_equal(&CanRxInfo.energy_info_bak.byte_0.byte,&CanRxInfo.energy_info.byte_0.byte,sizeof(CAN_ENERGY_INFO)))
				{					
					CanRxInfo.energy_info_bak.byte_0.byte=CanRxInfo.energy_info.byte_0.byte;
					CanRxInfo.energy_info_bak.byte_1.byte=CanRxInfo.energy_info.byte_1.byte;
					CanRxInfo.energy_info_bak.byte_2.byte=CanRxInfo.energy_info.byte_2.byte;
					CanRxInfo.energy_info_bak.byte_3.byte=CanRxInfo.energy_info.byte_3.byte;
					CanRxInfo.energy_info_bak.byte_4.byte=CanRxInfo.energy_info.byte_4.byte;
					CanRxInfo.energy_info_bak.byte_5.byte=CanRxInfo.energy_info.byte_5.byte;
					CanRxInfo.energy_info_bak.byte_6.byte=CanRxInfo.energy_info.byte_6.byte;
					CanRxInfo.energy_info_bak.byte_7.byte=CanRxInfo.energy_info.byte_7.byte;
					CanRxInfo.energy_info_bak.byte_8.byte=CanRxInfo.energy_info.byte_8.byte;
					CanRxInfo.energy_info_bak.byte_9.byte=CanRxInfo.energy_info.byte_9.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_ENERGY_INO);
					//CanTxEnergyTimer=T200MS_1;
				}
				if(0==strcmp_equal(&CanRxInfo.charge_info_bak.byte_0.byte,&CanRxInfo.charge_info.byte_0.byte,sizeof(CAN_CHARGE_INFO)))
				{					
					CanRxInfo.charge_info_bak.byte_0.byte=CanRxInfo.charge_info.byte_0.byte;
					CanRxInfo.charge_info_bak.byte_1.byte=CanRxInfo.charge_info.byte_1.byte;
					CanRxInfo.charge_info_bak.byte_2.byte=CanRxInfo.charge_info.byte_2.byte;
					CanRxInfo.charge_info_bak.byte_3.byte=CanRxInfo.charge_info.byte_3.byte;
					CanRxInfo.charge_info_bak.byte_4.byte=CanRxInfo.charge_info.byte_4.byte;
					CanRxInfo.charge_info_bak.byte_5.byte=CanRxInfo.charge_info.byte_5.byte;
					CanRxInfo.charge_info_bak.byte_6.byte=CanRxInfo.charge_info.byte_6.byte;
					CanRxInfo.charge_info_bak.byte_7.byte=CanRxInfo.charge_info.byte_7.byte;
					CanRxInfo.charge_info_bak.byte_8.byte=CanRxInfo.charge_info.byte_8.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO, Positron_VW_RX_CHARGE_INO);
					//CanTxChargeTimer=T200MS_1;
				}
				
				if(0==strcmp_equal(&CanRxInfo.vehicle_info_bak.byte_0.byte,&CanRxInfo.vehicle_info.byte_0.byte,sizeof(CAN_VEHICLE_INFO)))
				{
					CanRxInfo.vehicle_info_bak.byte_0.byte=CanRxInfo.vehicle_info.byte_0.byte;					
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_BASE_INO);
					CanTxBaseTimer=T200MS_1;					
				}				
				if(0==strcmp_equal(&CanRxInfo.test_set_info_bak.order,&CanRxInfo.test_set_info.order,sizeof(CAN_TEST_SETTING_INFO)))
				{					
					CanRxInfo.test_set_info_bak.order=CanRxInfo.test_set_info.order;
					CanRxInfo.test_set_info_bak.gain=CanRxInfo.test_set_info.gain;
					CanRxInfo.test_set_info_bak.minus=CanRxInfo.test_set_info.minus;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEST_INO);
					CanTxAutoTimer=T100MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.med_info_bak.byte_0.byte,&CanRxInfo.med_info.byte_0.byte,sizeof(CAN_MED_INFO)))
				{
					CanRxInfo.med_info_bak.byte_0.byte=CanRxInfo.med_info.byte_0.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_MED_INO);
					
					if(Test_Start_flag)
					{
						CanTxMedTimer=T500MS_1;
					}
					else
					{
						CanTxMedTimer=T300MS_1;
					}				
					if(Test_Sta_flag)
					{
						CanTxMedTimer=T500MS_1;
					}
					else
					{
						CanTxMedTimer=T300MS_1;
					}				
				}				
				if(0==strcmp_equal(&CanRxInfo.language_info_bak.byte_0.byte,&CanRxInfo.language_info.byte_0.byte,sizeof(CAN_LANGUAGE_INFO)))
				{
					CanRxInfo.language_info_bak.byte_0.byte=CanRxInfo.language_info.byte_0.byte;
					CanRxInfo.language_info_bak.byte_1.byte=CanRxInfo.language_info.byte_1.byte;
					CanRxInfo.language_info_bak.byte_2.byte=CanRxInfo.language_info.byte_2.byte;					
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_LANGUAGE_INO);
					CanTxLanguageTimer=T200MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.tel_info_bak.byte_0.byte,&CanRxInfo.tel_info.byte_0.byte,sizeof(CAN_TEL_INFO)))
				{
					CanRxInfo.tel_info_bak.byte_0.byte=CanRxInfo.tel_info.byte_0.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEL_INO);
					if(Test_Start_flag)
					{
						CanTxTelTimer=T500MS_1;
					}
					else
					{
						CanTxTelTimer=T100MS_1;
					}					
				}					
				if(0==strcmp_equal(&CanRxInfo.vol_info_bak.byte_0.byte,&CanRxInfo.vol_info.byte_0.byte,sizeof(CAN_VOL_INFO)))
				{
					CanRxInfo.vol_info_bak.byte_0.byte=CanRxInfo.vol_info.byte_0.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_VOL_INO);
					CanTxVolTimer=T100MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.src_info_bak.byte_0.byte,&CanRxInfo.src_info.byte_0.byte,sizeof(CAN_SRC_INFO)))
				{
					CanRxInfo.src_info_bak.byte_0.byte=CanRxInfo.src_info.byte_0.byte;
#if AA_CP_TEST==1
#else					
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_SRC_INO);
#endif			
					CanTxSrcTimer=T500MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.rad_info_bak.byte_0.byte,&CanRxInfo.rad_info.byte_0.byte,sizeof(CAN_RAD_INFO)))
				{
					CanRxInfo.rad_info_bak.byte_0.byte=CanRxInfo.rad_info.byte_0.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_RAD_INO);
					CanTxRadTimer=T200MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.camera_info_bak.r_inten,&CanRxInfo.camera_info.r_inten,sizeof(CAN_CAMERA_INFO)))
				{
					CanRxBuffer_bak.camera_info.l_exten=0;
					CanRxBuffer_bak.camera_info.l_inten=0;
					CanRxBuffer_bak.camera_info.r_exten=0;
					CanRxBuffer_bak.camera_info.r_inten=0;

					CanRxInfo.camera_info_bak.r_inten=CanRxInfo.camera_info.r_inten;
					CanRxInfo.camera_info_bak.l_inten=CanRxInfo.camera_info.l_inten;
					CanRxInfo.camera_info_bak.r_exten=CanRxInfo.camera_info.r_exten;
					CanRxInfo.camera_info_bak.l_exten=CanRxInfo.camera_info.l_exten;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_CAMERA_INO);
					CanTxCameraTimer=T50MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.uds_info_bak.length,&CanRxInfo.uds_info.length,sizeof(CAN_UDS_INFO)))
				{
					CanRxInfo.uds_info_bak.length=CanRxInfo.uds_info.length;
					
					for(i=0;i<8;i++)
					{
						CanRxInfo.uds_info_bak.d[i]=CanRxInfo.uds_info.d[i];
					}					
					CanRxInfo.uds_info_bak.mode_h=CanRxInfo.uds_info.mode_h;
					CanRxInfo.uds_info_bak.mode_l=CanRxInfo.uds_info.mode_l;
					CanRxInfo.uds_info_bak.sid=CanRxInfo.uds_info.sid;
					CanRxInfo.uds_info_bak.dtc_h=CanRxInfo.uds_info.dtc_h;
					CanRxInfo.uds_info_bak.dtc_l=CanRxInfo.uds_info.dtc_l;
					CanRxInfo.uds_info_bak.dtc_m=CanRxInfo.uds_info.dtc_m;
					CanRxInfo.uds_info_bak.byte_0=CanRxInfo.uds_info.byte_0;
					CanRxInfo.uds_info_bak.byte_1=CanRxInfo.uds_info.byte_1;
					CanRxInfo.uds_info_bak.byte_2=CanRxInfo.uds_info.byte_2;
					CanRxInfo.uds_info_bak.byte_3=CanRxInfo.uds_info.byte_3;
					CanRxInfo.uds_info_bak.byte_4=CanRxInfo.uds_info.byte_4;
					CanRxInfo.uds_info_bak.byte_5=CanRxInfo.uds_info.byte_5;
					CanRxInfo.uds_info_bak.byte_6=CanRxInfo.uds_info.byte_6;
					
					if(Uds_set)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_INFORMATION_UDS_INO);
						Uds_set = 0;
					}
					else
					{
						if(U_BACK==0)
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_SETTING_UDS_INO);
						}
						else
						{
							U_BACK=0;
						}						
					}					
					CanTxUdsTimer=T200MS_1;
				}	
				else
				{
					Uds_set = 0;
				}
				if(0==strcmp_equal(&CanRxInfo.uds_error_info_bak.byte_0.byte,&CanRxInfo.uds_error_info.byte_0.byte,sizeof(CAN_UDS_ERROR_INFO)))
				{				
					CanRxInfo.uds_error_info_bak.byte_0.byte=CanRxInfo.uds_error_info.byte_0.byte;
					CanRxInfo.uds_error_info_bak.byte_1.byte=CanRxInfo.uds_error_info.byte_1.byte;
					CanRxInfo.uds_error_info_bak.byte_2.byte=CanRxInfo.uds_error_info.byte_2.byte;
					CanRxInfo.uds_error_info_bak.byte_3.byte=CanRxInfo.uds_error_info.byte_3.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_CHECK_UDS_INO);	
					UdsTimer=T5S_1;
				}

				if(0==strcmp_equal(&CanRxInfo.trip_time_info_bak.dri_time_hour_l,&CanRxInfo.trip_time_info.dri_time_hour_l,sizeof(CAN_TRIP_TIME_INFO)))
				{				
					CanRxInfo.trip_time_info_bak.dri_time_hour_l=CanRxInfo.trip_time_info.dri_time_hour_l;
					CanRxInfo.trip_time_info_bak.tra_time_hour_l=CanRxInfo.trip_time_info.tra_time_hour_l;
					CanRxInfo.trip_time_info_bak.byte_0.byte=CanRxInfo.trip_time_info.byte_0.byte;
					CanRxInfo.trip_time_info_bak.byte_1.byte=CanRxInfo.trip_time_info.byte_1.byte;
					CanRxInfo.trip_time_info_bak.dri_time_min=CanRxInfo.trip_time_info.dri_time_min;
					CanRxInfo.trip_time_info_bak.tra_time_min=CanRxInfo.trip_time_info.tra_time_min;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TRIP_TIME_INO);
					CanTxTripTimeTimer=T1S_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.auto_info_bak.auto_dt,&CanRxInfo.auto_info.auto_dt,sizeof(CAN_AUTO_INFO)))
				{				
					CanRxInfo.auto_info_bak.auto_dt=CanRxInfo.auto_info.auto_dt;
					CanRxInfo.auto_info_bak.ad_blue_auto_dt=CanRxInfo.auto_info.ad_blue_auto_dt;
					CanRxInfo.auto_info_bak.byte_0.byte=CanRxInfo.auto_info.byte_0.byte;
					CanRxInfo.auto_info_bak.byte_1.byte=CanRxInfo.auto_info.byte_1.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_AUTONOMY_INO);
					CanTxAutonomyTimer=T1S_1;
				}					
				if(0==strcmp_equal(&CanRxInfo.remain_info_bak.main_remain_dt_l,&CanRxInfo.remain_info.main_remain_dt_l,sizeof(CAN_REMAIN_INFO)))
				{				
					CanRxInfo.remain_info_bak.main_remain_dt_l=CanRxInfo.remain_info.main_remain_dt_l;
					CanRxInfo.remain_info_bak.main_remain_dt_h=CanRxInfo.remain_info.main_remain_dt_h;
					CanRxInfo.remain_info_bak.byte_0.byte=CanRxInfo.remain_info.byte_0.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_MAIN_INO);
					CanTxMaintenanceTimer=T50MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.consump_info_bak.instant_con,&CanRxInfo.consump_info.instant_con,sizeof(CAN_CONSUMP_INFO)))
				{				
					CanRxInfo.consump_info_bak.instant_con=CanRxInfo.consump_info.instant_con;
					CanRxInfo.consump_info_bak.avg_con=CanRxInfo.consump_info.avg_con;
					CanRxInfo.consump_info_bak.fuel_liter=CanRxInfo.consump_info.fuel_liter;
					CanRxInfo.consump_info_bak.byte_0.byte=CanRxInfo.consump_info.byte_0.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_CONSUMP_INO);
					CanTxConsumpTimer=T100MS_1;
				}		
				if(0==strcmp_equal(&CanRxInfo.axleweight_info_bak.axleweight1,&CanRxInfo.axleweight_info.axleweight1,sizeof(CAN_AXLEWEIGHT_INFO)))
				{				
					CanRxInfo.axleweight_info_bak.axleweight1=CanRxInfo.axleweight_info.axleweight1;
					CanRxInfo.axleweight_info_bak.axleweight2=CanRxInfo.axleweight_info.axleweight2;
					CanRxInfo.axleweight_info_bak.axleweight3=CanRxInfo.axleweight_info.axleweight3;
					CanRxInfo.axleweight_info_bak.axleweight4=CanRxInfo.axleweight_info.axleweight4;
					//CanRxInfo.axleweight_info_bak.byte_0.byte=CanRxInfo.axleweight_info.byte_0.byte;
					CanRxInfo.axleweight_info_bak.byte_1.byte=CanRxInfo.axleweight_info.byte_1.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_AXLEWEIGHT_INO);
					CanTxAxleWeightTimer=T50MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.weight_info_bak.level_adj,&CanRxInfo.weight_info.level_adj,sizeof(CAN_WEIGHT_INFO)))
				{				
					CanRxInfo.weight_info_bak.totalweight=CanRxInfo.weight_info.totalweight;
					CanRxInfo.weight_info_bak.byte_0.byte=CanRxInfo.weight_info.byte_0.byte;
					CanRxInfo.weight_info_bak.byte_1.byte=CanRxInfo.weight_info.byte_1.byte;						
					CanRxInfo.weight_info_bak.level_adj=CanRxInfo.weight_info.level_adj;						
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_WEIGHT_INO);
					CanTxWeightTimer=T600MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.speed_info_bak.vehicle_speed,&CanRxInfo.speed_info.vehicle_speed,sizeof(CAN_SPEED_INFO)))
				{				
					CanRxInfo.speed_info_bak.vehicle_speed=CanRxInfo.speed_info.vehicle_speed;
					CanRxInfo.speed_info_bak.trip_avg_speed=CanRxInfo.speed_info.trip_avg_speed;	
					CanRxInfo.speed_info_bak.byte_0.byte=CanRxInfo.speed_info.byte_0.byte;				
					CanRxInfo.speed_info_bak.trip_meter_1=CanRxInfo.speed_info.trip_meter_1;		
					CanRxInfo.speed_info_bak.trip_meter_2=CanRxInfo.speed_info.trip_meter_2;	
					CanRxInfo.speed_info_bak.trip_meter_3=CanRxInfo.speed_info.trip_meter_3;	
					CanRxInfo.speed_info_bak.trip_meter_4=CanRxInfo.speed_info.trip_meter_4;						
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TRIP_INO);
					CanTxTripTimer=T1S_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.grad_info_bak.drive_avg_grad_bar,&CanRxInfo.grad_info.drive_avg_grad_bar,sizeof(CAN_GRAD_INFO)))
				{				
					CanRxInfo.grad_info_bak.drive_avg_grad_bar=CanRxInfo.grad_info.drive_avg_grad_bar;
					CanRxInfo.grad_info_bak.drive_grad_brak=CanRxInfo.grad_info.drive_grad_brak;
					CanRxInfo.grad_info_bak.drive_grad_gear=CanRxInfo.grad_info.drive_grad_gear;
					CanRxInfo.grad_info_bak.drive_grad_acc=CanRxInfo.grad_info.drive_grad_acc;
					CanRxInfo.grad_info_bak.byte_0.byte=CanRxInfo.grad_info.byte_0.byte;
					CanRxInfo.grad_info_bak.byte_1.byte=CanRxInfo.grad_info.byte_1.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_DRV_GRADE_INO);
					CanTxDriveGradeTimer=T100MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.time_info_bak.hours,&CanRxInfo.time_info.hours,sizeof(CAN_TIME_INFO)))
				{				
					CanRxInfo.time_info_bak.hours=CanRxInfo.time_info.hours;
					CanRxInfo.time_info_bak.minutes=CanRxInfo.time_info.minutes;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TIME_INO);
					CanTxTimeTimer=T100MS_1;
				}				
				if(0==strcmp_equal(&CanRxInfo.date_info_bak.years,&CanRxInfo.date_info.years,sizeof(CAN_DATE_INFO)))
				{				
					CanRxInfo.date_info_bak.years=CanRxInfo.date_info.years;
					CanRxInfo.date_info_bak.months=CanRxInfo.date_info.months;
					CanRxInfo.date_info_bak.days=CanRxInfo.date_info.days;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_DATE_INO);
					CanTxDateTimer=T100MS_1;
				}
				if(0==strcmp_equal(&CanRxInfo.date_info_bak.years,&CanRxInfo.date_info.years,sizeof(CAN_DATE_INFO)))
				{				
					CanRxInfo.date_info_bak.years=CanRxInfo.date_info.years;
					CanRxInfo.date_info_bak.months=CanRxInfo.date_info.months;
					CanRxInfo.date_info_bak.days=CanRxInfo.date_info.days;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_DATE_INO);
					CanTxDateTimer=T100MS_1;
				}
				if(0==strcmp_equal(&CanRxInfo.ich4_info_bak.DateYearDt,&CanRxInfo.ich4_info.DateYearDt,sizeof(CAN_ICH4_INFO)))
				{
					CanRxInfo.ich4_info_bak.DateYearDt=CanRxInfo.ich4_info.DateYearDt;
					CanRxInfo.ich4_info_bak.byte_0.byte=CanRxInfo.ich4_info.byte_0.byte;
					CanRxInfo.ich4_info_bak.byte_1.byte=CanRxInfo.ich4_info.byte_1.byte;
					CanRxInfo.ich4_info_bak.byte_2.byte=CanRxInfo.ich4_info.byte_2.byte;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TIMES_INO);
					CanTxDateTimer=T500MS_1;
				}
				if(USB_MODE_bak!=USB_MODE)
				{
					USB_MODE_bak=USB_MODE;
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_USB_MODE);
				}
//				if((PKS_OK==0)&&(PKSTxDateTimer==0))
//				{
//					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_PKS_INO);
//					PKSTxDateTimer=T200MS_1;
//				}
			}
			else
			{
				CanRxInfo.camera_info_bak.l_exten=0;
				CanRxInfo.camera_info_bak.l_inten=0;
				CanRxInfo.camera_info_bak.r_exten=0;
				CanRxInfo.camera_info_bak.r_inten=0;
			}
		}
		break;
		
		case CAN_MAIN_GO_TO_SLEEP:
		{
			if((AccPinStatus&&BSG_off_flag)||(flag_time1_2))
			{
				CanMainState=CAN_MAIN_NORMAL;
			}
			else if(CanMainTimer==0&&F_CAN_RX_DATA==0)
			{				
				CAN_IC_STANDBY_ON;
				F_CAN_SLEEP=1;
				CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res=0;
	#if TEST_CAN_FUN==1
	#else 
				CanMainState=CAN_MAIN_SLEEP_CFG;
	#endif
				CanMainTimer=T1S5_1;
			}
		}
		break;
		
		case CAN_MAIN_SLEEP_CFG:
		{
			if(CanMainTimer)
			{
				break;
			}			
			CAN1_Ext_ClearRxMessage();
			CAN_IC_DISABLE;
			F_CAN_SLEEP=1;
			CanMainState=CAN_MAIN_SLEEP;
		}
		break;
		
		case CAN_MAIN_SLEEP:
		{
			if(CanMainTimer)
			{
				break;
			}
			if(F_CAN_SLEEP==0
				||F_CAN_INTERRUPT)
			{
				CAN_IC_STANDBY_OFF;
				F_CAN_SLEEP=0;
				freq_bak=0;
				CanMainState=CAN_MAIN_INIT;
#if CAN_DEBUG_FUN==1
				printf("CAN_MAIN_SLEEP->CAN_MAIN_INIT reason:can_data\r\n");
				printf("CAN_MAIN_SLEEP\r\n");
#endif
			}
		}
		break;

		default:
			break;
	}
}
void Positron_VW_ManySendmessage(void)
{
	u8 j;
	u8 seed_flag;
	if(flow_flag)//多包发送剩余包发送判定
		{
		if(DTC_FLAG)//DTC only
		{
			many_num=DTC_BUFFER[DTC_LOCATION_SEND][0];
			sta=1;
		}
		if(flag_f192||flag_f194||flag_f195)
		{
			many_num=VER_BUFFER[VER_LOCATION_SEND][0];
		}
		if(many_num>1)
		{
			box_size=block_size;
			while(box_size)
			{
				if(CanTxManyTimer)
				{
					CanTxManyTimer--;
				}
				
				if(CanTxManyTimer==0)
				{
					CanTxInfo.hu_uds_0.d[0]=0x20+send_counter;
					for(i=0;i<7;i++)
					{	
						switch(sta)
						{
							case 1:
							{
								CanTxInfo.hu_uds_0.d[i+1]=CanTxInfo.hu_tex_0.dtc[many_counter];
							}
							break;
							
							case 2:
							{
								CanTxInfo.hu_uds_0.d[i+1]=CanTxInfo.hu_tex_0.num[many_counter];
							}
							break;
							
							case 3:
							{
								seed_flag=1;
								seed[4]=((Positron_VW_TxTimer&0x0ff0)>>4);
								seed[5]=CanTxGearTimer;
								seed[6]=CanTxSrcTimer;
								seed[7]=Positron_VW_TxTimer;						
								for(j=0;j<4;j++)
								{
									CanTxInfo.hu_uds_0.d[j+1]=seed[j+4];
									
									if(j<3)
									{
										CanTxInfo.hu_uds_0.d[j+5]=0;
									}
								}								 
							}
							break;
							
						}
						
						if(many_counter<0x6E)
						{
							many_counter++;
						}
						else 
						{
							many_counter=0;
						}
					}
					if(seed_flag==1)
					{
						memset(ch_key, 0, sizeof(ch_key));
						encipher(seed, ch_key);
						
						for(i=0;i<8;i++)
						{
							seed[i]=0;
						}						
						seed_flag=0;
					}
					
					Positron_VW_PostMessage(CAN_POST_UDS);
					send_counter++;
					
					if(send_counter<=(many_num-1))
					{
						box_size--;
						CanTxManyTimer=st_min+0x10;		
					}
					else
					{
						box_size=0;
						st_min=0;
						many_num=1;
						send_counter=1;
						many_counter=0;						
						sta=0;					
						for(i=0;i<data_length;i++)
						{
							CanTxInfo.hu_tex_0.dtc[i]=0;
							CanTxInfo.hu_tex_0.num[i]=0;
						}					
						for(i=0;i<50;i++)
						{
							CanTxInfo.hu_tex_0.dtc[i]=0;
						}						
						data_length=0;
					}	
				}		
			}
			flow_flag=0;
		}		
	}
	else 
	{
		if(many_num!=0)
		{
			many_counter=0;
			CanTxInfo.hu_uds_0.d[0]=0x10;
			CanTxInfo.hu_uds_0.d[1]=data_length;			
			if(sta==3)
			{
				CanTxInfo.hu_uds_0.d[1]=0x0A;
			}		
			CanTxInfo.hu_uds_0.d[2]=CanRxInfo.uds_info.sid+0x40;
			
			for(i=0;i<2;i++)
			{
				CanTxInfo.hu_uds_0.d[i+3]=CanRxInfo.uds_info.d[i];
			}
			
			for(i=0;i<3;i++)
			{
				switch(sta)
				{
					case 1:
					{
						CanTxInfo.hu_uds_0.d[i+5]=CanTxInfo.hu_tex_0.dtc[many_counter];
					}
					break;
							
					case 2:
					{
						CanTxInfo.hu_uds_0.d[i+5]=CanTxInfo.hu_tex_0.num[many_counter];
					}
					break;
					
					case 3:
					{
						seed[0]=((System_Time_Counter&0x0ff0)>>4);
						seed[1]=(System_Time_Counter&0xFF);
						seed[2]=CanTxVolTimer;
						seed[3]=CanTxGearTimer;
						
						for(i=0;i<4;i++)
						{
							CanTxInfo.hu_uds_0.d[i+4]=seed[i];
						}
					}
					break;
				}
				
				many_counter++;
			}		
			Positron_VW_PostMessage(CAN_POST_UDS);
			Positron_VW_Rx_Message();
		}
	}
	
}

void Positron_VW_UdsPro(void)
{
	if(Check_mode)
	{	
		CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length;
		CanTxInfo.hu_uds_0.d[1]=CanRxInfo.uds_info.sid+0x40;
		
		for(i=0;i<6;i++)
		{
			CanTxInfo.hu_uds_0.d[i+2]=CanRxInfo.uds_info.d[i];
		}	
		switch(CanRxInfo.uds_info.sid)
		{
			case 0x10://Diagnostic Session Control
			{
				if(AccPinStatus)
				{
					if(CanRxInfo.uds_info.length==2)
					{		
						CanTxInfo.hu_uds_0.d[0]=6;				
						CanTxInfo.hu_uds_0.d[3]=0;
						CanTxInfo.hu_uds_0.d[4]=0x32;
						CanTxInfo.hu_uds_0.d[5]=0x01;
						CanTxInfo.hu_uds_0.d[6]=0xF4;
						
						switch(CanRxInfo.uds_info.d[0])
						{
							case 1://default Session 
							{
								check_flag=1;	
#if DQA_UDS_TEST == 0
								ser_ag=0;						
#endif
							}
							break;
							
							case 2://ECU Programming Session
							{	
								CanTxInfo.hu_uds_0.d[5]=0x0B;
								CanTxInfo.hu_uds_0.d[6]=0xB8;
								check_flag=2;
#if DQA_UDS_TEST == 0
								ser_ag=0;						
#endif
							}
							break;
							
							case 3:// extendedDiagnostic Session 
							{
								check_flag=3;
#if DQA_UDS_TEST == 0
								ser_ag=0;						
#endif
							}
							break;
							
							case 0x40://vehicle Manufacturer End Of Line Session
							{
								check_flag=4;
#if DQA_UDS_TEST == 0
								ser_ag=0;						
#endif
							}
							break;

							default:
							{
								CanTxInfo.hu_uds_0.d[0]=3;
								CanTxInfo.hu_uds_0.d[1]=0x7F;
								CanTxInfo.hu_uds_0.d[2]=0x10;
								CanTxInfo.hu_uds_0.d[3]=0x12;
#if DQA_UDS_TEST == 0
								ser_ag=0;						
#endif
								
								for(i=4;i<8;i++)
								{
									CanTxInfo.hu_uds_0.d[i]=0;
								}
							}
							break;	
							
						}								
						Positron_VW_PostMessage(CAN_POST_UDS);
						
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}	
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x10;
						CanTxInfo.hu_uds_0.d[3]=0x13;
						
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}								
						Positron_VW_PostMessage(CAN_POST_UDS);
					}
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x10;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}						
					Positron_VW_PostMessage(CAN_POST_UDS);
					Check_mode=0;
				}
			}
			break;
				
			case 0x11: //ECU Reset
			{
				if(AccPinStatus)
				{
					if(CanRxInfo.uds_info.length==2)
					{
						if(check_flag>1)
						{
								switch(CanRxInfo.uds_info.d[0])
								{
									case 1://ecuHardReset  Resets the whole software
									{										
										reset_can_flag=1;
										Positron_VW_PostMessage(CAN_POST_UDS);
										Check_mode=0;
										PostMessage(MMI_MODULE,UICC_SYS_RESET,0);											
									}
									break;
									
									case 2://keyOffOnReset
									{																
										check_flag=1;		
										seed_time=0;									
									}
									break;

									default:
									{
										CanTxInfo.hu_uds_0.d[0]=3;
										CanTxInfo.hu_uds_0.d[1]=0x7F;
										CanTxInfo.hu_uds_0.d[2]=0x11;
										CanTxInfo.hu_uds_0.d[3]=0x12;
										
										for(i=4;i<8;i++)
										{
											CanTxInfo.hu_uds_0.d[i]=0;
										}								
									}
									break;
						
								}									
								Positron_VW_PostMessage(CAN_POST_UDS);
								Check_mode=0;
						}
						else
						{
							CanTxInfo.hu_uds_0.d[0]=3;
							CanTxInfo.hu_uds_0.d[1]=0x7F;
							CanTxInfo.hu_uds_0.d[2]=0x11;
							CanTxInfo.hu_uds_0.d[3]=0x22;
							
							for(i=4;i<8;i++)
							{
								CanTxInfo.hu_uds_0.d[i]=0;
							}								
							Positron_VW_PostMessage(CAN_POST_UDS);
							Check_mode=0;									
						}					
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x11;
						CanTxInfo.hu_uds_0.d[3]=0x13;
						
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}							
						Positron_VW_PostMessage(CAN_POST_UDS);
						Check_mode=0;
					}
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x11;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}						
					Positron_VW_PostMessage(CAN_POST_UDS);
					Check_mode=0;
				}	
			}
			break;
				
			case 0x19://Read Failure Active or Inactive (Read DTC Information)
			{	
				u8 l=0;
				if(AccPinStatus)
				{
					if(CanRxInfo.uds_info.length==3)
					{
						CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length+3;
						CanTxInfo.hu_uds_0.d[5]=0;
					
						if(check_flag!=2)
						{
							switch(CanRxInfo.uds_info.d[0])
							{
								case 1:// reportNumberOfDTCByStatusMask
								{
									CanTxInfo.hu_uds_0.d[2]=CanRxInfo.uds_info.d[0];
									CanTxInfo.hu_uds_0.d[4]=1;
									CanTxInfo.hu_uds_0.d[5]=0;
									
									switch(CanRxInfo.uds_info.d[1])
									{
										case 8://Read the number of passive DTCs  查询Active和Passive态//Actived but dead
										{
											CanRxInfo.uds_info.byte_0.field.rd_pas_num=1;																										
										}	
										break;
										
										case 9://Read the number of active  and pas 查询Active和Passive态// Active and live
										{
											CanRxInfo.uds_info.byte_0.field.rd_act_num=1;	
										}
										break;
										
										case 0://Read the number of passive DTCs  查询未发生态
										{
											CanRxInfo.uds_info.byte_0.field.rd_not_ocr_num=1;																						
										}	
										break;
										
										case 1://Read the number of act DTCs  查all active态
										{
											//CanRxInfo.uds_info.byte_0.field.rd_act_num=1;	
											CanRxInfo.uds_info.byte_0.field.rd_act_pas_num=1;											
										}	
										break;
										
										default:
										{
											CanTxInfo.hu_uds_0.d[0]=3;
											CanTxInfo.hu_uds_0.d[1]=0x7F;
											CanTxInfo.hu_uds_0.d[2]=0x19;
											CanTxInfo.hu_uds_0.d[3]=0x31;
											
											for(i=4;i<8;i++)
											{
												CanTxInfo.hu_uds_0.d[i]=0;
											}												
											Positron_VW_PostMessage(CAN_POST_UDS);
										}
										break;
									}
								}
								break;
								
								case 2://	report DTC By Status Mask
								{
									switch(CanRxInfo.uds_info.d[1])
									{
										case 0x08://Read all passive DTCs.  查询Passive态
										{
											DTC_FLAG=1;
											dtc_location = 1;
											sta=1;
											for(l=0;l<DTC_BUFFER[dtc_location][1]+1;l++)
											{
												CanTxInfo.hu_tex_0.dtc[l]=DTC_BUFFER[dtc_location][5+l];
												CanTxInfo.hu_uds_0.d[l]=DTC_BUFFER[dtc_location][1+l];
											}
											CanTxInfo.hu_uds_0.d[3]=0x08;
											data_length=DTC_BUFFER[dtc_location][1];
											many_num_8=DTC_BUFFER[dtc_location][0];
											if(many_num_8<2)
											{						
												Positron_VW_PostMessage(CAN_POST_UDS);
												many_num_8=1;
											}
											else
											{
												DTC_LOCATION_SEND=1;
												Positron_VW_ManySendmessage();
											}
											
										}
										break;
										
										case 0x09://Read the  active and passive DTCs 查询Active态
										{
											dtc_location = 0;
											sta=1;
											DTC_FLAG=1;
											for(l=0;l<DTC_BUFFER[dtc_location][1]+1;l++)
											{
												CanTxInfo.hu_tex_0.dtc[l]=DTC_BUFFER[dtc_location][5+l];
												CanTxInfo.hu_uds_0.d[l]=DTC_BUFFER[dtc_location][1+l];
											}
											CanTxInfo.hu_uds_0.d[3]=0x09;
											data_length=DTC_BUFFER[dtc_location][1];
											many_num_9=DTC_BUFFER[dtc_location][0];
											if(many_num_9<2)
											{						
												Positron_VW_PostMessage(CAN_POST_UDS);
												many_num_9=1;
											}
											else
											{
												DTC_LOCATION_SEND=0;
												Positron_VW_ManySendmessage();
											}
										}
										break;
										
										case 0://Read No_ocr  查询No_ocr 态
										{
											dtc_location = 2;
											sta=1;
											DTC_FLAG=1;
											for(l=0;l<DTC_BUFFER[dtc_location][1];l++)
											{
												CanTxInfo.hu_tex_0.dtc[l]=DTC_BUFFER[dtc_location][6+l];
												CanTxInfo.hu_uds_0.d[l]=CanTxInfo.hu_tex_0.dtc[l];
											}
											data_length=DTC_BUFFER[dtc_location][1];
											many_num_0=DTC_BUFFER[dtc_location][0];
											if(many_num_0<2)
											{						
												Positron_VW_PostMessage(CAN_POST_UDS);
												many_num_0=1;
											}
											else
											{
												DTC_LOCATION_SEND=2;
												Positron_VW_ManySendmessage();
											}
										}
										break;
										
										case 1://Read all Act or Pas  查询Act and Pas 态
										{
											dtc_location = 3;
											sta=1;
											DTC_FLAG=1;
											for(l=0;l<DTC_BUFFER[dtc_location][1]+1;l++)
											{
												CanTxInfo.hu_tex_0.dtc[l]=DTC_BUFFER[dtc_location][5+l];
												CanTxInfo.hu_uds_0.d[l]=DTC_BUFFER[dtc_location][1+l];
											}
											CanTxInfo.hu_uds_0.d[3]=0x01;
											data_length=DTC_BUFFER[dtc_location][1];
											many_num_1=DTC_BUFFER[dtc_location][0];
											if(many_num_1<2)
											{						
												Positron_VW_PostMessage(CAN_POST_UDS);
												many_num_1=1;
											}
											else
											{
												DTC_LOCATION_SEND=3;
												Positron_VW_ManySendmessage();
											}
										}
										break;										
										
										default:
										{
											CanTxInfo.hu_uds_0.d[0]=3;
											CanTxInfo.hu_uds_0.d[1]=0x7F;
											CanTxInfo.hu_uds_0.d[2]=0x19;
											CanTxInfo.hu_uds_0.d[3]=0x31;
											
											for(i=4;i<8;i++)
											{
												CanTxInfo.hu_uds_0.d[i]=0;
											}												
											Positron_VW_PostMessage(CAN_POST_UDS);
											Check_mode=0;
										}
										break;
										
									}
								}
								break;
								
								default:
								{
									CanTxInfo.hu_uds_0.d[0]=3;
									CanTxInfo.hu_uds_0.d[1]=0x7F;
									CanTxInfo.hu_uds_0.d[2]=0x19;
									CanTxInfo.hu_uds_0.d[3]=0x12;
									
									for(i=4;i<8;i++)
									{
										CanTxInfo.hu_uds_0.d[i]=0;
									}										
									Positron_VW_PostMessage(CAN_POST_UDS);
								}
								break;
							
							}								
							Check_mode=0;								
						}
						else
						{
								CanTxInfo.hu_uds_0.d[0]=3;
								CanTxInfo.hu_uds_0.d[1]=0x7F;
								CanTxInfo.hu_uds_0.d[2]=0x19;
								CanTxInfo.hu_uds_0.d[3]=0x22;
								CanTxInfo.hu_uds_0.d[4]=0x00;
								CanTxInfo.hu_uds_0.d[5]=0x00;
								Positron_VW_PostMessage(CAN_POST_UDS);
						}							
						Check_mode=0;
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x19;
						CanTxInfo.hu_uds_0.d[3]=0x13;
						CanTxInfo.hu_uds_0.d[4]=0x00;
						CanTxInfo.hu_uds_0.d[5]=0x00;
						Positron_VW_PostMessage(CAN_POST_UDS);
					}
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x19;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					CanTxInfo.hu_uds_0.d[4]=0x00;
					CanTxInfo.hu_uds_0.d[5]=0x00;
					Positron_VW_PostMessage(CAN_POST_UDS);
				}					
			}
			break;
				
			case 0x14: //Erase Failure (Clear Diagnostic Information)
			{	
				u32 dtc;
				
				if(AccPinStatus)
				{
					if(CanRxInfo.uds_info.length==4)
					{
						CanTxInfo.hu_uds_0.d[0]=1;
						
						for(i=2;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}							
						dtc=(CanRxInfo.uds_info.d[0]<<16)|(CanRxInfo.uds_info.d[1]<<8)|(CanRxInfo.uds_info.d[2]);
						
						if(check_flag!=2)
						{
							uds_clear=1;
							switch(dtc)
							{
								case 0xFFFFFF:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;
								
								case 0x01FB03:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;									
								
								case 0x02FB04:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;
								
								case 0x03FB1F:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;
								
								case 0x04FB1F:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;
								
								case 0x05FB1F:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;
								
								case 0x06FB1F:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;
								
								case 0x07FB1F:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;
								
								case 0x08FB1F:
								{
									CanRxInfo.uds_info.dtc_h=CanRxInfo.uds_info.d[0];
									CanRxInfo.uds_info.dtc_m=CanRxInfo.uds_info.d[1];
									CanRxInfo.uds_info.dtc_l=CanRxInfo.uds_info.d[2];
									Positron_VW_PostMessage(CAN_POST_UDS);				
								}
								break;
								
								default:
								{
									CanTxInfo.hu_uds_0.d[0]=3;
									CanTxInfo.hu_uds_0.d[1]=0x7F;
									CanTxInfo.hu_uds_0.d[2]=0x14;
									CanTxInfo.hu_uds_0.d[3]=0x31;
									
									for(i=4;i<8;i++)
									{
										CanTxInfo.hu_uds_0.d[i]=0;
									}
									Positron_VW_PostMessage(CAN_POST_UDS);
								}
								break;
								
							}
							Uds_defaultTimer=T3S_1;							
						}
						else
						{							
							CanTxInfo.hu_uds_0.d[0]=3;
							CanTxInfo.hu_uds_0.d[1]=0x7F;
							CanTxInfo.hu_uds_0.d[2]=0x14;
							CanTxInfo.hu_uds_0.d[3]=0x22;
							
							for(i=4;i<8;i++)
							{
								CanTxInfo.hu_uds_0.d[i]=0;
							}
							Positron_VW_PostMessage(CAN_POST_UDS);
						}
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x14;
						CanTxInfo.hu_uds_0.d[3]=0x13;
						
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}
						Positron_VW_PostMessage(CAN_POST_UDS);
					}
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x14;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
					Positron_VW_PostMessage(CAN_POST_UDS);
				}
				Check_mode=0;		
			}
			break;
					
			case 0x27: //	Security Access 安全码设置
			{
				if(check_flag!=1)
				{
					if(AccPinStatus)
					{
						if(seed_time==0)
						{
							if(CanRxInfo.uds_info.length==2)
							{
								switch(CanRxInfo.uds_info.d[0])
								{
									case 1://	 Request Seed
									{		
										flag_Access = 1;
										sta=3;
										many_num=2;
										Check_mode=0;								
										bam_flag=1;
										seed_time=1;
										Positron_VW_ManySendmessage();
									}
									break;

									default:
									{
										CanTxInfo.hu_uds_0.d[0]=3;
										CanTxInfo.hu_uds_0.d[1]=0x7F;
										CanTxInfo.hu_uds_0.d[2]=0x27;
										CanTxInfo.hu_uds_0.d[3]=0x12;
										for(i=4;i<8;i++)
										{
											CanTxInfo.hu_uds_0.d[i]=0;
										}
										Positron_VW_PostMessage(CAN_POST_UDS);
									}
									break;
								}
							}
							else
							{
								CanTxInfo.hu_uds_0.d[0]=3;
								CanTxInfo.hu_uds_0.d[1]=0x7F;
								CanTxInfo.hu_uds_0.d[2]=0x27;
								CanTxInfo.hu_uds_0.d[3]=0x13;
								for(i=4;i<8;i++)
								{
									CanTxInfo.hu_uds_0.d[i]=0;
								}
								Positron_VW_PostMessage(CAN_POST_UDS);
								seed_time=0;
							}
						}
						else
						{
							CanTxInfo.hu_uds_0.d[0]=3;
							CanTxInfo.hu_uds_0.d[1]=0x7F;
							CanTxInfo.hu_uds_0.d[2]=0x27;
							CanTxInfo.hu_uds_0.d[3]=0x24;
							for(i=4;i<8;i++)
							{
								CanTxInfo.hu_uds_0.d[i]=0;
							}
							Positron_VW_PostMessage(CAN_POST_UDS);
							
						}
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x27;
						CanTxInfo.hu_uds_0.d[3]=0x22;
						seed_time=0;
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}
						Positron_VW_PostMessage(CAN_POST_UDS);
					}
				}
				else
				{							
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x27;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
					Positron_VW_PostMessage(CAN_POST_UDS);
				}
				Check_mode=0;	
			}
			break;

			case 0x28://  CommunicationControl Service
			{
				if(check_flag>1)
				{
					if(AccPinStatus)
					{
						if(CanRxInfo.uds_info.length==3)
						{
							CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length-1;
							CanTxInfo.hu_uds_0.d[3]=0;
							if(CanRxInfo.uds_info.d[1]==1)
							{
								switch(CanRxInfo.uds_info.d[0])
								{
									case 0: //	 enableRxAndTx
									{
										if(CanRxInfo.uds_info.d[1]==1)
										{
											con_flag=1;
											Positron_VW_PostMessage(CAN_POST_UDS);	
										}
										else
										{
											CanTxInfo.hu_uds_0.d[0]=3;
											CanTxInfo.hu_uds_0.d[1]=0x7F;
											CanTxInfo.hu_uds_0.d[2]=0x28;
											CanTxInfo.hu_uds_0.d[3]=0x31;	
											for(i=4;i<8;i++)
											{
												CanTxInfo.hu_uds_0.d[i]=0;
											}
										}		
									}
									break;

									case 3 :// disableRxAndTx
									{		
										if(CanRxInfo.uds_info.d[1]==1)
										{
											Positron_VW_PostMessage(CAN_POST_UDS);	
											con_flag=0;
										}
										else
										{
											CanTxInfo.hu_uds_0.d[0]=3;
											CanTxInfo.hu_uds_0.d[1]=0x7F;
											CanTxInfo.hu_uds_0.d[2]=0x28;
											CanTxInfo.hu_uds_0.d[3]=0x31;	
											for(i=4;i<8;i++)
											{
												CanTxInfo.hu_uds_0.d[i]=0;
											}
										}												
									}
									break;
										
									default:
									{
										CanTxInfo.hu_uds_0.d[0]=3;
										CanTxInfo.hu_uds_0.d[1]=0x7F;
										CanTxInfo.hu_uds_0.d[2]=0x28;
										CanTxInfo.hu_uds_0.d[3]=0x12;	
										for(i=4;i<8;i++)
										{
											CanTxInfo.hu_uds_0.d[i]=0;
										}										
									}
									break;
								}
							}
							else
							{
								CanTxInfo.hu_uds_0.d[0]=3;
								CanTxInfo.hu_uds_0.d[1]=0x7F;
								CanTxInfo.hu_uds_0.d[2]=0x28;
								CanTxInfo.hu_uds_0.d[3]=0x31;
								for(i=4;i<8;i++)
								{
									CanTxInfo.hu_uds_0.d[i]=0;
								}
								Positron_VW_PostMessage(CAN_POST_UDS);
							}
						}
						else
						{
							CanTxInfo.hu_uds_0.d[0]=3;
							CanTxInfo.hu_uds_0.d[1]=0x7F;
							CanTxInfo.hu_uds_0.d[2]=0x28;
							CanTxInfo.hu_uds_0.d[3]=0x13;
							for(i=4;i<8;i++)
							{
								CanTxInfo.hu_uds_0.d[i]=0;
							}
							Positron_VW_PostMessage(CAN_POST_UDS);
						}
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x28;
						CanTxInfo.hu_uds_0.d[3]=0x22;
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}
						Positron_VW_PostMessage(CAN_POST_UDS);
					}
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x28;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
				}
				Check_mode=0;
				Positron_VW_PostMessage(CAN_POST_UDS);						
			}
			break;	
			
			case 0x2E://  Write Data By Identifier
			{
				u8 format;
				u8 data_loss=0;
				//flag_refresh=1;
				if(AccPinStatus)
				{
					switch(check_fun)
					{
						case 0x0004://Vehicle Settings 设置门和雨刷器
						{
							format=5;
							CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length-2;
						}
						break;
						
						case 0x0005:// weight和level
						{
							format=5;
							CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length-2;
						}
						break;
						
						default:
						{
							format=4;
							CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length-1;						
						}
						break;
						
					}
					if(CanRxInfo.uds_info.length==format)
					{
						if(check_flag>1)
						{
							if(ser_ag)
							{
								CanTxInfo.hu_uds_0.d[3]=CanRxInfo.uds_info.d[1];
								
								for(i=4;i<8;i++)
								{
									CanTxInfo.hu_uds_0.d[i]=0;
								}								
								Uds_set=1;
								
								switch(check_fun)
								{									
									case 0x0002://设置车种类
									{
										if((CanRxInfo.uds_info.d[2]>10)||(CanRxInfo.uds_info.d[2]<=0))
										{
											data_loss=1;
										}								
									}
									break;									
									
									case 0x0004://Vehicle Settings 设置门和雨刷器
									{										
										if(CanRxInfo.uds_info.d[2]>1)											
										{
											if(CanRxInfo.uds_info.d[3]>1)		
											{
												data_loss=1;
											}												
										}		
									}
									break;
									
									case 0x0005://Vehicle Status Information
									{										
										if(CanRxInfo.uds_info.d[2]>1)											
										{
											if(CanRxInfo.uds_info.d[3]>1)		
											{
												data_loss=1;
											}												
										}		
									}
									break;
									
									default://离线地图是否启用
									{
										if(CanRxInfo.uds_info.d[2]>1)
										{
											data_loss=1;
										}								
									}
									break;
									
								}

								if(data_loss==0)
								{
									switch(check_fun)
									{									
										case 0x0002://设置车种类
										{											
											CanRxInfo.uds_info.byte_1.field.vehc_type=CanRxInfo.uds_info.d[2];										
										}
										break;
										
										case 0x0003://离线地图是否启用
										{
											CanRxInfo.uds_info.byte_1.field.navi_offline=CanRxInfo.uds_info.d[2];
										}
										break;
										
										case 0x0004://Vehicle Settings 设置门和雨刷器
										{										
											CanRxInfo.uds_info.byte_2.field.door_en=CanRxInfo.uds_info.d[2];
											CanRxInfo.uds_info.byte_2.field.wipe_en=CanRxInfo.uds_info.d[3];
										}
										break;
										
										case 0x0005://Vehicle Status Information
										{								
											CanRxInfo.uds_info.byte_2.field.wei_en=CanRxInfo.uds_info.d[2];
											CanRxInfo.uds_info.byte_2.field.lev_en=CanRxInfo.uds_info.d[3];
										}
										break;
										
										case 0x0006:// Trip and Vehicle data
										{
											CanRxInfo.uds_info.byte_1.field.tri_veh_en=CanRxInfo.uds_info.d[2];								
										}
										break;

										case 0x0007:// Driver’s grade  
										{
											CanRxInfo.uds_info.byte_1.field.dri_gra_en=CanRxInfo.uds_info.d[2];
										}
										break;

										case 0x0008:// Ethernet connection
										{
											
											CanRxInfo.uds_info.byte_1.field.net_con=CanRxInfo.uds_info.d[2];
										}
										break;

										case 0x0009:// Parking camera
										{
											CanRxInfo.uds_info.byte_2.field.camera_en=CanRxInfo.uds_info.d[2];
										}
										break;

										case 0x000A:// Parking sensor 
										{
											CanRxInfo.uds_info.byte_2.field.sensor_en=CanRxInfo.uds_info.d[2];
										}
										break;
										
										case 0x000B:// Unit Menu
										{
											CanRxInfo.uds_info.byte_2.field.unit_en=CanRxInfo.uds_info.d[2];
										}
										break;
										
										case 0x000C:// ad_blue_auto
										{
											CanRxInfo.uds_info.byte_2.field.ad_blue_auto_en=CanRxInfo.uds_info.d[2];
										}
										break;
										
										case 0x000D:// PTO
										{
											CanRxInfo.uds_info.byte_5.field.pto_en=CanRxInfo.uds_info.d[2];
										}
										break;
										
										case 0x000E:// chome volks
										{
											CanRxInfo.uds_info.byte_5.field.chome_volks_en=CanRxInfo.uds_info.d[2];
										}
										break;
										
										default:
										{
											CanTxInfo.hu_uds_0.d[0]=3;
											CanTxInfo.hu_uds_0.d[1]=0x7F;
											CanTxInfo.hu_uds_0.d[2]=0x2E;
											CanTxInfo.hu_uds_0.d[3]=0x22;
											
											for(i=4;i<8;i++)
											{
												CanTxInfo.hu_uds_0.d[i]=0;
											}
											Uds_set=0;
										}
										break;
										
									}									
								}
								else
								{
									CanTxInfo.hu_uds_0.d[0]=3;
									CanTxInfo.hu_uds_0.d[1]=0x7F;
									CanTxInfo.hu_uds_0.d[2]=0x2E;
									CanTxInfo.hu_uds_0.d[3]=0x13;
								
									for(i=4;i<8;i++)
									{
										CanTxInfo.hu_uds_0.d[i]=0;
									}											
									Uds_set=0;
									data_loss=0;
								}															
							}
							else
							{
								CanTxInfo.hu_uds_0.d[0]=3;
								CanTxInfo.hu_uds_0.d[1]=0x7F;
								CanTxInfo.hu_uds_0.d[2]=0x2E;
								CanTxInfo.hu_uds_0.d[3]=0x33;
								
								for(i=4;i<8;i++)
								{
									CanTxInfo.hu_uds_0.d[i]=0;
								}
							}
						}
						else
						{
							CanTxInfo.hu_uds_0.d[0]=3;
							CanTxInfo.hu_uds_0.d[1]=0x7F;
							CanTxInfo.hu_uds_0.d[2]=0x2E;
							CanTxInfo.hu_uds_0.d[3]=0x22;
							
							for(i=4;i<8;i++)
							{
								CanTxInfo.hu_uds_0.d[i]=0;
							}
						}
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x2E;
						CanTxInfo.hu_uds_0.d[3]=0x13;
						
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}
					}
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x2E;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
				}
				Positron_VW_PostMessage(CAN_POST_UDS);
				Check_mode=0;								
			}					
			break;
					
			case 0x22: //Read Data By Identifier
			{
				u8 l=0;
				if(AccPinStatus)
				{
					if(CanRxInfo.uds_info.length==3)
					{
						CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length+1;
						
						for(j=4;j<8;j++)
						{
							CanTxInfo.hu_uds_0.d[j]=0;
						}							
						CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length+1;
						uds_request=1;
						//CanRxInfo.uds_info.byte_3.byte=0;
						//CanRxInfo.uds_info.byte_4.byte=0;
						
						switch(check_fun)
						{
							case 0xf192://查询硬件号
							{
								flag_f192 = 1;
								ver_Location=CanRxInfo.uds_info.d[1]-0x90;
								for(l=0;l<VER_BUFFER[ver_Location][1];l++)
								{
									CanTxInfo.hu_tex_0.num[l]=VER_BUFFER[ver_Location][5+l];
								}
								sta=2;
								data_length=VER_BUFFER[ver_Location][1];
								many_num=VER_BUFFER[ver_Location][0];
								VER_LOCATION_SEND=2;
								Positron_VW_ManySendmessage();
							}
							break;
							
							case 0xf193://查询硬件版本号
							{
								ver_Location=CanRxInfo.uds_info.d[1]-0x90;
								for(l=0;l<=VER_BUFFER[ver_Location][1];l++)
								{
									CanTxInfo.hu_uds_0.d[l]=VER_BUFFER[ver_Location][l+1];
								}
								CanTxInfo.hu_uds_0.d[6]=0;
								CanTxInfo.hu_uds_0.d[7]=0;
								Positron_VW_PostMessage(CAN_POST_UDS);
							}
							break;
							
							case 0xf194://查询软件号
							{
								flag_f194 = 1;
								ver_Location=CanRxInfo.uds_info.d[1]-0x90;
								for(l=0;l<VER_BUFFER[ver_Location][1];l++)
								{
									CanTxInfo.hu_tex_0.num[l]=VER_BUFFER[ver_Location][5+l];
								}
								sta=2;
								data_length=VER_BUFFER[ver_Location][1];
								many_num=VER_BUFFER[ver_Location][0];
								VER_LOCATION_SEND=4;
								Positron_VW_ManySendmessage();
							}
							break;

							case 0xf195://查询软件版本号
							{
								flag_f195 = 1;
								ver_Location=CanRxInfo.uds_info.d[1]-0x90;
								for(l=0;l<VER_BUFFER[ver_Location][1];l++)
								{
									CanTxInfo.hu_tex_0.num[l]=VER_BUFFER[ver_Location][5+l];
								}
								sta=2;
								data_length=VER_BUFFER[ver_Location][1];
								many_num=VER_BUFFER[ver_Location][0];
								VER_LOCATION_SEND=5;
								Positron_VW_ManySendmessage();
							}
							break;

							case 0x0001://查询波特率
							{
								CanTxInfo.hu_uds_0.d[4]=0;//回复波特率250k
							}
							break;
						
							case 0x0002://查询车种类
							{
								CanRxInfo.uds_info.byte_4.field.model_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_1.field.vehc_type;
							}
							break;
							
							case 0x0003://查询离线地图是否启用?
							{
								CanRxInfo.uds_info.byte_3.field.navi_offline_req=1;
							  CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_1.field.navi_offline;	
							}
							break;
							
							case 0x0004://查询Vehicle Settings 门和雨刷器
							{
								CanTxInfo.hu_uds_0.d[0]=5;
								CanRxInfo.uds_info.byte_3.field.wip_dor_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_2.field.door_en;
								CanTxInfo.hu_uds_0.d[5]=CanRxInfo.uds_info.byte_2.field.wipe_en;												
							}
							break;
							
							case 0x0005://查询weight和level 是否可用
							{
								CanTxInfo.hu_uds_0.d[0]=5;
								CanRxInfo.uds_info.byte_3.field.wei_lev_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_2.field.wei_en;
								CanTxInfo.hu_uds_0.d[5]=CanRxInfo.uds_info.byte_2.field.lev_en;																
							}
							break;
							
							case 0x0006:// Trip and Vehicle data
							{
								CanRxInfo.uds_info.byte_3.field.tri_veh_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_1.field.tri_veh_en;									
							}
							break;

							case 0x0007:// Driver’s grade  
							{
								CanRxInfo.uds_info.byte_3.field.dri_gra_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_1.field.dri_gra_en;
							}
							break;

							case 0x0008:// Ethernet connection
							{
								CanRxInfo.uds_info.byte_3.field.net_con_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_1.field.net_con;											
							}
							break;

							case 0x0009:// Parking camera
							{
								CanRxInfo.uds_info.byte_3.field.camera_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_2.field.camera_en;									
							}
							break;

							case 0x000A:// Parking sensor 
							{
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_2.field.sensor_en;
								CanRxInfo.uds_info.byte_3.field.sensor_req=1;									
							}
							break;
							
							case 0x000B:// Unit menu 
							{
								CanRxInfo.uds_info.byte_4.field.unit_menu_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_2.field.unit_en;												
							}
							break;
						
							case 0x000C:// ad_blue_auto
							{
								CanRxInfo.uds_info.byte_4.field.ad_blue_auto_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_2.field.ad_blue_auto_en;
							}
							break;
							
							case 0x000D:// PTO_menu
							{
								CanRxInfo.uds_info.byte_6.field.pto_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_5.field.pto_en;
							}
							break;
							
							case 0x000E:// chome volks
							{
								CanRxInfo.uds_info.byte_6.field.chome_volks_req=1;
								CanTxInfo.hu_uds_0.d[4]=CanRxInfo.uds_info.byte_5.field.chome_volks_en;
							}
							break;
							
							default:
							{
								CanTxInfo.hu_uds_0.d[0]=3;
								CanTxInfo.hu_uds_0.d[1]=0x7F;
								CanTxInfo.hu_uds_0.d[2]=0x22;
								CanTxInfo.hu_uds_0.d[3]=0x31;
								Positron_VW_PostMessage(CAN_POST_UDS);
								for(i=4;i<8;i++)
								{
									CanTxInfo.hu_uds_0.d[i]=0;
								}									
							}
							break;
							
						}
						if(check_fun<=0x0E)//&&(check_fun!=2))
						{
							Positron_VW_PostMessage(CAN_POST_UDS);
						}
						Uds_defaultTimer=T3S_1;
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x22;
						CanTxInfo.hu_uds_0.d[3]=0x13;
						
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}
						Positron_VW_PostMessage(CAN_POST_UDS);
					}
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x22;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
					Positron_VW_PostMessage(CAN_POST_UDS);
				}
			}
			break;
												
			case 0x3E: //Tester Present
			{
				if(CanRxInfo.uds_info.length<3)
				{
					switch(CanRxInfo.uds_info.d[0])
					{
						case 0 :
						{
							Positron_VW_PostMessage(CAN_POST_UDS);
							Check_mode=1;		
						}
						break;

						case 0x80 :
						{
							Check_mode=0;		
						}
						break;
						
						default:
						{
							CanTxInfo.hu_uds_0.d[0]=3;
							CanTxInfo.hu_uds_0.d[1]=0x7F;
							CanTxInfo.hu_uds_0.d[2]=0x3E;
							CanTxInfo.hu_uds_0.d[3]=0x12;
							
							for(i=4;i<8;i++)
							{
								CanTxInfo.hu_uds_0.d[i]=0;
							}
							Positron_VW_PostMessage(CAN_POST_UDS);
						}
						break;
						
					}		
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x3E;
					CanTxInfo.hu_uds_0.d[3]=0x13;
					
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
					Positron_VW_PostMessage(CAN_POST_UDS);
				}
			}
			break;
				
			case 0x85://	Control DTC Setting
			{
				if(AccPinStatus)
				{
					if(check_flag==3)
					{
						if(CanRxInfo.uds_info.length==2)
						{
							switch(CanRxInfo.uds_info.d[0])
							{
								case 1: //	on
								{
									set_flag=1;
								}
								break;

								case 2:// off
								{
									set_flag=0;
								}
								break;
								
								default:
								{
									CanTxInfo.hu_uds_0.d[0]=3;
									CanTxInfo.hu_uds_0.d[1]=0x7F;
									CanTxInfo.hu_uds_0.d[2]=0x85;
									CanTxInfo.hu_uds_0.d[3]=0x12;
									
									for(i=4;i<8;i++)
									{
										CanTxInfo.hu_uds_0.d[i]=0;
									}
								}
								break;
							}
						}
						else
						{
							CanTxInfo.hu_uds_0.d[0]=3;
							CanTxInfo.hu_uds_0.d[1]=0x7F;
							CanTxInfo.hu_uds_0.d[2]=0x85;
							CanTxInfo.hu_uds_0.d[3]=0x13;
							
							for(i=4;i<8;i++)
							{
								CanTxInfo.hu_uds_0.d[i]=0;
							}
						}
					}
					else
					{
						CanTxInfo.hu_uds_0.d[0]=3;
						CanTxInfo.hu_uds_0.d[1]=0x7F;
						CanTxInfo.hu_uds_0.d[2]=0x85;
						CanTxInfo.hu_uds_0.d[3]=0x22;
						
						for(i=4;i<8;i++)
						{
							CanTxInfo.hu_uds_0.d[i]=0;
						}
					}
				}
				else
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x85;
					CanTxInfo.hu_uds_0.d[3]=0x22;
					
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
				}
				Positron_VW_PostMessage(CAN_POST_UDS);
				Check_mode=0;
			}
			break;

			default:
			{
				if(bam_flag==0)
				{
					CanTxInfo.hu_uds_0.d[0]=3;
					CanTxInfo.hu_uds_0.d[1]=0x7F;
					CanTxInfo.hu_uds_0.d[2]=0x11;
					CanTxInfo.hu_uds_0.d[3]=0x12;
					
					for(i=4;i<8;i++)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
					
					if(CanRxInfo.uds_info.length!=0x10)
					{
						Positron_VW_PostMessage(CAN_POST_UDS);
						Check_mode=0;
					}					
				}
			}
			break;	
			
		}
	}
}

void encipher(u8 *seed, u8 *ch_key)
{
   /* Magic constant, to avoid round symmetry attacks */
   static const unsigned int kulCryptDelta = 0x9E3779B9uL;
   static const unsigned char kucNumberOfRounds = 32;
   unsigned char pu8AccessSecurityPrivateKey[16];
   unsigned int pulAccessSecurityPrivateKey[4];
   unsigned char Index;
   u32  Sum,DataLow,DataHigh;
   Sum = 0;
	
   memcpy(&pulAccessSecurityPrivateKey[0], &DefaultPrivKeyUds[0], sizeof(DefaultPrivKeyUds));
   DataHigh = (unsigned int)(seed[0] << 24) + (unsigned int)(seed[1] << 16) + (unsigned int)(seed[2] << 8) + (unsigned int)(seed[3]);
   DataLow = (unsigned int)(seed[4] << 24) + (unsigned int)(seed[5] << 16) + (unsigned int)(seed[6] << 8) + (unsigned int)(seed[7]);

   for (Index = 0; Index < kucNumberOfRounds; Index++)
   {
      DataHigh += (((DataLow << 4) ^ (DataLow >> 5)) + DataLow) ^ (Sum + pulAccessSecurityPrivateKey[(Sum & 0x03)]);
      Sum += kulCryptDelta;
      DataLow += (((DataHigh << 4) ^ (DataHigh >> 5) ) + DataHigh) ^ (Sum + pulAccessSecurityPrivateKey[(Sum >> 11) & 0x03]);
   }
   ch_key[0] = (uint8_t)((DataHigh & 0xFF000000) >> 24);
   ch_key[1] = (uint8_t)((DataHigh & 0x00FF0000) >> 16);
   ch_key[2] = (uint8_t)((DataHigh & 0x0000FF00) >> 8);
   ch_key[3] = (uint8_t)((DataHigh & 0x000000FF));
   ch_key[4] = (uint8_t)((DataLow & 0xFF000000) >> 24);
   ch_key[5] = (uint8_t)((DataLow & 0x00FF0000) >> 16);
   ch_key[6] = (uint8_t)((DataLow & 0x0000FF00) >> 8);
   ch_key[7] = (uint8_t)((DataLow & 0x000000FF));
}

void Positron_VW_BamSendmessage(void)
{
	if(send_sta==0)
	{
		switch(text_num)
		{
			case 1:
			{
				PGN_L=((CAN_ID_MM_FBK_02&0x00FF00)>>8);
				PGN_M=((CAN_ID_MM_FBK_02&0xFF0000)>>16);
				if(navi_sta)
				{
					navi_num=4;
				}
				
				for(i=16;i<60;i++)
				{
					tex[i]=0xff;
				}
			}
			break;
			
			case 3:
			{
				u8 j=0;
				
				PGN_L=((CAN_ID_TEL_RSP_01&0x00FF00)>>8);
				PGN_M=((CAN_ID_TEL_RSP_01&0xFF0000)>>16);
				tel[0]=CanTxInfo.hu_tel_0.byte_0.byte;
				tel[1]=CanTxInfo.hu_tel_0.byte_1.byte;
				tel[2]=CanTxInfo.hu_tel_0.byte_2.byte;
				tel[3]=CanTxInfo.hu_tel_0.byte_3.byte;
				tel[4]=CanTxInfo.hu_tel_0.byte_4.byte;
				data_length=29;
				send_num=5;
				
				switch(tel[0])
				{
					case 5: 	
					{				
						for(j=0;j<29;j++)
						{
							if(tel[j]==0)
							{
								tel[j]=0xff;
							}
						}
					}
					break;
					
					case 9:					
					break;
					
					case 10: 	
					break;
					
					case 13: 
					{
						for(j=11;j<29;j++)
						{
							if(tel[j]==0)
							{
								tel[j]=0xff;
							}
						}
					}							
					break;
					
					default:
					{
						tel[0]=0;
						for(j=5;j<29;j++)
						{							
								tel[j]=0xff;
						}
					}
					break;
					
				}			
			}
			break;

			case 5:
			{
				PGN_L=((CAN_ID_DM1_ANSWER&0x00FF00)>>8);
				PGN_M=((CAN_ID_DM1_ANSWER&0xFF0000)>>16);
				DM1_flag=1;
			}
			break;
			
		}
		if(text_num==5)
		{
			CanTxInfo.hu_tex_0.dm[0]=0x20;
			CanTxInfo.hu_tex_0.dm[1]=data_length;
			CanTxInfo.hu_tex_0.dm[3]=send_num;
			CanTxInfo.hu_tex_0.dm[4]=0xff;
			CanTxInfo.hu_tex_0.dm[5]=PGN_L;
			CanTxInfo.hu_tex_0.dm[6]=PGN_M;
			CanTxInfo.hu_tex_0.dm[7]=0;
			send_add=1;
			Positron_VW_PostMessage(CAN_POST_CM_BAM);
			DM1_flag=0;
		}
		else if(text_num==3)
		{
			CanTxInfo.hu_tex_0.d[0]=0x20;
			CanTxInfo.hu_tex_0.d[1]=data_length;
			CanTxInfo.hu_tex_0.d[3]=send_num;
			CanTxInfo.hu_tex_0.d[4]=0xff;
			CanTxInfo.hu_tex_0.d[5]=PGN_L;
			CanTxInfo.hu_tex_0.d[6]=PGN_M;
			CanTxInfo.hu_tex_0.d[7]=0;
			send_add=1;
			Positron_VW_PostMessage(CAN_POST_CM_BAM);
		}
		else
		{
			CanTxInfo.hu_tex_0.d[0]=0x20;
			CanTxInfo.hu_tex_0.d[1]=data_length;
			CanTxInfo.hu_tex_0.d[3]=send_num;
			CanTxInfo.hu_tex_0.d[4]=0xff;
			CanTxInfo.hu_tex_0.d[5]=PGN_L;
			CanTxInfo.hu_tex_0.d[6]=PGN_M;
			CanTxInfo.hu_tex_0.d[7]=0;
			send_add=1;
			Positron_VW_PostMessage(CAN_POST_CM_BAM);
		}		
		Text_flag=1;
	}
	else if(navi_sta)
	{
		switch(navi_num)
		{			
			case 2:
			{
				send_num=5;
				data_length=34;
				PGN_L=((CAN_ID_NAVIGATION&0x00FF00)>>8);
				PGN_M=(CAN_ID_NAVIGATION&0xFF0000>>16);
			}
			break;
			
			case 4:
			{
				send_num=6;
				data_length=36;
				PGN_L=((CAN_ID_PHONE_NAVI&0x00FF00)>>8);
				PGN_M=(CAN_ID_PHONE_NAVI&0xFF0000>>16);
			}
			break;
		}		
		CanTxInfo.hu_tex_0.d[0]=0x20;
		CanTxInfo.hu_tex_0.d[1]=data_length;
		CanTxInfo.hu_tex_0.d[3]=send_num;
		CanTxInfo.hu_tex_0.d[4]=0xff;
		CanTxInfo.hu_tex_0.d[5]=PGN_L;
		CanTxInfo.hu_tex_0.d[6]=PGN_M;
		send_add=1;
		Positron_VW_PostMessage(CAN_POST_CM_BAM);
	}
	
	if(bam_num==0)
	{
		bam_num=send_num;
	}
	while(bam_num)
	{		
		CanTxInfo.hu_tex_0.d[0]=send_counter;			
		if(text_num==5)
		{
			CanTxInfo.hu_tex_0.dm[0]=send_counter;
			
			for(i=0;i<7;i++)
			{	
				CanTxInfo.hu_tex_0.dm[i+1]=dm[data_counter];
				data_counter++;
			}
		}
		else if(text_num==3)
		{
			CanTxInfo.hu_tex_0.d[0]=send_counter;
			for(i=0;i<7;i++)
			{	
				CanTxInfo.hu_tex_0.d[i+1]=tel[data_counter];
				data_counter++;
			}
		}
		else
		{
			switch(navi_num)
			{
				case 2:
				{
					for(i=0;i<7;i++)
					{	
						CanTxInfo.hu_tex_0.d[i+1]=navi[data_counter];
						data_counter++;
					}
				}
				break;
				
				case 4:
				{
					for(i=0;i<7;i++)
					{	
						CanTxInfo.hu_tex_0.d[i+1]=phone[data_counter];
						data_counter++;
					}
				}
				break;
				
				default:
				{
					for(i=0;i<7;i++)
					{	
						CanTxInfo.hu_tex_0.d[i+1]=tex[data_counter];
						data_counter++;
					}
				}
				break;
				
			}
		}		
		Positron_VW_PostMessage(CAN_POST_DA_BAM);
		bam_num--;
		send_counter++;
	}
	CanTxInfo.hu_tel_0.byte_0.byte=0;
	
	for(i=0;i<data_counter;i++)
	{	
		tex[i]=0;
		CanTxInfo.hu_tex_0.d[i]=0;
		if(i>4)
		{
			tel[i]=0;			
		}
	}
	
	if(Text_flag)
	{
		send_sta=1;
		Text_flag=0;
		
		if(navi_num)
		{
			send_counter=1;
			data_counter=0;
			text_num=0;
			Positron_VW_BamSendmessage();
		}
	}
	send_counter=1;	
	text_num=0;
	data_counter=0;	
	navi_num=0;
	send_sta=0;
	send_add=0;
}

void Positron_VW_AutoTestStartCheck(void)
{
	u8 j;
	u8 d_bak[7];
	u8 d_flag=0;
	u8 d_check=0;
	u8 sid_check=0;
	
	if((CAN_TEST_RX_BUFFER[Test_Location][0]<0x7F)&&(CAN_TEST_RX_BUFFER[Test_Location][0]>0))// check pid fanwei
	{
		for(i=0;i<8;i++)
		{
			if(Test_Start_flag==0)
			{
				if(i==0)
				{
					CAN_TEST_TX_BUFFER[Test_Location][i]=CAN_TEST_RX_BUFFER[Test_Location][i]+0x80;
				}
				else if(i==1)
				{
					CAN_TEST_TX_BUFFER[Test_Location][i]=CAN_TEST_RX_BUFFER[Test_Location][i]+1;
				}
				else if(i>1)
				{
					CAN_TEST_TX_BUFFER[Test_Location][i]=CAN_TEST_RX_BUFFER[Test_Location][i];
				}
			}
			else if(Test_Start_flag==1)
			{
				if(i==0)
				{
					CAN_TEST_TX_BUFFER[Test_Location][i]=CAN_TEST_RX_BUFFER[Test_Location][i]+0x80;
				}
				else
				{
					CAN_TEST_TX_BUFFER[Test_Location][i]=CAN_TEST_RX_BUFFER[Test_Location][i];
				}
			}			
		}
		if(Test_Start_flag==0)
		{
			if(CAN_TEST_RX_BUFFER[Test_Location][0]==0x11) 
			{
				if(CAN_TEST_RX_BUFFER[Test_Location][1]>0&&CAN_TEST_RX_BUFFER[Test_Location][1]<8)
				{
					if(sid_bak)//cha 0x11 sid shi fou luo ji shun xu di zeng
					{
						if(CAN_TEST_RX_BUFFER[Test_Location][1]==(sid_bak+2))
						{
							sid_check=1;
							sid_bak=CAN_TEST_RX_BUFFER[Test_Location][1];
						}
						else
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;//sid logic wrong
						}
					}
					else
					{
						if(CAN_TEST_RX_BUFFER[Test_Location][1]==(sid_bak+1))
						{
							sid_check=1;
							sid_bak=CAN_TEST_RX_BUFFER[Test_Location][1];
						}
						else
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;//sid logic wrong
						}
					}
				}
				else
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=2;//sid logic wrong
				}
				if(sid_check)// check sid fanwei
				{
					for(i=1;i<7;i++)
					{
						d_bak[i]=CAN_TEST_RX_BUFFER[Test_Location][i+1];
					}
					if(sid_bak==5)
					{
						for(j=1;j<7;j++)
						{	
							if(j>1)
							{
								if(d_bak[j]==(0xff-seed[j-2]))
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
							else
							{
								if(d_bak[j]==0)
								{
									d_loss=1;
									break;
								}
								else if(d_bak[j]==0xff)
								{
									d_flag++;
								}
							}
						}
						if(d_loss)
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong							
						}
						else
						{
							if(d_flag==6)
							{
								d_check=1;
							}
							else
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
							}
						}	
					}	
					else if((sid_bak>0)&&(sid_bak!=5)&&(sid_bak<8))
					{
						for(j=1;j<7;j++)
						{								
								if(d_bak[j]==0)
								{
									d_loss=1;
									break;
								}
								else if(d_bak[j]==(j*16+j))
								{
									d_flag++;
								}
						}						
						if(d_loss)
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
							
						}
						else
						{
							if(d_flag==6)
							{
								d_check=1;
							}
							else
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
							}
						}	
					}				
				}
				else
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=2;// sid wrong
				}
				if(d_check)
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0xf1;
					switch(sid_bak)
					{
						case 3:
						{
							seed[0]=((System_Time_Counter&0x0ff0)>>4);
							seed[1]=(System_Time_Counter&0xFF);
							seed[2]=CanTxVolTimer;
							seed[3]=CanTxGearTimer;
							seed[4]=Positron_VW_TxTimer;	
							
							for(j=0;j<7;j++)
							{
								r_key[j]=(0xff-seed[j]);
							}							
							for(i=0;i<5;i++)
							{
								CAN_TEST_TX_BUFFER[Test_Location][i+3]=seed[i];
							}							
						}
						break;
						
						case 5:
						{
							CAN_TEST_TX_BUFFER[Test_Location][3]=0x22;
							CAN_TEST_TX_BUFFER[Test_Location][4]=0x33;
							CAN_TEST_TX_BUFFER[Test_Location][5]=0x44;
							CAN_TEST_TX_BUFFER[Test_Location][6]=0x55;
							CAN_TEST_TX_BUFFER[Test_Location][7]=0x66;			
						}
						break;
						
						case 7:
						{
							Test_Start_flag=1;					
						}
						break;
						
					}
				}
			}
			else
			{
				CAN_TEST_TX_BUFFER[Test_Location][2]=1;// not start test mode
			}
		}
		else
		{
			Positron_VW_AutoTestCheck();
		}
	}
	else
	{
		CAN_TEST_TX_BUFFER[Test_Location][2]=1;// not start test mode
	}
	for(i=0;i<8;i++)
	{
		if(i==0)
		{
			CanTxInfo.hu_tes_0.pid=CAN_TEST_TX_BUFFER[Test_Location][i];
		}
		else if(i>0)
		{
			CanTxInfo.hu_tes_0.d[i-1]=CAN_TEST_TX_BUFFER[Test_Location][i];
		}
	}
	if((Test_APP==0)||(d_loss))
	{
		Positron_VW_PostMessage(CAN_POST_TEST);
		d_loss=0;
	}
}

void Positron_VW_AutoTestCheck(void)
{
	u8 pid_h;
	u8 pid_l;
	u8 j=0;
	u8 d_bak[7];
	u8 d_flag=0;
	u8 d_check=0;
	
	pid_h=((CAN_TEST_RX_BUFFER[Test_Location][0]&0xF0)>>4);
	pid_l=(CAN_TEST_RX_BUFFER[Test_Location][0]&0x0F);
	sid_bak=CAN_TEST_RX_BUFFER[Test_Location][1];
	for(j=0;j<7;j++)
	{
		d_bak[j]=CAN_TEST_RX_BUFFER[Test_Location][j+1];
	}
	switch(pid_h)
	{
		case 1:
		{
			switch(pid_l)
			{
				case 1:
				{
					Test_Start_flag=0;
				}
				break;
				
				case 2:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<11)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<11)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<11)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 4:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 5:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<11)&&(d_bak[i]>=0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 3:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

						case 3:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 4:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 5:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 6:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<2)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 7:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 4:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<2)&&(d_bak[i]>=0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==2)
								{
									if((d_bak[i]<11)&&(d_bak[i]>=0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<2)&&(d_bak[i]>=0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

						case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<2)&&(d_bak[i]>=0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
											
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 5:
				{
					switch(sid_bak)
					{
					case 1://MIC set
					{
						for(i=1;i<7;i++)
						{
							if(i==1)
							{
								if((d_bak[i]<2)&&(d_bak[i])>=0)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
							else
							{
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
						}
						if(d_loss)
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
							
							break;
						}
						else
						{
							if(d_flag==6)
							{
								d_check=1;
							}
							else
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
								break;
							}
						}
						if(d_check)
						{
							Positron_VW_AutoTestPro();
						}
					}
					break;
						
					case 2://MIC req
					{
						for(i=1;i<7;i++)
						{	
							if(d_bak[i]==0xff)
							{
								d_flag++;
							}
							else
							{
								d_loss=1;
								break;
							}								
						}
						if(d_loss)
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
							
							break;
						}
						else
						{
							if(d_flag==6)
							{
								d_check=1;
							}
							else
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
								break;
							}
						}
						if(d_check)
						{
							Positron_VW_AutoTestPro();
						}
					}
					break;
					
					case 3://MIC record
					{
						for(i=1;i<7;i++)
						{
							if(i==1)
							{
								if((d_bak[i]<2)&&(d_bak[i])>=0)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
							else
							{
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
						}
						if(d_loss)
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
							
							break;
						}
						else
						{
							if(d_flag==6)
							{
								d_check=1;
							}
							else
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
								break;
							}
						}
						if(d_check)
						{
							Positron_VW_AutoTestPro();
						}
					}
					break;
					
					case 4://MIC record play
					{
						for(i=1;i<7;i++)
						{
							if(i==1)
							{
								if((d_bak[i]<2)&&(d_bak[i])>=0)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
							else
							{
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
						}
						if(d_loss)
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
							
							break;
						}
						else
						{
							if(d_flag==6)
							{
								d_check=1;
							}
							else
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
								break;
							}
						}
						if(d_check)
						{
							Positron_VW_AutoTestPro();
						}
					}
					break;
					
					default:
					{
						CAN_TEST_TX_BUFFER[Test_Location][2]=2;
					}
					break;
					}
				}
				break;
				
				default:
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=2;
				}
				break;
			}
		}
		break;
		
		case 2:
		{
			switch(pid_l)
			{
				case 1:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<5)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

						case 3:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
											
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 2:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<0x29)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

						case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<0x13)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 4:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 5:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<0x13)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 6:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 7:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<0x13)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 8:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 9:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<0x13)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 10:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 11:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<12)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 12:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 13:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<2)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 14:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 15:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<2)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 16:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 17:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 3:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<0x18)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==2)
								{
									if(d_bak[i]<0x3C)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
											
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
					
				default:
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=2;
				}
				break;
				
			}
		}
		break;
		
		case 3:
		{
			switch(pid_l)
			{
				case 1:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<3)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

					/*	case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<3)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 4:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;*/
						
						case 5:
						{
							u16 Freq;
							
							Freq=((d_bak[1]<<8)|d_bak[2]);
							
							if(((Freq>=0x02F8)&&(Freq<=0x0438))||((Freq>=0x1464)&&(Freq<=0x42cc)))
							{
								d_flag=+2;
							}
							else
							{
								d_loss=1;
							}
							
							for(i=3;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 6:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 7:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<0x13)&&(d_bak[i]>0x10))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 8:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 9:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]<3)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 10:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 11:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<0x13)&&(d_bak[i]>0x10))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 12:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 13:
						{
							u16 Freq;
							
							Freq=((d_bak[3]<<8)|d_bak[4]);
							
							for(i=1;i<7;i++)
							{
								if((i<5)&&(i>2))
								{
									if(((Freq>0x02F8)&&(Freq<0x0438))||((Freq>0x1464)&&(Freq<0x42cc)))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==1)
								{
									if(((d_bak[i]>0x10)&&(d_bak[i]<0x13)))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==2)
								{
									if(d_bak[i]<0x13)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 14:
						{
							for(i=1;i<7;i++)
							{	
								if(i==1)
								{
									if(((d_bak[i]>0x10)&&(d_bak[i]<0x13))||(d_bak[i]==0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}			
								}					
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
																
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 2:
				{
					switch(sid_bak)
					{
						case 1://yi si duo bao fa song
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<5)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]<=0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<5)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

						case 5:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 6:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 7:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 8:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]==1)
									{
										d_flag++;
									}
								}
								else if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 9:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<4)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 11:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 12://BT set
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 13://BT req
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 3:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{							
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}							
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{							
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}							
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

						/*case 3:
						{
							for(i=1;i<7;i++)
							{							
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}							
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;*/
																												
						
						
						
						case 4:
						{
							for(i=1;i<7;i++)
							{	
								if(i==1)
								{
									if((d_bak[i]>0)&&(d_bak[i]<3))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}		
								}									
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}		
								}
													
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 5:
						{
							for(i=1;i<7;i++)
							{									
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}															
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 4:
				{
					switch(sid_bak)
					{
						case 1://yi si duo bao fa song
						{
							for(i=1;i<7;i++)
							{						
								if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

						case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i<5)
								{
									if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;					
						
						case 4:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;				
													
						case 5:
						{
							for(i=1;i<7;i++)
							{	
								if(i==1)
								{
									if((d_bak[i]>0)&&(d_bak[i]<3))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}		
								}									
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}		
								}
													
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 6:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;	
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 5:
				{
					switch(sid_bak)
					{
						case 1://yi si duo bao fa song
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{								
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;

						case 3:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;									
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;				
						
						case 4:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;									
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;	

						case 5:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 6:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 7:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
																						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 6:
				{
					switch(sid_bak)
					{
						case 1://yi si duo bao fa song
						{
							for(i=1;i<7;i++)
							{						
								if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 3:
						{
							for(i=1;i<7;i++)
							{
								if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}							
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;										
						
						case 4:
						{
							for(i=1;i<7;i++)
							{
								if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}							
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;			

						case 5:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 6:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;	
						
						case 7:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 8:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;	
						
						case 9:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<3)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 10:
						{
							for(i=1;i<7;i++)
							{	
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;	
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				default:
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=2;
				}
				break;
			}
		}
		break;
		
		case 4:
		{
			switch(pid_l)
			{
				case 1:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<6)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==2)
								{
									if((d_bak[i]<11)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<6)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
																						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 2:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<2)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<10)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
																						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 3:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<2)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
																						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 4:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<2)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<6)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 4:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
																						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				default:
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=2;
				}
				break;
				
			}
		}
		break;
		
		case 5:
		{
			switch(pid_l)
			{
				case 1:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=0x10)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=0x10)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 3:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 4:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<0x15)&&(d_bak[i])>0x10)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 5:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 2:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
									
								}
								else
								{
									if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}			
							}													
				
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
									
								}
								else
								{
									if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
											
						case 4:
						{
							for(i=1;i<7;i++)
							{
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}			
							}													
				
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 5:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=0x04)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}			
								}
								else 
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}			
								}														
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
												
						case 6:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=0x0a)&&(d_bak[i]>0))
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}			
								}
								else 
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}			
								}														
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 7:
						{
							for(i=1;i<7;i++)
							{
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}			
							}													
				
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				case 3:
				{
					switch(sid_bak)
					{
						case 1:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
									
								}
								else
								{
									if((d_bak[i]<=0xfe)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 2:
						{
							for(i=1;i<7;i++)
							{								
								if(d_bak[i]==0xff)
								{
									d_flag++;
								}
								else
								{
									d_loss=1;
									break;
								}								
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 3:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=6)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==2)
								{
									if((d_bak[i]<=0xff)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}									
								}
								else if(i==3)
								{
									if((d_bak[i]<=12)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==4)
								{
									if((d_bak[i]<=0x1f)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==5)
								{
									if((d_bak[i]<=0x17)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
								else if(i==6)
								{
									if((d_bak[i]<=0x3b)&&(d_bak[i])>=0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						case 4:
						{
							for(i=1;i<7;i++)
							{
								if(i==1)
								{
									if((d_bak[i]<=5)&&(d_bak[i])>0)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}									
								}
								else
								{
									if(d_bak[i]==0xff)
									{
										d_flag++;
									}
									else
									{
										d_loss=1;
										break;
									}
								}
							}
							if(d_loss)
							{
								CAN_TEST_TX_BUFFER[Test_Location][2]=5;//data loss
								
								break;
							}
							else
							{
								if(d_flag==6)
								{
									d_check=1;
								}
								else
								{
									CAN_TEST_TX_BUFFER[Test_Location][2]=3;//data wrong
									break;
								}
							}
							if(d_check)
							{
								Positron_VW_AutoTestPro();
							}
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=2;
						}
						break;
					}
				}
				break;
				
				default:
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=2;
				}
				break;

			}
		}
		break;
		
		default:
		{
			CAN_TEST_TX_BUFFER[Test_Location][2]=2;
		}
		break;
		
	}
	for(i=0;i<8;i++)
	{
		if(i==0)
		{
			CanTxInfo.hu_tes_0.pid=CAN_TEST_TX_BUFFER[Test_Location][i];
		}
		else if(i>0)
		{
			CanTxInfo.hu_tes_0.d[i-1]=CAN_TEST_TX_BUFFER[Test_Location][i];
		}
	}
	
	if(CAN_TEST_TX_BUFFER[Test_Location][2]!=0xf1)
	{
		sid_bak=0;
	}
}
		
		
	



		
				
				
				
void Positron_VW_AutoTestPro(void)
{
	Test_APP=0;
	A_ILL_Flag=1;
	//KeyPwmConfig(KEY_LIGHT_CLOSED);
	CanTxInfo.hu_tes_0.pid=CAN_TEST_TX_BUFFER[Test_Location][0];
	CAN_TEST_TX_BUFFER[Test_Location][2]=0xf1;
	Test_APP=0;
	switch(CAN_TEST_RX_BUFFER[Test_Location][0])//pid
	{
		case 0x12://power 
		{
			
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])//sid
			{
				case 1://Hardware reset 硬件复位
				{
					CanTxAutoTestTimer=CAN_TEST_RX_BUFFER[Test_Location][2];
					Test_Power_flag=1;
					reset_can_flag=1;
				}
				break;
					
				case 2://Software reset 软件复位
				{
					CanTxAutoTestTimer=CAN_TEST_RX_BUFFER[Test_Location][2];
					Test_Power_flag=1;
				}
				break;
					
				case 3://Factory reset  工厂复位
				{
					PostMessage(MMI_MODULE,UICC_SYS_RESET,0);
				}
				break;
					
				case 4://Supply power 回复此时电压
				{				
					CAN_TEST_TX_BUFFER[Test_Location][3]=((power_current&0xFF00)>>8);
					CAN_TEST_TX_BUFFER[Test_Location][4]=(power_current&0x00FF);
				}
				break;	
				
				case 5://Sleep Mode 睡眠模式 一小时模式
				{					
					CanTxAutoTestTimer=CAN_TEST_RX_BUFFER[Test_Location][2];
					Test_Power_flag=1;
				}
				break;	

				default:
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=2;
				}
				break;
			}						
		}
		break;
				
		case 0x13: //hardware
		{
			CanRxInfo.base_info.byte_0.field.f_power=0;
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])//sid
			{
				/*case 1://Request Wireless Charger State 查询无线充电器状态
				{
					CanTxAutoTestTimer=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
					
				case 2:// Request Wireless Charger Frequency and duty cycle 查询无线充电器频率和占空比
				{
				}
				break;*/
						
				case 3://	Request Parking Brake State  查询手刹状态 
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=GPIO_Flag.field.f_stop_car;
				}
				break;

				/*case 4://	Request Vehicle Speed Signal 查询车速信号？车速信号将显示为频率信号。？
				{
				}
				break;*/

				case 5://	Request Reverse state 查询倒车状态
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=GPIO_Flag.field.f_reverse_det;
				}
				break;

				case 6://	Activate Auxiliary Analog Video Input 激活辅助模拟视频输入？
				{
					GPIO_Flag.field.f_auxin_det=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;

				case 7://	request Activate Auxiliary Analog Video Input 查询辅助模拟视频输入状态
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=GPIO_Flag.field.f_auxin_det;
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
			}								
		}
		break;
			
		case 0x14://ill 
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])//sid
			{
				case 1:// Turn illumination on 灯光打开选择
				{
					KeyLedAutoTest=(CAN_TEST_RX_BUFFER[Test_Location][3])*10;//亮度等级
					
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{
						case 0://  ID = 00h - Just the power button with red light;
						{
							KeyPwmConfig(KEY_LIGHT_CLOSED);
							POWER_LED_ON;
						}
						break;
							
						case 1://	All buttons with white light.
						{
							POWER_LED_OFF;
							KeyPwmConfig(KEY_LIGHT_AUTO_TEST);
						}
						break;
							
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
						}
						break;		
						
					}
				}
				break;
					
				case 2:// Turn illumination off 灯光关闭选择
				{
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{
						case 0://  ID = 00h - Just the power button with red light;
						{
							POWER_LED_OFF;
						}
						break;
							
						case 1://	All buttons with white light.
						{
							KeyLedAutoTest=0;
							KeyPwmConfig(KEY_LIGHT_AUTO_TEST);
						}
						break;
							
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
						}
						break;			
						
					}
				}
				break;
						
				case 3://	Request Ilumination state  查询灯光状态 返回灯光状态 亮度等级 
				{
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{
						case 0://  ID = 00h - Just the power button with red light;
						{
							CAN_TEST_TX_BUFFER[Test_Location][3]=POWER_LED_DET;
							if(POWER_LED_DET)
							{
								CAN_TEST_TX_BUFFER[Test_Location][4]=0x0A;
							}
							else 
							{
								CAN_TEST_TX_BUFFER[Test_Location][4]=0x00;
							}
						}
						break;
							
						case 1://	All buttons with white light.
						{
							if(KeyLedAutoTest)
							{
								CAN_TEST_TX_BUFFER[Test_Location][3]=1;
							}
							else
							{
								CAN_TEST_TX_BUFFER[Test_Location][3]=0;
							}
							CAN_TEST_TX_BUFFER[Test_Location][4]=KeyLedAutoTest/10;
						}
						break;
							
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
						}
						break;		
						
					}
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
				
			}								
		}
		break;
		
		case 0x15: //MIC
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	Turn microphone on or off 是否开启麦克风
				{
					CanRxInfo.test_set_info.order=0x35;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;

				case 2://	RRequest Microphone state 查询麦克风是否开启
				{
					CanRxInfo.test_set_info.order=0x36;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				case 3://Record sound from MIC
				{
					CanRxInfo.test_set_info.order=0x39;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
				
				case 4://play Record sound
				{
					CanRxInfo.test_set_info.order=0x3a;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
				
				default:
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
			}
		}
		break;
			
		case 0x21: //SRC 
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	Src 资源切换
				{
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{
						case 1://radio
						{
							CanRxInfo.src_info.byte_0.field.f_src_select=1;
						}
						break;
							
						case 2://USB
						{
							CanRxInfo.src_info.byte_0.field.f_src_select=6;
						}
						break;
							
						case 3://BT
						{
							CanRxInfo.src_info.byte_0.field.f_src_select=5;
						}
						break;
							
						case 4://AUX
						{
							CanRxInfo.src_info.byte_0.field.f_src_select=7;
						}
						break;
							
					}
				}
				break;
						
				case 2:// 查询此时处于什么资源 
				{
					switch(CanTxInfo.hu_src_0.byte_6.field.f_src_sel_res)
					{
						case 1://radio
						{
							CAN_TEST_TX_BUFFER[Test_Location][3]=1;
						}
						break;
								
						case 6://USB
						{
							CAN_TEST_TX_BUFFER[Test_Location][3]=2;
						}
						break;
								
						case 5://BT
						{
							CAN_TEST_TX_BUFFER[Test_Location][3]=3;
						}
						break;
								
						case 7://AUX
						{
							CAN_TEST_TX_BUFFER[Test_Location][3]=4;
						}
						break;
						
					}
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
					
			}
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_SRC_INO);
		}
		break;
				
		case 0x22: //	EQ 
		{
			u8 eq_flag;
			CanRxInfo.test_set_info.minus=0;
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	 音量大小设置
				{
					CanRxInfo.test_set_info.order=1;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
					
				case 2://	查询音量
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=CanTxInfo.hu_rad_0.byte_0.field.f_cur_vol;
					eq_flag=1;
				}
				break;

				case 3://	bass音设置
				{	
					CanRxInfo.test_set_info.order=2;
					if(CAN_TEST_RX_BUFFER[Test_Location][2]<4)
					{
						CanRxInfo.test_set_info.gain=4-CAN_TEST_RX_BUFFER[Test_Location][2];
						CanRxInfo.test_set_info.minus=2;
					}
					else if(CAN_TEST_RX_BUFFER[Test_Location][2]>=4)
					{
						CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2]-4;
						if(CAN_TEST_RX_BUFFER[Test_Location][2]>4)
						{
							CanRxInfo.test_set_info.minus=1;
						}
					}
				}
				break;
						
				case 4://bass音设置查询
				{
					CanRxInfo.test_set_info.order=0x23;
					CanRxInfo.test_set_info.minus=2;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				case 5://	Treble音设置
				{
					CanRxInfo.test_set_info.order=3;
					if(CAN_TEST_RX_BUFFER[Test_Location][2]<4)
					{
						CanRxInfo.test_set_info.gain=4-CAN_TEST_RX_BUFFER[Test_Location][2];
						CanRxInfo.test_set_info.minus=2;
					}
					else if(CAN_TEST_RX_BUFFER[Test_Location][2]>=4)
					{
						CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2]-4;
						if(CAN_TEST_RX_BUFFER[Test_Location][2]>4)
						{
							CanRxInfo.test_set_info.minus=1;
						}
					}
				}
				break;
						
				case 6://	Treble音设置查询
				{
					CanRxInfo.test_set_info.order=0x23;
					CanRxInfo.test_set_info.minus=1;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				case 7://Balance音设置
				{
					CanRxInfo.test_set_info.order=4;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
					if(CAN_TEST_RX_BUFFER[Test_Location][2]<=8)
					{
						CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
						CanRxInfo.test_set_info.minus=2;
					}
					else if(CAN_TEST_RX_BUFFER[Test_Location][2]>=9)
					{
						CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2]-9;					
						CanRxInfo.test_set_info.minus=1;
					}
				}
				break;
				
				case 8://	Balance音设置查询
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=DSP_Data.balance;
				}
				break;
					
				case 9://Fader音设置 MID
				{				
					CanRxInfo.test_set_info.order=5;
					if(CAN_TEST_RX_BUFFER[Test_Location][2]<4)
					{
						CanRxInfo.test_set_info.gain=4-CAN_TEST_RX_BUFFER[Test_Location][2];
						CanRxInfo.test_set_info.minus=2;
					}
					else if(CAN_TEST_RX_BUFFER[Test_Location][2]>=4)
					{
						CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2]-4;
						if(CAN_TEST_RX_BUFFER[Test_Location][2]>4)
						{
							CanRxInfo.test_set_info.minus=1;
						}
					}
				}
				break;
						
				case 10://	Fader音设置查询MID
				{
					CanRxInfo.test_set_info.order=0x23;
					CanRxInfo.test_set_info.minus=3;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				case 11://	EQ类型设置
				{
					CanRxInfo.test_set_info.order=6;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
					
				}
				break;
						
				case 12://	EQ类型查询
				{
					switch(DSP_Data.eq_mode)
					{
						case 0:
						{
							CAN_TEST_TX_BUFFER[Test_Location][3]=0x0B;
						}
						break;
						
						default:
						{
							CAN_TEST_TX_BUFFER[Test_Location][3]=DSP_Data.eq_mode;
						}
						break;
						
					}
				}
				break;
					
				case 13://	响度开关设置
				{
					CanRxInfo.test_set_info.order=7;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
						
				case 14://	响度开关设置查询
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=DSP_Data.loudness_on_off;
					eq_flag=1;
				}
				break;
					
				case 15://beep音开关设置
				{
					CanRxInfo.test_set_info.order=8;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
						
				case 16://	beep音开关设置查询
				{
					CanRxInfo.test_set_info.order=0x2b;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				case 17://	还原所有EQ值
				{
					CanRxInfo.test_set_info.order=9;
					CanRxInfo.test_set_info.gain=1;
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
				
			}
			if(eq_flag==0)
			{
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEST_INO);
			}
		}
		break;
				
		case 0x23:// Clock  
		{
			u8 clock_flag;
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	时间设置
				{
					CanRxInfo.test_set_info.order=10;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][3];
				}
				break;
						
				case 2://	查询当前时间
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=RTC_TimeInfo.hours;//APP  hour
					CAN_TEST_TX_BUFFER[Test_Location][4]=RTC_TimeInfo.minutes;//APP	min
					clock_flag=1;
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
					Test_mode=0;
				}
				break;
					
			}
			if(clock_flag)
			{
				PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEST_INO);
				clock_flag=0;
			}
		}
		break;
				
		case 0x31: //Radio测试
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	设置收音系统 
				{
					CanRxInfo.radio_info.set_radio=CAN_TEST_RX_BUFFER[Test_Location][2];					
				}
				break;
						
				case 2://	查询收音系统 已验证
				{						
					CAN_TEST_TX_BUFFER[Test_Location][3]=Radio.flag.field.f_stereo_mem+1; //	STEREO MOMO
				}
				break;
					
				case 3://	设置收音敏感度 已验证
				{
					CanRxInfo.radio_info.set_sen=CAN_TEST_RX_BUFFER[Test_Location][2]; //	DX  LOC
					PostMessage(TUNER_MODULE, EVT_TUN_DX_LOC,CanRxInfo.radio_info.set_sen);
					CanRxInfo.radio_info.set_sen=0;						
				}
				break;
						
				case 4://	查询收音敏感度 已验证
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=radiostruct_ram.flag.field.F_loc_dx; //	//	DX  LOC
				}
				break;

				case 5://	设置收音频率 已验证
				{
					u16 Test_Radio;
					//u16 Test_L;
					//u16 Test_H;
						
					//Test_H=CAN_TEST_RX_BUFFER[Test_Location][2];
					//Test_L=CAN_TEST_RX_BUFFER[Test_Location][3];								
					Test_Radio=((CAN_TEST_RX_BUFFER[Test_Location][2]<<8)|CAN_TEST_RX_BUFFER[Test_Location][3]);
					if((Test_Radio<=0x42cc)&&(Test_Radio>=0x14b4))
					{
						Test_Radio=Test_Radio/10;
						PostMessage(TUNER_MODULE, EVT_TUN_BAND,4);//AM
					}
					else if((Test_Radio<=0x0437)&&(Test_Radio>=0x02f9))
					{
						PostMessage(TUNER_MODULE, EVT_TUN_BAND,1);//FM
						Test_Radio=Test_Radio*10;
					}
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					//CanRxInfo.set_info.set_fre_h=CAN_TEST_RX_BUFFER[Test_Location][2];
					//CanRxInfo.set_info.set_fre_l=CAN_TEST_RX_BUFFER[Test_Location][3];
					PostMessage(TUNER_MODULE, EVT_TUN_FREQ,Test_Radio);//FM
						
				}
				break;

				case 6:// 查询收音频率 已验证
				{
					if(radiostruct_ram.band>2)
					{
						CAN_TEST_TX_BUFFER[Test_Location][3]=((radiostruct_ram.freq*10)>>8); //AM
						CAN_TEST_TX_BUFFER[Test_Location][4]=radiostruct_ram.freq*10; //AM
					}
					else if(radiostruct_ram.band<=2)
					{
						CAN_TEST_TX_BUFFER[Test_Location][4]=radiostruct_ram.freq/10; //FM
						CAN_TEST_TX_BUFFER[Test_Location][3]=((radiostruct_ram.freq/10)>>8); //FM
					}
				}
				break;

				case 7://	设置收音频段 //无频段之分 已验证
				{
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{
						case 0x11:
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,1);//FM
						}
						break;						
						
						case 0x12:
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,4);//AM
						}
						break;						
			
					}	
				}
				break;

				case 8://	查询收音频段 已验证
				{
					if(radiostruct_ram.band<=2)
					{
						CAN_TEST_TX_BUFFER[Test_Location][3]=0x11; 
					}
					else
					{
						CAN_TEST_TX_BUFFER[Test_Location][3]=0x21; 
					}
				}
				break;
						
				case 9://	设置收音寻台 手动seeking 自动scaning 已验证
				{					
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{
						case 0://	Stop Seek
						{
							CanRxInfo.rad_info.byte_0.field.f_set_radio=0;
							Seek_Stop();
						}									
						break;
							
															
						case 1://	Ascending frequency
						{
							if(seek_time==0)
							{
								CanRxInfo.rad_info.byte_0.field.f_set_radio=0x0A;
								seek_time=1;
							}
							else
							{
								Seek_Stop();
								CanRxInfo.rad_info.byte_0.field.f_set_radio=0;
								seek_time=0;
							}
							
						}
						break;
						
						case 2://	Descendig frequency
						{
							if(seek_time==0)
							{
								CanRxInfo.rad_info.byte_0.field.f_set_radio=0x0B;
								seek_time=1;
							}
							else
							{
								Seek_Stop();
								seek_time=0;
							}
						}
						break;
							
					}
				}
				break;

				case 0x0A://	查询收音寻台状态 手动seeking 自动scaning? 已验证
				{
					if(RadioSeekFlag.field.f_seeking)
					{
						CAN_TEST_TX_BUFFER[Test_Location][3]=0x01;
					}
					else 
					{
						CAN_TEST_TX_BUFFER[Test_Location][3]=0;
					}
				}
				break;

				case 0x0B://	设置收音在什么频段寻台  已验证
				{
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{
						case 0x11://	Fill the slot of FM Band
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,2);
						}
						break;
															
						case 0x12://	Fill the slot of AM Band
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,4);
						}
						break;
							
					}
					PostMessage(TUNER_MODULE, EVT_TUN_SCAN,0); 
				}
				break;

				case 0x0C://	Searching radio stations status 查询收台状态 手动seeking 自动scaning
				{
					if(RadioSeekFlag.field.f_scaning)
					{
						CAN_TEST_TX_BUFFER[Test_Location][3]=1;
					}
					else 
					{
						CAN_TEST_TX_BUFFER[Test_Location][3]=0;
					}	
				}
				break;

				case 0x0D://	设置特定台收音存台状态    先跳到特定台再跳到特定频率？ //待确认
				{
					u16 Test_Radio;
					Test_Radio=CAN_TEST_RX_BUFFER[Test_Location][4]|CAN_TEST_RX_BUFFER[Test_Location][5];
					for(i=0;i<4;i++)
					{
						CAN_TEST_TX_BUFFER[Test_Location][i+3]=CAN_TEST_RX_BUFFER[Test_Location][i+2];
					}
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{
						case 0x11:
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,1);//FM
						}
						break;
						
						case 0x12:
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,2);//FM
						}
						break;
						
						case 0x13:
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,1);//FM
						}
						break;
						
						case 0x21:
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,4);//AM
						}
						break;
						
						case 0x22:
						{
							PostMessage(TUNER_MODULE, EVT_TUN_BAND,4);//AM
						}
						break;
					}
					PostMessage(TUNER_MODULE, EVT_TUN_FREQ,Test_Radio);//FM
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;
						
				}
				break;

				case 0x0E://	还原收音特定频段存台 已验证
				{
					Radio_Area=RADIO_DEFAULT_REGION;
					radio_region=Radio_Area;
					PostMessage(TUNER_MODULE,EVT_TUN_AREA,(0x100|radio_region));
					CanRxInfo.test_set_info.order=0x2c;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
						
			}
				
		}
		break;
											
		case 0x32: //蓝牙模式
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{							
				case 1://	设置蓝牙名称
				{
					u8 r_counter=0;
					u8 id=0;
					u8 j=0;
					
					id=CAN_TEST_RX_BUFFER[Test_Location][2];
					r_counter=CAN_TEST_RX_BUFFER[Test_Location][2]-1;
					Test_APP=1;
					send[0]=1;
					send[1]=24;
					for(j=2;j<8;j++)
					{
						send[j+(6*r_counter)]=CAN_TEST_RX_BUFFER[Test_Location][j];
					}
					if(id==4)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEST_BT_INO);
						Test_APP=0;
						for(z=3;z<8;z++)
						{
							CAN_TEST_TX_BUFFER[Test_Location][z]=0xff;
						}						
					}
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;
				}
				break;
						
				case 2://	查询蓝牙名称
				{
					CanRxInfo.test_set_info.order=11;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
									
				case 5://	蓝牙切歌
				{				
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{			
						case 1://	next
						{							
							CanRxInfo.med_info.byte_0.field.f_med_con=0x01;
							CanRxInfo.med_info.byte_0.field.f_med_up=0x01;							
						}
						break;
							
						case 2://	preview
						{
							CanRxInfo.med_info.byte_0.field.f_med_con=0x02;
							CanRxInfo.med_info.byte_0.field.f_med_up=0x01;
						}
						break;
							
					}					
				}
				break;
					
				case 6://	蓝牙音乐播放停止
				{					
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{			
						case 1://	play song
						{
							CanRxInfo.med_info.byte_0.field.f_med_con=0x0d;
							CanRxInfo.med_info.byte_0.field.f_med_up=0x01;
						}
						break;
							
						case 2://	pause song
						{
							CanRxInfo.med_info.byte_0.field.f_med_con=0x0d;
							CanRxInfo.med_info.byte_0.field.f_med_up=0x01;
						}
						break;
							
					}					
				}
				break;
					
				case 7://	蓝牙接听/挂断电话 
				{	
					switch(CAN_TEST_RX_BUFFER[Test_Location][2])
					{			
						case 1://	answer call
						{
							CanRxInfo.tel_info.byte_0.field.f_tel_cmd=0x01;
							CanRxInfo.tel_info.byte_0.field.f_tel_up=0x01;							
						}
						break;
							
						case 2://	hang up call
						{
							CanRxInfo.tel_info.byte_0.field.f_tel_cmd=0x03;
							CanRxInfo.tel_info.byte_0.field.f_tel_up=0x01;
						}
						break;
							
					}
				}
				break;
					
				case 8://	清空蓝牙设备配对储存记录
				{
					CanRxInfo.test_set_info.order=12;
					CanRxInfo.test_set_info.gain=1;
				}
				break;
					
				case 9://	查询蓝牙当前连接的设备名字
				{
					CanRxInfo.test_set_info.order=13;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				case 11://	查询蓝牙MAC地址
				{
					CanRxInfo.test_set_info.order=14;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
	
				case 12://	Activate Bluetooth 是否开启BT
				{
					CanRxInfo.test_set_info.order=0x37;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;

				case 13://	Request Bluetooth state 查询BT是否开启
				{
					CanRxInfo.test_set_info.order=0x38;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
					
			}
		}
		break;
			
		case 0x33://	USB
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://检查USB连接状态
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=CanTxInfo.hu_src_0.byte_1.field.f_usb_con;//	00 no device 01 work normally 
				}
				break;
					
				case 2://检查USB连接类型
				{
					CanRxInfo.test_set_info.order=15;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				case 4://USB 播放暂停
				{
					CanRxInfo.med_info.byte_0.field.f_med_con=0x0d;
					CanRxInfo.med_info.byte_0.field.f_med_up=0x01;
				}
				break;
				
				case 5://USB status request
				{
					CanRxInfo.test_set_info.order=0x34;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
					
			}
					
		}
		break;

		case 0x34://	Ethernet
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				/*case 1://设置互联网MAC地址
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=CanTxInfo.hu_src_0.byte_1.field.f_usb_con;//	00 no device 01 work normally 
				}
				break;*/
					
				case 2://查询互联网MAC地址
				{
					CanRxInfo.test_set_info.order=16;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				/*case 3://设置互联网TCP/IP地址
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=CAN_TEST_RX_BUFFER[Test_Location][3]; //	00 no device  // 01 reading device     folders and songs//02 device read already done //03 playing some file //04 error while playing some file
				}
				break;*/

				case 4://查询互联网TCP/IP地址	
				{
					CanRxInfo.test_set_info.order=17;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				case 5://控制因特网Link 开启或者关闭
				{
					CanRxInfo.test_set_info.order=0x32;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
				
				case 6://查询因特网Link 开启或者关闭
				{
					CanRxInfo.test_set_info.order=0x33;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
					
			}
					
		}
		break;

		case 0x35://	GPS
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://Request HDOP and VDOP 查询HDOP 和 VDOP
				{
					CanRxInfo.test_set_info.order=18;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				case 2://Request latitude and longitude 查询经纬度？
				{
					CanRxInfo.test_set_info.order=19;			
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				case 3://Request Status Fixed State 查询GPS状态？
				{
					CanRxInfo.test_set_info.order=20;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;

				case 4://Request GPGSV 查询GPS试图中SV的个数？
				{
					CanRxInfo.test_set_info.order=21;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;

				case 5://	Request SV PRN Number and SNR 查询SV的PRN号和信噪比？
				{
					CanRxInfo.test_set_info.order=22;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				case 6://	open or close IGO app 设置IGO APP的状态
				{
					CanRxInfo.test_set_info.order=0x3B;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
				
				case 7://	Request IGO app state 查询IGO APP的状态
				{
					CanRxInfo.test_set_info.order=0x3C;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
					
			}				
		}
		break;

		case 0x36://	WIFI 
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				/*case 1://Set Wi-Fi Mac Address 设置wifi MAC地址
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=CanTxInfo.hu_src_0.byte_1.field.f_usb_con;//	00 no device 01 work normally 
				}
				break;*/
					
				case 2://Request Wi-Fi MAC Address 查询wifi MAC地址
				{
					CanRxInfo.test_set_info.order=23;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
				case 3://Set Wi-Fi SSID to connect 设置连接哪个ssid wifi
				{
					send[0]=2;
					send[1]=6;
					for(j=0;j<6;j++)
					{
						send[j+2]=CAN_TEST_RX_BUFFER[Test_Location][j+2];
					}
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEST_BT_INO);
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;
					
				}
				break;

				case 4://Set Wi-Fi Password to connect ssid的wifi密码
				{
					send[0]=3;
					send[1]=6;
					for(j=0;j<6;j++)
					{
						send[j+2]=CAN_TEST_RX_BUFFER[Test_Location][j+2];
					}
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEST_BT_INO);
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;
				}
				break;

				case 5://	Stabilish Wi-Fi connection 设置是否连接上03指定的SSID？
				{
					CanRxInfo.test_set_info.order=24;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;

				case 6://	Request Wi-Fi connection status 查询是否连接上03指定wifi
				{
					CanRxInfo.test_set_info.order=25;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				case 7://	 Wi-Fi  set
				{
					CanRxInfo.test_set_info.order=0x2d;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
				
				case 8://	Wi-Fi sta
				{
					CanRxInfo.test_set_info.order=0x2e;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				case 9://  Wi-Fi 热点 set 
				{
					CanRxInfo.test_set_info.order=0x30;
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
				
				case 10://	Request Wi-Fi 热点 sta
				{
					CanRxInfo.test_set_info.order=0x31;
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;

				default://	
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=0x02;
				}
				break;
					
			}
			
		}
		break;
		
		case 0x41://	面板方控
		{
			CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
			CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
			CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
			CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
			CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;
			
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	模拟面板按键按下
				{
						CanTxAutoTestTimer=CAN_TEST_RX_BUFFER[Test_Location][3]*1000;
					
						switch(CAN_TEST_RX_BUFFER[Test_Location][2])
						{
							case 1:
							{
								Test_Sta_flag=1;
							}
							break;
								
							case 2://voice control
							{
								Test_Sta_flag=2;
							}
							break;
							
							case 3:
							{
								Test_Sta_flag=3;
							}
							break;
							
							case 4:
							{
								Test_Sta_flag=4;
							}
							break;
							
						}
				}
				break;
						 
				case 2://	查询按钮状态 
				{
					CanRxInfo.test_set_info.order=27;
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;		
					CAN_TEST_TX_BUFFER[Test_Location][3]=CAN_TEST_RX_BUFFER[Test_Location][2];//	按钮id			
				}
				break;
				
			}					
		}
		break;
				
		case 0x42: //屏幕显示测试						
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	设置屏幕显示测试模式的开启或关闭
				{
					CanRxInfo.test_set_info.order=28;					
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
						
				case 2:// 查询屏幕显示测试模式是否开启
				{
					CanRxInfo.test_set_info.order=29;					
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;		
				}
				break;
						
				case 3://	设置显示那个图片	
				{
					CanRxInfo.test_set_info.order=30;					
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];					
				}
				break;

				default:
				{
					CAN_TEST_TX_BUFFER[Test_Location][2]=3;
				}
				break;
			}
					
		}
		break;
			
		case 0x43:  //	Steering wheel Control
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	Request SWC analog reading 请求SWC模拟读数
				{
				}
				break;
					
			}							
		}
		break;

		case 0x44:  //	Touch Screen 屏幕触摸测试
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	Set Touch Screen Test mode 开启屏幕触摸测试模式
				{
					CanRxInfo.test_set_info.order=31;					
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;

				case 2://	Request Touch Screen Test mode 查询是否开启了屏幕触摸测试模式
				{
					CanRxInfo.test_set_info.order=32;					
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;		
				}
				break;

				case 3://	Set LCD touch screen test button 设置屏幕触摸测试按钮位置
				{
					CanRxInfo.test_set_info.order=0x21;					
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;

				case 4://	Request LCD touch screen press coordinate
				{
					CanRxInfo.test_set_info.order=0x22;					
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
					Test_APP=1;		
				}
				break;
			}							
		}
		break;
			
		case 0x51: //	查询版本状态
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	查询MCU版本号
				{										
				/*	CanRxInfo.test_set_info.order=0x24;		
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];					
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;			*/
						u8 NUM_EOLVER;
					Test_APP=1;
					NUM_EOLVER=CAN_TEST_RX_BUFFER[Test_Location][2]-1;
					test_send_num=EOL_VER_LOCATION[1][NUM_EOLVER][0]/5;
					data_length=EOL_VER_LOCATION[1][NUM_EOLVER][0];
					for(u8 i=1;i<6;i++)
					{
						test[i-1]=EOL_VER_LOCATION[1][NUM_EOLVER][i];
					}
					Positron_VW_AutoTestSendmessage();
				}
				break;
						
				case 2://	查询build num
				{
				/*	CanRxInfo.test_set_info.order=0x25;		
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];					
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;		*/			
					u8 NUM_EOLVER;
					Test_APP=1;
					NUM_EOLVER=CAN_TEST_RX_BUFFER[Test_Location][2]-1;
					test_send_num=EOL_VER_LOCATION[2][NUM_EOLVER][0]/5;
					data_length=EOL_VER_LOCATION[2][NUM_EOLVER][0];
					for(u8 i=1;i<6;i++)
					{
						test[i-1]=EOL_VER_LOCATION[2][NUM_EOLVER][i];
					}
					Positron_VW_AutoTestSendmessage();		
				}
				break;

				case 3://	查询硬件版本号
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=0;//	MAJOR Ver
					CAN_TEST_TX_BUFFER[Test_Location][4]=0x52;//	MINOR ver	
					CAN_TEST_TX_BUFFER[Test_Location][5]=0x33;//	Patch ver	
				}
				break;
						
				case 4://	设置Mafacturer SW 版本
				{
					CanRxInfo.test_set_info.order=0x26;					
					CanRxInfo.test_set_info.gain=CAN_TEST_RX_BUFFER[Test_Location][2];
				}
				break;
						
				case 5://	查询Mafacturer SW 版本
				{
					CanRxInfo.test_set_info.order=0x27;					
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;		
				}
				break;
				
				default:
					break;
						
			}					
		}
		break;
			
		case 0x52: //	单元号
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	设置单元part号
				{					
					for(j=0;j<5;j++)
					{
						UNIT_Part[j]=CAN_TEST_RX_BUFFER[Test_Location][j+3];
					}
					EEPROM_SaveUNIT_PART();
					//EEPROM_SaveUNIT_PART_Bak();
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;					
				}
				break;
						
				case 2://	查询单元part号
				{
					EEPROM_LoadUNIT_PART();
					for(i=3;i<8;i++)
					{
						CAN_TEST_TX_BUFFER[Test_Location][i]=UNIT_Part[i-3];
					}
				}
				break;
					
				case 3://	设置 单元Serial号
				{					
					for(j=0;j<5;j++)
					{
						UNIT_Serial[j]=CAN_TEST_RX_BUFFER[Test_Location][j+3];
					}
					EEPROM_SaveUNIT_SERIAL();
					//EEPROM_SaveUNIT_PART_Bak();
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;					
				}
				break;
					
				case 4://	查询单元Serial号
				{
					EEPROM_LoadUNIT_SERIAL();
					for(i=3;i<8;i++)
					{
						CAN_TEST_TX_BUFFER[Test_Location][i]=UNIT_Serial[i-3];
					}
				}
				break;
				
				case 5:
				{
					CanRxInfo.test_set_info.order=0x28;		
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];							
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
				
				case 6: //uds model setting
				{
					CanRxInfo.uds_info.byte_1.field.vehc_type=CAN_TEST_RX_BUFFER[Test_Location][2];	
					Uds_set=1;
				}
				break;
				
				case 7: //uds model setting
				{
					CAN_TEST_TX_BUFFER[Test_Location][3]=CanRxInfo.uds_info.byte_1.field.vehc_type;
				}
				break;
			}
					
		}
		break;
			
		case 0x53: // 测试标记
		{
			switch(CAN_TEST_RX_BUFFER[Test_Location][1])
			{
				case 1://	设置测试标记
				{
					send[0]=5;
					send[1]=5;
					
					for(j=0;j<5;j++)
					{
						send[j+2]=CAN_TEST_RX_BUFFER[Test_Location][j+3];
					}					
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEST_BT_INO);
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;
				}
				break;
						
				case 2://	查询测试标记
				{
					CanRxInfo.test_set_info.order=0x29;					
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
						
				case 3://	设置Manufacture 时间轴
				{
					send[0]=6;
					send[1]=6;
					
					for(j=0;j<6;j++)
					{
						send[j+2]=CAN_TEST_RX_BUFFER[Test_Location][j+2];
					}					
					PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,Positron_VW_RX_TEST_BT_INO);
					CAN_TEST_TX_BUFFER[Test_Location][3]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][4]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][5]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][6]=0xff;
					CAN_TEST_TX_BUFFER[Test_Location][7]=0xff;
				}
				break;
					
				case 4://	查询Manufacture 时间轴
				{
					CanRxInfo.test_set_info.order=0x2A;			
					CanRxInfo.test_set_info.minus=CAN_TEST_RX_BUFFER[Test_Location][2];					
					CanRxInfo.test_set_info.gain=1;
					Test_APP=1;
				}
				break;
					
			}
		}
		break;
		
			default:
		break;	
	 }

	for(i=0;i<8;i++)
	{
		if(i==0)
		{
			CanTxInfo.hu_tes_0.pid=CAN_TEST_TX_BUFFER[Test_Location][i];
		}
		else if(i>0)
		{
			CanTxInfo.hu_tes_0.d[i-1]=CAN_TEST_TX_BUFFER[Test_Location][i];
		}
	}
	//for(i=0:i<)
	//Positron_VW_PostMessage(CAN_POST_TEST);			
	
}

void Positron_VW_AutoTestSendmessage(void)
{
	if(test_send_num>1)
	{
		while(test_send_num)
		{	
			switch(test_num)
			{
				case 1: //BT name
				{
					for(i=0;i<5;i++)
					{	
						CanTxInfo.hu_tes_0.d[i+3]=test[data_counter];
						data_counter++;
					}
				}
				break;
				
				case 2://MAC 
				{
					for(i=0;i<4;i++)
					{	
						CanTxInfo.hu_tes_0.d[i+3]=test[data_counter];
						data_counter++;
					}
				}
				break;
				
				case 3://经纬度
				{
					for(i=0;i<6;i++)
					{	
						CanTxInfo.hu_tes_0.d[i+1]=test[data_counter];
						data_counter++;
					}
				}
				break;

				case 4://build num /ver / unit num
				{
					for(i=0;i<5;i++)
					{	
						CanTxInfo.hu_tes_0.d[i+3]=test[data_counter];
						data_counter++;
					}
				}
				break;

				case 5://build num /ver / unit num
				{
					for(i=0;i<3;i++)
					{	
						CanTxInfo.hu_tes_0.d[i+3]=test[data_counter];
						data_counter++;
					}
				}
				break;

				case 6://ver
				{
					CanTxInfo.hu_tes_0.d[2]=send_counter;
					for(i=0;i<4;i++)
					{	
						CanTxInfo.hu_tes_0.d[i+3]=test[data_counter];
						data_counter++;
					}
				}
				break;
			}
			
			
			Positron_VW_PostMessage(CAN_POST_TEST);
					
			
			send_num--;
		}
	
	}
	else
	{
		if(test_num==6)
		{
			for(j=0;j<7;j++)
			{	
				CanTxInfo.hu_tes_0.d[j]=CAN_TEST_TX_BUFFER[Test_Location][j+1];
			}
			CanTxInfo.hu_tes_0.d[2]=CAN_TEST_RX_BUFFER[Test_Location][2]-1;

			for(j=0;j<4;j++)
			{	
				CanTxInfo.hu_tes_0.d[j+3]=ver[(CanTxInfo.hu_tes_0.d[2]*4)+ver_counter];
				ver_counter++;
			}
			
		}
		else
		{
			for(i=0;i<data_length;i++)
			{	
				if(CAN_TEST_RX_BUFFER[Test_Location][0]==0x35&&CAN_TEST_RX_BUFFER[Test_Location][1]==0x02)//gps问题所在点,添加判断有选择性地执行
				{
					CanTxInfo.hu_tes_0.d[i+1]=test[data_counter];
					data_counter++;
				}
				else
				{
					CanTxInfo.hu_tes_0.d[i+2]=test[data_counter];
				  data_counter++;
				}
			}
		}
		
		Positron_VW_PostMessage(CAN_POST_TEST);
	}
	
	for(i=0;i<data_counter;i++)
	{	
		test[i]=0;
		
		if(i<8)
		{
			CanTxInfo.hu_tes_0.d[i]=0;
		}
	}
	
	test_num=0;
	ver_counter=0;
	data_counter=0;	
	send_counter=1;

}
void Positron_VW_UDS_Security()
{
	CanTxInfo.hu_uds_0.d[0]=CanRxInfo.uds_info.length;
	CanTxInfo.hu_uds_0.d[1]=CanRxInfo.uds_info.sid+0x40;
	
	for(i=0;i<6;i++)
	{
		CanTxInfo.hu_uds_0.d[i+2]=CanRxInfo.uds_info.d[i];
	}	
	if(CanRxInfo.uds_info.length==0x10)
	{
		length_over=1;
		byte_num=CanRxInfo.uds_info.sid;
	
		if(CanRxInfo.uds_info.d[0]==0x27)
		{
			for(i=0;i<4;i++)
			{
				r_key[i]=CanRxInfo.uds_info.d[i+2];
			}
			byte_num-=6;
			CanTxInfo.hu_uds_0.d[0]=0x30;
			CanTxInfo.hu_uds_0.d[1]=0x03;
			CanTxInfo.hu_uds_0.d[2]=0x1F;
			
			for(i=3;i<8;i++)
			{
				CanTxInfo.hu_uds_0.d[i]=0;
			}
			Positron_VW_PostMessage(CAN_POST_UDS);
			//Positron_VW_Rx_Message();
		}
		else 
		{
			CanTxInfo.hu_uds_0.d[0]=0x03;
			CanTxInfo.hu_uds_0.d[1]=0x7f;
			CanTxInfo.hu_uds_0.d[2]=CanRxInfo.uds_info.d[0];
			CanTxInfo.hu_uds_0.d[3]=0x31;
			Positron_VW_PostMessage(CAN_POST_UDS);
			seed_time=0;
		}				
	}
	else if(CanRxInfo.uds_info.length==0x21)
	{	
		if(block_size==0)
		{
			seed_time=0;
		}
		bam_flag=0;
		r_key[4]=CanRxInfo.uds_info.sid;
		byte_num--;
		
		for(i=0;i<3;i++)
		{
			r_key[i+5]=CanRxInfo.uds_info.d[i];
		}		
		for(i=0;i<8;i++)
		{
			if(ch_key[i]==r_key[i])
			{
				ser_flag++;
			}
		}
		
		if(ser_flag==0x08)
		{
			if(seed_time)
			{
				CanTxInfo.hu_uds_0.d[0]=2;
				CanTxInfo.hu_uds_0.d[1]=0x67;
				CanTxInfo.hu_uds_0.d[2]=2;
				ser_ag=1;
				
				for(i=0;i<8;i++)
				{
					r_key[i]=0;
					ch_key[i]=0;
					seed[i]=0;
					sta=0;				
					if(i>2)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}		
				}
				Positron_VW_PostMessage(CAN_POST_UDS);
				sta=0;
				ser_flag=0;
				byte_num=0;
				seed_time=0;
			}
			else
			{
				CanTxInfo.hu_uds_0.d[0]=3;
				CanTxInfo.hu_uds_0.d[1]=0x7F;
				CanTxInfo.hu_uds_0.d[2]=0x27;
				CanTxInfo.hu_uds_0.d[3]=0x35;
				
				for(i=0;i<8;i++)
				{
					r_key[i]=0;
					ch_key[i]=0;
					seed[i]=0;
					
					if(i>3)
					{
						CanTxInfo.hu_uds_0.d[i]=0;
					}
				}					
				Positron_VW_PostMessage(CAN_POST_UDS);
				sta=0;
				ser_flag=0;
			}
		}
		else
		{
			CanTxInfo.hu_uds_0.d[0]=3;
			CanTxInfo.hu_uds_0.d[1]=0x7F;
			CanTxInfo.hu_uds_0.d[2]=0x27;
			CanTxInfo.hu_uds_0.d[3]=0x35;
			
			for(i=0;i<8;i++)
			{
				r_key[i]=0;
				ch_key[i]=0;
				seed[i]=0;				
				if(i>3)
				{
					CanTxInfo.hu_uds_0.d[i]=0;
				}
			}
			Positron_VW_PostMessage(CAN_POST_UDS);
			sta=0;
			ser_flag=0;
		}
		seed_time=0;
	}
	else if(CanRxInfo.uds_info.sid!=0x3E)
	{
		CanTxInfo.hu_uds_0.d[0]=0x03;
		CanTxInfo.hu_uds_0.d[1]=0x7f;
		CanTxInfo.hu_uds_0.d[2]=CanRxInfo.uds_info.sid;
		CanTxInfo.hu_uds_0.d[3]=0x31;
		Positron_VW_PostMessage(CAN_POST_UDS);
		seed_time=0;
	}		
}
#endif


