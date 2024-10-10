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
    DraggableButton(int x, int y, int width, int height, TTF_Font* font, SDL_Color color, Axis axis)
        : AButton("", x, y, width, height, font, color), isDragging(false), axis(axis) {}

    void click() override {
        isDragging = true;
        offset = 0;
        color = { 100, 100, 100, 255 };
        std::cout << "Draggable Button '" << label << "' clicked!" << " Offset: " << offset << std::endl;
    }

    void hover() override {
        std::cout << "Draggable Button '" << label << "' is hovered!" << std::endl;
    }

    void release() override {
        isDragging = false;
        color = { 200, 200, 200, 255 };
        std::cout << "Draggable Button '" << label << "' released!" << std::endl;
    }

    void render(SDL_Renderer* renderer) override {
        renderButtonRect(renderer);
    }

    void handleEvent(const SDL_Event& event) override {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (event.type == SDL_MOUSEBUTTONDOWN && isInsideButton(mouseX, mouseY)) {
            click();
        } 
        else if (event.type == SDL_MOUSEBUTTONUP) {
            if (isDragging) {
                release();
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

    void setPosition(int x, int y) override {
        rect.x = x;
        rect.y = y;
    }

    void setDimensions(int width, int height) override {
        rect.w = width;
        rect.h = height;
    }

    void setAxis(Axis axis) {
        this->axis = axis;
    }

    Axis getAxis() {
        return axis;
    }

private:
    bool isDragging;
    int offset;
    Axis axis;

    bool isInsideButton(int mouseX, int mouseY) {
        return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
    }
};

#endif // DRAGGABLEBUTTON_HPP
