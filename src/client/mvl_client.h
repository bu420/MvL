#pragma once

#include <SDL2/SDL_net.h>
#include <string>

#include "mvl_singleton.h"

namespace mvl {
    class Client : public Singleton<Client> {
    public:
        void init(std::string host, int port);
        bool connect();
        void tcpSend(void* data, int len);
        void udpSend(void* data, int len);

    private:
        std::string host;
        int port;

        IPaddress serverIP;
        TCPsocket tcpSocket;
        UDPsocket udpSocket;
        UDPpacket* packet;
    };
}