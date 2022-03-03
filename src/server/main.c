#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    assert(SDLNet_Init() == 0);

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