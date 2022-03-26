#include "mvl_state_select.h"

#include <SDL2/SDL.h>

#include "mvl_state_game.h"
#include "mvl_state_net_error.h"

using namespace mvl;
using namespace nlohmann;

void SelectState::init(Window& window, Client& client) {
    icons[0] = {{0, 0, 48, 48}, {32, 56, 48, 48}};
    icons[1] = {{0, 48, 48, 48}, {104, 56, 48, 48}};
    icons[2] = {{0, 96, 48, 48}, {176, 56, 48, 48}};
    icons[3] = {{0, 144, 48, 48}, {66, 124, 48, 48}};
    icons[4] = {{0, 192, 48, 48}, {140, 124, 48, 48}};
    selected = 0;
    backArrowDst = {224, 160, 30, 30};
}

void SelectState::update(Window& window, Client& client, Clock& clock, StateHandler& stateHandler) {
    auto packets = client.update([&]() -> void {
        stateHandler.push(new NetErrorState, window, client);
    });

    for (auto packet : packets) {
        json data = packet.second;

        if (data["type"] == "ready") {
            stateHandler.pop();
            stateHandler.push(new GameState, window, client);
        }
        else if (data["type"] == "back") {
            stateHandler.pop();
        }
        else if (data["type"] == "left") {
            selected = selected == 0 ? 4 : selected - 1;
        }
        else if (data["type"] == "right") {
            selected = selected == 4 ? 0 : selected + 1;
        }
    }

    if (client.role.value() == Client::Role::Mario) {
        if (window.input.keyPressed(SDL_SCANCODE_LEFT)) {
            selected = selected == 0 ? 4 : selected - 1;
            client.send({{"type", "left"}}, true);
        }
        if (window.input.keyPressed(SDL_SCANCODE_RIGHT)) {
            selected = selected == 4 ? 0 : selected + 1;
            client.send({{"type", "right"}}, true);
        }

        for (auto icon : icons) {
            window.regButton(icon.second, window.bottom, [&]() -> void {
                client.send({{"type", "select"}}, true);
            });
        }

        window.regButton(backArrowDst, window.bottom, [&]() -> void {
            backArrowDst.x += 2;
            backArrowDst.y += 2;

            clock.setInterval(250, [&]() -> bool {
                backArrowDst.x -= 2;
                backArrowDst.y -= 2;
                client.send({{"type", "back"}}, true);
                return false;
            });
        });
    }
}

void SelectState::render(Window& window, Client& client, Assets& assets) {
    window.renderMenuBackgrounds(assets);

    window.fill({16, 48, 224, 96}, {0, 0, 0, 255}, window.top);

    for (int i = 0; i < 2; i++) {
        window.renderSurface(assets.banner, SDL_Rect{24, 0, 24, 32}, SDL_Rect{i * 24, 8, 24, 32}, window.bottom);
    }
    
    for (int i = 0; i < 7; i++) {
        window.renderSurface(assets.banner, SDL_Rect{0, 0, 24, 32}, SDL_Rect{48 + i * 24, 8, 24, 32}, window.bottom);
    }

    for (int i = 0; i < 2; i++) {
        window.renderSurface(assets.banner, SDL_Rect{24, 0, 24, 32}, SDL_Rect{208 + i * 24, 8, 24, 32}, window.bottom);
    }

    for (int i = 0; i < 5; i++) {
        window.renderSurface(assets.borders, SDL_Rect{0, selected == i ? 0 : 64, 64, 64}, SDL_Rect{icons[i].second.x - 8, icons[i].second.y - 8, 64, 64}, window.bottom);
        window.renderSurface(assets.levelIcons, SDL_Rect{0, icons[i].first.y, 48, 48}, SDL_Rect{icons[i].second.x, icons[i].second.y, 48, 48}, window.bottom);
    }

    window.renderSurface(assets.backArrow, std::nullopt, backArrowDst, window.bottom);

    window.renderSurface(assets.net, SDL_Rect{0, 32, 16, 16}, SDL_Rect{2, 174, 16, 16}, window.bottom);
}
