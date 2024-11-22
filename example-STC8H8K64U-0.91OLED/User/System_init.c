/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 锟斤拷锟揭�锟节筹拷锟斤拷锟斤拷使锟矫此达拷锟斤拷,锟斤拷锟节筹拷锟斤拷锟斤拷注锟斤拷使锟斤拷锟斤拷STC锟斤拷锟斤拷锟较硷拷锟斤拷锟斤拷            */
/*---------------------------------------------------------------------*/

#include	"config.h"
#include	"STC8G_H_GPIO.h"
#include	"STC8H_PWM.h"
#include	"STC8G_H_ADC.h"
#include	"STC8G_PCA.h"
#include	"STC8G_H_Exti.h"
#include	"STC8G_H_I2C.h"
#include	"STC8G_H_SPI.h"
#include	"STC8G_H_Timer.h"
#include	"STC8G_H_UART.h"
#include	"STC8G_H_Compare.h"
#include	"STC8G_PWM15bit.h"
#include	"STC8G_H_Delay.h"
#include	"STC8G_H_Switch.h"
#include	"STC8G_H_WDT.h"
#include	"STC8G_H_NVIC.h"
#include	"app.h"

//========================================================================
//                                IO锟斤拷锟斤拷锟斤拷
//========================================================================
void	GPIO_config(void)
{
// 	P0_MODE_IO_PU(GPIO_Pin_All);		//P0 锟斤拷锟斤拷为准双锟斤拷锟�
// 	P1_MODE_IN_HIZ(GPIO_Pin_LOW);		//P1.0~P1.3 锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟斤拷
// 	P1_MODE_OUT_OD(GPIO_Pin_4 | GPIO_Pin_5);		//P1.4,P1.5 锟斤拷锟斤拷为漏锟斤拷锟斤拷路
// 	P2_MODE_IO_PU(GPIO_Pin_All);		//P2 锟斤拷锟斤拷为准双锟斤拷锟�
// 	P3_MODE_IO_PU(GPIO_Pin_LOW);		//P3.0~P3.3 锟斤拷锟斤拷为准双锟斤拷锟�
// 	P3_MODE_IO_PU(GPIO_Pin_HIGH);		//P3.4~P3.7 锟斤拷锟斤拷为准双锟斤拷锟�
// //	P3_MODE_IN_HIZ(GPIO_Pin_6 | GPIO_Pin_7);		//P3.6,P3.7 锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟斤拷
// 	P4_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_6 | GPIO_Pin_7);	//P4.0,P4.6,P4.7 锟斤拷锟斤拷为准双锟斤拷锟�
// 	P6_MODE_IO_PU(GPIO_Pin_All);		//P6 锟斤拷锟斤拷为准双锟斤拷锟�
// 	P7_MODE_IO_PU(GPIO_Pin_All);		//P7 锟斤拷锟斤拷为准双锟斤拷锟�
	
// 	P1_PULL_UP_ENABLE(GPIO_Pin_4 | GPIO_Pin_5);	//P1.4,P1.5 锟斤拷锟斤拷锟节诧拷锟斤拷锟斤拷
	P1_MODE_IO_PU(GPIO_Pin_4 | GPIO_Pin_5); // P2.4,P2.5 设置为准双向口
}

