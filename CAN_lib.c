#include "public.h"

#if CAN_FUNCTION==1
u32 CanErrorTimer;

void CAN1_SetErrorTimer(void)
{
	CanErrorTimer=T300S_1;
}

void CAN1_ClearErrorTimer(void)
{
	CanErrorTimer=0;
}

void CAN1_TxFrame(u32 ID,u8 *array,u8 length)
{
	u32 i = 0;

	if(CanTxBuffer.length<CAN_TX_BUFFER_LENGTH
		&&length<=8)
	{
		CanTxBuffer.message[CanTxBuffer.tail].ID=ID;
		CanTxBuffer.message[CanTxBuffer.tail].IDE=CAN_IDE_STD;
		CanTxBuffer.message[CanTxBuffer.tail].RTR=CAN_RTR_STD;
		CanTxBuffer.message[CanTxBuffer.tail].DLC=length;
		for(i=0;i<length;i++)
		{
			CanTxBuffer.message[CanTxBuffer.tail].Data[i]=array[i];
		}
		CanTxBuffer.tail=(CanTxBuffer.tail+1)%CAN_TX_BUFFER_LENGTH;
		CanTxBuffer.length++;
	}
}

#if CAN_FUN_TRUMPCHI==1||CAN_FUN_HAIMA_S7_360==1
void CAN2_TxFrame(u32 ID,u8 *array,u8 length)
{
	u32 i = 0;

	if(CanTxBuffer2.length<CAN_TX_BUFFER_LENGTH
		&&length<=8)
	{
		CanTxBuffer2.message[CanTxBuffer2.tail].ID=ID;
		CanTxBuffer2.message[CanTxBuffer2.tail].IDE=CAN_IDE_STD;
		CanTxBuffer2.message[CanTxBuffer2.tail].RTR=CAN_RTR_STD;
		CanTxBuffer2.message[CanTxBuffer2.tail].DLC=length;
		for(i=0;i<length;i++)
		{
			CanTxBuffer2.message[CanTxBuffer2.tail].Data[i]=array[i];
		}
		CanTxBuffer2.tail=(CanTxBuffer2.tail+1)%CAN_TX_BUFFER_LENGTH;
		CanTxBuffer2.length++;
	}
}
#endif
void CAN1_Ext_TxFrame(u32 ID,u8 *array,u8 length)
{
	u32 i = 0;
	
if(ID==0x1CEBFFFB||ID==0x1CECFFFB)
{
#if MODEL==ANDROID_Q133_00||MODEL==ANDROID_Q133_01||MODEL== ANDROID_Q133_uni
	if(CanTxBuffer3.length<CAN_TX_BUFFER_LENGTH
		&&length<=8)
	{
		CanTxBuffer3.message[CanTxBuffer3.tail].ID=ID;
		CanTxBuffer3.message[CanTxBuffer3.tail].IDE=CAN_IDE_EXT;
		CanTxBuffer3.message[CanTxBuffer3.tail].RTR=CAN_RTR_STD;
		CanTxBuffer3.message[CanTxBuffer3.tail].DLC=length;
		for(i=0;i<length;i++)
		{
			CanTxBuffer3.message[CanTxBuffer3.tail].Data[i]=array[i];

			if(ID==0x1CEBFFFB||ID==0x1CECFFFB)
			{
				if(CanTxBuffer3.message[CanTxBuffer3.tail].Data[i]==0)
				{
					if(DM1_flag==0)
					{
						if(dm_flag==2)
						{
							CanTxBuffer3.message[CanTxBuffer3.tail].Data[i]=0xff;
						}
					}
				}
				
			}

		}
		CanTxBuffer3.tail=(CanTxBuffer3.tail+1)%CAN_TX_BUFFER_LENGTH;
		CanTxBuffer3.length++;
	}
	
}
else if(ID==0x18ff50fb)
{
	if(CanTxBuffer4.length<CAN_TX_BUFFER_LENGTH
		&&length<=8)
		{
			CanTxBuffer4.message[CanTxBuffer4.tail].ID=ID;
			CanTxBuffer4.message[CanTxBuffer4.tail].IDE=CAN_IDE_EXT;
			CanTxBuffer4.message[CanTxBuffer4.tail].RTR=CAN_RTR_STD;
			CanTxBuffer4.message[CanTxBuffer4.tail].DLC=length;
			
			for(i=0;i<length;i++)
			{
				CanTxBuffer4.message[CanTxBuffer4.tail].Data[i]=array[i];
			}
			
			CanTxBuffer4.tail=(CanTxBuffer4.tail+1)%CAN_TX_BUFFER_LENGTH;
			CanTxBuffer4.length++;
	}
	
}
else if(ID==0x18FECAFB)
{
	if(CanTxBuffer5.length<CAN_TX_BUFFER_LENGTH
		&&length<=8)
		{
			CanTxBuffer5.message[CanTxBuffer5.tail].ID=ID;
			CanTxBuffer5.message[CanTxBuffer5.tail].IDE=CAN_IDE_EXT;
			CanTxBuffer5.message[CanTxBuffer5.tail].RTR=CAN_RTR_STD;
			CanTxBuffer5.message[CanTxBuffer5.tail].DLC=length;
			
			for(i=0;i<length;i++)
			{
				CanTxBuffer5.message[CanTxBuffer5.tail].Data[i]=array[i];
			}
			
			CanTxBuffer5.tail=(CanTxBuffer5.tail+1)%CAN_TX_BUFFER_LENGTH;
			CanTxBuffer5.length++;
	}
	
}
else if(ID==0x18dafafb)
{
	if(CanTxBuffer6.length<CAN_TX_BUFFER_LENGTH
		&&length<=8)
		{
			CanTxBuffer6.message[CanTxBuffer6.tail].ID=ID;
			CanTxBuffer6.message[CanTxBuffer6.tail].IDE=CAN_IDE_EXT;
			CanTxBuffer6.message[CanTxBuffer6.tail].RTR=CAN_RTR_STD;
			CanTxBuffer6.message[CanTxBuffer6.tail].DLC=length;
			
			for(i=0;i<length;i++)
			{
				CanTxBuffer6.message[CanTxBuffer6.tail].Data[i]=array[i];
			}
			
			CanTxBuffer6.tail=(CanTxBuffer6.tail+1)%CAN_TX_BUFFER_LENGTH;
			CanTxBuffer6.length++;
	}
	#endif
}
else
{
	if(CanTxBuffer.length<CAN_TX_BUFFER_LENGTH
		&&length<=8)
	{
		CanTxBuffer.message[CanTxBuffer.tail].ID=ID;
		CanTxBuffer.message[CanTxBuffer.tail].IDE=CAN_IDE_EXT;
		CanTxBuffer.message[CanTxBuffer.tail].RTR=CAN_RTR_STD;
		CanTxBuffer.message[CanTxBuffer.tail].DLC=length;
		for(i=0;i<length;i++)
		{
			CanTxBuffer.message[CanTxBuffer.tail].Data[i]=array[i];
		}
		
		CanTxBuffer.tail=(CanTxBuffer.tail+1)%CAN_TX_BUFFER_LENGTH;
		CanTxBuffer.length++;
	}
}
}
void CAN1_RTR_TxFrame(u32 ID,u8 IDE,u8 RTR,u8 *array,u8 length)
{
	u32 i = 0;
	if(CanTxBuffer.length<CAN_TX_BUFFER_LENGTH
		&&length<=8)
	{
		CanTxBuffer.message[CanTxBuffer.tail].ID=ID;
		CanTxBuffer.message[CanTxBuffer.tail].IDE=IDE;
		CanTxBuffer.message[CanTxBuffer.tail].RTR=RTR;
		CanTxBuffer.message[CanTxBuffer.tail].DLC=length;
		for(i=0;i<length;i++)
		{
			CanTxBuffer.message[CanTxBuffer.tail].Data[i]=array[i];
		}
		CanTxBuffer.tail=(CanTxBuffer.tail+1)%CAN_TX_BUFFER_LENGTH;
		CanTxBuffer.length++;
	}
}
void CAN1_ClearTxMessage(void)
{
	u32 i;
	u32 j;

	for(i=0;i<CAN_TX_BUFFER_LENGTH;i++)
	{
		CanTxBuffer.message[i].ID=0;
		CanTxBuffer.message[i].IDE=CAN_IDE_STD;
		CanTxBuffer.message[i].RTR=CAN_RTR_STD;
		CanTxBuffer.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanTxBuffer.message[i].Data[j]=0;
		}
	}
	CanTxBuffer.head=0;
	CanTxBuffer.tail=0;
	CanTxBuffer.length=0;
}
#if CAN_FUN_TRUMPCHI==1||CAN_FUN_HAIMA_S7_360==1
void CAN2_ClearTxMessage(void)
{
	u32 i;
	u32 j;
	for(i=0;i<CAN_TX_BUFFER_LENGTH;i++)
	{
		CanTxBuffer2.message[i].ID=0;
		CanTxBuffer2.message[i].IDE=CAN_IDE_STD;
		CanTxBuffer2.message[i].RTR=CAN_RTR_STD;
		CanTxBuffer2.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanTxBuffer2.message[i].Data[j]=0;
		}
	}
	CanTxBuffer2.head=0;
	CanTxBuffer2.tail=0;
	CanTxBuffer2.length=0;
}
#endif
void CAN1_Ext_ClearTxMessage(void)
{
	u32 i;
	u32 j;
	for(i=0;i<CAN_TX_BUFFER_LENGTH;i++)
	{
		CanTxBuffer.message[i].ID=0;
		CanTxBuffer.message[i].IDE=CAN_IDE_EXT;
		CanTxBuffer.message[i].RTR=CAN_RTR_STD;
		CanTxBuffer.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanTxBuffer.message[i].Data[j]=0;
		}
#if MODEL==ANDROID_Q133_00||MODEL==ANDROID_Q133_01||MODEL== ANDROID_Q133_uni
		CanTxBuffer3.message[i].ID=0;
		CanTxBuffer3.message[i].IDE=CAN_IDE_EXT;
		CanTxBuffer3.message[i].RTR=CAN_RTR_STD;
		CanTxBuffer3.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanTxBuffer3.message[i].Data[j]=0;
		}
		
		CanTxBuffer4.message[i].ID=0;
		CanTxBuffer4.message[i].IDE=CAN_IDE_EXT;
		CanTxBuffer4.message[i].RTR=CAN_RTR_STD;
		CanTxBuffer4.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanTxBuffer4.message[i].Data[j]=0;
		}
		
		CanTxBuffer5.message[i].ID=0;
		CanTxBuffer5.message[i].IDE=CAN_IDE_EXT;
		CanTxBuffer5.message[i].RTR=CAN_RTR_STD;
		CanTxBuffer5.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanTxBuffer5.message[i].Data[j]=0;
		}
		
		CanTxBuffer6.message[i].ID=0;
		CanTxBuffer6.message[i].IDE=CAN_IDE_EXT;
		CanTxBuffer6.message[i].RTR=CAN_RTR_STD;
		CanTxBuffer6.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanTxBuffer6.message[i].Data[j]=0;
		}
	}
	CanTxBuffer6.head=0;
	CanTxBuffer6.tail=0;
	CanTxBuffer6.length=0;
	CanTxBuffer5.head=0;
	CanTxBuffer5.tail=0;
	CanTxBuffer5.length=0;
	CanTxBuffer4.head=0;
	CanTxBuffer4.tail=0;
	CanTxBuffer4.length=0;
	CanTxBuffer3.head=0;
	CanTxBuffer3.tail=0;
	CanTxBuffer3.length=0;
	CanTxBuffer.head=0;
	CanTxBuffer.tail=0;
	CanTxBuffer.length=0;	
