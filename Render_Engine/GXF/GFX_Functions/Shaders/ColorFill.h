#include "../GFX_Functions_Pixel.h"
#include "../../../main_types/FBO.h"
#include "../../../Color_Spaces/RGB888_Struct.h"
#include "../../../Color_Spaces/HSL.h"
#ifndef COLORFILL_H
#define COLORFILL_H

void ClearFBO(FBO *fbo, RGB888 color);
void FiilColor(RGB888 *color, FBO *fbo, uint16_t rangeX1, uint16_t rangeX2);

#endif //COLORFILL_H
