/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** FileManager.hpp
*/

#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>

class FileManager {
public:
    FileManager() = default;
    ~FileManager() = default;
    static FileManager &getInstance() {
        static FileManager fileManager;
        return fileManager;
    }
    static SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
        SDL_Surface* surface = IMG_Load(path);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        std::cout << "Loaded texture from path: " << path << std::endl;
        return texture;
    }
};

#endif // FILEMANAGER_HPP