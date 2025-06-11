#ifndef FBO_H
#define FBO_H
#include <stdlib.h>
#include "../Color_Spaces/RGB888_Struct.h"


typedef struct FBO {
    RGB888 *FBO;
    uint16_t size;
}FBO;

void FBO_Create(FBO* fbo);
void FBO_Destroy(FBO* fbo);
void FBO_ReCreate(FBO* fbo);
size_t FBO_getAllocMem(FBO* fbo);

#endif //FBO_H
