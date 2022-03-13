#pragma once

#include <enet/enet.h>
#include <string>
#include <vector>
#include <utility>

#include "mvl_singleton.h"

namespace mvl {
    class Client : public Singleton<Client> {
    public:
        void init();
        bool connect(std::string host, int port);
        bool connected();
        std::vector<std::pair<ENetPeer*, std::string>> update();
        void send(std::string message, bool reliable);

    private:
        ENetAddress serverAddress;
        ENetHost* client;
        ENetPeer* server;
    };
}