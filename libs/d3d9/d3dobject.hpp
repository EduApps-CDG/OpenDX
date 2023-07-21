#pragma once
#include "idirect3ddevice9.hpp"

class D3DObject {
    public:
        D3DObject(IDirect3DDevice9* device):m_device(device) {
            // TODO: complete
        }
    protected:
        IDirect3DDevice9* m_device;
};