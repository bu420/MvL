#include "mvl_asset.h"

#include <stdio.h>
#include <SDL2/SDL_image.h>

Assets loadAssets(SDL_Renderer* renderer) {
    Assets assets = {
        .font = loadFont("asset/Nintendo-DS-BIOS (Edited).ttf", 24),
        .icon = loadSurface("asset/icon.png"),
        .numbers = loadTexture("asset/menu/numbers.png", renderer),
        .text = loadTexture("asset/menu/text.png", renderer),
        .menuBg = loadTexture("asset/menu/menu_bg.png", renderer),
        .menuDarkBg = loadTexture("asset/menu/menu_dark_bg.png", renderer),
        .banner = loadTexture("asset/menu/banner.png", renderer),
        .backArrow = loadTexture("asset/menu/back_arrow.png", renderer),
        .settings = loadTexture("asset/menu/settings.png", renderer),
        .button = loadTexture("asset/menu/button.png", renderer),
        .arrows = loadTexture("asset/menu/arrows.png", renderer),
        .borders = loadTexture("asset/menu/borders.png", renderer),
        .boxes = loadTexture("asset/menu/boxes.png", renderer),
        .levelIcons = loadTexture("asset/menu/level_icons.png", renderer)
    };

    return assets;
}

SDL_Surface* loadSurface(char* path) {
    SDL_Surface* surface = IMG_Load(path);

    if (surface == NULL) {
        printf("Could not load: %s\n", path);
    }

    return surface;
}

Texture loadTexture(char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = loadSurface(path);
    return (Texture){SDL_CreateTextureFromSurface(renderer, surface), {surface->w, surface->h}};
}

TTF_Font* loadFont(char* path, int size) {
    TTF_Font* font = TTF_OpenFont(path, size);

    if (font == NULL) {
        printf("Could not load font: %s\n", path);
    }

    return font;
}

Mix_Chunk* loadSound(char* path) {
    Mix_Chunk* sound = Mix_LoadWAV(path);

    if (sound == NULL) {
        printf("Could not load sound: %s\n", path);
    }

    return sound;
}

char* readFile(char* path) {
    FILE* file = fopen(path, "r");
    char* content;
    int length;

    if (!file) {
        printf("Could not open file: %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = malloc(length);

    int character, i = 0;
    while ((character = fgetc(file)) != EOF) {
        content[i++] = (char)character;
    }

    fclose(file);
    content[i] = '\0';

    return content;
}