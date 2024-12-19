/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Layers.cpp
*/

#include "Layers.hpp"

#include "imgui.h"
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

Layers::Layers() : selected_layer(0)
{
    layers = {
        {"Background", true, nullptr}    };
}

SDL_Texture* GenerateThumbnail(SDL_Renderer* renderer, const SDL_Texture* layer_texture, int thumbnail_width, int thumbnail_height) {
    SDL_Texture* thumbnail = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, thumbnail_width, thumbnail_height);
    SDL_SetRenderTarget(renderer, thumbnail);
    SDL_RenderCopy(renderer, const_cast<SDL_Texture*>(layer_texture), nullptr, nullptr);
    SDL_SetRenderTarget(renderer, nullptr);
    return thumbnail;
}

void Layers::render(SDL_Renderer* renderer)
{
	ImGui::Begin("Layers Manager", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    if (ImGui::Button("Add Layer")) {
        SDL_Texture* new_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
        if (!new_texture) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
            return;
        }
        SDL_SetTextureBlendMode(new_texture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(renderer, new_texture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, nullptr);
        layers.push_back({"New Layer", true, new_texture});
    }
    ImGui::SameLine();

    if (ImGui::Button("Delete Layer") && !layers.empty()) {
        layers.erase(layers.begin() + selected_layer);
        selected_layer = std::max(0, selected_layer - 1);
    }

    ImGui::Separator();

    for (int i = layers.size() - 1; i >= 0; i--) {
        ImGui::PushID(i);

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("LAYER_DRAG")) {
                int dragged_layer_index = *(int*)payload->Data;
                if (dragged_layer_index != i) {
                    std::swap(layers[i], layers[dragged_layer_index]);
                    if (selected_layer == dragged_layer_index) {
                        selected_layer = i;
                    } else if (selected_layer == i) {
                        selected_layer = dragged_layer_index;
                    }
                }
            }
            ImGui::EndDragDropTarget();
        }

        /*if (layers[i].thumbnail) {
            ImGui::Image((ImTextureID)layers[i].thumbnail, ImVec2(50, 50));
            ImGui::SameLine();
        }*/

        ImGui::Checkbox("##Visible", &layers[i].visible);
        ImGui::SameLine();

        // Selectable layer name
        if (ImGui::Selectable(layers[i].name.c_str(), selected_layer == i)) {
            selected_layer = i;
        }

        // Drag-and-Drop Source for Reordering
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            ImGui::SetDragDropPayload("LAYER_DRAG", &i, sizeof(int)); // Send the layer index
            ImGui::Text("Moving: %s", layers[i].name.c_str());
            ImGui::EndDragDropSource();
        }

        ImGui::PopID();
    }

    ImGui::Separator();

    // Display selected layer details
    if (selected_layer >= 0 && selected_layer < layers.size()) {
        ImGui::Text("Selected Layer: %s", layers[selected_layer].name.c_str());
    }

    ImGui::End();
}