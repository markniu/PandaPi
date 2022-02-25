#include "sys.h"
#include "Sdcard_spi.h"			   
#include "spi.h"	
 
u8  SD_Type=0;

void SD_DetectInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

bool SD_IsCardInserted(void)
{
  if(0!=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)) 
  {
    return FALSE;
  }
  return TRUE;
}

u8 SD_SPI_ReadWriteByte(u8 data)
{
	return SPI1_ReadWriteByte(data);
}	  

void SD_SPI_SpeedLow(void)
{
 	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);	
}

void SD_SPI_SpeedHigh(void)
{
 	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);
}

void SD_SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_4);
GPIO_ResetBits(GPIOA,GPIO_Pin_4);
  SPI1_Init();
	SD_CS=1;
}

void SD_DisSelect(void)
{
	SD_CS=1;
 	SD_SPI_ReadWriteByte(0xff);
}

u8 SD_Select(void)
{
	SD_CS=0;
	if(SD_WaitReady()==0)return 0;
	SD_DisSelect();
	return 1;
}

u8 SD_WaitReady(void)
{
	u32 t=0;
	do
	{
		if(SD_SPI_ReadWriteByte(0XFF)==0XFF)return 0;//OK
		t++;		  	
	}while(t<0XFFFFFF);
	return 1;
}

u8 SD_GetResponse(u8 Response)
{
	u16 Count=0xFFFF;						  
	while ((SD_SPI_ReadWriteByte(0XFF)!=Response)&&Count)Count--;	  
	if (Count==0)return MSD_RESPONSE_FAILURE;   
	else return MSD_RESPONSE_NO_ERROR;
}

u8 SD_RecvData(u8*buf,u16 len)
{			  	  
	if(SD_GetResponse(0xFE))return 1;
    while(len--)
    {
        *buf=SPI1_ReadWriteByte(0xFF);
        buf++;
    }

    SD_SPI_ReadWriteByte(0xFF);
    SD_SPI_ReadWriteByte(0xFF);									  					    
    return 0;
}

u8 SD_SendBlock(u8*buf,u8 cmd)
{	
	u16 t;		  	  
	if(SD_WaitReady())return 1;
	SD_SPI_ReadWriteByte(cmd);
	if(cmd!=0XFD)
	{
		for(t=0;t<512;t++)SPI1_ReadWriteByte(buf[t]);
	    SD_SPI_ReadWriteByte(0xFF);
	    SD_SPI_ReadWriteByte(0xFF);
		t=SD_SPI_ReadWriteByte(0xFF);
		if((t&0x1F)!=0x05)return 2;
	}						 									  					    
    return 0;
}
														  
u8 SD_SendCmd(u8 cmd, u32 arg, u8 crc)
{
    u8 r1;	
	u8 Retry=0; 
	SD_DisSelect();
	if(SD_Select())return 0XFF;

    SD_SPI_ReadWriteByte(cmd | 0x40);
    SD_SPI_ReadWriteByte(arg >> 24);
    SD_SPI_ReadWriteByte(arg >> 16);
    SD_SPI_ReadWriteByte(arg >> 8);
    SD_SPI_ReadWriteByte(arg);	  
    SD_SPI_ReadWriteByte(crc); 
	if(cmd==CMD12)SD_SPI_ReadWriteByte(0xff);//Skip a stuff byte when stop reading

	Retry=0X1F;
	do
	{
		r1=SD_SPI_ReadWriteByte(0xFF);
	}while((r1&0X80) && Retry--);	 
	
    return r1;
}		    																			  
													   
u8 SD_GetCID(u8 *cid_data)
{
    u8 r1;	   

    r1=SD_SendCmd(CMD10,0,0x01);
    if(r1==0x00)
	{
		r1=SD_RecvData(cid_data,16);	 
    }
	SD_DisSelect();
	if(r1)return 1;
	else return 0;
}																				  
													   
u8 SD_GetCSD(u8 *csd_data)
{
    u8 r1;	 
    r1=SD_SendCmd(CMD9,0,0x01);
    if(r1==0)
	{
    	r1=SD_RecvData(csd_data, 16);
    }
	SD_DisSelect();
	if(r1)return 1;
	else return 0;
}  
													  
