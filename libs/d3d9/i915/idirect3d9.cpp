#include <config.hpp>
#include <opendx.h>
#include "../idirect3d9.hpp"
#include "gtk/gtk.h"
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

static void on_drawing_area_realize(GtkWidget *widget, gpointer user_data);
static void draw_function(GtkDrawingArea *area, cairo_t *cr, int a, int b, gpointer user_data);
struct present_data {
    IDirect3DDevice9* device;
    uint32_t* framebuffer;
};

export IDirect3DDevice9* IDirect3D9_i915::createDevice(
    IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType, 
    HWND hFocusWindow, DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS *pPresentationParameters
) {
    //test-only:
	OpenDX* odx = OpenDX::getInstance();
    OpenDX_Device odxDevice = odx->getDevice(Adapter);
    int fd = odxDevice.fd;

    DLOG("IDirect3D9_i915::createDevice(\n" <<
        "    fd:" << fd << "("<< odxDevice.path << "),\n" <<
        "    pPresentationParameters: {" << "\n" <<
        "        BackBufferWidth: " << pPresentationParameters->BackBufferWidth << ",\n" <<
        "        BackBufferHeight: " << pPresentationParameters->BackBufferHeight << ",\n" <<
        "    }" <<
        "\n)"
    );

    //create IDirect3DDevice9 device; and assign functions to it
    IDirect3DDevice9* device = new IDirect3DDevice9();
    device->hFocusWindow = hFocusWindow;
    // ZeroMemory(device, sizeof(device));
    device->QueryInterface = (HRESULT (*)(REFIID riid, void **ppvObject))
        createQueryInterface(device)->target<HRESULT(REFIID, void**)>();
    device->AddRef = (ULONG (*)()) createAddRef(device)->target<ULONG()>();
    device->Release = (ULONG (*)()) createRelease(device)->target<ULONG()>();

    DLOG("  Device created");

    
    //create a dumb buffer
    struct drm_mode_create_dumb create_req = {
        .height = pPresentationParameters->BackBufferHeight,
        .width = pPresentationParameters->BackBufferWidth,
        .bpp = 32,
        .flags = 0,
    };
    int ioctlResult = drmIoctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &create_req);
    if (ioctlResult < 0) {
        // Erro ao criar o dumb buffer
        DLOG("[IDirect3D9_i915] ODX ERROR: Failed to create dumb buffer");
    }

    //create a framebuffer to hFocusWindow
    uint32_t* fbid = new uint32_t;
    uint32_t* pitch = new uint32_t;
    uint64_t* size = new uint64_t;
    ioctlResult = drmModeAddFB(
        fd,
        pPresentationParameters->BackBufferWidth,
        pPresentationParameters->BackBufferHeight,
        24, 32,
        create_req.pitch,
        create_req.handle,
        fbid
    );
    // drmIoctl(Adapter, DRM_IOCTL_MODE_CREATE_DUMB, &creq) < 0

    if (ioctlResult < 0) {
        std::cerr << "\033[1;31m" //RED BOLD
            << "[IDirect3D9_i915] ODX ERROR: Failed to create framebuffer:" << strerror(errno) << std::endl
            << "[IDirect3D9_i915] IDirect3DC9::CreateDevice fails and returns NULL.\033[0;0m" << std::endl
            << std::endl;
        
        delete fbid;
        delete pitch;
        delete size;
        return nullptr;
    }

    struct drm_mode_map_dumb mreq;
    mreq.handle = create_req.handle;
    if (drmIoctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &mreq) < 0) {
        perror("DRM_IOCTL_MODE_MAP_DUMB failed");
        drmModeRmFB(fd, create_req.handle); // Clean up
        return nullptr;
    }

    // drmModeCreateDumbBuffer(
    //     fd, //fd (14)
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

    // drmModeFB* fb = drmModeGetFB(fd, creq.handle);

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
    uint32_t* framebuffer = static_cast<uint32_t*>(mmap(0, create_req.size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mreq.offset)); 
    device->framebuffer = framebuffer;
    
    if (framebuffer == MAP_FAILED) {
        perror("mmap failed");
        //destroy fb
        drmModeRmFB(fd, create_req.handle);
        return nullptr;
    }
    int borderWidth = 5;

    for (int y = 0; y < create_req.height; y++) {
        for (int x = 0; x < create_req.width; x++) {
            if (x < borderWidth || x >= create_req.width - borderWidth ||
                y < borderWidth || y >= create_req.height - borderWidth) {
                framebuffer[y * create_req.pitch / 4 + x] = 0x00FF0000; // Red
            }
        }
    }

    uint32_t* conn = new uint32_t;

    // // Update CRTC
    ioctlResult = drmModeSetCrtc(
        fd,
        0, // CRTC ID
        create_req.handle, // framebuffer
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
    // save_to_ppm("framebuffer.ppm", framebuffer, create_req.width, create_req.height, create_req.pitch);
    // munmap(framebuffer, create_req.pitch * create_req.height);

    // drmSetMaster(fd);

    //inject framebuffer into HWND (through GdkD3DContext)
    DLOG("  Injecting GdkD3DContext into HWND");
    GtkWidget *drawing_area = gtk_drawing_area_new();
    present_data pdata = {device, framebuffer};
    g_signal_connect(drawing_area, "realize", G_CALLBACK(on_drawing_area_realize), &pdata);
    gtk_window_set_child(GTK_WINDOW(hFocusWindow), drawing_area);

    gtk_widget_set_visible(drawing_area, TRUE);
    return device;
}

