#pragma once

#include <functional>
#include <vector>

#include "mvl_window.h"
#include "mvl_asset.h"
#include "mvl_client.h"
#include "mvl_time.h"

namespace mvl {
    class State;

    class StateHandler {
    public:
        void push(State* state, Client& client);
        void pop();
        State* top();
        void update(Window&, Client&, Clock&);
        void render(Window&, Client&, Assets&);

    private:
        std::vector<State*> stack;
    };

    class State {
    public:
        virtual void init(Client&) = 0;
        virtual void update(Window&, Client&, Clock&, StateHandler&) = 0;
        virtual void render(Window&, Client&, Assets&) = 0;
    };
}