//========================================================================
//                               锟斤拷时锟斤拷锟斤拷锟斤拷
//========================================================================
void	Timer_config(void)
{
	TIM_InitTypeDef		TIM_InitStructure;                  //锟结构锟斤拷锟斤拷
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;  //指锟斤拷锟斤拷锟斤拷模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;         //指锟斤拷时锟斤拷源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;              //锟角凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�, ENABLE锟斤拷DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);   //锟斤拷值,
	TIM_InitStructure.TIM_Run       = ENABLE;               //锟角凤拷锟绞硷拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞憋拷锟�, ENABLE锟斤拷DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);               //锟斤拷始锟斤拷Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
	NVIC_Timer0_Init(ENABLE,Priority_0);    //锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3

//	//锟斤拷时锟斤拷1锟斤拷16位锟皆讹拷锟斤拷装, 锟叫讹拷频锟斤拷为20000HZ锟斤拷锟叫断猴拷锟斤拷锟斤拷P6.6取锟斤拷锟斤拷锟�10KHZ锟斤拷锟斤拷锟脚猴拷.
//	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指锟斤拷锟斤拷锟斤拷模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_T1Stop
//	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指锟斤拷时锟斤拷源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
//	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//锟角凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�, ENABLE锟斤拷DISABLE
//	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 20000);			//锟斤拷值,
//	TIM_InitStructure.TIM_Run       = ENABLE;				//锟角凤拷锟绞硷拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞憋拷锟�, ENABLE锟斤拷DISABLE
//	Timer_Inilize(Timer1,&TIM_InitStructure);				//锟斤拷始锟斤拷Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4
//	NVIC_Timer1_Init(ENABLE,Priority_0);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3

//	//锟斤拷时锟斤拷2锟斤拷16位锟皆讹拷锟斤拷装, 锟叫讹拷频锟斤拷为10000HZ锟斤拷锟叫断猴拷锟斤拷锟斤拷P6.5取锟斤拷锟斤拷锟�5KHZ锟斤拷锟斤拷锟脚猴拷.
//	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指锟斤拷时锟斤拷源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
//	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//锟角凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�, ENABLE锟斤拷DISABLE
//	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 10000);				//锟斤拷值
//	TIM_InitStructure.TIM_PS        = 0;					//8位预锟斤拷频锟斤拷(n+1), 0~255, (注锟斤拷:锟斤拷锟斤拷锟斤拷锟斤拷系锟叫讹拷锟叫此寄达拷锟斤拷,锟斤拷锟斤拷锟斤拷榭达拷锟斤拷锟斤拷植锟�)
//	TIM_InitStructure.TIM_Run       = ENABLE;				//锟角凤拷锟绞硷拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞憋拷锟�, ENABLE锟斤拷DISABLE
//	Timer_Inilize(Timer2,&TIM_InitStructure);				//锟斤拷始锟斤拷Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
//	NVIC_Timer2_Init(ENABLE,NULL);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟斤拷锟饺硷拷

//	//锟斤拷时锟斤拷3锟斤拷16位锟皆讹拷锟斤拷装, 锟叫讹拷频锟斤拷为100HZ锟斤拷锟叫断猴拷锟斤拷锟斤拷P6.4取锟斤拷锟斤拷锟�50HZ锟斤拷锟斤拷锟脚猴拷.
//	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;	//指锟斤拷时锟斤拷源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
//	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//锟角凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�, ENABLE锟斤拷DISABLE
//	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (100*12));		//锟斤拷值
//	TIM_InitStructure.TIM_PS        = 0;					//8位预锟斤拷频锟斤拷(n+1), 0~255, (注锟斤拷:锟斤拷锟斤拷锟斤拷锟斤拷系锟叫讹拷锟叫此寄达拷锟斤拷,锟斤拷锟斤拷锟斤拷榭达拷锟斤拷锟斤拷植锟�)
//	TIM_InitStructure.TIM_Run       = ENABLE;				//锟角凤拷锟绞硷拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞憋拷锟�, ENABLE锟斤拷DISABLE
//	Timer_Inilize(Timer3,&TIM_InitStructure);				//锟斤拷始锟斤拷Timer3	  Timer0,Timer1,Timer2,Timer3,Timer4
//	NVIC_Timer3_Init(ENABLE,NULL);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟斤拷锟饺硷拷

//	//锟斤拷时锟斤拷4锟斤拷16位锟皆讹拷锟斤拷装, 锟叫讹拷频锟斤拷为50HZ锟斤拷锟叫断猴拷锟斤拷锟斤拷P6.3取锟斤拷锟斤拷锟�25HZ锟斤拷锟斤拷锟脚猴拷.
//	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;	//指锟斤拷时锟斤拷源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
//	TIM_InitStructure.TIM_ClkOut    = ENABLE;				//锟角凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�, ENABLE锟斤拷DISABLE
//	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / (50*12));		//锟斤拷值
//	TIM_InitStructure.TIM_PS        = 0;					//8位预锟斤拷频锟斤拷(n+1), 0~255, (注锟斤拷:锟斤拷锟斤拷锟斤拷锟斤拷系锟叫讹拷锟叫此寄达拷锟斤拷,锟斤拷锟斤拷锟斤拷榭达拷锟斤拷锟斤拷植锟�)
//	TIM_InitStructure.TIM_Run       = ENABLE;				//锟角凤拷锟绞硷拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞憋拷锟�, ENABLE锟斤拷DISABLE
//	Timer_Inilize(Timer4,&TIM_InitStructure);				//锟斤拷始锟斤拷Timer4	  Timer0,Timer1,Timer2,Timer3,Timer4
//	NVIC_Timer4_Init(ENABLE,NULL);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟斤拷锟饺硷拷
}

