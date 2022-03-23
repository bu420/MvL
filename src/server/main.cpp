#include <enet/enet.h>
#include <iostream>
#include <stdexcept>
#include <functional>

#include "mvl_time.h"
#include "mvl_math.h"
#include "mvl_server.h"

using namespace mvl;
using namespace nlohmann;

int main(int argc, char** argv) {
    try {
        if (enet_initialize()) {
            throw std::runtime_error("Failed to init ENet.");
        }

        Server server;
        server.start(2000);
        std::cout << "Server started on port 2000." << std::endl;

        // TODO: classes for each state instead.
        bool stateConnect = true;
        bool stateSettings = false;
        bool stateSelect = false;
        bool stateGame = false;

        while (true) {
            auto packets = server.update(
                // Mario joined.
                [&]() -> void {
                    std::cout << "Mario joined." << std::endl;
                    server.marioSend({{"type", "mario"}}, true);
                },
                
                // Luigi joined.
                [&]() -> void {
                    std::cout << "Luigi joined." << std::endl;
                    server.luigiSend({{"type", "luigi"}}, true);
                    server.broadcast({{"type", "ready"}}, true);
                    stateConnect = false;
                    stateSettings = true;
                },
                
                // Mario left.
                [&]() -> void {
                    std::cout << "Mario left." << std::endl;
                },
                
                // Luigi left.
                [&]() -> void {
                    std::cout << "Luigi left." << std::endl;
                }
            );

            for (auto packet : packets) {
                json data = packet.second;

                if (stateConnect) {}
                else if (stateSettings) {
                    if (server.isMario(packet.first)) {
                        
                        if (data["type"] == "up") {
                            server.luigiSend({{"type", "up"}}, true);
                        }
                        else if (data["type"] == "down") {
                            server.luigiSend({{"type", "down"}}, true);
                        }
                        else if (data["type"] == "ok") {
                            server.broadcast({{"type", "ready"}}, true);
                            stateSettings = false;
                            stateSelect = true;
                        }
                    }
                }
                else if (stateSelect) {
                    if (server.isMario(packet.first)) {
                        if (data["type"] == "left") {
                            server.luigiSend({{"type", "left"}}, true);
                        }
                        else if (data["type"] == "right") {
                            server.luigiSend({{"type", "right"}}, true);
                        }
                        else if (data["type"] == "back") {
                            server.broadcast({{"type", "back"}}, true);
                            stateSelect = false;
                            stateSettings = true;
                        }
                        else if (data["type"] == "select") {
                            server.broadcast({{"type", "ready"}}, true);
                            stateSelect = false;
                            stateGame = true;
                        }
                    }
                }
                else if (stateGame) {
                    if (data["type"] == "pos") {
                        if (server.isMario(packet.first)) {
                            server.luigiSend({{"type", "pos"}, {"x", data["x"]}, {"y", data["y"]}}, false);
                        }
                        else if (server.isLuigi(packet.first)) {
                            server.marioSend({{"type", "pos"}, {"x", data["x"]}, {"y", data["y"]}}, false);
                        }
                    }
                }
            }
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