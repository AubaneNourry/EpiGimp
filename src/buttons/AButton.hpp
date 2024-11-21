/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** AButton.hpp
*/

#ifndef ABUTTON_HPP
#define ABUTTON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <string>
#include <iostream>

#include "IButton.hpp"

class AButton : public IButton {
public:
    AButton(const std::string& label, int x, int y, int width, int height, SDL_Color color, bool toggable = true);
    AButton(const std::string& label, SDL_Rect *rect, SDL_Color color, bool toggable = true);
    ~AButton() override;

    // Setters
    void setPosition(int x, int y) override;
    void setDimensions(int width, int height) override;
    void setLabel(const std::string& label);
    void setFont(TTF_Font* font);
    void setColor(SDL_Color color);
    void setDefaultCallbacks();

    // Callback setters
    void setOnClick(std::function<void()> onClickCallback) override;
    void setOnHover(std::function<void()> onHoverCallback) override;
    void setOnRelease(std::function<void()> onReleaseCallback) override;

    // Getters
    [[nodiscard]] std::string getLabel() const;
    [[nodiscard]] SDL_Rect *getRect() const;
    [[nodiscard]] TTF_Font* getFont() const;
    [[nodiscard]] SDL_Color getColor() const;

    [[nodiscard]] std::pair<int, int> getPosition() const override {
        return {rect->x, rect->y};
    }
    [[nodiscard]] std::pair<int, int> getDimensions() const override {
        return {rect->w, rect->h};
    }

    // Event handlers
    virtual void handleEvent(const SDL_Event& event);
    virtual void render(SDL_Renderer* renderer) = 0;  // Pure virtual, must be implemented by derived classes

protected:
    std::string label;
    SDL_Rect *rect;
    TTF_Font* font;
    SDL_Color color;
    bool toggable;
    bool isClicked = false;
    bool isHovered = false;

    // Callbacks
    std::function<void()> onClick;
    std::function<void()> onHover;
    std::function<void()> onRelease;

    // Helper functions for rendering
    virtual void renderButtonRect(SDL_Renderer* renderer);
    virtual void renderButtonLabel(SDL_Renderer* renderer);

private:
    SDL_Texture* textTexture = nullptr;

    void createTextTexture(SDL_Renderer* renderer);
    void destroyTextTexture();
};

#endif // ABUTTON_HPP
