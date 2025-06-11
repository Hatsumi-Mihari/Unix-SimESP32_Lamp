#include "FBO.h"
#include <stdlib.h>
#include <malloc/malloc.h>

#include "../STL_LIB/malloc_tracked.h"

void FBO_Create(FBO* fbo) {
    fbo->FBO = (RGB888*) malloc((sizeof(RGB888) * fbo->size));
}

void FBO_Destroy(FBO* fbo) {
    free(fbo->FBO);
}

void FBO_ReCreate(FBO* fbo) {
    FBO_Destroy(fbo);
    FBO_Create(fbo);
}

size_t FBO_getAllocMem(FBO* fbo) {
    return malloc_size(fbo->FBO) + sizeof(FBO);
}