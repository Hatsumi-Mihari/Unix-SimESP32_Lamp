
#include "AudioEffect.h"
void drawAudioLightSpectrum(void *arg , uint16_t *progress) {
    AudioEffect *e = (AudioEffect*)arg;
    for (int i = 0; i < e->SectrumSize; i++) {
        e->color.lightness = e->SectrumData[i];
        e->fbo->FBO[i] = GFX_HSL2RGB(&e->color);
    }
}