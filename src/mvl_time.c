#include "mvl_time.h"

#include <SDL2/SDL.h>

void tick(Clock* clock) {
    int current = SDL_GetTicks64();
    clock->delta = current - clock->last;
    clock->last = current;
}