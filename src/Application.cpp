/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.cpp
*/

#include "Application.hpp"

Application::Application(const char *appName) {
    app = gtk_application_new(appName, G_APPLICATION_FLAGS_NONE);
}

void Application::onActivate(GtkApplication* app, gpointer user_data) {
    (void) user_data;

    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "EpiGimp");
    gtk_widget_show(window);
    WindowManager::WindowManager::resize_window_screen_size(window);
}

int Application::run(int argc, char** argv) {
    g_signal_connect(app, "activate", G_CALLBACK(Application::onActivate), nullptr);
    g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

int Application::getStatus() const {
    return status;
}

GtkApplication* Application::getApp() const {
    return app;
}