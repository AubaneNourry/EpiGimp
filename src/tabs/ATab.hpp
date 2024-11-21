/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ATab.hpp
*/

#ifndef ATAB_HPP
#define ATAB_HPP

#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "../IUIElement.hpp"
#include "../FileManager.hpp"

class ATab : public IUIElement {
public:
    ATab(std::string tab_name, const std::string& icon_path, bool is_removable, IUIElement *owner, const std::vector<IUIElement*>& tab_content = {});
    ~ATab() = default;
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] SDL_Texture* get_icon() const;
    [[nodiscard]] bool is_removable() const;
    [[nodiscard]] std::vector<IUIElement*> get_content() const;
    void set_name(const std::string& new_name);
    void set_content(const std::vector<IUIElement*>& new_content);
    void set_removable(bool is_removable);
    void add_content(IUIElement *new_content);
    std::pair<int, int> getPosition() const override {
        return owner->getPosition();
    }
    std::pair<int, int> getDimensions() const override {
        return owner->getDimensions();
    }

protected:
    std::string name;
    SDL_Texture* icon;
    bool removable;
    std::vector<IUIElement*> content;
    IUIElement *owner;
};

#endif // ATAB_HPP
