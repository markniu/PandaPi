#include "init.h"

void SPI2_Configuration(void)										 
{

	SPI_InitTypeDef  SPI_InitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;

	SPI2GPIO_Configuration();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);


    //SPI2 configuration  
	SPI_Cmd(SPI2, DISABLE);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    
	SPI_Init(SPI2, &SPI_InitStructure);
    SPI_Cmd(SPI2, ENABLE); 
}

void SPI2GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB, ENABLE);
//ADS7843_Penqing
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				      
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


//=============================== ADS7843_CS==SST080_CS============
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12;				  //ADS7843_CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//PB13-SCK,PB15-MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PB14-MISO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOE, GPIO_Pin_10);    //cs
	GPIO_SetBits(GPIOE, GPIO_Pin_12);    //cs

}

void USART3_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
		
	// D8 T3X
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // D9 R3X 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART3, &USART_ClockInitStructure);
    USART_Init(USART3, &USART_InitStructure);
    
    USART_Cmd(USART3, ENABLE);

}

void SysTick_Configuration(void)
{
/*
     SysTick_CounterCmd(SysTick_Counter_Disable);
	 SysTick_ITConfig (DISABLE);

     SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//SysTick_CLKSource_HCLK_Div8
	 SysTick_SetReload(7200);

	 SysTick_ITConfig (ENABLE); 
	 SysTick_CounterCmd(SysTick_Counter_Clear);
*/
	 SysTick_Config(SystemCoreClock / 1000);
}


void RCC_Configuration(void)
{   
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */

     ErrorStatus HSEStartUpStatus;
	//	SystemInit();
     RCC_DeInit();
	                                                    
     RCC_HSEConfig(RCC_HSE_ON);
     HSEStartUpStatus = RCC_WaitForHSEStartUp();

     if(HSEStartUpStatus == SUCCESS)
     {
        FLASH_PrefetchBufferCmd(ENABLE);
        FLASH_SetLatency(FLASH_Latency_2);
   
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK2Config(RCC_HCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);

//		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE);
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

//		while(RCC_GetSYSCLKSource() !=0x08);

	 }


	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|
							RCC_APB2Periph_GPIOB|
							RCC_APB2Periph_GPIOC|
							RCC_APB2Periph_GPIOD|
							RCC_APB2Periph_GPIOE|
							RCC_APB2Periph_AFIO
							, ENABLE);
							
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2|
							RCC_APB1Periph_CAN1,ENABLE);
}
