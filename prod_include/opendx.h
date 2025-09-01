#pragma once
#include <string>
#include <windows.h>
#include <xf86drmMode.h>


struct OpenDX_ConfigOption {
    std::string name;
    std::string value;
};

/// @brief OpenDX configuration options from the opendx.conf file
struct OpenDX_Config {
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
        const GtkApplication* getApplication();
        const OpenDX_ApplicationConfig* appConfig;
        GdkPixbuf* createPixbuf(uint32_t* framebuffer, int width, int height, int pitch);

        static OpenDX* getInstance();
    private:
        int winMain_r = 0;
        const GtkApplication* app = nullptr;
        void loadConfig();
        void setDefaultConfig();
        void initializeFds();
        void deinitializeFds();
        OpenDX_Device* devices;
        int device_count = 0;
};

static OpenDX* LPDX = nullptr;