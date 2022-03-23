#pragma once

#include <enet/enet.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <utility>
#include <optional>
#include <functional>

namespace mvl {
    class Server {
    public:
        void start(int port);
        std::vector<std::pair<ENetPeer*, nlohmann::json>> update(
            std::optional<std::function<void()>> marioConnectCallback,
            std::optional<std::function<void()>> luigiConnectCallback,
            std::optional<std::function<void()>> marioDisconnectCallback,
            std::optional<std::function<void()>> luigiDisconnectCallback);
        
        void marioSend(nlohmann::json data, bool reliable);
        void luigiSend(nlohmann::json data, bool reliable);
        void broadcast(nlohmann::json data, bool reliable);

        bool isMario(ENetPeer* peer);
        bool isLuigi(ENetPeer* peer);

        std::string convertHost(enet_uint32 host);

    private:
        ENetAddress address;
        ENetHost* server;
        ENetPeer* mario;
        ENetPeer* luigi;
    };
}