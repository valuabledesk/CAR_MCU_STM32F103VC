/**
  ******************************************************************************
  * @file    Android_BU32107.c
  * @author  Maxmade Android Team
  * @brief  Audio DSP module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of DSP
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c)  Maxmade Auto Electronic Co.,LTD.
  * All rights reserved.  
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
 */

/***************************************************************************
	BUS FORMAT of DSP by I2C
	|S| Slave Address| A| Select Address High| A| Select Address Low| A| Data |A |P|
	
	S=Start condition(Recognition of start bit)
	Slave Address= Recognition of Slave Address(Writing: 80(hex), Reading: 81(hex))
	A=ACKNOWLEDGE bit(Recognition of acknowledgement)
	Select Address High/Low=Select Address of item
	Data=Data of item
	P=Stop condition(Recognition of stop bit)
****************************************************************************/
#include "public.h"	
#if BU32107_FUN==1
AUDIO_HANDLER_TYPE_DEF DSP_AudioHander; 
DSP_DATA DSP_Data;
u8 beep_Flag;
u8 beep_WriteRegisterBuffer[10];
u8 beep_ReadRegisterBuffer[10];
u16 DSPerrortimer;
u8 test_mix_flag;
u8 test_mix_vol;
u8 test_bg_vol;
u8 Umute_flag;
u8 FLAG_DSP_NORMAL=0;
u8 mix_on;
u8 mix_off;
#if 1
const u8 InitialRow1[8]=//0x0001~~0x0008
{
	0X0C,// f S Selector:48KHz; MCK Selector:256 fS=256*48KHz=12.288MHz,
	0X20,// SL X'over:Bypass; Loudness:Use; P2Bass:Use; X'0ver/EQ
	0X00,// default value
	0X00,// default value
	0X00,// default value
	0X33,// default value
	0XFF,// default value
	0XF3// default value
};

#if MODEL== ANDROID_Q133_00
const u8 InitialRow2[19]=
{
	0X2F,// BCK/LRCKdirection(DIND):output //0X0F
	0X0C,// Digital IO Bit Width(Input1):24bit; Digital IO Format(Input1):S/PDIF
	0X0C,// Digital IO Bit Width(Input3):24bit; Digital IO Format(Input3):S/PDIF
	0X00,// Digital IO Bit Width(output1):24bit; Digital IO Format(output1):I2S
	0X00,// default value
	0X00,// default value
	0X0C,// Digital IO Bit Width(output3):24bit; Digital IO Format(output3):S/PDIF
	0X00,// default value
	0X00,// default value
	0X42,// Input2(ExtIO),16bit,I2S
	0X00,// default value
	0X00,// default value
	0X00,// default value
	0X00,// default value
	0XC0,// default value
	0X00,// default value
	0XC0,// default value
	0X34,// default value
	0X05 // default value
};
#else
const u8 InitialRow2[19]=
{
	0X0F,// BCK/LRCKdirection(DIND):output //0X0F
	0X0C,// Digital IO Bit Width(Input1):24bit; Digital IO Format(Input1):S/PDIF
	0X0C,// Digital IO Bit Width(Input3):24bit; Digital IO Format(Input3):S/PDIF
	0X00,// Digital IO Bit Width(output1):24bit; Digital IO Format(output1):I2S
	0X00,// default value
	0X00,// default value
	0X0C,// Digital IO Bit Width(output3):24bit; Digital IO Format(output3):S/PDIF
	0X00,// default value
	0X00,// default value
	0X42,// Input2(ExtIO),16bit,I2S
	0X00,// default value
	0X00,// default value
	0X00,// default value
	0X00,// default value
	0XC0,// default value
	0X00,// default value
	0XC0,// default value
	0X34,// default value
	0X05 // default value
};
#endif

const u8 InitialRow3[10]=
{
	0X07,// Input Gain:7db
	0X00,// Rear Selector:RL/RR; Sub Selector:SL/SR
	0X00,// Analog Input Selector:Single1; Analog Mixing Input Selector:Single M1; Select Mode:Normal Mode
	0X11,// Analog Mixing Source(RR):MixR; Analog Mixing Source(RL):MixL; Analog Mixing Source(FR):MixR; Analog Mixing Source(FL):MixL
	0X01,// Analog Mixing Source(SR):MixR; Analog Mixing Source(SL):MixL; Stereo Mix Gain:0db
	0X80,// default value
	0X80,// AVol(AMix)(Lch):MUTE
	0X80,// AVol(AMix)(Rch):MUTE
	0XFF,// default value
	0xAB// AVol(DMix):MUTE
};

const u8 InitialRow4[9]=
{
	0X02,// Digital ExtIO IO Selector:B-1----Digital ExtIO(Output2 & Input2)
	0X04,// Digital Output1 IO Selector:D-1 ; Digital Output3 IO Selector:Disable
	0X22,// Digital Input1 IO Selector:B-1; Digital Input3 IO Selector:B-1
	0X00,// default value
	0X00,// default value
	0X05,// P 2 Bass Input Selector(Rear):Time Alignment; P 2 Bass Input Selector(Front):Time Alignment; 
	0X51,// Digital Mixing Input Selector:DC Cut HPF(Input2-SL/-SR);Digital Mixing Stereo Mix:Monaural(L);SR Volume Input Selector:DC Cut HPF(Input2-SR);SL X’over Input Selector:DC Cut HPF(Input2-SL)
	0X00,// Digital Output1 Front Selector:FL/FR; Digital Output1 Rear Selector:RL/RR; Digital Output1 Sub Selector:SL/SR
	0X00// Digital Output2 Selector:SpeAna Input; Digital Output3 Selector:SL/SR 
};

//Time Alignment Time
const u8 InitialRow5[14]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};

const u8 InitialRow6[2]={0X04,0X00};

const u8 InitialRow7=0X00;// EQ Mode:13-Band EQ+Tone

//EQ
const u8 InitialRow8[32]=
{
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
};

const u8 InitialRow9[10]=
{
	0X00,// default value 
	0X66,// Loudness LPF f C:125Hz; Loudness HPF f C:12.5kHz
	0X80,// default value,Loudness Gain,Loudness HiBoost
	0X00,// default value,Front HPF f C,Front HPF Order,Front HPF Phase,Direct Coef Set
	0X00,// default value,Rear HPF f C,Rear HPF Order,Rear HPF Phase
	0X80,// default value 
	0X80,// default value 
	0X1A,// Sub LPF Phase:0; Sub LPF Order:4 th order; Sub LPF f C:200Hz 
	0X00,// Sub HPF f C:Through
	0X00,// default value
};

