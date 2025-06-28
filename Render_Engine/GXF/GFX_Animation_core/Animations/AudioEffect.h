//
// Created by Mihari Hatsumi on 28/6/25.
//

#ifndef AUDIOEFFECT_H
#define AUDIOEFFECT_H
#include <stdbool.h>
#include <stdint.h>
#include "../../../main_types/FBO.h"
#include "../../../Color_Spaces/RGB888_Struct.h"
#include "../../../Color_Spaces/HSL.h"
#include "../../GFX_Functions/GFX_Functions_Pixel.h"

typedef struct AudioEffect {
    uint8_t *SectrumData;
    HSL color;
    uint16_t SectrumSize;
    uint8_t mix;
    FBO *fbo;
    bool *update;
}AudioEffect;

void drawAudioLightSpectrum(void *arg , uint16_t *progress);

#endif //AUDIOEFFECT_H
