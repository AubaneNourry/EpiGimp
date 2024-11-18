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
#include <SDL2/SDL_image.h>

#include "ImageField.hpp"

class FileManager {
public:
    FileManager() = default;
    ~FileManager() = default;

    static FileManager &getInstance();
    static SDL_Texture* loadTexture(const std::string& path);
    void setImageField(IUIElement* imageField);
    void newImageField();
    void saveImage();

private:
    ImageField* imageField;
};

#endif // FILEMANAGER_HPP