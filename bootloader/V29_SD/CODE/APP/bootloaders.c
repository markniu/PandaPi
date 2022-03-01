#include "bootloaders.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"

#if BOOTLOADER_FROM_SDCARD_EN
static FIL Fsrc;
static uint8_t ReadBuf[BOOTLOADER_BUF_SIZE];
#endif  //#if BOOTLOADER_FROM_SDCARD_EN

IAP_FUNCTION  jump2app;

void IAP_LoadApp(u32 appxAddr)
{
	
	////////////////
	GPIO_InitTypeDef  GPIO_InitStructure;
	// while (eTXIdle != TRUE);
    USART_Cmd(USART3, DISABLE);
    
    USART_ClearITPendingBit(USART3, USART_IT_TXE);
    USART_ClearITPendingBit(USART3, USART_IT_TC);
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);	

    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART3, USART_IT_TC, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,DISABLE);  
/////////////////////////
	
	SPI_Cmd(SPI1, DISABLE);
	SPI_I2S_DeInit(SPI1); 
	
	//////////////////
	
	///
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//////////////
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/////////

	//////////////
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/////////
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/////////
	
	//////////////////
	if(((*(vu32*)appxAddr)&0x2FFE0000)==0x20000000)
	{ 
		jump2app = (IAP_FUNCTION)*(vu32*)(appxAddr+4);
		MSR_MSP(*(vu32*)appxAddr);
		jump2app();
	}
}

#if BOOTLOADER_FROM_SDCARD_EN
FStat BootLoader_FromSDCard(void)
{
  FRESULT res;
  FStat stat;
  uint32_t cnt;
  uint32_t addr;
  
  printf("Boot Firmware checking ... \r\n");

  res = f_open( &Fsrc, BOOTLOADER_BIN_ADDR, FA_READ | FA_OPEN_EXISTING );
	if( FR_OK == res )
  {
    printf("Loading firmware ...\r\n");
    delay_ms(300);

    addr = BOOTLOADER_FLASH_ADDR;
    
  	res = f_read( &Fsrc, ReadBuf, BOOTLOADER_BUF_SIZE, &cnt );
  	if( FR_OK != res )
    { 
      printf("firmware read fail \r\n");
      return FuncErr;                                                                          
    }
    
  	BOOTLOADER_SECT_CHK( cnt );

  	while( 0 != cnt )
  	{
    	stat = Flash_Write( addr, ReadBuf, cnt );
    	FUNC_STAT_CHK( stat );
    
    	addr += cnt;
    
    	res = f_read( &Fsrc, ReadBuf, BOOTLOADER_BUF_SIZE, &cnt );
    	FAT_RES_CHK( res );
  	}

  	res = f_close( &Fsrc );
  	FAT_RES_CHK( res );

    if(FR_OK != f_rename("firmware.bin","old.bin"))
    {
      printf("Bad rename ...\r\n");
    }
    
    printf("Booting from new firmware 0x%x...\r\n",BOOTLOADER_FLASH_ADDR);	                                                             
  	IAP_LoadApp(BOOTLOADER_FLASH_ADDR);
      		
    while(1)
    {
      delay_ms(2000);
      printf("Boot fail...\r\n");
    }
	}
	else
  {
    printf("Booting from old firmware 0x%x.....\r\n",BOOTLOADER_FLASH_ADDR);
		IAP_LoadApp(BOOTLOADER_FLASH_ADDR);
	}

	return FuncOK;
}
#endif  //#if BOOTLOADER_FROM_SDCARD_EN

FStat BootLoader_Jump(uint32_t Sect, uint32_t Msp, uint32_t Reset)
{
  uint32_t base;
  uint32_t offset;
  IAP_FUNCTION jump2app;
  base = (Sect > NVIC_VectTab_FLASH ) ? NVIC_VectTab_FLASH : NVIC_VectTab_RAM;
  offset = Sect - base;
    
  NVIC_SetVectorTable( base, offset );
    
  jump2app=(IAP_FUNCTION)*(uint32_t*)(Sect+4);
	__set_MSP(*(uint32_t*)Sect);
	jump2app();	
  return FuncErr;
}
