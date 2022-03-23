#pragma once

#include "mvl_state.h"

namespace mvl {
    class ConnectState : public State {
    public:
        void init(Client&) override;
        void update(Window&, Client&, Input&, Buttons&, Clock&, StateHandler&, GlobalState&) override;
        void render(Window&, Assets&, GlobalState&) override;

    private:
    };
}