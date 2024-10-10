/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.cpp
*/

#include "MenuBar.hpp"

MenuBar::MenuBar(int x) : rect({0, 0, x, 25})
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
    Button *button_1 = new Button("opt1", new SDL_Rect({0, 0, 0, 0}), font, {200, 200, 200, 255});
    Button *button_2 = new Button("opt2", new SDL_Rect({0, 0, 0, 0}), font, {200, 200, 200, 255});
    Button *button_3 = new Button("opt3", new SDL_Rect({0, 0, 0, 0}), font, {200, 200, 200, 255});
    Button *button_4 = new Button("opt4", new SDL_Rect({0, 0, 0, 0}), font, {200, 200, 200, 255});
    Button *button_5 = new Button("opt5", new SDL_Rect({0, 0, 0, 0}), font, {200, 200, 200, 255});
    _menu_items.push_back(new DropdownButton("File", new SDL_Rect({0, 0, 100, 25}), 25, {button_1, button_5}, font));
    _menu_items.push_back(new DropdownButton("Edit", new SDL_Rect({100, 0, 100, 25}), 25, {button_2}, font));
    _menu_items.push_back(new DropdownButton("View", new SDL_Rect({200, 0, 100, 25}), 25, {button_3}, font));
    _menu_items.push_back(new DropdownButton("Help", new SDL_Rect({300, 0, 100, 25}), 25, {button_4}, font));
}

void MenuBar::render(SDL_Renderer* renderer)
{
    SDL_Color color = UICOLOR;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    rect.w = windowWidth;
    SDL_RenderFillRect(renderer, &rect);
    for (auto& item : _menu_items) {
        item->render(renderer);
    }
}
