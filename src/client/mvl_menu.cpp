#include "mvl_menu.h"

#include "mvl_input.h"

using namespace mvl;

void Buttons::reg(SDL_Rect area, std::optional<Screen> screen, std::function<void()> callback) {
    if (screen) {
        area.x += screen.value().pos.x;
        area.y += screen.value().pos.y;
    }

    buttons.push_back(Button(area, callback));
}

void Buttons::handle() {
    if (Input::get().buttonClicked(SDL_BUTTON_LEFT)) {
        Vec2i pos = Input::get().mousePos();
        SDL_Point point = {pos.x, pos.y};

        for (auto button : buttons) {
            if (SDL_PointInRect(&point, &button.first)) {
                button.second();
            }
        }
    }

    buttons.clear();
}
