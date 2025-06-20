#include "GFX_Functions_Pixel.h"
#include <math.h>

float GFXClamf(float x, float val_min, float val_max) {
    if (x < val_min)
        return val_min;
    if (x > val_max)
        return val_max;
    return x;
}

int GFXClam(int x, int val_min, int val_max) {
    if (x < val_min)
        return val_min;
    if (x > val_max)
        return val_max;
    return x;
}

RGB888 GFXBlandPixel(RGB888 *color1, RGB888 *color2, uint8_t factor) {
    RGB888 res;
    uint16_t inv_factor = 255 - factor;

    res.r = (uint8_t)((uint16_t)color1->r * inv_factor  + (uint16_t)color2->r * factor) / 255;
    res.g = (uint8_t)((uint16_t)color1->g * inv_factor  + (uint16_t)color2->g * factor) / 255;
    res.b = (uint8_t)((uint16_t)color1->b * inv_factor  + (uint16_t)color2->b * factor) / 255;

    return res;
}

RGB888 GFXBrightnessPixel(RGB888 *pixel, uint8_t level) {
    RGB888 temp_p;
    temp_p.r = (uint8_t)((pixel->r * level + 50) / 100);
    temp_p.g= (uint8_t)((pixel->g * level + 50) / 100);
    temp_p.b = (uint8_t)((pixel->b * level + 50) / 100);
    return temp_p;
}


RGB888 GFXKalvinTempf(uint16_t temp) {
    float temperature = temp / 100.0f;
    float red, green, blue;

    if (temperature <= 66)
    {
        red = 255;
        green = CONST_GREEN_COF_ONE * logf(temperature) - CONST_GREEN_COF_LOG;
    }
    else
    {
        red = CONST_RED_COF_ONE * pow(temperature - 60, CONST_RED_COF_POW);
        red = GFXClamf(red, 0.0f, 255.0f);
        green = CONST_GREEN_COF_TWO * powf(temperature - 60, CONST_GREEN_COF_POW);
    }
    green = GFXClamf(green, 0.0f, 255.0f);

    if (temperature >= 66)
        blue = 255.0f;
    else if (temperature <= 19)
        blue = 0.0f;
    else
    {
        blue = CONST_BLUE_COF_ONE * logf(temperature - 10) - CONST_BLUE_COF_LOG;
        blue = GFXClamf(blue, 0.0f, 255.0f);
    }

    RGB888 return_dt = {(uint8_t)red, (uint8_t)green, (uint8_t)blue};
    return return_dt;
}

RGB888 GFX_HSL2RGB(HSL *color) {
    return toRGB(color);
}

RGB888 GFX_WBpixel(uint8_t value) {
    return (RGB888){.r = value, .g = value, .b = value};
}