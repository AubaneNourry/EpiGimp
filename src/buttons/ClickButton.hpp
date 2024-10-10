/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ClickButton.hpp
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "AButton.hpp"
#include <iostream>

class ClickButton : public AButton {
public:
    ClickButton(const std::string& label, SDL_Rect *rect, TTF_Font* font, SDL_Color color = UICOLOR);

    void render(SDL_Renderer* renderer) override;
    void setCallbacks();
};

#endif // BUTTON_HPP
