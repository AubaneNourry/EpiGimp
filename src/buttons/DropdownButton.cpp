/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DropdownButton.cpp
*/

#include "DropdownButton.hpp"
#include "DropdownManager.hpp"

DropdownButton::DropdownButton(const std::string& label, SDL_Rect *rect, int buttonHeight, std::vector<AButton*> buttons, SDL_Color color)
    : AButton(label, rect, color), buttonHeight(buttonHeight), isOpen(false) {
    for (auto& btn : buttons) {
        btn->setPosition(rect->x, rect->y + rect->h + buttonHeight * this->buttons.size());
        btn->setDimensions(rect->w, buttonHeight);
        this->buttons.push_back(btn);
    }
    DropdownManager::getInstance().registerDropdown(this);
    setCallbacks();
}

void DropdownButton::close() {
    isOpen = false;
    isClicked = false;
}

void DropdownButton::setCallbacks() {
    onClick = [this]() {
        isOpen = isClicked;
        if (isOpen) {
            EventManager::getInstance().triggerEvent("dropdown_opened", { "dropdown_opened", time(nullptr), this });
        }
    };
    onHover = [this]() {
        isHovered = true;
        isOpen = true;
        EventManager::getInstance().triggerEvent("dropdown_opened", { "dropdown_opened", time(nullptr), this });
    };
}

void DropdownButton::handleEvent(const SDL_Event& event) {
    AButton::handleEvent(event);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (isOpen) {
        for (auto& btn : buttons) {
            btn->handleEvent(event);
        }
    }
    if (event.type == SDL_MOUSEMOTION) {
        isHovered = (mouseX >= rect->x && mouseX <= rect->x + rect->w && mouseY >= rect->y && mouseY <= rect->y + rect->h + buttonHeight * buttons.size());
        if (!isHovered && !isClicked) {
            isOpen = false;
        }
    }
}

void DropdownButton::render(SDL_Renderer* renderer) {
    renderButtonRect(renderer);
    renderButtonLabel(renderer);

    if (isOpen) {
        for (auto& btn : buttons) {
            btn->render(renderer);
        }
    }
}

void DropdownButton::addButton(AButton* button) {
    buttons.push_back(button);
}
