#pragma once
#include <windows.h>

/*
 * ref: https://learn.microsoft.com/en-us/windows/win32/api/windef/ns-windef-point
 */
typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

//ref: https://learn.microsoft.com/en-us/windows/win32/api/windef/ns-windef-rect
typedef struct tagRECT {
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;