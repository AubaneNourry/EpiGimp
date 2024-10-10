/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DropdownButton.hpp
*/

#include "DropdownButton.hpp"

DropdownButton::DropdownButton(const std::string& label, int x, int y, int width, int height, int buttonHeight, std::vector<AButton*> buttons, TTF_Font* font, SDL_Color color)
    : AButton(label, x, y, width, height, font, color), buttonHeight(buttonHeight), isOpen(false) {
    for (const auto& btn : buttons) {
        addButton(btn);
    }
}

void DropdownButton::click() {
    isOpen = !isOpen;
    if (isOpen) {
        color = { 100, 100, 100, 255 };
        std::cout << "Dropdown Button '" << label << "' opened!" << std::endl;
    } else {
        color = { 150, 150, 150, 255 };
        std::cout << "Dropdown Button '" << label << "' closed!" << std::endl;
    }
}

void DropdownButton::hover() {
    std::cout << "Dropdown Button '" << label << "' is hovered!" << std::endl;
}

void DropdownButton::release() {
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

    if (isOpen) {
        for (const auto& btn : buttons) {
            btn->handleEvent(event);
        }
    }
}

void DropdownButton::addButton(AButton* button) {
    button->setPosition(rect.x, rect.y + buttonHeight * buttons.size() + rect.h);
    button->setDimensions(rect.w, buttonHeight);
    buttons.push_back(button);
}
