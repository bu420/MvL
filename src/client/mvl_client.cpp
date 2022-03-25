#include "mvl_client.h"

#include <iostream>

using namespace mvl;
using namespace nlohmann;

void Client::init() {
    if (!(client = enet_host_create(nullptr, 1, 2, 0, 0))) {
        throw std::runtime_error("Failed to create ENet client.");
    }
}

bool Client::connect(std::string host, int port) {
    if (connected()) {
        return true;
    }

    enet_address_set_host(&serverAddress, host.c_str());
    serverAddress.port = port;

    if (!(server = enet_host_connect(client, &serverAddress, 2, 0))) {
        return false;
    }

    ENetEvent event;
    if (enet_host_service(client, &event, 5000) > 0) {
        if (event.type == ENET_EVENT_TYPE_CONNECT) {
            return true;
        }
    }

    enet_peer_reset(server);
    server = nullptr;

    return false;
}

bool Client::connected() {
    if (!client) {
        return false;
    }

    return client->connectedPeers > 0;
}

std::vector<std::pair<ENetPeer*, json>> Client::update(std::optional<std::function<void()>> disconnectCallback) {
    std::vector<std::pair<ENetPeer*, json>> packets;

    if (connected()) {
        ENetEvent event;
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_DISCONNECT:
                if (disconnectCallback) {
                    disconnectCallback.value()();
                }
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                packets.emplace_back(std::make_pair(event.peer, json::parse(event.packet->data)));
                enet_packet_destroy(event.packet);
            }
        }
    }

    return packets;
}

void Client::send(json data, bool reliable) {
    if (!connected()) {
        return;
    }

    ENetPacket* packet = enet_packet_create(data.dump().c_str(), data.dump().size() + 1, reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(server, 0, packet);
}