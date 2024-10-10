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
    DraggableButton(int x, int y, int width, int height, SDL_Color color, Axis axis);
    void click();
    void stopDragging();
    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;
    void setAxis(Axis axis);
    Axis getAxis();
    void setCallbacks();

private:
    bool isDragging;
    int offset;
    Axis axis;

    bool isInsideButton(int mouseX, int mouseY);
};

#endif // DRAGGABLEBUTTON_HPP
