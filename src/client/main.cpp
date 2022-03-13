#include <enet/enet.h>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "mvl_window.h"
#include "mvl_renderer.h"
#include "mvl_asset.h"
#include "mvl_input.h"
#include "mvl_state.h"
#include "mvl_menu.h"
#include "mvl_time.h"
#include "mvl_state_connect.h"
#include "mvl_client.h"

using namespace mvl;

std::vector<SDL_Event> pollEvents() {
    std::vector<SDL_Event> events;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        events.push_back(event);
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

        Window::get().init("MvL");
        Renderer::get().init();
        Assets::get().load();
        Window::get().setIcon(Assets::get().icon);
        Clock::get().init();
        Client::get().init();

        StateHandler::get().push(new ConnectState);

        while (true) {
            // Update.

            Clock::get().tick();

            auto events = pollEvents();
            for (auto event : events) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }
            }

            Input::get().update(events);
            Window::get().update();
            StateHandler::get().update();
            
            Buttons::get().handle();

            // Render.

            Renderer::get().fill({0, 0, Window::get().size.x, Window::get().size.y}, {0, 0, 0, 255});

            Screen top = Renderer::get().top;
            Screen bottom = Renderer::get().bottom;
            Renderer::get().fill({0, 0, Screen::res.x, Screen::res.y}, {255, 255, 255, 255}, top);
            Renderer::get().fill({0, 0, Screen::res.x, Screen::res.y}, {255, 255, 255, 255}, bottom);

            StateHandler::get().render();

            Renderer::get().renderTexture(top.renderTexture, std::nullopt, SDL_Rect{top.pos.x, top.pos.y, top.res.x, top.res.y});
            Renderer::get().renderTexture(bottom.renderTexture, std::nullopt, SDL_Rect{bottom.pos.x, bottom.pos.y, bottom.res.x, bottom.res.y});

            SDL_RenderPresent(Renderer::get().renderer);
        }
    }
    catch (std::runtime_error e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    catch (std::exception e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}