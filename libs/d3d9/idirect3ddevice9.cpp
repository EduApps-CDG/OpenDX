#include <config.hpp>
#include "idirect3ddevice9.hpp"
#include "cairo.h"
#include "gdk/gdk.h"
#include "gtk/gtk.h"
#include <drm/drm.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <opendx.h>
#include <functional>
#include <memory>
#include <fstream>
#include <cstdint>
#include <iostream>

export IDirect3DDevice9::IDirect3DDevice9() {
    // DLOG("libd3d9.so: IDirect3DDevice9::IDirect3DDevice9()");
    // OpenDX* odx = OpenDX::getInstance();
    // OpenDX_Device odxDevice = odx->getDevice(0);

    // int fd = odxDevice.fd;

    // uint32_t* fbid = new uint32_t;
    // uint32_t* pitch = new uint32_t;
    // uint64_t* size = new uint64_t;
    // //int ioctlResult = 
    // // drmModeAddFB(
    // //     Adapter,
    // //     pPresentationParameters->BackBufferWidth,
    // //     pPresentationParameters->BackBufferHeight,
    // //     24,
    // //     0,
    // //     pPresentationParameters->BackBufferWidth * 4,
    // //     pPresentationParameters->BackBufferFormat,
    // //     fbid
    // // );
    // // Also segfaults:

    // struct drm_mode_create_dumb creq;
    // creq.height = 480;
    // creq.width = 640;
    // creq.bpp = 32;

    // if (drmIoctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &creq) < 0) {
    //     std::cerr << "\033[1;31m" //RED BOLD
    //         << "[IDirect3DDevice9] ODX ERROR: Failed to create framebuffer:" << strerror(errno) << std::endl
    //         << "[IDirect3DDevice9] IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
    //         << std::endl;
        
    //     delete fbid;
    //     delete pitch;
    //     delete size;
    //     close(fd);
    //     return;
    // }

    // struct drm_mode_map_dumb mreq;
    // mreq.handle = creq.handle;
    // if (drmIoctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &mreq) < 0) {
    //     perror("DRM_IOCTL_MODE_MAP_DUMB failed");
    //     drmModeRmFB(fd, creq.handle); // Clean up
    //     close(fd);
    //     return;
    // }

    // // drmModeCreateDumbBuffer(
    // //     fd, //fd (14)
    // //     pPresentationParameters->BackBufferWidth, //width (640)
    // //     pPresentationParameters->BackBufferHeight, //height (480)
    // //     32, //bpp
    // //     0, //flags
    // //     fbid, //fbid ptr
    // //     pitch, //pitch ptr
    // //     size //size ptr
    // // );
    // // if (ioctlResult != 0) {
    // //     return device;
    // // }

    // DLOG("  Framebuffer created");

    // // drmModeFB* fb = drmModeGetFB(fd, creq.handle);

    // // if (fb == nullptr) {
    // //     std::cerr << "\033[1;31m" //RED BOLD
    // //         << "ODX ERROR: Failed to get framebuffer:" << strerror(errno) << std::endl
    // //         << "IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
    // //         << std::endl;
        
    // //     delete fbid;
    // //     delete pitch;
    // //     delete size;
    // //     close(fd);
    // //     return nullptr;
    // // }

    // // //test-only: draw a square
    // int width = 50;
    // int height = 50;

    // // // Draw a red square around the screen
    // uint32_t* framebuffer = static_cast<uint32_t*>(mmap(0, creq.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mreq.offset));
}

HRESULT IDirect3DDevice9::Present(
    const RECT* pSourceRect,
    const RECT* pDestRect,
    HWND hDestWindowOverride,
    const void/*RGNDATA*/* pDirtyRegion
) {
    // DLOG("libd3d9.so: IDirect3DDevice9::Present()");
    HWND hwnd = hDestWindowOverride ? hDestWindowOverride : this->hFocusWindow;
    if (hwnd == NULL) {
        return E_FAIL;
    }

    // gdk_d3d_context_set_framebuffer(GDK_D3D_CONTEXT(self), buffer);
    
    //check 
    return 0;
}