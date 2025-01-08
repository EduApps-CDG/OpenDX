#pragma once
#include <windows.h>

#define HRESULT LONG

//https://learn.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values
#define S_OK 0
#define E_NOTIMPL 0x80004001
#define E_NOINTERFACE 0x80004002
#define E_POINTER 0x80004003
#define E_ABORT 0x80004004
#define E_FAIL 0x80004005
#define E_UNEXPECTED 0x8000FFFF
#define E_ACCESSDENIED 0x80070005
#define E_HANDLE 0x80070006
#define E_OUTOFMEMORY 0x8007000E
#define E_INVALIDARG 0x80070057