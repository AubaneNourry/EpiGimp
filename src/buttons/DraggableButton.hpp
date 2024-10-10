/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DraggableButton.hpp
*/

#ifndef DRAGGABLEBUTTON_HPP
#define DRAGGABLEBUTTON_HPP

#include "AButton.hpp"
#include <iostream>
#include <SDL2/SDL.h>

enum Axis {
    X,
    Y
};

class DraggableButton : public AButton {
public:
    DraggableButton(int x, int y, int width, int height, TTF_Font* font, SDL_Color color, Axis axis);
    void click() override;
    void hover() override;
    void release() override;
    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;
    void setPosition(int x, int y) override;
    void setDimensions(int width, int height) override;
    void setAxis(Axis axis);
    Axis getAxis();

private:
    bool isDragging;
    int offset;
    Axis axis;

    bool isInsideButton(int mouseX, int mouseY);
};

#endif // DRAGGABLEBUTTON_HPP
