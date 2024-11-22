/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Shortcut.cpp
*/

#include "Shortcut.hpp"

#include <utility>

Shortcut::Shortcut(std::string name, std::string description, std::function<void()> callback, std::vector<std::vector<SDL_Keycode>> keys)
    : _name(std::move(name)), _description(std::move(description)), _callback(std::move(callback)), _keys(std::move(keys))
{
}

void Shortcut::addKey(const std::vector<SDL_Keycode>& key)
{
    _keys.push_back(key);
}

void Shortcut::removeKey(const std::vector<SDL_Keycode>& key)
{
    _keys.erase(std::remove(_keys.begin(), _keys.end(), key), _keys.end());
}

void Shortcut::setKeys(const std::vector<std::vector<SDL_Keycode>>& keys)
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
