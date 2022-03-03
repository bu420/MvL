#pragma once

typedef struct {
    int last;
    int delta;
} Clock;

typedef struct {
    int interval;
    int end;
} Timer;

typedef void (*TimeoutCallback)(void* context);
typedef void (*IntervalCallback)(void* context);

typedef struct {
    TimeoutCallback callback;
    void* context;
    Timer timer;
} Timeout;

typedef struct {
    IntervalCallback callback;
    void* context;
    Timer timer;
} Interval;

extern Clock clock;
extern Timeout* timeouts;
extern int timeoutCount;
extern Interval* intervals;
extern int intervalCount;

void timeInit();
void tick();
void timeout(int ms, TimeoutCallback callback, void* context);
void interval(int ms, IntervalCallback callback, void* context);