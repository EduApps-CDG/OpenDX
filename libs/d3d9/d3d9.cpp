#include <windows.h>
#include "d3d9helper.hpp"
#include "d3d9.hpp"
#include "d3dobj.hpp"
#include <iostream>
#include <winbase.h>

IDirect3D9::IDirect3D9 (UINT SDKVersion) {
	//TODO [Priority] complete this finction
}


ULONG IDirect3D9::AddRef() {
    DXGASSERT(((ULONG_PTR)(&m_cRef) & 3) == 0);

    InterlockedIncrement((LONG *)&m_cRef);
    return m_cRef;
}


HRESULT IDirect3D9::CreateDevice(
		UINT                  Adapter,
		D3DDEVTYPE            DeviceType,
		HWND                  hFocusWindow,
		DWORD                 BehaviorFlags,
		D3DPRESENT_PARAMETERS *pPresentationParameters,
		IDirect3DDevice9      **ppReturnedDeviceInterface
	) {
		return 0;
}

ULONG IDirect3D9::Release() {
	return 0;
}


HRESULT IDirect3D9::QueryInterface ( REFIID riid, void ** ppvObj ) {
	return 0;
}


IDirect3D9* Direct3DCreate9(UINT SDKVersion) {
	HINSTANCE instance = NULL;
	constexpr const UINT supported_sdk =  0x0900;

	if (SDKVersion != supported_sdk) {
		std::cout << "\033[1;31m" //RED BOLD
			<< std::endl
			<< "D3D ERROR: This application compiled against improper D3D headers." << std::endl
			<< "The application is compiled with SDK version (" << SDKVersion << ") but the currently installed" << std::endl
			<< "runtime supports versions from (" << supported_sdk << ")." << std::endl
			<< "Please recompile with an up-to-date SDK.\033[0;0m" << std::endl
			<< std::endl;
		return NULL;
	}

	IDirect3D9* r = new IDirect3D9(SDKVersion);

	if (r == NULL)
		std::cout << "\033[0;31m"
			<< "Creating D3D enumeration object failed; out of memory. Direct3DCreate fails and returns NULL.\033[0;0m" << std::endl;

	return r;
}
