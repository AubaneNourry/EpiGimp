/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Dock.cpp
*/

#include "Dock.hpp"

Dock::Dock(int min_width, int max_width, std::vector<Tab*> initial_tabs)
    : min_width(min_width), max_width(max_width), hidden(false), active_tab(nullptr) {
    // Set the initial dock area size
    dockArea = { 0, 0, min_width, 600 }; // Example height, adjust as needed

    for (Tab* tab : initial_tabs) {
        add_tab(tab);
    }
}

void Dock::render(SDL_Renderer* renderer) {
    if (hidden) return;

    // Render dock background
    SDL_SetRenderDrawColor(renderer, 58, 58, 58, 255); // Dark gray
    SDL_RenderFillRect(renderer, &dockArea);

    // Render tabs here
    for (auto& tab : tabs) {
        // Draw each tab; use tab's properties and methods to render
    }
}

void Dock::add_tab(Tab* tab) {
    tabs.push_back(tab);
    if (active_tab == nullptr) {
        active_tab = tab; // Switch to the first tab by default
    }
}
