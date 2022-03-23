#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <vector>

#include "mvl_math.h"

namespace mvl {
    class Input {
    public:
        void update(std::vector<SDL_Event> events);
        bool keyHeld(SDL_Scancode scancode);
        bool keyPressed(SDL_Scancode scancode);
        bool buttonHeld(uint8_t button);
        bool buttonClicked(uint8_t button);
        Vec2i mousePos();

    private:
        void updateKeyboard(std::vector<SDL_Event> events);
        void updateMouse(std::vector<SDL_Event> events);
        std::pair<bool, bool>& getKey(SDL_Scancode scancode);
        std::pair<bool, bool>& getButton(uint8_t button);

        std::map<SDL_Scancode, std::pair<bool, bool>> keys;
        std::map<uint8_t, std::pair<bool, bool>> buttons;
    };
}