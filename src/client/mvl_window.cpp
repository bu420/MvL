#include "mvl_window.h"

using namespace mvl;

Vec2i Screen::res = {256, 192};
int Screen::gap = 16;

void Window::init(std::string title) {
    size = Vec2i{Screen::res.x + 2 * Screen::gap, 2 * Screen::res.y + 3 * Screen::gap};
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, SDL_WINDOW_RESIZABLE);
}

void Window::update() {
    SDL_GetWindowSize(window, &size.x, &size.y);

    top.pos.x = size.x / 2 - Screen::res.x / 2;
    top.pos.y = size.y / 2 - (2 * Screen::res.y + Screen::gap) / 2;

    bottom.pos.x = size.x / 2 - Screen::res.x / 2;
    bottom.pos.y = size.y / 2 + Screen::gap / 2;
}

void Window::setIcon(SDL_Surface* icon) {
    SDL_SetWindowIcon(window, icon);
}