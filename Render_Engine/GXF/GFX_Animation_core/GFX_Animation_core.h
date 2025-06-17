#ifndef GFX_ANIMATION_CORE_H
#define GFX_ANIMATION_CORE_H
#include <stdint.h>
#include "../../STL_LIB/timer_manager.h"

typedef struct GFX_Animation {
    uint16_t indexRenderAnimation;
    Timer *timer;
    uint16_t progress;
    void (*callback)(void* arg, uint16_t* progress);
    void *arg;
    size_t arg_size;
}GFX_Animation;

void GXFAnimationInit(bool *flag_clear_fbo);
void GXFAnimationAdd(GFX_Animation* animation);
void GXFAnimationRemove(int indexList);
void GFXAnimationRemoveByLinkElem(GFX_Animation *link, int index);
void GXFAnimationRemoveByIndexGroup(int indexAnimation);
void GFXAnimationUpdate();

void GFXAnimationDebug();
size_t GXFGetSizeAnimationQueue();


#endif //GFX_ANIMATION_CORE_H
