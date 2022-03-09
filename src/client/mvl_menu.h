#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <vector>
#include <optional>

#include "mvl_singleton.h"
#include "mvl_renderer.h"

namespace mvl {
    using Button = std::pair<SDL_Rect, std::function<void()>>;

    class Buttons : public Singleton<Buttons> {
    public:
        void reg(SDL_Rect area, std::optional<Screen> screen, std::function<void()> callback);
        void handle();

    private:
        std::vector<Button> buttons;
    };
}
