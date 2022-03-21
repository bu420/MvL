#include "mvl_server.h"

#include <stdexcept>
#include <iostream>

using namespace mvl;

void Server::start(int port) {
    mario = nullptr;
    luigi = nullptr;

    address.host = ENET_HOST_ANY;
    address.port = port;

    if (!(server = enet_host_create(&address, 2, 2, 0, 0))) {
        throw std::runtime_error("Could not create ENet host.");
    }
}

std::vector<std::pair<ENetPeer*, std::string>> Server::update() {
    std::vector<std::pair<ENetPeer*, std::string>> packets;

    ENetEvent event;
    while (enet_host_service(server, &event, 0) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            if (!mario) {
                mario = event.peer;
                std::cout << "Mario connected." << std::endl;
            }
            else if (!luigi) {
                luigi = event.peer;
                std::cout << "Luigi connected." << std::endl;
            }
            else {
                enet_peer_reset(event.peer);
                std::cout << "3rd client tried to connect, disconnected it." << std::endl;
            }
            
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            if (mario) {
                if (event.peer->address.host == mario->address.host && event.peer->address.port == mario->address.port) {
                    std::cout << "Mario disconnected." << std::endl;
                    mario = nullptr;
                }
            }
            
            if (luigi) {
                if (event.peer->address.host == luigi->address.host && event.peer->address.port == luigi->address.port) {
                    std::cout << "Luigi disconnected." << std::endl;
                    luigi = nullptr;
                }
            }

            break;

        case ENET_EVENT_TYPE_RECEIVE:
            packets.push_back(std::make_pair(event.peer, (char*)event.packet->data));
            enet_packet_destroy(event.packet);
        }
    }

    return packets;
}

void Server::marioSend(std::string message, bool reliable) {
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(mario, 0, packet);
}

void Server::luigiSend(std::string message, bool reliable) {
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(luigi, 0, packet);
}

void Server::broadcast(std::string message, bool reliable) {
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_host_broadcast(server, 0, packet);
}

std::string Server::convertHost(enet_uint32 host) {
    return std::to_string((uint8_t)host) + "." + std::to_string((uint8_t)(host >> 8)) + "." + std::to_string((uint8_t)(host >> 16)) + "." + std::to_string((uint8_t)(host >> 24));
}