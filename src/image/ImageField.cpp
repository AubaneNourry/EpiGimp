/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ImageField.cpp
*/

#include "ImageField.hpp"
#include <iostream>
#include "../FileManager.hpp"
#include "Tools.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui.h"

void ImageField::InitializeDrawingSurface(SDL_Renderer* renderer) {
    pixels = new Uint32[rect.w * rect.h];
    memset(pixels, 255, rect.w * rect.h * sizeof(Uint32)); // Initialize white
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h);
}

void ImageField::UpdateTexture(SDL_Renderer* renderer) {
    SDL_UpdateTexture(texture, nullptr, pixels, rect.w * sizeof(Uint32));
}

void ImageField::FreeDrawingSurface() {
    if (texture) SDL_DestroyTexture(texture);
    delete[] pixels;
}

ImageField::ImageField(const int w, const int h, SDL_Renderer* renderer)
    : texture(nullptr), pixels(nullptr), pitch(0), isDrawing(false)
{
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    rect = {windowWidth / 2 - w / 2, windowHeight / 2 - h / 2, w, h};
    pixels = new Uint32[w * h];
    memset(pixels, 255, w * h * sizeof(Uint32));
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    std::cout << "rect: " << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << std::endl;
}

ImageField::~ImageField() {
    delete[] pixels;
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void ImageField::render(SDL_Renderer* renderer) {
    updateTexture();

    ImGui::SetNextWindowPos({static_cast<float>(rect.x), static_cast<float>(rect.y)});
    ImGui::SetNextWindowSize(ImVec2(rect.w, rect.h), ImGuiCond_FirstUseEver);
    ImGui::Begin("Drawing Surface", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);

    ImGui::Image((ImTextureID)texture, {static_cast<float>(rect.w), static_cast<float>(rect.h)});
    if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        isDrawing = true;
        Tools::getInstance().draw(ImGui::GetMousePos().x, ImGui::GetMousePos().y, rect, pixels);
        updateTexture();
    } if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
        isDrawing = false;
    } if (ImGui::IsItemHovered() && isDrawing) {
        Tools::getInstance().draw(ImGui::GetMousePos().x, ImGui::GetMousePos().y, rect, pixels);
        updateTexture();
    }
    ImGui::End();
}

void ImageField::handleEvent(const SDL_Event& event) {
    return;
}

void ImageField::setTextureFromPath(const char* path) const
{
    if (SDL_Surface* surface = FileManager::loadSurface(path)) {
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

SDL_Texture* ImageField::getTexture() const
{
    return texture;
}

void ImageField::setTexture(SDL_Texture* texture) {
    this->texture = texture;
}

Uint32* ImageField::getPixels() const
{
    return pixels;
}

void ImageField::setPixels(Uint32 *pixels)
{
    this->pixels = pixels;
}

void ImageField::clear(const Uint32 color) const
{
    if (pixels) {
        for (int i = 0; i < rect.w * rect.h; ++i) {
            pixels[i] = color;
        }
        updateTexture();
    }
}
