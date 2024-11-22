/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Button.cpp
*/

#include "Button.hpp"

Button::Button(const std::string& label, SDL_Rect *rect, const SDL_Color color, SDL_Texture *image, const bool toggle)
    : AButton(label, rect, color, image, toggle) {}

void Button::render(SDL_Renderer* renderer) {
    //if (image) {
    //    SDL_RenderCopy(renderer, image, nullptr, rect);
    //} else {
        renderButtonRect(renderer);
    //}
    renderButtonLabel(renderer);
}
