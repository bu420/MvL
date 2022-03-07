#pragma once

#include <functional>
#include <vector>
#include <tuple>

#include "mvl_singleton.h"

namespace mvl {
    using Interval = std::tuple<int, int, std::function<bool()>>;

    class Clock : public Singleton<Clock> {
    public:
        void init();
        void tick();
        int getDelta();
        void setInterval(int ms, std::function<bool()> callback);

    private:
        int prev;
        int delta;
        std::vector<Interval> intervals;
    };
}