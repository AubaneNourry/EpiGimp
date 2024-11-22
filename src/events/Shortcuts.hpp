/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Shortcuts.hpp
*/

#ifndef SHORTCUTS_HPP
#define SHORTCUTS_HPP

#include <vector>
#include <algorithm>
#include "Shortcut.hpp"

class Shortcuts {
public:
  void registerShortcut(Shortcut *shortcut);
  void unregisterShortcut(Shortcut *shortcut);
  void registerShortcut(std::string name, std::string description, std::function<void()> callback, std::vector<std::vector<SDL_Keycode>> keys);
  void unregisterShortcut(std::string name);
  void addKeyToShortcut(std::string name, std::vector<SDL_Keycode> key);
  void removeKeyFromShortcut(std::string name, std::vector<SDL_Keycode> key);
  void handleEvents(std::vector<SDL_Keycode> keysPressed);

  void registerBaseShortcuts();

  static Shortcuts& getInstance();

private:
  Shortcuts() = default;
  ~Shortcuts() = default;
  std::vector<Shortcut *> _shortcuts;
};

#endif // SHORTCUTS_HPP