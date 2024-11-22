/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Tool.hpp
*/

#ifndef TOOL_HPP
#define TOOL_HPP

#include <functional>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Tool {
public:
    Tool(std::string name, std::function<void(int, int, SDL_Rect, Uint32*)> draw);
    ~Tool() = default;

    [[nodiscard]] std::string getName() const { return _name; }
    void draw(int mouseX, int mouseY, SDL_Rect rect, Uint32* pixels) const;
private:
    std::string _name;
    std::function<void(int, int, SDL_Rect, Uint32*)> _draw;
};

#endif // TOOL_HPP
