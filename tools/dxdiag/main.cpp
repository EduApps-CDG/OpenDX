#include <iostream>
#include <gtk/gtk.h>
#include <config.hpp>
#include "layout/MainWindow.hpp"
#include "src/SystemTab.hpp"

//DirectX files:
#include <d3d9.h>

int main(int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    const gchar* glade_string = MainWindow::ui.c_str();

    GtkBuilder* builder = gtk_builder_new_from_string(glade_string, -1);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);

    SystemTab::setup(builder);
    gtk_widget_show_all(GTK_WIDGET(window));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    g_object_unref(builder);

    return 0;
}
