#include "public.h"

#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_TIGGO_5==1||CAN_FUN_CHERY_TIGGO_7==1||CAN_FUN_CHERY_ARRIZO_6==1||CAN_FUN_CHERY_TIGGO_2==1||CAN_FUN_CHERY_ARRIZO_5==1||CAN_FUN_CHERY_TIGGO_5X_T19==1
CAN_RX_BUFFER CanRxBuffer;
CAN_TX_BUFFER CanTxBuffer;
CAN_RX_INFO CanRxInfo;
CAN_RX_INFO CanRxInfoBak;
CAN_TX_INFO CanTxInfo;
CAN_TX_INFO CanTxInfoBak;
AIR_CONDITION_INFO AirConditionInfo;
AIR_CONDITION_INFO AirConditionInfoBak;
CAN_MAIN_STATE CanMainState;
CAN_MAIN_FLAG CanMainFlag;
MEDIA_ID3_INFO Media_ID3_Info;
u32 CanMainTimer;
u32 CanNoDataTimer;
u32 CanOverSpeedTimer;
u32 CanTimeInfoTimer;
u32 CanAirInfoTimer;
u32 CanBaseInfoTimer;
u32 CanTxAppTimer;
u32 CanTxCanTimer;

u32 CanTxAirTimer;
u16 AvmCalibrationTimeout;
u16 AvmCalibrationTimer;
u8 AvmCalibrationFlag;
u8 CanTxTimer;
u8 CanTurnOnVolume;

int CanTimeSyncRec;
int CanTimeSyncRec_Bak;
int RtcTimeSyncRec;

u8 CanTimeSyncDelay;
u8 CanNMmBCM_SendStaus;
u16 CanNMmBCM_TimerCounter;

u8 MediaTxMessage[CAN_TX_BUFFER_MEDIAinfo_LENGTH][8];
u8 Media_tx_num;

u8 Diagnostic_7000_Data[4];
u8 Diagnostic_7010_Data[4];
u8 SeedCode[2];
u8 FictitiousPowerOffFlag;




void Tiggo7_PostMessage(CAN_POST_MESSAGE_INDEX index);

void unicode_to_utf8(u16 *unic, u8 *pOutput, u8 *length)                             
{ 
	*length = 0;

	while(*unic&&(*length)<=40)
	{
		if((*unic)<=0x0000007F) 
		{ 
			// * U-00000000 - U-0000007F:  0xxxxxxx 
			*(pOutput++)=((*unic)&0x7F); 
			(*length)++;
		} 
		else if(((*unic)>=0x00000080)&&((*unic)<=0x000007FF)) 
		{ 
			// * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx 
			*(pOutput++)=(((*unic)>>6)&0x1F)|0xC0; 
			*(pOutput++)=((*unic)&0x3F)|0x80; 
			(*length) += 2;
		} 
		else if (((*unic)>=0x00000800)&&((*unic)<=0x0000FFFF)) 
		{ 
			// * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx 
			*(pOutput++)=(((*unic)>>12)&0x0F)|0xE0; 
			*(pOutput++)=(((*unic)>>6)&0x3F)|0x80;
			*(pOutput++)=((*unic)&0x3F)|0x80; 
			(*length)+=3;
		} 
		unic++;
	}
	if(*unic&&(*length)>=40)		//如果后面还有数据且数据长度大于40后面就设置为...
	{
		*pOutput++=0xE2;
		*pOutput++=0x80;
		*pOutput++=0xA6;			//...
		(*length)+=3;
	}
} 

void Tiggo7_TxMediaInfoPro(void)
{
	u32 i;
	u32 data_length;
	u8 *ptr;

	while(Media_ID3_Info.tx_ready)
	{
		if(Media_ID3_Info.pack_num==0)
		{
			if(Media_ID3_Info.tx_line==0)
			{
				data_length=Media_ID3_Info.text_1_len;
				ptr=&Media_ID3_Info.text_1[0];
			}
			else
			{
				data_length=Media_ID3_Info.text_2_len;
				ptr=&Media_ID3_Info.text_2[0];
			}
#if MODEL==LINUX_Q068_21||MODEL==LINUX_Q068A_21
			if(data_length<=5)
			{
				CanTxInfo.rrm_5_info[0]=data_length+2;
				CanTxInfo.rrm_5_info[1]=0x50+Media_ID3_Info.tx_line;
				CanTxInfo.rrm_5_info[2]=data_length;
				for(i=3;i<8&&data_length;i++,data_length--)
				{
					CanTxInfo.rrm_5_info[i]=*ptr;
					ptr++;
				}
			}
			else
#endif
			{
				CanTxInfo.rrm_5_info[0]=0x10;
				CanTxInfo.rrm_5_info[1]=data_length+2;
				CanTxInfo.rrm_5_info[2]=0x50+Media_ID3_Info.tx_line;
				CanTxInfo.rrm_5_info[3]=data_length;
				for(i=4;i<8&&data_length;i++,data_length--)
				{
					CanTxInfo.rrm_5_info[i]=*ptr;
					ptr++;
				}
			}
		}
		else
		{
			CanTxInfo.rrm_5_info[0]=0x20+Media_ID3_Info.pack_num;
			for(i=1;i<8&&data_length;i++,data_length--)
			{
				CanTxInfo.rrm_5_info[i]=*ptr;
				ptr++;
			}
		}
		for(;i<8;i++)
		{
			CanTxInfo.rrm_5_info[i]=0;
		}
#if CAN_FUN_CHERY_ARRIZO_6==1
        	Mem_strcpy((u8*)&MediaTxMessage[Media_tx_num++][0],CanTxInfo.rrm_5_info,8);
#else
		Tiggo7_PostMessage(CAN_POST_MSG_RRM_5);
#endif		
		Media_ID3_Info.pack_num++;
		if(data_length==0)
		{
			Media_ID3_Info.pack_num=0;
			Media_ID3_Info.tx_line++;
			if(Media_ID3_Info.tx_line>1)
			{
				Media_ID3_Info.tx_ready=0;
				Media_ID3_Info.tx_line=0;
				F_CAN_MEDIA_ALLOW=1;
				Media_tx_num=0;
			}
		}
	}
}

#if CAN_FUN_CHERY_ARRIZO_5==1
void Tiggo7_DiagNostic(CAN_MESSAGE_INFO message)
{
	if(message.Data[0]==0x02
		&&message.Data[1]==0x10
		&&message.Data[2]==0x01)
	{
		CanTxInfo.Msg_Diagnostic[0]=0x02;
		CanTxInfo.Msg_Diagnostic[1]=0x50;
		CanTxInfo.Msg_Diagnostic[2]=0x01;
		CanTxInfo.Msg_Diagnostic[3]=0x00;
		CanTxInfo.Msg_Diagnostic[4]=0x00;
		CanTxInfo.Msg_Diagnostic[5]=0x00;
		CanTxInfo.Msg_Diagnostic[6]=0x00;
		CanTxInfo.Msg_Diagnostic[7]=0x00;
		Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
	}
	else if(message.Data[0]==0x02
		&&message.Data[1]==0x10
		&&message.Data[2]==0x03)
	{
		CanTxInfo.Msg_Diagnostic[0]=0x02;
		CanTxInfo.Msg_Diagnostic[1]=0x50;
		CanTxInfo.Msg_Diagnostic[2]=0x03;
		CanTxInfo.Msg_Diagnostic[3]=0x00;
		CanTxInfo.Msg_Diagnostic[4]=0x00;
		CanTxInfo.Msg_Diagnostic[5]=0x00;
		CanTxInfo.Msg_Diagnostic[6]=0x00;
		CanTxInfo.Msg_Diagnostic[7]=0x00;
		Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
	}
	else if(message.Data[0]==0x02
		&&message.Data[1]==0x11
		&&message.Data[2]==0x01)
	{
		CanTxInfo.Msg_Diagnostic[0]=0x02;
		CanTxInfo.Msg_Diagnostic[1]=0x51;
		CanTxInfo.Msg_Diagnostic[2]=0x01;
		CanTxInfo.Msg_Diagnostic[3]=0x00;
		CanTxInfo.Msg_Diagnostic[4]=0x00;
		CanTxInfo.Msg_Diagnostic[5]=0x00;
		CanTxInfo.Msg_Diagnostic[6]=0x00;
		CanTxInfo.Msg_Diagnostic[7]=0x00;
		Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
	}
	else if(message.Data[0]==0x02
		&&message.Data[1]==0x27
		&&message.Data[2]==0x03)
	{
		SeedCode[0]=0x01;
		SeedCode[1]=0x02;
		CanTxInfo.Msg_Diagnostic[0]=0x04;
		CanTxInfo.Msg_Diagnostic[1]=0x67;
		CanTxInfo.Msg_Diagnostic[2]=0x03;
		CanTxInfo.Msg_Diagnostic[3]=SeedCode[0];
		CanTxInfo.Msg_Diagnostic[4]=SeedCode[1];
		CanTxInfo.Msg_Diagnostic[5]=0x00;
		CanTxInfo.Msg_Diagnostic[6]=0x00;
		CanTxInfo.Msg_Diagnostic[7]=0x00;
		Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
	}
	else if(message.Data[0]==0x04
		&&message.Data[1]==0x27
		&&message.Data[2]==0x04)
	{
		CanTxInfo.Msg_Diagnostic[0]=0x02;
		CanTxInfo.Msg_Diagnostic[1]=0x67;
		CanTxInfo.Msg_Diagnostic[2]=0x04;
		CanTxInfo.Msg_Diagnostic[3]=0x00;
		CanTxInfo.Msg_Diagnostic[4]=0x00;
		CanTxInfo.Msg_Diagnostic[5]=0x00;
		CanTxInfo.Msg_Diagnostic[6]=0x00;
		CanTxInfo.Msg_Diagnostic[7]=0x00;
		Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
	}
	else if(message.Data[0]==0x07
		&&message.Data[1]==0x2E)
	{
		u16 data_id;
		data_id = message.Data[2];
		data_id <<=8;
		data_id |= message.Data[3];
		switch(data_id)
		{
			case 0x7000:
				Diagnostic_7000_Data[0]=message.Data[4];
				Diagnostic_7000_Data[1]=message.Data[5];
				Diagnostic_7000_Data[2]=message.Data[6];
				Diagnostic_7000_Data[3]=message.Data[7];
				CanTxInfo.Msg_Diagnostic[0]=0x03;
				CanTxInfo.Msg_Diagnostic[1]=0x6E;
				CanTxInfo.Msg_Diagnostic[2]=0x70;
				CanTxInfo.Msg_Diagnostic[3]=0x00;
				CanTxInfo.Msg_Diagnostic[4]=0x00;
				CanTxInfo.Msg_Diagnostic[5]=0x00;
				CanTxInfo.Msg_Diagnostic[6]=0x00;
				CanTxInfo.Msg_Diagnostic[7]=0x00;
				Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
				break;
			case 0x7010:
				Diagnostic_7010_Data[0]=message.Data[4];
				Diagnostic_7010_Data[1]=message.Data[5];
				Diagnostic_7010_Data[2]=message.Data[6];
				Diagnostic_7010_Data[3]=message.Data[7];
				CanTxInfo.Msg_Diagnostic[0]=0x03;
				CanTxInfo.Msg_Diagnostic[1]=0x6E;
				CanTxInfo.Msg_Diagnostic[2]=0x70;
				CanTxInfo.Msg_Diagnostic[3]=0x10;
				CanTxInfo.Msg_Diagnostic[4]=0x00;
				CanTxInfo.Msg_Diagnostic[5]=0x00;
				CanTxInfo.Msg_Diagnostic[6]=0x00;
				CanTxInfo.Msg_Diagnostic[7]=0x00;
				Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
				break;
			default:
				break;
		}
	}
	else if(message.Data[0]==0x03
		&&message.Data[1]==0x22)
	{
		u16 data_id;
		data_id = message.Data[2];
		data_id <<=8;
		data_id |= message.Data[3];
		switch(data_id)
		{
			case 0x7000:
				CanTxInfo.Msg_Diagnostic[0]=0x07;
				CanTxInfo.Msg_Diagnostic[1]=0x62;
				CanTxInfo.Msg_Diagnostic[2]=0x70;
				CanTxInfo.Msg_Diagnostic[3]=0x00;
				CanTxInfo.Msg_Diagnostic[4]=Diagnostic_7000_Data[0];
				CanTxInfo.Msg_Diagnostic[5]=Diagnostic_7000_Data[1];
				CanTxInfo.Msg_Diagnostic[6]=Diagnostic_7000_Data[2];
				CanTxInfo.Msg_Diagnostic[7]=Diagnostic_7000_Data[3];
				Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
				break;
			case 0x7010:
				CanTxInfo.Msg_Diagnostic[0]=0x07;
				CanTxInfo.Msg_Diagnostic[1]=0x62;
				CanTxInfo.Msg_Diagnostic[2]=0x70;
				CanTxInfo.Msg_Diagnostic[3]=0x10;
				CanTxInfo.Msg_Diagnostic[4]=Diagnostic_7010_Data[0];
				CanTxInfo.Msg_Diagnostic[5]=Diagnostic_7010_Data[1];
				CanTxInfo.Msg_Diagnostic[6]=Diagnostic_7010_Data[2];
				CanTxInfo.Msg_Diagnostic[7]=Diagnostic_7010_Data[3];
				Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
				break;
			default:
				break;
		}
	}
	else if(message.Data[1]==0x14)
	{
		CanTxInfo.Msg_Diagnostic[0]=0x01;
		CanTxInfo.Msg_Diagnostic[1]=0x54;
		CanTxInfo.Msg_Diagnostic[2]=0x00;
		CanTxInfo.Msg_Diagnostic[3]=0x00;
		CanTxInfo.Msg_Diagnostic[4]=0x00;
		CanTxInfo.Msg_Diagnostic[5]=0x00;
		CanTxInfo.Msg_Diagnostic[6]=0x00;
		CanTxInfo.Msg_Diagnostic[7]=0x00;
		Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
	}
	else if(message.Data[1]==0x19)
	{
		switch(message.Data[2])
		{
			case 0x02:
				CanTxInfo.Msg_Diagnostic[0]=0x03;
				CanTxInfo.Msg_Diagnostic[1]=0x59;
				CanTxInfo.Msg_Diagnostic[2]=0x02;
				CanTxInfo.Msg_Diagnostic[3]=0xFF;
				CanTxInfo.Msg_Diagnostic[4]=0;
				CanTxInfo.Msg_Diagnostic[5]=0;
				CanTxInfo.Msg_Diagnostic[6]=0;
				CanTxInfo.Msg_Diagnostic[7]=0;
				Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
				break;
			case 0x0A:
				CanTxInfo.Msg_Diagnostic[0]=0x03;
				CanTxInfo.Msg_Diagnostic[1]=0x59;
				CanTxInfo.Msg_Diagnostic[2]=0x0A;
				CanTxInfo.Msg_Diagnostic[3]=0xFF;
				CanTxInfo.Msg_Diagnostic[4]=0;
				CanTxInfo.Msg_Diagnostic[5]=0;
				CanTxInfo.Msg_Diagnostic[6]=0;
				CanTxInfo.Msg_Diagnostic[7]=0;
				Tiggo7_PostMessage(CAN_POST_MSG_DIAGNOSTIC);
				break;
			default:
				break;
		}
	}

}
#endif

