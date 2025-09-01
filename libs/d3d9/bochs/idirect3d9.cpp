#include <config.hpp>
#include "../idirect3d9.hpp"
#include "idirect3d9.hpp"
#include <drm/drm.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm/i915_drm.h>
#include <sys/mman.h>
#include <functional>
#include <memory>
#include <fstream>
#include <cstdint>

// void save_to_ppm(const char* filename, uint32_t* framebuffer, int width, int height, int pitch) {
//     std::ofstream outfile(filename, std::ios::binary); // Abre o arquivo em modo binário
//     if (!outfile.is_open()) {
//         std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
//         return;
//     }

//     // Cabeçalho PPM
//     outfile << "P6\n"; // Tipo do PPM (dados RGB binários)
//     outfile << width << " " << height << "\n"; // Largura e altura
//     outfile << "255\n"; // Valor máximo da cor (8 bits por canal)

//     // Escreve os dados do framebuffer
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             uint32_t pixel = framebuffer[y * pitch / 4 + x];
//             unsigned char r = (pixel >> 16) & 0xFF;
//             unsigned char g = (pixel >> 8) & 0xFF;
//             unsigned char b = pixel & 0xFF;
//             outfile.write(reinterpret_cast<const char*>(&r), 1);
//             outfile.write(reinterpret_cast<const char*>(&g), 1);
//             outfile.write(reinterpret_cast<const char*>(&b), 1);
//         }
//     }

//     outfile.close();
//     std::cout << "Framebuffer salvo em " << filename << std::endl;
// }

