/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Callbacks.hpp
*/

#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include <gtk/gtk.h>

class Callbacks {
public:
    static void on_file_new(GSimpleAction *action, GVariant *parameter, gpointer user_data);
    static void on_file_open(GSimpleAction *action, GVariant *parameter, gpointer user_data);
    static void on_file_quit(GSimpleAction *action, GVariant *parameter, gpointer user_data);
};

#endif // CALLBACKS_HPP
