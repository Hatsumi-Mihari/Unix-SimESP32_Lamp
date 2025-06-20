#include "PipeLine_rendering.h"
#include "GFX_Animation_core/GFX_Animation_core.h"
#include "../../Render_Engine/STL_LIB/timer_manager.h"
#include "../main_types/Render_State.h"
#include "GFX_Functions/GFX_Functions_Pixel.h"
#include "GFX_Functions/Shaders/ColorFill.h"

void PipelinePostEffects(FBO *fbo) {

}

void PipelineRendering_Callback(void *arg) {
    RenderState *Render_State = (RenderState*)arg;
    Render_State->time_render_frame = GetTimeNow();
    GFXAnimationUpdateLoop();
    PipelinePostEffects(Render_State->fbo);
    if (Render_State->clear_fbo) {
        FiilColor(&(RGB888){.r = 0, .g = 0, .b = 0}, Render_State->fbo, 0, Render_State->fbo->size);
        Render_State->clear_fbo = false;
    }
    Render_State->time_render_frame = GetTimeNow() - Render_State->time_render_frame;
    if (Render_State->callback_render_device != NULL) Render_State->callback_render_device(Render_State->fbo);
}


void PipelineAddAnimations(FBO *fbo, GFX_Animation animations[], size_t numAnimations) {
    for (int i = 0; i < numAnimations; i++) {
        GXFAnimationAdd(&animations[i]);
    }
}

void PipelineDeleteAnimation(int ids[], int count) {
    for (int i = 0; i < count; i++) {
        GXFAnimationRemove(ids[i]);
    }
}

void PipelineDeleteAnimationGroup(int group) {
    GXFAnimationRemoveByIndexGroup(group);
}

void PipelineSetAnimationGroup(int ids[], int count, int group) {
    for (int i = 0; i < count; i++) {
        GFXAnimationSetIndexRender(ids[i], group);
    }
}

void PipelineSetAnimation(int id, GFX_Animation animations) {
    if (animations.indexRenderAnimation != -1) GFXAnimationSetIndexRender(id , animations.indexRenderAnimation);
    if (animations.arg != NULL) GFXAnimationSetArgCallback(animations.arg, id);
    if (animations.timer != NULL) GFXAnimationSetTimer(id, *animations.timer);
}
