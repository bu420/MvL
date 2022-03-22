#include "mvl_state_settings.h"

#include "mvl_input.h"
#include "mvl_menu.h"
#include "mvl_time.h"
#include "mvl_renderer.h"
#include "mvl_asset.h"
#include "mvl_window.h"
#include "mvl_state_select.h"
#include "mvl_global_state.h"
#include "mvl_client.h"

using namespace mvl;
using namespace nlohmann;

void SettingsState::init() {
    selected = 0;
    okDst = SDL_Rect{96, 156, 64, 28};
}

void SettingsState::update() {
    auto packets = Client::get().update();

    for (auto packet : packets) {
        json data = packet.second;

        if (data["type"] == "ready") {
            StateHandler::get().push(new SelectState);
        }
        else if (data["type"] == "up") {
            selected = selected == 0 ? 3 : selected - 1;
        }
        else if (data["type"] == "down") {
            selected = selected == 3 ? 0 : selected + 1;
        }
    }

    if (GlobalState::get().role.value() == GlobalState::Role::Mario) {
        if (Input::get().keyPressed(SDL_SCANCODE_UP)) {
            selected = selected == 0 ? 3 : selected - 1;
            Client::get().send({{"type", "up"}}, true);
        }
        if (Input::get().keyPressed(SDL_SCANCODE_DOWN)) {
            selected = selected == 3 ? 0 : selected + 1;
            Client::get().send({{"type", "down"}}, true);
        }

        Buttons::get().reg(okDst, Renderer::get().bottom, [this]() -> void {
            okDst.x += 2;
            okDst.y += 2;

            Clock::get().setInterval(250, [this]() -> bool {
                okDst.x -= 2;
                okDst.y -= 2;
                Client::get().send({{"type", "ok"}}, true);
                return false;
            });
        });
    }
}

void SettingsState::render() {
    Renderer::get().renderMenuBackgrounds();

    Renderer::get().fill({16, 48, 224, 96}, {0, 0, 0, 255}, Renderer::get().top);

    for (int i = 0; i < 4; i++) {
        Renderer::get().renderSurface(Assets::get().settings, SDL_Rect{0, selected == i ? 0 : 32, 256, 32}, SDL_Rect{0, 4 + i * 36, 256, 32}, Renderer::get().bottom);
    }

    Renderer::get().renderSurface(Assets::get().button, std::nullopt, okDst, Renderer::get().bottom);
    Renderer::get().renderSurface(Assets::get().text, SDL_Rect{96, 0, 32, 16}, SDL_Rect{okDst.x + 16, okDst.y + 4, 32, 16}, Renderer::get().bottom);

    Renderer::get().renderSurface(Assets::get().net, SDL_Rect{0, 32, 16, 16}, SDL_Rect{2, 174, 16, 16}, Renderer::get().bottom);
}