#else
	}
	CanTxBuffer.head=0;
	CanTxBuffer.tail=0;
	CanTxBuffer.length=0;
#endif


}
#if MODEL==ANDROID_Q133_00||MODEL==ANDROID_Q133_01||MODEL== ANDROID_Q133_uni
void CAN1_Ext_ClearBufferTxMessage(void)
{
	u32 i;
	u32 j;
	for(i=0;i<CAN_TX_BUFFER_LENGTH;i++)
	{
		CanTxBuffer4.message[i].ID=0;
		CanTxBuffer4.message[i].IDE=CAN_IDE_EXT;
		CanTxBuffer4.message[i].RTR=CAN_RTR_STD;
		CanTxBuffer4.message[i].DLC=0;
		
		
		for(j=0;j<8;j++)
		{
			CanTxBuffer4.message[i].Data[j]=0;
		}

	}
	CanTxBuffer4.head=0;
	CanTxBuffer4.tail=0;
	CanTxBuffer4.length=0;

}

#endif
void CAN1_RTR_ClearTxMessage(u8 IDE,u8 RTR)
{
	u32 i;
	u32 j;
	for(i=0;i<CAN_TX_BUFFER_LENGTH;i++)
	{
		CanTxBuffer.message[i].ID=0;
		CanTxBuffer.message[i].IDE=IDE;
		CanTxBuffer.message[i].RTR=RTR;
		CanTxBuffer.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanTxBuffer.message[i].Data[j]=0;
		}
	}
	CanTxBuffer.head=0;
	CanTxBuffer.tail=0;
	CanTxBuffer.length=0;
}

