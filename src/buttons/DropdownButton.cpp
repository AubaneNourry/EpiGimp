/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DropdownButton.hpp
*/

#include "DropdownButton.hpp"

DropdownButton::DropdownButton(const std::string& label, SDL_Rect rect, int buttonHeight, std::vector<AButton*> buttons, TTF_Font* font, SDL_Color color)
    : AButton(label, rect, font, color), buttonHeight(buttonHeight), isOpen(false) {
    for (const auto& btn : buttons) {
        addButton(btn);
    }
}

void DropdownButton::click() {
    AButton::click();
    isOpen = isClicked;
    if (isOpen) {
        std::cout << "Dropdown Button '" << label << "' opened!" << std::endl;
    } else {
        std::cout << "Dropdown Button '" << label << "' closed!" << std::endl;
    }
}

void DropdownButton::hover() {
    AButton::hover();
    isOpen = true;
    std::cout << "Dropdown Button '" << label << "' is hovered!" << std::endl;
}

void DropdownButton::release() {
    AButton::release();
    std::cout << "Dropdown Button '" << label << "' released!" << std::endl;
}

void DropdownButton::render(SDL_Renderer* renderer) {
    renderButtonRect(renderer);
    renderButtonLabel(renderer);
    if (isOpen) {
        for (const auto& btn : buttons) {
            btn->render(renderer);
        }
    }
}

void DropdownButton::handleEvent(const SDL_Event& event) {
    AButton::handleEvent(event);

    if (event.type == SDL_MOUSEMOTION) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        if (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h + buttonHeight * buttons.size()) {
            isHovered = true;
        } else {
            isHovered = false;
        }
    }
    
    if (isOpen) {
        for (const auto& btn : buttons) {
            btn->handleEvent(event);
        }
    } if (isOpen && !isHovered && !isClicked) {
        isOpen = false;
    }
}

void DropdownButton::addButton(AButton* button) {
    button->setPosition(rect.x, rect.y + buttonHeight * buttons.size() + rect.h);
    button->setDimensions(rect.w, buttonHeight);
    buttons.push_back(button);
}