const u8 InitialRow10[6]=
{
	0X80,// BEEP Level:-32dBFS
	0X03,// BEEP Mode:Auto; BEEP Repeat:1; BEEP Type:Sine wave; BEEP Frequency:2kHz 
	0X00,// BEEP ON time:32ms; BEEP OFF time:32ms
	0X00,// default value
	0X00,// default value
	0X40// DVol(Output2):0db
};

const u8 InitialRow11[12]=
{
	0X40,// DVol(Att)_FL:0db
	0X40,// DVol(Att)_FR:0db
	0X40,// DVol(Att)_RL:0db
	0X40,// DVol(Att)_RR:0db
	0X40,// DVol(Att)_SL:0db
	0X40,// DVol(Att)_SR:0db
	0X80,// DVol(Boost)_FL:0db
	0X80,// DVol(Boost)_FR:0db
	0X80,// DVol(Boost)_RL:0db
	0X80,// DVol(Boost)_RR:0db
	0X80,// DVol(Boost)_SL:0db
	0X80// DVol(Boost)_SR:0db
};

const u8 BU32107_VolumeTab[DSP_VOLUME_MAX+1]=
{
	0X00,// mute
	0XD0,// -72db
	0XC4,// -66db
	0XBC,// -62db
	0XB4,// -58db
	0XAC,// -54db
	0XA4,// -50db
	0X9C,// -46db
	0X94,// -42db
	0X90,// -40db
	0X8C,// -38db
	0X88,// -36db
	0X84,// -34db
	0X80,// -32db
	0X7C,// -30db
	0X78,// -28db
	0X74,// -26db
	0X70,// -24db
	0X6C,// -22db
	0X6A,// -21db
	0X68,// -20db
	0X66,// -19db
	0X64,// -18db
	0X62,// -17db
	0X60,// -16db
	0X5E,// -15db
	0X5C,// -14db
	0X5A,// -13db
	0X58,// -12db
	0X56,// -11db
	0X54,// -10db
	0X52,// -9db
	0X50,// -8db
	0X4E,// -7db
	0X4C,// -6db
	0X4A,// -5db
	0X48,// -4db
	0X46,// -3db
	0X44,// -2db
	0X42,// -1db
	0X40,// 0db
};

const u8 BU32107_Eq_Tab[DSP_EQ_MAX_NUM][16]=
{
	{0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C},
	{0x0E,0x0E,0x0E,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0x0C,0X0C,0X0C},//bass
	{0X0E,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C,0X0D,0X0D,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C},//0x04CLASSIC
	{0X0E,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C,0X0D,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C},//0x0Aclub
	{0X0E,0X0E,0X0D,0X0D,0X0D,0X0D,0X0C,0X0C,0X0C,0X0D,0X0D,0X0E,0X0E,0X0C,0X0C,0X0C},//dance
	{0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0C,0X0D,0X0C,0X0D,0X0C,0X0D,0X0D,0X0C,0X0C,0X0C},//FLAT
	{0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B},
	{0X0E,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C,0X0C,0X0C,0X0E,0X0F,0X0E,0X0C,0X0C,0X0C},//party
	{0X0E,0X0F,0X0F,0X0E,0X0E,0X0D,0X0C,0X0C,0X0D,0X0E,0X0E,0X0F,0X0F,0X0C,0X0C,0X0C},//0x03:POP
	{0X0E,0X0E,0X0F,0X0F,0X0F,0X0D,0X0C,0X0C,0X0E,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C},//0x05ROCK
	{0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0D,0X0E,0X0E,0X0C,0X0C,0X0C}//treble
	
};

const u8 BU32107_User_Eq_RegTab[25]=
{
	0x0e,//-12db
	0x0d,
    0x0c,
	0x0b,
	0x0a,
	0x09,
	0x00,//Odb
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,//+6db
};
const u8 BU32107_Eq_RegTab[25]=
{
//	0x1C,//-24dB
//	0x1B,
//	0x1A,
	0x19,
	0x18,
    0x17,
	0x16,
	0x15,
    0x14,
	0x13,
	0x12,
	0x11,
	0x00,//Odb
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,
	0x07,
	0x08,
	0x09,
//	0x0A,
//	0x0B,
//	0x0C//+24dB	
};

//	   fade      balance
//??¡ã¡Á¨®????1         1
//??¡ã????????1         0
//??¨®¡Á¨®????0         1
//??¨®????????0         0
const u8 BU32107_FadeBalanceTable[2][19]=
{
	45,20,16,12,10,8,6,4,2,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,2,4,6,8,10,12,16,20,45,
};

const u8 InitialRow12[6]=
{
		0XA2,//	0X82,// Fader Volume_FL:-2db
		0XA2,//	0X82,// Fader Volume_FR:-2db
		0XA2,//	0X82,// Fader Volume_RL:-2db
		0XA2,//	0X82,// Fader Volume_RR:-2db
//	0X80,// Fader Volume_SL:MUTE
//	0X80// Fader Volume_SR:MUTE
};
#else
const u8 InitialRow1[8]=//0x0001~~0x0008
{
	0X1C,// f S Selector:48KHz; MCK Selector:256 fS=256*48KHz=12.288MHz,
	0X00,// SL X'over:Bypass; Loudness:Use; P2Bass:Use; X'0ver/EQ   /// bypass mode  0X20,
	0X00,// default value
	0X00,// default value
	0X00,// default value
	0X33,// default value
	0XFF,// default value
	0XF3// default value
};

const u8 InitialRow2[19]=
{
	0X0F,// BCK/LRCKdirection(DIND):output //0X07
	0X0C,// Digital IO Bit Width(Input1):24bit; Digital IO Format(Input1):S/PDIF
	0X0C,// Digital IO Bit Width(Input3):24bit; Digital IO Format(Input3):S/PDIF
	0X0C,// Digital IO Bit Width(output1):24bit; Digital IO Format(output1):I2S
	0X00,// default value
	0X00,// default value
	0X0C,// Digital IO Bit Width(output3):24bit; Digital IO Format(output3):S/PDIF
	0X00,// default value
	0X00,// default value
	0X00,// Input2(ExtIO),16bit,I2S
	0X00,// default value
	0X00,// default value
	0X00,// default value
	0X00,// default value
	0XC0,// default value
	0X00,// default value
	0XC0,// default value
	0X34,// default value
	0X05 // default value
};

