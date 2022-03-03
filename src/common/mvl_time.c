#include "mvl_time.h"

#include <SDL2/SDL.h>

Clock gClock = {0};
Timeout* gTimeouts;
int gTimeoutCount = 0;
Interval* gIntervals;
int gIntervalCount = 0;

void timeInit() {
    gTimeouts = malloc(64 * sizeof(Timeout));
    gIntervals = malloc(64 * sizeof(Interval));
}

void tick() {
    int current = SDL_GetTicks64();
    gClock.delta = current - gClock.last;
    gClock.last = current;

    for (int i = 0; i < gTimeoutCount; i++) {
        if (SDL_GetTicks64() >= gTimeouts[i].timer.end) {
            gTimeouts[i].callback(gTimeouts[i].context);

            gTimeoutCount--;
            for (int j = i; j < gTimeoutCount; j++) {
                gTimeouts[j] = gTimeouts[j + 1];
            }
        }
    }

    for (int i = 0; i < gIntervalCount; i++) {
        if (SDL_GetTicks64() >= gIntervals[i].timer.end) {
            gIntervals[i].callback(gIntervals[i].context);
            gIntervals[i].timer.end = SDL_GetTicks64() + gIntervals[i].timer.interval;
        }
    }
}

void timeout(int ms, TimeoutCallback callback, void* context) {
    gTimeouts[gTimeoutCount++] = (Timeout){.callback = callback, .context = context, .timer = (Timer){.end = SDL_GetTicks64() + ms, .interval = -1}};
}

void interval(int ms, IntervalCallback callback, void* context) {
    gIntervals[gIntervalCount++] = (Interval){.callback = callback, .context = context, .timer = (Timer){.end = SDL_GetTicks64() + ms, .interval = ms}};
}