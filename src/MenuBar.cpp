/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.cpp
*/

#include "MenuBar.hpp"

MenuBar::MenuBar()
{
    std::string fontStr;
    #ifdef _WIN32
        fontStr = "C:\\Windows\\Fonts\\arial.ttf";
    #elif defined(__linux__)
        fontStr = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    #else
        return;
    #endif

    TTF_Font* font = TTF_OpenFont(fontStr.c_str(), 24);
    if (font == NULL) {
        fprintf(stderr, "error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    Button *button_1 = new Button("opt1", 0, 0, 0, 0, font, {200, 200, 200, 255});
    Button *button_2 = new Button("opt2", 0, 0, 0, 0, font, {200, 200, 200, 255});
    Button *button_3 = new Button("opt3", 0, 0, 0, 0, font, {200, 200, 200, 255});
    Button *button_4 = new Button("opt4", 0, 0, 0, 0, font, {200, 200, 200, 255});
    Button *button_5 = new Button("opt5", 0, 0, 0, 0, font, {200, 200, 200, 255});
    _menu_items.push_back(new DropdownButton("File", 0, 0, 100, 50, 50, {button_1, button_5}, font, {150, 150, 150, 255}));
    _menu_items.push_back(new DropdownButton("Edit", 100, 0, 100, 50, 50, {button_2}, font, {150, 150, 150, 255}));
    _menu_items.push_back(new DropdownButton("View", 200, 0, 100, 50, 50, {button_3}, font, {150, 150, 150, 255}));
    _menu_items.push_back(new DropdownButton("Help", 300, 0, 100, 50, 50, {button_4}, font, {150, 150, 150, 255}));
}

void MenuBar::render(SDL_Renderer* renderer)
{
    for (auto& item : _menu_items) {
        item->render(renderer);
    }
}
