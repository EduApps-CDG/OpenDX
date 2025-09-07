#include <config.hpp>
#include <opendx.h>
#include "d3d9types.hpp"
#include "idirect3d9.hpp"
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <drm/drm.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <dlfcn.h>

export IDirect3D9::IDirect3D9(UINT SDKVersion) {
	#ifdef DEBUG
		std::cout << "libd3d9.so: IDirect3D9::IDirect3D9()" << std::endl;
	#endif

	//Create connection with DRM
	OpenDX* odx = OpenDX::getInstance();
	OpenDX_Device odxDevice = odx->getDevice(D3DADAPTER_DEFAULT);
	int fd = odxDevice.fd;

	if (fd < 0) {
		std::cerr << "\033[1;31m" //RED BOLD
			<< "ODX ERROR: Failed to open /dev/dri/card0. Please check if you have the proper permissions to access the device." << std::endl
			<< "IDirect3D9 fails and returns NULL.\033[0;0m" << std::endl
			<< std::endl;

		return;
	}

	//check if the device is Hardware or Software (Does DirectX have this check?)
	uint64_t gpuType;
	int ioctlResult = drmGetCap(fd,DRM_CAP_DUMB_BUFFER,&gpuType); //ioctl(fd, DRM_IOCTL_GET_CAP, &gpuType);

	if (ioctlResult != 0) {
		std::cerr << "\033[1;31m"
			<< "ODX ERROR: Failed to get device info" << std::endl
			<< "IDirect3D9 fails and returns NULL.\033[0;0m" << std::endl
			<< std::endl;

		perror("ioctl");
		return;
	}


	#ifdef DEBUG
        //get device vendor id:
        drmVersion* version = drmGetVersion(fd);
		std::cout << "\033[1;32m" //GREEN BOLD
			<< "ODX INFO: Device \"" << version->name << " (" << version->desc << ' ' << version->version_minor << '.' << version->version_patchlevel << ')' << "\" is " << (gpuType == DRM_CAP_DUMB_BUFFER ? "Software" : "Hardware") << std::endl
			<< "\033[0;0m" << std::endl;
	#endif

	D3DDEVTYPE deviceType = D3DDEVTYPE::D3DDEVTYPE_NULLREF;

	//WRONG:
	if (gpuType == DRM_CAP_DUMB_BUFFER) {
		deviceType = D3DDEVTYPE::D3DDEVTYPE_HAL;
	} else {
		deviceType = D3DDEVTYPE::D3DDEVTYPE_SW;
	}

	IDirect3DDevice9* device;
	D3DPRESENT_PARAMETERS pp = D3DPRESENT_PARAMETERS();

	// Causing creation of 2 buffers
	// this->CreateDevice(
	// 	D3DADAPTER_DEFAULT,
	// 	deviceType,
	// 	NULL, // TODO
	// 	0, // TODO
	// 	&pp, // TODO
	// 	&device
	// );

	// this->base = new IDirect3D9_Base(FALSE);
}