const u8 InitialRow3[10]=
{
	0X00,// Input Gain:7db
	0X00,// Rear Selector:RL/RR; Sub Selector:SL/SR
	0X00,// Analog Input Selector:Single1; Analog Mixing Input Selector:Single M1; Select Mode:Normal Mode
	0X11,// Analog Mixing Source(RR):MixR; Analog Mixing Source(RL):MixL; Analog Mixing Source(FR):MixR; Analog Mixing Source(FL):MixL
	0X01,// Analog Mixing Source(SR):MixR; Analog Mixing Source(SL):MixL; Stereo Mix Gain:0db
	0X80,// default value
	0X80,// AVol(AMix)(Lch):MUTE
	0X80,// AVol(AMix)(Rch):MUTE
	0X80,// default value
	0x80// AVol(DMix):MUTE
};

const u8 InitialRow4[9]=
{
	0X00,// Digital ExtIO IO Selector:B-1----Digital ExtIO(Output2 & Input2)
	0X03,// Digital Output1 IO Selector:D-1 ; Digital Output3 IO Selector:Disable
	0X22,// Digital Input1 IO Selector:B-1; Digital Input3 IO Selector:B-1
	0X00,// default value
	0X00,// default value
	0X05,// P 2 Bass Input Selector(Rear):Time Alignment; P 2 Bass Input Selector(Front):Time Alignment; 
	0X00,// Digital Mixing Input Selector:DC Cut HPF(Input2-SL/-SR);Digital Mixing Stereo Mix:Monaural(L);SR Volume Input Selector:DC Cut HPF(Input2-SR);SL X’over Input Selector:DC Cut HPF(Input2-SL)
	0X00,// Digital Output1 Front Selector:FL/FR; Digital Output1 Rear Selector:RL/RR; Digital Output1 Sub Selector:SL/SR
	0X00// Digital Output2 Selector:SpeAna Input; Digital Output3 Selector:SL/SR 
};

//Time Alignment Time
const u8 InitialRow5[14]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};

const u8 InitialRow6[2]={0X04,0X00};

const u8 InitialRow7=0X00;// EQ Mode:13-Band EQ+Tone

//EQ
const u8 InitialRow8[32]=
{
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
};

const u8 InitialRow9[10]=
{
	0X00,// default value 
	0X00,// Loudness LPF f C:125Hz; Loudness HPF f C:12.5kHz
	0X80,// default value,Loudness Gain,Loudness HiBoost
	0X00,// default value,Front HPF f C,Front HPF Order,Front HPF Phase,Direct Coef Set
	0X00,// default value,Rear HPF f C,Rear HPF Order,Rear HPF Phase
	0X80,// default value 
	0X80,// default value 
	0X00,// Sub LPF Phase:0; Sub LPF Order:4 th order; Sub LPF f C:200Hz 
	0X00,// Sub HPF f C:Through
	0X00,// default value
};

const u8 InitialRow10[6]=
{
	0X00,// BEEP Level:-32dBFS
	0X00,// BEEP Mode:Auto; BEEP Repeat:1; BEEP Type:Sine wave; BEEP Frequency:2kHz 
	0X00,// BEEP ON time:32ms; BEEP OFF time:32ms
	0X00,// default value
	0X00,// default value
	0X40// DVol(Output2):0db
};

const u8 InitialRow11[12]=
{
	0X40,// DVol(Att)_FL:0db
	0X40,// DVol(Att)_FR:0db
	0X40,// DVol(Att)_RL:0db
	0X40,// DVol(Att)_RR:0db
	0X40,// DVol(Att)_SL:0db
	0X40,// DVol(Att)_SR:0db
	0X80,// DVol(Boost)_FL:0db
	0X80,// DVol(Boost)_FR:0db
	0X80,// DVol(Boost)_RL:0db
	0X80,// DVol(Boost)_RR:0db
	0X80,// DVol(Boost)_SL:0db
	0X80// DVol(Boost)_SR:0db
};

const u8 BU32107_VolumeTab[DSP_VOLUME_MAX+1]=
{
	0X00,// mute
	0XD0,// -72db
	0XC4,// -66db
	0XBC,// -62db
	0XB4,// -58db
	0XAC,// -54db
	0XA4,// -50db
	0X9C,// -46db
	0X94,// -42db
	0X90,// -40db
	0X8C,// -38db
	0X88,// -36db
	0X84,// -34db
	0X80,// -32db
	0X7C,// -30db
	0X78,// -28db
	0X74,// -26db
	0X70,// -24db
	0X6C,// -22db
	0X6A,// -21db
	0X68,// -20db
	0X66,// -19db
	0X64,// -18db
	0X62,// -17db
	0X60,// -16db
	0X5E,// -15db
	0X5C,// -14db
	0X5A,// -13db
	0X58,// -12db
	0X56,// -11db
	0X54,// -10db
	0X52,// -9db
	0X50,// -8db
	0X4E,// -7db
	0X4C,// -6db
	0X4A,// -5db
	0X48,// -4db
	0X46,// -3db
	0X44,// -2db
	0X42,// -1db
	0X40,// 0db
};

const u8 BU32107_Eq_Tab[DSP_EQ_MAX_NUM][16]=
{
	{0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C},
	{0x0E,0x0E,0x0E,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0x0C,0X0C,0X0C},//bass
	{0X0E,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C,0X0D,0X0D,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C},//0x04CLASSIC
	{0X0E,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C,0X0D,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C},//0x0Aclub
	{0X0E,0X0E,0X0D,0X0D,0X0D,0X0D,0X0C,0X0C,0X0C,0X0D,0X0D,0X0E,0X0E,0X0C,0X0C,0X0C},//dance
	{0X0D,0X0D,0X0D,0X0D,0X0D,0X0D,0X0C,0X0D,0X0C,0X0D,0X0C,0X0D,0X0D,0X0C,0X0C,0X0C},//FLAT
	{0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B},
	{0X0E,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C,0X0C,0X0C,0X0E,0X0F,0X0E,0X0C,0X0C,0X0C},//party
	{0X0E,0X0F,0X0F,0X0E,0X0E,0X0D,0X0C,0X0C,0X0D,0X0E,0X0E,0X0F,0X0F,0X0C,0X0C,0X0C},//0x03:POP
	{0X0E,0X0E,0X0F,0X0F,0X0F,0X0D,0X0C,0X0C,0X0E,0X0E,0X0E,0X0E,0X0E,0X0C,0X0C,0X0C},//0x05ROCK
	{0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0C,0X0D,0X0E,0X0E,0X0C,0X0C,0X0C}//treble
	
};

