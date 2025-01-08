#include <config.hpp>
#include "../idirect3d9.hpp"
#include "idirect3ddevice9.hpp"
#include <drm/drm.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm/i915_drm.h>
#include <sys/mman.h>
#include <functional>
#include <memory>

export IDirect3DDevice9 IDirect3D9_i915::createDevice(
    IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType, 
    HWND hFocusWindow, DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS *pPresentationParameters
) {
    //create IDirect3DDevice9 device; and assign functions to it
    IDirect3DDevice9 device = {}; 
    device.QueryInterface = (long (*)(REFIID riid, void **ppvObject)) createQueryInterface(&device);
    //create a framebuffer to hFocusWindow
    uint32_t fbid;
    drmModeAddFB(
        Adapter,
        pPresentationParameters->BackBufferWidth,
        pPresentationParameters->BackBufferHeight,
        24,
        32,
        pPresentationParameters->BackBufferWidth * 4,
        pPresentationParameters->BackBufferFormat,
        &fbid
    );
    drmModeFB* fb = drmModeGetFB(Adapter, fbid);

    //test-only: draw a square
    int width = pPresentationParameters->BackBufferWidth - 50;
    int height = pPresentationParameters->BackBufferHeight - 50;

    // Draw a red square around the screen
    uint32_t* framebuffer = static_cast<uint32_t*>(mmap(0, fb->pitch * fb->height, PROT_READ | PROT_WRITE, MAP_SHARED, Adapter, fb->handle));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i < 50 || i > width - 50 || j < 50 || j > height - 50) {
                framebuffer[i * fb->pitch / 4 + j] = 0x00FF0000;
            }
        }
    }
    munmap(framebuffer, fb->pitch * fb->height);

    // Update CRTC
    drmModeSetCrtc(
        Adapter,
        0, // CRTC ID
        fbid,
        0, // x
        0, // y
        NULL, // connectors
        0, // count
        0
    );

    //display the framebuffer in hFocusWindow as GtkWidget
    

    return device;
}


void* IDirect3D9_i915::createQueryInterface(IDirect3DDevice9* device) {
    std::shared_ptr<std::function<HRESULT(REFIID, void**)>> fun = std::make_shared<std::function<HRESULT(REFIID, void**)>>([device](REFIID riid, void ** ppvObj) -> HRESULT {
        if (!ppvObj) return E_POINTER;
        return E_NOINTERFACE;
    });

    return (void*) fun->target<HRESULT(REFIID, void**)>();
}