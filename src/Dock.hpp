/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Dock.hpp
*/

#ifndef DOCK_HPP
#define DOCK_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "Tab.hpp"

class Dock {
public:
    Dock(int min_width, int max_width, std::vector<Tab*> initial_tabs);
    void render(SDL_Renderer* renderer);
    void add_tab(Tab* tab);
    void set_hidden(bool hide);
    
private:
    int min_width;
    int max_width;
    bool hidden;
    Tab* active_tab;
    std::vector<Tab*> tabs;

    SDL_Rect dockArea; // Define your dock area as a rectangle
};

#endif // DOCK_HPP
