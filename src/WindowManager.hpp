/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** WindowManager.hpp
*/

#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <gtk/gtk.h>

class WindowManager {
public:
    static void resize_window_screen_size(GtkWidget* window);
    static void resize_window_windowed(GtkWidget* window, int width, int height);
    static void set_window_fullscreened(GtkWidget* window);
};

#endif // WINDOW_MANAGER_HPP
