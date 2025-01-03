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
#include "../Application.hpp"

ImageField::ImageField(const int w, const int h, SDL_Renderer* renderer)
    : pixels(nullptr), pitch(0), isDrawing(false), zoomFactor(1.0f), drawingSurface(nullptr)
{
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    rect = {windowWidth / 2 - w / 2, windowHeight / 2 - h / 2, w, h};
    viewRect = {0, 0, w, h};

    pixels = new Uint32[w * h];
    memset(pixels, 255, w * h * sizeof(Uint32));
    auto* layers = static_cast<Layers*>(Application::getInstance().getLayers());
    layers->getLayers().back().thumbnail = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    if (layers->getLayers().back().thumbnail) {
        SDL_SetTextureBlendMode(layers->getLayers().back().thumbnail, SDL_BLENDMODE_BLEND);
    } else {
        std::cerr << "Failed to create texture for layer thumbnail: " << SDL_GetError() << std::endl;
    }
    updateTexture();
}

Uint32* ImageField::GetPixelsFromTexture(SDL_Renderer* renderer, SDL_Texture* texture, int texture_width, int texture_height) {
    if (!renderer || !texture) {
        std::cerr << "Renderer or texture is null!" << std::endl;
        return nullptr;
    }
    Uint32 texture_format;
    int access, w, h;
    if (SDL_QueryTexture(texture, &texture_format, &access, &w, &h) != 0) {
        std::cerr << "Failed to query texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    if (access != SDL_TEXTUREACCESS_TARGET) {
        std::cerr << "Texture is not a render target!" << std::endl;
        return nullptr;
    }

    if (w != texture_width || h != texture_height) {
        std::cerr << "Texture dimensions do not match provided dimensions!" << std::endl;
        return nullptr;
    }
    Uint32* pixels = new Uint32[texture_width * texture_height];
    if (!pixels) {
        std::cerr << "Failed to allocate pixel buffer!" << std::endl;
        return nullptr;
    }
    if (SDL_SetRenderTarget(renderer, texture) != 0) {
        std::cerr << "Failed to set render target: " << SDL_GetError() << std::endl;
        delete[] pixels;
        return nullptr;
    }
    if (SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGBA8888, pixels, texture_width * sizeof(Uint32)) != 0) {
        std::cerr << "Failed to read pixels from texture: " << SDL_GetError() << std::endl;
        delete[] pixels;
        pixels = nullptr;
    }
    SDL_SetRenderTarget(renderer, nullptr);
    return pixels;
}

ImageField::~ImageField() {
    delete[] pixels;
}

void ImageField::render(SDL_Renderer* renderer) {
    auto* layers = static_cast<Layers*>(Application::getInstance().getLayers());
    drawingSurface = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
    SDL_SetRenderTarget(renderer, drawingSurface);

    for (auto& layer : layers->getLayers()) {
        if (layer.visible && layer.thumbnail) {
            SDL_RenderCopy(renderer, layer.thumbnail, nullptr, nullptr);
        }
    }
    SDL_SetRenderTarget(renderer, nullptr);

    ImGui::SetNextWindowPos({static_cast<float>(rect.x), static_cast<float>(rect.y)});
    ImGui::SetNextWindowSize(ImVec2(rect.w, rect.h), ImGuiCond_FirstUseEver);
    ImGui::Begin("Drawing Surface", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);

    if (drawingSurface) {
        int textureWidth, textureHeight;
        SDL_QueryTexture(drawingSurface, nullptr, nullptr, &textureWidth, &textureHeight);
        float textureAspectRatio = static_cast<float>(textureWidth) / textureHeight;
        float viewAspectRatio = static_cast<float>(viewRect.w) / viewRect.h;

        if (viewAspectRatio > textureAspectRatio) {
            viewRect.w = static_cast<int>(viewRect.h * textureAspectRatio);
        } else if (viewAspectRatio < textureAspectRatio) {
            viewRect.h = static_cast<int>(viewRect.w / textureAspectRatio);
        }

        ImVec2 uv0 = ImVec2(
            static_cast<float>(viewRect.x) / textureWidth,
            static_cast<float>(viewRect.y) / textureHeight
        );
        ImVec2 uv1 = ImVec2(
            static_cast<float>(viewRect.x + viewRect.w) / textureWidth,
            static_cast<float>(viewRect.y + viewRect.h) / textureHeight
        );
        ImGui::Image((ImTextureID)drawingSurface, {static_cast<float>(rect.w), static_cast<float>(rect.h)}, uv0, uv1);
    }

    IUIElement* tools = Application::getInstance().getTools();
    Tools* tools_cast = dynamic_cast<Tools*>(tools);

    static ImVec2 lastMousePos;
    static bool isMoving = false;

    if (tools_cast && tools_cast->isMoveToolActive()) {
        if (ImGui::IsItemHovered()) {
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
            if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
                ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
                ImVec2 currentMousePos = ImGui::GetMousePos();
                if (!isMoving) {
                    isMoving = true;
                    lastMousePos = currentMousePos;
                }

                ImVec2 delta = ImVec2(currentMousePos.x - lastMousePos.x, currentMousePos.y - lastMousePos.y);
                rect.x += static_cast<int>(delta.x);
                rect.y += static_cast<int>(delta.y);

                lastMousePos = currentMousePos;
                }
        }

        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            isMoving = false;
        }
    } else if (tools_cast) {
        int selected_layer = layers->getSelectedLayer();

        if (selected_layer >= 0 && selected_layer < layers->getLayers().size()) {
            Layer& currentLayer = layers->getLayers()[selected_layer];
            pixels = GetPixelsFromTexture(renderer, currentLayer.thumbnail, rect.w, rect.h);

            if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
                isDrawing = true;

                if (!tools_cast->isMoveToolActive()) {
                    tools_cast->draw(ImGui::GetMousePos().x, ImGui::GetMousePos().y, rect, pixels);
                }
                updateTexture();
            }
            if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
                isDrawing = false;
            }
        }
    }
    ImGui::End();
}


