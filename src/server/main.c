#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

void tcp() {
    TCPsocket socket;
    TCPsocket marioSocket;
    TCPsocket luigiSocket;

    IPaddress ip;
    IPaddress* marioIP;
    IPaddress* luigiIP;

    SDLNet_ResolveHost(&ip, NULL, 2000);
    socket = SDLNet_TCP_Open(&ip);

    printf("Server started on port 2000.\n");
    printf("Waiting for Mario...\n");

    char buffer[512];

    while (true) {
        if ((marioSocket = SDLNet_TCP_Accept(socket))) {
            if ((marioIP = SDLNet_TCP_GetPeerAddress(marioSocket))) {
                printf("Mario connected: %x %d\n", SDLNet_Read32(&marioIP->host), SDLNet_Read16(&marioIP->port));
                printf("Waiting for Luigi...\n");

                while (true) {
                    if ((luigiSocket = SDLNet_TCP_Accept(socket))) {
                        if ((luigiIP = SDLNet_TCP_GetPeerAddress(luigiSocket))) {
                            printf("Luigi connected: %x %d\n", SDLNet_Read32(&luigiIP->host), SDLNet_Read16(&luigiIP->port));

                            while (true) {
                                if (SDLNet_TCP_Recv(marioSocket, buffer, 512) > 0) {
                                    printf("Mario: %s\n", buffer);
                                }

                                if (SDLNet_TCP_Recv(luigiSocket, buffer, 512) > 0) {
                                    printf("Luigi: %s\n", buffer);
                                }
                            }
                        }
                    }
                }
            }

            SDLNet_TCP_Close(marioSocket);
            SDLNet_TCP_Close(luigiSocket);
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