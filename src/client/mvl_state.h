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
        void push(State* state, Window& window, Client& client);
        void pop();
        State* top();
        void update(Window& window, Client& client, Clock& clock);
        void render(Window& window, Client& client, Assets& assets);

    private:
        std::vector<State*> stack;
    };

    class State {
    public:
        virtual void init(Window&, Client&) = 0;
        virtual void update(Window&, Client&, Clock&, StateHandler&) = 0;
        virtual void render(Window&, Client&, Assets&) = 0;
    };
}