#if CAN_FUN_CHERY_ARRIZO_6==1
void Tiggo7_TxMedia(void)
{
    if(F_CAN_MEDIA_ALLOW)
    {
        if(MediaTxMessage[Media_tx_num][0]==0x10)
        {
            CAN1_TransBytefraem(CAN_ID_RRM_5,&MediaTxMessage[Media_tx_num][0],8);
            Media_tx_num++;
            F_CAN_MEDIA_ACK=0;
        }
        else
        {
            if(F_CAN_MEDIA_ACK)
            {
                CAN1_TransBytefraem(CAN_ID_RRM_5,&MediaTxMessage[Media_tx_num][0],8);
                Media_tx_num++;
                if(MediaTxMessage[Media_tx_num][0]==0)
                {
                    F_CAN_MEDIA_ALLOW=0;
                    F_CAN_MEDIA_ACK=0;
                    Media_tx_num=0;
                }
            }
        }
    }
}
#endif

u8 Tiggo7_TimerVerify(CAN_MESSAGE_INFO message)
{
    u8 result=1;
    CAN_TIME_INFO TimeInfo={0};

    TimeInfo.hour=message.Data[0];
    TimeInfo.min=message.Data[1];
    
    TimeInfo.sec=(message.Data[2]&0x03);
    TimeInfo.sec<<=4;
    TimeInfo.sec+=((message.Data[3]&0xF0)>>4);
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_ARRIZO_6==1
	if(CanRxInfo.ctrl_feedback_info.cluster_size==1)
	{
		if(TimeInfo.hour<=23&&TimeInfo.min<=59&&TimeInfo.sec<=59)
		{
			result=0;
		}
	}
	else
	{
    TimeInfo.year=(message.Data[6]&0x1F);
    TimeInfo.year<<=2;
    TimeInfo.year+=((message.Data[7]&0xC0)>>6);

    TimeInfo.month=(message.Data[5]&0x01);
    TimeInfo.month<<=3;
    TimeInfo.month+=((message.Data[6]&0xE0)>>5);

    TimeInfo.day=((message.Data[5]&0x3E)>>1);

    if(TimeInfo.hour<=23
        &&TimeInfo.min<=59
        &&TimeInfo.sec<=59
        &&TimeInfo.year<127
        &&(TimeInfo.month<=12&&TimeInfo.month>=1)
        &&(TimeInfo.day<=31&&TimeInfo.day>=1))
    {
        result=0;
		}
    }
#else
    if(TimeInfo.hour<=23&&TimeInfo.min<=59&&TimeInfo.sec<=59)
    {
        result=0;
    }
#endif
    return result;
}

void Tiggo7_PostMessage(CAN_POST_MESSAGE_INDEX index)
{
	u8 data[8];
	
	switch(index)
	{
		case CAN_POST_MSG_RRM_1:
#if CAN_FUN_CHERY_ARRIZO_5==1
			data[0]=CanTxInfo.rrm_1_info.byte_1.byte;
			data[1]=CanTxInfo.rrm_1_info.byte_2.byte;
			data[2]=CanTxInfo.rrm_1_info.byte_3.byte;
			data[3]=CanTxInfo.rrm_1_info.reserved_4;
			CAN1_TxFrame(CAN_ID_RRM_1,data,4);
#else
			data[0]=CanTxInfo.rrm_1_info.byte_1.byte;
			data[1]=CanTxInfo.rrm_1_info.byte_2.byte;
			data[2]=MSB(CanTxInfo.rrm_1_info.byte_34.word);
			data[3]=LSB(CanTxInfo.rrm_1_info.byte_34.word);
			data[4]=CanTxInfo.rrm_1_info.reserved_5;
			data[5]=CanTxInfo.rrm_1_info.reserved_6;
			data[6]=CanTxInfo.rrm_1_info.reserved_7;
			data[7]=CanTxInfo.rrm_1_info.byte_8.byte;
			CAN1_TxFrame(CAN_ID_RRM_1,data,8);
#endif
			
			break;
		case CAN_POST_MSG_RRM_2:
			data[0]=CanTxInfo.rrm_2_info.byte_1.byte;
			data[1]=CanTxInfo.rrm_2_info.frequence_fm_h;
			data[2]=CanTxInfo.rrm_2_info.frequence_fm_l;
			data[3]=CanTxInfo.rrm_2_info.frequence_am_h;
			data[4]=CanTxInfo.rrm_2_info.frequence_am_l;
			data[5]=CanTxInfo.rrm_2_info.volume;
#if CAN_FUN_CHERY_ARRIZO_6==1
            data[6]=CanTxInfo.rrm_2_info.byte_8.byte;
            data[7]=CanTxInfo.rrm_2_info.reserved_7;
#else
            data[6]=CanTxInfo.rrm_2_info.reserved_7;
            data[7]=CanTxInfo.rrm_2_info.byte_8.byte;
#endif
			CAN1_TxFrame(CAN_ID_RRM_2,data,8);
			break;
		case CAN_POST_MSG_RRM_3:
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_ARRIZO_6==1||MODEL==LINUX_Q068A_21
			data[0]=CanTxInfo.rrm_3_info.hour;
			data[1]=CanTxInfo.rrm_3_info.min;
			data[2]=CanTxInfo.rrm_3_info.instrument_back_light;
			data[3]=CanTxInfo.rrm_3_info.second;
			data[4]=CanTxInfo.rrm_3_info.reserved_5;
			data[5]=MSB(CanTxInfo.rrm_3_info.byte_67.word);
			data[6]=LSB(CanTxInfo.rrm_3_info.byte_67.word);
			data[7]=CanTxInfo.rrm_3_info.reserved_8;
			CAN1_TxFrame(CAN_ID_RRM_3,data,8);
#else
			data[0]=CanTxInfo.rrm_3_info.hour;
			data[1]=CanTxInfo.rrm_3_info.min;
			data[2]=CanTxInfo.rrm_3_info.instrument_back_light;
			data[3]=CanTxInfo.rrm_3_info.second;
			CAN1_TxFrame(CAN_ID_RRM_3,data,4);
#endif
			break;
		case CAN_POST_MSG_RRM_4:		
#if CAN_FUN_CHERY_TIGGO_3==1
			data[0]=CanTxInfo.rrm_4_info.byte_1.byte;
			data[1]=MSB(CanTxInfo.rrm_4_info.byte_23.word);
			data[2]=LSB(CanTxInfo.rrm_4_info.byte_23.word);
			data[3]=CanTxInfo.rrm_4_info.reserved_4;
			data[4]=CanTxInfo.rrm_4_info.reserved_5;
			data[5]=CanTxInfo.rrm_4_info.byte_6.byte;
			data[6]=CanTxInfo.rrm_4_info.reserved_7;
			data[7]=CanTxInfo.rrm_4_info.reserved_8;
			CAN1_TxFrame(CAN_ID_RRM_4,data,8);
#elif CAN_FUN_CHERY_ARRIZO_6==1
			data[0]=CanTxInfo.rrm_4_info.byte_1.byte;
			data[1]=CanTxInfo.rrm_4_info.byte_2.byte;
			data[2]=CanTxInfo.rrm_4_info.byte_3.byte;
			data[3]=CanTxInfo.rrm_4_info.reserved_4;
			data[4]=CanTxInfo.rrm_4_info.byte_5.byte;
			data[5]=CanTxInfo.rrm_4_info.reserved_6;
			CAN1_TxFrame(CAN_ID_RRM_4,data,5);//
#else
			data[0]=CanTxInfo.rrm_4_info.byte_1.byte;
			data[1]=MSB(CanTxInfo.rrm_4_info.byte_23.word);
			data[2]=LSB(CanTxInfo.rrm_4_info.byte_23.word);
			data[3]=MSB(CanTxInfo.rrm_4_info.byte_45.word);
			data[4]=LSB(CanTxInfo.rrm_4_info.byte_45.word);
			CAN1_TxFrame(CAN_ID_RRM_4,data,5);
#endif
			break;
		case CAN_POST_MSG_RRM_5:
			data[0]=CanTxInfo.rrm_5_info[0];
			data[1]=CanTxInfo.rrm_5_info[1];
			data[2]=CanTxInfo.rrm_5_info[2];
			data[3]=CanTxInfo.rrm_5_info[3];
			data[4]=CanTxInfo.rrm_5_info[4];
			data[5]=CanTxInfo.rrm_5_info[5];
			data[6]=CanTxInfo.rrm_5_info[6];
			data[7]=CanTxInfo.rrm_5_info[7];
			CAN1_TxFrame(CAN_ID_RRM_5,data,8);
			break;
		case CAN_POST_MSG_RRM_6:
			data[0]=CanTxInfo.rrm_6_info.coordinate_x_h;
			data[1]=CanTxInfo.rrm_6_info.coordinate_x_l;
			data[2]=CanTxInfo.rrm_6_info.coordinate_y_h;
			data[3]=CanTxInfo.rrm_6_info.coordinate_y_l;
			data[4]=CanTxInfo.rrm_6_info.byte_5.byte;
			data[5]=CanTxInfo.rrm_6_info.byte_6.byte;
			data[6]=CanTxInfo.rrm_6_info.byte_7.byte;
			data[7]=CanTxInfo.rrm_6_info.reserved_8;
			CAN1_TxFrame(CAN_ID_RRM_6,data,8);
			break;
		case CAN_POST_MSG_RRM_7:
			data[0]=CanTxInfo.rrm_7_info.reserved_1;
			data[1]=CanTxInfo.rrm_7_info.byte_2.byte;
			data[2]=CanTxInfo.rrm_7_info.reserved_3;
			data[3]=CanTxInfo.rrm_7_info.reserved_4;
			data[4]=CanTxInfo.rrm_7_info.reserved_5;
			data[5]=CanTxInfo.rrm_7_info.reserved_6;
			data[6]=CanTxInfo.rrm_7_info.reserved_7;
			data[7]=CanTxInfo.rrm_7_info.byte_8.byte;
			CAN1_TxFrame(CAN_ID_RRM_7,data,8);
			break;
		case CAN_POST_MSG_RRM_9:
			data[0]=CanTxInfo.rrm_9_info.byte_1.byte;
			data[1]=CanTxInfo.rrm_9_info.byte_2.byte;
			data[2]=CanTxInfo.rrm_9_info.byte_3.byte;
			data[3]=CanTxInfo.rrm_9_info.reserved_4;
			data[4]=CanTxInfo.rrm_9_info.reserved_5;
			data[5]=CanTxInfo.rrm_9_info.reserved_6;
			data[6]=CanTxInfo.rrm_9_info.reserved_7;
			data[7]=CanTxInfo.rrm_9_info.byte_8.byte;
			CAN1_TxFrame(CAN_ID_RRM_9,data,8);
			break;
		case CAN_POST_MSG_NMM_RRM:
			data[0]=CanTxInfo.nmm_rrm_info.state;
			data[1]=CanTxInfo.nmm_rrm_info.counter;
			CAN1_TxFrame(CAN_ID_NMm_RRM,data,2);
			break;
#if CAN_FUN_CHERY_ARRIZO_5==1	
		case CAN_POST_MSG_DIAGNOSTIC:
			data[0]=CanTxInfo.Msg_Diagnostic[0];
			data[1]=CanTxInfo.Msg_Diagnostic[1];
			data[2]=CanTxInfo.Msg_Diagnostic[2];
			data[3]=CanTxInfo.Msg_Diagnostic[3];
			data[4]=CanTxInfo.Msg_Diagnostic[4];
			data[5]=CanTxInfo.Msg_Diagnostic[5];
			data[6]=CanTxInfo.Msg_Diagnostic[6];
			data[7]=CanTxInfo.Msg_Diagnostic[7];
			CAN1_TxFrame(CAN_ID_DIAGNOSTIC_TX_ID,data,8);
			break;
#endif			
		default:
			break;
	}
}

void Tiggo7_Rx_Message(void)
{
	if(CanRxBuffer.head!=CanRxBuffer.tail)
	{
		CAN_MESSAGE_INFO message;

		message=CanRxBuffer.message[CanRxBuffer.head];
		CanRxBuffer.message[CanRxBuffer.head].ID=0;
		CanRxBuffer.head=(CanRxBuffer.head+1)%CAN_RX_BUFFER_LENGTH;
		
		switch(message.ID)
		{
			case CAN_ID_BCM_4:
				CanRxInfo.ctrl_feedback_info.enable_flag1.byte=0xFF;
				CanRxInfo.ctrl_feedback_info.enable_flag2.field.f_back_light=0x01;

				if(((message.Data[6]&0x60)>>5)==0x00)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_remote_lock_feedback=0x02;
				}
				else if(((message.Data[6]&0x60)>>5)==0x01)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_remote_lock_feedback=0x00;
				}
				else if(((message.Data[6]&0x60)>>5)==0x02)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_remote_lock_feedback=0x01;
				}

#if CAN_FUN_CHERY_ARRIZO_5==1
				if((message.Data[6])&0x01)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.F_Urgency_Brake_Warning = 1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.F_Urgency_Brake_Warning = 0;
				}
#endif
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_ARRIZO_5==1
				if(((message.Data[0]&0x60)>>5)==2
					||((message.Data[0]&0x60)>>5)==3)
				{
					CanRxInfo.base_info.byte_1.field.f_reverse=((message.Data[4]&0x08)>>3);
				}
				else
				{
					CanRxInfo.base_info.byte_1.field.f_reverse=0;
				}
#else
				CanRxInfo.base_info.byte_1.field.f_reverse=((message.Data[4]&0x08)>>3);
#endif
				CanGeneralCtrlFlag.field.reverse_on_off=CanRxInfo.base_info.byte_1.field.f_reverse;

				if(((message.Data[0]&0x60)>>5)==0x00)	
				{
					CanRxInfo.base_info.byte_1.field.f_acc=0;
				}
				else
				{
					CanRxInfo.base_info.byte_1.field.f_acc=1;
				}

				if(message.Data[1]&0x08)	
				{
					CanRxInfo.base_info.byte_1.field.f_illumi=1;
				}
				else
				{
					CanRxInfo.base_info.byte_1.field.f_illumi=0;
				}
				CanGeneralCtrlFlag.field.ill_onoff=CanRxInfo.base_info.byte_1.field.f_illumi;

				if(((message.Data[2]&0x01)&&(message.Data[2]&0x02))
					||(CanRxInfo.drive_info.speed>MAX_SIDE_VIEW_SPEED))
				{
					CanRxInfo.avm_info.left_camera_state=0;
					CanRxInfo.avm_info.right_camera_state=0;
				}
				else if ((message.Data[2]&0x01)&&(CanRxInfo.ctrl_feedback_info.byte_3.field.f_side_view))		
				{
					CanRxInfo.avm_info.left_camera_state=1;
					CanRxInfo.avm_info.right_camera_state=0;
				}
				else if((message.Data[2]&0x02)&&(CanRxInfo.ctrl_feedback_info.byte_3.field.f_side_view))	
				{
					CanRxInfo.avm_info.left_camera_state=0;
					CanRxInfo.avm_info.right_camera_state=1;
				}
				else
				{
					CanRxInfo.avm_info.left_camera_state=0;
					CanRxInfo.avm_info.right_camera_state=0;
				}

				if(message.Data[3]&0x01)
				{
					CanRxInfo.detail_info.byte_3.field.f_driver_door=1;
					F_DRIVER_DOOR_STATE=1;
				}
				else
				{
					CanRxInfo.detail_info.byte_3.field.f_driver_door=0;
					F_DRIVER_DOOR_STATE=0;
				}

#if CAN_FUN_CHERY_TIGGO_3==1
				if(message.Data[0]&0x10)
				{
					CanRxInfo.base_info.byte_1.field.f_light_detect=0;
				}
				else
				{
					CanRxInfo.base_info.byte_1.field.f_light_detect=1;
				}
				if(message.Data[0]&0x80)
				{
					CanRxInfo.ctrl_feedback_info.byte_5.field.f_fg_heat=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_5.field.f_fg_heat=0;
				}

				if(message.Data[7]&0x04)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_drl=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_drl=0;
				}

				if(message.Data[7]&0x01)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_auto_lock=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_auto_lock=0;
				}
				
				if(message.Data[7]&0x02)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_head_light_delay=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_head_light_delay=0;
				}

				if(message.Data[7]&0x80)
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_mirror_auto_fold=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_mirror_auto_fold=0;
				}	
