/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "stm32f10x.h"
#ifdef SD_SPI_INTERFACE
#include "Sdcard_spi.h"
#else
#include "sd_assist.h"
#endif
#include "usart.h"

#ifdef SD_SPI_INTERFACE
  #define SD_CARD	 0
  #define EX_FLASH 1

  #define FLASH_SECTOR_SIZE 	512			  

  /*-----------------------------------------------------------------------*/
  /* Inidialize a Drive                                                    */

  DSTATUS disk_initialize (
  	BYTE drv				/* Physical drive nmuber (0..) */
  )
  {
    u8 res=0;	    
    printf("Initializing sdcard ...\r\n");
		res = SD_Initialize();
	 	if(res)
		{
			SD_SPI_SpeedLow();
			SD_SPI_ReadWriteByte(0xff);
			SD_SPI_SpeedHigh();
		}	 
  	if(res) return  STA_NOINIT;
  	else return RES_OK;
  }



  /*-----------------------------------------------------------------------*/
  /* Return Disk Status                                                    */

  DSTATUS disk_status (
  	BYTE drv		/* Physical drive nmuber (0..) */
  )
  {
  	return RES_OK;
  }



  /*-----------------------------------------------------------------------*/
  /* Read Sector(s)                                                        */

  DRESULT disk_read (
  	BYTE drv,		/* Physical drive nmuber (0..) */
  	BYTE *buff,		/* Data buffer to store read data */
  	DWORD sector,	/* Sector address (LBA) */
  	BYTE count		/* Number of sectors to read (1..255) */
  )
  {
  	u8 res=0; 

    if(drv != 0 || count == 0)
  	{
  		return RES_PARERR;
  	}
    
		res=SD_ReadDisk(buff,sector,count);	 
	 	if(res)
		{
			SD_SPI_SpeedLow();
			SD_SPI_ReadWriteByte(0xff);
			SD_SPI_SpeedHigh();
		}
    
    if(res==0x00) return RES_OK;	 
    else return RES_ERROR;	   
  }



  /*-----------------------------------------------------------------------*/
  /* Write Sector(s)                                                       */

  #if _READONLY == 0
    DRESULT disk_write (
    	BYTE drv,			/* Physical drive nmuber (0..) */
    	const BYTE *buff,	/* Data to be written */
    	DWORD sector,		/* Sector address (LBA) */
    	BYTE count			/* Number of sectors to write (1..255) */
    )
    {
      u8 res=0; 
      
    	if(drv != 0 || count == 0)
    	{
    		return RES_PARERR;
    	}				   
       	 
    	res=SD_WriteDisk((u8*)buff,sector,count);    			
      
      if(res == 0x00)return RES_OK;	 
      else return RES_ERROR;	    
    }
  #endif /* _READONLY */



  /*-----------------------------------------------------------------------*/
  /* Miscellaneous Functions                                               */

  DRESULT disk_ioctl (
  	BYTE drv,		/* Physical drive nmuber (0..) */
  	BYTE ctrl,		/* Control code */
  	void *buff		/* Buffer to send/receive control data */
  )
  {
    DRESULT res;
    
    if(drv!=0)	return RES_OK;    					  			     

    switch(ctrl)
    {
	    case CTRL_SYNC:
			    SD_CS=0;
	        if(SD_WaitReady()==0)res = RES_OK; 
	        else res = RES_ERROR;	  
			    SD_CS=1;
	        break;	 
	    case GET_SECTOR_SIZE:
	        *(WORD*)buff = 512;
	        res = RES_OK;
	        break;	 
	    case GET_BLOCK_SIZE:
	        *(WORD*)buff = 8;
	        res = RES_OK;
	        break;	 
	    case GET_SECTOR_COUNT:
	        *(DWORD*)buff = SD_GetSectorCount();
	        res = RES_OK;
	        break;
	    default:
	        res = RES_PARERR;
	        break;
    }
  	return res;
  }

#else // ! SD_SPI_INTERFACE

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define ATA		0
#define MMC		1
#define USB		2

#define SECTOR_SIZE 512//5120

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	if(drv == 0 && SD_Card_Init() == SD_OK)
	{
		return RES_OK;
	}
	else
	{
		return STA_NOINIT;
	}	
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	SD_Error SD_Status = SD_OK;
	
	if(drv != 0 || count == 0)
	{
		return RES_PARERR;
	}

	if(count == 1)
	{
		SD_Status = SD_ReadBlock(sector << 9, (uint32_t *)(&buff[0]), SECTOR_SIZE);
	}
	else
	{
		SD_Status = SD_ReadMultiBlocks(sector << 9, (uint32_t *)(&buff[0]), SECTOR_SIZE, count);
	}

	if(SD_Status == SD_OK)
	{
		return RES_OK;
	}
	else
	{
		return RES_ERROR;
	}
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	SD_Error SD_Status = SD_OK;
	
	if(drv != 0 || count == 0)
	{
		return RES_PARERR;
	}				   

	if(count == 1)
	{
		SD_Status = SD_WriteBlock(sector << 9, (uint32_t *)(buff), SECTOR_SIZE);
	}
	else
	{
		SD_Status = SD_WriteMultiBlocks(sector << 9, (uint32_t *)(buff), SECTOR_SIZE, count);
	}

	if(SD_Status == SD_OK)
	{
		return RES_OK;
	}
	else
	{
		return RES_ERROR;
	}
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return RES_OK;
}

#endif
