#pragma once
#include "types.h"

typedef struct Timer {
    int FPS, ms;
    float DELTA, sec;
} Timer;

Timer* anim_CreateTimer(u8 fps);
void anim_UpdateTimer(Timer* timer);
void anim_DestroyTimer(Timer* timer);
