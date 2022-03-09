#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <optional>
#include <string>

#include "mvl_singleton.h"
#include "mvl_math.h"

namespace mvl {
    struct Screen {
        static Vec2i res;
        static int gap;
        Vec2i pos;
        SDL_Texture* renderTexture;
    };

    class Renderer : public Singleton<Renderer> {
    public:
        void init();
        void renderTexture(SDL_Texture* texture, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen = std::nullopt);
        void renderSurface(SDL_Surface* surface, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen = std::nullopt);
        void renderText(std::string text, TTF_Font* font, SDL_Color color, Vec2i pos, std::optional<Screen> screen = std::nullopt);
        void fill(SDL_Rect area, SDL_Color color, std::optional<Screen> screen = std::nullopt);
        void renderMenuBackgrounds();

        SDL_Renderer* renderer;
        Screen top;
        Screen bottom;
    };
}