#elif CAN_FUN_CHERY_ARRIZO_6==1
				if(message.Data[7]&0x01)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_auto_lock=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_auto_lock=0;
				}

				if(message.Data[7]&0x02)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_head_light_delay=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_head_light_delay=0;
				}

				if(message.Data[7]&0x04)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_drl= 1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_drl=0;
				}
				
				if(message.Data[7]&0x80)
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_mirror_auto_fold=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_mirror_auto_fold=0;
				}	
#else
#if MODEL==LINUX_Q068A_21
				if(message.Data[7]&0x04)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_drl=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_drl=0;
				}
				if(message.Data[7]&0x02)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_head_light_delay=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_head_light_delay=0;
				}
				if(message.Data[7]&0x80)
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_mirror_auto_fold=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_mirror_auto_fold=0;
				}
#else
				if(message.Data[7]&0x04)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_drl=0;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_drl=1;
				}


				if(message.Data[7]&0x02)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_head_light_delay=0;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_head_light_delay=1;
				}

				if(message.Data[7]&0x80)
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_mirror_auto_fold=0;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_mirror_auto_fold=1;
				}
#endif	
				if(message.Data[7]&0x01)
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_auto_lock=0;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.byte_3.field.f_auto_lock=1;
				}			
#endif
				break;
			case CAN_ID_BCM_5:
				CanRxInfo.tpms_info.system_fail_status=((message.Data[0]&0x80)>>7);
				CanRxInfo.tpms_info.warning_lamp_status=((message.Data[0]&0x30)>>4);
				CanRxInfo.tpms_info.left_front_warning=((message.Data[0]&0x0E)>>1);
				CanRxInfo.tpms_info.right_front_warning=(((message.Data[1]&0xC0)>>6)|((message.Data[0]&0x01)<<2));
				CanRxInfo.tpms_info.left_rear_warning=((message.Data[1]&0x38)>>3);
				CanRxInfo.tpms_info.right_rear_warning=(message.Data[1]&0x07);
				if(0x00==(message.Data[2]&0x03))
				{
					CanRxInfo.tpms_info.byte_7.field.f_left_front=1;
					CanRxInfo.tpms_info.left_front_temperature=message.Data[3];
				}
				else if(0x01==(message.Data[2]&0x03))
				{
					CanRxInfo.tpms_info.byte_7.field.f_right_front=1;
					CanRxInfo.tpms_info.right_front_temperature=message.Data[3];
				}
				else if(0x02==(message.Data[2]&0x03))
				{
					CanRxInfo.tpms_info.byte_7.field.f_left_rear=1;
					CanRxInfo.tpms_info.left_rear_temperature=message.Data[3];
				}
				else
				{
					CanRxInfo.tpms_info.byte_7.field.f_right_rear=1;
					CanRxInfo.tpms_info.right_rear_temperature=message.Data[3];
				}
				CanRxInfo.tpms_info.left_front_pressure=message.Data[4];
				CanRxInfo.tpms_info.right_front_pressure=message.Data[5];
				CanRxInfo.tpms_info.left_rear_pressure=message.Data[6];
				CanRxInfo.tpms_info.right_rear_pressure=message.Data[7];
				break;
			case CAN_ID_BCM_10:         
				if(3==(message.Data[0]&0x03))         
					{ 
						
					if(0x2==(message.Data[1]&0x2))            
						{             
						CanRxInfo.ctrl_feedback_info.cluster_size=0;
				    }           
					else
						{             
						CanRxInfo.ctrl_feedback_info.cluster_size=1;
						}
					}         
				break;	
			case CAN_ID_ICM_1:
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_ARRIZO_6==1
				CanRxInfo.drive_info.fuel_level=message.Data[4];
				CanRxInfo.drive_info.total_odometer=(message.Data[5]&0x0F);
				CanRxInfo.drive_info.total_odometer <<=8;
				CanRxInfo.drive_info.total_odometer+=message.Data[6];
				CanRxInfo.drive_info.total_odometer <<=8;
				CanRxInfo.drive_info.total_odometer+=message.Data[7];
#endif
				break;
			case CAN_ID_ICM_2:	
				if(CanOverSpeedTimer==0)
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_over_speed=((message.Data[3])&0xFC)>>2;
				}
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_ARRIZO_6==1
				CanRxInfo.drive_info.average_fuel_consumption=message.Data[0];
#endif				
				break;
			case CAN_ID_ICM_3:
				CanRxInfo.ctrl_feedback_info.byte_5.field.f_instrument_backlight=(message.Data[3]&0x0F);
				if(Tiggo7_TimerVerify(message))
				{
					break;
				}
				CanRxInfo.time_info.hour=message.Data[0];
				CanRxInfo.time_info.min=message.Data[1];

				CanRxInfo.time_info.sec=(message.Data[2]&0x03);
				CanRxInfo.time_info.sec<<=4;
				CanRxInfo.time_info.sec+=((message.Data[3]&0xF0)>>4);

				if(CanTimeInfoTimer)
				{
					break;
				}
				if(CanTimeSyncDelay)
				{
					CanTimeSyncDelay--;
				}
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_ARRIZO_6==1||MODEL==LINUX_Q068A_21
				if(message.Data[2]&0x04)
				{
					CanRxInfo.drive_info.byte_3.field.f_low_fuel_warning=1;
				}
				else
				{
					CanRxInfo.drive_info.byte_3.field.f_low_fuel_warning=0;
				}
				if(message.DLC==4)
				{
				    break;
				}
				
				if(CanRxInfo.ctrl_feedback_info.cluster_size==0)
				{
				CanRxInfo.time_info.year=(message.Data[6]&0x1F);
				CanRxInfo.time_info.year<<=2;
				CanRxInfo.time_info.year+=((message.Data[7]&0xC0)>>6);
				
				CanRxInfo.time_info.month=(message.Data[5]&0x01);
				CanRxInfo.time_info.month<<=3;
				CanRxInfo.time_info.month+=((message.Data[6]&0xE0)>>5);
				
				CanRxInfo.time_info.day=((message.Data[5]&0x3E)>>1);

								
						     
					      
				}
				else
				{
					CanRxInfo.time_info.year=0;
					CanRxInfo.time_info.month=1;
					CanRxInfo.time_info.day=1;
				}
				
				
				

				if(CanRxInfo.time_info.hour!=RTC_TimeInfo.hours
					||CanRxInfo.time_info.min!=RTC_TimeInfo.minutes
					||CanRxInfo.time_info.year!=RTC_TimeInfo.year
					||CanRxInfo.time_info.month!=RTC_TimeInfo.month
					||CanRxInfo.time_info.day!=RTC_TimeInfo.day)
				{
					RTC_TimeInfo.year=CanRxInfo.time_info.year;
					RTC_TimeInfo.month=CanRxInfo.time_info.month;
					RTC_TimeInfo.day=CanRxInfo.time_info.day;
					RTC_TimeInfo.hours=CanRxInfo.time_info.hour;
					RTC_TimeInfo.minutes=CanRxInfo.time_info.min;
					RTC_TimeInfo.seconds = CanRxInfo.time_info.sec;
#if RTC_TIMER_FUN==1
					RTC_SetTime(RTC_TimeInfo);
#endif
					PostMessage(NAVI_MODULE, MCU_TX_CLOCK,0);
				}
#elif CAN_FUN_CHERY_TIGGO_2==1
				if(CanRxInfo.time_info.hour!=RTC_TimeInfo.hours
					||CanRxInfo.time_info.min!=RTC_TimeInfo.minutes)
				{
					RTC_TimeInfo.hours=CanRxInfo.time_info.hour;
					RTC_TimeInfo.minutes=CanRxInfo.time_info.min;
					RTC_TimeInfo.seconds = CanRxInfo.time_info.sec;
#if RTC_TIMER_FUN==1
					RTC_SetTime(RTC_TimeInfo);
#endif
					PostMessage(NAVI_MODULE, MCU_TX_CLOCK,0);
				}
#else
				CanTimeSyncRec=CanRxInfo.time_info.hour*60*60+CanRxInfo.time_info.min*60+CanRxInfo.time_info.sec;
				
				if(F_RTC_READ_STATUS==1
					&&nPowerState==POWER_NORMAL_RUN
					&&CanTimeInfoTimer==0
					&&CanTimeSyncDelay==0)
				{
					RtcTimeSyncRec=RTC_TimeInfo.hours*60*60+RTC_TimeInfo.minutes*60+RTC_TimeInfo.seconds;
					if(abs(CanTimeSyncRec-CanTimeSyncRec_Bak)<=1||abs(CanTimeSyncRec-CanTimeSyncRec_Bak)>=86399)
					{
						if(abs(RtcTimeSyncRec-CanTimeSyncRec)>5&&abs(RtcTimeSyncRec-CanTimeSyncRec)<86395)
						{
							CanTxInfo.rrm_3_info.hour=RTC_TimeInfo.hours;
							CanTxInfo.rrm_3_info.min=RTC_TimeInfo.minutes;
							CanTxInfo.rrm_3_info.second=RTC_TimeInfo.seconds;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_3);
							CanTxInfo.rrm_3_info.hour=0xFF;
							CanTxInfo.rrm_3_info.min=0xFF;
							CanTxInfo.rrm_3_info.second=0xFF;
							CanTimeInfoTimer=T2S_1;
							CanTimeSyncDelay=4;
						}
					}
					else
					{
						//设置时间
						RTC_TimeInfo.hours=CanRxInfo.time_info.hour;
						RTC_TimeInfo.minutes=CanRxInfo.time_info.min;
						RTC_TimeInfo.seconds = CanRxInfo.time_info.sec;
#if RTC_TIMER_FUN==1
						RTC_SetTime(RTC_TimeInfo);
#endif
						PostMessage(NAVI_MODULE, MCU_TX_CLOCK,0);
					}
				
				}
				CanTimeSyncRec_Bak=CanTimeSyncRec;
#endif
				break;
			case CAN_ID_BCM_ABS_G:
				CanRxInfo.drive_info.speed=(message.Data[1]&0x1F);
				CanRxInfo.drive_info.speed<<=8;
				CanRxInfo.drive_info.speed|=message.Data[2];
				CanRxInfo.drive_info.speed/=16;
#if 0//MODEL==LINUX_Q068_21||MODEL==LINUX_Q068A_21
#else
				if(CanRxInfo.drive_info.speed>MAX_PARKING_SPEED)
				{
					CanRxInfo.base_info.byte_1.field.f_parking=0;
				}
				else
				{
					CanRxInfo.base_info.byte_1.field.f_parking=1;
				}
				if(CanRxInfo.base_info.byte_1.field.f_parking)
				{
					CanGeneralCtrlFlag.field.parking_on_off=1;
				}
				else
				{
					CanGeneralCtrlFlag.field.parking_on_off=0;
				}
#endif
				if(CanRxInfo.drive_info.speed>MAX_SIDE_VIEW_SPEED)
				{
					CanRxInfo.avm_info.left_camera_state=0;
					CanRxInfo.avm_info.right_camera_state=0;
				}
				if(CanRxInfo.drive_info.speed>MAX_AVM_SPEED)
				{
					CanRxInfo.avm_info.avm_state=0;
				}
				break;
#if CAN_FUN_CHERY_ARRIZO_5==1
			case CAN_ID_BCM_SAM_2_G:
#else
			case CAN_ID_BCM_SAM_1_G:
#endif			
				if(CanRxInfo.base_info.byte_1.field.f_reverse)
				{
					u16 temp_old;
					u16 temp_now;
					u16 index_old;
					u16 index_now;

					temp_old=CanRxInfo.base_info.swa_msb;
					temp_old<<=8;
					temp_old+=CanRxInfo.base_info.swa_lsb;

					CanRxInfo.base_info.swa_msb=message.Data[0];
					CanRxInfo.base_info.swa_lsb=message.Data[1];
				
					temp_now=CanRxInfo.base_info.swa_msb;
					temp_now<<=8;
					temp_now+=CanRxInfo.base_info.swa_lsb;

					if(temp_old>=0xA1C0)
					{
						index_old=23;
					}
					else if(temp_old>0x8000)
					{
						index_old=((23*(temp_old-0x8000))/(0xA1C0-0x8000));
					}
					else if(temp_old==0x8000)
					{
						index_old=0;
					}
					else if(temp_old>0x5E40)
					{
						index_old=24+((23*(0x8000-temp_old))/(0x8000-0x5E40));
					}
					else
					{
						index_old=46;
					}

					if(temp_now>=0xA1C0)
					{
						index_now=23;
					}
					else if(temp_now>0x8000)
					{
						index_now=((23*(temp_now-0x8000))/(0xA1C0-0x8000));
					}
					else if(temp_now==0x8000)
					{
						index_now=0;
					}
					else if(temp_now>0x5E40)
					{
						index_now=24+((23*(0x8000-temp_now))/(0x8000-0x5E40));
					}
					else
					{
						index_now=46;
					}
					
					if(index_now!=index_old)
					{
						if(CanBaseInfoTimer==0)
						{
							PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_BASIC_INFO);
							CanBaseInfoTimer=T500MS_1;
						}
						else
						{
							CanRxInfo.base_info.swa_msb=0x80;
							CanRxInfo.base_info.swa_lsb=0x00;
						}
					}
				}
				break;
			case CAN_ID_NMm_BCM:
				F_CAN_READY=1; 	
				if((message.Data[0]&0x03)==0x03||(message.Data[0]&0x03)==0x01)
				{	
					CanTxInfo.nmm_rrm_info.state=message.Data[0]&0x03;
					CanTxInfo.nmm_rrm_info.counter=(message.Data[1]&0x8F);
					CanNMmBCM_SendStaus=1;
					CanNMmBCM_TimerCounter=T1S5_1;
					Tiggo7_PostMessage(CAN_POST_MSG_NMM_RRM);
                }
				else
				{
				    CanNMmBCM_SendStaus=0;
				}
				break;
			case CAN_ID_CLM_2:
				{
#if CAN_FUN_CHERY_TIGGO_5==1
					CanRxInfo.air_info.out_temperature=message.Data[6];
#elif CAN_FUN_CHERY_TIGGO_3==1
					u8 temp1=0;
					u8 temp2=0;
					if((message.Data[2]&0x01)==0)
					{
						temp1=message.Data[3];
						if(temp1<30)
						{
							temp1=30;
						}
						temp1=temp1/2+73;
					}
					
					if((message.Data[4]&0x03)==0)
					{
						temp2=message.Data[6];
						temp2=temp2/2+73+15;
					}
					if(temp1)
					{
						CanRxInfo.air_info.out_temperature=temp1;
					}
					else if(temp2)
					{
						CanRxInfo.air_info.out_temperature=temp2;
					}
					else
					{
						CanRxInfo.air_info.out_temperature=0;
					}
					CanRxInfo.air_info.byte_4.field.f_filter_change=((message.Data[0]&0x20)>>5);
#endif
				}
				break;
			case CAN_ID_AVM_1:
				CanRxInfo.ctrl_feedback_info.byte_3.field.f_side_view=((message.Data[0])&0x20)>>5;
				CanRxInfo.ctrl_feedback_info.byte_3.field.f_3d_around_view=((message.Data[1])&0x01);
				if(((message.Data[0]&0xC0)>>6)==0x00) 
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_trajectory=0x00;
				}
				else if(((message.Data[0]&0xC0)>>6)==0x02)
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_trajectory=0x01;
				}
				else if(((message.Data[0]&0xC0)>>6)==0x01)
				{
					CanRxInfo.ctrl_feedback_info.byte_4.field.f_trajectory=0x02;
				}

				if(CanRxInfo.avm_info.avm_state
					&&((message.Data[0]&0x01)==0x00))
				{
					F_AVM_CALIBRATION=0;
				}
				if((message.Data[0]&0x01)==0x01)
				{
					CanRxInfo.avm_info.avm_state=1;
					CanGeneralCtrlFlag.field.camera_on_off=1;
					CanRxInfo.avm_info.left_camera_state=0;
					CanRxInfo.avm_info.right_camera_state=0;
				}
				else
				{
					CanRxInfo.avm_info.avm_state=0;
					CanGeneralCtrlFlag.field.camera_on_off=0;
					CanRxInfo.avm_info.left_camera_state=0;
					CanRxInfo.avm_info.right_camera_state=0;
				}
				CanRxInfo.avm_info.camera_view_state=((message.Data[1]&0x06)>>1);
				CanRxInfo.avm_info.avm_exist=1;
				break;
			case CAN_ID_IPM_1:
			    if(DisableKeyProFlag==1)
			    {
			        break;
			    }
				if(message.Data[0]&0x03)
				{
					if((message.Data[0]&0x03)==0x01)
					{
						PostKeyCode(SYSTEM_POWER_OFF_KEY,PANEL);
					}
				}
				if(message.Data[0]&0x0C)
				{	
					if(((message.Data[0]&0x0C)>>2)==0x01)
					{
						PostKeyCode(UICC_HOME,PANEL);
					}
					AvmCalibrationFlag|=0x01;
					AvmCalibrationTimeout=T300MS_1;
				}
				if(message.Data[0]&0x30)
				{
					if(((message.Data[0]&0x30)>>4)==0x01)
					{
						PostKeyCode(UICC_SETUP,PANEL);
					}
					AvmCalibrationFlag|=0x02;
					AvmCalibrationTimeout=T300MS_1;
				}
				if(message.Data[1]&0x03)
				{	
					if((message.Data[1]&0x03)==0x01)
					{
						PostKeyCode(UICC_BT,PANEL);
					}
					AvmCalibrationFlag|=0x04;
					AvmCalibrationTimeout=T300MS_1;
				}
				
				if(AvmCalibrationFlag==0x07)
				{
					F_AVM_CALIBRATION=1;
					CanTxInfo.rrm_6_info.byte_5.field.f_calibration_req=0x01;
					AvmCalibrationTimer=T300MS_1;
					AvmCalibrationFlag=0;
					AvmCalibrationTimeout=0;
				}
				
				if(message.Data[0]&0xC0)
				{
					if(((message.Data[0]&0xC0)>>6)==0x01)
					{
#if MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
						PostKeyCode(UICC_CLOUD,PANEL);
#else
						PostKeyCode(UICC_OPEN_SOUND,(0x40|PANEL));
						PostKeyCode(UICC_OPEN_SOUND,PANEL);
#endif
					}	
				}
				if(message.Data[1]&0x04)
				{
					//PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AIR_KEY);	
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
				}
				if(message.Data[1]&0x08)
				{
					if(message.Data[2]==0x02)
					{
						PostKeyCode(UICC_VOLUME_UP,PANEL);
					}
					else if(message.Data[2] == 0x01)
					{
						PostKeyCode(UICC_VOLUME_DOWN,PANEL);
					}
				}
				break;
			case CAN_ID_IPM_2:

				
				F_CAN_RX_AIR_INFO=1;
