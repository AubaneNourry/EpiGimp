/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DropdownManager.hpp
*/

#ifndef DROPDOWNMANAGER_HPP
#define DROPDOWNMANAGER_HPP

#include "../EventManager.hpp"
#include <vector>

class DropdownButton;

class DropdownManager {
public:
    static DropdownManager& getInstance();

    void initialize();
    void registerDropdown(DropdownButton* dropdown);
    void handleDropdownOpened(const EventData& data);

private:
    DropdownManager();
    ~DropdownManager() = default;

    std::vector<DropdownButton*> managedDropdowns;
    DropdownButton* activeDropdown;
};

#endif // DROPDOWNMANAGER_HPP
