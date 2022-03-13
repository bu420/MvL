#pragma once

#include <enet/enet.h>
#include <vector>
#include <string>
#include <utility>

#include "mvl_singleton.h"

namespace mvl {
    class Server : public Singleton<Server> {
    public:
        void start(int port);
        std::vector<std::pair<ENetPeer*, std::string>> update();
        
        void marioSend(std::string message, bool reliable);
        void luigiSend(std::string message, bool reliable);
        void broadcast(std::string message, bool reliable);

        std::string convertHost(enet_uint32 host);

    private:
        ENetAddress address;
        ENetHost* server;
        ENetPeer* mario;
        ENetPeer* luigi;
    };
}