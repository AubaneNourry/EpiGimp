/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** WindowManager.cpp
*/

#include "WindowManager.hpp"

void WindowManager::resize_window_screen_size(GtkWidget* window) {
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

void WindowManager::resize_window_windowed(GtkWidget* window, int width, int height) {
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
}

void WindowManager::set_window_fullscreened(GtkWidget* window) {
    gtk_window_fullscreen(GTK_WINDOW(window));
}