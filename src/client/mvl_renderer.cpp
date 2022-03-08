#include "mvl_renderer.h"

#include "mvl_window.h"
#include "mvl_asset.h"

using namespace mvl;

void Renderer::init() {
    renderer = SDL_CreateRenderer(Window::get().window, -1, SDL_RENDERER_ACCELERATED);
    Window::get().top.renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Screen::res.x, Screen::res.y);
    Window::get().bottom.renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Screen::res.x, Screen::res.y);
}

void Renderer::renderTexture(SDL_Texture* texture, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen) {
    SDL_SetRenderTarget(renderer, screen ? screen.value().renderTexture : nullptr);
    SDL_RenderCopy(renderer, texture, src ? &src.value() : nullptr, dst ? &dst.value() : nullptr);
}

void Renderer::renderSurface(SDL_Surface* surface, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    renderTexture(texture, src, dst, screen);
    SDL_DestroyTexture(texture);
}

 void Renderer::renderText(std::string text, TTF_Font* font, SDL_Color color, Vec2i pos, std::optional<Screen> screen) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    renderSurface(surface, std::nullopt, SDL_Rect{pos.x, pos.y, surface->w, surface->h}, screen);
    SDL_FreeSurface(surface);
 }

void Renderer::fill(SDL_Rect area, SDL_Color color, std::optional<Screen> screen) {
    SDL_SetRenderTarget(renderer, screen ? screen.value().renderTexture : nullptr);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &area);
}

void Renderer::renderMenuBackgrounds() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 6; y++) {
            renderSurface(y == 0 || y == 5 ? Assets::get().menuDarkBg : Assets::get().menuBg, std::nullopt, SDL_Rect{x * 32, y * 32, 32, 32}, Window::get().top);
            renderSurface(Assets::get().menuBg, std::nullopt, SDL_Rect{x * 32, y * 32, 32, 32}, Window::get().bottom);
        }
    }
}
