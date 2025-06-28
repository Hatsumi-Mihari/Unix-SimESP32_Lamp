#include "Debuger_CLI.h"
#include "Device.h"
#include "Render_State.h"
#ifdef __APPLE__
#include <malloc/malloc.h>
#define get_alloc_size(ptr) malloc_size(ptr)
#else
#include <malloc.h>
#define get_alloc_size(ptr) malloc_usable_size(ptr)
#endif
#include "FBO.h"
#include "../STL_LIB/timer_manager.h"
#include "../GXF/GFX_Animation_core/GFX_Animation_core.h"

void CallBackDebuger(void *arg) {
    Debuger_config *temp = (Debuger_config *)arg;
    if (temp->DebugFBO) {
        for (int i = 0; i < temp->DebugDevice_info->Device_FBO_bind->size; i++) {
            printf("\033[38;2;%d;%d;%dm█", temp->DebugDevice_info->Device_FBO_bind->FBO[i].r, temp->DebugDevice_info->Device_FBO_bind->FBO[i].g, temp->DebugDevice_info->Device_FBO_bind->FBO[i].b);
        }
        printf("\033[0m\n");
    }
    if (temp->DebugDevice) {
        printf("Device: %s\n", temp->DebugDevice_info->name_device);
        printf("Version Software: %s\n", temp->version);
        printf("VRAM Alloced: %lu bytes\n", get_alloc_size(temp->DebugDevice_info->Device_FBO_bind->FBO));
        printf("Led Count: %d\n", temp->DebugDevice_info->Device_FBO_bind->size);
        printf("----------------------------------------------------------\n");
    }
    if (temp->DebugNetwork) debugNetwork(temp->sockDebug);
    if (temp->DebugRenderState);
    if (temp->DebugFullMemoryAllocd) {
        temp->memoryAllocated =
            FBO_getAllocMem(temp->DebugDevice_info->Device_FBO_bind) + GXFGetSizeAnimationQueue() + TimerListGetSize() + temp->sockDebug->sizeBuffer;
        printf("Memory Allocd Total: %ld bytes\n", temp->memoryAllocated);
        printf("----------------------------------------------------------\n");
    }
    if (temp->DebugTimerQueue) DebugTimerQueue();
    if (temp->DebugShowAnimationQueue) GFXAnimationDebug();
    printf("\033[2J\033[H");
}
