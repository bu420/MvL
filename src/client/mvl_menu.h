#pragma once

#include "mvl_asset.h"

#define maxButtonCount 32

typedef void (*ButtonCallback)(void* context);
typedef struct {
    SDL_Rect area;
    ButtonCallback callback;
    void* context;
} Button;

extern Button buttons[maxButtonCount];
extern int buttonCount;

void registerButton(Button button);
void handleButtons();
