#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

void tcp() {
    TCPsocket socket;
    TCPsocket clientSocket;

    IPaddress ip;
    IPaddress* clientIP;

    SDLNet_ResolveHost(&ip, NULL, 2000);
    socket = SDLNet_TCP_Open(&ip);

    char buffer[512];

    while (true) {
        if ((clientSocket = SDLNet_TCP_Accept(socket))) {
            if ((clientIP = SDLNet_TCP_GetPeerAddress(clientSocket))) {
                printf("New client: %x %d\n", SDLNet_Read32(&clientIP->host), SDLNet_Read16(&clientIP->port));

                while (true) {
                    if (SDLNet_TCP_Recv(clientSocket, buffer, 512) > 0) {
                        printf("Client: %s\n", buffer);
                    }
                }
            }

            SDLNet_TCP_Close(clientSocket);
        }
    }

    SDLNet_TCP_Close(socket);
}

void udp() {
    UDPsocket socket = SDLNet_UDP_Open(2000);
    UDPpacket* packet = SDLNet_AllocPacket(512);
    bool done = false;

    while (!done) {
        if (SDLNet_UDP_Recv(socket, packet)) {
            printf("UDP Packet incoming\n");
            printf("\tChan: %d\n", packet->channel);
            printf("\tData: %s\n", (char *)packet->data);
            printf("\tLen: %d\n", packet->len);
            printf("\tMaxlen: %d\n", packet->maxlen);
            printf("\tStatus: %d\n", packet->status);
            printf("\tAddress: %x %x\n", packet->address.host, packet->address.port);

            if (!strcmp((char*)packet->data, "quit")) {
                done = true;
            }
        }

        SDLNet_FreePacket(packet);
    }
}

int main(int argc, char** argv) {
    assert(SDLNet_Init() == 0);

    tcp();
}