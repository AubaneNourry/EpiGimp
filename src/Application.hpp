/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.hpp
*/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "Dock.hpp"
#include "MenuBar.hpp"
#include "WindowManager.hpp"

class Application {
public:
    int run();
    int getScreenWidth();
    int getScreenHeight();

    static Application &getInstance() {
        static Application app("EpiGimp");
        return app;
    }
    
private:
    Application(const char *appName);
    void initWindow();
    void handleEvents();
    void render();
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    int status;
    MenuBar* menuBar;
    Dock* leftDock;
    Dock* rightDock;

    // Add any additional member variables for state management
};

#endif // APPLICATION_HPP
