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
    AButton(const std::string& label, int x, int y, int width, int height, TTF_Font* font, SDL_Color color)
        : label(label), rect({ x, y, width, height }), font(font), color(color) {}

    virtual ~AButton() {
        if (textTexture) {
            SDL_DestroyTexture(textTexture);
        }
    }

    virtual void click() override = 0;  // Pure virtual click method
    virtual void hover() override = 0;  // Pure virtual hover method
    virtual void release() override = 0; // Pure virtual release method
    virtual void render(SDL_Renderer* renderer) override = 0; // Pure virtual render method

    void setPosition(int x, int y) override {
        rect.x = x;
        rect.y = y;
    }

    void setDimensions(int width, int height) override {
        rect.w = width;
        rect.h = height;
    }

    void setLabel(const std::string& label) {
        this->label = label;
    }

    void setFont(TTF_Font* font) {
        this->font = font;
    }

    void setColor(SDL_Color color) {
        this->color = color;
    }

    std::string getLabel() const {
        return label;
    }

    SDL_Rect getRect() const {
        return rect;
    }

    TTF_Font* getFont() const {
        return font;
    }

    SDL_Color getColor() const {
        return color;
    }

    SDL_Texture* getTextTexture() const {
        return textTexture;
    }

    void createTextTexture(SDL_Renderer* renderer) {
        if (textTexture) {
            SDL_DestroyTexture(textTexture);
        }
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, label.c_str(), { 255, 255, 255, 255 });
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
    }

    void destroyTextTexture() {
        if (textTexture) {
            SDL_DestroyTexture(textTexture);
            textTexture = nullptr;
        }
    }

    void renderButtonRect(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    void renderButtonLabel(SDL_Renderer* renderer) {
        if (!textTexture) {
            createTextTexture(renderer);
        }
        SDL_Rect padded_rect = { 
            rect.x + (rect.w - static_cast<int>(label.size()) * 10) / 2, 
            rect.y + (rect.h - 20) / 2, 
            static_cast<int>(label.size()) * 10, 
            20 
        };
        SDL_RenderCopy(renderer, textTexture, NULL, &padded_rect);
    }

    void handleEvent(const SDL_Event& event) override {
        if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEMOTION) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    click();
                } else if (event.type == SDL_MOUSEBUTTONUP) {
                    release();
                } else if (event.type == SDL_MOUSEMOTION) {
                    hover();
                }
            }
        }
    }

    SDL_Rect *getRect() {
        return &rect;
    }

protected:
    std::string label; // Button label
    SDL_Rect rect;    // Button rectangle
    TTF_Font* font;    // Font for rendering text
    SDL_Color color;   // Color for rendering text
    SDL_Texture* textTexture = nullptr; // Texture for rendering text
};

#endif // ABUTTON_HPP
