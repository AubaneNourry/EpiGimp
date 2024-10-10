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

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

int EventManager::registerListener(const std::string& eventName, const EventConsumer& listener) {
    if (_listeners.find(eventName) == _listeners.end()) {
        _listeners[eventName] = std::vector<std::pair<int, EventConsumer>>();
    }
    int id = _listeners[eventName].size();
    _listeners[eventName].emplace_back(id, listener);
    return id;
}

bool EventManager::unregisterListener(const int& listenerId) {
    for (auto& [eventName, listeners] : _listeners) {
        auto it = std::remove_if(listeners.begin(), listeners.end(),
                                 [listenerId](const std::pair<int, EventConsumer>& listenerPair) {
                                     return listenerPair.first == listenerId;
                                 });
        if (it != listeners.end()) {
            listeners.erase(it, listeners.end());
            return true;
        }
    }
    return false;
}

bool EventManager::triggerEvent(const std::string& eventName, const EventData& data) {
    return _triggerEventFromEventName(eventName, data);
}

bool EventManager::_triggerEventFromEventName(const std::string& eventName, const EventData& eventData) {
    if (_listeners.find(eventName) == _listeners.end()) {
        return false;
    }
    for (auto& [id, listener] : _listeners[eventName]) {
        listener(eventData);
    }
    return true;
}
