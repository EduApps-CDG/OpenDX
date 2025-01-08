#include <config.hpp>
#include <opendx.h>
#include "d3d9types.hpp"
#include "idirect3d9.hpp"
#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <drm/drm.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <dlfcn.h>
#include "i915/idirect3ddevice9.hpp"

export IDirect3D9::IDirect3D9(UINT SDKVersion) {
	#ifdef DEBUG
		std::cout << "libd3d9.so: IDirect3D9::IDirect3D9()" << std::endl;
	#endif

	//Create connection with DRM
    char* card = OpenDX_Config.preferred_card.value ?: OpenDX::getPreferredGraphics();

    DLOG("  Using card: " << card);

	int fd = open(card, O_RDWR, 0);

	if (fd < 0) {
		std::cerr << "\033[1;31m" //RED BOLD
			<< "ODX ERROR: Failed to open /dev/dri/card0. Please check if you have the proper permissions to access the device." << std::endl
			<< "IDirect3D9 fails and returns NULL.\033[0;0m" << std::endl
			<< std::endl;

		close(fd);
		return;
	}

	//check if the device is Hardware or Software (Does DirectX have this check?)
	drm_get_cap gpuType;
	int ioctlResult = ioctl(fd, DRM_IOCTL_GET_CAP, &gpuType);

	if (ioctlResult != 0) {
		std::cerr << "\033[1;31m"
			<< "ODX ERROR: Failed to get device info" << std::endl
			<< "IDirect3DC9 fails and returns NULL.\033[0;0m" << std::endl
			<< std::endl;

		close(fd);
		perror("ioctl");
		return;
	}


	#ifdef DEBUG
        //get device vendor id:
        drmVersion* version = drmGetVersion(fd);
		std::cout << "\033[1;32m" //GREEN BOLD
			<< "ODX INFO: Device \"" << version->name << " (" << version->desc << ' ' << version->version_minor << '.' << version->version_patchlevel << ')' << "\" is " << (gpuType.value == DRM_CAP_DUMB_BUFFER ? "Software" : "Hardware") << std::endl
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
		fd, // D3DADAPTER_DEFAULT
		deviceType,
		NULL, // TODO
		NULL, // TODO
		NULL, // TODO
		&device
	);

	close(fd);

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
    //is the device i915 (Intel)?
	drmVersion* version = drmGetVersion(Adapter);
    if (version == nullptr) {
        std::cerr << "\033[1;31m" //RED BOLD
            << "ODX ERROR: Failed to get device info" << std::endl
            << "IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
            << std::endl;
        return E_FAIL;
    }

    if (strcmp(version->name, "i915") == 0) {
        //load the libd3d915_i915.so
        dlopen("libd3d915_i915.so", RTLD_NOW);
		*ppReturnedDeviceInterface = new IDirect3DDevice9(IDirect3D9_i915::createDevice(
			this,
			Adapter,
			DeviceType,
			hFocusWindow,
			BehaviorFlags,
			pPresentationParameters
		));
    }
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