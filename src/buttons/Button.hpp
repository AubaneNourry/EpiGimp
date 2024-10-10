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
    Button(const std::string& label, SDL_Rect *rect, SDL_Color color = UICOLOR, bool toggle = false);

    void render(SDL_Renderer* renderer) override;
};

#endif // BUTTON_HPP
