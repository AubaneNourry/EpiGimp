/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Button.hpp
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "AButton.hpp"
#include <iostream>

class Button : public AButton {
public:
    Button(const std::string& label, int x, int y, int width, int height, TTF_Font* font, SDL_Color color);

    void click() override;
    void hover() override;
    void release() override;
    void render(SDL_Renderer* renderer) override;
};

#endif // BUTTON_HPP
