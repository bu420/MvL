#pragma once

#include <functional>
#include <vector>

#include "mvl_singleton.h"

namespace mvl {
    class State {
    public:
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
    };

    class StateHandler : public Singleton<StateHandler> {
    public:
        void push(State* state);
        void pop();
        State* top();
        void update();
        void render();

    private:
        std::vector<State*> stack;
    };
}