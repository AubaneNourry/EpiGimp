/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** EventManager.hpp
*/

#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "IUIElement.hpp"

class EventManager {
public:
    EventManager() = default;
    ~EventManager() = default;

    void registerElement(IUIElement* element);
    void unregisterElement(IUIElement* element);
    void handleEvents();
    bool getQuitStatus() const;

private:
    std::vector<IUIElement*> elements;
    bool shouldQuit = false;
};

#endif // EVENTMANAGER_HPP
