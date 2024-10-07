/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Main.cpp
*/
#include <gtk/gtk.h>

#include "Application.hpp"

int main(int argc, char** argv) {
    Application app("org.gtk.example");

    return app.run(argc, argv);
}
