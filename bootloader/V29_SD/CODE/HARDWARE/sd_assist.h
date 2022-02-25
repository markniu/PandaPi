#ifndef __SD_ASSIST_H
#define __SD_ASSIST_H

#define OEM_UNICODE		"0:/TrasCode/OEM_Uni.bin"
#define	UNICODE_OEM		"0:/TrasCode/Uni_OEM.bin"

#include "stm32f10x.h"
#include "sdcard.h"
#include "ff.h"
#include "stdlib.h"
#include "util.h"

#define FAT_STATUS_CHK(res)				if(res != FR_OK) FILE_FAIL()
#define FAT_STATUS_CHK_RET(res, val)	if(res != FR_OK) FILE_FAIL_RET(val)

#define	FILE_FAIL()						FileFail_Handle("file operate fail!", __FILE__, __LINE__)
#define FILE_FAIL_RET(x)			FileFail_HandleRet("file operate fail!", __FILE__, __LINE__, x)

SD_Error SD_Card_Init(void);
uint8_t Check_FileStatus(FRESULT Status);

void Fat_ReadDir(uint8_t *Dir);
void File_Write(uint8_t *File, const uint16_t *Content);

void FileFail_Handle(uint8_t *Msg, uint8_t *FileName, uint32_t Line);
uint8_t FileFail_HandleRet(uint8_t *Msg, uint8_t *FileName, uint32_t Line, uint8_t Val);

WCHAR ff_convert(WCHAR Src, UINT Dir);

#endif	//__SD_ASSIST_H
