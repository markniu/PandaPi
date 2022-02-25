#include "sd_assist.h"

uint8_t FileFail_HandleRet(uint8_t *Msg, uint8_t *FileName, uint32_t Line, uint8_t Val)
{
	return Val;
}

void FileFail_Handle(uint8_t *Msg, uint8_t *FileName, uint32_t Line)
{
	EXIT();
}

WCHAR ff_wtoupper (	// Upper converted character 
	WCHAR chr		// Input character 
)
{
    return 0;
}

WCHAR ff_convert(WCHAR Src, UINT Dir)
{
    return 0;
}

void SDIO_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

SD_Error SD_Card_Init(void)
{
	SD_CardInfo SD_Info;
	SD_Error SD_Status;

	SDIO_NVIC_Config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	SD_Status = SD_Init();
	if(SD_Status == SD_OK)
	{
		SD_Status = SD_GetCardInfo(&SD_Info);
	}

	if(SD_Status == SD_OK)
	{
		SD_Status = SD_SelectDeselect((uint32_t) SD_Info.RCA << 16);
	}

	if(SD_Status == SD_OK)
	{
		SD_Status = SD_EnableWideBusOperation(SDIO_BusWide_1b);
	}

	if(SD_Status == SD_OK)
	{
		SD_Status = SD_SetDeviceMode(SD_DMA_MODE);
	}

	return SD_Status;
}

