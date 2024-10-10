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

#include "IUIElement.hpp"
#include "ImageField.hpp"

class FileManager {
public:
    FileManager() = default;
    ~FileManager() = default;

    static FileManager &getInstance();
    SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
    void setImageField(IUIElement* imageField);
    void newImageField();
    void saveImage();

private:
    IUIElement* imageField;
};

#endif // FILEMANAGER_HPP