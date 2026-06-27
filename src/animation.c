#include <stdlib.h>

#include <SDL3/SDL.h>

#include "animation.h"
#include "types.h"

Timer* anim_CreateTimer(u8 fps) {
    Timer* newTimer = malloc(sizeof(Timer));
    newTimer->FPS = fps;
    newTimer->DELTA = 1.0f/fps;
    newTimer->sec = 1.0f;
    newTimer->ms = 0;

    return newTimer;
}

void anim_UpdateTimer(Timer* timer) {
    timer->ms = SDL_GetTicks();
    timer->sec = timer->ms / 1000.0f;
}

void anim_DestroyTimer(Timer* timer) {
    free(timer);
}
