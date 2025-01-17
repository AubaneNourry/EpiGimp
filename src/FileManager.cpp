/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** FileManager.cpp
*/

#include "FileManager.hpp"
#include "Application.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui.h"

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

SDL_Surface* FileManager::loadSurface(const std::string& path) {
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
    return surface;
}

void FileManager::setImageField(IUIElement *imageField) {
    this->imageField = dynamic_cast<ImageField*>(imageField);
}

void FileManager::newImageField() const
{
    imageField->clear();
}

void FileManager::update()
{
    auto* fileManager = &FileManager::getInstance();

    if (fileManager->isSavingImage) {
        fileManager->saveImage();
    }
    if (fileManager->isOpeningImage) {
        fileManager->openImage();
    }
}

void FileManager::saveImage()
{
    static const char* extensions[] = { ".png", ".bmp", ".jpg" };
    static int selectedExtensionIndex = 0;

    if (!isSavingImage) {
        fileName[0] = '\0';
    }

    isSavingImage = true;
    ImGui::OpenPopup("Save Image");

    if (ImGui::BeginPopupModal("Save Image", NULL, ImGuiWindowFlags_MenuBar))
    {
        ImGui::Text("File name:");
        ImGui::InputText("##edit", fileName, IM_ARRAYSIZE(fileName), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);

        ImGui::Text("File extension:");
        if (ImGui::Combo("##extension", &selectedExtensionIndex, extensions, IM_ARRAYSIZE(extensions)))
        {
            // Update selected extension if necessary (logic is handled below during saving)
        }

        if (ImGui::Button("Save")) {
            isSavingImage = false;
            ImGui::CloseCurrentPopup();

            // Save image
            SDL_Texture* texture = imageField->getTexture();
            auto [height, width] = imageField->getDimensions();
            SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000);

            if (!surface) {
                std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
                return;
            }

            SDL_Renderer* renderer = Application::getInstance().getRenderer();
            SDL_Texture* targetTexture = SDL_CreateTexture(renderer, surface->format->format, SDL_TEXTUREACCESS_TARGET, height, width);
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

            // Build the file path with the selected extension
            std::string filePath = "results/" + std::string(fileName) + extensions[selectedExtensionIndex];

            // Save the image based on the selected extension
            int saveResult = 0;
            if (selectedExtensionIndex == 0) { // .png
                saveResult = IMG_SavePNG(surface, filePath.c_str());
            } else if (selectedExtensionIndex == 1) { // .bmp
                saveResult = SDL_SaveBMP(surface, filePath.c_str());
            } else if (selectedExtensionIndex == 2) { // .jpg
                saveResult = IMG_SaveJPG(surface, filePath.c_str(), 100); // Quality: 100 (max)
            }

            if (saveResult != 0) {
                std::cerr << "Failed to save image: " << IMG_GetError() << std::endl;
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(targetTexture);
                return;
            }

            std::cout << "Image saved to: " << filePath << std::endl;

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(targetTexture);
        }
        ImGui::EndPopup();
    }
}

#include <fstream>
#include <string>
#include <filesystem>

void FileManager::openImage()
{
    static char filePath[256] = "";
    bool fileExists = false;
    bool validExtension = false;

    if (!isOpeningImage) {
        filePath[0] = '\0';
    }

    isOpeningImage = true;
    ImGui::OpenPopup("Open Image");

    if (ImGui::BeginPopupModal("Open Image", NULL, ImGuiWindowFlags_MenuBar))
    {
        ImGui::Text("File path:");

        // Check if the file exists and is not a directory
        std::ifstream file(filePath);
        if (file.good() && !std::filesystem::is_directory(filePath)) {
            fileExists = true;
        } else {
            fileExists = false;
        }

        // Validate the file extension (only allow image types: .jpg, .png, .bmp)
        std::string pathStr(filePath);
        std::string validExtensions[] = { ".jpg", ".png", ".bmp" };

        for (const auto& ext : validExtensions) {
            if (pathStr.size() >= ext.size() && pathStr.compare(pathStr.size() - ext.size(), ext.size(), ext) == 0) {
                validExtension = true;
                break;
            }
        }

        // Determine the input field color based on the file state:
        ImVec4 inputColor;
        if (!fileExists) {
            inputColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);  // Gray if file doesn't exist or isn't a file
        } else if (!validExtension) {
            inputColor = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);  // Red if the file exists but is unsupported
        } else {
            inputColor = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);  // Green if the file exists and is supported
        }

        // Apply the color to the input field
        ImGui::PushStyleColor(ImGuiCol_FrameBg, inputColor);
        ImGui::InputText("##filePath", filePath, IM_ARRAYSIZE(filePath), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
        ImGui::PopStyleColor();  // Reset the color style

        if (ImGui::Button("Open")) {
            isOpeningImage = false;
            ImGui::CloseCurrentPopup();

            // If the file exists and has a valid extension, open the image
            if (fileExists && validExtension) {
                imageField->setTextureFromPath(filePath);
                std::cout << "Image loaded: " << filePath << std::endl;
            } else {
                std::cerr << "Failed to open image: " << filePath << std::endl;
            }
        }
        ImGui::EndPopup();
    }
}
