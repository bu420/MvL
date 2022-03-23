#include "mvl_state.h"

using namespace mvl;

void StateHandler::push(State* state, Client& client) {
    stack.emplace_back(state);
    stack.back()->init(client);
}

void StateHandler::pop() {
    delete stack.back();
    stack.pop_back();
}

State* StateHandler::top() {
    return stack.back();
}

void StateHandler::update(Window& window, Client& client, Clock& clock) {
    top()->update(window, client, clock, *this);
}

void StateHandler::render(Window& window, Client& client, Assets& assets) {
    top()->render(window, client, assets);
}
