#pragma once

#include <windows.h>
#include <winerror.h>
#include <objbase.h>

struct IUnknown {
  HRESULT (*QueryInterface) (REFIID riid, void **ppvObject);
  ULONG (*AddRef) ();
  ULONG (*Release) ();
};
