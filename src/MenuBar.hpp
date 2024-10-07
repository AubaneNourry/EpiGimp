/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.hpp
*/

#ifndef MENU_BAR_HPP
#define MENU_BAR_HPP

#include <gtk/gtk.h>

class MenuBar {
public:
    MenuBar() = default;
    ~MenuBar() = default;

    GtkWidget* create_menubar(GtkWidget* window);

private:
    GMenu* create_file_menu();
    GMenu* create_edit_menu();
    GMenu* create_select_menu();
    GMenu* create_view_menu();

    void add_menu_item(GMenu* menu, const char* label, const char* action);
};

#endif // MENU_BAR_HPP