#if CAN_FUN_CHERY_TIGGO_5==1
				AirConditionInfo.dual=0;
				AirConditionInfo.auto_mode=0;
				AirConditionInfo.right_temperature=0;
				AirConditionInfo.wind_speed=((message.Data[2])&0x07);
				if(message.Data[2]&0x8)
				{
					AirConditionInfo.ac=1;
				}
				else
				{
					AirConditionInfo.ac=0;
				}
				AirConditionInfo.on_off=((message.Data[3])&0x02)>>1;
				AirConditionInfo.wind_mode=((message.Data[3])&0x70)>>4;
				AirConditionInfo.circle=((message.Data[5])&0x04)>>2;
				AirConditionInfo.left_temperature=((message.Data[4])&0xF8)>>3;
				AirConditionInfo.display=(message.Data[4]&0x01);
				
				if(!strcmp_equal(&AirConditionInfo.display,&AirConditionInfoBak.display,sizeof(AirConditionInfo)))  
				{	
					Mem_strcpy(&AirConditionInfoBak.display,&AirConditionInfo.display,sizeof(AirConditionInfo));
					
					CanTxInfo.rrm_4_info.byte_1.field.f_ac=AirConditionInfo.ac;
					if(AirConditionInfo.on_off)		
					{
						CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0;
						CanTxInfo.rrm_4_info.byte_23.field.f_air_off=1;
					}
					else												
					{
						CanTxInfo.rrm_4_info.byte_1.field.f_air_on=1;
						CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0;
					}
					CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed= AirConditionInfo.wind_speed;
					CanTxInfo.rrm_4_info.byte_23.field.f_circle= AirConditionInfo.circle;
					CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode= AirConditionInfo.wind_mode;
					CanTxInfo.rrm_4_info.byte_45.field.f_temperature=AirConditionInfo.left_temperature;

					CanRxInfo.air_info.byte_1.field.f_auto=0;
					CanRxInfo.air_info.byte_1.field.f_ac_max=0;
					CanRxInfo.air_info.byte_2.field.f_dual=0;
					CanRxInfo.air_info.right_temperature=0;
					CanRxInfo.air_info.byte_4.field.f_blow_advance_on=0;
					CanRxInfo.air_info.byte_4.field.f_blow_delay_off=0;
					CanRxInfo.air_info.byte_1.field.f_disp=AirConditionInfo.display;
					CanRxInfo.air_info.byte_2.field.f_ac=AirConditionInfo.ac;
					CanRxInfo.air_info.byte_2.field.f_circle= AirConditionInfo.circle;
					if(AirConditionInfo.on_off)
					{
						CanRxInfo.air_info.byte_1.field.f_on_off=0;
					}
					else
					{
						CanRxInfo.air_info.byte_1.field.f_on_off=1;
					}
					if(AirConditionInfo.wind_mode==0x04)
					{
						CanRxInfo.air_info.byte_3.field.f_front_defrost=1;
					}
					else
					{
						CanRxInfo.air_info.byte_3.field.f_front_defrost=0;
					}
					switch(AirConditionInfo.wind_mode)
					{
						case 0x00:
							CanRxInfo.air_info.wind_mode=WIND_BODY;
							break;
						case 0x01:
							CanRxInfo.air_info.wind_mode=WIND_BODY_FEET;
							break;
						case 0x02:
							CanRxInfo.air_info.wind_mode=WIND_FEET;
							break;
						case 0x03:
							CanRxInfo.air_info.wind_mode=WIND_FRONT_WIN_FEET;
							break;
						case 0x04:
							CanRxInfo.air_info.wind_mode=WIND_OFF;
							break;
						default:
							break;
					}
					CanRxInfo.air_info.wind_speed=AirConditionInfo.wind_speed;
					CanRxInfo.air_info.left_temperature=AirConditionInfo.left_temperature;
					if (!AirConditionInfo.on_off)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AIR_INFO);
					}
				}
#elif CAN_FUN_CHERY_TIGGO_3==1
				AirConditionInfo.auto_mode=0;
				AirConditionInfo.dual=0;
				AirConditionInfo.right_temperature=0;
				AirConditionInfo.wind_speed=((message.Data[2])&0x07);
				if(message.Data[2]&0x08)
				{
					AirConditionInfo.ac=1;
				}
				else
				{
					AirConditionInfo.ac=0;
				}
				AirConditionInfo.on_off=((message.Data[3])&0x02)>>1;
				AirConditionInfo.wind_mode=((message.Data[3])&0x70)>>4;
				AirConditionInfo.circle=((message.Data[5])&0x04)>>2;
				AirConditionInfo.left_temperature=((message.Data[4])&0xF8)>>3;
				AirConditionInfo.display=(message.Data[4]&0x01);
				AirConditionInfo.blow_advance_on=!((message.Data[4]&0x02)>>1);
				AirConditionInfo.blow_delay_off=!((message.Data[4]&0x04)>>2);

				if(!strcmp_equal(&AirConditionInfo.display,&AirConditionInfoBak.display,sizeof(AirConditionInfo)))  
				{
					Mem_strcpy(&AirConditionInfoBak.display,&AirConditionInfo.display,sizeof(AirConditionInfo));
					
					CanTxInfo.rrm_4_info.byte_1.field.f_ac= AirConditionInfo.ac;
					if(AirConditionInfo.on_off)
					{
						CanTxInfo.rrm_4_info.byte_23.field.f_air_off=1;
					}
					else												
					{
						CanTxInfo.rrm_4_info.byte_23.field.f_air_off=1;
					}
					CanTxInfo.rrm_4_info.byte_23.field.f_circle= AirConditionInfo.circle;
					CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=AirConditionInfo.wind_mode;
					CanTxInfo.rrm_4_info.byte_6.field.f_blow_advance_on=0;
					CanTxInfo.rrm_4_info.byte_6.field.f_blow_delay_off=0;
					
					CanRxInfo.air_info.byte_1.field.f_auto=0;
					CanRxInfo.air_info.byte_1.field.f_ac_max=0;
					CanRxInfo.air_info.byte_2.field.f_dual=0;
					CanRxInfo.air_info.right_temperature=0;
					CanRxInfo.air_info.byte_1.field.f_disp=AirConditionInfo.display;
					CanRxInfo.air_info.byte_2.field.f_ac=AirConditionInfo.ac;
					CanRxInfo.air_info.byte_2.field.f_circle= AirConditionInfo.circle;
					if(AirConditionInfo.on_off)
					{
						CanRxInfo.air_info.byte_1.field.f_on_off=0;
					}
					else
					{
						CanRxInfo.air_info.byte_1.field.f_on_off=1;
					}
					if(AirConditionInfo.wind_mode==0x04)
					{
						CanRxInfo.air_info.byte_3.field.f_front_defrost=1;
					}
					else
					{
						CanRxInfo.air_info.byte_3.field.f_front_defrost=0;
					}
					switch(AirConditionInfo.wind_mode)
					{
						case 0x00:
							CanRxInfo.air_info.wind_mode=WIND_BODY;
							break;
						case 0x01:
							CanRxInfo.air_info.wind_mode=WIND_BODY_FEET;
							break;
						case 0x02:
							CanRxInfo.air_info.wind_mode=WIND_FEET;
							break;
						case 0x03:
							CanRxInfo.air_info.wind_mode=WIND_FRONT_WIN_FEET;
							break;
						case 0x04:
							CanRxInfo.air_info.wind_mode=WIND_OFF;
							break;
						default:
							break;
					}
					CanRxInfo.air_info.wind_speed=AirConditionInfo.wind_speed;
					CanRxInfo.air_info.left_temperature=AirConditionInfo.left_temperature;
					CanRxInfo.air_info.byte_4.field.f_blow_advance_on=AirConditionInfo.blow_advance_on;
					CanRxInfo.air_info.byte_4.field.f_blow_delay_off=AirConditionInfo.blow_delay_off;
					if (!AirConditionInfo.on_off)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AIR_INFO);
					}	
				}
#elif CAN_FUN_CHERY_ARRIZO_6==1
				AirConditionInfo.auto_mode=0;
				AirConditionInfo.dual=0;
				AirConditionInfo.right_temperature=0;
				AirConditionInfo.wind_speed=((message.Data[2])&0x07);
				AirConditionInfo.ac=((message.Data[2]&0x08)>>3);
				AirConditionInfo.ac_max=((message.Data[2]&0x40)>>6);
				AirConditionInfo.on_off=((message.Data[3])&0x02)>>1;
				AirConditionInfo.wind_mode=((message.Data[3])&0x70)>>4;
				AirConditionInfo.display=(message.Data[4]&0x01);
				AirConditionInfo.left_temperature= ((message.Data[4])&0xF8)>>3;
				AirConditionInfo.circle=((message.Data[5])&0x04)>>2;
				
				if(!strcmp_equal(&AirConditionInfo.display,&AirConditionInfoBak.display,sizeof(AirConditionInfo)))  
				{
					Mem_strcpy(&AirConditionInfoBak.display,&AirConditionInfo.display,sizeof(AirConditionInfo));
					
					CanTxInfo.rrm_4_info.byte_1.field.f_ac_max=AirConditionInfo.ac_max;
					CanTxInfo.rrm_4_info.byte_1.field.f_ac=AirConditionInfo.ac;
					CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=AirConditionInfo.wind_speed;
					if(AirConditionInfo.on_off)
					{
						CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0;
						CanTxInfo.rrm_4_info.byte_2.field.f_air_off=1;
					}
					else												
					{
						CanTxInfo.rrm_4_info.byte_1.field.f_air_on=1;
						CanTxInfo.rrm_4_info.byte_2.field.f_air_off=0;
					}
					CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=AirConditionInfo.wind_mode;
					CanTxInfo.rrm_4_info.byte_3.field.f_circlen=AirConditionInfo.circle;
					CanTxInfo.rrm_4_info.byte_5.field.f_temperature=AirConditionInfo.left_temperature;

					CanRxInfo.air_info.byte_1.field.f_auto=0;
					CanRxInfo.air_info.byte_2.field.f_dual=0;
					CanRxInfo.air_info.right_temperature=0;
					CanRxInfo.air_info.byte_4.field.f_blow_advance_on=0;
					CanRxInfo.air_info.byte_4.field.f_blow_delay_off=0;
					CanRxInfo.air_info.byte_1.field.f_disp=AirConditionInfo.display;
					CanRxInfo.air_info.byte_2.field.f_ac=AirConditionInfo.ac;
					CanRxInfo.air_info.byte_2.field.f_circle= AirConditionInfo.circle;
					CanRxInfo.air_info.byte_1.field.f_ac_max=AirConditionInfo.ac_max;
					if(AirConditionInfo.on_off)
					{
						CanRxInfo.air_info.byte_1.field.f_on_off=0;
					}
					else
					{
						CanRxInfo.air_info.byte_1.field.f_on_off=1;
					}
					if(AirConditionInfo.wind_mode==0x04)
					{
						CanRxInfo.air_info.byte_3.field.f_front_defrost=1;
					}
					else
					{
						CanRxInfo.air_info.byte_3.field.f_front_defrost=0;
					}
					switch(AirConditionInfo.wind_mode)
					{
						case 0x00:
							CanRxInfo.air_info.wind_mode=WIND_BODY;
							break;
						case 0x01:
							CanRxInfo.air_info.wind_mode=WIND_BODY_FEET;
							break;
						case 0x02:
							CanRxInfo.air_info.wind_mode=WIND_FEET;
							break;
						case 0x03:
							CanRxInfo.air_info.wind_mode=WIND_FRONT_WIN_FEET;
							break;
						case 0x04:
							CanRxInfo.air_info.wind_mode=WIND_FRONT_WIN;
							break;	
						case 0x05:
							CanRxInfo.air_info.wind_mode=WIND_OFF;
							break;
						default:
							break;
					}
					CanRxInfo.air_info.wind_speed=AirConditionInfo.wind_speed;
					CanRxInfo.air_info.left_temperature=AirConditionInfo.left_temperature;
					if (!AirConditionInfo.on_off)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AIR_INFO);
					}
				}
