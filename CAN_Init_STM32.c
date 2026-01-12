#include "public.h"

#if CAN_FUNCTION==1
void CAN1_SetErrorFlag(void)
{
	
}

void CAN1_ClearErrorFlag(void)
{
	
}

u8 CAN1_GetErrorFlag(void)
{
	u8 result=0;

	return result;
}

void CAN1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1|RCC_APB1Periph_CAN2,ENABLE);

	/* PA11:CAN1_RX */
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN_RX_PIN;    
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; 
	GPIO_Init(GPIO_CAN_RX_PORT,&GPIO_InitStructure);

	/* PA12:CAN1_TX */
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN_TX_PIN;   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; 
	GPIO_Init(GPIO_CAN_TX_PORT,&GPIO_InitStructure);

	/* PB12:CAN2_RX */
#if CAN_FUN_TRUMPCHI==1
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN2_RX_PIN;    
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; 
	GPIO_Init(GPIO_CAN2_RX_PORT,&GPIO_InitStructure);

	/* PB13:CAN2_TX */
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN2_TX_PIN;   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; 
	GPIO_Init(GPIO_CAN2_TX_PORT,&GPIO_InitStructure);
#endif
#if MODEL==LINUX_D068_55||MODEL==LINUX_D078_55||MODEL==LINUX_P068_55||MODEL==LINUX_D065_55||MODEL==LINUX_P079_55||MODEL==LINUX_D095_55||MODEL==LINUX_1299WM_MG
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN_POWER_PIN;   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_Init(GPIO_CAN_POWER_PORT,&GPIO_InitStructure);
	CAN_IC_POWER_ON;
#endif
#if MODEL==LINUX_P079_55
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN_POWER_PIN2;
	GPIO_Init(GPIO_CAN_POWER_PORT2,&GPIO_InitStructure);
	CAN_IC_POWER_ON2;
#endif
#if MODEL==LINUX_P068_55||MODEL==LINUX_D068_55||MODEL==LINUX_D065_55||MODEL==LINUX_P079_55||MODEL==LINUX_D095_55
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN_EN_PIN;   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_Init(GPIO_CAN_EN_PORT,&GPIO_InitStructure);
	CAN_IC_ENABLE;
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN_ERROR_PIN;   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIO_CAN_ERROR_PORT,&GPIO_InitStructure);	
#endif
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN_STANDBY_PIN;   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_Init(GPIO_CAN_STANDBY_PORT,&GPIO_InitStructure);
#if CAN_FUN_TRUMPCHI==1
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN2_STANDBY_PIN;
	GPIO_Init(GPIO_CAN2_STANDBY_PORT,&GPIO_InitStructure);
#endif
	CAN_IC_STANDBY_OFF;
#if CAN_FUN_TRUMPCHI==1
	CAN2_IC_STANDBY_OFF;
	CAN_DeInit(CAN2); 
#endif
	
	CAN_DeInit(CAN1);  
	
	
	CAN_StructInit(&CAN_InitStructure);
	CAN_InitStructure.CAN_TTCM=DISABLE;         
	CAN_InitStructure.CAN_ABOM=DISABLE;        
	CAN_InitStructure.CAN_AWUM=DISABLE;         
	CAN_InitStructure.CAN_NART=DISABLE;         
	CAN_InitStructure.CAN_RFLM=DISABLE;         
	CAN_InitStructure.CAN_TXFP=DISABLE;         
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; 

	//BandRate = (36M / (BRP[9:0] + 1) / ((TS1[3:0] + 1) + (TS2[2:0] + 1))) 
	//                                                                    tBS1               tBS2     
#if CAN_FUN_PEUGEOT_207==1||CAN_FUN_IKCO_K132==1
/*********************** 125K **************************/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      
	CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      
	CAN_InitStructure.CAN_Prescaler=48;
#elif CAN_FUN_HYUNDAI_TUCSON==1||CAN_FUN_TOYOTA_PROMASTER==1||CAN_FUN_SAIPA_SP100==1
/*********************** 100K **************************/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      
	CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      
	CAN_InitStructure.CAN_Prescaler=60;
#elif CAN_FUN_ZHIZI_NE3==1
/*********************** 500K **************************/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      
	CAN_InitStructure.CAN_BS1=CAN_BS1_6tq; 
	CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;      
	CAN_InitStructure.CAN_Prescaler=9;
#else
/*********************** 500K **************************/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      
	CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      
	CAN_InitStructure.CAN_Prescaler=12;
