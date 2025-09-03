#pragma once
#include <gdk/gdk.h>
#include "gdkd3dcontextprivate.hpp"

G_BEGIN_DECLS
#define GDK_TYPE_D3D_CONTEXT (gdk_d3d_context_get_type())
#define GDK_D3D_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GDK_TYPE_D3D_CONTEXT, GdkD3DContext))
#define GDK_IS_D3D_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GDK_TYPE_D3D_CONTEXT))

#define GDK_D3D_ERROR (gdk_d3d_error_quark())

GDK_AVAILABLE_IN_ALL
GQuark gdk_d3d_error_quark (void);
GDK_AVAILABLE_IN_ALL GType gdk_d3d_context_get_type(void) G_GNUC_CONST;

static void gdk_d3d_context_init(GdkD3DContext *context);
GDK_AVAILABLE_IN_ALL void gdk_d3d_context_set_framebuffer(GdkD3DContext *self, uint32_t *buffer);
GDK_AVAILABLE_IN_ALL void gdk_d3d_context_set_device(GdkD3DContext *self, ID3DCompatibleDevice *device);
G_END_DECLS