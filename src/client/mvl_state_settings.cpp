#include "mvl_state_settings.h"

#include "mvl_state_select.h"

using namespace mvl;
using namespace nlohmann;

void SettingsState::init(Client& client) {
    selected = 0;
    okDst = SDL_Rect{96, 156, 64, 28};
}

void SettingsState::update(Window& window, Client& client, Clock& clock, StateHandler& stateHandler) {
    auto packets = client.update();

    for (auto packet : packets) {
        json data = packet.second;

        if (data["type"] == "ready") {
            stateHandler.push(new SelectState, client);
        }
        else if (data["type"] == "up") {
            selected = selected == 0 ? 3 : selected - 1;
        }
        else if (data["type"] == "down") {
            selected = selected == 3 ? 0 : selected + 1;
        }
    }

    if (client.role.value() == Client::Role::Mario) {
        if (window.input.keyPressed(SDL_SCANCODE_UP)) {
            selected = selected == 0 ? 3 : selected - 1;
            client.send({{"type", "up"}}, true);
        }
        if (window.input.keyPressed(SDL_SCANCODE_DOWN)) {
            selected = selected == 3 ? 0 : selected + 1;
            client.send({{"type", "down"}}, true);
        }

        window.regButton(okDst, window.bottom, [&]() -> void {
            okDst.x += 2;
            okDst.y += 2;

            clock.setInterval(250, [&]() -> bool {
                okDst.x -= 2;
                okDst.y -= 2;
                client.send({{"type", "ok"}}, true);
                return false;
            });
        });
    }
}

void SettingsState::render(Window& window, Client& client, Assets& assets) {
    window.renderMenuBackgrounds(assets);

    window.fill({16, 48, 224, 96}, {0, 0, 0, 255}, window.top);

    for (int i = 0; i < 4; i++) {
        window.renderSurface(assets.settings, SDL_Rect{0, selected == i ? 0 : 32, 256, 32}, SDL_Rect{0, 4 + i * 36, 256, 32}, window.bottom);
    }

    window.renderSurface(assets.button, std::nullopt, okDst, window.bottom);
    window.renderSurface(assets.text, SDL_Rect{96, 0, 32, 16}, SDL_Rect{okDst.x + 16, okDst.y + 4, 32, 16}, window.bottom);

    window.renderSurface(assets.net, SDL_Rect{0, 32, 16, 16}, SDL_Rect{2, 174, 16, 16}, window.bottom);
}
