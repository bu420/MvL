#include "mvl_state_game.h"

#include <cmath>

#include "mvl_time.h"
#include "mvl_input.h"
#include "mvl_window.h"
#include "mvl_renderer.h"
#include "mvl_asset.h"

using namespace mvl;

void GameState::init() {
    for (int i = 0; i < 10; i++) {
        tiles.push_back({32 + i * 16, 32});
    }

    mario = {64, 16, 16, 16};
}

void GameState::update() {
    float speed = Clock::get().getDelta() * .2f;

    if (Input::get().keyHeld(SDL_SCANCODE_LEFT)) {
        mario.x -= speed;
    }
    if (Input::get().keyHeld(SDL_SCANCODE_RIGHT)) {
        mario.x += speed;
    }
    if (Input::get().keyHeld(SDL_SCANCODE_UP)) {
        mario.y -= speed;
    }
    if (Input::get().keyHeld(SDL_SCANCODE_DOWN)) {
        mario.y += speed;
    }
}

void GameState::render() {
    Vec2i camera = {Screen::res.x / 2 - (int)mario.x - (int)mario.w / 2, Screen::res.y / 2 - (int)mario.y - (int)mario.h / 2};

    for (auto tile : tiles) {
        Renderer::get().renderSurface(Assets::get().blueBricks, std::nullopt, SDL_Rect{tile.x + camera.x, tile.y + camera.y, 16, 16}, Renderer::get().top);
    }

    Renderer::get().fill({(int)mario.x + camera.x, (int)mario.y + camera.y, (int)mario.w, (int)mario.h}, {255, 0, 0, 255}, Renderer::get().top);
}
