#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include "stm32f10x.h"

typedef enum    _FUNCTION_STATUS_
{
    FuncOK = 0,
    FuncErr,
    FuncBusy,
    FuncIdle,
    FuncTimeOut
}FStat;

#define FUNC_STAT_CHK(stat)         if( FuncOK != stat )        \
                                        return stat

#endif  //#ifndef __TYPEDEFS_H
