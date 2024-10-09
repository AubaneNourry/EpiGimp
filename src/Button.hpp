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
    Button(const std::string& label, int x, int y, int width, int height, TTF_Font* font, SDL_Color color)
        : AButton(label, x, y, width, height, font, color) {
    }

    void click() override {
        std::cout << "Button '" << label << "' clicked!" << std::endl;
    }

    void hover() override {
        std::cout << "Button '" << label << "' is hovered!" << std::endl;
    }

    void release() override {
        std::cout << "Button '" << label << "' released!" << std::endl;
    }

    void render(SDL_Renderer* renderer) override {
        renderButtonRect(renderer);
        renderButtonLabel(renderer);
    }
};

#endif // BUTTON_HPP
