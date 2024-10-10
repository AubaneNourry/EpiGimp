/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** FileManager.cpp
*/

#include "FileManager.hpp"
#include "Application.hpp"

FileManager &FileManager::getInstance() {
    static FileManager fileManager;
    return fileManager;
}

SDL_Texture* FileManager::loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void FileManager::setImageField(IUIElement* imageField) {
    this->imageField = imageField;
}

void FileManager::newImageField() {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 600, 600, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 255, 255));
    SDL_Texture* blankTexture = SDL_CreateTextureFromSurface(Application::getInstance().getRenderer(), surface);
    SDL_FreeSurface(surface);

    static_cast<ImageField*>(imageField)->setTexture(blankTexture);
}

void FileManager::saveImage() {
    std::cout << "Saving image..." << std::endl;

    // Create a surface for the 200x200 image
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 200, 200, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000);
    
    if (!surface) {
        std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
        return;
    }

    // Get the current renderer
    SDL_Renderer* renderer = Application::getInstance().getRenderer();

    // Define the rectangle to capture the middle of the screen
    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

    // Calculate the position to capture the middle of the screen
    int x = (screenWidth - 200) / 2;
    int y = (screenHeight - 200) / 2;
    SDL_Rect captureRect = { x, y, 200, 200 };

    // Set the render target to the texture you want to read pixels from
    SDL_SetRenderTarget(renderer, static_cast<ImageField*>(imageField)->getTexture());

    // Read the pixels into the surface from the specified rectangle
    if (SDL_RenderReadPixels(renderer, &captureRect, surface->format->format, surface->pixels, surface->pitch) != 0) {
        std::cerr << "Failed to read pixels: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Save the surface as a PNG file
    if (IMG_SavePNG(surface, "results/output.png") != 0) {
        std::cerr << "Failed to save PNG: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Clean up
    SDL_FreeSurface(surface);
    std::cout << "Image saved successfully as results/output.png" << std::endl;
}
