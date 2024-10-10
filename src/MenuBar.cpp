/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.cpp
*/

#include "MenuBar.hpp"
#include "Application.hpp"

MenuBar::MenuBar(int x) : rect({0, 0, x, 25})
{
    Button *button_3 = new Button("opt3", new SDL_Rect({0, 0, 0, 0}));
    Button *button_4 = new Button("opt4", new SDL_Rect({0, 0, 0, 0}));
    Button *button_5 = new Button("opt5", new SDL_Rect({0, 0, 0, 0}));
   
    init_file_menu();
    _menu_items.push_back(new DropdownButton("Edit", new SDL_Rect({100, 0, 100, 25}), 25, {button_5}));
    _menu_items.push_back(new DropdownButton("View", new SDL_Rect({200, 0, 100, 25}), 25, {button_3}));
    _menu_items.push_back(new DropdownButton("Help", new SDL_Rect({300, 0, 100, 25}), 25, {button_4}));
}

void MenuBar::init_file_menu()
{
    Button *newbtn = new Button("new", new SDL_Rect({0, 0, 0, 0}));
    newbtn->setOnClick([]() {
        FileManager::getInstance().newImageField();
    });
    Button *openbtn = new Button("open", new SDL_Rect({0, 0, 0, 0}));
    Button *savebtn = new Button("save", new SDL_Rect({0, 0, 0, 0}));
    savebtn->setOnClick([]() {
        FileManager::getInstance().saveImage();
    });
    Button *closebtn = new Button("close", new SDL_Rect({0, 0, 0, 0}));
    Button *quitbtn = new Button("quit", new SDL_Rect({0, 0, 0, 0}));
    _menu_items.push_back(new DropdownButton("File", new SDL_Rect({0, 0, 100, 25}), 25, {newbtn, openbtn, savebtn, closebtn, quitbtn}));
}

void MenuBar::init_edit_menu()
{
}

void MenuBar::init_select_menu()
{
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
