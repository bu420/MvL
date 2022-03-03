#include "mvl_time.h"

#include <SDL2/SDL.h>

Clock clock = {0};
Timeout* timeouts;
int timeoutCount = 0;
Interval* intervals;
int intervalCount = 0;

void timeInit() {
    timeouts = malloc(64 * sizeof(Timeout));
    intervals = malloc(64 * sizeof(Interval));
}

void tick() {
    int current = SDL_GetTicks64();
    clock.delta = current - clock.last;
    clock.last = current;

    for (int i = 0; i < timeoutCount; i++) {
        if (SDL_GetTicks64() >= timeouts[i].timer.end) {
            timeouts[i].callback(timeouts[i].context);

            timeoutCount--;
            for (int j = i; j < timeoutCount; j++) {
                timeouts[j] = timeouts[j + 1];
            }
        }
    }

    for (int i = 0; i < intervalCount; i++) {
        if (SDL_GetTicks64() >= intervals[i].timer.end) {
            intervals[i].callback(intervals[i].context);
            intervals[i].timer.end = SDL_GetTicks64() + intervals[i].timer.interval;
        }
    }
}

void timeout(int ms, TimeoutCallback callback, void* context) {
    timeouts[timeoutCount++] = (Timeout){.callback = callback, .context = context, .timer = (Timer){.end = SDL_GetTicks64() + ms, .interval = -1}};
}

void interval(int ms, IntervalCallback callback, void* context) {
    intervals[intervalCount++] = (Interval){.callback = callback, .context = context, .timer = (Timer){.end = SDL_GetTicks64() + ms, .interval = ms}};
}