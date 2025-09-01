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
  friend class IDirect3D9;
  friend class IDirect3D9_i915;
  friend class IDirect3D9_vmwgfx;
  friend class IDirect3D9_bochs;
  
  public:IDirect3DDevice9();
  public:HRESULT Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const void/*RGNDATA*/* pDirtyRegion);
  private:uint32_t* framebuffer;
};