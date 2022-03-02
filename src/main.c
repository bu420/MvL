#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "mvl_ds.h"
#include "mvl_input.h"
#include "mvl_state.h"
#include "mvl_time.h"
#include "mvl_menu.h"

void handleEvents() {
    SDL_Event* mouseEvents = malloc(16 * sizeof(SDL_Event));
    int count = 0;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                exit(0);
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                mouseEvents[count++] = e;
                break;
        }
    }

    inputUpdate(mouseEvents, count);
    free(mouseEvents);
}

int main(int argc, char** argv) {
    assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0);
    assert(TTF_Init() == 0);
    assert(Mix_OpenAudio(44100, AUDIO_S16SYS, 4, 512) == 0);

    SDL_Window* window = SDL_CreateWindow("MvL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution.x + 2 * gap, 2 * resolution.y + 3 * gap, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Assets assets = loadAssets(renderer);
    SDL_SetWindowIcon(window, assets.icon);
    timeInit();
    inputInit();
    stateHandlerInit();
    statesInit();

    stateHandlerPush(&settings);

    while (true) {
        // Update.

        tick();
        handleEvents();

        Vec2i size;
        SDL_GetWindowSize(window, &size.x, &size.y);
        top = (Vec2i){size.x / 2 - resolution.x / 2, size.y / 2 - (2 * resolution.y + gap) / 2};
        bottom = (Vec2i){size.x / 2 - resolution.x / 2, size.y / 2 + gap / 2};

        stateHandlerUpdate(clock.delta);
        handleButtons();

        // Render.

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_Rect topDst = {top.x, top.y, resolution.x, resolution.y};
        SDL_Rect bottomDst = {bottom.x, bottom.y, resolution.x, resolution.y};
        SDL_RenderFillRect(renderer, &topDst);
        SDL_RenderFillRect(renderer, &bottomDst);

        stateHandlerRender(clock.delta, renderer, assets);

        SDL_RenderPresent(renderer);
    }
}