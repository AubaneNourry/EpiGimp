/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ToolTab.hpp
*/

#ifndef TOOLTAB_HPP
#define TOOLTAB_HPP

#include <SDL2/SDL.h>
#include "ATab.hpp"

class ToolTab final : public ATab {
public:
    ToolTab(std::string tab_name, const std::string& icon_path, bool is_removable, IUIElement *owner, const std::vector<IUIElement*>& tab_content = {});
    ~ToolTab() override = default;
    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;
};

#endif // TOOLTAB_HPP
