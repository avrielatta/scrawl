#pragma once
#include "types.h"
#include "txt.h"
#include "linebuffer.h"
#include "textblock.h"

typedef enum e_VimMode {
    NORMAL,
    INSERT,
    VISUAL
} e_VimMode;

/* handles basic text inputs and returns true if current line
 * had enough space to add a character
 */
bool input_HandleTextInput(const char *input, TextBlock* block);
void input_HandleKeyDown(SDL_KeyboardEvent event, TextBlock* block);
