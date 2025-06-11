#include "Debuger_CLI.h"
#include "Device.h"
#include "Render_State.h"
#include "malloc/malloc.h"
#include "FBO.h"
#include "../STL_LIB/timer_manager.h"

void CallBackDebuger(void *arg) {
    Debuger_config *temp = (Debuger_config *)arg;
    if (temp->DebugDevice) {
        printf("Device: %s\n", temp->DebugDevice_info->name_device);
        printf("Version Software: %s\n", temp->version);
        printf("VRAM Alloced: %lu bytes\n", malloc_size(temp->DebugDevice_info->Device_FBO_bind->FBO));
        printf("Led Count: %d\n", temp->DebugDevice_info->Device_FBO_bind->size);
        printf("----------------------------------------------------------\n");
    }
    if (temp->DebugRenderState);
    if (temp->DebugFullMemoryAllocd) {
        temp->memoryAllocated =
            FBO_getAllocMem(temp->DebugDevice_info->Device_FBO_bind) + GetTimerSizeBytes_bytes();
        printf("Memory Allocd Total: %ld bytes\n", temp->memoryAllocated);
    }
    if (temp->DebugTimerQueue) DebugTimerQueue();
}
