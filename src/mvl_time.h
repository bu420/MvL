#pragma once

typedef struct {
    int last;
    int delta;
} Clock;

typedef struct {
    int interval;
    int end;
} Timer;

void tick(Clock* clock);