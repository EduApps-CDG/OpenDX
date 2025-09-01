#include <iostream>
#include <windows.h>
#include "d3d9types.hpp"
#include "d3d9helper.hpp"
#include "d3d9.hpp"
#include "d3dobject.hpp"
#include <winbase.h>
#include <linux/kd.h>

export IDirect3D9Ex::IDirect3D9Ex(UINT SDKVersion):IDirect3D9(SDKVersion) {
}

export IDirect3D9* Direct3DCreate9(UINT SDKVersion) {
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

// IDirect3DDevice9::IDirect3DDevice9(/*IDirect3D9* d3d, D3DPRESENT_PARAMETERS* pp*/) {
// 	#ifdef DEBUG
// 		std::cout << "libd3d9.so: IDirect3DDevice9::IDirect3DDevice9()" << std::endl;
// 	#endif

// 	refCount = 1;
// }

// ULONG IDirect3DDevice9::AddRef() {
// 	DXGASSERT(((ULONG_PTR)(&refCount) & 3) == 0);

// 	InterlockedIncrement((LONG *)&refCount);
// 	return refCount;
// }

// ULONG IDirect3DDevice9::Release() {
// 	InterlockedDecrement((LONG *)&refCount);
// 	return refCount;
// }

// HRESULT IDirect3DDevice9::QueryInterface(REFIID riid, void** ppvObj) {
//     *ppvObj = this;

// 	IDirect3DDevice9::AddRef();
// 	return 0;
// }

// HRESULT IDirect3DDevice9::Clear(DWORD Count, const void/*D3DRECT*/ *pRects, DWORD Flags, int/*D3DCOLOR*/ Color, float Z, DWORD Stencil) {
// 	#ifdef DEBUG
// 		std::cout << "libd3d9.so: IDirect3DDevice9::Clear()" << std::endl;
// 	#endif

// 	//intel code

// 	return 0;
// }