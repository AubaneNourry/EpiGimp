/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Tab.hpp
*/

#ifndef TAB_HPP
#define TAB_HPP

#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "IUIElement.hpp"
#include "FileManager.hpp"

class Tab {
public:
    Tab(std::string  tab_name, const std::string& icon_path, bool is_removable, const std::vector<IUIElement*>& tab_content = {});
    ~Tab() = default;
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] SDL_Texture* get_icon() const;
    [[nodiscard]] bool is_removable() const;
    [[nodiscard]] std::vector<IUIElement*> get_content() const;
    void set_name(const std::string& new_name);
    void set_content(const std::vector<IUIElement*>& new_content);
    void set_removable(bool is_removable);
    void render(SDL_Renderer* renderer);
    void add_content(IUIElement *new_content);

private:
    std::string name;
    SDL_Texture* icon;
    bool removable;
    std::vector<IUIElement*> content;
};

#endif // TAB_HPP
