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
#include <SDL2/SDL.h>

class Tab {
public:
    Tab(const std::string& tab_name, const std::string& icon_path, bool is_removable, SDL_Texture* tab_content);
    ~Tab();
    std::string get_name() const;
    SDL_Texture* get_icon() const;
    bool is_removable() const;
    SDL_Texture* get_content() const;
    void set_name(const std::string& new_name);
    void set_content(SDL_Texture* new_content);
    void set_removable(bool is_removable);

private:
    std::string name;
    SDL_Texture* icon;
    bool removable;
    SDL_Texture* content;
};

#endif // TAB_HPP
