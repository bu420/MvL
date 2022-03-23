#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "mvl_state.h"
#include "mvl_math.h"

namespace mvl {
    class GameState : public State {
    public:
        void init(Client&) override;
        void update(Window&, Client&, Input&, Buttons&, Clock&, StateHandler&, GlobalState&) override;
        void render(Window&, Assets&, GlobalState&) override;

    private:
        std::vector<Vec2i> tiles;

        Vec2f player, other;
    };
}