#else
				AirConditionInfo.out_temperature=message.Data[1];
				AirConditionInfo.wind_speed=((message.Data[2])&0x07);
				AirConditionInfo.auto_mode=((message.Data[2])&0x10)>>4;
				if(message.Data[2]&0x08)
				{
					AirConditionInfo.ac=1;
				}
				else
				{
					AirConditionInfo.ac=0;
				}
				AirConditionInfo.on_off=((message.Data[3])&0x02)>>1;
				AirConditionInfo.wind_mode=((message.Data[3])&0x70)>>4;
				AirConditionInfo.circle=((message.Data[5])&0x04)>>2;
				AirConditionInfo.dual=((message.Data[5])&0x02)>>1;
				AirConditionInfo.right_temperature=((message.Data[5])&0xF8)>>3;
				AirConditionInfo.left_temperature=((message.Data[4])&0xF8)>>3;
				AirConditionInfo.display= (message.Data[4]&0x01);
				
				if(!strcmp_equal(&AirConditionInfo.display,&AirConditionInfoBak.display,sizeof(AirConditionInfo)))  
				{
					Mem_strcpy(&AirConditionInfoBak.display,&AirConditionInfo.display,sizeof(AirConditionInfo));
					
					CanTxInfo.rrm_4_info.byte_1.field.f_ac= AirConditionInfo.ac;
					CanTxInfo.rrm_4_info.byte_1.field.f_auto=AirConditionInfo.auto_mode;
					if(AirConditionInfo.on_off)		//关
					{
						CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0;
						CanTxInfo.rrm_4_info.byte_23.field.f_air_off=1;
					}
					else												//开
					{
						CanTxInfo.rrm_4_info.byte_1.field.f_air_on=1;
						CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0;
					}
					CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=AirConditionInfo.wind_speed;
					CanTxInfo.rrm_4_info.byte_23.field.f_circle= AirConditionInfo.circle;
					CanTxInfo.rrm_4_info.byte_23.field.f_dual= AirConditionInfo.dual;
					CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1= AirConditionInfo.left_temperature;
					CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1= AirConditionInfo.right_temperature;
					CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=AirConditionInfo.wind_mode;
					CanTxInfo.rrm_4_info.byte_45.field.f_left_temperature_2= AirConditionInfo.left_temperature;
					CanTxInfo.rrm_4_info.byte_45.field.f_right_temperature_2=AirConditionInfo.right_temperature;

					CanRxInfo.air_info.byte_1.field.f_ac_max=0;
					CanRxInfo.air_info.byte_4.field.f_blow_advance_on=0;
					CanRxInfo.air_info.byte_4.field.f_blow_delay_off=0;
					CanRxInfo.air_info.byte_2.field.f_dual=AirConditionInfo.dual;
					CanRxInfo.air_info.byte_1.field.f_auto=AirConditionInfo.auto_mode;
					CanRxInfo.air_info.byte_1.field.f_disp=AirConditionInfo.display;
					CanRxInfo.air_info.byte_2.field.f_ac=AirConditionInfo.ac;
					CanRxInfo.air_info.byte_2.field.f_circle= AirConditionInfo.circle;
					if(AirConditionInfo.on_off)
					{
						CanRxInfo.air_info.byte_1.field.f_on_off=0;
					}
					else
					{
						CanRxInfo.air_info.byte_1.field.f_on_off=1;
					}
					if(AirConditionInfo.wind_mode==0x04)
					{
						CanRxInfo.air_info.byte_3.field.f_front_defrost=1;
					}
					else
					{
						CanRxInfo.air_info.byte_3.field.f_front_defrost=0;
					}
					switch(AirConditionInfo.wind_mode)
					{
						case 0x00:
							CanRxInfo.air_info.wind_mode=WIND_BODY;
							break;
						case 0x01:
							CanRxInfo.air_info.wind_mode=WIND_BODY_FEET;
							break;
						case 0x02:
							CanRxInfo.air_info.wind_mode=WIND_FEET;
							break;
						case 0x03:
							CanRxInfo.air_info.wind_mode=WIND_FRONT_WIN_FEET;
							break;
						case 0x04:
							CanRxInfo.air_info.wind_mode=WIND_OFF;
							break;
						default:
							break;
					}
					CanRxInfo.air_info.wind_speed=AirConditionInfo.wind_speed;
					switch(AirConditionInfo.left_temperature)
					{
						case 0x00:
							CanRxInfo.air_info.left_temperature=0xFE;
							break;
						case 0x1E:
						  	CanRxInfo.air_info.left_temperature=0xFF;
							break;
						default:
							CanRxInfo.air_info.left_temperature=35+AirConditionInfo.left_temperature;
							break;
					}
					switch(AirConditionInfo.right_temperature)
					{
						case 0x00:
							CanRxInfo.air_info.right_temperature=0xFE;
							break;
						case 0x1E:
							CanRxInfo.air_info.right_temperature=0xFF;
							break;
						default:
							CanRxInfo.air_info.right_temperature=35+AirConditionInfo.right_temperature;
							break;
					}
					CanRxInfo.air_info.out_temperature=AirConditionInfo.out_temperature/2+73;
					if (!AirConditionInfo.on_off)
					{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AIR_INFO);
					}
				}
#endif
#if MODEL==LINUX_Q068_21
				if(!strcmp_equal(&CanRxInfo.air_info.byte_1.byte,&CanRxInfoBak.air_info.byte_1.byte,sizeof(CAN_AIR_INFO)))
				{
					if(CanAirInfoTimer==0)
					{
						CanTxAirTimer=T1S_1;
					}
				}
#endif
				break;
#if CAN_FUN_CHERY_TIGGO_3==1
			case CAN_ID_PEPS_2:
				CanRxInfo.ctrl_feedback_info.byte_5.field.f_peps_intelligent_open=((message.Data[0]&0x08)>>3) ;
				CanRxInfo.ctrl_feedback_info.byte_5.field.f_peps_polling= ((message.Data[0]&0x10)>>4);
				CanRxInfo.ctrl_feedback_info.byte_5.field.f_welcom_light_polling=((message.Data[0]&0x04)>>2);
				break;
#endif
#if CAN_FUN_CHERY_ARRIZO_6==1
			case CAN_ID_LDW_1:
				CanRxInfo.ctrl_feedback_info.byte_6.field.f_ldw_switch=((message.Data[0]&0x80)>>7);
				CanRxInfo.ctrl_feedback_info.byte_6.field.f_ldw_sensitivity=((message.Data[0]&0x60)>>5);
				if(CanRxInfo.ctrl_feedback_info.byte_6.field.f_ldw_sensitivity)
				{
					CanRxInfo.ctrl_feedback_info.byte_6.field.f_ldw_sensitivity-=1;
				}
				break;
			case CAN_ID_ICM_4:
                if(message.Data[0]==0x30)
			    {
			        F_CAN_MEDIA_ACK=1;
			    }
			    break;
			case CAN_ID_BCM_PEPS_G:
				if(((message.Data[5]>>3)&0x07)==0x04)
				{
					CCFL_Power_OnOff(0);
				}	
				break;
#endif
#if CAN_FUN_CHERY_ARRIZO_5==1
			case CAN_ID_DIAGNOSTIC_RX_ID:
				Tiggo7_DiagNostic(message);
				break;
#endif
#if MODEL==LINUX_Q068_21||MODEL==LINUX_Q068A_21
			case CAN_ID_BCM_7:
				if(message.Data[4]&0x04)
				{
					CanRxInfo.ctrl_feedback_info.enable_flag2.field.f_mirror_auto_fold=1;
				}
				else
				{
					CanRxInfo.ctrl_feedback_info.enable_flag2.field.f_mirror_auto_fold=0;
				}
				break;
#if 0
			case CAN_ID_BCM_EPB_G:
				CanRxInfo.base_info.byte_1.field.f_parking=((message.Data[0]&0x20)>>5);
				CanGeneralCtrlFlag.field.parking_on_off=CanRxInfo.base_info.byte_1.field.f_parking;
				break;
#endif
#endif
			default:
				break;
		}
#if CAN_WAKEUP_FUN==1
		F_CAN_RX_DATA=1;
		F_CAN_SLEEP=0;
#if MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
		CanNoDataTimer=T300S_1;
#else
		CanNoDataTimer=T600S_1;
#endif
#endif
		CAN1_ClearErrorTimer();
	}
}

void Tiggo7_RxAppDataPro(u8 *buffer)
{
	u8 cmd_id;
	u8 flag=1;
	cmd_id=buffer[3];

	if(Get_ACC_Det_Flag==0)
	{
		return;
	}
	switch(cmd_id)
	{
		case CHERY_TIGGO7_TX_MACHINE_INFO:
			switch(buffer[4])
			{	
				case MEDIA_SOURCE_TUNER:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x01;
					if(radio_band<BAND_AM1)
					{
						CanTxInfo.rrm_2_info.byte_1.field.f_fm_am=0x01;
						CanTxInfo.rrm_2_info.frequence_fm_h=MSB(radio_freq*2);
						CanTxInfo.rrm_2_info.frequence_fm_l=LSB(radio_freq*2);
					}
					else
					{
						CanTxInfo.rrm_2_info.byte_1.field.f_fm_am=0x02;
						CanTxInfo.rrm_2_info.frequence_am_h=MSB(radio_freq);
						CanTxInfo.rrm_2_info.frequence_am_l=LSB(radio_freq);
					}
					if(F_TUN_Seeking|F_TUN_ASing|F_TUN_Scaning)
					{
						CanTxInfo.rrm_2_info.byte_1.field.f_as=0x02;
					}
					else
					{
						CanTxInfo.rrm_2_info.byte_1.field.f_as=0x01;
					}
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_AUX:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x04;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_USB:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x02;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_SD:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x03;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_IPOD:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x06;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_BT_MUSIC:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x05;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				case MEDIA_SOURCE_OFF:
					CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x00;
					CanTxInfo.rrm_2_info.byte_1.field.f_source=0x00;
					CanTxInfo.rrm_2_info.byte_1.field.f_as=0x00;
					CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					break;
				default:
					flag=0;
					break;
			}
			if(flag)
			{
				CanTxInfoBak.rrm_2_info.byte_1.field.f_source=CanTxInfo.rrm_2_info.byte_1.field.f_source;
#if MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
				if(F_FICTITIOUS_POWER_OFF==0)
#endif
				{
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
				}
			}
			break;
		case CHERY_TIGGO7_TX_TEXT_INFO:
			{
				u32 text_length;
				u32 i;
				u32 counter=5;
				u16 text_data[MAX_MEDIA_ID3_INFO_LENGTH/2];

				for(i=0;i<(MAX_MEDIA_ID3_INFO_LENGTH/2);i++)
				{
					text_data[i]=0x00;
				}
				text_length=(buffer[2]-1)/2;
				if(text_length>(MAX_MEDIA_ID3_INFO_LENGTH/2))
				{
					text_length=MAX_MEDIA_ID3_INFO_LENGTH/2;
				}
				for(i=0;i<text_length;i++)
				{
					text_data[i]=buffer[counter];
					text_data[i]<<=8;
					text_data[i]+=buffer[counter+1];
					counter+=2;
				}
				if(buffer[4]==0x01)
				{
					FormatMemery(&Media_ID3_Info.text_1[0],MAX_MEDIA_ID3_INFO_LENGTH);
					unicode_to_utf8(text_data,&Media_ID3_Info.text_1[0],&Media_ID3_Info.text_1_len);
				}
				else if(buffer[4]==0x02)
				{
					FormatMemery(&Media_ID3_Info.text_2[0],MAX_MEDIA_ID3_INFO_LENGTH);
					unicode_to_utf8(text_data,&Media_ID3_Info.text_2[0],&Media_ID3_Info.text_2_len);
					Media_ID3_Info.tx_ready=0x01;
					Media_ID3_Info.tx_line=0x00;
					Media_ID3_Info.pack_num=0x00;
					FormatMemery(&MediaTxMessage[0][0],sizeof(MediaTxMessage));
					Media_tx_num=0;
				}
			}
			break;
		case CHERY_TIGGO7_TX_REQUEST_CMD:
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AIR_INFO);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_CONTROL_INFO);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AVM_INFO);
			PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_TPMS_INFO);
			break;
		case CHERY_TIGGO7_TX_CONTROL_CMD:
			switch(buffer[4])
			{	              
				case CTRL_CMD_REMOTE_LOCK_FEEDBACK:
#if CAN_FUN_CHERY_ARRIZO_6==1
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_9_info.byte_1.field.f_remote_lock_feedback=0x02;
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_9_info.byte_1.field.f_remote_lock_feedback=0x03;
					}
					else if(buffer[5]==2)
					{
						CanTxInfo.rrm_9_info.byte_1.field.f_remote_lock_feedback=0x01;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_9);
					CanTxInfo.rrm_9_info.byte_1.field.f_remote_lock_feedback=0x00;
