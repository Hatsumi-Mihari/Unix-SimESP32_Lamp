#include "../../../main_types/FBO.h"
#include "../../../Color_Spaces/RGB888_Struct.h"
#include "../../../Color_Spaces/HSL.h"
#ifndef RAINBOW_H
#define RAINBOW_H

typedef struct Rainbow_data {
    FBO *fbo;
    HSL color1;
    HSL color2;
    uint16_t rangeX1;
    uint16_t rangeX2;
    float speed;
}Rainbow_data;

void MonotoneFiilRanbow(void *arg, uint16_t *progress);

#endif //RAINBOW_H
