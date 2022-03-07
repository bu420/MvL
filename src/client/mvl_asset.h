#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

#include "mvl_singleton.h"

namespace mvl {
    class Assets : public Singleton<Assets> {
    public:
        void load();

        TTF_Font* font;
        SDL_Surface* icon;
        SDL_Surface* numbers;
        SDL_Surface* text;
        SDL_Surface* menuBg;
        SDL_Surface* menuDarkBg;
        SDL_Surface* banner;
        SDL_Surface* backArrow;
        SDL_Surface* settings;
        SDL_Surface* button;
        SDL_Surface* arrows;
        SDL_Surface* borders;
        SDL_Surface* boxes;
        SDL_Surface* levelIcons;
        SDL_Surface* blueBricks;

    private:
        SDL_Surface* loadSurface(std::string path);
        TTF_Font* loadFont(std::string path, int size);
        Mix_Chunk* loadSound(std::string path);
        std::string readFile(std::string path);
    };
}