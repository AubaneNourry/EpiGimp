/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Shortcuts.cpp
*/

#include "Shortcuts.hpp"
#include "EventManager.hpp"
#include "../image/Tools.hpp"

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

void Shortcuts::handleEvents(std::vector<SDL_Keycode>* keysPressed) {
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
    _shortcuts.push_back(new Shortcut("Red", "Pencil goes red", []() {
        Tools::getInstance().setColor(0xFF0000FF);
    }, {{SDLK_LCTRL, SDLK_r}}));
    _shortcuts.push_back(new Shortcut("Green", "Pencil goes green", []() {
        Tools::getInstance().setColor(0x00FF00FF);
    }, {{SDLK_LCTRL, SDLK_g}}));
    _shortcuts.push_back(new Shortcut("Blue", "Pencil goes blue", []() {
        Tools::getInstance().setColor(0x00FF00);
    }, {{SDLK_LCTRL, SDLK_b}}));
    _shortcuts.push_back(new Shortcut("Black", "Pencil goes black", []() {
        Tools::getInstance().setColor(0x000000FF);
    }, {{SDLK_LCTRL, SDLK_k}}));
    _shortcuts.push_back(new Shortcut("White", "Pencil goes white", []() {
        Tools::getInstance().setColor(0xFFFFFFFF);
    }, {{SDLK_LCTRL, SDLK_w}}));
    _shortcuts.push_back(new Shortcut("Orange", "Pencil goes slightly transparent orange", []() {
        Tools::getInstance().setColor(0xFFA50080); // ARGB: Alpha 50%, Orange
    }, {{SDLK_LCTRL, SDLK_o}}));
    _shortcuts.push_back(new Shortcut("Size+", "Increase pencil size", []() {
        std::cout << "Size+" << std::endl;
        Tools::getInstance().setSize(Tools::getInstance().getSize() + 1 > 100 ? 100 : Tools::getInstance().getSize() + 1);
    }, {{SDLK_LSHIFT, SDLK_1}}));
    _shortcuts.push_back(new Shortcut("Size-", "Decrease pencil size", []() {
        std::cout << "Size-" << std::endl;
        Tools::getInstance().setSize(Tools::getInstance().getSize() - 1 < 1 ? 1 : Tools::getInstance().getSize() - 1);
    }, {{SDLK_LSHIFT, SDLK_2}}));
    _shortcuts.push_back(new Shortcut("Next Tool", "Change to next tool", []() {
        Tools::getInstance().next();
    }, {{SDLK_SPACE}}));
}
