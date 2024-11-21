/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Dock.cpp
*/

#include "Dock.hpp"
#include "../Application.hpp"

Dock::Dock(const int width, const std::vector<ATab*>& initial_tabs, const DockPosition position, const std::vector<ATab *>& dock_tabs, const SDL_Color color)
    : width(width), hidden(false), active_tab(0), tabs(initial_tabs), color(color), position(position)
{
    SDL_Rect button_area = {0, 0, 0, 0};
    Axis axis = X;
    switch (position) {
        case LEFT:
            dockArea = {0, 25, width, 600};
            button_area = {dockArea.x + dockArea.w, dockArea.y, 15, dockArea.h};
            axis = X;
            break;
        case RIGHT:
            dockArea = {800 - width, 25, width, 600};
            button_area = {dockArea.x - 15, dockArea.y, 15, dockArea.h};
            axis = X;
            break;
        case TOP:
            dockArea = {0, 25, 800, width};
            button_area = {dockArea.x, dockArea.y + dockArea.h, dockArea.w, 15};
            axis = Y;
            break;
        case BOTTOM:
            dockArea = {0, 600 - width, 800, width};
            button_area = {dockArea.x, dockArea.y - 15, dockArea.w, 15};
            axis = Y;
            break;
    }
    const SDL_Color dragColor = {
        static_cast<Uint8>(std::max(0, static_cast<int>(color.r) - 15)),
        static_cast<Uint8>(std::max(0, static_cast<int>(color.g) - 15)),
        static_cast<Uint8>(std::max(0, static_cast<int>(color.b) - 15)),
        color.a
    };
    dragDockButton = new DraggableButton(button_area.x, button_area.y, button_area.w, button_area.h, dragColor, axis);
    tabs = dock_tabs;
}

void Dock::handleEvent(const SDL_Event& event) {
    dragDockButton->handleEvent(event);
    for (const auto& tab : tabs) {
        tab->handleEvent(event);
    }
}

void Dock::maintainRatio(SDL_Renderer* renderer) {
    if (hidden) return;
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    
    SDL_Rect *buttonRect = dragDockButton->getRect();
    switch (position) {
        case RIGHT:
            dockArea.x = windowWidth - width;
            buttonRect->x = dockArea.x - 15;
            break;
        case BOTTOM:
            dockArea.y = windowHeight - width;
            buttonRect->y = dockArea.y - 15;
            break;
        default:
            break;
    }
            
}

void Dock::stickToEdge(SDL_Renderer* renderer) {
    if (hidden) return;
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_Rect *buttonRect = dragDockButton->getRect();
    switch (position) {
        case LEFT:
            dockArea.w = buttonRect->x;
            dockArea.h = windowHeight;
            buttonRect->h = windowHeight;
            break;
        case RIGHT:
            dockArea.x = buttonRect->x + buttonRect->w;
            dockArea.w = windowWidth - dockArea.x;
            dockArea.h = windowHeight;
            buttonRect->h = windowHeight;
            break;
        case TOP:
            dockArea.h = buttonRect->y - 25;
            dockArea.w = windowWidth;
            buttonRect->w = windowWidth;
            break;
        case BOTTOM:
            dockArea.y = buttonRect->y + buttonRect->h;
            dockArea.h = windowHeight - dockArea.y;
            dockArea.w = windowWidth;
            buttonRect->w = windowWidth;
            break;
    }
}

void Dock::render(SDL_Renderer* renderer) {
    if (hidden) return;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    stickToEdge(renderer);
    SDL_RenderFillRect(renderer, &dockArea);

    dragDockButton->render(renderer);

    for (const auto& tab : tabs) {
        tab->render(renderer);
    }
}

void Dock::add_tab(ATab* tab) {
    tabs.push_back(tab);
}

void Dock::set_hidden(const bool hide) {
    hidden = hide;
}
