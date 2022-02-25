#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
		  	    													  
void SPI1_Init(void);
void SPI1_SetSpeed(u8 SpeedSet);
u8 SPI1_ReadWriteByte(u8 TxData);
		 
#endif

