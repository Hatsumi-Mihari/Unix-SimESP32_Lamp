#ifndef DEBUGER_CLI_H
#define DEBUGER_CLI_H
#include <stdbool.h>
#include <stdio.h>
#include "FBO.h"
#include "Device.h"

typedef struct Debuger_config {
    const char* version;
    bool DebugDevice;
    bool DebugRenderState;
    Device* DebugDevice_info;
    bool DebugShowTimeRender;
    uint16_t *time_render;
    bool DebugTimerQueue;
    bool DebugFullMemoryAllocd;
    size_t memoryAllocated;
}Debuger_config;

void CallBackDebuger(void *arg);
void FrameBufferShow(FBO *fbo);

#endif //DEBUGER_CLI_H
