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

        mvl::Renderer::get().fill({0, 0, mvl::Window::get().size.x, mvl::Window::get().size.y}, {0, 0, 0, 255});

        mvl::Screen top = mvl::Window::get().top;
        mvl::Screen bottom = mvl::Window::get().bottom;
        mvl::Renderer::get().fill({0, 0, mvl::Screen::res.x, mvl::Screen::res.y}, {255, 255, 255, 255}, top);
        mvl::Renderer::get().fill({0, 0, mvl::Screen::res.x, mvl::Screen::res.y}, {255, 255, 255, 255}, bottom);

        mvl::StateHandler::get().render();

        mvl::Renderer::get().renderTexture(top.renderTexture, std::nullopt, SDL_Rect{top.pos.x, top.pos.y, top.res.x, top.res.y});
        mvl::Renderer::get().renderTexture(bottom.renderTexture, std::nullopt, SDL_Rect{bottom.pos.x, bottom.pos.y, bottom.res.x, bottom.res.y});

        SDL_RenderPresent(mvl::Renderer::get().renderer);
    }

    return 0;
}