#pragma once

#include <SDL2/SDL.h>

#include "mvl_state.h"

namespace mvl {
    class SettingsState : public State {
    public:
        void init() override;
        void update() override;
        void render() override;

    private:
        int selected;
        SDL_Rect okDst;
    };
}