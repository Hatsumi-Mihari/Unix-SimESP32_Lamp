#ifndef RENDER_STATE_H
#define RENDER_STATE_H

#include <stdbool.h>
#include "FBO.h"

typedef struct RenderState {
    FBO* fbo;

    void* (*callback_render_device)(void*);
    uint64_t main_timer_update_usec;
    uint16_t time_render_frame;
    uint64_t drawn_frames;

    bool clear_fbo;
    bool enable_bland;
    bool signal_recreate_fbo;
}RenderState;



#endif //RENDER_STATE_H
