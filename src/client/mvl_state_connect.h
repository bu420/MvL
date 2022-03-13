#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "mvl_state.h"

namespace mvl {
    class ConnectState : public State {
    public:
        void init() override;
        void update() override;
        void render() override;

    private:
        SDL_Rect okDst;
        std::string host;
        int port;
    };
}