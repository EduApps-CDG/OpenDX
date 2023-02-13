#pragma once
//does it really goes here?
#include <unistd.h>
#include <sys/syscall.h>
#define __syscall syscall(SYS_gettid)

//windows types:
#define WCHAR wchar_t
#define ULONG unsigned long
#define LONG long;

#include <stdarg.h>
#include <windef.h>
#include <winnt.h>
