#include <enet/enet.h>
#include <iostream>
#include <stdexcept>
#include <functional>

#include "mvl_time.h"
#include "mvl_math.h"
#include "mvl_server.h"

using namespace mvl;

int main(int argc, char** argv) {
    try {
        if (enet_initialize()) {
            throw std::runtime_error("Failed to init ENet.");
        }

        Server& server = Server::get();

        server.start(2000);
        std::cout << "Server started on port 2000." << std::endl;

        while (true) {
            auto packets = server.update();

            for (auto packet : packets) {
                std::cout << "Received '" << packet.second << "' from " << server.convertHost(packet.first->address.host) << ":" << packet.first->address.port << "." << std::endl;
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