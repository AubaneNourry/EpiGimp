/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** IUIElement.hpp
*/

#ifndef IUIELEMENT_HPP
#define IUIELEMENT_HPP

#include <SDL2/SDL.h>

#include "Utils.hpp"

class IUIElement {
public:
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void handleEvent(const SDL_Event& event) = 0;
};

#endif // IUIELEMENT_HPP
