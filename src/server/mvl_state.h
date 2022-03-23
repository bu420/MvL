#pragma once

#include <functional>
#include <vector>

namespace mvl {
    class State {
    public:
        virtual void init() = 0;
        virtual void update() = 0;
    };

    class StateHandler {
    public:
        void push(State* state);
        void pop();
        State* top();
        void update();

    private:
        std::vector<State*> stack;
    };
}