#endif
	CAN_Init(CAN1,&CAN_InitStructure);
	
#if CAN_FUN_TRUMPCHI==1
	CAN_Init(CAN2,&CAN_InitStructure);  
#endif

#if CAN_FUN_PEUGEOT_207==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 

	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= CAN_ID_NMM_C_1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow= CAN_ID_CCNC1_C<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_FEI_F<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_NMM_C_2<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);   

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= CAN_ID_MTC_SGL<<5;           
	CAN_FilterInitStructure.CAN_FilterIdLow= CAN_ID_BACKL_IC<<5;           
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_CCNGW1_C<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_VIN1_MM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= CAN_ID_LS_BCM_HS3<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= CAN_ID_ICN_INFO1<<5;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_VIN2_MM<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_PASD_C<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=3;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= CAN_ID_VIN3_MM<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= CAN_ID_FAM_INFO<<5;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_FDS_D<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_RDS_R<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=4;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= CAN_ID_CLUSTER_ODO<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= CAN_ID_FOS_F<<5;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ROS_R<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_EMS67<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=5;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= CAN_ID_BCM_PAS<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= CAN_ID_LS_BCM_OS<<5;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_FAM_OS<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_TEMP_AMBT<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=6;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= CAN_ID_CCN_TPMS_COMMON<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= 0;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure); 
	
#elif CAN_FUN_HAIMA_S7==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 

	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_GW<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_HVAC<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_PEPS<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);   

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_SVM<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_DIAG_IST_REQ<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_SPEED<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_THROTTLE<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_GEAR<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_SAS<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_TEST<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure);  
	
#elif CAN_FUN_CHERY_TIGGO_3==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_4<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_NMm_BCM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_CLM_2<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_IPM_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_PEPS_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_ICM_3<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 	

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_SAM_1_G<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_ABS_G<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_DIAGNOSTIC_RX_ID<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure); 	
	
#elif CAN_FUN_CHERY_TIGGO_5==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_4<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_NMm_BCM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_CLM_2<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_IPM_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_AVM_1<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_IPM_1<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_5<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_3<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_BCM_SAM_1_G<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_ABS_G<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=3;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_7<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=0;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
#elif CAN_FUN_CHERY_TIGGO_7==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_4<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_NMm_BCM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_CLM_2<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_IPM_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_AVM_1<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_IPM_1<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_5<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_3<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_BCM_SAM_1_G<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_ABS_G<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=3;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_7<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=0;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
#elif CAN_FUN_CHERY_ARRIZO_6==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_4<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_NMm_BCM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_IPM_2<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_AVM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_LDW_1<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_ICM_3<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_SAM_1_G<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_ABS_G<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_4<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_PEPS_G<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 
	
#elif CAN_FUN_CHERY_TIGGO_2==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_4<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_NMm_BCM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_SAM_1_G<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_ABS_G<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_3<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure); 
	
#elif CAN_FUN_CHERY_ARRIZO_5==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_4<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_NMm_BCM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_CLM_2<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_IPM_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_PEPS_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_ICM_3<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 	

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_SAM_1_G<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_ABS_G<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_DIAGNOSTIC_RX_ID<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure); 	
	
#elif CAN_FUN_CHERY_TIGGO_5X_T19
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_4<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_NMm_BCM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

#elif CAN_FUN_CHERY_TIGGO_5X==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 

	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_4<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICM_3<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_SAM_1_G<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);   

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_IPM_2<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_PEPS_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_AVM<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure); 
	
#elif CAN_FUN_HAIMA_S5==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_VEHICLE_WARNING<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_INFO<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_TCU_INFO<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_STEER_INFO<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);   
	
#elif CAN_FUN_HYUNDAI_TUCSON==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_ALARM<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BRIGHTNESS<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_DOOR_STATUS<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_PARKING_SENSORS<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);   

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_VEHICLE_INDICATIONS<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=0;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure);   

