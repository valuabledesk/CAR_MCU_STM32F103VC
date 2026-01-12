#ifndef _AD2433_DRV_H_
#define _AD2433_DRV_H_

#if A2B_AD2433_FUN==1

#define A2B_I2C_BASE_ADDR					0x6E
#define A2B_I2C_BUS_ADDR					(A2B_I2C_BASE_ADDR|0x01)
#define A2B_I2C_DERVICE_BASE_ADDR			(A2B_I2C_BASE_ADDR<<1)
#define A2B_I2C_DERVICE_BUS_ADDR			(A2B_I2C_BUS_ADDR<<1)

#define AD2433_REG_CHIP					0x00       
#define AD2433_REG_NODEADR				0x01     
#define AD2433_REG_VENDOR				0x02     
#define AD2433_REG_PRODUCT				0x03     
#define AD2433_REG_VERSION				0x04     
#define AD2433_REG_CAPABILITY			0x05 
#define AD2433_REG_SWCTL				0x09       
#define AD2433_REG_BCDNSLOTS			0x0A   
#define AD2433_REG_LDNSLOTS				0x0B   
#define AD2433_REG_LUPSLOTS				0x0C   
#define AD2433_REG_DNSLOTS				0x0D     
#define AD2433_REG_UPSLOTS				0x0E     
#define AD2433_REG_RESPCYCS				0x0F   
#define AD2433_REG_SLOTFMT				0x10     
#define AD2433_REG_DATCTL				0x11     
#define AD2433_REG_CONTROL				0x12     
#define AD2433_REG_DISCVRY				0x13     
#define AD2433_REG_SWSTAT				0x14     
#define AD2433_REG_INTSTAT				0x15     
#define AD2433_REG_INTSRC				0x16     
#define AD2433_REG_INTTYPE				0x17     
#define AD2433_REG_INTPND0				0x18     
#define AD2433_REG_INTPND1				0x19     
#define AD2433_REG_INTPND2				0x1A     
#define AD2433_REG_INTMSK0				0x1B     
#define AD2433_REG_INTMSK1				0x1C     
#define AD2433_REG_INTMSK2				0x1D     
#define AD2433_REG_BECCTL				0x1E     
#define AD2433_REG_BECNT				0x1F       
#define AD2433_REG_TESTMODE				0x20   
#define AD2433_REG_ERRCNT0				0x21     
#define AD2433_REG_ERRCNT1				0x22     
#define AD2433_REG_ERRCNT2				0x23     
#define AD2433_REG_ERRCNT3				0x24     
#define AD2433_REG_NODE					0x29       
#define AD2433_REG_DISCSTAT				0x2B   
#define AD2433_REG_TXCTL				0x2E       
#define AD2433_REG_LINTTYPE				0x3E   
#define AD2433_REG_I2CCFG				0x3F     
#define AD2433_REG_PLLCTL				0x40     
#define AD2433_REG_I2SGCFG				0x41     
#define AD2433_REG_I2SCFG				0x42     
#define AD2433_REG_I2SRATE				0x43     
#define AD2433_REG_I2STXOFFSET			0x44 
#define AD2433_REG_SYNCOFFSET			0x46 
#define AD2433_REG_PDMCTL				0x47     
#define AD2433_REG_ERRMGMT				0x48     
#define AD2433_REG_GPIODAT				0x4A     
#define AD2433_REG_GPIODATSET			0x4B 
#define AD2433_REG_GPIODATCLR			0x4C 
#define AD2433_REG_GPIOOEN				0x4D     
#define AD2433_REG_GPIOIEN				0x4E     
#define AD2433_REG_GPIOIN				0x4F     
#define AD2433_REG_PINTEN				0x50     
#define AD2433_REG_PINTINV				0x51     
#define AD2433_REG_PINCFG				0x52     
#define AD2433_REG_I2STEST				0x53     
#define AD2433_REG_RAISE				0x54       
#define AD2433_REG_GENERR				0x55     
#define AD2433_REG_I2SRRATE				0x56   
#define AD2433_REG_I2SRRCTL				0x57   
#define AD2433_REG_I2SRRSOFFS			0x58 
#define AD2433_REG_CLK1CFG				0x59     
#define AD2433_REG_CLK2CFG				0x5A     
#define AD2433_REG_BMMCFG				0x5B     
#define AD2433_REG_SUSCFG				0x5C     
#define AD2433_REG_PDMCTL2				0x5D     
#define AD2433_REG_BSDSTAT				0x5E     
#define AD2433_REG_UPMASK0				0x60     
#define AD2433_REG_UPMASK1				0x61     
#define AD2433_REG_UPMASK2				0x62     
#define AD2433_REG_UPMASK3				0x63     
#define AD2433_REG_UPOFFSET				0x64   
#define AD2433_REG_DNMASK0				0x65     
#define AD2433_REG_DNMASK1				0x66     
#define AD2433_REG_DNMASK2				0x67     
#define AD2433_REG_DNMASK3				0x68     
#define AD2433_REG_DNOFFSET				0x69   
#define AD2433_REG_CHIPID0				0x6A     
#define AD2433_REG_CHIPID1				0x6B     
#define AD2433_REG_CHIPID2				0x6C     
#define AD2433_REG_CHIPID3				0x6D     
#define AD2433_REG_CHIPID4				0x6E     
#define AD2433_REG_CHIPID5				0x6F     
#define AD2433_REG_DTCFG				0x7C       
#define AD2433_REG_DTSLOTS				0x7D     
#define AD2433_REG_DTDNOFFS				0x7E   
#define AD2433_REG_DTUPOFFS				0x7F   
#define AD2433_REG_GPIODEN				0x80     
#define AD2433_REG_GPIOD0MSK			0x81   
#define AD2433_REG_GPIOD1MSK			0x82   
#define AD2433_REG_GPIOD2MSK			0x83   
#define AD2433_REG_GPIOD3MSK			0x84   
#define AD2433_REG_GPIOD4MSK			0x85   
#define AD2433_REG_GPIOD5MSK			0x86   
#define AD2433_REG_GPIOD6MSK			0x87   
#define AD2433_REG_GPIOD7MSK			0x88   
#define AD2433_REG_GPIODDAT				0x89   
#define AD2433_REG_GPIODINV				0x8A   
#define AD2433_REG_MBOX0CTL				0x90   
#define AD2433_REG_MBOX0STAT			0x91   
#define AD2433_REG_MBOX0B0				0x92     
#define AD2433_REG_MBOX0B1				0x93     
#define AD2433_REG_MBOX0B2				0x94     
#define AD2433_REG_MBOX0B3				0x95     
#define AD2433_REG_MBOX1CTL				0x96   
#define AD2433_REG_MBOX1STAT			0x97   
#define AD2433_REG_MBOX1B0				0x98     
#define AD2433_REG_MBOX1B1				0x99     
#define AD2433_REG_MBOX1B2				0x9A     
#define AD2433_REG_MBOX1B3				0x9B     
#define AD2433_REG_SWCTL2				0xA0     
#define AD2433_REG_SWCTL5				0xA3     
#define AD2433_REG_SWSTAT2				0xA5     
#define AD2433_REG_SPIDTLCMD			0xAF   
#define AD2433_REG_SPICFG				0xB0     
#define AD2433_REG_SPISTAT				0xB1     
#define AD2433_REG_SPICKDIV				0xB2   
#define AD2433_REG_SPIFDSIZE			0xB3   
#define AD2433_REG_SPIFDTARG			0xB4   
#define AD2433_REG_SPIPINCFG			0xB5   
#define AD2433_REG_SPIINT				0xB6     
#define AD2433_REG_SPIMSK				0xB7     
#define AD2433_REG_RXMASK0				0xB8     
#define AD2433_REG_RXMASK1				0xB9     
#define AD2433_REG_RXMASK2				0xBA     
#define AD2433_REG_RXMASK3				0xBB     
#define AD2433_REG_RXMASK4				0xBC     
#define AD2433_REG_RXMASK5				0xBD     
#define AD2433_REG_RXMASK6				0xBE     
#define AD2433_REG_RXMASK7				0xBF     
#define AD2433_REG_TXXBAR0				0xC0     
#define AD2433_REG_TXXBAR1				0xC1     
#define AD2433_REG_TXXBAR2				0xC2     
#define AD2433_REG_TXXBAR3				0xC3     
#define AD2433_REG_TXXBAR4				0xC4     
#define AD2433_REG_TXXBAR5				0xC5     
#define AD2433_REG_TXXBAR6				0xC6     
#define AD2433_REG_TXXBAR7				0xC7     
#define AD2433_REG_TXXBAR8				0xC8     
#define AD2433_REG_TXXBAR9				0xC9     
#define AD2433_REG_TXXBAR10				0xCA   
#define AD2433_REG_TXXBAR11				0xCB   
#define AD2433_REG_TXXBAR12				0xCC   
#define AD2433_REG_TXXBAR13				0xCD   
#define AD2433_REG_TXXBAR14				0xCE   
#define AD2433_REG_TXXBAR15				0xCF   
#define AD2433_REG_TXXBAR16				0xD0   
#define AD2433_REG_TXXBAR17				0xD1   
#define AD2433_REG_TXXBAR18				0xD2   
#define AD2433_REG_TXXBAR19				0xD3   
#define AD2433_REG_TXXBAR20				0xD4   
#define AD2433_REG_TXXBAR21				0xD5   
#define AD2433_REG_TXXBAR22				0xD6   
#define AD2433_REG_TXXBAR23				0xD7   
#define AD2433_REG_TXXBAR24				0xD8   
#define AD2433_REG_TXXBAR25				0xD9   
#define AD2433_REG_TXXBAR26				0xDA   
#define AD2433_REG_TXXBAR27				0xDB   
#define AD2433_REG_TXXBAR28				0xDC   
#define AD2433_REG_TXXBAR29				0xDD   
#define AD2433_REG_TXXBAR30				0xDE   
#define AD2433_REG_TXXBAR31				0xDF   
#define AD2433_REG_MMRPAGE				0xE0     
#define AD2433_REG_VMTR_VEN				0x100  
#define AD2433_REG_VMTR_INTEN				0x101
#define AD2433_REG_VMTR_MXSTAT				0x102
#define AD2433_REG_VMTR_MNSTAT				0x103
#define AD2433_REG_VMTR_VLTGO				0x120
#define AD2433_REG_VMTR_VMAXO				0x121
#define AD2433_REG_VMTR_VMINO				0x122
#define AD2433_REG_VMTR_VLTG1				0x123
#define AD2433_REG_VMTR_VMAX1				0x124
#define AD2433_REG_VMTR_VMIN1				0x125
#define AD2433_REG_VMTR_VLTG2				0x126
#define AD2433_REG_VMTR_VMAX2				0x127
#define AD2433_REG_VMTR_VMIN2				0x128
#define AD2433_REG_VMTR_VLTG3				0x129
#define AD2433_REG_VMTR_VMAX3				0x12A
#define AD2433_REG_VMTR_VMIN3				0x12B
#define AD2433_REG_VMTR_VLTG4				0x12C
#define AD2433_REG_VMTR_VMAX4				0x12D
#define AD2433_REG_VMTR_VMIN4				0x12E
#define AD2433_REG_VMTR_VLTG5				0x12F
#define AD2433_REG_VMTR_VMAX5				0x130
#define AD2433_REG_VMTR_VMIN5				0x131
#define AD2433_REG_VMTR_VLTG6				0x132
#define AD2433_REG_VMTR_VMAX6				0x133
#define AD2433_REG_VMTR_VMIN6				0x134
#define AD2433_REG_PWMCFG					0x140    
#define AD2433_REG_PWMFREQ					0x141    
#define AD2433_REG_PWMBLINK1				0x142  
#define AD2433_REG_PWMBLINK2				0x143  
#define AD2433_REG_PWM1VALL					0x148  
#define AD2433_REG_PWM1VALH					0x149  
#define AD2433_REG_PWM2VALL					0x14A  
#define AD2433_REG_PWM2VALH					0x14B  
#define AD2433_REG_PWM3VALL					0x14C  
#define AD2433_REG_PWM3VALH					0x14D  
#define AD2433_REG_PWMOEVALL				0x14E  
#define AD2433_REG_PWMOEVALH				0x14F  
#define AD2433_REG_MMRPAGE1					0x1E0  

