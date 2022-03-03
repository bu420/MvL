#pragma once

#include "mvl_asset.h"

typedef struct {
    int selected;
    SDL_Rect okDst;
    SDL_Rect backArrowDst;
} SettingsState;

void initSettingsState(void* context);
void updateSettingsState(void* context, float delta);
void renderSettingsState(void* context, float delta, SDL_Renderer* renderer, Assets assets);