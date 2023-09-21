#include <windows.h>
#include <gtk/gtk.h>
#include <winuser.h>
#include <opendx.h>

/**
 * @brief Create a Window 
 * 
 * @return HWND 
 */
HWND CreateWindowExA(
    DWORD extStyle,
    LPCSTR className, //optional
    LPCSTR title, //optional
    DWORD style,
    int x, //ignored. It's the user responsability to set the window position. (GTK4)
    int y, //ignored. It's the user responsability to set the window position. (GTK4)
    int width,
    int height,
    HWND parent, //optional
    HMENU menu, //optional
    HINSTANCE instance, //optional (Windows ignores it)
    LPVOID param //optional
) {
    GtkWidget* window = gtk_window_new();

    if (title != nullptr) {
        gtk_window_set_title(GTK_WINDOW(window), title);
    }

    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    //style:
    // TODO: Complete the list
    if (!(style & WS_CAPTION)) {
        gtk_window_set_title(GTK_WINDOW(window), "");
    }
    if (!(style & WS_SYSMENU)) {
        gtk_window_set_deletable(GTK_WINDOW(window), false);
    }
    if (style & WS_VISIBLE) {
        gtk_widget_show(GTK_WIDGET(window));
    }

    return window;
}

BOOL ShowWindow(HWND window, int nCmdShow) {
    BOOL r = gtk_widget_get_visible(GTK_WIDGET(window));
    gtk_widget_show(GTK_WIDGET(window));
    return r;
}

BOOL DestroyWindow(HWND window) {
    gtk_window_destroy(GTK_WINDOW(window));
    return true;
}

BOOL GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax) {
    BOOL r = g_main_context_pending(NULL);


   //i know this is wrong, but i need to get the sample working
    if (r) {
        g_main_context_iteration(NULL, true);
    } else {
        lpMsg->message = WM_QUIT;
    }

    return r;
}

BOOL PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
    BOOL r = g_main_context_pending(NULL);
   
   //i know this is wrong, but i need to get the sample working
    if (r) {
        g_main_context_iteration(NULL, true);
    } else {
        lpMsg->message = WM_QUIT;
    }

    return r;
}

/*
 * OpenDX utility class
 */
OpenDX::OpenDX(int argc, char* argv[], int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int)) {
    //Converts argc and argv to WinMain params
    char* cmdline = (char*) malloc(sizeof(char));
    cmdline[0] = '\0';

    for (int i = 0; i < argc; i++) {
        cmdline = (char*) realloc(cmdline, strlen(cmdline) + strlen(argv[i]) + 2);
        strcat(cmdline, argv[i]);
        if (i < argc - 1) {
            strcat(cmdline, " ");
        }
    }

    gtk_init();
    if (WinMain != nullptr) {
        winMain_r = (*WinMain)(nullptr,nullptr,cmdline,0);
    }
}

OpenDX::OpenDX(int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int)) {
    gtk_init();

    if (WinMain != nullptr) {
        winMain_r = (*WinMain)(nullptr,nullptr,"",0);
    }
}

int OpenDX::getReturnCode() {
    return winMain_r;
}