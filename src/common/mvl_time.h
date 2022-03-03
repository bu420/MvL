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

extern Clock gClock;
extern Timeout* gTimeouts;
extern int gTimeoutCount;
extern Interval* gIntervals;
extern int gIntervalCount;

void timeInit();
void tick();
void timeout(int ms, TimeoutCallback callback, void* context);
void interval(int ms, IntervalCallback callback, void* context);