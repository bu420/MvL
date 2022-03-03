#pragma once

#include "mvl_asset.h"

typedef struct {
    SDL_Rect okDst;
} ConnectState;

void initConnectState(void* context);
void updateConnectState(void* context, float delta);
void renderConnectState(void* context, float delta, SDL_Renderer* renderer, Assets assets);