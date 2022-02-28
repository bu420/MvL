#pragma once

#include "mvl_asset.h"

#define levelCount 5
#define maxButtonCount 32

typedef void (*ButtonCallback)(void* context);
typedef struct {
    SDL_Rect area;
    ButtonCallback callback;
    void* context;
} Button;

typedef struct {
    SDL_Rect src;
    SDL_Rect dst;
} LevelIcon;

typedef struct {
    SDL_Rect okDst;
    SDL_Rect backArrowDst;
} LevelSettings;

typedef struct {
    LevelIcon levelIcons[levelCount];
    int selected;

    SDL_Rect backArrowDst;
} LevelSelect;

extern Button buttons[maxButtonCount];
extern int buttonCount;

void registerButton(Button button);
void handleButtons();

void initLevelSettings(void* context);
void updateLevelSettings(void* context, float delta);
void renderLevelSettings(void* context, float delta, SDL_Renderer* renderer, Assets assets);

void initLevelSelect(void* context);
void updateLevelSelect(void* context, float delta);
void renderLevelSelect(void* context, float delta, SDL_Renderer* renderer, Assets assets);