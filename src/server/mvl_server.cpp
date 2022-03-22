#include "mvl_server.h"

#include <stdexcept>
#include <iostream>

using namespace mvl;
using namespace nlohmann;

void Server::start(int port) {
    mario = nullptr;
    luigi = nullptr;

    address.host = ENET_HOST_ANY;
    address.port = port;

    if (!(server = enet_host_create(&address, 2, 2, 0, 0))) {
        throw std::runtime_error("Could not create ENet host.");
    }
}

std::vector<std::pair<ENetPeer*, nlohmann::json>> Server::update(std::optional<std::function<void()>> marioConnectCallback, std::optional<std::function<void()>> luigiConnectCallback, std::optional<std::function<void()>> marioDisconnectCallback, std::optional<std::function<void()>> luigiDisconnectCallback) {
    std::vector<std::pair<ENetPeer*, nlohmann::json>> packets;

    ENetEvent event;
    while (enet_host_service(server, &event, 0) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            if (!mario) {
                mario = event.peer;
                if (marioConnectCallback) {
                    marioConnectCallback.value()();
                }
            }
            else if (!luigi) {
                luigi = event.peer;
                if (luigiConnectCallback) {
                    luigiConnectCallback.value()();
                }
            }
            else {
                enet_peer_reset(event.peer);
            }
            
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            if (mario) {
                if (isMario(event.peer)) {
                    mario = nullptr;
                    if (marioDisconnectCallback) {
                        marioDisconnectCallback.value()();
                    }
                }
            }
            
            if (luigi) {
                if (isLuigi(event.peer)) {
                    luigi = nullptr;
                    if (luigiDisconnectCallback) {
                        luigiDisconnectCallback.value()();
                    }
                }
            }

            break;

        case ENET_EVENT_TYPE_RECEIVE:
            packets.push_back(std::make_pair(event.peer, json::parse(event.packet->data)));
            enet_packet_destroy(event.packet);
        }
    }

    return packets;
}

void send(ENetPeer* peer, json data, bool reliable) {
    ENetPacket* packet = enet_packet_create(data.dump().c_str(), data.dump().size() + 1, reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(peer, 0, packet);
}

void Server::marioSend(json data, bool reliable) {
    send(mario, data, reliable);
}

void Server::luigiSend(json data, bool reliable) {
    send(luigi, data, reliable);
}

void Server::broadcast(json data, bool reliable) {
    ENetPacket* packet = enet_packet_create(data.dump().c_str(), data.dump().size() + 1, reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_host_broadcast(server, 0, packet);
}

bool Server::isMario(ENetPeer* peer) {
    return peer->address.host == mario->address.host && peer->address.port == mario->address.port;
}

bool Server::isLuigi(ENetPeer* peer) {
    return peer->address.host == luigi->address.host && peer->address.port == luigi->address.port;
}

std::string Server::convertHost(enet_uint32 host) {
    return std::to_string((uint8_t)host) + "." + std::to_string((uint8_t)(host >> 8)) + "." + std::to_string((uint8_t)(host >> 16)) + "." + std::to_string((uint8_t)(host >> 24));
}