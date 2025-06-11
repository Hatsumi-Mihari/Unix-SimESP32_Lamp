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
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    timer->id = last_id;
    timer->time_start = GetTimeNow();

    list_push(Timer_Queue, timer, false);
    last_id++;
}

void RemoveTimer(uint8_t id) {
    Timer *ElemSearch;
    for (int i = 0; i < Timer_Queue->size; i++) {
        ElemSearch = (Timer*)list_get(Timer_Queue, i, false);
        if (ElemSearch->id = id) {
            list_remove(Timer_Queue, i);
            free(ElemSearch);
            return;
        }
    }
}

void Timer_loop() {
    Timer *timer;
    if (Timer_Queue == NULL) return;

    for (int i = 0; i < Timer_Queue->size; i++) {
        timer = (Timer*)list_get(Timer_Queue, i, false);
        if (timer->elapsed_time >= timer->duration_ms) {
            if (timer->running) {
                timer->callback(timer->arg);
            }

            if (timer->inifinity) {
                timer->elapsed_time = 0;
                timer->time_start = GetTimeNow();
            }else {
                list_remove(Timer_Queue, i);
                i--;
                continue;
            }
        }

        if (timer->running) {
            timer->elapsed_time = (GetTimeNow() - timer->time_start) / 1000;
        }
    }
}

void DestroyTimerQueue() {
    free(Timer_Queue);
}

size_t GetTimerSizeBytes_bytes() {
    return (Timer_Queue->size * Timer_Queue->element_size) + sizeof(List);
}

void DebugTimerQueue() {
    printf("Timer queue size: %zu bytes \n", GetTimerSizeBytes_bytes());
    Timer *Elem;
    for (int i = 0; i < Timer_Queue->size; i++) {
        Elem = (Timer*)list_get(Timer_Queue, i, false);
        printf("\tTimer id: %d / %s \n", Elem->id, Elem->name);
        printf("\t\ttime_start: %lld \n", Elem->time_start);
        printf("\t\telapsed_time: %d\n", Elem->elapsed_time);
        printf("\t\tduration_ms: %d \n", Elem->duration_ms);
        printf("\t\tinifinity: %d \n", Elem->inifinity);
        printf("\t\trunning: %d \n\n", Elem->running);

    }

    printf("\033[2J\033[H");
}