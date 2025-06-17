#include "../../Color_Spaces/RGB888_Struct.h"
#include "../../Color_Spaces/HSL.h"

#define CONST_RED_COF_ONE 329.670f
#define CONST_RED_COF_POW -0.133f
#define CONST_GREEN_COF_ONE 99.470f
#define CONST_GREEN_COF_TWO 288.122f
#define CONST_GREEN_COF_LOG 161.119f
#define CONST_GREEN_COF_POW -0.075f
#define CONST_BLUE_COF_ONE 138.518f
#define CONST_BLUE_COF_LOG 305.045f

#ifndef GFX_FUNCTIONS_PIXEL_H
#define GFX_FUNCTIONS_PIXEL_H

float GFXClamf(float x, float val_min, float val_max);
int GFXClam(int x, int val_min, int val_max);
RGB888 GFXBlandPixel(RGB888 *color1, RGB888 *color2, uint8_t factor);
RGB888 GFXBrightnessPixel(RGB888 *color1, uint8_t level);
RGB888 GFXKalvinTempf(uint16_t temp);
RGB888 GFXKalvinTemp(uint16_t temp);
RGB888 GFX_HSL2RGB(HSL *color);
RGB888 GFX_WBpixel(uint8_t value);

#endif //GFX_FUNCTIONS_PIXEL_H
