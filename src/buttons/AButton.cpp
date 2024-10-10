/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** AButton.cpp
*/

#include "AButton.hpp"

#include <iostream>

AButton::AButton(const std::string& label, int x, int y, int width, int height, TTF_Font* font, SDL_Color color)
    : label(label), rect({ x, y, width, height }), font(font), color(color) {}

AButton::AButton(const std::string& label, SDL_Rect rect, TTF_Font* font, SDL_Color color)
    : label(label), rect(rect), font(font), color(color) {}

AButton::~AButton() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
}


void AButton::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void AButton::setDimensions(int width, int height) {
    rect.w = width;
    rect.h = height;
}

void AButton::setLabel(const std::string& label) {
    this->label = label;
}

void AButton::setFont(TTF_Font* font) {
    this->font = font;
}

void AButton::setColor(SDL_Color color) {
    this->color = color;
}

std::string AButton::getLabel() const {
    return label;
}

SDL_Rect AButton::getRect() const {
    return rect;
}

TTF_Font* AButton::getFont() const {
    return font;
}

SDL_Color AButton::getColor() const {
    return color;
}

SDL_Texture* AButton::getTextTexture() const {
    return textTexture;
}

void AButton::createTextTexture(SDL_Renderer* renderer) {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, label.c_str(), { 255, 255, 255, 255 });
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
}

void AButton::destroyTextTexture() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
}

void AButton::renderButtonRect(SDL_Renderer* renderer) {
    SDL_Color actualColor = color;
    if (isClicked) {
        actualColor = { static_cast<Uint8>(color.r + CLICKED_OFFSET), static_cast<Uint8>(color.g + CLICKED_OFFSET), static_cast<Uint8>(color.b + CLICKED_OFFSET), color.a };
    } else if (isHovered) {
        actualColor = { static_cast<Uint8>(color.r + HOVERED_OFFSET), static_cast<Uint8>(color.g + HOVERED_OFFSET), static_cast<Uint8>(color.b + HOVERED_OFFSET), color.a };
    }
    SDL_SetRenderDrawColor(renderer, actualColor.r, actualColor.g, actualColor.b, actualColor.a);
    SDL_RenderFillRect(renderer, &rect);
}

void AButton::renderButtonLabel(SDL_Renderer* renderer) {
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

void AButton::click() {
    std::cout << "Button '" << label << "' clicked!" << std::endl;
    isClicked = !isClicked;
}

void AButton::hover() {
    isHovered = true;
}

void AButton::release() {}

void AButton::handleEvent(const SDL_Event& event) {
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
        } else {
            isHovered = false;
        }
    }
}

SDL_Rect *AButton::getRect() {
    return &rect;
}