const u8 BU32107_User_Eq_RegTab[25]=
{
	0x0e,//-12db
	0x0d,
    0x0c,
	0x0b,
	0x0a,
	0x09,
	0x00,//Odb
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,//+6db
};
const u8 BU32107_Eq_RegTab[25]=
{
//	0x1C,//-24dB
//	0x1B,
//	0x1A,
	0x19,
	0x18,
    0x17,
	0x16,
	0x15,
    0x14,
	0x13,
	0x12,
	0x11,
	0x00,//Odb
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,
	0x07,
	0x08,
	0x09,
//	0x0A,
//	0x0B,
//	0x0C//+24dB	
};

//	   fade      balance
//??¡ã¡Á¨®????1         1
//??¡ã????????1         0
//??¨®¡Á¨®????0         1
//??¨®????????0         0
const u8 BU32107_FadeBalanceTable[2][19]=
{
	45,20,16,12,10,8,6,4,2,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,2,4,6,8,10,12,16,20,45,
};

const u8 InitialRow12[6]=
{
		0XA0,//	0X82,// Fader Volume_FL:-2db
		0XA0,//	0X82,// Fader Volume_FR:-2db
		0XA0,//	0X82,// Fader Volume_RL:-2db
		0XA0,//	0X82,// Fader Volume_RR:-2db
  	0XA0,// Fader Volume_SL:MUTE
  	0XA0// Fader Volume_SR:MUTE
};
#endif
void AudioWriteData(u8 SlaveAddHigh,u8 SlaveAddLow,u8 data)
{

	GPIO_I2C2_Start();
	GPIO_I2C2_SendByte(DSP_I2C_ADDR);
	GPIO_I2C2_WaitACK();
	GPIO_I2C2_SendByte(SlaveAddHigh);
	GPIO_I2C2_WaitACK();	
	GPIO_I2C2_SendByte(SlaveAddLow);
	GPIO_I2C2_WaitACK();		
	GPIO_I2C2_SendByte(data);
	GPIO_I2C2_WaitACK();			
	GPIO_I2C2_Stop();		
}

u8 AudioReadData(u8 SlaveAddHigh,u8 SlaveAddLow)
{
	u8 Data;
	GPIO_I2C2_Start();
	GPIO_I2C2_SendByte(DSP_I2C_ADDR);
	GPIO_I2C2_WaitACK();
	GPIO_I2C2_SendByte(0xD0);
	GPIO_I2C2_WaitACK();	
	GPIO_I2C2_SendByte(0x00);
	GPIO_I2C2_WaitACK();	
	GPIO_I2C2_SendByte(SlaveAddHigh);
	GPIO_I2C2_WaitACK();	
	GPIO_I2C2_SendByte(SlaveAddLow);
	GPIO_I2C2_WaitACK();
	GPIO_I2C2_Stop();		
	
	GPIO_I2C2_Start();
	GPIO_I2C2_SendByte(0x81);
	GPIO_I2C2_WaitACK();
	Data=GPIO_I2C2_ReceiveByte();
	GPIO_I2C2_WaitACK();			
	GPIO_I2C2_Stop();	
	return Data;
}

void AudioWriteBuf(u8 SlaveAddHigh,u8 SlaveAddLow,const u8 *data,u8 Len)
{
	u32 i;
	
	GPIO_I2C2_Start();
	GPIO_I2C2_SendByte(DSP_I2C_ADDR);
	GPIO_I2C2_WaitACK();
	GPIO_I2C2_SendByte(SlaveAddHigh);
	GPIO_I2C2_WaitACK(); 
	GPIO_I2C2_SendByte(SlaveAddLow);
	GPIO_I2C2_WaitACK(); 
	for(i=0;i<Len;i++)
	{
		GPIO_I2C2_SendByte(*data);
		data++;
		GPIO_I2C2_WaitACK();
	}		
	GPIO_I2C2_Stop();		
}

void BU32107_SelectEqMode(u8 mode)
{
	if(mode)
	{
		AudioWriteData(0x06,0x00,0x80);
	}
	else
	{
		AudioWriteData(0x06,0x00,0x00);
	}
}

void BU32107_TimeAlignmentSet(u8 chn,u8 time)
{ 
	u16 tempTime;

	tempTime=(u16) time*48;
	chn<<=1;
	AudioWriteData(0x04,chn,MSB(tempTime));
	chn++;
	AudioWriteData(0x04,chn,LSB(tempTime));
}

void BU32107_SetVolume(u8 volume)    //
{
	DSP_Data.current_volume=volume;
	AudioWriteData(0x09,0x00,BU32107_VolumeTab[volume]);
	AudioWriteData(0x09,0x01,BU32107_VolumeTab[volume]);
	AudioWriteData(0x09,0x02,BU32107_VolumeTab[volume]);
	AudioWriteData(0x09,0x03,BU32107_VolumeTab[volume]);
	AudioWriteData(0x01,0x0A,0xAB);//0xA0
}

void BU32107_SetAudioCh(u8 ch) 
{
    switch(ch)
    {
	    case DSP_CH_ANALOG_1:
			AudioWriteData(0X00,0X19,0XC2); 	
			AudioWriteData(0X01,0X03,0X00); 
			AudioWriteData(0X02,0X03,0X00);  
			break;
	    case DSP_CH_ANALOG_2:
			AudioWriteData(0X01,0X03,0X04); 
			AudioWriteData(0X02,0X03,0X00); 
			AudioWriteData(0X00,0X02,0X00);
			break;
	    case DSP_CH_ANALOG_3:
			break;
	    case DSP_CH_ANALOG_4:
			break;
	    case DSP_CH_ANALOG_5:
			break;
	    case DSP_CH_DIGITAL_1:
			AudioWriteData(0x02,0x00,0x02);
			AudioWriteData(0x02,0x03,0x20);
			AudioWriteData(0x00,0x19,0x82);//C2
	    	break;
	    case DSP_CH_DIGITAL_2:
			break;
	    case DSP_CH_DIGITAL_3:
			break;
		default:
			break;
    }
}

void BU32107_SetAudioMute(u8 mute) 
{
	if(mute)
	{
		AudioWriteData(0x01,0x0A,0x80);
		AudioWriteData(0x09,0x00,BU32107_VolumeTab[0]);
		AudioWriteData(0x09,0x01,BU32107_VolumeTab[0]);
		AudioWriteData(0x09,0x02,BU32107_VolumeTab[0]);
		AudioWriteData(0x09,0x03,BU32107_VolumeTab[0]);

		DSP_Data.current_volume=0;
	}
	else
	{
		AudioWriteData(0x01,0x0A,0xAB);
		if(DSP_Data.volume<=40)
		{
			AudioWriteData(0x09,0x00,BU32107_VolumeTab[DSP_Data.volume]);
			AudioWriteData(0x09,0x01,BU32107_VolumeTab[DSP_Data.volume]);
			AudioWriteData(0x09,0x02,BU32107_VolumeTab[DSP_Data.volume]);
			AudioWriteData(0x09,0x03,BU32107_VolumeTab[DSP_Data.volume]);

			DSP_Data.current_volume=DSP_Data.volume;
		}
	}
}

