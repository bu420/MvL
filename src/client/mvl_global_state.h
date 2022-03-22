#pragma once

#include <optional>

#include "mvl_singleton.h"

namespace mvl {
    class GlobalState : public Singleton<GlobalState> {
    public:
        enum class Role {
            Mario,
            Luigi
        };

        std::optional<Role> role;
    };
}