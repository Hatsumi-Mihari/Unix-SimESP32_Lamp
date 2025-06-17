#include <stdio.h>
#include <unistd.h>
#include <malloc/malloc.h>

#include "Render_Engine/STL_LIB/List.h"
#include "Render_Engine/main_types/FBO.h"
#include "Render_Engine/main_types/Render_State.h"
#include "Render_Engine/STL_LIB/timer_manager.h"
#include "Render_Engine/main_types/Debuger_CLI.h"
#include "Render_Engine/GXF/GFX_Animation_core/GFX_Animation_core.h"
#include "Render_Engine/GXF/PipeLine_rendering.h"

#define TOTAL_DRAM_ESP32_S2 215588

void test_callback (void*) {
    GXFAnimationRemoveByIndexGroup(0);
}

int main(void) {
    printf("Hello, World!\n");
    size_t total_memory_allocd = 0;


    RenderState render_state = {
        .fbo = &(FBO){
            .size = 88
        },
        .main_timer_update_usec = 16,
        .enable_bland = true,
        .callback_render_device = NULL,
        .clear_fbo = false,
    };

    FBO_Create(render_state.fbo);
    InitTimerQueue();

    Debuger_config db_conf = {
        .DebugDevice_info = &(Device){
            .Device_FBO_bind = render_state.fbo,
            .name_device = "CLI_Debug_Test_ESP32_S2"
        },
        .DebugFBO = true,
        .version = "PC_Unix_ALPHA:0.2.10",
        .DebugFullMemoryAllocd = true,
        .DebugTimerQueue = true,
        .DebugDevice = true,
        .DebugShowAnimationQueue = true
    };

    GXFAnimationInit(&render_state.clear_fbo);
    AddTimer(&(Timer){
        .name = "Timer Render Update",
        .callback = &PipelineRendering_Callback,
        .arg = &render_state,
        .duration_ms = render_state.main_timer_update_usec,
        .inifinity = true,
        .running = true,
    });

    AddTimer(&(Timer){
        .name = "Debug CallBack",
        .callback = &CallBackDebuger,
        .arg = &db_conf,
        .duration_ms = 33,
        .inifinity = true,
        .running = true,
    });

    AddTimer(&(Timer){
        .name = "Test timer for kill group animation",
        .callback = &test_callback,
        .arg = NULL,
        .duration_ms = 5000,
        .inifinity = false,
        .running = true,
        .callback_by_tick = true,
    });

    PipelineMake(render_state.fbo);



    while (1) {
        Timer_loop();
        usleep(1000);
    }

    return 0;
}