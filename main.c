#include <stdio.h>
#include <unistd.h>
#include <malloc/malloc.h>

#include "Render_Engine/STL_LIB/List.h"
#include "Render_Engine/Color_Spaces/HSL.h"
#include "Render_Engine/Color_Spaces/RGB888_Struct.h"
#include "Render_Engine/main_types/FBO.h"
#include "Render_Engine/main_types/Render_State.h"
#include "Render_Engine/STL_LIB/timer_manager.h"
#include "Render_Engine/main_types/Debuger_CLI.h"
#include "Render_Engine/STL_LIB/malloc_tracked.h"

#define TOTAL_DRAM_ESP32_S2 215588


int main(void) {
    printf("Hello, World!\n");
    size_t total_memory_allocd = 0;


    RenderState render_state = {
        .fbo = &(FBO){
            .size = 144
        },
        .main_timer_update_usec = 166660,
        .enable_bland = true,
    };

    FBO_Create(render_state.fbo);
    InitTimerQueue();

    Debuger_config db_conf = {
        .DebugDevice_info = &(Device){
            .Device_FBO_bind = render_state.fbo,
            .name_device = "CLI_Debug_Test_ESP32_S2"
        },
        .version = "PC_Unix_ALPHA:0.1.95",
        .DebugFullMemoryAllocd = true,
        .DebugTimerQueue = true,
        .DebugDevice = true
    };

    AddTimer(&(Timer){
        .name = "Timer Test Loop",
        .callback = &CallBackDebuger,
        .arg = &db_conf,
        .duration_ms = 1000,
        .inifinity = true,
        .running = true,
    });





    while (1) {
        Timer_loop();
        sleep(0.5);
    }

    return 0;
}