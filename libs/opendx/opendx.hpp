#pragma once

#include <config.hpp>
#include <windows.h>
#include "opendx_config.hpp"

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

char* loadConfig_preferred_card(char* value);