#elif CAN_FUN_TRUMPCHI==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 

	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_GW_MRR_1_B<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_BCAN_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_BCM_BCAN_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_BCAN_4<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);   

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_HVACF_1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_HVACF_3<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_PEPS_6<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_ICM_1_B<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_ICM_3_B<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_4_B<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_GW_SAS_1_B<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_MSM_1<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=3;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_GW_EPS_1_B<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_HVSM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_FCP_3<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_FCP_5<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=4;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_GW_1_B<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_PANEL_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_LIGHT_1;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 

	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_PCS_1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_IFC_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_PAS_1<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_PAS_2<<5;
	CAN2_FilterInit(&CAN_FilterInitStructure);   

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_WCM_1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BSD_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN2_FilterInit(&CAN_FilterInitStructure);   
#elif CAN_FUN_IKCO_K132==1
  FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_MMS_DATE_TIME<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_MMS_CONFIG<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_MMS_FAULT<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_MMS_DIAGNOSTIC_ANSWER<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  
	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_MMS_SUPER<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_MMS_VERSION<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_BCM_MEDIA<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_CLUSTER<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 	
	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_NETWORK<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_BAOADCAST<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_BCM_PARKING<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_DATA_SLOW<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_FilterInitStructure.CAN_FilterNumber=3;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_DATA_SLOW2<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_DATA_SLOW3<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_BCM_SPEED<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_CONSUMPTION<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  
	CAN_FilterInitStructure.CAN_FilterNumber=4;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_TRIP_INFOS1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_TRIP_INFOS2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_MMS_DIAGNOSTIC_REQUEST<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BCM_VIN_WMI<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 	
	CAN_FilterInitStructure.CAN_FilterNumber=5;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_VIN_VDS<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_VIN_VIS<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ICN_INFO<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_ATC_ACK<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 
	CAN_FilterInitStructure.CAN_FilterNumber=6;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_ATC_INFO<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ATC_SUPERVISION<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);
#elif CAN_FUN_TOYOTA_PROMASTER==1
  FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_RX1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=0;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure); 
	
#elif CAN_FUN_MORRIS_GARAGES==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 

	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_REVERSE<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_PARKING<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ILLUMI<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure);
#elif CAN_FUN_ZHIZI_NE3==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 

	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=((((unsigned int)CAN_ID_CGW_VEHINFO1<<3)>>16)&0xffff);    
	CAN_FilterInitStructure.CAN_FilterIdLow=(((unsigned int)CAN_ID_CGW_VEHINFO1<<3)&0xffff)|CAN_ID_EXT;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=(((unsigned int)CAN_ID_EVT_TD<<3)>>16)&0xffff;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=(((unsigned int)CAN_ID_EVT_TD<<3)&0xffff)|CAN_ID_EXT;
	CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=(((unsigned int)CAN_ID_BPDU_OUTCTRLST<<3)>>16)&0xffff;    
	CAN_FilterInitStructure.CAN_FilterIdLow=(((unsigned int)CAN_ID_BPDU_OUTCTRLST<<3)&0xffff)|CAN_ID_EXT;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=(((unsigned int)CAN_ID_BPDU_VEHPWRSTS<<3)>>16)&0xffff;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=(((unsigned int)CAN_ID_BPDU_VEHPWRSTS<<3)&0xffff)|CAN_ID_EXT;
	CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=(((unsigned int)CAN_ID_BPDU_MFLCTRL<<3)>>16)&0xffff;    
	CAN_FilterInitStructure.CAN_FilterIdLow=(((unsigned int)CAN_ID_BPDU_MFLCTRL<<3)&0xffff)|CAN_ID_EXT;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=(((unsigned int)CAN_ID_CGW_ADAS_INFO<<3)>>16)&0xffff;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=(((unsigned int)CAN_ID_CGW_ADAS_INFO<<3)&0xffff)|CAN_ID_EXT;
	CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_FilterInitStructure.CAN_FilterNumber=3;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=(((unsigned int)CAN_ID_AVM_REQ<<3)>>16)&0xffff;    
	CAN_FilterInitStructure.CAN_FilterIdLow=(((unsigned int)CAN_ID_AVM_REQ<<3)&0xffff)|CAN_ID_EXT;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure);
#elif CAN_FUN_SAIPA_SP100==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_EMS_1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_CHASSIS<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_BODY_1<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_BODY_2<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BODY_3<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ASSIST<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_TPMS_1<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_TPMS_2<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_PHYSICAL_REQ<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_BCM_NM<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_ICM_NM<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  
#elif CAN_FUN_MAHINDRA_SCORPIO11==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_EMS_1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_MBFM_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_FATC_1<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_MBFM_5<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_MBFM_6<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_MBFM_7<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_RPAS_1<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;//CAN_ID_TPMS_2<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

