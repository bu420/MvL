#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <optional>
#include <string>

#include "mvl_singleton.h"
#include "mvl_math.h"
#include "mvl_window.h"

namespace mvl {
    class Renderer : public Singleton<Renderer> {
    public:
        void init();
        void renderSurface(SDL_Surface* surface, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen = std::nullopt);
        void renderText(std::string text, TTF_Font* font, SDL_Color color, Vec2i pos, std::optional<Screen> screen = std::nullopt);
        void fill(SDL_Rect area, SDL_Color color, std::optional<Screen> screen = std::nullopt);
        void renderMenuBackgrounds();

        SDL_Renderer* renderer;
    };
}