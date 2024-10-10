/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.hpp
*/

#ifndef MENU_BAR_HPP
#define MENU_BAR_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "buttons/DropdownButton.hpp"
#include "buttons/Button.hpp"
#include "IUIElement.hpp"

class MenuBar : public IUIElement {
public:
    MenuBar(int x);
    ~MenuBar() = default;
    
    void init_file_menu();
    void init_edit_menu();
    void init_select_menu();
    void init_view_menu();
    void init_image_menu();
    void init_layer_menu();
    void init_color_menu();
    void init_tool_menu();
    void init_filter_menu();
    void init_window_menu();
    void init_help_menu();

    void render(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event) {
        for (auto& item : _menu_items) {
            item->handleEvent(event);
        }
    }

private:
    std::vector<DropdownButton *> _menu_items;
    SDL_Rect rect;
};

#endif // MENU_BAR_HPP
