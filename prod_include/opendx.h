#pragma once
#include <string>
#include <windows.h>
#include <unknwn.h>
#include <xf86drmMode.h>


struct OpenDX_ConfigOption {
    std::string name;
    std::string value;
};

/// @brief OpenDX configuration options from the opendx.conf file
static struct OpenDX_Config_t {
    /// @brief the preferred graphics card set by configuration
    OpenDX_ConfigOption preferred_card;
    /// @brief  Experimental: ensure that our fb is the "master" framebuffer (the fb that owns the display)
    OpenDX_ConfigOption experimental_force_master;
} OpenDX_Config;

/// @brief Extra initialization parameters for OpenDX applications
struct OpenDX_ApplicationConfig {
    const char* ApplicationId;
};

/// @brief Represents a graphics device
struct OpenDX_Device {
    int fd;
    std::string path;
    drmModeRes* resources;
};

class OpenDX {
    public:
        OpenDX(int argc, char* argv[],int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int) = nullptr, const OpenDX_ApplicationConfig* appConfig = nullptr);
        OpenDX(int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int) = nullptr, const OpenDX_ApplicationConfig* appConfig = nullptr);
        ~OpenDX();
        int getReturnCode();
        std::string getPreferredGraphics();
        OpenDX_Device getDevice(int index);
        GtkApplication* getApplication();
        const OpenDX_ApplicationConfig* appConfig;
        GdkPixbuf* createPixbuf(uint32_t* framebuffer, int width, int height, int pitch);

        static OpenDX* getInstance();
    private:
        int winMain_r = 0;
        GtkApplication* app = nullptr;
        void loadConfig();
        void setDefaultConfig();
        void initializeFds();
        void deinitializeFds();
        OpenDX_Device* devices;
        int device_count = 0;
};

static OpenDX* LPDX = nullptr;

/*
 * Context rendering
 */
typedef struct _GdkD3DContextClass       GdkD3DContextClass;
typedef struct _GdkD3DContext          GdkD3DContext;

struct ID3DCompatibleDevice:IUnknown {
    HRESULT Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const void/*RGNDATA*/* pDirtyRegion);
};

G_BEGIN_DECLS
#define GDK_TYPE_D3D_CONTEXT (gdk_d3d_context_get_type())
#define GDK_D3D_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GDK_TYPE_D3D_CONTEXT, GdkD3DContext))
#define GDK_IS_D3D_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GDK_TYPE_D3D_CONTEXT))

#define GDK_D3D_ERROR (gdk_d3d_error_quark())

GDK_AVAILABLE_IN_ALL
GQuark gdk_d3d_error_quark (void);
GDK_AVAILABLE_IN_ALL GType gdk_d3d_context_get_type(void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL void gdk_d3d_context_set_framebuffer(GdkD3DContext *self, uint32_t *buffer);
GDK_AVAILABLE_IN_ALL void gdk_d3d_context_set_device(GdkD3DContext *self, ID3DCompatibleDevice *device);
G_END_DECLS