void BU32107_SetAudioEQ(u8 EQ)
{
	u8 t;
	
	if(EQ==DSP_EQ_USER)
	{
		for(t=0;t<16;t++)
		{
			AudioWriteData(0x06,(0x10+t),0x40);
		}
		
		AudioWriteData(0x06,0x00,0x00);
		u32 i;
		u8 gain;
		u8 boost_cut;
		u8 temp;
		
		for(i=0;i<16;i++)
		{
			gain=(DSP_Data.eq_band_value_user[i]&0x7F);
			boost_cut=((DSP_Data.eq_band_value_user[i]&0x80)>>7);
			temp=gain;
			if(boost_cut)
			{
	
				temp|=0x08;
			}
			temp|=0x60;
			AudioWriteData(0x06,(0x1D+i),temp);//3tone
			DSP_Data.eq_band_value[i]=DSP_Data.eq_band_value_user[i];
		}
	}
	else if(EQ<DSP_EQ_MAX_NUM)
	{
		AudioWriteData(0x06,0x00,0x80);
		u32 i;
		u8 temp;
		u8 value;
		
		for(i=0;i<16;i++)
		{
			value=BU32107_Eq_Tab[EQ][i];
			temp=BU32107_Eq_RegTab[value];
			temp|=0x40;
			AudioWriteData(0x06,(0x10+i),temp);

			if(BU32107_Eq_Tab[EQ][i]<12)
			{
				DSP_Data.eq_band_value[i]=12-BU32107_Eq_Tab[EQ][i];
				DSP_Data.eq_band_value[i]|=0x80;
			}
			else
			{
				DSP_Data.eq_band_value[i]=BU32107_Eq_Tab[EQ][i]-12;
			}
		}
	}
}

void BU32107_SetAudioBandGain(u8 band,u8 boost_cut,u8 gain)
{
	if(band<16&&gain<13)
	{
		u8 temp;
		u8 reg_value;

		DSP_Data.eq_band_value[band]=gain;
		if(boost_cut==0)
		{
			temp=12+gain;
		}
		else
		{
			temp=12-gain;
			DSP_Data.eq_band_value[band]|=0x80;
		}
		DSP_Data.eq_band_value_user[band]=DSP_Data.eq_band_value[band];
		
		reg_value=BU32107_Eq_RegTab[temp];
		reg_value|=0x40;
		AudioWriteData(0x06,0x00,0x80);
		AudioWriteData(0x06,(0x10+band),reg_value);	
	}
}

void BU32107_SetAudio_3_BandGain(u8 band,u8 boost_cut,u8 gain)
{
	if(band<3&&gain<13)
	{
		u8 temp;
		u8 reg_value;
		u8 band_value;
		
		band_value=gain;
		if(boost_cut==0)
		{
			temp=6+gain;//3Tone 0db-12db ,step 2db;16band:12
		}
		else
		{
			temp=6-gain;
			band_value|=0x80;
		}
		
		reg_value=BU32107_User_Eq_RegTab[temp];
		AudioWriteData(0x06,0x00,0x00);
		
		if(band==0)
		{
			reg_value|=0x60;
			AudioWriteData(0x06,0x1D,reg_value);			
			DSP_Data.eq_band_value[0]=band_value;
			DSP_Data.eq_band_value_user[0]=DSP_Data.eq_band_value[0];
		}
		else if(band==1)
		{
			reg_value|=0x60;
			AudioWriteData(0x06,0x1E,reg_value);
			DSP_Data.eq_band_value[1]=band_value;
			DSP_Data.eq_band_value_user[1]=DSP_Data.eq_band_value[1];
		}
		else
		{
			reg_value|=0x70;
			AudioWriteData(0x06,0x1F,reg_value);
			DSP_Data.eq_band_value[2]=band_value;
			DSP_Data.eq_band_value_user[2]=DSP_Data.eq_band_value[2];
		}
	}
}

void BU32107_SetFadeBalance(u8 fade,u8 balance)
{
	if(fade<=18
		&&balance<=18)
	{
		u8 fl;
		u8 fr;
		u8 rl;
		u8 rr;
		u8 sl;
		u8 sr;

		fl=BU32107_FadeBalanceTable[1][fade]+BU32107_FadeBalanceTable[1][balance];
		if(fl>79)
		{
			fl=0;
		}
		else
		{
			fl+=0x20;
		}
		fl|=0xA2;//-2db 
		AudioWriteData(0x0A,0x00,fl);//FL
		
		fr=BU32107_FadeBalanceTable[1][fade]+BU32107_FadeBalanceTable[0][balance];
		if(fr>79)
		{
			fr=0;
		}
		else
		{
			fr+=0x20;
		}
		fr|=0xA2;
		AudioWriteData(0x0A,0x01,fr);//FR
		
		rl=BU32107_FadeBalanceTable[0][fade]+BU32107_FadeBalanceTable[1][balance];
		if(rl>79)
		{
			rl=0;
		}
		else
		{
			rl+=0x20;
		}
		rl|=0xA2;
		AudioWriteData(0x0A,0x02,rl);//RL
		
		
		rr=BU32107_FadeBalanceTable[0][fade]+BU32107_FadeBalanceTable[0][balance];
		if(rr>79)
		{
			rr=0;
		}
		else
		{
			rr+=0x20;
		}
		rr|=0xA2;
		AudioWriteData(0x0A,0x03,rr);//RR
/*
		sl=BU32107_FadeBalanceTable[1][balance];
		sl+=0x20;
		sl|=0x80;
		AudioWriteData(0x0A,0x04,sl);
		
		sr=BU32107_FadeBalanceTable[0][balance];
		sr+=0x20;
		sr|=0x80;
		AudioWriteData(0x0A,0x05,sr);
*/		
	}
}

void BU32107_SetLoudnessOnOff(u8 loudness_on_off)
{
	if(loudness_on_off)
	{
		AudioWriteData(0X00,0X02,0X00);
		AudioWriteData(0X07,0X01,0x06);
		AudioWriteData(0X07,0X02,0X84);
		AudioWriteData(0X09,0X06,0X72);
		AudioWriteData(0X09,0X07,0X72);
		AudioWriteData(0X09,0X08,0X72);
		AudioWriteData(0X09,0X09,0X72);
		AudioWriteData(0X09,0X0a,0X72);
		AudioWriteData(0X09,0X0b,0X72);
	}
	else
	{
		AudioWriteData(0X00,0X02,0X00);
		AudioWriteData(0X07,0X01,0X55);
		AudioWriteData(0X07,0X02,0X00);
		AudioWriteData(0X09,0X06,0X80);
		AudioWriteData(0X09,0X07,0X80);
		AudioWriteData(0X09,0X08,0X80);
		AudioWriteData(0X09,0X09,0X80);
		AudioWriteData(0X09,0X0a,0X80);
		AudioWriteData(0X09,0X0b,0X80);
	}
}

