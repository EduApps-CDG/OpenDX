#pragma once
#include <windows.h>

/**
 * @brief OpenDX utility class
 */
class OpenDX {
    public:
        OpenDX(int argc, char* argv[],int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int) = nullptr);
        OpenDX(int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int) = nullptr);
        int getReturnCode();
    
    private:
        int winMain_r = 0;
};