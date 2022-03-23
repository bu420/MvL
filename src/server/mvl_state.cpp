#include "mvl_state.h"

using namespace mvl;

void StateHandler::push(State* state) {
    stack.emplace_back(state);
    stack.back()->init();
}

void StateHandler::pop() {
    delete stack.back();
    stack.pop_back();
}

State* StateHandler::top() {
    return stack.back();
}

void StateHandler::update() {
    top()->update();
}
