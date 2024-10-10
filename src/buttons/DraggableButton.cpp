/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DraggableButton.cpp
*/

#include "DraggableButton.hpp"

DraggableButton::DraggableButton(int x, int y, int width, int height, TTF_Font* font, SDL_Color color, Axis axis)
    : AButton("", x, y, width, height, font, color), isDragging(false), axis(axis) {
        setCallbacks();
    }

void DraggableButton::setCallbacks() {
    onClick = [this]() {
        isClicked = !isClicked;
        isDragging = true;
        offset = 0;
    };
}

void DraggableButton::handleEvent(const SDL_Event& event) {
    AButton::handleEvent(event);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (event.type == SDL_MOUSEBUTTONUP && isDragging) {
        isDragging = false;
    } else if (event.type == SDL_MOUSEMOTION && isDragging) {
        if (axis == Axis::X) {
            rect->x = mouseX;
        } else if (axis == Axis::Y) {
            rect->y = mouseY;
        }
    }
}

void DraggableButton::click() {
    isDragging = true;
}

void DraggableButton::render(SDL_Renderer* renderer) {
    renderButtonRect(renderer);
}
