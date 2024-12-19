/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "tabs/Dock.hpp"
#include "MenuBar.hpp"
#include "image/ImageField.hpp"
#include "events/Shortcuts.hpp"
#include "image/Tools.hpp"
#include "Layers.hpp"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>

void Application::initDearImGUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void Application::initFonts() {
    io->Fonts->AddFontDefault();
    std::string fontStr;
    #ifdef _WIN32
        fontStr = "C:\\Windows\\Fonts\\arial.ttf";
    #elif defined(__linux__)
        fontStr = "/usr/share/fonts/liberation-sans/LiberationSans-Regular.ttf";
    #else
        return;
    #endif
    ImFont* imFont = io->Fonts->AddFontFromFileTTF(fontStr.c_str(), 18.0f, nullptr);
    IM_ASSERT(imFont != nullptr);
    font = TTF_OpenFont(fontStr.c_str(), 24);
    if (font == NULL) {
        fprintf(stderr, "error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

Application::Application(const char *appName, const char *defaultImagePath) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    #ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_Log("Error creating SDL_Renderer!");
        exit(EXIT_FAILURE);
    }
    status = 0;

    initDearImGUI();
    initFonts();
    running = true;
}

int Application::run() {
    while (status == 0 && !EventManager::getInstance().getQuitStatus() && running) {
        EventManager::getInstance().handleEvents();
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Color Picker", nullptr, ImGuiWindowFlags_NoCollapse);
        Uint32 color = Tools::getInstance().getColor();
        float r = (color >> 24) & 0xFF;
    	float g = (color >> 16) & 0xFF;
    	float b = (color >> 8) & 0xFF;

        float colorPicker[4] = {r / 255, g / 255, b / 255, 255};
        ImGui::ColorEdit4("Color", (float*)&color, ImGuiColorEditFlags_NoInputs);
        Tools::getInstance().setColor(color);
        ImGui::End();

        render();
    }
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return status;
}

void Application::init() {
    menuBar = new MenuBar();
    layers = new Layers();
    imageField = new ImageField(200, 200, renderer);
    FileManager::getInstance().setImageField(imageField);
    EventManager::getInstance().registerElement(menuBar);
    EventManager::getInstance().registerElement(imageField);
    Shortcuts::getInstance().registerBaseShortcuts();
    Tools::getInstance().init();
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
}

void Application::render() const
{
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);

    SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    SDL_RenderClear(renderer);

    imageField->render(renderer);
    menuBar->render(renderer);
    layers->render(renderer);
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
}

int Application::getScreenWidth() const
{
    int width;
    SDL_GetRendererOutputSize(renderer, &width, nullptr);
    return width;
}

int Application::getScreenHeight() const
{
    int height;
    SDL_GetRendererOutputSize(renderer, nullptr, &height);
    return height;
}

TTF_Font *Application::getFont() const
{
    return font;
}

void Application::quit() {
    running = false;
}
