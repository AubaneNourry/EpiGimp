/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** IButton.hpp
*/

#ifndef IBUTTON_HPP
#define IBUTTON_HPP

#include <string>
#include <SDL2/SDL.h>

class IButton {
public:
    virtual ~IButton() = default;

    virtual void click() = 0;         // Handle button click
    virtual void hover() = 0;         // Handle button hover
    virtual void release() = 0;       // Handle button release
    virtual void render(SDL_Renderer* renderer) = 0; // Render button
    virtual void handleEvent(const SDL_Event& event) = 0; // Handle SDL events
    virtual void setPosition(int x, int y) = 0; // Set button position
    virtual void setDimensions(int width, int height) = 0; // Set button dimensions
};

#endif // IBUTTON_HPP
