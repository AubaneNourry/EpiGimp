/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Tools.hpp
*/

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "Tool.hpp"

class Tools {
public:
    static Tools& getInstance();
    void draw(int mouseX, int mouseY, SDL_Rect rect, Uint32* pixels) const;

    void addTool(Tool *tool);
    void removeTool(Tool *tool);
    void addTool(std::string name, std::function<void(int, int, SDL_Rect, Uint32*)> draw);
    void removeTool(std::string name);

    void next();
    void previous();

    void init();

    [[nodiscard]] Uint32 getColor() const { return _color; }
    void setColor(const Uint32 color) { _color = color; }
    [[nodiscard]] unsigned int getCurrentToolIndex() const { return _currentToolIndex; }
    void setCurrentToolIndex(const unsigned int index) { _currentToolIndex = index; }
    [[nodiscard]] unsigned int getSize() const { return _size; }
    void setSize(const unsigned int size) { _size = size; }

private:
    Tools() = default;
    ~Tools() = default;
    Uint32 _color;
    unsigned int _currentToolIndex = 0;
    unsigned int _size = 1;
    std::vector<Tool *> _tools;
};

#endif // TOOLS_HPP
