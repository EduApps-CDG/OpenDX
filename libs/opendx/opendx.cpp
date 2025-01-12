#include <config.hpp>
#include "opendx.hpp"
#include "opendx_config.hpp"
#include <windows.h>
#include <gtk/gtk.h>
#include <winuser.h>
#include <iostream>
#include <string>
#include <drm/drm.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

/**
 * @brief Create a Window 
 * 
 * @return HWND 
 */
export HWND CreateWindowExA(
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
    #ifdef DEBUG
        std::cout << "libopendx.so: CreateWindowExA()" << std::endl;
    #endif

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

    // TODO: find a no-signal way
    // g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    return window;
}

/**
 * @brief Aka ZeroMemory (Thanks Wine project)
 * 
 * @param dest 
 * @param size 
 */
export VOID WINAPI RtlZeroMemory(LPVOID dest, SIZE_T size) {
    memset(dest, 0, size);
}

export BOOL ShowWindow(HWND window, int nCmdShow) {
    BOOL r = gtk_widget_get_visible(GTK_WIDGET(window));
    gtk_widget_show(GTK_WIDGET(window));
    return r;
}

export BOOL DestroyWindow(HWND window) {
    gtk_window_destroy(GTK_WINDOW(window));
    return true;
}

export BOOL GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax) {
    BOOL r = g_main_context_pending(NULL);


   //i know this is wrong, but i need to get the sample working
    if (r) {
        g_main_context_iteration(NULL, true);
    } else {
        lpMsg->message = WM_QUIT;
    }

    return r;
}

export BOOL PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
    BOOL r = g_list_model_get_n_items(gtk_window_get_toplevels ()) > 0;

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
export OpenDX::OpenDX(int argc, char* argv[], int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int)) {
    this->loadConfig();

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

export OpenDX::OpenDX(int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int)) {
    this->loadConfig();
    
    gtk_init();

    if (WinMain != nullptr) {
        winMain_r = (*WinMain)(nullptr,nullptr,"",0);
    }
}

export int OpenDX::getReturnCode() {
    return winMain_r;
}

/**
 * search for the preferred graphics and return the it's name
 */
export char* OpenDX::getPreferredGraphics() {
    DLOG("libopendx.so: OpenDX::getPreferredGraphics()");

    drmDevicePtr devices;
    int numDevices = drmGetDevices(&devices, 32);
    DLOG("  Found " << numDevices << " devices");

    char* preferred = nullptr;

    for (int i = 0; i < numDevices; i++) {
        char* node = devices[i].nodes[0];
        DLOG("  Checking device " << node);

        int fd = open(node, O_RDWR);
        drmModeRes* res = drmModeGetResources(fd);

        if (res == nullptr) {
            DLOG("  Failed to get resources from " << node << ". Not a DRM device.");
            continue;
        } else {
            preferred = node;
            break;
        }
    }

    return preferred;
}

/**
 * Load the configuration file from user's .config/opendx/opendx.conf
 */
export void OpenDX::loadConfig() {
    DLOG("libopendx.so: loadConfig()");
    OpenDX_Config = {};
    OpenDX_Config.preferred_card = {
        name: "preferred_card",
        value: OpenDX::getPreferredGraphics()
    };
    OpenDX_Config.experimental_force_master = {
        name: "experimental_force_master",
        value: "false"
    };
    
    //read ~/.config/opendx/opendx.conf
    char* home = getenv("HOME") ?: (char*) "~";
    char* config = "/.config/opendx/opendx.conf";
    std::string path = std::string(home) + std::string(config);

    ifstream file = ifstream(path);
    if (!file.is_open()) {
        DLOG("  Failed to open " << path << ". Using default values.");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        //ini standard (with comments)
        if (line[0] == ';' || line[0] == '#' || line[0] == '\n') {
            continue;
        }

        //parse the line
        size_t pos = line.find("=");
        if (pos == std::string::npos) { //Warning (do not continue)
            std::cout << "\033[1;33m" //YELLOW BOLD
                << "ODX WARNING: Invalid configuration line in " << path << ":" <<
                line << ". Ignoring subsequent lines.\033[0;0m" << std::endl;
            break;
        }

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        //is value "default" or a comment or empty?
        if (value == "default" || value == "" || value[0] == ';' || value[0] == '#') {
            continue;
        }

        //load the configuration
        char* val = (char*) value.c_str();
        if (key == "preferred_card") {
            val = loadConfig_preferred_card(val);
            OpenDX_Config.preferred_card = {
                name:key.c_str(), 
                value:val
            };
        }

        DLOG("  Config: " << key << " = " << val);
    }

    file.close();
}

char* loadConfig_preferred_card(char* value) {
    DLOG("libopendx.so: loadConfig_preferred_card()");

    int fd = open(value, O_RDWR, 0);
    if (fd < 0) {
        DLOG("  Failed to open " << value << ".");
        return OpenDX::getPreferredGraphics();
    }

    drmModeRes* res = drmModeGetResources(fd);
    if (res == nullptr) {
        DLOG("  Failed to get resources from " << value << ". Not a DRM device.");
        return OpenDX::getPreferredGraphics();
    }
    
    return value;
}

char* loadConfig_experimental_force_master(char* value) {
    DLOG("libopendx.so: loadConfig_experimental_force_master()");

    if (strcmp(value, "true") == 0 || strcmp(value, "1") == 0) {
        //check if we are in a tty
        if (isatty(fileno(stdout))) {
            DLOG("  Experimental: enforcing master framebuffer");
            return "true";
        } else {
            std::cout << "\033[1;33m" //YELLOW BOLD
                << "ODX WARNING: Experimental feature 'experimental_force_master' enabled. Please try to run this program under a tty.\033[0;0m" << std::endl;
                throw std::runtime_error("Experimental feature 'experimental_force_master' enabled without a tty.");
        }
    }

    return "false";
}