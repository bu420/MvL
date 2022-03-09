#pragma once

#include <SDL2/SDL.h>

#include "mvl_state.h"

namespace mvl {
    class ConnectState : public State {
    public:
        void init() override;
        void update() override;
        void render() override;

    private:
        SDL_Rect connectDst;
        bool connected;
        SDL_Rect okDst;
    };
}