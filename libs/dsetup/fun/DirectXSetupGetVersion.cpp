#include "DirectXSetupGetVersion.hpp"

/**
 * @brief Get DirectX version
 * 
 * @todo Implement this function
 * *    @see https://github.com/EduApps-CDG/OpenDX/wiki/dsetup.dll-or-libdsetup.so#int-directxsetupgetversiondword-dword
 * 
 * @param ver 
 * @param rev 
 * @return int 1 (always?)
 */
int DirectXSetupGetVersion(DWORD* ver, DWORD* rev) {
    *ver = 0;
    *rev = 0;
    return 1;
}