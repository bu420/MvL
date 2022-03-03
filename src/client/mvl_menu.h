#pragma once

#include "mvl_asset.h"

#define gMaxButtonCount 32

typedef void (*ButtonCallback)(void* context);
typedef struct {
    SDL_Rect area;
    ButtonCallback callback;
    void* context;
} Button;

extern Button gButtons[gMaxButtonCount];
extern int gButtonCount;

void registerButton(Button button);
void handleButtons();
