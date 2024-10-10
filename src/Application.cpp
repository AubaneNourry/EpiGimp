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

    menuBar = new MenuBar(800);
    leftDock = new Dock(200, {}, LEFT, { 175, 175, 175, 255 });
    rightDock = new Dock(200, {}, RIGHT, { 175, 175, 175, 255 });

    imageField = new ImageField(200, 200, nullptr);
    imageField->setTextureFromPath("assets/gimp_logo.jpg", renderer);
}

int Application::getScreenWidth() {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    return windowWidth;
}

int Application::getScreenHeight() {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    return windowHeight;
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
            status = 1;
        } if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            leftDock->maintainRatio(renderer);
            rightDock->maintainRatio(renderer);
        }
        menuBar->handleEvent(event);
        leftDock->handleEvent(event);
        rightDock->handleEvent(event);
        imageField->handleEvent(event);
    }
}

void Application::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set draw color to white
    SDL_RenderClear(renderer);

    imageField->render(renderer);
    
    leftDock->render(renderer);
    rightDock->render(renderer);

    menuBar->render(renderer);
    SDL_RenderPresent(renderer);
}
