#pragma once

#include <functional>
#include <vector>

#include "mvl_window.h"
#include "mvl_asset.h"
#include "mvl_input.h"
#include "mvl_client.h"
#include "mvl_time.h"
#include "mvl_menu.h"
#include "mvl_global_state.h"

namespace mvl {
    class State;

    class StateHandler {
    public:
        void push(State* state, Client& client);
        void pop();
        State* top();
        void update(Window&, Client&, Input&, Buttons&, Clock&, GlobalState&);
        void render(Window&, Assets&, GlobalState&);

    private:
        std::vector<State*> stack;
    };

    class State {
    public:
        virtual void init(Client&) = 0;
        virtual void update(Window&, Client&, Input&, Buttons&, Clock&, StateHandler&, GlobalState&) = 0;
        virtual void render(Window&, Assets&, GlobalState&) = 0;
    };
}