#include <SDL2/SDL_net.h>
#include <vector>
#include <stdexcept>

#include "mvl_window.h"
#include "mvl_renderer.h"
#include "mvl_asset.h"
#include "mvl_input.h"
#include "mvl_state.h"
#include "mvl_menu.h"
#include "mvl_time.h"
#include "mvl_state_connect.h"

std::vector<SDL_Event> pollEvents() {
    std::vector<SDL_Event> events;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        events.push_back(event);
    }

    return events;
}

/*
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
    packet->data = (uint8_t*)msg;
    packet->len = strlen(msg) + 1;
    SDLNet_UDP_Send(socket, -1, packet);
    //SDLNet_FreePacket(packet);
}
*/

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        throw std::runtime_error("Failed to init SDL video and audio.");
    }
    if (TTF_Init() != 0) {
        throw std::runtime_error("Failed to init SDL TTF.");
    }
    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 4, 512) != 0) {
        throw std::runtime_error("Failed to init SDL mixer.");
    }
    if (SDLNet_Init() != 0) {
        throw std::runtime_error("Failed to init SDL net.");
    }

    mvl::Window::get().init("MvL");
    mvl::Renderer::get().init();
    mvl::Assets::get().load();
    mvl::Window::get().setIcon(mvl::Assets::get().icon);
    mvl::Clock::get().init();

    mvl::StateHandler::get().push(new mvl::ConnectState);

    while (true) {
        // Update.

        mvl::Clock::get().tick();

        auto events = pollEvents();
        for (auto event : events) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }

        mvl::Input::get().update(events);
        mvl::Window::get().update();

        mvl::StateHandler::get().update();
        mvl::Buttons::get().handle();

        // Render.

        SDL_SetRenderDrawColor(mvl::Renderer::get().renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(mvl::Renderer::get().renderer);

        SDL_SetRenderDrawColor(mvl::Renderer::get().renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_Rect topDst = {mvl::Window::get().top.pos.x, mvl::Window::get().top.pos.y, mvl::Screen::res.x, mvl::Screen::res.y};
        SDL_Rect bottomDst = {mvl::Window::get().bottom.pos.x, mvl::Window::get().bottom.pos.y, mvl::Screen::res.x, mvl::Screen::res.y};
        SDL_RenderFillRect(mvl::Renderer::get().renderer, &topDst);
        SDL_RenderFillRect(mvl::Renderer::get().renderer, &bottomDst);

        mvl::StateHandler::get().render();

        SDL_RenderPresent(mvl::Renderer::get().renderer);
    }
}