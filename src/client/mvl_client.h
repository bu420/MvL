#pragma once

#include <enet/enet.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <functional>

namespace mvl {
    class Client {
    public:
        void init();
        bool connect(std::string host, int port);
        bool connected();
        std::vector<std::pair<ENetPeer*, nlohmann::json>> update(std::optional<std::function<void()>> disconnectCallback = std::nullopt);
        void send(nlohmann::json data, bool reliable);

        enum class Role {
            Mario,
            Luigi
        };

        std::optional<Role> role;

    private:
        ENetAddress serverAddress;
        ENetHost* client;
        ENetPeer* server;
    };
}