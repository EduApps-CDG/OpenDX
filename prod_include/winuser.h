/**
 * From "libopendx.so"
 */
#pragma once
#include <windows.h>

/*
 * MSG
 * ref: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-msg
 */
typedef struct tagMSG {
  HWND   hwnd;
  UINT   message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD  time;
  POINT  pt;
  DWORD  lPrivate;
} MSG, *PMSG, *NPMSG, *LPMSG;

#define WM_QUIT 0x0012

/**
 * Extended Window Styles
 * ref: https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles
 */
#define WS_EX_ACCEPTFILES 0x00000010L
#define WS_EX_APPWINDOW 0x00040000L
#define WS_EX_CLIENTEDGE 0x00000200L
#define WS_EX_COMPOSITED 0x02000000L
#define WS_EX_CONTEXTHELP 0x00000400L
#define WS_EX_CONTROLPARENT 0x00010000L
#define WS_EX_DLGMODALFRAME 0x00000001L
#define WS_EX_LAYERED 0x00080000
#define WS_EX_LAYOUTRTL 0x00400000L
#define WS_EX_LEFT 0x00000000L
#define WS_EX_LEFTSCROLLBAR 0x00004000L
#define WS_EX_LTRREADING 0x00000000L
#define WS_EX_MDICHILD 0x00000040L
#define WS_EX_NOACTIVATE 0x08000000L
#define WS_EX_NOINHERITLAYOUT 0x00100000L
#define WS_EX_NOPARENTNOTIFY 0x00000004L
#define WS_EX_NOREDIRECTIONBITMAP 0x00200000L
#define WS_EX_RIGHT 0x00001000L
#define WS_EX_RIGHTSCROLLBAR 0x00000000L
#define WS_EX_RTLREADING 0x00002000L
#define WS_EX_STATICEDGE 0x00020000L
#define WS_EX_TOOLWINDOW 0x00000080L
#define WS_EX_TOPMOST 0x00000008L
#define WS_EX_TRANSPARENT 0x00000020L
#define WS_EX_WINDOWEDGE 0x00000100L
#define WS_EX_OVERLAPPEDWINDOW (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)

/*
 * Window Styles
 * ref: https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
 */
#define WS_BORDER 0x00800000L
#define WS_CAPTION 0x00C00000L
#define WS_CHILD 0x40000000L
#define WS_CHILDWINDOW 0x40000000L
#define WS_CLIPCHILDREN 0x02000000L
#define WS_CLIPSIBLINGS 0x04000000L
#define WS_DISABLED 0x08000000L
#define WS_DLGFRAME 0x00400000L
#define WS_GROUP 0x00020000L
#define WS_HSCROLL 0x00100000L
#define WS_ICONIC 0x20000000L
#define WS_MAXIMIZE 0x01000000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_MINIMIZE 0x20000000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_OVERLAPPED 0x00000000L
#define WS_POPUP 0x80000000L
#define WS_SIZEBOX 0x00040000L
#define WS_SYSMENU 0x00080000L
#define WS_TABSTOP 0x00010000L
#define WS_THICKFRAME 0x00040000L
#define WS_TILED 0x00000000L
#define WS_VISIBLE 0x10000000L
#define WS_VSCROLL 0x00200000L
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)
#define WS_TILEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

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
);

BOOL ShowWindow(HWND window, int nCmdShow);
BOOL DestroyWindow(HWND window);

BOOL PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
#define CreateWindowExW CreateWindowExA
#define PeekMessageW PeekMessageA
#define PM_NOREMOVE 0x0000
#define PM_REMOVE 0x0001
#define PM_NOYIELD 0x0002

// https://www.codeproject.com/Answers/136442/Differences-Between-CreateWindow-and-CreateWindowE#answer3
#define CreateWindowA(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\
CreateWindowExA(0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)
#define CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\
CreateWindowExW(0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)

//TODO: check if it's needed in a linux environment
#if UNICODE
    #define CreateWindow CreateWindowW
    #define PeekMessage PeekMessageW
#else
    #define CreateWindow CreateWindowA
    #define PeekMessage PeekMessageA
#endif