export HRESULT IDirect3D9::CreateDevice(
    UINT                  Adapter,
    D3DDEVTYPE            DeviceType,
    HWND                  hFocusWindow,
    DWORD                 BehaviorFlags,
    D3DPRESENT_PARAMETERS *pPresentationParameters,
    IDirect3DDevice9      **ppReturnedDeviceInterface
) {
	//complete presentation parameters
	if (hFocusWindow != NULL) {
		this->m_hFocusWindow = hFocusWindow;
		pPresentationParameters->hDeviceWindow = hFocusWindow;
		int width, height;
		gtk_window_get_default_size(GTK_WINDOW(hFocusWindow), &width, &height);
		pPresentationParameters->BackBufferWidth = width;
		pPresentationParameters->BackBufferHeight = height;
		DLOG("size { w: " << pPresentationParameters->BackBufferWidth << ", h: " << pPresentationParameters->BackBufferHeight << " }");
	}

	if (this->m_device != nullptr) {
		*ppReturnedDeviceInterface = this->m_device;
		return S_OK;
	}

	DLOG("IDirect3D9::CreateDevice(\n" <<
		"    Adapter: " << Adapter << ",\n" <<
		"    DeviceType: " << DeviceType << ",\n" <<
		"    hFocusWindow: " << hFocusWindow << ",\n" <<
		"    BehaviorFlags: " << BehaviorFlags << ",\n" <<
		"    pPresentationParameters: {" << "\n" <<
		"        BackBufferWidth: " << pPresentationParameters->BackBufferWidth << ",\n" <<
		"        BackBufferHeight: " << pPresentationParameters->BackBufferHeight << ",\n" <<
		"    }" <<
		"\n)"
	);

	OpenDX* odx = OpenDX::getInstance();
	OpenDX_Device odxDevice = odx->getDevice(Adapter);
	int fd = odxDevice.fd;

	drmVersion* version = drmGetVersion(fd);
    if (version == nullptr) {
        std::cerr << "\033[1;31m" //RED BOLD
            << "ODX ERROR: Failed to get device info" << std::endl
            << "IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
            << std::endl;
        return E_FAIL;
    }

	#ifdef DEBUG
		#define mode RTLD_LAZY
	#else
		#define mode RTLD_NOW
	#endif

	if (strcmp(version->name, "i915") == 0) { //Intel GPU
		void* handle = dlopen("libd3d9_i915.so", mode);
		if (!handle) {
			DLOG("  Failed to load libd3d9_i915.so");
			return E_FAIL;
		}
		using CreateFn = IDirect3DDevice9* (*)(IDirect3D9*, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*);
		CreateFn createDevice = reinterpret_cast<CreateFn>(dlsym(handle, "odx_create_i915_device"));
		if (!createDevice) {
			DLOG("  Failed to locate odx_create_i915_device in libd3d9_i915.so");
			return E_FAIL;
		}
		this->m_device = createDevice(this, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters);
		*ppReturnedDeviceInterface = this->m_device;
		return S_OK;
	} else if (strcmp(version->name, "vmwgfx") == 0) { //VMware virtual GPU
		void* handle = dlopen("libd3d9_vmwgfx.so", mode);
		if (!handle) {
			DLOG("  Failed to load libd3d9_vmwgfx.so");
			return E_FAIL;
		}
		using CreateFn = IDirect3DDevice9* (*)(IDirect3D9*, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*);
		CreateFn createDevice = reinterpret_cast<CreateFn>(dlsym(handle, "odx_create_vmwgfx_device"));
		if (!createDevice) {
			DLOG("  Failed to locate odx_create_vmwgfx_device in libd3d9_vmwgfx.so");
			return E_FAIL;
		}
		this->m_device = createDevice(this, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters);
		*ppReturnedDeviceInterface = this->m_device;
		return S_OK;
	} else if (strcmp(version->name, "bochs-drm") == 0) { //Bochs virtual GPU
		void* handle = dlopen("libd3d9_bochs.so", mode);
		if (!handle) {
			DLOG("  Failed to load libd3d9_bochs.so");
			return E_FAIL;
		}
		using CreateFn = IDirect3DDevice9* (*)(IDirect3D9*, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*);
		CreateFn createDevice = reinterpret_cast<CreateFn>(dlsym(handle, "odx_create_bochs_device"));
		if (!createDevice) {
			DLOG("  Failed to locate odx_create_bochs_device in libd3d9_bochs.so");
			return E_FAIL;
		}
		this->m_device = createDevice(this, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters);
		*ppReturnedDeviceInterface = this->m_device;
		return S_OK;
	}

	std::cerr << "\033[1;31m" //RED BOLD
		<< "ODX ERROR: Driver library for " << version->name << " not found." << std::endl
		<< "IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
		<< std::endl;

	return E_FAIL;
}

export HRESULT IDirect3D9::QueryInterface(REFIID riid, void ** ppvObj) {
    if (!ppvObj) return E_POINTER;
    
    return 0;
}

export ULONG IDirect3D9::AddRef() {
    DXGASSERT(((ULONG_PTR)(&m_cRef) & 3) == 0);

    InterlockedIncrement((LONG *)&m_cRef);
    return m_cRef;
}

export ULONG IDirect3D9::Release() {
    return 0;
}