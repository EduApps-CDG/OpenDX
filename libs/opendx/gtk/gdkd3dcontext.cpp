/**
 * Thanks to https://github.com/GNOME/gtk/blob/main/gdk/gdkvulkancontext.c
 * 
 * @brief A D3D context for GDK
 */
 #include <cstdint>
#include <gdk/gdk.h>
 #include <config.hpp>
 #include "gdkd3dcontext.hpp"
#include <cairo.h>
 #include "gdkd3dcontextprivate.hpp"
#include "glib.h"
#include "gtk/gtk.h"

G_DEFINE_TYPE_WITH_PRIVATE(GdkD3DContext, gdk_d3d_context, GDK_TYPE_DRAW_CONTEXT)
G_DEFINE_QUARK (gdk-d3d-error, gdk_d3d_error)

static void gdk_d3d_context_dispose(GObject *object);
static void gdk_d3d_context_begin_frame (
    GdkDrawContext *draw_context,
    gboolean        prefers_high_depth,
    cairo_region_t *region
);
static void gdk_d3d_context_draw(GtkDrawingArea *area,
               cairo_t        *cr,
               int             width,
               int             height,
               gpointer        data);

static void gdk_d3d_context_end_frame (
    GdkDrawContext *draw_context,
    cairo_region_t *painted
);
// Add overrides for other virtual functions from GdkDrawContext here.

static void
gdk_d3d_context_class_init(GdkD3DContextClass *klass)
{
    DLOG("libopendx.so: gdk_d3d_context_class_init(): Initializing D3D rendering context class");
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    GdkDrawContextClass *draw_context_class = GDK_DRAW_CONTEXT_CLASS(klass);

    // Override the dispose method from GObject. This is the correct place
    // to free native graphics resources (e.g., the D3D device).
    object_class->dispose = gdk_d3d_context_dispose;
    // draw_context_class->begin_frame = gdk_d3d_context_begin_frame;
    // draw_context_class->end_frame = gdk_d3d_context_end_frame;

    // Override virtual functions from the parent GdkDrawContextClass.
    // These are now accessible because we used G_DECLARE_DERIVABLE_TYPE.
    // For a modern implementation, you would investigate which functions
    // are called by the GSK renderer to override.
    // e.g., draw_context_class->surface_resized = gdk_d3d_context_surface_resized;
}

static void
gdk_d3d_context_init(GdkD3DContext *self)
{
    DLOG("libopendx.so: gdk_d3d_context_init(): Initializing D3D rendering context");
    // Get a pointer to the private data structure, which is allocated automatically.
    self->priv = (GdkD3DContextPrivate *) gdk_d3d_context_get_instance_private(self);
    GdkD3DContextPrivate *priv = self->priv;
    GObject *object = G_OBJECT(self);

    // Initialize all instance variables to their default state.
    // priv->d3d_device = NULL; // etc.
    priv->framebuffer = nullptr;
    priv->d3d_device = nullptr;
    gtk_drawing_area_set_draw_func(
        GTK_DRAWING_AREA(object),
        gdk_d3d_context_draw,
        &priv->framebuffer,
        NULL
    );
    
    // NOTE: Actual D3D device and swapchain creation is a complex process.
    // It requires a native window handle (HWND on Windows), which is only available
    // after the associated GtkWidget has been "realized". Therefore, this init
    // function is too early for that step. Device setup should be triggered by
    // connecting to the GtkWidget::realize signal.
}

static void
gdk_d3d_context_dispose(GObject *object)
{
    DLOG("libopendx.so: gdk_d3d_context_dispose(): Disposing D3D rendering context");
    GdkD3DContext *self = GDK_D3D_CONTEXT(object);
    GdkD3DContextPrivate *priv = self->priv;

    // This function is called when the last reference to the object is dropped.
    // Release all your native Direct3D resources here to prevent leaks.
    // The order of release is often important.
    // e.g., if (priv->swap_chain) { priv->swap_chain->Release(); priv->swap_chain = NULL; }
    // e.g., if (priv->d3d_device) { priv->d3d_device->Release(); priv->d3d_device = NULL; }

    // Always chain up to the parent class's dispose method. This is crucial
    // for ensuring the parent object is cleaned up correctly.
    G_OBJECT_CLASS(gdk_d3d_context_parent_class)->dispose(object);
}

extern "C" void gdk_d3d_context_set_framebuffer(GdkD3DContext *self, uint32_t *buffer)
{
    // g_return_if_fail é um macro de checagem do GLib
    g_return_if_fail(GDK_IS_D3D_CONTEXT(self));

    DLOG("libopendx.so: gdk_d3d_context_set_framebuffer(): Setting framebuffer for D3D context");
    GdkD3DContextPrivate *priv = (GdkD3DContextPrivate *) gdk_d3d_context_get_instance_private(self);
    priv->framebuffer = buffer;
}

extern "C" void gdk_d3d_context_set_device(GdkD3DContext *self, ID3DCompatibleDevice *device)
{
    g_return_if_fail(GDK_IS_D3D_CONTEXT(self));

    DLOG("libopendx.so: gdk_d3d_context_set_device(): Setting D3D device for D3D context");
    GdkD3DContextPrivate *priv = (GdkD3DContextPrivate *) gdk_d3d_context_get_instance_private(self);
    priv->d3d_device = device;
}

static void gdk_d3d_context_begin_frame (
    GdkDrawContext *draw_context,
    gboolean        prefers_high_depth,
    cairo_region_t *region
) {

}

static void gdk_d3d_context_end_frame (
    GdkDrawContext *draw_context,
    cairo_region_t *painted_region
) {
    GdkD3DContext *ctx = (GdkD3DContext *) GDK_D3D_CONTEXT(draw_context);
    GdkD3DContextPrivate *priv = ctx->priv;
    uint32_t* framebuffer = priv->framebuffer;

    GdkSurface *surface = gdk_draw_context_get_surface(draw_context);

    GDK_DRAW_CONTEXT_CLASS(gdk_d3d_context_parent_class)->end_frame(draw_context, painted_region);
}

static void gdk_d3d_context_draw(GtkDrawingArea *area,
               cairo_t        *cr,
               int             width,
               int             height,
               gpointer        data) {
    DLOG("libopendx.so: gdk_d3d_context_draw(): Drawing framebuffer to widget");
    uint32_t* framebuffer = *(uint32_t**)data;
    if (framebuffer == nullptr) {
        DLOG("libopendx.so: gdk_d3d_context_draw(): No framebuffer set, skipping draw");
        return;
    }

    cairo_surface_t *cairo_surface =
        cairo_image_surface_create_for_data(
            (unsigned char*)framebuffer,
            CAIRO_FORMAT_ARGB32,
            width,
            height,
            width * 4 // pitch (bytes per row)
        );
    
    cairo_set_source_surface(cr, cairo_surface, 0, 0);
    cairo_paint(cr);
    cairo_surface_destroy(cairo_surface);
}