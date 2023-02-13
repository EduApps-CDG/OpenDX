#pragma once

#include <windows.h>
#include <winerror.h>
#include <objbase.h>

class IUnknown {
  virtual HRESULT QueryInterface (REFIID riid, void **ppvObject) = 0;
  virtual ULONG AddRef () = 0;
  virtual ULONG Release () = 0;
};
