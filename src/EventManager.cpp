/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** EventManager.cpp
*/

#include "EventManager.hpp"

void EventManager::registerElement(IUIElement* element) {
    elements.push_back(element);
}

void EventManager::unregisterElement(IUIElement* element) {
    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
}

void EventManager::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            shouldQuit = true;
            return;
        }
        for (auto& element : elements) {
            element->handleEvent(event);
        }
    }
}

bool EventManager::getQuitStatus() const {
    return shouldQuit;
}
