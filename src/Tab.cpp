/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Tab.cpp
*/

#include "Tab.hpp"

#include <utility>

Tab::Tab(std::string tab_name, const std::string& icon_path, const bool is_removable, const std::vector<IUIElement*>& tab_content)
    : name(std::move(tab_name)), removable(is_removable)
{
    icon = FileManager::loadTexture(icon_path);
    content = tab_content;
}

std::string Tab::get_name() const
{
    return name;
}

SDL_Texture* Tab::get_icon() const
{
    return icon;
}

bool Tab::is_removable() const
{
    return removable;
}

std::vector<IUIElement*> Tab::get_content() const
{
    return content;
}

void Tab::set_name(const std::string& new_name)
{
    name = new_name;
}

void Tab::set_content(const std::vector<IUIElement*>& new_content)
{
    content = new_content;
}

void Tab::set_removable(const bool is_removable)
{
    removable = is_removable;
}

void Tab::render(SDL_Renderer* renderer)
{
    constexpr SDL_Rect tabRect = {0, 0, 200, 25};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &tabRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &tabRect);
    SDL_RenderCopy(renderer, icon, nullptr, &tabRect);

    for (const auto& element : content) {
        element->render(renderer);
    }
}

void Tab::add_content(IUIElement* new_content)
{
    content.push_back(new_content);
}

