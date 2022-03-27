#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "mvl_state.h"
#include "mvl_math.h"

namespace mvl {
    class GameState : public State {
    public:
        void init(Window&, Client&) override;
        void update(Window&, Client&, Clock&, StateHandler&) override;
        void render(Window&, Client&, Assets&) override;

    private:
        void handleCollision(bool trueForVerticalAndFalseForHorizontal);

        std::vector<Vec2i> tiles;

        Vec2f player, other;

        Vec2f vel;
        float gravity;
        bool onGround;
        float jump;
    };
}