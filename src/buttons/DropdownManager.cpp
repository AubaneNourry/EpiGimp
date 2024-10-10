/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DropdownManager.cpp
*/
#include "DropdownManager.hpp"
#include "DropdownButton.hpp"

DropdownManager& DropdownManager::getInstance() {
    static DropdownManager instance;
    return instance;
}

DropdownManager::DropdownManager()
    : activeDropdown(nullptr) {
    initialize();
}

void DropdownManager::initialize() {
    EventManager::getInstance().registerListener("dropdown_opened", 
        [this](const EventData& data) {
            handleDropdownOpened(data);
        }
    );
}

void DropdownManager::registerDropdown(DropdownButton* dropdown) {
    managedDropdowns.push_back(dropdown);
}

void DropdownManager::handleDropdownOpened(const EventData& data) {
    DropdownButton* openedDropdown = static_cast<DropdownButton*>(data.data);

    if (activeDropdown && activeDropdown != openedDropdown) {
        activeDropdown->close();
    }

    activeDropdown = openedDropdown;
}