void BU32107_SetLoudnessGain(u8 gain)
{
	if(gain<=15)
	{
		u8 temp;

		temp=0x80;
		gain=15-gain;
		temp|=gain;
		AudioWriteData(0X07,0X02,temp);
	}
}

void BU32107_MixVolume(u8 background_volume)
{
	if(background_volume<=69)
	{

		u8 temp;

		temp=0xDE-(background_volume*2);
		AudioWriteData(0x09,0x00,temp);
		AudioWriteData(0x09,0x01,temp);
		AudioWriteData(0x09,0x02,temp);
		AudioWriteData(0x09,0x03,temp);
		//DSP_Data.background_volume=temp;
	}
}

void BU32107_DigitalMixVolume(u8 mix_vol,u8 bg_vol)
{
	if(mix_vol<=69
		&&bg_vol<=79)
	{
		u8 temp;
		
		temp=0xE5-mix_vol;
		AudioWriteData(0X01,0X0A,temp);	

		temp=0xDE-(bg_vol*2);
		AudioWriteData(0x09,0x00,temp);
		AudioWriteData(0x09,0x01,temp);
		AudioWriteData(0x09,0x02,temp);
		AudioWriteData(0x09,0x03,temp);
	}
}

void BU32107_beep(u8 beep)
{
	if(beep)
	{
#if MODEL==ANDROID_Q133_00	
		test_flag=0;
		AudioWriteData(0x00,0x10,0x0F);//start beep of touch
#endif		
		AudioWriteData(0x08,0x00,0x70);
		AudioWriteData(0x08,0x01,0x09);
		AudioWriteData(0X08,0x02,0x00);
		AudioWriteData(0x08,0x03,0x01);
	}
	else
	{
		AudioWriteData(0X01,0X0A,0x80);
	}
}

void BU32107_BeepStart(u8 beep_level,
						u8 beep_freq,
						u8 beep_type,
						u8 beep_repeat,
						u8 beep_on_time,
						u8 beep_off_time,
						u8 mix_vol)
{
	if(beep_level<=79
		&&beep_freq<DSP_BEEP_FREQ_MAX
		&&beep_repeat
		&&beep_repeat<=8
		&&beep_on_time<DSP_BEEP_TIME_MAX
		&&beep_off_time<DSP_BEEP_TIME_MAX
		&&mix_vol<=69)
	{
		u8 temp;

		//temp=0xE5-mix_vol;
		//AudioWriteData(0X01,0X0A,temp);	

		temp=0xDE-(beep_level*2);
		AudioWriteData(0x08,0x00,temp);

		temp=(beep_repeat-1);
		temp<<=1;
		temp|=(beep_type&0x01);
		temp<<=3;
		temp|=beep_freq;
		temp|=0x80;//wjp
		AudioWriteData(0x08,0x01,temp);

//		temp=beep_off_time;
//		temp<<=4;
//		temp|=beep_on_time;
//		AudioWriteData(0X08,0x02,temp);

		//AudioWriteData(0x08,0x03,0x01);
	}
}

void BU32107_PowerOn(void)
{
	DSP_AudioHander.state=AUD_START;
	DSP_AudioHander.flag.byte=0;
}
  
void BU32107_PowerOff(void)
{
	DSP_AudioHander.state=AUD_POWER_OFF;
	DSP_AudioHander.flag.byte=0;
}

u8 BU32107_IsBusy(void)
{
	u8 result=1;
	
	if(DSP_AudioHander.state==AUD_NORMAL)
	{
		result=0;
	}
	return result;
}

void BU32107_InitData(void)
{
	u32 i;
	
	DSP_AudioHander.state=AUD_IDLE;
	DSP_Data.audio_ch=DSP_CH_DIGITAL_1;//DSP_CH_ANALOG_1
	DSP_Data.volume=DSP_DEFAULT_VOLUME;
	DSP_Data.fade=DSP_DEFAULT_FADE;
	DSP_Data.balance=DSP_DEFAULT_BALANCE;
	BU32107_SetLoudnessOnOff(0);
	DSP_Data.eq_mode=DSP_EQ_USER;
	for(i=0;i<16;i++)
	{
		DSP_Data.eq_band_value[i]=0;
		DSP_Data.eq_band_value_user[i]=0;
	}
}

