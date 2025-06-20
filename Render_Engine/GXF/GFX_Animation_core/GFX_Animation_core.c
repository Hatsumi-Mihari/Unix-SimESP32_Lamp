#include "GFX_Animation_core.h"

#include <stdlib.h>
#include <string.h>

#include "../../STL_LIB/List.h"

volatile List *GFX_AnimationList;
volatile bool *flagClearFBO;

void GXFAnimationInit(bool *flag_clear_fbo) {
    GFX_AnimationList = (List*)malloc(sizeof(List));
    list_init(GFX_AnimationList, sizeof(GFX_Animation));
    flagClearFBO = flag_clear_fbo;
}

void GXFAnimationAdd(GFX_Animation* animation) {
    GFX_Animation* animation_new = (GFX_Animation*)malloc(sizeof(GFX_Animation));
    memcpy(animation_new, animation, sizeof(GFX_Animation));
    animation_new->timer = AddTimerCopy(animation->timer);
    animation_new->timer->thisAnimation = true;

    if (animation->arg && animation->arg_size > 0) {
        animation_new->arg = malloc(animation->arg_size);
        memcpy(animation_new->arg, animation->arg, animation->arg_size);
    }else {
        animation_new->arg = NULL;
    }

    list_push((List*)GFX_AnimationList, animation_new, false);
}

void GXFAnimationRemove(int indexList) {
    GFX_Animation *elem = (GFX_Animation*)list_get((List*)GFX_AnimationList, indexList, false);
    if (elem->arg != NULL) {
        free(elem->arg);
        elem->arg = NULL;
    }
    if (elem->timer != NULL) {
        RemoveTimer(elem->timer->id);
        elem->timer = NULL;
    }
    list_remove((List*)GFX_AnimationList, indexList);
}

void GFXAnimationRemoveByLinkElem(GFX_Animation *link, int index) {
    if (link->arg != NULL) {
        free(link->arg);
        link->arg = NULL;
    }
    if (link->timer != NULL) {
        RemoveTimer(link->timer->id);
        link->timer = NULL;
    }
    list_remove((List*)GFX_AnimationList, index);
}

void GXFAnimationRemoveByIndexGroup(int indexAnimation) {
    GFX_Animation *elem;
    for (int i = 0; i < GFX_AnimationList->size; i++) {
        elem = (GFX_Animation*)list_get((List*)GFX_AnimationList, i, false);
        if (elem->indexRenderAnimation == indexAnimation) {
            GFXAnimationRemoveByLinkElem(elem, i);
            i--;
        }
    }
    if (flagClearFBO != NULL) *flagClearFBO = true;
}


void GFXAnimationUpdateLoop() {
    GFX_Animation *elem;
    for (int i = 0; i < GFX_AnimationList->size; i++) {
        elem = (GFX_Animation*)list_get((List*)GFX_AnimationList, i, false);
        if (elem->timer->delete_animation) {
            GXFAnimationRemove(i);
            if (flagClearFBO != NULL) *flagClearFBO = true;
            i--;
            continue;
        };
        if (elem->callback) {
            elem->progress = TimerGetProgress(elem->timer, 1000);
            elem->callback(elem->arg, &elem->progress);
        }
    }
}

void GFXAnimationDebug() {
    GFX_Animation *elem;
    printf("\n----------------------------------------------------------\n");
    printf("Animation debug\nMemory Alloced: %lu bytes\n", list_size((List*)GFX_AnimationList));
    for (int i = 0; i < GFX_AnimationList->size; i++) {
        elem = (GFX_Animation*)list_get((List*)GFX_AnimationList, i, false);
        printf("\t%s\n", elem->timer->name);
        printf("\t\tIndex: %d\n", i);
        printf("\t\tIndex render: %d\n", elem->indexRenderAnimation);
        printf("\t\tProgress: %d\n", elem->progress / 10);
        printf("\t\tElapsed_time: %d ms\n", elem->timer->elapsed_time);
        printf("\t\tDuration_ms: %d ms\n", elem->timer->duration_ms);
        printf("\t\tinifinity: %d \n", elem->timer->inifinity);
        printf("\t\trunning: %d \n\n", elem->timer->running);
    }
    elem = NULL;
}


void GFXAnimationSetIndexRender(int indexAnimation, int indexRender){
    GFX_Animation *elem = (GFX_Animation*)list_get((List*)GFX_AnimationList, indexAnimation, false);
    elem->indexRenderAnimation = indexRender;
}

void GFXAnimationSetArgCallback(void *arg, int index) {
    GFX_Animation *elem = (GFX_Animation*)list_get((List*)GFX_AnimationList, index, false);
    if (arg != NULL) {
        memcpy(elem->arg, arg, elem->arg_size);
    }
}

void GFXAnimationSetTimer(int index, Timer timer) {
    GFX_Animation *elem = (GFX_Animation*)list_get((List*)GFX_AnimationList, index, false);
    int id_timer = elem->timer->id;
    memcpy(elem->timer, &timer, sizeof(Timer));
    elem->timer->id = id_timer;
    ResetTimer(elem->timer);
}

size_t GXFGetSizeAnimationQueue() {
    return list_size((List*)GFX_AnimationList);
}

size_t GFXGetCountAnimation() {
    return GFX_AnimationList->size;
}