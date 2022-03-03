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
} SelectState;

void initSelectState(void* context);
void updateSelectState(void* context, float delta);
void renderSelectState(void* context, float delta, SDL_Renderer* renderer, Assets assets);