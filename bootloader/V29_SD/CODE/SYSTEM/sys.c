#include "sys.h"

__asm void WFI_SET(void)
{
	WFI;
}

__asm void INTX_DISABLE(void)
{
	CPSID I;
}

__asm void INTX_ENABLE(void)
{
	CPSIE I;
}

__asm void MSR_MSP(u32 addr)
{
	MSR MSP, r0
	BX r14
}
