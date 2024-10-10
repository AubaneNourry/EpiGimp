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
#include "IUIElement.hpp"

class ImageField : public IUIElement {
public:
    ImageField(int w, int h, SDL_Texture* texture);

    void render(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event);
    void setTexture(SDL_Texture* newTexture);
    void setTextureFromPath(const char* path, SDL_Renderer* renderer);

private:
    int w;
    int h;
    SDL_Texture* texture;
};

#endif // IMAGEFIELD_HPP