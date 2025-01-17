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

    Layer(const std::string& name, bool visible, SDL_Texture* thumbnail)
        : name(name), visible(visible), thumbnail(thumbnail) {}
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

    void addLayer(const std::string& name, SDL_Texture* texture);
private:
    std::vector<Layer> layers;
    int selected_layer;
};

#endif // LAYERS_HPP
