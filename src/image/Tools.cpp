/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Tools.cpp
*/

#include "Tools.hpp"
#include <queue>

Tools::Tools()
{
    init();
}

void Tools::draw(const int mouseX, const int mouseY, const SDL_Rect rect, Uint32* pixels) const
{
    _tools[_currentToolIndex]->draw(mouseX, mouseY, rect, pixels);
}

void Tools::addTool(Tool *tool)
{
    _tools.push_back(tool);
}

void Tools::removeTool(Tool *tool)
{
    _tools.erase(std::remove(_tools.begin(), _tools.end(), tool), _tools.end());
}

void Tools::addTool(std::string name, std::function<void(int, int, SDL_Rect, Uint32*)> draw)
{
    _tools.push_back(new Tool(name, draw));
}

void Tools::removeTool(std::string name)
{
    for (auto &tool : _tools) {
        if (tool->getName() == name) {
            _tools.erase(std::remove(_tools.begin(), _tools.end(), tool), _tools.end());
            return;
        }
    }
}

void Tools::init()
{
    _color = 0x000000FF;
    _currentToolIndex = 0;
    _size = 1;
    addTool("Pencil", [this](int mouseX, int mouseY, SDL_Rect rect, Uint32* pixels) {
        if (mouseX >= rect.x && mouseX < rect.x + rect.w &&
        mouseY >= rect.y && mouseY < rect.y + rect.h) {
        const int color = this->getColor();
        const int startX = mouseX - rect.x;
        const int startY = mouseY - rect.y;
        for (int y = 0; y < this->getSize(); ++y) {
            for (int x = 0; x < this->getSize(); ++x) {
                int pixelX = startX + x;
                int pixelY = startY + y;
                if (pixelX >= 0 && pixelX < rect.w && pixelY >= 0 && pixelY < rect.h) {
                    pixels[pixelY * rect.w + pixelX] = color;
                }
            }
        }
    }});
    addTool("Paint Bucket", [this](int mouseX, int mouseY, SDL_Rect rect, Uint32* pixels) {
        if (mouseX < rect.x || mouseX >= rect.x + rect.w ||
            mouseY < rect.y || mouseY >= rect.y + rect.h) {
            return;
        }

        const int startX = mouseX - rect.x;
        const int startY = mouseY - rect.y;

        const int targetColor = pixels[startY * rect.w + startX];
        const int fillColor = this->getColor();

        if (targetColor == fillColor) {
             return;
        }

        std::queue<std::pair<int, int>> toFill;
        toFill.push({startX, startY});

        while (!toFill.empty()) {
            auto [x, y] = toFill.front();
            toFill.pop();

            if (x < 0 || x >= rect.w || y < 0 || y >= rect.h) continue;
            if (pixels[y * rect.w + x] != targetColor) continue;

            pixels[y * rect.w + x] = fillColor;

            toFill.push({x + 1, y});
            toFill.push({x - 1, y});
            toFill.push({x, y + 1});
            toFill.push({x, y - 1});
        }
    });
    addTool("Eraser", [this](int mouseX, int mouseY, SDL_Rect rect, Uint32* pixels) {
        if (mouseX >= rect.x && mouseX < rect.x + rect.w &&
        mouseY >= rect.y && mouseY < rect.y + rect.h) {
        const int color = this->getColor();
        const int startX = mouseX - rect.x;
        const int startY = mouseY - rect.y;
        for (int y = 0; y < this->getSize(); ++y) {
            for (int x = 0; x < this->getSize(); ++x) {
                int pixelX = startX + x;
                int pixelY = startY + y;
                if (pixelX >= 0 && pixelX < rect.w && pixelY >= 0 && pixelY < rect.h) {
                    pixels[pixelY * rect.w + pixelX] = 0xFFFFFFFF;
                }
            }
        }
    }});
    addTool("Airbrush", [this](int mouseX, int mouseY, SDL_Rect rect, Uint32* pixels) {
        if (mouseX < rect.x || mouseX >= rect.x + rect.w ||
        mouseY < rect.y || mouseY >= rect.y + rect.h) {
        return;
        }
        const int color = this->getColor();
        const int size = this->getSize();
        const int radius = size / 2;
        const int centerX = mouseX - rect.x;
        const int centerY = mouseY - rect.y;

        const Uint8 r = (color >> 24) & 0xFF;
        const Uint8 g = (color >> 16) & 0xFF;
        const Uint8 b = (color >> 8) & 0xFF;
        const Uint8 a = color & 0xFF;

        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                int pixelX = centerX + x;
                int pixelY = centerY + y;

                if (pixelX >= 0 && pixelX < rect.w && pixelY >= 0 && pixelY < rect.h) {
                    float distance = std::sqrt(x * x + y * y);

                    if (distance <= radius) {
                        float fadeFactor = std::max(0.0f, 1.0f - (distance / radius));

                        fadeFactor *= static_cast<float>(std::rand()) / RAND_MAX;

                        int index = pixelY * rect.w + pixelX;
                        Uint32 existingColor = pixels[index];

                        Uint8 existingR = (existingColor >> 24) & 0xFF;
                        Uint8 existingG = (existingColor >> 16) & 0xFF;
                        Uint8 existingB = (existingColor >> 8) & 0xFF;
                        Uint8 existingA = existingColor & 0xFF;

                        Uint8 newR = static_cast<Uint8>(existingR * (1.0f - fadeFactor) + r * fadeFactor);
                        Uint8 newG = static_cast<Uint8>(existingG * (1.0f - fadeFactor) + g * fadeFactor);
                        Uint8 newB = static_cast<Uint8>(existingB * (1.0f - fadeFactor) + b * fadeFactor);
                        Uint8 newA = static_cast<Uint8>(existingA * (1.0f - fadeFactor) + a * fadeFactor);

                        pixels[index] = (newR << 24) | (newG << 16) | (newB << 8) | newA;
                    }
                }
            }
    }});
}

