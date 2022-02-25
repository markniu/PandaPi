#ifndef __BOOTLOADERS_H
#define __BOOTLOADERS_H

#include "stm32f10x.h"

#include "typedefs.h"
#include "fat.h"
#include "flash.h"

typedef void (*IAP_FUNCTION)(void);
static uc16 StatusShow[2]={250,292};
static char *status[]=
{
	"The program file detection.",
	"To update.",
	"Updating program...",
	"Update success.",
	"Update failed.",
	"Please turn off the machine and unplug the SD card.",
};

#define BOOTLOADER_FROM_SDCARD_EN   ( 1 )

#define BOOTLOADER_BIN_ADDR         ( "0:/firmware.bin" )
#define BOOTLOADER_OLD_BIN_ADDR     ( "0:/old.bin" )
#define BOOTLOADER_FLASH_ADDR       ( 0x08008000 )
#define BOOTLOADER_BUF_SIZE         ( 512 )
#define BOOTLOADER_SECT_SIZE        ( 8 )

typedef  void (*IAP_FUNCTION)(void);

#define BOOTLOADER_SECT_CHK(cnt)    if( cnt < BOOTLOADER_SECT_SIZE )       \
                                        return FuncErr

FStat BootLoader_FromSDCard(void);
FStat BootLoader_Jump(uint32_t Sect, uint32_t Msp, uint32_t Reset);

extern void IAP_LoadApp(u32 appxaddr);

#endif  //#ifndef __BOOTLOADERS_H
