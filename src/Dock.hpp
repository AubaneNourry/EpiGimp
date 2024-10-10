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
#include "buttons/DraggableButton.hpp"

enum DockPosition {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

class Dock {
public:
    Dock(int width, std::vector<Tab*> initial_tabs, DockPosition position, SDL_Color color);
    void render(SDL_Renderer* renderer);
    void add_tab(Tab* tab);
    void set_hidden(bool hide);
    void handleEvent(const SDL_Event& event);
    void stickToEdge(SDL_Renderer* renderer);
    void maintainRatio(SDL_Renderer* renderer);
    
private:
    unsigned int width;
    bool hidden;
    unsigned int active_tab;
    std::vector<Tab*> tabs;
    SDL_Color color;
    SDL_Rect dockArea;
    DraggableButton* dragDockButton;
    DockPosition position;
};

#endif // DOCK_HPP
