#include "delay.h"

static u8  us_unit=0;
static u16 ms_unit=0;

void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	us_unit=SystemCoreClock/8000000;	
	ms_unit=(u16)us_unit*1000;
}								    
	    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*us_unit;
	SysTick->VAL=0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}

void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*ms_unit;
	SysTick->VAL =0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}
