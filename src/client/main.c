#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <SDL2/SDL_net.h>

#include "mvl_ds.h"
#include "mvl_input.h"
#include "mvl_state.h"
#include "mvl_time.h"
#include "mvl_menu.h"

void handleEvents() {
    SDL_Event* mouseEvents = malloc(16 * sizeof(SDL_Event));
    int count = 0;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                exit(0);
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                mouseEvents[count++] = e;
                break;
        }
    }

    inputUpdate(mouseEvents, count);
    free(mouseEvents);
}

void tcp() {
    IPaddress serverIP;
    TCPsocket socket;

    char* msg = "hello world!";

    if (SDLNet_ResolveHost(&serverIP, "localhost", 2000) == 0) {
        socket = SDLNet_TCP_Open(&serverIP);

        int len = strlen(msg) + 1;

        SDLNet_TCP_Send(socket, msg, len);
    }
    else {
        printf("Could not resolve host.\n");
    }

    SDLNet_TCP_Close(socket);
}

void udp() {
    UDPsocket socket = SDLNet_UDP_Open(0);

    IPaddress serverIP;
    SDLNet_ResolveHost(&serverIP, "localhost", 2000);

    UDPpacket* packet = SDLNet_AllocPacket(512);
    packet->address = serverIP;
    char* msg = "quit";
    packet->data = msg;
    packet->len = strlen(msg) + 1;
    SDLNet_UDP_Send(socket, -1, packet);
    //SDLNet_FreePacket(packet);
}

int main(int argc, char** argv) {
    assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0);
    assert(TTF_Init() == 0);
    assert(Mix_OpenAudio(44100, AUDIO_S16SYS, 4, 512) == 0);
    assert(SDLNet_Init() == 0);

    SDL_Window* window = SDL_CreateWindow("MvL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gResolution.x + 2 * gGap, 2 * gResolution.y + 3 * gGap, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Assets assets = loadAssets(renderer);
    SDL_SetWindowIcon(window, assets.icon);
    timeInit();
    inputInit();
    stateHandlerInit();
    statesInit();

    stateHandlerPush(&gConnectState);

    //tcp();

    while (true) {
        // Update.

        tick();
        handleEvents();

        Vec2i size;
        SDL_GetWindowSize(window, &size.x, &size.y);
        gTop = (Vec2i){size.x / 2 - gResolution.x / 2, size.y / 2 - (2 * gResolution.y + gGap) / 2};
        gBottom = (Vec2i){size.x / 2 - gResolution.x / 2, size.y / 2 + gGap / 2};

        stateHandlerUpdate(gClock.delta);
        handleButtons();

        // Render.

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_Rect topDst = {gTop.x, gTop.y, gResolution.x, gResolution.y};
        SDL_Rect bottomDst = {gBottom.x, gBottom.y, gResolution.x, gResolution.y};
        SDL_RenderFillRect(renderer, &topDst);
        SDL_RenderFillRect(renderer, &bottomDst);

        stateHandlerRender(gClock.delta, renderer, assets);

        SDL_RenderPresent(renderer);
    }
}