#pragma once

#include <SDL2/SDL.h>

#include "mvl_state.h"

namespace mvl {
    class SettingsState : public State {
    public:
        void init(Client&) override;
        void update(Window&, Client&, Input&, Buttons&, Clock&, StateHandler&, GlobalState&) override;
        void render(Window&, Assets&, GlobalState&) override;

    private:
        int selected;
        SDL_Rect okDst;
    };
}