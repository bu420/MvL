#include "mvl_window.h"

#include "mvl_renderer.h"

using namespace mvl;

void Window::init(std::string title, bool hidden) {
    size = Vec2i{Screen::res.x + 2 * Screen::gap, 2 * Screen::res.y + 3 * Screen::gap};
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, hidden ? SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN : SDL_WINDOW_RESIZABLE);
}

void Window::update() {
    SDL_GetWindowSize(window, &size.x, &size.y);

    Renderer::get().top.pos.x = size.x / 2 - Screen::res.x / 2;
    Renderer::get().top.pos.y = size.y / 2 - (2 * Screen::res.y + Screen::gap) / 2;

    Renderer::get().bottom.pos.x = size.x / 2 - Screen::res.x / 2;
    Renderer::get().bottom.pos.y = size.y / 2 + Screen::gap / 2;
}

void Window::setIcon(SDL_Surface* icon) {
    SDL_SetWindowIcon(window, icon);
}

void Window::hide() {
    SDL_HideWindow(window);
}

void Window::show() {
    SDL_ShowWindow(window);
}

void Window::setTitle(std::string title) {
    SDL_SetWindowTitle(window, title.c_str());
}