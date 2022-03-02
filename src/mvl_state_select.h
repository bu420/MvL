#pragma once

#include "mvl_asset.h"

#define levelCount 5

typedef struct {
    SDL_Rect src;
    SDL_Rect dst;
} LevelIcon;

typedef struct {
    LevelIcon levelIcons[levelCount];
    int selected;

    SDL_Rect backArrowDst;
} LevelSelect;

void initLevelSelect(void* context);
void updateLevelSelect(void* context, float delta);
void renderLevelSelect(void* context, float delta, SDL_Renderer* renderer, Assets assets);