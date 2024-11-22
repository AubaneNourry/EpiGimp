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
    SDL_Rect btnRect = {getPosition().first, getPosition().second, getDimensions().first / 2, getDimensions().second / 3};
    std::cout << "button dimensions: " << btnRect.w << " " << btnRect.h << std::endl;
    std::cout << "button position: " << btnRect.x << " " << btnRect.y << std::endl;
    SDL_Texture *icon = FileManager::loadTexture("assets/icons/brush.png");
    Button *button = new Button("test", &btnRect, {255, 0, 0, 255}, icon, false);
    content.push_back(button);
}

void ToolTab::render(SDL_Renderer *renderer)
{
    SDL_Rect tabRect = {getPosition().first, getPosition().second, getDimensions().first, getDimensions().second / 3};
    //SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    //SDL_RenderFillRect(renderer, &tabRect);
    for (auto &element : content) {
        //std::cout << "rendering element in: " << getPosition().first << " " << getPosition().second << " size: " << getDimensions().first << " " << getDimensions().second << std::endl;
        element->render(renderer);
    }
}

void ToolTab::handleEvent(const SDL_Event &event)
{
    (void)event;
}
