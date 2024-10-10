/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** IButton.hpp
*/

#ifndef IBUTTON_HPP
#define IBUTTON_HPP

#include <string>
#include <functional> // For std::function
#include <SDL2/SDL.h>
#include "../IUIElement.hpp"
#include "../Utils.hpp"

class IButton : public IUIElement {
public:
    virtual ~IButton() = default;

    // Virtual methods to be implemented by the button classes
    virtual void setPosition(int x, int y) = 0; // Set button position
    virtual void setDimensions(int width, int height) = 0; // Set button dimensions

    // Methods to set the callback functions
    virtual void setOnClick(std::function<void()> callback) = 0;
    virtual void setOnHover(std::function<void()> callback) = 0;
    virtual void setOnRelease(std::function<void()> callback) = 0;
};

#endif // IBUTTON_HPP
