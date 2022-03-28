#include <enet/enet.h>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "mvl_state.h"
#include "mvl_state_connect.h"

using namespace mvl;

std::vector<SDL_Event> pollEvents() {
    std::vector<SDL_Event> events;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        events.emplace_back(event);
    }

    return events;
}

int main(int argc, char** argv) {
    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
            throw std::runtime_error("Failed to init SDL video and audio.");
        }
        if (TTF_Init() != 0) {
            throw std::runtime_error("Failed to init SDL TTF.");
        }
        if (Mix_OpenAudio(44100, AUDIO_S16SYS, 4, 512) != 0) {
            throw std::runtime_error("Failed to init SDL mixer.");
        }
        if (enet_initialize()) {
            throw std::runtime_error("Failed to init ENet.");
        }

        Window window;
        Assets assets;
        Clock clock;
        StateHandler stateHandler;
        Client client;

        window.init("MvL", true);
        assets.load();
        window.setIcon(assets.icon);
        clock.init();
        client.init();

        stateHandler.push(new ConnectState, window, client);

        while (true) {
            // Update.

            clock.tick();

            auto events = pollEvents();
            for (auto event : events) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }
            }

            window.update(events);
            stateHandler.update(window, client, clock);
            window.handleButtons();
            
            // Render.

            window.fill({0, 0, window.size.x, window.size.y}, {0, 0, 0, 255});

            Screen top = window.top;
            Screen bottom = window.bottom;
            window.fill({0, 0, Screen::res.x, Screen::res.y}, {255, 255, 255, 255}, top);
            window.fill({0, 0, Screen::res.x, Screen::res.y}, {255, 255, 255, 255}, bottom);

            stateHandler.render(window, client, assets);

            window.renderTexture(top.renderTexture, std::nullopt, SDL_Rect{top.pos.x, top.pos.y, top.res.x, top.res.y});
            window.renderTexture(bottom.renderTexture, std::nullopt, SDL_Rect{bottom.pos.x, bottom.pos.y, bottom.res.x, bottom.res.y});

            SDL_RenderPresent(window.renderer);
        }
    }
    catch (std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}