#include <config.hpp>
#include "idirect3ddevice9.hpp"

export class D3DObject {
    public:
        D3DObject(IDirect3DDevice9* device) : m_device(device) {}
        virtual ~D3DObject() {}

        virtual void render() = 0;

    protected:
        IDirect3DDevice9* m_device;
};