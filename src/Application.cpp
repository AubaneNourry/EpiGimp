/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.cpp
*/

#include "Application.hpp"

Application::Application(const char *appName) {
    app = gtk_application_new(appName, G_APPLICATION_FLAGS_NONE);
    status = 0;

    g_signal_connect(app, "activate", G_CALLBACK(Application::onActivate), this);  // Pass 'this' as user_data
}

void Application::onActivate(GtkApplication* app, gpointer user_data) {
    Application* self = static_cast<Application*>(user_data);

    self->window = self->initWindow(app);
    self->menuBar = self->initMenuBar(self->window);
    self->bindEntries(app);
}

GtkWidget* Application::initWindow(GtkApplication* app) {
    GtkWidget* window = gtk_application_window_new(app);

    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_title(GTK_WINDOW(window), "EpiGimp");
    gtk_widget_show(window);
    WindowManager::WindowManager::resize_window_screen_size(window);
    return window;
}

void Application::bindEntries(GtkApplication* app) {
    static const GActionEntry app_entries[] = {
        { "new", Callbacks::on_file_new, NULL, NULL, NULL, { 0 } },
        { "open", Callbacks::on_file_open, NULL, NULL, NULL, { 0 } },
        { "save", NULL, NULL, NULL, NULL, { 0 } },
        { "quit", Callbacks::on_file_quit, NULL, NULL, NULL, { 0 } },
        { "undo", NULL, NULL, NULL, NULL, { 0 } },
        { "redo", NULL, NULL, NULL, NULL, { 0 } },
        { "cut", NULL, NULL, NULL, NULL, { 0 } },
        { "copy", NULL, NULL, NULL, NULL, { 0 } },
        { "paste", NULL, NULL, NULL, NULL, { 0 } },
        { "select-all", NULL, NULL, NULL, NULL, { 0 } },
        { "select-none", NULL, NULL, NULL, NULL, { 0 } },
        { "select-invert", NULL, NULL, NULL, NULL, { 0 } },
        { "zoom-in", NULL, NULL, NULL, NULL, { 0 } },
        { "zoom-out", NULL, NULL, NULL, NULL, { 0 } },
        { "fullscreen", NULL, NULL, NULL, NULL, { 0 } },
    };
    g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), NULL);
}

MenuBar *Application::initMenuBar(GtkWidget* window) {
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    MenuBar *menubar = new MenuBar();
    GtkWidget* menuBarWidget = menubar->create_menubar(window);

    gtk_box_append(GTK_BOX(vbox), menuBarWidget);
    gtk_window_set_child(GTK_WINDOW(window), vbox);
    gtk_widget_show(vbox);
    return menubar;
}

int Application::run(int argc, char** argv) {
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