/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ImageField.hpp
*/

#ifndef IMAGEFIELD_HPP
#define IMAGEFIELD_HPP

#include <SDL2/SDL.h>
#include <SDL_image.h>

class ImageField {
public:
    ImageField(int w, int h, SDL_Texture* texture)
        : w(w), h(h), texture(texture) {}

    void render(SDL_Renderer* renderer) {
        int windowWidth, windowHeight;
        SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
        SDL_Rect rect = { windowWidth / 2 - w / 2, windowHeight / 2 - h / 2, w, h };
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void handleEvent(const SDL_Event& event) {
        // Handle events for the image field
    }

    void setTexture(SDL_Texture* newTexture) {
        texture = newTexture;
    }

    void setTextureFromPath(const char* path, SDL_Renderer* renderer) {
        SDL_Surface* surface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

private:
    int w;
    int h;
    SDL_Texture* texture;
};

#endif // IMAGEFIELD_HPP