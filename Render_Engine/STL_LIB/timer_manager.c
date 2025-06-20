#include <unistd.h>
#include "timer_manager.h"
#include "malloc_tracked.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

volatile List* Timer_Queue;
volatile uint8_t last_id;

void InitTimerQueue() {
    Timer_Queue = (List*)malloc(sizeof(List));
    list_init(Timer_Queue, sizeof(Timer));
}

void DeleteTimerQueue() {
    list_free(Timer_Queue);
}

int64_t GetTimeNow() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000000 + now.tv_nsec / 1000;
}

void AddTimer(Timer *timer) {
    timer->id = last_id;
    timer->time_start = GetTimeNow();
    list_push(Timer_Queue, timer, false);
    last_id++;
}

Timer *AddTimerCopy(Timer *timer) {
    Timer *timer_copy = (Timer*)malloc(sizeof(Timer));
    memcpy(timer_copy, timer, sizeof(Timer));

    timer_copy->id = last_id;
    timer_copy->time_start = GetTimeNow();
    list_push(Timer_Queue, timer_copy, false);
    last_id++;
    return timer_copy;
}


void RemoveTimer(uint16_t id) {
    Timer *ElemSearch;
    for (int i = 0; i < Timer_Queue->size; i++) {
        ElemSearch = (Timer*)list_get((List*)Timer_Queue, i, false);
        if (ElemSearch->id == id) {
            list_remove((List*)Timer_Queue, i);
            return;
        }
    }
}

void ResetTimer(Timer *timer) {
    timer->elapsed_time = 0;
    timer->time_start = GetTimeNow();
}

void Timer_loop() {
    Timer *timer;
    if (Timer_Queue == NULL) return;

    for (int i = 0; i < Timer_Queue->size; i++) {
        timer = (Timer*)list_get(Timer_Queue, i, false);
        if (timer->running) {
            timer->elapsed_time = (GetTimeNow() - timer->time_start) / 1000;
        }

        if (timer->elapsed_time >= timer->duration_ms) {
            if (timer->callback_by_tick) {
                timer->callback(timer->arg);
            }
            if (timer->inifinity) {
                timer->elapsed_time = 0;
                timer->time_start = GetTimeNow();
            }else {
                if (timer->thisAnimation) {
                    timer->delete_animation = true;
                    continue;
                }
                list_remove(Timer_Queue, i);
                i--;
                continue;
            }

            if (timer->running) {
                if (!timer->thisAnimation) timer->callback(timer->arg);
            }else continue;

        }
    }
}

void DestroyTimerQueue() {
    free(Timer_Queue);
}

uint16_t TimerGetProgress(Timer *timer, uint16_t max_progres) {
    if (timer->duration_ms <= 0) return 0;
    if (timer->elapsed_time >= timer->duration_ms) return max_progres;
    return (max_progres * (timer->elapsed_time) / (timer->duration_ms));
}

void DebugTimerQueue() {
    printf("Timer queue size: %zu bytes \n", list_size((List*)Timer_Queue));
    Timer *Elem;
    for (int i = 0; i < Timer_Queue->size; i++) {
        Elem = (Timer*)list_get(Timer_Queue, i, false);
        if (Elem->thisAnimation) continue;
        printf("\tTimer id: %d / %s \n", Elem->id, Elem->name);
        printf("\t\ttime_start: %lld \n", Elem->time_start);
        printf("\t\telapsed_time: %d\n", Elem->elapsed_time);
        printf("\t\tduration_ms: %d \n", Elem->duration_ms);
        printf("\t\tinifinity: %d \n", Elem->inifinity);
        printf("\t\trunning: %d \n\n", Elem->running);

    }
}

size_t TimerListGetSize() {
    return list_size((List*)Timer_Queue);
}