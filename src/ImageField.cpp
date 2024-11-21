/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ImageField.cpp
*/

#include "ImageField.hpp"
#include <iostream>

ImageField::ImageField(int w, int h, SDL_Renderer* renderer)
    : texture(nullptr), pixels(nullptr), isDrawing(false) {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    rect = { windowWidth / 2 - w / 2, windowHeight / 2 - h / 2, w, h };
    pixels = new Uint32[w * h];
    memset(pixels, 255, w * h * sizeof(Uint32));
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);
}

ImageField::~ImageField() {
    delete[] pixels;
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void ImageField::render(SDL_Renderer* renderer) {
    updateTexture();
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void ImageField::handleEvent(const SDL_Event& event) {
    const int mouseX = event.button.x;
    const int mouseY = event.button.y;

    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (mouseX >= rect.x && mouseX < rect.x + rect.w &&
                mouseY >= rect.y && mouseY < rect.y + rect.h) {
                isDrawing = true;
                drawPixel(mouseX, mouseY);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            isDrawing = false;
            break;
        case SDL_MOUSEMOTION:
            if (isDrawing) {
                drawPixel(mouseX, mouseY);
            }
            break;
        default:
            break;
    }
}

void ImageField::drawPixel(int mouseX, int mouseY) {
    if (mouseX >= rect.x && mouseX < rect.x + rect.w &&
        mouseY >= rect.y && mouseY < rect.y + rect.h) {

        int relativeX = mouseX - rect.x;
        int relativeY = mouseY - rect.y;

        pixels[relativeY * rect.w + relativeX] = 0x000000FF;
        updateTexture();
    }
}

void ImageField::setTextureFromPath(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (surface) {
        memcpy(pixels, surface->pixels, rect.w * rect.h * sizeof(Uint32));
        updateTexture();
        SDL_FreeSurface(surface);
    }
}

void ImageField::setDimensions(int w, int h) {
    rect.w = w;
    rect.h = h;

    delete[] pixels;
    pixels = new Uint32[w * h];

    memset(pixels, 255, w * h * sizeof(Uint32));
}

void ImageField::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void ImageField::updateTexture() const {
    SDL_UpdateTexture(texture, nullptr, pixels, rect.w * sizeof(Uint32));
}

SDL_Texture* ImageField::getTexture() {
    return texture;
}

void ImageField::setTexture(SDL_Texture* texture) {
    this->texture = texture;
}

Uint32* ImageField::getPixels()
{
    return pixels;
}

void ImageField::setPixels(Uint32 *pixels)
{
    this->pixels = pixels;
}

void ImageField::clear(Uint32 color) {
    if (pixels) {
        // Set all pixels to the specified color
        for (int i = 0; i < rect.w * rect.h; ++i) {
            pixels[i] = color;
        }
        // Update the texture with the new pixel data
        updateTexture();  // Assuming WindowID 1, change as needed
    }
}
