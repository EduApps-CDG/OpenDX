#pragma once
#include "idirect3d9.hpp"
#include <functional>
#include <memory>

class IDirect3D9_Base : public IUnknown {
    public:static IDirect3DDevice9* createDevice(IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters);
    public:static std::shared_ptr<std::function<HRESULT(REFIID, void**)>> createQueryInterface(IDirect3DDevice9* device);
    public:static std::shared_ptr<std::function<ULONG()>> createAddRef(IDirect3DDevice9* device);
    public:static std::shared_ptr<std::function<ULONG()>> createRelease(IDirect3DDevice9* device);
};