#pragma once
#include <windows.h>

/*
 * ref: https://learn.microsoft.com/en-us/windows/win32/api/windef/ns-windef-point
 */
typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;