#else
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_1_info.byte_1.field.f_remote_lock_feedback=0x02;
					}
					else if(buffer[5]==1)
					{
						CanTxInfo.rrm_1_info.byte_1.field.f_remote_lock_feedback=0x03;
					}
					else if(buffer[5]==2)
					{
						CanTxInfo.rrm_1_info.byte_1.field.f_remote_lock_feedback=0x01;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
#if CAN_FUN_CHERY_TIGGO_3==1
					CanTxInfo.rrm_1_info.byte_1.field.f_remote_lock_feedback=0x00;
#endif
#endif
					break;
				case CTRL_CMD_VOLUME:
					CanTxInfo.rrm_2_info.volume=buffer[5];
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0;
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					break;
				case CTRL_CMD_AUTO_LOCK:
#if CAN_FUN_CHERY_ARRIZO_6==1
					if(buffer[5])
					{
						CanTxInfo.rrm_9_info.byte_3.field.f_auto_lock=0x01;
					}
					else
					{
						CanTxInfo.rrm_9_info.byte_3.field.f_auto_lock=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_9);
					CanTxInfo.rrm_9_info.byte_3.field.f_auto_lock=0x00;
#elif CAN_FUN_CHERY_ARRIZO_5==1					
#else
					if(buffer[5])
					{
						CanTxInfo.rrm_1_info.byte_1.field.f_auto_lock=0x01;
					}
					else
					{
						CanTxInfo.rrm_1_info.byte_1.field.f_auto_lock=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
#if CAN_FUN_CHERY_TIGGO_3==1
					CanTxInfo.rrm_1_info.byte_1.field.f_auto_lock=0x00;
#endif
#endif
					break;
				case CTRL_CMD_HEADLIGHT_DELAY:
#if CAN_FUN_CHERY_ARRIZO_6==1
					if(buffer[5])
					{
						CanTxInfo.rrm_9_info.byte_2.field.f_head_light_delay=0x01;
					}
					else
					{
						CanTxInfo.rrm_9_info.byte_2.field.f_head_light_delay=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_9);
					CanTxInfo.rrm_9_info.byte_2.field.f_head_light_delay=0x00;	
#elif CAN_FUN_CHERY_ARRIZO_5==1					
#else
					if(buffer[5])
					{
						CanTxInfo.rrm_1_info.byte_2.field.f_head_light_delay=0x01;
					}
					else
					{
						CanTxInfo.rrm_1_info.byte_2.field.f_head_light_delay=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
#if CAN_FUN_CHERY_TIGGO_3==1
					CanTxInfo.rrm_1_info.byte_2.field.f_head_light_delay=0x00;
#endif					
#endif
					break;
				case CTRL_CMD_DRL:
#if CAN_FUN_CHERY_ARRIZO_6==1
					if(buffer[5])
					{
						CanTxInfo.rrm_9_info.byte_2.field.f_drl=0x01;
					}
					else
					{
						CanTxInfo.rrm_9_info.byte_2.field.f_drl=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_9);
					CanTxInfo.rrm_9_info.byte_2.field.f_drl=0x00;	
#elif CAN_FUN_CHERY_ARRIZO_5==1
#else
					if(buffer[5])
					{
						CanTxInfo.rrm_1_info.byte_2.field.f_drl=0x01;
					}
					else
					{
						CanTxInfo.rrm_1_info.byte_2.field.f_drl=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
#if CAN_FUN_CHERY_TIGGO_3==1
					CanTxInfo.rrm_1_info.byte_2.field.f_drl=0x00;
#endif					
#endif
#if CAN_DEBUG_FUN==1
					printf("CTRL_CMD_DRL:param=%x\r\n",buffer[5]);
#endif
					break;
				case CTRL_CMD_OVER_SPEED:
#if CAN_FUN_CHERY_ARRIZO_5==1
#else
					if(buffer[5]==0)
					{
						CanTxInfo.rrm_1_info.byte_34.field.f_over_speed=0x3F;
					}
					else
					{
						CanTxInfo.rrm_1_info.byte_34.field.f_over_speed=buffer[5];
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
					CanTxInfo.rrm_1_info.byte_34.field.f_over_speed = 0x00;
					CanOverSpeedTimer=T3S_1;
#endif
					break;
				case CTRL_CMD_BACKLIGHT:
					CanTxInfo.rrm_3_info.instrument_back_light=buffer[5];
					CanTxInfo.rrm_3_info.hour=0xFF;
					CanTxInfo.rrm_3_info.min=0xFF;
					CanTxInfo.rrm_3_info.second=0xFF;
#if CAN_FUN_CHERY_ARRIZO_6==1||CAN_FUN_CHERY_TIGGO_3==1||MODEL==LINUX_Q068A_21
					CanTxInfo.rrm_3_info.byte_67.field.f_year=0x7F;
					CanTxInfo.rrm_3_info.byte_67.field.f_month=0x00;
					CanTxInfo.rrm_3_info.byte_67.field.f_day=0x00;
#endif
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_3);
#if CAN_FUN_CHERY_ARRIZO_6==1||CAN_FUN_CHERY_TIGGO_3==1
					CanTxInfo.rrm_3_info.instrument_back_light=0x00;
#endif
					break;
				case CTRL_CMD_SIDE_VIEW:
					if(buffer[5])
					{
						CanTxInfo.rrm_6_info.byte_5.field.f_side_view=0x01;
					}
					else
					{
						CanTxInfo.rrm_6_info.byte_5.field.f_side_view=0x02;
					}
					if(CanTxInfo.rrm_6_info.byte_6.field.f_trajectory==0x00)
					{

						CanTxInfo.rrm_6_info.byte_6.field.f_trajectory=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
#if CAN_FUN_CHERY_ARRIZO_6==1
					CanTxInfo.rrm_6_info.byte_5.field.f_side_view=0;
#endif
					break;
				case CTRL_CMD_3D_AROUND_VIEW:
					if(buffer[5])
					{
						CanTxInfo.rrm_6_info.byte_6.field.f_3d_around_view=0x01;
					}
					else
					{
						CanTxInfo.rrm_6_info.byte_6.field.f_3d_around_view=0x02;
					}
					if(CanTxInfo.rrm_6_info.byte_6.field.f_trajectory==0x00)
					{

						CanTxInfo.rrm_6_info.byte_6.field.f_trajectory=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
#if CAN_FUN_CHERY_ARRIZO_6==1
					CanTxInfo.rrm_6_info.byte_6.field.f_3d_around_view=0;
#endif
					break;
				case CTRL_CMD_TRAJECTORY:
					if(buffer[5]==0x00)
					{
						CanTxInfo.rrm_6_info.byte_6.field.f_trajectory=0x01;
					}
					else if(buffer[5]==0x01)
					{
						CanTxInfo.rrm_6_info.byte_6.field.f_trajectory=0x03;
					}
					else if(buffer[5]==0x02)
					{
						CanTxInfo.rrm_6_info.byte_6.field.f_trajectory=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
					break;
				case CTRL_CMD_MIRROR_AUTO_FOLD:
#if CAN_FUN_CHERY_ARRIZO_6==1
					if(buffer[5])
					{
						CanTxInfo.rrm_9_info.byte_8.field.f_mirror_auto_fold=0x01;
					}
					else
					{
						CanTxInfo.rrm_9_info.byte_8.field.f_mirror_auto_fold=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_9);
					CanTxInfo.rrm_9_info.byte_8.field.f_mirror_auto_fold=0;
#elif CAN_FUN_CHERY_ARRIZO_5==1
#else
					if(buffer[5])
					{
						CanTxInfo.rrm_1_info.byte_8.field.f_mirror_auto_fold=0x01;
					}
					else
					{
						CanTxInfo.rrm_1_info.byte_8.field.f_mirror_auto_fold=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
#if CAN_FUN_CHERY_TIGGO_3==1
					CanTxInfo.rrm_1_info.byte_8.field.f_mirror_auto_fold=0x00;
#endif						
#endif
#if CAN_DEBUG_FUN==1
					printf("CTRL_CMD_MIRROR_AUTO_FOLD:param=%x\r\n",buffer[5]);
#endif
					break;
				case CTRL_CMD_BLIND_AREA_MONITOR:
#if CAN_FUN_CHERY_ARRIZO_5==1
#else
					if(buffer[5])
					{
						CanTxInfo.rrm_1_info.byte_8.field.f_blind_area_monitoring=0x01;
					}
					else
					{
						CanTxInfo.rrm_1_info.byte_8.field.f_blind_area_monitoring=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
#endif					
					break;
#if CAN_FUN_CHERY_TIGGO_3==1
				case CTRL_CMD_WELCOM_LIGHT_POLLING:
					if(buffer[5]) 
					{
						CanTxInfo.rrm_7_info.byte_2.field.f_welcom_light_polling=0x01;
					}
					else
					{
						CanTxInfo.rrm_7_info.byte_2.field.f_welcom_light_polling=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_7);
					CanTxInfo.rrm_7_info.byte_2.field.f_welcom_light_polling=0x00;
					break;
				case CTRL_CMD_PEPS_INTELLIGENT_OPEN:
					if(buffer[5])
					{
						CanTxInfo.rrm_7_info.byte_2.field.f_peps_intelligent_open=0x01;
					}
					else
					{
						CanTxInfo.rrm_7_info.byte_2.field.f_peps_intelligent_open=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_7);
					CanTxInfo.rrm_7_info.byte_2.field.f_peps_intelligent_open=0x00;
					break;
				case CTRL_CMD_PEPS_POLLING:
					if(buffer[5])
					{
						CanTxInfo.rrm_7_info.byte_2.field.f_peps_polling=0x01;
					}
					else
					{
						CanTxInfo.rrm_7_info.byte_2.field.f_peps_polling=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_7);
					CanTxInfo.rrm_7_info.byte_2.field.f_peps_polling=0x00;
					break;
				case CTRL_CMD_BLOW_ADVANCE_ON:
					if(buffer[5])
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_blow_advance_on=0x01;
					}
					else
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_blow_advance_on=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_6.field.f_blow_advance_on=0x00;
					break;
				case CTRL_CMD_BLOW_DELAY_OFF:
					if(buffer[5])
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_blow_delay_off=0x01;
					}
					else
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_blow_delay_off=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					CanTxInfo.rrm_4_info.byte_6.field.f_blow_delay_off=0x00;
					break;
				case CTRL_CMD_FG_HEAT:
					if(buffer[5])
					{
						CanTxInfo.rrm_7_info.byte_8.field.f_fg_heat=0x01;
					}
					else
					{
						CanTxInfo.rrm_7_info.byte_8.field.f_fg_heat=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_7);
					CanTxInfo.rrm_7_info.byte_8.field.f_fg_heat=0x00;
					break;
#endif
#if CAN_FUN_CHERY_ARRIZO_6==1
				case CTRL_CMD_LDW_ON_OFF:
					if(buffer[5])
					{
						CanTxInfo.rrm_6_info.byte_6.field.f_ldw_switch=0x01;
					}
					else
					{
						CanTxInfo.rrm_6_info.byte_6.field.f_ldw_switch=0x02;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
					CanTxInfo.rrm_6_info.byte_6.field.f_ldw_switch=0;
					break;
				case CTRL_CMD_LDW_SENSITIVITY:
					CanTxInfo.rrm_6_info.byte_7.field.f_ldw_sensitivity=buffer[5];
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
					CanTxInfo.rrm_6_info.byte_7.field.f_ldw_sensitivity=0;
					break;
#endif
	
#if CAN_FUN_CHERY_ARRIZO_5==1
				case CTRL_CMD_URGENCY_BRAKE_WARNING:
					if(buffer[5])
					{
						CanTxInfo.rrm_1_info.byte_2.field.f_HazardLampForUrgencyBrake = 1;
					}
					else
					{
						CanTxInfo.rrm_1_info.byte_2.field.f_HazardLampForUrgencyBrake = 2;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
					break;	
#endif					
				default:
					break;
			}
			break;
		case CHERY_TIGGO7_TX_LANGUAGE_CMD:
#if CAN_FUN_CHERY_ARRIZO_5==1
#else
			if(buffer[4]== 0x01)
			{
				if(buffer[5]==0x01)         //英文
				{
					CanTxInfo.rrm_1_info.byte_34.field.f_language=0x02;
				}
				else if(buffer[5] == 0x02)    //中文
				{
					CanTxInfo.rrm_1_info.byte_34.field.f_language=0x01;
				}
				else if(buffer[5] == 0x03)    //葡萄牙
				{
					CanTxInfo.rrm_1_info.byte_34.field.f_language=0x05;
				}	
				else if(buffer[5] == 0x04)    //西班牙
				{
					CanTxInfo.rrm_1_info.byte_34.field.f_language=0x07;
				}	
				else if(buffer[5] == 0x05)    //俄罗斯
				{
					CanTxInfo.rrm_1_info.byte_34.field.f_language=0x03;
				}
				else if(buffer[5] == 0x06)    //阿拉伯
				{
					CanTxInfo.rrm_1_info.byte_34.field.f_language=0x04;
				}
				Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);	
				CanTxInfo.rrm_1_info.byte_34.field.f_language=0x00;
			}
#endif
			break;
		case CHERY_TIGGO7_TX_TIME_SET_CMD:
			{
#if CAN_FUN_CHERY_ARRIZO_6==1||CAN_FUN_CHERY_TIGGO_3==1||MODEL==LINUX_Q068A_21
				u32 temp;

				CanTxInfo.rrm_3_info.hour=buffer[5];
				CanTxInfo.rrm_3_info.min=buffer[6];
				CanTxInfo.rrm_3_info.second=buffer[7];
				temp=buffer[8];
				temp<<=8;
				temp+=buffer[9];
				if(temp>2126)
				{
					temp=126;
				}
				else if(temp>2000)
				{
					temp-=2000;
				}
				else
				{
					temp=0;
				}
				if(CanRxInfo.ctrl_feedback_info.cluster_size==0)
				{
				CanTxInfo.rrm_3_info.byte_67.field.f_year=temp;
				CanTxInfo.rrm_3_info.byte_67.field.f_month=buffer[10];
				CanTxInfo.rrm_3_info.byte_67.field.f_day=buffer[11];
				}
				else
				{
					CanTxInfo.rrm_3_info.byte_67.field.f_year=0x7F;
					CanTxInfo.rrm_3_info.byte_67.field.f_month=0x00;
					CanTxInfo.rrm_3_info.byte_67.field.f_day=0x00;
				}
				Tiggo7_PostMessage(CAN_POST_MSG_RRM_3);
				CanTxInfo.rrm_3_info.hour=0xFF;
				CanTxInfo.rrm_3_info.min=0xFF;
				CanTxInfo.rrm_3_info.second=0xFF;
				CanTxInfo.rrm_3_info.byte_67.field.f_year=0x7F;
				CanTxInfo.rrm_3_info.byte_67.field.f_month=0x00;
				CanTxInfo.rrm_3_info.byte_67.field.f_day=0x00;
#else
				CanTxInfo.rrm_3_info.hour=buffer[5];
				CanTxInfo.rrm_3_info.min=buffer[6];
				CanTxInfo.rrm_3_info.second=buffer[7];
				Tiggo7_PostMessage(CAN_POST_MSG_RRM_3);
				CanTxInfo.rrm_3_info.hour=0xFF;
				CanTxInfo.rrm_3_info.min=0xFF;
				CanTxInfo.rrm_3_info.second=0xFF;
#endif
				CanTimeInfoTimer=T2S_1;
				CanTimeSyncDelay=4;
			}
			break;
		case CHERY_TIGGO7_TX_AIR_SET_CMD:
			switch(buffer[4])
			{
#if CAN_FUN_CHERY_TIGGO_3==1
				case AIR_CMD_ON_OFF:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.on_off)
						{
							Mem_strcpy(&CanTxInfo.rrm_4_info.byte_1.byte,&CanTxInfoBak.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0x00;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							Mem_strcpy(&CanTxInfoBak.rrm_4_info.byte_1.byte,&CanTxInfo.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
					}
					break;
				case AIR_CMD_AC:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.ac)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac=0;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac=1;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_FRONT_DEFROST:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode==0x04)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x05;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x04;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_CIRCLE:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.circle==0x00)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_circle=0x01;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_circle=0x00;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_BLOW_ADVANCE_ON:
					if(buffer[5])
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_blow_advance_on=1;
					}
					else
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_blow_advance_on=0;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					break;
				case AIR_CMD_BLOW_DELAY_OFF:
					if(buffer[5])
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_blow_delay_off=1;
					}
					else
					{
						CanTxInfo.rrm_4_info.byte_6.field.f_blow_delay_off=0;
					}
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					break;
				case AIR_CMD_WIND_BODY:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x00)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x00;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_BODY_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x01)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_WIN_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x03)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x03;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x02)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x02;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
