#pragma once
#include <windows.h>
#include "d3d9helper.hpp"
#include "d3d9types.hpp"
#include "idirect3ddevice9.hpp"

// struct IDirect3D9 : public IUnknown {
// 	IDirect3D9(UINT SDKVersion);

//     HRESULT QueryInterface(REFIID riid, void** ppvObj);
//     ULONG AddRef();
//     ULONG Release();

// 	HRESULT CreateDevice(
// 		UINT                  Adapter,
// 		D3DDEVTYPE            DeviceType,
// 		HWND                  hFocusWindow,
// 		DWORD                 BehaviorFlags,
// 		D3DPRESENT_PARAMETERS *pPresentationParameters,
// 		IDirect3DDevice9      **ppReturnedDeviceInterface
// 	);

// private:
// 	DWORD m_cRef;

//     // Define other methods required by IDirect3D9 interface
// };

typedef struct IDirect3D9 *LPDIRECT3D9, *PDIRECT3D9;
IDirect3D9* Direct3DCreate9(UINT SDKVersion);