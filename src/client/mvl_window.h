#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <optional>
#include <vector>
#include <utility>
#include <functional>

#include "mvl_math.h"
#include "mvl_asset.h"
#include "mvl_input.h"

namespace mvl {
    struct Screen {
        static Vec2i res;
        static int gap;
        Vec2i pos;
        SDL_Texture* renderTexture;
    };

    class Window {
    public:
        void init(std::string title, bool hidden);
        void update();
        void setIcon(SDL_Surface* icon);
        void hide();
        void show();
        void setTitle(std::string title);

        void renderTexture(SDL_Texture* texture, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen = std::nullopt);
        void renderSurface(SDL_Surface* surface, std::optional<SDL_Rect> src, std::optional<SDL_Rect> dst, std::optional<Screen> screen = std::nullopt);
        void renderText(std::string text, TTF_Font* font, SDL_Color color, Vec2i pos, std::optional<Screen> screen = std::nullopt);
        void fill(SDL_Rect area, SDL_Color color, std::optional<Screen> screen = std::nullopt);
        void renderMenuBackgrounds(Assets& assets);

        void regButton(SDL_Rect area, std::optional<Screen> screen, std::function<void()> callback);
        void handleButtons();

        SDL_Window* window;
        Vec2i size;

        SDL_Renderer* renderer;
        Screen top;
        Screen bottom;

        Input input;

        std::vector<std::pair<SDL_Rect, std::function<void()>>> buttons;
    };
}