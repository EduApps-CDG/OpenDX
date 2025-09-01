#pragma once
#include <gdk/gdk.h>

G_BEGIN_DECLS
#define GDK_TYPE_D3D_CONTEXT (gdk_d3d_context_get_type())
#define GDK_D3D_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GDK_TYPE_D3D_CONTEXT, GdkD3DContext))
#define GDK_IS_D3D_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GDK_TYPE_D3D_CONTEXT))

#define GDK_D3D_ERROR (g_error_quark())

G_DECLARE_FINAL_TYPE(GdkD3DContext, gdk_d3d_context, GDK, D3D_CONTEXT, GdkDrawContext)

GDK_AVAILABLE_IN_ALL GType gdk_d3d_context_get_type(void) G_GNUC_CONST;

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkD3DContext, g_object_unref)

G_END_DECLS