#include <imgui.h>

uint32_t FloatRGBAToUint32(const float rgba[4]) {
    uint32_t r = static_cast<uint32_t>(rgba[0] * 255.0f) & 0xFF;
    uint32_t g = static_cast<uint32_t>(rgba[1] * 255.0f) & 0xFF;
    uint32_t b = static_cast<uint32_t>(rgba[2] * 255.0f) & 0xFF;
    uint32_t a = static_cast<uint32_t>(rgba[3] * 255.0f) & 0xFF;

    return (r << 24) | (g << 16) | (b << 8) | a;
}

void Uint32ToFloatRGBA(uint32_t color, float rgba[4]) {
    rgba[0] = ((color >> 24) & 0xFF) / 255.0f; // Red
    rgba[1] = ((color >> 16) & 0xFF) / 255.0f; // Green
    rgba[2] = ((color >> 8) & 0xFF) / 255.0f;  // Blue
    rgba[3] = (color & 0xFF) / 255.0f;         // Alpha
}

void Tools::render(SDL_Renderer* renderer)
{
    ImGui::Begin("Tool Settings", nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::Text("Brush Settings");
    ImGui::ColorEdit3("Color (RGB)", rgba);
    int opacityPercentage = static_cast<int>(rgba[3] * 100.0f);
    if (ImGui::SliderInt("Opacity (%)", &opacityPercentage, 0, 100)) {
        rgba[3] = opacityPercentage / 100.0f;
    }
    _color = FloatRGBAToUint32(rgba);

    ImGui::SliderInt("Size", reinterpret_cast<int*>(&_size), 1, 100);

    ImGui::Separator();

    ImGui::Text("Tools");
    for (size_t i = 0; i < _tools.size(); ++i) {
        if (ImGui::Button(_tools[i]->getName().c_str())) {
            _currentToolIndex = i;
        }
        if ((i + 1) % 3 != 0) {
            ImGui::SameLine();
        }
    }

    ImGui::End();
}


#include <iostream>

void Tools::next()
{
    _currentToolIndex = (_currentToolIndex + 1) % _tools.size();
    std::cout << "current tool: " << _tools[_currentToolIndex]->getName() << std::endl;
}

void Tools::previous()
{
    _currentToolIndex = (_currentToolIndex - 1) % _tools.size();
    if (_currentToolIndex < 0) {
        _currentToolIndex = _tools.size() - 1;
    }
}
