/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Shortcuts.cpp
*/

#include "Shortcuts.hpp"
#include "EventManager.hpp"

void Shortcuts::registerShortcut(Shortcut *shortcut) {
    _shortcuts.push_back(shortcut);
}

void Shortcuts::unregisterShortcut(Shortcut *shortcut) {
    _shortcuts.erase(std::remove(_shortcuts.begin(), _shortcuts.end(), shortcut), _shortcuts.end());
}

void Shortcuts::registerShortcut(const std::string& name, const std::string& description, const std::function<void()>& callback, const std::vector<std::vector<SDL_Keycode>>& keys) {
    _shortcuts.push_back(new Shortcut(name, description, callback, keys));
}

void Shortcuts::unregisterShortcut(const std::string& name) {
    for (const auto& shortcut : _shortcuts) {
        if (shortcut->getName() == name) {
            _shortcuts.erase(std::remove(_shortcuts.begin(), _shortcuts.end(), shortcut), _shortcuts.end());
            return;
        }
    }
}

void Shortcuts::addKeyToShortcut(const std::string& name, const std::vector<SDL_Keycode>& key) {
    for (const auto& shortcut : _shortcuts) {
        if (shortcut->getName() == name) {
            shortcut->addKey(key);
            return;
        }
    }
}

void Shortcuts::removeKeyFromShortcut(const std::string& name, const std::vector<SDL_Keycode>& key) {
    for (const auto& shortcut : _shortcuts) {
        if (shortcut->getName() == name) {
            shortcut->removeKey(key);
            return;
        }
    }
}

void Shortcuts::handleEvents(const std::vector<SDL_Keycode>& keysPressed) {
    for (const auto& shortcut : _shortcuts) {
        shortcut->handleEvent(keysPressed);
    }
}

Shortcuts& Shortcuts::getInstance() {
    static Shortcuts instance;
    return instance;
}

void Shortcuts::registerBaseShortcuts() {
    _shortcuts.push_back(new Shortcut("Quit", "Quit the application", []() {
        EventManager::getInstance().setQuitStatus(true);
    }, {{SDLK_LCTRL, SDLK_q}, {SDLK_ESCAPE}}));
}
