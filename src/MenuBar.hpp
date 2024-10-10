/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.hpp
*/

#ifndef MENU_BAR_HPP
#define MENU_BAR_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "buttons/DropdownButton.hpp"
#include "buttons/Button.hpp"

class MenuBar {
public:
    MenuBar(int x);
    ~MenuBar() = default;

    void render(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event) {
        for (auto& item : _menu_items) {
            item->handleEvent(event);
        }
    }

private:
    std::vector<DropdownButton *> _menu_items;
    SDL_Rect rect;
};

#endif // MENU_BAR_HPP
