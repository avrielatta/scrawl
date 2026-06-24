#pragma once
#include "types.h"
#include "txt.h"
#include "gapbuffer.h"

typedef enum e_VimMode {
    NORMAL,
    INSERT,
    VISUAL
} e_VimMode;

void input_HandleTextInput(const char *input, GapBuffer *buf);
void input_HandleKeyDown(SDL_KeyboardEvent event, GapBuffer *buffer);
