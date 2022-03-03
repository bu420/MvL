#include "mvl_menu.h"

#include <assert.h>
#include <stdio.h>

#include "mvl_input.h"
#include "mvl_ds.h"
#include "mvl_state.h"
#include "mvl_time.h"

Button gButtons[gMaxButtonCount];
int gButtonCount = 0;

void registerButton(Button button) {
    assert(gButtonCount < gMaxButtonCount);
    gButtons[gButtonCount++] = button;
}

void handleButtons() {
    if (mousePressed(SDL_BUTTON_LEFT)) {
        Vec2i pos = subVec2i(mousePos(), gBottom);
        SDL_Point point = {pos.x, pos.y};

        for (int i = 0; i < gButtonCount; i++) {
            if (SDL_PointInRect(&point, &gButtons[i].area)) {
                if (gButtons[i].callback) {
                    gButtons[i].callback(gButtons[i].context);
                }
                break;
            }
        }
    }

    gButtonCount = 0;
}
