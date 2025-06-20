#ifndef DEVICE_H
#define DEVICE_H
#include "Render_State.h"
#include "FBO.h"
#ifdef PLATFORM_UNIX
#include <malloc.h>
#include <stdlib.h>
#endif

#ifdef PLATFORM_MACOSX_ARM64
#include <malloc/malloc.h>
#endif


typedef struct Device {
    FBO *Device_FBO_bind;
    uint16_t clock_update_qsec;
    const char* name_device;

    bool enable_vsync;
}Device;

void Device_Init(Device *Device);
void Device_Destroy(Device *Device);

#endif //DEVICE_H
