/**
 * Windows API codes were commented to focus
 * on what's important: OpenDX.
 *
 * Code that doesn't work is also commented and will be gradually
 * fixed. This is a work in progress.
 */

 //default values
#include "gio/gio.h"
#include "glib-object.h"
#include "gtk/gtk.h"
#define ODX_APP_NAME "DX9 Sample" //default app name
#define ODX_APP_CLASS "OpenDX.DX9Sample" //app identifier
#define ODX_ICON "/usr/share/icons/opendx.png" //relative, absolute or system path

#include <opendx.h>
#include <windows.h>
#include <winuser.h>
#include <d3d9.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

//GtkWidget* == HWND
static LPDIRECT3DDEVICE9 compatCode(HWND hWnd) {
    LPDIRECT3DDEVICE9 pDevice = NULL;
    D3DPRESENT_PARAMETERS pp;
    
    ZeroMemory(&pp, sizeof(pp));
    pp.Windowed = TRUE;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    
    LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    pD3D->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &pp, 
        &pDevice
    );

    // Enter the message loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // Clean up
    //pDevice->Release(); //causes a segfault
    //pD3D->Release();
    //return msg.wParam;
    return pDevice;
}

// Render the scene
static void drawCall(LPDIRECT3DDEVICE9 pDevice) {
    /*pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
    pDevice->BeginScene();
    pDevice->EndScene();*/
    pDevice->Present(NULL, NULL, NULL, NULL);
}

//is windows?
#ifdef _WIN32
/**
 * OpenDX can convert MSVC's WinMain, but
 * it's not recommended as it could cause every kind of issue.
 * You can still use it for testing purposes.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Create the Direct3D device
    
    // Create the window
    HWND hWnd = CreateWindow(
        "DX9 Window", "DX9 Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, 640, 480,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    compatCode(hWnd);


    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {
            //TranslateMessage(&msg);
            //DispatchMessage(&msg);
        } else {
            drawCall(pDevice);
        }
    }

    DestroyWindow(hWnd);

    return 0;
}
#endif // _WIN32


#ifdef __linux__
static void activate(GtkApplication* app, gpointer user_data);
//Linux's main or MinGW's main:
int main(int argc, char* argv[]) {
    //If you want to use WinMain (please dont)
    //you can pass it as a parameter:
    OpenDX odx = OpenDX(); //pass WinMain and appConfig if you would like to experimentally run a WinMain app

    GtkApplication* app = gtk_application_new(ODX_APP_CLASS, G_APPLICATION_DEFAULT_FLAGS);
    g_application_register(G_APPLICATION(app), NULL, NULL);
    GMainContext *context = g_main_context_default();
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int r = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);


    return r; //odx.getReturnCode(); // 0 if WinMain is not passed.
}

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), ODX_APP_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_window_set_default_icon_name("opendx");

    gtk_window_present(GTK_WINDOW(window));

    LPDIRECT3DDEVICE9 pDevice = compatCode(window);

    while (g_list_model_get_n_items (gtk_window_get_toplevels ()) > 0) {
        GMainContext *context = g_main_context_default();
        if (g_main_context_pending(context)) {
            g_main_context_iteration(context, true);
        }
        drawCall(pDevice);
    }
}
#endif //__linux__