#define AD2433_INT_DSCDONE					24
#define AD2433_INT_PLL_LOCKED				255

#define MAX_A2B_REGISTER_NUM				(AD2433_REG_PWMOEVALH+1)

#define A2B_SLAVE_NODE_NUM					1
#define MAX_A2B_SLAVE_NODE_NUM				16

#define A2B_AD2433_VENDOR					0xAD
#define A2B_AD2433_PRODUCT					0x33
#define A2B_AD2433_VERSION					0x00

#define A2B_AD2428_VENDOR					0xAD
#define A2B_AD2428_PRODUCT					0x28
#define A2B_AD2428_VERSION					0x00

#define A2B_I2S_SYCN_RISING_EDGE_START		0x00
#define A2B_I2S_SYCN_FALLING_EDGE_START		0x80
#define A2B_I2S_SYCN_INV_CFG				A2B_I2S_SYCN_FALLING_EDGE_START	
#define A2B_I2S_SYCN_INV_CFG_MASK			0x7F

#define A2B_RESPONSE_CYCLES					94

#define A2B_INTERRUPT_MASK_0				0x77
#define A2B_INTERRUPT_MASK_1				0x00
#define A2B_INTERRUPT_MASK_2				0x0F

#define A2B_XCVRBINV_NORMAL					0x00
#define A2B_XCVRBINV_INVERTED				0x10
#define A2B_XCVRBINV_CFG					A2B_XCVRBINV_NORMAL
#define A2B_XCVRBINV_CFG_MASK				0xEF

