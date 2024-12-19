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
#include "../IUIElement.hpp"

class Tools : public IUIElement {
public:
    Tools();
    ~Tools() = default;
    void draw(int mouseX, int mouseY, SDL_Rect rect, Uint32* pixels) const;

    void addTool(Tool *tool);
    void removeTool(Tool *tool);
    void addTool(std::string name, std::function<void(int, int, SDL_Rect, Uint32*)> draw);
    void removeTool(std::string name);

    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override { return; }

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
    Uint32 _color = 0x000000FF; // Black
    unsigned int _currentToolIndex = 0;
    unsigned int _size = 1;
    std::vector<Tool *> _tools;
    float rgba[4] = {0.0f, 0.0f, 0.0f, 1.0f};
};

#endif // TOOLS_HPP
