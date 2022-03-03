#include "mvl_state_game.h"

#include <math.h>

#include "mvl_state.h"
#include "mvl_ds.h"
#include "mvl_time.h"

void initGameState(void* context) {
    GameState* game = context;

    for (int i = 0; i < 10; i++) {
        game->tiles[i] = (Vec2i){32 + i * 16, 32};
    }

    game->mario = (SDL_FRect){64, 16, 16, 16};
}

void updateGameState(void* context, float delta) {
    GameState* game = context;

    float speed = delta * .2f;

    if (keyHeld(SDL_SCANCODE_LEFT)) {
        game->mario.x -= speed;
    }
    if (keyHeld(SDL_SCANCODE_RIGHT)) {
        game->mario.x += speed;
    }
    if (keyHeld(SDL_SCANCODE_UP)) {
        game->mario.y -= speed;
    }
    if (keyHeld(SDL_SCANCODE_DOWN)) {
        game->mario.y += speed;
    }
}

void renderGameState(void* context, float delta, SDL_Renderer* renderer, Assets assets) {
    GameState game = *(GameState*)context;
    SDL_Rect mario = {roundf(game.mario.x), roundf(game.mario.y), game.mario.w, game.mario.h};

    Vec2i camera = {resolution.x / 2 - mario.x - mario.w / 2, resolution.y / 2 - mario.y - mario.h / 2};

    for (int i = 0; i < 10; i++) {
        SDL_Rect dst = {top.x + game.tiles[i].x + camera.x, top.y + game.tiles[i].y + camera.y, 16, 16};
        SDL_RenderCopy(renderer, assets.blueBricks.ptr, NULL, &dst);
    }

    SDL_Rect marioDst = {top.x + mario.x + camera.x, top.y + mario.y + camera.y, mario.w, mario.h};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &marioDst);
}