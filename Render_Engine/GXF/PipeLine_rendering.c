#include "PipeLine_rendering.h"
#include "GFX_Animation_core/GFX_Animation_core.h"
#include "../../Render_Engine/STL_LIB/timer_manager.h"
#include "../main_types/Render_State.h"
#include "GFX_Animation_core/Animations/Rainbow.h"
#include "GFX_Functions/GFX_Functions_Pixel.h"
#include "GFX_Functions/Shaders/ColorFill.h"

void PipelineRendering_Callback(void *arg) {
    RenderState *Render_State = (RenderState*)arg;
    Render_State->time_render_frame = GetTimeNow();
    GFXAnimationUpdate();
    if (Render_State->clear_fbo) {
        FiilColor(&(RGB888){.r = 0, .g = 0, .b = 0}, Render_State->fbo, 0, Render_State->fbo->size);
        Render_State->clear_fbo = false;
    }
    Render_State->time_render_frame = GetTimeNow() - Render_State->time_render_frame;
    if (Render_State->callback_render_device != NULL) Render_State->callback_render_device(Render_State->fbo);
}

void PipelineMake(FBO *fbo) {
    GXFAnimationAdd(&(GFX_Animation){
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
            .fbo = fbo,
            .color1 = (HSL){
                .hue = 0,
                .saturation = 255,
                .lightness = 255,
            },
            .rangeX1 = 0,
            .rangeX2 = fbo->size / 3,
            .speed = 1.0f
        },
        .arg_size = sizeof(Rainbow_data),
    });

    GXFAnimationAdd(&(GFX_Animation){
        .indexRenderAnimation = 0,
        .timer = &(Timer){
            .name = "Test fill rainbow",
            .callback = NULL,
            .arg = NULL,
            .duration_ms = 30000,
            .inifinity = true,
            .running = true,
        },
        .callback = &MonotoneFiilRanbow,
        .arg = &(Rainbow_data){
            .fbo = fbo,
            .color1 = (HSL){
                .hue = 60,
                .saturation = 255,
                .lightness = 255,
            },
            .rangeX1 = fbo->size / 3,
            .rangeX2 = fbo->size / 3 + 20,
            .speed = 1.0f
        },
        .arg_size = sizeof(Rainbow_data),
    });

    GXFAnimationAdd(&(GFX_Animation){
    .indexRenderAnimation = 1,
    .timer = &(Timer){
        .name = "Test fill rainbow",
        .callback = NULL,
        .arg = NULL,
        .duration_ms = 50000,
        .inifinity = true,
        .running = true,
    },
    .callback = &MonotoneFiilRanbow,
    .arg = &(Rainbow_data){
        .fbo = fbo,
        .color1 = (HSL){
            .hue = 60,
            .saturation = 255,
            .lightness = 255,
        },
        .rangeX1 = fbo->size / 3 + 20,
        .rangeX2 = fbo->size,
        .speed = 1.0f
    },
    .arg_size = sizeof(Rainbow_data),
});
}