#elif CAN_FUN_CHERY_ARRIZO_6==1
				case AIR_CMD_ON_OFF:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.on_off)
						{
							Mem_strcpy(&CanTxInfo.rrm_4_info.byte_1.byte,&CanTxInfoBak.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x01;
							CanTxInfo.rrm_4_info.byte_2.field.f_air_off=0x00;
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed==0)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=1;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							Mem_strcpy(&CanTxInfoBak.rrm_4_info.byte_1.byte,&CanTxInfo.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x00;
							CanTxInfo.rrm_4_info.byte_2.field.f_air_off=0x01;
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=0x00;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
					}
					break;
				case AIR_CMD_AC:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.ac)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac=0;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac=1;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_FRONT_DEFROST:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode==0x04)
						{
							CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=0x05;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=0x04;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_CIRCLE:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.circle==0x00)
						{
							CanTxInfo.rrm_4_info.byte_3.field.f_circlen=0x01;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_3.field.f_circlen=0x00;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_WIND_UP:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.on_off)
						{
							Mem_strcpy(&CanTxInfo.rrm_4_info.byte_1.byte,&CanTxInfoBak.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x01;
							CanTxInfo.rrm_4_info.byte_2.field.f_air_off=0x00;
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=0x00;
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed<2)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=2;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed<0x07)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed++;
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
								CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
							}
							else
							{
								CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
							}
						}
					}
					break;
				case AIR_CMD_WIND_DOWN:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed>0x01)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed--;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_LEFT_TEMP_UP:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_5.field.f_temperature<0x0E)
						{
							CanTxInfo.rrm_4_info.byte_5.field.f_temperature++;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_LEFT_TEMP_DOWN:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_5.field.f_temperature>0x01)
						{
							CanTxInfo.rrm_4_info.byte_5.field.f_temperature--;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
                case AIR_CMD_WIND_VALUE:
                    if(AirConditionInfo.on_off)
                    {
                        if(buffer[5]>=CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed)
                        {
                            Mem_strcpy(&CanTxInfo.rrm_4_info.byte_1.byte,&CanTxInfoBak.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x01;
							CanTxInfo.rrm_4_info.byte_2.field.f_air_off=0x00;
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=0x00;
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed<2)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=2;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
                        }
                    }
                    else
                    {
                        if(buffer[5] != CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed)
                        {
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=buffer[5];
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
                        }
                        else
                        {
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
                        }
                    }
                    break;
                case AIR_CMD_LEFT_TEMP_VALUE:
                    if(buffer[5]!=CanTxInfo.rrm_4_info.byte_5.field.f_temperature)
                    {
                        CanTxInfo.rrm_4_info.byte_5.field.f_temperature=buffer[5];
                        Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
                        CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
                    }
                    else
                    {
                        CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
                        Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
                        Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
                        Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
                        CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
                    }
                    break;
				case AIR_CMD_AC_MAX:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.ac_max)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac_max=0;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac_max=1;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_WIND_BODY:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x00)
						{
							CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=0x00;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_BODY_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x01)
						{
							CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_WIN_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x03)
						{
							CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=0x03;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x02)
						{
							CanTxInfo.rrm_4_info.byte_2.field.f_wind_mode=0x02;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
#elif CAN_FUN_CHERY_TIGGO_5==1
				case AIR_CMD_ON_OFF:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.on_off)
						{
							Mem_strcpy(&CanTxInfo.rrm_4_info.byte_1.byte,&CanTxInfoBak.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x01;
							CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0x00;
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed==0)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=1;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							Mem_strcpy(&CanTxInfoBak.rrm_4_info.byte_1.byte,&CanTxInfo.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x00;
							CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0x01;
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=0x00;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
					}
					break;
				case AIR_CMD_AC:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.ac)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac=0;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac=1;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_FRONT_DEFROST:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode==0x04)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x05;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x04;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_CIRCLE:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.circle==0x00)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_circle=0x01;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_circle=0x00;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_WIND_UP:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.on_off)
						{
							Mem_strcpy(&CanTxInfo.rrm_4_info.byte_1.byte,&CanTxInfoBak.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x01;
							CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0x00;
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed<2)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=2;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed<7)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed++;
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
								CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
							}
							else
							{
								CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
							}
						}
					}
					break;
				case AIR_CMD_WIND_DOWN:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed>1)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed--;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_LEFT_TEMP_UP:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_45.field.f_temperature<0x10)
						{
							CanTxInfo.rrm_4_info.byte_45.field.f_temperature++;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_LEFT_TEMP_DOWN:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_45.field.f_temperature>0x01)
						{
							CanTxInfo.rrm_4_info.byte_45.field.f_temperature--;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_WIND_BODY:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x00)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x00;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_BODY_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x01)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_WIN_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x03)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x03;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x02)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x02;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
#else
				case AIR_CMD_ON_OFF:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.on_off)
						{
							Mem_strcpy(&CanTxInfo.rrm_4_info.byte_1.byte,&CanTxInfoBak.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x01;
							CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0x00;
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=0x00;
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed==0)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=1;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							Mem_strcpy(&CanTxInfoBak.rrm_4_info.byte_1.byte,&CanTxInfo.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x00;
							CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0x01;
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=0x00;
							CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1=CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
					}
					break;
				case AIR_CMD_AC:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.ac)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac=0;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_ac=1;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_FRONT_DEFROST:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode==0x04)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x05;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x04;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_CIRCLE:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.circle==0x00)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_circle=0x01;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_circle=0x00;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_DUAL:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.dual)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_dual=0;
							CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1=CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1;
						}
						else
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_dual=1;
						}
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
					}
					break;
				case AIR_CMD_AUTO:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.auto_mode==0x00)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_auto=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
					}
					break;
				case AIR_CMD_WIND_UP:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.on_off)
						{
							Mem_strcpy(&CanTxInfo.rrm_4_info.byte_1.byte,&CanTxInfoBak.rrm_4_info.byte_1.byte,sizeof(CAN_RRM_4_INFO));
							CanTxInfo.rrm_4_info.byte_1.field.f_air_on=0x01;
							CanTxInfo.rrm_4_info.byte_23.field.f_air_off=0x00;
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=0x00;
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed==0)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed=1;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed<7)
							{
								CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed++;
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
								CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
							}
							else
							{
								CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
								CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
							}
						}
					}
					break;
				case AIR_CMD_WIND_DOWN:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed>0x01)
						{
							CanTxInfo.rrm_4_info.byte_1.field.f_wind_speed--;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_LEFT_TEMP_UP:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1<0x1E)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1++;
							if(AirConditionInfo.dual==0x00)
							{
								CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1++;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_LEFT_TEMP_DOWN:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1>0x00)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1--;
							if(AirConditionInfo.dual==0x00)
							{
								CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1--;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_RIGHT_TEMP_UP:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1<0x1E)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1++;
							if(AirConditionInfo.dual==0x00)
							{
								CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1++;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_RIGHT_TEMP_DOWN:
					if(buffer[5]==0)
					{
						if(CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1>0x00)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_right_temperature_1--;
							if(AirConditionInfo.dual==0x00)
							{
								CanTxInfo.rrm_4_info.byte_23.field.f_left_temperature_1--;
							}
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
							CanAirInfoTimer=CHERY_AIR_DISABLE_TIME;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
						}
					}
					break;
				case AIR_CMD_WIND_BODY:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x00)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x00;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_BODY_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x01)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_WIN_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x03)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x03;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
				case AIR_CMD_WIND_FEET:
					if(buffer[5]==0)
					{
						if(AirConditionInfo.wind_mode!=0x02)
						{
							CanTxInfo.rrm_4_info.byte_23.field.f_wind_mode=0x02;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
							Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
						}
					}
					break;
#endif
				case AIR_CMD_OPEN_SCREEN:
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x01;
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
					break;
				case AIR_CMD_CLOSE_SCREEN:
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x02;
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
					CanTxInfo.rrm_2_info.byte_8.field.f_disp=0x00;
					break;
				default:
					break;
			}
			break;
		case CHERY_TIGGO7_TX_AVM_CMD:
			{
				u16 touch_value_x;
				u16 touch_value_y;
				
				if(buffer[4]==0x00)
				{
					touch_value_x=(((u16)buffer[5])<<8)|buffer[6];
					touch_value_y=(((u16)buffer[7])<<8)|buffer[8];
					if((touch_value_x>0&&touch_value_x<1024)&&(touch_value_y>0&&touch_value_y<600))
					{
#if CAN_FUN_CHERY_TIGGO_7==1||CAN_FUN_CHERY_ARRIZO_6==1
						CanTxInfo.rrm_6_info.coordinate_x_h=buffer[5];
						CanTxInfo.rrm_6_info.coordinate_x_l=buffer[6];
						CanTxInfo.rrm_6_info.coordinate_y_h=buffer[7];
						CanTxInfo.rrm_6_info.coordinate_y_l=buffer[8];
						CanTxInfo.rrm_6_info.byte_7.field.f_touch_event=0x01;
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
						CanTxInfo.rrm_6_info.byte_7.field.f_touch_event=0x00;
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);

						CanTxInfo.rrm_6_info.coordinate_x_h=0xFF;
						CanTxInfo.rrm_6_info.coordinate_x_l=0xFF;
						CanTxInfo.rrm_6_info.coordinate_y_h=0xFF;
						CanTxInfo.rrm_6_info.coordinate_y_l=0xFF;
						CanTxInfo.rrm_6_info.byte_7.field.f_touch_event=0x03;
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
						CanTxInfo.rrm_6_info.byte_7.field.f_touch_event=0x00;
#else
						if(F_AVM_CALIBRATION)
						{
							if(touch_value_x>=224
								&&touch_value_y>=60
								&&touch_value_y<=540)
							{
								u16 tx_x_value;
								u16 tx_y_value;
								u16 temp_x_value;
								u16 temp_y_value;

								temp_x_value = ((touch_value_x-224)*32)/25;
								temp_y_value = ((touch_value_y-60)*5)/4;
								
								tx_x_value=((temp_x_value*21)/25)+218;
								tx_y_value=((temp_y_value*5)/8)+108;
								CanTxInfo.rrm_6_info.coordinate_x_h=(tx_x_value&0xFF00)>>8;
								CanTxInfo.rrm_6_info.coordinate_x_l=tx_x_value&0x00FF;
								CanTxInfo.rrm_6_info.coordinate_y_h=(tx_y_value&0xFF00)>>8;
								CanTxInfo.rrm_6_info.coordinate_y_l=tx_y_value&0x00FF;
							}
						}
						else
						{
							if(touch_value_x>=224)//off area
							{	
								CanTxInfo.rrm_6_info.coordinate_x_h=0x02;
								CanTxInfo.rrm_6_info.coordinate_x_l=0x00;
								CanTxInfo.rrm_6_info.coordinate_y_h=0x01;
								CanTxInfo.rrm_6_info.coordinate_y_l=0x2C;
							}	
							else
							{
								CanTxInfo.rrm_6_info.coordinate_x_h=buffer[5];
								CanTxInfo.rrm_6_info.coordinate_x_l=buffer[6];
								CanTxInfo.rrm_6_info.coordinate_y_h=buffer[7];
								CanTxInfo.rrm_6_info.coordinate_y_l=buffer[8];
							}
						}
						CanTxInfo.rrm_6_info.byte_7.field.f_touch_event=0x01;
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
						CanTxInfo.rrm_6_info.byte_7.field.f_touch_event=0x00;
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);

						CanTxInfo.rrm_6_info.coordinate_x_h=0xFF;
						CanTxInfo.rrm_6_info.coordinate_x_l=0xFF;
						CanTxInfo.rrm_6_info.coordinate_y_h=0xFF;
						CanTxInfo.rrm_6_info.coordinate_y_l=0xFF;
						CanTxInfo.rrm_6_info.byte_7.field.f_touch_event=0x03;
						Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
						CanTxInfo.rrm_6_info.byte_7.field.f_touch_event=0x00;
#endif
					}
				}
			}
			break;
		default:
			break;
	}
}

void Tiggo7_TxAppDataPro(u8 cmd_id,u8 *buffer,u16 *length)
{
	u8 i;
	u8 error_flag=0;
	u8 checksum=0;
	
	*length=0;
	buffer[0]=TIGGO7_HEAD_CODE0;	
	buffer[1]=TIGGO7_HEAD_CODE1;	
	buffer[3]=cmd_id;
	checksum+=buffer[3];
	switch(cmd_id)
	{
		case CHERY_TIGGO7_RX_BASIC_INFO:
			buffer[2]=10;
			buffer[4]=CanRxInfo.base_info.byte_1.byte;
			buffer[5]=0;
			buffer[6]=0;
			buffer[7]=0;
			buffer[8]=0;
			buffer[9]=0;
			buffer[10]=CanRxInfo.base_info.swa_msb;
			buffer[11]=CanRxInfo.base_info.swa_lsb;
			buffer[12]=0;
			buffer[13]=0;
			break;
		case CHERY_TIGGO7_RX_DETAIL_INFO:
			buffer[2]=10;
			buffer[4]=0;
			buffer[5]=0;
			buffer[6]=CanRxInfo.detail_info.byte_3.byte;
			buffer[7]=0;
			buffer[8]=0;
			buffer[9]=0;
			buffer[10]=0;
			buffer[11]=0;
			buffer[12]=0;
			buffer[13]=0;
			break;
		case CHERY_TIGGO7_RX_TPMS_INFO:
			buffer[2]=15;
			buffer[4]=CanRxInfo.tpms_info.system_fail_status;
			buffer[5]=CanRxInfo.tpms_info.warning_lamp_status;
			buffer[6]=CanRxInfo.tpms_info.left_front_warning;
			buffer[7]=CanRxInfo.tpms_info.right_front_warning;
			buffer[8]=CanRxInfo.tpms_info.left_rear_warning;
			buffer[9]=CanRxInfo.tpms_info.right_rear_warning;
			buffer[10]=CanRxInfo.tpms_info.byte_7.byte;
			buffer[11]=CanRxInfo.tpms_info.left_front_temperature;
			buffer[12]=CanRxInfo.tpms_info.right_front_temperature;
			buffer[13]=CanRxInfo.tpms_info.left_rear_temperature;
			buffer[14]=CanRxInfo.tpms_info.right_rear_temperature;
			buffer[15]=CanRxInfo.tpms_info.left_front_pressure;
			buffer[16]=CanRxInfo.tpms_info.right_front_pressure;
			buffer[17]=CanRxInfo.tpms_info.left_rear_pressure;
			buffer[18]=CanRxInfo.tpms_info.right_rear_pressure;
			break;
		case CHERY_TIGGO7_RX_DRIVING_INFO:
			buffer[2]=9;
			buffer[4]=CanRxInfo.drive_info.fuel_level;
			buffer[5]=CanRxInfo.drive_info.average_fuel_consumption;
			buffer[6]=CanRxInfo.drive_info.byte_3.byte;
			buffer[7]= MSB(CanRxInfo.drive_info.speed);
			buffer[8]=LSB(CanRxInfo.drive_info.speed);
			buffer[9]=((CanRxInfo.drive_info.total_odometer&0xFF000000)>>24);
			buffer[10]=((CanRxInfo.drive_info.total_odometer&0x00FF0000)>>16);
			buffer[11]=((CanRxInfo.drive_info.total_odometer&0x0000FF00)>>8);
			buffer[12]=(CanRxInfo.drive_info.total_odometer&0x000000FF);
			break;
		case CHERY_TIGGO7_RX_AIR_INFO:
			buffer[2]=12;
			buffer[4]=CanRxInfo.air_info.byte_1.byte;
			buffer[5]=CanRxInfo.air_info.byte_2.byte;
			buffer[6]=CanRxInfo.air_info.byte_3.byte;
			buffer[7]=CanRxInfo.air_info.byte_4.byte;
			buffer[8]=CanRxInfo.air_info.wind_mode;
			buffer[9]=CanRxInfo.air_info.wind_speed;
			buffer[10]=CanRxInfo.air_info.left_temperature;
			buffer[11]=CanRxInfo.air_info.right_temperature;
			buffer[12]=0;
			buffer[13]=0;
			buffer[14]=0;
			buffer[15]=CanRxInfo.air_info.out_temperature;
			break;
		case CHERY_TIGGO7_RX_AIR_KEY:
			buffer[2]=1;
			buffer[4]=0;
			break;
		case CHERY_TIGGO7_RX_CONTROL_INFO:
			buffer[2]=8;
			buffer[4]=CanRxInfo.ctrl_feedback_info.enable_flag1.byte;
			buffer[5]=CanRxInfo.ctrl_feedback_info.enable_flag2.byte;
			buffer[6]=CanRxInfo.ctrl_feedback_info.byte_3.byte;
			buffer[7]=CanRxInfo.ctrl_feedback_info.byte_4.byte;
			buffer[8]=CanRxInfo.ctrl_feedback_info.byte_5.byte;
			buffer[9]=CanRxInfo.ctrl_feedback_info.byte_6.byte;
			buffer[10]=CanRxInfo.ctrl_feedback_info.cluster_size;
			buffer[11]=0;
#if CAN_DEBUG_FUN==1
			printf("CHERY_TIGGO7_RX_CONTROL_INFO:byte3=%x,byte4=%x\r\n",buffer[6],buffer[7]);
#endif
			break;
		case CHERY_TIGGO7_RX_AVM_INFO:
			buffer[2]=7;
			buffer[4]=CanRxInfo.avm_info.avm_exist;
			buffer[5]=0;
			buffer[6]=CanRxInfo.avm_info.right_camera_state;
			buffer[7]=CanRxInfo.avm_info.avm_state;
			buffer[8]=CanRxInfo.avm_info.left_camera_state;
			buffer[9]=CanRxInfo.avm_info.camera_view_state;
			buffer[10]=0;
			break;
		default:
			error_flag=1;
			break;
	}
	if(error_flag==0)
	{
		checksum+=buffer[2];
		for(i=0;i<buffer[2];i++)
		{
			checksum+=buffer[i+4];
		}
		checksum-=1;
		checksum&=0xFF;
		*length=buffer[2]+5;
		buffer[(*length)-1]=checksum;
	}
}

