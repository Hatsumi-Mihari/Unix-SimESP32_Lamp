#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H
#include <stdint.h>
#include "List.h"

typedef struct Timer {
    uint8_t id;
    const char* name;
    void (*callback)(void*);
    void *arg;
    uint64_t time_start;
    uint32_t elapsed_time;
    uint16_t duration_ms;
    bool inifinity;
    bool running;
}Timer;

void InitTimerQueue();
int64_t GetTimeNow();
void AddTimer(Timer *timer);
void RemoveTimer(uint8_t id);
void Timer_loop();
void DestroyTimerQueue();
size_t GetTimerSizeBytes_bytes();

void DebugTimerQueue();

#endif //TIMER_MANAGER_H
