#include "mvl_window.h"

using namespace mvl;

Vec2i Screen::res = {256, 192};
int Screen::gap = 16;

void Window::init(std::string title, bool hidden) {
    size = Vec2i{Screen::res.x + 2 * Screen::gap, 2 * Screen::res.y + 3 * Screen::gap};
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, hidden ? SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN : SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    top.renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Screen::res.x, Screen::res.y);
    bottom.renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Screen::res.x, Screen::res.y);
}

void Window::update(std::vector<SDL_Event> events) {
    SDL_GetWindowSize(window, &size.x, &size.y);

    input.update(events);

    top.pos.x = size.x / 2 - Screen::res.x / 2;
    top.pos.y = size.y / 2 - (2 * Screen::res.y + Screen::gap) / 2;

    bottom.pos.x = size.x / 2 - Screen::res.x / 2;
    bottom.pos.y = size.y / 2 + Screen::gap / 2;
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

void Window::renderTexture(SDL_Texture* texture, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen) {
    SDL_SetRenderTarget(renderer, screen ? screen.value().renderTexture : nullptr);
    SDL_RenderCopy(renderer, texture, src ? &src.value() : nullptr, dst ? &dst.value() : nullptr);
}

void Window::renderSurface(SDL_Surface* surface, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    renderTexture(texture, src, dst, screen);
    SDL_DestroyTexture(texture);
}

 void Window::renderText(std::string text, TTF_Font* font, SDL_Color color, Vec2i pos, std::optional<Screen> screen) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    renderSurface(surface, std::nullopt, SDL_Rect{pos.x, pos.y, surface->w, surface->h}, screen);
    SDL_FreeSurface(surface);
 }

void Window::fill(SDL_Rect area, SDL_Color color, std::optional<Screen> screen) {
    SDL_SetRenderTarget(renderer, screen ? screen.value().renderTexture : nullptr);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &area);
}

void Window::renderMenuBackgrounds(Assets& assets) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 6; y++) {
            renderSurface(assets.menuBg, SDL_Rect{0, y == 0 || y == 5 ? 32 : 0, 32, 32}, SDL_Rect{x * 32, y * 32, 32, 32}, top);
            renderSurface(assets.menuBg, SDL_Rect{0, 0, 32, 32}, SDL_Rect{x * 32, y * 32, 32, 32}, bottom);
        }
    }
}

void Window::regButton(SDL_Rect area, std::optional<Screen> screen, std::function<void()> callback) {
    if (screen) {
        area.x += screen.value().pos.x;
        area.y += screen.value().pos.y;
    }

    buttons.emplace_back(std::make_pair(area, callback));
}

void Window::handleButtons() {
    if (input.buttonClicked(SDL_BUTTON_LEFT)) {
        Vec2i pos = input.mousePos();
        SDL_Point point = {pos.x, pos.y};

        for (auto button : buttons) {
            if (SDL_PointInRect(&point, &button.first)) {
                button.second();
            }
        }
    }

    buttons.clear();
}