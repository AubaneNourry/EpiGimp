/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DropdownButton.hpp
*/

#ifndef DROPDOWNBUTTON_HPP
#define DROPDOWNBUTTON_HPP

#include "AButton.hpp"
#include "../EventManager.hpp"
#include <vector>
#include <iostream>

class DropdownButton : public AButton {
public:
    DropdownButton(const std::string& label, SDL_Rect *rect, int buttonHeight, std::vector<AButton*> buttons, TTF_Font* font, SDL_Color color = UICOLOR);

    void setCallbacks();
    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;
    void addButton(AButton* button);
    void close();

private:
    int buttonHeight;             // Fixed height for dropdown buttons
    std::vector<AButton*> buttons; // List of buttons in the dropdown
    bool isOpen;                  // Indicates if the dropdown is open
};

#endif // DROPDOWNBUTTON_HPP
