#pragma once

#include "mvl_state.h"

namespace mvl {
    class ConnectState : public State {
    public:
        void init(Client&) override;
        void update(Window&, Client&, Clock&, StateHandler&) override;
        void render(Window&, Client&, Assets&) override;

    private:
    };
}