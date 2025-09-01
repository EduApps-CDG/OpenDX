#pragma once
#include <config.hpp>
#include <windows.h>
#include "d3d9helper.hpp"
#include "d3d9types.hpp"
#include "idirect3ddevice9.hpp"

#define D3DCREATE_PUREDEVICE                    0x00000010L
#define D3DCREATE_SOFTWARE_VERTEXPROCESSING     0x00000020L
#define D3DCREATE_HARDWARE_VERTEXPROCESSING     0x00000040L
#define D3DCREATE_MIXED_VERTEXPROCESSING        0x00000080L

typedef struct IDirect3D9 *LPDIRECT3D9, *PDIRECT3D9;
IDirect3D9* Direct3DCreate9(UINT SDKVersion);