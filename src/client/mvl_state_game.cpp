#include "mvl_state_game.h"

#include <cmath>

using namespace mvl;
using namespace nlohmann;

void GameState::init(Client& client) {
    for (int i = 0; i < 10; i++) {
        tiles.emplace_back(Vec2i{32 + i * 16, 32});
    }

    player = other = {64, 16};
    vel = {0, 0};
    gravity = 3 / 13.f;
}

void GameState::handleCollision(bool trueForVerticalAndFalseForHorizontal) {
    for (auto tile : tiles) {
        SDL_Rect r0 = {(int)player.x, (int)player.y, 16, 16};
        SDL_Rect r1 = {tile.x, tile.y, 16, 16};

        if (SDL_HasIntersection(&r0, &r1)) {
            if (trueForVerticalAndFalseForHorizontal && vel.y != 0) {
                player.y = vel.y > 0 ? tile.y - 16 : tile.y + 16;
            }
            else if (!trueForVerticalAndFalseForHorizontal && vel.x != 0) {
                player.x = vel.x > 0 ? tile.x - 16 : tile.x + 16;
            }
        }
    }
}

void GameState::update(Window& window, Client& client, Clock& clock, StateHandler& stateHandler) {
    float speed = clock.getDelta() * .2f;

    Vec2f before = {player.x, player.y};

    bool up = window.input.keyHeld(SDL_SCANCODE_UP);
    bool down = window.input.keyHeld(SDL_SCANCODE_DOWN);
    bool left = window.input.keyHeld(SDL_SCANCODE_LEFT);
    bool right = window.input.keyHeld(SDL_SCANCODE_RIGHT);

    if (up) {
        vel.y = -speed;
    }
    if (down) {
        vel.y = speed;
    }
    if (!up && !down) {
        vel.y = 0;
    }

    player.y += vel.y;

    handleCollision(true);

    if (left) {
        vel.x = -speed;
    }
    if (right) {
        vel.x = speed;
    }
    if (!left && !right) {
        vel.x = 0;
    }

    player.x += vel.x;

    handleCollision(false);

    if (player.x != before.x || player.y != before.x) {
        client.send({{"type", "pos"}, {"x", player.x}, {"y", player.y}}, false);
    }

    auto packets = client.update();

    for (auto packet : packets) {
        json data = packet.second;

        if (data["type"] == "pos") {
            other.x = data["x"];
            other.y = data["y"];
        }
    }
}

void GameState::render(Window& window, Client& client, Assets& assets) {
    Vec2i camera = {Screen::res.x / 2 - (int)player.x - 8, Screen::res.y / 2 - (int)player.y - 8};

    for (auto tile : tiles) {
        window.renderSurface(assets.blueBricks, std::nullopt, SDL_Rect{tile.x + camera.x, tile.y + camera.y, 16, 16}, window.top);
    }

    bool which = client.role.value() == Client::Role::Mario;
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};

    window.fill({(int)other.x + camera.x, (int)other.y + camera.y, 16, 16}, !which ? red : green, window.top);
    window.fill({(int)player.x + camera.x, (int)player.y + camera.y, 16, 16}, which ? red : green, window.top);
}
