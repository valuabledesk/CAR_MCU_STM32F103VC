#ifndef _A2B_SLAVE_ADI_AMP_BOARD_DRV_H_
#define _A2B_SLAVE_ADI_AMP_BOARD_DRV_H_
#if A2B_SLAVE_ADI_AMP_BOARD==1

#define ADI_AMP_BOARD_DEVICE_NUM	2
#define ADI_AMP_BOARD_NUM			1

typedef struct
{
	u8 vendor;
	u8 device_1;
	u8 device_2;
	u8 revision;
}SSM3582_IC_INFO;

extern A2B_SLAVE_NODE_LIST ADI_AMP_NodeList;

void ADI_AMP_NodeListInit(void);

#endif
#endif

