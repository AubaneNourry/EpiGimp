/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Shortcut.cpp
*/

#include "Shortcut.hpp"

Shortcut::Shortcut(std::string name, std::string description, std::function<void()> callback, std::vector<std::vector<SDL_Keycode>> keys)
    : _name(name), _description(description), _callback(callback), _keys(keys)
{
}

void Shortcut::addKey(std::vector<SDL_Keycode> key)
{
    _keys.push_back(key);
}

void Shortcut::removeKey(std::vector<SDL_Keycode> key)
{
    _keys.erase(std::remove(_keys.begin(), _keys.end(), key), _keys.end());
}

void Shortcut::setKeys(std::vector<std::vector<SDL_Keycode>> keys)
{
    _keys = keys;
}

void Shortcut::handleEvent(std::vector<SDL_Keycode> keysPressed)
{
    for (auto &key : _keys) {
        if (std::includes(keysPressed.begin(), keysPressed.end(), key.begin(), key.end())) {
            _callback();
        }
    }
}
