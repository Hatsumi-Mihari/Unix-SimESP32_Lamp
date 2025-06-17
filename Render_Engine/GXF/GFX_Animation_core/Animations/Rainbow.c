#include "Rainbow.h"
#include "../../GFX_Functions/Shaders/ColorFill.h"

void MonotoneFiilRanbow(void *arg, uint16_t *progress) {
    Rainbow_data *obj = (Rainbow_data *)arg;
    obj->color1.hue =+ ((*progress * 255) / obj->speed);
    RGB888 pixel_t = GFX_HSL2RGB(&obj->color1);

    FiilColor(&pixel_t, obj->fbo, obj->rangeX1, obj->rangeX2);
}