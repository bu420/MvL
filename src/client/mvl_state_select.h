#pragma once

#include <SDL2/SDL.h>
#include <utility>
#include <array>

#include "mvl_state.h"

namespace mvl {
    class SelectState : public State {
    public:
        void init(Client&) override;
        void update(Window&, Client&, Input&, Buttons&, Clock&, StateHandler&, GlobalState&) override;
        void render(Window&, Assets&, GlobalState&) override;

    private:
        std::array<std::pair<SDL_Rect, SDL_Rect>, 5> icons;
        int selected;
        SDL_Rect backArrowDst;
    };
}