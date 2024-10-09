/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.cpp
*/

#include "Application.hpp"

Application::Application(const char *appName) {
    window = SDL_CreateWindow(appName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    status = 0;

    menuBar = new MenuBar();
}

int Application::run() {
    while (status == 0) {
        handleEvents();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return status;
}

void Application::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            status = 1; // Set status to exit
        }
        menuBar->handleEvent(event);
        // Handle other events (e.g., keyboard, mouse)
    }
}

void Application::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set draw color to white
    SDL_RenderClear(renderer);

    // Render the menu bar
    menuBar->render(renderer);
    
    // Render the docks and menu bar here
    // e.g., leftDock->render(renderer);
    // e.g., rightDock->render(renderer);
    
    SDL_RenderPresent(renderer);
}
