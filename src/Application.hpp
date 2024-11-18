/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.hpp
*/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "WindowManager.hpp"
#include "FileManager.hpp"
#include "IUIElement.hpp"
#include "EventManager.hpp"

class Application {
public:
    int run();
    [[nodiscard]] int getScreenWidth() const;
    [[nodiscard]] int getScreenHeight() const;
    [[nodiscard]] TTF_Font *getFont() const;

    static Application &getInstance() {
        static Application app("EpiGimp", "assets/gimp_logo.jpg");
        return app;
    }
    Application(const char *appName, const char *defaultImagePath);
    void init();
    [[nodiscard]] SDL_Renderer *getRenderer() const { return renderer; }
    [[nodiscard]] SDL_Window *getWindow() const { return window; }
    void quit();
private:
    void render() const;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    int status;
    bool running;
    IUIElement* menuBar{};
    IUIElement* leftDock{};
    IUIElement* rightDock{};
    IUIElement* imageField{};
    TTF_Font* font;
};

#endif // APPLICATION_HPP