void ImageField::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_MOUSEWHEEL) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        int textureWidth, textureHeight;
        SDL_QueryTexture(getTexture(), nullptr, nullptr, &textureWidth, &textureHeight);

        // Relative mouse position in the current view
        float relativeMouseX = (mouseX - rect.x) / static_cast<float>(rect.w);
        float relativeMouseY = (mouseY - rect.y) / static_cast<float>(rect.h);

        // Zoom speed control (slower zoom)
        float zoomSpeed = 0.05f;  // Adjust to control zoom speed

        // Zoom logic
        float zoomStep = (event.wheel.y > 0) ? (1.0f - zoomSpeed) : (1.0f + zoomSpeed);
        zoomFactor *= zoomStep;  // Apply zoom factor

        // Clamp zoom factor to reasonable values (e.g., between 0.1 and 3.0)
        if (zoomFactor < 0.1f) zoomFactor = 0.1f;
        if (zoomFactor > 3.0f) zoomFactor = 3.0f;

        // Compute new width and height based on zoom factor
        int newWidth = static_cast<int>(viewRect.w * zoomFactor);
        int newHeight = static_cast<int>(viewRect.h * zoomFactor);

        // Ensure viewRect doesn't get too small
        int minSize = 1;  // Minimum size for viewRect (you can adjust as needed)
        newWidth = std::max(newWidth, minSize);
        newHeight = std::max(newHeight, minSize);

        // Adjust viewRect center to zoom in/out around the mouse position
        viewRect.x += (viewRect.w - newWidth) * relativeMouseX;
        viewRect.y += (viewRect.h - newHeight) * relativeMouseY;

        // Update the viewRect dimensions
        viewRect.w = newWidth;
        viewRect.h = newHeight;

        // Clamp the viewRect to texture boundaries
        viewRect.x = std::max(0, viewRect.x);
        viewRect.y = std::max(0, viewRect.y);
        viewRect.w = std::min(textureWidth - viewRect.x, viewRect.w);
        viewRect.h = std::min(textureHeight - viewRect.y, viewRect.h);
    }
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
    auto* layers = static_cast<Layers*>(Application::getInstance().getLayers());
    SDL_Renderer* renderer = Application::getInstance().getRenderer();

    for (auto& layer : layers->getLayers()) {
        Uint32* oldPixels = GetPixelsFromTexture(renderer, layer.thumbnail, rect.w, rect.h);

        Uint32* newPixels = new Uint32[w * h];
        memset(newPixels, 255, w * h * sizeof(Uint32));

        if (oldPixels) {
            int copyWidth = std::min(rect.w, w);
            int copyHeight = std::min(rect.h, h);

            for (int y = 0; y < copyHeight; ++y) {
                memcpy(&newPixels[y * w], &oldPixels[y * rect.w], copyWidth * sizeof(Uint32));
            }

            delete[] oldPixels;
        }

        if (layer.thumbnail) {
            SDL_DestroyTexture(layer.thumbnail);
        }

        layer.thumbnail = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

        if (layer.thumbnail) {
            SDL_SetTextureBlendMode(layer.thumbnail, SDL_BLENDMODE_BLEND);

            SDL_UpdateTexture(layer.thumbnail, nullptr, newPixels, w * sizeof(Uint32));
        } else {
            std::cerr << "Failed to resize texture for layer: " << SDL_GetError() << std::endl;
        }

        delete[] newPixels;
    }

    rect.w = w;
    rect.h = h;
}

void ImageField::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void ImageField::updateTexture() const {

    auto* layers = static_cast<Layers*>(Application::getInstance().getLayers());
    int selected_layer = layers->getSelectedLayer();

    if (selected_layer >= 0 && selected_layer < layers->getLayers().size()) {
        Layer& currentLayer = layers->getLayers()[selected_layer];
        SDL_UpdateTexture(currentLayer.thumbnail, nullptr, pixels, rect.w * sizeof(Uint32));
    }
}

SDL_Texture* ImageField::getTexture() const
{
  	auto* layers = static_cast<Layers*>(Application::getInstance().getLayers());
    int selected_layer = layers->getSelectedLayer();

    if (selected_layer >= 0 && selected_layer < layers->getLayers().size()) {
        Layer& currentLayer = layers->getLayers()[selected_layer];
        return currentLayer.thumbnail;
    }
    return nullptr;
}

void ImageField::setTexture(SDL_Texture* texture) {
    return;
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