void Tiggo7_MainPro(void)
{
	if(CanMainTimer)
	{
		CanMainTimer--;
	}
#if CAN_WAKEUP_FUN==1
	if(CanNoDataTimer)
	{
		CanNoDataTimer--;
		if(CanNoDataTimer==0)
		{
			F_CAN_RX_DATA=0;
		}
	}
#endif
	if(CanTxCanTimer)
	{
		CanTxCanTimer--;
	}
	if(CanNMmBCM_TimerCounter)
	{
	    CanNMmBCM_TimerCounter--;
	}
	if(CanTxAppTimer)
	{
		CanTxAppTimer--;
	}
	if(CanBaseInfoTimer)
	{
		CanBaseInfoTimer--;
	}
	if(CanOverSpeedTimer)
	{
		CanOverSpeedTimer--;
	}
	if(AvmCalibrationTimeout)
	{
		AvmCalibrationTimeout--;
		if(AvmCalibrationTimeout==0)
		{
			AvmCalibrationFlag=0;
		}
	}
	if(AvmCalibrationTimer)
	{
		AvmCalibrationTimer--;
		if(AvmCalibrationTimer==0)
		{
			CanTxInfo.rrm_6_info.byte_5.field.f_calibration_req=0x00;
		}
	}

	if(CanAirInfoTimer)
	{
		CanAirInfoTimer--;
	}
	if(CanTxAirTimer)
	{
		CanTxAirTimer--;
	}

	if(CanTimeInfoTimer)
	{
		CanTimeInfoTimer--;
	}
		
	/*
	if(CanErrorTimer)
	{
		CanErrorTimer--;
		if(CanErrorTimer==0
			&&CAN1_GetErrorFlag()==0)
		{
			CAN1_SetErrorFlag();
			CAN_IC_POWER_OFF;
			SystemReset();
		}
	}
	*/
	Tiggo7_Rx_Message();

	if(CanTxTimer)
	{
		CanTxTimer--;
	}
	if(CanTxTimer==0)
	{
		CanTxTimer=T50MS_1;
		if(F_CAN_INIT)
		{
			CAN1_Transmit();
		}
	}
#if CAN_FUN_CHERY_ARRIZO_6==1	
	if((CanTxTimer%10)==0)
	{
	    if(F_CAN_INIT)
	    {	        
	        Tiggo7_TxMedia();
	    }
	}
#endif	
    if(Get_ACC_Det_Flag)
    {
        if(CanNMmBCM_TimerCounter==0)
        {
            CanNMmBCM_TimerCounter=T1S_1;
            if(CanNMmBCM_SendStaus)
            {
                Tiggo7_PostMessage(CAN_POST_MSG_NMM_RRM);
            }
        }
    }
	switch(CanMainState)
	{
		case CAN_MAIN_IDLE:
			F_CAN_INIT=0;
			CanMainState=CAN_MAIN_CFG;
			break;
		case CAN_MAIN_CFG:
			CAN1_Init();
			FormatMemery(&CanTxInfo.rrm_1_info.byte_1.byte,sizeof(CanTxInfo));
#if MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
			// 复位后恢复默认设置,ACR客户要求
			CanTxInfo.rrm_1_info.byte_1.field.f_auto_lock=1;
			CanTxInfo.rrm_1_info.byte_1.field.f_remote_lock_feedback=1;
			CanTxInfo.rrm_1_info.byte_2.field.f_drl=1;
			CanTxInfo.rrm_1_info.byte_2.field.f_head_light_delay=1;
			CanTxInfo.rrm_1_info.byte_8.field.f_mirror_auto_fold=1;

			CanTxInfo.rrm_6_info.byte_5.field.f_side_view=1;
			CanTxInfo.rrm_6_info.byte_6.field.f_3d_around_view=1;
			CanTxInfo.rrm_6_info.byte_6.field.f_trajectory=2;

#if MODEL==LINUX_Q068A_21
			CanTxInfo.rrm_3_info.byte_67.field.f_year=0x7F;
			CanTxInfo.rrm_3_info.byte_67.field.f_month=0x00;
			CanTxInfo.rrm_3_info.byte_67.field.f_day=0x00;
#endif
			CanTxInfo.rrm_3_info.hour=0xFF;
			CanTxInfo.rrm_3_info.min=0xFF;
			CanTxInfo.rrm_3_info.second=0xFF;
			CanTxInfo.rrm_3_info.instrument_back_light=10;
#endif
			CanMainState=CAN_MAIN_INIT;
			break;
		case CAN_MAIN_INIT:
			CAN1_ClearTxMessage();
			FormatMemery(&CanRxInfo.air_info.byte_1.byte,sizeof(CanRxInfo));
			FormatMemery(&CanRxInfoBak.air_info.byte_1.byte,sizeof(CanRxInfoBak));
			FormatMemery(&CanTxInfoBak.rrm_1_info.byte_1.byte,sizeof(CanTxInfoBak));
			FormatMemery(&AirConditionInfoBak.display,sizeof(AirConditionInfoBak));
			FormatMemery(&Media_ID3_Info.tx_ready,sizeof(Media_ID3_Info));
			//F_CAN_SLEEP=0;
			F_CAN_SLEEP=1;
			F_CAN_RX_DATA=1;
			F_CAN_INTERRUPT=0;
			F_CAN_READY=0;
			F_DRIVER_DOOR_STATE=0;
			F_AVM_CALIBRATION=0;
			F_CAN_RX_AIR_INFO=0;
#if MODEL==LINUX_Q068_00
			RTC_TimeInfo.year=0x00; 	 
			RTC_TimeInfo.month=1;	
			RTC_TimeInfo.day=1;    
			RTC_TimeInfo.hours=0;		
			RTC_TimeInfo.minutes=0; 	  
			RTC_TimeInfo.seconds=0; 
			RTC_TimeInfo.week_day=6;		
#endif
			CanNoDataTimer=T60S_1;
			CanMainState=CAN_MAIN_WAIT_ACC;
			CanMainTimer=T2S_1;
			CanTimeSyncDelay=4;
			CanNMmBCM_SendStaus=0;
			break;
		case CAN_MAIN_WAIT_ACC:
			if(Get_ACC_Det_Flag)
			{
				CanMainState=CAN_MAIN_TX_POWER_OFF;
#if MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
				// 复位后恢复默认设置,ACR客户要求
				if(F_Mcu_Restart)
				{
					CanTxInfo.rrm_1_info.byte_34.field.f_over_speed=0x3F;
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
					CanTxInfo.rrm_1_info.byte_34.field.f_over_speed = 0x00;
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_3);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_3);
					Tiggo7_PostMessage(CAN_POST_MSG_RRM_3);
				}
#endif
			}
			else if(CanMainTimer==0)
			{
				CanMainState=CAN_MAIN_WAIT_SLEEP;
			}
			break;
		case CAN_MAIN_TX_POWER_OFF:
			FormatMemery(&CanTxInfo.rrm_2_info.byte_1.byte,sizeof(CAN_RRM_2_INFO));
			Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
			CanMainState=CAN_MAIN_TX_POWER_ON;
			CanMainTimer=T2S_1;
			break;
		case CAN_MAIN_TX_POWER_ON:
			if(CanMainTimer)
			{
				break;
			}
			CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
			Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
			CanMainState=CAN_MAIN_TX_MEDIA_1;
			CanMainTimer=T2S_1;
			break;
		case CAN_MAIN_TX_MEDIA_1:
			if(CanMainTimer)
			{
				break;
			}
			CanTxInfo.rrm_5_info[0]=0x03;
			CanTxInfo.rrm_5_info[1]=0x01;
			CanTxInfo.rrm_5_info[2]=0x01;
			CanTxInfo.rrm_5_info[3]=0x01;
			CanTxInfo.rrm_5_info[4]=0x00;
			CanTxInfo.rrm_5_info[5]=0x00;
			CanTxInfo.rrm_5_info[6]=0x00;
			CanTxInfo.rrm_5_info[7]=0x00;
			Tiggo7_PostMessage(CAN_POST_MSG_RRM_5);
			CanMainState=CAN_MAIN_TX_MEDIA_2;
			CanMainTimer=T2S_1;
			break;
		case CAN_MAIN_TX_MEDIA_2:
			if(CanMainTimer)
			{
				break;
			}
			CanTxInfo.rrm_5_info[0]=0x03;
			CanTxInfo.rrm_5_info[1]=0x03;
			CanTxInfo.rrm_5_info[2]=0x01;
			CanTxInfo.rrm_5_info[3]=0x01;
			CanTxInfo.rrm_5_info[4]=0x00;
			CanTxInfo.rrm_5_info[5]=0x00;
			CanTxInfo.rrm_5_info[6]=0x00;
			CanTxInfo.rrm_5_info[7]=0x00;
			Tiggo7_PostMessage(CAN_POST_MSG_RRM_5);
			CanMainState=CAN_MAIN_NORMAL;
			FictitiousPowerOffFlag=F_FICTITIOUS_POWER_OFF;
			break;
		case CAN_MAIN_NORMAL:
#if CAN_WAKEUP_FUN==1
			if(F_CAN_RX_DATA==0)
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}
			else 
#endif
			if(Get_ACC_Det_Flag==0)
			{
				CanMainState=CAN_MAIN_WAIT_SLEEP;
			}
			else
			{
				if(APP_READY==APP_Status)
				{
					if(!strcmp_equal(&CanRxInfo.air_info.byte_1.byte,&CanRxInfoBak.air_info.byte_1.byte,sizeof(CAN_AIR_INFO))
#if MODEL==LINUX_Q068_21
						&&CanAirInfoTimer==0
#endif
						)
					{
						Mem_strcpy(&CanRxInfoBak.air_info.byte_1.byte,&CanRxInfo.air_info.byte_1.byte,sizeof(CAN_AIR_INFO));
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AIR_INFO);
#if CAN_DEBUG_FUN==1
						printf("MCU_TX_CAN_BOX_INFO:CHERY_TIGGO7_RX_AIR_INFO\r\n");
#endif
					}
					if(!strcmp_equal(&CanRxInfo.avm_info.avm_exist,&CanRxInfoBak.avm_info.avm_exist,sizeof(CAN_AVM_INFO)))
					{
						Mem_strcpy(&CanRxInfoBak.avm_info.avm_exist,&CanRxInfo.avm_info.avm_exist,sizeof(CAN_AVM_INFO));
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AVM_INFO);
#if CAN_DEBUG_FUN==1
						printf("MCU_TX_CAN_BOX_INFO:CHERY_TIGGO7_RX_AVM_INFO\r\n");
#endif
					}
					if(!strcmp_equal(&CanRxInfo.ctrl_feedback_info.enable_flag1.byte,&CanRxInfoBak.ctrl_feedback_info.enable_flag1.byte,sizeof(CAN_CTRL_FEEDBACK_INFO)))
					{
						Mem_strcpy(&CanRxInfoBak.ctrl_feedback_info.enable_flag1.byte,&CanRxInfo.ctrl_feedback_info.enable_flag1.byte,sizeof(CAN_CTRL_FEEDBACK_INFO));
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_CONTROL_INFO);
#if CAN_DEBUG_FUN==1
						printf("MCU_TX_CAN_BOX_INFO:CHERY_TIGGO7_RX_CONTROL_INFO\r\n");
#endif
					}
					if(CanTxAppTimer==0)
					{
						CanTxAppTimer=T5S_1;
#if MODEL==LINUX_Q068_21
						if(CanAirInfoTimer==0)
#endif
						{
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AIR_INFO);
						}
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_CONTROL_INFO);
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_AVM_INFO);
						PostMessage(NAVI_MODULE,MCU_TX_CAN_BOX_INFO,CHERY_TIGGO7_RX_DRIVING_INFO);
#if CAN_DEBUG_FUN==1
						printf("MCU_TX_CAN_BOX_INFO:period==5s \r\n");
#endif
					}
				}
				if(CanTxCanTimer==0)
				{
					CanTxCanTimer=T500MS_1;
					if(F_CAN_READY)
					{
#if MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
						if(FictitiousPowerOffFlag!=F_FICTITIOUS_POWER_OFF)
						{
							FictitiousPowerOffFlag=F_FICTITIOUS_POWER_OFF;
						if(F_FICTITIOUS_POWER_OFF)
						{
							if(CanTxInfo.rrm_2_info.byte_1.field.f_source)
							{
							CanTxInfoBak.rrm_2_info.byte_1.field.f_source=CanTxInfo.rrm_2_info.byte_1.field.f_source;
							}
							CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x00;
							CanTxInfo.rrm_2_info.byte_1.field.f_source=0x00;
						}
						else
						{
							CanTxInfo.rrm_2_info.byte_1.field.f_rrm_on=0x01;
								if(CanTxInfoBak.rrm_2_info.byte_1.field.f_source)
							{
								CanTxInfo.rrm_2_info.byte_1.field.f_source=CanTxInfoBak.rrm_2_info.byte_1.field.f_source;
								}
								if(1)
								{
									Media_ID3_Info.tx_ready=0x01;
									Media_ID3_Info.tx_line=0x00;
									Media_ID3_Info.pack_num=0x00;
									Media_tx_num=0;
								}
							}
						}
#endif
#if CAN_FUN_CHERY_TIGGO_3==1||CAN_FUN_CHERY_TIGGO_2==1
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);				
#elif CAN_FUN_CHERY_TIGGO_5==1
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
    					if(F_CAN_RX_AIR_INFO)
    					{
    						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
    					}
#elif CAN_FUN_CHERY_TIGGO_7==1
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
						if(F_CAN_RX_AIR_INFO
#if MODEL==LINUX_Q068_21
							&&CanTxAirTimer==0
#endif
						)
    					{
    						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
    					}
#elif CAN_FUN_CHERY_ARRIZO_6==1
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_6);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_9);
    					if(F_CAN_RX_AIR_INFO)
    					{
    						Tiggo7_PostMessage(CAN_POST_MSG_RRM_4);
    					}	
#elif CAN_FUN_CHERY_ARRIZO_5==1
    	    			Tiggo7_PostMessage(CAN_POST_MSG_RRM_1);
    					Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);	
#endif
					}
				}
				if(CanTurnOnVolume!=TurnOn_Volume)
				{
				    CanTurnOnVolume = TurnOn_Volume;
				    CanTxInfo.rrm_2_info.volume=TurnOn_Volume;
				    Tiggo7_PostMessage(CAN_POST_MSG_RRM_2);
				}
				Tiggo7_TxMediaInfoPro();
			}
			break;
		case CAN_MAIN_WAIT_SLEEP:
#if CAN_WAKEUP_FUN==1
			if(F_CAN_RX_DATA==0)
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}

			if(Get_ACC_Det_Flag==1)
			{	
#if MODEL==LINUX_Q068A_21||MODEL==LINUX_Q068_21
				CanMainState=CAN_MAIN_INIT;
#else
				CanMainState=CAN_MAIN_NORMAL;
				FictitiousPowerOffFlag=F_FICTITIOUS_POWER_OFF;
#endif
			}
#else
			if(Get_ACC_Det_Flag==1)
			{	
				CanMainState=CAN_MAIN_NORMAL;
				FictitiousPowerOffFlag=F_FICTITIOUS_POWER_OFF;
			}
			else
			{
				CanMainState=CAN_MAIN_SLEEP_CFG;
			}
#endif

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
#if CAN_WAKEUP_FUN==1
			if(F_CAN_SLEEP==0
				||F_CAN_INTERRUPT)
#else
			if(Get_ACC_Det_Flag==1)
#endif
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

