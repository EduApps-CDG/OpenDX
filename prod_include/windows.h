/**
 * This file only provides types for
 * Compatibility propourses regarding
 * OpenDX. It's not intended to rewrite
 * the entire Windows API and you should
 * not use MSVC if you want compatibility
 * with other platforms.
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
#define WINAPI __stdcall
#define __int64 long long

//windows types:
#define WCHAR wchar_t
#define TCHAR char
#define UINT unsigned int
#define ULONG unsigned long
#define ULONG_PTR unsigned long
#define LONG long
#define BOOL bool
#define BYTE unsigned char
#define LPSTR char*
#define LPCSTR const char*
#define LPCTSTR const char*
#define LPCWSTR const char*

#include <stdarg.h>
#include <windef.h>
#include <winnt.h>
#include <gtk/gtk.h>

#define DWORD unsigned long
#define HWND GtkWidget*
#define HMENU void*
#define HINSTANCE void*
#define LPVOID void*

#define LONG_PTR __int64
#define LPARAM LONG_PTR
#define WPARAM unsigned __int64

#include <basetsd.h>
#include <winbase.h>