#include <stdio.h>
#include <unistd.h>

#ifdef PLATFORM_UNIX
#include <malloc.h>
#include <stdlib.h>
#endif

#ifdef PLATFORM_MACOSX_ARM64
#include <malloc/malloc.h>
#endif

#include "Render_Engine/STL_LIB/List.h"
#include "Render_Engine/main_types/FBO.h"
#include "Render_Engine/main_types/Render_State.h"
#include "Render_Engine/STL_LIB/timer_manager.h"
#include "Render_Engine/main_types/Debuger_CLI.h"
#include "Render_Engine/GXF/GFX_Animation_core/GFX_Animation_core.h"
#include "Render_Engine/GXF/GFX_Animation_core/Animations/Animations.h"
#include "Render_Engine/GXF/PipeLine_rendering.h"
#include "Network/INet.h"

#define TOTAL_DRAM_ESP32_S2 215588

void test_callback (void* arg) {
    RenderState *rs = (RenderState*)arg;
    PipelineSetAnimation(1, (GFX_Animation){
        .indexRenderAnimation = 1,
        .timer = &(Timer){
            .name = "Test fill rainbow",
            .callback = NULL,
            .arg = NULL,
            .duration_ms = 15000,
            .inifinity = false,
            .running = true,
            .thisAnimation = true,
        },
        .arg = &(Rainbow_data){
            .fbo = rs->fbo,
            .color1 = (HSL){
                .hue = 0,
                .saturation = 255,
                .lightness = 128,
            },
            .rangeX1 = rs->fbo->size / 2,
            .rangeX2 = rs->fbo->size,
            .speed = 1.0f
        },
    });
}

int main(void) {
    printf("Hello, World!\n");
    size_t total_memory_allocd = 0;


    RenderState render_state = {
        .fbo = &(FBO){
            .size = 72
        },
        .main_timer_update_usec = 15,
        .enable_bland = true,
        .callback_render_device = NULL,
        .clear_fbo = false,
    };

    FBO_Create(render_state.fbo);
    InitTimerQueue();

    InetSock UDPAudioSock = {
        .port = 2206,
        .sizeBuffer = 1024,
    };
    UDPServerMake(&UDPAudioSock);

    Debuger_config db_conf = {
        .DebugDevice_info = &(Device){
            .Device_FBO_bind = render_state.fbo,
            .name_device = "CLI_Debug_Test_ESP32_S2"
        },
        .DebugFBO = true,
        .version = "PC_Unix_ALPHA:0.2.25",
        .DebugFullMemoryAllocd = true,
        .DebugTimerQueue = false,
        .DebugDevice = true,
        .DebugShowAnimationQueue = false,
        .sockDebug = &UDPAudioSock,
        .DebugNetwork = true
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
        .duration_ms = 32,
        .inifinity = true,
        .running = true,
    });

    AddTimer(&(Timer){
        .name = "Debug Netwotk",
        .callback = &UDPServerListen_callback,
        .arg = &UDPAudioSock,
        .duration_ms = 32,
        .inifinity = true,
        .running = true,
    });

    AddTimer(&(Timer){
        .name = "Debug Pipeline API",
        .callback = &test_callback,
        .arg = &render_state,
        .duration_ms = 5000,
        .inifinity = false,
        .callback_by_tick = true,
        .running = false,
    });


    PipelineAddAnimations(render_state.fbo, (GFX_Animation[]){
        (GFX_Animation){
        .indexRenderAnimation = 0,
        .timer = &(Timer){
            .name = "Test FFT test",
            .callback = NULL,
            .arg = NULL,
            .duration_ms = 15000,
            .inifinity = true,
            .running = true,
        },
        .callback = &drawAudioLightSpectrum,
        .arg = &(AudioEffect){
            .fbo = render_state.fbo,
            .color = (RGB888){
                .r = 0,
                .g = 255,
                .b = 154,
            },
            .SectrumData = UDPAudioSock.bufferRX,
            .SectrumSize = 72
        },
        .arg_size = sizeof(AudioEffect),
        },
        (GFX_Animation){
            .indexRenderAnimation = 0,
            .timer = &(Timer){
                .name = "Test fill rainbow",
                .callback = NULL,
                .arg = NULL,
                .duration_ms = 2000,
                .inifinity = true,
                .running = true,
            },
            .callback = &MonotoneFiilRanbow,
            .arg = &(Rainbow_data){
                .fbo = render_state.fbo,
                .color1 = (HSL){
                    .hue = 128,
                    .saturation = 255,
                    .lightness = 255,
                },
                .rangeX1 = 0,
                .rangeX2 = render_state.fbo->size,
                .speed = 0.0f
            },
            .arg_size = sizeof(Rainbow_data),
            },


    },1);





    while (1) {
        Timer_loop();
        usleep(1000);
    }

    return 0;
}