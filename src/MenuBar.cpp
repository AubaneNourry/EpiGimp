/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.cpp
*/

#include "MenuBar.hpp"

GtkWidget* MenuBar::create_menubar(GtkWidget* window) {
    (void)window;
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    // File menu
    GtkWidget* fileButton = gtk_menu_button_new();
    GtkWidget* fileLabel = gtk_label_new("File");
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(fileButton), G_MENU_MODEL(create_file_menu()));
    gtk_menu_button_set_child(GTK_MENU_BUTTON(fileButton), fileLabel);
    gtk_box_append(GTK_BOX(box), fileButton);

    // Edit menu
    GtkWidget* editButton = gtk_menu_button_new();
    GtkWidget* editLabel = gtk_label_new("Edit");
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(editButton), G_MENU_MODEL(create_edit_menu()));
    gtk_menu_button_set_child(GTK_MENU_BUTTON(editButton), editLabel);
    gtk_box_append(GTK_BOX(box), editButton);

    // Select menu
    GtkWidget* selectButton = gtk_menu_button_new();
    GtkWidget* selectLabel = gtk_label_new("Select");
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(selectButton), G_MENU_MODEL(create_select_menu()));
    gtk_menu_button_set_child(GTK_MENU_BUTTON(selectButton), selectLabel);
    gtk_box_append(GTK_BOX(box), selectButton);

    // View menu
    GtkWidget* viewButton = gtk_menu_button_new();
    GtkWidget* viewLabel = gtk_label_new("View");
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(viewButton), G_MENU_MODEL(create_view_menu()));
    gtk_menu_button_set_child(GTK_MENU_BUTTON(viewButton), viewLabel);
    gtk_box_append(GTK_BOX(box), viewButton);

    return box;
}

GMenu* MenuBar::create_file_menu() {
    GMenu* menu = g_menu_new();
    add_menu_item(menu, "New", "app.new");
    add_menu_item(menu, "Open", "app.open");
    add_menu_item(menu, "Save", "app.save");
    add_menu_item(menu, "Quit", "app.quit");
    return menu;
}

GMenu* MenuBar::create_edit_menu() {
    GMenu* menu = g_menu_new();
    add_menu_item(menu, "Undo", "app.undo");
    add_menu_item(menu, "Redo", "app.redo");
    add_menu_item(menu, "Cut", "app.cut");
    add_menu_item(menu, "Copy", "app.copy");
    add_menu_item(menu, "Paste", "app.paste");
    return menu;
}

GMenu* MenuBar::create_select_menu() {
    GMenu* menu = g_menu_new();
    add_menu_item(menu, "All", "app.select-all");
    add_menu_item(menu, "None", "app.select-none");
    add_menu_item(menu, "Invert", "app.select-invert");
    return menu;
}

GMenu* MenuBar::create_view_menu() {
    GMenu* menu = g_menu_new();
    add_menu_item(menu, "Zoom In", "app.zoom-in");
    add_menu_item(menu, "Zoom Out", "app.zoom-out");
    add_menu_item(menu, "Fullscreen", "app.fullscreen");
    return menu;
}

void MenuBar::add_menu_item(GMenu* menu, const char* label, const char* action) {
    g_menu_append(menu, label, action);
}
