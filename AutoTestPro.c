#include "public.h"
#if FACTORY_AUTO_TEST_FUN==1

AUTO_TEST_RX_STATE AutoTestRxState;
AUTO_TEST_FLAG AutoTestFlag;
MEDIAPLAYINFO MediaPlayInfo;
UNIT_CODE_DATA UnitCodeData;
AUTO_TEST_BT_INFO AutoTestBtInfo;
AUTO_TEST_WIFI_FLAG AutoTestWifiFlag;
u8 AutoTestTxBuffer[AUTO_TEST_TX_MAX_LENGTH];
u8 AutoTestRxBuffer[AUTO_TEST_RX_MAX_LENGTH];
u8 AutoTestAppVersion[APP_VERSION_MAX_LENGTH];
u8 AutoTestOsVersion[OS_VERSION_MAX_LENGTH];
u8 AutoTestDvpVersion[DVP_VERSION_MAX_LENGTH];
u8 AutoTestServoVersion[SERVO_VERSION_MAX_LENGTH];
u8 AutoTestBTAddr[6];
u8 AutoTestBTCheckAddr[6];
u8 AutoTestIP_Addr[15];
u8 AutoTestWifiSSID[WIFI_SSID_MAX_LENGTH];
u8 AutoTestWifiPassword[WIFI_PASSWORD_MAX_LENGTH];
u8 PARAM_LENGTH;
u8 *AutoTest_RxPtr;
u8 *AutoTest_TxPtr;
u8 AutoTest_RxLength;
u8 Autotest_TxLength;
u8 Autotest_RxCounter;
u8 Autotest_ErCounter;
u8 Autotest_KeyCode;
u8 GetVersionTimer;
u8 GetVersionCounter;
u16 AutoTestBandTimer;
u8 SCREEN_SUB_COMMAND;
u8 AutoTestRxAppBuffer[AUTO_TEST_RX_APP_LENGTH];
u8 CMD_WaitForSend;
u8 WaitAppTimer;

u8 AutoTestModeFlag;

#if MODEL == LINUX_1465_16
const KEY_INFO AutoTest_StudySteerKeyTab[2][STUDY_STEER_KEY_NUM] =
{
	{
		{4095,					4095,			NO_KEY,							NO_KEY, 						0},
		{0,						0,				UICC_VOLUME_UP,					UICC_VOLUME_UP,					3},
		{0,						1688, 			UICC_VOLUME_DOWN,				UICC_VOLUME_DOWN, 				3},
		{111,					2786,			UICC_SKIPB,						UICC_PREV_LONG,					7},
		{383,					3571, 			UICC_SKIPF,						UICC_NEXT_LONG,					7},
		{4095,					4095,			NO_KEY,							NO_KEY, 						0},
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
	},
	{
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
		{0,						2603,			UICC_SOURCE,					NO_KEY,							0},
		{385,			    	3584,	    	UICC_MUTE,						NO_KEY,							0},
		{637,					3778,			UICC_BT_ACPTCALL,				NO_KEY,							0},
		{942,					3894, 			UICC_BT_HUNGUPCALL,				NO_KEY,							0},
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
		{4095,					4095,			NO_KEY,							NO_KEY, 						0},
		{4095,					4095,			NO_KEY, 						NO_KEY, 						0},
	},
};
#endif

void AutoTestEnterRxInterrupt(u8 data)
{
	F_AUTOTEST_READY=1;
	AutoTestRxState=AUTO_TEST_RX_HEADCODE2;
	AutoTest_RxPtr=AutoTestRxBuffer;					
	*AutoTest_RxPtr=data;
	AutoTest_RxPtr++;
}

void AutoTestEnableRxInterrupt(void)
{
	F_AUTOTEST_READY=0;
	F_AUTOTEST_RX_OK=0;
	AutoTestRxState=AUTO_TEST_RX_HEADCODE1;
}

void AutoTestUartTxFormat(u8 *pbuf, u8 length)
{
#if defined(AUTOCHIPS_AC781X)
	UART6_SendData(pbuf,length);
#elif defined(HDSC_HC32F460)
	UART4_SendData(pbuf,length);
#elif defined(HDSC_HC32L072)
	UART0_SendData(pbuf,length);
#elif defined(STM32_F103VC)
	UART3_SendData(pbuf,length);
#elif defined(STM32F401xx)
	UART2_SendData(pbuf,length);
#endif
}

u8 AutoAscii2Hex(u8 data)
{
	u8 i;
	
	if('A'==data) 
	{
		i=0x0A;
	}
	else if('B'==data) 
	{
		i=0x0B;
	}
	else if('C'==data) 
	{
		i=0x0C;
	}
	else if('D'==data) 
	{
		i=0x0D;
	}
	else if('E'==data)
	{
		i=0x0E;
	}
	else if('F'==data)
	{
		i=0x0F;
	}
	else 
	{
		i=data&0x0F;
	}
	return i;	
}

u8 AutoHex2Ascii(u8 data)
{
	u8 k;
	
	if(0x0A==data) 
	{
		k='A';
	}
	else if(0x0B==data) 
	{
		k='B';
	}
	else if(0x0C==data) 
	{
		k='C';
	}
	else if(0x0D==data) 
	{
		k='D';
	}
	else if(0x0E==data)
	{
		k='E';
	}
	else if(0x0F==data)
	{
		k='F';
	}
	else
	{
		k=data+'0';
	}
	return k;
}

void AutoTestRxInterrupt(u8 data)
{
	
	if(AUTO_TEST_HEADCODE1_0==data||AUTO_TEST_HEADCODE1_1==data)
	{
		if(0==F_AUTOTEST_READY)	
		{
			AutoTestEnterRxInterrupt(data);
			return;
		}
	}

	if(0==F_AUTOTEST_READY||1==F_AUTOTEST_RX_OK)
	{
		return; 
	}
	
	if(AutoTestRxState>AUTO_TEST_RX_CHECKSUM1)
	{
		AutoTestRxState=AUTO_TEST_RX_HEADCODE1;
	}
	
	switch(AutoTestRxState)
	{
		case AUTO_TEST_RX_HEADCODE1:				
		case AUTO_TEST_RX_HEADCODE2:
			if(AUTO_TEST_HEADCODE1_0==data||AUTO_TEST_HEADCODE1_1==data)
			{
			}
			else if(AUTO_TEST_HEADCODE2_0==data||AUTO_TEST_HEADCODE2_1==data)
			{				
				*AutoTest_RxPtr=data;
				AutoTest_RxPtr++;
				AutoTestRxState=AUTO_TEST_RX_LENGTH;	
			}
			else
			{
				AutoTestRxState=AUTO_TEST_RX_HEADCODE1;
				F_AUTOTEST_READY=0;
			}
			break;
		case AUTO_TEST_RX_LENGTH:
			*AutoTest_RxPtr=data;
			AutoTest_RxPtr++;
			AutoTest_RxLength=AutoAscii2Hex(data);
			AutoTest_RxLength=AutoTest_RxLength*16;
			AutoTestRxState=AUTO_TEST_RX_LENGTH1;
			break;
		case AUTO_TEST_RX_LENGTH1:
			*AutoTest_RxPtr=data;
			AutoTest_RxPtr++;
			AutoTest_RxLength+=AutoAscii2Hex(data);			
			if((AutoTest_RxLength>(AUTO_TEST_RX_MAX_LENGTH-6))||(AutoTest_RxLength<2))
			{
				AutoTestRxState=AUTO_TEST_RX_HEADCODE1;
				F_AUTOTEST_READY=0;	
			}
			else if(AutoTest_RxLength==2)
			{
				AutoTestRxState=AUTO_TEST_RX_CHECKSUM;
			}
			else
			{
				AutoTestRxState=AUTO_TEST_RX_CMD;
			}
			break;
		case AUTO_TEST_RX_CMD:
			*AutoTest_RxPtr=data;
			AutoTest_RxPtr++;
			AutoTestRxState=AUTO_TEST_RX_CMD1;				
			break;
		case AUTO_TEST_RX_CMD1:
			*AutoTest_RxPtr=data;
			AutoTest_RxPtr++;
			AutoTest_RxLength-=2;
			AutoTestRxState=AUTO_TEST_RX_DATA;				
			break;
		case AUTO_TEST_RX_DATA:
			*AutoTest_RxPtr=data;
			AutoTest_RxPtr++;
			AutoTest_RxLength--;
			if(0==AutoTest_RxLength)
			{
				AutoTestRxState=AUTO_TEST_RX_CHECKSUM;	
			}
			break;
		case AUTO_TEST_RX_CHECKSUM:
			*AutoTest_RxPtr=data;
			AutoTest_RxPtr++;
			AutoTestRxState=AUTO_TEST_RX_CHECKSUM1;
			break;
		case AUTO_TEST_RX_CHECKSUM1:
			*AutoTest_RxPtr=data;
			AutoTest_RxPtr++;
			AutoTestRxState=AUTO_TEST_RX_HEADCODE1;
			F_AUTOTEST_RX_OK=1;
			break;
		default:
			AutoTestRxState=AUTO_TEST_RX_HEADCODE1;
			F_AUTOTEST_RX_OK=0;
			break;
	}	
}

