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


class ImageField : public IUIElement {
public:
    ImageField(int w, int h, SDL_Renderer* renderer);
    ~ImageField();

    void render(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event);
    void setTextureFromPath(const char* path, SDL_Renderer* renderer);

    void setDimensions(int w, int h);
    int getWidth() const { return rect.w; }
    int getHeight() const { return rect.h; }

    void setPosition(int x, int y);
    SDL_Texture* getTexture();
    void setTexture(SDL_Texture* texture);
    void updateTexture(SDL_Renderer* renderer) const;

    void setPixels(Uint32* pixels);
    Uint32* getPixels();

    void clear(Uint32 color = 0xFFFFFFFF);

private:
    SDL_Rect rect;       // SDL_Rect to store position and size
    SDL_Texture* texture;
    Uint32* pixels;      // Pixel buffer to hold texture data
    int pitch;           // Pitch of the texture

    bool isDrawing;      // Tracks if the mouse button is being pressed
    void drawPixel(int mouseX, int mouseY);
};

#endif // IMAGEFIELD_HPP
