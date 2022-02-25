#include "util.h"

FStat Buf_LinearFill32(void *Buf, uint32_t Len)
{
    uint32_t *buf;
    uint32_t i;
    
    if( NULL == Buf)
    {   
        return FuncErr;
    }
    
    buf = (uint32_t *)Buf;
    for( i=0; i<Len/4; i++ )
    {
        buf[i] = (uint32_t)i;
    }
    
    return FuncOK;
}

void MemFail_Handle(uint8_t *Msg, uint8_t *FileName, uint32_t Line)
{
	EXIT();
}


void StrCpy(uint8_t *Dst, uint8_t *Src)
{
	while(*Src != '\0')
	{
		*Dst++ = *Src++;
	}
	*Dst = '\0';
}
