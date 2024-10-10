/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Button.cpp
*/

#include "Button.hpp"

Button::Button(const std::string& label, int x, int y, int width, int height, TTF_Font* font, SDL_Color color)
    : AButton(label, x, y, width, height, font, color) {}

void Button::click() {
    std::cout << "Button '" << label << "' clicked!" << std::endl;
}

void Button::hover() {
    std::cout << "Button '" << label << "' is hovered!" << std::endl;
    
}

void Button::release() {
    std::cout << "Button '" << label << "' released!" << std::endl;
}

void Button::render(SDL_Renderer* renderer) {
    renderButtonRect(renderer);
    renderButtonLabel(renderer);
}
