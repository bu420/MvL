#include "mvl_client.h"

#include <iostream>

using namespace mvl;

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
    if (enet_host_service(client, &event, 2000) > 0) {
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

std::vector<std::pair<ENetPeer*, std::string>> Client::update() {
    std::vector<std::pair<ENetPeer*, std::string>> packets;

    if (connected()) {
        ENetEvent event;
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected." << std::endl;
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Received." << std::endl;
                packets.push_back(std::make_pair(event.peer, (char*)event.packet->data));
                enet_packet_destroy(event.packet);
            }
        }
    }

    return packets;
}

void Client::send(std::string message, bool reliable) {
    if (!connected()) {
        return;
    }

    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(server, 0, packet);
}