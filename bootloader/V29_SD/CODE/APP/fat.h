#ifndef __FAT_H
#define __FAT_H
 
#include "stm32f10x.h"
#include <string.h>
#include "diskio.h"
#ifdef SD_SPI_INTERFACE
#include "Sdcard_spi.h"
#else
#include "sd_assist.h"
#endif
#include "ff.h"

#include "typedefs.h"


#define FAT_TEST_EN                 ( 1 )
#define FAT_FILE_CREATE_EN          ( 1 )

#define FAT_TXT_ADDR                ( "0:/hello.txt" )
#define FAT_TXT_CONTENT             ( "Hello World\n" )
#define FAT_TXT_LEN                 ( 13 )

#define FAT_RES_CHK(res)            if( FR_OK != res )     \
                                        return FuncErr

FStat FAT_Init(void);
FStat FAT_Test(void);

#endif  //#ifndef __FAT_H
