/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ATab.cpp
*/

#include "ATab.hpp"

#include <utility>

ATab::ATab(std::string tab_name, const std::string& icon_path, const bool is_removable, IUIElement *owner, const std::vector<IUIElement*>& tab_content)
    : name(std::move(tab_name)), removable(is_removable), owner(owner)
{
    icon = FileManager::loadTexture(icon_path);
    content = tab_content;
}

std::string ATab::get_name() const
{
    return name;
}

SDL_Texture* ATab::get_icon() const
{
    return icon;
}

bool ATab::is_removable() const
{
    return removable;
}

std::vector<IUIElement*> ATab::get_content() const
{
    return content;
}

void ATab::set_name(const std::string& new_name)
{
    name = new_name;
}

void ATab::set_content(const std::vector<IUIElement*>& new_content)
{
    content = new_content;
}

void ATab::set_removable(const bool is_removable)
{
    removable = is_removable;
}

void ATab::add_content(IUIElement* new_content)
{
    content.push_back(new_content);
}
