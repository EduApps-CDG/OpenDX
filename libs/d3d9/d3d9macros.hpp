#pragma once

//not sure if this goes here.
/*#define API_ENTER_NO_LOCK() \
    do { \
        InterlockedIncrement(&g_nInsideAPI); \
    } while (false)*/

// #ifdef _DEBUG
// #define DXGASSERT(exp) do { \
//     if (!(exp)) { \
//         fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #exp, __FILE__, __LINE__); \
//         abort(); \
//     } \
// } while (0)
// #else
// #define DXGASSERT(exp) ((void)0)
// #endif

// #define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
//                 ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
//                 ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))