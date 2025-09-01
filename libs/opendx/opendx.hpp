#pragma once

#include <config.hpp>
#include <string>
#include <windows.h>
#include <xf86drmMode.h>
#include "opendx_config.hpp"

struct OpenDX_ApplicationConfig {
    const char* ApplicationId;
};

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

std::string loadConfig_preferred_card(std::string value);