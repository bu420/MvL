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

        auto& window = Window::get();
        auto& renderer =  Renderer::get();
        auto& assets = Assets::get();
        auto& clock = Clock::get();
        auto& stateHandler = StateHandler::get();
        auto& client = Client::get();
        auto& input = Input::get();
        auto& buttons = Buttons::get();

        window.init("MvL", true);
        renderer.init();
        assets.load();
        window.setIcon(assets.icon);
        clock.init();
        client.init();

        stateHandler.push(new ConnectState);

        while (true) {
            // Update.

            clock.tick();

            auto events = pollEvents();
            for (auto event : events) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }
            }

            input.update(events);
            window.update();
            stateHandler.update();
            
            buttons.handle();

            // Render.

            renderer.fill({0, 0, window.size.x, window.size.y}, {0, 0, 0, 255});

            Screen top = renderer.top;
            Screen bottom = renderer.bottom;
            renderer.fill({0, 0, Screen::res.x, Screen::res.y}, {255, 255, 255, 255}, top);
            renderer.fill({0, 0, Screen::res.x, Screen::res.y}, {255, 255, 255, 255}, bottom);

            stateHandler.render();

            renderer.renderTexture(top.renderTexture, std::nullopt, SDL_Rect{top.pos.x, top.pos.y, top.res.x, top.res.y});
            renderer.renderTexture(bottom.renderTexture, std::nullopt, SDL_Rect{bottom.pos.x, bottom.pos.y, bottom.res.x, bottom.res.y});

            SDL_RenderPresent(renderer.renderer);
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