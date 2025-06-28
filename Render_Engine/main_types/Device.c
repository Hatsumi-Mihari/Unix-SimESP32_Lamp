#include "Device.h"
#include "../DeviceRender/Rpi/Rpi_WS2811.h"
#include "FBO.h"
#ifdef WS281X_RPI


void Device_Init(int countLeds) {
    init_ws2811(countLeds);
}

void Device_Render(FBO *fbo) {
    render(fbo);
}

#else
void Device_Init(int countLeds) {

}

void Device_Render(FBO *fbo) {

}
#endif