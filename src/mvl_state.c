#include "mvl_state.h"

#include <assert.h>
#include <stdio.h>

#include "mvl_state_settings.h"
#include "mvl_state_select.h"

StateHandler stateHandler;

State settings;
State select;

void stateHandlerInit() {
    stateHandler.capacity = 8;
    stateHandler.stack = malloc(stateHandler.capacity * sizeof(State*));
    stateHandler.top = -1;
}

void stateHandlerPush(State* state) {
    stateHandler.stack[++stateHandler.top] = state;
    assert(stateHandler.top < stateHandler.capacity);

    if (state->init) {
        state->init(state->context);
    }
}

void stateHandlerPop() {
    assert(stateHandler.top >= 0);
    stateHandler.stack[stateHandler.top--] = NULL;
}

State* stateHandlerTop() {
    return stateHandler.stack[stateHandler.top];
}

void stateHandlerUpdate(float delta) {
    State* state = stateHandlerTop();

    if (state->update) {
        state->update(state->context, delta);
    }
}

void stateHandlerRender(float delta, SDL_Renderer* renderer, Assets assets) {
    State* state = stateHandlerTop();

    if (state->render) {
        state->render(state->context, delta, renderer, assets);
    }
}

void statesInit() {
    settings.context = malloc(sizeof(LevelSettings));
    settings.init = initLevelSettings;
    settings.update = updateLevelSettings;
    settings.render = renderLevelSettings;

    select.context = malloc(sizeof(LevelSelect));
    select.init = initLevelSelect;
    select.update = updateLevelSelect;
    select.render = renderLevelSelect;
}