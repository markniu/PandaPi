#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "flash.h"
#include "fat.h"
#include "bootloaders.h"

int main(void)
{	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  delay_init();
  UART_init(115200);

  delay_ms(5000);
  printf("Going to boot ... \r\n");
  /*
  SD_DetectInit();

  if(!SD_IsCardInserted()) 
  {
    printf("Booting from old firmware ... \r\n");
    IAP_LoadApp(BOOTLOADER_FLASH_ADDR);
    while(1) 
    {
      delay_ms(2000);
      printf("Boot fail...\r\n");
    }
  }
  else
  {
    printf("Going to load new firmware ... \r\n");
  }    
*/
  Flash_Init();                   
  if(FuncOK != FAT_Init())
  {
    printf("FAT init fail , booting from old firmware ... \r\n");
		IAP_LoadApp(BOOTLOADER_FLASH_ADDR);
  }

  //printf("FAT_Test \r\n");
  //FAT_Test();		

  //Boot load from sdcard
  BootLoader_FromSDCard();                     
}