u32 SD_GetSectorCount(void)
{
    u8 csd[16];
    u32 Capacity;  
    u8 n;
	u16 csize;  					    

    if(SD_GetCSD(csd)!=0) return 0;	    
    if((csd[0]&0xC0)==0x40)
    {	
		csize = csd[9] + ((u16)csd[8] << 8) + 1;
		Capacity = (u32)csize << 10;		   
    }else//V1.XX
    {	
		n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
		csize = (csd[8] >> 6) + ((u16)csd[7] << 2) + ((u16)(csd[6] & 3) << 10) + 1;
		Capacity= (u32)csize << (n - 9); 
    }
    return Capacity;
}

u8 SD_Initialize(void)
{
    u8 r1;
    u16 retry;
    u8 buf[4];  
	u16 i;

	SD_SPI_Init();
 	SD_SPI_SpeedLow();
 	for(i=0;i<10;i++)SD_SPI_ReadWriteByte(0XFF);
	retry=20;
	do
	{
		r1=SD_SendCmd(CMD0,0,0x95);
	}while((r1!=0X01) && retry--);
 	SD_Type=0;
	if(r1==0X01)
	{
		if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0
		{
			for(i=0;i<4;i++)buf[i]=SD_SPI_ReadWriteByte(0XFF);	//Get trailing return value of R7 resp
			if(buf[2]==0X01&&buf[3]==0XAA)
			{
				retry=0XFFFE;
				do
				{
					SD_SendCmd(CMD55,0,0X01);
					r1=SD_SendCmd(CMD41,0x40000000,0X01);
				}while(r1&&retry--);
				if(retry&&SD_SendCmd(CMD58,0,0X01)==0)
				{
					for(i=0;i<4;i++)buf[i]=SD_SPI_ReadWriteByte(0XFF);
					if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;
					else SD_Type=SD_TYPE_V2;   
				}
			}
		}else//SD V1.x/ MMC	V3
		{
			SD_SendCmd(CMD55,0,0X01);
			r1=SD_SendCmd(CMD41,0,0X01);
			if(r1<=1)
			{		
				SD_Type=SD_TYPE_V1;
				retry=0XFFFE;
				do
				{
					SD_SendCmd(CMD55,0,0X01);
					r1=SD_SendCmd(CMD41,0,0X01);
				}while(r1&&retry--);
			}else
			{
				SD_Type=SD_TYPE_MMC;
				retry=0XFFFE;
				do
				{											    
					r1=SD_SendCmd(CMD1,0,0X01);
				}while(r1&&retry--);  
			}
			if(retry==0||SD_SendCmd(CMD16,512,0X01)!=0)SD_Type=SD_TYPE_ERR;
		}
	}
	SD_DisSelect();
	SD_SPI_SpeedHigh();
	if(SD_Type)return 0;
	else if(r1)return r1; 	   
	return 0xaa;
}

u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt)
{
	u8 r1;
	if(SD_Type!=SD_TYPE_V2HC)sector <<= 9;
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD17,sector,0X01);
		if(r1==0)
		{
			r1=SD_RecvData(buf,512);
		}
	}
  else
	{
		r1=SD_SendCmd(CMD18,sector,0X01);
		do
		{
			r1=SD_RecvData(buf,512);
			buf+=512;  
		}while(--cnt && r1==0); 	
		SD_SendCmd(CMD12,0,0X01);
	}   
	SD_DisSelect();
	return r1;//
}

u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt)
{
	u8 r1;
	if(SD_Type!=SD_TYPE_V2HC)sector *= 512;
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD24,sector,0X01);
		if(r1==0)
		{
			r1=SD_SendBlock(buf,0xFE);   
		}
	}else
	{
		if(SD_Type!=SD_TYPE_MMC)
		{
			SD_SendCmd(CMD55,0,0X01);	
			SD_SendCmd(CMD23,cnt,0X01);
		}
 		r1=SD_SendCmd(CMD25,sector,0X01);
		if(r1==0)
		{
			do
			{
				r1=SD_SendBlock(buf,0xFC);
				buf+=512;  
			}while(--cnt && r1==0);
			r1=SD_SendBlock(0,0xFD);
		}
	}   
	SD_DisSelect();
	return r1;
}	





