#elif CAN_FUN_HAIMA_8S==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_AVM<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_T_BOX_9<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ESP_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_ICM_1<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_ICM_2<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_ICM_3<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_ACP<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_TPMS_1<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_BCM_1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_BCM_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_CCM<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_CCM_2<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=3;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_EPS<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_MRR_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_EMS_4<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_SCM_1<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 

	CAN_FilterInitStructure.CAN_FilterNumber=4;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_APM_1<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_MPC_1<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_SAS<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=CAN_ID_LCAS<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 

	CAN_FilterInitStructure.CAN_FilterNumber=5;  
	CAN_FilterInitStructure.CAN_FilterIdHigh=CAN_ID_IAL<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow=CAN_ID_TPMS_2<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=CAN_ID_TCU_2<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0<<5;
	CAN_FilterInit(&CAN_FilterInitStructure); 
#else
#endif      

	CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE); 
	//CAN_ITConfig(CAN2,CAN_IT_FMP0, ENABLE);

	FormatMemery((u8*)&NVIC_InitStructure,sizeof(NVIC_InitStructure));
	NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#if CAN_FUN_TRUMPCHI==1
  CAN_ITConfig(CAN2,CAN_IT_FMP0, ENABLE);
	FormatMemery((u8*)&NVIC_InitStructure,sizeof(NVIC_InitStructure));
	NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
	F_CAN_INIT=1;
}
#if MODEL==LINUX_Y039_55
/*两个can都需要使用时注意！！！
  过滤器不要重复，否则后初始化的将会覆盖掉先初始化的
*/
void CAN2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2,ENABLE);
	
	/* PB12:CAN2_RX */
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN2_RX_PIN;    
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; 
	GPIO_Init(GPIO_CAN2_RX_PORT,&GPIO_InitStructure);

	/* PB13:CAN2_TX */
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN2_TX_PIN;   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; 
	GPIO_Init(GPIO_CAN2_TX_PORT,&GPIO_InitStructure);
	
	/* PE15:CAN2_STANDBY */
	FormatMemery((u8*)&GPIO_InitStructure,sizeof(GPIO_InitStructure));
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN2_STANDBY_PIN;   
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin=GPIO_CAN2_STANDBY_PIN;
	GPIO_Init(GPIO_CAN2_STANDBY_PORT,&GPIO_InitStructure);
	CAN2_IC_STANDBY_OFF;
	
	CAN_DeInit(CAN2); 
	
	CAN_StructInit(&CAN_InitStructure);
	CAN_InitStructure.CAN_TTCM=DISABLE;         
	CAN_InitStructure.CAN_ABOM=DISABLE;        
	CAN_InitStructure.CAN_AWUM=DISABLE;         
	CAN_InitStructure.CAN_NART=DISABLE;         
	CAN_InitStructure.CAN_RFLM=DISABLE;         
	CAN_InitStructure.CAN_TXFP=DISABLE;         
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; 

	//BandRate = (36M / (BRP[9:0] + 1) / ((TS1[3:0] + 1) + (TS2[2:0] + 1))) 
	//                                                                    tBS1               tBS2     
#if 0
/*********************** 125K **************************/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      
	CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      
	CAN_InitStructure.CAN_Prescaler=48;
#elif 0
/*********************** 100K **************************/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      
	CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      
	CAN_InitStructure.CAN_Prescaler=60;
#else
/*********************** 500K **************************/
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;      
	CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;      
	CAN_InitStructure.CAN_Prescaler=12;
#endif
	CAN_Init(CAN2,&CAN_InitStructure);  