export IDirect3DDevice9* IDirect3D9_bochs::createDevice(
    IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType, 
    HWND hFocusWindow, DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS *pPresentationParameters
) {
    //test-only:
    pPresentationParameters->BackBufferWidth = 640;
    pPresentationParameters->BackBufferHeight = 480;

    DLOG("IDirect3D9_bochs::createDevice(\n" <<
        "    fd:" << Adapter << ",\n" <<
        "    pPresentationParameters: {" << "\n" <<
        "        BackBufferWidth: " << pPresentationParameters->BackBufferWidth << ",\n" <<
        "        BackBufferHeight: " << pPresentationParameters->BackBufferHeight << ",\n" <<
        "    }" <<
        "\n)"
    );

    //create IDirect3DDevice9 device; and assign functions to it
    IDirect3DDevice9* device = new IDirect3DDevice9();
    // ZeroMemory(device, sizeof(device));
    device->QueryInterface = (HRESULT (*)(REFIID riid, void **ppvObject))
        createQueryInterface(device)->target<HRESULT(REFIID, void**)>();
    device->AddRef = (ULONG (*)()) createAddRef(device)->target<ULONG()>();
    device->Release = (ULONG (*)()) createRelease(device)->target<ULONG()>();

    DLOG("  Device created");

    //create a framebuffer to hFocusWindow
    uint32_t* fbid = new uint32_t;
    uint32_t* pitch = new uint32_t;
    uint64_t* size = new uint64_t;
    //int ioctlResult = 
    // drmModeAddFB(
    //     Adapter,
    //     pPresentationParameters->BackBufferWidth,
    //     pPresentationParameters->BackBufferHeight,
    //     24,
    //     0,
    //     pPresentationParameters->BackBufferWidth * 4,
    //     pPresentationParameters->BackBufferFormat,
    //     fbid
    // );
    // Also segfaults:

    struct drm_mode_create_dumb creq;
    creq.height = 480;
    creq.width = 640;
    creq.bpp = 32;

    if (drmIoctl(Adapter, DRM_IOCTL_MODE_CREATE_DUMB, &creq) < 0) {
        std::cerr << "\033[1;31m" //RED BOLD
            << "[IDirect3D9_bochs] ODX ERROR: Failed to create framebuffer:" << strerror(errno) << std::endl
            << "[IDirect3D9_bochs] IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
            << std::endl;
        
        delete fbid;
        delete pitch;
        delete size;
        close(Adapter);
        return nullptr;
    }

    struct drm_mode_map_dumb mreq;
    mreq.handle = creq.handle;
    if (drmIoctl(Adapter, DRM_IOCTL_MODE_MAP_DUMB, &mreq) < 0) {
        std::cerr << "\033[1;31m" //RED BOLD
            << "[IDirect3D9_bochs] ODX ERROR: DRM_IOCTL_MODE_MAP_DUMB failed:" << strerror(errno) << std::endl
            << "[IDirect3D9_bochs] IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
            << std::endl;
        drmModeRmFB(Adapter, creq.handle); // Clean up
        close(Adapter);
        return nullptr;
    }

    // drmModeCreateDumbBuffer(
    //     Adapter, //fd (14)
    //     pPresentationParameters->BackBufferWidth, //width (640)
    //     pPresentationParameters->BackBufferHeight, //height (480)
    //     32, //bpp
    //     0, //flags
    //     fbid, //fbid ptr
    //     pitch, //pitch ptr
    //     size //size ptr
    // );
    // if (ioctlResult != 0) {
    //     return device;
    // }

    DLOG("  Framebuffer created");

    // drmModeFB* fb = drmModeGetFB(Adapter, creq.handle);

    // if (fb == nullptr) {
    //     std::cerr << "\033[1;31m" //RED BOLD
    //         << "ODX ERROR: Failed to get framebuffer:" << strerror(errno) << std::endl
    //         << "IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
    //         << std::endl;
        
    //     delete fbid;
    //     delete pitch;
    //     delete size;
    //     close(Adapter);
    //     return nullptr;
    // }

    // //test-only: draw a square
    int width = 50;
    int height = 50;

    // // Draw a red square around the screen
    uint32_t* framebuffer = static_cast<uint32_t*>(mmap(0, creq.size, PROT_READ | PROT_WRITE, MAP_SHARED, Adapter, mreq.offset)); 
    if (framebuffer == MAP_FAILED) {
        perror("mmap failed");
        //destroy fb
        drmModeRmFB(Adapter, creq.handle);
        close(Adapter);
        return nullptr;
    }
    int borderWidth = 5;

    for (int y = 0; y < creq.height; y++) {
        for (int x = 0; x < creq.width; x++) {
            if (x < borderWidth || x >= creq.width - borderWidth ||
                y < borderWidth || y >= creq.height - borderWidth) {
                framebuffer[y * creq.pitch / 4 + x] = 0x00FF0000; // Red
            }
        }
    }

    uint32_t* conn = new uint32_t;

    // // Update CRTC
    int ioctlResult = drmModeSetCrtc(
        Adapter,
        0, // CRTC ID
        creq.handle, // framebuffer
        0, // x
        0, // y
        conn, // connectors
        0, // count
        0
    );

    // if (ioctlResult != 0) {
    //     std::cerr << "\033[1;31m" //RED BOLD
    //         << "ODX ERROR: Failed to set CRTC" << std::endl
    //         << "IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
    //         << std::endl;
    //     return device;
    // } else {
    //     DLOG("  CRTC set");
    // }

    //test: save framebuffer to a file (so we can actually see it)
    // save_to_ppm("framebuffer.ppm", framebuffer, creq.width, creq.height, creq.pitch);
    munmap(framebuffer, creq.pitch * creq.height);

    // drmSetMaster(Adapter);

    return device;
}

extern "C" __attribute__((visibility("default"))) IDirect3DDevice9* odx_create_bochs_device(
    IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType,
    HWND hFocusWindow, DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS* pPresentationParameters
) {
    return IDirect3D9_bochs::createDevice(d3d9, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters);
}


std::shared_ptr<std::function<HRESULT(REFIID, void**)>> IDirect3D9_bochs::createQueryInterface(IDirect3DDevice9* device) {
    std::shared_ptr<std::function<HRESULT(REFIID, void**)>> fun = std::make_shared<std::function<HRESULT(REFIID, void**)>>([device](REFIID riid, void ** ppvObj) -> HRESULT {
        if (!ppvObj) return E_POINTER;
        return E_NOINTERFACE;
    });

    return fun;
}

std::shared_ptr<std::function<ULONG()>> IDirect3D9_bochs::createAddRef(IDirect3DDevice9* device) {
    std::shared_ptr<std::function<ULONG()>> fun = std::make_shared<std::function<ULONG()>>([device]() -> ULONG {
        return 0;
    });

    return fun;
}

std::shared_ptr<std::function<ULONG()>> IDirect3D9_bochs::createRelease(IDirect3DDevice9* device) {
    std::shared_ptr<std::function<ULONG()>> fun = std::make_shared<std::function<ULONG()>>([device]() -> ULONG {
        return 0;
    });

    return fun;
}