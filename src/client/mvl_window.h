#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "mvl_math.h"
#include "mvl_singleton.h"

namespace mvl {
    class Window : public Singleton<Window> {
    public:
        void init(std::string title);
        void update();
        void setIcon(SDL_Surface* icon);

        SDL_Window* window;
        Vec2i size;
    };
}