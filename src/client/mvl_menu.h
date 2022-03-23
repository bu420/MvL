#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <vector>
#include <optional>

#include "mvl_input.h"
#include "mvl_window.h"

namespace mvl {
    using Button = std::pair<SDL_Rect, std::function<void()>>;

    class Buttons {
    public:
        void reg(SDL_Rect area, std::optional<Screen> screen, std::function<void()> callback);
        void handle(Input& input);

    private:
        std::vector<Button> buttons;
    };
}
