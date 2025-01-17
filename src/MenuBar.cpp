/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.cpp
*/

#include "MenuBar.hpp"
#include "Application.hpp"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

void MenuBar::render(SDL_Renderer* renderer)
{
    bool my_tool_active = true;
    float my_color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 viewport_size = io.DisplaySize;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    float toolbar_height = 0.0f;
    ImGui::SetNextWindowSize(ImVec2(viewport_size.x, toolbar_height));

    ImGui::Begin("Tools", &my_tool_active,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("new", "Ctrl+N")) {FileManager::getInstance().newImageField();}
            if (ImGui::MenuItem("open", "Ctrl+O"))   {FileManager::getInstance().openImage();}
            if (ImGui::MenuItem("save", "Ctrl+S"))  {FileManager::getInstance().saveImage();}
            if (ImGui::MenuItem("close", "Ctrl+W"))  {Application::getInstance().quit();}
            if (ImGui::MenuItem("quit", "Ctrl+Q"))  {Application::getInstance().quit();}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Import image", "Ctrl+O")) {FileManager::getInstance().openImage();}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}
