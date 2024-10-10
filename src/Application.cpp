/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "Dock.hpp"
#include "MenuBar.hpp"
#include "ImageField.hpp"

Application::Application(const char *appName, const char *defaultImagePath) {
    window = SDL_CreateWindow(appName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    status = 0;

    menuBar = new MenuBar(800);
    leftDock = new Dock(200, {}, LEFT);
    rightDock = new Dock(200, {}, RIGHT);

    imageField = new ImageField(200, 200, FileManager::getInstance().loadTexture(defaultImagePath, renderer));

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
            static_cast<Dock*>(leftDock)->maintainRatio(renderer);
            static_cast<Dock*>(rightDock)->maintainRatio(renderer);
        }
        menuBar->handleEvent(event);
        leftDock->handleEvent(event);
        rightDock->handleEvent(event);
        imageField->handleEvent(event);
    }
}

void Application::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    imageField->render(renderer);
    
    leftDock->render(renderer);
    rightDock->render(renderer);

    menuBar->render(renderer);
    SDL_RenderPresent(renderer);
}
