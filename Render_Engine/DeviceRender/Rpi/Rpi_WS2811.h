//
// Created by Mihari Hatsumi on 28/6/25.
//

#ifndef RPI_WS2811_H
#define RPI_WS2811_H
#include "../../Color_Spaces/RGB888_Struct.h"
#include "../../main_types/FBO.h"


uint32_t convertColor(RGB888 color);
void init_ws2811(int countLeds);
void render(FBO *fbo);
#ifdef WS281X_RPI
#endif
#endif //RPI_WS2811_H
