/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** MenuBar.cpp
*/

#include "MenuBar.hpp"
#include "Application.hpp"

MenuBar::MenuBar(int x) : rect({0, 0, x, 25})
{
    Button *button_3 = new Button("opt3", new SDL_Rect({0, 0, 0, 0}));
    Button *button_4 = new Button("opt4", new SDL_Rect({0, 0, 0, 0}));
    Button *button_5 = new Button("opt5", new SDL_Rect({0, 0, 0, 0}));
   
    init_file_menu();
    _menu_items.push_back(new DropdownButton("Edit", new SDL_Rect({100, 0, 100, 25}), 25, {button_5}));
    _menu_items.push_back(new DropdownButton("View", new SDL_Rect({200, 0, 100, 25}), 25, {button_3}));
    _menu_items.push_back(new DropdownButton("Help", new SDL_Rect({300, 0, 100, 25}), 25, {button_4}));
}

struct PopupWindowData {
    std::string title;
    int width;
    int height;
};

int PopupWindowThread(void* data) {
    PopupWindowData* popupData = static_cast<PopupWindowData*>(data);

    SDL_Window* popupWindow = SDL_CreateWindow(popupData->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, popupData->width, popupData->height, SDL_WINDOW_SHOWN);
    if (!popupWindow) {
        std::cerr << "Failed to create popup window: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* popupRenderer = SDL_CreateRenderer(popupWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!popupRenderer) {
        std::cerr << "Failed to create popup renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(popupWindow);
        return -1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }

        }
        std::cout << "Popup window running" << std::endl;
        SDL_SetRenderDrawColor(popupRenderer, 50, 50, 50, 255);
        SDL_RenderClear(popupRenderer);

        SDL_Rect rect = { popupData->width / 4, popupData->height / 4, popupData->width / 2, popupData->height / 2 };
        SDL_SetRenderDrawColor(popupRenderer, 255, 0, 0, 255);
        SDL_RenderFillRect(popupRenderer, &rect);
        SDL_RenderPresent(popupRenderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(popupRenderer);
    SDL_DestroyWindow(popupWindow);
    delete popupData;
    return 0;
}

void createPopupWindowAsync(const std::string& title, int width, int height) {
    PopupWindowData* popupData = new PopupWindowData{ title, width, height };

    SDL_Thread* popupThread = SDL_CreateThread(PopupWindowThread, "PopupThread", static_cast<void*>(popupData));
    if (!popupThread) {
        std::cerr << "Failed to create popup thread: " << SDL_GetError() << std::endl;
        delete popupData;
    } else {
        // Wait for the thread to finish to avoid potential memory issues
        int threadReturnValue;
        SDL_WaitThread(popupThread, &threadReturnValue);
        std::cout << "Popup thread finished with return value: " << threadReturnValue << std::endl;
    }
}

void MenuBar::init_file_menu()
{
    Button *newbtn = new Button("new", new SDL_Rect({0, 0, 0, 0}));
    newbtn->setOnClick([]() {
        FileManager::getInstance().newImageField();
    });
    Button *openbtn = new Button("open", new SDL_Rect({0, 0, 0, 0}));
    openbtn->setOnClick([]() {
        createPopupWindowAsync("Open", 400, 400);
    });
    Button *savebtn = new Button("save", new SDL_Rect({0, 0, 0, 0}));
    savebtn->setOnClick([]() {
        FileManager::getInstance().saveImage();
    });
    Button *closebtn = new Button("close", new SDL_Rect({0, 0, 0, 0}));
    Button *quitbtn = new Button("quit", new SDL_Rect({0, 0, 0, 0}));
    quitbtn->setOnClick([]() {
        Application::getInstance().quit();
    });
    _menu_items.push_back(new DropdownButton("File", new SDL_Rect({0, 0, 100, 25}), 25, {newbtn, openbtn, savebtn, closebtn, quitbtn}));
}

void MenuBar::init_edit_menu()
{
}

void MenuBar::init_select_menu()
{
}

void MenuBar::render(SDL_Renderer* renderer)
{
    SDL_Color color = UICOLOR;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    rect.w = windowWidth;
    SDL_RenderFillRect(renderer, &rect);
    for (auto& item : _menu_items) {
        item->render(renderer);
    }
}
