#include "mvl_state_game.h"

#include <cmath>

#include "mvl_time.h"
#include "mvl_input.h"
#include "mvl_window.h"
#include "mvl_renderer.h"
#include "mvl_asset.h"
#include "mvl_client.h"
#include "mvl_global_state.h"

using namespace mvl;
using namespace nlohmann;

void GameState::init() {
    for (int i = 0; i < 10; i++) {
        tiles.push_back({32 + i * 16, 32});
    }

    player = other = {64, 16};
}

void GameState::update() {
    float speed = Clock::get().getDelta() * .2f;

    Vec2f before = {player.x, player.y};

    if (Input::get().keyHeld(SDL_SCANCODE_LEFT)) {
        player.x -= speed;
    }
    if (Input::get().keyHeld(SDL_SCANCODE_RIGHT)) {
        player.x += speed;
    }
    if (Input::get().keyHeld(SDL_SCANCODE_UP)) {
        player.y -= speed;
    }
    if (Input::get().keyHeld(SDL_SCANCODE_DOWN)) {
        player.y += speed;
    }

    if (player.x != before.x || player.y != before.x) {
        Client::get().send({{"type", "pos"}, {"x", player.x}, {"y", player.y}}, false);
    }

    auto packets = Client::get().update();

    for (auto packet : packets) {
        json data = packet.second;

        if (data["type"] == "pos") {
            other.x = data["x"];
            other.y = data["y"];
        }
    }
}

void GameState::render() {
    Vec2i camera = {Screen::res.x / 2 - (int)player.x - 8, Screen::res.y / 2 - (int)player.y - 8};

    for (auto tile : tiles) {
        Renderer::get().renderSurface(Assets::get().blueBricks, std::nullopt, SDL_Rect{tile.x + camera.x, tile.y + camera.y, 16, 16}, Renderer::get().top);
    }

    bool which = GlobalState::get().role.value() == GlobalState::Role::Mario;
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};

    Renderer::get().fill({(int)player.x + camera.x, (int)player.y + camera.y, 16, 16}, which ? red : green, Renderer::get().top);
    Renderer::get().fill({(int)other.x + camera.x, (int)other.y + camera.y, 16, 16}, !which ? red : green, Renderer::get().top);
}