//========================================================================
//                              ADC锟斤拷始锟斤拷
//========================================================================
void	ADC_config(void)
{
	ADC_InitTypeDef		ADC_InitStructure;		//锟结构锟斤拷锟斤拷
	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模锟斤拷锟脚号诧拷锟斤拷时锟斤拷锟斤拷锟�, 0~31锟斤拷注锟解： SMPDUTY 一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷小锟斤拷 10锟斤拷
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通锟斤拷选锟斤拷时锟斤拷锟斤拷锟� 0(默锟斤拷),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通锟斤拷选锟今保筹拷时锟斤拷锟斤拷锟� 0,1(默锟斤拷),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X16T;		//锟斤拷锟斤拷 ADC 锟斤拷锟斤拷时锟斤拷频锟斤拷	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC锟斤拷锟斤拷锟斤拷锟�,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//锟斤拷始锟斤拷
	ADC_PowerControl(ENABLE);				//ADC锟斤拷源锟斤拷锟斤拷, ENABLE锟斤拷DISABLE
	NVIC_ADC_Init(DISABLE,Priority_0);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3
}

//========================================================================
//                              锟斤拷锟节筹拷始锟斤拷
//========================================================================
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;				//锟结构锟斤拷锟斤拷

	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;		//选锟斤拷锟斤拷锟绞凤拷锟斤拷锟斤拷, BRT_Timer1, BRT_Timer2 (注锟斤拷: 锟斤拷锟斤拷2锟教讹拷使锟斤拷BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;		//锟斤拷锟斤拷锟斤拷, 一锟斤拷 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;			//锟斤拷锟斤拷锟斤拷锟斤拷,   ENABLE锟斤拷DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;		//锟斤拷锟斤拷锟绞加憋拷, ENABLE锟斤拷DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//锟斤拷始锟斤拷锟斤拷锟斤拷1 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3

//	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
////	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;	//选锟斤拷锟斤拷锟绞凤拷锟斤拷锟斤拷, BRT_Timer2 (注锟斤拷: 锟斤拷锟斤拷2锟教讹拷使锟斤拷BRT_Timer2, 锟斤拷锟皆诧拷锟斤拷选锟斤拷)
//	COMx_InitStructure.UART_BaudRate  = 115200ul;		//锟斤拷锟斤拷锟斤拷,     110 ~ 115200
//	COMx_InitStructure.UART_RxEnable  = ENABLE;			//锟斤拷锟斤拷锟斤拷锟斤拷,   ENABLE锟斤拷DISABLE
//	UART_Configuration(UART2, &COMx_InitStructure);		//锟斤拷始锟斤拷锟斤拷锟斤拷2 UART1,UART2,UART3,UART4
//	NVIC_UART2_Init(ENABLE,Priority_1);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3
}

//========================================================================
//                               I2C锟斤拷始锟斤拷
//========================================================================
void	I2C_config(void)
{
	I2C_InitTypeDef		I2C_InitStructure;
	I2C_InitStructure.I2C_Mode      = I2C_Mode_Master;	//锟斤拷锟斤拷选锟斤拷   I2C_Mode_Master, I2C_Mode_Slave
	I2C_InitStructure.I2C_Enable    = ENABLE;			//I2C锟斤拷锟斤拷使锟斤拷,   ENABLE, DISABLE
	I2C_InitStructure.I2C_MS_WDTA   = DISABLE;			//锟斤拷锟斤拷使锟斤拷锟皆讹拷锟斤拷锟斤拷,  ENABLE, DISABLE
	I2C_InitStructure.I2C_Speed     = 16;				//锟斤拷锟斤拷锟劫讹拷=Fosc/2/(Speed*2+4),      0~63
	I2C_Init(&I2C_InitStructure);
	NVIC_I2C_Init(I2C_Mode_Master,DISABLE,Priority_0);	//锟斤拷锟斤拷模式, I2C_Mode_Master, I2C_Mode_Slave; 锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3
	I2C_SW(I2C_P14_P15); // I2C_P14_P15,I2C_P24_P25,I2C_P76_P77,I2C_P33_P32
}

