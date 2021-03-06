#include "mvl_state_connect.h"

#include <stdexcept>
#include <iostream>

#include "mvl_state_settings.h"
#include "mvl_state_net_error.h"

using namespace mvl;
using namespace nlohmann;

void ConnectState::init(Window& window, Client& client) {
    window.hide();

    std::string host, portStr;
        
    std::cout << "Host (default: 127.0.0.1)>";
    std::getline(std::cin, host);
    host = host.empty() ? "127.0.0.1" : host;

    std::cout << "Port (default: 2000)>";
    std::getline(std::cin, portStr);
    int port = portStr.empty() ? 2000 : std::stoi(portStr);

    std::cout << "Connecting to server (" << host << ":" << port << ")..." << std::endl;

    if (client.connect(host, port)) {
        std::cout << "Successfully connected to server." << std::endl;
    }
    else {
        std::cout << "Failed to connect to server." << std::endl;
        std::cout << "Press Enter to try again." << std::endl;
        std::cin.get();
        init(window, client);
    }
}

void ConnectState::update(Window& window, Client& client, Clock& clock, StateHandler& stateHandler) {
    auto packets = client.update([&]() -> void {
        stateHandler.push(new NetErrorState, window, client);
    });

    for (auto packet : packets) {
        json data = packet.second;

        if (data["type"] == "mario") {
            client.role = Client::Role::Mario;
            std::cout << "Welcome Mario, waiting for Luigi to join..." << std::endl;
        }
        else if (data["type"] == "luigi") {
            client.role = Client::Role::Luigi;
            std::cout << "Welcome Luigi, waiting for game to start..." << std::endl;
        }
        else if (data["type"] == "ready") {
            if (!client.role.has_value()) {
                throw std::runtime_error("Game started before receiving a role.");
            }

            std::cout << "Starting!" << std::endl;
            stateHandler.pop();
            stateHandler.push(new SettingsState, window, client);
            window.setTitle(std::string("MvL: ") + (client.role.value() == Client::Role::Mario ? "Mario" : "Luigi"));
        }
    }
}

void ConnectState::render(Window& window, Client&, Assets& assets) {

}
