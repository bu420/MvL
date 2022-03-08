#include <SDL2/SDL_net.h>
#include <iostream>
#include <stdexcept>
#include <functional>

#include "mvl_time.h"
#include "mvl_math.h"

using namespace mvl;

struct Server {
    void init(int port) {
        this->port = port;

        serverIP = new IPaddress;
        SDLNet_ResolveHost(serverIP, nullptr, port);

        if (!(serverTCPSocket = SDLNet_TCP_Open(serverIP))) {
            throw std::runtime_error("Failed to open TCP server socket.");
        }

        serverUDPSocket = SDLNet_UDP_Open(port);
        packet = SDLNet_AllocPacket(512);

        std::cout << "Server started on port " << port << "." << std::endl;
    }

    void connect() {
        std::cout << "Waiting for Mario to connect..." << std::endl;

        while (true) {
            if ((marioTCPSocket = SDLNet_TCP_Accept(serverTCPSocket))) {
                if ((marioIP = SDLNet_TCP_GetPeerAddress(marioTCPSocket))) {
                    printf("Mario connected: %x %d\n", SDLNet_Read32(&marioIP->host), SDLNet_Read16(&marioIP->port));
                    printf("Waiting for Luigi to connect...\n");

                    while (true) {
                        if ((luigiTCPSocket = SDLNet_TCP_Accept(serverTCPSocket))) {
                            if ((luigiIP = SDLNet_TCP_GetPeerAddress(luigiTCPSocket))) {
                                printf("Luigi connected: %x %d\n", SDLNet_Read32(&luigiIP->host), SDLNet_Read16(&luigiIP->port));
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    void update() {
        void* data;
        if (SDLNet_TCP_Recv(marioTCPSocket, data, 512) > 0) {
            marioTCPReceiveCallback(data);
        }
        if (SDLNet_TCP_Recv(luigiTCPSocket, data, 512) > 0) {
            luigiTCPReceiveCallback(data);
        }

        if (SDLNet_UDP_Recv(serverUDPSocket, packet)) {
            if (packet->address.host == marioIP->host && packet->address.port == marioIP->host) {
                marioUDPReceiveCallback(packet);
            }
            else if (packet->address.host == luigiIP->host && packet->address.port == luigiIP->host) {
                luigiUDPReceiveCallback(packet);
            }
        }
    }

    int port;

    IPaddress* serverIP;
    IPaddress* marioIP;
    IPaddress* luigiIP;

    TCPsocket serverTCPSocket;
    TCPsocket marioTCPSocket;
    TCPsocket luigiTCPSocket;

    UDPsocket serverUDPSocket;
    UDPpacket* packet;

    std::function<void(void*)> marioTCPReceiveCallback;
    std::function<void(void*)> luigiTCPReceiveCallback;

    std::function<void(UDPpacket*)> marioUDPReceiveCallback;
    std::function<void(UDPpacket*)> luigiUDPReceiveCallback;
};

int main(int argc, char** argv) {
    if (SDLNet_Init() != 0) {
        throw std::runtime_error("Failed to init SDL net.");
    }

    Server server;

    try {
        server.init(2000);
        server.connect();

        server.marioTCPReceiveCallback = [&](void* data) -> void {
            std::cout << "Mario TCP: " << (char*)data << std::endl;
        };

        server.luigiTCPReceiveCallback = [&](void* data) -> void {
            std::cout << "Luigi TCP: " << (char*)data << std::endl;
        };

        server.marioUDPReceiveCallback = [&](UDPpacket* packet) -> void {
            std::cout << "Mario UDP: " << (char*)packet->data << std::endl;
        };

        server.luigiUDPReceiveCallback = [&](UDPpacket* packet) -> void {
            std::cout << "Luigi UDP: " << (char*)packet->data << std::endl;
        };

        while (true) {
            server.update();
        }
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}