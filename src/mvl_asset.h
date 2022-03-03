#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "mvl_math.h"

typedef struct {
    SDL_Texture* ptr;
    Vec2i size;
} Texture;

typedef struct {
    TTF_Font* font;
    SDL_Surface* icon;
    Texture numbers;
    Texture text;
    Texture menuBg;
    Texture menuDarkBg;
    Texture banner;
    Texture backArrow;
    Texture settings;
    Texture button;
    Texture arrows;
    Texture borders;
    Texture boxes;
    Texture levelIcons;
    Texture blueBricks;
} Assets;

SDL_Surface* loadSurface(char* path);
Texture loadTexture(char* path, SDL_Renderer* renderer);
TTF_Font* loadFont(char* path, int size);
Mix_Chunk* loadSound(char* path);
Assets loadAssets(SDL_Renderer* renderer);
char* readFile(char* path);