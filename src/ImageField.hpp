/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ImageField.hpp
*/

#ifndef IMAGEFIELD_HPP
#define IMAGEFIELD_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "IUIElement.hpp"


class ImageField final : public IUIElement {
public:
    ImageField(int w, int h, SDL_Renderer* renderer);
    ~ImageField() override;

    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;
    void setTextureFromPath(const char* path) const;

    void setDimensions(int w, int h);
    [[nodiscard]] int getWidth() const { return rect.w; }
    [[nodiscard]] int getHeight() const { return rect.h; }

    void setPosition(int x, int y);
    [[nodiscard]] SDL_Texture* getTexture() const;
    void setTexture(SDL_Texture* texture);
    void updateTexture() const;

    void setPixels(Uint32* pixels);
    [[nodiscard]] Uint32* getPixels() const;

    void clear(Uint32 color = 0xFFFFFFFF) const;
    [[nodiscard]] std::pair<int, int> getPosition() const override {
        return {rect.x, rect.y};
    }
    [[nodiscard]] std::pair<int, int> getDimensions() const override {
        return {rect.w, rect.h};
    }

private:
    SDL_Rect rect{};
    SDL_Texture* texture;
    Uint32* pixels;
    int pitch{};

    bool isDrawing;
    void drawPixel(int mouseX, int mouseY) const;
};

#endif // IMAGEFIELD_HPP
