#include "mvl_menu.h"

#include <assert.h>
#include <stdio.h>

#include "mvl_input.h"
#include "mvl_ds.h"
#include "mvl_state.h"
#include "mvl_time.h"

Button buttons[maxButtonCount];
int buttonCount = 0;

void registerButton(Button button) {
    assert(buttonCount < maxButtonCount);
    buttons[buttonCount++] = button;
}

void handleButtons() {
    if (mousePressed(SDL_BUTTON_LEFT)) {
        Vec2i pos = subVec2i(mousePos(), bottom);
        SDL_Point point = {pos.x, pos.y};

        for (int i = 0; i < buttonCount; i++) {
            if (SDL_PointInRect(&point, &buttons[i].area)) {
                if (buttons[i].callback) {
                    buttons[i].callback(buttons[i].context);
                }
                break;
            }
        }
    }

    buttonCount = 0;
}
