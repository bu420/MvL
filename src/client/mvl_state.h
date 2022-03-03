#pragma once

#include "mvl_input.h"
#include "mvl_asset.h"

typedef void (*InitCallback)(void* context);
typedef void (*UpdateCallback)(void* context, float delta);
typedef void (*RenderCallback)(void* context, float delta, SDL_Renderer* renderer, Assets assets);

typedef struct {
    void* context;
    InitCallback init;
    UpdateCallback update;
    RenderCallback render;
} State;

typedef struct {
    State** stack;
    int capacity;
    int top;
} StateHandler;

extern StateHandler stateHandler;

extern State settings;
extern State select;
extern State game;

void stateHandlerInit();
void stateHandlerPush(State* state);
void stateHandlerPop();
State* stateHandlerTop();
void stateHandlerUpdate(float delta);
void stateHandlerRender(float delta, SDL_Renderer* renderer, Assets assets);

void statesInit();