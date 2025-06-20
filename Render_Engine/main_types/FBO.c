#include "FBO.h"
#include <stdlib.h>
#ifdef __APPLE__
#include <malloc/malloc.h>
#define get_alloc_size(ptr) malloc_size(ptr)
#else
#include <malloc.h>
#define get_alloc_size(ptr) malloc_usable_size(ptr)
#endif


void FBO_Create(FBO* fbo) {
    fbo->FBO = (RGB888*) malloc((sizeof(RGB888) * fbo->size));
    for (int i = 0; i < fbo->size; i++) {
        fbo->FBO[i] = (RGB888){.r = 0, .g = 0, .b = 0};
    }
}

void FBO_Destroy(FBO* fbo) {
    free(fbo->FBO);
}

void FBO_ReCreate(FBO* fbo) {
    FBO_Destroy(fbo);
    FBO_Create(fbo);
}

size_t FBO_getAllocMem(FBO* fbo) {
    return get_alloc_size(fbo->FBO) + sizeof(FBO);
}