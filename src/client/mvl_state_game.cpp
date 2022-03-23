#include "mvl_state_game.h"

#include <cmath>

#include "mvl_time.h"
#include "mvl_input.h"
#include "mvl_window.h"
#include "mvl_asset.h"
#include "mvl_client.h"
#include "mvl_global_state.h"

using namespace mvl;
using namespace nlohmann;

void GameState::init(Client& client) {
    for (int i = 0; i < 10; i++) {
        tiles.push_back({32 + i * 16, 32});
    }

    player = other = {64, 16};
}

void GameState::update(Window& window, Client& client, Input& input, Buttons& buttons, Clock& clock, StateHandler& stateHandler, GlobalState& globalState) {
    float speed = clock.getDelta() * .2f;

    Vec2f before = {player.x, player.y};

    if (input.keyHeld(SDL_SCANCODE_LEFT)) {
        player.x -= speed;
    }
    if (input.keyHeld(SDL_SCANCODE_RIGHT)) {
        player.x += speed;
    }
    if (input.keyHeld(SDL_SCANCODE_UP)) {
        player.y -= speed;
    }
    if (input.keyHeld(SDL_SCANCODE_DOWN)) {
        player.y += speed;
    }

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

void GameState::render(Window& window, Assets& assets, GlobalState& globalState) {
    Vec2i camera = {Screen::res.x / 2 - (int)player.x - 8, Screen::res.y / 2 - (int)player.y - 8};

    for (auto tile : tiles) {
        window.renderSurface(assets.blueBricks, std::nullopt, SDL_Rect{tile.x + camera.x, tile.y + camera.y, 16, 16}, window.top);
    }

    bool which = globalState.role.value() == GlobalState::Role::Mario;
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};

    window.fill({(int)other.x + camera.x, (int)other.y + camera.y, 16, 16}, !which ? red : green, window.top);
    window.fill({(int)player.x + camera.x, (int)player.y + camera.y, 16, 16}, which ? red : green, window.top);
}
