#pragma once

#include <functional>
#include <vector>
#include <tuple>

namespace mvl {
    using Interval = std::tuple<int, int, std::function<bool()>>;

    class Clock {
    public:
        void init();
        void tick();
        double getDelta();
        void setInterval(int ms, std::function<bool()> callback);

    private:
        double prev;
        double delta;
        std::vector<Interval> intervals;
    };
}