#define A2B_HPSW_CFG_MODE_0					0
#define A2B_HPSW_CFG_MODE_4					4
#define A2B_HIGH_POWER_SWITCH_CFG			A2B_HPSW_CFG_MODE_0
#define A2B_HPSW_CFG_MASK					0xF8

#define A2B_SIMPLE_DISCOVERY_FLOW			1
#define A2B_OPTIMIZED_DISCOVERY_FLOW		2
#define A2B_DISCOVERY_FLOW_MODE				A2B_SIMPLE_DISCOVERY_FLOW

#if A2B_DISCOVERY_FLOW_MODE==A2B_SIMPLE_DISCOVERY_FLOW
typedef enum
{
	A2B_DISC_IDLE=0,
	A2B_DISC_POWER_OFF,
	A2B_DISC_POWER_ON,
	A2B_DISC_RESET_OFF,
	A2B_DISC_SOFT_RESET,
	A2B_DISC_CFG_NODE_TO_MASTER,
	A2B_DISC_WAIT_PLL_LOCKED,
	A2B_DISC_CHECK_HPSW_CFG,
	A2B_DISC_SET_HPSW_CFG,
	A2B_DISC_START_FIND_FIRST_NODE,
	A2B_DISC_WAIT_FIRST_NODE,
	A2B_DISC_FIRST_SET_EXT_SWITCS_MODE,
	
	A2B_DISC_OTHER_CFG_SLAVE_NODE,
	A2B_DISC_OTHER_CHECK_HPSW_CFG,
	A2B_DISC_OTHER_SET_HPSW_CFG,
	A2B_DISC_START_FIND_OTHER_NODE,
	A2B_DISC_WAIT_OTHER_NODE,
	A2B_DISC_OTHER_SET_EXT_SWITCS_MODE,
	A2B_DISC_GET_NODE_INFO,

	A2B_DISC_INIT_SLAVE_NODE,
	A2B_DISC_INIT_SLAVE_DEVICE_START,
	A2B_DISC_INIT_SLAVE_DEVICE_WAIT,
	A2B_DISC_INIT_SLAVE_CFG_ENSW,

	A2B_DISC_INIT_MASTE_NODE,

	A2B_DISC_OK,
	
	A2B_DISC_ERROR
}A2B_DISCOVERY_FLOW_STATE;
#elif A2B_DISCOVERY_FLOW_MODE==A2B_OPTIMIZED_DISCOVERY_FLOW
typedef enum
{
}A2B_DISCOVERY_FLOW_STATE;
#endif

