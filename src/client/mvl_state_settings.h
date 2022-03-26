#pragma once

#include <SDL2/SDL.h>

#include "mvl_state.h"

namespace mvl {
    class SettingsState : public State {
    public:
        void init(Window&, Client&) override;
        void update(Window&, Client&, Clock&, StateHandler&) override;
        void render(Window&, Client&, Assets&) override;

    private:
        int selected;
        SDL_Rect okDst;
    };
}