//========================================================================
//                               SPI锟斤拷始锟斤拷
//========================================================================
void	SPI_config(void)
{
	SPI_InitTypeDef		SPI_InitStructure;

	SPI_InitStructure.SPI_Enable    = ENABLE;				//SPI锟斤拷锟斤拷    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG      = ENABLE;				//片选位     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit  = SPI_MSB;				//锟斤拷位锟斤拷锟斤拷   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode      = SPI_Mode_Slave;		//锟斤拷锟斤拷选锟斤拷   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;			//时锟斤拷锟斤拷位   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;		//锟斤拷锟捷憋拷锟斤拷   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Speed     = SPI_Speed_4;			//SPI锟劫讹拷    SPI_Speed_4, SPI_Speed_8, SPI_Speed_16, SPI_Speed_2/SPI_Speed_32
	SPI_Init(&SPI_InitStructure);
	NVIC_SPI_Init(ENABLE,Priority_3);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3

//	SPI_InitStructure.SPI_Enable    = ENABLE;				//SPI锟斤拷锟斤拷    ENABLE, DISABLE
//	SPI_InitStructure.SPI_SSIG      = DISABLE;				//片选位     ENABLE, DISABLE
//	SPI_InitStructure.SPI_FirstBit  = SPI_MSB;				//锟斤拷位锟斤拷锟斤拷   SPI_MSB, SPI_LSB
//	SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;		//锟斤拷锟斤拷选锟斤拷   SPI_Mode_Master, SPI_Mode_Slave
//	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;			//时锟斤拷锟斤拷位   SPI_CPOL_High,   SPI_CPOL_Low
//	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;		//锟斤拷锟捷憋拷锟斤拷   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
//	SPI_InitStructure.SPI_Speed     = SPI_Speed_4;			//SPI锟劫讹拷    SPI_Speed_4, SPI_Speed_8, SPI_Speed_16, SPI_Speed_2/SPI_Speed_32
//	SPI_Init(&SPI_InitStructure);
//	NVIC_SPI_Init(ENABLE,Priority_3);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3
}

//========================================================================
//                             锟饺斤拷锟斤拷锟斤拷始锟斤拷
//========================================================================
void	CMP_config(void)
{
	CMP_InitDefine CMP_InitStructure;				//锟结构锟斤拷锟斤拷
	CMP_InitStructure.CMP_EN = ENABLE;				//锟斤拷锟斤拷锟饺斤拷锟斤拷		ENABLE,DISABLE
	CMP_InitStructure.CMP_P_Select     = CMP_P_P37;	//锟饺斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷选锟斤拷, CMP_P_P37,CMP_P_P50,CMP_P_P51,CMP_P_ADC.
	CMP_InitStructure.CMP_N_Select     = CMP_N_GAP;	//锟饺斤拷锟斤拷锟斤拷锟诫负锟斤拷选锟斤拷, CMP_N_GAP: 选锟斤拷锟节诧拷BandGap锟斤拷锟斤拷OP锟斤拷牡锟窖癸拷锟斤拷锟斤拷锟斤拷锟�, CMP_N_P36: 选锟斤拷P3.6锟斤拷锟斤拷锟斤拷锟斤拷.
	CMP_InitStructure.CMP_InvCMPO      = DISABLE;	//锟饺斤拷锟斤拷锟斤拷锟饺★拷锟�, 	ENABLE,DISABLE
	CMP_InitStructure.CMP_100nsFilter  = ENABLE;	//锟节诧拷0.1us锟剿诧拷,  	ENABLE,DISABLE
	CMP_InitStructure.CMP_Outpt_En     = ENABLE;	//锟斤拷锟斤拷锟饺较斤拷锟斤拷锟斤拷,ENABLE,DISABLE
	CMP_InitStructure.CMP_OutDelayDuty = 16;		//锟饺较斤拷锟斤拷浠�锟斤拷时锟斤拷锟斤拷锟斤拷, 0~63
	CMP_InitStructure.CMP_CHYS = CMP_CHYS_10mV;		//DC锟斤拷锟斤拷锟斤拷锟斤拷选锟斤拷,  CMP_CHYS_0mV,CMP_CHYS_10mV,CMP_CHYS_20mV,CMP_CHYS_30mV
	CMP_Inilize(&CMP_InitStructure);				//锟斤拷始锟斤拷锟饺斤拷锟斤拷
	NVIC_CMP_Init(RISING_EDGE|FALLING_EDGE,Priority_0);	//锟叫讹拷使锟斤拷, RISING_EDGE/FALLING_EDGE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3
}
//========================================================================
//                             锟解部锟叫断筹拷始锟斤拷
//========================================================================
void	Exti_config(void)
{
	EXTI_InitTypeDef	Exti_InitStructure;				//锟结构锟斤拷锟斤拷

	Exti_InitStructure.EXTI_Mode      = EXT_MODE_Fall;  //锟叫讹拷模式,   EXT_MODE_RiseFall,EXT_MODE_Fall
	Ext_Inilize(EXT_INT0,&Exti_InitStructure);			//锟斤拷始锟斤拷
	NVIC_INT0_Init(ENABLE,Priority_0);	//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3

	Exti_InitStructure.EXTI_Mode      = EXT_MODE_Fall;  //锟叫讹拷模式,   EXT_MODE_RiseFall,EXT_MODE_Fall
	Ext_Inilize(EXT_INT1,&Exti_InitStructure);			//锟斤拷始锟斤拷
	NVIC_INT1_Init(ENABLE,Priority_0);	//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟饺硷拷(锟酵碉拷锟斤拷) Priority_0,Priority_1,Priority_2,Priority_3

	NVIC_INT2_Init(ENABLE,NULL);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟斤拷锟饺硷拷
	NVIC_INT3_Init(ENABLE,NULL);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟斤拷锟饺硷拷
	NVIC_INT4_Init(ENABLE,NULL);		//锟叫讹拷使锟斤拷, ENABLE/DISABLE; 锟斤拷锟斤拷锟饺硷拷
}

