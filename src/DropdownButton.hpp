/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DropdownButton.hpp
*/

#ifndef DROPDOWNBUTTON_HPP
#define DROPDOWNBUTTON_HPP

#include "AButton.hpp"
#include <vector>
#include <iostream>

class DropdownButton : public AButton {
public:
    DropdownButton(const std::string& label, int x, int y, int width, int height, int buttonHeight, std::vector<AButton*> buttons, TTF_Font* font, SDL_Color color)
        : AButton(label, x, y, width, height, font, color), buttonHeight(buttonHeight), isOpen(false) {
        for (const auto& btn : buttons) {
            addButton(btn);
        }
    }

    void click() override {
        isOpen = !isOpen; // Toggle dropdown state
        if (isOpen) {
            std::cout << "Dropdown Button '" << label << "' opened!" << std::endl;
        } else {
            std::cout << "Dropdown Button '" << label << "' closed!" << std::endl;
        }
    }

    void hover() override {
        std::cout << "Dropdown Button '" << label << "' is hovered!" << std::endl;
    }

    void release() override {
        std::cout << "Dropdown Button '" << label << "' released!" << std::endl;
    }

    void render(SDL_Renderer* renderer) override {
        renderButtonRect(renderer);
        renderButtonLabel(renderer);
        if (isOpen) {
            for (const auto& btn : buttons) {
                btn->render(renderer);
            }
        }
    }

    void addButton(AButton* button) {
        button->setPosition(rect.x, rect.y + buttonHeight * buttons.size() + rect.h); // Set position of dropdown buttons
        button->setDimensions(rect.w, buttonHeight); // Set dimensions of dropdown buttons
        buttons.push_back(button);
    }

private:
    std::vector<AButton*> buttons; // List of buttons in the dropdown
    int buttonHeight;             // Fixed height for dropdown buttons
    bool isOpen;                  // Indicates if the dropdown is open
};

#endif // DROPDOWNBUTTON_HPP
