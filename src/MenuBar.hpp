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
#include "IUIElement.hpp"

class MenuBar final : public IUIElement {
public:
    MenuBar() = default;
    ~MenuBar() override = default;

    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override {
        return;
    }
};

#endif // MENU_BAR_HPP
