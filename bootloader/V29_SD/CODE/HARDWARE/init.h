/*
*	文件名:	    init.h
*	参考:		互联网资料
*	版本		V1.00
*	时间:		2014-5-29
*/

#ifndef __INIT_H__
#define __INIT_H__

#include "stm32f10x.h"
#include "delay.h"
#include "typedefs.h"

#define LED_FLOW_EN                                 ( 1 )


#define ON  0
#define OFF 1
															 
/*#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOF,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOF,GPIO_Pin_6)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define LED3(a) if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_5);*/

/*								   	*
*		以下为init.c的函数声明	  	*
*									*/	
																	
void SPI2_Configuration(void);		                                                        //配置LED的GPIO,包括选用端口,输出模式,时钟
void SPI2GPIO_Configuration(void);
void USART3_Configuration(void);
void SysTick_Configuration(void);
void RCC_Configuration(void);
//void LED_AllOFF(void);				                                                        //关闭三个LED灯
//void LED_AllON(void);			                                                            //打开三个LED
void delay(__IO uint32_t Count);	                                                        //延时函数
//void LED_Display(void);				                                                        //LED流水灯
//void GPIO_TurnOverBit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
//void LED_StatShow(FStat Stat);
                    
                    
                    
#endif		  //init.h文件


/****************************文件结束*****************************/
