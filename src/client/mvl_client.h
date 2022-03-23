#pragma once

#include <enet/enet.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <utility>

#include "mvl_global_state.h"

namespace mvl {
    class Client {
    public:
        void init();
        bool connect(std::string host, int port);
        bool connected();
        std::vector<std::pair<ENetPeer*, nlohmann::json>> update();
        void send(nlohmann::json data, bool reliable);

        GlobalState globalState;

    private:
        ENetAddress serverAddress;
        ENetHost* client;
        ENetPeer* server;
    };
}