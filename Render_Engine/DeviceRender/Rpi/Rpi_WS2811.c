

#include "Rpi_WS2811.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#ifdef WS281X_RPI
#include <ws2811/ws2811.h>

#define GPIO_PIN 18
#define TARGET_FREQ WS2811_TARGET_FREQ
#define DMA 10

volatile ws2811_t led;
volatile ws2811_return_t ret;

uint32_t convertColor(RGB888 color) {
    return (color.r << 16) | (color.g << 8) | color.b;
}

void init_ws2811(int countLeds) {
    memset(&led, 0, sizeof(ws2811_t));

    led.freq = TARGET_FREQ;
    led.dmanum = DMA;
    led.channel[0].gpionum = GPIO_PIN;
    led.channel[0].count = countLeds;
    led.channel[0].invert = 0;
    led.channel[0].brightness = 220;
    led.channel[0].strip_type = WS2811_STRIP_GRB;

    ret = ws2811_init(&led);

    if (ret != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init() failed: %s\n", ws2811_get_return_t_str(ret));
        return;
    }
}

void render(FBO *fbo) {
    for (int i = 0; i < fbo->size; ++i) {
        led.channel[0].leds[i] = convertColor(fbo->FBO[i]);
    }

    ws2811_render(&led);
}

#endif
