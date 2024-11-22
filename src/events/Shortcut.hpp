/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Shortcut.hpp
*/

#ifndef SHORTCUT_HPP
#define SHORTCUT_HPP

#include <functional>
#include <vector>
#include <string>
#include <algorithm>
#include <SDL2/SDL.h>

class Shortcut {
public:
    Shortcut(std::string name, std::string description, std::function<void()> callback, std::vector<std::vector<SDL_Keycode>> keys);
    ~Shortcut() = default;

    [[nodiscard]] std::string getName() const { return _name; }
    [[nodiscard]] std::string getDescription() const { return _description; }
    [[nodiscard]] std::vector<std::vector<SDL_Keycode>> getKeys() const { return _keys; }
    void addKey(const std::vector<SDL_Keycode>& key);
    void removeKey(const std::vector<SDL_Keycode>& key);
    void setKeys(const std::vector<std::vector<SDL_Keycode>>& keys);

    void handleEvent(std::vector<SDL_Keycode>* keysPressed);
private:
    std::string _name;
    std::string _description;
    std::function<void()> _callback;
    std::vector<std::vector<SDL_Keycode>> _keys;
};

#endif // SHORTCUT_HPP