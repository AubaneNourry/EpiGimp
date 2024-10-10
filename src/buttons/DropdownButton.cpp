/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DropdownButton.cpp
*/

#include "DropdownButton.hpp"

DropdownButton::DropdownButton(const std::string& label, SDL_Rect *rect, int buttonHeight, std::vector<AButton*> buttons, TTF_Font* font, SDL_Color color)
    : AButton(label, rect, font, color), buttonHeight(buttonHeight), isOpen(false) {
        for (auto& btn : buttons) {
            btn->setPosition(rect->x, rect->y + rect->h + buttonHeight * this->buttons.size());
            btn->setDimensions(rect->w, buttonHeight);
            this->buttons.push_back(btn);
        }
        setCallbacks();
    }

void DropdownButton::setCallbacks() {
    onClick = [this]() {
        std::cout << "Button '" << label << "' clicked!" << std::endl;
        isClicked = !isClicked;
        isOpen = !isOpen;
    };
}

void DropdownButton::handleEvent(const SDL_Event& event) {
    AButton::handleEvent(event);
    
    if (isOpen) {
        for (auto& btn : buttons) {
            btn->handleEvent(event);
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
