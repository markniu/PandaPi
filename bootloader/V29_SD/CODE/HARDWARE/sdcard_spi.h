#ifndef _MMC_SD_H_
#define _MMC_SD_H_		 
#include "sys.h"	 
//#include <stm32f10x.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  /* SDIO specific error defines */
  SD_CMD_CRC_FAIL                    = (1), /* Command response received (but CRC check failed) */
  SD_DATA_CRC_FAIL                   = (2), /* Data bock sent/received (CRC check Failed) */
  SD_CMD_RSP_TIMEOUT                 = (3), /* Command response timeout */
  SD_DATA_TIMEOUT                    = (4), /* Data time out */
  SD_TX_UNDERRUN                     = (5), /* Transmit FIFO under-run */
  SD_RX_OVERRUN                      = (6), /* Receive FIFO over-run */
  SD_START_BIT_ERR                   = (7), /* Start bit not detected on all data signals in widE bus mode */
  SD_CMD_OUT_OF_RANGE                = (8), /* CMD's argument was out of range.*/
  SD_ADDR_MISALIGNED                 = (9), /* Misaligned address */
  SD_BLOCK_LEN_ERR                   = (10), /* Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
  SD_ERASE_SEQ_ERR                   = (11), /* An error in the sequence of erase command occurs.*/
  SD_BAD_ERASE_PARAM                 = (12), /* An Invalid selection for erase groups */
  SD_WRITE_PROT_VIOLATION            = (13), /* Attempt to program a write protect block */
  SD_LOCK_UNLOCK_FAILED              = (14), /* Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
  SD_COM_CRC_FAILED                  = (15), /* CRC check of the previous command failed */
  SD_ILLEGAL_CMD                     = (16), /* Command is not legal for the card state */
  SD_CARD_ECC_FAILED                 = (17), /* Card internal ECC was applied but failed to correct the data */
  SD_CC_ERROR                        = (18), /* Internal card controller error */
  SD_GENERAL_UNKNOWN_ERROR           = (19), /* General or Unknown error */
  SD_STREAM_READ_UNDERRUN            = (20), /* The card could not sustain data transfer in stream read operation. */
  SD_STREAM_WRITE_OVERRUN            = (21), /* The card could not sustain data programming in stream mode */
  SD_CID_CSD_OVERWRITE               = (22), /* CID/CSD overwrite error */
  SD_WP_ERASE_SKIP                   = (23), /* only partial address space was erased */
  SD_CARD_ECC_DISABLED               = (24), /* Command has been executed without using internal ECC */
  SD_ERASE_RESET                     = (25), /* Erase sequence was cleared before executing because an out of erase sequence command was received */
  SD_AKE_SEQ_ERROR                   = (26), /* Error in sequence of authentication. */
  SD_INVALID_VOLTRANGE               = (27),
  SD_ADDR_OUT_OF_RANGE               = (28),
  SD_SWITCH_ERROR                    = (29),
  SD_SDIO_DISABLED                   = (30),
  SD_SDIO_FUNCTION_BUSY              = (31),
  SD_SDIO_FUNCTION_FAILED            = (32),
  SD_SDIO_UNKNOWN_FUNCTION           = (33),

  /* Standard error defines */
  SD_INTERNAL_ERROR, 
  SD_NOT_CONFIGURED,
  SD_REQUEST_PENDING, 
  SD_REQUEST_NOT_APPLICABLE, 
  SD_INVALID_PARAMETER,  
  SD_UNSUPPORTED_FEATURE,  
  SD_UNSUPPORTED_HW,  
  SD_ERROR,  
  SD_OK,  
} SD_Error;
 
#define SD_TYPE_ERR     0X00
#define SD_TYPE_MMC     0X01
#define SD_TYPE_V1      0X02
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06	   
	   
#define CMD0    0 
#define CMD1    1
#define CMD8    8 
#define CMD9    9
#define CMD10   10
#define CMD12   12
#define CMD16   16
#define CMD17   17
#define CMD18   18
#define CMD23   23
#define CMD24   24
#define CMD25   25
#define CMD41   41
#define CMD55   55
#define CMD58   58
#define CMD59   59

#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF

#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF
 							   						 	 
#define	SD_CS  PAout(4)					    	  

extern u8  SD_Type;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SD_DetectInit(void);
bool SD_IsCardInserted(void);
u8 SD_SPI_ReadWriteByte(u8 data);
void SD_SPI_SpeedLow(void);
void SD_SPI_SpeedHigh(void);
u8 SD_WaitReady(void);							
u8 SD_GetResponse(u8 Response);
u8 SD_Initialize(void);
u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt);
u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt);
u32 SD_GetSectorCount(void);
u8 SD_GetCID(u8 *cid_data);
u8 SD_GetCSD(u8 *csd_data);
 
#endif





