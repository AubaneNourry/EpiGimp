/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "tabs/Dock.hpp"
#include "MenuBar.hpp"
#include "ImageField.hpp"

Application::Application(const char *appName, const char *defaultImagePath) {
    window = SDL_CreateWindow(appName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    status = 0;

    std::string fontStr;
    #ifdef _WIN32
        fontStr = "C:\\Windows\\Fonts\\arial.ttf";
    #elif defined(__linux__)
        fontStr = "/usr/share/fonts/liberation-sans/LiberationSans-Regular.ttf";
    #else
        return;
    #endif

    font = TTF_OpenFont(fontStr.c_str(), 24);
    if (font == NULL) {
        fprintf(stderr, "error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    running = true;
}

int Application::run() {
    while (status == 0 && !EventManager::getInstance().getQuitStatus() && running) {
        EventManager::getInstance().handleEvents();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return status;
}

void Application::init() {
    menuBar = new MenuBar(800);
    leftDock = new Dock(200, {}, LEFT);
    const auto dockLeft = dynamic_cast<Dock *>(leftDock);
    dockLeft->add_tab(new ToolTab("Tools", "assets/icons/brush.png", false, leftDock));

    rightDock = new Dock(200, {}, RIGHT);
    imageField = new ImageField(200, 200, renderer);
    FileManager::getInstance().setImageField(imageField);
    EventManager::getInstance().registerElement(menuBar);
    EventManager::getInstance().registerElement(leftDock);
    EventManager::getInstance().registerElement(rightDock);
    EventManager::getInstance().registerElement(imageField);
}

void Application::render() const
{
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    SDL_RenderClear(renderer);

    imageField->render(renderer);
    leftDock->render(renderer);
    rightDock->render(renderer);
    menuBar->render(renderer);

    SDL_RenderPresent(renderer);
}

int Application::getScreenWidth() const
{
    int width;
    SDL_GetRendererOutputSize(renderer, &width, nullptr);
    return width;
}

int Application::getScreenHeight() const
{
    int height;
    SDL_GetRendererOutputSize(renderer, nullptr, &height);
    return height;
}

TTF_Font *Application::getFont() const
{
    return font;
}

void Application::quit() {
    running = false;
}
