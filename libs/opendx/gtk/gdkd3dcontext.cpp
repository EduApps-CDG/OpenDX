/**
 * Thanks to https://github.com/GNOME/gtk/blob/main/gdk/gdkvulkancontext.c
 * 
 * @brief A D3D context for GDK
 */
#include "gdkd3dcontext.hpp"
#include <gdk/gdk.h>


struct _GdkD3DContextPrivate {
    int drm_fd;
    int dmabuf_fd;
    uint32_t framebuffer_id;
    // ... outros dados como EGLDisplay, EGLContext, etc.
    bool is_in_frame; // Para saber se estamos entre begin_frame e end_frame
};

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

static void gdk_d3d_context_class_init(GdkD3DContextClass *klass) {
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    GdkDrawContextClass *context_class = GDK_DRAW_CONTEXT_CLASS(klass);

    gobject_class->finalize = gdk_d3d_context_finalize;

    context_class->begin_frame = gdk_d3d_context_begin_frame;
    context_class->end_frame = gdk_d3d_context_end_frame;
    context_class->is_in_frame = gdk_d3d_context_is_in_frame;
}

GdkDrawContext* gdk_d3d_context_new(void) {
    return (GdkDrawContext*) g_object_new(GDK_TYPE_D3D_CONTEXT, NULL);
}