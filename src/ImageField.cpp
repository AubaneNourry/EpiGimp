/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ImageField.cpp
*/

#include "ImageField.hpp"

ImageField::ImageField(int w, int h, SDL_Texture* texture)
    : w(w), h(h), texture(texture) {}

void ImageField::render(SDL_Renderer* renderer) {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    SDL_Rect rect = { windowWidth / 2 - w / 2, windowHeight / 2 - h / 2, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void ImageField::handleEvent(const SDL_Event& event) {
    (void)event;
}

void ImageField::setTexture(SDL_Texture* newTexture) {
    texture = newTexture;
}

void ImageField::setTextureFromPath(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}
