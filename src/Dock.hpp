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
#include "IUIElement.hpp"

enum DockPosition {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

class Dock final : public IUIElement {
public:
    Dock(int width, const std::vector<Tab*>& initial_tabs, DockPosition position, const std::vector<Tab *>& dock_tabs = {}, SDL_Color color = UICOLOR);
    void render(SDL_Renderer* renderer) override;
    void add_tab(Tab* tab);
    void set_hidden(bool hide);
    void handleEvent(const SDL_Event& event) override;
    void stickToEdge(SDL_Renderer* renderer);
    void maintainRatio(SDL_Renderer* renderer);
    
private:
    int width;
    bool hidden;
    unsigned int active_tab;
    std::vector<Tab*> tabs;
    SDL_Color color;
    SDL_Rect dockArea{};
    DraggableButton* dragDockButton;
    DockPosition position;
};

#endif // DOCK_HPP
