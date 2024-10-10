/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DraggableButton.cpp
*/

#include "DraggableButton.hpp"

DraggableButton::DraggableButton(int x, int y, int width, int height, TTF_Font* font, SDL_Color color, Axis axis)
    : AButton("", x, y, width, height, font, color), isDragging(false), axis(axis) {}

void DraggableButton::click() {
    AButton::click();
    isDragging = true;
    offset = 0;
    std::cout << "Draggable Button '" << label << "' clicked!" << " Offset: " << offset << std::endl;
}

void DraggableButton::hover() {
    AButton::hover();
    std::cout << "Draggable Button '" << label << "' is hovered!" << std::endl;
}

void DraggableButton::release() {
    AButton::release();
    std::cout << "Draggable Button '" << label << "' released!" << std::endl;
}

void DraggableButton::stopDragging() {
    isDragging = false;
    std::cout << "Draggable Button '" << label << "' stopped dragging!" << std::endl;
}

void DraggableButton::render(SDL_Renderer* renderer) {
    renderButtonRect(renderer);
}

void DraggableButton::handleEvent(const SDL_Event& event) {
    AButton::handleEvent(event);
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (isDragging) {
            stopDragging();
        }
    } 
    else if (event.type == SDL_MOUSEMOTION && isDragging) {
        if (axis == Axis::X) {
            rect.x = mouseX;
        } else if (axis == Axis::Y) {
            rect.y = mouseY;
        }
    }
}

void DraggableButton::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void DraggableButton::setDimensions(int width, int height) {
    rect.w = width;
    rect.h = height;
}

void DraggableButton::setAxis(Axis axis) {
    this->axis = axis;
}

Axis DraggableButton::getAxis() {
    return axis;
}

bool DraggableButton::isInsideButton(int mouseX, int mouseY) {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
}
