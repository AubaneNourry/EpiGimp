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
  void registerShortcut(const std::string& name, const std::string& description, const std::function<void()>& callback, const std::vector<std::
                        vector<SDL_Keycode>>& keys);
  void unregisterShortcut(const std::string& name);
  void addKeyToShortcut(const std::string& name, const std::vector<SDL_Keycode>& key);
  void removeKeyFromShortcut(const std::string& name, const std::vector<SDL_Keycode>& key);
  void handleEvents(const std::vector<SDL_Keycode>& keysPressed);

  void registerBaseShortcuts();

  static Shortcuts& getInstance();

private:
  Shortcuts() = default;
  ~Shortcuts() = default;
  std::vector<Shortcut *> _shortcuts;
};

#endif // SHORTCUTS_HPP