#pragma once

#include <SDL2/SDL.h>
#include <utility>
#include <array>

#include "mvl_state.h"

namespace mvl {
    class SelectState : public State {
    public:
        void init(Window&, Client&) override;
        void update(Window&, Client&, Clock&, StateHandler&) override;
        void render(Window&, Client&, Assets&) override;

    private:
        std::array<std::pair<SDL_Rect, SDL_Rect>, 5> icons;
        int selected;
        SDL_Rect backArrowDst;
    };
}