#pragma once
#include <windows.h>


struct OpenDX_ConfigOption {
    const char* name;
    char* value;
};

/// @brief OpenDX configuration options from the opendx.conf file
struct OpenDX_Config {
    /// @brief the preferred graphics card set by configuration
    OpenDX_ConfigOption preferred_card;
    /// @brief  Experimental: ensure that our fb is the "master" framebuffer (the fb that owns the display)
    OpenDX_ConfigOption experimental_force_master;
} OpenDX_Config;

/**
 * @brief OpenDX utility class
 */
class OpenDX {
    public:
        OpenDX(int argc, char* argv[],int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int) = nullptr);
        OpenDX(int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int) = nullptr);
        int getReturnCode();
        static char* getPreferredGraphics();    
    private:
        int winMain_r = 0;
        void loadConfig();
};