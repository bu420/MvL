#include "mvl_state_net_error.h"

#include <stdexcept>
#include <iostream>

#include "mvl_state_connect.h"

using namespace mvl;
using namespace nlohmann;

void NetErrorState::init(Window& window, Client& client) {
    window.hide();
}

void NetErrorState::update(Window& window, Client& client, Clock& clock, StateHandler& stateHandler) {
    std::cout << "A network error occured." << std::endl;
    std::cout << "Either you lost connection, the other player left or the server shut down." << std::endl;
    std::cout << "Press Enter to restart." << std::endl;
    std::cin.get();
    stateHandler.push(new ConnectState, window, client);
}

void NetErrorState::render(Window& window, Client&, Assets& assets) {

}
