#pragma once

namespace mvl {
    template<typename T> struct Vec2 {
        T x, y;

        // TODO: implement operator overloads.
    };

    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;
}