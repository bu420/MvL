#include "mvl_state.h"

using namespace mvl;

void StateHandler::push(State* state, Client& client) {
    stack.push_back(state);
    stack.back()->init(client);
}

void StateHandler::pop() {
    delete stack.back();
    stack.pop_back();
}

State* StateHandler::top() {
    return stack.back();
}

void StateHandler::update(Window& window, Client& client, Input& input, Buttons& buttons, Clock& clock, GlobalState& globalState) {
    top()->update(window, client, input, buttons, clock, *this, globalState);
}

void StateHandler::render(Window& window, Assets& assets, GlobalState& globalState) {
    top()->render(window, assets, globalState);
}
