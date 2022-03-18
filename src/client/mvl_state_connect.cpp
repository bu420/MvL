#include "mvl_state_connect.h"

#include <stdexcept>
#include <iostream>

#include "mvl_menu.h"
#include "mvl_time.h"
#include "mvl_renderer.h"
#include "mvl_asset.h"
#include "mvl_window.h"
#include "mvl_input.h"
#include "mvl_state_settings.h"
#include "mvl_client.h"

using namespace mvl;

void ConnectState::init() {
    okDst = {96, 156, 64, 28};
    host = "127.0.0.1";
    port = 2000;
}

void ConnectState::update() {
    Buttons::get().reg(okDst, Renderer::get().bottom, [this]() -> void {
        okDst.x += 2;
        okDst.y += 2;

        Clock::get().setInterval(250, [this]() -> bool {
            if (Client::get().connect(host, port)) {
                std::cout << "Connected." << std::endl;

                std::cout << "Sending packet..." << std::endl;
                Client::get().send("Hello from client", true);
                std::cout << "Sent!" << std::endl;

                //StateHandler::get().pop();
                //StateHandler::get().push(new SettingsState);
                //Client::get().send("Hello there.", true);
            }
            else {
                std::cout << "Failed to connect to server." << std::endl;
            }

            okDst.x -= 2;
            okDst.y -= 2;

            return false;
        });
    });

    auto packets = Client::get().update();

    for (auto packet : packets) {
        std::cout << "Address: " << packet.first << std::endl;
        std::cout << "Received " << packet.second << " from " << packet.first->address.host << "." << std::endl;
    }
}
    
void ConnectState::render() {
    Renderer& rndrr = Renderer::get();

    rndrr.renderMenuBackgrounds();

    rndrr.fill({16, 48, 224, 96}, {0, 0, 0, 255}, rndrr.top);
    rndrr.renderText("Connect To Server", Assets::get().font, {255, 255, 255, 255}, {44, 84}, rndrr.top);
    rndrr.renderSurface(Assets::get().net, SDL_Rect{0, 0, 16, 16}, SDL_Rect{206, 86, 16, 16}, rndrr.top);

    rndrr.fill({31, 47, 194, 34}, {0, 0, 0, 255}, rndrr.bottom);
    rndrr.fill({31, 95, 194, 34}, {0, 0, 0, 255}, rndrr.bottom);
    rndrr.fill({32, 48, 192, 32}, {255, 255, 255, 255}, rndrr.bottom);
    rndrr.fill({32, 96, 192, 32}, {255, 255, 255, 255}, rndrr.bottom);
    rndrr.renderText(host, Assets::get().font, {0, 0, 0, 255}, {40, 54}, rndrr.bottom);
    rndrr.renderText(std::to_string(port), Assets::get().font, {0, 0, 0, 255}, {40, 102}, rndrr.bottom);

    rndrr.renderSurface(Assets::get().button, std::nullopt, okDst, rndrr.bottom);
    rndrr.renderSurface(Assets::get().text, SDL_Rect{96, 0, 32, 16}, SDL_Rect{okDst.x + 16, okDst.y + 4, 32, 16}, rndrr.bottom);

    rndrr.renderSurface(Assets::get().net, SDL_Rect{0, Client::get().connected() ? 32 : 16, 16, 16}, SDL_Rect{2, 174, 16, 16}, rndrr.bottom);
}
