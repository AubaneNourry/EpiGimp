/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Tool.cpp
*/

#include "Tool.hpp"

Tool::Tool(std::string name, std::function<void(int, int, SDL_Rect, Uint32*)> draw)
    : _name(name), _draw(draw)
{
}

void Tool::draw(const int mouseX, const int mouseY, const SDL_Rect rect, Uint32* pixels) const
{
    _draw(mouseX, mouseY, rect, pixels);
}