static void on_drawing_area_realize(GtkWidget *widget, gpointer user_data) {
    DLOG("libd3d9.so: on_drawing_area_realize(): Drawing area injected. Inserting framebuffer");
    present_data* pdata = static_cast<present_data*>(user_data);
    IDirect3DDevice9* device = pdata->device;
    uint32_t* framebuffer = pdata->framebuffer;

    GtkNative *native = gtk_widget_get_native(widget);
    GdkSurface *surface = gtk_native_get_surface(native);
    GdkDisplay *display = gdk_surface_get_display(surface);

    GdkD3DContext *context = (GdkD3DContext *) g_object_new(
        GDK_TYPE_D3D_CONTEXT,
        "surface",
        surface,
        "display", display,
        NULL
    );

    if (context == NULL) {
        g_critical("Failed to create GdkD3DContext!");
        return;
    }

    gdk_d3d_context_set_framebuffer(context, framebuffer);
    gdk_d3d_context_set_device(context, (ID3DCompatibleDevice*) device);
    gtk_drawing_area_set_draw_func(
        GTK_DRAWING_AREA(widget),
        draw_function,
        &framebuffer,
        NULL
    );
    // gdk_draw_context_begin_draw(GDK_DRAW_CONTEXT(context), nullptr);
    // gdk_draw_context_end_draw(GDK_DRAW_CONTEXT(context));
}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    
    DLOG("libopendx.so: gdk_d3d_context_draw(): Drawing framebuffer to widget");
    uint32_t* framebuffer = *(uint32_t**)user_data;
    if (framebuffer == nullptr) {
        DLOG("libopendx.so: gdk_d3d_context_draw(): No framebuffer set, skipping draw");
        return;
    }

    cairo_surface_t *cairo_surface =
        cairo_image_surface_create_for_data(
            (unsigned char*)framebuffer,
            CAIRO_FORMAT_ARGB32,
            width,
            height,
            width * 4 // pitch (bytes per row)
        );
    
    cairo_set_source_surface(cr, cairo_surface, 0, 0);
    cairo_paint(cr);
    cairo_surface_destroy(cairo_surface);
}

extern "C" __attribute__((visibility("default"))) IDirect3DDevice9* odx_create_i915_device(
    IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType,
    HWND hFocusWindow, DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS* pPresentationParameters
) {
    return IDirect3D9_i915::createDevice(d3d9, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters);
}


std::shared_ptr<std::function<HRESULT(REFIID, void**)>> IDirect3D9_i915::createQueryInterface(IDirect3DDevice9* device) {
    std::shared_ptr<std::function<HRESULT(REFIID, void**)>> fun = std::make_shared<std::function<HRESULT(REFIID, void**)>>([device](REFIID riid, void ** ppvObj) -> HRESULT {
        if (!ppvObj) return E_POINTER;
        return E_NOINTERFACE;
    });

    return fun;
}

std::shared_ptr<std::function<ULONG()>> IDirect3D9_i915::createAddRef(IDirect3DDevice9* device) {
    std::shared_ptr<std::function<ULONG()>> fun = std::make_shared<std::function<ULONG()>>([device]() -> ULONG {
        return 0;
    });

    return fun;
}

std::shared_ptr<std::function<ULONG()>> IDirect3D9_i915::createRelease(IDirect3DDevice9* device) {
    std::shared_ptr<std::function<ULONG()>> fun = std::make_shared<std::function<ULONG()>>([device]() -> ULONG {
        return 0;
    });

    return fun;
}