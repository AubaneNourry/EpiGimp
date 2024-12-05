/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** EventManager.cpp
*/

#include "EventManager.hpp"
#include "Shortcuts.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "../Application.hpp"

void EventManager::registerElement(IUIElement* element) {
    elements.push_back(element);
}

void EventManager::unregisterElement(IUIElement* element) {
    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
}

void EventManager::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            shouldQuit = true;
            return;
        }
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(Application::getInstance().getWindow())) {
            shouldQuit = true;
            return;
        }
        if (SDL_GetWindowFlags(Application::getInstance().getWindow()) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (std::find(_keysPressed.begin(), _keysPressed.end(), event.key.keysym.sym) == _keysPressed.end())
            {
                _keysPressed.push_back(event.key.keysym.sym);
            }
        }
        if (event.type == SDL_KEYUP)
        {
            _keysPressed.erase(std::remove(_keysPressed.begin(), _keysPressed.end(), event.key.keysym.sym), _keysPressed.end());
        }
        Shortcuts::getInstance().handleEvents(&_keysPressed);
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

void EventManager::setQuitStatus(bool status) {
    shouldQuit = status;
}