void CAN1_ClearRxMessage(void)
{
	u32 i;
	u32 j;

	for(i=0;i<CAN_RX_BUFFER_LENGTH;i++)
	{
		CanRxBuffer.message[i].ID=0;
		CanRxBuffer.message[i].IDE=CAN_IDE_STD;
		CanRxBuffer.message[i].RTR=CAN_RTR_STD;
		CanRxBuffer.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanRxBuffer.message[i].Data[j]=0;
		}
	}
	CanRxBuffer.head=0;
	CanRxBuffer.tail=0;
}

#if CAN_FUN_TRUMPCHI==1
void CAN2_ClearRxMessage(void)
{
	u32 i;
	u32 j;
	for(i=0;i<CAN_RX_BUFFER_LENGTH;i++)
	{
		CanRxBuffer2.message[i].ID=0;
		CanRxBuffer2.message[i].IDE=CAN_IDE_STD;
		CanRxBuffer2.message[i].RTR=CAN_RTR_STD;
		CanRxBuffer2.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanRxBuffer2.message[i].Data[j]=0;
		}
	}
	CanRxBuffer2.head=0;
	CanRxBuffer2.tail=0;
}
#endif

void CAN1_Ext_ClearRxMessage(void)
{
	u32 i;
	u32 j;
	for(i=0;i<CAN_RX_BUFFER_LENGTH;i++)
	{
		CanRxBuffer.message[i].ID=0;
		CanRxBuffer.message[i].IDE=CAN_IDE_EXT;
		CanRxBuffer.message[i].RTR=CAN_RTR_STD;
		CanRxBuffer.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanRxBuffer.message[i].Data[j]=0;
		}
	}
	CanRxBuffer.head=0;
	CanRxBuffer.tail=0;
}
void CAN1_RTR_ClearRxMessage(u8 IDE,u8 RTR)
{
	u32 i;
	u32 j;
	for(i=0;i<CAN_RX_BUFFER_LENGTH;i++)
	{
		CanRxBuffer.message[i].ID=0;
		CanRxBuffer.message[i].IDE=IDE;
		CanRxBuffer.message[i].RTR=RTR;
		CanRxBuffer.message[i].DLC=0;
		for(j=0;j<8;j++)
		{
			CanRxBuffer.message[i].Data[j]=0;
		}
	}
	CanRxBuffer.head=0;
	CanRxBuffer.tail=0;
}
#endif
