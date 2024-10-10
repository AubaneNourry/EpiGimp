/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Button.cpp
*/

#include "Button.hpp"

Button::Button(const std::string& label, SDL_Rect *rect, SDL_Color color, bool toggle)
    : AButton(label, rect, color, toggle) {}

void Button::render(SDL_Renderer* renderer) {
    renderButtonRect(renderer);
    renderButtonLabel(renderer);
}
