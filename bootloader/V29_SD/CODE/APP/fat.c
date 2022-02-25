#include "fat.h"
#include "usart.h"


FATFS FileSystem;

#if FAT_TEST_EN
FIL Fsrc;
static uint8_t ReadBuf[FAT_TXT_LEN];
#endif  // FAT_TEST_EN

/*
 *  FUNCTION    :   FAT_Test
 *  DESCRIPTION :   FAT file system test
 *  INPUT       :   NO
 *  OUTPUT      :   FStat   --- FuncOK
 */
#if FAT_TEST_EN
FStat FAT_Test(void)
{
    FRESULT res;
    uint32_t cnt;
 
#if FAT_FILE_CREATE_EN
    res = f_open( &Fsrc, FAT_TXT_ADDR, FA_WRITE | FA_CREATE_ALWAYS);
    FAT_RES_CHK( res );
    res = f_write( &Fsrc, FAT_TXT_CONTENT, FAT_TXT_LEN, &cnt );
    FAT_RES_CHK( res );
    res = f_close( &Fsrc );
    FAT_RES_CHK( res );
#endif  //#if FAT_FILE_CREATE_EN
    
    res = f_open( &Fsrc, FAT_TXT_ADDR, FA_READ );
    FAT_RES_CHK( res );
    res = f_read( &Fsrc, ReadBuf, FAT_TXT_LEN, &cnt );
    FAT_RES_CHK( res );
    res = f_close( &Fsrc );
    FAT_RES_CHK( res );

    if( 0 != strcmp( FAT_TXT_CONTENT, (void *)ReadBuf ) )
    {
        printf("fat fail\r\n");
        return FuncErr;
    }
    printf("fat good\r\n");
    return FuncOK;
}
#endif  //#if FAT_TEST_EN

/*
 *  FUNCTION    :   FAT_Init
 *  DESCRIPTION :   FAT file sysetm init , mount SD card
 *  INPUT       :   no
 *  OUTPUT      :   succeed:FuncOK fail:FuncErr
 */
FStat FAT_Init(void)
{
  DSTATUS stat;
  FRESULT res;

  printf("Initializing disk...\r\n");
  stat = disk_initialize(0);
  if( RES_OK != stat )
  {
	    printf("Initialize disk fail\r\n");
      return FuncErr;
  }
  
  res = f_mount( 0, &FileSystem );
  if( FR_OK != res )
  {
    printf("Mount sdcard fail\r\n");
    return FuncErr;
  }
  
  return FuncOK;
}
