#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H
#include <stdint.h>
#include "List.h"

typedef struct Timer {
    uint16_t id;
    const char* name;
    void (*callback)(void* arg);
    void *arg;
    uint64_t time_start;
    uint32_t elapsed_time;
    uint16_t duration_ms;
    bool inifinity;
    bool running;
    bool callback_by_tick;

    bool thisAnimation;
    bool delete_animation;
}Timer;

void InitTimerQueue();
int64_t GetTimeNow();
void AddTimer(Timer *timer);
Timer *AddTimerCopy(Timer *timer);
void RemoveTimer(uint16_t id);
void ResetTimer(Timer *timer);
void Timer_loop();
void DestroyTimerQueue();

uint16_t TimerGetProgress(Timer *timer, uint16_t max_progress);

void DebugTimerQueue();
size_t TimerListGetSize();

#endif //TIMER_MANAGER_H
