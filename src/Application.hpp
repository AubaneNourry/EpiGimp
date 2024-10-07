/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.hpp
*/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <gtk/gtk.h>
#include <iostream>
#include <vector>

#include "WindowManager.hpp"
#include "MenuBar.hpp"
#include "Callbacks.hpp"

class Application {
public:
    Application(const char *appName);
    ~Application() = default;
    int run(int argc, char** argv);
    int getStatus() const;
    GtkApplication* getApp() const;
    static void onActivate(GtkApplication* app, gpointer user_data);

private:
    GtkApplication* app;
    MenuBar *menuBar;
    int status;
};

#endif // APPLICATION_HPP
