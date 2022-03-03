#include "mvl_state.h"

#include <assert.h>
#include <stdio.h>

#include "mvl_state_connect.h"
#include "mvl_state_settings.h"
#include "mvl_state_select.h"
#include "mvl_state_game.h"

StateHandler gStateHandler;

State gConnectState;
State gSettingsState;
State gSelectState;
State gGameState;

void stateHandlerInit() {
    gStateHandler.capacity = 8;
    gStateHandler.stack = malloc(gStateHandler.capacity * sizeof(State*));
    gStateHandler.top = -1;
}

void stateHandlerPush(State* state) {
    gStateHandler.stack[++gStateHandler.top] = state;
    assert(gStateHandler.top < gStateHandler.capacity);

    if (state->init) {
        state->init(state->context);
    }
}

void stateHandlerPop() {
    assert(gStateHandler.top >= 0);
    gStateHandler.stack[gStateHandler.top--] = NULL;
}

State* stateHandlerTop() {
    return gStateHandler.stack[gStateHandler.top];
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
    gConnectState.context = malloc(sizeof(ConnectState));
    gConnectState.init = initConnectState;
    gConnectState.update = updateConnectState;
    gConnectState.render = renderConnectState;

    gSettingsState.context = malloc(sizeof(SettingsState));
    gSettingsState.init = initSettingsState;
    gSettingsState.update = updateSettingsState;
    gSettingsState.render = renderSettingsState;

    gSelectState.context = malloc(sizeof(SelectState));
    gSelectState.init = initSelectState;
    gSelectState.update = updateSelectState;
    gSelectState.render = renderSelectState;

    gGameState.context = malloc(sizeof(GameState));
    gGameState.init = initGameState;
    gGameState.update = updateGameState;
    gGameState.render = renderGameState;
}