u8 AutoTestCheckSum(void)
{
	u8 i;
	u8 j;
	u8 k;
	u8 n;
	
	j=AutoAscii2Hex(AutoTestRxBuffer[3]);
	i=AutoAscii2Hex(AutoTestRxBuffer[2]);
	i<<=4;
	i=i+j;  
	PARAM_LENGTH=i-3;
	j=3+i; //数据帧的最后一字节
	n=j+2;//校验字节的最后一字节
	k=0;
	for(;;)
	{
		k=k+AutoTestRxBuffer[j];
		--j;
		--i;
		if(i==0) 
		{
			break;
		}
	}
	j=AutoAscii2Hex(AutoTestRxBuffer[n]);
	--n;
	i=AutoAscii2Hex(AutoTestRxBuffer[n]);
	i<<=4;
	i=i+j; 
	if(k==i) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

void AutoTestTxCmd(u8 module,u8 cmd, u8 data,u8 data1)
{
	u8 i;
	u8 j;
	
	AutoTestTxBuffer[0]='S';
	AutoTestTxBuffer[1]='T';
	AutoTestTxBuffer[2]='0';
	AutoTestTxBuffer[3]='5';
	AutoTestTxBuffer[4]=module;
	AutoTestTxBuffer[5]=cmd;
	i=Autotest_RxCounter;
	i++;
	if(i>10) 
	{
		i=i-10;
	}
	i=AutoHex2Ascii(i);
	AutoTestTxBuffer[6]=i;
	AutoTestTxBuffer[7]=data;
	AutoTestTxBuffer[8]=data1;
	AutoTest_TxPtr=&AutoTestTxBuffer[4];
	j=0;
	for(i=0;i<5;i++)
	{
		j+=*AutoTest_TxPtr;
		++AutoTest_TxPtr;
	}
	i=j&0xF0;
	i=i/16;
	j=j&0x0F;
	AutoTestTxBuffer[9]=AutoHex2Ascii(i);
	AutoTestTxBuffer[10]=AutoHex2Ascii(j);
}

void AutoTestReTxCmd(void)
{
	if(Autotest_TxLength<AUTO_TEST_TX_CMD_LENGTH) 
	{
		Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
	}
	
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestAskFrontSource(u8 module)
{
	u8 i;
	u8 j;
	SOURCE front_source;

	front_source=FrontSource;
	if(front_source==SOURCE_AUX)
	{
		front_source=SOURCE_TAIL_AUX;
	}
	
	i=front_source&0xF0;
	i=i/16;
	j=front_source&0x0F;
	i=AutoHex2Ascii(i);
	j=AutoHex2Ascii(j);
	AutoTestTxCmd(module,'b',i,j);
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestEnterSource(u8 module)
{
	u8 i;
	u8 j;
	
	i=FrontSource&0xF0;
	i=i/16;
	j=FrontSource&0x0F;
	i=AutoHex2Ascii(i);
	j=AutoHex2Ascii(j);
	AutoTestTxCmd(module,'c',i,j);
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
	
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();

}

void AutoTestPlayTrack(u8 module)
{
	u8 i,j;

	j=AutoAscii2Hex(AutoTestRxBuffer[7]);
	j=j*16;
	j+=AutoAscii2Hex(AutoTestRxBuffer[8]);
	if((j>0)&&(j<=26))
	{
		PostKeyCode(UICC_10P,j);
	}
	i=MediaPlayInfo.cur_play_track;	
	i=i/16;
	j=MediaPlayInfo.cur_play_track&0x0F;
	i=AutoHex2Ascii(i);
	j=AutoHex2Ascii(j);
	AutoTestTxCmd(module,'d',i,j);
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestVolumeUp(u8 module)
{
	u8 i;
	u8 j;		
	
#if MODEL==LINUX_1475_21||MODEL==LINUX_1475_CP||MODEL==LINUX_1479_21
	PostKeyCode(UICC_VOLUME_UP,0x40|REMOTE);
#else
	PostKeyCode(UICC_VOLUME_UP,REMOTE);
#endif
	i=TurnOn_Volume;					
	if(i<0x28)
	{
		++i;
	}
	else
	{
		i=40;
	}
	j=i;
	i=i/16;
	j=j&0x0F;
	i=AutoHex2Ascii(i);
	j=AutoHex2Ascii(j);
	AutoTestTxCmd(module,'f',i,j);
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestVolumeDn(u8 module)	
{
	u8 i;
	u8 j;	
	
	i=TurnOn_Volume;					
	if(i>1)
	{
		--i;
#if MODEL==LINUX_1475_21||MODEL==LINUX_1475_CP||MODEL==LINUX_1479_21
		PostKeyCode(UICC_VOLUME_DOWN,0x40|REMOTE);
#else
		PostKeyCode(UICC_VOLUME_DOWN,REMOTE);
#endif
	
	}
	j=i;
	i=i/16;
	j=j&0x0F;
	i=AutoHex2Ascii(i);
	j=AutoHex2Ascii(j);
	AutoTestTxCmd(module ,'g',i,j);
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestDvd( u8 cmd)
{
	u8 j;
	
	switch(cmd)
	{
		case 'a':
			// ASK  if the disc exist
			if(0==F_Exist_DISC)
			{
				AutoTestTxCmd('b','a','0','0');
			}
			else 
			{
				AutoTestTxCmd('b','a','0','1');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			//ask the front source
			AutoTestAskFrontSource('b');
			break;
		case 'c':
			//enter DVD
			PostKeyCode(UICC_DVD,REMOTE);
			AutoTestEnterSource('b');
			break;
		case 'd':
			//play the track no. send back the track no.
			AutoTestPlayTrack('b');					
			break;
		case 'e':
			// ask the play state
			j=MediaPlayInfo.PlayState;
			j=AutoHex2Ascii(j);
			AutoTestTxCmd('b','e','0',j);
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'f':
			//UICC_VOLUME_UP
			AutoTestVolumeUp('b');
			break;
		case 'g':
			//UICC_VOLUME_DOWN										
			AutoTestVolumeDn('b');			
			break;
		default:
			break;			
	}	
}
void AutoTestSUB_Enable(void)
{
}

void AutoTestUsb(u8 cmd)	
{
	u8 j;
	
	switch(cmd)
	{
		case 'a':
			// ASK	if the USB exist
			AutoTestTxCmd('l','a','0','1');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
        AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			//ask the front source
			AutoTestAskFrontSource('l');
			break;
		case 'c':
			//enter USB
			PostKeyCode(UICC_USB_CARD,AutoAscii2Hex(AutoTestRxBuffer[8]) | (3 << 4));
			AutoTestEnterSource('l');
			break;
		case 'd':
			//	play the track no. send back the track no.
			AutoTestPlayTrack('l'); 				
			break;
		case 'e':
			// ask the play state
			j=MediaPlayInfo.PlayState;
			j=AutoHex2Ascii(j);
			AutoTestTxCmd('l','e','0',j);
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'f':
			//UICC_VOLUME_UP
			AutoTestVolumeUp('l');
			break;
		case 'g':
			//UICC_VOLUME_DOWN										
			AutoTestVolumeDn('l');
			break;
		case 'h':
			AutoTestSUB_Enable();		
			break;
		default:
			break;
	}		
}

void AutoTestSd(u8 cmd)	
{
	u8 j;
	
	switch(cmd)
	{
		case 'a':
			// ASK	if the USB exist
			AutoTestTxCmd('h','a','0','1');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			//ask the front source
			AutoTestAskFrontSource('h');
			break;
		case 'c':
			//enter USB
			PostKeyCode(UICC_SD_CARD,REMOTE);
			AutoTestEnterSource('h');
			break;
		case 'd':
			//	play the track no. send back the track no.
			AutoTestPlayTrack('h'); 				
			break;
		case 'e':
			// ask the play state
			j=MediaPlayInfo.PlayState;
			j=AutoHex2Ascii(j);
			AutoTestTxCmd('h','e','0',j);
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'f':
			//UICC_VOLUME_UP
			AutoTestVolumeUp('h');
			break;
		case 'g':
			//UICC_VOLUME_DOWN										
			AutoTestVolumeDn('h');
			break;
		default:
			break;
	}			
}

void AutoTestAuxIn(u8 cmd)	
{
	u8 j;
	
	switch(cmd)
	{
		case 'a':
			// ASK	if the aux exist
			AutoTestTxCmd('f','a','0','1');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			//ask the front source
			AutoTestAskFrontSource('f');
			break;
		case 'c':
			//enter USB
			PostKeyCode(UICC_AUX,REMOTE);
			AutoTestEnterSource('f');
			break;
		case 'd':
			//	play the track no. send back the track no.
			AutoTestPlayTrack('f'); 				
			break;
		case 'e':
			// ask the play state
			j=MediaPlayInfo.PlayState;
			j=AutoHex2Ascii(j);
			AutoTestTxCmd('f','e','0',j);
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'f':
			//UICC_VOLUME_UP
			AutoTestVolumeUp('f');
			break;
		case 'g':
			//UICC_VOLUME_DOWN										
			AutoTestVolumeDn('f');
			break;
		default:
			break;
	}		
}

#if TUNER_FUNCTION==1
void AutoTestAskCurrentFreq(u8 cmd)
{
	u8 j;
	u16 i;

	AutoTestTxBuffer[0]='S';
	AutoTestTxBuffer[1]='T';
	AutoTestTxBuffer[2]='0';
	AutoTestTxBuffer[3]='8';
	AutoTestTxBuffer[4]='a';
	AutoTestTxBuffer[5]=cmd;
	j=Autotest_RxCounter;
	j++;
	if(j>10) 
	{
		j=j-10;
	}
	j=AutoHex2Ascii(j);
	AutoTestTxBuffer[6]=j;
	i=radio_freq;
	j=i%10;	
	j=AutoHex2Ascii(j);
	AutoTestTxBuffer[11]=j;
	i=radio_freq;
	i=i/10;
	j=i%10;
	j=AutoHex2Ascii(j);
	AutoTestTxBuffer[10]=j;
	i=radio_freq;
	i=i/100;
	j=i%10;
	j=AutoHex2Ascii(j);
	AutoTestTxBuffer[9]=j;
	i=radio_freq;
	i=i/1000;
	j=i%10;
	j=AutoHex2Ascii(j);
	AutoTestTxBuffer[8]=j;
	i=radio_freq;
	i=i/10000;
	j=i%10;
	j=AutoHex2Ascii(j);
	AutoTestTxBuffer[7]=j;
	AutoTest_TxPtr=&AutoTestTxBuffer[4];
	j=0;
	for(i=0;i<8;i++)
	{
		j+=*AutoTest_TxPtr;
		++AutoTest_TxPtr;
	}
	i=j&0xF0;
	i=i/16;
	j=j&0x0F;
	AutoTestTxBuffer[12]=AutoHex2Ascii(i);
	AutoTestTxBuffer[13]=AutoHex2Ascii(j);
	Autotest_TxLength=AUTO_TEST_FR_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestRadioInit(void)
{
	PostMessage(TUNER_MODULE,EVT_TUN_AREA,(0x100|radio_region));
					
	if(TurnOn_Volume>20)
	{
		
		PostKeyCode(UICC_VOLUME_DOWN,REMOTE);
	}
	else 
	{
		PostKeyCode(UICC_VOLUME_UP,REMOTE);
	}
}

void AutoTestBand(u8 module)
{
	PostMessage(TUNER_MODULE, EVT_TUN_BAND,BAND_AM2);
#if TUNER_TYPE==TDA7708_TUNER
	AutoTestBandTimer=10000;
#endif
	AutoTestTxCmd(module,'i','0' ,'0');
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestPreset(u8 module)
{
	u8 i;
	
	i=AutoTestRxBuffer[7];
	i=AutoAscii2Hex(i);
	PostMessage(TUNER_MODULE, EVT_TUN_LISTEN,i);
	AutoTestTxCmd(module,'j','0' ,'0');
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();

}

void AutoTestDxLoc(u8 module)
{
	u8 i;
	
	i=AutoTestRxBuffer[7];
	i=AutoAscii2Hex(i);
	PostMessage(TUNER_MODULE, EVT_TUN_DX_LOC,i);
	AutoTestTxCmd(module,'k','0' ,'0');
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestStIndicator(u8 module)
{
	//ask the ST
	Tuner_Get_Stereo_Smeter_Indicator();
	if(F_TunerStereo)
	{
		AutoTestTxCmd(module,'m','0','1');
	}
	else 
	{
		AutoTestTxCmd(module,'m','0','0');
	}
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestSeek(u8 module)
{
	PostMessage(TUNER_MODULE, EVT_TUN_SEEK,1);//20220414,lixg
	//PostKeyCode(UICC_SKIPF,REMOTE);  //20200714 zjb
	AutoTestTxCmd(module,'l','0' ,'0');
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestRadio(u8 cmd)
{	
	if(TunerSeekBreak()) 
	{
		PostMessage(TUNER_MODULE, EVT_TUN_SEEK,1);	//20200613zjb
	}
	switch(cmd)
	{
		case 'a':
			// ASK	current frequency
			AutoTestAskCurrentFreq('a');
			break;
		case 'b':
			//ask the front source
			AutoTestAskFrontSource('a');
			break;
		case 'c':
			//enter radio
			PostKeyCode(UICC_TUNER,REMOTE);
			AutoTestEnterSource('a');
			break;
		case 'd':
			//initialize the radio and send back the start frequency.
			AutoTestRadioInit(); 
			AutoTestAskCurrentFreq('d');
			break;
		case 'e':
			// manual step up
			PostMessage(TUNER_MODULE, EVT_TUN_MANUAL,1);
			AutoTestTxCmd('a','e','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'n':
			PostMessage(TUNER_MODULE, EVT_TUN_MANUAL,0);
			AutoTestTxCmd('a','n','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'f':
			//UICC_VOLUME_UP
			AutoTestVolumeUp('a');
			break;
		case 'g':
			//UICC_VOLUME_DOWN										
			AutoTestVolumeDn('a');
			break;
		case 'i':
			//change to AM
			AutoTestBand('a');
#if TUNER_TYPE==TDA7708_TUNER
			break;
#endif
		case 'j':
			//preset
			AutoTestPreset('a');	
			break;
		case 'k':
			//DX=0; LOC=1 
			AutoTestDxLoc('a');				
			break;
		case 'l':
			//seek up
			AutoTestSeek('a');	
			break;
		case 'm':	
			//ST=0 no light; ST=1 Lighting 
			AutoTestStIndicator('a');		
			break;
#if AF_ENABLE==1
		case 'o':
			if (AutoTestRxBuffer[7] == '0' && AutoTestRxBuffer[8] == '0')
			{
				PostMessage(TUNER_MODULE, EVT_RDS_AF,0);
			}
			else if (AutoTestRxBuffer[7] == '0' && AutoTestRxBuffer[8] == '1')
			{
				PostMessage(TUNER_MODULE, EVT_RDS_AF,1);
			}
			AutoTestTxCmd('a','o','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			break;
#endif			
		default:
			break;
	}	
}
#endif

#if MODEL==LINUX_1269_21||MODEL==LINUX_9289_21
void AutoTestAskCurrentFreq(u8 cmd)
{
    u8 j;
    u8 i;
		u16 current_freq;
	
    AutoTestTxBuffer[0] = 'S';
    AutoTestTxBuffer[1] = 'T';
    AutoTestTxBuffer[2] = '0';
    AutoTestTxBuffer[3] = '8';
    AutoTestTxBuffer[4] = 'a';
    AutoTestTxBuffer[5] = cmd;
    j = Autotest_RxCounter;
    j++;
    if (j > 10)
    {
        j = j - 10;
    }
    j = AutoHex2Ascii(j);
    AutoTestTxBuffer[6] = j;
//		if (AutoTestRxAppBuffer[0] == 1 && AutoTestRxAppBuffer[1] == 0)
				current_freq = (AutoTestRxAppBuffer[2] << 8) | AutoTestRxAppBuffer[3];
    for (i = 0; i < 5; i++)
    {
        j = (current_freq / (u16)pow(10, i)) % 10;
        AutoTestTxBuffer[11 - i] = AutoHex2Ascii(j);
    }
    AutoTest_TxPtr = &AutoTestTxBuffer[4];
    j = 0;
    for (i = 0; i < 8; i++)
    {
        j += *AutoTest_TxPtr;
        ++AutoTest_TxPtr;
    }
    i = j & 0xF0;
    i = i / 16;
    j = j & 0x0F;
    AutoTestTxBuffer[12] = AutoHex2Ascii(i);
    AutoTestTxBuffer[13] = AutoHex2Ascii(j);
    Autotest_TxLength = AUTO_TEST_FR_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
    AutoTestEnableRxInterrupt();
}

void AutoTestRadio(u8 cmd)
{
    switch (cmd)
    {
    case 'a':
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_CURRENT_FREQ);
				CMD_WaitForSend='a';
				WaitAppTimer=100;
        break;
    case 'b':
        AutoTestAskFrontSource('a');
        break;
    case 'c':
        PostKeyCode(UICC_TUNER, REMOTE);
        AutoTestEnterSource('a');
        break;
    case 'd':
				if(TurnOn_Volume>20)
				{
					PostKeyCode(UICC_VOLUME_DOWN,REMOTE);
				}
				else 
				{
					PostKeyCode(UICC_VOLUME_UP,REMOTE);
				}
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_INIT);
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_CURRENT_FREQ);
				CMD_WaitForSend='d';
				WaitAppTimer=100;
        break;
    case 'e':
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_STEP_UP);
        AutoTestTxCmd('a', 'e', '0', '0');
        Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
        AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
        AutoTestEnableRxInterrupt();
        break;
    case 'n':
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_STEP_DOWN);
        AutoTestTxCmd('a', 'n', '0', '0');
        Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
        AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
        AutoTestEnableRxInterrupt();
        break;
    case 'f':
        AutoTestVolumeUp('a');
        break;
    case 'g':
        AutoTestVolumeDn('a');
        break;
    case 'i':
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_AM);
        AutoTestTxCmd('a', 'i', '0', '0');
        Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
        AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
        AutoTestEnableRxInterrupt();
        break;
    case 'j':
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_PRESET );
        AutoTestTxCmd('a', 'j', '0', '0');
        Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
        AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
        AutoTestEnableRxInterrupt();
        break;
    case 'k':
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_DX_LOC);
        AutoTestTxCmd('a', 'k', '0', '0');
        Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
        AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
        AutoTestEnableRxInterrupt();
        break;
    case 'l':
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_SEEK_UP);
        AutoTestTxCmd('a', 'l', '0', '0');
        Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
        AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
        AutoTestEnableRxInterrupt();
        break;
    case 'm':
        PostMessage(NAVI_MODULE, MCU_TX_AUTO_TEST_CMD, AT_RADIO_CMD_ST);
				WaitAppTimer=100;
        break;
    default:
        break;
    }
}
#endif
void AutoTestSWC(u8 cmd)
{
	u8 i;
	u8 j;
	
	switch(cmd)
	{
		// ask key code
		case 'a':
			i=Autotest_KeyCode&0xF0;
			i=i/16;
			j=Autotest_KeyCode&0x0F;
			i=AutoHex2Ascii(i);
			j=AutoHex2Ascii(j);			
			AutoTestTxCmd('v','a',i,j);
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			if(Autotest_KeyCode)
			{
				Autotest_KeyCode=0;
			}
			break;
#if MODEL == LINUX_1465_16
		case 'b':
			StudySteerKeyInfo.key_flag[3] = 0xFF;
			Mem_strcpy((u8 *)StudySteerKeyInfo.key_tab, (u8 *)AutoTest_StudySteerKeyTab, sizeof(AutoTest_StudySteerKeyTab));
			AutoTestTxCmd('v','b','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			break;
		case 'c':
			ClearSteerKeyInfo();
			AutoTestTxCmd('v','c','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			break;
#endif
		case 'd':
			break;
		case 'e':
			break;
		case 'f':
			
			AutoTestTxCmd('v','a','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
      		AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			//PostKeyCode(UICC_TFT_STANDBY,REMOTE);
			PostKeyCode(SYSTEM_POWER_OFF_KEY,REMOTE);
			break;
		default:
			break;
	}
}

void AutoTestTxSoftVersion(u8 cmd,u8 *version_data,u8 version_length)
{
	u8 length;
	u8 temp;
	u8 i;
	u8 checksum=0;

	AutoTestTxBuffer[0]='S';
	AutoTestTxBuffer[1]='T';

	length=version_length+3;
	temp=length/16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[2]=temp;
	temp=length%16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[3]=temp;
	
	AutoTestTxBuffer[4]='c';
	checksum+=AutoTestTxBuffer[4];
	AutoTestTxBuffer[5]=cmd;
	checksum+=AutoTestTxBuffer[5];
	
	temp=Autotest_RxCounter;
	temp++;
	if(temp>10) 
	{
		temp-=10;
	}
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[6]=temp;	
	checksum+=AutoTestTxBuffer[6];

	for(i=0;i<version_length;i++)
	{
		AutoTestTxBuffer[i+7]=version_data[i];
		checksum+=AutoTestTxBuffer[i+7];
	}
	
	temp=checksum/16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[i+7]=temp;
	i++;
	temp=checksum%16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[i+7]=temp;	

	Autotest_TxLength=version_length+9;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestVersion(u8 cmd)
{
	u8 i;
	
	switch(cmd)
	{
		case 'a':
			if(F_VERSION_VALID)
			{
				PostKeyCode(UICC_AUTOTEST_ON, 1);
				CameraInfo.reverse_setting = 0;
				AutoTestTxSoftVersion('a',AutoTestAppVersion,APP_VERSION_MAX_LENGTH);
				PostMessage(NAVI_MODULE,MCU_TX_AUTO_START_CMD,1);//发送自动化测试开始命令
			}
			else
			{
				AutoTestEnableRxInterrupt();
			}
			break;
		case 'b':
			if(F_VERSION_VALID)
			{
				AutoTestTxSoftVersion('b',AutoTestOsVersion,OS_VERSION_MAX_LENGTH);
			}
			else
			{
				AutoTestEnableRxInterrupt();
			}
			break;
		case 'c':
			if(F_VERSION_VALID)
			{
				AutoTestTxSoftVersion('c',AutoTestDvpVersion,DVP_VERSION_MAX_LENGTH);
			}
			else
			{
				AutoTestEnableRxInterrupt();
			}
			break;
		case 'd':
			if(F_VERSION_VALID)
			{
				AutoTestTxSoftVersion('d',AutoTestServoVersion,SERVO_VERSION_MAX_LENGTH);
			}
			else
			{
				AutoTestEnableRxInterrupt();
			}
			break;
		case 'e':
			{
				u8 length;
				u8 version[MCU_VERSION_MAX_LENGTH];	

				for(i=0;i<MCU_VERSION_MAX_LENGTH;i++)
				{
					version[i]=0x20;
				}

				length=sizeof(MCU_VERSION);
				Mem_strcpy(version,MCU_VERSION,length);
				AutoTestTxSoftVersion('e',version,MCU_VERSION_MAX_LENGTH);
			}
			break;
		default:
			break;
	}
}

void AutoTestTxUnitCode(u8 cmd)
{
	u8 length;
	u8 temp;
	u8 i;
	u8 checksum=0;
	AutoTestTxBuffer[0]='S';
	AutoTestTxBuffer[1]='T';
	length=UNIT_CODE_LENGTH+1+3;
	temp=length/16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[2]=temp;
	temp=length%16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[3]=temp;
	AutoTestTxBuffer[4]='d';
	checksum+=AutoTestTxBuffer[4];
	AutoTestTxBuffer[5]=cmd;
	checksum+=AutoTestTxBuffer[5];
	temp=Autotest_RxCounter;
	temp++;
	if(temp>10) 
	{
		temp-=10;
	}
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[6]=temp;	
	checksum+=AutoTestTxBuffer[6];
	if(UnitCodeData.flag)
	{
		AutoTestTxBuffer[7]='1';
	}
	else
	{
		AutoTestTxBuffer[7]='0';
	}
	checksum+=AutoTestTxBuffer[7];
	for(i=0;i<UNIT_CODE_LENGTH;i++)
	{
		AutoTestTxBuffer[i+8]=UnitCodeData.code[i];
		checksum+=AutoTestTxBuffer[i+8];
	}	
	temp=checksum/16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[i+8]=temp;
	i++;
	temp=checksum%16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[i+8]=temp;	
	Autotest_TxLength=UNIT_CODE_LENGTH+1+9;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

u8 IsAutoTestUnitCodeExist(void)
{
	return UnitCodeData.flag;
}

void AutoTestUnitCodeLoad(void)
{
	u8 result=0;
	u32 i;
	result=EEPROM_LoadUnitCode();
	if(result)
	{
		UnitCodeData.flag=1;
	}
	else
	{
		UnitCodeData.flag=0;
		for(i=0;i<(UNIT_CODE_LENGTH+1);i++)
		{
			UnitCodeData.code[i]='0';
		}
	}
}

void AutoTestUnitCodeSave(void)
{
	EEPROM_SaveUnitCode();
	UnitCodeData.flag=1;
}

void AutoTestUnitCode(u8 cmd)
{
	u8 i;
	switch(cmd)
	{
		case 'a':
			AutoTestTxUnitCode('a');
			break;
		case 'b':
			for(i=0;i<UNIT_CODE_LENGTH;i++)
			{
				UnitCodeData.code[i]=AutoTestRxBuffer[i+7];
			}
			AutoTestUnitCodeSave();
			AutoTestTxUnitCode('b');
			break;
		default:
			break;
	}
}

void AutoTestUUIDLoad(void)
{
	u8 result;
	u8 result_bak;
	u8 valid=0;
	u8 vaid_bak=0;
	u32 i;
	result=EEPROM_LoadUUID();
	result_bak=EEPROM_LoadUUID_Bak();
	for(i=0;i<UUID_DATA_LENGTH;i++)
	{
		if(UUID_Code[i]!=0x00
			&&UUID_Code[i]!=0xFF)
		{
			valid=1;
			break;
		}
	}
	for(i=0;i<UUID_DATA_LENGTH;i++)
	{
		if(UUID_Code_Bak[i]!=0x00
			&&UUID_Code_Bak[i]!=0xFF)
		{
			vaid_bak=1;
			break;
		}
	}
	if(result&&valid)
	{
		if(result_bak==0
			||vaid_bak==0)
		{
			for(i=0;i<UUID_DATA_LENGTH;i++)
			{
				UUID_Code_Bak[i]=UUID_Code[i];
			}
			EEPROM_SaveUUID_Bak();
		}
		UUID_Flag.field.f_valid=1;
	}
	else if(result_bak&&vaid_bak)
	{
		for(i=0;i<UUID_DATA_LENGTH;i++)
		{
			UUID_Code[i]=UUID_Code_Bak[i];
		}
		EEPROM_SaveUUID();
		UUID_Flag.field.f_valid=1;	
	}
	else
	{
		EEPROM_ClearUUID();
		EEPROM_ClearUUID_Bak();
		UUID_Flag.field.f_valid=0;
	}
}

void AutoTestUUIDSave(void)
{
	EEPROM_SaveUUID();
	EEPROM_SaveUUID_Bak();
	UUID_Flag.field.f_valid=1;
}

void AutoTestTxUUID(u8 cmd)
{
	u8 length;
	u8 temp;
	u8 i;
	u8 checksum=0;
	u8 number[10];
	u32 data;
	AutoTestTxBuffer[0]='S';
	AutoTestTxBuffer[1]='T';
	length=16+1+3;
	temp=length/16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[2]=temp;
	temp=length%16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[3]=temp;
	AutoTestTxBuffer[4]='e';
	checksum+=AutoTestTxBuffer[4];
	AutoTestTxBuffer[5]=cmd;
	checksum+=AutoTestTxBuffer[5];
	temp=Autotest_RxCounter;
	temp++;
	if(temp>10) 
	{
		temp-=10;
	}
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[6]=temp;	
	checksum+=AutoTestTxBuffer[6];
	if(UUID_Flag.field.f_valid)
	{
		AutoTestTxBuffer[7]='1';
	}
	else
	{
		AutoTestTxBuffer[7]='0';
	}
	checksum+=AutoTestTxBuffer[7];
	data=UUID_Code[4];
	data<<=8;
	data|=UUID_Code[5];
	data<<=8;	
	data|=UUID_Code[6];
	data<<=8;
	data|=UUID_Code[7];
	AutoTestTxBuffer[8]=UUID_Code[0];
	checksum+=AutoTestTxBuffer[8];
	AutoTestTxBuffer[9]=UUID_Code[1];
	checksum+=AutoTestTxBuffer[9];
	AutoTestTxBuffer[10]='0';
	checksum+=AutoTestTxBuffer[10];
	AutoTestTxBuffer[11]='0';
	checksum+=AutoTestTxBuffer[11];
	AutoTestTxBuffer[12]='0';
	checksum+=AutoTestTxBuffer[12];
	AutoTestTxBuffer[13]='0';
	checksum+=AutoTestTxBuffer[13];
	for(i=0;i<10;i++)
	{
		number[9-i]=data%10;
		data/=10;
	}
	for(i=0;i<10;i++)
	{
		AutoTestTxBuffer[i+14]=number[i]+'0';
		checksum+=AutoTestTxBuffer[i+14];
	}		
	temp=checksum/16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[i+14]=temp;
	i++;
	temp=checksum%16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[i+14]=temp;	
	Autotest_TxLength=26;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestBackupCurrent(void)
{    
	AutoTestTxCmd('x','a','0','1');	
	Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
    AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();	
}

void AutoTestSetting(u8 cmd)//编辑中
{
	
	u8 temp;
	switch(cmd)
	{
		case 'a':
			AutoTestBackupCurrent();
			break;
		case 'b':
			AutoTestTxCmd('x','b','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
      AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			PostKeyCode(UICC_RESET_FACTORY,REMOTE);
			//PostMessage(NAVI_MODULE,MCU_TX_FACTORY_RESET_CMD,0);
			break;
		case 'c':
			break;
		case 'd':
			break;
		case 'e':
			AutoTestTxCmd('x','e','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
      AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			PostKeyCode(UICC_AV_AUX,REMOTE);
			break;
		case 'f':
			AutoTestTxCmd('x','f','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
      AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			PostKeyCode(UICC_SEARCH_GPS,REMOTE);
			break;
		case 'g':
			if((AutoTestRxBuffer[7]=='1')&&(AutoTestRxBuffer[8]=='0'))
			{
				PostMessage(NAVI_MODULE,MCU_TX_AUTO_START_CMD,1);
			}
			else if((AutoTestRxBuffer[7]=='0')&&(AutoTestRxBuffer[8]=='0'))
			{
				PostMessage(NAVI_MODULE,MCU_TX_AUTO_START_CMD,0);
			}
			AutoTestTxCmd('x','g','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'h':
			temp = AutoAscii2Hex(AutoTestRxBuffer[7]) * 10 + AutoAscii2Hex(AutoTestRxBuffer[8]);
			temp = (temp > 20) ? 20 : temp;
			TFT_Brightness=temp;
			TFT_Brightness_illumine=temp;
			TFT_Backlight_Level=((temp*(BACKLIGHT_PERCENT_MAX-BACKLIGHT_PERCENT_MIN))/SYS_BRIGHTNESS_VALUE_MAX)+BACKLIGHT_PERCENT_MIN;
			AutoTestTxCmd('x','h','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		default:
			break;
	}
}

void AutoTestCP(u8 cmd)
{
	switch(cmd)
	{
		case 'a':
			AutoTestTxCmd('m','a','0','1');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			AutoTestAskFrontSource('m');
			break;
		case 'c':
//			PostMessage(MMI_MODULE,UICC_OPEN_SOUND,0x0100|STEER);
//			PostMessage(MMI_MODULE,UICC_OPEN_SOUND,0x0000|STEER);
			SourceDelayTimer=1;
			Source_SW_Seq=SOURCE_CARPLAY;
			//AutoTestEnterSource('m');
			AutoTestTxCmd('m', 'c' ,'0' , '1');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
		break;
	}
}

void AutoTestAA(u8 cmd)
{
	switch(cmd)
	{
		case 'a':
			AutoTestTxCmd('n','a','0','1');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			AutoTestAskFrontSource('n');
			break;
		case 'c':
//			PostMessage(MMI_MODULE,UICC_OPEN_SOUND,0x0100|STEER);
//			PostMessage(MMI_MODULE,UICC_OPEN_SOUND,0x0000|STEER);
			SourceDelayTimer=1;
			Source_SW_Seq=SOURCE_ANDROID_AUTO;
			//AutoTestEnterSource('n');
			AutoTestTxCmd('n', 'c' ,'0' , '1');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
	}
}

void AutoTestUUID(u8 cmd)
{
	u8 i;
	u32 data=0;
	
	switch(cmd)
	{
		case 'a':
			AutoTestTxUUID('a');
			break;
		case 'b':
			UUID_Code[0]=AutoTestRxBuffer[7];
			UUID_Code[1]=AutoTestRxBuffer[8];
			UUID_Code[2]=0;
			UUID_Code[3]=0;
			for(i=0;i<10;i++)
			{
				data+=AutoTestRxBuffer[i+13]-0x30;
				if(i<9)
				{
					data*=10;
				}
			}
			UUID_Code[4]=(data>>24);
			UUID_Code[5]=(data>>16);
			UUID_Code[6]=(data>>8);
			UUID_Code[7]=data;
			for(i=0;i<UUID_DATA_LENGTH;i++)
			{
				UUID_Code_Bak[i]=UUID_Code[i];
			}
			AutoTestUUIDSave();
			AutoTestTxUUID('b');
			break;
		default:
			break;
	}
}

#if CAN_ADAPTER==1
void AutoTestCAN(u8 cmd)
{
	switch(cmd)
	{
		case 'a':
			if(F_CAN_BUS_READY)
			{
				AutoTestTxCmd('w','a','0','1');
			}
			else 
			{
				AutoTestTxCmd('w','a','0','0');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();	
			break;
		default:
			break;
	}
}
#endif

#if MODEL==LINUX_2289_31
u8 pulse_width;
u8 speed_flag_1;
u8 speed_flag_2;
u16 pulse_count;
void	AutoTestSpeed_Pro(void)
{
	pulse_width++;
	pulse_count++;
	
	if(pulse_count<5000)
	{
		if(pulse_width<=100)
		{
			RearCameraOn();
		}
		else if((pulse_width>100)&&(pulse_width<=200))
		{
			RearCameraOff();
		}
		else
		{
			pulse_width=0;
		}
	}
	else if((pulse_count>=5000)&&(pulse_count<10000))
	{
		RearCameraOff();
		pulse_count++;
	}
	else if(pulse_count>=10000)
	{
		pulse_count=0;
	}
}
#endif

void AutoTestBT(u8 cmd)
{
	u32 i;
	
	switch(cmd)
	{
		case 'a':
			for(i=0;i<6;i++)
			{
				u8 msb;
				u8 lsb;

				msb=AutoAscii2Hex(AutoTestRxBuffer[(i*2)+7]);
				lsb=AutoAscii2Hex(AutoTestRxBuffer[(i*2)+1+7]);
				AutoTestBTAddr[i]=(msb<<4)|lsb;
			}
			PostMessage(NAVI_MODULE,MCU_TX_BT_TEST_CMD,AT_BT_CMD_CONNECT);
			if(AutoTestBtInfo.field.f_connect)
			{
				AutoTestTxCmd('g','a','1','0');
			}
			else
			{
				AutoTestTxCmd('g','a','0','0');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			AutoTestAskFrontSource('g');
			break;
		case 'c':
			PostMessage(NAVI_MODULE,MCU_TX_BT_TEST_CMD,AT_BT_CMD_A2DP_MENU);
			if(AutoTestBtInfo.field.f_audio_menu)
			{
				AutoTestTxCmd('g','c','1','0');
			}
			else
			{		
			AutoTestTxCmd('g','c','0','0');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'd':
			PostMessage(NAVI_MODULE,MCU_TX_BT_TEST_CMD,AT_BT_CMD_DIAL_MENU);
			if(AutoTestBtInfo.field.f_audio_menu==0)
			{
				AutoTestTxCmd('g','d','1','0');
			}
			else
			{		
			AutoTestTxCmd('g','d','0','0');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'e':
			PostMessage(NAVI_MODULE,MCU_TX_BT_TEST_CMD,AT_BT_CMD_HUNGUP);
			if(AutoTestBtInfo.field.f_hungup)
			{
				AutoTestTxCmd('g','e','1','0');
			}
			else
			{		
			AutoTestTxCmd('g','e','0','0');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'f':
			AutoTestVolumeUp('g');
			break;
		case 'g':									
			AutoTestVolumeDn('g');
			break;
		case 'h':
			PostMessage(NAVI_MODULE,MCU_TX_BT_TEST_CMD,AT_BT_CMD_DISCONNECT);
			if(AutoTestBtInfo.field.f_connect)
			{
			AutoTestTxCmd('g','h','0','0');
			}
			else
			{
				AutoTestTxCmd('g','h','1','0');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'i':
			PostMessage(NAVI_MODULE,MCU_TX_BT_TEST_CMD,AT_BT_CMD_OPEN_INTERNAL_MIC);
			if(AutoTestBtInfo.field.f_internal_mic)
			{
				AutoTestTxCmd('g','i','1','0');
			}
			else
			{
				AutoTestTxCmd('g','i','0','0');
			}
			AutoTestTxCmd('g','i','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'j':
			PostMessage(NAVI_MODULE,MCU_TX_BT_TEST_CMD,AT_BT_CMD_OPEN_EXTERNAL_MIC);
			if(AutoTestBtInfo.field.f_internal_mic)
			{
			AutoTestTxCmd('g','j','0','0');
			}
			else
			{
				AutoTestTxCmd('g','j','1','0');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'k':
			for(i=0;i<6;i++)
			{
				u8 msb;
				u8 lsb;
				msb=AutoAscii2Hex(AutoTestRxBuffer[(i*2)+7]);
				lsb=AutoAscii2Hex(AutoTestRxBuffer[(i*2)+1+7]);
				AutoTestBTCheckAddr[i]=(msb<<4)|lsb;
			}
			PostMessage(NAVI_MODULE,MCU_TX_BT_TEST_CMD,AT_BT_CMD_CHECK_ADDRESS);
			if(AutoTestBtInfo.field.f_adress_right)
			{
				AutoTestTxCmd('g','k','1','0');
			}
			else
			{
				AutoTestTxCmd('g','k','0','0');
			}
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
            AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		default:
			break;
	}
}

void AutoTestButton(u8 cmd)//编辑中
{
	u8 i;
	u8 j;
	switch(cmd)
	{
		case 'a':
			i=Autotest_KeyCode&0xF0;
			i=i/16;
			j=Autotest_KeyCode&0x0F;
			i=AutoHex2Ascii(i);
			j=AutoHex2Ascii(j);			
			AutoTestTxCmd('y','a',i,j);
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
      		AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			if(Autotest_KeyCode)
			{
				Autotest_KeyCode=0;
			}
		break;
	}
}

void AutoTestTxInternetWifi(u8 cmd,u8 *wifi_data)
{
	u8 length;
	u8 temp;
	u8 i;
	u8 checksum=0;

	AutoTestTxBuffer[0]='S';
	AutoTestTxBuffer[1]='T';

	length=wifi_data[0]+3;
	temp=length/16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[2]=temp;
	temp=length%16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[3]=temp;
	
	AutoTestTxBuffer[4]='i';
	checksum+=AutoTestTxBuffer[4];
	AutoTestTxBuffer[5]=cmd;
	checksum+=AutoTestTxBuffer[5];
	
	temp=Autotest_RxCounter;
	temp++;
	if(temp>10) 
	{
		temp-=10;
	}
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[6]=temp;	
	checksum+=AutoTestTxBuffer[6];

	for(i=0;i<wifi_data[0];i++)
	{
		AutoTestTxBuffer[i+7]=wifi_data[i+1];
		checksum+=AutoTestTxBuffer[i+7];
	}
	
	temp=checksum/16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[i+7]=temp;
	i++;
	temp=checksum%16;
	temp=AutoHex2Ascii(temp);
	AutoTestTxBuffer[i+7]=temp;	

	Autotest_TxLength=wifi_data[0]+9;
  AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
	AutoTestEnableRxInterrupt();
}

void AutoTestInternetWifi(u8 cmd)//编辑中
{
//	u8 i;
	switch (cmd)
	{
		case 'a':
			if((AutoTestRxBuffer[7]=='1')&&(AutoTestRxBuffer[8]=='0'))
			{
				PostMessage(NAVI_MODULE,MCU_TX_WIFI_TEST_CMD,AT_InternetWifi_CMD_CLOSE_INTERNET);
			}
			else
			{
				PostMessage(NAVI_MODULE,MCU_TX_WIFI_TEST_CMD,AT_InternetWifi_CMD_OPEN_INTERNET);
			}
			AutoTestTxCmd('i','a','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			if((AutoTestRxBuffer[7]=='0')&&(AutoTestRxBuffer[8]=='0'))
			{
				PostMessage(NAVI_MODULE,MCU_TX_WIFI_TEST_CMD,AT_InternetWifi_CMD_CLOSE_WIFI);
			}
			else
			{
				PostMessage(NAVI_MODULE,MCU_TX_WIFI_TEST_CMD,AT_InternetWifi_CMD_OPEN_WIFI);
			}
			AutoTestTxCmd('i','b','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'c':
//			PostMessage(NAVI_MODULE,MCU_TX_WIFI_TEST_CMD,AT_InternetWifi_CMD_CONNECT_WIFI);
//		  if(AutoTestWifiFlag.f_connect)
//			{
//				AutoTestTxCmd('i','c','1','0');
//			}
//			else
//			{
//				AutoTestTxCmd('i','c','0','0');
//			}
//			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
//			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
//			AutoTestEnableRxInterrupt();
		  //AutoTestWifiFlag.f_connect 
		  break;
		case 'd'://等待编辑
//			PostMessage(NAVI_MODULE,MCU_TX_WIFI_TEST_CMD,AT_InternetWifi_CMD_IP);
//		  for(i=0;i<PARAM_LENGTH;i++)//PARAM_LENGTH
//		  {
//				AutoTestIP_Addr[i]=AutoTestRxBuffer[i+7];
//			}
//		  if(AutoTestWifiFlag.f_ping)
//			{
//				AutoTestTxCmd('i','d','1','0');
//			}
//			else
//			{
//				AutoTestTxCmd('i','d','0','0');
//			}
//			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
//			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
//			AutoTestEnableRxInterrupt();
		  break;			
		case 'e':
			PostMessage(NAVI_MODULE,MCU_TX_WIFI_TEST_CMD,AT_InternetWifi_CMD_SSID);
			AutoTestTxInternetWifi('e',AutoTestWifiSSID);
			break;
		case 'f':
			PostMessage(NAVI_MODULE,MCU_TX_WIFI_TEST_CMD,AT_InternetWifi_CMD_PASSWORD);
			AutoTestTxInternetWifi('f',AutoTestWifiPassword);
			break;
		default :
			break;
	}
	

}

void AutoTestScreen(u8 cmd)
{
	switch(cmd)
	{
		case 'a':
			if(AutoTestRxBuffer[7]=='1')//&&(AutoTestRxBuffer[8]=='0'))
			{
				SCREEN_SUB_COMMAND=1;
			}
			else
			{
				SCREEN_SUB_COMMAND=0;
			}
			PostMessage(NAVI_MODULE,MCU_TX_SCREEN_TEST_CMD,AT_SCREEN_CMD_SCREEN_TEST);
			AutoTestTxCmd('j','a','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
			break;
		case 'b':
			PostMessage(NAVI_MODULE,MCU_TX_SCREEN_TEST_CMD,AT_SCREEN_CMD_SHOW_BLACK);
		  AutoTestTxCmd('j','b','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
		  break;
		case 'c':
			PostMessage(NAVI_MODULE,MCU_TX_SCREEN_TEST_CMD,AT_SCREEN_CMD_SHOW_WHITE);
		  AutoTestTxCmd('j','c','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
		  break;
		case 'd':
			PostMessage(NAVI_MODULE,MCU_TX_SCREEN_TEST_CMD,AT_SCREEN_CMD_SHOW_RED);
		  AutoTestTxCmd('j','d','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
		  break;
		case 'e':
			PostMessage(NAVI_MODULE,MCU_TX_SCREEN_TEST_CMD,AT_SCREEN_CMD_SHOW_GREEN);
		  AutoTestTxCmd('j','e','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
		  break;
		case 'f':
			PostMessage(NAVI_MODULE,MCU_TX_SCREEN_TEST_CMD,AT_SCREEN_CMD_SHOW_BLUE);
		  AutoTestTxCmd('j','f','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
		  break;
		case 'g':
		  if(AutoTestRxBuffer[7]=='1')//&&(AutoTestRxBuffer[8]=='0'))
			{
				SCREEN_SUB_COMMAND=1;
			}
			else
			{
				SCREEN_SUB_COMMAND=0;
			}
			PostMessage(NAVI_MODULE,MCU_TX_SCREEN_TEST_CMD,AT_SCREEN_CMD_TOUCH);
			AutoTestTxCmd('j','g','0','0');
			Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
			AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
			AutoTestEnableRxInterrupt();
		  break;
		default :
			break;
	}
}

#if MODEL==LINUX_1307W_14||MODEL==LINUX_1305W_14B
void CanBox_AutoTest_Start(void)
{
	CanFunTxBuffer[0]=0x2E;
	CanFunTxBuffer[1]=AutoTest_Start_End;
	CanFunTxBuffer[2]=1;
	CanFunTxBuffer[3]=1;
	CanFunTxBuffer[4]=(AutoTest_Start_End+CanFunTxBuffer[2]+CanFunTxBuffer[3])^0xFF;
	CanFunTxLength=5;
	CanBox_StartFrame();
}
void CanBox_AutoTest_End(void)
{
	CanFunTxBuffer[0]=0x2E;
	CanFunTxBuffer[1]=AutoTest_Start_End;
	CanFunTxBuffer[2]=1;
	CanFunTxBuffer[3]=0;
	CanFunTxBuffer[4]=(AutoTest_Start_End+CanFunTxBuffer[2]+CanFunTxBuffer[3])^0xFF;
	CanFunTxLength=5;
	CanBox_StartFrame();
}
#endif

void AutoTestMainPro(void)
{
	u8 i;
	u8 j;
	
#if TUNER_TYPE==TDA7708_TUNER	
	if(AutoTestBandTimer)
	{
		AutoTestBandTimer--;
		if(AutoTestBandTimer<9980)
		{
			if(StarTunerData.startup_state==STAR_STARTUP_CHANGE_BAND_WAIT
				||StarTunerData.startup_state==STAR_STARTUP_WORK_NORMAL)
			{
				PostMessage(TUNER_MODULE, EVT_TUN_LISTEN,0);
				AutoTestBandTimer=0;
			}
		}
	}
#endif
	if(WaitAppTimer)
	{
		WaitAppTimer--;
		return;
	}
	if(0==F_AUTOTEST_RX_OK)
	{
		return;
	}

	if(0==AutoTestCheckSum()) 
	{
		//check  checksum at first;
		AutoTestTxCmd('z','c','0','0');
		Autotest_TxLength=AUTO_TEST_TX_CMD_LENGTH;
        AutoTestUartTxFormat(AutoTestTxBuffer,Autotest_TxLength);
		AutoTestEnableRxInterrupt();
		return;
	}
	i=AutoTestRxBuffer[6];
	j=AutoTestRxBuffer[5];
	if(j=='a') 
	{
		Autotest_RxCounter=0x0F;
	}
	i=AutoAscii2Hex(i);
	if(i==Autotest_RxCounter)
	{
		//check RxCounter ;
		AutoTestReTxCmd();		
		if(Autotest_ErCounter<3)
		{
			Autotest_ErCounter++;
		}
		else
		{
			Autotest_RxCounter=0x0F;
		}
		return;
	}
	else
	{		
		if(i>=10)
		{
			i=i-10;
		}
		Autotest_RxCounter=i;
		Autotest_ErCounter=0;
	}
	i=AutoTestRxBuffer[4];
	j=AutoTestRxBuffer[5];
	switch(i)
	{
#if TUNER_FUNCTION==1 || MODEL==LINUX_1269_21||MODEL==LINUX_9289_21
		case 'a':
			AutoTestRadio(j);
			break;
#endif
		case 'b':
			AutoTestDvd(j);
			break;
		case 'l':
			AutoTestUsb(j);
			break;
		case 'h':
			AutoTestSd(j);
			break;
		case 'f':
			AutoTestAuxIn(j);
			break;
		case 'v':
			AutoTestSWC(j);
			break;
		case 'c':
			AutoTestVersion(j);
			break;
		case 'd':
			AutoTestUnitCode(j);
			break;
		case 'e':
			AutoTestUUID(j);
			break;
#if CAN_ADAPTER==1
		case 'w':
			AutoTestCAN(j);
			break;
#endif
		case 'x':
			AutoTestSetting(j);
			break;
		case 'm':
			AutoTestCP(j);
			break;
		case 'n':
			AutoTestAA(j);
			break;
		case 'g':
			AutoTestBT(j);
			break;
		case 'y'://未完善，函数为空
			AutoTestButton(j);
			break;
		case 'i':
			AutoTestInternetWifi(j);//函数为空
			break;
		case 'j':
			AutoTestScreen(j);
			break;
		default:
			AutoTestEnableRxInterrupt();
			break;
	}
	AutoTestEnableRxInterrupt();
}

void AutoTestRxApp(void)
{
	WaitAppTimer=0;
	switch(AutoTestRxAppBuffer[0])
	{
		case 0x03:
			switch(AutoTestRxAppBuffer[1])
			{
				case 0x00:
					AutoTestTxCmd('k', 'a', '0', AutoTestRxAppBuffer[2]);
					Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
					AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
					AutoTestEnableRxInterrupt();
					break;
				case 0x01:
					AutoTestTxCmd('k', 'b', '0', AutoTestRxAppBuffer[2]);
					Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
					AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
					AutoTestEnableRxInterrupt();
					break;
				case 0x03:
					AutoTestTxCmd('k', 'c', '0', AutoTestRxAppBuffer[2]);
					Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
					for(int i = 0;i<7;i++)
					{
						AutoTestTxBuffer[AUTO_TEST_TX_CMD_LENGTH+i] = AutoHex2Ascii(AutoTestRxAppBuffer[3+i]);
						Autotest_TxLength++;
					}
					AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
					AutoTestEnableRxInterrupt();
				default:
					break;
			}
		
#if MODEL==LINUX_1269_21||MODEL==LINUX_9289_21
		case 0x01:
			switch(AutoTestRxAppBuffer[1])
			{
				case 0x00:
					AutoTestAskCurrentFreq(CMD_WaitForSend);
					break;
				case 0x08:
					AutoTestTxCmd('a', 'm', '0', AutoTestRxAppBuffer[2]);
					Autotest_TxLength = AUTO_TEST_TX_CMD_LENGTH;
					AutoTestUartTxFormat(AutoTestTxBuffer, Autotest_TxLength);
					AutoTestEnableRxInterrupt();
					break;
			}
		break;
#endif
#if MODEL==LINUX_1307W_14||MODEL==LINUX_1305W_14B
		case 0x02:
			switch(AutoTestRxAppBuffer[1])
			{
				case 0x00:
						CanBox_AutoTest_End();
					break;
				case 0x01:
					CanBox_AutoTest_Start();
					break;
			}
#endif
	}
}
#endif

