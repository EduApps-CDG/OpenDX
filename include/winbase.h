#pragma once
#include <windows.h>

inline LONG InterlockedIncrement(LONG volatile *p)
{
    return __sync_add_and_fetch(p, 1);
}

inline LONG InterlockedDecrement(LONG volatile *p)
{
    return __sync_sub_and_fetch(p, 1);
}
