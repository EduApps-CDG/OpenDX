#pragma once
#include <iostream>

#define export __attribute__((visibility("default")))

#define DEBUG true
#ifdef DEBUG
    #define DLOG(x) std::cout << x << std::endl;
#else
    #define DLOG(x) //x
#endif

//PREPROCESSING ONLY!!!
#define PROJECT_SOURCE_DIR "/home/eduardo/Documentos/proj/OpenDX/"
#define CONFIG_FILE "opendx.conf"