//========================================================================
//                             锟解部锟叫断筹拷始锟斤拷
//========================================================================

//========================================================================
//                               锟斤拷锟杰斤拷锟叫伙拷
//========================================================================
void	Switch_config(void)
{
	UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
	UART2_SW(UART2_SW_P46_P47);		//UART2_SW_P10_P11,UART2_SW_P46_P47
//	UART3_SW(UART3_SW_P00_P01);		//UART3_SW_P00_P01,UART3_SW_P50_P51
//	UART4_SW(UART4_SW_P02_P03);		//UART4_SW_P02_P03,UART4_SW_P52_P53
//	I2C_SW(I2C_P14_P15);			//I2C_P14_P15,I2C_P24_P25,I2C_P33_P32
//	COMP_SW(CMP_OUT_P34);			//CMP_OUT_P34,CMP_OUT_P41
	SPI_SW(SPI_P22_P23_P24_P25);	//SPI_P12_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P54_P40_P41_P43,SPI_P35_P34_P33_P32

	PWM1_SW(PWM1_SW_P60_P61);		//PWM1_SW_P10_P11,PWM1_SW_P20_P21,PWM1_SW_P60_P61
	PWM2_SW(PWM2_SW_P62_P63);		//PWM2_SW_P12_P13,PWM2_SW_P22_P23,PWM2_SW_P62_P63
	PWM3_SW(PWM3_SW_P64_P65);		//PWM3_SW_P14_P15,PWM3_SW_P24_P25,PWM3_SW_P64_P65
	PWM4_SW(PWM4_SW_P66_P67);		//PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33

	PWM5_SW(PWM5_SW_P00);			//PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74
	PWM6_SW(PWM6_SW_P01);			//PWM6_SW_P21,PWM6_SW_P54,PWM6_SW_P01,PWM6_SW_P75
	PWM7_SW(PWM7_SW_P02);			//PWM7_SW_P22,PWM7_SW_P33,PWM7_SW_P02,PWM7_SW_P76
	PWM8_SW(PWM8_SW_P03);			//PWM8_SW_P23,PWM8_SW_P34,PWM8_SW_P03,PWM8_SW_P77

//	PCA_SW(PCA_P12_P11_P10_P37);	//PCA_P12_P11_P10_P37,PCA_P34_P35_P36_P37,PCA_P24_P25_P26_P27
}

//========================================================================
//                                系统锟斤拷始锟斤拷
//========================================================================
void	SYS_Init(void)
{
	GPIO_config();
	Timer_config();
//	ADC_config();
//	UART_config();
//	Exti_config();
	I2C_config();
//	SPI_config();
//	CMP_config();
	Switch_config();
	EA = 1;
	
	APP_config();
}

