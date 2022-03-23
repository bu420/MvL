#pragma once

#include <optional>

namespace mvl {
    class GlobalState {
    public:
        enum class Role {
            Mario,
            Luigi
        };

        std::optional<Role> role;
    };
}