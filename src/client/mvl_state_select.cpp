#include "mvl_state_select.h"

#include <SDL2/SDL.h>

#include "mvl_input.h"
#include "mvl_menu.h"
#include "mvl_state.h"
#include "mvl_state_game.h"
#include "mvl_time.h"
#include "mvl_renderer.h"
#include "mvl_asset.h"

using namespace mvl;

void SelectState::init() {
    icons[0] = {{0, 0, 48, 48}, {32, 56, 48, 48}};
    icons[1] = {{0, 48, 48, 48}, {104, 56, 48, 48}};
    icons[2] = {{0, 96, 48, 48}, {176, 56, 48, 48}};
    icons[3] = {{0, 144, 48, 48}, {66, 124, 48, 48}};
    icons[4] = {{0, 192, 48, 48}, {140, 124, 48, 48}};
    selected = 0;
    backArrowDst = {224, 160, 30, 30};
}

void SelectState::update() {
    if (Input::get().keyPressed(SDL_SCANCODE_RIGHT)) {
        selected = selected == 4 ? 0 : selected + 1;
    }
    if (Input::get().keyPressed(SDL_SCANCODE_LEFT)) {
        selected = selected == 0 ? 4 : selected - 1;
    }

    for (auto icon : icons) {
        Buttons::get().reg(icon.second, Renderer::get().bottom, [this]() -> void {
            StateHandler::get().pop();
            StateHandler::get().push(new GameState);
        });
    }

    Buttons::get().reg(backArrowDst, Renderer::get().bottom, [this]() -> void {
        backArrowDst.x += 2;
        backArrowDst.y += 2;

        Clock::get().setInterval(250, [this]() -> bool {
            StateHandler::get().pop();
            return false;
        });
    });
}

void SelectState::render() {
    Renderer::get().renderMenuBackgrounds();

    Renderer::get().fill({16, 48, 224, 96}, {0, 0, 0, 255}, Renderer::get().top);

    for (int i = 0; i < 2; i++) {
        Renderer::get().renderSurface(Assets::get().banner, SDL_Rect{24, 0, 24, 32}, SDL_Rect{i * 24, 8, 24, 32}, Renderer::get().bottom);
    }
    
    for (int i = 0; i < 7; i++) {
        Renderer::get().renderSurface(Assets::get().banner, SDL_Rect{0, 0, 24, 32}, SDL_Rect{48 + i * 24, 8, 24, 32}, Renderer::get().bottom);
    }

    for (int i = 0; i < 2; i++) {
        Renderer::get().renderSurface(Assets::get().banner, SDL_Rect{24, 0, 24, 32}, SDL_Rect{208 + i * 24, 8, 24, 32}, Renderer::get().bottom);
    }

    for (int i = 0; i < 5; i++) {
        Renderer::get().renderSurface(Assets::get().borders, SDL_Rect{0, selected == i ? 0 : 64, 64, 64}, SDL_Rect{icons[i].second.x - 8, icons[i].second.y - 8, 64, 64}, Renderer::get().bottom);
        Renderer::get().renderSurface(Assets::get().levelIcons, SDL_Rect{0, icons[i].first.y, 48, 48}, SDL_Rect{icons[i].second.x, icons[i].second.y, 48, 48}, Renderer::get().bottom);
    }

    Renderer::get().renderSurface(Assets::get().backArrow, std::nullopt, backArrowDst, Renderer::get().bottom);

    Renderer::get().renderSurface(Assets::get().net, SDL_Rect{0, 32, 16, 16}, SDL_Rect{2, 174, 16, 16}, Renderer::get().bottom);
}
