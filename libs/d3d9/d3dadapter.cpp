#include <windows.h>
#include "idirect3d9.hpp"

// typedef struct IDirect3D9ExVtbl
// {
// 	/* IUnknown */
// 	HRESULT (*QueryInterface)(IDirect3D9Ex *This, REFIID riid, void **ppvObject);
// 	ULONG (*AddRef)(IDirect3D9Ex *This);
// 	ULONG (*Release)(IDirect3D9Ex *This);
// 	/* IDirect3D9 */
// 	HRESULT (*RegisterSoftwareDevice)(IDirect3D9Ex *This, void *pInitializeFunction);
// 	UINT (*GetAdapterCount)(IDirect3D9Ex *This);
// 	HRESULT (*GetAdapterIdentifier)(IDirect3D9Ex *This, UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 *pIdentifier);
// 	UINT (*GetAdapterModeCount)(IDirect3D9Ex *This, UINT Adapter, D3DFORMAT Format);
// 	HRESULT (*EnumAdapterModes)(IDirect3D9Ex *This, UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE *pMode);
// 	HRESULT (*GetAdapterDisplayMode)(IDirect3D9Ex *This, UINT Adapter, D3DDISPLAYMODE *pMode);
// 	HRESULT (*CheckDeviceType)(IDirect3D9Ex *This, UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed);
// 	HRESULT (*CheckDeviceFormat)(IDirect3D9Ex *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
// 	HRESULT (*CheckDeviceMultiSampleType)(IDirect3D9Ex *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD *pQualityLevels);
// 	HRESULT (*CheckDepthStencilMatch)(IDirect3D9Ex *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat);
// 	HRESULT (*CheckDeviceFormatConversion)(IDirect3D9Ex *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
// 	HRESULT (*GetDeviceCaps)(IDirect3D9Ex *This, UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9 *pCaps);
// 	HMONITOR (*GetAdapterMonitor)(IDirect3D9Ex *This, UINT Adapter);
// 	HRESULT (*CreateDevice)(IDirect3D9Ex *This, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface);
// 	/* IDirect3D9Ex */
// 	UINT (*GetAdapterModeCountEx)(IDirect3D9Ex *This, UINT Adapter, const D3DDISPLAYMODEFILTER *pFilter);
// 	HRESULT (*EnumAdapterModesEx)(IDirect3D9Ex *This, UINT Adapter, const D3DDISPLAYMODEFILTER *pFilter, UINT Mode, D3DDISPLAYMODEEX *pMode);
// 	HRESULT (*GetAdapterDisplayModeEx)(IDirect3D9Ex *This, UINT Adapter, D3DDISPLAYMODEEX *pMode, D3DDISPLAYROTATION *pRotation);
// 	HRESULT (*CreateDeviceEx)(IDirect3D9Ex *This, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, D3DDISPLAYMODEEX *pFullscreenDisplayMode, IDirect3DDevice9Ex **ppReturnedDeviceInterface);
// 	HRESULT (*GetAdapterLUID)(IDirect3D9Ex *This, UINT Adapter, LUID *pLUID);
// } IDirect3D9ExVtbl;

// /**
//  * Thanks to Gallium Nine for the implementation of this function.
//  */
// static IDirect3D9ExVtbl d3dadapter9_vtable = {
//     (void *)d3dadapter9_QueryInterface,
//     (void *)d3dadapter9_AddRef,
//     (void *)d3dadapter9_Release,
//     (void *)d3dadapter9_RegisterSoftwareDevice,
//     (void *)d3dadapter9_GetAdapterCount,
//     (void *)d3dadapter9_GetAdapterIdentifier,
//     (void *)d3dadapter9_GetAdapterModeCount,
//     (void *)d3dadapter9_EnumAdapterModes,
//     (void *)d3dadapter9_GetAdapterDisplayMode,
//     (void *)d3dadapter9_CheckDeviceType,
//     (void *)d3dadapter9_CheckDeviceFormat,
//     (void *)d3dadapter9_CheckDeviceMultiSampleType,
//     (void *)d3dadapter9_CheckDepthStencilMatch,
//     (void *)d3dadapter9_CheckDeviceFormatConversion,
//     (void *)d3dadapter9_GetDeviceCaps,
//     (void *)d3dadapter9_GetAdapterMonitor,
//     (void *)d3dadapter9_CreateDevice,
//     (void *)d3dadapter9_GetAdapterModeCountEx,
//     (void *)d3dadapter9_EnumAdapterModesEx,
//     (void *)d3dadapter9_GetAdapterDisplayModeEx,
//     (void *)d3dadapter9_CreateDeviceEx,
//     (void *)d3dadapter9_GetAdapterLUID
// };