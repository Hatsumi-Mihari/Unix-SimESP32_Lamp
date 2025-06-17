#include "ColorFill.h"
#include "math.h"

void FiilColor(RGB888 *color, FBO *fbo, uint16_t rangeX1, uint16_t rangeX2) {
    uint16_t dist = abs(rangeX2 - rangeX1);
    uint16_t devider = (uint16_t)(dist / 4);
    uint16_t temp_index2 = devider * 2, temp_index3 = devider * 3;

    uint16_t extra_devider = (uint16_t)(dist % 4);
    uint16_t temp_index_Extra = (dist + rangeX1) - extra_devider;

    for (int i = 0; i < devider; i++) {
        fbo->FBO[rangeX1 + i] = *color;
        fbo->FBO[i + rangeX1 + devider] = *color;
        fbo->FBO[i + rangeX1 + temp_index2] = *color;
        fbo->FBO[i + rangeX1 + temp_index3] = *color;
    }

    for (int i = temp_index_Extra; i < rangeX2; i++) {
        fbo->FBO[i] = *color;
    }
}