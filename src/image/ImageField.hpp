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
#include "../IUIElement.hpp"


class ImageField final : public IUIElement {
public:
    ImageField(int w, int h, SDL_Renderer* renderer);
    ~ImageField() override;

    void InitializeDrawingSurface(SDL_Renderer* renderer);
    void UpdateTexture(SDL_Renderer* renderer);
    void FreeDrawingSurface();

    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;
    void setTextureFromPath(const char* path) const;
    [[nodiscard]] SDL_Texture* getTexture() const;
    void setTexture(SDL_Texture* texture);
    void updateTexture() const;

    void setPixels(Uint32* pixels);
    [[nodiscard]] Uint32* getPixels() const;

    void clear(Uint32 color = 0xFFFFFFFF) const;
    [[nodiscard]] std::pair<int, int> getPosition() const {
        return {rect.x, rect.y};
    }
    [[nodiscard]] std::pair<int, int> getDimensions() const {
        return {rect.w, rect.h};
    }
    void setDimensions(int w, int h);
    void setPosition(int x, int y);

private:
    SDL_Rect rect{};
    Uint32* pixels;
    int pitch{};
    bool isDrawing;
};

#endif // IMAGEFIELD_HPP
