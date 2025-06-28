
#include "AudioEffect.h"
void drawAudioLightSpectrum(void *arg , uint16_t *progress) {
    AudioEffect *e = (AudioEffect*)arg;
    for (int i = 0; i < e->SectrumSize; i++) {
        e->fbo->FBO[i] = GFXBrightnessPixel(&e->color, e->SectrumData[i]);
    }
}