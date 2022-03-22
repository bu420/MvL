#pragma once

#include "mvl_state.h"

namespace mvl {
    class ConnectState : public State {
    public:
        void init() override;
        void update() override;
        void render() override;

    private:
    };
}