/**
 * Windows API codes were commented to focus
 * on what's important: OpenDX.
 *
 * Code that doesn't work is also commented.
 */
#include <d3d9.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Create the window
    //HWND hWnd = CreateWindow("DX9 Window", "DX9 Window", 0, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);

    // Create the Direct3D device
    LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    LPDIRECT3DDEVICE9 pDevice = NULL;
    D3DPRESENT_PARAMETERS pp;
    /*ZeroMemory(&pp, sizeof(pp));
    pp.Windowed = TRUE;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &pDevice);

    // Enter the message loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // Render the scene
            pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
            pDevice->BeginScene();
            pDevice->EndScene();
            pDevice->Present(NULL, NULL, NULL, NULL);
        }
    }

    // Clean up
    pDevice->Release();
    pD3D->Release();
    DestroyWindow(hWnd);
    return msg.wParam;*/

    return 0;
}

//Linux's main
int main(int argc, char* argv[]) {
    char* cmdline = (char*) malloc(sizeof(char));
    cmdline[0] = '\0';

    for (int i = 0; i < argc; i++) {
        cmdline = (char*) realloc(cmdline, strlen(cmdline) + strlen(argv[i]) + 2);
        strcat(cmdline, argv[i]);
        if (i < argc - 1) {
            strcat(cmdline, " ");
        }
    }

    return WinMain(nullptr, nullptr, cmdline, 0);
}
