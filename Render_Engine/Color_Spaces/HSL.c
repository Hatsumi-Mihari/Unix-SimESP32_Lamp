#include "HSL.h"
#define SCALE 1000

int int_clamp(int x, int max, int min) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

int hue_to_rgb(int p, int q, int t) {
    if (t < 0)   t += 360;
    if (t >= 360) t -= 360;

    if (t < 60)
        return p + ((q - p) * t * SCALE / 60 + SCALE/2) / SCALE;

    if (t < 180)
        return q;

    if (t < 240)
        return p + ((q - p) * (240 - t) * SCALE / 60 + SCALE/2) / SCALE;

    return p;
}

RGB888 toRGB(HSL *pixel) {
    RGB888 result;

    uint8_t r, g, b;
    uint8_t value = ((24 * pixel->hue / 17) / 60) % 6;
    uint8_t vmin = (long)pixel->lightness - pixel->lightness * pixel->saturation / 255;
    uint8_t a = (long)pixel->lightness * pixel->saturation / 255 * (pixel->hue * 24 / 17 % 60) / 60;
    uint8_t vinc = vmin + a;
    uint8_t vdec = pixel->lightness - a;
    switch (value) {
        case 0: r = pixel->lightness; g = vinc; b = vmin; break;
        case 1: r = vdec; g = pixel->lightness; b = vmin; break;
        case 2: r = vmin; g = pixel->lightness; b = vinc; break;
        case 3: r = vmin; g = vdec; b = pixel->lightness; break;
        case 4: r = vinc; g = vmin; b = pixel->lightness; break;
        case 5: r = pixel->lightness; g = vmin; b = vdec; break;
    }
    result.r = r;
    result.g = g;
    result.b = b;
    return result;
}

