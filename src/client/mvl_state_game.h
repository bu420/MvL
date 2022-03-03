#pragma once

#include "mvl_asset.h"

typedef struct {
    Vec2i tiles[10];

    SDL_FRect mario;
} GameState;

void initGameState(void* context);
void updateGameState(void* context, float delta);
void renderGameState(void* context, float delta, SDL_Renderer* renderer, Assets assets);