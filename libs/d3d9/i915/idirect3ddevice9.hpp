#pragma once
#include "../idirect3d9.hpp"
#include <functional>
#include <memory>

class IDirect3D9_i915 : public IUnknown {
    public:static IDirect3DDevice9 createDevice(IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters);
    public:static void* createQueryInterface(IDirect3DDevice9* device);
};