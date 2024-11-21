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

SDL_Texture* FileManager::loadTexture(const std::string& path) {
    const std::string& filePath = path;
    const std::string extension = filePath.substr(filePath.find_last_of('.') + 1);
    SDL_Surface* surface = nullptr;

    if (extension == "bmp") {
        surface = SDL_LoadBMP(path.c_str());
    } else if (extension == "png" || extension == "jpg" || extension == "jpeg" || extension == "tif" || extension == "tiff") {
        surface = IMG_Load(path.c_str());
    } else {
        std::cerr << "Unsupported file format: " << extension << std::endl;
        return nullptr;
    }

    if (!surface) {
        std::cerr << "Failed to load image: " << path << ", SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Renderer *renderer = Application::getInstance().getRenderer();
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Failed to load image: " << path << ", SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    return texture;
}

void FileManager::setImageField(IUIElement *imageField) {
    this->imageField = dynamic_cast<ImageField*>(imageField);
}

void FileManager::newImageField() {
    imageField->clear();
}

void FileManager::saveImage() {
    SDL_Texture* texture = static_cast<ImageField*>(imageField)->getTexture();
    int width = static_cast<ImageField*>(imageField)->getWidth();
    int height = static_cast<ImageField*>(imageField)->getHeight();
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000);
    
    if (!surface) {
        std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Renderer* renderer = Application::getInstance().getRenderer();
    SDL_Texture* targetTexture = SDL_CreateTexture(renderer, surface->format->format, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!targetTexture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_SetRenderTarget(renderer, targetTexture);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    if (SDL_RenderReadPixels(renderer, nullptr, surface->format->format, surface->pixels, surface->pitch) != 0) {
        std::cerr << "Failed to read pixels: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(targetTexture);
        return;
    }

    if (IMG_SavePNG(surface, "results/output.png") != 0) {
        std::cerr << "Failed to save PNG: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(targetTexture);
        return;
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(targetTexture);
}
