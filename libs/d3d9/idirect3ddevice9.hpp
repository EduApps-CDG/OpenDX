#pragma once
#include <unknwn.h>
/**
 * Defines device types
 */
typedef enum D3DDEVTYPE {
  D3DDEVTYPE_HAL          = 1,
  D3DDEVTYPE_NULLREF      = 4,
  D3DDEVTYPE_REF          = 2,
  D3DDEVTYPE_SW           = 3,
  D3DDEVTYPE_FORCE_DWORD  = 0xffffffff
} D3DDEVTYPE, *LPD3DDEVTYPE;


struct IDirect3DDevice9:IUnknown {
    
};