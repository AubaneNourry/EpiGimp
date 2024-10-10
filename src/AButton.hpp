/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** AButton.hpp
*/

#ifndef ABUTTON_HPP
#define ABUTTON_HPP

#include "IButton.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class AButton : public IButton {
public:
    AButton(const std::string& label, int x, int y, int width, int height, TTF_Font* font, SDL_Color color);

    virtual ~AButton();
    virtual void click() override = 0;  // Pure virtual click method
    virtual void hover() override = 0;  // Pure virtual hover method
    virtual void release() override = 0; // Pure virtual release method
    virtual void render(SDL_Renderer* renderer) override = 0; // Pure virtual render method

    void setPosition(int x, int y) override;
    void setDimensions(int width, int height) override;
    void setLabel(const std::string& label);
    void setFont(TTF_Font* font);
    void setColor(SDL_Color color);
    std::string getLabel() const;

    SDL_Rect getRect() const;

    TTF_Font* getFont() const;

    SDL_Color getColor() const;
    SDL_Texture* getTextTexture() const;
    void createTextTexture(SDL_Renderer* renderer);
    void destroyTextTexture();
    void renderButtonRect(SDL_Renderer* renderer);
    void renderButtonLabel(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event) override;
    SDL_Rect *getRect();

protected:
    std::string label; // Button label
    SDL_Rect rect;    // Button rectangle
    TTF_Font* font;    // Font for rendering text
    SDL_Color color;   // Color for rendering text
    SDL_Texture* textTexture = nullptr; // Texture for rendering text
};

#endif // ABUTTON_HPP
