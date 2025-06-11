#ifndef HSL_H
#define HSL_H
#include "RGB888_Struct.h"

typedef struct HSL {
    uint8_t hue;
    uint8_t saturation;
    uint8_t lightness;
}HSL;

int int_clamp(int x, int max, int min);

static int hue_to_rgb (int p, int q, int t);
RGB888 toRGB(HSL *pixel);

#endif //HSL_H
