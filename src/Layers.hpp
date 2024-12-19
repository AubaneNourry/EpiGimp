/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Layers.hpp
*/

#ifndef LAYERS_HPP
#define LAYERS_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "IUIElement.hpp"

struct Layer {
    std::string name;
    bool visible = true;
    SDL_Texture* thumbnail = nullptr;
};

class Layers : public IUIElement {
public:
    Layers();
    ~Layers() = default;

    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override {
        return;
    }

    [[nodiscard]] std::vector<Layer>& getLayers() { return layers; }
    [[nodiscard]] int getSelectedLayer() const { return selected_layer; }
private:
    std::vector<Layer> layers;
    int selected_layer;
};

#endif // LAYERS_HPP
