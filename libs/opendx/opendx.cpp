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

    //if experimental_force_master is true, do not create the window and return nullptr
    if (OpenDX_Config.experimental_force_master.value == "true") {
        return nullptr;
    }

    GtkApplication* app = const_cast<GtkApplication*>(LPDX->getApplication());

    if (!app) {
        app = gtk_application_new(LPDX->appConfig->ApplicationId, G_APPLICATION_DEFAULT_FLAGS);
        g_application_register(G_APPLICATION(app), NULL, NULL);
        DLOG("  Application created with ID: " << LPDX->appConfig->ApplicationId);
    }

    GtkWidget* window = gtk_application_window_new(app);
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
        gtk_window_present(GTK_WINDOW(window));
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
    gtk_window_present(GTK_WINDOW(window));
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
export OpenDX::OpenDX(
    int argc, char* argv[],
    int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int),
    const OpenDX_ApplicationConfig* appConfig
) {
    this->loadConfig();
    this->initializeFds();

    if (appConfig != nullptr) {
        this->appConfig = appConfig;
    } else {
        this->appConfig = new OpenDX_ApplicationConfig {
            .ApplicationId = "org.opendx.default"
        };
    }

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

export OpenDX::OpenDX(
    int (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int),
    const OpenDX_ApplicationConfig* appConfig
) : OpenDX(0, {}, WinMain, appConfig) {
}

export const GtkApplication* OpenDX::getApplication() {
    return app;
}

export int OpenDX::getReturnCode() {
    return winMain_r;
}

/**
 * search for the preferred graphics and return the it's name,
 * The selected graphics is equivalent to D3DADAPTER_DEFAULT
 */
export std::string OpenDX::getPreferredGraphics() {
    DLOG("libopendx.so: OpenDX::getPreferredGraphics()");
    drmDevicePtr devices = nullptr;
    int numDevices = drmGetDevices(&devices, 32);
    DLOG("  Found " << numDevices << " devices");

    std::string found_path = "";

    for (int i = 0; i < numDevices; i++) {
        char* node = devices[i].nodes[0];
        DLOG("  Checking device " << node);

        int fd = open(node, O_RDWR);
        if (fd < 0) continue; // Não conseguiu abrir o dispositivo

        drmModeRes* res = drmModeGetResources(fd);

        if (res != nullptr) {
            drmModeFreeResources(res);
            close(fd);
            DLOG("  Found preferred device: " << node);
            found_path = node;
            break;
        } else {
            close(fd);
            DLOG("  Failed to get resources from " << node);
        }
    }

    return found_path;
}

void OpenDX::initializeFds() {
    DLOG("libopendx.so: OpenDX::initializeFds()");
    drmDevicePtr drmDevices = nullptr;
    int numDevices = drmGetDevices(&drmDevices, 32);
    OpenDX_Device* devices = new OpenDX_Device[numDevices];

    //init preferred card first
    std::string preferred = OpenDX_Config.preferred_card.value;
    DLOG("  Checking device " << preferred);
    int pfsd = open(preferred.c_str(), O_RDWR);
    drmModeRes* pres = drmModeGetResources(pfsd);

    devices[0] = {
        .fd = pfsd,
        .path = preferred,
        .resources = pres
    };

    bool found_preferred = false;
    int count = 1;
    for (int i = 1; i < numDevices; i++) {
        char* node = drmDevices[i].nodes[0];

        if (node == preferred) {
            found_preferred = true;
            continue; // Already initialized
        }

        DLOG("  Checking device " << node);

        int fd = open(node, O_RDWR);
        drmModeRes* res = drmModeGetResources(fd);

        if (fd < 0 || res == nullptr) {
            DLOG("  Failed to open or get resources from " << node);
            continue;
        }

        int index = found_preferred ? i : i + 1;
        devices[index] = {
            .fd = fd,
            .path = node,
            .resources = res
        };

        DLOG("  Initialized device " << node << " with fd " << fd);
        count++;
    }

    this->devices = devices;
    this->device_count = count;
}

OpenDX* OpenDX::getInstance() {
    return LPDX;
}

void OpenDX::deinitializeFds() {
    DLOG("libopendx.so: OpenDX::deinitializeFds()");
    if (this->devices != nullptr) {
        int x = 0;
        // Check if devices[x] itself is valid (not a nullptr or invalid struct)
        while (this->device_count > x) {
            std::string msg = "  Closed device " + this->devices[x].path + " with fd " + std::to_string(this->devices[x].fd);
            drmModeFreeResources(this->devices[x].resources);
            close(this->devices[x].fd);
            DLOG(msg);
            x++;
        }
        delete[] this->devices;
        this->devices = nullptr;
    }
}

OpenDX_Device OpenDX::getDevice(int index) {
    if (this->devices != nullptr) { // Seg fault here
        return this->devices[index];
    } else {
        return OpenDX_Device{-1, "", nullptr};
    }
}



OpenDX::~OpenDX() {
    this->deinitializeFds();
}

/**
 * Load the configuration file from user's .config/opendx/opendx.conf
 */
export void OpenDX::loadConfig() {
    DLOG("libopendx.so: loadConfig()");

    if (LPDX != nullptr) {
        std::cerr << "\033[1;31m" //RED BOLD
            << "ODX ERROR: OpenDX already initialized."
            << "\033[0;0m" << std::endl;
    }
    LPDX = this;

    OpenDX_Config = {};
    OpenDX_Config.preferred_card = {
        .name = "preferred_card",
        .value = OpenDX::getPreferredGraphics()
    };
    OpenDX_Config.experimental_force_master = {
        .name = "experimental_force_master",
        .value = "false"
    };
    
    //read ~/.config/opendx/opendx.conf
    char* home = getenv("HOME") ?: (char*) "~";
    char* config = "/.config/opendx/opendx.conf";
    std::string path = std::string(home) + std::string(config);

    ifstream file = ifstream(path);
    if (!file.is_open()) {
        DLOG("  Failed to open " << path << ". Using default values.");
        setDefaultConfig();
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
        std::string val = value;
        if (key == "preferred_card") {
            val = loadConfig_preferred_card(val);
            OpenDX_Config.preferred_card = {
                .name = key.c_str(),
                .value = val
            };
        }

        DLOG("  Config: " << key << " = " << val);
    }

    file.close();
}

void OpenDX::setDefaultConfig() {
    OpenDX_Config.experimental_force_master = {
        .name = "experimental_force_master",
        .value = "false"
    };

    #ifdef DEBUG
        //if tty, force master
        const char* term = std::getenv("TERM");
        if (term != nullptr && strcmp(term, "linux") == 0) {
            //YELLOW COLOR
            std::cout << "\033[1;33m" 
                << "ODX WARNING: You are running in a tty."
                << "Enabling experimental feature 'experimental_force_master'."
                << "\033[0;0m" << std::endl;

            OpenDX_Config.experimental_force_master.value = "true";
        }
    #endif
    
}

export GdkPixbuf* OpenDX::createPixbuf(uint32_t* framebuffer, int width, int height, int pitch) {
    int rowstride = pitch;
    int bits_per_sample = 8;
    int n_channels = 4; // ARGB
    GdkPixbuf* pixbuf = gdk_pixbuf_new_from_data(
        (const guchar*)framebuffer, GDK_COLORSPACE_RGB, TRUE, bits_per_sample,
        width, height, rowstride, NULL, NULL);
    if (!pixbuf) {
        g_printerr("Failed to create GdkPixbuf\n");
        return nullptr;
    }
    return pixbuf;
}

std::string loadConfig_preferred_card(std::string value) {
    DLOG("libopendx.so: loadConfig_preferred_card()");

    int fd = open(value.c_str(), O_RDWR, 0);
    if (fd < 0) {
        DLOG("  Failed to open " << value << ".");
        return LPDX->getPreferredGraphics();
    }

    drmModeRes* res = drmModeGetResources(fd);
    if (res == nullptr) {
        DLOG("  Failed to get resources from " << value << ". Not a DRM device.");
        return LPDX->getPreferredGraphics();
    }
    drmModeFreeResources(res);
    close(fd);
    
    return value;
}

std::string loadConfig_experimental_force_master(const char* value) {
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