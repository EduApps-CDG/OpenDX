/**
 * Thanks to https://github.com/GNOME/gtk/blob/main/gdk/gdkvulkancontext.c
 * 
 * @brief A D3D context for GDK
 */
#include "gdkd3dcontext.hpp"

static void gdk_d3d_context_init(GdkD3DContext* self) {
}

static gboolean gdk_d3d_context_real_init(
    GInitable* initable,
    GCancellable* cancellable,
    GError** error
) {
    GdkD3DContext* context = GDK_D3D_CONTEXT(initable);
    // GdkVulkanContextPrivate *priv = gdk_vulkan_context_get_instance_private (context);
    GdkDisplay* display = gdk_draw_context_get_display(GDK_DRAW_CONTEXT(context));
    GdkSurface* surface = gdk_draw_context_get_surface(GDK_DRAW_CONTEXT(context));
    return TRUE;
}

static void gdk_d3d_context_initable_init(GInitableIface* iface) {
    iface->init = gdk_d3d_context_real_init;
}