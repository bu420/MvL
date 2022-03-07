#pragma once

#include <SDL2/SDL.h>
#include <utility>
#include <array>

#include "mvl_state.h"

namespace mvl {
    class SelectState : public State {
    public:
        void init() override;
        void update() override;
        void render() override;

    private:
        std::array<std::pair<SDL_Rect, SDL_Rect>, 5> icons;
        int selected;
        SDL_Rect backArrowDst;
    };
}