void BU32107_WorkPro(void)
{
    MESSAGE *pMsg;                           //
	pMsg= GetMessage(DSP_MODULE);
	
	switch(pMsg->ID)
	{
        case EVT_DSP_VOLUME_UP:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy()
#if POWER_ONE_HOUR_MODE_FUN==1
				||GetPowerOneHourModeMuteFlag()
#endif
				)
			{
				break;
			}
			if(DSP_Data.volume<40)
			{
				DSP_Data.volume++;
				BU32107_SetVolume(DSP_Data.volume);
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
				DSP_Data.f_mute=0;
			}
            break;
		case EVT_DSP_VOLUME_DOWN:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy()
#if POWER_ONE_HOUR_MODE_FUN==1
				||GetPowerOneHourModeMuteFlag()
#endif
				)
			{
				break;
			}
			if(DSP_Data.volume>0)
			{
				DSP_Data.volume--;
				BU32107_SetVolume(DSP_Data.volume);
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
				DSP_Data.f_mute=0;
			}
		    break;
		case EVT_DSP_VOLUME_SET:
			mix_on++;
			if(DSP_AudioHander.flag.field.f_init_flag==0
#if POWER_ONE_HOUR_MODE_FUN==1
				||GetPowerOneHourModeMuteFlag()
#endif
				)
			{
				break;
			}
			if(((pMsg->prm>>8)==0)&&((DSP_Data.audio_ch<=DSP_CH_ANALOG_5)&&(DSP_Data.audio_ch>=DSP_CH_ANALOG_1)))
			{
				break;
			}
			else
			{ 
				pMsg->prm&=0xff;
			}
			printf("2##DSP_Data.audio_ch:%x, pMsg->prm:%x\n",DSP_Data.audio_ch,pMsg->prm);
			if(pMsg->prm<=40)
			{
				if(BU32107_IsBusy()&&Umute_flag)//加Umute_flag为了解mute音量缓慢增加过程中收到app设置音量的命令不会被打断
				{
					DSP_Data.volume=pMsg->prm;  
					PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
				}
				else
				{					
#if AA_CP_TEST==1	
					DSP_Data.volume=pMsg->prm;
					BU32107_SetVolume(DSP_Data.volume);			
#else					
					if(DSP_Data.volume==0)
					{
						DSP_Data.volume=pMsg->prm;
						Umute_flag=0;
						DSP_AudioHander.state=AUD_PATH_CHG_VOL_INC;//解mute音量缓慢增加
					  
					}
					else
					{
						DSP_Data.volume=pMsg->prm;
						BU32107_SetVolume(DSP_Data.volume);
					}
#endif					
					PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
				}
				DSP_Data.f_mute=0;
			}
			break;
		case EVT_DSP_AUDIO_CH:
			if(DSP_AudioHander.flag.field.f_init_flag==0)
			{
				break;
			}
			if(pMsg->prm>DSP_CH_NONE
				&&pMsg->prm<DSP_CH_MAX_NUM)
			{
				DSP_Data.audio_ch=pMsg->prm;
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
#if POWER_ONE_HOUR_MODE_FUN==1
				if(GetPowerOneHourModeMuteFlag())
				{
					BU32107_SetAudioMute(1);
					DSP_Data.f_mute=1;
					DSP_AudioHander.state=AUD_PATH_CHG_HARD_MUTE;
				}
				else
				{
					if(DSP_Data.f_mute==0)
					{
						DSP_AudioHander.state=AUD_PATH_CHG_VOL_DEC;
					}
					else
					{
						DSP_AudioHander.state=AUD_PATH_CHG_HARD_MUTE;
					}
				}
#else 
					DSP_AudioHander.state=AUD_PATH_CHG_VOL_DEC;
#endif
			
				
				
			}
			break;
    	case EVT_DSP_AUDIO_EQ:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy())
			{
				break;
			}
			if(pMsg->prm>=DSP_EQ_USER
				&&pMsg->prm<DSP_EQ_MAX_NUM)
			{
				DSP_Data.eq_mode=pMsg->prm;
				BU32107_SetAudioEQ(DSP_Data.eq_mode);
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
			}
			break;
    	case EVT_DSP_AUDIO_BAND:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy())
			{
				break;
			}
			{
				u8 band;
				u8 boost_cut;
				u8 gain;

				band=((pMsg->prm&0xF000)>>12);
				boost_cut=((pMsg->prm&0x0F00)>>8);
				gain=(pMsg->prm&0x00FF);

				BU32107_SetAudioBandGain(band,boost_cut,gain);
				DSP_Data.eq_mode=DSP_EQ_USER;
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
    		}
			break;
    	case EVT_DSP_AUDIO_FADE_BALANCE:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy())
			{
				break;
			}
			{
				u8 temp_fade;
				u8 temp_balance;

				temp_fade=((pMsg->prm&0xFF00)>>8);
				temp_balance=(pMsg->prm&0xFF);
				if(temp_fade<=18
					&&temp_balance<=18)
				{
					DSP_Data.fade=temp_fade;
					DSP_Data.balance=temp_balance;
					BU32107_SetFadeBalance(DSP_Data.fade,DSP_Data.balance);
					PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
				}
			}
            break;
		case EVT_DSP_AUDIO_3_BAND:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy())
			{
				break;
			}
			{
				u8 band;
				u8 boost_cut;
				u8 gain;

				band=((pMsg->prm&0xF000)>>12);
				boost_cut=((pMsg->prm&0x0F00)>>8);
				gain=(pMsg->prm&0x00FF);

				BU32107_SetAudio_3_BandGain(band,boost_cut,gain);
				DSP_Data.eq_mode=DSP_EQ_USER;
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
    		}
			break;
		case EVT_DSP_AUDIO_MUTE:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy()
#if POWER_ONE_HOUR_MODE_FUN==1
				||(GetPowerOneHourModeMuteFlag()&&pMsg->prm==0)
#endif
				)
			{
				break;
			}
			if(pMsg->prm)
			{
				BU32107_SetAudioMute(1);
				DSP_Data.f_mute=1;
			}
			else
			{
				BU32107_SetAudioMute(0);
				DSP_Data.f_mute=0;
			}
			break;
		case EVT_DSP_AUDIO_LOUDNESS:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy())
			{
				break;
			}
			if(pMsg->prm)
			{
				BU32107_SetLoudnessOnOff(1);
				DSP_Data.loudness_on_off=pMsg->prm;
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
			}
			else
			{
				BU32107_SetLoudnessOnOff(0);
				DSP_Data.loudness_on_off=pMsg->prm;
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
			}
			break;
		case EVT_DSP_AUDIO_BEEP:
		{
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy()
#if POWER_ONE_HOUR_MODE_FUN==1          //add4.2
				||GetPowerOneHourModeMuteFlag()
#endif			
			)
			{
				break;
			}
			
			BU32107_beep(1);
		}
		break;
		case EVT_DSP_MIX_ON:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy()
#if POWER_ONE_HOUR_MODE_FUN==1
				||GetPowerOneHourModeMuteFlag()
