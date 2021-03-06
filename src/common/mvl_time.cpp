#include "mvl_time.h"

#include <SDL2/SDL.h>

using namespace mvl;

void Clock::init() {
    prev = SDL_GetTicks64();
}

void Clock::tick() {
    double current = (double)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
    delta = current - prev;
    prev = current;

    for (auto it = intervals.begin(); it != intervals.end();) {
        int ms = std::get<0>(*it);
        int start = std::get<1>(*it);
        auto callback = std::get<2>(*it);

        if (SDL_GetTicks64() >= start + ms) {
            start = SDL_GetTicks64();
            
            if (!callback()) {
                intervals.erase(it);
            }
            else {
                it++;
            }
        }
        else {
            it++;
        }
    }
}

double Clock::getDelta() {
    return delta;
}

void Clock::setInterval(int ms, std::function<bool()> callback) {
    intervals.emplace_back(Interval(ms, SDL_GetTicks64(), callback));
}