/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** WindowManager.hpp
*/

#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <SDL2/SDL.h>

class WindowManager {
public:
    static void resize_window(SDL_Window* window, int width, int height);
    static void set_window_fullscreen(SDL_Window* window);
    static void set_window_windowed(SDL_Window* window);
};

#endif // WINDOW_MANAGER_HPP
