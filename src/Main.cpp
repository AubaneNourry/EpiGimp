/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Main.cpp
*/
#include <gtk/gtk.h>

void resize_window_screen_size(GtkWidget* window) {
    GdkDisplay* display = gdk_display_get_default();
    GdkSurface* surface = gtk_native_get_surface(gtk_widget_get_native(window));
    
    if (surface) {
        GdkMonitor* monitor = gdk_display_get_monitor_at_surface(display, surface);
        GdkRectangle geometry;

        gdk_monitor_get_geometry(monitor, &geometry);
        gtk_window_set_default_size(GTK_WINDOW(window), geometry.width, geometry.height);
    } else {
        g_warning("Surface is NULL. Unable to get monitor information.");
    }
}

void resize_window_windowed(GtkWidget* window, int width, int height) {
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
}

void set_window_fullscreened(GtkWidget* window) {
    gtk_window_fullscreen(GTK_WINDOW(window));
}

static void on_activate(GtkApplication* app, gpointer user_data) {
    (void) user_data;

    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "EpiGimp");
    gtk_widget_show(window);
    resize_window_screen_size(window);
}

int main(int argc, char** argv) {
    GtkApplication* app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
