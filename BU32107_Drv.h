
/**
  ******************************************************************************
  * @file    Android_BU32107.h
  * @author  Aaron
  * @brief   Header file of audio DSP module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c)  Maxmade Auto Electronic Co.,LTD.
  * All rights reserved.  
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BU32107_DRV_H_
#define _BU32107_DRV_H_
#if BU32107_FUN==1
	  
#ifdef __cplusplus
	  extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

#define DSP_I2C_ADDR 					0X80
#define DSP_VOLUME_MAX					40
#define DSP_DEFAULT_VOLUME				35
#define DSP_DEFAULT_FADE				9
#define DSP_DEFAULT_BALANCE				9

typedef enum
{
    DSP_BEEP_FREQ_50HZ=0, 
	DSP_BEEP_FREQ_500HZ,
    DSP_BEEP_FREQ_1000HZ,
    DSP_BEEP_FREQ_2000HZ,
    DSP_BEEP_FREQ_3000HZ,
    DSP_BEEP_FREQ_MAX  
}BU32107_BEEP_FREQ;

typedef enum
{
    DSP_BEEP_TIME_32MS=0, 
	DSP_BEEP_TIME_50MS,
    DSP_BEEP_TIME_100MS,
    DSP_BEEP_TIME_200MS,
    DSP_BEEP_TIME_250MS,
    DSP_BEEP_TIME_500MS,
    DSP_BEEP_TIME_600MS,
    DSP_BEEP_TIME_750MS,
    DSP_BEEP_TIME_1000MS,
    DSP_BEEP_TIME_3000MS,
    DSP_BEEP_TIME_MAX  
}BU32107_BEEP_TIME;

typedef enum
{
	AUD_IDLE=0,
	AUD_START,
	AUD_POWER_ON,
	AUD_INITIAL_SETUP,
	AUD_SEND_ALL_DATA,     
	AUD_SET_LAST_MEMORY,
	AUD_NORMAL,
	AUD_PATH_CHG_VOL_DEC,
	AUD_PATH_CHG_HARD_MUTE,
	AUD_PATH_CHG_SET_CH,
	AUD_PATH_CHG_HARD_UNMUTE,
	AUD_PATH_CHG_VOL_INC,
	AUD_POWER_OFF
}AUDIO_PROCESS_STATE;

typedef enum
{
    DSP_CH_NONE=0,   
    DSP_CH_ANALOG_1,
    DSP_CH_ANALOG_2,
    DSP_CH_ANALOG_3,
    DSP_CH_ANALOG_4,
    DSP_CH_ANALOG_5,
    DSP_CH_DIGITAL_1,
    DSP_CH_DIGITAL_2,
    DSP_CH_DIGITAL_3,
    DSP_CH_MAX_NUM
}BU32107_AUDIO_CH;

#define RADIO_CHANCEL DSP_CH_ANALOG_1
#define AUX_CHANCEL DSP_CH_ANALOG_2
#define USB_CHANCEL DSP_CH_DIGITAL_1

typedef enum
{
        DSP_EQ_USER=0, 
		DSP_EQ_BASS,
		DSP_EQ_CLASSICAL,
		DSP_EQ_CLUB,
		DSP_EQ_DANCE,
		DSP_EQ_FLAT,
		DSP_EQ_STANDAND,
		DSP_EQ_PARTY,
        DSP_EQ_POP,
		DSP_EQ_ROCK,
		DSP_EQ_TREBLE,
    DSP_EQ_MAX_NUM   
}BU32107_AUDIO_EQ;

typedef enum            //
{                       
	EVT_DSP_NONE=0, 
    EVT_DSP_VOLUME_UP,
    EVT_DSP_VOLUME_DOWN,
    EVT_DSP_VOLUME_SET,
    EVT_DSP_AUDIO_CH,
    EVT_DSP_AUDIO_EQ,
    EVT_DSP_AUDIO_BAND,
    EVT_DSP_AUDIO_FADE_BALANCE,
    EVT_DSP_AUDIO_3_BAND,
    EVT_DSP_AUDIO_MUTE,
    EVT_DSP_AUDIO_LOUDNESS,
	EVT_DSP_MIX_ON,
	EVT_DSP_MIX_OFF,
	EVT_DSP_AUDIO_BEEP
}DSP_EVT; 

typedef struct
{
	u8 volume;
	u8 audio_ch;
	u8 eq_mode;
	u8 eq_band_value[16];
	u8 eq_band_value_user[16];
	u8 fade;
	u8 balance;
	u8 current_volume;
	u8 on_off;
	u8 loudness_on_off;
	u8 beef;
	u8 f_mute;
	u8 mix_on_off;
	u8 mix_vol;
	u8 background_volume;
}DSP_DATA;

typedef struct
{
	unsigned f_init_flag:1;
}_DSP_FLAG;

typedef union
{
	_DSP_FLAG field;
	u8 byte;
}DSP_FLAG;

typedef struct
{
	DSP_FLAG flag;
	u32 wait_time;					// 10ms
	AUDIO_PROCESS_STATE state;
}AUDIO_HANDLER_TYPE_DEF;

extern DSP_DATA DSP_Data;

void BU32107_BeepStart(u8 beep_level,
						u8 beep_freq,
						u8 beep_type,
						u8 beep_repeat,
						u8 beep_on_time,
						u8 beep_off_time,
						u8 mix_vol);
void BU32107_PowerOn(void);
void BU32107_PowerOff(void);
void BU32107_WorkPro(void);
void BU32107_InitData(void);
void BU32107_SetVolume(u8 volume);
void BU32107_SetAudioCh(u8 ch);
void BU32107_SetAudioMute(u8 mute);
void BU32107_SetAudioEQ(u8 EQ);
void BU32107_SetAudioBandGain(u8 band,u8 boost_cut,u8 gain)	;
void BU32107_SetAudio_3_BandGain(u8 band,u8 boost_cut,u8 gain);
void BU32107_SetFadeBalance(u8 fade,u8 balance);
void BU32107_SetLoudnessOnOff(u8 loudness_on_off);
void BU32107_SetLoudnessGain(u8 gain);
void BU32107_DigitalMixOnOff(u8 on_off);
void BU32107_DigitalMixVolume(u8 mix_vol,u8 bg_vol);
void BU32107_beep(u8 beep);
void BU32107_MixVolume(u8 background_volume);
void AudioWriteData(u8 SlaveAddHigh,u8 SlaveAddLow,u8 data);
void AudioWriteBuf(u8 SlaveAddHigh,u8 SlaveAddLow,const u8 *data,u8 Len);
extern u8 FLAG_DSP_NORMAL;
#endif
#endif /* _BU32107_DRV_H_*/


