/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Main.cpp
*/

#include "Application.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return 1;
    }
    Application *app = &Application::getInstance();
    app->init();
    return app->run();
}
