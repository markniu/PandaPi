#ifndef __ASSIST_H
#define __ASSIST_H

#include "stm32f10x.h"
#include <stdlib.h>

#include "typedefs.h"

#define MAX(a, b)			(a > b) ? a : b
#define MIN(a, b)			(a < b) ? a : b

#define MEN_CHK(x)		MEM_CHK(x)
#define	MEM_CHK(x)		if(NULL == x)	MEM_FAIL()

#define	MEM_FAIL()		MemFail_Handle("Memory Overflow", __FILE__, __LINE__)

#define	EXIT()				while(1)

uint8_t *NumberToString(uint32_t num);
uint8_t String_Cmp(uint8_t *First, uint8_t *Second, uint32_t NumberCmp);
void String_Copy(uint8_t *Target, uint8_t *Source, uint32_t CopyNumber);
void Array_Fill(uint32_t *Array, uint32_t Fill_Number, uint32_t Number_To_Fill);
void StrCpy(uint8_t *Src, uint8_t *Dst);
uint8_t StrCmp(uint8_t *Dst, uint8_t *Src, uint32_t Num);
void StrCat(uint8_t *Dst, uint8_t *Src);	
uint8_t StrChr(uint8_t *Src, uint8_t ch, uint8_t *Num);
void GetMaxMin(int32_t Wave[], uint32_t Len, int32_t *Max, int32_t *Min);
uint32_t Log_2(uint32_t Num);
void MemFail_Handle(uint8_t *Msg, uint8_t *FileName, uint32_t Line);

FStat Buf_LinearFill32(void *Buf, uint32_t Len);

#endif	//__ASSIST_H
