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

Application::Application(const char *appName, const char *defaultImagePath)
    : eventManager(new EventManager()) { // Initialize EventManager
    window = SDL_CreateWindow(appName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    status = 0;

    menuBar = new MenuBar(800);
    leftDock = new Dock(200, {}, LEFT);
    rightDock = new Dock(200, {}, RIGHT);
    imageField = new ImageField(200, 200, FileManager::getInstance().loadTexture(defaultImagePath, renderer));

    eventManager->registerElement(menuBar);
    eventManager->registerElement(leftDock);
    eventManager->registerElement(rightDock);
    eventManager->registerElement(imageField);
}

int Application::run() {
    while (status == 0 && !eventManager->getQuitStatus()) {
        eventManager->handleEvents();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return status;
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
