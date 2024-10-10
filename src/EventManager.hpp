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
#include <unordered_map>
#include <functional>
#include <ctime>
#include <iostream>
#include "IUIElement.hpp"

class EventData {
public:
    std::string name;
    time_t timestamp;
    void* data;
};

using EventConsumer = std::function<void(const EventData&)>;

class EventManager {
public:
    int registerListener(const std::string& eventName, const EventConsumer& listener);
    bool unregisterListener(const int& listenerId);
    bool triggerEvent(const std::string& eventName, const EventData& data);

    void registerElement(IUIElement* element);
    void unregisterElement(IUIElement* element);
    void handleEvents();
    bool getQuitStatus() const;

    static EventManager& getInstance();

private:
    EventManager() = default;
    ~EventManager() = default;
    std::vector<IUIElement*> elements;
    bool shouldQuit = false;

    bool _triggerEventFromEventName(const std::string& eventName, const EventData& eventData);
    std::unordered_map<std::string, std::vector<std::pair<int, EventConsumer>>> _listeners;
};

#endif // EVENTMANAGER_HPP
