#pragma once

#include "mvl_asset.h"

typedef struct {
    int selected;
    SDL_Rect okDst;
    SDL_Rect backArrowDst;
} LevelSettings;

void initLevelSettings(void* context);
void updateLevelSettings(void* context, float delta);
void renderLevelSettings(void* context, float delta, SDL_Renderer* renderer, Assets assets);