typedef enum
{
	SLAVE_DEVICE_INIT_IDLE=0,
	SLAVE_DEVICE_INIT_START,
	SLAVE_DEVICE_INIT_PRO,
	SLAVE_DEVICE_INIT_END
}A2B_SLAVE_DEVICE_INIT_STATE;

typedef void (* pSlaveNodeInitFun) (void);

typedef struct
{
	u8 vendor;
	u8 product;
	u8 version;
}SLAVE_NODE_INFO;

typedef struct
{
	void (*start_init)(void);
	void (*init_pro)(void);
	u8 (*is_inti_end)(void);
}A2B_SLAVE_DEVICE_FUN;

typedef struct
{
	u8 device_num;
	A2B_SLAVE_DEVICE_FUN *ptr;
}A2B_SLAVE_DEVICE_ITEM;

typedef struct
{
	u8 node_index;
	SLAVE_NODE_INFO node_info;
	pSlaveNodeInitFun node_int_fun;
	A2B_SLAVE_DEVICE_ITEM device_item;
}A2B_SLAVE_NODE_ITEM;

typedef struct
{
	u8 node_num;
	A2B_SLAVE_NODE_ITEM list[MAX_A2B_SLAVE_NODE_NUM];
}A2B_SLAVE_NODE_LIST;

typedef struct
{
	unsigned f_irq_pin_req:1;
}_A2B_PRO_FLAG_;

typedef union
{
	_A2B_PRO_FLAG_ field;
	u32 byte;
}A2B_PRO_FLAG;

typedef struct
{
	u32 timer;
	u8 node_counter;
	u8 device_counter;
	A2B_DISCOVERY_FLOW_STATE state;
}A2B_DISCOVERY_DATA;

typedef struct
{
	A2B_SLAVE_NODE_LIST node_list;
	u8 register_value[MAX_A2B_REGISTER_NUM];
	u8 node_num;
	u8 vendor;
	u8 product;
	u8 version;
	u8 swstat;
	u8 swstat2;
	u8 discstat;
	u8 intpend2;
	A2B_PRO_FLAG flag;
	A2B_DISCOVERY_DATA discovery_data;
}A2B_PRO_DATA;

extern A2B_PRO_DATA A2B_ProData;

#define F_IRQ_PIN_REQ		A2B_ProData.flag.field.f_irq_pin_req	

u8 A2B_I2C_WaitACK(void);
void A2B_I2C_SingleWrite(u8 device_addr,u8 reg_addr,u8 reg_value);
u8 A2B_I2C_SingleRead(u8 device_addr,u8 reg_addr);
void A2B_DiscoveryPro(void);
void A2B_DiscoveryStart(void);

#endif
#endif

