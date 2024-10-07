/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Callbacks.cpp
*/
#include "Callbacks.hpp"

void Callbacks::on_file_new(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    (void) action;
    (void) parameter;
    (void) user_data;

    g_print("New file\n");
}

void Callbacks::on_file_open(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    (void) action;
    (void) parameter;
    (void) user_data;

    g_print("Open file\n");
}

void Callbacks::on_file_quit(GSimpleAction *action, GVariant *parameter, gpointer user_data) {
    (void) action;
    (void) parameter;
    (void) user_data;

    g_print("Quit\n");
}
