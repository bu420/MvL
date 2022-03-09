#include "mvl_client.h"

#include <iostream>

using namespace mvl;

void Client::init(std::string host, int port) {
    this->host = host;
    this->port = port;

    udpSocket = SDLNet_UDP_Open(0);
    packet = SDLNet_AllocPacket(512);
}

bool Client::connect() {
    if (SDLNet_ResolveHost(&serverIP, host.c_str(), port) == 0) {
        if ((tcpSocket = SDLNet_TCP_Open(&serverIP))) {
            return true;
        }
    }

    std::cout << "Failed to connect to server." << std::endl;
    return false;
}

void Client::tcpSend(void* data, int len) {
    SDLNet_TCP_Send(tcpSocket, data, len);
}

void Client::udpSend(void* data, int len) {
    packet->address = serverIP;
    packet->data = (uint8_t*)data;
    packet->len = len;
    SDLNet_UDP_Send(udpSocket, -1, packet);
}