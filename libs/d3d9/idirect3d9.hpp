#pragma once
#include <unknwn.h>
#include "idirect3ddevice9.hpp"
#include "d3d9types.hpp"

struct IDirect3D9 : public IUnknown {
	IDirect3D9(UINT SDKVersion);

    HRESULT QueryInterface(REFIID riid, void** ppvObj);
    ULONG AddRef();
    ULONG Release();

	HRESULT CreateDevice(
		UINT                  Adapter,
		D3DDEVTYPE            DeviceType,
		HWND                  hFocusWindow,
		DWORD                 BehaviorFlags,
		D3DPRESENT_PARAMETERS *pPresentationParameters,
		IDirect3DDevice9      **ppReturnedDeviceInterface
	);

	private:DWORD m_cRef;
	private:IDirect3DDevice9* m_device;
	private:HWND m_hFocusWindow;
};

//redeclare IDirect3D9 as IDirect3D9Ex
struct IDirect3D9Ex : public IDirect3D9 {
    IDirect3D9Ex(UINT SDKVersion);
};