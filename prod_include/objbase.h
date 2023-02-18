#pragma once
#include <unistd.h>
#include <sys/syscall.h>

#define STDMETHODCALLTYPE syscall(SYS_gettid);
struct IID {
  unsigned long  Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char  Data4[8];
};
typedef const IID* REFIID;
