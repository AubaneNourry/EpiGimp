/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.cpp
*/

#include "Application.hpp"

Application::Application(const char *appName) {
    app = gtk_application_new(appName, G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(Application::onActivate), nullptr);
    status = 0;
}

void Application::onActivate(GtkApplication* app, gpointer user_data) {
    (void) user_data;

    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "EpiGimp");
    gtk_widget_show(window);
    WindowManager::WindowManager::resize_window_screen_size(window);

    static const GActionEntry app_entries[] = {
    { "new", Callbacks::on_file_new, NULL, NULL, NULL },
    { "open", Callbacks::on_file_open, NULL, NULL, NULL },
    { "save", NULL, NULL, NULL, NULL },
    { "quit", Callbacks::on_file_quit, NULL, NULL, NULL },
    { "undo", NULL, NULL, NULL, NULL },
    { "redo", NULL, NULL, NULL, NULL },
    { "cut", NULL, NULL, NULL, NULL },
    { "copy", NULL, NULL, NULL, NULL },
    { "paste", NULL, NULL, NULL, NULL },
    { "select-all", NULL, NULL, NULL, NULL },
    { "select-none", NULL, NULL, NULL, NULL },
    { "select-invert", NULL, NULL, NULL, NULL },
    { "zoom-in", NULL, NULL, NULL, NULL },
    { "zoom-out", NULL, NULL, NULL, NULL },
    { "fullscreen", NULL, NULL, NULL, NULL },
    };
    g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), NULL);

    // Create a vertical box to hold the menubar and the rest of the content
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    MenuBar menubar;
    GtkWidget* menuBarWidget = menubar.create_menubar(window);
    gtk_box_append(GTK_BOX(vbox), menuBarWidget);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    gtk_widget_show(vbox);
    gtk_widget_show(window);

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