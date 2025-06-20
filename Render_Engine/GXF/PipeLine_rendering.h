#ifndef PIPELINE_RENDERING_H
#define PIPELINE_RENDERING_H
#include "../main_types/Render_State.h"
#include "GFX_Animation_core/GFX_Animation_core.h"

void PipelinePostEffects(FBO *fbo);
void PipelineRendering_Callback(void *arg);
void PipelineAddAnimations(FBO *fbo, GFX_Animation animations[], size_t numAnimations);
void PipelineDeleteAnimation(int ids[], int count);
void PipelineDeleteAnimationGroup(int group);
void PipelineSetAnimationGroup(int ids[], int count, int group);
void PipelineSetAnimation(int id, GFX_Animation animations);

#endif //PIPELINE_RENDERING_H
