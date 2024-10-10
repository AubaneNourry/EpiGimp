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
    AButton(const std::string& label, int x, int y, int width, int height, TTF_Font* font, SDL_Color color, bool toggable = true);
    AButton(const std::string& label, SDL_Rect *rect, TTF_Font* font, SDL_Color color, bool toggable = true);
    virtual ~AButton();

    // Setters
    void setPosition(int x, int y);
    void setDimensions(int width, int height);
    void setLabel(const std::string& label);
    void setFont(TTF_Font* font);
    void setColor(SDL_Color color);
    void setDefaultCallbacks();

    // Callback setters
    void setOnClick(std::function<void()> onClickCallback);
    void setOnHover(std::function<void()> onHoverCallback);
    void setOnRelease(std::function<void()> onReleaseCallback);

    // Getters
    std::string getLabel() const;
    SDL_Rect *getRect() const;
    TTF_Font* getFont() const;
    SDL_Color getColor() const;

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
