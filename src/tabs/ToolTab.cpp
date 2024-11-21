/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ToolTab.cpp
*/

#include "ToolTab.hpp"
#include "../buttons/Button.hpp"

ToolTab::ToolTab(std::string tab_name, const std::string &icon_path, bool is_removable, IUIElement *owner, const std::vector<IUIElement *> &tab_content)
    : ATab(std::move(tab_name), icon_path, is_removable, owner, tab_content)
{
    SDL_Rect tabRect = {getPosition().first, getPosition().second, getDimensions().first, getDimensions().second / 3};
    Button *button = new Button("test", &tabRect, {255, 255, 255, 255}, false);
    content.push_back(button);
}

void ToolTab::render(SDL_Renderer *renderer)
{
    SDL_Rect tabRect = {getPosition().first, getPosition().second, getDimensions().first, getDimensions().second / 3};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &tabRect);
    SDL_RenderCopy(renderer, get_icon(), nullptr, &tabRect);
}

void ToolTab::handleEvent(const SDL_Event &event)
{
    (void)event;
}