#endif
			)
			{
				break;
			}
			if(pMsg->prm<=79)
			{
				DSP_Data.background_volume=pMsg->prm;
				BU32107_MixVolume(DSP_Data.background_volume);
				PostMessage(NAVI_MODULE,MCU_TX_DSP_DATA,0);
				mix_on=0;
			}
			break;
		case EVT_DSP_MIX_OFF:
			if(DSP_AudioHander.flag.field.f_init_flag==0
				||BU32107_IsBusy()
#if POWER_ONE_HOUR_MODE_FUN==1
				||GetPowerOneHourModeMuteFlag()
#endif			
			)
			{
				break;
			}
			BU32107_SetVolume(DSP_Data.current_volume);
			//AudioWriteData(0x01,0x0A,0x80);
			mix_off=0;
			//printf("9##DSP_Data.current_volume:%x, DSP_Data.audio_ch:%x\n",DSP_Data.current_volume,DSP_Data.audio_ch);
			break;	
		default:
			break;
	}
	
	if(DSP_AudioHander.wait_time)
	{
		DSP_AudioHander.wait_time--;
	}
	if(DSPerrortimer)
	{
		DSPerrortimer--;
		if(DSPerrortimer==0)
		{
			if(AUD_IDLE==DSP_AudioHander.state)
			{	
			}
		}		
	}
	switch(DSP_AudioHander.state)
	{
		case AUD_IDLE:
			if(APP_READY==APP_Status)
			{
				DSPerrortimer=T3Min_100;
			}
			break;
		case AUD_START:
			GPIO_I2C2_PortInit();
			DSP_AudioHander.wait_time=T30MS_10;
			DSP_AudioHander.state=AUD_POWER_ON;
 		    beep_Flag=0;
			break;
		case AUD_POWER_ON:
			if(DSP_AudioHander.wait_time)
			{
				break;
			}
			AudioWriteData(0XFE,0XFE,0X81); // system reset
			DSP_AudioHander.state=AUD_INITIAL_SETUP;
			break;
		case AUD_INITIAL_SETUP:
			// Data RAM clear
			// Coef RAM clear
			// MCK Selector:256 fS=256*48KHz=12.288MHz
			// f S Selector:48KHz
			AudioWriteData(0X00,0X01,0XCC);
			DSP_AudioHander.state=AUD_SEND_ALL_DATA;
			break;
		case AUD_SEND_ALL_DATA:
			//Digital format
			AudioWriteBuf(0X00,0X01,InitialRow1,8);
            AudioWriteBuf(0X00,0X10,InitialRow2,19);
			AudioWriteBuf(0X01,0X01,InitialRow3,10);
			AudioWriteBuf(0X02,0X00,InitialRow4,9);
			AudioWriteBuf(0X40,0X00,InitialRow5,14);
			AudioWriteBuf(0X05,0X00,InitialRow6,2);
           	AudioWriteData(0X06,0X00,InitialRow7);
			AudioWriteBuf(0X06,0X10,InitialRow8,32);
			AudioWriteBuf(0X07,0X00,InitialRow9,10);
			AudioWriteBuf(0X08,0X00,InitialRow10,6);
			AudioWriteBuf(0X09,0X00,InitialRow11,12);
			AudioWriteBuf(0X0A,0X00,InitialRow12,4);
			DSP_AudioHander.state=AUD_SET_LAST_MEMORY;	   
			break;
		case AUD_SET_LAST_MEMORY:
			if(DSP_AudioHander.wait_time)
			{
				break;
			}       
			BU32107_SetVolume(0);
			BU32107_SelectEqMode(1);
			BU32107_SetAudioEQ(DSP_Data.eq_mode);
			BU32107_SetFadeBalance(DSP_Data.fade,DSP_Data.balance);
			DSP_Data.f_mute=1;
			DSP_AudioHander.flag.field.f_init_flag=1;
			DSP_AudioHander.state=AUD_NORMAL;
			FLAG_DSP_NORMAL=1;
			BU32107_SetAudioCh(USB_CHANCEL);
			break;
		case AUD_NORMAL:
				
#if MODEL==ANDROID_Q133_00||MODEL==ANDROID_Q133_01	
		u8 text_buffer;
		text_buffer=AudioReadData(0x0A,0x00);
		if(text_buffer==0xFF)
		{
			uds_time=1;
			DTC_DSP_flag=1;
		}
		else
		{
			DTC_DSP_flag=0;
		}
#endif
			if(DSP_AudioHander.wait_time)
			{
				break;
			}
			break;	
		case AUD_PATH_CHG_VOL_DEC:
			if(DSP_AudioHander.wait_time)
			{
				break;
			}
			if(DSP_Data.current_volume)
			{
				DSP_Data.current_volume--;
				BU32107_SetVolume(DSP_Data.current_volume);
				DSP_AudioHander.wait_time=T1MS_1;				
			}
			else
			{
				DSP_AudioHander.state=AUD_PATH_CHG_HARD_MUTE;
				DSP_AudioHander.wait_time=T50MS_10;
				DSP_Data.f_mute=1;
			}
			break;
		case AUD_PATH_CHG_HARD_MUTE:
			if(DSP_AudioHander.wait_time)
			{
				break;
			}
#if MODEL== ANDROID_Q133_00
			if(beep_status>=1&&beep_status<=5){}
			else
			{
				Hard_Mute();
			}
#else
			Hard_Mute();
#endif
			DSP_AudioHander.state=AUD_PATH_CHG_SET_CH;
			DSP_AudioHander.wait_time=T50MS_10;
			break;
		case AUD_PATH_CHG_SET_CH:
			if(DSP_AudioHander.wait_time)
			{
				break;
			}
			BU32107_SetAudioCh(DSP_Data.audio_ch);
			DSP_AudioHander.state=AUD_PATH_CHG_HARD_UNMUTE;
			DSP_AudioHander.wait_time=T50MS_10;
			break;
		case AUD_PATH_CHG_HARD_UNMUTE:
			Hard_UMute();
#if POWER_ONE_HOUR_MODE_FUN==1
			if(GetPowerOneHourModeMuteFlag())
			{
				DSP_AudioHander.state=AUD_NORMAL;
				FLAG_DSP_NORMAL=1;
			}
			else
			{
				DSP_AudioHander.state=AUD_PATH_CHG_VOL_INC;
				DSP_AudioHander.wait_time=T50MS_10;
			}
#else
			DSP_AudioHander.state=AUD_PATH_CHG_VOL_INC;
			DSP_AudioHander.wait_time=T50MS_10;
#endif
			break;
		case AUD_PATH_CHG_VOL_INC:
			if(DSP_AudioHander.wait_time)
			{
				break;
			}
#if POWER_ONE_HOUR_MODE_FUN==1
			if(GetPowerOneHourModeMuteFlag())
			{
				BU32107_SetAudioMute(1);
				DSP_Data.f_mute=1;
				DSP_AudioHander.state=AUD_NORMAL;
				FLAG_DSP_NORMAL=1;
			}
			else
			{
				if(DSP_Data.current_volume<DSP_Data.volume)
				{
					DSP_Data.current_volume++;
					BU32107_SetVolume(DSP_Data.current_volume);
					DSP_AudioHander.wait_time=T10MS_10;
				}
				else
				{
					DSP_AudioHander.state=AUD_NORMAL;
					FLAG_DSP_NORMAL=1;
                    Umute_flag=1;
				}
				DSP_Data.f_mute=0;
			}
#else
			if(DSP_Data.current_volume<DSP_Data.volume)
			{
				DSP_Data.current_volume++;
				BU32107_SetVolume(DSP_Data.current_volume);
				DSP_AudioHander.wait_time=T20MS_10;
			}
			else
			{
				DSP_AudioHander.state=AUD_NORMAL;
			}
#endif
			break;
		case AUD_POWER_OFF:
			DSP_AudioHander.state=AUD_IDLE;
			break;
		default:
			break;
	}
}
#endif