#if CAN_FUN_HAIMA_S7_360==1
	FormatMemery((u8*)&CAN_FilterInitStructure,sizeof(CAN_FilterInitStructure));     
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList;   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; 
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;     
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 

	CAN_FilterInitStructure.CAN_FilterNumber=0;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= 0<<5;    
	CAN_FilterInitStructure.CAN_FilterIdLow= 0<<5;       
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);   

	CAN_FilterInitStructure.CAN_FilterNumber=1;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= 0<<5;           
	CAN_FilterInitStructure.CAN_FilterIdLow= 0<<5;           
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=2;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= 0<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= 0<<5;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=3;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= 0<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= 0<<5;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=4;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= 0<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= 0<<5;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=5;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= 0<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= 0<<5;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0<<5;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0<<5;
	CAN_FilterInit(&CAN_FilterInitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=6;  
	CAN_FilterInitStructure.CAN_FilterIdHigh= 0<<5;       
	CAN_FilterInitStructure.CAN_FilterIdLow= 0;        
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0;            
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0;
	CAN_FilterInit(&CAN_FilterInitStructure);
#else
#endif      
	CAN_ITConfig(CAN2,CAN_IT_FMP0, ENABLE);

	FormatMemery((u8*)&NVIC_InitStructure,sizeof(NVIC_InitStructure));
	NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	F_CAN_INIT=1;
}
#endif
void CAN1_Transmit(void)
{
	u8 mailbox;
	u32 i;
	CAN_MESSAGE_INFO TxMessage;
	CanTxMsg message;

	if(CanTxBuffer.length > 0)
	{
		FormatMemery((u8*)&TxMessage,sizeof(TxMessage));
		TxMessage = CanTxBuffer.message[CanTxBuffer.head];
		
		message.StdId=TxMessage.ID;
		message.RTR=TxMessage.RTR;
		message.IDE=TxMessage.IDE;
		message.DLC=TxMessage.DLC;
		for(i=0;i<8;i++)
		{
			message.Data[i]=TxMessage.Data[i];
		}
			
		CanTxBuffer.head = (CanTxBuffer.head+1)%CAN_TX_BUFFER_LENGTH;
		CanTxBuffer.length--;

		if(CanTxBuffer.head >= CAN_TX_BUFFER_LENGTH)
		{
			CanTxBuffer.head = 0;
		}
		i=0;
		mailbox=CAN_Transmit(CAN1,&message);
		while((CAN_TransmitStatus(CAN1,mailbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
		{
			i++;    //等待发送结束 
		}
#if CAN_FUN_HAIMA_S7==1
		if(mailbox==CAN_TxStatus_NoMailBox)
		{
			CanNoTxCounter++;
			if(CanNoTxCounter>=60)
			{
				Haima_S7_CanReset();
				CanNoTxCounter=0;
			}
		}
		if(i>=0xFFF)
		{
			CanTxErrorCounter++;
			if(CanTxErrorCounter>=60)
			{
				Haima_S7_CanReset();
				CanTxErrorCounter=0;
			}
		}
#endif
	}
}

#if CAN_FUN_TRUMPCHI==1||CAN_FUN_HAIMA_S7_360==1
void CAN2_Transmit(void)
{
	u8 mailbox;
	u32 i;
	CAN_MESSAGE_INFO TxMessage;
	CanTxMsg message;

	if(CanTxBuffer2.length > 0)
	{
		FormatMemery((u8*)&TxMessage,sizeof(TxMessage));
		TxMessage = CanTxBuffer2.message[CanTxBuffer2.head];
		
		message.StdId=TxMessage.ID;
		message.RTR=TxMessage.RTR;
		message.IDE=TxMessage.IDE;
		message.DLC=TxMessage.DLC;
		for(i=0;i<8;i++)
		{
			message.Data[i]=TxMessage.Data[i];
		}
			
		CanTxBuffer2.head = (CanTxBuffer2.head+1)%CAN_TX_BUFFER_LENGTH;
		CanTxBuffer2.length--;

		if(CanTxBuffer2.head >= CAN_TX_BUFFER_LENGTH)
		{
			CanTxBuffer2.head = 0;
		}
		i=0;
		mailbox=CAN_Transmit(CAN2,&message);
		while((CAN_TransmitStatus(CAN2,mailbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
		{
			i++;    
		}
	}
}
#endif
void CAN1_Ext_Transmit(void)
{
	u8 mailbox;
	u32 i;
	CAN_MESSAGE_INFO TxMessage;
	CanTxMsg message;

	if(CanTxBuffer.length > 0)
	{
		FormatMemery((u8*)&TxMessage,sizeof(TxMessage));
		TxMessage = CanTxBuffer.message[CanTxBuffer.head];
		
		message.ExtId=TxMessage.ID;
		message.RTR=TxMessage.RTR;
		message.IDE=0x04;
		message.DLC=TxMessage.DLC;
		for(i=0;i<8;i++)
		{
			message.Data[i]=TxMessage.Data[i];
		}
			
		CanTxBuffer.head = (CanTxBuffer.head+1)%CAN_TX_BUFFER_LENGTH;
		CanTxBuffer.length--;

		if(CanTxBuffer.head >= CAN_TX_BUFFER_LENGTH)
		{
			CanTxBuffer.head = 0;
		}
		i=0;
		mailbox=CAN_Transmit(CAN1,&message);
		while((CAN_TransmitStatus(CAN1,mailbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
		{
			i++;
		}
	}
}

void CAN1_TransBytefraem(u32 ID,u8 *data,u8 length)
{
	CanTxMsg message;
	u8 mailbox;
	u32 i;
	
	FormatMemery((u8 *) &message, sizeof(message));
	message.StdId=ID;
	message.IDE=CAN_IDE_STD;
	message.RTR=CAN_RTR_STD;
	message.DLC=length;
	Mem_strcpy(message.Data,data,length);
	mailbox=CAN_Transmit(CAN1,&message);
	while((CAN_TransmitStatus(CAN1,mailbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
	{
		i++;   
	}
}

void CAN2_TransBytefraem(u32 ID,u8 *data,u8 length)
{
	CanTxMsg message;
	u8 mailbox;
	u32 i;
	
	FormatMemery((u8 *) &message, sizeof(message));
	message.StdId=ID;
	message.IDE=CAN_IDE_STD;
	message.RTR=CAN_RTR_STD;
	message.DLC=length;
	Mem_strcpy(message.Data,data,length);
	mailbox=CAN_Transmit(CAN2,&message);
	while((CAN_TransmitStatus(CAN2,mailbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
	{
		i++;   
	}
}

#if CAN_FUN_ZHIZI_NE3==1
void CAN_RxInterruptPro(void)
{
	u32 i;
	CanRxMsg RxMessage;
	CAN_MESSAGE_INFO message;
	
	if(CAN_MessagePending(CAN1,CAN_FIFO0))
	{
		CAN_Receive(CAN1, CAN_FIFO0,&RxMessage);
		message.ID=RxMessage.ExtId;
		message.DLC=RxMessage.DLC;
		message.IDE=RxMessage.IDE;
		message.RTR=RxMessage.RTR;
		for(i=0;i<8;i++)
		{
			message.Data[i]=RxMessage.Data[i];
		}
		if(((CanRxBuffer.tail+1)% CAN_RX_BUFFER_LENGTH)!=CanRxBuffer.head)
		{
			CanRxBuffer.message[CanRxBuffer.tail]=message;
			CanRxBuffer.tail=(CanRxBuffer.tail+1)%CAN_RX_BUFFER_LENGTH;
		}
	}
}
#else
void CAN_RxInterruptPro(void)
{
	u32 i;
	CanRxMsg RxMessage;
	CAN_MESSAGE_INFO message;
	
	if(CAN_MessagePending(CAN1,CAN_FIFO0))
	{
		CAN_Receive(CAN1, CAN_FIFO0,&RxMessage);
		message.ID=RxMessage.StdId;
		message.DLC=RxMessage.DLC;
		message.IDE=RxMessage.IDE;
		message.RTR=RxMessage.RTR;
		for(i=0;i<8;i++)
		{
			message.Data[i]=RxMessage.Data[i];
		}
		if(((CanRxBuffer.tail+1)% CAN_RX_BUFFER_LENGTH)!=CanRxBuffer.head)
		{
			CanRxBuffer.message[CanRxBuffer.tail]=message;
			CanRxBuffer.tail=(CanRxBuffer.tail+1)%CAN_RX_BUFFER_LENGTH;
		}
	}
}
#endif

#if CAN_FUN_TRUMPCHI==1||CAN_FUN_HAIMA_S7_360==1
void CAN2_RxInterruptPro(void)
{
	u32 i;
	CanRxMsg RxMessage;
	CAN_MESSAGE_INFO message;
	
	if(CAN_MessagePending(CAN2,CAN_FIFO0))
	{
		CAN_Receive(CAN2, CAN_FIFO0,&RxMessage);
		message.ID=RxMessage.StdId;
		message.DLC=RxMessage.DLC;
		message.IDE=RxMessage.IDE;
		message.RTR=RxMessage.RTR;
		for(i=0;i<8;i++)
		{
			message.Data[i]=RxMessage.Data[i];
		}
		if(((CanRxBuffer2.tail+1)% CAN_RX_BUFFER_LENGTH)!=CanRxBuffer2.head)
		{
			CanRxBuffer2.message[CanRxBuffer2.tail]=message;
			CanRxBuffer2.tail=(CanRxBuffer2.tail+1)%CAN_RX_BUFFER_LENGTH;
		}
	}
}
#endif
#if CAN_BUS_OFF_FUN==1
void BUS_OFF_Recovery_Main(void)
{
	CAN1->MCR|=CAN_MCR_INRQ;/* Request initialisation */
	while(!(CAN1->MSR&CAN_MSR_INAK));

	CAN1->MCR&=~CAN_MCR_INRQ;/* Request leave initialisation */
	while(CAN1->MSR&CAN_MSR_INAK);
}
#endif
#endif

