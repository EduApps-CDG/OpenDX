#pragma once
#include <gdk/gdk.h>
#include "gdkdrawcontextprivate.hpp"
#include <unknwn.h>

G_BEGIN_DECLS

#define GDK_D3D_CONTEXT_CLASS(klass)        (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_D3D_CONTEXT, GdkD3DContextClass))
#define GDK_IS_D3D_CONTEXT_CLASS(klass)        (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_D3D_CONTEXT))
#define GDK_D3D_CONTEXT_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_D3D_CONTEXT, GdkD3DContextClass))


typedef struct _GdkD3DContextClass       GdkD3DContextClass;
typedef struct _GdkD3DContext          GdkD3DContext;

typedef struct _GdkD3DContextPrivate GdkD3DContextPrivate;

struct ID3DCompatibleDevice:IUnknown {
    HRESULT Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const void/*RGNDATA*/* pDirtyRegion);
};

struct _GdkD3DContextPrivate
{
    ///TODO: Fix when implementing D3D10, D3D11, D3D12...
    ID3DCompatibleDevice* d3d_device;

    // Other internal state
    uint32_t *framebuffer;
};

struct _GdkD3DContext
{
  GdkDrawContext parent_instance;
  cairo_region_t *old_updated_area[2];
  GdkD3DContextPrivate *priv;
};

struct _GdkD3DContextClass
{
  GdkDrawContextClass parent_class;
  gpointer padding;
};

G_END_DECLS