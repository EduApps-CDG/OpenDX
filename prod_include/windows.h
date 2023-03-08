/**
 * This file only provides types for
 * Compatibility propourses regarding
 * OpenDX. It's not intended to rewrite
 * the entire Windows API.
 *
 * Part of: libopendx.so
 */

#pragma once
//does it really goes here?
#include <unistd.h>
#include <sys/syscall.h>

#if defined(__GNUC__)
	#define __stdcall __attribute__((stdcall))
#endif

//windows types:
#define WCHAR wchar_t
#define TCHAR char
#define UINT unsigned int
#define ULONG unsigned long
#define UlONG_PTR unsigned long
#define LONG long
#define BOOL bool
#define BYTE unsigned char

#include <stdarg.h>
#include <windef.h>
#include <winnt.h>
#include <gtk/gtk.h>

#define LPCTSTR const char*
#define DWORD unsigned long
#define HWND void*
#define HMENU void*
#define HINSTANCE void*
#define LPVOID void*
