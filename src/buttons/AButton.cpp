/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** AButton.cpp
*/

#include "AButton.hpp"
#include "../Application.hpp"

AButton::AButton(const std::string& label, int x, int y, int width, int height, SDL_Color color, bool toggable)
    : label(label), rect(new SDL_Rect({x, y, width, height})), font(Application::getInstance().getFont()), color(color), toggable(toggable) {
        setDefaultCallbacks();
    }

AButton::AButton(const std::string& label, SDL_Rect *rect, SDL_Color color, bool toggable)
    : label(label), rect(rect), font(Application::getInstance().getFont()), color(color), toggable(toggable) {
        setDefaultCallbacks();
    }

AButton::~AButton() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
}

void AButton::setDefaultCallbacks() {
    onClick = [this]() {
        isClicked = !isClicked;
        if (!toggable) {
        }
    };

    onHover = [this]() {
        isHovered = true;
    };

    onRelease = [this]() {
        if (!toggable) {
            isClicked = false;
        }
    };
}

void AButton::setPosition(int x, int y) {
    rect->x = x;
    rect->y = y;
}

void AButton::setDimensions(int width, int height) {
    rect->w = width;
    rect->h = height;
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

void AButton::setOnClick(std::function<void()> onClickCallback) {
    this->onClick = onClickCallback;
}

void AButton::setOnHover(std::function<void()> onHoverCallback) {
    this->onHover = onHoverCallback;
}

void AButton::setOnRelease(std::function<void()> onReleaseCallback) {
    this->onRelease = onReleaseCallback;
}

std::string AButton::getLabel() const {
    return label;
}

SDL_Rect *AButton::getRect() const {
    return rect;
}

TTF_Font* AButton::getFont() const {
    return font;
}

SDL_Color AButton::getColor() const {
    return color;
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
    SDL_RenderFillRect(renderer, rect);
}

void AButton::renderButtonLabel(SDL_Renderer* renderer) {
    if (!textTexture) {
        createTextTexture(renderer);
    }
    SDL_Rect padded_rect = {
        rect->x + (rect->w - static_cast<int>(label.size()) * 10) / 2,
        rect->y + (rect->h - 20) / 2,
        static_cast<int>(label.size()) * 10,
        20
    };
    SDL_RenderCopy(renderer, textTexture, nullptr, &padded_rect);
}

void AButton::handleEvent(const SDL_Event& event) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (event.type == SDL_MOUSEMOTION) {
        isHovered = (mouseX >= rect->x && mouseX <= rect->x + rect->w && mouseY >= rect->y && mouseY <= rect->y + rect->h);
        if (isHovered && onHover) onHover();
    } else if (event.type == SDL_MOUSEBUTTONDOWN && (mouseX >= rect->x && mouseX <= rect->x + rect->w && mouseY >= rect->y && mouseY <= rect->y + rect->h)) {
        isClicked = !isClicked;
        if (onClick) onClick();
    } else if (event.type == SDL_MOUSEBUTTONUP && isClicked && (mouseX >= rect->x && mouseX <= rect->x + rect->w && mouseY >= rect->y && mouseY <= rect->y + rect->h)) {
        if (onRelease) onRelease();
    }
}
