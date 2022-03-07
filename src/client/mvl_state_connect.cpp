#include "mvl_state_connect.h"

#include "mvl_menu.h"
#include "mvl_time.h"
#include "mvl_renderer.h"
#include "mvl_asset.h"
#include "mvl_window.h"
#include "mvl_state_settings.h"

using namespace mvl;

void ConnectState::init() {
    okDst = SDL_Rect{100, 156, 64, 28};
}

void ConnectState::update() {
    Buttons::get().reg(okDst, Window::get().bottom, [this]() -> void {
        okDst.x += 2;
        okDst.y += 2;

        Clock::get().setInterval(250, [this]() -> bool {
            StateHandler::get().pop();
            StateHandler::get().push(new SettingsState);
            return false;
        });
    });
}

void ConnectState::render() {
    Renderer::get().renderMenuBackgrounds();

    Renderer::get().fill({16, 48, 224, 96}, {0, 0, 0, 255}, Window::get().top);
    Renderer::get().renderText("Connect To Server", Assets::get().font, {200, 200, 200, 255}, {56, 84}, Window::get().top);

    Renderer::get().renderSurface(Assets::get().button, std::nullopt, okDst, Window::get().bottom);
    Renderer::get().renderSurface(Assets::get().text, SDL_Rect{96, 0, 32, 16}, SDL_Rect{okDst.x + 16, okDst.y + 4, 32, 16}, Window::get().bottom);
}
