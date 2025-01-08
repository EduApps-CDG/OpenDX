#pragma once
#include <windows.h>

inline LONG InterlockedIncrement(LONG volatile *p)
{
    return __sync_add_and_fetch(p, 1);
}

#define ZeroMemory RtlZeroMemory
VOID WINAPI RtlZeroMemory(LPVOID dest, SIZE_T size);