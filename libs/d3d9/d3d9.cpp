#include <windows.h>
#include "d3d9helper.hpp"
#include "d3d9.hpp"
#include "d3dobject.hpp"
#include <iostream>
#include <winbase.h>
#include <drm/drm.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

//TODO: add ifdefs when implementing another gpu
#include <drm/i915_drm.h>

IDirect3D9::IDirect3D9(UINT SDKVersion) {
	#ifdef DEBUG
		std::cout << "libd3d9.so: IDirect3D9::IDirect3D9()" << std::endl;
	#endif

	//Create connection with DRM
	int fd = open("/dev/dri/card0", O_RDWR, 0); //DirectX automatically selects the first GPU

	if (fd < 0) {
		std::cerr << "\033[1;31m" //RED BOLD
			<< "ODX ERROR: Failed to open /dev/dri/card0. Please check if you have the proper permissions to access the device." << std::endl
			<< "Direct3DCreate9 fails and returns NULL.\033[0;0m" << std::endl
			<< std::endl;

		close(fd);
		return;
	}

	//check if the device is Hardware or Software (Does DirectX have this check?)
    drm_get_cap gpuType;
    int ioctlResult = ioctl(fd, DRM_IOCTL_GET_CAP, &gpuType);

	//get device vendor id:
	drmVersion* version = drmGetVersion(fd);

    if (ioctlResult != 0) {
        std::cerr << "\033[1;31m"
			<< "ODX ERROR: Failed to get device info" << std::endl
			<< "Direct3DCreate9 fails and returns NULL.\033[0;0m" << std::endl
			<< std::endl;

        close(fd);
		perror("ioctl");
        return;
    }


	#ifdef DEBUG
		std::cout << "\033[1;32m" //GREEN BOLD
			<< "ODX INFO: Device \"" << version->name << '(' << version->desc << ' ' << version->version_minor << '.' << version->version_patchlevel << ')' << "\" is " << (gpuType.value == DRM_CAP_DUMB_BUFFER ? "Software" : "Hardware") << std::endl
			<< "\033[0;0m" << std::endl;
	#endif

	D3DDEVTYPE deviceType = D3DDEVTYPE::D3DDEVTYPE_NULLREF;

	if (gpuType.value == DRM_CAP_DUMB_BUFFER) {
		deviceType = D3DDEVTYPE::D3DDEVTYPE_SW;
	} else {
		deviceType = D3DDEVTYPE::D3DDEVTYPE_HAL;
	}

	IDirect3DDevice9* device;
	this->CreateDevice(
		D3DADAPTER_DEFAULT,
		deviceType,
		NULL, // TODO
		NULL, // TODO
		NULL, // TODO
		&device
	);

	close(fd);
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
	#ifdef DEBUG
		std::cout << "libd3d9.so: IDirect3D9::CreateDevice()" << std::endl;
	#endif

	//get GtkWindow specs and put them into D3DPRESENT_PARAMETERS
	pPresentationParameters->hDeviceWindow = hFocusWindow;
	pPresentationParameters->BackBufferWidth = gtk_widget_get_size(hFocusWindow,GTK_ORIENTATION_HORIZONTAL);
	pPresentationParameters->BackBufferHeight = gtk_widget_get_size(hFocusWindow,GTK_ORIENTATION_VERTICAL);

	//create the device
	IDirect3DDevice9 device = IDirect3DDevice9(/*this, pPresentationParameters*/);
	*ppReturnedDeviceInterface = &device;

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

IDirect3DDevice9::IDirect3DDevice9(/*IDirect3D9* d3d, D3DPRESENT_PARAMETERS* pp*/) {
	#ifdef DEBUG
		std::cout << "libd3d9.so: IDirect3DDevice9::IDirect3DDevice9()" << std::endl;
	#endif

	refCount = 1;
}

ULONG IDirect3DDevice9::AddRef() {
	DXGASSERT(((ULONG_PTR)(&refCount) & 3) == 0);

	InterlockedIncrement((LONG *)&refCount);
	return refCount;
}

ULONG IDirect3DDevice9::Release() {
	InterlockedDecrement((LONG *)&refCount);
	return refCount;
}

HRESULT IDirect3DDevice9::QueryInterface(REFIID riid, void** ppvObj) {
    *ppvObj = this;

	IDirect3DDevice9::AddRef();
	return 0;
}

HRESULT IDirect3DDevice9::Clear(DWORD Count, const void/*D3DRECT*/ *pRects, DWORD Flags, int/*D3DCOLOR*/ Color, float Z, DWORD Stencil) {
	#ifdef DEBUG
		std::cout << "libd3d9.so: IDirect3DDevice9::Clear()" << std::endl;
	#endif

	//intel code

	return 0;
}