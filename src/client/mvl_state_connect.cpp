#include "mvl_state_connect.h"

#include <stdexcept>
#include <iostream>

#include "mvl_window.h"
#include "mvl_state_settings.h"
#include "mvl_client.h"
#include "mvl_global_state.h"

using namespace mvl;
using namespace nlohmann;

void ConnectState::init() {
    auto& client = Client::get();
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
        init();
    }
}

void ConnectState::update() {
    auto packets = Client::get().update();

    for (auto packet : packets) {
        json data = packet.second;

        if (data["type"] == "mario") {
            GlobalState::get().role = GlobalState::Role::Mario;
            std::cout << "Welcome Mario, waiting for Luigi to join..." << std::endl;
        }
        else if (data["type"] == "luigi") {
            GlobalState::get().role = GlobalState::Role::Luigi;
            std::cout << "Welcome Luigi, waiting for game to start..." << std::endl;
        }
        else if (data["type"] == "ready") {
            if (!GlobalState::get().role.has_value()) {
                throw std::runtime_error("Game started before receiving a role.");
            }

            std::cout << "Starting!" << std::endl;
            StateHandler::get().pop();
            StateHandler::get().push(new SettingsState);
            Window::get().show();
            Window::get().setTitle(std::string("MvL: ") + (GlobalState::get().role.value() == GlobalState::Role::Mario ? "Mario" : "Luigi"));
        }
    }
}

void ConnectState::render() {

}
