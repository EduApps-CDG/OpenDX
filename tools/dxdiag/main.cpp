#include <iostream>

#include <gtk/gtk.h> //GTK4

#include <config.hpp>
#include "layout/MainWindow.hpp"
#include "src/SystemTab.hpp"

//DirectX files:
#include <d3d9.h>

int main(int argc, char *argv[])
{
    #if DEBUG 
        printf("Application started!\n\n");
    #endif

    //initializes GTK screen
    gtk_init();
    const gchar* glade_string = MainWindow::ui.c_str();
    GtkBuilder* builder = gtk_builder_new_from_string(glade_string, -1);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    //setup events and show the screen:
    new SystemTab(builder);
    gtk_widget_show(GTK_WIDGET(window));

    while (g_list_model_get_n_items (gtk_window_get_toplevels ()) > 0)
        g_main_context_iteration (NULL, TRUE);

    g_object_unref(builder);

    return 0;
}
