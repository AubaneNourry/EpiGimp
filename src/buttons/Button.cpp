/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Button.cpp
*/

#include "Button.hpp"

Button::Button(const std::string& label, SDL_Rect rect, TTF_Font* font, SDL_Color color)
    : AButton(label, rect, font, color) {}

void Button::click() {
    AButton::click();
}

void Button::hover() {
    AButton::hover();
}

void Button::release() {
    AButton::release();
}

void Button::render(SDL_Renderer* renderer) {
    renderButtonRect(renderer);
    renderButtonLabel(renderer);
}
