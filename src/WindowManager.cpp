/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** WindowManager.cpp
*/

#include "WindowManager.hpp"

void WindowManager::resize_window(SDL_Window* window, int width, int height) {
    SDL_SetWindowSize(window, width, height);
}

void WindowManager::set_window_fullscreen(SDL_Window* window) {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void WindowManager::set_window_windowed(SDL_Window* window) {
    SDL_SetWindowFullscreen(window, 0);
}
