/**
  ******************************************************************************
  * @file    LTDC_ColorKeying/main.h 
  * @author  MCD Application Team
  * @version V1.0.1unsigned int  SD_cardSize(void)
  * @date    11-November-2013
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/


/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
#include <stdio.h>
#include "wiringPi.h"

#ifdef __cplusplus
extern "C" {

#endif
#define     __IO    volatile 
#define u8 unsigned char//unsigned short
#define u16 unsigned short//unsigned short
#define u32 unsigned int //unsigned int
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;

typedef unsigned int uint32_t;
typedef signed int int32_t;

void test_api(void);
extern	 __IO  u16 Read_ADC_Raw[32][4] ;

int Serial_PC(const long usb_serial_baud,const long octo_serial_baud,void (*rx_process)(char) );

void USART1_IRQHandler(void);

void tmper_init_stm32(void(*termal_isr)(void));
/*
//u16 Get_Pin(unsigned char Pin);
void  GPIO_Set_INPUT(unsigned char Pin);
void  GPIO_Set_OUTPUT(unsigned char Pin);
void ANALOG_SELECT_GPIO(unsigned char Pin);
  //void WRITE_IO(unsigned char IO,unsigned char v);
 // bool READ_IO(unsigned char IO);
 */
void SPIn_Init(char SPI_num,unsigned char SCK_pin,unsigned char MISO_pin,unsigned char MOSI_pin,unsigned char CS_pin,char remap);
u8 SPIn_ReadWriteByte(u8 TxData);
u8 SD_RecvData(u8*buf,u16 len);
u8 SD_SendBlock(u8*buf,u8 cmd);

void SPIn_SetSpeed(u16 SPI_BaudRatePrescaler);
//char pinMode(int pin_number, unsigned char pin_status);
void step_motor_init(void(*step_isr)(void),int n);

///unsigned long millis(void);
///void millis_count_init(void);
void motor_next_isr(u16 time_n);
char Serial_send(char uart_index, const char* buf_data);
char Serial_send_char( char uart_index, char  buf_data);

void FLUSH_serial0(void);
void stm32_wdg_init(unsigned int time_out_ms);
void stm32_wdg_feed(void);
char Serial5_send(unsigned char buf_data);
unsigned int  SD_cardSize(void);
char SDcard_Init(void);
char SDcard_ReadBlock(uint32_t blockNumber, uint8_t* dst);




}



